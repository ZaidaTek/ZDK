/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_CHAR_H_INCLUDED
#define ZT_CHAR_H_INCLUDED

#include "ZTM.h"

// USED FOR GENERATING SPRITES OF FONTS
#define ZTM_CHAR_MASK ((ZT_CHAR)~0x0)
#define ZTM_CHAR_SET (ZTM_CHAR_MASK + 1)
// OVERFLOW PENDING REMOVAL
#define ZTM_TEXT_MAX_LENGTH 8192 // overflow protection
// CHAR DEFINES
#define ZTM_CHAR_NT 			0x00
#define ZTM_CHAR_CR 			0x0d
#define ZTM_CHAR_LF 			0x0a
#define ZTM_CHAR_QUOTES 		0x22
#define ZTM_CHAR_QUOTE 			0x27
#define ZTM_CHAR_SPACE 			0x20
#define ZTM_CHAR_MINUS 			0x2d
#define ZTM_CHAR_COLON 			0x3a
#define ZTM_CHAR_COMMA 			','
#define ZTM_CHAR_DOT 			0x2e
#define ZTM_CHAR_SLASH 			0x2f
#define ZTM_CHAR_BACKSLASH		0x5c
#define ZTM_CHAR_0 				0x30
#define ZTM_CHAR_A 				0x41
#define ZTM_CHAR_a 				0x61
#define ZTM_CHAR_ZERO			ZTM_CHAR_0
#define ZTM_CHAR_b 				(ZTM_CHAR_a + 1)
#define ZTM_CHAR_x 				(ZTM_CHAR_a + 23) // YETI Uppercase hex-keys, as in 0XFFBBCCEF? Same for binary.
#define ZTM_CHAR_2 				(ZTM_CHAR_0 + 2)
#define ZTM_CHAR_0L1 			(ZTM_CHAR_0 - 1)
#define ZTM_CHAR_9P1 			(ZTM_CHAR_0 + 10)
#define ZTM_CHAR_AL1 			(ZTM_CHAR_A - 1)
#define ZTM_CHAR_aL1 			(ZTM_CHAR_a - 1)
#define ZTM_CHAR_FP1 			(ZTM_CHAR_A + 6)
#define ZTM_CHAR_fP1 			(ZTM_CHAR_a + 6)
#define ZTM_CHAR_ZP1 			(ZTM_CHAR_A + 26)
#define ZTM_CHAR_zP1 			(ZTM_CHAR_a + 26)
#define ZTM_CHAR_HEX_AOFF 		(ZTM_CHAR_A - 10)
#define ZTM_CHAR_HEX_aOFF 		(ZTM_CHAR_a - 10)
// CHAR SYMBOLS
#define ZTM_CHAR_ESCAPE 		ZTM_CHAR_BACKSLASH
#define ZTM_CHAR_FILETYPE	 	ZTM_CHAR_DOT
// NEWLINE SYMBOL & STRING
#ifdef ZTM_ARCH__MAC
#define ZTM_CHAR_NL      		ZTM_CHAR_CR
#define ZTM_TEXT_NL				"\r"
#else
#define ZTM_CHAR_NL      		ZTM_CHAR_LF
#ifdef ZTM_ARCH__WIN
#define ZTM_TEXT_NL				"\r\n"
#else
#define ZTM_TEXT_NL				"\n"
#endif // ZTM_ARCH__WIN
#endif // ZTM_ARCH__MAC
// PATH DENOMINATOR
#ifdef ZTM_ARCH__WIN
#define ZTM_CHAR_PATH			ZTM_CHAR_BACKSLASH
#else
#define ZTM_CHAR_PATH			ZTM_CHAR_SLASH
#endif // ZTM_ARCH__WIN
// DECIMAL MARK
#define ZTM_CHAR_DECIMAL	 	ZTM_CHAR_DOT

#define ZTM_TEXT_TYPE_ASCII		0x0
#define ZTM_TEXT_TYPE_UTF8		0x1
#define ZTM_TEXT_TYPE_UTF16LE	0x2
#define ZTM_TEXT_TYPE_UTF16BE	0x4
#define ZTM_TEXT_TYPE_UTF32LE	0x8
#define ZTM_TEXT_TYPE_UTF32BE	0x10
#define ZTM_TEXT_TYPES			4
#define ZTM_TEXT_TYPE_NONE		ZTM_TEXT_TYPE_ASCII
#define ZTM_TEXT_BOM_ABORT		16

