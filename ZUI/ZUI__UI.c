/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI__UI_C_INCLUDED
#define ZUI__UI_C_INCLUDED

#include "ZUI__Runtime.h"

void ZUI_UINew(rZUI_ELEMENT* iElement, const void* iSource) {
    ZUI_UISourcesNew(iElement);
    ZUI_UIColorsNew(iElement);
    ZUI_UISource(iElement, iElement->UI.draw, iSource);
}
void ZUI_UIFree(rZUI_ELEMENT* iElement) {
    ZUI_UISpritesFree(iElement);
    ZUI_UIColorsFree(iElement);
    ZUI_UISourcesFree(iElement);
}
void ZUI_UIZero(rZUI_ELEMENT* iElement) {
    iElement->UI.S = ZUI_UIS_NONE;
    iElement->UI.type = ZUI_UI_TYPE_NONE;
    iElement->UI.draw = ZUI_UIS_NONE;
    iElement->UI.border = 0;
    iElement->UI.font = NULL;
    iElement->UI.sources = NULL;
    iElement->UI.colors = NULL;
    iElement->UI.sprites = NULL;
}
void ZUI_UIState(rZUI_ELEMENT* iElement) {
    switch (iElement->UI.type) {
        case ZUI_UI_TYPE_PRINT_LIST: ZUI_UIPrintListState(iElement); return;
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericState(iElement); return;
        default: return;
    }
}
void ZUI_UISource(rZUI_ELEMENT* iElement, ZT_FLAG iUIS, const ZT_CHAR* iSource) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericSource(&(iElement->UI), iUIS, iSource); return;
        default: return;
    }
}
void ZUI_UIColor(rZUI_ELEMENT* iElement, ZT_FLAG iUIS, const ZUI_COLOR* iColor) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericColor(&(iElement->UI), iUIS, iColor); return;
        default: return;
    }
}
void ZUI_UISourcesNew(rZUI_ELEMENT* iElement) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericSourcesNew(&(iElement->UI)); return;
        default: return;
    }
}
void ZUI_UISourcesFree(rZUI_ELEMENT* iElement) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericSourcesFree(&(iElement->UI)); return;
        default: return;
    }
}
void ZUI_UIColorsNew(rZUI_ELEMENT* iElement) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericColorsNew(&(iElement->UI)); return;
        default: return;
    }
}
void ZUI_UIColorsFree(rZUI_ELEMENT* iElement) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericColorsFree(&(iElement->UI)); return;
        default: return;
    }
}
void ZUI_UISpritesNew(rZUI_ELEMENT* iElement) {
    switch (iElement->UI.type) {
        case ZUI_UI_TYPE_PRINT_LIST: ZUI_UIPrintListSpritesNew(&(iElement->UI), &(iElement->rect)); return;
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericSpritesNew(&(iElement->UI), &(iElement->rect)); return;
        default: return;
    }
}
void ZUI_UISpritesFree(rZUI_ELEMENT* iElement) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_PRINT_LIST: ZUI_UIPrintListSpritesFree(&(iElement->UI)); return;
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericSpritesFree(&(iElement->UI)); return;
        default: return;
    }
}
void ZUI_UISpritesReload(rZUI_ELEMENT* iElement) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_PRINT_LIST: ZUI_UIPrintListSpritesFree(&(iElement->UI)); ZUI_UIPrintListSpritesNew(&(iElement->UI), &(iElement->rect)); return;
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericSpritesFree(&(iElement->UI)); ZUI_UIGenericSpritesNew(&(iElement->UI), &(iElement->rect)); return;
        default: return;
    }
}
void ZUI_UIGenericState(rZUI_ELEMENT* iElement) {
    ZT_FLAG lUIS = iElement->UI.S & ZUI_UIS_MASK;
    if (iElement->flag & ZUI_ELEMENT_FLAG_DISABLE) {lUIS |= ZUI_UIS_DISABLED; lUIS &= ~ZUI_UIS_NORMAL;} else {lUIS |= ZUI_UIS_NORMAL; lUIS &= ~ZUI_UIS_DISABLED;}
    if (iElement->id.A & ZTK_AID_MOVE) {lUIS |= ZUI_UIS_HOVER;} else {lUIS &= ~ZUI_UIS_HOVER;}
    if (iElement->id.A & ZTK_AID_PRESS) {lUIS |= ZUI_UIS_PRESS;} else {lUIS &= ~ZUI_UIS_PRESS;}
    if (iElement->id.A & ZTK_AID_RELEASE) {lUIS |= ZUI_UIS_RELEASE;} else {lUIS &= ~ZUI_UIS_RELEASE;}
    if (rZUI_RTime.element.focus == iElement) {lUIS |= ZUI_UIS_FOCUS;} else {lUIS &= ~ZUI_UIS_FOCUS;}
    iElement->UI.S &= ~ZUI_UIS_MASK;
    iElement->UI.S |= lUIS;
}
ZT_INDEX ZUI_UIGenericGetStateIndex(const rZUI_UI* iUI, ZT_FLAG iUIS) {
    ZT_INDEX lIndex = -1;
    for (ZT_INDEX lUIS = 0x1; lUIS & ZUI_UIS_ALL; lUIS <<= 1) {
        if (lUIS & iUI->draw) {
            ++lIndex;
            if (lUIS & iUIS) {return lIndex;}
        }
    }
    return ZTM_BitCount(ZUI_UIS_ALL);
}
void ZUI_UIGenericSource(rZUI_UI* iUI, ZT_FLAG iUIS, const ZT_CHAR* iSource) {
    ZT_INDEX lIndex = -1;
    for (ZT_FLAG lUIS = 0x1; lUIS & ZUI_UIS_ALL; lUIS <<= 1) {
        if (lUIS & iUI->draw) {
            ++lIndex;
            if (lUIS & iUIS) {iUI->sources[lIndex] = iSource;}
        }
    }
}
void ZUI_UIGenericColor(rZUI_UI* iUI, ZT_FLAG iUIS, const ZUI_COLOR* iColor) {
    ZT_INDEX lIndex = -1;
    for (ZT_FLAG lUIS = 0x1; lUIS & ZUI_UIS_ALL; lUIS <<= 1) {
        if (lUIS & iUI->draw) {
            ++lIndex;
            if (lUIS & iUIS) {iUI->colors[lIndex] = *iColor;}
        }
    }
}
void ZUI_UIGenericSourcesNew(rZUI_UI* iUI) {
    iUI->sources = ZTM8_New(sizeof(void*) * ZTM_BitCount(iUI->draw & ZUI_UIS_MASK));
}
void ZUI_UIGenericSourcesFree(rZUI_UI* iUI) {
    ZTM8_Free(iUI->sources);
}
void ZUI_UIGenericColorsNew(rZUI_UI* iUI) {
    iUI->colors = ZTM8_New(sizeof(ZUI_COLOR) * ZTM_BitCount(iUI->draw & ZUI_UIS_MASK));
}
void ZUI_UIGenericColorsFree(rZUI_UI* iUI) {
    ZTM8_Free(iUI->colors);
}
void ZUI_UIGenericSpritesNew(rZUI_UI* iUI, const ZT_RECT* iRect) {
    iUI->sprites = ZTM8_New(sizeof(ZT_SPRITE*) * ZTM_BitCount(iUI->draw & ZUI_UIS_MASK));
    for (ZT_INDEX i = 0; i < ZTM_BitCount(iUI->draw & ZUI_UIS_MASK); i++) {
        ZT_SURFACE* lBack = ZTM_SurfaceNewFill((const ZT_POINT*)&(iRect->w), ZUI_COLOR_TRANSPARENT);
        for (ZT_I y = iUI->border; y < (lBack->block.y - (ZT_I)iUI->border); y++) {
            for (ZT_I x = iUI->border; x < (lBack->block.x - (ZT_I)iUI->border); x++) {
                lBack->pixels[x + y * lBack->block.x] = iUI->colors[i].background;
            }
        }
        if (iUI->sources[i] != NULL/* && iUI->font != NULL*/) {
            ZT_FLAG lPalette;
            ZT_COLOR lColorCache = iUI->font->color;
            if (iUI->colors[i].foreground != ZUI_COLOR_TRANSPARENT) {
                iUI->font->color = iUI->colors[i].foreground;
                ZT_SURFACE* lLabel = ZTK_SurfaceFromFont(iUI->sources[i], iUI->font, &lPalette);
                ZTM_PixelsConvert(lLabel->pixels, lLabel->pixels, ZTM_PointArea(&(lLabel->block)), lPalette, *rZUI_RTime.system.paletteUser);
                ZTM_SurfaceBlend(lLabel, lBack, NULL, NULL, *rZUI_RTime.system.paletteUser);
                ZTM_SurfaceFree(lLabel);
            } else {
                ZT_COLOR lTransparent = (ZTM_ColorComplementary(iUI->colors[i].background) & ZTM_ColorMaskC(*rZUI_RTime.system.paletteUser)) | (0xff << ZTM_ColorShiftA(*rZUI_RTime.system.paletteUser));
                iUI->font->color = lTransparent;
                ZT_SURFACE* lLabel = ZTK_SurfaceFromFont(iUI->sources[i], iUI->font, &lPalette);
                ZTM_PixelsConvert(lLabel->pixels, lLabel->pixels, ZTM_PointArea(&(lLabel->block)), lPalette, *rZUI_RTime.system.paletteUser);
                ZTM_SurfaceBlend(lLabel, lBack, NULL, NULL, *rZUI_RTime.system.paletteUser);
                ZTM_SurfaceReplaceColor(lBack, lTransparent, ZUI_COLOR_TRANSPARENT);
                ZTM_SurfaceFree(lLabel);
            }
            iUI->font->color = lColorCache;
        }
        ZT_SURFACE* lBorder = ZTM_SurfaceNewFill((const ZT_POINT*)&(iRect->w), iUI->colors[i].border);
        for (ZT_I y = iUI->border; y < (lBorder->block.y - (ZT_I)iUI->border); y++) {
            for (ZT_I x = iUI->border; x < (lBorder->block.x - (ZT_I)iUI->border); x++) {
                lBorder->pixels[x + y * lBorder->block.x] = ZUI_COLOR_TRANSPARENT;
            }
        }
        ZTM_SurfaceBlend(lBorder, lBack, NULL, NULL, *rZUI_RTime.system.paletteUser);
        ZTM_SurfaceFree(lBorder);
        iUI->sprites[i] = ZTK_SpriteFromSurface(lBack, *rZUI_RTime.system.paletteUser);
        ZTM_SurfaceFree(lBack);
    }
}
void ZUI_UIGenericSpritesFree(rZUI_UI* iUI) {
    for (ZT_INDEX i = 0; i < ZTM_BitCount(iUI->draw & ZUI_UIS_MASK); i++) {ZTK_SpriteFree(iUI->sprites[i]);}
    ZTM8_Free(iUI->sprites);
}
void ZUI_UIPrintListState(rZUI_ELEMENT* iElement) {
    iElement->UI.S &= ~ZUI_UIS_MASK_INDEX;
    ZT_INDEX lIndex = ((ZT_INDEX)iElement->data->value - (ZT_INDEX)iElement->data->minimum);
    iElement->UI.S |= ((lIndex << ZUI_UIS_SHIFT_INDEX) & ZUI_UIS_MASK_INDEX);
}
void ZUI_UIPrintListSpritesNew(rZUI_UI* iUI, const ZT_RECT* iRect) {
    (void)iRect;
    iUI->sprites = ZTM8_New(sizeof(ZT_SPRITE*) * (((iUI->draw & ZUI_UIS_MASK_INDEX) >> ZUI_UIS_SHIFT_INDEX) + 1));
    for (ZT_INDEX i = 0; i < (((iUI->draw & ZUI_UIS_MASK_INDEX) >> ZUI_UIS_SHIFT_INDEX) + 1); i++) {iUI->sprites[i] = ZTK_SpriteFromFont(iUI->sources[i], iUI->font);}
}
void ZUI_UIPrintListSpritesFree(rZUI_UI* iUI) {
    for (ZT_INDEX i = 0; i < (((iUI->draw & ZUI_UIS_MASK_INDEX) >> ZUI_UIS_SHIFT_INDEX) + 1); i++) {ZTK_SpriteFree(iUI->sprites[i]);}
    ZTM8_Free(iUI->sprites);
}
void ZUI_UIGenericDraw(const rZUI_UI* iUI, const ZT_RECT* iRect) {
    ZT_INDEX drawIndex = -1;
    for (ZT_FLAG lUIS = 0x1; lUIS & ZUI_UIS_ALL; lUIS <<= 1) {
        if (iUI->draw & lUIS) {
            ++drawIndex;
            if (iUI->S & lUIS) {ZTK_DrawSprite(iUI->sprites[drawIndex], iRect);}
        }
    }
}
void ZUI_UIPrintDataDraw(const rZUI_UI* iUI, const ZT_RECT* iRect, const rZUI_DATA* iData) {
    ZT_RECT lRect;
    ZT_RECT lSize;
    ZT_POINT lCursor;
    ZT_INDEX lPrecision = (iUI->draw >> (ZUI_UIS_SHIFT_INDEX + 4)) & 0xf;
    ZT_INDEX lLength = (iUI->draw >> ZUI_UIS_SHIFT_INDEX) & 0xf;
    for (ZT_INDEX i = 0; i < (lLength + (lPrecision ? 1 : 0)); i++) {
        if (i < lLength) {
            switch(iData->type) {
                case ZUI_ELEMENT_DATA_TYPE_UINT: ZTK_PrintBufferLoad("%u", (((ZT_U)iData->value / ZTM_Exp(lLength - 1 - i)) % 10)); break;
                case ZUI_ELEMENT_DATA_TYPE_INT: ZTK_PrintBufferLoad("%d", (((ZT_I)iData->value / (ZT_I)ZTM_Exp(lLength - 1 - i)) % 10)); break;
                default: ZTK_PrintBufferLoad(""); break;
            }
        } else {
            ZTK_PrintBufferLoad(".");
        }
        ZTM_PointZero(&lCursor);
        ZTM_RectZeroPos(&lRect);
        ZTM_RectCopySize(iRect, &lRect);
        ZTK_PrintBufferGetCustomSize(iUI->font, &lCursor, &lRect, &lSize);
        ZTM_RectCopySize(&lSize, &lRect);
        ZT_I lX = iRect->x + ((i < lLength) ? ((i << 1) + 1) * iRect->w / (lLength << 1) : (lLength - lPrecision) * iRect->w / lLength);
        ZTM_RectPosFromIntegers(&lRect, lX - (lSize.w >> 1), iRect->y + (iRect->h >> 1) - (lSize.h >> 1));
        ZTK_PrintBufferCustom(iUI->font, &lCursor, &lRect);
    }
}
void ZUI_UIPrintListDraw(const rZUI_UI* iUI, const ZT_RECT* iRect) {
    ZT_RECT lRect;
    rZT_SPRITE* lSprite = iUI->sprites[((iUI->S & ZUI_UIS_MASK_INDEX) >> ZUI_UIS_SHIFT_INDEX)];
    ZTM_RectSize(&lRect, &(lSprite->block));
    lRect.x = iRect->x + ((iRect->w - lRect.w) >> 1);
    lRect.y = iRect->y + ((iRect->h - lRect.h) >> 1);
    ZTK_DrawSprite(lSprite, &lRect);
}
void ZUI_UIDraw(const rZUI_ELEMENT* iElement) {
    switch(iElement->UI.type) {
        case ZUI_UI_TYPE_GENERIC: ZUI_UIGenericDraw(&iElement->UI, &iElement->rect); return;
        case ZUI_UI_TYPE_PRINT_DATA: ZUI_UIPrintDataDraw(&iElement->UI, &iElement->rect, iElement->data); return;
        case ZUI_UI_TYPE_PRINT_LIST: ZUI_UIPrintListDraw(&iElement->UI, &iElement->rect); return;
        default: return;
    }
}

#endif // ZUI__UI_C_INCLUDED
