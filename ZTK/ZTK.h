/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_H_INCLUDED
#define ZTK_H_INCLUDED

// ZTK OPTIONS
#define ZTK_MACRO
// ZTK MANDATORY
#include <ZTM.h>
#include "ZTK_Define.h"
#include "ZTK_Types.h"
// ZTK FUNCTIONS
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
// OUT-OF-ORDER FUNCTIONS
ZT_BOOL ZTK_HostTimeout(const ZT_TIME* iLast, ZT_TIME iNow, ZT_TIME iTimeout);
void ZTK_HostTimeoutReset(ZT_TIME* iLast, ZT_TIME iNow, ZT_TIME iTimeout);
ZT_BOOL ZTK_Timeout(const ZT_TIME* iLast, ZT_TIME iTimeout);
void ZTK_TimeoutReset(ZT_TIME* iLast, ZT_TIME iTimeout);
ZT_BOOL ZTK_Repeat(ZT_TIME iTimeout);
// MAIN FUNCTIONS
void ZTK_Quit(void);
void ZTK_Free(void);
void ZTK_New(const ZT_CHAR* iTitle, const ZT_RECT* iRect, const ZT_CHAR* iIcon);
ZT_BOOL ZTK_Main(void (*iMainFunction)(void));
ZT_BOOL ZTK_Exiting(void);
// GET FUNCTIONS
ZT_TIME ZTK_GetTicks(void); // returns intermediate (frame-locked) time
ZT_FLAG ZTK_GetStatus(void);
ZT_FLAG ZTK_GetType(void);
ZT_FLAG ZTK_GetStyle(void);
const ZT_CHAR* ZTK_GetTitle(void);
ZT_CHAR ZTK_GetInputText(void);
ZT_I ZTK_GetPosX(void);
ZT_I ZTK_GetPosY(void);
ZT_I ZTK_GetWidth(void);
ZT_I ZTK_GetHeight(void);
ZT_COLOR ZTK_GetBackground(void);
ZT_FLAG ZTK_GetMouseState(void);
ZT_I ZTK_GetMousePosX(void);
ZT_I ZTK_GetMousePosY(void);
void ZTK_GetMousePos(ZT_POINT* oPosition);
void ZTK_GetPosition(ZT_POINT* oPosition);
void ZTK_GetSize(ZT_POINT* oSize);
void ZTK_GetRect(ZT_RECT* oRect);
ZT_FLAG ZTK_GetPalette(void);
// SET FUNCTIONS
void ZTK_InputTextCapture(ZT_BOOL iEnable);
void ZTK_IdleHoldOff(ZT_TIME iDelay);
void ZTK_IdleForbid(ZT_BOOL iForbid);
void ZTK_IdleAuto(ZT_BOOL iEnabled);
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
void ZTK_Background(ZT_BOOL iEnabled);
void ZTK_BackgroundAuto(ZT_BOOL iEnabled);
void ZTK_BackgroundColor(ZT_COLOR iColor);
void ZTK_FontColor(ZT_FONT* iFont, ZT_COLOR iColor);
void ZTK_FontColorBk(ZT_FONT* iFont, ZT_COLOR iColor);
void ZTK_FontSize(ZT_FONT* iFont, ZT_INDEX iSize);
void ZTK_FontStyle(ZT_FONT* iFont, ZT_FLAG iStyle);
// RUNTIME-DEPENDENT FUNCTIONS
ZT_TIME ZTK_HostGetTicks(void); // returns immediate system time
ZT_I ZTK_HostGetScreenWidth(void);
ZT_I ZTK_HostGetScreenHeight(void);
void ZTK_FontFree(ZT_FONT* iFont);
ZT_FONT* ZTK_FontNew(const ZT_CHAR* iSource, const ZT_CHAR* iName, ZT_I iHeight, ZT_FLAG iStyle, ZT_COLOR iColor);
void ZTK_FontReload(ZT_FONT *iFont);
void ZTK_FontSet(ZT_FONT* iFont);
void ZTK_DrawBackground(void);
void ZTK_DrawClear(void);
void ZTK_DrawPresent(void);
void ZTK_DrawSurface(ZT_SURFACE* iSurface, const ZT_RECT* iTarget);
void ZTK_DrawSprite(ZT_SPRITE* iSprite, const ZT_RECT* iTarget);
void ZTK_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox);
void ZTK_GetDrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize);
void ZTK_Heartbeat(ZT_TIME iDelay);
void ZTK_Idle(ZT_TIME iWake);
void ZTK_Open(void);
ZT_INDEX ZTK_PollMessages(ZT_EVENT** iEvent);
ZT_SURFACE* ZTK_SurfaceFromBitmap(const ZT_CHAR* iPath, ZT_FLAG* oPalette);
ZT_SURFACE* ZTK_SurfaceFromBitmapWithOpacity(const ZT_CHAR* iPath, ZT_INDEX iOpacity, ZT_FLAG* oPalette);
ZT_SURFACE* ZTK_SurfaceFromBitmapWithTransparent(const ZT_CHAR* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacity, ZT_FLAG* oPalette);
ZT_SURFACE* ZTK_SurfaceFromText(const ZT_CHAR* iText, ZT_FLAG* oPalette);
ZT_SURFACE* ZTK_SurfaceFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_FLAG* oPalette);
void ZTK_GetSizeFromText(const ZT_CHAR* iText, ZT_POINT* oSize);
void ZTK_GetSizeFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_POINT* oSize);
#ifdef __cplusplus
}
#endif // __cplusplus
// ZTK INCLUDES
#include "ZT_Sprite.h"
#include "ZTK_Printer.h"
#include "ZUI/ZUI.h"

#endif //ZTK_H_INCLUDED
