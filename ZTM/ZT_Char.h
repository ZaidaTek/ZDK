/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_CHAR_H_INCLUDED
#define ZT_CHAR_H_INCLUDED

#include "ZTM.h"

#define ZTM_CHAR_MAP_ANSI 0x0
#define ZTM_CHAR_MAP ZTM_CHAR_MAP_ANSI
#define ZTM_TEXT_MAX_LENGTH 8192 // fallback-length for some functions if no length parameter is passed
// CHAR MAPPING ANSI
#define ZTM_CHAR_ANSI_NT 			0x00
#define ZTM_CHAR_ANSI_CR 			0x0d
#define ZTM_CHAR_ANSI_LF 			0x0a
#define ZTM_CHAR_ANSI_SPACE 		0x20
#define ZTM_CHAR_ANSI_QUOTES 		0x22
#define ZTM_CHAR_ANSI_QUOTE 		0x27
#define ZTM_CHAR_ANSI_COLON 		0x3a
#define ZTM_CHAR_ANSI_COMMA 		0x2c
#define ZTM_CHAR_ANSI_DOT 			0x2e
#define ZTM_CHAR_ANSI_MINUS 		0x2d
#define ZTM_CHAR_ANSI_UNDERSCORE	0x5f
#define ZTM_CHAR_ANSI_SLASH 		0x2f
#define ZTM_CHAR_ANSI_BACKSLASH		0x5c
#define ZTM_CHAR_ANSI_0 			0x30
#define ZTM_CHAR_ANSI_A 			0x41
#define ZTM_CHAR_ANSI_a 			0x61
#define ZTM_CHAR_ANSI_PRINT_MIN		0x20
#define ZTM_CHAR_ANSI_PRINT_MAX		0x7E
// CHAR MAPPING
#if (ZTM_CHAR_MAP == ZTM_CHAR_MAP_ANSI)
#define ZTM_CHAR_NT 			ZTM_CHAR_ANSI_NT
#define ZTM_CHAR_CR 			ZTM_CHAR_ANSI_CR
#define ZTM_CHAR_LF 			ZTM_CHAR_ANSI_LF
#define ZTM_CHAR_SPACE 			ZTM_CHAR_ANSI_SPACE
#define ZTM_CHAR_QUOTES 		ZTM_CHAR_ANSI_QUOTES
#define ZTM_CHAR_QUOTE 			ZTM_CHAR_ANSI_QUOTE
#define ZTM_CHAR_COLON 			ZTM_CHAR_ANSI_COLON
#define ZTM_CHAR_COMMA 			ZTM_CHAR_ANSI_COMMA
#define ZTM_CHAR_DOT 			ZTM_CHAR_ANSI_DOT
#define ZTM_CHAR_MINUS 			ZTM_CHAR_ANSI_MINUS
#define ZTM_CHAR_UNDERSCORE		ZTM_CHAR_ANSI_UNDERSCORE
#define ZTM_CHAR_SLASH 			ZTM_CHAR_ANSI_SLASH
#define ZTM_CHAR_BACKSLASH		ZTM_CHAR_ANSI_BACKSLASH
#define ZTM_CHAR_0 				ZTM_CHAR_ANSI_0
#define ZTM_CHAR_A 				ZTM_CHAR_ANSI_A
#define ZTM_CHAR_a 				ZTM_CHAR_ANSI_a
#define ZTM_CHAR_PRINT_MIN		ZTM_CHAR_ANSI_PRINT_MIN
#define ZTM_CHAR_PRINT_MAX		ZTM_CHAR_ANSI_PRINT_MAX
#endif // ZTM_CHAR_MAP
// CHAR RELATIONAL MAPPING
#define ZTM_CHAR_ZERO			ZTM_CHAR_0
#define ZTM_CHAR_b 				(ZTM_CHAR_a + 1)
#define ZTM_CHAR_x 				(ZTM_CHAR_a + 23) // YETI Uppercase hex-keys, as in 0XFFBBCCEF? Same for binary.
#define ZTM_CHAR_B 				(ZTM_CHAR_A + 1)
#define ZTM_CHAR_X 				(ZTM_CHAR_A + 23) // YETI Uppercase hex-keys, as in 0XFFBBCCEF? Same for binary.
#define ZTM_CHAR_2 				(ZTM_CHAR_0 + 2)
#define ZTM_CHAR_0L1 			(ZTM_CHAR_0 - 1)
#define ZTM_CHAR_9P1 			(ZTM_CHAR_0 + 10)
#define ZTM_CHAR_AL1 			(ZTM_CHAR_A - 1)
#define ZTM_CHAR_aL1 			(ZTM_CHAR_a - 1)
#define ZTM_CHAR_FP1 			(ZTM_CHAR_A + 6)
#define ZTM_CHAR_fP1 			(ZTM_CHAR_a + 6)
#define ZTM_CHAR_VP1 			(ZTM_CHAR_A + 22)
#define ZTM_CHAR_vP1 			(ZTM_CHAR_a + 22)
#define ZTM_CHAR_ZP1 			(ZTM_CHAR_A + 26)
#define ZTM_CHAR_zP1 			(ZTM_CHAR_a + 26)
#define ZTM_CHAR_HEX_AOFF 		(ZTM_CHAR_A - 10)
#define ZTM_CHAR_HEX_aOFF 		(ZTM_CHAR_a - 10)
// CHAR SYMBOLS
#define ZTM_CHAR_ESCAPE 		ZTM_CHAR_BACKSLASH
#define ZTM_CHAR_FILETYPE	 	ZTM_CHAR_DOT
// NEWLINE SYMBOL & STRING
/*
#ifdef ZTM__OS__APPLE
#define ZTM_CHAR_NL      		ZTM_CHAR_CR
#define ZTM_TEXT_NL				((const ZT_CHAR*)"\r")
#else
#define ZTM_CHAR_NL      		ZTM_CHAR_LF
#endif // ZTM__OS__APPLE
*/
#define ZTM_CHAR_NL      		ZTM_CHAR_LF
#ifdef ZTM__OS__WINDOWS
#define ZTM_TEXT_NL				((const ZT_CHAR*)"\r\n")
#else
#define ZTM_TEXT_NL				((const ZT_CHAR*)"\n")
#endif // ZTM__OS__WINDOWS
// PATH DENOMINATOR
#ifdef ZTM__OS__WINDOWS
#define ZTM_CHAR_PATH			ZTM_CHAR_BACKSLASH
#define ZTM_TEXT_PATH			((const ZT_CHAR*)"\\")
#else
#define ZTM_CHAR_PATH			ZTM_CHAR_SLASH
#define ZTM_TEXT_PATH			((const ZT_CHAR*)"/")
#endif // ZTM__OS__WINDOWS
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

