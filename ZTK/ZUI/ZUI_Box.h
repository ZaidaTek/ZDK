/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_BOX_H_INCLUDED
#define ZUI_BOX_H_INCLUDED

#include "ZUI.h"

typedef ZUI_ELEMENT ZUI_BOX;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZUI_BOX* ZUI_BoxNew(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_COLOR iFill, ZT_COLOR iBorder);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI_BOX_H_INCLUDED
