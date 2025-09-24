/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTXCB_DEBUG_C_INCLUDED
#define ZTXCB_DEBUG_C_INCLUDED
#include "ZTXCB-RT.h"
#if defined(ZTK_BUILD_DEBUG) && (ZTK_BUILD_DEBUG)
#if defined(ZTK_BUILD_XCB) && (ZTK_BUILD_XCB)
#include <stdio.h>
static const char* rZTXCB__DBG_Context[3] = {"init", "main", "exit"};
static const char* rZTXCB__DBG_Events[] = {
	"",
	"",
	"XCB_KEY_PRESS",
	"XCB_KEY_RELEASE",
	"XCB_BUTTON_PRESS",
	"XCB_BUTTON_RELEASE",
	"XCB_MOTION_NOTIFY",
	"XCB_ENTER_NOTIFY",
	"XCB_LEAVE_NOTIFY",
	"XCB_FOCUS_IN",
	"XCB_FOCUS_OUT",
	"XCB_KEYMAP_NOTIFY",
	"XCB_EXPOSE",
	"XCB_GRAPHICS_EXPOSURE",
	"XCB_NO_EXPOSURE",
	"XCB_VISIBILITY_NOTIFY",
	"XCB_CREATE_NOTIFY",
	"XCB_DESTROY_NOTIFY",
	"XCB_UNMAP_NOTIFY",
	"XCB_MAP_NOTIFY",
	"XCB_MAP_REQUEST",
	"XCB_REPARENT_NOTIFY",
	"XCB_CONFIGURE_NOTIFY",
	"XCB_CONFIGURE_REQUEST",
	"XCB_GRAVITY_NOTIFY",
	"XCB_RESIZE_REQUEST",
	"XCB_CIRCULATE_NOTIFY",
	"XCB_CIRCULATE_REQUEST",
	"XCB_PROPERTY_NOTIFY",
	"XCB_SELECTION_CLEAR",
	"XCB_SELECTION_REQUEST",
	"XCB_SELECTION_NOTIFY",
	"XCB_COLORMAP_NOTIFY",
	"XCB_CLIENT_MESSAGE",
	"XCB_MAPPING_NOTIFY",
	"XCB_GE_GENERIC",
	"<OTHER>",
	"<WM_USER>",
	"<WM_PUMP>",
};
void ZTXCB_DBG_Event(ZT_FLAG iContext, const xcb_generic_event_t* iEvent) {
	if (iEvent != NULL) {
		ZT_CHAR* lExtra = NULL;
		ZT_INDEX lIndex;
		switch (lIndex = (iEvent->response_type & 0x7f)) {
			case XCB_PROPERTY_NOTIFY: {
					void* lReply = (void*)xcb_get_atom_name_reply(rZTXCB_Host.conn, xcb_get_atom_name(rZTXCB_Host.conn, ((xcb_property_notify_event_t*)iEvent)->atom), NULL);
					lExtra = ZTC8_CopyLength((const ZT_CHAR*)xcb_get_atom_name_name(lReply), xcb_get_atom_name_name_length(lReply));
					free(lReply);
				}
				break;
			default:
				if (lIndex > 36) {lIndex = 37;}
				break;
		}
		ZT_CHAR* lBytes = ZTC8_Bytes((ZT_U8*)iEvent, 32, (const ZT_CHAR*)" ", 4);
		printf("%s\t%s\t%s\t%s\n",
			rZTXCB__DBG_Context[iContext & 0x3],
			(const char*)lBytes,
			rZTXCB__DBG_Events[lIndex],
			lExtra != NULL ? (const char*)lExtra : ""
		);
		ZTM8_Free(lBytes);
		if (lExtra != NULL) {ZTM8_Free(lExtra);}
	} else {
		// printf("<WM_USER>\n");
	}
}
#endif // ZTK_BUILD_XCB
#endif // ZTK_BUILD_DEBUG
#endif // ZTXCB_DEBUG_C_INCLUDED
