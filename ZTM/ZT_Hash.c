/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_HASH_C_INCLUDED
#define ZT_HASH_C_INCLUDED

#include "ZTM__Runtime.h"
#include "ZT_HashMD5.h"

void* ZTM_HashNew(ZT_INDEX iBits) {
	switch (iBits) {
		case 32: return ZTM_HashNew_32();
		case 64: return ZTM_HashNew_64();
		case 128: return ZTM_HashNew_128();
		case 256: return ZTM_HashNew_256();
		case 512: return ZTM_HashNew_512();
		case 1024: return ZTM_HashNew_1024();
		default: return NULL;
	}
}
ZT_HASH32* ZTM_HashNew_32(void) {return (ZT_HASH32*)ZTM8_Init(sizeof(ZT_HASH32), 0x0);}
ZT_HASH64* ZTM_HashNew_64(void) {return (ZT_HASH64*)ZTM8_Init(sizeof(ZT_HASH64), 0x0);}
ZT_HASH128* ZTM_HashNew_128(void) {return (ZT_HASH128*)ZTM8_Init(sizeof(ZT_HASH128), 0x0);}
ZT_HASH256* ZTM_HashNew_256(void) {return (ZT_HASH256*)ZTM8_Init(sizeof(ZT_HASH256), 0x0);}
ZT_HASH512* ZTM_HashNew_512(void) {return (ZT_HASH512*)ZTM8_Init(sizeof(ZT_HASH512), 0x0);}
ZT_HASH1024* ZTM_HashNew_1024(void) {return (ZT_HASH1024*)ZTM8_Init(sizeof(ZT_HASH1024), 0x0);}
void ZTM_HashTransform_128(ZT_HASH128* iHash) {
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
void ZTM_HashData_128(ZT_HASH128* iHash, const ZT_DATA* iData) {
    if (iHash != NULL && iData != NULL) {
		ZT_SIZE lLength;
        if (iData->payload != NULL && (lLength = iData->length)) {
			for (ZT_SIZE i = 0; i < 8; ++i) {iHash->byte[8 + i] =  (i < lLength) ? iData->byte[i] : (i - lLength);}
			ZT_SIZE lRun = (lLength < 16) ? 16 : (((lLength + 7) >> 3) << 3);
			ZT_SIZE lCursor = 0;
			while ((lCursor += 8) < lRun) {
				iHash->data[0] = iHash->data[2];
				iHash->data[1] = iHash->data[3];
				for (ZT_SIZE i = 0; i < 8; ++i) {iHash->byte[8 + i] = (lCursor + i < lLength) ? iData->byte[lCursor + i] : (lCursor + i - lLength);}
				ZTM_HashTransform_128(iHash);
			}
		}
    }
}
void ZTM_HashData_MD5(ZT_HASH128* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			static ZT_U8 lBuffer[64];
			static ZT_U32 lCounter[2];
			ZTM_HashMD5_Init(iHash, lCounter);
			ZTM_HashMD5_Feed(iHash, lCounter, lBuffer, iData->byte, iData->length);
			ZTM_HashMD5_Finish(iHash, lCounter, lBuffer);
		}
	}
}
void ZTM_HashData_DJB2(ZT_HASH32* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->data[0] = 0x1505;
			ZT_SIZE lIndex = -1;
			while (++lIndex < iData->length) {iHash->data[0] = ((iHash->data[0] << 5) + iHash->data[0]) + iData->byte[lIndex];}
		}
	}
}
void ZTM_HashData_DJB2A(ZT_HASH32* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->data[0] = 0x1505;
			ZT_SIZE lIndex = -1;
			while (++lIndex < iData->length) {iHash->data[0] = (((iHash->data[0] << 5) + iHash->data[0])) ^ iData->byte[lIndex];}
		}
	}
}
void ZTM_HashData_SDBM_32(ZT_HASH32* iHash, const ZT_DATA* iData) { // still not sure if this right...
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->data[0] = 0x0;
			ZT_INDEX lIndex = -1;
			while (++lIndex < iData->length) {iHash->data[0] = iData->byte[lIndex] + (iHash->data[0] << 6) + (iHash->data[0] << 16) - iHash->data[0];}
		}
	}
}
void ZTM_HashData_SDBM_64(ZT_HASH64* iHash, const ZT_DATA* iData) { // still not sure if this right...
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->quad[0] = 0x0;
			ZT_INDEX lIndex = -1;
			while (++lIndex < iData->length) {iHash->quad[0] = iData->byte[lIndex] + (iHash->quad[0] << 6) + (iHash->quad[0] << 16) - iHash->quad[0];}
		}
	}
}
void ZTM_HashData_FNV0_32(ZT_HASH32* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->data[0] = 0x0;
			ZT_INDEX lIndex = -1;
			while (++lIndex < iData->length) {iHash->data[0] *= 0x1000193; iHash->data[0] = (iHash->data[0] ^ iData->byte[lIndex]);}
		}
	}
}
void ZTM_HashData_FNV0_64(ZT_HASH64* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->quad[0] = 0x0;
			ZT_INDEX lIndex = -1;
			while (++lIndex < iData->length) {iHash->quad[0] *= 0x100000001b3; iHash->quad[0] = (iHash->quad[0] ^ iData->byte[lIndex]);}
		}
	}
}
void ZTM_HashData_FNV1_32(ZT_HASH32* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->data[0] = 0x811c9dc5;
			ZT_INDEX lIndex = -1;
			while (++lIndex < iData->length) {iHash->data[0] *= 0x1000193; iHash->data[0] = (iHash->data[0] ^ iData->byte[lIndex]);}
		}
	}
}
void ZTM_HashData_FNV1_64(ZT_HASH64* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->quad[0] = 0xcbf29ce484222325;
			ZT_INDEX lIndex = -1;
			while (++lIndex < iData->length) {iHash->quad[0] *= 0x100000001b3; iHash->quad[0] = (iHash->quad[0] ^ iData->byte[lIndex]);}
		}
	}
}
void ZTM_HashData_FNV1A_32(ZT_HASH32* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->data[0] = 0x811c9dc5;
			ZT_INDEX lIndex = -1;
			while (++lIndex < iData->length) {iHash->data[0] = (iHash->data[0] ^ iData->byte[lIndex]); iHash->data[0] *= 0x1000193;}
		}
	}
}
void ZTM_HashData_FNV1A_64(ZT_HASH64* iHash, const ZT_DATA* iData) {
	if (iHash != NULL && iData != NULL) {
		if (iData->payload != NULL && iData->length) {
			iHash->quad[0] = 0xcbf29ce484222325;
			ZT_INDEX lIndex = -1;
			while (++lIndex < iData->length) {iHash->quad[0] = (iHash->quad[0] ^ iData->byte[lIndex]); iHash->quad[0] *= 0x100000001b3;}
		}
	}
}

