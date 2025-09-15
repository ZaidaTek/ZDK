/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_RT_H_INCLUDED
#define ZTW32_RT_H_INCLUDED

#include "../ZTK-RT.h"
#include "ZTW32.h"

#define WIN32_LEAN_AND_MEAN // since 2020-12-31
#define WINVER 0x0501 // so that AlphaBlend function is included
#include <windows.h>

#define ZTW32_DEFAULT_CLASS "ZTK-ZTW32"
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
	    ZT_THREAD* dummyTHREAD; //alignment
	    ZT_INDEX sent;
	    ZT_INDEX received;
	} pump;
	HINSTANCE instance;
	HINSTANCE dummyHINSTANCE; //alignment
	struct {
        HWND handle;
        HWND dummyHWND; //alignment
        RECT rect;
        RECT dimensions;
        MSG message;
        MSG dummyMSG; //alignment
        DWORD style;
        DWORD dummyDWORD; //alignment
        ZT_LIST* fonts;
        ZT_LIST* dummyList;
    } window;
} rZTW32_HOST;

extern rZTW32_HOST rZTW32_Host;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
///ZTW32.c
LRESULT CALLBACK ZTW32_CallbackInit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
LRESULT CALLBACK ZTW32_CallbackMain(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
LRESULT CALLBACK ZTW32_CallbackExit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
///ZTW32__Debug.c
void ZTW32_PrintMessage(ZT_INDEX iMessage);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTW32_RT_H_INCLUDED
