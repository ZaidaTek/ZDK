/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_SPRITE_H_INCLUDED
#define ZTK_SPRITE_H_INCLUDED

#define ZTK_SPRITE_TYPE_UNKNOWN 0x0
#define ZTK_SPRITE_TYPE_PIXELS 0x1
#define ZTK_SPRITE_TYPE_SYSTEM 0x100
#define ZTK_SPRITE_TYPE_GLPIXELS 0x200
#define ZTK_SPRITE_TYPE_GLTEX 0x201

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_SpriteFree(ZT_SPRITE* iSprite);
ZT_SPRITE* ZTK_SpriteFromSurface(const ZT_SURFACE* iSurface, ZT_FLAG iPalette);
ZT_SPRITE* ZTK_SpriteFromBitmap(const ZT_CHAR* iPath);
ZT_SPRITE* ZTK_SpriteFromBitmapWithOpacity(const ZT_CHAR* iPath, ZT_INDEX iOpacity);
ZT_SPRITE* ZTK_SpriteFromBitmapWithTransparent(const ZT_U8* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacityTransparent, ZT_INDEX iOpacityOther);
ZT_SPRITE* ZTK_SpriteFromFont(const ZT_CHAR* iText, ZT_FONT* iFont);
ZT_SPRITE* ZTK_SpriteFromText(const ZT_CHAR* iText);
void ZTK_SpriteSize(const ZT_SPRITE* iSprite, ZT_POINT* oSize);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTK_SPRITE_H_INCLUDED
