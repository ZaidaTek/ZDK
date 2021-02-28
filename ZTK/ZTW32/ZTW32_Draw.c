/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_DRAW_C_INCLUDED
#define ZTW32_DRAW_C_INCLUDED

#include "ZTW32__Runtime.h"

void ZTW32_DrawFontLoad(void) {
    rZT_FONT* lFont;
    ZTK_FontLoad(lFont = rZTK_Host.user.font);
    SelectObject(rZTW32_Host.dc.buffer, (HFONT)lFont->runtime);
    ZT_COLOR lColor = lFont->color;
    ZTM_PixelsConvert(&lColor, &lColor, 1, rZTK_Host.user.palette, ZTK_PALETTE_BRUSH);
    SetTextColor(rZTW32_Host.dc.buffer, lColor & ZTM_ColorMaskC(ZTK_PALETTE_BRUSH));
    lColor = lFont->colorBk;
    ZTM_PixelsConvert(&lColor, &lColor, 1, rZTK_Host.user.palette, ZTK_PALETTE_BRUSH);
    SetBkColor(rZTW32_Host.dc.buffer, lColor & ZTM_ColorMaskC(ZTK_PALETTE_BRUSH));
    SetBkMode(rZTW32_Host.dc.buffer, (lFont->style & ZTK_FONT_STYLE_OPAQUE) ? OPAQUE : TRANSPARENT);
}
void ZTW32_DrawExit(void) {
    DeleteDC(rZTW32_Host.dc.buffer);
    DeleteDC(rZTW32_Host.dc.pipe);
    DeleteDC(rZTW32_Host.dc.font);
    ReleaseDC(rZTW32_Host.window.handle, rZTW32_Host.dc.main);
}
void ZTW32_DrawSize(void) {
    HBITMAP lSize = CreateCompatibleBitmap(rZTW32_Host.dc.main, rZTK_Host.rect.w, rZTK_Host.rect.h);
    SelectObject(rZTW32_Host.dc.buffer, lSize);
    DeleteObject(SelectObject(rZTW32_Host.dc.buffer, GetStockObject(DC_BRUSH)));
    ZTK_BackgroundColor(rZTK_Host.user.background); // can this be skipped, and put in init instead?
    ZTW32_DrawFontLoad(); // this too?
}
void ZTW32_DrawInit(void) {
    rZTW32_Host.dc.main = GetDC(rZTW32_Host.window.handle);
    rZTW32_Host.dc.font = CreateCompatibleDC(rZTW32_Host.dc.main);
    rZTW32_Host.dc.pipe = CreateCompatibleDC(rZTW32_Host.dc.main);
    rZTW32_Host.dc.buffer = CreateCompatibleDC(rZTW32_Host.dc.main);
}
void ZTW32_DrawPresent(void) {
    BitBlt(rZTW32_Host.dc.main, 0, 0, rZTK_Host.rect.w, rZTK_Host.rect.h, rZTW32_Host.dc.buffer, 0, 0, SRCCOPY);
    RedrawWindow(rZTW32_Host.window.handle, &(rZTW32_Host.window.dimensions), NULL, RDW_UPDATENOW);
}
void ZTW32_DrawClear(void) {
    FillRect(rZTW32_Host.dc.buffer, &(rZTW32_Host.window.dimensions), NULL);
}
UINT ZTW32_DrawTextFlag(ZT_FLAG iFontStyle) {
    UINT lDTFlags = DT_NOPREFIX;
    if (iFontStyle & ZTK_FONT_STYLE_ALIGN_RIGHT) {lDTFlags |= DT_RIGHT;} else {if (iFontStyle & ZTK_FONT_STYLE_ALIGN_CENTER) {lDTFlags |= DT_CENTER;} else {lDTFlags |= DT_LEFT;}}
    if (iFontStyle & ZTK_FONT_STYLE_VALIGN_BOTTOM) {lDTFlags |= DT_BOTTOM;} else {if (iFontStyle & ZTK_FONT_STYLE_VALIGN_CENTER) {lDTFlags |= DT_VCENTER;} else {lDTFlags |= DT_TOP;}}
    if (iFontStyle & ZTK_FONT_STYLE_BREAK_WORDS) {lDTFlags |= DT_WORDBREAK;}
    if (iFontStyle & ZTK_FONT_STYLE_SINGLE_LINE) {lDTFlags |= DT_SINGLELINE;}
    if (!(iFontStyle & ZTK_FONT_STYLE_CLIP)) {lDTFlags |= DT_NOCLIP;}
    return lDTFlags;
}
void ZTW32_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox) {
    ZTK_FontLoad(rZTK_Host.user.font);
    UINT lDTFlags = ZTW32_DrawTextFlag(rZTK_Host.user.font->style);
    RECT lW32Rect;
    RECT* lW32RectPtr = &lW32Rect;
    if (iTextBox != NULL) {
        lW32Rect.left = iTextBox->x;
        lW32Rect.top = iTextBox->y;
        lW32Rect.right = lW32Rect.left + iTextBox->w;
        lW32Rect.bottom = lW32Rect.top + iTextBox->h;
    } else {
        lW32RectPtr = &(rZTW32_Host.window.dimensions);
    }
    DrawText(rZTW32_Host.dc.buffer, (const char*)iText, -1, lW32RectPtr, lDTFlags);
}
void ZTW32_DrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize) {
    ZTK_FontLoad(rZTK_Host.user.font);
    RECT lW32Rect;
    lW32Rect.top = 0;
    lW32Rect.left = 0;
    UINT lDTFlags = ZTW32_DrawTextFlag(rZTK_Host.user.font->style) | DT_CALCRECT;
    DrawText(rZTW32_Host.dc.buffer, (const char*)iText, -1, &lW32Rect, lDTFlags);
    oTextSize->x = lW32Rect.right;
    oTextSize->y = lW32Rect.bottom;
}
void ZTW32_DrawW32Bitmap(const HBITMAP iBitmap, const ZT_POINT* iBitmapSize, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
    if (rZTK_Host.system.renderer != ZTK_RENDERER_SYSTEM) {return;}
    static HBITMAP lLastBitmap = NULL;
    ZT_RECT lTarget;
    if (iTarget == NULL) {
        ZTM_RectZeroPos(&lTarget);
        ZTM_RectCopySize(&(rZTK_Host.rect), &lTarget);
        iTarget = &lTarget;
    }
    if (iBitmapSize == NULL) {iBitmapSize = (ZT_POINT*)&(lTarget.w);} // shouldnt this be iTarget instead?
    if (lLastBitmap != iBitmap) {SelectObject(rZTW32_Host.dc.pipe, (lLastBitmap = iBitmap));}
    switch (iBlendmode) {
        case ZTK_BLENDMODE_ALPHA: {
                BLENDFUNCTION lBlend;
                lBlend.AlphaFormat = AC_SRC_ALPHA;
                lBlend.BlendFlags = 0x0;
                lBlend.BlendOp = AC_SRC_OVER;
                lBlend.SourceConstantAlpha = 0xff;
                AlphaBlend(rZTW32_Host.dc.buffer, iTarget->x, iTarget->y, iTarget->w, iTarget->h, rZTW32_Host.dc.pipe, 0, 0, iBitmapSize->x, iBitmapSize->y, lBlend);
            }
            return;
        case ZTK_BLENDMODE_BLOT:
            BitBlt(rZTW32_Host.dc.buffer, iTarget->x, iTarget->y, iTarget->w, iTarget->h, rZTW32_Host.dc.pipe, 0, 0, SRCCOPY);
            return;
        default:
            return;
    }
}
void ZTW32_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
    HBITMAP lBitmap = CreateBitmap(iDimensions->x, iDimensions->y, 1, 32, (void*)iPixels);
    ZTW32_DrawW32Bitmap(lBitmap, iDimensions, iTarget, iBlendmode);
    DeleteObject(lBitmap);
}
void ZTW32_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
    HBITMAP lBitmap = CreateBitmap(iSurface->block.x, iSurface->block.y, 1, 32, (void*)iSurface->pixels);
    ZTW32_DrawW32Bitmap(lBitmap, &(iSurface->block), iTarget, iBlendmode);
    DeleteObject(lBitmap);
}
void ZTW32_DrawSprite(const rZT_SPRITE* iSprite, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
    switch (iSprite->type) {
        case ZTK_SPRITE_TYPE_SYSTEM: ZTW32_DrawW32Bitmap((const HBITMAP)iSprite->data, &(iSprite->block), iTarget, iBlendmode); return;
        case ZTK_SPRITE_TYPE_PIXELS: ZTW32_DrawPixels((const ZT_COLOR*)iSprite->data, &(iSprite->block), iTarget, iBlendmode); return;
        default: return;
    }
}
void ZTW32_SpriteFree(rZT_SPRITE* iSprite) {
    DeleteObject((HBITMAP)iSprite->data);
}
rZT_SPRITE* ZTW32_Sprite(const ZT_COLOR* iPixels, const ZT_POINT* iBlock, ZT_FLAG iPalette) {
    ZT_INDEX lLength;
    ZT_COLOR* lBuffer;
    rZT_SPRITE* lSprite = ZTM8_New(sizeof(rZT_SPRITE));
    lSprite->type = ZTK_SPRITE_TYPE_SYSTEM;
    lSprite->palette = rZTK_Host.system.palette;
    lBuffer = ZTM32_New(lLength = (lSprite->block.x = iBlock->x) * (lSprite->block.y = iBlock->y));
    ZTM_PixelsConvert(iPixels, lBuffer, lLength, iPalette, rZTK_Host.system.palette);
    ZTM_PixelsBlendAlpha(lBuffer, lBuffer, lLength, rZTK_Host.system.palette);
    lSprite->data = CreateBitmap(iBlock->x, iBlock->y, 1, 32, (void*)lBuffer);
    ZTM32_Free(lBuffer);
    return lSprite;
}

