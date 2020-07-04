/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_SPRITE_C_INCLUDED
#define ZT_SPRITE_C_INCLUDED

#include "ZTK/ZTK__Runtime.h"

void ZTK_SpriteFree(ZT_SPRITE* iSprite) {
    if (iSprite != NULL) {
        if (gZT_Window != NULL) {if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeSpriteFree(iSprite);}}
        ZTM8_Free(iSprite);
    }
}
ZT_SPRITE* ZTK_SpriteNewEmpty(void) {return ZTM8_Init(sizeof(ZT_SPRITE), 0x0);}
ZT_SPRITE* ZTK_SpriteFromSurface(const ZT_SURFACE* iSurface, ZT_FLAG iPalette) {
    ZT_SPRITE* lSprite = NULL;
	if (gZT_Window != NULL && iSurface != NULL) {
        lSprite = ZTK_RuntimeSpriteOptimize(ZTK_SpriteNewEmpty(), iSurface, &(iSurface->block), ZTK_SPRITE_TYPE_ZT_SURFACE, iPalette);
    }
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromBitmap(const ZT_U8* iPath) {
    ZT_SPRITE* lSprite = NULL;
	if (gZT_Window != NULL && iPath != NULL) {
        ZT_FLAG lPalette;
        ZT_SURFACE* lSurface = ZTK_SurfaceFromBitmap(iPath, &lPalette);
        lSprite = ZTK_RuntimeSpriteOptimize(ZTK_SpriteNewEmpty(), lSurface, &(lSurface->block), ZTK_SPRITE_TYPE_ZT_SURFACE, lPalette);
        ZTM_SurfaceFree(lSurface);
    }
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromBitmapWithOpacity(const ZT_U8* iPath, ZT_INDEX iOpacity) {
    ZT_SPRITE* lSprite = NULL;
	if (gZT_Window != NULL && iPath != NULL) {
        ZT_FLAG lPalette;
        ZT_SURFACE* lSurface = ZTK_SurfaceFromBitmapWithOpacity(iPath, iOpacity, &lPalette);
        lSprite = ZTK_RuntimeSpriteOptimize(ZTK_SpriteNewEmpty(), lSurface, &(lSurface->block), ZTK_SPRITE_TYPE_ZT_SURFACE, lPalette);
        ZTM_SurfaceFree(lSurface);
    }
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromBitmapWithTransparent(const ZT_U8* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacity) {
    ZT_SPRITE* lSprite = NULL;
	if (gZT_Window != NULL && iPath != NULL) {
        ZT_FLAG lPalette;
        ZT_SURFACE* lSurface = ZTK_SurfaceFromBitmapWithTransparent(iPath, iTransparent, iOpacity, &lPalette);
        lSprite = ZTK_RuntimeSpriteOptimize(ZTK_SpriteNewEmpty(), lSurface, &(lSurface->block), ZTK_SPRITE_TYPE_ZT_SURFACE, lPalette);
        ZTM_SurfaceFree(lSurface);
    }
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromFont(const ZT_CHAR* iText, ZT_FONT* iFont) {
    ZT_SPRITE* lSprite = NULL;
	if (gZT_Window != NULL && iText != NULL) {
        ZT_FLAG lPalette;
        ZT_SURFACE* lSurface = ZTK_SurfaceFromFont(iText, iFont, &lPalette);
        lSprite = ZTK_RuntimeSpriteOptimize(ZTK_SpriteNewEmpty(), lSurface, &(lSurface->block), ZTK_SPRITE_TYPE_ZT_SURFACE, lPalette);
        ZTM_SurfaceFree(lSurface);
    }
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromText(const ZT_CHAR* iText) {
    ZT_SPRITE* lSprite = NULL;
	if (gZT_Window != NULL && iText != NULL) {
        ZT_FLAG lPalette;
        ZT_SURFACE* lSurface = ZTK_SurfaceFromText(iText, &lPalette);
        lSprite = ZTK_RuntimeSpriteOptimize(ZTK_SpriteNewEmpty(), lSurface, &(lSurface->block), ZTK_SPRITE_TYPE_ZT_SURFACE, lPalette);
        ZTM_SurfaceFree(lSurface);
    }
    return lSprite;
}

#endif // ZT_SPRITE_C_INCLUDED
