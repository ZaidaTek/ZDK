/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTLNX_RT_H_INCLUDED
#define ZTLNX_RT_H_INCLUDED

#include "ZTK-RT.h"
#include "ZTLNX.h"

#include <X11/Xlib.h>

#define ZTLNX_X11_EVENT_MASK (SubstructureRedirectMask | SubstructureNotifyMask | StructureNotifyMask | ExposureMask)
#define ZTLNX_X11_INPUT_MASK (ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | FocusChangeMask)

/*
#define WIN32_LEAN_AND_MEAN // since 2020-12-31
#define WINVER 0x0501 // so that AlphaBlend function is included
#include <windows.h>

#define ZTLNX_DEFAULT_CLASS "ZTK-ZTW32"
#define ZTLNX_DEFAULT_CLASS_STYLE (CS_HREDRAW | CS_VREDRAW | CS_OWNDC)
#define ZTLNX_DEFAULT_WINDOW_STYLE (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME | WS_MAXIMIZEBOX)
#define ZTLNX_WM_USER 0x8001
#define ZTLNX_WM_PUMP 0x8002
*/


typedef struct {
	struct {
		Display* handle;
		void* alignHandle;
		int screen;
		int alignScreen;
	} display;
	struct {
		Window root;
		Window id;
		Atom quit;
		Atom alignQuit;
		XEvent event;
	} window;
	struct {
		ZT_LIST* fonts;
	} res;
	/*
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
	*/
} rZTLNX_HOST;

extern rZTLNX_HOST rZTLNX_Host;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*
///ZTW32.c
LRESULT CALLBACK ZTLNX_CallbackInit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
LRESULT CALLBACK ZTLNX_CallbackMain(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
LRESULT CALLBACK ZTLNX_CallbackExit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
*/
///ZTLNX__Debug.c
#if defined(ZTK_BUILD_DEBUG) && (ZTK_BUILD_DEBUG)
void ZTLNX_DBG_Event(const XEvent* iEvent);
#endif // ZTK_BUILD_DEBUG
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTLNX_RT_H_INCLUDED
