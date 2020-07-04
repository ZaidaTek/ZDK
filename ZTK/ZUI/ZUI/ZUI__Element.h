/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI__ELEMENT_H_INCLUDED
#define ZUI__ELEMENT_H_INCLUDED

#include "ZUI__Runtime.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZUI_HOST_ELEMENT* ZUI_ElementNew(ZT_FLAG iSID, ZT_FLAG iType, const ZT_RECT* iRect);
ZUI_HOST_ELEMENT* ZUI_ElementZero(ZUI_HOST_ELEMENT* iElement);
void ZUI_ElementFree(ZUI_HOST_ELEMENT* iElement);
void ZUI_ElementDraw(ZUI_HOST_ELEMENT* iElement);
void ZUI_ElementEvent(ZUI_HOST_ELEMENT* iElement);
void ZUI_ElementFlagAppend(ZUI_HOST_ELEMENT* iElement, ZT_FLAG iFlag);
void ZUI_ElementFlagRemove(ZUI_HOST_ELEMENT* iElement, ZT_FLAG iFlag);
ZT_FLAG ZUI_ElementFlagMask(ZT_FLAG iType);

void ZUI_ElementTrunkFree(ZUI_HOST_ELEMENT_TRUNK* iTrunk);
ZUI_HOST_ELEMENT_TRUNK* ZUI_ElementTrunkNew(ZT_INDEX iBranches, ZT_FLAG iFlags, ZT_FLAG iType);
ZUI_HOST_ELEMENT_TRUNK* ZUI_ElementTrunkNewZero(void);
ZUI_HOST_ELEMENT_TRUNK* ZUI_ElementTrunkRoot(ZUI_HOST_ELEMENT_TRUNK* iTrunk, ZUI_HOST_ELEMENT* iRoot);

void ZUI_ElementDataFree(ZUI_HOST_ELEMENT_DATA* iData);
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataNewZero(void);
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataNew(ZT_FLAG iFlags, ZT_FLAG iType, void* iMin, void* iMax, void* iUnit, void* iValue);
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataIncrement(ZUI_HOST_ELEMENT_DATA* iData, ZT_INDEX iAmount);
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataDecrement(ZUI_HOST_ELEMENT_DATA* iData, ZT_INDEX iAmount);
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataValue(ZUI_HOST_ELEMENT_DATA* iData, ZT_FLAG iValue);
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataMaximum(ZUI_HOST_ELEMENT_DATA* iData, ZT_FLAG iMaximum);
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataMinimum(ZUI_HOST_ELEMENT_DATA* iData, ZT_FLAG iMinimum);
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataUnit(ZUI_HOST_ELEMENT_DATA* iData, ZT_FLAG iUnit);
/*ZT_FLAG ZUI_ElementDataGetValue(ZUI_HOST_ELEMENT_DATA* iData);
ZT_FLAG ZUI_ElementDataGetMaximum(ZUI_HOST_ELEMENT_DATA* iData);
ZT_FLAG ZUI_ElementDataGetMinimum(ZUI_HOST_ELEMENT_DATA* iData);
ZT_FLAG ZUI_ElementDataGetUnit(ZUI_HOST_ELEMENT_DATA* iData);*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI__ELEMENT_H_INCLUDED