#define ZTM_DATE_ISO 0x1 // YYYY-MM-DD
#define ZTM_DATE_INTL 0x2 // DD/MM/YYYY
#define ZTM_DATE_DE 0x4 // DD.MM.YYYY
#define ZTM_DATE_US 0x8 // MM/DD/YYYY
#define ZTM_DATE_ANSI 0x10 // MMM DD YYYY, (D < 10) ? " D" : "DD"
#define ZTM_DATE_COMPILER ZTM_DATE_ANSI

///PENDING MOVE TO ZTK:
///USED FOR GENERATING SPRITES OF FONTS
///MOVED TO ZTK, STILL NEEDED FOR ZTMWV
#define ZTM_TEXT_STYLE_NORMAL 0x0
#define ZTM_TEXT_STYLE_BOLD 0x1
#define ZTM_TEXT_STYLE_ITALIC 0x2
#define ZTM_TEXT_STYLE_UNDERLINE 0x4
#define ZTM_TEXT_STYLE_STRIKEOUT 0x8
#define ZTM_TEXT_STYLE_ALIGN_RIGHT 0x10
#define ZTM_TEXT_STYLE_ALIGN_CENTER 0x20
#define ZTM_TEXT_STYLE_VALIGN_BOTTOM 0x40
#define ZTM_TEXT_STYLE_VALIGN_CENTER 0x80
#define ZTM_TEXT_STYLE_SINGLE_LINE 0x100
#define ZTM_TEXT_STYLE_BREAK_WORDS 0x200
#define ZTM_TEXT_STYLE_OPAQUE 0x1000
#define ZTM_TEXT_STYLE_CLIP 0x2000

