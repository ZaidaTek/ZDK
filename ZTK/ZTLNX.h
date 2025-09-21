/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTLNX_H_INCLUDED
#define ZTLNX_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
///ZTLNX.c
void ZTLNX_Free(void);
void ZTLNX_New(void);
void ZTLNX_RectLoad(void);
void ZTLNX_RectApply(void);
void ZTLNX_Open(void);
void ZTLNX_Quit(void);
ZT_INDEX ZTLNX_Process(void);
void ZTLNX_KeyLoad(ZT_U32* oTarget);
void ZTLNX_FontFreeSource(rZT_FONT* iFont);
void ZTLNX_FontLoadSource(rZT_FONT* iFont);
void ZTLNX_FontFreeRuntime(rZT_FONT* iFont);
void ZTLNX_FontLoadRuntime(rZT_FONT* iFont);
void ZTLNX_Loop(void);
///ZTLNX_Draw.c
void ZTLNX_DrawFontLoad(void);
void ZTLNX_DrawInit(void);
void ZTLNX_DrawExit(void);
void ZTLNX_DrawSize(void);
void ZTLNX_DrawClear(void);
void ZTLNX_DrawPresent(void);
void ZTLNX_DrawClearColor(ZT_COLOR iColor);
void ZTLNX_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox);
void ZTLNX_DrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize);
void ZTLNX_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTLNX_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTLNX_DrawSprite(const rZT_SPRITE* iSprite, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTLNX_SpriteFree(rZT_SPRITE* iSprite);
rZT_SPRITE* ZTLNX_Sprite(const ZT_COLOR* iSource, const ZT_POINT* iBlock, ZT_FLAG iPalette);
ZT_SURFACE* ZTLNX_SurfaceFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_FLAG* oPalette);
void ZTLNX_SizeFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_POINT* oSize);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTLNX_H_INCLUDED
