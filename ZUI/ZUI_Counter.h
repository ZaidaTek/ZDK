/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_COUNTER_H_INCLUDED
#define ZUI_COUNTER_H_INCLUDED

#include "ZUI.h"

typedef ZUI_ELEMENT ZUI_COUNTER;
typedef ZUI_COUNTER ZUI_CYCLE;
typedef ZUI_COUNTER ZUI_INCREMENT;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZUI_INCREMENT* ZUI_IncrementNew(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit);
ZUI_INCREMENT* ZUI_IncrementNewVertical(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit);
ZUI_INCREMENT* ZUI_IncrementNewDigital(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit);
ZUI_INCREMENT* ZUI_IncrementNewPrecision(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit, ZT_INDEX iPrecision);
ZUI_CYCLE* ZUI_CycleNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR** iCaptions, ZT_INDEX iLength);
ZUI_CYCLE* ZUI_CycleNewVertical(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR** iCaptions, ZT_INDEX iLength);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI_COUNTER_H_INCLUDED
