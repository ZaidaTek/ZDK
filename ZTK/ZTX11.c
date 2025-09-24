/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX11_C_INCLUDED
#define ZTX11_C_INCLUDED
#include "ZTX11-RT.h"
#if defined(ZTK_BUILD_X11) && (ZTK_BUILD_X11)

rZTX11_HOST rZTX11_Host;

/*
ZT_FLAG ZTX11_Pump(void* iArg) {
	(void)iArg;
	while (!(rZTK_Host.system.state & ZTK_STATE_RUNNING)) {ZTL_Sleep(rZTK_Host.system.timer.resolution ? rZTK_Host.system.timer.resolution : 1);}
	while (!(rZTK_Host.system.state & ZTK_STATE_EXITING)) {
		if (rZTX11_Host.pump.received == rZTX11_Host.pump.sent) {
			SendMessageCallback(rZTX11_Host.window.handle, ZTX11_WM_PUMP, 0x0, 0x0, NULL, 0);
			++rZTX11_Host.pump.sent;
		}
		ZTL_Sleep(rZTK_Host.system.timer.resolution ? rZTK_Host.system.timer.resolution : 1);
	}
	return 0x0;
}
void ZTX11_PumpExit(void) {ZTL_ThreadFree(rZTX11_Host.pump.runtime);}
void ZTX11_PumpInit(void) {rZTX11_Host.pump.runtime = ZTL_ThreadNew(&ZTX11_Pump, NULL);}
*/
void ZTX11_RectApply(void) {
	/*
	RECT lRect = rZTX11_Host.window.rect;
	AdjustWindowRectEx(&lRect, rZTX11_Host.window.style, FALSE, 0);
	SetWindowPos(rZTX11_Host.window.handle, NULL, lRect.left, lRect.top, lRect.right - lRect.left, lRect.bottom - lRect.top, SWP_NOCOPYBITS | SWP_NOZORDER);
	ZTX11_DrawSize();
	*/
}
void ZTX11_DrawPresent(void) {
	XFlush(rZTX11_Host.display.handle);
}
void ZTX11_Open(void) {
	ZTX11_RectApply();
	XMapWindow(rZTX11_Host.display.handle, rZTX11_Host.window.id);
	// ShowWindow(rZTX11_Host.window.handle, SW_SHOW);
}
void ZTX11_FontFreeSources(void) {
	ZT_LIST* lList = rZTX11_Host.res.fonts;
	for (ZT_INDEX i = 0; i < lList->length; i++) {
		// RemoveFontResourceEx((LPCTSTR)lList->items[i], FR_PRIVATE, 0x0);
		ZTM8_Free(lList->items[i]);
		lList->items[i] = NULL;
	}
	ZTM_ListLength(lList, 0);
}
void ZTX11_FontFreeSource(rZT_FONT* iFont) {
	(void)iFont;
}
void ZTX11_FontLoadSource(rZT_FONT* iFont) {
	if (iFont->source != NULL) {
		ZT_LIST* lList = rZTX11_Host.res.fonts;
		for (ZT_INDEX i = 0; i < lList->length; i++) {if (ZTC8_Match(lList->items[i], iFont->source)) {return;}}
		// if (AddFontResourceEx((LPCTSTR)iFont->source, FR_PRIVATE, 0x0)) {ZTM_ListAppend(lList, ZTC8_Copy(iFont->source));}
		if (0x1) {ZTM_ListAppend(lList, ZTC8_Copy(iFont->source));}
	}
}
void ZTX11_FontFreeRuntime(rZT_FONT* iFont) {
	(void)iFont;
	// DeleteObject((HFONT)iFont->runtime);
}
void ZTX11_FontLoadRuntime(rZT_FONT* iFont) {
	//ZTX11_FontFreeRuntime(iFont);
	// LOGFONT lFontStyle;
	// ZTM8_Zero(&lFontStyle, sizeof(LOGFONT));
	// lFontStyle.lfHeight = iFont->height;
	// lFontStyle.lfWeight = (iFont->style & ZTK_FONT_STYLE_BOLD) ? FW_BOLD : FW_NORMAL;
	// lFontStyle.lfItalic = (iFont->style & ZTK_FONT_STYLE_ITALIC) ? 0x1 : 0x0;
	// lFontStyle.lfUnderline = (iFont->style & ZTK_FONT_STYLE_UNDERLINE) ? 0x1 : 0x0;
	// lFontStyle.lfStrikeOut = (iFont->style & ZTK_FONT_STYLE_STRIKEOUT) ? 0x1 : 0x0;
	// lFontStyle.lfCharSet = ANSI_CHARSET;
	// lFontStyle.lfOutPrecision = OUT_DEFAULT_PRECIS;
	// lFontStyle.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	// lFontStyle.lfQuality = NONANTIALIASED_QUALITY;
	// lFontStyle.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
	// ZTC8_CopyTargetLength(iFont->name, (ZT_CHAR*)lFontStyle.lfFaceName, LF_FACESIZE - 1); // does this copy NT if length exceeded?
	// lFontStyle.lfFaceName[LF_FACESIZE - 1] = 0x0;
	// iFont->runtime = CreateFontIndirect(&lFontStyle);
	iFont->runtime = NULL;
}
void ZTX11_DrawExit(void) {
	// DeleteDC(rZTW32_Host.dc.buffer);
	// DeleteDC(rZTW32_Host.dc.pipe);
	// DeleteDC(rZTW32_Host.dc.font);
	// ReleaseDC(rZTW32_Host.window.handle, rZTW32_Host.dc.main);
}
void ZTX11_DrawSize(void) {
	// HBITMAP lSize = CreateCompatibleBitmap(rZTW32_Host.dc.main, rZTK_Host.rect.w, rZTK_Host.rect.h);
	// SelectObject(rZTW32_Host.dc.buffer, lSize);
	// DeleteObject(SelectObject(rZTW32_Host.dc.buffer, GetStockObject(DC_BRUSH)));
	// ZTK_BackgroundColor(rZTK_Host.user.background); // can this be skipped, and put in init instead?
	// ZTW32_DrawFontLoad(); // this too?
}
void ZTX11_DrawInit(void) {
	// rZTW32_Host.dc.main = GetDC(rZTW32_Host.window.handle);
	// rZTW32_Host.dc.font = CreateCompatibleDC(rZTW32_Host.dc.main);
	// rZTW32_Host.dc.pipe = CreateCompatibleDC(rZTW32_Host.dc.main);
	// rZTW32_Host.dc.buffer = CreateCompatibleDC(rZTW32_Host.dc.main);
}
void ZTX11_ResourceLoad(void) {
	//rZTX11_Host.res.fonts = ZTM_ListNew(0);
	ZTX11_DrawInit();
	ZTX11_DrawSize();
	//ZTX11_PumpInit();
}
void ZTX11_ResourceFree(void) {
	//ZTX11_PumpExit();
	ZTX11_DrawExit();
	//ZTX11_FontFreeSources();
	//ZTM_ListFree(rZTX11_Host.res.fonts);
}
void ZTX11_Register(void) {
	XSetWindowAttributes lWinAttr;
	lWinAttr.event_mask = ZTX11_EVENT_MASK;
	lWinAttr.do_not_propagate_mask = 0;
	lWinAttr.background_pixel = 0x0;
	rZTX11_Host.window.id = XCreateWindow(
		rZTX11_Host.display.handle, (rZTX11_Host.window.root = XRootWindow(rZTX11_Host.display.handle, rZTX11_Host.display.screen)),
		rZTK_Host.rect.x, rZTK_Host.rect.y, rZTK_Host.rect.w, rZTK_Host.rect.h, 0, // x, y, w, h, border
		CopyFromParent, InputOutput, CopyFromParent, // depth, class, visual
		CWEventMask | NoEventMask | CWBackPixel, // .event_mask, .do_not_propagate_mask, .background_pixel
		&lWinAttr
	);
	XStoreName(rZTX11_Host.display.handle, rZTX11_Host.window.id, (const char*)rZTK_Host.user.title);
	XSelectInput(rZTX11_Host.display.handle, rZTX11_Host.window.id, ZTX11_INPUT_MASK);
	rZTX11_Host.window.quit = XInternAtom(rZTX11_Host.display.handle, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(rZTX11_Host.display.handle, rZTX11_Host.window.id, &rZTX11_Host.window.quit, 1);
	/*
	WNDCLASSEX lW32Container;
	ZTM8_Zero(&lW32Container, sizeof(lW32Container));
	lW32Container.cbSize = sizeof(lW32Container);
	lW32Container.style = ZTX11_DEFAULT_CLASS_STYLE;
	lW32Container.lpfnWndProc = &ZTX11_CallbackInit;
	lW32Container.hInstance = rZTX11_Host.instance;
	if ((rZTK_Host.user.icon != NULL) && ZTL_FileExists(rZTK_Host.user.icon)) {
		lW32Container.hIcon = (HICON)LoadImage(NULL, (LPCTSTR)rZTK_Host.user.icon, IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_LOADFROMFILE | LR_DEFAULTCOLOR);
	} else {
		lW32Container.hIcon = LoadIcon(rZTX11_Host.instance, MAKEINTRESOURCE(ZTK_ICON_INTEGRATED));
	}
	lW32Container.hCursor = LoadCursor(NULL, IDC_ARROW);
	lW32Container.hbrBackground = (HBRUSH)COLOR_SCROLLBAR; // SCROLLBAR = BLACK
	lW32Container.lpszClassName = ZTX11_DEFAULT_CLASS;
	lW32Container.hIconSm = (HICON)LoadImage(rZTX11_Host.instance, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	if (RegisterClassEx(&lW32Container)) {
		rZTX11_Host.window.style = ZTX11_DEFAULT_WINDOW_STYLE;
		RECT lRect = rZTX11_Host.window.rect;
		AdjustWindowRectEx(&lRect, rZTX11_Host.window.style, FALSE, 0);
		rZTX11_Host.window.handle = CreateWindow(ZTX11_DEFAULT_CLASS, (LPCTSTR)rZTK_Host.user.title, rZTX11_Host.window.style, lRect.left, lRect.top, lRect.right - lRect.left, lRect.bottom - lRect.top, NULL, NULL, rZTX11_Host.instance, NULL);
	}
	*/
}
void ZTX11_Free(void) {
	ZTX11_ResourceFree();
	//DestroyWindow(rZTX11_Host.window.handle);
	XUnmapWindow(rZTX11_Host.display.handle, rZTX11_Host.window.id);
	XDestroyWindow(rZTX11_Host.display.handle, rZTX11_Host.window.id);
	XCloseDisplay(rZTX11_Host.display.handle);
	rZTX11_Host.display.handle = NULL;
}
void ZTX11_New(void) {
	ZTM8_Zero(&rZTX11_Host, sizeof(rZTX11_Host));
	if ((rZTX11_Host.display.handle = XOpenDisplay(NULL)) != NULL) {
		// if (() != NULL) {}
		rZTX11_Host.display.screen = XDefaultScreen(rZTX11_Host.display.handle);
		ZTX11_Register();
		ZTX11_ResourceLoad();
		//if (rZTX11_Host.window.id != NULL) {ZTX11_ResourceLoad();}
	}
}
ZT_INDEX ZTX11_Process(void) {
	ZT_INDEX lMessages = 0;
	while (XCheckWindowEvent(rZTX11_Host.display.handle,rZTX11_Host.window.id, ZTX11_EVENT_MASK, &rZTX11_Host.window.event)) {
		ZTX11_DBG_Event(&rZTX11_Host.window.event);
		// if (lEvent.type == ClientMessage && lEvent.xclient.data.l[0] == lQuit) {break;}
		++lMessages;
	}
	return lMessages;
}
//void ZTX11_KeyLoad(ZT_U8* oTarget) {
void ZTX11_KeyLoad(ZT_U32* oTarget) {
	(void)oTarget;
	// ZTM8_Zero(oTarget, ZTK_KEY_SIZE_LENGTH >> 3);
	// for (ZT_INDEX i = 0x8; i < ZTK_KEY_SIZE_LENGTH; i++) { // offset to skip VK_MOUSE keys
		// ZT_FLAG lMask = (0x1 << (i % ZTK_KEY_SIZE_UNIT));
		// ZT_FLAG lIndex = (i >> ZTK_KEY_SIZE_SHIFT);
		// oTarget[lIndex] |= ((GetAsyncKeyState(i) & 0x8000) ? lMask : 0x0);
	// }
}
// #define ZTX11_MouseX(LPARAM) (LPARAM & 0xffff)
// #define ZTX11_MouseY(LPARAM) ((LPARAM >> 16))
// #define ZTX11_MouseWheel(WPARAM) ((ZT_I16)(WPARAM >> 16))
// #define ZTX11_MouseXButton(WPARAM) (((WPARAM >> 16) & XBUTTON2) ? ZTK_SID_MOUSE_X2BUTTON : ZTK_SID_MOUSE_X1BUTTON)
/*
#define ZTX11_MouseState(WPARAM) ({\
	ZT_FLAG rHOSTMOUSESTATE_s = (iWParam & MK_LBUTTON) ? ZTK_SID_MOUSE_LBUTTON : ZTK_SID_NONE;\
	if (iWParam & MK_RBUTTON) {lState |= ZTK_SID_MOUSE_RBUTTON;}\
	if (iWParam & MK_MBUTTON) {lState |= ZTK_SID_MOUSE_MBUTTON;}\
	if (iWParam & MK_XBUTTON1) {lState |= ZTK_SID_MOUSE_X1BUTTON;}\
	if (iWParam & MK_XBUTTON2) {lState |= ZTK_SID_MOUSE_X2BUTTON;}\
	rHOSTMOUSESTATE_s;\
})
*/
// void ZTX11_Command(ZT_FLAG iWParam) {
	// switch (iWParam) {
		// case SC_MINIMIZE: ZTK_MSG_Minimize(ZT_TRUE); break;
		// case SC_RESTORE: ZTK_MSG_Minimize(ZT_FALSE); break;
		// case SC_MAXIMIZE: ZTK_MSG_Minimize(ZT_FALSE); break;
		// default: break;
	// }
// }
void ZTX11_Loop(void) {
	// SendMessageCallback(rZTX11_Host.window.handle, ZTX11_WM_USER, 0x0, 0x0, NULL, 0);
	XEvent lEvent = {
		.xclient.type = ClientMessage,
		.xclient.window = rZTX11_Host.window.id,
		.xclient.message_type = XInternAtom(rZTX11_Host.display.handle, "WM_PROTOCOLS", True),
		.xclient.format = 32,
	};
	XSendEvent(rZTX11_Host.display.handle, rZTX11_Host.window.id, False, NoEventMask, &lEvent);
}
void ZTX11_Quit(void) {
	// ZTK_MSG_Close(); ZTX11_ModeExit();
	XEvent lEvent = {
		.xclient.type = ClientMessage,
		.xclient.window = rZTX11_Host.window.id,
		.xclient.message_type = XInternAtom(rZTX11_Host.display.handle, "WM_PROTOCOLS", True),
		.xclient.format = 32,
		.xclient.data.l[0] = XInternAtom(rZTX11_Host.display.handle, "WM_DELETE_WINDOW", False),
		.xclient.data.l[1] = CurrentTime,
	};
	XSendEvent(rZTX11_Host.display.handle, rZTX11_Host.window.id, False, NoEventMask, &lEvent);
}
/*
void ZTX11_ModeMain(void) {SetWindowLongPtr(rZTX11_Host.window.handle, GWL_WNDPROC, (LONG_PTR)&ZTX11_CallbackMain);}
void ZTX11_ModeExit(void) {SetWindowLongPtr(rZTX11_Host.window.handle, GWL_WNDPROC, (LONG_PTR)&ZTX11_CallbackExit);}
LRESULT CALLBACK ZTX11_CallbackInit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
	//ZTX11_PrintMessage(iMessage);
	if (!(rZTK_Host.buffer.state & ZTK_STATE_DEFINED)) {
		rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
		rZTK_Host.buffer.state |= ZTK_STATE_DEFINED;
	}
	switch (iMessage) {
		case WM_NCCREATE: ZTK_MSG_NCCreate(); break;
		case WM_CREATE: ZTK_MSG_Create(); break;
		case WM_ACTIVATE: ZTK_MSG_Activate(iWParam & 0x1); break;
		case WM_KILLFOCUS: ZTK_MSG_KeyFocus(ZT_FALSE); break;
		case WM_SETFOCUS: ZTK_MSG_KeyFocus(ZT_TRUE); break;
		case WM_SHOWWINDOW: ZTK_MSG_Show(iWParam ? ZT_TRUE : ZT_FALSE); break;
		case WM_SIZE: ZTK_MSG_Size((ZT_I)LOWORD(iLParam), (ZT_I)HIWORD(iLParam)); break;
		case WM_MOVE: ZTK_MSG_Move((ZT_I)LOWORD(iLParam), (ZT_I)HIWORD(iLParam)); break;
		case ZTX11_WM_USER: ZTK_MSG_User(); ZTX11_ModeMain(); break;
		default: break;
	}
	ZTK_Process();
	return DefWindowProc(iHwnd, iMessage, iWParam, iLParam);
}
LRESULT CALLBACK ZTX11_CallbackExit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
	//ZTX11_PrintMessage(iMessage);
	switch (iMessage) {
		case WM_ACTIVATE: ZTK_MSG_Activate(iWParam & 0x1); break;
		case WM_KILLFOCUS: ZTK_MSG_KeyFocus(ZT_FALSE); break;
		case WM_SETFOCUS: ZTK_MSG_KeyFocus(ZT_TRUE); break;
		case WM_DESTROY: break;
		case WM_NCDESTROY: ZTK_MSG_NCDestroy(); break;
		default: break;
	}
	ZTK_Process();
	return DefWindowProc(iHwnd, iMessage, iWParam, iLParam);
}
LRESULT CALLBACK ZTX11_CallbackMain(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
	//ZTX11_PrintMessage(iMessage);
	static ZT_BOOL lPumped = ZT_FALSE;
	static ZT_BOOL lDefault = ZT_TRUE;
	switch (iMessage) {
		case ZTX11_WM_USER: break;
		case ZTX11_WM_PUMP: lPumped = ZT_TRUE; break;
		case WM_SIZE: ZTK_MSG_Size((ZT_I)LOWORD(iLParam), (ZT_I)HIWORD(iLParam)); break;
		case WM_MOVE: ZTK_MSG_Move((ZT_I)LOWORD(iLParam), (ZT_I)HIWORD(iLParam)); break;
		case WM_KILLFOCUS: ZTK_MSG_KeyFocus(ZT_FALSE); break;
		case WM_SETFOCUS: ZTK_MSG_KeyFocus(ZT_TRUE); break;
		case WM_ACTIVATE: ZTK_MSG_Activate(iWParam & 0x1); break;
		case WM_SHOWWINDOW: ZTK_MSG_Show(iWParam ? ZT_TRUE : ZT_FALSE); break;
		case WM_SYSCOMMAND: ZTX11_Command(iWParam); break;
		case WM_MOUSEMOVE: ZTK_MSG_MouseMove(ZTX11_MouseX(iLParam), ZTX11_MouseY(iLParam)); break;
		case WM_LBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_LBUTTON, ZT_TRUE); break;
		case WM_RBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_RBUTTON, ZT_TRUE); break;
		case WM_MBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_MBUTTON, ZT_TRUE); break;
		case WM_LBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_LBUTTON, ZT_FALSE); break;
		case WM_RBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_RBUTTON, ZT_FALSE); break;
		case WM_MBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_MBUTTON, ZT_FALSE); break;
		case WM_XBUTTONUP: ZTK_MSG_MouseButton(ZTX11_MouseXButton(iWParam), ZT_FALSE); break;
		case WM_XBUTTONDOWN: ZTK_MSG_MouseButton(ZTX11_MouseXButton(iWParam), ZT_TRUE); break;
		case WM_MOUSEWHEEL: ZTK_MSG_MouseWheel(ZTX11_MouseWheel(iWParam)); break;
		case WM_KEYDOWN: if (!((rZTK_Host.system.events.pump & ZTK_HID_KEY) && (iLParam & 0x40000000))) {ZTK_MSG_Key(ZT_TRUE, iWParam & 0xff);} break;
		case WM_KEYUP: ZTK_MSG_Key(ZT_FALSE, iWParam & 0xff); break;
		case WM_CHAR: if (rZTK_Host.system.input.flag & ZTK_WINDOW_INPUT_CHAR) {ZTK_MSG_Char(iWParam & (~((ZT_CHAR)0x0)));} break;
		case WM_SYSKEYDOWN: if (!((rZTK_Host.system.events.pump & ZTK_HID_KEY) && (iLParam & 0x40000000))) {ZTK_MSG_Key(ZT_TRUE, iWParam & 0xff);} break;
		case WM_SYSKEYUP: ZTK_MSG_Key(ZT_FALSE, iWParam & 0xff); break;
		case WM_SYSCHAR: if (rZTK_Host.system.input.flag & ZTK_WINDOW_INPUT_CHAR) {ZTK_MSG_Char(iWParam & (~((ZT_CHAR)0x0)));} break;
		//case WM_ENTERSIZEMOVE: ZTX11_TimerSizing(); break;
		//case WM_EXITSIZEMOVE: ZTX11_TimerSizingStop(); break;
		//case WM_MOUSEACTIVATE: return ((iLParam & HTCLIENT) ? MA_ACTIVATEANDEAT : MA_ACTIVATE); // inhibit passing window activation click to event processing
		case WM_CLOSE: ZTX11_Quit(); lDefault = ZT_FALSE; break;
		default: break;
	}
	ZTK_Process();
	//ZTK_User();
	(*rZTK_Host.loop)();
	if (lPumped) {lPumped = ZT_FALSE; ++rZTX11_Host.pump.received;}
	if (lDefault) {return DefWindowProc(iHwnd, iMessage, iWParam, iLParam);} else {lDefault = ZT_TRUE; return 0x0;}
}
*/
#endif // ZTK_BUILD_X11
#endif // ZTX11_C_INCLUDED
