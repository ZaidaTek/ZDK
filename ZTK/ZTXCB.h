/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTXCB_H_INCLUDED
#define ZTXCB_H_INCLUDED
#if defined(ZTK_BUILD_XCB) && (ZTK_BUILD_XCB)
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
///ZTXCB.c
void ZTXCB_Free(void);
void ZTXCB_New(void);
void ZTXCB_RectLoad(void);
void ZTXCB_RectApply(void);
void ZTXCB_Open(void);
void ZTXCB_Quit(void);
ZT_INDEX ZTXCB_Process(void);
void ZTXCB_KeyLoad(ZT_U32* oTarget);
void ZTXCB_FontFreeSource(rZT_FONT* iFont);
void ZTXCB_FontLoadSource(rZT_FONT* iFont);
void ZTXCB_FontFreeRuntime(rZT_FONT* iFont);
void ZTXCB_FontLoadRuntime(rZT_FONT* iFont);
void ZTXCB_Loop(void);
///ZTXCB_Draw.c
void ZTXCB_DrawFontLoad(void);
void ZTXCB_DrawInit(void);
void ZTXCB_DrawExit(void);
void ZTXCB_DrawSize(void);
void ZTXCB_DrawClear(void);
void ZTXCB_DrawPresent(void);
void ZTXCB_DrawClearColor(ZT_COLOR iColor);
void ZTXCB_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox);
void ZTXCB_DrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize);
void ZTXCB_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTXCB_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTXCB_DrawSprite(const rZT_SPRITE* iSprite, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTXCB_SpriteFree(rZT_SPRITE* iSprite);
rZT_SPRITE* ZTXCB_Sprite(const ZT_COLOR* iSource, const ZT_POINT* iBlock, ZT_FLAG iPalette);
ZT_SURFACE* ZTXCB_SurfaceFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_FLAG* oPalette);
void ZTXCB_SizeFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_POINT* oSize);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ZTK_BUILD_XCB
#endif // ZTXCB_H_INCLUDED
