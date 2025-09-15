/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_EVENT_H_INCLUDED
#define ZTK_EVENT_H_INCLUDED

#define ZTK_AID_Press(LAST,NEW) ((NEW) ? (ZTK_AID_PRESS | ((LAST) ? ZTK_AID_REPEAT : ZTK_AID_STRIKE)) : ((LAST) ? ZTK_AID_RELEASE : ZTK_AID_NONE))
#define ZTK_AID_MoveH(LAST,NEW) (((LAST) != (NEW)) ? (((NEW) > (LAST)) ? ZTK_AID_MOVE_RIGHT : ZTK_AID_MOVE_LEFT) : ZTK_AID_NONE)
#define ZTK_AID_MoveV(LAST,NEW) (((LAST) != (NEW)) ? (((NEW) > (LAST)) ? ZTK_AID_MOVE_DOWN : ZTK_AID_MOVE_UP) : ZTK_AID_NONE)
#define ZTK_AID_Move(LAST,NEWX,NEWY) (ZTK_AID_MoveH((LAST)->x, (NEWX)) | ZTK_AID_MoveV((LAST)->y, (NEWY)))

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_EVENT* ZTK_EventGet(ZT_FLAG iA, ZT_INDEX iH, ZT_INDEX iS);
ZT_FLAG ZTK_EventWindowMove(const ZT_POINT* iLast, ZT_I iNewX, ZT_I iNewY);
ZT_FLAG ZTK_EventWindowSize(const ZT_POINT* iLast, ZT_I iNewWidth, ZT_I iNewHeight);
ZT_FLAG ZTK_EventChar(ZT_FLAG iCharLast, ZT_FLAG iCharNew);
ZT_FLAG ZTK_EventMouseMove(const ZT_POINT* iLast, const ZT_POINT* iNew);
ZT_FLAG ZTK_EventMouseButton(ZT_FLAG iLast, ZT_FLAG iNew, ZT_FLAG iButton, ZT_BOOL iDouble);
ZT_FLAG ZTK_EventMouseWheel(ZT_INDEX iLast, ZT_INDEX iNew);
ZT_FLAG ZTK_EventKey(ZT_FLAG iLast, ZT_FLAG iNew, ZT_INDEX iKey);
ZT_FLAG ZTK_EventEnumerateMouseButtons(ZT_FLAG iLast, ZT_FLAG iNew);
//ZT_FLAG ZTK_EventEnumerateKeys(const ZT_U8* iLast, const ZT_U8* iNew);
ZT_FLAG ZTK_EventEnumerateKeys(const ZT_U32* iLast, const ZT_U32* iNew);
ZT_FLAG ZTK_EventPumpMouse(const rZTK_MOUSE* iDevice);
ZT_FLAG ZTK_EventPumpKeyboard(const rZTK_KEYBOARD* iDevice);
ZT_FLAG ZTK_EventCacheWindowState(ZT_FLAG* iState, const ZT_FLAG* iCache);
ZT_FLAG ZTK_EventCacheWindowRect(ZT_RECT* iRect, const ZT_RECT* iCache);
ZT_FLAG ZTK_EventCacheMouse(rZTK_MOUSE* iDevice, const rZTK_MOUSE* iCache);
ZT_FLAG ZTK_EventCacheKeyboard(rZTK_KEYBOARD* iDevice, const rZTK_KEYBOARD* iCache);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTK_EVENT_H_INCLUDED
