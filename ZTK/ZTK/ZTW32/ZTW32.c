/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_C_INCLUDED
#define ZTW32_C_INCLUDED

#include "ZTW32/ZTW32__Runtime.h"

ZTW32_RUNTIME* gZTW32_RTime = NULL;

// PUBLIC FUNCTIONS
#ifndef ZTW32_MACRO
ZT_TIME ZTW32_Ticks(void) {return (ZT_TIME)timeGetTime();}
ZT_I ZTW32_ScreenWidth(void) {return GetSystemMetrics(SM_CXFULLSCREEN);}
ZT_I ZTW32_ScreenHeight(void) {return GetSystemMetrics(SM_CYFULLSCREEN);}
#endif // ZTW32_MACRO
void ZTW32_RectApply(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL) {
            RECT tempRect = gZTW32_RTime->window.rect;
            AdjustWindowRectEx(&tempRect, gZTW32_RTime->window.style, FALSE, 0);
            SetWindowPos(gZTW32_RTime->window.handle, NULL, tempRect.left, tempRect.top, tempRect.right - tempRect.left, tempRect.bottom - tempRect.top, SWP_NOCOPYBITS | SWP_NOZORDER);
			ZTW32_DrawReset();
        }
	}
}
void ZTW32_WindowDestroy(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL) {
            ZTW32_HostFreeResources();
			DestroyWindow(gZTW32_RTime->window.handle);
			gZTW32_RTime->window.handle = NULL;
		}
	}
}
void ZTW32_HostRegister(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->instance != NULL && !(gZTW32_RTime->window.handle != NULL)) {
            WNDCLASSEX lW32Container;
            ZTM8_Zero(&lW32Container, sizeof(lW32Container));
            lW32Container.cbSize = sizeof(lW32Container);
            lW32Container.style = ZTW32_DEFAULT_CLASS_STYLE;
            lW32Container.lpfnWndProc = &ZTW32_HostCallback;
            lW32Container.hInstance = gZTW32_RTime->instance;
            if ((gZTW32_RTime->owner->user.icon == NULL) || (gZTW32_RTime->owner->user.icon[0] == 0x0) || (GetFileAttributes((const char*)gZTW32_RTime->owner->user.icon) == INVALID_FILE_ATTRIBUTES)) {
                lW32Container.hIcon = LoadIcon(gZTW32_RTime->instance, MAKEINTRESOURCE(ZTK_DEFAULT_WINDOW_ICON_INTEGRATED_ID));
            } else {
                lW32Container.hIcon = (HICON)LoadImage(NULL, (const char*)gZTW32_RTime->owner->user.icon, IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_LOADFROMFILE | LR_DEFAULTCOLOR);
            }
            lW32Container.hCursor = LoadCursor(NULL, IDC_ARROW);
            lW32Container.hbrBackground = (HBRUSH)COLOR_SCROLLBAR; // SCROLLBAR = BLACK
            lW32Container.lpszClassName = ZTW32_DEFAULT_CLASS;
            lW32Container.hIconSm = (HICON)LoadImage(gZTW32_RTime->instance, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
            if (RegisterClassEx(&lW32Container)) {
                gZTW32_RTime->window.style = ZTW32_DEFAULT_WINDOW_STYLE;
                RECT lRect = gZTW32_RTime->window.rect;
                AdjustWindowRectEx(&lRect, gZTW32_RTime->window.style, FALSE, 0);
                gZTW32_RTime->window.handle = CreateWindow(ZTW32_DEFAULT_CLASS, (const char*)gZTW32_RTime->owner->user.title, gZTW32_RTime->window.style, lRect.left, lRect.top, lRect.right - lRect.left, lRect.bottom - lRect.top, NULL, NULL, gZTW32_RTime->instance, NULL);
            }
		}
    }
}
void ZTW32_WindowOpen(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->instance != NULL) {
            if (gZTW32_RTime->window.handle != NULL) {
                ZTW32_RectApply();
                ShowWindow(gZTW32_RTime->window.handle, SW_SHOW);
            }
		}
	}
}
void ZTW32_Free(void) {
	if (gZTW32_RTime != NULL) {
		ZTW32_WindowDestroy();
		gZTW32_RTime->instance = NULL;
		gZTW32_RTime->owner->system.runtime = NULL;
		ZTM8_Free(gZTW32_RTime);
		gZTW32_RTime = NULL;
	}
}
void ZTW32_New(ZT_WINDOW* iWindow) {
	if (iWindow != NULL && !(gZTW32_RTime != NULL)) {
		if ((iWindow->system.type & ZTK_WINDOW_TYPE_WIN32) && !(iWindow->system.runtime != NULL)) {
			if ((gZTW32_RTime = (ZTW32_RUNTIME*)ZTM8_Init(sizeof(ZTW32_RUNTIME), 0x0)) != NULL) {
				gZTW32_RTime->owner = iWindow;
				iWindow->system.runtime = gZTW32_RTime;
				gZTW32_RTime->instance = GetModuleHandle(NULL);
                ZTW32_RectReload();
                ZTW32_HostRegister();
                if (gZTW32_RTime->window.handle != NULL) {
                    ZTW32_HostLoadResources();
                }
			}
		}
	}
}
void ZTW32_HostProcess(void) {
	if (gZTW32_RTime != NULL) {
        while (ZTW32_HostPoll()) {
            TranslateMessage(&(gZTW32_RTime->window.message));
            ZTW32_HostMain(gZTW32_RTime->window.handle, gZTW32_RTime->window.message.message, gZTW32_RTime->window.message.wParam, gZTW32_RTime->window.message.lParam);
        }
	}
}
void ZTW32_HostLoadKey(ZT_U8* oTarget) {
	if (oTarget != NULL) {
        ZTM8_Zero(oTarget, ZTK_KEY_SIZE_LENGTH >> 3);
        for (ZT_INDEX i = 0x8; i < ZTK_KEY_SIZE_LENGTH; i++) { // offset to skip VK_MOUSE keys
            ZT_FLAG lMask = (0x1 << (i % ZTK_KEY_SIZE_UNIT));
            ZT_FLAG lIndex = (i >> ZTK_KEY_SIZE_SHIFT);
            oTarget[lIndex] |= ((GetAsyncKeyState(i) & 0x8000) ? lMask : 0x0);
        }
	}
}

