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
void ZTXCB_DBG_Event(const xcb_generic_event_t* iEvent) {
	(void)iEvent;
	printf("%s\n", "asd");
}
#endif // ZTK_BUILD_XCB
#endif // ZTK_BUILD_DEBUG
#endif // ZTXCB_DEBUG_C_INCLUDED
