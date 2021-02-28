/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI__ELEMENT_H_INCLUDED
#define ZUI__ELEMENT_H_INCLUDED

#include "ZUI__Runtime.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
rZUI_ELEMENT* ZUI_ElementNew(ZT_FLAG iSID, ZT_FLAG iType, const ZT_RECT* iRect);
rZUI_ELEMENT* ZUI_ElementZero(rZUI_ELEMENT* iElement);
void ZUI_ElementFree(rZUI_ELEMENT* iElement);
void ZUI_ElementDraw(rZUI_ELEMENT* iElement);
void ZUI_ElementEvent(rZUI_ELEMENT* iElement);
void ZUI_ElementFlagAppend(rZUI_ELEMENT* iElement, ZT_FLAG iFlag);
void ZUI_ElementFlagRemove(rZUI_ELEMENT* iElement, ZT_FLAG iFlag);
ZT_FLAG ZUI_ElementFlagMask(ZT_FLAG iType);

void ZUI_ElementTrunkFree(rZUI_TRUNK* iTrunk);
rZUI_TRUNK* ZUI_ElementTrunkNew(ZT_INDEX iBranches, ZT_FLAG iFlags, ZT_FLAG iType);
rZUI_TRUNK* ZUI_ElementTrunkNewZero(void);
rZUI_TRUNK* ZUI_ElementTrunkRoot(rZUI_TRUNK* iTrunk, rZUI_ELEMENT* iRoot);

void ZUI_ElementDataFree(rZUI_DATA* iData);
rZUI_DATA* ZUI_ElementDataNewZero(void);
rZUI_DATA* ZUI_ElementDataNew(ZT_FLAG iFlags, ZT_FLAG iType, void* iMin, void* iMax, void* iUnit, void* iValue);
rZUI_DATA* ZUI_ElementDataIncrement(rZUI_DATA* iData, ZT_INDEX iAmount);
rZUI_DATA* ZUI_ElementDataDecrement(rZUI_DATA* iData, ZT_INDEX iAmount);
rZUI_DATA* ZUI_ElementDataValue(rZUI_DATA* iData, ZT_FLAG iValue);
rZUI_DATA* ZUI_ElementDataMaximum(rZUI_DATA* iData, ZT_FLAG iMaximum);
rZUI_DATA* ZUI_ElementDataMinimum(rZUI_DATA* iData, ZT_FLAG iMinimum);
rZUI_DATA* ZUI_ElementDataUnit(rZUI_DATA* iData, ZT_FLAG iUnit);
/*ZT_FLAG ZUI_ElementDataGetValue(rZUI_DATA* iData);
ZT_FLAG ZUI_ElementDataGetMaximum(rZUI_DATA* iData);
ZT_FLAG ZUI_ElementDataGetMinimum(rZUI_DATA* iData);
ZT_FLAG ZUI_ElementDataGetUnit(rZUI_DATA* iData);*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI__ELEMENT_H_INCLUDED
