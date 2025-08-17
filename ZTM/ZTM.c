/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_C_INCLUDED
#define ZTM_C_INCLUDED

#include "ZTM__Runtime.h"
#include ZTM__INCL__MAIN

ZT_U32 ZTM_Seed_32(ZT_U32 iSeed) {
	ZT_U32 lCache = rZTM__SEED_32;
	rZTM__SEED_32 = iSeed;
	return lCache;
}
ZT_U32 ZTM_Random_32(ZT_U32 iModulo) {
	rZTM__SEED_32 ^= ~(rZTM__SEED_32 >> 25);
	rZTM__SEED_32 ^= ~(rZTM__SEED_32 << 7);
	rZTM__SEED_32 ^= ~(rZTM__SEED_32 << 19);
	return (iModulo ? (rZTM__SEED_32 % iModulo) : rZTM__SEED_32);
}
ZT_U32 ZTM_Randomize_32(ZT_U32* ioSeed, ZT_U32 iModulo) {
	*ioSeed ^= ~(*ioSeed >> 25);
	*ioSeed ^= ~(*ioSeed << 7);
	*ioSeed ^= ~(*ioSeed << 19);
	return (iModulo ? (*ioSeed % iModulo) : *ioSeed);
}
ZT_U64 ZTM_Seed_64(ZT_U64 iSeed) {
	ZT_U64 lCache = rZTM__SEED_64;
	rZTM__SEED_64 = iSeed;
	return lCache;
}
ZT_U64 ZTM_Random_64(ZT_U64 iModulo) {
	rZTM__SEED_64 ^= ~(rZTM__SEED_64 >> 51);
	rZTM__SEED_64 ^= ~(rZTM__SEED_64 << 13);
	rZTM__SEED_64 ^= ~(rZTM__SEED_64 << 29);
	return (iModulo ? (rZTM__SEED_64 % iModulo) : rZTM__SEED_64);
}
ZT_U64 ZTM_Randomize_64(ZT_U64* ioSeed, ZT_U64 iModulo) {
	*ioSeed ^= ~(*ioSeed >> 51);
	*ioSeed ^= ~(*ioSeed << 13);
	*ioSeed ^= ~(*ioSeed << 29);
	return (iModulo ? (*ioSeed % iModulo) : *ioSeed);
}
ZT_FLAG ZTM_LSB(ZT_FLAG iFlag) {
	// inb4 vectorizing all this and if else if sizeof(ZT_FLAG), etc.
    ZT_FLAG lBit = iFlag ? 0x1u : 0x0u; // TODO test me
    while (!(iFlag & lBit) && (lBit <<= 1));
    return lBit;
}
ZT_FLAG ZTM_MSB(ZT_FLAG iFlag) {
    ZT_FLAG lBit = iFlag ? ~((ZT_FLAG)~0x0u >> 1) : 0x0u;
    while (!(iFlag & lBit) && (lBit >>= 1));
    return lBit;
}
ZT_FLAG ZTM_BitFillLeft(ZT_INDEX iCount) { //NOTE left *shift*, not origin
    ///safe, but slow:
    //ZT_FLAG lIndex = ~0x0;
    //++iCount;
    //while (--iCount && (lIndex <<= 1));
    //return ~lIndex;
    ///warning: signed and unsigned type in conditional expression [-Wsign-compare]: // D25229: seems to have disappeared with newer GCC?
    return (iCount < (sizeof(ZT_FLAG) << 3)) ? ~(((ZT_FLAG)~0x0u) << iCount) : (ZT_FLAG)~0x0u;
    ///no warnings with this(?):
    //if (iCount < (sizeof(ZT_FLAG) << 3)) {return ~(((ZT_FLAG)~0x0) << iCount);} else {return ~0x0;}
}
ZT_FLAG ZTM_BitFillRight(ZT_INDEX iCount) {
    ///safe, but slow:
    //ZT_FLAG lIndex = ~0x0;
    //++iCount;
    //while (--iCount && (lIndex >>= 1));
    //return ~lIndex;
    ///warning: signed and unsigned type in conditional expression [-Wsign-compare]: // D25229: seems to have disappeared with newer GCC?
    return (iCount < (sizeof(ZT_FLAG) << 3)) ? ~(((ZT_FLAG)~0x0u) >> iCount) : (ZT_FLAG)~0x0u;
    ///no warnings with this(?):
    //if (iCount < (sizeof(ZT_FLAG) << 3)) {return ~(((ZT_FLAG)~0x0) >> iCount);} else {return ~0x0;}
}
ZT_INDEX ZTM_BitCount(ZT_FLAG iFlag) {
    ZT_INDEX lBits = 0;
    do {if (iFlag & 0x1u) {++lBits;}} while (iFlag >>= 1);
    return lBits;
}
ZT_INDEX ZTM_BitIndex(ZT_FLAG iFlag) {
    ZT_INDEX lBitIndex = -1;
    do {++lBitIndex; if (iFlag & 0x1u) {return lBitIndex;}} while (iFlag >>= 1);
    return (sizeof(ZT_FLAG) << 3);
}
ZT_INDEX ZTM_BitIndexIndex(ZT_FLAG iFlag, ZT_INDEX iIndex) {
    ZT_INDEX lBitIndex = -1;
    do {++lBitIndex; if (iFlag & 0x1u) {if (iIndex) {--iIndex;} else {return lBitIndex;}}} while (iFlag >>= 1);
    return (sizeof(ZT_FLAG) << 3);
}
ZT_INDEX ZTM_BitIndexFlag(ZT_FLAG iFlag, ZT_FLAG iBit) {
    ZT_FLAG lMatch;
    if ((lMatch = iFlag & iBit)) {
        ZT_FLAG lBit = 0x1u;
        ZT_INDEX lBitIndex = 0;
        do {if (lMatch & lBit) {return lBitIndex;} else if (iFlag & lBit) {++lBitIndex;}} while (lBit <<= 1);
    }
    return (sizeof(ZT_FLAG) << 3);
}
ZT_INDEX ZTM_BitFlagIndex(ZT_FLAG iFlag) {
    ZT_INDEX lBitIndex = 0;
    do {++lBitIndex; if (iFlag & 0x1u) {return lBitIndex;}} while (iFlag >>= 1);
    return 0;
}
ZT_FLAG ZTM_ByteOffset(ZT_FLAG iInput, ZT_FLAG iReference) {
    ZT_FLAG lOffset = 0x0u;
    ZT_FLAG lByte;
    ZT_FLAG lReference;
    ZT_FLAG lIndex = 0xffu;
    do {lOffset |= ((lByte = iInput & lIndex) < (lReference = iReference & lIndex)) ? (lReference - lByte) : (lByte - lReference);} while (lIndex <<= 8);
    return lOffset;
}
ZT_INDEX ZTM_ByteSum(ZT_FLAG iFlag) {
    ZT_INDEX lSum = 0;
    do {lSum += iFlag & 0xffu;} while (iFlag >>= 8);
    return lSum;
}
ZT_FLAG ZTM_ByteMirror(ZT_FLAG iInput) {
    ZT_FLAG lUpper = ~((ZT_FLAG)~0x0u >> 8);
    ZT_FLAG lLower = 0xffu;
    ZT_INDEX lCount = 0;
    ZT_FLAG lMirror = 0x0;
    do {
        lMirror |= (iInput & lLower) << (((sizeof(ZT_FLAG) - 1) << 3) - (lCount << 4));
        lMirror |= (iInput & lUpper) >> (((sizeof(ZT_FLAG) - 1) << 3) - (lCount << 4));
        lLower <<= 8;
        lUpper >>= 8;
    } while (++lCount < (sizeof(ZT_FLAG) >> 1));
    return lMirror;
}
// need to be tested
#define ZTM_BYTECOMPARISON(SAMPLE,REFERENCE,OPERATION) \
    ZT_FLAG lResults = 0x0;\
    ZT_INDEX lByteMask;\
    ZT_INDEX lIndexByte = -1;\
    while ((lByteMask = ((ZT_FLAG)0xff << ((++lIndexByte) << 3)))) {\
        lResults |= ((((SAMPLE & lByteMask) OPERATION (REFERENCE & lByteMask)) ? 0x01010101 : 0x0) & lByteMask);\
    }\
    return lResults
