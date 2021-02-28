/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
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
/*void ZTC8_ReadDate_ANSI_C(const ZT_U8* iText, ZT_DATE* oDate) {
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
}*/
#ifndef ZTM_CHAR_MACRO
ZT_INDEX ZTC8_GetLength(const ZT_U8* iText) {ZT_INDEX lCursor = -1; while (iText[++lCursor] != ZTM_CHAR_NT); return lCursor;}
ZT_INDEX ZTC8_CountChar(const ZT_U8* iHaystack, ZT_U8 iNeedle) {// UNTESTED!
	ZT_INDEX lCount = 0; ZT_INDEX lCursor = -1;
	while (iHaystack[++lCursor] != ZTM_CHAR_NT) {if (iHaystack[lCursor] == iNeedle) {++lCount;}}
	return lCount;
}
ZT_INDEX ZTC8_CountCharVerbatim(const ZT_U8* iHaystack, ZT_INDEX iLength, ZT_U8 iNeedle) {
	ZT_INDEX lCount = 0; ZT_INDEX lCursor = -1;
	while (++lCursor < iLength) {if (iHaystack[lCursor] == iNeedle) {++lCount;}}
	return lCount;
}
ZT_INDEX ZTC8_Count(const ZT_U8* iHaystack, const ZT_U8* iNeedle) {// UNTESTED!
	ZT_INDEX lCount = 0; ZT_INDEX lCursor = -1;
	while (iHaystack[++lCursor] != ZTM_CHAR_NT) {if (ZTC8_Match(iHaystack, iNeedle)) {++lCount;}}
	return lCount;
}
ZT_INDEX ZTC8_CountVerbatim(const ZT_U8* iHaystack, ZT_INDEX iLength, const ZT_U8* iNeedle) {// UNTESTED!
	ZT_INDEX lCount = 0; ZT_INDEX lCursor = -1;
	while (++lCursor < iLength) {if (ZTC8_Match(iHaystack, iNeedle)) {++lCount;}}
	return lCount;
}
void ZTC8_GetDimensions(const ZT_U8* iText, ZT_UPOINT* oDimensions) {// UNTESTED!
	if (oDimensions != NULL) {
		oDimensions->xU = 0; oDimensions->yU = 0; ZT_INDEX lLine = 0; ZT_INDEX lCursor = -1;
		while (iText[++lCursor] != ZTM_CHAR_NT) {++lLine; if (iText[lCursor] == ZTM_CHAR_LF) {if (oDimensions->xU < lLine) {oDimensions->xU = lLine;} lLine = 0; ++(oDimensions->yU);}}
	}
}
void ZTC8_GetDimensionsVerbatim(const ZT_U8* iText, ZT_INDEX iLength, ZT_UPOINT* oDimensions) {
	if (oDimensions != NULL) {
		oDimensions->xU = 0; oDimensions->yU = 0; ZT_INDEX lLine = 0; ZT_INDEX lCursor = -1;
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
        if (oCursor != NULL) {*(oCursor) = (lCursor - lengthTerm);} return 0x1;}} ++lCursor;
	}
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
ZT_U8* ZTC8_Unsigned(ZT_U iInteger) {return ZTC8_UnsignedBase(iInteger, 10);}
ZT_U8* ZTC8_Integer(ZT_I iInteger) {return ZTC8_IntegerBase(iInteger, 10);}
ZT_U8* ZTC8_Hex(ZT_U iInteger) {return ZTC8_UnsignedBase(iInteger, 0x10);}
//ZT_U8* ZTC8_HexSigned(ZT_I iInteger) {return ZTC8_IntegerBase(iInteger, 0x10);}
ZT_U8* ZTC8_Binary(ZT_U iInteger) {return ZTC8_UnsignedBase(iInteger, 0x2);}
//ZT_U8* ZTC8_BinarySigned(ZT_I iInteger) {return ZTC8_IntegerBase(iInteger, 0x2);}
#endif // ZTM_CHAR_MACRO
ZT_BOOL ZTC8_SeekDigitCursorMax(const ZT_U8* iText, ZT_INDEX* oCursor, ZT_INDEX iByteMax) {
    ZT_INDEX lCursor = (oCursor != NULL) ? *(oCursor) : 0;
    while (ZTC8_CursorValidMax(iText, lCursor, iByteMax)) {if (ZTC8_IsDigit(iText[lCursor])) {if (oCursor != NULL) {*(oCursor) = lCursor;} return 0x1;} ++lCursor;}
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
        ZT_INDEX lDummy = 0;
        if (ZTC8_SeekCursorMax(iText, lBOM, &lDummy, ZTM_TEXT_BOM_ABORT)) {return lType;}
    }
    return ZTM_TEXT_TYPE_NONE;
}
#define ZTC8_READDECIMAL() \
	ZT_FLAG lNegative = 0x0;\
    ZT_U lNumber = 0;\
    ZT_INDEX lDigit;\
    ZT_INDEX lChar;\
    ZT_INDEX lCursor = -1;\
    while ((lChar = iText[++lCursor]) != ZTM_CHAR_NT) {\
        if ((lDigit = lChar - ZTM_CHAR_0) < 10) {\
            lNumber *= 10;\
            if (lNegative) {lNumber -= lDigit;} else {lNumber += lDigit;}\
        } else if (lChar == ZTM_CHAR_MINUS) {\
            lNegative = 0x1;\
        }\
    }\
    return lNumber
