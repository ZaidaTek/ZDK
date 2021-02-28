/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_SPRITE_C_INCLUDED
#define ZT_SPRITE_C_INCLUDED

#include "ZTK__Runtime.h"

void ZTK_SpriteFree(ZT_SPRITE* iSprite) {
    rZT_SPRITE* lSprite = iSprite;
    switch (lSprite->type) {
        #ifdef ZTK_OPENGL_ENABLE
        case ZTK_SPRITE_TYPE_GLTEX: ZTGL_SpriteTextureFree(lSprite); break;
        #endif // ZTK_OPENGL_ENABLE
        case ZTK_SPRITE_TYPE_GLPIXELS: ZTM32_Free(lSprite->data); break;
        case ZTK_SPRITE_TYPE_SYSTEM: ZTK_RuntimeSpriteFree(lSprite); break;
        case ZTK_SPRITE_TYPE_PIXELS: ZTM32_Free(lSprite->data); break;
        default: break;
    }
    ZTM8_Free(lSprite);
}
ZT_SPRITE* ZTK_SpriteFromSurface(const ZT_SURFACE* iSurface, ZT_FLAG iPalette) {
    switch (rZTK_Host.system.renderer) {
        case ZTK_RENDERER_SYSTEM: return ZTK_RuntimeSprite(iSurface->pixels, &(iSurface->block), iPalette);
        #ifdef ZTK_OPENGL_ENABLE
        case ZTK_RENDERER_OPENGL: return ZTGL_Sprite(iSurface->pixels, &(iSurface->block), iPalette);
        #endif // ZTK_OPENGL_ENABLE
        default: return NULL;
    }
}
ZT_SPRITE* ZTK_SpriteFromBitmap(const ZT_U8* iPath) {
    ZT_FLAG lPalette = rZTK_Host.user.palette;
    ZT_SURFACE* lSurface = ZTM_SurfaceFromBitmap(iPath, lPalette);
    ZT_SPRITE* lSprite = ZTK_SpriteFromSurface(lSurface, lPalette);
    ZTM_SurfaceFree(lSurface);
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromBitmapWithOpacity(const ZT_U8* iPath, ZT_INDEX iOpacity) {
    ZT_FLAG lPalette = rZTK_Host.user.palette;
    ZT_SURFACE* lSurface = ZTM_SurfaceFromBitmap(iPath, lPalette);
    ZTM_SurfaceOpacity(lSurface, lPalette, iOpacity);
    ZT_SPRITE* lSprite = ZTK_SpriteFromSurface(lSurface, lPalette);
    ZTM_SurfaceFree(lSurface);
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromBitmapWithTransparent(const ZT_U8* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacityTransparent, ZT_INDEX iOpacityOther) {
    ZT_FLAG lPalette = rZTK_Host.user.palette;
    ZT_SURFACE* lSurface = ZTM_SurfaceFromBitmap(iPath, lPalette);
    ZTM_SurfaceOpacityFromColor(lSurface, lPalette, iTransparent, iOpacityTransparent, iOpacityOther);
    ZT_SPRITE* lSprite = ZTK_SpriteFromSurface(lSurface, lPalette);
    ZTM_SurfaceFree(lSurface);
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromFont(const ZT_CHAR* iText, ZT_FONT* iFont) {
    ZT_FLAG lPalette;
    ZT_SURFACE* lSurface = ZTK_SurfaceFromFont(iText, iFont, &lPalette);
    ZT_SPRITE* lSprite = ZTK_SpriteFromSurface(lSurface, lPalette);
    ZTM_SurfaceFree(lSurface);
    return lSprite;
}
ZT_SPRITE* ZTK_SpriteFromText(const ZT_CHAR* iText) {
    ZT_FLAG lPalette;
    ZT_SURFACE* lSurface = ZTK_SurfaceFromText(iText, &lPalette);
    ZT_SPRITE* lSprite = ZTK_SpriteFromSurface(lSurface, lPalette);
    ZTM_SurfaceFree(lSurface);
    return lSprite;
}
void ZTK_SpriteSize(const ZT_SPRITE* iSprite, ZT_POINT* oSize) {
    ZTM_Point(oSize, ((rZT_SPRITE*)iSprite)->block.x, ((rZT_SPRITE*)iSprite)->block.y);
}

#endif // ZT_SPRITE_C_INCLUDED
