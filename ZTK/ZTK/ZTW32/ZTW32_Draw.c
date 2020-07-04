/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_DRAW_C_INCLUDED
#define ZTW32_DRAW_C_INCLUDED

#include "ZTW32/ZTW32__Runtime.h"

// PUBLIC FUNCTIONS
void ZTW32_DrawLoadColors(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->dc.buffer != NULL) {
		    ZTW32_DrawColor((gZTW32_RTime->owner->user.options & ZTK_WINDOW_BACKGROUND_ENABLED) ? gZTW32_RTime->owner->user.background : ZTK_DEFAULT_WINDOW_BACKGROUND_COLOR);
		}
	}
}
void ZTW32_DrawLoadFont(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->dc.buffer != NULL) {
            if (gZTW32_RTime->owner->user.font == NULL) {gZTW32_RTime->owner->user.font = &(gZTW32_RTime->owner->system.font.window);}
            ZT_FONT* lFont = gZTW32_RTime->owner->user.font;
            ZTW32_HostLoadFont(lFont);
            if (lFont->runtime != NULL) {
                SelectObject(gZTW32_RTime->dc.buffer, (HFONT)lFont->runtime);
                ZT_COLOR lColor = lFont->color;
                ZTM_PixelsPaletteConversion(&lColor, 1, gZTW32_RTime->owner->user.palette, ZTK_DEFAULT_PALETTE_SYSTEM_INPUT);
                SetTextColor(gZTW32_RTime->dc.buffer, lColor & ZTM_ColorMask(ZTK_DEFAULT_PALETTE_SYSTEM_INPUT));
                lColor = lFont->colorBk;
                ZTM_PixelsPaletteConversion(&lColor, 1, gZTW32_RTime->owner->user.palette, ZTK_DEFAULT_PALETTE_SYSTEM_INPUT);
                SetBkColor(gZTW32_RTime->dc.buffer, lColor & ZTM_ColorMask(ZTK_DEFAULT_PALETTE_SYSTEM_INPUT));
                SetBkMode(gZTW32_RTime->dc.buffer, (lFont->style & ZTM_FONT_STYLE_OPAQUE) ? OPAQUE : TRANSPARENT);
            }
		}
    }
}
void ZTW32_DrawFree(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL) {
			if (gZTW32_RTime->dc.font != NULL) {DeleteDC(gZTW32_RTime->dc.font); gZTW32_RTime->dc.font = NULL;}
			if (gZTW32_RTime->dc.pipe != NULL) {DeleteDC(gZTW32_RTime->dc.pipe); gZTW32_RTime->dc.pipe = NULL;}
			if (gZTW32_RTime->dc.buffer != NULL) {DeleteDC(gZTW32_RTime->dc.buffer); gZTW32_RTime->dc.buffer = NULL;}
			if (gZTW32_RTime->dc.main != NULL) {ReleaseDC(gZTW32_RTime->window.handle, gZTW32_RTime->dc.main); gZTW32_RTime->dc.main = NULL;}
		}
	}
}
void ZTW32_DrawLoad(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL)  {
			ZTW32_DrawFree();
			gZTW32_RTime->dc.main = GetDC(gZTW32_RTime->window.handle);
			gZTW32_RTime->dc.buffer = CreateCompatibleDC(gZTW32_RTime->dc.main);
			gZTW32_RTime->dc.pipe = CreateCompatibleDC(gZTW32_RTime->dc.main);
			gZTW32_RTime->dc.font = CreateCompatibleDC(gZTW32_RTime->dc.main);
			HBITMAP lWindowSize = CreateCompatibleBitmap(gZTW32_RTime->dc.main, gZTW32_RTime->owner->rect.w, gZTW32_RTime->owner->rect.h);
			SelectObject(gZTW32_RTime->dc.buffer, lWindowSize);
            DeleteObject(SelectObject(gZTW32_RTime->dc.buffer, GetStockObject(DC_BRUSH)));
            ZTW32_DrawLoadColors();
            ZTW32_DrawLoadFont();
		}
	}
}
ZT_FLAG ZTW32_DrawPaletteFromBitmap_W32(BITMAPINFO* iBitmapinfo) {
    ZT_FLAG lPalette = ZTM_PALETTE_UNKNOWN;
    if (iBitmapinfo != NULL) {
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
            } else {
                if (lGreen && !(lRed) && !(lBlue) && !(lRGB & 0x222)) {
                    lRGB |= 0x2;
                } else {
                    if (lBlue && !(lGreen) && !(lRed) && !(lRGB & 0x444)) {
                        lRGB |= 0x4;
                    }
                }
            }
        }
        lPalette |= (lRGB & 0xfff);
    }
    return lPalette;
}
void ZTW32_DrawClear(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->dc.buffer != NULL) {
            if ((gZTW32_RTime->owner->user.options & ZTK_WINDOW_BACKGROUND_ENABLED) && !(gZTW32_RTime->owner->user.options & ZTK_WINDOW_BACKGROUND_AUTO)) {
                ZTW32_DrawColor(ZTK_DEFAULT_WINDOW_BACKGROUND_COLOR);
                ZTW32_DrawBackground();
                ZTW32_DrawColor(gZTW32_RTime->owner->user.background);
            } else {
                ZTW32_DrawBackground();
            }
		}
	}
}
void ZTW32_DrawReset(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL) {
            ZTW32_DrawLoad();
		}
	}
}
void ZTW32_DrawPresent(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->dc.main != NULL && gZTW32_RTime->dc.buffer) {
			BitBlt(gZTW32_RTime->dc.main, 0, 0, gZTW32_RTime->owner->rect.w, gZTW32_RTime->owner->rect.h, gZTW32_RTime->dc.buffer, 0, 0, SRCCOPY);
            RedrawWindow(gZTW32_RTime->window.handle, &(gZTW32_RTime->window.dimensions), NULL, RDW_UPDATENOW);
		}
	}
}
void ZTW32_DrawBackground(void) {
	if (gZTW32_RTime != NULL) {
        if (gZTW32_RTime->dc.buffer != NULL) {
            FillRect(gZTW32_RTime->dc.buffer, &(gZTW32_RTime->window.dimensions), NULL);
            //Rectangle(gZTW32_RTime->dc.buffer, 0, 0, gZTW32_RTime->owner->rect.w, gZTW32_RTime->owner->rect.h);
        }
	}
}
UINT ZTW32_DrawTextFlags_W32(ZT_FLAG iFontStyle) {
    UINT lDTFlags = DT_NOPREFIX;
    if (iFontStyle & ZTM_FONT_STYLE_ALIGN_RIGHT) {lDTFlags |= DT_RIGHT;} else {if (iFontStyle & ZTM_FONT_STYLE_ALIGN_CENTER) {lDTFlags |= DT_CENTER;} else {lDTFlags |= DT_LEFT;}}
    if (iFontStyle & ZTM_FONT_STYLE_VALIGN_BOTTOM) {lDTFlags |= DT_BOTTOM;} else {if (iFontStyle & ZTM_FONT_STYLE_VALIGN_CENTER) {lDTFlags |= DT_VCENTER;} else {lDTFlags |= DT_TOP;}}
    if (iFontStyle & ZTM_FONT_STYLE_BREAK_WORDS) {lDTFlags |= DT_WORDBREAK;}
    if (iFontStyle & ZTM_FONT_STYLE_SINGLE_LINE) {lDTFlags |= DT_SINGLELINE;}
    if (!(iFontStyle & ZTM_FONT_STYLE_CLIP)) {lDTFlags |= DT_NOCLIP;}
    return lDTFlags;
}
void ZTW32_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox) {
	if (gZTW32_RTime != NULL && iText != NULL) {
		if (gZTW32_RTime->dc.buffer != NULL && gZTW32_RTime->owner->user.font != NULL) {
            if (gZTW32_RTime->owner->user.font->flag & ZTM_FONT_FLAG_RELOAD) {ZTW32_DrawLoadFont();}
			UINT lDTFlags = ZTW32_DrawTextFlags_W32(gZTW32_RTime->owner->user.font->style);
			RECT lW32Rect;
			RECT* lW32RectPtr = &lW32Rect;
			if (iTextBox != NULL) {
                lW32Rect.left = iTextBox->x;
                lW32Rect.top = iTextBox->y;
                lW32Rect.right = lW32Rect.left + iTextBox->w;
                lW32Rect.bottom = lW32Rect.top + iTextBox->h;
			} else {
                lW32RectPtr = &(gZTW32_RTime->window.dimensions);
			}
			DrawText(gZTW32_RTime->dc.buffer, (const char*)iText, -1, lW32RectPtr, lDTFlags);
		}
	}
}
void ZTW32_GetDrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize) {
	if (gZTW32_RTime != NULL && iText != NULL && oTextSize != NULL) {
		if (gZTW32_RTime->dc.buffer != NULL && gZTW32_RTime->owner->user.font != NULL) {
            if (gZTW32_RTime->owner->user.font->flag & ZTM_FONT_FLAG_RELOAD) {ZTW32_DrawLoadFont();}
			RECT lW32Rect;
			lW32Rect.top = 0;
			lW32Rect.left = 0;
			UINT lDTFlags = ZTW32_DrawTextFlags_W32(gZTW32_RTime->owner->user.font->style) | DT_CALCRECT;
			DrawText(gZTW32_RTime->dc.buffer, (const char*)iText, -1, &lW32Rect, lDTFlags);
            oTextSize->x = lW32Rect.right;
            oTextSize->y = lW32Rect.bottom;
		}
	}
}
void ZTW32_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
	if (gZTW32_RTime != NULL && iPixels != NULL && iDimensions != NULL) {
        HBITMAP lBitmap = CreateBitmap(iDimensions->x, iDimensions->y, 1, 32, (void*)iPixels);
        if (lBitmap != NULL) {
            ZTW32_DrawBitmap_W32(lBitmap, iDimensions, iTarget, iBlendmode);
            DeleteObject(lBitmap);
        }
	}
}
void ZTW32_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
	if (gZTW32_RTime != NULL && iSurface != NULL) {
        HBITMAP lBitmap = CreateBitmap(iSurface->block.x, iSurface->block.y, 1, 32, (void*)iSurface->pixels);
        if (lBitmap != NULL) {
            ZTW32_DrawBitmap_W32(lBitmap, &(iSurface->block), iTarget, iBlendmode);
            DeleteObject(lBitmap);
        }
	}
}
void ZTW32_DrawSprite(ZT_SPRITE* iSprite, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
	if (gZTW32_RTime != NULL && iSprite != NULL) {
		if (iSprite->data != NULL) {
            switch (iSprite->type) {
                case ZTK_SPRITE_TYPE_MS_HBITMAP: ZTW32_DrawBitmap_W32((HBITMAP)iSprite->data, &(iSprite->block), iTarget, iBlendmode); return;
                case ZTK_SPRITE_TYPE_ZT_SURFACE: ZTW32_DrawSurface((ZT_SURFACE*)iSprite->data, iTarget, iBlendmode); return;
                case ZTK_SPRITE_TYPE_ZT_PIXELS: ZTW32_DrawPixels((ZT_COLOR*)iSprite->data, &(iSprite->block), iTarget, iBlendmode); return;
                default: return;
            }
		}
	}
}