ZT_FLAG ZTM_ByteLess(ZT_FLAG iInput, ZT_FLAG iReference) {ZTM_BYTECOMPARISON(iInput, iReference, <);}
ZT_FLAG ZTM_ByteLessEqual(ZT_FLAG iInput, ZT_FLAG iReference) {ZTM_BYTECOMPARISON(iInput, iReference, <=);}
ZT_FLAG ZTM_ByteGreater(ZT_FLAG iInput, ZT_FLAG iReference) {ZTM_BYTECOMPARISON(iInput, iReference, >);}
ZT_FLAG ZTM_ByteGreaterEqual(ZT_FLAG iInput, ZT_FLAG iReference) {ZTM_BYTECOMPARISON(iInput, iReference, >=);}
// need to be tested
#define ZTM_BYTEOPERATION(INPUT,OPERAND,OPERATION) \
    ZT_INDEX lResult = 0x0;\
    ZT_INDEX lIndexByte = -1;\
    ZT_INDEX lIndexShift;\
    while (((ZT_FLAG)0xff << (lIndexShift = ((++lIndexByte) << 3)))) {\
        lResult |= (((((INPUT >> lIndexShift) & 0xff) OPERATION ((OPERAND >> lIndexShift) & 0xff)) % 0x100) << lIndexShift);\
    }\
    return lResult
