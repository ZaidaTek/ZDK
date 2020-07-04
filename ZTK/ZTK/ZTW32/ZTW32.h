/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_H_INCLUDED
#define ZTW32_H_INCLUDED

#include "../../ZTK/ZTK__Runtime.h"

// needed so that AlphaBlend function is included - last checked w/ CB16.something
#define WINVER 0x0501
#include <windows.h>

#define ZTW32_MACRO

#define ZTW32_DEFAULT_CLASS "ZTK-ZTW32"
#define ZTW32_DEFAULT_CLASS_STYLE (CS_HREDRAW | CS_VREDRAW | CS_OWNDC)
#define ZTW32_DEFAULT_WINDOW_STYLE (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME | WS_MAXIMIZEBOX)
#define ZTW32_WM_USER 0x8001

#include "ZTW32_Draw.h"
#include "ZTW32_Timer.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#ifndef ZTW32_MACRO
ZT_TIME ZTW32_Ticks(void);
ZT_I ZTW32_ScreenWidth(void);
ZT_I ZTW32_ScreenHeight(void);
#else
#define ZTW32_Ticks() timeGetTime()
#define ZTW32_ScreenWidth() GetSystemMetrics(SM_CXFULLSCREEN)
#define ZTW32_ScreenHeight() GetSystemMetrics(SM_CYFULLSCREEN)
#endif // ZTW32_MACRO
void ZTW32_Free(void);
void ZTW32_New(ZT_WINDOW* iWindow);
void ZTW32_RectReload(void);
void ZTW32_RectApply(void);
void ZTW32_WindowDestroy(void);
void ZTW32_WindowOpen(void);
void ZTW32_HostWait(void);
ZT_INDEX ZTW32_HostMessages(void);
void ZTW32_HostProcess(void);
void ZTW32_HostLoadKey(ZT_U8* oTarget);
void ZTW32_HostLoadFont(ZT_FONT* iFont);
void ZTW32_HostFreeFont(ZT_FONT* iFont);
void ZTW32_HostLoop(void);
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ZTW32_H_INCLUDED