#define ZTM_HASHTEXT(HASH) \
	ZT_DATA lData;\
	if (iHash != NULL && (lData.payload = (void*)iText) != NULL) {\
		if ((lData.length = ZTC8_GetLength(iText))) {HASH(iHash, &lData);}\
	}
void ZTM_HashText_128(ZT_HASH128* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_128);}
void ZTM_HashText_MD5(ZT_HASH128* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_MD5);}
void ZTM_HashText_DJB2(ZT_HASH32* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_DJB2);}
void ZTM_HashText_DJB2A(ZT_HASH32* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_DJB2A);}
void ZTM_HashText_SDBM_32(ZT_HASH32* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_SDBM_32);}
void ZTM_HashText_SDBM_64(ZT_HASH64* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_SDBM_64);}
void ZTM_HashText_FNV0_32(ZT_HASH32* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_FNV0_32);}
void ZTM_HashText_FNV0_64(ZT_HASH64* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_FNV0_64);}
void ZTM_HashText_FNV1_32(ZT_HASH32* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_FNV1_32);}
void ZTM_HashText_FNV1_64(ZT_HASH64* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_FNV1_64);}
void ZTM_HashText_FNV1A_32(ZT_HASH32* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_FNV1A_32);}
void ZTM_HashText_FNV1A_64(ZT_HASH64* iHash, const ZT_CHAR* iText) {ZTM_HASHTEXT(ZTM_HashData_FNV1A_64);}

#define ZTM_HASHTEXTNEW(TYPE,NEW,HASH) \
	ZT_DATA lData;\
	if ((lData.payload = (void*)iText) != NULL) {\
		if ((lData.length = ZTC8_GetLength(iText))) {\
			TYPE* lHash;\
			if ((lHash = NEW()) != NULL) {HASH(lHash, &lData); return lHash;}\
		}\
	}\
	return NULL
ZT_HASH128* ZTM_HashTextNew_128(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH128, ZTM_HashNew_128, ZTM_HashData_128);}
ZT_HASH128* ZTM_HashTextNew_MD5(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH128, ZTM_HashNew_128, ZTM_HashData_MD5);}
ZT_HASH32* ZTM_HashTextNew_DJB2(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH32, ZTM_HashNew_32, ZTM_HashData_DJB2);}
ZT_HASH32* ZTM_HashTextNew_DJB2A(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH32, ZTM_HashNew_32, ZTM_HashData_DJB2A);}
ZT_HASH32* ZTM_HashTextNew_SDBM_32(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH32, ZTM_HashNew_32, ZTM_HashData_SDBM_32);}
ZT_HASH64* ZTM_HashTextNew_SDBM_64(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH64, ZTM_HashNew_64, ZTM_HashData_SDBM_64);}
ZT_HASH32* ZTM_HashTextNew_FNV0_32(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH32, ZTM_HashNew_32, ZTM_HashData_FNV0_32);}
ZT_HASH64* ZTM_HashTextNew_FNV0_64(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH64, ZTM_HashNew_64, ZTM_HashData_FNV0_64);}
ZT_HASH32* ZTM_HashTextNew_FNV1_32(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH32, ZTM_HashNew_32, ZTM_HashData_FNV1_32);}
ZT_HASH64* ZTM_HashTextNew_FNV1_64(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH64, ZTM_HashNew_64, ZTM_HashData_FNV1_64);}
ZT_HASH32* ZTM_HashTextNew_FNV1A_32(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH32, ZTM_HashNew_32, ZTM_HashData_FNV1A_32);}
ZT_HASH64* ZTM_HashTextNew_FNV1A_64(const ZT_CHAR* iText) {ZTM_HASHTEXTNEW(ZT_HASH64, ZTM_HashNew_64, ZTM_HashData_FNV1A_64);}

#endif // ZT_HASH_C_INCLUDED
