/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__MSG_C_INCLUDED
#define ZTK__MSG_C_INCLUDED

#include "ZTK__Runtime.h"

void ZTK_MSG_MouseMove(ZT_I iX, ZT_I iY) {
    rZTK_Host.buffer.flag |= ZTK_HID_MOUSE;
    rZTK_Host.buffer.input.mouse.pos.x = iX;
    rZTK_Host.buffer.input.mouse.pos.y = iY;
}
void ZTK_MSG_MouseButton(ZT_FLAG iButton, ZT_FLAG iState){
    rZTK_Host.buffer.flag |= ZTK_HID_MOUSE;
    rZTK_Host.buffer.input.mouse.state &= (~iButton);
    if (iState) {rZTK_Host.buffer.input.mouse.state |= iButton;}
}
void ZTK_MSG_MouseState(ZT_FLAG iState) {
    rZTK_Host.buffer.flag |= ZTK_HID_MOUSE;
    rZTK_Host.buffer.input.mouse.state = iState;
}
void ZTK_MSG_MouseWheel(ZT_I iIncrement) {
	if (iIncrement) {
        rZTK_Host.buffer.flag |= ZTK_HID_MOUSE;
        rZTK_Host.buffer.input.mouse.wheel -= iIncrement;
	}
}
void ZTK_MSG_Key(ZT_BOOL iDown, ZT_INDEX iKey) {
    rZTK_Host.buffer.flag |= ZTK_HID_KEY;
    ZT_INDEX lKeyIndex = (iKey >> ZTK_KEY_SIZE_SHIFT);
    ZT_FLAG lKeyMask = (0x1 << (iKey % ZTK_KEY_SIZE_UNIT));
    (rZTK_Host.buffer.input.keyboard.state)[lKeyIndex] &= (~lKeyMask);
    if (iDown) {(rZTK_Host.buffer.input.keyboard.state)[lKeyIndex] |= lKeyMask;}
}
void ZTK_MSG_Move(ZT_I iX, ZT_I iY) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    rZTK_Host.buffer.rect.x = iX;
    rZTK_Host.buffer.rect.y = iY;
}
void ZTK_MSG_Size(ZT_I iWidth, ZT_I iHeight) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    rZTK_Host.buffer.rect.w = iWidth;
    rZTK_Host.buffer.rect.h = iHeight;
}
void ZTK_MSG_KeyFocus(ZT_BOOL iEnabled) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    if (iEnabled) {
        rZTK_Host.buffer.state |= ZTK_STATE_KEYFOCUS;
        if (!(rZTK_Host.system.events.enabled & ZTK_HID_KEY)) {
            rZTK_Host.buffer.flag |= ZTK_HID_KEY;
            rZTK_Host.system.events.enabled |= ZTK_HID_KEY;
            ZTK_RuntimeKeyReload(rZTK_Host.buffer.input.keyboard.state);
        }
    } else {
        rZTK_Host.buffer.state &= (~ZTK_STATE_KEYFOCUS);
        if (rZTK_Host.system.events.enabled & ZTK_HID_KEY) {
            rZTK_Host.buffer.flag |= ZTK_HID_KEY;
            rZTK_Host.system.events.enabled &= (~ZTK_HID_KEY);
            ZTM8_Zero(rZTK_Host.buffer.input.keyboard.state, (ZTK_KEY_SIZE_LENGTH >> 3));
        }
    }
}
void ZTK_MSG_NCCreate(void) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    rZTK_Host.buffer.state |= ZTK_STATE_REGISTERED;
}
void ZTK_MSG_Create(void) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    rZTK_Host.buffer.state |= ZTK_STATE_CREATED;
}
void ZTK_MSG_Close(void) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    rZTK_Host.buffer.state |= ZTK_STATE_EXITING;
}
void ZTK_MSG_NCDestroy(void) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    rZTK_Host.buffer.state |= ZTK_STATE_DESTROYED;
}
void ZTK_MSG_Show(ZT_BOOL iEnabled) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    if (iEnabled) {
        rZTK_Host.buffer.state |= (ZTK_STATE_OPENED | ZTK_STATE_SHOW);
    } else {
        rZTK_Host.buffer.state &= (~ZTK_STATE_SHOW);
    }
}
void ZTK_MSG_Activate(ZT_BOOL iEnabled) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    if (iEnabled) {
        rZTK_Host.buffer.state |= ZTK_STATE_ACTIVATED;
    } else {
        rZTK_Host.buffer.state &= (~ZTK_STATE_ACTIVATED);
    }
}
void ZTK_MSG_User(void) {
    if (!(rZTK_Host.buffer.state & ZTK_STATE_RUNNING)) {
        rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
        rZTK_Host.buffer.state |= ZTK_STATE_RUNNING;
    }
}
void ZTK_MSG_Minimize(ZT_BOOL iEnabled) {
    rZTK_Host.buffer.flag |= ZTK_HID_WINDOW;
    if (iEnabled) {
        rZTK_Host.buffer.state |= ZTK_STATE_MINIMIZED;
    } else {
        rZTK_Host.buffer.state &= (~ZTK_STATE_MINIMIZED);
    }
}
void ZTK_MSG_Char(ZT_CHAR iChar) {
    rZTK_Host.buffer.flag |= ZTK_HID_KEY;
    rZTK_Host.buffer.input.text = iChar;
}

#endif // ZTK__MSG_C_INCLUDED
