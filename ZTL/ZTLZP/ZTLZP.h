/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTLZP_H_INCLUDED
#define ZTLZP_H_INCLUDED

#include <ZTM.h>

#define ZZP_CHUNK_GZIP 0x4000
#define ZZP_CACHE 0x40000
#define ZZP_MODE_DEFLATE 0x0
#define ZZP_MODE_INFLATE 0x1

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_INDEX ZZP_GZIP_Deflate(void* iData, ZT_INDEX iLength, void* oData, ZT_INDEX* oLength);
ZT_INDEX ZZP_GZIP_Inflate(void* iData, ZT_INDEX iLength, void* oData, ZT_INDEX* oLength);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ZTLZP_H_INCLUDED