// INTERNAL-ONLY FUNCTIONS
void ZTW32_HostFreeFontSources(void) {
    if (gZTW32_RTime != NULL) {
        ZT_LIST* lList = gZTW32_RTime->window.fontsLoaded;
        for (ZT_INDEX i = 0; i < lList->length; i++) {
            RemoveFontResourceEx((const char*)lList->items[i], FR_PRIVATE, 0x0);
            ZTM8_Free(lList->items[i]);
            lList->items[i] = NULL;
        }
        ZTM_ListLength(lList, 0);
    }
}
void ZTW32_HostFreeFontRuntime(ZT_FONT* iFont) {
    if (gZTW32_RTime != NULL && iFont != NULL) {
        if (iFont->runtime != NULL) {
            DeleteObject((HFONT)iFont->runtime);
            iFont->runtime = NULL;
        }
    }
}
void ZTW32_HostFreeFont(ZT_FONT* iFont) {//if (gZTW32_RTime != NULL && iFont != NULL)
    // are both also checked by:
    {ZTW32_HostFreeFontRuntime(iFont);}
}
ZT_BOOL ZTW32_HostLoadFontSourceSkip(ZT_CHAR* iSource) {
    ZT_BOOL lSkip = (iSource != NULL) ? ZT_FALSE : ZT_TRUE;
    if (gZTW32_RTime != NULL && !lSkip) {
        ZT_LIST* lList = gZTW32_RTime->window.fontsLoaded;
        for (ZT_INDEX i = 0; i < lList->length; i++) {
            if (ZTC8_Match(lList->items[i], iSource)) {lSkip = ZT_TRUE; break;}
        }
    }
    return lSkip;
}
void ZTW32_HostLoadFontSource(ZT_FONT* iFont) {
    if (gZTW32_RTime != NULL && iFont != NULL) {
        if (!(ZTW32_HostLoadFontSourceSkip(iFont->source))) {
            if (AddFontResourceEx((const char*)iFont->source, FR_PRIVATE, 0x0)) {ZTM_ListAppend(gZTW32_RTime->window.fontsLoaded, ZTC8_Copy(iFont->source));}
        }
        iFont->flag |= ZTM_FONT_FLAG_SOURCE_LOADED;
    }
}
void ZTW32_HostLoadFontRuntime(ZT_FONT* iFont) {
    if (gZTW32_RTime != NULL && iFont != NULL) {
        if (iFont->flag & ZTM_FONT_FLAG_SOURCE_LOADED) {
            ZTW32_HostFreeFontRuntime(iFont);
            LOGFONT lFontStyle;
            ZTM8_Zero(&lFontStyle, sizeof(LOGFONT));
            lFontStyle.lfHeight = iFont->height;
            lFontStyle.lfWeight = (iFont->style & ZTM_FONT_STYLE_BOLD) ? FW_BOLD : FW_NORMAL;
            lFontStyle.lfItalic = (iFont->style & ZTM_FONT_STYLE_ITALIC) ? 0x1 : 0x0;
            lFontStyle.lfUnderline = (iFont->style & ZTM_FONT_STYLE_UNDERLINE) ? 0x1 : 0x0;
            lFontStyle.lfStrikeOut = (iFont->style & ZTM_FONT_STYLE_STRIKEOUT) ? 0x1 : 0x0;
            lFontStyle.lfCharSet = ANSI_CHARSET;
            lFontStyle.lfOutPrecision = OUT_DEFAULT_PRECIS;
            lFontStyle.lfClipPrecision = CLIP_DEFAULT_PRECIS;
            lFontStyle.lfQuality = NONANTIALIASED_QUALITY;
            lFontStyle.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
            ZTC8_CopyTarget(iFont->name, (ZT_CHAR*)&(lFontStyle.lfFaceName[0]));
            iFont->runtime = CreateFontIndirect(&lFontStyle);
        }
    }
}
void ZTW32_HostLoadFont(ZT_FONT* iFont) {
    if (gZTW32_RTime != NULL && iFont != NULL) {
        ZTW32_HostLoadFontSource(iFont);
        ZTW32_HostLoadFontRuntime(iFont);
        iFont->flag &= ~ZTM_FONT_FLAG_RELOAD;
    }
}
void ZTW32_HostLoadResources(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL) {
            gZTW32_RTime->window.fontsLoaded = ZTM_ListNew(0);
            ZTW32_DrawLoad();
            ZTW32_TimerResolution();
            ZTW32_TimerHeartbeat();
		}
    }
}
void ZTW32_HostFreeResources(void) {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL) {
			ZTW32_TimerFree();
			ZTW32_TimerResolutionReset();
			ZTW32_DrawFree();
			ZTW32_HostFreeFontSources();
			ZTM_ListFree(gZTW32_RTime->window.fontsLoaded);
		}
	}
}
void ZTW32_RectReload(void) {
	if (gZTW32_RTime != NULL) {
        ZTW32_HostRect(&(gZTW32_RTime->window.rect), &(gZTW32_RTime->owner->rect));
		ZTW32_HostRectFromIntegers(&(gZTW32_RTime->window.dimensions), 0, 0, gZTW32_RTime->owner->rect.w, gZTW32_RTime->owner->rect.h);
	}
}
void ZTW32_HostRect(RECT* oRect, const ZT_RECT* iRect) {
    if (oRect != NULL && iRect != NULL) {
		oRect->left = iRect->x;
		oRect->top = iRect->y;
		oRect->right = iRect->x + iRect->w;
		oRect->bottom = iRect->y + iRect->h;
    }
}
void ZTW32_HostRectFromIntegers(RECT* oRect, ZT_I iX, ZT_I iY, ZT_I iWidth, ZT_I iHeight) {
    if (oRect != NULL) {
		oRect->left = iX;
		oRect->top = iY;
		oRect->right = iX + iWidth;
		oRect->bottom = iY + iHeight;
    }
}
#define ZTW32_HostMouseX(LPARAM) (LPARAM & 0xffff)
#define ZTW32_HostMouseY(LPARAM) ((LPARAM >> 16))
#define ZTW32_HostMouseWheel(WPARAM) ((ZT_I16)(WPARAM >> 16))
#define ZTW32_HostMouseXButton(WPARAM) (((WPARAM >> 16) & XBUTTON2) ? ZTK_SID_MOUSE_X2BUTTON : ZTK_SID_MOUSE_X1BUTTON)
#define ZTW32_HostMouseState(WPARAM) ({\
    ZT_FLAG rHOSTMOUSESTATE_s = (iWParam & MK_LBUTTON) ? ZTK_SID_MOUSE_LBUTTON : ZTK_SID_NONE;\
    if (iWParam & MK_RBUTTON) {lState |= ZTK_SID_MOUSE_RBUTTON;}\
    if (iWParam & MK_MBUTTON) {lState |= ZTK_SID_MOUSE_MBUTTON;}\
    if (iWParam & MK_XBUTTON1) {lState |= ZTK_SID_MOUSE_X1BUTTON;}\
    if (iWParam & MK_XBUTTON2) {lState |= ZTK_SID_MOUSE_X2BUTTON;}\
    rHOSTMOUSESTATE_s;\
})
#define ZTW32_HostPosClientFromScreen(LPARAM) ({\
    ZT_I rHOSTPCFS_x = ZTW32_HostMouseX(LPARAM);\
    ZT_I rHOSTPCFS_y = ZTW32_HostMouseY(LPARAM);\
    if (gZTW32_RTime != NULL) {; ;}\
    ((((ZT_I16)((ZT_I)ZTW32_HostMouseY(LPARAM) - gZTW32_RTime->window.rect.top) << 16) | ((ZT_I16)((ZT_I)ZTW32_HostMouseX(LPARAM) - gZTW32_RTime->window.rect.left)));\
})
void ZTW32_HostWait(void) {if (gZTW32_RTime != NULL) {WaitMessage();}}
ZT_INDEX ZTW32_HostMessages(void) {if (gZTW32_RTime != NULL) {return (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, PM_NOREMOVE));} return 0;}
void ZTW32_HostLoop(void) {
	if (gZTW32_RTime != NULL) {
        if (gZTW32_RTime->window.handle != NULL) {
            SendMessageCallback(gZTW32_RTime->window.handle, ZTW32_WM_USER, 0x0, 0x0, NULL, 0);
        }
	}
}
ZT_BOOL ZTW32_HostPoll(void) {
	if (gZTW32_RTime != NULL) {
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_TIMER << 16) | PM_REMOVE) > 0) {return ZT_TRUE;}
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_MOUSEMOVE << 16) | PM_REMOVE) > 0) {return ZT_TRUE;}
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_MOUSEBUTTON << 16) | PM_REMOVE) > 0) {return ZT_TRUE;}
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_MOUSE << 16) | PM_REMOVE) > 0) {return ZT_TRUE;}
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_INPUT << 16) | PM_REMOVE) > 0) {return ZT_TRUE;}
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, PM_REMOVE) > 0) {return ZT_TRUE;}
	}
	return ZT_FALSE;
}
void ZTW32_HostCommand(ZT_FLAG iWParam) {
	if (gZTW32_RTime != NULL) {
        switch (iWParam) {
            case SC_MINIMIZE: ZTK_MSG_Minimize(ZT_TRUE); break;
            case SC_RESTORE: ZTK_MSG_Minimize(ZT_FALSE); break;
            case SC_MAXIMIZE: ZTK_MSG_Minimize(ZT_FALSE); break;
            default: break;
        }
	}
}