ZT_I ZTC8_ReadInteger(const ZT_U8* iText) {ZTC8_READDECIMAL();}
ZT_U ZTC8_ReadUnsigned(const ZT_U8* iText) {ZTC8_READDECIMAL();}
ZT_U ZTC8_ReadDecimal(const ZT_U8* iText) {ZTC8_READDECIMAL();}
ZT_U ZTC8_ReadHex(const ZT_U8* iText) {
    ZT_U lNumber = 0;
    ZT_INDEX lDigit;
    ZT_INDEX lChar;
    ZT_INDEX lCursor = -1;
    while ((lChar = iText[++lCursor]) != ZTM_CHAR_NT) {
        if ((lDigit = lChar - ZTM_CHAR_0) < 10) {
            lNumber <<= 4;
            lNumber |= lDigit;
        } else if ((lDigit = lChar - ZTM_CHAR_a) < 6) {
            lNumber <<= 4;
            lNumber |= (lDigit + 10);
        } else if ((lDigit = lChar - ZTM_CHAR_A) < 6) {
            lNumber <<= 4;
            lNumber |= (lDigit + 10);
        }
    }
    return lNumber;
}
ZT_U ZTC8_ReadBinary(const ZT_U8* iText) {
    ZT_U lNumber = 0;
    ZT_INDEX lDigit;
    ZT_INDEX lChar;
    ZT_INDEX lCursor = -1;
    while ((lChar = iText[++lCursor]) != ZTM_CHAR_NT) {
        if ((lDigit = lChar - ZTM_CHAR_0) < 2) {
            lNumber <<= 1;
            lNumber |= lDigit;
        }
    }
    return lNumber;
}
#define ZTC8_READFLOATINGPOINT(TYPE) \
	ZT_FLAG lNegative = 0x0;\
	ZT_FLAG lDecimal = 0x0;\
    TYPE lUpper = 0.0;\
    TYPE lLower = 0.0;\
    TYPE lDivisor = 1;\
    ZT_INDEX lChar;\
    ZT_INDEX lDigit;\
    ZT_INDEX lCursor = -1;\
    while ((lChar = iText[++lCursor]) != ZTM_CHAR_NT) {\
        if ((lDigit = lChar - ZTM_CHAR_0) < 10) {\
            if (lDecimal) {\
                lDivisor *= 10;\
                if (lNegative) {lLower -= lDigit / lDivisor;} else {lLower += lDigit / lDivisor;}\
            } else {\
                lUpper *= 10;\
                if (lNegative) {lUpper -= lDigit;} else {lUpper += lDigit;}\
            }\
        } else if (lChar == ZTM_CHAR_DECIMAL) {\
            lDecimal = 0x1;\
        } else if (lChar == ZTM_CHAR_MINUS) {\
            lNegative = 0x1;\
        }\
    }\
    return lUpper + lLower
