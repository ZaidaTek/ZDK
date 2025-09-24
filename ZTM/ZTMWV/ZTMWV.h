/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTMWV_H_INCLUDED
#define ZTMWV_H_INCLUDED

#include "../ZTM.h"

#define ZWV__DEFAULT_LENGTH_MAX 8192000
#define ZWV__DEFAULT_LENGTH_MIN 8
#define ZWV__DEFAULT_EXTEND 0x0

#define ZWV__LENGTH_MAX ZWV__DEFAULT_LENGTH_MAX // ZWV_New(LENGTH > THIS) --> return NULL
#define ZWV__LENGTH_MIN ZWV__DEFAULT_LENGTH_MIN // ZWV_New(LENGTH && LENGTH < THIS) --> return ZWV_New(THIS)
// COMPAT
#define ZWV_AddAndDelete ZWV_AddDiscard
#define ZWV_AddVerbatimAndDelete ZWV_AddVerbatimDiscard
#define ZWV_AddUnsignedInteger ZWV_AddUnsigned
#define ZWV_AddHexInteger ZWV_AddHex
#define ZWV_AddBinInteger ZWV_AddBin

typedef struct {
	ZT_FLAG reserveFree;
	ZT_FLAG extend; // used, but not implement!
	ZT_SIZE capacity; // TODO implement ZT_DATA capacity and deprecate this
	ZT_SIZE alignCapacity;
	ZT_DATA data;
} ZT_WEAVE;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_SIZE ZWV_Length(ZT_WEAVE* iWeave, ZT_SIZE iLength);
ZT_SIZE ZWV_Fit(ZT_WEAVE* iWeave, ZT_SIZE iLength);
void ZWV_Free(ZT_WEAVE* iWeave);
ZT_WEAVE* ZWV_New(ZT_SIZE iLength);
ZT_WEAVE* ZWV_Set(ZT_WEAVE* iWeave);
ZT_WEAVE* ZWV_Get(void);
void ZWV_Empty(void);
void ZWV_Add(const void* iData);
void ZWV_AddVerbatim(const void* iData, ZT_SIZE iLength);
void ZWV_AddDiscard(void* iData);
void ZWV_AddVerbatimDiscard(void* iData, ZT_SIZE iLength);
void ZWV_AddInteger(ZT_I iInteger);
void ZWV_AddUnsigned(ZT_U iInteger);
void ZWV_AddHex(ZT_U iInteger);
void ZWV_AddBin(ZT_U iInteger);
void ZWVX_Empty(ZT_WEAVE* iTarget);
void ZWVX_Add(ZT_WEAVE* iTarget, const void* iData);
void ZWVX_AddVerbatim(ZT_WEAVE* iTarget, const void* iData, ZT_SIZE iLength);
void ZWVX_AddDiscard(ZT_WEAVE* iTarget, void* iData);
void ZWVX_AddVerbatimDiscard(ZT_WEAVE* iTarget, void* iData, ZT_SIZE iLength);
void ZWVX_AddInteger(ZT_WEAVE* iTarget, ZT_I iInteger);
void ZWVX_AddUnsigned(ZT_WEAVE* iTarget, ZT_U iInteger);
void ZWVX_AddHex(ZT_WEAVE* iTarget, ZT_U iInteger);
void ZWVX_AddBin(ZT_WEAVE* iTarget, ZT_U iInteger);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTMWV_H_INCLUDED
