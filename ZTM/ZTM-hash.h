/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_HASH_H_INCLUDED
#define ZTM_HASH_H_INCLUDED

#include "ZTM.h" // ?
#include "ZTM-hash-md5.h"

#define ZTM_HASH_MAX_PASS 64
#define ZTM_HASH_MAX_STAGE 512

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void* ZTM_HashNew(ZT_INDEX iBits);
ZT_HASH32* ZTM_HashNew_32(void);
ZT_HASH64* ZTM_HashNew_64(void);
ZT_HASH128* ZTM_HashNew_128(void);
ZT_HASH256* ZTM_HashNew_256(void);
ZT_HASH512* ZTM_HashNew_512(void);
ZT_HASH1024* ZTM_HashNew_1024(void);
void ZTM_HashTransform_128(ZT_HASH128* iHash);
void ZTM_HashData_128(ZT_HASH128* iHash, const ZT_DATA* iData);
void ZTM_HashData_MD5(ZT_HASH128* iHash, const ZT_DATA* iData);
void ZTM_HashData_DJB2(ZT_HASH32* iHash, const ZT_DATA* iData);
void ZTM_HashData_DJB2A(ZT_HASH32* iHash, const ZT_DATA* iData);
void ZTM_HashData_SDBM_32(ZT_HASH32* iHash, const ZT_DATA* iData);
void ZTM_HashData_SDBM_64(ZT_HASH64* iHash, const ZT_DATA* iData);
void ZTM_HashData_FNV0_32(ZT_HASH32* iHash, const ZT_DATA* iData);
void ZTM_HashData_FNV0_64(ZT_HASH64* iHash, const ZT_DATA* iData);
void ZTM_HashData_FNV1_32(ZT_HASH32* iHash, const ZT_DATA* iData);
void ZTM_HashData_FNV1_64(ZT_HASH64* iHash, const ZT_DATA* iData);
void ZTM_HashData_FNV1A_32(ZT_HASH32* iHash, const ZT_DATA* iData);
void ZTM_HashData_FNV1A_64(ZT_HASH64* iHash, const ZT_DATA* iData);
void ZTM_HashText_128(ZT_HASH128* iHash, const ZT_CHAR* iText);
void ZTM_HashText_MD5(ZT_HASH128* iHash, const ZT_CHAR* iText);
void ZTM_HashText_DJB2(ZT_HASH32* iHash, const ZT_CHAR* iText);
void ZTM_HashText_DJB2A(ZT_HASH32* iHash, const ZT_CHAR* iText);
void ZTM_HashText_SDBM_32(ZT_HASH32* iHash, const ZT_CHAR* iText);
void ZTM_HashText_SDBM_64(ZT_HASH64* iHash, const ZT_CHAR* iText);
void ZTM_HashText_FNV0_32(ZT_HASH32* iHash, const ZT_CHAR* iText);
void ZTM_HashText_FNV0_64(ZT_HASH64* iHash, const ZT_CHAR* iText);
void ZTM_HashText_FNV1_32(ZT_HASH32* iHash, const ZT_CHAR* iText);
void ZTM_HashText_FNV1_64(ZT_HASH64* iHash, const ZT_CHAR* iText);
void ZTM_HashText_FNV1A_32(ZT_HASH32* iHash, const ZT_CHAR* iText);
void ZTM_HashText_FNV1A_64(ZT_HASH64* iHash, const ZT_CHAR* iText);
ZT_HASH128* ZTM_HashTextNew_128(const ZT_CHAR* iText);
ZT_HASH128* ZTM_HashTextNew_MD5(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashTextNew_DJB2(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashTextNew_DJB2A(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashTextNew_SDBM_32(const ZT_CHAR* iText);
ZT_HASH64* ZTM_HashTextNew_SDBM_64(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashTextNew_FNV0_32(const ZT_CHAR* iText);
ZT_HASH64* ZTM_HashTextNew_FNV0_64(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashTextNew_FNV1_32(const ZT_CHAR* iText);
ZT_HASH64* ZTM_HashTextNew_FNV1_64(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashTextNew_FNV1A_32(const ZT_CHAR* iText);
ZT_HASH64* ZTM_HashTextNew_FNV1A_64(const ZT_CHAR* iText);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTM_HASH_H_INCLUDED
