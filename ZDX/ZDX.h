/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_H_INCLUDED
#define ZDX_H_INCLUDED

#include <ZTM.h>

#include "ZDX_Define.h"
#include "ZDX_Types.h"

#include "ZDX_Interface.h"
#include "ZDX_Runtime.h"
#include "ZDX_Data.h"
#include "ZDX_Diagram.h"

#ifdef __cplusplus
extern 'C' {
#endif // __cplusplus
void ZDX_Free(ZDX_DEVICE* iDevice);
ZDX_DEVICE* ZDX_New(const ZT_CHAR* iAddress, ZT_FLAG iType);
void ZDX_Assign(ZDX_DEVICE* iDevice, ZT_FLAG iType, ZT_FLAG iConfig, ZT_INDEX iSpeed);
void ZDX_Connect(ZDX_DEVICE* iDevice);
void ZDX_Disconnect(ZDX_DEVICE* iDevice);
ZT_INDEX ZDX_Read(ZDX_DEVICE* iDevice, ZDX_DATA* oData);

ZT_INDEX ZDX_GetSpeed(ZDX_DEVICE* iDevice);
ZT_FLAG ZDX_GetChannels(ZDX_DEVICE* iDevice);

ZDX_TRIGGER* ZDX_TriggerNew(void);
void ZDX_TriggerFree(ZDX_TRIGGER* iTrigger);
ZT_INDEX ZDX_TriggerCheck(ZDX_TRIGGER* iTrigger, ZDX_DATA* iData, ZT_INDEX iChannel);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZDX_H_INCLUDED