ZT_FLT ZTC8_ReadFloat(const ZT_U8* iText) {ZTC8_READFLOATINGPOINT(ZT_FLT);}
ZT_DBL ZTC8_ReadDouble(const ZT_U8* iText) {ZTC8_READFLOATINGPOINT(ZT_DBL);}

const ZT_U8* ZTC8_CopyTarget(const ZT_U8* iSource, ZT_U8* oTarget) {
    ZT_INDEX lCursor = -1;
    while ((oTarget[++lCursor] = iSource[lCursor]) != ZTM_CHAR_NT);
    return iSource;
}
const ZT_U8* ZTC8_CopyTargetLength(const ZT_U8* iSource, ZT_U8* oTarget, ZT_INDEX iLength) {
    ZT_INDEX lCursor = -1;
    while ((++lCursor < iLength) && ((oTarget[lCursor] = iSource[lCursor]) != ZTM_CHAR_NT));
    return iSource;
}
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
    ZT_U8* lCopy = ZTC8_CopyLength(iRoot, lLength);
    for (ZT_INDEX i = 0; i < lBranchLength; i++) {lCopy[lRootLength + i] = iBranch[i];}
    lCopy[lLength] = ZTM_CHAR_NT;
    return lCopy;
}
ZT_U8* ZTC8_MergeFreeR(ZT_U8* iRoot, const ZT_U8* iBranch) {ZT_U8* lCopy = ZTC8_Merge(iRoot, iBranch); ZTM8_Free(iRoot); return lCopy;}
ZT_U8* ZTC8_MergeFreeB(const ZT_U8* iRoot, ZT_U8* iBranch) {ZT_U8* lCopy = ZTC8_Merge(iRoot, iBranch); ZTM8_Free(iBranch); return lCopy;}
ZT_U8* ZTC8_MergeFree(ZT_U8* iRoot, ZT_U8* iBranch) {ZT_U8* lCopy = ZTC8_Merge(iRoot, iBranch); ZTM8_Free(iRoot); ZTM8_Free(iBranch); return lCopy;}
ZT_U8* ZTC8_DeleteAndCopy(ZT_U8* iDelete, const ZT_U8* iCopy) {ZTM8_Free(iDelete); return ZTC8_Copy(iCopy);}
ZT_U8* ZTC8_CopyAndDelete(const ZT_U8* iCopy, ZT_U8* iDelete) {ZT_U8* lCopy = ZTC8_Copy(iCopy); ZTM8_Free(iDelete); return lCopy;}
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
ZT_U8* ZTC8_UnsignedBase(ZT_U iInteger, ZT_U iBase) {
    ZT_U lDivisor = iBase;
    ZT_INDEX lMagnitude = 2; // includes NT offset
    while (iInteger / lDivisor) {++lMagnitude; if (!(lDivisor *= iBase) || (lDivisor % iBase)) {break;}}
    lDivisor = 1;
    ZT_U8* lNumber = ZTM8_New(lMagnitude);
    lNumber[--lMagnitude] = ZTM_CHAR_NT;
    if (iBase > 10) {
        ZT_U lDigit;
        while (--lMagnitude != (ZT_INDEX)-1) {
            lDigit = (iInteger / lDivisor) % iBase;
            lNumber[lMagnitude] = lDigit + ((lDigit < 10) ? ZTM_CHAR_0 : ZTM_CHAR_HEX_aOFF);
            lDivisor *= iBase;
        }
    } else {
        while (--lMagnitude != (ZT_INDEX)-1) {
            lNumber[lMagnitude] = ((iInteger / lDivisor) % iBase) + ZTM_CHAR_0;
            lDivisor *= iBase;
        }
    }
    return lNumber;
}
ZT_U8* ZTC8_IntegerBase(ZT_I iInteger, ZT_U iBase) {
    ZT_INDEX lIsNegative;
    ZT_U lInteger = (lIsNegative = (iInteger < 0) ? 1 : 0) ? -iInteger : iInteger;
    ZT_U lDivisor = iBase;
    ZT_INDEX lMagnitude = 2 + lIsNegative; // includes NT offset
    while (lInteger / lDivisor) {++lMagnitude; if (!(lDivisor *= iBase) || (lDivisor % iBase)) {break;}}
    lDivisor = 1;
    ZT_U8* lNumber = ZTM8_New(lMagnitude);
    lNumber[--lMagnitude] = ZTM_CHAR_NT;
    ZT_INDEX lStop = lIsNegative ? 0 : -1;
    if (iBase > 10) {
        ZT_U lDigit;
        while (--lMagnitude != lStop) {
            lDigit = (lInteger / lDivisor) % iBase;
            lNumber[lMagnitude] = lDigit + ((lDigit < 10) ? ZTM_CHAR_0 : ZTM_CHAR_HEX_aOFF);
            lDivisor *= iBase;
        }
    } else {
        while (--lMagnitude != lStop) {
            lNumber[lMagnitude] = ((lInteger / lDivisor) % iBase) + ZTM_CHAR_0;
            lDivisor *= iBase;
        }
    }
    if (lIsNegative) {lNumber[0] = ZTM_CHAR_MINUS;}
    return lNumber;
}
ZT_U8* ZTC8_Date(ZT_TIME iUnix, ZT_FLAG iFormat) {
	switch (iFormat) {
		case ZTM_DATE_ISO: return ZTC8_DateISO(iUnix);
		case ZTM_DATE_INTL: return ZTC8_DateINTL(iUnix);
		case ZTM_DATE_DE: return ZTC8_DateDE(iUnix);
		case ZTM_DATE_US: return ZTC8_DateUS(iUnix);
		case ZTM_DATE_ANSI: return ZTC8_DateANSI(iUnix);
		default: return NULL;
	}
}
#define ZTC8_DATEISO(TEXT_OUT) \
    (TEXT_OUT)[0] = ZTM_CHAR_0 + (lDate.year % 10000) / 1000;\
    (TEXT_OUT)[1] = ZTM_CHAR_0 + (lDate.year % 1000) / 100;\
    (TEXT_OUT)[2] = ZTM_CHAR_0 + (lDate.year % 100) / 10;\
    (TEXT_OUT)[3] = ZTM_CHAR_0 + (lDate.year % 10);\
    (TEXT_OUT)[4] = ZTM_CHAR_MINUS;\
    (TEXT_OUT)[5] = ZTM_CHAR_0 + (lDate.month % 100) / 10;\
    (TEXT_OUT)[6] = ZTM_CHAR_0 + (lDate.month % 10);\
    (TEXT_OUT)[7] = ZTM_CHAR_MINUS;\
    (TEXT_OUT)[8] = ZTM_CHAR_0 + (lDate.day % 100) / 10;\
    (TEXT_OUT)[9] = ZTM_CHAR_0 + (lDate.day % 10)
