/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_RUNTIME_H_INCLUDED
#define ZDX_RUNTIME_H_INCLUDED

#include "ZDX.h"

typedef struct {
    void* device;
} ZDX_RUNTIME_SERIAL;

#ifdef __cplusplus
extern 'C' {
#endif // __cplusplus
void ZDX_RuntimeFlush(ZDX_INTERFACE* iInterface);
ZT_INDEX ZDX_RuntimeQueue(ZDX_INTERFACE* iInterface);
ZT_INDEX ZDX_RuntimeRead(ZDX_INTERFACE* iInterface, void* iBuffer, ZT_INDEX iLength);
ZT_INDEX ZDX_RuntimeWrite(ZDX_INTERFACE* iInterface, void* iBuffer, ZT_INDEX iLength);
void ZDX_RuntimeNew(ZDX_INTERFACE* iInterface, const ZT_CHAR* iAddress);
void ZDX_RuntimeFree(ZDX_INTERFACE* iInterface);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZDX_RUNTIME_H_INCLUDED