ZT_FLAG ZTM_ByteAdd(ZT_FLAG iInput, ZT_FLAG iOperand) {ZTM_BYTEOPERATION(iInput, iOperand, +);}
ZT_FLAG ZTM_ByteSubtract(ZT_FLAG iInput, ZT_FLAG iOperand) {ZTM_BYTEOPERATION(iInput, iOperand, -);}
ZT_FLAG ZTM_ByteMultiply(ZT_FLAG iInput, ZT_FLAG iOperand) {ZTM_BYTEOPERATION(iInput, iOperand, *);}
ZT_FLAG ZTM_ByteDivide(ZT_FLAG iInput, ZT_FLAG iOperand) {ZTM_BYTEOPERATION(iInput, iOperand, /);}

ZT_U ZTM_Exp(ZT_INDEX iMagnitude) {++iMagnitude; ZT_U lExp = 1u; while (--iMagnitude) {lExp *= 10u;} return lExp;}
ZT_INDEX ZTM_Magnitude(ZT_U iInteger) {ZT_INDEX lMag = 0u; while (iInteger /= 10u) {++lMag;} return lMag;}
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
ZT_BOOL ZTM_PointWithinRect(const ZT_POINT* iPoint, const ZT_RECT* iRect) {return ((iPoint->x >= iRect->x) && (iPoint->x < iRect->x + iRect->w) && (iPoint->y >= iRect->y) && (iPoint->y < iRect->y + iRect->h)) ? ZT_TRUE : ZT_FALSE;}
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
ZT_BOOL ZTM_RectIntersect(const ZT_RECT* iRect0, const ZT_RECT* iRect1, ZT_RECT* oIntersection) {
	ZT_I lL0 = iRect0->x;
	ZT_I lT0 = iRect0->y;
	ZT_I lR0 = lL0 + iRect0->w;
	ZT_I lB0 = lT0 + iRect0->h;
	ZT_I lL1 = iRect1->x;
	ZT_I lT1 = iRect1->y;
	ZT_I lR1 = lL1 + iRect1->w;
	ZT_I lB1 = lT1 + iRect1->h;
	if (lR0 <= lL1 || lR1 <= lL0) {
		return ZT_FALSE;
	} else if (lB0 <= lT1 || lB1 <= lT0) {
		return ZT_FALSE;
	} else {
		if (oIntersection != NULL) {
			oIntersection->w = ((lR1 > lR0) ? lR0 : lR1) - (oIntersection->x = (lL1 < lL0) ? lL0 : lL1);
			oIntersection->h = ((lB1 > lB0) ? lB0 : lB1) - (oIntersection->y = (lT1 < lT0) ? lT0 : lT1);
		}
		return ZT_TRUE;
	}
}
#define ZTM_FREE(DATA) free(DATA)
#define ZTM_NEW(LENGTH,UNIT) malloc((LENGTH) * sizeof(UNIT))
#define ZTM_RESIZE(DATA,LENGTH,UNIT) realloc((DATA),(LENGTH) * sizeof(UNIT))
#define ZTM_ZERO(DATA,LENGTH,UNIT) ({ZT_SIZE rZERO_i = -1; while (++rZERO_i < (LENGTH)) {((UNIT*)(DATA))[rZERO_i] = 0x0;} (DATA);})
#define ZTM_COPY(SOURCE,TARGET,LENGTH,UNIT) ({ZT_SIZE rCOPY_i = -1; while (++rCOPY_i < (LENGTH)) {((UNIT*)(TARGET))[rCOPY_i] = ((UNIT*)(SOURCE))[rCOPY_i];} (TARGET);})
#define ZTM_SET(DATA,VALUE,LENGTH,UNIT) ({ZT_SIZE rSET_i = -1; while (++rSET_i < (LENGTH)) {((UNIT*)(DATA))[rSET_i] = VALUE;} (DATA);})
#define ZTM_INIT(LENGTH,VALUE,UNIT) ({void* rINIT_data = ZTM_NEW(LENGTH,UNIT); ZTM_SET(rINIT_data,VALUE,LENGTH,UNIT); rINIT_data;})
#define ZTM_MOVE(SOURCE,TARGET,LENGTH,UNIT) ({ZTM_COPY(SOURCE,TARGET,LENGTH,UNIT); ZTM_FREE(SOURCE); (TARGET);})
void ZTM8_Free(void* iData) {ZTM_FREE(iData);}
void* ZTM8_New(ZT_SIZE iLength) {return ZTM_NEW(iLength, ZT_U8);}
void* ZTM8_Resize(void* iData, ZT_SIZE iLength) {return ZTM_RESIZE(iData, iLength, ZT_U8);}
void* ZTM8_Zero(void* iData, ZT_SIZE iLength)  {return ZTM_ZERO(iData, iLength, ZT_U8);}
void* ZTM8_Set(void* iData, ZT_U8 iValue, ZT_SIZE iLength) {return ZTM_SET(iData, iValue, iLength, ZT_U8);}
void* ZTM8_Init(ZT_SIZE iLength, ZT_U8 iValue) {return ZTM_INIT(iLength, iValue, ZT_U8);}
void* ZTM8_Copy(const void* iSource, void* oTarget, ZT_SIZE iLength) {return ZTM_COPY(iSource, oTarget, iLength, ZT_U8);}
void* ZTM8_Move(void* iSource, void* oTarget, ZT_SIZE iLength) {return ZTM_MOVE(iSource, oTarget, iLength, ZT_U8);}
void ZTM32_Free(void* iData) {ZTM_FREE(iData);}
void* ZTM32_New(ZT_SIZE iLength) {return ZTM_NEW(iLength, ZT_U32);}
void* ZTM32_Resize(void* iData, ZT_SIZE iLength) {return ZTM_RESIZE(iData, iLength, ZT_U32);}
void* ZTM32_Zero(void* iData, ZT_SIZE iLength)  {return ZTM_ZERO(iData, iLength, ZT_U32);}
void* ZTM32_Set(void* iData, ZT_U32 iValue, ZT_SIZE iLength) {return ZTM_SET(iData, iValue, iLength, ZT_U32);}
void* ZTM32_Init(ZT_SIZE iLength, ZT_U32 iValue) {return ZTM_INIT(iLength, iValue, ZT_U32);}
void* ZTM32_Copy(const void* iSource, void* oTarget, ZT_SIZE iLength) {return ZTM_COPY(iSource, oTarget, iLength, ZT_U32);}
void* ZTM32_Move(void* iSource, void* oTarget, ZT_SIZE iLength) {return ZTM_MOVE(iSource, oTarget, iLength, ZT_U32);}
void* ZTM32_NewBlock(const ZT_UPOINT* iSize) {return ZTM_NEW((iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_ResizeBlock(void* iData, const ZT_UPOINT* iSize) {return ZTM_RESIZE(iData, (iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_CopyBlock(const void* iSource, void* oTarget, const ZT_UPOINT* iSize) {return ZTM_COPY(iSource, oTarget, (iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_MoveBlock(void* iSource, void* oTarget, const ZT_UPOINT* iSize) {return ZTM_MOVE(iSource, oTarget, (iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_SetBlock(void* iData, ZT_U32 iValue, const ZT_UPOINT* iSize) {return ZTM_SET(iData, iValue, (iSize->xU * iSize->yU), ZT_U32);}
void* ZTM32_InitBlock(const ZT_UPOINT* iSize, ZT_U32 iValue) {return ZTM_INIT((iSize->xU * iSize->yU), iValue, ZT_U32);}
void* ZTM8_NewArray(ZT_SIZE iCount, ZT_SIZE iElement, ZT_SIZE iPadding, void** oList) {
	ZT_SIZE lLength = ((iElement % iPadding) ? (iElement + (iPadding - (iElement % iPadding))) : iElement);
	void* lMemory = ZTM_NEW(lLength * iCount, ZT_U8);
	if (oList != NULL) {for (ZT_SIZE i = 0; i < iCount; ++i) {oList[i] = lMemory + i * lLength;}}
	return lMemory;
}
ZT_BOOL ZTM8_Match(const void* iSource, const void* iTarget, ZT_SIZE iLength) {
    ZT_SIZE lIndex = -1;
    while (++lIndex < iLength) {if (((const ZT_U8*)iTarget)[lIndex] != ((const ZT_U8*)iSource)[lIndex]) {return ZT_FALSE;}}
    return ZT_TRUE;
}
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
    //if (iData != NULL) {
		ZTM8_Zero(iData->payload, iData->length);
        ZTM_FreeNull(iData->payload);
		iData->length = 0;
    //}
}
void ZTM_DataFreeSecure(ZT_DATA* iData) {
    //if (iData != NULL) {
		ZTM8_Zero(iData->payload, iData->length);
        ZTM8_Free(iData->payload);
        ZTM8_Free(iData);
    //}
}
void ZTM_DataFreePayload(ZT_DATA* iData) {
    //if (iData != NULL) {
        ZTM_FreeNull(iData->payload);
		iData->length = 0;
    //}
}
void ZTM_DataFreeWrap(ZT_DATA* iData) {
    //if (iData != NULL) {
        ZTM8_Free(iData);
    //}
}
void ZTM_DataFree(ZT_DATA* iData) {
    //if (iData != NULL) {
        ZTM8_Free(iData->payload);
        ZTM8_Free(iData);
    //}
}
#endif // ZTM_C_INCLUDED