// INTERNAL-ONLY FUNCTIONS
void ZTW32_DrawClearColor(ZT_COLOR iColor) {
    ZT_COLOR lColor = ZTM_ColorConvert(iColor, rZTK_Host.user.palette, ZTK_PALETTE_BRUSH) & ZTM_ColorMaskC(ZTK_PALETTE_BRUSH);
    //SelectObject(lBuffer, GetStockObject(DC_BRUSH)); // is this maybe needed if DrawText is being used?
    SetDCBrushColor(rZTW32_Host.dc.buffer, lColor);
}
ZT_FLAG ZTW32_DrawPaletteFromW32Bitmap(const BITMAPINFO* iBitmapinfo) {
    ZT_FLAG lPalette = ZTM_PALETTE_UNKNOWN;
    ZT_INDEX lChannels = 0;
    ZT_COLOR lRGB = 0x0;
    switch (iBitmapinfo->bmiHeader.biBitCount) {
        case 32:
            lPalette |= (ZTM_PALETTE_A << 12);
            if (iBitmapinfo->bmiHeader.biCompression == BI_BITFIELDS) {
                lChannels = 3;
            } else {
                lPalette |= ZTM_PALETTE_0RGB;
                return lPalette;
            }
            break;
        case 24: lPalette |= ZTM_PALETTE_0RGB; return lPalette;
        default: return lPalette;
    }
    for (ZT_INDEX i = 0; i < lChannels; i++) {
        ZT_COLOR lRed = ((iBitmapinfo->bmiColors) + i)->rgbRed & 0xff;
        ZT_COLOR lGreen = ((iBitmapinfo->bmiColors) + i)->rgbGreen & 0xff;
        ZT_COLOR lBlue = ((iBitmapinfo->bmiColors) + i)->rgbBlue & 0xff;
        lRGB <<= 4;
        if (lRed && !(lGreen) && !(lBlue) && !(lRGB & 0x111)) {
            lRGB |= 0x1;
        } else if (lGreen && !(lRed) && !(lBlue) && !(lRGB & 0x222)) {
            lRGB |= 0x2;
        } else if (lBlue && !(lGreen) && !(lRed) && !(lRGB & 0x444)) {
            lRGB |= 0x4;
        }
    }
    lPalette |= (lRGB & 0xfff);
    return lPalette;
}
ZT_SURFACE* ZTW32_SurfaceFromW32Bitmap(const HBITMAP iBitmap, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = ZTM8_New(sizeof(ZT_SURFACE));
    BITMAPINFO lBitmapInfo;
    ZTM8_Zero(&lBitmapInfo, sizeof(BITMAPINFO));
    lBitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    GetDIBits(rZTW32_Host.dc.pipe, iBitmap, 0, 0, NULL, &lBitmapInfo, DIB_RGB_COLORS);
    ZT_INDEX lWidth = (lSurface->block.x = lBitmapInfo.bmiHeader.biWidth);
    ZT_INDEX lHeight = (lSurface->block.y = lBitmapInfo.bmiHeader.biHeight);
    ZT_BOOL lReadTD = ZT_FALSE;
    if (lBitmapInfo.bmiHeader.biHeight < 0) {lHeight = -lHeight; lReadTD = ZT_TRUE;}
    switch (lBitmapInfo.bmiHeader.biBitCount) {
        case 32:
            lSurface->pixels = ZTM32_New(((lWidth * 32 + 31) / 32) * 4 * lHeight);
            for (ZT_INDEX y = 0; y < lHeight; y++) {
                ZT_INDEX lOffset = lWidth * ((lReadTD != ZT_TRUE) ? (lHeight - 1 - y) : y);
                GetDIBits(rZTW32_Host.dc.pipe, iBitmap, y, 1, (void*)&(lSurface->pixels[lOffset]), &lBitmapInfo, DIB_RGB_COLORS);
            }
            if (oPalette != NULL) {*oPalette = ZTW32_DrawPaletteFromW32Bitmap(&lBitmapInfo);}
            break;
        default:
            lSurface->pixels = ZTM32_Init(lWidth * lHeight, 0x0);
            break;
    }
	return lSurface;
}
ZT_SURFACE* ZTW32_SurfaceFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
    rZT_FONT* lFont;
    ZTK_FontLoad(lFont = ZTK_FONTGET(iFont));
    SelectObject(rZTW32_Host.dc.font, lFont->runtime);
    RECT lW32Rect;
    lW32Rect.top = 0;
    lW32Rect.left = 0;
    DrawText(rZTW32_Host.dc.font, (const char*)iText, -1, &lW32Rect, ZTW32_DrawTextFlag(lFont->style) | DT_CALCRECT);
    if (!lW32Rect.right) {return ZTM_SurfaceNewFillFromIntegers(0, lW32Rect.bottom, 0x0);}
    HBITMAP lBitmap = CreateCompatibleBitmap(rZTW32_Host.dc.main, lW32Rect.right, lW32Rect.bottom);
    ZT_FLAG lUserPalette = rZTK_Host.user.palette;
    HBRUSH lBrush = CreateSolidBrush(ZTM_ColorConvert(lFont->colorBk, lUserPalette, ZTK_PALETTE_BRUSH) & ZTM_ColorMaskC(ZTK_PALETTE_BRUSH));
    SelectObject(rZTW32_Host.dc.font, lBitmap);
    FillRect(rZTW32_Host.dc.font, &lW32Rect, lBrush);
    SetBkMode(rZTW32_Host.dc.font, TRANSPARENT);
    SetTextColor(rZTW32_Host.dc.font, ZTM_ColorConvert(lFont->color, lUserPalette, ZTK_PALETTE_BRUSH) & ZTM_ColorMaskC(ZTK_PALETTE_BRUSH));
    DrawText(rZTW32_Host.dc.font, (const char*)iText, -1, &lW32Rect, ZTW32_DrawTextFlag(lFont->style));
    ZT_FLAG lPalette;
    lSurface = ZTW32_SurfaceFromW32Bitmap(lBitmap, &lPalette);
    if (lFont->style & ZTK_FONT_STYLE_OPAQUE) {
        ZTM_SurfaceOpacity(lSurface, lPalette, ZTM_ColorA(lFont->color, lUserPalette));
        ZT_COLOR lColorBk = ZTM_ColorConvert(lFont->colorBk, lUserPalette, lPalette);
        ZT_COLOR lColorBkSearch = (lColorBk & ZTM_ColorMaskC(lPalette)) | (ZTM_ColorA(lFont->color, lUserPalette) << ZTM_ColorShiftA(lPalette));
        ZTM_SurfaceReplaceColor(lSurface, lColorBkSearch, lColorBk);
    } else {
        ZTM_SurfaceOpacityFromColor(lSurface, lPalette, ZTM_ColorConvert(lFont->colorBk, lUserPalette, lPalette), 0x0, ZTM_ColorA(lFont->color, lUserPalette));
        ZTM_SurfaceReplaceOpaqueColors(lSurface, lPalette, ZTM_ColorConvert(lFont->color, lUserPalette, lPalette), 0x1);
    }
    if (oPalette != NULL) {*oPalette = lPalette;}
    DeleteObject(lBrush);
    DeleteObject(lBitmap);
    return lSurface;
}
void ZTW32_SizeFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_POINT* oSize) {
    rZT_FONT* lFont;
    ZTK_FontLoad(lFont = ZTK_FONTGET(iFont));
    SelectObject(rZTW32_Host.dc.font, lFont->runtime);
    RECT lW32Rect;
    lW32Rect.left = (lW32Rect.top = 0);
    DrawText(rZTW32_Host.dc.font, (const char*)iText, -1, &lW32Rect, ZTW32_DrawTextFlag(lFont->style) | DT_CALCRECT);
    oSize->x = lW32Rect.right;
    oSize->y = lW32Rect.bottom;
}

#endif // ZTW32_DRAW_C_INCLUDED
