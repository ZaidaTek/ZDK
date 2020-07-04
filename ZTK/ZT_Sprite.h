/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_SPRITE_H_INCLUDED
#define ZT_SPRITE_H_INCLUDED

#include "ZTK.h"

#define ZTK_SPRITE_TYPE_UNKNOWN 0x0
#define ZTK_SPRITE_TYPE_ZT_PIXELS 0x1
#define ZTK_SPRITE_TYPE_ZT_SURFACE 0x2
#define ZTK_SPRITE_TYPE_MS_HBITMAP 0x100

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_SpriteFree(ZT_SPRITE* iSprite);
ZT_SPRITE* ZTK_SpriteNewEmpty(void);
//ZT_SPRITE* ZTK_SpriteOptimize(ZT_SPRITE* iSprite);
ZT_SPRITE* ZTK_SpriteFromSurface(const ZT_SURFACE* iSurface, ZT_FLAG iPalette);
ZT_SPRITE* ZTK_SpriteFromBitmap(const ZT_CHAR* iPath);
ZT_SPRITE* ZTK_SpriteFromBitmapWithOpacity(const ZT_CHAR* iPath, ZT_INDEX iOpacity);
ZT_SPRITE* ZTK_SpriteFromBitmapWithTransparent(const ZT_CHAR* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacity);
ZT_SPRITE* ZTK_SpriteFromFont(const ZT_CHAR* iText, ZT_FONT* iFont);
ZT_SPRITE* ZTK_SpriteFromText(const ZT_CHAR* iText);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_SPRITE_H_INCLUDED
