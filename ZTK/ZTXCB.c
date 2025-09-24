/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTXCB_C_INCLUDED
#define ZTXCB_C_INCLUDED
#include "ZTXCB-RT.h"
#if defined(ZTK_BUILD_XCB) && (ZTK_BUILD_XCB)

#include <stdio.h>

rZTXCB_RUNTIME rZTXCB_Host;
/*
ZT_FLAG ZTXCB_PumpMain(void* iArg) {
	(void)iArg;
	while (!(rZTK_Host.system.state & ZTK_STATE_DESTROYED)) {
		
		ZTL_Sleep(rZTK_Host.system.timer.resolution ? rZTK_Host.system.timer.resolution : 1);
	}
	return 0x0;
}
void ZTXCB_PumpExit(void) {ZTL_ThreadFree(rZTXCB_Host.pump.handle);}
void ZTXCB_PumpInit(void) {rZTXCB_Host.pump.handle = ZTL_ThreadNew(&ZTXCB_PumpMain, NULL);}
*/

void ZTXCB_EventSend(void* iEvent) {
	xcb_send_event(rZTXCB_Host.conn, 0x0, rZTXCB_Host.window.id, XCB_EVENT_MASK_STRUCTURE_NOTIFY, (char*)iEvent);
	xcb_flush(rZTXCB_Host.conn);
	rZTXCB_Host.flag &= ~ZTXCB_FLAG_FLUSH;
}
void ZTXCB_TitleSet(const ZT_CHAR* iTitle) {
	xcb_change_property(rZTXCB_Host.conn, XCB_PROP_MODE_REPLACE, rZTXCB_Host.window.id, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, ZTC8_GetLength(iTitle), iTitle);
	rZTXCB_Host.flag |= ZTXCB_FLAG_FLUSH;
}
void ZTXCB_RectSet(const ZT_RECT* iRect) {
	uint32_t lValue[4] = {iRect->x, iRect->y, iRect->w, iRect->h};
	xcb_configure_window(rZTXCB_Host.conn, rZTXCB_Host.window.id, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, lValue);
	rZTXCB_Host.flag |= ZTXCB_FLAG_FLUSH;
}
void ZTXCB_RectGet(ZT_RECT* oRect) {
	xcb_get_geometry_reply_t* lReply;
	if ((lReply = xcb_get_geometry_reply(rZTXCB_Host.conn, xcb_get_geometry(rZTXCB_Host.conn, rZTXCB_Host.window.id), NULL)) != NULL) {
		if (oRect != NULL) {
			oRect->x = lReply->x;
			oRect->y = lReply->y;
			oRect->w = lReply->width;
			oRect->h = lReply->height;
		}
		free(lReply);
	}
}
void ZTXCB_RectApply(void) {
	ZTXCB_RectSet(&rZTK_Host.rect);
	ZTXCB_DrawSize();
}
void ZTXCB_Open(void) {
	ZTXCB_RectApply();
	xcb_map_window(rZTXCB_Host.conn, rZTXCB_Host.window.id);
	rZTXCB_Host.flag |= ZTXCB_FLAG_FLUSH;
}
void ZTXCB_FontFreeSources(void) {
	ZT_LIST* lList = rZTXCB_Host.res.fonts;
	for (ZT_INDEX i = 0; i < lList->length; i++) {
		// RemoveFontResourceEx((LPCTSTR)lList->items[i], FR_PRIVATE, 0x0);
		ZTM8_Free(lList->items[i]);
		lList->items[i] = NULL;
	}
	ZTM_ListLength(lList, 0);
}
void ZTXCB_FontFreeSource(rZT_FONT* iFont) {
	(void)iFont;
}
void ZTXCB_FontLoadSource(rZT_FONT* iFont) {
	if (iFont->source != NULL) {
		ZT_LIST* lList = rZTXCB_Host.res.fonts;
		for (ZT_INDEX i = 0; i < lList->length; i++) {if (ZTC8_Match(lList->items[i], iFont->source)) {return;}}
		// if (AddFontResourceEx((LPCTSTR)iFont->source, FR_PRIVATE, 0x0)) {ZTM_ListAppend(lList, ZTC8_Copy(iFont->source));}
		if (0x1) {ZTM_ListAppend(lList, ZTC8_Copy(iFont->source));}
	}
}
void ZTXCB_FontFreeRuntime(rZT_FONT* iFont) {
	(void)iFont;
}
void ZTXCB_FontLoadRuntime(rZT_FONT* iFont) {
	iFont->runtime = NULL;
}
void ZTXCB_ResourceLoad(void) {
	ZTXCB_DrawInit();
	ZTXCB_DrawSize();
}
void ZTXCB_ResourceFree(void) {
	ZTXCB_DrawExit();
}
void ZTXCB_Register(void) {
	uint32_t lAttr[2] = {rZTXCB_Host.screen->black_pixel, 0xffffff}; // TODO cycle through enum to get 0xffffff
	xcb_void_cookie_t lRequestWindow = xcb_create_window_checked(
		rZTXCB_Host.conn,
		rZTXCB_Host.screen->root_depth,
		(rZTXCB_Host.window.id = xcb_generate_id(rZTXCB_Host.conn)),
		(rZTXCB_Host.window.root = rZTXCB_Host.screen->root),
		rZTK_Host.rect.x, rZTK_Host.rect.y, rZTK_Host.rect.w, rZTK_Host.rect.h,
		0, // border width
		XCB_WINDOW_CLASS_INPUT_OUTPUT,
		rZTXCB_Host.screen->root_visual,
		XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
		lAttr
	);
	xcb_generic_error_t* lErrorWindow;
	if (
		((lErrorWindow = xcb_request_check(rZTXCB_Host.conn, lRequestWindow)) == NULL) &&
		((rZTXCB_Host.res.prot = xcb_intern_atom_reply(rZTXCB_Host.conn, xcb_intern_atom(rZTXCB_Host.conn, 0x1, 12, "WM_PROTOCOLS"), NULL)) != NULL) &&
		((rZTXCB_Host.res.quit = xcb_intern_atom_reply(rZTXCB_Host.conn, xcb_intern_atom(rZTXCB_Host.conn, 0x1, 16, "WM_DELETE_WINDOW"), NULL)) != NULL)
	) {
		xcb_change_property(
			rZTXCB_Host.conn,
			XCB_PROP_MODE_REPLACE,
			rZTXCB_Host.window.id,
			rZTXCB_Host.res.prot->atom,
			XCB_ATOM_ATOM, 32, 1,
			&rZTXCB_Host.res.quit->atom
		);
		rZTXCB_Host.flag |= ZTXCB_FLAG_FLUSH;
		ZTK_MSG_NCCreate(); // TODO does ZTK really support this being set at first iteration?
		ZTXCB_TitleSet(rZTK_Host.user.title);
	} else {
		// free(lErrorWindow); // TODO Not sure
	}
}
void ZTXCB_Free(void) {
	ZTXCB_ResourceFree();
	// XUnmapWindow(rZTXCB_Host.conn, rZTXCB_Host.window.id);
	// XDestroyWindow(rZTXCB_Host.conn, rZTXCB_Host.window.id);
	xcb_disconnect(rZTXCB_Host.conn);
	rZTXCB_Host.screen = NULL;
	rZTXCB_Host.conn = NULL;
}
void ZTXCB_New(void) {
	int lScreen;
	ZTM8_Zero(&rZTXCB_Host, sizeof(rZTXCB_Host));
	if ((rZTXCB_Host.conn = xcb_connect(NULL, &lScreen)) != NULL) {
		xcb_screen_iterator_t lIterator = xcb_setup_roots_iterator(xcb_get_setup(rZTXCB_Host.conn));
		while (lIterator.rem && lScreen) {--lScreen; xcb_screen_next(&lIterator);}
		if ((rZTXCB_Host.screen = lScreen ? NULL : lIterator.data) != NULL) {
			ZTXCB_Register();
			ZTXCB_ResourceLoad();
			rZTXCB_Host.callback = &ZTXCB_CallbackInit;
		}
	}
}
ZT_INDEX ZTXCB_Process(void) {
	ZT_INDEX lMessages = 0;
	while (((rZTXCB_Host.event = xcb_poll_for_event(rZTXCB_Host.conn)) != NULL)) {
		(*rZTXCB_Host.callback)(rZTXCB_Host.event);
		free(rZTXCB_Host.event);
		++lMessages;
	}
	return lMessages;
}
void ZTXCB_KeyLoad(ZT_U32* oTarget) {
	(void)oTarget;
}
void ZTXCB_Loop(void) {
	(*rZTXCB_Host.callback)(NULL);
}
void ZTXCB_Quit(void) {
	xcb_client_message_event_t* lEvent = ZTM8_New(32);
	lEvent->response_type = XCB_CLIENT_MESSAGE;
	lEvent->format = 32;
	lEvent->window = rZTXCB_Host.window.id;
	lEvent->type = rZTXCB_Host.res.prot->atom;
	lEvent->data.data32[0] = rZTXCB_Host.res.quit->atom;
	ZTXCB_EventSend(lEvent);
	ZTM8_Free(lEvent);
}
void ZTXCB_ModeMain(void) {rZTXCB_Host.callback = &ZTXCB_CallbackMain;}
void ZTXCB_ModeExit(void) {rZTXCB_Host.callback = &ZTXCB_CallbackExit;}
ZTXCB__RETURN ZTXCB_ProcessHead(ZTXCB__RETURN iReturn, ZT_INDEX iContext, const xcb_generic_event_t* iEvent) {
	#if defined(ZTK_BUILD_DEBUG) && (ZTK_BUILD_DEBUG)
	ZTXCB_DBG_Event(iContext, iEvent);
	#endif // ZTK_BUILD_DEBUG
	return iReturn;
}
ZTXCB__RETURN ZTXCB_ProcessMain(ZTXCB__RETURN iReturn) {
	ZTK_Process();
	return iReturn;
}
ZTXCB__RETURN ZTXCB_ProcessTail(ZTXCB__RETURN iReturn) {
	if (rZTXCB_Host.flag & ZTXCB_FLAG_FLUSH) {
		xcb_flush(rZTXCB_Host.conn);
		rZTXCB_Host.flag &= ~ZTXCB_FLAG_FLUSH;
	}
	return iReturn;
}
ZTXCB__RETURN ZTXCB_CallbackInit(const xcb_generic_event_t* iEvent) {
	ZT_FLAG lReturn = ZTXCB_ProcessHead(0x0, 0, iEvent);
	switch (iEvent != NULL ? iEvent->response_type & 0x7f : ZTXCB__WM_USER) {
		case XCB_PROPERTY_NOTIFY:
			if (((xcb_property_notify_event_t*)iEvent)->atom == rZTXCB_Host.res.prot->atom) {ZTK_MSG_Create();}
			break;
		case ZTXCB__WM_USER:
			if (rZTK_Host.system.state & ZTK_STATE_CREATED) {ZTK_MSG_User(); ZTXCB_ModeMain();}
			break;
		default:
			break;
	}
	return ZTXCB_ProcessTail(ZTXCB_ProcessMain(lReturn));
}
ZTXCB__RETURN ZTXCB_CallbackExit(const xcb_generic_event_t* iEvent) {
	ZT_FLAG lReturn = ZTXCB_ProcessHead(0x0, 2, iEvent);
	switch (iEvent != NULL ? iEvent->response_type & 0x7f : ZTXCB__WM_USER) {
		case ZTXCB__WM_USER:
			if (rZTK_Host.system.state & ZTK_STATE_EXITING) {ZTK_MSG_NCDestroy();}
			break;
		default:
			break;
	}
	return ZTXCB_ProcessTail(ZTXCB_ProcessMain(lReturn));
}
ZTXCB__RETURN ZTXCB_CallbackMain(const xcb_generic_event_t* iEvent) {
	ZT_FLAG lReturn = ZTXCB_ProcessHead(0x0, 1, iEvent);
	switch (iEvent != NULL ? iEvent->response_type & 0x7f : ZTXCB__WM_USER) {
		case XCB_REPARENT_NOTIFY: {
				const xcb_reparent_notify_event_t* lEvent = (xcb_reparent_notify_event_t*)iEvent;
				if (lEvent->event == rZTXCB_Host.window.id && lEvent->window == rZTXCB_Host.window.id) {
					rZTXCB_Host.window.root = lEvent->parent;
				}
			}
			break;
		case XCB_RESIZE_REQUEST: {
				// xcb_resize_request_event_t* lEvent = (xcb_resize_request_event_t*)iEvent;
				// ZTK_MSG_Move(lEvent->x, lEvent->y); // TODO no pos updates if resize window from top-left to NW
				// so I need to poll pos here?
				ZT_RECT lRect;
				ZTXCB_RectGet(&lRect);
				ZTK_MSG_Rect(&lRect);
			}
			break;
		case XCB_CONFIGURE_NOTIFY: {
				xcb_configure_notify_event_t* lEvent = (xcb_configure_notify_event_t*)iEvent;
				ZT_RECT lRect = {.x = lEvent->x, .y = lEvent->y, .w = lEvent->width, .h = lEvent->height};
				ZTK_MSG_Rect(&lRect);
			}
			break;
		case XCB_EXPOSE: {
				const xcb_expose_event_t* lEvent = (xcb_expose_event_t*)iEvent;
				(void)lEvent;
			}
			break;
		case XCB_BUTTON_PRESS: {
				const xcb_button_press_event_t* lEvent = (xcb_button_press_event_t*)iEvent;
				(void)lEvent;
			}
			break;
		case XCB_KEY_RELEASE: {
				const xcb_key_release_event_t* lEvent = (xcb_key_release_event_t*)iEvent;
				(void)lEvent;
				// switch (lEvent->detail) {
					// case 9: // ESC
						// ZTXCB_Quit();
						// break;
					// default:
						// break;
				// }
			}
			break;
		case XCB_CLIENT_MESSAGE:
			if (((xcb_client_message_event_t*)iEvent)->data.data32[0] == rZTXCB_Host.res.quit->atom) {
				ZTK_MSG_Close();
				ZTXCB_ModeExit();
			}
			break;
		default: break;
	}
	lReturn = ZTXCB_ProcessMain(lReturn);
	(*rZTK_Host.loop)();
	return ZTXCB_ProcessTail(lReturn);
}
#endif // ZTK_BUILD_XCB
#endif // ZTXCB_C_INCLUDED
