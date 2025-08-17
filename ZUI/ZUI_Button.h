/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_BUTTON_H_INCLUDED
#define ZUI_BUTTON_H_INCLUDED

#include "ZUI.h"

typedef ZUI_ELEMENT ZUI_BUTTON;
typedef ZUI_ELEMENT ZUI_SWITCH;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZUI_BUTTON* ZUI_ButtonNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iLabel);
ZUI_SWITCH* ZUI_SwitchNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iLabelOff, const ZT_CHAR* iLabelOn);
ZUI_SWITCH* ZUI_SwitchNewArray(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iLabelOff, const ZT_CHAR* iLabelOn, ZT_INDEX iLength);
ZUI_SWITCH* ZUI_SwitchNewArrayVertical(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iLabelOff, const ZT_CHAR* iLabelOn, ZT_INDEX iLength);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI_BUTTON_H_INCLUDED
