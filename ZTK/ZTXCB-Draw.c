/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTXCB_DRAW_C_INCLUDED
#define ZTXCB_DRAW_C_INCLUDED
#include "ZTXCB-RT.h"
#if defined(ZTK_BUILD_XCB) && (ZTK_BUILD_XCB)
void ZTXCB_DrawFontLoad(void) {}
void ZTXCB_DrawInit(void) {}
void ZTXCB_DrawExit(void) {}
void ZTXCB_DrawSize(void) {
	ZTK_BackgroundColor(rZTK_Host.user.background);
}
void ZTXCB_DrawClear(void) {}
void ZTXCB_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox) {
	(void)iText;
	(void)iTextBox;
}
void ZTXCB_DrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize) {
	(void)iText;
	(void)oTextSize;
}
void ZTXCB_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
	(void)iSurface;
	(void)iTarget;
	(void)iBlendmode;
}
void ZTXCB_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
	(void)iPixels;
	(void)iDimensions;
	(void)iTarget;
	(void)iBlendmode;
}
void ZTXCB_DrawPresent(void) {
}
void ZTXCB_DrawClearColor(ZT_COLOR iColor) {
	ZT_COLOR lColor[1] = {ZTM_ColorConvert(iColor, rZTK_Host.user.palette, ZTK_PALETTE_SYSTEM) & ZTM_ColorMaskC(ZTK_PALETTE_SYSTEM)};
	xcb_change_window_attributes(rZTXCB_Host.conn, rZTXCB_Host.window.id, XCB_CW_BACK_PIXEL, lColor);
	rZTXCB_Host.flag |= ZTXCB_FLAG_FLUSH;
}
void ZTXCB_DrawSprite(const rZT_SPRITE* iSprite, const ZT_RECT* iTarget, ZT_FLAG iBlendmode) {
	(void)iSprite;
	(void)iTarget;
	(void)iBlendmode;
}
void ZTXCB_SpriteFree(rZT_SPRITE* iSprite) {
	(void)iSprite;
}
rZT_SPRITE* ZTXCB_Sprite(const ZT_COLOR* iSource, const ZT_POINT* iBlock, ZT_FLAG iPalette) {
	(void)iSource;
	(void)iBlock;
	(void)iPalette;
	return NULL;
}
ZT_SURFACE* ZTXCB_SurfaceFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_FLAG* oPalette) {
	(void)iText;
	(void)iFont;
	(void)oPalette;
	return NULL;
}
void ZTXCB_SizeFromFont(const ZT_CHAR* iText, rZT_FONT* iFont, ZT_POINT* oSize) {
	(void)iText;
	(void)iFont;
	(void)oSize;
}
#endif // ZTK_BUILD_XCB
#endif // ZTXCB_DRAW_C_INCLUDED