#define ZTM_DATE_ISO8601 0x1
#define ZTM_DATE_INTERNATIONAL 0x2 // DDMMYYYY
#define ZTM_DATE_AMERICAN 0x4 // MMDDYYYY
#define ZTM_DATE_ANSI_C 0x8 // MMM DD YYYY, (D < 10) ? "DD" = " D" 
#define ZTM_DATE_COMPILER ZTM_DATE_ANSI_C

#define ZTM_FONT_STYLE_NORMAL 0x0
#define ZTM_FONT_STYLE_BOLD 0x1
#define ZTM_FONT_STYLE_ITALIC 0x2
#define ZTM_FONT_STYLE_UNDERLINE 0x4
#define ZTM_FONT_STYLE_STRIKEOUT 0x8

#define ZTM_FONT_STYLE_ALIGN_RIGHT 0x10
#define ZTM_FONT_STYLE_ALIGN_CENTER 0x20
#define ZTM_FONT_STYLE_VALIGN_BOTTOM 0x40
#define ZTM_FONT_STYLE_VALIGN_CENTER 0x80
#define ZTM_FONT_STYLE_SINGLE_LINE 0x100
#define ZTM_FONT_STYLE_BREAK_WORDS 0x200

#define ZTM_FONT_STYLE_OPAQUE 0x1000
#define ZTM_FONT_STYLE_CLIP 0x2000

#define ZTM_FONT_TYPE_NONE 0x0
#define ZTM_FONT_TYPE_TTF 0x1

#define ZTM_FONT_FLAG_NONE 0x0
#define ZTM_FONT_FLAG_SOURCE_LOADED 0x1
#define ZTM_FONT_FLAG_RELOAD 0x2
#define ZTM_FONT_FLAG_COPIED_SOURCE 0x4
#define ZTM_FONT_FLAG_COPIED_NAME 0x8

#define ZTC8_NotNull(TEXT) (((TEXT) != NULL) ? (TEXT) : (const ZT_CHAR*)"")

#define ZTC8_CursorValidMax(TEXT,CURSOR,MAX) ((CURSOR < MAX) ? ((((const ZT_CHAR*)(TEXT))[CURSOR] != ZTM_CHAR_NT) ? 0x1 : 0x0) : 0x0)
#define ZTC8_CursorValid(TEXT,CURSOR) ZTC8_CURSORVALIDMAX(TEXT,CURSOR,ZTM_TEXT_MAX_LENGTH)
#define ZTC8_IsAZ(TEXT) ((TEXT)[0] > ZTM_CHAR_AL1 && (TEXT)[0] < ZTM_CHAR_ZP1)
#define ZTC8_IsAz(TEXT) ((TEXT)[0] > ZTM_CHAR_aL1 && (TEXT)[0] < ZTM_CHAR_zP1)
#define ZTC8_IsAzZ(TEXT) (((TEXT)[0] > ZTM_CHAR_aL1 && (TEXT)[0] < ZTM_CHAR_zP1) || (TEXT)[0] > ZTM_CHAR_AL1 && (TEXT)[0] < ZTM_CHAR_ZP1)
#define ZTC8_IsDigit(TEXT) ((TEXT)[0] > ZTM_CHAR_0L1 && (TEXT)[0] < ZTM_CHAR_9P1)
#define ZTC8_IsBinary(TEXT) ((TEXT)[0] > ZTM_CHAR_0L1 && (TEXT)[0] < ZTM_CHAR_2)
#define ZTC8_IsHexAF(TEXT) ((TEXT)[0] > ZTM_CHAR_AL1 && (TEXT)[0] < ZTM_CHAR_FP1)
#define ZTC8_IsHexAf(TEXT) ((TEXT)[0] > ZTM_CHAR_aL1 && (TEXT)[0] < ZTM_CHAR_fP1)
#define ZTC8_IsHexAfF(TEXT) (((TEXT)[0] > ZTM_CHAR_aL1 && (TEXT)[0] < ZTM_CHAR_fP1) || ((TEXT)[0] > ZTM_CHAR_AL1 && (TEXT)[0] < ZTM_CHAR_FP1))
#define ZTC8_IsCRLF(TEXT) (((TEXT)[0] == ZTM_CHAR_CR) ? (((TEXT)[1] == ZTM_CHAR_LF) ? 0x1 : 0x0) : 0x0)
#define ZTC8_IsDblCRLF(TEXT) (((TEXT)[0] == ZTM_CHAR_CR) ? (((TEXT)[1] == ZTM_CHAR_LF) ? (((TEXT)[2] == ZTM_CHAR_CR) ? (((TEXT)[3] == ZTM_CHAR_LF) ? 0x1 : 0x0) : 0x0) : 0x0) : 0x0)
#define ZTC8_IsAlphanumeric(TEXT) (ZTC8_IsAz(TEXT) || ZTC8_IsAZ(TEXT) || ZTC8_IsDigit(TEXT))
#define ZTC8_SeekDigit(TEXT) ZTC8_SeekDigitCursorMax((TEXT),NULL,ZTM_TEXT_MAX_LENGTH)
#define ZTC8_SeekDigitCursor(TEXT,CURSOR) ZTC8_SeekDigitCursorMax((TEXT),(CURSOR),ZTM_TEXT_MAX_LENGTH)
#define ZTC8_SeekCRLF(TEXT) ZTC8_SeekCRLFCursorMax((TEXT),NULL,ZTM_TEXT_MAX_LENGTH)
#define ZTC8_SeekCRLFCursor(TEXT,CURSOR) ZTC8_SeekCRLFCursorMax((TEXT),(CURSOR),ZTM_TEXT_MAX_LENGTH)
#define ZTC8_Seek(TEXT,SEARCH) ZTC8_SeekCursorMax((TEXT),(SEARCH),NULL,ZTM_TEXT_MAX_LENGTH)
#define ZTC8_SeekCursor(TEXT,SEARCH,CURSOR) ZTC8_SeekCursorMax((TEXT),(SEARCH),(CURSOR),ZTM_TEXT_MAX_LENGTH)
#define ZTC8_GetDigit(TEXT) (ZTC8_IsDigit(TEXT) ? ((TEXT)[0] - ZTM_CHAR_0) : 10)
#define ZTC8_GetBinary(TEXT) (ZTC8_IsBinary(TEXT) ? ((TEXT)[0] - ZTM_CHAR_0) : 0x2)
#define ZTC8_GetHex(TEXT) (ZTC8_IsDigit(TEXT) ? ((TEXT)[0] - ZTM_CHAR_0) : (ZTC8_IsHexAf(TEXT) ? ((TEXT)[0] - ZTM_CHAR_HEX_aOFF) : (ZTC8_IsHexAF(TEXT) ? (TEXT)[0] - ZTM_CHAR_HEX_AOFF : 0x10)))

