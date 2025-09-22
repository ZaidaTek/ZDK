/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTXCB_C_INCLUDED
#define ZTXCB_C_INCLUDED
#include "ZTXCB-RT.h"
#if defined(ZTK_BUILD_XCB) && (ZTK_BUILD_XCB)

rZTXCB_HOST rZTXCB_Host;

void ZTXCB_RectApply(void) {
}
void ZTXCB_DrawPresent(void) {
	xcb_flush(rZTXCB_Host.display.handle);
}
void ZTXCB_Open(void) {
    ZTXCB_RectApply();
	xcb_map_window(rZTXCB_Host.display.handle, rZTXCB_Host.window.id);
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
void ZTXCB_DrawExit(void) {
}
void ZTXCB_DrawSize(void) {
}
void ZTXCB_DrawInit(void) {
}
void ZTXCB_ResourceLoad(void) {
    ZTXCB_DrawInit();
    ZTXCB_DrawSize();
}
void ZTXCB_ResourceFree(void) {
    ZTXCB_DrawExit();
}
void ZTXCB_Register(void) {
	uint32_t lWinAttr[2] = {rZTXCB_Host.display.screen->white_pixel, XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION};
	rZTXCB_Host.window.id = xcb_generate_id(rZTXCB_Host.display.handle);
	xcb_create_window(
		rZTXCB_Host.display.handle,
		rZTXCB_Host.display.screen->root_depth,
		rZTXCB_Host.window.id,
		rZTXCB_Host.display.screen->root,
		rZTK_Host.rect.x, rZTK_Host.rect.y, rZTK_Host.rect.w, rZTK_Host.rect.h,
		0, // border width
		XCB_WINDOW_CLASS_INPUT_OUTPUT,
		rZTXCB_Host.display.screen->root_visual,
		XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
		lWinAttr
	);
}
void ZTXCB_Free(void) {
    ZTXCB_ResourceFree();
    // XUnmapWindow(rZTXCB_Host.display.handle, rZTXCB_Host.window.id);
    // XDestroyWindow(rZTXCB_Host.display.handle, rZTXCB_Host.window.id);
    xcb_disconnect(rZTXCB_Host.display.handle);
    rZTXCB_Host.display.screen = NULL;
    rZTXCB_Host.display.handle = NULL;
}
void ZTXCB_New(void) {
	ZTM8_Zero(&rZTXCB_Host, sizeof(rZTXCB_Host));
	int lScreen;
	if ((rZTXCB_Host.display.handle = xcb_connect(NULL, &lScreen)) != NULL) {
		xcb_screen_iterator_t lIterator = xcb_setup_roots_iterator(xcb_get_setup(rZTXCB_Host.display.handle));
		rZTXCB_Host.display.screen = NULL;
		while (lIterator.rem) {
			xcb_screen_next(&lIterator);
			if (!(--lScreen)) {rZTXCB_Host.display.screen = lIterator.data; break;}
		}
		if (rZTXCB_Host.display.screen != NULL) {
			ZTXCB_Register();
			ZTXCB_ResourceLoad();
		}
	}
}
// ZT_INDEX ZTXCB_Poll(void) {return PeekMessage(&(rZTXCB_Host.window.message), NULL, 0, 0, PM_REMOVE);}
ZT_INDEX ZTXCB_Poll(void) { // TODO check/optimize Windows version
	return ((rZTXCB_Host.window.event = xcb_poll_for_event(rZTXCB_Host.display.handle)) != NULL) ? 1 : 0;
}

ZT_INDEX ZTXCB_Process(void) {
	ZT_INDEX lMessages = 0;
	while (ZTXCB_Poll()) {
		++lMessages;
		ZTXCB_DBG_Event(rZTXCB_Host.window.event);
		ZTM8_Free(rZTXCB_Host.window.event); // TODO XCB specifies using free() for this
		// if (lEvent.type == ClientMessage && lEvent.xclient.data.l[0] == lQuit) {break;}
	}
	return lMessages;
}
void ZTXCB_KeyLoad(ZT_U32* oTarget) {
	(void)oTarget;
}
void ZTXCB_Loop(void) {
	// XEvent lEvent = {
		// .xclient.type = ClientMessage,
		// .xclient.window = rZTXCB_Host.window.id,
		// .xclient.message_type = XInternAtom(rZTXCB_Host.display.handle, "WM_PROTOCOLS", True),
		// .xclient.format = 32,
	// };
	// XSendEvent(rZTXCB_Host.display.handle, rZTXCB_Host.window.id, False, NoEventMask, &lEvent);
}
void ZTXCB_Quit(void) {
	// XEvent lEvent = {
		// .xclient.type = ClientMessage,
		// .xclient.window = rZTXCB_Host.window.id,
		// .xclient.message_type = XInternAtom(rZTXCB_Host.display.handle, "WM_PROTOCOLS", True),
		// .xclient.format = 32,
		// .xclient.data.l[0] = XInternAtom(rZTXCB_Host.display.handle, "WM_DELETE_WINDOW", False),
		// .xclient.data.l[1] = CurrentTime,
	// };
	// XSendEvent(rZTXCB_Host.display.handle, rZTXCB_Host.window.id, False, NoEventMask, &lEvent);
}
#endif // ZTK_BUILD_XCB
#endif // ZTXCB_C_INCLUDED
