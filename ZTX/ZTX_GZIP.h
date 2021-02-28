/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX_GZIP_H_INCLUDED
#define ZTX_GZIP_H_INCLUDED

#include "ZTX.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_SIZE ZTX_Deflate_GZIP(const ZT_U8* iSource, ZT_U8* oTarget, ZT_SIZE iLength);
ZT_SIZE ZTX_Inflate_GZIP(const ZT_U8* iSource, ZT_U8* oTarget, ZT_SIZE iLength);
ZT_SIZE ZTX_DeflateFromFile_GZIP(const ZT_CHAR* iPathSource, ZT_U8* oTarget);
ZT_SIZE ZTX_InflateFromFile_GZIP(const ZT_CHAR* iPathSource, ZT_U8* oTarget);
ZT_SIZE ZTX_DeflateToFile_GZIP(const ZT_U8* iSource, const ZT_CHAR* iPathTarget, ZT_SIZE iLength);
ZT_SIZE ZTX_InflateToFile_GZIP(const ZT_U8* iSource, const ZT_CHAR* iPathTarget, ZT_SIZE iLength);
///works up to 2^31 filesize, not sure as to why not 2^32, despite ZT_SIZE also being U32
ZT_SIZE ZTX_DeflateFromFileToFile_GZIP(const ZT_CHAR* iPathSource, const ZT_U8* iPathTarget);
ZT_SIZE ZTX_InflateFromFileToFile_GZIP(const ZT_CHAR* iPathSource, const ZT_U8* iPathTarget);
ZT_SIZE ZTX_DeflateSize_GZIP(const ZT_U8* iSource, ZT_SIZE iLength);
ZT_SIZE ZTX_InflateSize_GZIP(const ZT_U8* iSource, ZT_SIZE iLength);
ZT_SIZE ZTX_DeflateSizeFromFile_GZIP(const ZT_CHAR* iPath);
ZT_SIZE ZTX_InflateSizeFromFile_GZIP(const ZT_CHAR* iPath);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ZTX_GZIP_H_INCLUDED

