/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_C_INCLUDED
#define ZTM_C_INCLUDED

#include "ZTM__Runtime.h"
#include ZTM__INCL__MAIN

void ZTM_SRand(ZT_U32 iSeed) {rZTM__SEED = iSeed;}
ZT_U32 ZTM_Rand(ZT_U32 iModulo) {
	rZTM__SEED ^= rZTM__SEED << 13;
	rZTM__SEED ^= rZTM__SEED >> 17;
	rZTM__SEED ^= rZTM__SEED << 5;
	return (iModulo ? (rZTM__SEED % iModulo) : rZTM__SEED);
}
ZT_FLAG ZTM_LSB(ZT_FLAG iFlag) {
    ZT_FLAG lMask = 0x0;
    ZT_INDEX lIndex = -1;
    while ((!(lMask = (iFlag & ((ZT_FLAG)0x1 << ++lIndex)))) && ((ZT_FLAG)0x1 << lIndex));
    return lMask;
}
ZT_FLAG ZTM_MSB(ZT_FLAG iFlag) {
    ZT_FLAG lMask = 0x0;
    ZT_INDEX lIndex = -1;
    while ((!(lMask = iFlag & (~(((ZT_FLAG)~0x0) >> ((++lIndex) + 1))))) && ((ZT_FLAG)0x1 << lIndex));
    return lMask;
}
ZT_FLAG ZTM_BitFillLeft(ZT_INDEX iCount) {
    ZT_FLAG lMask = 0x0;
    ZT_INDEX lIndex = -1;
    while((++lIndex < iCount) && ((ZT_FLAG)0x1 << lIndex)) {lMask <<= 1; lMask |= 0x1;}
    return lMask;
}
ZT_FLAG ZTM_BitFillRight(ZT_INDEX iCount) {
    ZT_FLAG lMask = 0x0;
    ZT_FLAG lMSB = ~((ZT_FLAG)~0x0 >> 1);
    ZT_INDEX lIndex = -1;
    while((++lIndex < iCount) && ((ZT_FLAG)0x1 << lIndex)) {lMask >>= 1; lMask |= lMSB;}
    return lMask;
}
ZT_INDEX ZTM_BitCount(ZT_FLAG iFlag) {
    ZT_FLAG lMask;
    ZT_INDEX lBits = 0;
    ZT_INDEX lIndex = -1;
    while ((lMask = (ZT_FLAG)0x1 << (++lIndex))) {if (iFlag & lMask) {++lBits;}}
    return lBits;
}
ZT_INDEX ZTM_BitIndex(ZT_FLAG iFlag) {ZT_INDEX lBitIndex = -1; while (!((iFlag >> ++lBitIndex) & 0x1) && ((ZT_FLAG)0x1 << lBitIndex)); return lBitIndex;}
ZT_INDEX ZTM_BitFlagIndex(ZT_FLAG iFlag) {ZT_INDEX lBitIndex = -1; while (!((iFlag >> ++lBitIndex) & 0x1) && ((ZT_FLAG)0x1 << lBitIndex)); return (((ZT_FLAG)0x1 << lBitIndex) ? ++lBitIndex : 0);}
#define ZTM_BYTECOMPARISON(SAMPLE,REFERENCE,OPERATION) \
    ZT_FLAG lResults = 0x0;\
    ZT_INDEX lByteMask;\
    ZT_INDEX lIndexByte = -1;\
    while ((lByteMask = (0xff << ((++lIndexByte) << 3)))) {\
        lResults |= ((((SAMPLE & lByteMask) OPERATION (REFERENCE & lByteMask)) ? 0x01010101 : 0x0) & lByteMask);\
    }\
    return lResults
