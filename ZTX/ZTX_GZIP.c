/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX_GZIP_C_INCLUDED
#define ZTX_GZIP_C_INCLUDED

#include "ZTX__Runtime.h"

ZT_SIZE ZTX_GZIP_Main(const ZT_U8* iSource, ZT_U8* oTarget, ZT_SIZE iLength, ZT_FLAG iMode) {
    if (rZTX__INIT || !(rZTX_Host.flag & ZTX_GZIP)) {return 0;}
    z_stream lStream;
    lStream.zalloc = Z_NULL;
    lStream.zfree = Z_NULL;
    lStream.opaque = Z_NULL;
    ZT_SIZE lLengthCacheIn;
    ZT_SIZE lLengthCacheOut;
    ZT_U8* lCacheInput;
    ZT_U8* lCacheOut;
    ZT_FLAG lUseCacheIn;
    ZT_FLAG lUseCacheOut;
    if (iMode & ZTX_MODE_INFLATE) {
        rZTX_Host.zlib.f_inflateInit(&lStream, ZTX_GZIP_WINDOW_BITS | ZTX_GZIP_ENABLE, ZLIB_VERSION, sizeof(lStream));
        lLengthCacheIn = ZTX_GZIP_CACHE;
        lLengthCacheOut = ZTX_GZIP_CACHE << 2;
    } else {
        rZTX_Host.zlib.f_deflateInit(&lStream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, ZTX_GZIP_WINDOW_BITS | ZTX_GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY, ZLIB_VERSION, sizeof(lStream));
        lLengthCacheIn = ZTX_GZIP_CACHE << 2;
        lLengthCacheOut = ZTX_GZIP_CACHE;
    }
    if (iMode & ZTX_MODE_FILE_READ) {
        iLength = ZIO_PipedScan(iSource); /// not actually necessary, see below, but works and calling it a day.
        lCacheInput = ZTM8_New(lLengthCacheIn);
        lUseCacheIn = 0x1;
    } else {
        lCacheInput = NULL;
        lUseCacheIn = 0x0;
    }
    if (iMode & ZTX_MODE_SIZE || iMode & ZTX_MODE_FILE_WRITE) {
        lCacheOut = ZTM8_New(lLengthCacheOut);
        lUseCacheOut = 0x1;
    } else {
        lCacheOut = NULL;
        lUseCacheOut = 0x0;
    }
    ZT_FLAG lEOF = 0x0;
    ZT_SIZE lBytesIn = 0;
	ZT_SIZE lBytesOut = 0;
    do {
        ZT_SIZE lRemaining = iLength - lBytesIn;
        lEOF = (lRemaining > lLengthCacheIn) ? 0x0 : 0x1;
        ZT_SIZE lBytesCache = (lEOF ? lRemaining : lLengthCacheIn);
        if (iMode & ZTX_MODE_FILE_READ) {ZIO_PipedRead(iSource, lCacheInput, lBytesCache, lBytesIn);}
        lStream.next_in = lUseCacheIn ? lCacheInput : (void*)&iSource[lBytesIn];
        lBytesIn += (lStream.avail_in = lBytesCache);
        ZT_SIZE lCached = 0;
        do {
            lStream.avail_out = ZTX_GZIP_CHUNK; /// not sure if this *really* works all the time - i.e. if inflate, it could generate more than cache can hold, etc..
            lStream.next_out = lUseCacheOut ? &lCacheOut[lCached] : &oTarget[lBytesOut + lCached];
            if (iMode & ZTX_MODE_INFLATE) {
                switch (rZTX_Host.zlib.f_inflate(&lStream, Z_NO_FLUSH)) {case Z_OK: case Z_STREAM_END: case Z_BUF_ERROR: break; default: rZTX_Host.zlib.f_inflateEnd(&lStream); return 0;}
            } else {
                rZTX_Host.zlib.f_deflate(&lStream, Z_NO_FLUSH);
                if (lEOF && !lStream.avail_in) {rZTX_Host.zlib.f_deflate(&lStream, Z_FINISH);}
            }
            lCached += (ZTX_GZIP_CHUNK - lStream.avail_out);
            if (!((lCached + ZTX_GZIP_CHUNK) < lLengthCacheOut) || !lStream.avail_in) {
                if (iMode & ZTX_MODE_FILE_WRITE) {
                    if (lBytesOut) {
                        ZIO_PipedAppend(oTarget, lCacheOut, lCached);
                    } else {
                        ZIO_PipedWrite(oTarget, lCacheOut, lCached, 0);
                    }
                }
                lBytesOut += lCached;
                lCached = 0;
            }
        } while (!lStream.avail_out);
    } while (!lEOF);
    if (iMode & ZTX_MODE_INFLATE) {rZTX_Host.zlib.f_inflateEnd(&lStream);} else {rZTX_Host.zlib.f_deflateEnd(&lStream);}
    ZTM8_Free(lCacheOut);
    ZTM8_Free(lCacheInput);
	return lBytesOut;
}
ZT_SIZE ZTX_Deflate_GZIP(const ZT_U8* iSource, ZT_U8* oTarget, ZT_SIZE iLength) {return ZTX_GZIP_Main(iSource, oTarget, iLength, ZTX_MODE_DEFLATE);}
ZT_SIZE ZTX_Inflate_GZIP(const ZT_U8* iSource, ZT_U8* oTarget, ZT_SIZE iLength) {return ZTX_GZIP_Main(iSource, oTarget, iLength, ZTX_MODE_INFLATE);}

