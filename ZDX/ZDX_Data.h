/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_DATA_H_INCLUDED
#define ZDX_DATA_H_INCLUDED

#include "ZDX.h"

#ifdef __cplusplus
extern 'C' {
#endif // __cplusplus
ZDX_DATA* ZDX_DataNew(ZDX_DEVICE* iDevice, ZT_INDEX iLength);
ZDX_DATA* ZDX_DataSet(ZDX_DATA* iData, ZT_U iValue);
void ZDX_DataFree(ZDX_DATA* iData);
void ZDX_DataLineAdd(ZDX_DATA* iData, const ZT_U* iSample);
ZT_U* ZDX_DataGetLastLine(ZDX_DATA* iData);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZDX_DATA_H_INCLUDED
