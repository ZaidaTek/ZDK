/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__EVENT_C_INCLUDED
#define ZTK__EVENT_C_INCLUDED

#include "ZTK__Runtime.h"

/*ZT_FLAG ZTK_AID_Press(ZT_BOOL iLast, ZT_BOOL iNew) {return (iNew ? (ZTK_AID_PRESS | (iLast ? ZTK_AID_REPEAT : ZTK_AID_STRIKE)) : (iLast ? ZTK_AID_RELEASE : ZTK_AID_NONE));}
ZT_FLAG ZTK_AID_MoveH(ZT_I iLast, ZT_I iNew) {return ((iLast != iNew) ? ((iNew > iLast) ? ZTK_AID_MOVE_RIGHT : ZTK_AID_MOVE_LEFT) : ZTK_AID_NONE);}
ZT_FLAG ZTK_AID_MoveV(ZT_I iLast, ZT_I iNew) {return ((iLast != iNew) ? ((iNew > iLast) ? ZTK_AID_MOVE_DOWN : ZTK_AID_MOVE_UP) : ZTK_AID_NONE);}
ZT_FLAG ZTK_AID_Move(const ZT_POINT* iLast, ZT_I iNewX, ZT_I iNewY) {return (ZTK_AID_MoveH(iLast->x, iNewX) | ZTK_AID_MoveV(iLast->y, iNewY));}*/
ZT_EVENT* ZTK_EventGet(ZT_FLAG iA, ZT_INDEX iH, ZT_INDEX iS) {
    ZT_EVENT* lEvent = ZTM_QListAdvanceItem(rZTK_Host.buffer.event);
    ZT_FLAG lE = ZTK_EID_NONE;
    lEvent->id.H = iH;
    lEvent->id.S = iS;
    if ((lEvent->id.A = iA)) {
        if (lEvent->id.H & ZTK_HID_KEY) {
            if (lEvent->id.S & ZTK_SID_KEY_FOCUS) {
                lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_KEYBOARD_FOCUS_LOSE : ZTK_EID_KEYBOARD_FOCUS_GAIN;
            } else {
                lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_KEYBOARD_KEY_UP : ZTK_EID_KEYBOARD_KEY_DOWN;
            }
        } else {
            switch (lEvent->id.device) {
                case ZTK_HSID_MOUSE_POSITION: lE = ZTK_EID_MOUSE_MOVE; break;
                case ZTK_HSID_MOUSE_LBUTTON: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_MOUSE_BUTTON_L_UP : ZTK_EID_MOUSE_BUTTON_L_DOWN; break;
                case ZTK_HSID_MOUSE_RBUTTON: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_MOUSE_BUTTON_R_UP : ZTK_EID_MOUSE_BUTTON_R_DOWN; break;
                case ZTK_HSID_MOUSE_MBUTTON: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_MOUSE_BUTTON_M_UP : ZTK_EID_MOUSE_BUTTON_M_DOWN; break;
                case ZTK_HSID_MOUSE_X1BUTTON: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_MOUSE_BUTTON_X1_UP : ZTK_EID_MOUSE_BUTTON_X2_DOWN; break;
                case ZTK_HSID_MOUSE_X2BUTTON: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_MOUSE_BUTTON_X2_UP : ZTK_EID_MOUSE_BUTTON_X2_DOWN; break;
                case ZTK_HSID_MOUSE_WHEEL: lE = (iA & ZTK_AID_MOVE_UP) ? ZTK_EID_MOUSE_WHEEL_UP : ZTK_EID_MOUSE_WHEEL_DOWN; break;
                case ZTK_HSID_WINDOW_POSITION: lE = ZTK_EID_WINDOW_REPOSITION; break;
                case ZTK_HSID_WINDOW_SIZE: lE = ZTK_EID_WINDOW_RESIZE; break;
                case ZTK_HSID_WINDOW_VISIBILITY: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_WINDOW_HIDE : ZTK_EID_WINDOW_SHOW; break;
                case ZTK_HSID_WINDOW_EXECUTION: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_NONE : ZTK_EID_WINDOW_RUN; break;
                case ZTK_HSID_WINDOW_ACTIVATION: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_WINDOW_DEACTIVATE : ZTK_EID_WINDOW_ACTIVATE; break;
                case ZTK_HSID_WINDOW_INITIALIZATION: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_NONE : ZTK_EID_WINDOW_INITIALIZE; break;
                case ZTK_HSID_WINDOW_REGISTRATION: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_NONE : ZTK_EID_WINDOW_REGISTER; break;
                case ZTK_HSID_WINDOW_CREATION: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_NONE : ZTK_EID_WINDOW_CREATE; break;
                case ZTK_HSID_WINDOW_HALT: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_NONE : ZTK_EID_WINDOW_CLOSE; break;
                case ZTK_HSID_WINDOW_DESTRUCTION: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_NONE : ZTK_EID_WINDOW_DESTROY; break;
                case ZTK_HSID_WINDOW_MINIMIZATION: lE = (iA & ZTK_AID_RELEASE) ? ZTK_EID_WINDOW_RESTORE : ZTK_EID_WINDOW_MINIMIZE; break;
                default: break;
            }
        }
    }
    lEvent->id.E = lE;
	return lEvent;
}
ZT_FLAG ZTK_EventWindowMove(const ZT_POINT* iLast, ZT_I iNewX, ZT_I iNewY) {
    ZT_FLAG lA = ZTK_AID_NONE;
    if ((rZTK_Host.system.events.enabled & ZTK_HID_WINDOW) && (lA = ZTK_AID_Move(iLast, iNewX, iNewY))) {
        ZT_EVENT* lEvent = ZTK_EventGet(lA, ZTK_HID_WINDOW, ZTK_SID_WINDOW_POSITION);
        lEvent->data.d0 = iNewX;
        lEvent->data.d1 = iNewY;
        lEvent->data.d2 = iLast->x;
        lEvent->data.d3 = iLast->y;
    }
    return lA;
}
ZT_FLAG ZTK_EventWindowSize(const ZT_POINT* iLast, ZT_I iNewWidth, ZT_I iNewHeight) {
    ZT_FLAG lA = ZTK_AID_NONE;
    if ((rZTK_Host.system.events.enabled & ZTK_HID_WINDOW) && (lA = ZTK_AID_Move(iLast, iNewWidth, iNewHeight))) {
        ZT_EVENT* lEvent = ZTK_EventGet(lA, ZTK_HID_WINDOW, ZTK_SID_WINDOW_SIZE);
        lEvent->data.d0 = iNewWidth;
        lEvent->data.d1 = iNewHeight;
        lEvent->data.d2 = iLast->x;
        lEvent->data.d3 = iLast->y;
    }
    return lA;
}
ZT_FLAG ZTK_EventChar(ZT_FLAG iCharLast, ZT_FLAG iCharNew) {
    ZT_FLAG lA = ZTK_AID_Press((iCharLast == iCharNew), ZT_TRUE);
    if (rZTK_Host.system.events.enabled & ZTK_HID_KEY) {
        ZT_EVENT* lEvent = ZTK_EventGet(lA, ZTK_HID_KEY, ZTK_SID_KEY_CHAR | (iCharNew & 0xff));
        lEvent->data.d0 = iCharNew & 0xff;
        lEvent->data.d1 = iCharNew & 0xff00;
        lEvent->data.d2 = iCharNew & 0xff0000;
        lEvent->data.d3 = iCharNew & 0xff000000;
    }
    return lA;
}
ZT_FLAG ZTK_EventMouseMove(const ZT_POINT* iLast, const ZT_POINT* iNew) {
    ZT_FLAG lA = ZTK_AID_NONE;
    if ((rZTK_Host.system.events.enabled & ZTK_HID_MOUSE) && (lA = ZTK_AID_Move(iLast, iNew->x, iNew->y))) {
        ZT_EVENT* lEvent = ZTK_EventGet(lA, ZTK_HID_MOUSE, ZTK_SID_MOUSE_POSITION);
        lEvent->data.d0 = iNew->x;
        lEvent->data.d1 = iNew->y;
        lEvent->data.d2 = iLast->x;
        lEvent->data.d3 = iLast->y;
    }
    return lA;
}
ZT_FLAG ZTK_EventMouseButton(ZT_FLAG iLast, ZT_FLAG iNew, ZT_FLAG iButton, ZT_BOOL iDouble) {
    ZT_FLAG lA = ZTK_AID_NONE;
    if ((rZTK_Host.system.events.enabled & ZTK_HID_MOUSE) && (lA = ZTK_AID_Press(iLast, iNew))) {
        lA |= iDouble ? ZTK_AID_DOUBLE : ZTK_AID_NONE;
        ZT_EVENT* lEvent = ZTK_EventGet(lA, ZTK_HID_MOUSE, iButton);
        lEvent->data.d0 = rZTK_Host.system.input.mouse.pos.x;
        lEvent->data.d1 = rZTK_Host.system.input.mouse.pos.y;
    }
    return lA;
}
ZT_FLAG ZTK_EventMouseWheel(ZT_INDEX iLast, ZT_INDEX iNew) {
    ZT_FLAG lA = ZTK_AID_NONE;
    ZT_I lIncrement = iNew - iLast;
	if (lIncrement) {
        if ((rZTK_Host.system.events.enabled & ZTK_HID_MOUSE) && (lA = ZTK_AID_MoveV(0, lIncrement))) {
            ZT_EVENT* lEvent = ZTK_EventGet(lA, ZTK_HID_MOUSE, ZTK_SID_MOUSE_WHEEL);
            lEvent->data.d0 = rZTK_Host.system.input.mouse.pos.x;
            lEvent->data.d1 = rZTK_Host.system.input.mouse.pos.y;
            lEvent->data.d2 = (lIncrement < 0) ? (-lIncrement) : lIncrement;
            lEvent->data.d3 = lIncrement;
        }
	}
    return lA;
}
ZT_FLAG ZTK_EventKey(ZT_FLAG iLast, ZT_FLAG iNew, ZT_INDEX iKey) {
    ZT_FLAG lA = ZTK_AID_NONE;
    if ((rZTK_Host.system.events.enabled & ZTK_HID_KEY) && (lA = ZTK_AID_Press(iLast, iNew))) {
        ZTK_EventGet(lA, ZTK_HID_KEY, iKey);
    }
    return lA;
}
ZT_FLAG ZTK_EventEnumerateMouseButtons(ZT_FLAG iLast, ZT_FLAG iNew) {
    ZT_FLAG lA = ZTK_AID_NONE;
    ZT_FLAG lButtons[] = {ZTK_SID_MOUSE_LBUTTON, ZTK_SID_MOUSE_RBUTTON, ZTK_SID_MOUSE_MBUTTON, ZTK_SID_MOUSE_X1BUTTON, ZTK_SID_MOUSE_X2BUTTON};
    ZT_INDEX lLength = sizeof(lButtons) / sizeof(lButtons[0]);
    for (ZT_INDEX i = 0; i < lLength; i++) {
        lA |= ZTK_EventMouseButton(iLast & lButtons[i], iNew & lButtons[i], lButtons[i], ZT_FALSE);
    }
    return lA;
}
//ZT_FLAG ZTK_EventEnumerateKeys(const ZT_U8* iLast, const ZT_U8* iNew) {
ZT_FLAG ZTK_EventEnumerateKeys(const ZT_U32* iLast, const ZT_U32* iNew) {
    ZT_FLAG lA = ZTK_AID_NONE;
    for (ZT_INDEX i = 0; i < ZTK_KEY_SIZE_LENGTH; i++) {
        lA |= ZTK_EventKey((iLast[(i >> ZTK_KEY_SIZE_SHIFT)] & (0x1 << (i % ZTK_KEY_SIZE_UNIT))), (iNew[(i >> ZTK_KEY_SIZE_SHIFT)] & (0x1 << (i % ZTK_KEY_SIZE_UNIT))), i);
    }
    return lA;
}
ZT_FLAG ZTK_EventPumpMouse(const rZTK_MOUSE* iDevice) {
    ZT_FLAG lA = ZTK_AID_NONE;
	if (iDevice != NULL) {lA |= ZTK_EventEnumerateMouseButtons(iDevice->state, iDevice->state);}
    return lA;
}
ZT_FLAG ZTK_EventPumpKeyboard(const rZTK_KEYBOARD* iDevice) {
    ZT_FLAG lA = ZTK_AID_NONE;
	if (iDevice != NULL) {
        lA |= ZTK_EventEnumerateKeys(iDevice->state, iDevice->state);
    }
    return lA;
}
ZT_FLAG ZTK_EventCacheWindowState(ZT_FLAG* iState, const ZT_FLAG* iCache) {
    ZT_FLAG lAction = ZTK_AID_NONE;
    ZT_FLAG lA = ZTK_AID_NONE;
    ZT_FLAG lH = ZTK_HID_NONE;
    ZT_FLAG lS = ZTK_SID_NONE;
    ZT_FLAG lToggled = (*iState ^ *iCache);
    for (ZT_FLAG i = 0x1; i; i <<= 1) {
        if (lToggled & i) {
            lA = ((*iCache & i) ? ZTK_AID_PRESS : ZTK_AID_RELEASE);
            switch (i) {
                case ZTK_STATE_DEFINED: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_INITIALIZATION; break;
                case ZTK_STATE_REGISTERED: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_REGISTRATION; break;
                case ZTK_STATE_CREATED: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_CREATION; break;
                case ZTK_STATE_RUNNING: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_EXECUTION; break;
                case ZTK_STATE_EXITING: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_HALT; break;
                case ZTK_STATE_DESTROYED: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_DESTRUCTION; break;
                case ZTK_STATE_SHOW: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_VISIBILITY; break;
                case ZTK_STATE_ACTIVATED: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_ACTIVATION; break;
                case ZTK_STATE_MINIMIZED: lH = ZTK_HID_WINDOW; lS = ZTK_SID_WINDOW_MINIMIZATION; break;

                case ZTK_STATE_KEYFOCUS: lH = ZTK_HID_KEY; lS = ZTK_SID_KEY_FOCUS; break;

                default: lA = ZTK_AID_NONE; lH = ZTK_HID_NONE; lS = ZTK_SID_NONE; break;
            }
            ZTK_EventGet(lA, lH, lS);
            lAction |= lA;
        }
    }
    if (lAction) {*iState = *iCache;}
    return lAction;
}
ZT_FLAG ZTK_EventCacheWindowRect(ZT_RECT* iRect, const ZT_RECT* iCache) {
    ZT_FLAG lAction = ZTK_AID_NONE;
    lAction |= ZTK_EventWindowMove((const ZT_POINT*)&(iRect->x), iCache->x, iCache->y);
    lAction |= ZTK_EventWindowSize((const ZT_POINT*)&(iRect->w), iCache->w, iCache->h) << 8;
    if (lAction) {*iRect = *iCache;}
    return lAction;
}
ZT_FLAG ZTK_EventCacheMouse(rZTK_MOUSE* iDevice, const rZTK_MOUSE* iCache) {
    ZT_FLAG lA = ZTK_AID_NONE;
	if (iDevice != NULL && iCache != NULL) {
        if ((lA |= ZTK_EventMouseMove(&(iDevice->pos), &(iCache->pos)))) {iDevice->pos = iCache->pos;}
        if ((lA |= ZTK_EventEnumerateMouseButtons(iDevice->state, iCache->state))) {iDevice->state = iCache->state;}
        if ((lA |= ZTK_EventMouseWheel(iDevice->wheel, iCache->wheel))) {iDevice->wheel = iCache->wheel;}
	}
    return lA;
}
ZT_FLAG ZTK_EventCacheKeyboard(rZTK_KEYBOARD* iDevice, const rZTK_KEYBOARD* iCache) {
    ZT_FLAG lA = ZTK_AID_NONE;
	if (iDevice != NULL && iCache != NULL) {
        lA |= ZTK_EventEnumerateKeys(iDevice->state, iCache->state);
        if (lA) {ZTM8_Copy(iCache->state, iDevice->state, (ZTK_KEY_SIZE_LENGTH >> 3));}
        if (rZTK_Host.system.input.flag & ZTK_WINDOW_INPUT_CHAR) {
            if (rZTK_Host.buffer.input.text != ZTM_CHAR_NT) {
                ZTK_EventChar(rZTK_Host.system.input.text, rZTK_Host.buffer.input.text);
                rZTK_Host.system.input.text = rZTK_Host.buffer.input.text;
                rZTK_Host.buffer.input.text = ZTM_CHAR_NT;
            }
        }
	}
    return lA;
}

#endif // ZTK__EVENT_C_INCLUDED