ZT_SIZE ZTX_DeflateFromFile_GZIP(const ZT_CHAR* iPathSource, ZT_U8* oTarget) {return ZTX_GZIP_Main(iPathSource, oTarget, -1, ZTX_MODE_DEFLATE | ZTX_MODE_FILE_READ);}
ZT_SIZE ZTX_InflateFromFile_GZIP(const ZT_CHAR* iPathSource, ZT_U8* oTarget) {return ZTX_GZIP_Main(iPathSource, oTarget, -1, ZTX_MODE_INFLATE | ZTX_MODE_FILE_READ);}

ZT_SIZE ZTX_DeflateToFile_GZIP(const ZT_U8* iSource, const ZT_CHAR* iPathTarget, ZT_SIZE iLength) {return ZTX_GZIP_Main(iSource, (ZT_U8*)iPathTarget, iLength, ZTX_MODE_DEFLATE | ZTX_MODE_FILE_WRITE);}
ZT_SIZE ZTX_InflateToFile_GZIP(const ZT_U8* iSource, const ZT_CHAR* iPathTarget, ZT_SIZE iLength) {return ZTX_GZIP_Main(iSource, (ZT_U8*)iPathTarget, iLength, ZTX_MODE_INFLATE | ZTX_MODE_FILE_WRITE);}

ZT_SIZE ZTX_DeflateFromFileToFile_GZIP(const ZT_CHAR* iPathSource, const ZT_U8* iPathTarget) {return ZTX_GZIP_Main(iPathSource, (ZT_U8*)iPathTarget, -1, ZTX_MODE_DEFLATE | ZTX_MODE_FILE_READ | ZTX_MODE_FILE_WRITE);}
ZT_SIZE ZTX_InflateFromFileToFile_GZIP(const ZT_CHAR* iPathSource, const ZT_U8* iPathTarget) {return ZTX_GZIP_Main(iPathSource, (ZT_U8*)iPathTarget, -1, ZTX_MODE_INFLATE | ZTX_MODE_FILE_READ | ZTX_MODE_FILE_WRITE);}

ZT_SIZE ZTX_InflateSize_GZIP(const ZT_U8* iSource, ZT_SIZE iLength) {return ZTX_GZIP_Main(iSource, NULL, iLength, ZTX_MODE_INFLATE | ZTX_MODE_SIZE);}
ZT_SIZE ZTX_DeflateSize_GZIP(const ZT_U8* iSource, ZT_SIZE iLength) {return ZTX_GZIP_Main(iSource, NULL, iLength, ZTX_MODE_DEFLATE | ZTX_MODE_SIZE);}

ZT_SIZE ZTX_DeflateSizeFromFile_GZIP(const ZT_CHAR* iPathSource) {return ZTX_GZIP_Main(iPathSource, NULL, -1, ZTX_MODE_DEFLATE | ZTX_MODE_SIZE | ZTX_MODE_FILE_READ);}
ZT_SIZE ZTX_InflateSizeFromFile_GZIP(const ZT_CHAR* iPathSource) {return ZTX_GZIP_Main(iPathSource, NULL, -1, ZTX_MODE_INFLATE | ZTX_MODE_SIZE | ZTX_MODE_FILE_READ);}

#endif //ZTX_GZIP_C_INCLUDED
