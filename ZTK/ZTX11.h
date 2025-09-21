/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX11_H_INCLUDED
#define ZTX11_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
///ZTX11.c
void ZTX11_Free(void);
void ZTX11_New(void);
void ZTX11_RectLoad(void);
void ZTX11_RectApply(void);
void ZTX11_Open(void);
void ZTX11_Quit(void);
ZT_INDEX ZTX11_Process(void);
void ZTX11_KeyLoad(ZT_U32* oTarget);
void ZTX11_FontFreeSource(rZT_FONT* iFont);
void ZTX11_FontLoadSource(rZT_FONT* iFont);
void ZTX11_FontFreeRuntime(rZT_FONT* iFont);
void ZTX11_FontLoadRuntime(rZT_FONT* iFont);
void ZTX11_Loop(void);
///ZTX11_Draw.c
void ZTX11_DrawFontLoad(void);
void ZTX11_DrawInit(void);
void ZTX11_DrawExit(void);
void ZTX11_DrawSize(void);
void ZTX11_DrawClear(void);
void ZTX11_DrawPresent(void);
void ZTX11_DrawClearColor(ZT_COLOR iColor);
void ZTX11_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox);
void ZTX11_DrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize);
void ZTX11_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTX11_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTX11_DrawSprite(const rZT_SPRITE* iSprite, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTX11_SpriteFree(rZT_SPRITE* iSprite);
rZT_SPRITE* ZTX11_Sprite(const ZT_COLOR* iSource, const ZT_POINT* iBlock, ZT_FLAG iPalette);
ZT_SURFACE* ZTX11_SurfaceFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_FLAG* oPalette);
void ZTX11_SizeFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_POINT* oSize);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTX11_H_INCLUDED
