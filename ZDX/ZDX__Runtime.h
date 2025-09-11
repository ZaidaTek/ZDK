/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX__RUNTIME_H_INCLUDED
#define ZDX__RUNTIME_H_INCLUDED

#include "ZDX.h"

#ifdef __cplusplus
extern 'C' {
#endif // __cplusplus
void ZDX_InterfaceFree(ZDX_DEVICE* iDevice);
void ZDX_InterfaceNew(ZDX_DEVICE* iDevice);
void ZDX_InterfaceStart(ZDX_DEVICE* iDevice);
void ZDX_InterfaceStop(ZDX_DEVICE* iDevice);
ZT_INDEX ZDX_InterfaceQueue(ZDX_DEVICE* iDevice);
ZT_INDEX ZDX_InterfaceRead(ZDX_DEVICE* iDevice, ZDX_DATA* oData);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZDX__RUNTIME_H_INCLUDED