// INTERNAL-ONLY FUNCTIONS
void ZTW32_DrawColor(ZT_COLOR iColor) {
	if (gZTW32_RTime != NULL) {
	    HDC lBuffer = NULL;
		if ((lBuffer = gZTW32_RTime->dc.buffer) != NULL) {
			ZT_COLOR lColor = ZTM_ColorPaletteConvert(iColor, gZTW32_RTime->owner->user.palette, ZTK_DEFAULT_PALETTE_SYSTEM_INPUT) & ZTM_ColorMask(ZTK_DEFAULT_PALETTE_SYSTEM_INPUT);
            //SelectObject(lBuffer, GetStockObject(DC_BRUSH));
			SetDCBrushColor(lBuffer, lColor);
		}
	}
}
void ZTW32_DrawBitmap_W32(HBITMAP iBitmap, const ZT_POINT* iBitmapSize, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
    static HBITMAP lLastBitmap = NULL;
	if (gZTW32_RTime != NULL && iBitmap != NULL) {
        HDC lBuffer = NULL;
        HDC lPipe = NULL;
		if ((lBuffer = gZTW32_RTime->dc.buffer) != NULL && (lPipe = gZTW32_RTime->dc.pipe) != NULL) {
            ZT_RECT lTarget;
            if (iTarget == NULL) {
                ZTM_RectZeroPos(&lTarget);
                ZTM_RectCopySize(&(gZTW32_RTime->owner->rect), &lTarget);
                iTarget = &lTarget;
            }
            if (iBitmapSize == NULL) {iBitmapSize = (ZT_POINT*)&(lTarget.w);}
			if (lLastBitmap != iBitmap) {SelectObject(lPipe, (lLastBitmap = iBitmap));}
			switch (iBlendmode) {
				case ZTK_WINDOW_BLENDMODE_ALPHA: {
						BLENDFUNCTION blendFunction;
						blendFunction.AlphaFormat = AC_SRC_ALPHA;
						blendFunction.BlendFlags = 0x0;
						blendFunction.BlendOp = AC_SRC_OVER;
						blendFunction.SourceConstantAlpha = 0xff;
						AlphaBlend(lBuffer, iTarget->x, iTarget->y, iTarget->w, iTarget->h, lPipe, 0, 0, iBitmapSize->x, iBitmapSize->y, blendFunction);
					}
					return;
				case ZTK_WINDOW_BLENDMODE_BLOT:
				    BitBlt(lBuffer, iTarget->x, iTarget->y, iTarget->w, iTarget->h, lPipe, 0, 0, SRCCOPY);
				    return;
				default:
				    return;
			}
		}
	}
}

