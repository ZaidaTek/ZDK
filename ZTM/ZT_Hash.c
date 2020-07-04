/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_HASH_C_INCLUDED
#define ZT_HASH_C_INCLUDED

#include "ZTM__Runtime.h"

ZT_HASH32* ZTM_Hash_32_New(void) {return (ZT_HASH32*)ZTM8_Init(sizeof(ZT_HASH32), 0x0);}
ZT_HASH64* ZTM_Hash_64_New(void) {return (ZT_HASH64*)ZTM8_Init(sizeof(ZT_HASH64), 0x0);}
ZT_HASH128* ZTM_Hash_128_New(void) {return (ZT_HASH128*)ZTM8_Init(sizeof(ZT_HASH128), 0x0);}
ZT_HASH256* ZTM_Hash_256_New(void) {return (ZT_HASH256*)ZTM8_Init(sizeof(ZT_HASH256), 0x0);}
ZT_HASH512* ZTM_Hash_512_New(void) {return (ZT_HASH512*)ZTM8_Init(sizeof(ZT_HASH512), 0x0);}
ZT_HASH1024* ZTM_Hash_1024_New(void) {return (ZT_HASH1024*)ZTM8_Init(sizeof(ZT_HASH1024), 0x0);}

void ZTM_HashDJB(ZT_HASH32* iHash, const ZT_CHAR* iData, ZT_FLAG iMode) {
    iHash->data[0] = 0x1505;
    ZT_INDEX lIndex = -1;
    if (iMode == 0x22) {
        while (iData[++lIndex] != ZTM_CHAR_NT) {iHash->data[0] = ((iHash->data[0] << 5) + iHash->data[0]) + iData[lIndex];}
    } else if (iMode == 0x23) {
        while (iData[++lIndex] != ZTM_CHAR_NT) {iHash->data[0] = (((iHash->data[0] << 5) + iHash->data[0])) ^ iData[lIndex];}
    }
}
void ZTM_HashSDBM(void* iHash, const ZT_CHAR* iData, ZT_FLAG iMode) { // is this correct?
    ZT_FLAG lBitWidth = iMode & 0xffffffe0;
    ZT_HASH1024* lHash = iHash;
    ZT_INDEX lIndex = -1;
    switch (lBitWidth) {
        case 32: lHash->data[0] = 0x0; while (iData[++lIndex] != ZTM_CHAR_NT) {lHash->data[0] = iData[lIndex] + (lHash->data[0] << 6) + (lHash->data[0] << 16) - lHash->data[0];} break;
        case 64: lHash->quad[0] = 0x0; while (iData[++lIndex] != ZTM_CHAR_NT) {lHash->quad[0] = iData[lIndex] + (lHash->quad[0] << 6) + (lHash->quad[0] << 16) - lHash->quad[0];} break;
    }

}
void ZTM_HashFNV(void* iHash, const ZT_CHAR* iData, ZT_FLAG iMode) {
    ZT_FLAG lBitWidth = iMode & 0xffffffe0;
    ZT_FLAG lMode = iMode & 0x1f;
    ZT_HASH1024* lHash = iHash;
    ZT_INDEX lIndex = -1;
    switch (lBitWidth) {
        case 32: 
			lHash->data[0] = lMode ? 0x811c9dc5 : 0x0;
			if (!lMode || (lMode & 0x1)) {
				while (iData[++lIndex] != ZTM_CHAR_NT) {lHash->data[0] *= 0x1000193; lHash->data[0] = (lHash->data[0] ^ iData[lIndex]);}
			} else if (lMode & 0x2) {
				while (iData[++lIndex] != ZTM_CHAR_NT) {lHash->data[0] = (lHash->data[0] ^ iData[lIndex]); lHash->data[0] *= 0x1000193;}
			}
            break;
        case 64: 
			lHash->quad[0] = lMode ? 0xcbf29ce484222325 : 0x0;
			if (!lMode || (lMode & 0x1)) {
				while (iData[++lIndex] != ZTM_CHAR_NT) {lHash->quad[0] *= 0x100000001b3; lHash->quad[0] = (lHash->quad[0] ^ iData[lIndex]);}
			} else if (lMode & 0x2) {
				while (iData[++lIndex] != ZTM_CHAR_NT) {lHash->quad[0] = (lHash->quad[0] ^ iData[lIndex]); lHash->quad[0] *= 0x100000001b3;}
			}
            break;
        default:
            break;
    }
}
void ZTM_Hash_128(ZT_HASH128* iHash) {
    ZT_U32* iTarget = &iHash->data[0];
    ZT_U32* iScale = &iHash->data[1];
    ZT_U32* iOperator = &iHash->data[2];
    ZT_U32* iSource = &iHash->data[3];
    ZT_INDEX lPasses = ZTM_HASH_MAX_PASS + (*iTarget % ZTM_HASH_MAX_PASS);
    for (ZT_INDEX p = 0; p < lPasses; ++p) {
        for (ZT_INDEX i = 0; i < (ZTM_HASH_MAX_STAGE + (*iScale % ZTM_HASH_MAX_STAGE)); ++i) {
            switch (*iOperator % 3) {
                case 0: {*iTarget ^= (i & 0x1) ? *iSource : ~(*iSource);} break;
                case 1: {*iTarget -= (i & 0x1) ? *iSource : ~(*iSource);} break;
                case 2: {*iTarget += (i & 0x1) ? *iSource : ~(*iSource);} break;
                default: break;
            }
            iSource = &iHash->data[(*iTarget + 1) % 4];
            iOperator = &iHash->data[(*iTarget + 2) % 4];
            iScale = &iHash->data[(*iTarget + 3) % 4];
            iTarget = &iHash->data[*iTarget % 4];
        }
    }
}
ZT_HASH32* ZTM_HashSDBM_32_Text(const ZT_CHAR* iText) {
    ZT_HASH32* lHash = ZTM_Hash_32_New();
    if (lHash != NULL) {ZTM_HashSDBM(lHash, iText, 32);}
    return lHash;
}
ZT_HASH32* ZTM_HashDJB2_Text(const ZT_CHAR* iText) {
    ZT_HASH32* lHash = ZTM_Hash_32_New();
    if (lHash != NULL) {ZTM_HashDJB(lHash, iText, 32 | 0x2);}
    return lHash;
}
ZT_HASH32* ZTM_HashDJB2A_Text(const ZT_CHAR* iText) {
    ZT_HASH32* lHash = ZTM_Hash_32_New();
    if (lHash != NULL) {ZTM_HashDJB(lHash, iText, 32 | 0x3);}
    return lHash;
}
ZT_HASH32* ZTM_HashFNV0_32_Text(const ZT_CHAR* iText) {
    ZT_HASH32* lHash = ZTM_Hash_32_New();
    if (lHash != NULL) {ZTM_HashFNV(lHash, iText, 32);}
    return lHash;
}
ZT_HASH32* ZTM_HashFNV1_32_Text(const ZT_CHAR* iText) {
    ZT_HASH32* lHash = ZTM_Hash_32_New();
    if (lHash != NULL) {ZTM_HashFNV(lHash, iText, 32 | 0x1);}
    return lHash;
}
ZT_HASH32* ZTM_HashFNV1A_32_Text(const ZT_CHAR* iText) {
    ZT_HASH32* lHash = ZTM_Hash_32_New();
    if (lHash != NULL) {ZTM_HashFNV(lHash, iText, 32 | 0x2);}
    return lHash;
}
ZT_HASH64* ZTM_HashSDBM_64_Text(const ZT_CHAR* iText) {
    ZT_HASH64* lHash = ZTM_Hash_64_New();
    if (lHash != NULL) {ZTM_HashSDBM(lHash, iText, 64);}
    return lHash;
}
ZT_HASH64* ZTM_HashFNV0_64_Text(const ZT_CHAR* iText) {
    ZT_HASH64* lHash = ZTM_Hash_64_New();
    if (lHash != NULL) {ZTM_HashFNV(lHash, iText, 64);}
    return lHash;
}
ZT_HASH64* ZTM_HashFNV1_64_Text(const ZT_CHAR* iText) {
    ZT_HASH64* lHash = ZTM_Hash_64_New();
    if (lHash != NULL) {ZTM_HashFNV(lHash, iText, 64 | 0x1);}
    return lHash;
}
ZT_HASH64* ZTM_HashFNV1A_64_Text(const ZT_CHAR* iText) {
    ZT_HASH64* lHash = ZTM_Hash_64_New();
    if (lHash != NULL) {ZTM_HashFNV(lHash, iText, 64 | 0x2);}
    return lHash;
}
ZT_HASH128* ZTM_Hash_128_Text(const ZT_CHAR* iText) {
    ZT_HASH128* lHash = NULL;
    ZT_INDEX lLength = ZTC8_GetLength(iText);
    if ((lHash = ZTM_Hash_128_New()) != NULL) {
        for (ZT_INDEX i = 0; i < 8; ++i) {lHash->byte[8 + i] =  (i < lLength) ? iText[i] : (i - lLength);}
		ZT_INDEX lRun = (lLength < 16) ? 16 : (((lLength + 7) >> 3) << 3);
        ZT_INDEX lCursor = 0;
		while ((lCursor += 8) < lRun) {
			lHash->data[0] = lHash->data[2];
			lHash->data[1] = lHash->data[3];
			for (ZT_INDEX i = 0; i < 8; ++i) {lHash->byte[8 + i] = (lCursor + i < lLength) ? iText[lCursor + i] : (lCursor + i - lLength);}
			ZTM_Hash_128(lHash);
		}
    }
    return lHash;
}
#endif // ZT_HASH_C_INCLUDED
