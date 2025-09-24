/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTWIN_RT_H_INCLUDED
#define ZTWIN_RT_H_INCLUDED
#include "ZTK-RT.h"
#include "ZTWIN.h"
#define WIN32_LEAN_AND_MEAN // since 2020-12-31
#include <windows.h>
#define ZTW32_DEFAULT_CLASS "ZTK-ZTWIN"
#define ZTW32_DEFAULT_CLASS_STYLE (CS_HREDRAW | CS_VREDRAW | CS_OWNDC)
#define ZTW32_DEFAULT_WINDOW_STYLE (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME | WS_MAXIMIZEBOX)
#define ZTW32_WM_USER 0x8001
#define ZTW32_WM_PUMP 0x8002
typedef struct {
	struct {
		HDC buffer;
		HDC pipe;
		HDC main;
		HDC font;
	} dc;
	struct {
		ZT_THREAD* runtime;
		ZT_THREAD* alignRuntime;
		ZT_INDEX sent;
		ZT_INDEX received;
	} pump;
	HINSTANCE instance;
	HINSTANCE alignInstance;
	struct {
		HWND handle;
		HWND alignHandle;
		RECT rect;
		RECT dimensions;
		MSG message;
		MSG alignMessage;
		DWORD style;
		DWORD alignStyle;
		ZT_LIST* fonts;
		ZT_LIST* alignFonts;
	} window;
} rZTW32_RUNTIME;
extern rZTW32_RUNTIME rZTW32_Host;
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
LRESULT CALLBACK ZTW32_CallbackInit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
LRESULT CALLBACK ZTW32_CallbackMain(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
LRESULT CALLBACK ZTW32_CallbackExit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
#if defined(ZTK_BUILD_DEBUG) && (ZTK_BUILD_DEBUG)
void ZTWIN_DBG_Message(ZT_INDEX iMessage);
#endif // ZTK_BUILD_DEBUG
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ZTWIN_RT_H_INCLUDED
