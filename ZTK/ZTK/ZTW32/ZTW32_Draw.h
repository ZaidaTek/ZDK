/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_DRAW_H_INCLUDED
#define ZTW32_DRAW_H_INCLUDED

#include "ZTW32.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTW32_DrawLoadColors(void);
void ZTW32_DrawLoadFont(void);
void ZTW32_DrawFree(void);
void ZTW32_DrawLoad(void);
void ZTW32_DrawReset(void);
void ZTW32_DrawClear(void);
void ZTW32_DrawPresent(void);
void ZTW32_DrawBackground(void);
void ZTW32_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox);
void ZTW32_GetDrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize);
void ZTW32_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTW32_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTW32_DrawSprite(ZT_SPRITE* iSprite, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
ZT_SPRITE* ZTW32_SpriteFree_W32(ZT_SPRITE* iSprite);
ZT_SPRITE* ZTW32_Sprite_W32(ZT_SPRITE* iSprite, const void* iSource, const ZT_POINT* iBlock, ZT_FLAG iType, ZT_FLAG iPalette);
ZT_SURFACE* ZTW32_SurfaceFromBitmapFile(const ZT_CHAR* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacity, ZT_FLAG* oPalette);
ZT_SURFACE* ZTW32_SurfaceFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_FLAG* oPalette);
void ZTW32_SizeFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_POINT* oSize);
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ZTW32_DRAW_H_INCLUDED