ZT_FLAG ZTM_ByteLess(ZT_FLAG iInput, ZT_FLAG iReference) {ZTM_BYTECOMPARISON(iInput, iReference, <);}
ZT_FLAG ZTM_ByteLessEqual(ZT_FLAG iInput, ZT_FLAG iReference) {ZTM_BYTECOMPARISON(iInput, iReference, <=);}
ZT_FLAG ZTM_ByteGreater(ZT_FLAG iInput, ZT_FLAG iReference) {ZTM_BYTECOMPARISON(iInput, iReference, >);}
ZT_FLAG ZTM_ByteGreaterEqual(ZT_FLAG iInput, ZT_FLAG iReference) {ZTM_BYTECOMPARISON(iInput, iReference, >=);}
ZT_FLAG ZTM_ByteOffset(ZT_FLAG iInput, ZT_FLAG iReference) {
    ZT_FLAG lOffset = 0x0;
    ZT_FLAG lByte;
    ZT_FLAG lReference;
    ZT_INDEX lIndex = -1;
    ZT_INDEX lShift;
    while (0xff << (lShift = ((++lIndex) << 3))) {
        lByte = ((iInput >> lShift) & 0xff);
        lReference = ((iReference >> lShift) & 0xff);
        if (lByte < iReference) {
            lOffset |= (lReference - lByte) << lShift;
        } else {
            lOffset |= (lByte - lReference) << lShift;
        }
    }
    return lOffset;
}
#define ZTM_BYTEOPERATION(INPUT,OPERAND,OPERATION) \
    ZT_INDEX lResult = 0;\
    ZT_INDEX lIndexByte = -1;\
    ZT_INDEX lIndexShift;\
    while (0xff << (lIndexShift = ((++lIndexByte) << 3))) {\
        lResult |= (((((INPUT >> lIndexShift) & 0xff) OPERATION ((OPERAND >> lIndexShift) & 0xff)) % 0x100) << lIndexShift);\
    }\
    return lResult
