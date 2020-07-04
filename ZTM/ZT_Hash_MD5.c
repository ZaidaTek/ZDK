/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_HASHMD5_C_INCLUDED
#define ZT_HASHMD5_C_INCLUDED

#include "ZTM__Runtime.h"

#define ZTM_HASHMD5_BSIZE 64

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

unsigned int ZTM_HashMD5_R(unsigned int x, int n) {return (x << n) | (x >> (32 - n));}
unsigned int ZTM_HashMD5_F(unsigned int x, unsigned int y, unsigned int z) {return ((x & y) | (~x & z));}
unsigned int ZTM_HashMD5_G(unsigned int x, unsigned int y, unsigned int z) {return ((x & z) | (y & ~z));}
unsigned int ZTM_HashMD5_H(unsigned int x, unsigned int y, unsigned int z) {return (x ^ y ^ z);}
unsigned int ZTM_HashMD5_I(unsigned int x, unsigned int y, unsigned int z) {return (y ^ (x | ~z));}
void ZTM_HashMD5_FF(unsigned int* a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {*a = ZTM_HashMD5_R(*a + ZTM_HashMD5_F(b, c, d) + x + ac, s) + b;}
void ZTM_HashMD5_GG(unsigned int* a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {*a = ZTM_HashMD5_R(*a + ZTM_HashMD5_G(b, c, d) + x + ac, s) + b;}
void ZTM_HashMD5_HH(unsigned int* a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {*a = ZTM_HashMD5_R(*a + ZTM_HashMD5_H(b, c ,d) + x + ac, s) + b;}
void ZTM_HashMD5_II(unsigned int* a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {*a = ZTM_HashMD5_R(*a + ZTM_HashMD5_I(b, c, d) + x + ac, s) + b;}
void ZTM_HashMD5_Transform(ZTM_HASH__MD5* iHash, const unsigned char* iInputBlock) {
	const unsigned int* x = (const unsigned int*)&iInputBlock[0];
	unsigned int a = iHash->state->data[0];
	unsigned int b = iHash->state->data[1];
	unsigned int c = iHash->state->data[2];
	unsigned int d = iHash->state->data[3];
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
	iHash->state->data[0] += a;
	iHash->state->data[1] += b;
	iHash->state->data[2] += c;
	iHash->state->data[3] += d;
}
void ZTM_HashMD5_Update(ZTM_HASH__MD5* iHash, const unsigned char* iString, unsigned int iLength) {
    unsigned int lIndex = iHash->counter[0] / 8 % ZTM_HASHMD5_BSIZE;
    if ((iHash->counter[0] += (iLength << 3)) < (iLength << 3)) {iHash->counter[1]++;}
    iHash->counter[1] += (iLength >> 29);
    unsigned int firstpart = 64 - lIndex;
    unsigned int i;
    if (iLength >= firstpart) {
        for (unsigned int lCopy = 0; lCopy < firstpart; lCopy++) {iHash->buffer[lIndex + lCopy] = iString[lCopy];}
        ZTM_HashMD5_Transform(iHash, iHash->buffer);
        for (i = firstpart; i + ZTM_HASHMD5_BSIZE <= iLength; i += ZTM_HASHMD5_BSIZE) {ZTM_HashMD5_Transform(iHash, &iString[i]);}
        lIndex = 0;
    } else {i = 0;}
    for (unsigned int lCopy = 0; lCopy < (iLength - i); lCopy++) {iHash->buffer[lIndex + lCopy] = iString[i + lCopy];}
}
void ZTM_HashMD5_Init(ZTM_HASH__MD5* iHash, ZT_HASH128* iState) {
	iHash->state = iState;
    for (unsigned int i = 0; i < 4; i++) {
        iHash->counter[i] = 0x0;
        for (unsigned int ii = 0; ii < ZTM_HASHMD5_BSIZE / 16; ii++) {iHash->buffer[ii] = 0x0;}
        switch (i) {case 0: iHash->state->data[i] = 0x67452301; break; case 1: iHash->state->data[i] = 0xefcdab89; break; case 2: iHash->state->data[i] = 0x98badcfe; break; case 3: iHash->state->data[i] = 0x10325476; break;}
    }
}
void ZTM_HashMD5_128(ZT_HASH128* iHash, const void* iData, ZT_INDEX iLength) {
	if (iHash != NULL && iData != NULL) {
		ZTM_HashMD5_Init(&rZTM_HASH__MD5, iHash);
		ZTM_HashMD5_Update(&rZTM_HASH__MD5, (const unsigned char*)iData, iLength);
		rZTM_HASH__MD5.counter[2] = rZTM_HASH__MD5.counter[0];
		rZTM_HASH__MD5.counter[3] = rZTM_HASH__MD5.counter[1];
		unsigned char lPadding[64];
		for (unsigned int i = 0; i < 64; i++) {lPadding[i] = i ? 0x0 : 0x80;}
        unsigned int lIndex = rZTM_HASH__MD5.counter[0] / 8 % 64;
        unsigned int lPaddingLength = (lIndex < 56) ? (56 - lIndex) : (120 - lIndex);
        ZTM_HashMD5_Update(&rZTM_HASH__MD5, lPadding, lPaddingLength);
        ZTM_HashMD5_Update(&rZTM_HASH__MD5, (const unsigned char*)&rZTM_HASH__MD5.counter[2], 8);
	}
}
ZT_HASH128* ZTM_HashMD5_128_Text(const ZT_CHAR* iString) {
	ZT_HASH128* lHash = NULL;
	if (iString != NULL) {
        ZT_INDEX lLength = ZTC8_GetLength(iString);
		if (lLength) {if ((lHash = ZTM_Hash_128_New()) != NULL) {ZTM_HashMD5_128(lHash, iString, lLength);}}
	}
	return lHash;
}

#endif // ZT_HASHMD5_C_INCLUDED
