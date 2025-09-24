/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTXCB_RT_H_INCLUDED
#define ZTXCB_RT_H_INCLUDED
#include "ZTK-RT.h"
#include "ZTXCB.h"
#if defined(ZTK_BUILD_XCB) && (ZTK_BUILD_XCB)
#include <stdlib.h>
#include <xcb/xcb.h>
#define ZTXCB__RETURN ZT_FLAG
#define ZTXCB__WM_USER 0x81
#define ZTXCB__WM_PUMP 0x82
#define ZTXCB_FLAG_FLUSH 0x1
typedef struct {
	ZTXCB__RETURN					(*callback)(const xcb_generic_event_t*);
	void*							alignCallback;
	xcb_connection_t*				conn;
	xcb_screen_t*					screen;
	xcb_generic_event_t*			event;
	void*	 						alignEvent;
	struct {
		xcb_window_t 				id;
		xcb_window_t 				root; // REPARENT not in all handlers
	} window;
	ZT_FLAG 						flag;
	ZT_FLAG 						alignFlag;
	struct {
		xcb_intern_atom_reply_t*	prot;
		xcb_intern_atom_reply_t*	quit;
		ZT_LIST* 					fonts;
		ZT_LIST* 					alignFonts;
	} res;
} rZTXCB_RUNTIME;
extern rZTXCB_RUNTIME rZTXCB_Host;
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZTXCB__RETURN ZTXCB_CallbackInit(const xcb_generic_event_t* iEvent);
ZTXCB__RETURN ZTXCB_CallbackMain(const xcb_generic_event_t* iEvent);
ZTXCB__RETURN ZTXCB_CallbackExit(const xcb_generic_event_t* iEvent);
#if defined(ZTK_BUILD_DEBUG) && (ZTK_BUILD_DEBUG)
void ZTXCB_DBG_Event(ZT_FLAG iContext, const xcb_generic_event_t* iEvent);
#endif // ZTK_BUILD_DEBUG
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ZTXCB_RT_H_INCLUDED
#endif // ZTK_BUILD_XCB
