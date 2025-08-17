/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_HASHMD5_H_INCLUDED
#define ZT_HASHMD5_H_INCLUDED

#include "ZTM.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTM_HashMD5_Init(ZT_HASH128* iHash, ZT_U32* iCounter);
void ZTM_HashMD5_Feed(ZT_HASH128* iHash, ZT_U32* iCounter, ZT_U8* iBuffer, const ZT_U8* iData, ZT_SIZE iLength);
void ZTM_HashMD5_Finish(ZT_HASH128* iHash, ZT_U32* iCounter, ZT_U8* iBuffer);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_HASHMD5_H_INCLUDED