ZT_U8* ZTC8_DateISO(ZT_TIME iUnix) {
    ZT_U8* lISO = ZTM8_New(11);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
	ZTC8_DATEISO(lISO);
    lISO[10] = ZTM_CHAR_NT;
	return lISO;
}
ZT_U8* ZTC8_DateINTL(ZT_TIME iUnix) {
    ZT_U8* lINTL = ZTM8_New(11);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
    lINTL[0] = ZTM_CHAR_0 + (lDate.day % 100) / 10;
    lINTL[1] = ZTM_CHAR_0 + (lDate.day % 10);
	lINTL[2] = ZTM_CHAR_SLASH;
	lINTL[3] = ZTM_CHAR_0 + (lDate.month % 100) / 10;
	lINTL[4] = ZTM_CHAR_0 + (lDate.month % 10);
	lINTL[5] = ZTM_CHAR_SLASH;
    lINTL[6] = ZTM_CHAR_0 + (lDate.year % 10000) / 1000;
    lINTL[7] = ZTM_CHAR_0 + (lDate.year % 1000) / 100;
    lINTL[8] = ZTM_CHAR_0 + (lDate.year % 100) / 10;
    lINTL[9] = ZTM_CHAR_0 + (lDate.year % 10);
	lINTL[10] = ZTM_CHAR_NT;
	return lINTL;
}
ZT_U8* ZTC8_DateDE(ZT_TIME iUnix) {
    ZT_U8* lDE = ZTM8_New(11);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
    lDE[0] = ZTM_CHAR_0 + (lDate.day % 100) / 10;
    lDE[1] = ZTM_CHAR_0 + (lDate.day % 10);
	lDE[2] = ZTM_CHAR_DOT;
	lDE[3] = ZTM_CHAR_0 + (lDate.month % 100) / 10;
	lDE[4] = ZTM_CHAR_0 + (lDate.month % 10);
	lDE[5] = ZTM_CHAR_DOT;
    lDE[6] = ZTM_CHAR_0 + (lDate.year % 10000) / 1000;
    lDE[7] = ZTM_CHAR_0 + (lDate.year % 1000) / 100;
    lDE[8] = ZTM_CHAR_0 + (lDate.year % 100) / 10;
    lDE[9] = ZTM_CHAR_0 + (lDate.year % 10);
	lDE[10] = ZTM_CHAR_NT;
	return lDE;
}
ZT_U8* ZTC8_DateUS(ZT_TIME iUnix) {
    ZT_U8* lUS = ZTM8_New(11);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
	lUS[0] = ZTM_CHAR_0 + (lDate.month % 100) / 10;
	lUS[1] = ZTM_CHAR_0 + (lDate.month % 10);
	lUS[2] = ZTM_CHAR_SLASH;
    lUS[3] = ZTM_CHAR_0 + (lDate.day % 100) / 10;
    lUS[4] = ZTM_CHAR_0 + (lDate.day % 10);
	lUS[5] = ZTM_CHAR_SLASH;
    lUS[6] = ZTM_CHAR_0 + (lDate.year % 10000) / 1000;
    lUS[7] = ZTM_CHAR_0 + (lDate.year % 1000) / 100;
    lUS[8] = ZTM_CHAR_0 + (lDate.year % 100) / 10;
    lUS[9] = ZTM_CHAR_0 + (lDate.year % 10);
	lUS[10] = ZTM_CHAR_NT;
	return lUS;
}
ZT_U8* ZTC8_DateANSI(ZT_TIME iUnix) {
    ZT_U8* lANSI = ZTM8_New(12);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
	const ZT_U8* lMonth = rZTC8__MONTH[lDate.month - 1];
	lANSI[0] = lMonth[0];
	lANSI[1] = lMonth[1];
	lANSI[2] = lMonth[2];
	lANSI[3] = ZTM_CHAR_SPACE;
    lANSI[4] = ZTM_CHAR_0 + (lDate.day % 100) / 10;
    lANSI[5] = ZTM_CHAR_0 + (lDate.day % 10);
	lANSI[6] = ZTM_CHAR_SPACE;
    lANSI[7] = ZTM_CHAR_0 + (lDate.year % 10000) / 1000;
    lANSI[8] = ZTM_CHAR_0 + (lDate.year % 1000) / 100;
    lANSI[9] = ZTM_CHAR_0 + (lDate.year % 100) / 10;
    lANSI[10] = ZTM_CHAR_0 + (lDate.year % 10);
	lANSI[11] = ZTM_CHAR_NT;
	return lANSI;
}
#define ZTC8_TIME24HHMMSS(TEXT_OUT) \
    (TEXT_OUT)[0] = ZTM_CHAR_0 + (lDate.hour % 100) / 10;\
    (TEXT_OUT)[1] = ZTM_CHAR_0 + (lDate.hour % 10);\
    (TEXT_OUT)[2] = ZTM_CHAR_COLON;\
    (TEXT_OUT)[3] = ZTM_CHAR_0 + (lDate.minute % 100) / 10;\
    (TEXT_OUT)[4] = ZTM_CHAR_0 + (lDate.minute % 10);\
    (TEXT_OUT)[5] = ZTM_CHAR_COLON;\
    (TEXT_OUT)[6] = ZTM_CHAR_0 + (lDate.second % 100) / 10;\
    (TEXT_OUT)[7] = ZTM_CHAR_0 + (lDate.second % 10)
