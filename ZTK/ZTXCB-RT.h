/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTXCB_RT_H_INCLUDED
#define ZTXCB_RT_H_INCLUDED
#include "ZTK-RT.h"
#include "ZTXCB.h"
#if defined(ZTK_BUILD_XCB) && (ZTK_BUILD_XCB)
#include <xcb/xcb.h>
typedef struct {
	struct {
		xcb_connection_t* handle;
		xcb_screen_t* screen;
	} display;
	struct {
		xcb_window_t id;
		xcb_window_t alignId;
		xcb_generic_event_t* event;
	} window;
	struct {
		ZT_LIST* fonts;
	} res;
} rZTXCB_HOST;

extern rZTXCB_HOST rZTXCB_Host;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*
///ZTW32.c
LRESULT CALLBACK ZTXCB_CallbackInit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
LRESULT CALLBACK ZTXCB_CallbackMain(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
LRESULT CALLBACK ZTXCB_CallbackExit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam);
*/
///ZTXCB__Debug.c
#if defined(ZTK_BUILD_DEBUG) && (ZTK_BUILD_DEBUG)
void ZTXCB_DBG_Event(const xcb_generic_event_t* iEvent);
#endif // ZTK_BUILD_DEBUG
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ZTXCB_RT_H_INCLUDED
#endif // ZTK_BUILD_XCB
