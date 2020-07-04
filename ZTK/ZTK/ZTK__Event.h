/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__EVENT_H_INCLUDED
#define ZTK__EVENT_H_INCLUDED

#include "ZTK__Runtime.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_FLAG ZTK_AID_Press(ZT_BOOL iLast, ZT_BOOL iNew);
ZT_FLAG ZTK_AID_MoveH(ZT_I iLast, ZT_I iNew);
ZT_FLAG ZTK_AID_MoveV(ZT_I iLast, ZT_I iNew);
ZT_FLAG ZTK_AID_Move(const ZT_POINT* iLast, ZT_I iNewX, ZT_I iNewY);
ZT_EVENT* ZTK_EventGet(ZT_FLAG iA, ZT_INDEX iH, ZT_INDEX iS);
ZT_FLAG ZTK_EventWindowMove(const ZT_POINT* iLast, ZT_I iNewX, ZT_I iNewY);
ZT_FLAG ZTK_EventWindowSize(const ZT_POINT* iLast, ZT_I iNewWidth, ZT_I iNewHeight);
ZT_FLAG ZTK_EventTimer(ZT_INDEX iSID);
ZT_FLAG ZTK_EventChar(ZT_FLAG iCharLast, ZT_FLAG iCharNew);
ZT_FLAG ZTK_EventMouseMove(const ZT_POINT* iLast, const ZT_POINT* iNew);
ZT_FLAG ZTK_EventMouseButton(ZT_FLAG iLast, ZT_FLAG iNew, ZT_FLAG iButton, ZT_BOOL iDouble);
ZT_FLAG ZTK_EventMouseWheel(ZT_INDEX iLast, ZT_INDEX iNew);
ZT_FLAG ZTK_EventKey(ZT_FLAG iLast, ZT_FLAG iNew, ZT_INDEX iKey);
ZT_FLAG ZTK_EventEnumerateMouseButtons(ZT_FLAG iLast, ZT_FLAG iNew);
ZT_FLAG ZTK_EventEnumerateKeys(const ZT_U8* iLast, const ZT_U8* iNew);

ZT_FLAG ZTK_EventPumpMouse(const ZT_MOUSE* iDevice);
ZT_FLAG ZTK_EventPumpKeyboard(const ZT_KEYBOARD* iDevice);

ZT_FLAG ZTK_EventCacheWindowState(ZT_FLAG* iState, const ZT_FLAG* iCache);
ZT_FLAG ZTK_EventCacheWindowRect(ZT_RECT* iRect, const ZT_RECT* iCache);
ZT_FLAG ZTK_EventCacheMouse(ZT_MOUSE* iDevice, const ZT_MOUSE* iCache);
ZT_FLAG ZTK_EventCacheKeyboard(ZT_KEYBOARD* iDevice, const ZT_KEYBOARD* iCache);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTK__EVENT_H_INCLUDED