ZT_U8* ZTC8_Time24Hhmmss(ZT_TIME iUnix) {
    ZT_U8* l24Hhmmss = ZTM8_New(9);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
	ZTC8_TIME24HHMMSS(l24Hhmmss);
    l24Hhmmss[8] = ZTM_CHAR_NT;
	return l24Hhmmss;
}
ZT_U8* ZTC8_Time24Hhmm(ZT_TIME iUnix) {
    ZT_U8* l24Hhmm = ZTM8_New(6);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
    l24Hhmm[0] = ZTM_CHAR_0 + (lDate.hour % 100) / 10;
    l24Hhmm[1] = ZTM_CHAR_0 + (lDate.hour % 10);
    l24Hhmm[2] = ZTM_CHAR_COLON;
    l24Hhmm[3] = ZTM_CHAR_0 + (lDate.minute % 100) / 10;
    l24Hhmm[4] = ZTM_CHAR_0 + (lDate.minute % 10);
    l24Hhmm[5] = ZTM_CHAR_NT;
	return l24Hhmm;
}
ZT_U8* ZTC8_Time12Hhmmss(ZT_TIME iUnix) {
    ZT_U8* l12Hhmmss = ZTM8_New(12);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
	ZT_U8 lHour = lDate.hour ? ((lDate.hour > 12) ? (lDate.hour - 12) : lDate.hour) : 12;
    l12Hhmmss[0] = ZTM_CHAR_0 + (lHour % 100) / 10;
    l12Hhmmss[1] = ZTM_CHAR_0 + (lHour % 10);
    l12Hhmmss[2] = ZTM_CHAR_COLON;
    l12Hhmmss[3] = ZTM_CHAR_0 + (lDate.minute % 100) / 10;
    l12Hhmmss[4] = ZTM_CHAR_0 + (lDate.minute % 10);
    l12Hhmmss[5] = ZTM_CHAR_COLON;
    l12Hhmmss[6] = ZTM_CHAR_0 + (lDate.second % 100) / 10;
    l12Hhmmss[7] = ZTM_CHAR_0 + (lDate.second % 10);
    l12Hhmmss[8] = ZTM_CHAR_SPACE;
    l12Hhmmss[9] = (lDate.hour > 12) ? (ZTM_CHAR_A + 15) : (ZTM_CHAR_A);
    l12Hhmmss[10] = ZTM_CHAR_A + 12;
    l12Hhmmss[11] = ZTM_CHAR_NT;
	return l12Hhmmss;
}
ZT_U8* ZTC8_Time12Hhmm(ZT_TIME iUnix) {
    ZT_U8* l12Hhmmss = ZTM8_New(9);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
	ZT_U8 lHour = lDate.hour ? ((lDate.hour > 12) ? (lDate.hour - 12) : lDate.hour) : 12;
    l12Hhmmss[0] = ZTM_CHAR_0 + (lHour % 100) / 10;
    l12Hhmmss[1] = ZTM_CHAR_0 + (lHour % 10);
    l12Hhmmss[2] = ZTM_CHAR_COLON;
    l12Hhmmss[3] = ZTM_CHAR_0 + (lDate.minute % 100) / 10;
    l12Hhmmss[4] = ZTM_CHAR_0 + (lDate.minute % 10);
    l12Hhmmss[5] = ZTM_CHAR_SPACE;
    l12Hhmmss[6] = (lDate.hour > 12) ? (ZTM_CHAR_A + 15) : (ZTM_CHAR_A);
    l12Hhmmss[7] = ZTM_CHAR_A + 12;
    l12Hhmmss[8] = ZTM_CHAR_NT;
	return l12Hhmmss;
}
ZT_U8* ZTC8_ISO8601(ZT_TIME iUnix) {
    ZT_U8* lISO8601 = ZTM8_New(20);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
	ZTC8_DATEISO(lISO8601);
    lISO8601[10] = ZTM_CHAR_SPACE;
	ZTC8_TIME24HHMMSS(&lISO8601[11]);
    lISO8601[19] = ZTM_CHAR_NT;
    return lISO8601;
}
ZT_U8* ZTC8_ISO8601T(ZT_TIME iUnix) {
    ZT_U8* lISO8601 = ZTM8_New(20);
    ZT_DATE lDate;
    ZTM_Date(iUnix, &lDate);
	ZTC8_DATEISO(lISO8601);
    lISO8601[10] = ZTM_CHAR_A + 19;
	ZTC8_TIME24HHMMSS(&lISO8601[11]);
    lISO8601[19] = ZTM_CHAR_NT;
    return lISO8601;
}
ZT_U8* ZTC8_RFC1123(ZT_TIME iUnixUTC) {
    ZT_U8* lRFC1123 = ZTM8_New(30);
    ZT_DATE_EXTRA lDate;
    ZTM_DateExtra(iUnixUTC, &lDate);
	const ZT_U8* lDay = rZTC8__DAY[lDate.extra.weekday];
	const ZT_U8* lMonth = rZTC8__MONTH[lDate.month - 1];
    lRFC1123[0] = lDay[0];
    lRFC1123[1] = lDay[1];
    lRFC1123[2] = lDay[2];
    lRFC1123[3] = ZTM_CHAR_COMMA;
    lRFC1123[4] = ZTM_CHAR_SPACE;
    lRFC1123[5] = ZTM_CHAR_0 + (lDate.day % 100) / 10;
    lRFC1123[6] = ZTM_CHAR_0 + (lDate.day % 10);
    lRFC1123[7] = ZTM_CHAR_SPACE;
    lRFC1123[8] = lMonth[0];
    lRFC1123[9] = lMonth[1];
    lRFC1123[10] = lMonth[2];
    lRFC1123[11] = ZTM_CHAR_SPACE;
    lRFC1123[12] = ZTM_CHAR_0 + (lDate.year % 10000) / 1000;
    lRFC1123[13] = ZTM_CHAR_0 + (lDate.year % 1000) / 100;
    lRFC1123[14] = ZTM_CHAR_0 + (lDate.year % 100) / 10;
    lRFC1123[15] = ZTM_CHAR_0 + (lDate.year % 10);
    lRFC1123[16] = ZTM_CHAR_SPACE;
    lRFC1123[17] = ZTM_CHAR_0 + (lDate.hour % 100) / 10;
    lRFC1123[18] = ZTM_CHAR_0 + (lDate.hour % 10);
    lRFC1123[19] = ZTM_CHAR_COLON;
    lRFC1123[20] = ZTM_CHAR_0 + (lDate.minute % 100) / 10;
    lRFC1123[21] = ZTM_CHAR_0 + (lDate.minute % 10);
    lRFC1123[22] = ZTM_CHAR_COLON;
    lRFC1123[23] = ZTM_CHAR_0 + (lDate.second % 100) / 10;
    lRFC1123[24] = ZTM_CHAR_0 + (lDate.second % 10);
    lRFC1123[25] = ZTM_CHAR_SPACE;
    lRFC1123[26] = ZTM_CHAR_A + 6;
    lRFC1123[27] = ZTM_CHAR_A + 12;
    lRFC1123[28] = ZTM_CHAR_A + 19;
    lRFC1123[29] = ZTM_CHAR_NT;
    return lRFC1123;
}
ZT_U8* ZTC8_Bytes(const ZT_U8* iBytes, ZT_INDEX iLength, const ZT_U8* iDelimiter, ZT_INDEX iGrouping) {
    ZT_INDEX lLengthDelimit = (iDelimiter != NULL) ? ZTC8_GetLength(iDelimiter) : 0;
    ZT_INDEX lChars = (iLength << 1);
    if (iDelimiter != NULL && iGrouping) {lChars += ((iLength - 1) / iGrouping) * lLengthDelimit;}
    ZT_U8* lString = ZTM8_New(lChars + 1);
    ZT_INDEX lCursor = 0;
    ZT_INDEX lIndex = -1;
    while (++lIndex < iLength) {
        if (iDelimiter != NULL && iGrouping) {if (!(lIndex % iGrouping) && lIndex) {ZTC8_CopyTarget(iDelimiter, &lString[lCursor]); lCursor += lLengthDelimit;}}
        ZT_U8 lNibble = iBytes[lIndex] >> 4;
        lString[lCursor++] = (lNibble > 9) ? (lNibble + ZTM_CHAR_HEX_aOFF) : (lNibble + ZTM_CHAR_0);
        lNibble = iBytes[lIndex] & 0xf;
        lString[lCursor++] = (lNibble > 9) ? (lNibble + ZTM_CHAR_HEX_aOFF) : (lNibble + ZTM_CHAR_0);
    }
    lString[lChars] = ZTM_CHAR_NT;
    return lString;
}
ZT_U8* ZTC8_Hash(const void* iHash, ZT_INDEX iBits, const ZT_U8* iDelimiter, ZT_INDEX iGrouping) {
    const ZT_HASH1024* lHash = iHash;
    ZT_INDEX lLength = ((iBits + 7) >> 3);
	return ZTC8_Bytes(lHash->byte, lLength, iDelimiter, iGrouping);
}
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
						lPrintable[lCursor] = lChar; // maybe if LF check if prev CR as optimization?
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
ZT_INDEX ZTC8_PathIndexBranchLast(const ZT_U8* iPath) {
    ZT_INDEX lLength = ZTC8_GetLength(iPath);
    while (lLength) {if (iPath[--lLength] == ZTM_CHAR_PATH) {return lLength + 1;}}
    return 0;
}
ZT_INDEX ZTC8_PathIndexFileExtension(const ZT_U8* iPath) {
    ZT_INDEX lLength = ZTC8_GetLength(iPath);
    while (lLength) {if (iPath[--lLength] == ZTM_CHAR_FILETYPE) {return lLength;}}
    return 0;
}
ZT_INDEX ZTC8_PathIndexFileType(const ZT_U8* iPath) {
    ZT_INDEX lLength = ZTC8_GetLength(iPath);
    while (lLength) {if (iPath[--lLength] == ZTM_CHAR_FILETYPE) {return lLength + 1;}}
    return 0;
}
ZT_U8* ZTC8_PathBranchLast(const ZT_U8* iPath) {return ZTC8_Copy(&iPath[ZTC8_PathIndexBranchLast(iPath)]);}
ZT_U8* ZTC8_PathFileExtension(const ZT_U8* iPath) {return ZTC8_Copy(&iPath[ZTC8_PathIndexFileExtension(iPath)]);}
ZT_U8* ZTC8_PathFileType(const ZT_U8* iPath) {return ZTC8_Copy(&iPath[ZTC8_PathIndexFileType(iPath)]);}
ZT_U8* ZTC8_PathFileTitle(const ZT_U8* iPath) {ZT_INDEX lStart = ZTC8_PathIndexBranchLast(iPath); return ZTC8_CopyLength(&iPath[lStart], ZTC8_PathIndexFileExtension(iPath) - lStart);}
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
