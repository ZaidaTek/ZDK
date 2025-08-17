/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_C_INCLUDED
#define ZTW32_C_INCLUDED

#include "ZTW32__Runtime.h"

ZT_FLAG ZTW32_Pump(void* iArg) {
    (void)iArg;
    while (!(rZTK_Host.system.state & ZTK_STATE_RUNNING)) {ZTL_Sleep(rZTK_Host.system.timer.resolution ? rZTK_Host.system.timer.resolution : 1);}
    while (!(rZTK_Host.system.state & ZTK_STATE_EXITING)) {
        if (rZTW32_Host.pump.received == rZTW32_Host.pump.sent) {
            SendMessageCallback(rZTW32_Host.window.handle, ZTW32_WM_PUMP, 0x0, 0x0, NULL, 0);
            ++rZTW32_Host.pump.sent;
        }
        ZTL_Sleep(rZTK_Host.system.timer.resolution ? rZTK_Host.system.timer.resolution : 1);
    }
    return 0x0;
}
void ZTW32_PumpExit(void) {ZTL_ThreadFree(rZTW32_Host.pump.runtime);}
void ZTW32_PumpInit(void) {rZTW32_Host.pump.runtime = ZTL_ThreadNew(&ZTW32_Pump, NULL);}
void ZTW32_RectApply(void) {
    RECT lRect = rZTW32_Host.window.rect;
    AdjustWindowRectEx(&lRect, rZTW32_Host.window.style, FALSE, 0);
    SetWindowPos(rZTW32_Host.window.handle, NULL, lRect.left, lRect.top, lRect.right - lRect.left, lRect.bottom - lRect.top, SWP_NOCOPYBITS | SWP_NOZORDER);
    ZTW32_DrawSize();
}
void ZTW32_Register(void) {
    WNDCLASSEX lW32Container;
    ZTM8_Zero(&lW32Container, sizeof(lW32Container));
    lW32Container.cbSize = sizeof(lW32Container);
    lW32Container.style = ZTW32_DEFAULT_CLASS_STYLE;
    lW32Container.lpfnWndProc = &ZTW32_CallbackInit;
    lW32Container.hInstance = rZTW32_Host.instance;
    if ((rZTK_Host.user.icon != NULL) && ZTL_FileExists(rZTK_Host.user.icon)) {
        lW32Container.hIcon = (HICON)LoadImage(NULL, (LPCTSTR)rZTK_Host.user.icon, IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_LOADFROMFILE | LR_DEFAULTCOLOR);
    } else {
        lW32Container.hIcon = LoadIcon(rZTW32_Host.instance, MAKEINTRESOURCE(ZTK_ICON_INTEGRATED));
    }
    lW32Container.hCursor = LoadCursor(NULL, IDC_ARROW);
    lW32Container.hbrBackground = (HBRUSH)COLOR_SCROLLBAR; // SCROLLBAR = BLACK
    lW32Container.lpszClassName = ZTW32_DEFAULT_CLASS;
    lW32Container.hIconSm = (HICON)LoadImage(rZTW32_Host.instance, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
    if (RegisterClassEx(&lW32Container)) {
        rZTW32_Host.window.style = ZTW32_DEFAULT_WINDOW_STYLE;
        RECT lRect = rZTW32_Host.window.rect;
        AdjustWindowRectEx(&lRect, rZTW32_Host.window.style, FALSE, 0);
        rZTW32_Host.window.handle = CreateWindow(ZTW32_DEFAULT_CLASS, (LPCTSTR)rZTK_Host.user.title, rZTW32_Host.window.style, lRect.left, lRect.top, lRect.right - lRect.left, lRect.bottom - lRect.top, NULL, NULL, rZTW32_Host.instance, NULL);
    }
}
void ZTW32_Open(void) {
    ZTW32_RectApply();
    ShowWindow(rZTW32_Host.window.handle, SW_SHOW);
}
void ZTW32_FontFreeSources(void) {
    ZT_LIST* lList = rZTW32_Host.window.fonts;
    for (ZT_INDEX i = 0; i < lList->length; i++) {
        RemoveFontResourceEx((LPCTSTR)lList->items[i], FR_PRIVATE, 0x0);
        ZTM8_Free(lList->items[i]);
        lList->items[i] = NULL;
    }
    ZTM_ListLength(lList, 0);
}
void ZTW32_FontFreeSource(rZT_FONT* iFont) {
    (void)iFont;
}
void ZTW32_FontLoadSource(rZT_FONT* iFont) {
    if (iFont->source != NULL) {
        ZT_LIST* lList = rZTW32_Host.window.fonts;
        for (ZT_INDEX i = 0; i < lList->length; i++) {if (ZTC8_Match(lList->items[i], iFont->source)) {return;}}
        if (AddFontResourceEx((LPCTSTR)iFont->source, FR_PRIVATE, 0x0)) {ZTM_ListAppend(lList, ZTC8_Copy(iFont->source));}
    }
}
void ZTW32_FontFreeRuntime(rZT_FONT* iFont) {
    DeleteObject((HFONT)iFont->runtime);
}
void ZTW32_FontLoadRuntime(rZT_FONT* iFont) {
    //ZTW32_FontFreeRuntime(iFont);
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
void ZTW32_ResourceLoad(void) {
    rZTW32_Host.window.fonts = ZTM_ListNew(0);
    ZTW32_DrawInit();
    ZTW32_DrawSize();
    ZTW32_PumpInit();
}
void ZTW32_ResourceFree(void) {
    ZTW32_PumpExit();
    ZTW32_DrawExit();
    ZTW32_FontFreeSources();
    ZTM_ListFree(rZTW32_Host.window.fonts);
}
void ZTW32_Free(void) {
    ZTW32_ResourceFree();
    DestroyWindow(rZTW32_Host.window.handle);
    rZTW32_Host.instance = NULL;
}
void ZTW32_New(void) {
    ZTM8_Zero(&rZTW32_Host, sizeof(rZTW32_Host));
    rZTW32_Host.instance = GetModuleHandle(NULL);
    ZTW32_RectLoad();
    ZTW32_Register();
    if (rZTW32_Host.window.handle != NULL) {ZTW32_ResourceLoad();}
}
ZT_INDEX ZTW32_Poll(void) {return PeekMessage(&(rZTW32_Host.window.message), NULL, 0, 0, PM_REMOVE);}
ZT_INDEX ZTW32_Process(void) {
    ZT_INDEX lMessages = 0;
    while (ZTW32_Poll()) {
        ++lMessages;
        TranslateMessage(&(rZTW32_Host.window.message));
        DispatchMessage(&(rZTW32_Host.window.message));
    }
	return lMessages;
}
//void ZTW32_KeyLoad(ZT_U8* oTarget) {
void ZTW32_KeyLoad(ZT_U32* oTarget) {
    ZTM8_Zero(oTarget, ZTK_KEY_SIZE_LENGTH >> 3);
    for (ZT_INDEX i = 0x8; i < ZTK_KEY_SIZE_LENGTH; i++) { // offset to skip VK_MOUSE keys
        ZT_FLAG lMask = (0x1 << (i % ZTK_KEY_SIZE_UNIT));
        ZT_FLAG lIndex = (i >> ZTK_KEY_SIZE_SHIFT);
        oTarget[lIndex] |= ((GetAsyncKeyState(i) & 0x8000) ? lMask : 0x0);
    }
}
void ZTW32_RectLoad(void) {
    rZTW32_Host.window.rect.right = (rZTW32_Host.window.rect.left = rZTK_Host.rect.x) + (rZTW32_Host.window.dimensions.right = rZTK_Host.rect.w);
    rZTW32_Host.window.rect.bottom = (rZTW32_Host.window.rect.top = rZTK_Host.rect.y) + (rZTW32_Host.window.dimensions.bottom = rZTK_Host.rect.h);
    rZTW32_Host.window.dimensions.top = (rZTW32_Host.window.dimensions.left = 0);
}
#define ZTW32_MouseX(LPARAM) (LPARAM & 0xffff)
#define ZTW32_MouseY(LPARAM) ((LPARAM >> 16))
#define ZTW32_MouseWheel(WPARAM) ((ZT_I16)(WPARAM >> 16))
#define ZTW32_MouseXButton(WPARAM) (((WPARAM >> 16) & XBUTTON2) ? ZTK_SID_MOUSE_X2BUTTON : ZTK_SID_MOUSE_X1BUTTON)
#define ZTW32_MouseState(WPARAM) ({\
    ZT_FLAG rHOSTMOUSESTATE_s = (iWParam & MK_LBUTTON) ? ZTK_SID_MOUSE_LBUTTON : ZTK_SID_NONE;\
    if (iWParam & MK_RBUTTON) {lState |= ZTK_SID_MOUSE_RBUTTON;}\
    if (iWParam & MK_MBUTTON) {lState |= ZTK_SID_MOUSE_MBUTTON;}\
    if (iWParam & MK_XBUTTON1) {lState |= ZTK_SID_MOUSE_X1BUTTON;}\
    if (iWParam & MK_XBUTTON2) {lState |= ZTK_SID_MOUSE_X2BUTTON;}\
    rHOSTMOUSESTATE_s;\
})
void ZTW32_Command(ZT_FLAG iWParam) {
    switch (iWParam) {
        case SC_MINIMIZE: ZTK_MSG_Minimize(ZT_TRUE); break;
        case SC_RESTORE: ZTK_MSG_Minimize(ZT_FALSE); break;
        case SC_MAXIMIZE: ZTK_MSG_Minimize(ZT_FALSE); break;
        default: break;
    }
}
void ZTW32_Loop(void) {SendMessageCallback(rZTW32_Host.window.handle, ZTW32_WM_USER, 0x0, 0x0, NULL, 0);}
void ZTW32_ModeMain(void) {SetWindowLongPtr(rZTW32_Host.window.handle, GWL_WNDPROC, (LONG_PTR)&ZTW32_CallbackMain);}
void ZTW32_ModeExit(void) {SetWindowLongPtr(rZTW32_Host.window.handle, GWL_WNDPROC, (LONG_PTR)&ZTW32_CallbackExit);}
void ZTW32_Quit(void) {ZTK_MSG_Close(); ZTW32_ModeExit();}
LRESULT CALLBACK ZTW32_CallbackInit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
    //ZTW32_PrintMessage(iMessage);
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
        case ZTW32_WM_USER: ZTK_MSG_User(); ZTW32_ModeMain(); break;
        default: break;
    }
    ZTK_Process();
    return DefWindowProc(iHwnd, iMessage, iWParam, iLParam);
}
LRESULT CALLBACK ZTW32_CallbackExit(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
    //ZTW32_PrintMessage(iMessage);
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
LRESULT CALLBACK ZTW32_CallbackMain(HWND iHwnd, UINT iMessage, WPARAM iWParam, LPARAM iLParam) {
    //ZTW32_PrintMessage(iMessage);
    static ZT_BOOL lPumped = ZT_FALSE;
    static ZT_BOOL lDefault = ZT_TRUE;
    switch (iMessage) {
        case ZTW32_WM_USER: break;
        case ZTW32_WM_PUMP: lPumped = ZT_TRUE; break;
        case WM_SIZE: ZTK_MSG_Size((ZT_I)LOWORD(iLParam), (ZT_I)HIWORD(iLParam)); break;
        case WM_MOVE: ZTK_MSG_Move((ZT_I)LOWORD(iLParam), (ZT_I)HIWORD(iLParam)); break;
        case WM_KILLFOCUS: ZTK_MSG_KeyFocus(ZT_FALSE); break;
        case WM_SETFOCUS: ZTK_MSG_KeyFocus(ZT_TRUE); break;
        case WM_ACTIVATE: ZTK_MSG_Activate(iWParam & 0x1); break;
        case WM_SHOWWINDOW: ZTK_MSG_Show(iWParam ? ZT_TRUE : ZT_FALSE); break;
        case WM_SYSCOMMAND: ZTW32_Command(iWParam); break;
        case WM_MOUSEMOVE: ZTK_MSG_MouseMove(ZTW32_MouseX(iLParam), ZTW32_MouseY(iLParam)); break;
        case WM_LBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_LBUTTON, ZT_TRUE); break;
        case WM_RBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_RBUTTON, ZT_TRUE); break;
        case WM_MBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_MBUTTON, ZT_TRUE); break;
        case WM_LBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_LBUTTON, ZT_FALSE); break;
        case WM_RBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_RBUTTON, ZT_FALSE); break;
        case WM_MBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_MBUTTON, ZT_FALSE); break;
        case WM_XBUTTONUP: ZTK_MSG_MouseButton(ZTW32_MouseXButton(iWParam), ZT_FALSE); break;
        case WM_XBUTTONDOWN: ZTK_MSG_MouseButton(ZTW32_MouseXButton(iWParam), ZT_TRUE); break;
        case WM_MOUSEWHEEL: ZTK_MSG_MouseWheel(ZTW32_MouseWheel(iWParam)); break;
        case WM_KEYDOWN: if (!((rZTK_Host.system.events.pump & ZTK_HID_KEY) && (iLParam & 0x40000000))) {ZTK_MSG_Key(ZT_TRUE, iWParam & 0xff);} break;
        case WM_KEYUP: ZTK_MSG_Key(ZT_FALSE, iWParam & 0xff); break;
        case WM_CHAR: if (rZTK_Host.system.input.flag & ZTK_WINDOW_INPUT_CHAR) {ZTK_MSG_Char(iWParam & (~((ZT_CHAR)0x0)));} break;
        case WM_SYSKEYDOWN: if (!((rZTK_Host.system.events.pump & ZTK_HID_KEY) && (iLParam & 0x40000000))) {ZTK_MSG_Key(ZT_TRUE, iWParam & 0xff);} break;
        case WM_SYSKEYUP: ZTK_MSG_Key(ZT_FALSE, iWParam & 0xff); break;
        case WM_SYSCHAR: if (rZTK_Host.system.input.flag & ZTK_WINDOW_INPUT_CHAR) {ZTK_MSG_Char(iWParam & (~((ZT_CHAR)0x0)));} break;
        //case WM_ENTERSIZEMOVE: ZTW32_TimerSizing(); break;
        //case WM_EXITSIZEMOVE: ZTW32_TimerSizingStop(); break;
        //case WM_MOUSEACTIVATE: return ((iLParam & HTCLIENT) ? MA_ACTIVATEANDEAT : MA_ACTIVATE); // inhibit passing window activation click to event processing
        case WM_CLOSE: ZTW32_Quit(); lDefault = ZT_FALSE; break;
        default: break;
    }
    ZTK_Process();
    //ZTK_User();
    (*rZTK_Host.loop)();
    if (lPumped) {lPumped = ZT_FALSE; ++rZTW32_Host.pump.received;}
    if (lDefault) {return DefWindowProc(iHwnd, iMessage, iWParam, iLParam);} else {lDefault = ZT_TRUE; return 0x0;}
}

#endif // ZTW32_C_INCLUDED