LRESULT CALLBACK ZTW32_HostCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (gZTW32_RTime != NULL) {
        ZTK_Wake();
        if (message == ZTW32_WM_USER) {
            ZTK_MSG_User();
            ZTK_User();
            return 0x0;
        } else {
			ZT_BOOL lLoop = ZT_TRUE;
            if (!(gZTW32_RTime->owner->system.cache.state & ZTK_WINDOW_STATE_DEFINED)) {
                gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
                gZTW32_RTime->owner->system.cache.state |= ZTK_WINDOW_STATE_DEFINED;
            }
            switch (message) {
                case WM_TIMER: ZTK_MSG_Timer((ZT_INDEX)wParam); break;
                case WM_MOVE: ZTK_MSG_Move((ZT_I)LOWORD(lParam), (ZT_I)HIWORD(lParam)); break;
                case WM_SIZE: ZTK_MSG_Size((ZT_I)LOWORD(lParam), (ZT_I)HIWORD(lParam)); break;
                case WM_MOUSEACTIVATE: return ((lParam & HTCLIENT) ? MA_ACTIVATEANDEAT : MA_ACTIVATE); // inhibit passing window activation click to event processing
                case WM_KILLFOCUS: ZTK_MSG_KeyFocus(ZT_FALSE); break;
                case WM_SETFOCUS: ZTK_MSG_KeyFocus(ZT_TRUE); break;
                case WM_ACTIVATE: ZTK_MSG_Activate(wParam & 0x1); break;
                case WM_SHOWWINDOW: ZTK_MSG_Show(wParam ? ZT_TRUE : ZT_FALSE); break;
                case WM_SYSCOMMAND: ZTW32_HostCommand(wParam); lLoop = ZT_FALSE; break;
                case WM_NCDESTROY: ZTK_MSG_NCDestroy(); lLoop = ZT_FALSE; break;
                case WM_DESTROY: lLoop = ZT_FALSE; break;
                case WM_CLOSE: ZTK_MSG_Close(); return 0x1;
                case WM_QUIT: lLoop = ZT_FALSE; break;
                case WM_CREATE: ZTK_MSG_Create(); lLoop = ZT_FALSE; break;
                case WM_NCCREATE: ZTK_MSG_NCCreate(); lLoop = ZT_FALSE; break;
                default: /*ZTW32_PrintMessage(message);*/ break;
            }
			if (lLoop) {ZTK_User();}
        }
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK ZTW32_HostMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (gZTW32_RTime != NULL) {
        ZTK_Wake();
        if (message == WM_TIMER) {
            ZTK_MSG_Timer((ZT_INDEX)wParam);
        } else {
            switch (message) {
                case WM_MOUSEMOVE: ZTK_MSG_MouseMove(ZTW32_HostMouseX(lParam), ZTW32_HostMouseY(lParam)); return 0x0;
                case WM_LBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_LBUTTON, ZT_TRUE); return 0x0;
                case WM_RBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_RBUTTON, ZT_TRUE); return 0x0;
                case WM_MBUTTONDOWN: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_MBUTTON, ZT_TRUE); return 0x0;
                case WM_LBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_LBUTTON, ZT_FALSE); return 0x0;
                case WM_RBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_RBUTTON, ZT_FALSE); return 0x0;
                case WM_MBUTTONUP: ZTK_MSG_MouseButton(ZTK_SID_MOUSE_MBUTTON, ZT_FALSE); return 0x0;
                case WM_XBUTTONUP: ZTK_MSG_MouseButton(ZTW32_HostMouseXButton(wParam), ZT_FALSE); return TRUE;
                case WM_XBUTTONDOWN: ZTK_MSG_MouseButton(ZTW32_HostMouseXButton(wParam), ZT_TRUE); return TRUE;
                case WM_MOUSEWHEEL: ZTK_MSG_MouseWheel(ZTW32_HostMouseWheel(wParam)); return 0x0;
                case WM_KEYDOWN: if (!((gZTW32_RTime->owner->system.events.pump & ZTK_HID_KEY) && (lParam & 0x40000000))) {ZTK_MSG_Key(ZT_TRUE, wParam & 0xff);} return 0x0;
                case WM_KEYUP: ZTK_MSG_Key(ZT_FALSE, wParam & 0xff); return 0x0;
                case WM_CHAR: if (gZTW32_RTime->owner->system.input.flag & ZTK_WINDOW_INPUT_CHAR) {ZTK_MSG_Char(wParam & (~((ZT_CHAR)0x0)));} return 0x0;
                case WM_SYSKEYDOWN: if (!((gZTW32_RTime->owner->system.events.pump & ZTK_HID_KEY) && (lParam & 0x40000000))) {ZTK_MSG_Key(ZT_TRUE, wParam & 0xff);} break;
                case WM_SYSKEYUP: ZTK_MSG_Key(ZT_FALSE, wParam & 0xff); break;
                case WM_SYSCHAR: if (gZTW32_RTime->owner->system.input.flag & ZTK_WINDOW_INPUT_CHAR) {ZTK_MSG_Char(wParam & (~((ZT_CHAR)0x0)));} break;
                case WM_SYSCOMMAND: ZTW32_HostCommand(wParam); break;
                /*case WM_LBUTTONDBLCLK: break;
                case WM_MBUTTONDBLCLK: break;
                case WM_RBUTTONDBLCLK: break;
                case WM_XBUTTONDBLCLK: break;
                case WM_DEADCHAR: break;
                case WM_SYSDEADCHAR: break;
                case WM_PAINT: break;
                case WM_NCMOUSEMOVE: break;
                case WM_NCMOUSELEAVE: break;
                case WM_NCLBUTTONDOWN: break;
                case WM_NCLBUTTONUP: break;
                case WM_NCMBUTTONDOWN: break;
                case WM_NCMBUTTONUP: break;
                case WM_NCRBUTTONDOWN: break;
                case WM_NCRBUTTONUP: break;
                case 0x31f: break;
                case 0xc0b6: break;
                default: ZTW32_PrintMessage(message); break;*/
                default: break;
            }
        }
	}
    return DefWindowProc(hWnd, message, wParam, lParam);
}

#endif // ZTW32_C_INCLUDED