// ***All*** functions will only null-check pointers if they are optional
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
const ZT_U8* ZTC8__DATE__(void);
const ZT_U8* ZTC8__DATE__Set(const ZT_U8* i__DATE__, const ZT_U8* i__TIME__); // if no call, ZTC8__DATE__() returns ZTM_CHAR_NT
#ifndef ZTM_CHAR_MACRO
ZT_INDEX ZTC8_GetLength(const ZT_U8* iText); // gets number of characters in array - does not include NT
ZT_INDEX ZTC8_CountCharVerbatim(const ZT_U8* iHaystack, ZT_INDEX iLength, ZT_U8 iNeedle);
void ZTC8_GetDimensionsVerbatim(const ZT_U8* iText, ZT_INDEX iLength, ZT_POINT* oDimensions);
ZT_BOOL ZTC8_Match(const ZT_U8* iHaystack, const ZT_U8* iNeedle); // returns false if NT is first found in iHaystack or if no match
ZT_BOOL ZTC8_MatchExact(const ZT_U8* iText1, const ZT_U8* iText2); // returns true only if completely identical, including NT, ergo length
ZT_BOOL ZTC8_MatchLenient(const ZT_U8* iText1, const ZT_U8* iText2); // returns false upon mismatch, else exits true if either input terminates
ZT_BOOL ZTC8_SeekCursorMax(const ZT_U8* iText, const ZT_U8* iSearch, ZT_INDEX* oCursor, ZT_INDEX iByteMax); // oCursor is *both* input and output
ZT_FLAG ZTC8_Escape(ZT_FLAG iEscape, ZT_CHAR iChar);
#else
#define ZTC8_GetLength(TEXT) ({ZT_INDEX rGETLENGTH_n = -1; while ((TEXT)[++rGETLENGTH_n] != ZTM_CHAR_NT); rGETLENGTH_n;})
#define ZTC8_CountCharVerbatim(HAYSTACK,LENGTH,NEEDLE) ({ZT_INDEX rCOUNTCHARV_n = 0; ZT_INDEX rCOUNTCHARV_i = -1; while (++rCOUNTCHARV_i < (LENGTH)) {if ((HAYSTACK)[rCOUNTCHARV_i] == (NEEDLE)) {++rCOUNTCHARV_n;}} rCOUNTCHARV_n;})
#define ZTC8_GetDimensionsVerbatim(TEXT,LENGTH,DIM_OUT) ({\
	if ((ZT_POINT*)(DIM_OUT) != (ZT_POINT*)NULL) {\
		ZT_INDEX rGETDIMENSIONSV_l = 0; (DIM_OUT)->xU = 0; (DIM_OUT)->yU = 0; ZT_INDEX rGETDIMENSIONSV_i = -1;\
		while (++rGETDIMENSIONSV_i < (LENGTH)) {++rGETDIMENSIONSV_l; if ((TEXT)[rGETDIMENSIONSV_i] == ZTM_CHAR_LF) {if ((DIM_OUT)->xU < rGETDIMENSIONSV_l) {(DIM_OUT)->xU = rGETDIMENSIONSV_l;} rGETDIMENSIONSV_l = 0; ++((DIM_OUT)->yU);}}\
	}\
})
#define ZTC8_Match(HAYSTACK,NEEDLE) ({\
	ZT_BOOL rMATCH_m = 0x1; ZT_INDEX rMATCH_i = -1;\
    while (((const ZT_CHAR*)(NEEDLE))[++rMATCH_i] != ZTM_CHAR_NT) {if ((((const ZT_CHAR*)(HAYSTACK))[rMATCH_i] != ((const ZT_CHAR*)(NEEDLE))[rMATCH_i]) || (((const ZT_CHAR*)(HAYSTACK))[rMATCH_i] == ZTM_CHAR_NT)) {rMATCH_m = 0x0; break;}}\
	rMATCH_m;\
})
#define ZTC8_MatchExact(TEXT1,TEXT2) ({\
	ZT_BOOL rMATCHEXACT_m = 0x0; ZT_INDEX rMATCHEXACT_i = 0;\
	while ((TEXT1)[rMATCHEXACT_i] == (TEXT2)[rMATCHEXACT_i]) {if ((TEXT1)[rMATCHEXACT_i] == ZTM_CHAR_NT) {rMATCHEXACT_m = 0x1; break;} ++rMATCHEXACT_i;}\
	rMATCHEXACT_m;\
})
#define ZTC8_MatchLenient(TEXT1,TEXT2) ({\
	ZT_BOOL rMATCHL_m = 0x1; ZT_INDEX rMATCHL_i = -1;\
	while ((TEXT1)[++rMATCHL_i] != ZTM_CHAR_NT && (TEXT2)[rMATCHL_i] != ZTM_CHAR_NT) {if ((TEXT1)[rMATCHL_i] != (TEXT2)[rMATCHL_i]) {rMATCHL_m = 0x0; break;}}\
	rMATCHL_m;\
})
#define ZTC8_SeekCursorMax(HAYSTACK,NEEDLE,CURSOR_INOUT,MAX) ({\
	ZT_FLAG rSEEKCURSORM_f = 0x0; ZT_INDEX rSEEKCURSORM_i = ((ZT_INDEX*)(CURSOR_INOUT) != (ZT_INDEX*)NULL) ? *((ZT_INDEX*)(CURSOR_INOUT)) : 0;\
    while (ZTC8_CursorValidMax((HAYSTACK), rSEEKCURSORM_i, MAX)) {if (ZTC8_Match(&((const ZT_CHAR*)(HAYSTACK))[rSEEKCURSORM_i], ((const ZT_CHAR*)(NEEDLE)))) {\
        if ((ZT_INDEX*)(CURSOR_INOUT) != (ZT_INDEX*)NULL) {*((ZT_INDEX*)(CURSOR_INOUT)) = rSEEKCURSORM_i;} rSEEKCURSORM_f = 0x1; break;}\
		++rSEEKCURSORM_i;\
	}\
    rSEEKCURSORM_f;\
})
#define ZTC8_Escape(FLAG,CHAR) ({\
	if (FLAG) {\
		if (FLAG & 0x1) {\
			FLAG &= ~0x1;\
		} else if (FLAG & 0x2 && (CHAR == ZTM_CHAR_QUOTES)) {\
			FLAG &= ~0x2;\
		} else if (FLAG & 0x4 && (CHAR == ZTM_CHAR_QUOTE)) {\
			FLAG &= ~0x4;\
		}\
	} else if (CHAR == ZTM_CHAR_ESCAPE) {\
		FLAG |= 0x1;\
	} else if (CHAR == ZTM_CHAR_QUOTES) {\
		FLAG |= 0x2;\
	} else if (CHAR == ZTM_CHAR_QUOTE) {\
		FLAG |= 0x4;\
	}\
	FLAG;\
})
#endif // ZTM_CHAR_MACRO
//ZT_INDEX ZTC8_Count(const ZT_U8* iHaystack, const ZT_U8* iNeedle);// UNTESTED!
ZT_INDEX ZTC8_CountChar(const ZT_U8* iHaystack, ZT_U8 iNeedle);// UNTESTED!
void ZTC8_GetDimensions(const ZT_U8* iText, ZT_POINT* oDimensions);// UNTESTED!
ZT_BOOL ZTC8_SeekDigitCursorMax(const ZT_U8* iText, ZT_INDEX* oCursor, ZT_INDEX iByteMax);
ZT_BOOL ZTC8_SeekCRLFCursorMax(const ZT_U8* iText, ZT_INDEX* oCursor, ZT_INDEX iByteMax);
ZT_FLAG ZTC8_SeekBOM(const void* iText);
ZT_I ZTC8_ReadNumber(const ZT_U8* iText); // TODO implement all-detected-ok
ZT_U ZTC8_ReadUnsigned(const ZT_U8* iText);
ZT_I ZTC8_ReadInteger(const ZT_U8* iText);
ZT_U ZTC8_ReadBinary(const ZT_U8* iText);
ZT_U ZTC8_ReadHex(const ZT_U8* iText);
ZT_FLT ZTC8_ReadFloat(const ZT_U8* iText);
ZT_DBL ZTC8_ReadDouble(const ZT_U8* iText);
void ZTC8_ReadDate_ANSI_C(const ZT_U8* iText, ZT_DATE* oDate);
void ZTC8_ReadTime_ANSI_C(const ZT_U8* iText, ZT_DATE* oDate);
const ZT_U8* ZTC8_CopyTarget(const ZT_U8* iSource, ZT_U8* oTarget);
ZT_U8* ZTC8_CopyLength(const ZT_U8* iText, ZT_INDEX iLength);
ZT_U8* ZTC8_CopyModulating(const ZT_U8* iText, ZT_INDEX iLength);
ZT_U8* ZTC8_Copy(const ZT_U8* iText);
ZT_U8* ZTC8_Merge(const ZT_U8* iRoot, const ZT_U8* iBranch);
ZT_U8* ZTC8_MergeFreeR(ZT_U8* iRoot, const ZT_U8* iBranch);
ZT_U8* ZTC8_MergeFreeB(const ZT_U8* iRoot, ZT_U8* iBranch);
ZT_U8* ZTC8_MergeFree(ZT_U8* iRoot, ZT_U8* iBranch);
ZT_U8* ZTC8_CopyAndFree(const ZT_U8* iCopy, ZT_U8* iDelete); // do two things on one line!
ZT_U8* ZTC8_FreeAndCopy(ZT_U8* iDelete, const ZT_U8* iCopy); // name-sequences are tantamount
ZT_U8* ZTC8_Unsigned(ZT_U iInteger);
ZT_U8* ZTC8_Integer(ZT_I iInteger);
ZT_U8* ZTC8_Hex(ZT_U iInteger);
ZT_U8* ZTC8_HexSigned(ZT_I iInteger);
ZT_U8* ZTC8_Binary(ZT_U iInteger);
ZT_U8* ZTC8_BinarySigned(ZT_I iInteger);
ZT_U8* ZTC8_HashString(const void* iHash, const ZT_U8* iDelimiter, ZT_INDEX iBits, ZT_INDEX iGrouping);
ZT_U8* ZTC8_DateISO8601(ZT_TIME iUnix);
ZT_U8* ZTC8_DateRFC1123(ZT_TIME iUnix);
ZT_U8* ZTC8_Replace(const ZT_U8* iHaystack, const ZT_U8* iNeedle, const ZT_U8* iReplacement);
//ZT_BOOL ZTC8_WinCLI(ZT_INDEX argc, ZT_U8** argv, const ZT_U8* iSearch, ZT_INDEX* oIndexFound);
//ZT_U8* ZTC8_ConvertUTF8ToWin1252(const ZT_U8* iText);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_CHAR_H_INCLUDED
