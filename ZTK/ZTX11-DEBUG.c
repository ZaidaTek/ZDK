/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX11_DEBUG_C_INCLUDED
#define ZTX11_DEBUG_C_INCLUDED
#include "ZTX11-RT.h"
#if defined(ZTK_BUILD_DEBUG) && (ZTK_BUILD_DEBUG)
#if defined(ZTK_BUILD_X11) && (ZTK_BUILD_X11)
#include <stdio.h>
static const char* rZTX11__DBG_Events[] = {
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
void ZTX11_DBG_Event(const XEvent* iEvent) {
	printf("%s\n", rZTX11__DBG_Events[iEvent->type]);
}
#endif // ZTK_BUILD_X11
#endif // ZTK_BUILD_DEBUG
#endif // ZTX11_DEBUG_C_INCLUDED
