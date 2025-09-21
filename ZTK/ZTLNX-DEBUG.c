/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTLNX_DEBUG_C_INCLUDED
#define ZTLNX_DEBUG_C_INCLUDED

#include "ZTLNX-RT.h"

#if defined(ZTK_BUILD_DEBUG) && (ZTK_BUILD_DEBUG)
#include <stdio.h>
static const char* rZTLNX__DBG_Events[] = {
	"",
	"",
	"KeyPress",
	"KeyRelease",
	"ButtonPress",
	"ButtonRelease",
	"MotionNotify",
	"EnterNotify",
	"LeaveNotify",
	"FocusIn",
	"FocusOut",
	"KeymapNotify",
	"Expose",
	"GraphicsExpose",
	"NoExpose",
	"VisibilityNotify",
	"CreateNotify",
	"DestroyNotify",
	"UnmapNotify",
	"MapNotify",
	"MapRequest",
	"ReparentNotify",
	"ConfigureNotify",
	"ConfigureRequest",
	"GravityNotify",
	"ResizeRequest",
	"CirculateNotify",
	"CirculateRequest",
	"PropertyNotify",
	"SelectionClear",
	"SelectionRequest",
	"SelectionNotify",
	"ColormapNotify",
	"ClientMessage",
	"MappingNotify"
};

void ZTLNX_DBG_Event(const XEvent* iEvent) {
	printf("%s\n", rZTLNX__DBG_Events[iEvent->type]);
}

#endif // ZTK_BUILD_DEBUG

#endif // ZTLNX_DEBUG_C_INCLUDED