ZT_SURFACE* ZTW32_SurfaceFromBitmapFile(const ZT_CHAR* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacity, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
	if (gZTW32_RTime != NULL) {
        if (gZTW32_RTime->instance != NULL) {
            ZT_FLAG lUserPalette = gZTW32_RTime->owner->user.palette;
            HBITMAP loadedFile = (HBITMAP)LoadImage(gZTW32_RTime->instance, (const char*)iPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (loadedFile != NULL) {
                ZT_FLAG lPalette;
                lSurface = ZTW32_SurfaceFromBitmap_W32(loadedFile, &lPalette);
                if (iTransparent) {
                    ZTM_SurfacePixelsOpacityFromColor(lSurface, lPalette, iOpacity, ZTM_ColorPaletteConvert(ZTM_ColorMask(lUserPalette) & iTransparent, lUserPalette, lPalette));
                } else {
                    ZTM_SurfacePixelsOpacity(lSurface, lPalette, iOpacity);
                }
                if (oPalette != NULL) {*oPalette = lPalette;}
                DeleteObject(loadedFile);
            }
        }
    }
    return lSurface;
}
ZT_SURFACE* ZTW32_SurfaceFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
	if (gZTW32_RTime != NULL && iText != NULL) {
		if (gZTW32_RTime->dc.font != NULL && gZTW32_RTime->dc.main != NULL) {
            ZT_FONT* lFont = (iFont != NULL) ? iFont : gZTW32_RTime->owner->user.font;
            if (lFont != NULL) {
                if (lFont->runtime == NULL || (lFont->flag & ZTM_FONT_FLAG_RELOAD)) {ZTW32_HostLoadFont(lFont);}
                if (lFont->runtime != NULL) {
                    SelectObject(gZTW32_RTime->dc.font, lFont->runtime);
                    RECT lW32Rect;
                    lW32Rect.top = 0;
                    lW32Rect.left = 0;
                    DrawText(gZTW32_RTime->dc.font, (const char*)iText, -1, &lW32Rect, ZTW32_DrawTextFlags_W32(lFont->style) | DT_CALCRECT);
                    if (lW32Rect.right) {
                        HBITMAP lBitmap = CreateCompatibleBitmap(gZTW32_RTime->dc.main, lW32Rect.right, lW32Rect.bottom);
                        if (lBitmap != NULL) {
                            ZT_FLAG lUserPalette = gZTW32_RTime->owner->user.palette;
                            HBRUSH lBrush = CreateSolidBrush(ZTM_ColorPaletteConvert(lFont->colorBk, lUserPalette, ZTK_DEFAULT_PALETTE_SYSTEM_INPUT) & ZTM_ColorMask(ZTK_DEFAULT_PALETTE_SYSTEM_INPUT));
                            if (lBrush != NULL) {
                                SelectObject(gZTW32_RTime->dc.font, lBitmap);
                                FillRect(gZTW32_RTime->dc.font, &lW32Rect, lBrush);
                                SetBkMode(gZTW32_RTime->dc.font, TRANSPARENT);
                                SetTextColor(gZTW32_RTime->dc.font, ZTM_ColorPaletteConvert(lFont->color, lUserPalette, ZTK_DEFAULT_PALETTE_SYSTEM_INPUT) & ZTM_ColorMask(ZTK_DEFAULT_PALETTE_SYSTEM_INPUT));
                                DrawText(gZTW32_RTime->dc.font, (const char*)iText, -1, &lW32Rect, ZTW32_DrawTextFlags_W32(lFont->style));
                                ZT_FLAG lPalette;
                                lSurface = ZTW32_SurfaceFromBitmap_W32(lBitmap, &lPalette);
                                if (lFont->style & ZTM_FONT_STYLE_OPAQUE) {
                                    ZTM_SurfacePixelsOpacity(lSurface, lPalette, ZTM_ColorAlpha(lFont->color, lUserPalette));
                                    ZT_COLOR lColorBk = ZTM_ColorPaletteConvert(lFont->colorBk, lUserPalette, lPalette);
                                    ZT_COLOR lColorBkSearch = (lColorBk & ZTM_ColorMask(lPalette)) | (ZTM_ColorAlpha(lFont->color, lUserPalette) << ZTM_ColorAlphaShift(lPalette));
                                    ZTM_SurfacePixelsReplaceColor(lSurface, lColorBkSearch, lColorBk, 0);
                                } else {
                                    ZTM_SurfacePixelsOpacityFromColor(lSurface, lPalette, ZTM_ColorAlpha(lFont->color, lUserPalette), ZTM_ColorPaletteConvert(lFont->colorBk, lUserPalette, lPalette));
                                    ZTM_SurfacePixelsReplaceOpaqueColors(lSurface, lPalette, ZTM_ColorPaletteConvert(lFont->color, lUserPalette, lPalette), 0);
                                }
                                if (oPalette != NULL) {*oPalette = lPalette;}
                                DeleteObject(lBrush);
                            }
                            DeleteObject(lBitmap);
                        }
                    }
                }
            }
		}
	}
    return lSurface;
}
void ZTW32_SizeFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_POINT* oSize) {
	if (gZTW32_RTime != NULL && iText != NULL && oSize != NULL) {
		if (gZTW32_RTime->dc.font != NULL && gZTW32_RTime->dc.main != NULL) {
            ZT_FONT* lFont = (iFont != NULL) ? iFont : gZTW32_RTime->owner->user.font;
            if (lFont != NULL) {
                if (lFont->runtime == NULL || (lFont->flag & ZTM_FONT_FLAG_RELOAD)) {ZTW32_HostLoadFont(lFont);}
                if (lFont->runtime != NULL) {
                    SelectObject(gZTW32_RTime->dc.font, lFont->runtime);
                    RECT lW32Rect;
                    lW32Rect.top = 0;
                    lW32Rect.left = 0;
                    DrawText(gZTW32_RTime->dc.font, (const char*)iText, -1, &lW32Rect, ZTW32_DrawTextFlags_W32(lFont->style) | DT_CALCRECT);
                    oSize->x = lW32Rect.right;
                    oSize->y = lW32Rect.bottom;
                }
            }
		}
	}
}
ZT_SURFACE* ZTW32_SurfaceFromBitmap_W32(HBITMAP iBitmap, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
	if (gZTW32_RTime != NULL && iBitmap != NULL) {
		if (gZTW32_RTime->dc.pipe != NULL) {
			BITMAPINFO lBitmapInfo;
			ZTM8_Zero(&lBitmapInfo, sizeof(BITMAPINFO));
			lBitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			if (GetDIBits(gZTW32_RTime->dc.pipe, iBitmap, 0, 0, NULL, &lBitmapInfo, DIB_RGB_COLORS)) {
				if (lBitmapInfo.bmiHeader.biWidth > 0 && lBitmapInfo.bmiHeader.biHeight > 0) {
					ZT_INDEX lWidth = lBitmapInfo.bmiHeader.biWidth;
                    ZT_BOOL lReadTD = ZT_FALSE;
					ZT_INDEX lHeight = lBitmapInfo.bmiHeader.biHeight;
                    if (lBitmapInfo.bmiHeader.biHeight < 0) {lHeight = -lHeight; lReadTD = ZT_TRUE;}
					ZT_COLOR* lPixels = NULL;
					switch (lBitmapInfo.bmiHeader.biBitCount) {
						case 32:
							if ((lPixels = ZTM32_New(((lWidth * 32 + 31) / 32) * 4 * lHeight)) != NULL) {
								for (ZT_INDEX y = 0; y < lHeight; y++) {
									ZT_INDEX lOffset = lWidth * ((lReadTD != ZT_TRUE) ? (lHeight - 1 - y) : y);
									GetDIBits(gZTW32_RTime->dc.pipe, iBitmap, y, 1, (void*)&(lPixels[lOffset]), &lBitmapInfo, DIB_RGB_COLORS);
								}
								if ((lSurface = ZTM8_New(sizeof(ZT_SURFACE))) != NULL) {
                                    lSurface->pixels = lPixels;
                                    lSurface->block.x = lWidth;
                                    lSurface->block.y = lHeight;
									if (oPalette != NULL) {*oPalette = ZTW32_DrawPaletteFromBitmap_W32(&lBitmapInfo);}
								}
							}
							break;
						default:
							break;
					}
				}
			}
		}
	}
	return lSurface;
}


