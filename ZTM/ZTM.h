/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_H_INCLUDED
#define ZTM_H_INCLUDED

// ZTM ENVIRONMENT
#include "ZTM__Environment.h"
#ifndef NULL
#define NULL (void*)0x0
#endif // NULL
// ZTM OPTIONS
//#define ZTM_MALLOC_MACRO // uses function macros for memory management routines
#define ZTM_POINT_MACRO // uses function macros for ZT_POINT types instead of -fPIC
#define ZTM_RECT_MACRO // uses function macros for ZT_RECT types instead of -fPIC
#define ZTM_CHAR_MACRO
// ZTM MANDATORY
#include "ZTM_Types.h"
// ZTM MACRO
#define ZTM_CoerceIfZero(VAR, VAL) ((!(VAR)) ? ((VAR) = (VAL)) : (VAR))
#define ZTM_CoerceIfNotZero(VAR, VAL) ((VAR) ? ((VAR) = (VAL)) : (VAR))
#define ZTM_CoerceIfLess(VAR, VAL) (((VAR) < (VAL)) ? ((VAR) = (VAL)) : (VAR))
#define ZTM_CoerceIfMore(VAR, VAL) (((VAR) > (VAL)) ? ((VAR) = (VAL)) : (VAR))
#define ZTM_CoerceIfZeroAndLess(VAR, VAL) (((!(VAR)) && ((VAR) < (VAL))) ? ((VAR) = (VAL)) : (VAR))
#define ZTM_CoerceIfZeroAndMore(VAR, VAL) (((!(VAR)) && ((VAR) > (VAL))) ? ((VAR) = (VAL)) : (VAR))
#define ZTM_CoerceIfNotZeroAndLess(VAR, VAL) (((VAR) && ((VAR) < (VAL))) ? ((VAR) = (VAL)) : (VAR))
#define ZTM_CoerceIfNotZeroAndMore(VAR, VAL) (((VAR) && ((VAR) > (VAL))) ? ((VAR) = (VAL)) : (VAR))
#define ZTM_DoNull(FUNC,VAR) FUNC((VAR)); (VAR) = NULL
#define ZTM_FlagIfSetUnset(VAR,FLAG) (((VAR) & (FLAG)) ? (((VAR) &= ~(FLAG)) ^ (FLAG)) : 0x0) // returns non-zero on perform unset, else 0x0
#define ZTM_FlagIfToggleReset(VAR,NEW) (((VAR) ^ (NEW)) ? ((((VAR) = (NEW)) | 0x1) & 0x1) : 0x0)
#define ZTM_FlagSet(VAR,FLAG) ((VAR) |= (FLAG))
#define ZTM_FlagUnset(VAR,FLAG) ((VAR) &= ~(FLAG))
#define ZTM_SetIfNull(VAR,VAL) if ((VAR) == NULL) {(VAR) = (VAL);}
#define ZTM_SetIfEqual(VAR,REF,VAL) if ((VAR) == (REF)) {(VAR) = (VAL);}
#define ZTM_SetIfNotEqual(VAR,REF,VAL) if ((VAR) != (REF)) {(VAR) = (VAL);}
#define ZTM_SetIfZero(VAR,VAL) if (!(VAR)) {(VAR) = (VAL);}
#define ZTM_SetIfNotZero(VAR,VAL) if ((VAR)) {(VAR) = (VAL);}
#define ZTM_SetIfEqualElseToggle(VAR,REF,VAL) if ((VAR) == (REF)) {(VAR) = (VAL);} else {(VAR) ^= (VAL);}
#define ZTM_SetIfEqualElseToggleBy(VAR,REF,VAL,ELSE) if ((VAR) == (REF)) {(VAR) = (VAL);} else {(VAR) ^= (ELSE);}
#define ZTM_FreeNull(DATA) ZTM8_Free(DATA); (DATA) = NULL
#define ZTM_FreeSet(DATA, VAL) ({ZTM8_Free(DATA); (DATA) = (VAL);})
#define ZTM_GetU16LE(ADDRESS) (((ADDRESS)[0]) | ((ADDRESS)[1] << 8))
#define ZTM_GetU32LE(ADDRESS) (((ADDRESS)[0]) | ((ADDRESS)[1] << 8) | ((ADDRESS)[2] << 16) | ((ADDRESS)[3] << 24))
#define ZTM_GetU64LE(ADDRESS) (((ADDRESS)[0]) | ((ADDRESS)[1] << 8) | ((ADDRESS)[2] << 16) | ((ADDRESS)[3] << 24) | ((ADDRESS)[4] << 32) | ((ADDRESS)[5] << 40) | ((ADDRESS)[6] << 48) | ((ADDRESS)[7] << 56))
#define ZTM_GetU16BE(ADDRESS) (((ADDRESS)[1]) | ((ADDRESS)[0] << 8))
#define ZTM_GetU32BE(ADDRESS) (((ADDRESS)[3]) | ((ADDRESS)[2] << 8) | ((ADDRESS)[1] << 16) | ((ADDRESS)[0] << 24))
#define ZTM_GetU64BE(ADDRESS) (((ADDRESS)[7]) | ((ADDRESS)[6] << 8) | ((ADDRESS)[5] << 16) | ((ADDRESS)[4] << 24) | ((ADDRESS)[3] << 32) | ((ADDRESS)[2] << 40) | ((ADDRESS)[1] << 48) | ((ADDRESS)[0] << 56))
#define ZTM_U16LE(ADDRESS,DATA) (ADDRESS)[0] = ((DATA) & 0xff); (ADDRESS)[1] = (((DATA) >> 8) & 0xff)
#define ZTM_U32LE(ADDRESS,DATA) (ADDRESS)[0] = ((DATA) & 0xff); (ADDRESS)[1] = (((DATA) >> 8) & 0xff); (ADDRESS)[2] = (((DATA) >> 16) & 0xff); (ADDRESS)[3] = (((DATA) >> 24) & 0xff)
// ZTM FUNCTIONS
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_U32 ZTM_Seed_32(ZT_U32 iSeed); // returns previous seed
ZT_U32 ZTM_Random_32(ZT_U32 iModulo);
ZT_U32 ZTM_Randomize_32(ZT_U32* ioSeed, ZT_U32 iModulo);
ZT_U64 ZTM_Seed_64(ZT_U64 iSeed); // returns previous seed
ZT_U64 ZTM_Random_64(ZT_U64 iModulo);
ZT_U64 ZTM_Randomize_64(ZT_U64* ioSeed, ZT_U64 iModulo);
#define ZTM_Seed(SEED) ZTM_Seed_32(SEED)
#define ZTM_Random(MODULO) ZTM_Random_32(MODULO)
#define ZTM_Randomize(SEED,MODULO) ZTM_Randomize_32(SEED, MODULO)
ZT_FLAG ZTM_LSB(ZT_FLAG iFlag);
ZT_FLAG ZTM_MSB(ZT_FLAG iFlag);
ZT_FLAG ZTM_BitFillLeft(ZT_INDEX iCount);
ZT_FLAG ZTM_BitFillRight(ZT_INDEX iCount);
ZT_INDEX ZTM_BitCount(ZT_FLAG iFlag);
ZT_INDEX ZTM_BitIndex(ZT_FLAG iFlag); ///need to find new names for these...
ZT_INDEX ZTM_BitIndexIndex(ZT_FLAG iFlag, ZT_INDEX iIndex);
ZT_INDEX ZTM_BitIndexFlag(ZT_FLAG iFlag, ZT_FLAG iBit);
ZT_INDEX ZTM_BitFlagIndex(ZT_FLAG iFlag);
ZT_FLAG ZTM_ByteLess(ZT_FLAG iInput, ZT_FLAG iReference);
ZT_FLAG ZTM_ByteLessEqual(ZT_FLAG iInput, ZT_FLAG iReference);
ZT_FLAG ZTM_ByteGreater(ZT_FLAG iInput, ZT_FLAG iReference);
ZT_FLAG ZTM_ByteGreaterEqual(ZT_FLAG iInput, ZT_FLAG iReference);
ZT_FLAG ZTM_ByteOffset(ZT_FLAG iInput, ZT_FLAG iReference);
ZT_FLAG ZTM_ByteAdd(ZT_FLAG iInput, ZT_FLAG iOperand);
ZT_FLAG ZTM_ByteSubtract(ZT_FLAG iInput, ZT_FLAG iOperand);
ZT_FLAG ZTM_ByteMultiply(ZT_FLAG iInput, ZT_FLAG iOperand);
ZT_FLAG ZTM_ByteDivide(ZT_FLAG iInput, ZT_FLAG iOperand);
ZT_FLAG ZTM_ByteMirror(ZT_FLAG iInput);
ZT_INDEX ZTM_ByteSum(ZT_FLAG iInput);
#define ZTM_Abs(INT) (((INT) < 0) ? -(INT) : INT)
ZT_U ZTM_Exp(ZT_INDEX iMagnitude); // no overflow protection! user must consider
ZT_INDEX ZTM_Magnitude(ZT_U iInteger);
ZT_INDEX ZTM_MagnitudeSigned(ZT_I iInteger);
#ifndef ZTM_POINT_MACRO
void ZTM_Point(ZT_POINT* oPoint, const ZT_I iX, const ZT_I iY);
void ZTM_UPoint(ZT_UPOINT* oPoint, const ZT_U iX, const ZT_U iY);
void ZTM_PointCopy(const ZT_POINT* iSource, ZT_POINT* oTarget);
void ZTM_PointZero(ZT_POINT* oPoint);
ZT_I ZTM_PointArea(const ZT_POINT* iPoint);
ZT_U ZTM_UPointArea(const ZT_UPOINT* iUPoint);
ZT_BOOL ZTM_PointIsNotZero(const ZT_POINT* iPoint);
#else
#define ZTM_Point(POINT,X,Y) (POINT)->x = X; (POINT)->y = Y
#define ZTM_UPoint(POINT,X,Y)  ZTM_Point(POINT,X,Y)
#define ZTM_PointCopy(SOURCE,TARGET) (TARGET)->x = (SOURCE)->x; (TARGET)->y = (SOURCE)->y
#define ZTM_PointZero(POINT) (POINT)->x = 0; (POINT)->y = 0
#define ZTM_PointIsNotZero(POINT) ((POINT)->x || (POINT)->y)
#define ZTM_PointArea(POINT) ((POINT)->x * (POINT)->y)
#define ZTM_UPointArea(POINT) ((POINT)->xU * (POINT)->yU)
#endif // ZTM_POINT_MACRO
ZT_BOOL ZTM_PointWithinRect(const ZT_POINT* iPoint, const ZT_RECT* iRect); // or just "PointInRect"?
#ifndef ZTM_RECT_MACRO
void ZTM_Rect(ZT_RECT* oRect, const ZT_I iX, const ZT_I iY, const ZT_I iW, const ZT_I iH);
void ZTM_RectCopy(const ZT_RECT* iSource, ZT_RECT* oTarget);
void ZTM_RectCopyPos(const ZT_RECT* iSource, ZT_RECT* oTarget);
void ZTM_RectCopySize(const ZT_RECT* iSource, ZT_RECT* oTarget);
void ZTM_RectPos(ZT_RECT* oRect, const ZT_POINT* iPos);
void ZTM_RectPosIntoPoint(const ZT_RECT* iRect, ZT_POINT* oPos);
void ZTM_RectPosFromIntegers(ZT_RECT* oRect, const ZT_I iX, const ZT_I iY);
void ZTM_RectPosIntoPointers(const ZT_RECT* iRect, ZT_I* oX, ZT_I* oY);
void ZTM_RectSize(ZT_RECT* oRect, const ZT_POINT* iSize);
void ZTM_RectSizeIntoPoint(const ZT_RECT* iRect, ZT_POINT* oSize);
void ZTM_RectSizeFromIntegers(ZT_RECT* oRect, const ZT_I iW, const ZT_I iH);
void ZTM_RectSizeIntoPointers(const ZT_RECT* iRect, ZT_I* oWidth, ZT_I* oHeight);
void ZTM_RectZero(ZT_RECT* oRect);
void ZTM_RectZeroPos(ZT_RECT* oRect);
void ZTM_RectZeroSize(ZT_RECT* oRect);
ZT_I ZTM_RectArea(const ZT_RECT* iRect);
#else
#define ZTM_Rect(RECT,X,Y,W,H) (RECT)->x = X; (RECT)->y = Y; (RECT)->w = W; (RECT)->h = H
#define ZTM_RectZero(RECT) (RECT)->x = 0; (RECT)->y = 0; (RECT)->w = 0; (RECT)->h = 0
#define ZTM_RectZeroPos(RECT) (RECT)->x = 0; (RECT)->y = 0
#define ZTM_RectZeroSize(RECT) (RECT)->w = 0; (RECT)->h = 0
#define ZTM_RectCopy(SOURCE,TARGET) (TARGET)->x = (SOURCE)->x; (TARGET)->y = (SOURCE)->y; (TARGET)->w = (SOURCE)->w; (TARGET)->h = (SOURCE)->h
#define ZTM_RectCopyPos(SOURCE,TARGET) (TARGET)->x = (SOURCE)->x; (TARGET)->y = (SOURCE)->y
#define ZTM_RectCopySize(SOURCE,TARGET) (TARGET)->w = (SOURCE)->w; (TARGET)->h = (SOURCE)->h
#define ZTM_RectPos(RECT,POS) (RECT)->x = (POS)->x; (RECT)->y = (POS)->y
#define ZTM_RectPosFromIntegers(RECT,X,Y) (RECT)->x = X; (RECT)->y = Y
#define ZTM_RectSize(RECT,SIZE) (RECT)->w = (SIZE)->x; (RECT)->h = (SIZE)->y
#define ZTM_RectSizeFromIntegers(RECT,W,H) (RECT)->w = W; (RECT)->h = H
#define ZTM_RectPosIntoPoint(RECT,POS) (POS)->x = (RECT)->x; (POS)->y = (RECT)->y
#define ZTM_RectPosIntoPointers(RECT,X,Y) *X = (RECT)->x; *Y = (RECT)->y
#define ZTM_RectSizeIntoPoint(RECT,SIZE) (SIZE)->x = (RECT)->x; (SIZE)->y = (RECT)->y
#define ZTM_RectSizeIntoPointers(RECT,W,H) *W = (RECT)->x; *H = (RECT)->y
#define ZTM_RectArea(RECT) ((RECT)->w * (RECT)->h)
#endif // ZTM_RECT_MACRO
void ZTM_RectClipFromOriginToPoint(ZT_RECT* iRect, const ZT_POINT* iSize);
ZT_BOOL ZTM_RectIntersect(const ZT_RECT* iRect0, const ZT_RECT* iRect1, ZT_RECT* oIntersection);
//void ZTM_RectCorner(const ZT_RECT* iRect, ZT_POINT* oCorners);
void ZTM8_Free(void* iData);
void* ZTM8_New(ZT_SIZE iLength);
void* ZTM8_Resize(void* iData, ZT_SIZE iLength);
void* ZTM8_Copy(const void* iSource, void* iTarget, ZT_SIZE iLength);
void* ZTM8_Set(void* iData, ZT_U8 iValue, ZT_SIZE iLength);
void* ZTM8_Zero(void* iData, ZT_SIZE iLength);
void* ZTM8_Init(ZT_SIZE iLength, ZT_U8 iVal);
void* ZTM8_Move(void* iSource, void* iTarget, ZT_SIZE iLength);
void* ZTM8_NewArray(ZT_SIZE iCount, ZT_SIZE iElement, ZT_SIZE iPadding, void** oList);
void ZTM32_Free(void* iData);
void* ZTM32_New(ZT_SIZE iLength);
void* ZTM32_Resize(void* iData, ZT_SIZE iLength);
void* ZTM32_Copy(const void* iSource, void* iTarget, ZT_SIZE iLength);
void* ZTM32_Move(void* iSource, void* iTarget, ZT_SIZE iLength);
void* ZTM32_Set(void* iData, ZT_U32 iValue, ZT_SIZE iLength);
void* ZTM32_Zero(void* iData, ZT_SIZE iLength);
void* ZTM32_Init(ZT_SIZE iLength, ZT_U32 iValue);
void* ZTM32_NewBlock(const ZT_UPOINT* iSize);
void* ZTM32_ResizeBlock(void* iData, const ZT_UPOINT* iSize);
void* ZTM32_CopyBlock(const void* iSource, void* iTarget, const ZT_UPOINT* iSize);
void* ZTM32_MoveBlock(void* iSource, void* iTarget, const ZT_UPOINT* iSize);
void* ZTM32_SetBlock(void* iData, ZT_U32 iValue, const ZT_UPOINT* iSize);
void* ZTM32_InitBlock(const ZT_UPOINT* iSize, ZT_U32 iValue);
ZT_BOOL ZTM8_Match(const void* iSource, const void* iTarget, ZT_SIZE iLength);
ZT_DATA* ZTM_DataNew(ZT_SIZE iLength);
ZT_DATA* ZTM_DataNewCopy(const ZT_U8* iData, ZT_SIZE iLength);
ZT_DATA* ZTM_DataNewWrap(ZT_U8* iData, ZT_SIZE iLength);
void ZTM_DataFreePayloadSecure(ZT_DATA* iData);
void ZTM_DataFreeSecure(ZT_DATA* iData);
void ZTM_DataFreePayload(ZT_DATA* iData);
void ZTM_DataFreeWrap(ZT_DATA* iData);
void ZTM_DataFree(ZT_DATA* iData);
#ifdef __cplusplus
}
#endif // __cplusplus

#include "ZT_Time.h"
#include "ZT_Hash.h"
#include "ZT_List.h"
#include "ZT_Char.h"
#include "ZT_Color.h"
#include "ZT_Pixel.h"
#include "ZT_Surface.h"
#include "ZTMIO/ZTMIO.h"
#include "ZTMKY/ZTMKY.h"
#include "ZTMWV/ZTMWV.h"

#endif // ZTM_H_INCLUDED
