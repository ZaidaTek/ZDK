/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_H_INCLUDED
#define ZTK_H_INCLUDED

// ZTK OPTIONS
#define ZTK_OPENGL_ENABLE
// ZTK MANDATORY
#include <ZTL.h>
#include "ZTK-BUILD.h"
#include "ZTK-TYPE.h"
#include "ZTK-DEFINE.h"
#include "ZTK-DEFAULT.h"

#define ZTK_Sleep(LENGTH) ZTL_Sleep(LENGTH)
#define ZTK_HostGetScreenWidth() ZTL_ScreenWidth()
#define ZTK_HostGetScreenHeight() ZTL_ScreenHeight()

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// MAIN FUNCTIONS
void ZTK_Quit(void);
void ZTK_Free(void);
void ZTK_New(void (*iMainFunction)(void), const ZT_CHAR* iTitle, const ZT_RECT* iRect, const ZT_CHAR* iIcon);
ZT_BOOL ZTK_Main(void);
void ZTK_Open(void);
ZT_INDEX ZTK_PollMessages(ZT_EVENT** iEvent);
//ZT_BOOL ZTK_Exiting(void);
ZT_BOOL ZTK_Timeout(ZT_TIME iLast, ZT_TIME iTimeout);
ZT_BOOL ZTK_TimeoutReset(ZT_TIME* ioLast, ZT_TIME iTimeout);
ZT_BOOL ZTK_Repeat(ZT_TIME iTimeout);
void ZTK_DrawClear(void);
void ZTK_DrawPresent(void);
void ZTK_DrawSurface(ZT_SURFACE* iSurface, const ZT_RECT* iTarget);
void ZTK_DrawSprite(ZT_SPRITE* iSprite, const ZT_RECT* iTarget);
void ZTK_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox);
void ZTK_DrawTextDelete(ZT_CHAR* iText, const ZT_RECT* iTextBox);
// GET FUNCTIONS
ZT_TIME ZTK_GetTicks(void); // returns intermediate (frame-locked) time
ZT_FLAG ZTK_GetStatus(void);
ZT_FLAG ZTK_GetType(void);
ZT_FLAG ZTK_GetStyle(void);
ZT_FLAG ZTK_GetMouseState(void);
ZT_FLAG ZTK_GetPalette(void);
ZT_FLAG ZTK_GetPaletteSystem(void);
ZT_FLAG ZTK_GetRendererType(void);
ZT_CHAR ZTK_GetInputText(void);
ZT_I ZTK_GetPosX(void);
ZT_I ZTK_GetPosY(void);
ZT_I ZTK_GetWidth(void);
ZT_I ZTK_GetHeight(void);
ZT_I ZTK_GetMousePosX(void);
ZT_I ZTK_GetMousePosY(void);
ZT_COLOR ZTK_GetBackground(void);
const ZT_CHAR* ZTK_GetTitle(void);
void ZTK_GetMousePos(ZT_POINT* oPosition);
void ZTK_GetPosition(ZT_POINT* oPosition);
void ZTK_GetSize(ZT_POINT* oSize);
void ZTK_GetRect(ZT_RECT* oRect);
void ZTK_GetDrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize);
void ZTK_GetSizeFromText(const ZT_CHAR* iText, ZT_POINT* oSize);
void ZTK_GetSizeFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_POINT* oSize);
// SET FUNCTIONS
void ZTK_Renderer(ZT_FLAG iType);
void ZTK_InputTextCapture(ZT_BOOL iEnable);
void ZTK_Title(const ZT_CHAR* iTitle);
void ZTK_PaletteUser(ZT_FLAG iPalette);
void ZTK_PosX(ZT_I iX);
void ZTK_PosY(ZT_I iY);
void ZTK_Width(ZT_I iWidth);
void ZTK_Height(ZT_I iHeight);
void ZTK_Pos(const ZT_POINT* iPos);
void ZTK_PosFromIntegers(ZT_I iX, ZT_I iY);
void ZTK_Size(const ZT_POINT* iSize);
void ZTK_SizeFromIntegers(ZT_I iWidth, ZT_I iHeight);
void ZTK_Rect(const ZT_RECT* iRect);
void ZTK_RectFromIntegers(ZT_I iX, ZT_I iY, ZT_I iWidth, ZT_I iHeight);
// rename to ZTK_Background
void ZTK_BackgroundColor(ZT_COLOR iColor);

ZT_SURFACE* ZTK_SurfaceFromText(const ZT_CHAR* iText, ZT_FLAG* oPalette);
ZT_SURFACE* ZTK_SurfaceFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_FLAG* oPalette);
#ifdef __cplusplus
}
#endif // __cplusplus

#include "ZTK-Font.h"
#include "ZTK-Sprite.h"
#include "ZTK-Printer.h"

#endif // ZTK_H_INCLUDED