//#define ZTC8_NotNull(TEXT) (((TEXT) != NULL) ? (TEXT) : (const ZT_CHAR*)"") // what was this for?

#define ZTC8_CursorValidMax(TEXT,CURSOR,MAX) ((CURSOR < MAX) ? ((((const ZT_CHAR*)(TEXT))[CURSOR] != ZTM_CHAR_NT) ? 0x1 : 0x0) : 0x0)
#define ZTC8_CursorValid(TEXT,CURSOR) ZTC8_CURSORVALIDMAX(TEXT,CURSOR,ZTM_TEXT_MAX_LENGTH)

#define ZTC8_IsAZ(CHAR) ((((CHAR) < ZTM_CHAR_ZP1) && ((CHAR) > ZTM_CHAR_AL1)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsAz(CHAR) ((((CHAR) < ZTM_CHAR_zP1) && ((CHAR) > ZTM_CHAR_aL1)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsAzAZ(CHAR) (((((CHAR) < ZTM_CHAR_ZP1) && ((CHAR) > ZTM_CHAR_AL1)) || (((CHAR) < ZTM_CHAR_zP1) && ((CHAR) > ZTM_CHAR_aL1))) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsDigit(CHAR) ((((CHAR) < ZTM_CHAR_9P1) && ((CHAR) > ZTM_CHAR_0L1)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsBinary(CHAR) ((((CHAR) < ZTM_CHAR_2) && ((CHAR) > ZTM_CHAR_0L1)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsHexAF(CHAR) ((((CHAR) < ZTM_CHAR_FP1) && ((CHAR) > ZTM_CHAR_AL1)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsHexAf(CHAR) ((((CHAR) < ZTM_CHAR_fP1) && ((CHAR) > ZTM_CHAR_aL1)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsHexAfAF(CHAR) (((((CHAR) < ZTM_CHAR_fP1) && ((CHAR) > ZTM_CHAR_aL1)) || (((CHAR) < ZTM_CHAR_FP1) && ((CHAR) > ZTM_CHAR_AL1))) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsHex32AV(CHAR) ((((CHAR) < ZTM_CHAR_VP1) && ((CHAR) > ZTM_CHAR_AL1)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsHex32Av(CHAR) ((((CHAR) < ZTM_CHAR_vP1) && ((CHAR) > ZTM_CHAR_aL1)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsHex32AvAV(CHAR) (((((CHAR) < ZTM_CHAR_vP1) && ((CHAR) > ZTM_CHAR_aL1)) || (((CHAR) < ZTM_CHAR_VP1) && ((CHAR) > ZTM_CHAR_AL1))) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsAlphanumeric(CHAR) (((ZTC8_IsAzAZ(CHAR) != ZT_FALSE) || (ZTC8_IsDigit(CHAR) != ZT_FALSE)) ? ZT_TRUE : ZT_FALSE)
#define ZTC8_IsBase32AV(CHAR) ZTC8_IsHex32AV(CHAR)
#define ZTC8_IsBase32Av(CHAR) ZTC8_IsHex32Av(CHAR)
#define ZTC8_IsBase32AvAV(CHAR) ZTC8_IsHex32AvAV(CHAR)
#define ZTC8_IsHex36AZ(CHAR) ZTC8_IsAZ(CHAR)
#define ZTC8_IsHex36Az(CHAR) ZTC8_IsAz(CHAR)
#define ZTC8_IsHex36AzAZ(CHAR) ZTC8_IsAzAZ(CHAR)
#define ZTC8_IsBase36AZ(CHAR) ZTC8_IsAZ(CHAR)
#define ZTC8_IsBase36Az(CHAR) ZTC8_IsAz(CHAR)
#define ZTC8_IsBase36AzAZ(CHAR) ZTC8_IsAzAZ(CHAR)