ZT_FLAG ZTM_ByteAdd(ZT_FLAG iInput, ZT_FLAG iOperand) {ZTM_BYTEOPERATION(iInput, iOperand, +);}
ZT_FLAG ZTM_ByteSubtract(ZT_FLAG iInput, ZT_FLAG iOperand) {ZTM_BYTEOPERATION(iInput, iOperand, -);}
ZT_FLAG ZTM_ByteMultiply(ZT_FLAG iInput, ZT_FLAG iOperand) {ZTM_BYTEOPERATION(iInput, iOperand, *);}
ZT_FLAG ZTM_ByteDivide(ZT_FLAG iInput, ZT_FLAG iOperand) {ZTM_BYTEOPERATION(iInput, iOperand, /);}
ZT_INDEX ZTM_ByteSum(ZT_FLAG iFlag) {
    ZT_INDEX lSum = 0;
    ZT_INDEX lShift;
    ZT_INDEX lIndex = -1;
    while (0xff << (lShift = ((++lIndex) << 3))) {lSum += ((iFlag >> lShift) & 0xff);}
    return lSum;
}
ZT_FLAG ZTM_ByteMirror(ZT_FLAG iInput) {return ((iInput << 24) | (iInput >> 24) | ((iInput & 0xff00) << 8) | ((iInput >> 8) & 0xff00));}
ZT_U ZTM_Exp(ZT_INDEX iMagnitude) {ZT_INDEX lIndex = -1; ZT_U lFactor = 1; while ((0x1 << ++lIndex) && (lIndex < iMagnitude)) {lFactor *= 10;} return lFactor;}
ZT_INDEX ZTM_Magnitude(ZT_U iInteger) {ZT_INDEX lIndex = -1; while ((0x1 << ++lIndex) && (iInteger /= 10)); return lIndex;}
ZT_INDEX ZTM_MagnitudeSigned(ZT_I iInteger) {return ZTM_Magnitude((iInteger < 0) ? -iInteger : iInteger);}
#ifndef ZTM_POINT_MACRO
void ZTM_UPoint(ZT_UPOINT* oPoint, const ZT_U iX, const ZT_U iY) {oPoint->xU = iX; oPoint->yU = iY;}
ZT_U ZTM_UPointArea(const ZT_UPOINT* iUPoint) {return (iUPoint->xU * iUPoint->yU);}
void ZTM_Point(ZT_POINT* oPoint, const ZT_I iX, const ZT_I iY) {oPoint->x = iX; oPoint->y = iY;}
void ZTM_PointCopy(const ZT_POINT* iSource, ZT_POINT* oTarget) {oTarget->x = iSource->x; oTarget->y = iSource->y;}
void ZTM_PointZero(ZT_POINT* oPoint) {oPoint->x = 0; oPoint->y = 0;}
ZT_I ZTM_PointArea(const ZT_POINT* iPoint) {return (iPoint->x * iPoint->y);}
ZT_BOOL ZTM_PointIsNotZero(const ZT_POINT* iPoint) {return (iPoint->x || iPoint->y);}
#endif // ZTM_POINT_MACRO
ZT_BOOL ZTM_PointWithinRect(const ZT_POINT* iPoint, const ZT_RECT* iRect) {
	if (iPoint->x >= iRect->x) {if (iPoint->x < iRect->x + iRect->w) {if (iPoint->y >= iRect->y) {if (iPoint->y < iRect->y + iRect->h) {return ZT_TRUE;}}}} return ZT_FALSE;
}
#ifndef ZTM_RECT_MACRO
void ZTM_Rect(ZT_RECT* oRect, const ZT_I iX, const ZT_I iY, const ZT_I iW, const ZT_I iH) {oRect->x = iX; oRect->y = iY; oRect->w = iW; oRect->h = iH;}
void ZTM_RectZero(ZT_RECT* oRect) {oRect->x = 0; oRect->y = 0; oRect->w = 0; oRect->h = 0;}
void ZTM_RectZeroPos(ZT_RECT* oRect) {oRect->x = 0; oRect->y = 0;}
void ZTM_RectZeroSize(ZT_RECT* oRect) {oRect->w = 0; oRect->h = 0;}
void ZTM_RectCopy(const ZT_RECT* iSource, ZT_RECT* oTarget) {oTarget->x = iSource->x; oTarget->y = iSource->y; oTarget->w = iSource->w; oTarget->h = iSource->h;}
void ZTM_RectCopyPos(const ZT_RECT* iSource, ZT_RECT* oTarget) {oTarget->x = iSource->x; oTarget->y = iSource->y;}
void ZTM_RectCopySize(const ZT_RECT* iSource, ZT_RECT* oTarget) {oTarget->w = iSource->w; oTarget->h = iSource->h;}
void ZTM_RectPos(ZT_RECT* oRect, const ZT_POINT* iPos) {oRect->x = iPos->x; oRect->y = iPos->y;}
void ZTM_RectPosFromIntegers(ZT_RECT* oRect, const ZT_I iX, const ZT_I iY) {oRect->x = iX; oRect->y = iY;}
void ZTM_RectSize(ZT_RECT* oRect, const ZT_POINT* iSize) {oRect->w = iSize->x; oRect->h = iSize->y;}
void ZTM_RectSizeFromIntegers(ZT_RECT* oRect, const ZT_I iW, const ZT_I iH) {oRect->w = iW; oRect->h = iH;}
void ZTM_RectPosIntoPoint(const ZT_RECT* iRect, ZT_POINT* oPos) {oPos->x = iRect->x; oPos->y = iRect->y;}
void ZTM_RectPosIntoPointers(const ZT_RECT* iRect, ZT_I* oX, ZT_I* oY) {*oX = iRect->x; *oY = iRect->y;}
void ZTM_RectSizeIntoPoint(const ZT_RECT* iRect, ZT_POINT* oSize) {oSize->x = iRect->w; oSize->y = iRect->h;}
void ZTM_RectSizeIntoPointers(const ZT_RECT* iRect, ZT_I* oWidth, ZT_I* oHeight) {*oWidth = iRect->w; *oHeight = iRect->h;}
ZT_I ZTM_RectArea(const ZT_RECT* iRect) {return (iRect->w * iRect->h);}
#endif // ZTM_RECT_MACRO
void ZTM_RectClipFromOriginToPoint(ZT_RECT* ioRect, const ZT_POINT* iSize) { // rect clip size?
    if (ioRect->x < 0) {ioRect->w += ioRect->x; ioRect->x = 0;} else {if (ioRect->x > iSize->x) {ioRect->x = iSize->x;}}
    if (ioRect->y < 0) {ioRect->y += ioRect->y; ioRect->y = 0;} else {if (ioRect->y > iSize->y) {ioRect->y = iSize->y;}}
    if (iSize->x - ioRect->x < ioRect->w) {ioRect->w = iSize->x - ioRect->x;}
    if (iSize->y - ioRect->y < ioRect->h) {ioRect->h = iSize->y - ioRect->y;}
}
#ifndef ZTM_MALLOC_MACRO
void ZTM8_Free(void* iData) {free(iData);}
void* ZTM8_New(ZT_INDEX iLength) {return malloc(iLength);}
void* ZTM8_Resize(void* iData, ZT_INDEX iLength) {return realloc(iData, iLength);}
void* ZTM8_Zero(void* iData, ZT_INDEX iLength)  {ZT_INDEX i = ~0; while (++i < iLength) {((ZT_U8*)iData)[i] = 0x0;} return iData;}
void* ZTM8_Set(void* iData, ZT_U8 iValue, ZT_INDEX iLength) {ZT_INDEX i = ~0; while (++i < iLength) {((ZT_U8*)iData)[i] = iValue;} return iData;}
void* ZTM8_Init(ZT_INDEX iLength, ZT_U8 iValue) {return ZTM8_Set(malloc(iLength), iValue, iLength);}
void* ZTM8_Copy(const void* iSource, void* oTarget, ZT_INDEX iLength) {ZT_INDEX lCursor = ~0; while (++lCursor < iLength) {((ZT_U8*)oTarget)[lCursor] = ((ZT_U8*)iSource)[lCursor];} return oTarget;}
void* ZTM8_Move(void* iSource, void* oTarget, ZT_INDEX iLength) {ZTM8_Copy(iSource, oTarget, iLength); ZTM8_Free(iSource); return oTarget;}
void ZTM32_Free(void* iData) {free(iData);}
void* ZTM32_New(ZT_INDEX iLength) {return malloc(iLength << 2);}
void* ZTM32_Resize(void* iData, ZT_INDEX iLength) {return realloc(iData, iLength << 2);}
void* ZTM32_Copy(const void* iSource, void* oTarget, ZT_INDEX iLength) {ZT_INDEX lCursor = ~0; while (++lCursor < iLength) {((ZT_U32*)oTarget)[lCursor] = ((ZT_U32*)iSource)[lCursor];} return oTarget;}
void* ZTM32_Move(void* iSource, void* oTarget, ZT_INDEX iLength) {ZTM32_Copy(iSource, oTarget, iLength); ZTM32_Free(iSource); return oTarget;}
void* ZTM32_Zero(void* iData, ZT_INDEX iLength)  {ZT_INDEX i = ~0; while (++i < iLength) {((ZT_U32*)iData)[i] = 0x0;} return iData;}
void* ZTM32_Set(void* iData, ZT_U32 iValue, ZT_INDEX iLength) {ZT_INDEX i = ~0; while (++i < iLength) {((ZT_U32*)iData)[i] = iValue;} return iData;}
void* ZTM32_Init(ZT_INDEX iLength, ZT_U32 iValue) {return ZTM32_Set(malloc(iLength << 2), iValue, iLength);}
void* ZTM32_NewBlock(const ZT_UPOINT* iBlockSize) {return malloc((iBlockSize->xU * iBlockSize->yU) << 2);}
void* ZTM32_ResizeBlock(void* iData, const ZT_UPOINT* iBlockSize) {return realloc(iData, (iBlockSize->xU * iBlockSize->yU) << 2);}
void* ZTM32_CopyBlock(const void* iSource, void* oTarget, const ZT_UPOINT* iBlockSize) {ZT_INDEX lLength = (iBlockSize->xU * iBlockSize->yU); ZT_INDEX lCursor = ~0; while (++lCursor < lLength) {((ZT_U32*)oTarget)[lCursor] = ((ZT_U32*)iSource)[lCursor];} return oTarget;}
void* ZTM32_MoveBlock(void* iSource, void* oTarget, const ZT_UPOINT* iBlockSize) {ZTM32_CopyBlock(iSource, oTarget, iBlockSize); ZTM32_Free(iSource); return oTarget;}
void* ZTM32_SetBlock(void* iData, ZT_U32 iValue, const ZT_UPOINT* iBlockSize) {return ZTM32_Set(iData, iValue, (iBlockSize->xU * iBlockSize->yU));}
void* ZTM32_InitBlock(const ZT_UPOINT* iBlockSize, ZT_U32 iValue) {return ZTM32_Set(malloc((iBlockSize->xU * iBlockSize->yU) << 2), iValue, (iBlockSize->xU * iBlockSize->yU));}
#else
#define ZTM_FREE(DATA) free(DATA)
#define ZTM_NEW(LENGTH,UNIT) malloc(LENGTH * sizeof(UNIT))
#define ZTM_RESIZE(DATA,LENGTH,UNIT) realloc(DATA,LENGTH * sizeof(UNIT))
#define ZTM_ZERO(DATA,LENGTH,UNIT) ({ZT_INDEX rZERO_i = -1; while (++rZERO_i < (LENGTH)) {((UNIT*)(DATA))[rZERO_i] = 0x0;} (DATA);})
#define ZTM_COPY(SOURCE,TARGET,LENGTH,UNIT) ({ZT_INDEX rCOPY_i = -1; while (++rCOPY_i < (LENGTH)) {((UNIT*)(TARGET))[rCOPY_i] = ((UNIT*)(SOURCE))[rCOPY_i];} (TARGET);})
#define ZTM_SET(DATA,VALUE,LENGTH,UNIT) ({ZT_INDEX rSET_i = -1; while (++rSET_i < (LENGTH)) {((UNIT*)(DATA))[rSET_i] = VALUE;} (DATA);})
#define ZTM_INIT(LENGTH,VALUE,UNIT) ({void* rINIT_data = ZTM_NEW(LENGTH,UNIT); ZTM_SET(rINIT_data,VALUE,LENGTH,UNIT); rINIT_data;})
#define ZTM_MOVE(SOURCE,TARGET,LENGTH,UNIT) ({ZTM_COPY(SOURCE,TARGET,LENGTH,UNIT); ZTM_FREE(SOURCE); (TARGET);})
void ZTM8_Free(void* iData) {ZTM_FREE(iData);}
void* ZTM8_New(ZT_INDEX iLength) {return ZTM_NEW(iLength, ZT_U8);}
void* ZTM8_Resize(void* iData, ZT_INDEX iLength) {return ZTM_RESIZE(iData, iLength, ZT_U8);}
void* ZTM8_Zero(void* iData, ZT_INDEX iLength)  {return ZTM_ZERO(iData, iLength, ZT_U8);}
void* ZTM8_Set(void* iData, ZT_U8 iValue, ZT_INDEX iLength) {return ZTM_SET(iData, iValue, iLength, ZT_U8);}
void* ZTM8_Init(ZT_INDEX iLength, ZT_U8 iValue) {return ZTM_INIT(iLength, iValue, ZT_U8);}
void* ZTM8_Copy(const void* iSource, void* oTarget, ZT_INDEX iLength) {return ZTM_COPY(iSource, oTarget, iLength, ZT_U8);}
void* ZTM8_Move(void* iSource, void* oTarget, ZT_INDEX iLength) {return ZTM_MOVE(iSource, oTarget, iLength, ZT_U8);}
void ZTM32_Free(void* iData) {ZTM_FREE(iData);}
void* ZTM32_New(ZT_INDEX iLength) {return ZTM_NEW(iLength, ZT_U32);}
void* ZTM32_Resize(void* iData, ZT_INDEX iLength) {return ZTM_RESIZE(iData, iLength, ZT_U32);}
void* ZTM32_Zero(void* iData, ZT_INDEX iLength)  {return ZTM_ZERO(iData, iLength, ZT_U32);}
void* ZTM32_Set(void* iData, ZT_U32 iValue, ZT_INDEX iLength) {return ZTM_SET(iData, iValue, iLength, ZT_U32);}
void* ZTM32_Init(ZT_INDEX iLength, ZT_U32 iValue) {return ZTM_INIT(iLength, iValue, ZT_U32);}
void* ZTM32_Copy(const void* iSource, void* oTarget, ZT_INDEX iLength) {return ZTM_COPY(iSource, oTarget, iLength, ZT_U32);}
void* ZTM32_Move(void* iSource, void* oTarget, ZT_INDEX iLength) {return ZTM_MOVE(iSource, oTarget, iLength, ZT_U32);}
void* ZTM32_NewBlock(const ZT_UPOINT* iSize) {return ZTM_NEW((iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_ResizeBlock(void* iData, const ZT_UPOINT* iSize) {return ZTM_RESIZE(iData, (iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_CopyBlock(const void* iSource, void* oTarget, const ZT_UPOINT* iSize) {return ZTM_COPY(iSource, oTarget, (iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_MoveBlock(void* iSource, void* oTarget, const ZT_UPOINT* iSize) {return ZTM_MOVE(iSource, oTarget, (iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_SetBlock(void* iData, ZT_U32 iValue, const ZT_UPOINT* iSize) {return ZTM_SET(iData, iValue, (iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_InitBlock(const ZT_UPOINT* iSize, ZT_U32 iValue) {return ZTM_INIT((iSize->xU * iSize->yU), iValue, ZT_U32);}
#endif // ZTM_MALLOC_MACRO
ZT_BOOL ZTM8_Match(const void* iSource, const void* iTarget, ZT_INDEX iLength) {
    ZT_INDEX lIndex = -1;
    while (++lIndex < iLength) {if (((const ZT_U8*)iTarget)[lIndex] != ((const ZT_U8*)iSource)[lIndex]) {return ZT_FALSE;}}
    return ZT_TRUE;
}
/*void ZTM8_DataFree(ZT_DATA_U8* iData) {
	if (iData != NULL) {ZTM8_Free(iData->payload);}
}
ZT_DATA_U8* ZTM8_DataNull(ZT_DATA_U8* iData) {
	if (iData != NULL) {
		iData->payload = NULL;
		iData->length = 0;
	}
	return iData;
}
ZT_DATA_U8* ZTM8_DataZero(ZT_DATA_U8* iData) {
	if (iData != NULL) {
		ZTM8_Zero(iData->payload, iData->length);
		iData->length = 0;
	}
	return iData;
}*/
ZT_DATA* ZTM_DataNew(ZT_SIZE iLength) {
	ZT_DATA* lData;
	if ((lData = ZTM8_New(sizeof(ZT_DATA))) != NULL) {
		if ((lData->length = iLength)) {
			if ((lData->byte = ZTM8_New(lData->length)) != NULL) {return lData;}
			ZTM8_Free(lData);
		} else {
			lData->payload = NULL;
			return lData;
		}
	}
    return NULL;
}
ZT_DATA* ZTM_DataNewCopy(const ZT_U8* iData, ZT_SIZE iLength) {
	if (iData != NULL) {
		ZT_DATA* lData;
		if ((lData = ZTM_DataNew(iLength)) != NULL) {
			ZTM8_Copy(iData, lData->byte, iLength);
			return lData;
		}
	}
	return NULL;
}
ZT_DATA* ZTM_DataNewWrap(ZT_U8* iData, ZT_SIZE iLength) {
	if (iData != NULL) {
		ZT_DATA* lData;
		if ((lData = ZTM_DataNew(0)) != NULL) {
			lData->payload = iData;
			lData->length = iLength;
			return lData;
		}
	}
	return NULL;
}
void ZTM_DataFreePayloadSecure(ZT_DATA* iData) {
    if (iData != NULL) {
		ZTM8_Zero(iData->payload, iData->length);
        ZTM_FreeNull(iData->payload);
		iData->length = 0;
    }
}
void ZTM_DataFreeSecure(ZT_DATA* iData) {
    if (iData != NULL) {
		ZTM8_Zero(iData->payload, iData->length);
        ZTM8_Free(iData->payload);
        ZTM8_Free(iData);
    }
}
void ZTM_DataFreePayload(ZT_DATA* iData) {
    if (iData != NULL) {
        ZTM_FreeNull(iData->payload);
		iData->length = 0;
    }
}
void ZTM_DataFreeWrap(ZT_DATA* iData) {
    if (iData != NULL) {
        ZTM8_Free(iData);
    }
}
void ZTM_DataFree(ZT_DATA* iData) {
    if (iData != NULL) {
        ZTM8_Free(iData->payload);
        ZTM8_Free(iData);
    }
}
#endif // ZTM_C_INCLUDED
