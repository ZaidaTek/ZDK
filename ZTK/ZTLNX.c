/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTLNX_C_INCLUDED
#define ZTLNX_C_INCLUDED

#include "ZTLNX-RT.h"

rZTLNX_HOST rZTLNX_Host;

/*
ZT_FLAG ZTLNX_Pump(void* iArg) {
    (void)iArg;
    while (!(rZTK_Host.system.state & ZTK_STATE_RUNNING)) {ZTL_Sleep(rZTK_Host.system.timer.resolution ? rZTK_Host.system.timer.resolution : 1);}
    while (!(rZTK_Host.system.state & ZTK_STATE_EXITING)) {
        if (rZTLNX_Host.pump.received == rZTLNX_Host.pump.sent) {
            SendMessageCallback(rZTLNX_Host.window.handle, ZTLNX_WM_PUMP, 0x0, 0x0, NULL, 0);
            ++rZTLNX_Host.pump.sent;
        }
        ZTL_Sleep(rZTK_Host.system.timer.resolution ? rZTK_Host.system.timer.resolution : 1);
    }
    return 0x0;
}
void ZTLNX_PumpExit(void) {ZTL_ThreadFree(rZTLNX_Host.pump.runtime);}
void ZTLNX_PumpInit(void) {rZTLNX_Host.pump.runtime = ZTL_ThreadNew(&ZTLNX_Pump, NULL);}
*/
void ZTLNX_RectLoad(void) {
	/*
    rZTLNX_Host.window.rect.right = (rZTLNX_Host.window.rect.left = rZTK_Host.rect.x) + (rZTLNX_Host.window.dimensions.right = rZTK_Host.rect.w);
    rZTLNX_Host.window.rect.bottom = (rZTLNX_Host.window.rect.top = rZTK_Host.rect.y) + (rZTLNX_Host.window.dimensions.bottom = rZTK_Host.rect.h);
    rZTLNX_Host.window.dimensions.top = (rZTLNX_Host.window.dimensions.left = 0);
	*/
}
void ZTLNX_RectApply(void) {
    /*
	RECT lRect = rZTLNX_Host.window.rect;
    AdjustWindowRectEx(&lRect, rZTLNX_Host.window.style, FALSE, 0);
    SetWindowPos(rZTLNX_Host.window.handle, NULL, lRect.left, lRect.top, lRect.right - lRect.left, lRect.bottom - lRect.top, SWP_NOCOPYBITS | SWP_NOZORDER);
    ZTLNX_DrawSize();
	*/
}
void ZTLNX_Open(void) {
    ZTLNX_RectApply();
    ShowWindow(rZTLNX_Host.window.handle, SW_SHOW);
}
void ZTLNX_FontFreeSources(void) {
    ZT_LIST* lList = rZTLNX_Host.window.fonts;
    for (ZT_INDEX i = 0; i < lList->length; i++) {
        RemoveFontResourceEx((LPCTSTR)lList->items[i], FR_PRIVATE, 0x0);
        ZTM8_Free(lList->items[i]);
        lList->items[i] = NULL;
    }
    ZTM_ListLength(lList, 0);
}
void ZTLNX_FontFreeSource(rZT_FONT* iFont) {
    (void)iFont;
}
void ZTLNX_FontLoadSource(rZT_FONT* iFont) {
    if (iFont->source != NULL) {
        ZT_LIST* lList = rZTLNX_Host.window.fonts;
        for (ZT_INDEX i = 0; i < lList->length; i++) {if (ZTC8_Match(lList->items[i], iFont->source)) {return;}}
        if (AddFontResourceEx((LPCTSTR)iFont->source, FR_PRIVATE, 0x0)) {ZTM_ListAppend(lList, ZTC8_Copy(iFont->source));}
    }
}
void ZTLNX_FontFreeRuntime(rZT_FONT* iFont) {
    DeleteObject((HFONT)iFont->runtime);
}
void ZTLNX_FontLoadRuntime(rZT_FONT* iFont) {
    //ZTLNX_FontFreeRuntime(iFont);
    LOGFONT lFontStyle;
    ZTM8_Zero(&lFontStyle, sizeof(LOGFONT));
    lFontStyle.lfHeight = iFont->height;
    lFontStyle.lfWeight = (iFont->style & ZTK_FONT_STYLE_BOLD) ? FW_BOLD : FW_NORMAL;
    lFontStyle.lfItalic = (iFont->style & ZTK_FONT_STYLE_ITALIC) ? 0x1 : 0x0;
    lFontStyle.lfUnderline = (iFont->style & ZTK_FONT_STYLE_UNDERLINE) ? 0x1 : 0x0;
    lFontStyle.lfStrikeOut = (iFont->style & ZTK_FONT_STYLE_STRIKEOUT) ? 0x1 : 0x0;
    lFontStyle.lfCharSet = ANSI_CHARSET;
    lFontStyle.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lFontStyle.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lFontStyle.lfQuality = NONANTIALIASED_QUALITY;
    lFontStyle.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
    ZTC8_CopyTargetLength(iFont->name, (ZT_CHAR*)lFontStyle.lfFaceName, LF_FACESIZE - 1); // does this copy NT if length exceeded?
    lFontStyle.lfFaceName[LF_FACESIZE - 1] = 0x0;
    iFont->runtime = CreateFontIndirect(&lFontStyle);
}
void ZTLNX_ResourceLoad(void) {
    //rZTLNX_Host.window.fonts = ZTM_ListNew(0);
    ZTLNX_DrawInit();
    ZTLNX_DrawSize();
    //ZTLNX_PumpInit();
}
void ZTLNX_ResourceFree(void) {
    //ZTLNX_PumpExit();
    ZTLNX_DrawExit();
    //ZTLNX_FontFreeSources();
    //ZTM_ListFree(rZTLNX_Host.window.fonts);
}
void ZTLNX_Register(void) {
    XSetWindowAttributes lWinAttr;
    lWinAttr.event_mask = SubstructureRedirectMask | SubstructureNotifyMask | StructureNotifyMask | ExposureMask;
    lWinAttr.do_not_propagate_mask = 0;
    lWinAttr.background_pixel = 0x0;
	rZTLNX_Host.window.id = XCreateWindow(
        rZTLNX_Host.display.handle, (rZTLNX_Host.window.root = XRootWindow(rZTLNX_Host.display.handle, rZTLNX_Host.display.screen)),
        rZTK_Host.rect.x, rZTK_Host.rect.y, rZTK_Host.rect.w, rZTK_Host.rect.h, 0, // x, y, w, h, border
        CopyFromParent, InputOutput, CopyFromParent, // depth, class, visual
        CWEventMask | NoEventMask | CWBackPixel, // .event_mask, .do_not_propagate_mask, .background_pixel
        &lWinAttr
    );
	XStoreName(rZTK_Host.user.title);
	/*
    WNDCLASSEX lW32Container;
    ZTM8_Zero(&lW32Container, sizeof(lW32Container));
    lW32Container.cbSize = sizeof(lW32Container);
    lW32Container.style = ZTLNX_DEFAULT_CLASS_STYLE;
    lW32Container.lpfnWndProc = &ZTLNX_CallbackInit;
    lW32Container.hInstance = rZTLNX_Host.instance;
    if ((rZTK_Host.user.icon != NULL) && ZTL_FileExists(rZTK_Host.user.icon)) {
        lW32Container.hIcon = (HICON)LoadImage(NULL, (LPCTSTR)rZTK_Host.user.icon, IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_LOADFROMFILE | LR_DEFAULTCOLOR);
    } else {
        lW32Container.hIcon = LoadIcon(rZTLNX_Host.instance, MAKEINTRESOURCE(ZTK_ICON_INTEGRATED));
    }
    lW32Container.hCursor = LoadCursor(NULL, IDC_ARROW);
    lW32Container.hbrBackground = (HBRUSH)COLOR_SCROLLBAR; // SCROLLBAR = BLACK
    lW32Container.lpszClassName = ZTLNX_DEFAULT_CLASS;
    lW32Container.hIconSm = (HICON)LoadImage(rZTLNX_Host.instance, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
    if (RegisterClassEx(&lW32Container)) {
        rZTLNX_Host.window.style = ZTLNX_DEFAULT_WINDOW_STYLE;
        RECT lRect = rZTLNX_Host.window.rect;
        AdjustWindowRectEx(&lRect, rZTLNX_Host.window.style, FALSE, 0);
        rZTLNX_Host.window.handle = CreateWindow(ZTLNX_DEFAULT_CLASS, (LPCTSTR)rZTK_Host.user.title, rZTLNX_Host.window.style, lRect.left, lRect.top, lRect.right - lRect.left, lRect.bottom - lRect.top, NULL, NULL, rZTLNX_Host.instance, NULL);
    }
	*/
}
void ZTLNX_Free(void) {
    ZTLNX_ResourceFree();
    //DestroyWindow(rZTLNX_Host.window.handle);
    XCloseDisplay(rZTLNX_Host.display);
    rZTLNX_Host.display = NULL;
}
void ZTLNX_New(void) {
    ZTM8_Zero(&rZTLNX_Host, sizeof(rZTLNX_Host));
    if ((rZTLNX_Host.display.handle = XOpenDisplay(NULL)) != NULL) {
		if ((rZTLNX_Host.display.screen = XDefaultScreen(rZTLNX_Host.display.handle)) != NULL) {
			ZTLNX_RectLoad();
			ZTLNX_Register();
			ZTLNX_ResourceLoad();
			//if (rZTLNX_Host.window.id != NULL) {ZTLNX_ResourceLoad();}
		}
	}
}
ZT_INDEX ZTLNX_Poll(void) {return PeekMessage(&(rZTLNX_Host.window.message), NULL, 0, 0, PM_REMOVE);}
ZT_INDEX ZTLNX_Process(void) {
    ZT_INDEX lMessages = 0;
    while (ZTLNX_Poll()) {
        ++lMessages;
        TranslateMessage(&(rZTLNX_Host.window.message));
        DispatchMessage(&(rZTLNX_Host.window.message));
    }
	return lMessages;
}
//void ZTLNX_KeyLoad(ZT_U8* oTarget) {
void ZTLNX_KeyLoad(ZT_U32* oTarget) {
    ZTM8_Zero(oTarget, ZTK_KEY_SIZE_LENGTH >> 3);
    for (ZT_INDEX i = 0x8; i < ZTK_KEY_SIZE_LENGTH; i++) { // offset to skip VK_MOUSE keys
        ZT_FLAG lMask = (0x1 << (i % ZTK_KEY_SIZE_UNIT));
        ZT_FLAG lIndex = (i >> ZTK_KEY_SIZE_SHIFT);
        oTarget[lIndex] |= ((GetAsyncKeyState(i) & 0x8000) ? lMask : 0x0);
    }
}
#define ZTLNX_MouseX(LPARAM) (LPARAM & 0xffff)
#define ZTLNX_MouseY(LPARAM) ((LPARAM >> 16))
#define ZTLNX_MouseWheel(WPARAM) ((ZT_I16)(WPARAM >> 16))
#define ZTLNX_MouseXButton(WPARAM) (((WPARAM >> 16) & XBUTTON2) ? ZTK_SID_MOUSE_X2BUTTON : ZTK_SID_MOUSE_X1BUTTON)
#define ZTLNX_MouseState(WPARAM) ({\
    ZT_FLAG rHOSTMOUSESTATE_s = (iWParam & MK_LBUTTON) ? ZTK_SID_MOUSE_LBUTTON : ZTK_SID_NONE;\
    if (iWParam & MK_RBUTTON) {lState |= ZTK_SID_MOUSE_RBUTTON;}\
    if (iWParam & MK_MBUTTON) {lState |= ZTK_SID_MOUSE_MBUTTON;}\
    if (iWParam & MK_XBUTTON1) {lState |= ZTK_SID_MOUSE_X1BUTTON;}\
    if (iWParam & MK_XBUTTON2) {lState |= ZTK_SID_MOUSE_X2BUTTON;}\
    rHOSTMOUSESTATE_s;\
})
void ZTLNX_Command(ZT_FLAG iWParam) {
    switch (iWParam) {
        case SC_MINIMIZE: ZTK_MSG_Minimize(ZT_TRUE); break;
        case SC_RESTORE: ZTK_MSG_Minimize(ZT_FALSE); break;
        case SC_MAXIMIZE: ZTK_MSG_Minimize(ZT_FALSE); break;
        default: break;
    }
}
void ZTLNX_Loop(void) {SendMessageCallback(rZTLNX_Host.window.handle, ZTLNX_WM_USER, 0x0, 0x0, NULL, 0);}
void ZTLNX_ModeMain(void) {SetWindowLongPtr(rZTLNX_Host.window.handle, GWL_WNDPROC, (LONG_PTR)&ZTLNX_CallbackMain);}
void ZTLNX_ModeExit(void) {SetWindowLongPtr(rZTLNX_Host.window.handle, GWL_WNDPROC, (LONG_PTR)&ZTLNX_CallbackExit);}
void ZTLNX_Quit(void) {ZTK_MSG_Close(); ZTLNX_ModeExit();}
LRESULT CALLBACK ZTLNX_CallbackInit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
    //ZTLNX_PrintMessage(iMessage);
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
        case ZTLNX_WM_USER: ZTK_MSG_User(); ZTLNX_ModeMain(); break;
        default: break;
    }
    ZTK_Process();
    return DefWindowProc(iHwnd, iMessage, iWParam, iLParam);
}
LRESULT CALLBACK ZTLNX_CallbackExit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
    //ZTLNX_PrintMessage(iMessage);
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
LRESULT CALLBACK ZTLNX_CallbackMain(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
    //ZTLNX_PrintMessage(iMessage);
    static ZT_BOOL lPumped = ZT_FALSE;
    static ZT_BOOL lDefault = ZT_TRUE;
    switch (iMessage) {
        case ZTLNX_WM_USER: break;
        case ZTLNX_WM_PUMP: lPumped = ZT_TRUE; break;
        case WM_SIZE: ZTK_MSG_Size((ZT_I)LOWORD(iLParam), (ZT_I)HIWORD(iLParam)); break;
        case WM_MOVE: ZTK_MSG_Move((ZT_I)LOWORD(iLParam), (ZT_I)HIWORD(iLParam)); break;
        case WM_KILLFOCUS: ZTK_MSG_KeyFocus(ZT_FALSE); break;
        case WM_SETFOCUS: ZTK_MSG_KeyFocus(ZT_TRUE); break;
        case WM_ACTIVATE: ZTK_MSG_Activate(iWParam & 0x1); break;
        case WM_SHOWWINDOW: ZTK_MSG_Show(iWParam ? ZT_TRUE : ZT_FALSE); break;
        case WM_SYSCOMMAND: ZTLNX_Command(iWParam); break;
        case WM_MOUSEMOVE: ZTK_MSG_MouseMove(ZTLNX_MouseX(iLParam), ZTLNX_MouseY(iLParam)); break;
        case WM_LBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_LBUTTON, ZT_TRUE); break;
        case WM_RBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_RBUTTON, ZT_TRUE); break;
        case WM_MBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_MBUTTON, ZT_TRUE); break;
        case WM_LBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_LBUTTON, ZT_FALSE); break;
        case WM_RBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_RBUTTON, ZT_FALSE); break;
        case WM_MBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_MBUTTON, ZT_FALSE); break;
        case WM_XBUTTONUP: ZTK_MSG_MouseButton(ZTLNX_MouseXButton(iWParam), ZT_FALSE); break;
        case WM_XBUTTONDOWN: ZTK_MSG_MouseButton(ZTLNX_MouseXButton(iWParam), ZT_TRUE); break;
        case WM_MOUSEWHEEL: ZTK_MSG_MouseWheel(ZTLNX_MouseWheel(iWParam)); break;
        case WM_KEYDOWN: if (!((rZTK_Host.system.events.pump & ZTK_HID_KEY) && (iLParam & 0x40000000))) {ZTK_MSG_Key(ZT_TRUE, iWParam & 0xff);} break;
        case WM_KEYUP: ZTK_MSG_Key(ZT_FALSE, iWParam & 0xff); break;
        case WM_CHAR: if (rZTK_Host.system.input.flag & ZTK_WINDOW_INPUT_CHAR) {ZTK_MSG_Char(iWParam & (~((ZT_CHAR)0x0)));} break;
        case WM_SYSKEYDOWN: if (!((rZTK_Host.system.events.pump & ZTK_HID_KEY) && (iLParam & 0x40000000))) {ZTK_MSG_Key(ZT_TRUE, iWParam & 0xff);} break;
        case WM_SYSKEYUP: ZTK_MSG_Key(ZT_FALSE, iWParam & 0xff); break;
        case WM_SYSCHAR: if (rZTK_Host.system.input.flag & ZTK_WINDOW_INPUT_CHAR) {ZTK_MSG_Char(iWParam & (~((ZT_CHAR)0x0)));} break;
        //case WM_ENTERSIZEMOVE: ZTLNX_TimerSizing(); break;
        //case WM_EXITSIZEMOVE: ZTLNX_TimerSizingStop(); break;
        //case WM_MOUSEACTIVATE: return ((iLParam & HTCLIENT) ? MA_ACTIVATEANDEAT : MA_ACTIVATE); // inhibit passing window activation click to event processing
        case WM_CLOSE: ZTLNX_Quit(); lDefault = ZT_FALSE; break;
        default: break;
    }
    ZTK_Process();
    //ZTK_User();
    (*rZTK_Host.loop)();
    if (lPumped) {lPumped = ZT_FALSE; ++rZTLNX_Host.pump.received;}
    if (lDefault) {return DefWindowProc(iHwnd, iMessage, iWParam, iLParam);} else {lDefault = ZT_TRUE; return 0x0;}
}

#endif // ZTLNX_C_INCLUDED
