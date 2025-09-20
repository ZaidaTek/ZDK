/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTWIN_H_INCLUDED
#define ZTWIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
///ZTW32.c
void ZTW32_Free(void);
void ZTW32_New(void);
void ZTW32_RectLoad(void);
void ZTW32_RectApply(void);
void ZTW32_Open(void);
void ZTW32_Quit(void);
ZT_INDEX ZTW32_Process(void);
//void ZTW32_KeyLoad(ZT_U8* oTarget);
void ZTW32_KeyLoad(ZT_U32* oTarget);
void ZTW32_FontFreeSource(rZT_FONT* iFont);
void ZTW32_FontLoadSource(rZT_FONT* iFont);
void ZTW32_FontFreeRuntime(rZT_FONT* iFont);
void ZTW32_FontLoadRuntime(rZT_FONT* iFont);
void ZTW32_Loop(void);
///ZTW32_Draw.c
void ZTW32_DrawFontLoad(void);
void ZTW32_DrawInit(void);
void ZTW32_DrawExit(void);
void ZTW32_DrawSize(void);
void ZTW32_DrawClear(void);
void ZTW32_DrawPresent(void);
void ZTW32_DrawClearColor(ZT_COLOR iColor);
void ZTW32_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox);
void ZTW32_DrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize);
void ZTW32_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTW32_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTW32_DrawSprite(const rZT_SPRITE* iSprite, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
void ZTW32_SpriteFree(rZT_SPRITE* iSprite);
rZT_SPRITE* ZTW32_Sprite(const ZT_COLOR* iSource, const ZT_POINT* iBlock, ZT_FLAG iPalette);
ZT_SURFACE* ZTW32_SurfaceFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_FLAG* oPalette);
void ZTW32_SizeFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_POINT* oSize);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTWIN_H_INCLUDED
