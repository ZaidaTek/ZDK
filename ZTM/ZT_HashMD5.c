/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_HASHMD5_C_INCLUDED
#define ZT_HASHMD5_C_INCLUDED

#include "ZTM__Runtime.h"
#include "ZT_HashMD5.h"


inline ZT_U32 ZTM_HashMD5_R(ZT_U32 x, ZT_INDEX n) {return (x << n) | (x >> (32 - n));}
inline ZT_U32 ZTM_HashMD5_F(ZT_U32 x, ZT_U32 y, ZT_U32 z) {return ((x & y) | (~x & z));}
inline ZT_U32 ZTM_HashMD5_G(ZT_U32 x, ZT_U32 y, ZT_U32 z) {return ((x & z) | (y & ~z));}
inline ZT_U32 ZTM_HashMD5_H(ZT_U32 x, ZT_U32 y, ZT_U32 z) {return (x ^ y ^ z);}
inline ZT_U32 ZTM_HashMD5_I(ZT_U32 x, ZT_U32 y, ZT_U32 z) {return (y ^ (x | ~z));}
inline void ZTM_HashMD5_FF(ZT_U32* a, ZT_U32 b, ZT_U32 c, ZT_U32 d, ZT_U32 x, ZT_U32 s, ZT_U32 ac) {*a = ZTM_HashMD5_R(*a + ZTM_HashMD5_F(b, c, d) + x + ac, s) + b;}
inline void ZTM_HashMD5_GG(ZT_U32* a, ZT_U32 b, ZT_U32 c, ZT_U32 d, ZT_U32 x, ZT_U32 s, ZT_U32 ac) {*a = ZTM_HashMD5_R(*a + ZTM_HashMD5_G(b, c, d) + x + ac, s) + b;}
inline void ZTM_HashMD5_HH(ZT_U32* a, ZT_U32 b, ZT_U32 c, ZT_U32 d, ZT_U32 x, ZT_U32 s, ZT_U32 ac) {*a = ZTM_HashMD5_R(*a + ZTM_HashMD5_H(b, c ,d) + x + ac, s) + b;}
inline void ZTM_HashMD5_II(ZT_U32* a, ZT_U32 b, ZT_U32 c, ZT_U32 d, ZT_U32 x, ZT_U32 s, ZT_U32 ac) {*a = ZTM_HashMD5_R(*a + ZTM_HashMD5_I(b, c, d) + x + ac, s) + b;}
void ZTM_HashMD5_Transform(ZT_HASH128* iHash, const ZT_U8* iInputBlock) {
	#define S11 7
	#define S12 12
	#define S13 17
	#define S14 22
	#define S21 5
	#define S22 9
	#define S23 14
	#define S24 20
	#define S31 4
	#define S32 11
	#define S33 16
	#define S34 23
	#define S41 6
	#define S42 10
	#define S43 15
	#define S44 21
	const ZT_U32* x = (const ZT_U32*)&iInputBlock[0];
	ZT_U32 a = iHash->data[0];
	ZT_U32 b = iHash->data[1];
	ZT_U32 c = iHash->data[2];
	ZT_U32 d = iHash->data[3];
	ZTM_HashMD5_FF(&a, b, c, d, x[ 0], S11, 0xd76aa478); // 1
    ZTM_HashMD5_FF(&d, a, b, c, x[ 1], S12, 0xe8c7b756); // 2
    ZTM_HashMD5_FF(&c, d, a, b, x[ 2], S13, 0x242070db); // 3
    ZTM_HashMD5_FF(&b, c, d, a, x[ 3], S14, 0xc1bdceee); // 4
    ZTM_HashMD5_FF(&a, b, c, d, x[ 4], S11, 0xf57c0faf); // 5
    ZTM_HashMD5_FF(&d, a, b, c, x[ 5], S12, 0x4787c62a); // 6
    ZTM_HashMD5_FF(&c, d, a, b, x[ 6], S13, 0xa8304613); // 7
    ZTM_HashMD5_FF(&b, c, d, a, x[ 7], S14, 0xfd469501); // 8
    ZTM_HashMD5_FF(&a, b, c, d, x[ 8], S11, 0x698098d8); // 9
    ZTM_HashMD5_FF(&d, a, b, c, x[ 9], S12, 0x8b44f7af); // 10
    ZTM_HashMD5_FF(&c, d, a, b, x[10], S13, 0xffff5bb1); // 11
    ZTM_HashMD5_FF(&b, c, d, a, x[11], S14, 0x895cd7be); // 12
    ZTM_HashMD5_FF(&a, b, c, d, x[12], S11, 0x6b901122); // 13
    ZTM_HashMD5_FF(&d, a, b, c, x[13], S12, 0xfd987193); // 14
    ZTM_HashMD5_FF(&c, d, a, b, x[14], S13, 0xa679438e); // 15
    ZTM_HashMD5_FF(&b, c, d, a, x[15], S14, 0x49b40821); // 16
    ZTM_HashMD5_GG(&a, b, c, d, x[ 1], S21, 0xf61e2562); // 17
    ZTM_HashMD5_GG(&d, a, b, c, x[ 6], S22, 0xc040b340); // 18
    ZTM_HashMD5_GG(&c, d, a, b, x[11], S23, 0x265e5a51); // 19
    ZTM_HashMD5_GG(&b, c, d, a, x[ 0], S24, 0xe9b6c7aa); // 20
    ZTM_HashMD5_GG(&a, b, c, d, x[ 5], S21, 0xd62f105d); // 21
    ZTM_HashMD5_GG(&d, a, b, c, x[10], S22,  0x2441453); // 22
    ZTM_HashMD5_GG(&c, d, a, b, x[15], S23, 0xd8a1e681); // 23
    ZTM_HashMD5_GG(&b, c, d, a, x[ 4], S24, 0xe7d3fbc8); // 24
    ZTM_HashMD5_GG(&a, b, c, d, x[ 9], S21, 0x21e1cde6); // 25
    ZTM_HashMD5_GG(&d, a, b, c, x[14], S22, 0xc33707d6); // 26
    ZTM_HashMD5_GG(&c, d, a, b, x[ 3], S23, 0xf4d50d87); // 27
    ZTM_HashMD5_GG(&b, c, d, a, x[ 8], S24, 0x455a14ed); // 28
    ZTM_HashMD5_GG(&a, b, c, d, x[13], S21, 0xa9e3e905); // 29
    ZTM_HashMD5_GG(&d, a, b, c, x[ 2], S22, 0xfcefa3f8); // 30
    ZTM_HashMD5_GG(&c, d, a, b, x[ 7], S23, 0x676f02d9); // 31
    ZTM_HashMD5_GG(&b, c, d, a, x[12], S24, 0x8d2a4c8a); // 32
    ZTM_HashMD5_HH(&a, b, c, d, x[ 5], S31, 0xfffa3942); // 33
    ZTM_HashMD5_HH(&d, a, b, c, x[ 8], S32, 0x8771f681); // 34
    ZTM_HashMD5_HH(&c, d, a, b, x[11], S33, 0x6d9d6122); // 35
    ZTM_HashMD5_HH(&b, c, d, a, x[14], S34, 0xfde5380c); // 36
    ZTM_HashMD5_HH(&a, b, c, d, x[ 1], S31, 0xa4beea44); // 37
    ZTM_HashMD5_HH(&d, a, b, c, x[ 4], S32, 0x4bdecfa9); // 38
    ZTM_HashMD5_HH(&c, d, a, b, x[ 7], S33, 0xf6bb4b60); // 39
    ZTM_HashMD5_HH(&b, c, d, a, x[10], S34, 0xbebfbc70); // 40
    ZTM_HashMD5_HH(&a, b, c, d, x[13], S31, 0x289b7ec6); // 41
    ZTM_HashMD5_HH(&d, a, b, c, x[ 0], S32, 0xeaa127fa); // 42
    ZTM_HashMD5_HH(&c, d, a, b, x[ 3], S33, 0xd4ef3085); // 43
    ZTM_HashMD5_HH(&b, c, d, a, x[ 6], S34,  0x4881d05); // 44
    ZTM_HashMD5_HH(&a, b, c, d, x[ 9], S31, 0xd9d4d039); // 45
    ZTM_HashMD5_HH(&d, a, b, c, x[12], S32, 0xe6db99e5); // 46
    ZTM_HashMD5_HH(&c, d, a, b, x[15], S33, 0x1fa27cf8); // 47
    ZTM_HashMD5_HH(&b, c, d, a, x[ 2], S34, 0xc4ac5665); // 48
    ZTM_HashMD5_II(&a, b, c, d, x[ 0], S41, 0xf4292244); // 49
    ZTM_HashMD5_II(&d, a, b, c, x[ 7], S42, 0x432aff97); // 50
    ZTM_HashMD5_II(&c, d, a, b, x[14], S43, 0xab9423a7); // 51
    ZTM_HashMD5_II(&b, c, d, a, x[ 5], S44, 0xfc93a039); // 52
    ZTM_HashMD5_II(&a, b, c, d, x[12], S41, 0x655b59c3); // 53
    ZTM_HashMD5_II(&d, a, b, c, x[ 3], S42, 0x8f0ccc92); // 54
    ZTM_HashMD5_II(&c, d, a, b, x[10], S43, 0xffeff47d); // 55
    ZTM_HashMD5_II(&b, c, d, a, x[ 1], S44, 0x85845dd1); // 56
    ZTM_HashMD5_II(&a, b, c, d, x[ 8], S41, 0x6fa87e4f); // 57
    ZTM_HashMD5_II(&d, a, b, c, x[15], S42, 0xfe2ce6e0); // 58
    ZTM_HashMD5_II(&c, d, a, b, x[ 6], S43, 0xa3014314); // 59
    ZTM_HashMD5_II(&b, c, d, a, x[13], S44, 0x4e0811a1); // 60
    ZTM_HashMD5_II(&a, b, c, d, x[ 4], S41, 0xf7537e82); // 61
    ZTM_HashMD5_II(&d, a, b, c, x[11], S42, 0xbd3af235); // 62
    ZTM_HashMD5_II(&c, d, a, b, x[ 2], S43, 0x2ad7d2bb); // 63
    ZTM_HashMD5_II(&b, c, d, a, x[ 9], S44, 0xeb86d391); // 64
	iHash->data[0] += a;
	iHash->data[1] += b;
	iHash->data[2] += c;
	iHash->data[3] += d;
}
void ZTM_HashMD5_Feed(ZT_HASH128* iHash, ZT_U32* iCounter, ZT_U8* iBuffer, const ZT_U8* iData, ZT_SIZE iLength) {
    ZT_SIZE lIndex = iCounter[0] / 8 % 64;
    if ((iCounter[0] += (iLength << 3)) < (iLength << 3)) {iCounter[1]++;}
    iCounter[1] += (iLength >> 29);
    ZT_SIZE firstpart = 64 - lIndex;
    ZT_SIZE i;
    if (iLength >= firstpart) {
        for (ZT_SIZE lCopy = 0; lCopy < firstpart; lCopy++) {iBuffer[lIndex + lCopy] = iData[lCopy];}
        ZTM_HashMD5_Transform(iHash, iBuffer);
        for (i = firstpart; i + 64 <= iLength; i += 64) {ZTM_HashMD5_Transform(iHash, &iData[i]);}
        lIndex = 0;
    } else {
		i = 0;
	}
    for (ZT_SIZE lCopy = 0; lCopy < (iLength - i); lCopy++) {iBuffer[lIndex + lCopy] = iData[i + lCopy];}
}
void ZTM_HashMD5_Init(ZT_HASH128* iHash, ZT_U32* iCounter) {
	//for (unsigned int i = 0; i < 64 / 16; i++) {lCache.buffer[i] = 0x0;} // what is/was this for?
	iCounter[0] = 0x0;
	iCounter[1] = 0x0;
	iHash->data[0] = 0x67452301;
	iHash->data[1] = 0xefcdab89;
	iHash->data[2] = 0x98badcfe;
	iHash->data[3] = 0x10325476;
}
void ZTM_HashMD5_Finish(ZT_HASH128* iHash, ZT_U32* iCounter, ZT_U8* iBuffer) {
	static const ZT_U8 lPadding[64] = {0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	ZT_U32 lCache[2] = {iCounter[0], iCounter[1]};
	ZT_SIZE lIndex = iCounter[0] / 8 % 64;
	ZT_SIZE lPaddingLength = (lIndex < 56) ? (56 - lIndex) : (120 - lIndex);
	ZTM_HashMD5_Feed(iHash, iCounter, iBuffer, lPadding, lPaddingLength);
	ZTM_HashMD5_Feed(iHash, iCounter, iBuffer, (const ZT_U8*)lCache, 8);
}

#endif // ZT_HASHMD5_C_INCLUDED
