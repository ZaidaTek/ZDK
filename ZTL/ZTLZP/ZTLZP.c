/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTLZP_C_INCLUDED
#define ZTLZP_C_INCLUDED

#include <zlib.h>

#include "ZTLZP.h"

#define windowBits 15
#define GZIP_ENCODING 16
#define ENABLE_ZLIB_GZIP 32

ZT_INDEX ZZP_GZIP_Main(void* iData, ZT_INDEX iLength, void* oData, ZT_INDEX* oLength, ZT_FLAG iMode) {
	ZT_INDEX lBytesOut = 0;
	if (iData != NULL && iLength && oData != NULL && oLength != NULL && iMode) {
		z_stream lStream;
		lStream.zalloc = Z_NULL;
		lStream.zfree = Z_NULL;
		lStream.opaque = Z_NULL;
		ZT_INDEX lLengthCacheIn = (iMode & ZZP_MODE_INFLATE) ? ZZP_CACHE : (ZZP_CACHE * 3);
		ZT_INDEX lLengthCacheOut = (iMode & ZZP_MODE_INFLATE) ? (ZZP_CACHE * 3) : ZZP_CACHE;
		ZT_U8* lCacheInput = ZTM8_New(lLengthCacheIn);
		if (lCacheInput != NULL) {
			ZT_U8* lCacheOut = ZTM8_New(lLengthCacheOut);
			if (lCacheOut != NULL) {
				if (iMode & ZZP_MODE_INFLATE) {inflateInit2(&lStream, windowBits | ENABLE_ZLIB_GZIP);} else {deflateInit2(&lStream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, windowBits | GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY);}
				ZT_FLAG lEOF = 0x0;
				ZT_INDEX lBytesIn = 0;
				do {
					lStream.next_in = &lCacheInput[lBytesIn];
					lEOF = ((iLength - lBytesIn) > lLengthCacheIn) ? 0x0 : 0x1;
					lBytesIn += (lStream.avail_in = (lEOF ? (iLength - lBytesIn) : lLengthCacheIn));
					ZT_INDEX lCached = 0;
					do {
						lStream.avail_out = ZZP_CHUNK_GZIP;
						lStream.next_out = &lCacheOut[lCached];
						if (iMode & ZZP_MODE_INFLATE) {
							switch (inflate(&lStream, Z_NO_FLUSH)) {case Z_OK: case Z_STREAM_END: case Z_BUF_ERROR: break; default: inflateEnd(&lStream); return 0;}
						} else {
							deflate(&lStream, Z_NO_FLUSH);
							if (lEOF && !lStream.avail_in) {deflate(&lStream, Z_FINISH);}
						}
						lCached += (ZZP_CHUNK_GZIP - lStream.avail_out);
						if (!lStream.avail_in || !((lCached + ZZP_CHUNK_GZIP) < lLengthCacheOut)) {
							ZTM8_Copy(lCacheOut, &(((ZT_U8*)oData)[lBytesOut]), lCached);
							lBytesOut += lCached;
							lCached = 0;
						}
					} while (!lStream.avail_out);
				} while (!lEOF);
				if (iMode & ZZP_MODE_INFLATE) {inflateEnd(&lStream);} else {deflateEnd(&lStream);}
				*oLength = lBytesOut;
				ZTM8_Free(lCacheOut);
			}
			ZTM8_Free(lCacheInput);
		}
	}
	return lBytesOut;
}
ZT_INDEX ZZP_GZIP_Deflate(void* iData, ZT_INDEX iLength, void* oData, ZT_INDEX* oLength) {return ZZP_GZIP_Main(iData, iLength, oData, oLength, ZZP_MODE_DEFLATE);}
ZT_INDEX ZZP_GZIP_Inflate(void* iData, ZT_INDEX iLength, void* oData, ZT_INDEX* oLength) {return ZZP_GZIP_Main(iData, iLength, oData, oLength, ZZP_MODE_INFLATE);}

#endif //ZTLZP_C_INCLUDED