#define ZTC8_IsCRLF(TEXT) (((TEXT)[0] == ZTM_CHAR_CR) ? (((TEXT)[1] == ZTM_CHAR_LF) ? 0x1 : 0x0) : 0x0)
#define ZTC8_IsDblCRLF(TEXT) (((TEXT)[0] == ZTM_CHAR_CR) ? (((TEXT)[1] == ZTM_CHAR_LF) ? (((TEXT)[2] == ZTM_CHAR_CR) ? (((TEXT)[3] == ZTM_CHAR_LF) ? 0x1 : 0x0) : 0x0) : 0x0) : 0x0)

#define ZTC8_SeekDigit(TEXT) ZTC8_SeekDigitCursorMax((TEXT),NULL,ZTM_TEXT_MAX_LENGTH)
#define ZTC8_SeekDigitCursor(TEXT,CURSOR) ZTC8_SeekDigitCursorMax((TEXT),(CURSOR),ZTM_TEXT_MAX_LENGTH)
#define ZTC8_SeekCRLF(TEXT) ZTC8_SeekCRLFCursorMax((TEXT),NULL,ZTM_TEXT_MAX_LENGTH)
#define ZTC8_SeekCRLFCursor(TEXT,CURSOR) ZTC8_SeekCRLFCursorMax((TEXT),(CURSOR),ZTM_TEXT_MAX_LENGTH)
#define ZTC8_Seek(TEXT,SEARCH) ZTC8_SeekCursorMax((TEXT),(SEARCH),NULL,ZTM_TEXT_MAX_LENGTH)
#define ZTC8_SeekCursor(TEXT,SEARCH,CURSOR) ZTC8_SeekCursorMax((TEXT),(SEARCH),(CURSOR),ZTM_TEXT_MAX_LENGTH)

