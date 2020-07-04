/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_HASH_H_INCLUDED
#define ZT_HASH_H_INCLUDED

#include "ZTM.h"

#define ZTM_HASH_MAX_PASS 64
#define ZTM_HASH_MAX_STAGE 512

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void* ZTM_Hash_New(ZT_INDEX iBits);
ZT_HASH64* ZTM_Hash_64_New(void);
ZT_HASH128* ZTM_Hash_128_New(void);
ZT_HASH256* ZTM_Hash_256_New(void);
ZT_HASH512* ZTM_Hash_512_New(void);
ZT_HASH1024* ZTM_Hash_1024_New(void);
ZT_HASH32* ZTM_HashDJB2_Text(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashDJB2A_Text(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashSDBM_32_Text(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashFNV0_32_Text(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashFNV1_32_Text(const ZT_CHAR* iText);
ZT_HASH32* ZTM_HashFNV1A_32_Text(const ZT_CHAR* iText);
ZT_HASH64* ZTM_HashSDBM_64_Text(const ZT_CHAR* iText);
ZT_HASH64* ZTM_HashFNV0_64_Text(const ZT_CHAR* iText);
ZT_HASH64* ZTM_HashFNV1_64_Text(const ZT_CHAR* iText);
ZT_HASH64* ZTM_HashFNV1A_64_Text(const ZT_CHAR* iText);
ZT_HASH128* ZTM_Hash_128_Text(const ZT_CHAR* iText);
ZT_HASH128* ZTM_HashMD5_128_Text(const ZT_CHAR* iString);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_HASH_H_INCLUDED
