/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_CHAR_C_INCLUDED
#define ZT_CHAR_C_INCLUDED

#include "ZTM__Runtime.h"

const ZT_U8* ZTC8__DATE__(void) {return rZTC8__ISO8601__;}
const ZT_U8* ZTC8__DATE__Set(const ZT_U8* i__DATE__, const ZT_U8* i__TIME__) {
	if (i__DATE__ != NULL && i__TIME__ != NULL) {
		ZT_INDEX lMonth = 0;
		while ((lMonth < 12) && !ZTC8_Match(i__DATE__, rZTC8__MONTH[lMonth++]));
		rZTC8__ISO8601__[0] = i__DATE__[7];
		rZTC8__ISO8601__[1] = i__DATE__[8];
		rZTC8__ISO8601__[2] = i__DATE__[9];
		rZTC8__ISO8601__[3] = i__DATE__[10];
		rZTC8__ISO8601__[4] = ZTM_CHAR_MINUS;
		rZTC8__ISO8601__[5] = ZTM_CHAR_0 + (lMonth / 10);
		rZTC8__ISO8601__[6] = ZTM_CHAR_0 + (lMonth % 10);
		rZTC8__ISO8601__[7] = ZTM_CHAR_MINUS;
		rZTC8__ISO8601__[8] = (i__DATE__[4] != ' ') ? i__DATE__[4] : ZTM_CHAR_0;
		rZTC8__ISO8601__[9] = i__DATE__[5];
		rZTC8__ISO8601__[10] = ZTM_CHAR_SPACE;
		rZTC8__ISO8601__[11] = i__TIME__[0];
		rZTC8__ISO8601__[12] = i__TIME__[1];
		rZTC8__ISO8601__[13] = ZTM_CHAR_COLON;
		rZTC8__ISO8601__[14] = i__TIME__[3];
		rZTC8__ISO8601__[15] = i__TIME__[4];
		rZTC8__ISO8601__[16] = ZTM_CHAR_COLON;
		rZTC8__ISO8601__[17] = i__TIME__[6];
		rZTC8__ISO8601__[18] = i__TIME__[7];
		rZTC8__ISO8601__[19] = ZTM_CHAR_NT;
	}
	return rZTC8__ISO8601__;
}
#ifndef ZTM_CHAR_MACRO
ZT_INDEX ZTC8_GetLength(const ZT_U8* iText) {ZT_INDEX lCursor = -1; while (iText[++lCursor] != ZTM_CHAR_NT); return lCursor;}
ZT_INDEX ZTC8_CountCharVerbatim(const ZT_U8* iHaystack, ZT_INDEX iLength, ZT_U8 iNeedle) {
	ZT_INDEX lCount = 0;
	ZT_INDEX lCursor = -1;
	while (++lCursor < iLength) {if (iHaystack[lCursor] == iNeedle) {++lCount;}}
	return lCount;
}
void ZTC8_GetDimensionsVerbatim(const ZT_U8* iText, ZT_INDEX iLength, ZT_UPOINT* oDimensions) {
	if (oDimensions != NULL) {
		ZT_INDEX lLine = 0;
		oDimensions->xU = 0;
		oDimensions->yU = 0;
		ZT_INDEX lCursor = -1;
		while (++lCursor < iLength) {++lLine; if (iText[lCursor] == ZTM_CHAR_NL) {if (oDimensions->xU < lLine) {oDimensions->xU = lLine;} lLine = 0; ++(oDimensions->yU);}}
	}
}
ZT_BOOL ZTC8_Match(const ZT_U8* iHaystack, const ZT_U8* iNeedle) {
    ZT_INDEX lCursor = -1;
    while (iNeedle[++lCursor] != ZTM_CHAR_NT) {if ((iHaystack[lCursor] != iNeedle[lCursor]) || (iHaystack[lCursor] == ZTM_CHAR_NT)) {return 0x0;}} return 0x1;
}
ZT_BOOL ZTC8_MatchExact(const ZT_U8* iText1, const ZT_U8* iText2) {
    ZT_INDEX lCursor = 0;// operation undefined if using -1 (?)
    while (iText1[lCursor] == iText2[lCursor]) {if (iText1[lCursor] == ZTM_CHAR_NT) {return 0x1;} ++lCursor;} return 0x0;
}
ZT_BOOL ZTC8_MatchLenient(const ZT_U8* iText1, const ZT_U8* iText2) {
	ZT_INDEX lCursor = -1;
	while (iText1[++lCursor] != ZTM_CHAR_NT && iText2[lCursor] != ZTM_CHAR_NT) {if (iText1[lCursor] != iText2[lCursor]) {return 0x0;}} return 0x1;
}
ZT_BOOL ZTC8_SeekCursorMax(const ZT_U8* iText, const ZT_U8* iSearch, ZT_INDEX* oCursor, ZT_INDEX iByteMax) {
    ZT_INDEX lengthTerm = ZTC8_GetLength(iSearch) - 1;
    ZT_INDEX lCursor = (oCursor != NULL) ? *(oCursor) : 0;
    ZT_INDEX start = lCursor;
    while (ZTC8_CursorValidMax(iText, lCursor, iByteMax)) {if ((lCursor - start) >= lengthTerm) {if (ZTC8_Match(&iText[lCursor - lengthTerm], iSearch)) {
        if (oCursor != NULL) {*(oCursor) = (lCursor - lengthTerm);} return 0x1;}} ++lCursor;}
    return 0x0;
}
ZT_FLAG ZTC8_Escape(ZT_FLAG iEscape, ZT_CHAR iChar) {
	if (iEscape) {
		if (iEscape & 0x1) {
			iEscape &= ~0x1;
		} else if (iEscape & 0x2 && (iChar == ZTM_CHAR_QUOTES)) {
			iEscape &= ~0x2;
		} else if (iEscape & 0x4 && (iChar == ZTM_CHAR_QUOTE)) {
			iEscape &= ~0x4;
		}
	} else if (iChar == ZTM_CHAR_ESCAPE) {
		iEscape |= 0x1;
	} else if (iChar == ZTM_CHAR_QUOTES) {
		iEscape |= 0x2;
	} else if (iChar == ZTM_CHAR_QUOTE) {
		iEscape |= 0x4;
	}
	return iEscape;
}
#endif // ZTM_CHAR_MACRO
/*ZT_INDEX ZTC8_Count(const ZT_U8* iHaystack, const ZT_U8* iNeedle) {// UNTESTED!
	ZT_INDEX lCount = 0;
	ZT_INDEX lCursor = -1;
	while (iHaystack[++lCursor] != ZTM_CHAR_NT) {if (ZTC8_Match(iNeedle, iHaystack)) {lCount++;}}
	return lCount;
}*/
ZT_INDEX ZTC8_CountChar(const ZT_U8* iHaystack, ZT_U8 iNeedle) {// UNTESTED!
	ZT_INDEX lCount = 0;
	ZT_INDEX lCursor = -1;
	while (iHaystack[++lCursor] != ZTM_CHAR_NT) {if (iHaystack[lCursor] == iNeedle) {++lCount;}}
	return lCount;
}
void ZTC8_GetDimensions(const ZT_U8* iText, ZT_UPOINT* oDimensions) {// UNTESTED!
	if (oDimensions != NULL) {
		ZT_INDEX lLine = 0;
		oDimensions->xU = 0;
		oDimensions->yU = 0;
		ZT_INDEX lCursor = -1;
		while (iText[++lCursor] != ZTM_CHAR_NT) {++lLine; if (iText[lCursor] == ZTM_CHAR_LF) {if (oDimensions->xU < lLine) {oDimensions->xU = lLine;} lLine = 0; ++(oDimensions->yU);}}
	}
}
ZT_BOOL ZTC8_SeekDigitCursorMax(const ZT_U8* iText, ZT_INDEX* oCursor, ZT_INDEX iByteMax) {
    ZT_INDEX lCursor = (oCursor != NULL) ? *(oCursor) : 0;
    while (ZTC8_CursorValidMax(iText, lCursor, iByteMax)) {if (ZTC8_IsDigit(&iText[lCursor])) {if (oCursor != NULL) {*(oCursor) = lCursor;} return 0x1;} ++lCursor;}
    return 0x0;
}
ZT_BOOL ZTC8_SeekCRLFCursorMax(const ZT_U8* iText, ZT_INDEX* oCursor, ZT_INDEX iByteMax) {
    ZT_INDEX lCursor = (oCursor != NULL) ? *(oCursor) : 0;
    while (ZTC8_CursorValidMax(iText, lCursor, iByteMax)) {if (ZTC8_IsCRLF(&iText[lCursor])) {if (oCursor != NULL) {*(oCursor) = lCursor;} return 0x1;} ++lCursor;}
    return 0x0;
}
ZT_FLAG ZTC8_SeekBOM(const void* iText) {
    ZT_U8 lBOM[5];
    ZT_FLAG lType = ZTM_TEXT_TYPE_NONE;
    for (ZT_INDEX i = 0; i < (ZTM_TEXT_TYPES - 1); i++) {
        switch(i) {
            case 0: lBOM[0] = 0xef; lBOM[1] = 0xbb; lBOM[2] = 0xbf; lBOM[3] = 0x0; lType = ZTM_TEXT_TYPE_UTF8; break;
            case 1: lBOM[0] = 0xff; lBOM[1] = 0xfe; lBOM[2] = 0x0; lType = ZTM_TEXT_TYPE_UTF16LE; break;
            case 2: lBOM[0] = 0xfe; lBOM[1] = 0xff; lBOM[2] = 0x0; lType = ZTM_TEXT_TYPE_UTF16BE; break;
            default: lBOM[0] = ZTM_CHAR_NT; break;
        }
        ZT_INDEX lDummy;
        if (ZTC8_SeekCursorMax(iText, lBOM, &lDummy, ZTM_TEXT_BOM_ABORT)) {return lType;}
    }
    return ZTM_TEXT_TYPE_NONE;
}
//#define ZTM_TEXT_FLAG_READNUM_UNDEF 0x0
#define ZTM_TEXT_READ_INT 0x1
#define ZTM_TEXT_READ_BIN 0x2
#define ZTM_TEXT_READ_HEX 0x4
#define ZTM_TEXT_READ_FLT 0x8
#define ZTM_TEXT_READ_DEC (ZTM_TEXT_READ_INT | ZTM_TEXT_READ_FLT)
#define ZTM_TEXT_DETECT_INT 0x100
#define ZTM_TEXT_DETECT_BIN 0x200
#define ZTM_TEXT_DETECT_HEX 0x400
#define ZTM_TEXT_DETECT_FLT 0x800
#define ZTM_TEXT_DETECT_NGT 0x1000
#define ZTM_TEXT_DETECT_OK 0x80000000
ZT_U32 ZTC8_ReadUINT32(const ZT_U8* iText, ZT_FLAG iFlags, ZT_FLAG* oFlags) {
	ZT_FLAG lDetect = ZTM_TEXT_DETECT_OK; // implement: input was sanitized?
    ZT_U32 lBase = (iFlags & ZTM_TEXT_READ_BIN) ? 0x2 : ((iFlags & ZTM_TEXT_READ_HEX) ? 0x10 : 10);
    ZT_INDEX lCounter = 0;
    ZT_INDEX lDecimal = 0;
    ZT_INDEX lCursor = -1;
    ZT_U32 lNumber = 0;
    ZT_U32 lDigit = 0;
    while (iText[++lCursor] != ZTM_CHAR_NT) {
        if ((lDigit = ZTC8_GetBinary(&iText[lCursor])) != 0x2) {
            lDetect |= ZTM_TEXT_DETECT_INT;
        } else if ((iFlags & ZTM_TEXT_READ_BIN) || ((!iFlags) && (lDetect & ZTM_TEXT_DETECT_BIN))) {
			lDigit = 0x10;
		} else if ((lDigit = ZTC8_GetDigit(&iText[lCursor])) != 10) {
			lDetect |= ZTM_TEXT_DETECT_INT;
		} else if ((iFlags & ZTM_TEXT_READ_DEC) || ((!iFlags) && (lDetect & ZTM_TEXT_DETECT_FLT))) {
			lDigit = 0x10;
		} else if ((lDigit = ZTC8_GetHex(&iText[lCursor])) != 0x10) {
			lDetect |= ZTM_TEXT_DETECT_INT;
		} else if ((iText[lCursor] == ZTM_CHAR_MINUS) && (iFlags & ZTM_TEXT_READ_INT || iFlags & ZTM_TEXT_READ_FLT || !iFlags)) {
            lDetect |= ZTM_TEXT_DETECT_NGT;
			lDigit = 0x10;
		} else if ((!iFlags || iFlags & ZTM_TEXT_READ_FLT) && (iText[lCursor] == ZTM_CHAR_DECIMAL)) {
            if (!(lDetect & ZTM_TEXT_DETECT_INT)) {lCounter++;} // if no leading zero in number
            lDecimal = (lCounter & 0xff);
            lDetect |= ZTM_TEXT_DETECT_FLT;
			lDigit = 0x10;
		} else if (iFlags) {lDigit = 0x10;} else {
            if (iText[lCursor] == ZTM_CHAR_x) {lDetect |= ZTM_TEXT_DETECT_HEX; lBase = 0x10;
            } else if (!(lDetect & ZTM_TEXT_DETECT_HEX) && iText[lCursor] == ZTM_CHAR_b) {lDetect |= ZTM_TEXT_DETECT_BIN; lBase = 0x2;}
			lDigit = 0x10;
		}
        if (lDigit < 0x10) {if (lBase != 10) {
				if (lBase != 0x10) {lNumber <<= 1; lNumber |= lDigit; ++lCounter;
				} else {lNumber <<= 4; lNumber |= lDigit; ++lCounter;}
		} else {lNumber *= lBase; lNumber += lDigit; ++lCounter;}}
    }
    if (lDecimal) {lDetect |= ((lCounter - lDecimal) & 0xff);}
    if (oFlags != NULL) {*(oFlags) = lDetect;}
    return ((lDetect & ZTM_TEXT_DETECT_OK) ? lNumber : 0);
}
ZT_I ZTC8_ReadNumber(const ZT_U8* iText) {
    ZT_FLAG lFlag = 0x0;
    ZT_I lInt = ((ZT_I)(ZTC8_ReadUINT32(iText, 0x0, &lFlag)));
    if (!(lFlag & ZTM_TEXT_DETECT_BIN) && !(lFlag & ZTM_TEXT_DETECT_HEX)) {
        if (lFlag & ZTM_TEXT_DETECT_NGT) {lInt = -lInt;}
    }
    return lInt;
}
ZT_U ZTC8_ReadHex(const ZT_U8* iText) {return ZTC8_ReadUINT32(iText, ZTM_TEXT_READ_HEX, NULL);}
ZT_U ZTC8_ReadBinary(const ZT_U8* iText) {return ZTC8_ReadUINT32(iText, ZTM_TEXT_READ_BIN, NULL);}
ZT_I ZTC8_ReadInteger(const ZT_U8* iText) {
    ZT_FLAG lFlag = 0x0;
    ZT_I lInt = ((ZT_I)(ZTC8_ReadUINT32(iText, ZTM_TEXT_READ_INT, &lFlag)));
    if (lFlag & ZTM_TEXT_DETECT_NGT) {lInt = -lInt;}
    return lInt;
}
ZT_U ZTC8_ReadUnsigned(const ZT_U8* iText) {return ZTC8_ReadUINT32(iText, ZTM_TEXT_READ_INT, NULL);}
ZT_FLT ZTC8_ReadFloat(const ZT_U8* iText) {
    ZT_FLAG lFlag = 0x0;
    ZT_FLT lFloat = ((ZT_FLT)(ZTC8_ReadUINT32(iText, ZTM_TEXT_READ_FLT, &lFlag)));
    for (ZT_INDEX i = 0; i < (lFlag & 0xff); i++) {lFloat /= 10;}
    if (lFlag & ZTM_TEXT_DETECT_NGT) {lFloat = -lFloat;}
    return lFloat;
}
ZT_DBL ZTC8_ReadDouble(const ZT_U8* iText) {
    ZT_FLAG lFlag = 0x0;
    ZT_DBL lDouble = ((ZT_DBL)(ZTC8_ReadUINT32(iText, ZTM_TEXT_READ_FLT, &lFlag)));
    for (ZT_INDEX i = 0; i < (lFlag & 0xff); i++) {lDouble /= 10;}
    if (lFlag & ZTM_TEXT_DETECT_NGT) {lDouble = -lDouble;}
    return lDouble;
}
void ZTC8_ReadDate_ANSI_C(const ZT_U8* iText, ZT_DATE* oDate) {
	oDate->year = iText[10] - '0';
	oDate->year += (iText[9] - '0') * 10;
	oDate->year += (iText[8] - '0') * 100;
	oDate->year += (iText[7] - '0') * 1000;
	oDate->day = iText[5] - '0';
	if (iText[4] != ' ') {oDate->day += ((iText[4] - '0') * 10);}
	oDate->month = 0;
	while ((oDate->month < 12) && !ZTC8_Match(iText, rZTC8__MONTH[oDate->month++]));
}
void ZTC8_ReadTime_ANSI_C(const ZT_U8* iText, ZT_DATE* oDate) {
	oDate->hour = (iText[0] - '0') * 10 + (iText[1] - '0');
	oDate->minute = (iText[3] - '0') * 10 + (iText[4] - '0');
	oDate->second = (iText[6] - '0') * 10 + (iText[7] - '0');
}
const ZT_U8* ZTC8_CopyTarget(const ZT_U8* iSource, ZT_U8* oTarget) {ZT_INDEX lCursor = -1; while ((oTarget[++lCursor] = iSource[lCursor]) != ZTM_CHAR_NT); return iSource;}
ZT_U8* ZTC8_CopyLength(const ZT_U8* iText, ZT_INDEX iLength) {
    ZT_INDEX lLengthSource = ZTC8_GetLength(iText);
    if (iLength) {if (lLengthSource > iLength) {lLengthSource = iLength;}} else {iLength = lLengthSource;}
    ZT_U8* lCopy = ZTM8_New(iLength + 1);
    ZT_INDEX lCursor = -1;
    while (++lCursor < lLengthSource) {lCopy[lCursor] = iText[lCursor];}
    lCopy[iLength] = ZTM_CHAR_NT;
    return lCopy;
}
ZT_U8* ZTC8_CopyModulating(const ZT_U8* iText, ZT_INDEX iLength) {
    ZT_INDEX lLengthSource = ZTC8_GetLength(iText);
    ZT_U8* lCopy = ZTM8_New(iLength + 1);
    ZT_INDEX lCursor = -1;
    while (++lCursor < iLength) {lCopy[lCursor] = iText[lCursor % lLengthSource];}
    lCopy[iLength] = ZTM_CHAR_NT;
    return lCopy;
}
ZT_U8* ZTC8_Copy(const ZT_U8* iText) {return ZTC8_CopyLength(iText, 0);}
ZT_U8* ZTC8_Merge(const ZT_U8* iRoot, const ZT_U8* iBranch) {
    ZT_INDEX lRootLength = ZTC8_GetLength(iRoot);
    ZT_INDEX lBranchLength = ZTC8_GetLength(iBranch);
    ZT_INDEX lLength = lRootLength + lBranchLength;
    ZT_U8* newCopy = ZTC8_CopyLength(iRoot, lLength);
    for (ZT_INDEX i = 0; i < lBranchLength; i++) {newCopy[lRootLength + i] = iBranch[i];}
    newCopy[lLength] = ZTM_CHAR_NT;
    return newCopy;
}
ZT_U8* ZTC8_MergeFreeR(ZT_U8* iRoot, const ZT_U8* iBranch) {ZT_U8* newCopy = ZTC8_Merge(iRoot, iBranch); ZTM8_Free(iRoot); return newCopy;}
ZT_U8* ZTC8_MergeFreeB(const ZT_U8* iRoot, ZT_U8* iBranch) {ZT_U8* newCopy = ZTC8_Merge(iRoot, iBranch); ZTM8_Free(iBranch); return newCopy;}
ZT_U8* ZTC8_MergeFree(ZT_U8* iRoot, ZT_U8* iBranch) {ZT_U8* newCopy = ZTC8_Merge(iRoot, iBranch); ZTM8_Free(iRoot); ZTM8_Free(iBranch); return newCopy;}
ZT_U8* ZTC8_DeleteAndCopy(ZT_U8* iDelete, const ZT_U8* iCopy) {ZTM8_Free(iDelete); return ZTC8_Copy(iCopy);}
ZT_U8* ZTC8_CopyAndDelete(const ZT_U8* iCopy, ZT_U8* iDelete) {ZT_U8* lCopy = ZTC8_Copy(iCopy); ZTM8_Free(iDelete); return lCopy;}
ZT_U8* ZTC8_UnsignedBase(ZT_U iInteger, ZT_U iBase) {
    ZT_U8* lNumber = NULL;
    ZT_INDEX lMagnitude = 1;
    ZT_U lDivisor = iBase;
    while (iInteger / lDivisor) {++lMagnitude; if (!(lDivisor *= iBase) || (lDivisor % iBase)) {break;}}
    lNumber = ZTM8_New(lMagnitude + 1);
    lNumber[lMagnitude] = ZTM_CHAR_NT;
    lDivisor = 1;
    for (ZT_INDEX i = 0; i < lMagnitude; i++) {
        ZT_U lDigit = ((iInteger / lDivisor) % iBase);
        lNumber[lMagnitude - i - 1] = ((lDigit < 10) ? ZTM_CHAR_0 : ZTM_CHAR_HEX_aOFF) + lDigit;
        lDivisor *= iBase;
    }
    return lNumber;
}
ZT_U8* ZTC8_IntegerBase(ZT_I iInteger, ZT_I iBase) {
    if (iInteger == (ZT_I)0x80000000) {return ZTC8_MergeFreeB((const ZT_U8*)"-", ZTC8_Unsigned(0x80000000));} // else integer overflow
    ZT_U8* lNumber = NULL;
    ZT_INDEX lIsPositive = (iInteger < 0) ? 0x0 : 0x1;
    ZT_INDEX lMagnitude = 1;
    ZT_I lDivisor = (lIsPositive) ? iBase : -iBase;
    while (iInteger / lDivisor) {++lMagnitude; if (!(lDivisor *= iBase) || (lDivisor % iBase)) {break;}}
    lNumber = ZTM8_New(lMagnitude + 2 - lIsPositive);
    lNumber[lMagnitude + (!lIsPositive)] = ZTM_CHAR_NT;
    lDivisor = (lIsPositive) ? 1 : -1;
    for (ZT_INDEX i = 0; i < lMagnitude; i++) {
        ZT_I lDigit = ((iInteger / lDivisor) % iBase);
        lNumber[lMagnitude - i - lIsPositive] = ((lDigit < 10) ? ZTM_CHAR_0 : ZTM_CHAR_HEX_aOFF) + lDigit;
        lDivisor *= iBase;
    }
    if (iInteger < 0) {lNumber[0] = ZTM_CHAR_MINUS;}
    return lNumber;
}
ZT_U8* ZTC8_Unsigned(ZT_U iInteger) {return ZTC8_UnsignedBase(iInteger, 10);}
ZT_U8* ZTC8_Integer(ZT_I iInteger) {return ZTC8_IntegerBase(iInteger, 10);}
ZT_U8* ZTC8_Hex(ZT_U iInteger) {return ZTC8_UnsignedBase(iInteger, 0x10);}
ZT_U8* ZTC8_HexSigned(ZT_I iInteger) {return ZTC8_IntegerBase(iInteger, 0x10);}
ZT_U8* ZTC8_Binary(ZT_U iInteger) {return ZTC8_UnsignedBase(iInteger, 0x2);}
ZT_U8* ZTC8_BinarySigned(ZT_I iInteger) {return ZTC8_IntegerBase(iInteger, 0x2);}
ZT_U8* ZTC8_ByteString(const ZT_U8* iBytes, ZT_INDEX iLength, const ZT_U8* iDelimiter, ZT_INDEX iGrouping) {
    ZT_INDEX lLengthDelimit = (iDelimiter != NULL) ? ZTC8_GetLength(iDelimiter) : 0;
    ZT_INDEX lChars = (iLength << 1);
    if (iDelimiter != NULL && iGrouping) {lChars += ((iLength - 1) / iGrouping) * lLengthDelimit;}
    ZT_U8* lString = ZTM8_New(lChars + 1);
    ZT_INDEX lCursor = 0;
    ZT_INDEX lIndex = -1;
    while (++lIndex < iLength) {
        if (iDelimiter != NULL && iGrouping) {if (!(lIndex % iGrouping) && lIndex) {ZTC8_CopyTarget(iDelimiter, &lString[lCursor]); lCursor += lLengthDelimit;}}
        ZT_U8 lNibble = iBytes[lIndex] >> 4;
        lString[lCursor++] = (lNibble > 9) ? (lNibble + ZTM_CHAR_HEX_aOFF) : (lNibble + 0x30);
        lNibble = iBytes[lIndex] & 0xf;
        lString[lCursor++] = (lNibble > 9) ? (lNibble + ZTM_CHAR_HEX_aOFF) : (lNibble + 0x30);
    }
    lString[lChars] = ZTM_CHAR_NT;
    return lString;
}
ZT_U8* ZTC8_HashString(const void* iHash, ZT_INDEX iBits, const ZT_U8* iDelimiter, ZT_INDEX iGrouping) {
    const ZT_HASH1024* lHash = iHash;
    ZT_INDEX lLength = ((iBits + 7) >> 3);
	return ZTC8_ByteString(lHash->byte, lLength, iDelimiter, iGrouping);
}
/*ZT_U8* ZTC8_HashString(const void* iHash, const ZT_U8* iDelimiter, ZT_INDEX iBits, ZT_INDEX iGrouping) {
    const ZT_HASH1024* lHash = iHash;
    ZT_INDEX lLengthDelimit = (iDelimiter != NULL) ? ZTC8_GetLength(iDelimiter) : 0;
    ZT_INDEX lBytes = ((iBits + 7) >> 3);
    ZT_INDEX lChars = (lBytes << 1);
    if (iDelimiter != NULL && iGrouping) {lChars += ((lBytes - 1) / iGrouping) * lLengthDelimit;}
    ZT_U8* lString = ZTM8_New(lChars + 1);
    ZT_INDEX lCursor = 0;
    ZT_INDEX lIndex = -1;
    while (++lIndex < lBytes) {
        if (iDelimiter != NULL && iGrouping) {if (!(lIndex % iGrouping) && lIndex) {ZTC8_CopyTarget(iDelimiter, &lString[lCursor]); lCursor += lLengthDelimit;}}
        ZT_U8 lNibble = lHash->byte[lIndex] >> 4;
        lString[lCursor++] = (lNibble > 9) ? (lNibble + ZTM_CHAR_HEX_aOFF) : (lNibble + 0x30);
        lNibble = lHash->byte[lIndex] & 0xf;
        lString[lCursor++] = (lNibble > 9) ? (lNibble + ZTM_CHAR_HEX_aOFF) : (lNibble + 0x30);
    }
    lString[lChars] = ZTM_CHAR_NT;
    return lString;
}*/
ZT_U8* ZTC8_Printable(const ZT_U8* iData, ZT_INDEX iLength, ZT_U8 iReplacement) {
	if (iData != NULL) {
		ZT_U8* lPrintable;
		if ((lPrintable = ZTM8_New(iLength + 1)) != NULL) {
			ZT_INDEX lCursor = -1;
			while (++lCursor < iLength) {
				ZT_U8 lChar = iData[lCursor];
				if (lChar > ZTM_CHAR_PRINT_MAX) {
					lPrintable[lCursor] = iReplacement;
				} else if (lChar < ZTM_CHAR_PRINT_MIN) {
					if ((lChar == ZTM_CHAR_CR) ? (((lCursor + 1) < iLength) ? (iData[lCursor + 1] == ZTM_CHAR_LF) : 0x0) : (lChar == ZTM_CHAR_LF)) {
						lPrintable[lCursor] = lChar;
					} else {
						lPrintable[lCursor] = iReplacement;
					}
				} else {
					lPrintable[lCursor] = lChar;
				}
			}
			lPrintable[iLength] = ZTM_CHAR_NT;
			return lPrintable;
		}
	}
	return NULL;
}
ZT_U8* ZTC8_DateISO8601(ZT_TIME iUnix) {
    ZT_U8* lDate = ZTM8_New(20);
    ZT_DATE lTimestamp;
    ZTM_DateRead(iUnix, &lTimestamp);
    lDate[0] = 0x30 + (lTimestamp.year % 10000) / 1000;
    lDate[1] = 0x30 + (lTimestamp.year % 1000) / 100;
    lDate[2] = 0x30 + (lTimestamp.year % 100) / 10;
    lDate[3] = 0x30 + (lTimestamp.year % 10);
    lDate[4] = ZTM_CHAR_MINUS;
    lDate[5] = 0x30 + (lTimestamp.month % 100) / 10;
    lDate[6] = 0x30 + (lTimestamp.month % 10);
    lDate[7] = ZTM_CHAR_MINUS;
    lDate[8] = 0x30 + (lTimestamp.day % 100) / 10;
    lDate[9] = 0x30 + (lTimestamp.day % 10);
    lDate[10] = ZTM_CHAR_SPACE;
    lDate[11] = 0x30 + (lTimestamp.hour % 100) / 10;
    lDate[12] = 0x30 + (lTimestamp.hour % 10);
    lDate[13] = ZTM_CHAR_COLON;
    lDate[14] = 0x30 + (lTimestamp.minute % 100) / 10;
    lDate[15] = 0x30 + (lTimestamp.minute % 10);
    lDate[16] = ZTM_CHAR_COLON;
    lDate[17] = 0x30 + (lTimestamp.second % 100) / 10;
    lDate[18] = 0x30 + (lTimestamp.second % 10);
    lDate[19] = ZTM_CHAR_NT;
    return lDate;
}
ZT_U8* ZTC8_DateRFC1123(ZT_TIME iUnix) {
    ZT_U8* lDate = ZTM8_New(30);
    ZT_DATE_EXTRA lTimestamp;
    ZTM_DateExtraRead(&lTimestamp, iUnix);
    lDate[0] = (rZTC8__DAY[lTimestamp.extra.weekday])[0];
    lDate[1] = (rZTC8__DAY[lTimestamp.extra.weekday])[1];
    lDate[2] = (rZTC8__DAY[lTimestamp.extra.weekday])[2];
    lDate[3] = ZTM_CHAR_COMMA;
    lDate[4] = ZTM_CHAR_SPACE;
    lDate[5] = 0x30 + (lTimestamp.day % 100) / 10;
    lDate[6] = 0x30 + (lTimestamp.day % 10);
    lDate[7] = ZTM_CHAR_SPACE;
    lDate[8] = (rZTC8__MONTH[lTimestamp.month - 1])[0];
    lDate[9] = (rZTC8__MONTH[lTimestamp.month - 1])[1];
    lDate[10] = (rZTC8__MONTH[lTimestamp.month - 1])[2];
    lDate[11] = ZTM_CHAR_SPACE;
    lDate[12] = 0x30 + (lTimestamp.year % 10000) / 1000;
    lDate[13] = 0x30 + (lTimestamp.year % 1000) / 100;
    lDate[14] = 0x30 + (lTimestamp.year % 100) / 10;
    lDate[15] = 0x30 + (lTimestamp.year % 10);
    lDate[16] = ZTM_CHAR_SPACE;
    lDate[17] = 0x30 + (lTimestamp.hour % 100) / 10;
    lDate[18] = 0x30 + (lTimestamp.hour % 10);
    lDate[19] = ZTM_CHAR_COLON;
    lDate[20] = 0x30 + (lTimestamp.minute % 100) / 10;
    lDate[21] = 0x30 + (lTimestamp.minute % 10);
    lDate[22] = ZTM_CHAR_COLON;
    lDate[23] = 0x30 + (lTimestamp.second % 100) / 10;
    lDate[24] = 0x30 + (lTimestamp.second % 10);
    lDate[25] = ZTM_CHAR_SPACE;
    lDate[26] = 'G';
    lDate[27] = 'M';
    lDate[28] = 'T';
    lDate[29] = ZTM_CHAR_NT;
    return lDate;
}
ZT_INDEX ZTC8_ReplaceGetLength(const ZT_U8* iHaystack, const ZT_U8* iNeedle, const ZT_U8* iReplacement) {
	ZT_INDEX lLengthNeedle = ZTC8_GetLength(iNeedle);
	ZT_INDEX lLengthReplace = (iReplacement != NULL) ? ZTC8_GetLength(iReplacement) : 0;
	ZT_INDEX lCount = 0;
	ZT_INDEX lCursor = 0;
	while (ZTC8_SeekCursor(iHaystack, iNeedle, &lCursor)) {++lCount;}
	if (lCount) {return (lCursor - (lCount * lLengthNeedle) + (lCount * lLengthReplace));}
	return 0;
}
ZT_U8* ZTC8_Replace(const ZT_U8* iHaystack, const ZT_U8* iNeedle, const ZT_U8* iReplacement) {
	ZT_INDEX lLength;
	if ((lLength = ZTC8_ReplaceGetLength(iHaystack, iNeedle, iReplacement))) {
		ZT_U8* lTextReplaced = ZTM8_New(lLength + 1);
		ZT_INDEX lLengthNeedle = ZTC8_GetLength(iNeedle);
		ZT_INDEX lLengthReplace = (iReplacement != NULL) ? ZTC8_GetLength(iReplacement) : 0;
		ZT_INDEX lRead = 0;
		ZT_INDEX lWrite = 0;
		ZT_INDEX lCursor = 0;
		while (ZTC8_SeekCursor(iHaystack, iNeedle, &lCursor)) {
			ZTM8_Copy(&iHaystack[lRead], &lTextReplaced[lWrite], lCursor - lRead);
			lWrite += (lCursor - lRead);
			if (iReplacement != NULL) {
				ZTM8_Copy(iReplacement, &lTextReplaced[lWrite], lLengthReplace);
				lWrite += lLengthReplace;
			}
			lRead = lCursor + lLengthNeedle;
		}
		lTextReplaced[lLength] = ZTM_CHAR_NT;
		return lTextReplaced;
	}
	return NULL;
}
/*
ZT_BOOL ZTC8_WinCLI(ZT_INDEX argc, ZT_U8** argv, const ZT_U8* iSearch, ZT_INDEX* oIndexFound) {
    if (oIndexFound != NULL) {
        for (ZT_INDEX i = 0; i < argc; i++) {
            if (ZTC8_MatchExact(iSearch, argv[i])){
                *oIndexFound = i;
                return 0x1;
            }
        }
    }
    return 0x0;
}
ZT_U8* ZTC8_ConvertUTF8ToWin1252(const ZT_U8* iText) {
    char currentChar = 0;
    unsigned int numReplace = 0;
    unsigned int lCursor = 0;
    while (ZTC8_IsNotNT(&iText[lCursor])) {
        currentChar = iText[lCursor];
        if ((currentChar == char(0xC2)) || (currentChar == char(0xC3))) {
            numReplace++;
        }
        lCursor++;
    }
    if (numReplace) {
        unsigned int newLength = lCursor - numReplace;
        lCursor = 0;
        numReplace = 0;
        unsigned int addNext = 0;
        char* newText = (char*)ZTM_MemAllocZero(newLength + 1, sizeof(char));
        while (lCursor < newLength) {
            addNext = 0;
            currentChar = iText[lCursor + numReplace];
            if ((currentChar == char(0xC2)) || (currentChar == char(0xC3))) {
                if (currentChar == char(0xC3)) {
                    addNext = 0x40;
                }
                numReplace++;
            }
            newText[lCursor] = iText[lCursor + numReplace] + addNext;
            lCursor++;
        }
        newText[newLength] = ZTM_CHAR_NT;
        return newText;
    } else {
        return NULL;
    }
}
*/

#endif // ZT_CHAR_C_INCLUDED
