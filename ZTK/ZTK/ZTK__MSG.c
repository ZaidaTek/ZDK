/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__MSG_C_INCLUDED
#define ZTK__MSG_C_INCLUDED

#include "ZTK__Runtime.h"

void ZTK_MSG_Timer(ZT_INDEX iSID) {
	if (gZT_Window != NULL) {
        ZTK_EventTimer(iSID);
    }
}
void ZTK_MSG_MouseMove(ZT_I iX, ZT_I iY) {
	if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_MOUSE;
        gZT_Window->system.cache.input.mouse.pos.x = iX;
        gZT_Window->system.cache.input.mouse.pos.y = iY;
	}
}
void ZTK_MSG_MouseButton(ZT_FLAG iButton, ZT_FLAG iState){
	if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_MOUSE;
        gZT_Window->system.cache.input.mouse.state &= (~iButton);
        if (iState) {gZT_Window->system.cache.input.mouse.state |= iButton;}
	}
}
void ZTK_MSG_MouseState(ZT_FLAG iState) {
	if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_MOUSE;
        gZT_Window->system.cache.input.mouse.state = iState;
	}
}
void ZTK_MSG_MouseWheel(ZT_I iIncrement) {
	if (gZT_Window != NULL && iIncrement) {
        gZT_Window->system.cache.flag |= ZTK_HID_MOUSE;
        gZT_Window->system.cache.input.mouse.wheel -= iIncrement;
	}
}
void ZTK_MSG_Key(ZT_BOOL iDown, ZT_INDEX iKey) {
	if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_KEY;
        ZT_INDEX lKeyIndex = (iKey >> ZTK_KEY_SIZE_SHIFT);
        ZT_FLAG lKeyMask = (0x1 << (iKey % ZTK_KEY_SIZE_UNIT));
        (gZT_Window->system.cache.input.keyboard.state)[lKeyIndex] &= (~lKeyMask);
        if (iDown) {(gZT_Window->system.cache.input.keyboard.state)[lKeyIndex] |= lKeyMask;}
	}
}

void ZTK_MSG_Move(ZT_I iX, ZT_I iY) {
	if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        gZT_Window->system.cache.rect.x = iX;
        gZT_Window->system.cache.rect.y = iY;
	}
}
void ZTK_MSG_Size(ZT_I iWidth, ZT_I iHeight) {
	if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        gZT_Window->system.cache.rect.w = iWidth;
        gZT_Window->system.cache.rect.h = iHeight;
	}
}
void ZTK_MSG_KeyFocus(ZT_BOOL iEnabled) {
	if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        if (iEnabled) {
            gZT_Window->system.cache.state |= ZTK_WINDOW_STATE_KEYFOCUS;
            if (!(gZT_Window->system.events.enabled & ZTK_HID_KEY)) {
                gZT_Window->system.cache.flag |= ZTK_HID_KEY;
                gZT_Window->system.events.enabled |= ZTK_HID_KEY;
                ZTK_RuntimeKeyReload(gZT_Window->system.cache.input.keyboard.state);
            }
        } else {
            gZT_Window->system.cache.state &= (~ZTK_WINDOW_STATE_KEYFOCUS);
            if (gZT_Window->system.events.enabled & ZTK_HID_KEY) {
                gZT_Window->system.cache.flag |= ZTK_HID_KEY;
                gZT_Window->system.events.enabled &= (~ZTK_HID_KEY);
                ZTM8_Zero(gZT_Window->system.cache.input.keyboard.state, (ZTK_KEY_SIZE_LENGTH >> 3));
            }
        }
	}
}
void ZTK_MSG_NCCreate(void) {
    if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        gZT_Window->system.cache.state |= ZTK_WINDOW_STATE_REGISTERED;
    }
}
void ZTK_MSG_Create(void) {
    if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        gZT_Window->system.cache.state |= ZTK_WINDOW_STATE_CREATED;
    }
}
void ZTK_MSG_Close(void) {
    if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        gZT_Window->system.cache.state |= ZTK_WINDOW_STATE_EXITING;
        ZTK_Close();
    }
}
void ZTK_MSG_NCDestroy(void) {
    if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        gZT_Window->system.cache.state |= ZTK_WINDOW_STATE_DESTROYED;
    }
}
void ZTK_MSG_Show(ZT_BOOL iEnabled) {
    if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        if (iEnabled) {
            gZT_Window->system.cache.state |= (ZTK_WINDOW_STATE_OPENED | ZTK_WINDOW_STATE_SHOW);
        } else {
            gZT_Window->system.cache.state &= (~ZTK_WINDOW_STATE_SHOW);
        }
    }
}
void ZTK_MSG_Activate(ZT_BOOL iEnabled) {
    if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        if (iEnabled) {
            gZT_Window->system.cache.state |= ZTK_WINDOW_STATE_ACTIVATED;
        } else {
            gZT_Window->system.cache.state &= (~ZTK_WINDOW_STATE_ACTIVATED);
        }
    }
}
void ZTK_MSG_User(void) {
    if (gZT_Window != NULL) {
        if (!(gZT_Window->system.cache.state & ZTK_WINDOW_STATE_RUNNING)) {
            gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
            gZT_Window->system.cache.state |= ZTK_WINDOW_STATE_RUNNING;
        }
    }
}
void ZTK_MSG_Minimize(ZT_BOOL iEnabled) {
    if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_WINDOW;
        if (iEnabled) {
            gZT_Window->system.cache.state |= ZTK_WINDOW_STATE_MINIMIZED;
        } else {
            gZT_Window->system.cache.state &= (~ZTK_WINDOW_STATE_MINIMIZED);
        }
    }
}
void ZTK_MSG_Char(ZT_CHAR iChar) {
    if (gZT_Window != NULL) {
        gZT_Window->system.cache.flag |= ZTK_HID_KEY;
        gZT_Window->system.cache.input.text = iChar;
    }
}
#endif // ZTK__MSG_C_INCLUDED