#define ZTC8_GetDigit(CHAR) ((ZTC8_IsDigit(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_0) : 10)
#define ZTC8_GetBinary(CHAR) ((ZTC8_IsBinary(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_0) : 0x2)
#define ZTC8_GetHex(CHAR) ((ZTC8_IsDigit(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_0) : ((ZTC8_IsHexAf(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_HEX_aOFF) : ((ZTC8_IsHexAF(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_HEX_AOFF) : 0x10)))
///NEED TO IMPLEMENT FOR W/O MACRO (wait, do these even have macro-less implementations?)
#define ZTC8_GetHex32(CHAR) ((ZTC8_IsDigit(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_0) : ((ZTC8_IsHex32Av(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_HEX_aOFF) : ((ZTC8_IsHex32AV(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_HEX_AOFF) : 0x20)))
#define ZTC8_GetHex36(CHAR) ((ZTC8_IsDigit(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_0) : ((ZTC8_IsAz(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_HEX_aOFF) : ((ZTC8_IsAZ(CHAR) != ZT_FALSE) ? ((CHAR) - ZTM_CHAR_HEX_AOFF) : 0x24)))
#define ZTC8_GetBase32(CHAR) ZTC8_GetHex32(CHAR)
#define ZTC8_GetBase36(CHAR) ZTC8_GetHex36(CHAR)
// ***All*** functions will only null-check pointers if they are optional
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#define ZTC8_FormatLength(TEXT,...) ({ZT_SIZE mLENGTH = 0; ZTC8_FormatTarget(NULL, &mLENGTH, (TEXT), __VA_ARGS__); mLENGTH;})
//ZT_SIZE ZTC8_FormatLength(iFormatText, ...);
ZT_CHAR* ZTC8_FormatTarget(ZT_CHAR* oTarget, ZT_SIZE* ioCapacity, const ZT_CHAR* iFormatText, ...);
const ZT_U8* ZTC8__DATE__(void);
const ZT_U8* ZTC8__DATE__Set(const ZT_U8* i__DATE__, const ZT_U8* i__TIME__); // if no call, ZTC8__DATE__() returns ZTM_CHAR_NT
/*void ZTC8_ReadDate_ANSI_C(const ZT_U8* iText, ZT_DATE* oDate);
void ZTC8_ReadTime_ANSI_C(const ZT_U8* iText, ZT_DATE* oDate);*/
#ifndef ZTM_CHAR_MACRO
ZT_INDEX ZTC8_GetLength(const ZT_U8* iText); // gets number of characters in array - does not include NT
ZT_INDEX ZTC8_CountChar(const ZT_U8* iHaystack, ZT_U8 iNeedle);// UNTESTED!
ZT_INDEX ZTC8_CountCharVerbatim(const ZT_U8* iHaystack, ZT_INDEX iLength, ZT_U8 iNeedle);
ZT_INDEX ZTC8_Count(const ZT_U8* iHaystack, const ZT_U8* iNeedle);// UNTESTED!
ZT_INDEX ZTC8_CountVerbatim(const ZT_U8* iHaystack, ZT_INDEX iLength, const ZT_U8* iNeedle);// UNTESTED!
void ZTC8_GetDimensions(const ZT_U8* iText, ZT_POINT* oDimensions);// UNTESTED!
void ZTC8_GetDimensionsVerbatim(const ZT_U8* iText, ZT_INDEX iLength, ZT_POINT* oDimensions);
ZT_BOOL ZTC8_Match(const ZT_U8* iHaystack, const ZT_U8* iNeedle); // returns false if NT is first found in iHaystack or if no match
ZT_BOOL ZTC8_MatchExact(const ZT_U8* iText1, const ZT_U8* iText2); // returns true only if completely identical, including NT, ergo length
ZT_BOOL ZTC8_MatchLenient(const ZT_U8* iText1, const ZT_U8* iText2); // returns false upon mismatch, else exits true if either input terminates
ZT_BOOL ZTC8_SeekCursorMax(const ZT_U8* iText, const ZT_U8* iSearch, ZT_INDEX* oCursor, ZT_INDEX iByteMax); // oCursor is *both* input and output
ZT_FLAG ZTC8_Escape(ZT_FLAG iEscape, ZT_CHAR iChar);
ZT_U8* ZTC8_Unsigned(ZT_U iInteger);
ZT_U8* ZTC8_Integer(ZT_I iInteger);
ZT_U8* ZTC8_Hex(ZT_U iInteger);
//ZT_U8* ZTC8_HexSigned(ZT_I iInteger);
ZT_U8* ZTC8_Binary(ZT_U iInteger);
//ZT_U8* ZTC8_BinarySigned(ZT_I iInteger);
#else
#define ZTC8_GetLength(TEXT) ({ZT_INDEX rGETLENGTH_n = -1; while ((TEXT)[++rGETLENGTH_n] != ZTM_CHAR_NT); rGETLENGTH_n;})
#define ZTC8_CountChar(HAYSTACK,NEEDLE) ({ZT_INDEX rCOUNTCHAR_n = 0; ZT_INDEX rCOUNTCHAR_i = -1; while ((HAYSTACK)[++rCOUNTCHAR_i] != ZTM_CHAR_NT) {if ((HAYSTACK)[rCOUNTCHAR_i] == (NEEDLE)) {++rCOUNTCHAR_n;}} rCOUNTCHAR_n;})
#define ZTC8_CountCharVerbatim(HAYSTACK,LENGTH,NEEDLE) ({ZT_INDEX rCOUNTCHARV_n = 0; ZT_INDEX rCOUNTCHARV_i = -1; while (++rCOUNTCHARV_i < (LENGTH)) {if ((HAYSTACK)[rCOUNTCHARV_i] == (NEEDLE)) {++rCOUNTCHARV_n;}} rCOUNTCHARV_n;})
#define ZTC8_Count(HAYSTACK,NEEDLE) ({ZT_INDEX rCOUNT_n = 0; ZT_INDEX rCOUNT_i = -1; while ((HAYSTACK)[rCOUNT_i] != ZTM_CHAR_NT) {if (ZTC8_Match((HAYSTACK), (NEEDLE))) {++rCOUNT_n;}} rCOUNT_n;})
#define ZTC8_CountVerbatim(HAYSTACK,LENGTH,NEEDLE) ({ZT_INDEX rCOUNTV_n = 0; ZT_INDEX rCOUNTV_i = -1; while (++rCOUNTV_i < (LENGTH)) {if (ZTC8_Match((HAYSTACK), (NEEDLE))) {++rCOUNTV_n;}} rCOUNTV_n;})
#define ZTC8_GetDimensions(TEXT,DIM_OUT) ({\
	if ((ZT_POINT*)(DIM_OUT) != (ZT_POINT*)NULL) {\
		(DIM_OUT)->xU = 0; (DIM_OUT)->yU = 0; ZT_INDEX rGETDIMENSIONS_l = 0; ZT_INDEX rGETDIMENSIONS_i = -1;\
		while ((TEXT)[++rGETDIMENSIONS_i] != ZTM_CHAR_NT) {++rGETDIMENSIONS_l; if ((TEXT)[rGETDIMENSIONS_i] == ZTM_CHAR_LF) {if ((DIM_OUT)->xU < rGETDIMENSIONS_l) {(DIM_OUT)->xU = rGETDIMENSIONS_l;} rGETDIMENSIONS_l = 0; ++((DIM_OUT)->yU);}}\
	}\
})
#define ZTC8_GetDimensionsVerbatim(TEXT,LENGTH,DIM_OUT) ({\
	if ((ZT_POINT*)(DIM_OUT) != (ZT_POINT*)NULL) {\
		(DIM_OUT)->xU = 0; (DIM_OUT)->yU = 0; ZT_INDEX rGETDIMENSIONSV_l = 0; ZT_INDEX rGETDIMENSIONSV_i = -1;\
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
#define ZTC8_Unsigned(NUMBER) ZTC8_UnsignedBase((NUMBER),10)
#define ZTC8_Integer(NUMBER) ZTC8_IntegerBase((NUMBER),10)
#define ZTC8_Hex(NUMBER) ZTC8_UnsignedBase((NUMBER),0x10)
//#define ZTC8_HexSigned(NUMBER) ZTC8_IntegerBase((NUMBER),0x10)
#define ZTC8_Binary(NUMBER) ZTC8_UnsignedBase((NUMBER),0x2)
//#define ZTC8_BinarySigned(NUMBER) ZTC8_IntegerBase((NUMBER),0x2)
#endif // ZTM_CHAR_MACRO
ZT_BOOL ZTC8_SeekDigitCursorMax(const ZT_U8* iText, ZT_INDEX* oCursor, ZT_INDEX iByteMax);
ZT_BOOL ZTC8_SeekCRLFCursorMax(const ZT_U8* iText, ZT_INDEX* oCursor, ZT_INDEX iByteMax);
ZT_FLAG ZTC8_SeekBOM(const void* iText);

///ZT_I ZTC8_ReadNumber(const ZT_U8* iText); // reimplement with arbitrary base
ZT_I ZTC8_ReadInteger(const ZT_U8* iText);
ZT_U ZTC8_ReadUnsigned(const ZT_U8* iText);
ZT_U ZTC8_ReadDecimal(const ZT_U8* iText);
ZT_U ZTC8_ReadBinary(const ZT_U8* iText);
ZT_U ZTC8_ReadHex(const ZT_U8* iText);
ZT_FLT ZTC8_ReadFloat(const ZT_U8* iText);
ZT_DBL ZTC8_ReadDouble(const ZT_U8* iText);

const ZT_U8* ZTC8_CopyTarget(const ZT_U8* iSource, ZT_U8* oTarget); // make void!
const ZT_U8* ZTC8_CopyTargetLength(const ZT_U8* iSource, ZT_U8* oTarget, ZT_INDEX iLength); // make void too!
ZT_U8* ZTC8_CopyLength(const ZT_U8* iText, ZT_INDEX iLength);
ZT_U8* ZTC8_CopyModulating(const ZT_U8* iText, ZT_INDEX iLength);
ZT_U8* ZTC8_Copy(const ZT_U8* iText);
ZT_U8* ZTC8_Merge(const ZT_U8* iRoot, const ZT_U8* iBranch);
ZT_U8* ZTC8_MergeFreeR(ZT_U8* iRoot, const ZT_U8* iBranch);
ZT_U8* ZTC8_MergeFreeB(const ZT_U8* iRoot, ZT_U8* iBranch);
ZT_U8* ZTC8_MergeFree(ZT_U8* iRoot, ZT_U8* iBranch);
ZT_U8* ZTC8_CopyAndFree(const ZT_U8* iCopy, ZT_U8* iDelete); // do two things on one line!
ZT_U8* ZTC8_FreeAndCopy(ZT_U8* iDelete, const ZT_U8* iCopy); // name-sequences are tantamount
ZT_INDEX ZTC8_ReplaceGetLength(const ZT_U8* iHaystack, const ZT_U8* iNeedle, const ZT_U8* iReplacement);
ZT_U8* ZTC8_Replace(const ZT_U8* iHaystack, const ZT_U8* iNeedle, const ZT_U8* iReplacement);
ZT_U8* ZTC8_UnsignedBase(ZT_U iInteger, ZT_U iBase);
ZT_U8* ZTC8_IntegerBase(ZT_I iInteger, ZT_U iBase);
ZT_U8* ZTC8_Date(ZT_TIME iUnix, ZT_FLAG iFormat);
ZT_U8* ZTC8_DateISO(ZT_TIME iUnix);
ZT_U8* ZTC8_DateINTL(ZT_TIME iUnix);
ZT_U8* ZTC8_DateDE(ZT_TIME iUnix);
ZT_U8* ZTC8_DateUS(ZT_TIME iUnix);
ZT_U8* ZTC8_DateANSI(ZT_TIME iUnix);
ZT_U8* ZTC8_Time24Hhmmss(ZT_TIME iUnix);
ZT_U8* ZTC8_Time24Hhmm(ZT_TIME iUnix);
ZT_U8* ZTC8_Time12Hhmmss(ZT_TIME iUnix);
ZT_U8* ZTC8_Time12Hhmm(ZT_TIME iUnix);
ZT_U8* ZTC8_ISO8601(ZT_TIME iUnix);
ZT_U8* ZTC8_ISO8601T(ZT_TIME iUnix);
ZT_U8* ZTC8_RFC1123(ZT_TIME iUnixUTC);
ZT_U8* ZTC8_Bytes(const ZT_U8* iBytes, ZT_INDEX iLength, const ZT_U8* iDelimiter, ZT_INDEX iGrouping);
ZT_U8* ZTC8_Hash(const void* iHash, ZT_INDEX iBits, const ZT_U8* iDelimiter, ZT_INDEX iGrouping);
ZT_U8* ZTC8_Printable(const ZT_U8* iData, ZT_INDEX iLength, ZT_U8 iReplacement);
ZT_INDEX ZTC8_PathIndexBranchLast(const ZT_U8* iPath);
#define ZTC8_PathIndexFilename(PATH) ZTC8_PathIndexBranchLast(PATH)
ZT_INDEX ZTC8_PathIndexFileExtension(const ZT_U8* iPath);
ZT_INDEX ZTC8_PathIndexFileType(const ZT_U8* iPath);
ZT_U8* ZTC8_PathBranchLast(const ZT_U8* iPath);
#define ZTC8_PathFilename(PATH) ZTC8_PathBranchLast(PATH)
ZT_U8* ZTC8_PathFileExtension(const ZT_U8* iPath);
ZT_U8* ZTC8_PathFileType(const ZT_U8* iPath);
ZT_U8* ZTC8_PathFileTitle(const ZT_U8* iPath);
ZT_U8* ZTC8_PathFileISO(const ZT_U8* iRoot, const ZT_U8* iExtension, ZT_TIME iUnix);
//ZT_BOOL ZTC8_WinCLI(ZT_INDEX argc, ZT_U8** argv, const ZT_U8* iSearch, ZT_INDEX* oIndexFound);
//ZT_U8* ZTC8_ConvertUTF8ToWin1252(const ZT_U8* iText);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_CHAR_H_INCLUDED
