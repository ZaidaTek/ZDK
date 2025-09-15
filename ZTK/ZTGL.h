/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTGL_H_INCLUDED
#define ZTGL_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTGL_Init(void);
void ZTGL_Exit(void);
void ZTGL_Size(void);
void ZTGL_Clear(void);
void ZTGL_ClearColor(ZT_COLOR iColor);
void ZTGL_Present(void);
void ZTGL_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget);
void ZTGL_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget);
void ZTGL_DrawSprite(const rZT_SPRITE* iSprite, const ZT_RECT* iTarget);
void ZTGL_DrawTexture(ZT_FLAG iID, const ZT_RECT* iTarget);
void ZTGL_SpriteTextureFree(rZT_SPRITE* iSprite);
rZT_SPRITE* ZTGL_Sprite(const ZT_COLOR* iPixels, const ZT_POINT* iBlock, ZT_FLAG iPalette);
rZT_SPRITE* ZTGL_SpritePixel(const ZT_COLOR* iPixels, const ZT_POINT* iBlock, ZT_FLAG iPalette);
rZT_SPRITE* ZTGL_SpriteTexture(const ZT_COLOR* iPixels, const ZT_POINT* iBlock, ZT_FLAG iPalette);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTGL_H_INCLUDED