ZT_SPRITE* ZTW32_SpriteFree_W32(ZT_SPRITE* iSprite) {
    if (iSprite != NULL) {
		if (iSprite->data != NULL && (iSprite->type & ZTK_SPRITE_TYPE_MS_HBITMAP)) {
			DeleteObject((HBITMAP)iSprite->data);
			iSprite->data = NULL;
		}
    }
    return iSprite;
}

ZT_SPRITE* ZTW32_Sprite_W32(ZT_SPRITE* iSprite, const void* iSource, const ZT_POINT* iBlock, ZT_FLAG iType, ZT_FLAG iPalette) {
    if (gZTW32_RTime != NULL && iSprite != NULL && iSource != NULL) {
		ZT_COLOR* lBuffer = NULL;
		ZT_INDEX lLength = 0;
		switch (iType) {
			case ZTK_SPRITE_TYPE_ZT_PIXELS:
				if (iSource != NULL && iBlock != NULL) {
					const ZT_SURFACE* lSource = iSource;
					if ((lLength = ZTM_PointArea(iBlock))) {
						if ((lBuffer = ZTM32_Copy(lSource->pixels, ZTM32_New(lLength), lLength)) != NULL) {
							ZTM_PixelsPaletteConversion(lBuffer, lLength, iPalette, ZTK_DEFAULT_PALETTE_SYSTEM);
							ZTM_PixelsBlendWithAlpha(lBuffer, lLength, ZTK_DEFAULT_PALETTE_SYSTEM);
							ZTW32_SpriteFree_W32(iSprite);
							iSprite->data = CreateBitmap(iBlock->x, iBlock->y, 1, 32, (void*)lBuffer);
							iSprite->block.x = iBlock->x;
							iSprite->block.y = iBlock->y;
							iSprite->type = ZTK_SPRITE_TYPE_MS_HBITMAP;
							iSprite->palette = ZTK_DEFAULT_PALETTE_SYSTEM;
							ZTM32_Free(lBuffer);
						}
					}
				}
				break;
			case ZTK_SPRITE_TYPE_ZT_SURFACE:
				if (iSource != NULL) {
					const ZT_SURFACE* lSource = iSource;
					if ((lLength = ZTM_PointArea(&(lSource->block)))) {
						if ((lBuffer = ZTM32_Copy(lSource->pixels, ZTM32_New(lLength), lLength)) != NULL) {
							ZTM_PixelsPaletteConversion(lBuffer, lLength, iPalette, ZTK_DEFAULT_PALETTE_SYSTEM);
							ZTM_PixelsBlendWithAlpha(lBuffer, lLength, ZTK_DEFAULT_PALETTE_SYSTEM);
							ZTW32_SpriteFree_W32(iSprite);
							iSprite->data = CreateBitmap(lSource->block.x, lSource->block.y, 1, 32, (void*)lBuffer);
							iSprite->block.x = lSource->block.x;
							iSprite->block.y = lSource->block.y;
							iSprite->type = ZTK_SPRITE_TYPE_MS_HBITMAP;
							iSprite->palette = ZTK_DEFAULT_PALETTE_SYSTEM;
							ZTM32_Free(lBuffer);
						}
					}
				}
				break;
			default: break;
		}

    }
    return iSprite;
}

#endif // ZTW32_DRAW_C_INCLUDED
