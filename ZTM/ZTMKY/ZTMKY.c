/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTMKY_C_INCLUDED
#define ZTMKY_C_INCLUDED

#include "ZTMKY.h"

#include <stdio.h>

ZT_INDEX ZKY_GetLength(const ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign) {
	ZT_INDEX lLength = 0;
	if (iKeyHive != NULL && iDelimit != NULL && iAssign != NULL) {
		for (ZT_INDEX i = 0; i < iKeyHive->length; i++) {
			if (iKeyHive->items[i] != NULL) {
				ZKY_KEYPAIR* lKey = iKeyHive->items[i];
				if (lKey->name != NULL) {
					if (lLength) {lLength += ZTC8_GetLength(iDelimit);}
					lLength += ZTC8_GetLength(lKey->name);
					lLength += ZTC8_GetLength(iAssign);
					if (lKey->value != NULL) {lLength += ZTC8_GetLength(lKey->value);}
				}
			}
		}
	}
	return lLength;
}

ZKY_KEYPAIR* ZKY_GetKey(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex) {
	if (iKeyHive != NULL && iName != NULL) {
		ZKY_KEYPAIR* lKey = NULL;
		for (ZT_INDEX i = 0; i < iKeyHive->length; i++) {
			if ((lKey = iKeyHive->items[i]) != NULL) {
				if (ZTC8_MatchExact(lKey->name, iName)) {
					if (!(iIndex--)) {return lKey;}
				}
			}
		}
	}
	return NULL;
}
ZKY_KEYPAIR* ZKY_KeyNew(const ZT_CHAR* iName, const ZT_CHAR* iValue) {
	ZKY_KEYPAIR* lKey = NULL;
	if (iName != NULL) {
		if (ZTC8_GetLength(iName)) {
			if ((lKey = (ZKY_KEYPAIR*)ZTM8_New(sizeof(ZKY_KEYPAIR))) != NULL) {
				if ((lKey->name = ZTC8_Copy(iName)) != NULL) {
					if ((lKey->value = ZTC8_Copy(iValue != NULL ? iValue : (const ZT_CHAR*)"")) != NULL) {
						return lKey;
					}
				}
				ZTM8_Free((ZT_CHAR*)lKey->name);
			}
			ZTM8_Free(lKey);
		}
	}
	return NULL;
}
void ZKY_KeyClear(ZKY_KEYPAIR* iKey) {
	if (iKey != NULL) {
		ZTM8_Free((ZT_CHAR*)iKey->name);
		ZTM8_Free((ZT_CHAR*)iKey->value);
		iKey->name = NULL;
		iKey->value = NULL;
	}
}
void ZKY_KeyFree(ZKY_KEYPAIR* iKey) {
	if (iKey != NULL) {
		ZTM8_Free((ZT_CHAR*)iKey->name);
		ZTM8_Free((ZT_CHAR*)iKey->value);
		ZTM8_Free(iKey);
	}
}
void ZKY_KeySet(ZKY_KEYPAIR* iKey, const ZT_CHAR* iValue) {
	if (iKey != NULL) {
		ZTM8_Free((ZT_CHAR*)iKey->value);
		iKey->value = iValue != NULL ? ZTC8_Copy(iValue) : NULL;
	}
}
void ZKY_KeyAppend(ZKY_KEYPAIR* iKey, const ZT_CHAR* iAppend, const ZT_CHAR* iDelimit) {
	if (iKey != NULL) {
		if (iKey->value != NULL ? ZTC8_GetLength(iKey->value) : 0x0) {
			if (iDelimit != NULL) {iKey->value = ZTC8_MergeFreeR((ZT_CHAR*)iKey->value, iDelimit);}
			if (iAppend != NULL) {iKey->value = ZTC8_MergeFreeR((ZT_CHAR*)iKey->value, iAppend);}
		} else if (iAppend != NULL) {
			ZTM8_Free((ZT_CHAR*)iKey->value);
			iKey->value = ZTC8_Copy(iAppend);
		}
	}
}

ZKY* ZKY_New(void) {
	return ZTM_ListNew(0);
}
ZT_INDEX ZKY_FileRead(ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, const ZT_CHAR* iPath) {
	ZT_INDEX lKeysFound = 0;
	if (iKeyHive != NULL && iPath != NULL) {
		ZT_INDEX lFileSize = 0;
		if ((lFileSize = ZIO_PipedScan(iPath))) {
			ZT_CHAR* lString = (ZT_CHAR*)ZTM8_New(lFileSize + 1);
			if (lString != NULL) {
				ZT_INDEX lRead = ZIO_PipedRead(iPath, lString, lFileSize, 0);
				lString[lRead] = ZTM_CHAR_NT;
				lKeysFound = ZKY_Deserialize(iKeyHive, iDelimit, iAssign, lString);
				ZTM8_Free(lString);
			}
		}
	}
	return lKeysFound;
}
ZT_INDEX ZKY_FileReadAndDeletePath(ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, ZT_CHAR* iPath) {
	ZT_INDEX lKeysFound = ZKY_FileRead(iKeyHive, iDelimit, iAssign, iPath);
	ZTM8_Free(iPath);
	return lKeysFound;
}
ZT_INDEX ZKY_Deserialize(ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, const ZT_CHAR* iString) {
	ZT_INDEX lKeysFound = 0;
	if (iKeyHive != NULL && iString != NULL && iDelimit != NULL && iAssign != NULL) {
		ZT_INDEX lMatchLength = ZTC8_GetLength(iDelimit);
		ZT_INDEX lLine = 0;
		ZT_INDEX lIndex = -1;
		ZT_FLAG lEscape = 0x0;
		while (iString[++lIndex] != ZTM_CHAR_NT) {
			ZTC8_Escape(lEscape, iString[lIndex]);
			if (ZTC8_Match(&iString[lIndex], iDelimit) && (lLine < lIndex) && !lEscape) {
				ZTM_ListAppend(iKeyHive, ZTC8_CopyLength(&iString[lLine], lIndex - lLine));
				lLine = lIndex + lMatchLength;
			}
		}
		if (lIndex > lLine) {
			ZTM_ListAppend(iKeyHive, ZTC8_CopyLength(&iString[lLine], lIndex - lLine));
			lLine = lIndex;
		}
		for (ZT_INDEX i = 0; i < iKeyHive->length; i++) {
			ZKY_KEYPAIR* lKey = NULL;
			ZT_CHAR* lString = iKeyHive->items[i];
			lMatchLength = ZTC8_GetLength(iAssign);
			lLine = 0;
			lIndex = -1;
			lEscape = 0x0;
			while (lString[++lIndex] != ZTM_CHAR_NT) {
				ZTC8_Escape(lEscape, iString[lIndex]);
				if (ZTC8_Match(&lString[lIndex], iAssign) && (lLine < lIndex) && !lEscape) {
					if ((lKey = (ZKY_KEYPAIR*)ZTM8_New(sizeof(ZKY_KEYPAIR))) != NULL) {
						lKeysFound++;
						iKeyHive->items[i] = lKey;
						lKey->name = ZTC8_CopyLength(&lString[lLine], lIndex - lLine);
						lLine = lIndex + lMatchLength;
					}
				}
			}
			if (lKey != NULL) {
				if (lIndex > lLine) {
					lKey->value = ZTC8_CopyLength(&lString[lLine], lIndex - lLine);
				} else {
					lKey->value = ZTC8_Copy((const ZT_CHAR*)"");
				}
			} else if (lIndex > lLine) {
				if ((lKey = (ZKY_KEYPAIR*)ZTM8_New(sizeof(ZKY_KEYPAIR))) != NULL) {
					lKeysFound++;
					iKeyHive->items[i] = lKey;
					lKey->name = ZTC8_CopyLength(&lString[lLine], lIndex - lLine);
					lKey->value = ZTC8_Copy((const ZT_CHAR*)"");
					lLine = lIndex;
				}
			}
			ZTM8_Free(lString);
		}
	}
	return lKeysFound;
}
ZT_INDEX ZKY_Serialize(const ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, ZT_CHAR* oString) {
	ZT_INDEX lKeysFound = 0;
	if (iKeyHive != NULL && iDelimit != NULL && iAssign != NULL && oString != NULL) {
		ZT_INDEX lCursor = 0;
		for (ZT_INDEX i = 0; i < iKeyHive->length; i++) {
			if (iKeyHive->items[i] != NULL) {
				ZKY_KEYPAIR* lKey = iKeyHive->items[i];
				if (lKey->name != NULL) {
					if (lCursor) {ZTC8_CopyTarget(iDelimit, &(oString[lCursor])); lCursor += ZTC8_GetLength(iDelimit);}
					ZTC8_CopyTarget(lKey->name, &(oString[lCursor]));
					lCursor += ZTC8_GetLength(lKey->name);
					ZTC8_CopyTarget(iAssign, &(oString[lCursor]));
					lCursor += ZTC8_GetLength(iAssign);
					if (lKey->value != NULL) {ZTC8_CopyTarget(lKey->value, &(oString[lCursor])); lCursor += ZTC8_GetLength(lKey->value);}
					lKeysFound++;
				}
			}
		}
	}
	return lKeysFound;
}
ZT_INDEX ZKY_FileWrite(const ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, const ZT_CHAR* iPath) {
	ZT_INDEX lKeysFound = 0;
	if (iKeyHive != NULL && iDelimit != NULL && iAssign != NULL && iPath != NULL) {
		ZT_INDEX lLength = ZKY_GetLength(iKeyHive, iDelimit, iAssign);
		if (lLength) {
			ZT_CHAR* lString = NULL;
			if ((lString = (ZT_CHAR*)ZTM8_New(sizeof(ZT_CHAR) * (lLength + 1))) != NULL) {
				lKeysFound = ZKY_Serialize(iKeyHive, iDelimit, iAssign, lString);
				lString[lLength] = ZTM_CHAR_NT; // for some reason fwrite still needs NT despite having size?
				ZIO_PipedWrite(iPath, lString, lLength, 0);
				ZTM8_Free(lString);
			}
		}
	}
	return lKeysFound;
}
ZT_INDEX ZKY_FileWriteDiscardKeys(ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, const ZT_CHAR* iPath) {
	ZT_INDEX lKeysFound = ZKY_FileWrite(iKeyHive, iDelimit, iAssign, iPath);
	ZKY_Free(iKeyHive);
	return lKeysFound;
}
ZT_INDEX ZKY_FileWriteDiscardPath(const ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, ZT_CHAR* iPath) {
	ZT_INDEX lKeysFound = ZKY_FileWrite(iKeyHive, iDelimit, iAssign, iPath);
	ZTM8_Free(iPath);
	return lKeysFound;
}
ZT_INDEX ZKY_FileWriteDiscardKeysPath(ZKY* iKeyHive, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, ZT_CHAR* iPath) {
	ZT_INDEX lKeysFound = ZKY_FileWrite(iKeyHive, iDelimit, iAssign, iPath);
	ZKY_Free(iKeyHive);
	ZTM8_Free(iPath);
	return lKeysFound;
}
void ZKY_Clear(ZKY* iKeyHive) {
	if (iKeyHive != NULL) {
		for (ZT_INDEX i = 0; i < iKeyHive->length; i++) {
			ZKY_KeyFree(iKeyHive->items[i]);
			iKeyHive->items[i] = NULL;
		}
	}
}
void ZKY_Free(ZKY* iKeyHive) {
	if (iKeyHive != NULL) {
		ZKY_Clear(iKeyHive);
		ZTM_ListFree(iKeyHive);
	}
}
#define ZKY_LOADED(DB,KEY,NAME,INDEX) (((KEY) = ZKY_GetKey((DB), (NAME), (INDEX))) != NULL)
#define ZKY_GET(DB,NAME,INDEX) ({const ZT_CHAR* lVal = NULL; ZKY_KEYPAIR* lKey; if (ZKY_LOADED((DB), lKey, (NAME), (INDEX))) {lVal = lKey->value;} lVal;})
#define ZKY_GETHEX(DB,NAME,INDEX) ({ZT_U lVal = 0x0; const ZT_CHAR* lText; if ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL) {lVal = ZTC8_ReadHex(lText);} lVal;})
#define ZKY_GETUNSIGNED(DB,NAME,INDEX) ({ZT_U lVal = 0x0; const ZT_CHAR* lText; if ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL) {lVal = ZTC8_ReadUnsigned(lText);} lVal;})
#define ZKY_GETINTEGER(DB,NAME,INDEX) ({ZT_U lVal = 0x0; const ZT_CHAR* lText; if ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL) {lVal = ZTC8_ReadInteger(lText);} lVal;})
#define ZKY_GETFLOAT(DB,NAME,INDEX) ({ZT_U lVal = 0.0; const ZT_CHAR* lText; if ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL) {lVal = ZTC8_ReadFloat(lText);} lVal;})
#define ZKY_GETDOUBLE(DB,NAME,INDEX) ({ZT_U lVal = 0.0; const ZT_CHAR* lText; if ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL) {lVal = ZTC8_ReadDouble(lText);} lVal;})
#define ZKY_READ(DB,NAME,INDEX,TARGET) ({ZT_FLAG lFound = 0x0; if ((TARGET) != NULL) {ZKY_KEYPAIR* lKey; if (ZKY_LOADED((DB), lKey, (NAME), (INDEX))) {if ((lFound = ((lKey->value) != NULL))) {ZTC8_CopyTarget(lKey->value, (TARGET));}}} lFound;})
#define ZKY_READHEX(DB,NAME,INDEX,TARGET) ({ZT_FLAG lFound = 0x0; if ((TARGET) != NULL) {const ZT_CHAR* lText; if ((lFound = ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL))) {*(TARGET) = ZTC8_ReadHex(lText);}} lFound;})
#define ZKY_READUNSIGNED(DB,NAME,INDEX,TARGET) ({ZT_FLAG lFound = 0x0; if ((TARGET) != NULL) {const ZT_CHAR* lText; if ((lFound = ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL))) {*(TARGET) = ZTC8_ReadUnsigned(lText);}} lFound;})
#define ZKY_READINTEGER(DB,NAME,INDEX,TARGET) ({ZT_FLAG lFound = 0x0; if ((TARGET) != NULL) {const ZT_CHAR* lText; if ((lFound = ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL))) {*(TARGET) = ZTC8_ReadInteger(lText);}} lFound;})
#define ZKY_READFLOAT(DB,NAME,INDEX,TARGET) ({ZT_FLAG lFound = 0x0; if ((TARGET) != NULL) {const ZT_CHAR* lText; if ((lFound = ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL))) {*(TARGET) = ZTC8_ReadFloat(lText);}} lFound;})
#define ZKY_READDOUBLE(DB,NAME,INDEX,TARGET) ({ZT_FLAG lFound = 0x0; if ((TARGET) != NULL) {const ZT_CHAR* lText; if ((lFound = ((lText = ZKY_GET((DB), (NAME), (INDEX))) != NULL))) {*(TARGET) = ZTC8_ReadDouble(lText);}} lFound;})
const ZT_CHAR* ZKY_Get(const ZKY* iKeyHive, const ZT_CHAR* iName) {return ZKY_GET(iKeyHive, iName, 0);}
ZT_U ZKY_GetHex(const ZKY* iKeyHive, const ZT_CHAR* iName) {return ZKY_GETHEX(iKeyHive, iName, 0);}
ZT_U ZKY_GetUnsigned(const ZKY* iKeyHive, const ZT_CHAR* iName) {return ZKY_GETUNSIGNED(iKeyHive, iName, 0);}
ZT_I ZKY_GetInteger(const ZKY* iKeyHive, const ZT_CHAR* iName) {return ZKY_GETINTEGER(iKeyHive, iName, 0);}
ZT_FLT ZKY_GetFloat(const ZKY* iKeyHive, const ZT_CHAR* iName) {return ZKY_GETFLOAT(iKeyHive, iName, 0);}
ZT_DBL ZKY_GetDouble(const ZKY* iKeyHive, const ZT_CHAR* iName) {return ZKY_GETDOUBLE(iKeyHive, iName, 0);}
const ZT_CHAR* ZKY_GetIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex) {return ZKY_GET(iKeyHive, iName, iIndex);}
ZT_U ZKY_GetHexIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex) {return ZKY_GETHEX(iKeyHive, iName, iIndex);}
ZT_U ZKY_GetUnsignedIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex) {return ZKY_GETUNSIGNED(iKeyHive, iName, iIndex);}
ZT_I ZKY_GetIntegerIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex) {return ZKY_GETINTEGER(iKeyHive, iName, iIndex);}
ZT_FLT ZKY_GetFloatIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex) {return ZKY_GETFLOAT(iKeyHive, iName, iIndex);}
ZT_DBL ZKY_GetDoubleIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex) {return ZKY_GETDOUBLE(iKeyHive, iName, iIndex);}
ZT_FLAG ZKY_Read(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_CHAR* oTarget) {return ZKY_READ(iKeyHive, iName, 0, oTarget);}
ZT_FLAG ZKY_ReadHex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U* oTarget) {return ZKY_READHEX(iKeyHive, iName, 0, oTarget);}
ZT_FLAG ZKY_ReadUnsigned(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U* oTarget) {return ZKY_READUNSIGNED(iKeyHive, iName, 0, oTarget);}
ZT_FLAG ZKY_ReadInteger(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_I* oTarget) {return ZKY_READINTEGER(iKeyHive, iName, 0, oTarget);}
ZT_FLAG ZKY_ReadFloat(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_FLT* oTarget) {return ZKY_READFLOAT(iKeyHive, iName, 0, oTarget);}
ZT_FLAG ZKY_ReadDouble(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_DBL* oTarget) {return ZKY_READDOUBLE(iKeyHive, iName, 0, oTarget);}
ZT_FLAG ZKY_ReadIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_CHAR* oTarget) {return ZKY_READ(iKeyHive, iName, iIndex, oTarget);}
ZT_FLAG ZKY_ReadHexIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U* oTarget) {return ZKY_READHEX(iKeyHive, iName, iIndex, oTarget);}
ZT_FLAG ZKY_ReadUnsignedIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U* oTarget) {return ZKY_READUNSIGNED(iKeyHive, iName, iIndex, oTarget);}
ZT_FLAG ZKY_ReadIntegerIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_I* oTarget) {return ZKY_READINTEGER(iKeyHive, iName, iIndex, oTarget);}
ZT_FLAG ZKY_ReadFloatIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_FLT* oTarget) {return ZKY_READFLOAT(iKeyHive, iName, iIndex, oTarget);}
ZT_FLAG ZKY_ReadDoubleIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_DBL* oTarget) {return ZKY_READDOUBLE(iKeyHive, iName, iIndex, oTarget);}
#define ZKY_SET(DB,NAME,INDEX,VAL) \
	if ((DB) != NULL) {\
		ZKY_KEYPAIR* lKey;\
		if (ZKY_LOADED((DB), lKey, (NAME), (INDEX))) {\
			ZKY_KeySet(lKey, (VAL));\
		} else if ((lKey = ZKY_KeyNew((NAME), (VAL))) != NULL) {\
			ZTM_ListAppend((DB), lKey);\
		}\
	}
#define ZKY_SETHEX(DB,NAME,INDEX,VAL) ZT_CHAR* lText; if ((lText = ZTC8_Hex(VAL)) != NULL) {ZKY_SET((DB), (NAME), (INDEX), lText); ZTM8_Free(lText);}
#define ZKY_SETUNSIGNED(DB,NAME,INDEX,VAL) ZT_CHAR* lText; if ((lText = ZTC8_Unsigned(VAL)) != NULL) {ZKY_SET((DB), (NAME), (INDEX), lText); ZTM8_Free(lText);}
#define ZKY_SETINTEGER(DB,NAME,INDEX,VAL) ZT_CHAR* lText; if ((lText = ZTC8_Integer(VAL)) != NULL) {ZKY_SET((DB), (NAME), (INDEX), lText); ZTM8_Free(lText);}
void ZKY_Set(ZKY* iKeyHive, const ZT_CHAR* iName, const ZT_CHAR* iValue) {ZKY_SET(iKeyHive, iName, 0, iValue);}
void ZKY_SetFree(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_CHAR* iValue) {ZKY_SET(iKeyHive, iName, 0, iValue); ZTM8_Free(iValue);}
void ZKY_SetIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, const ZT_CHAR* iValue) {ZKY_SET(iKeyHive, iName, iIndex, iValue);}
void ZKY_SetIndexedFree(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_CHAR* iValue) {ZKY_SET(iKeyHive, iName, iIndex, iValue); ZTM8_Free(iValue);}
void ZKY_SetHex(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U iValue) {ZKY_SETHEX(iKeyHive, iName, 0, iValue);}
void ZKY_SetHexIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U iValue) {ZKY_SETHEX(iKeyHive, iName, iIndex, iValue);}
void ZKY_SetUnsigned(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U iValue) {ZKY_SETUNSIGNED(iKeyHive, iName, 0, iValue);}
void ZKY_SetUnsignedIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U iValue) {ZKY_SETUNSIGNED(iKeyHive, iName, iIndex, iValue);}
void ZKY_SetInteger(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_I iValue) {ZKY_SETINTEGER(iKeyHive, iName, 0, iValue);}
void ZKY_SetIntegerIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_I iValue) {ZKY_SETINTEGER(iKeyHive, iName, iIndex, iValue);}
#define ZKY_APPEND(DB,NAME,INDEX,APPEND,DELIMIT) \
	if ((DB) != NULL) {\
		ZKY_KEYPAIR* lKey;\
		if (ZKY_LOADED((DB), lKey, (NAME), (INDEX))) {\
			ZKY_KeyAppend(lKey, (APPEND), (DELIMIT));\
		} else if ((lKey = ZKY_KeyNew((NAME), (APPEND))) != NULL) {\
			ZTM_ListAppend((DB), lKey);\
		}\
	}
#define ZKY_APPENDHEX(DB,NAME,INDEX,APPEND,DELIMIT) ZT_CHAR* lText; if ((lText = ZTC8_Hex(APPEND)) != NULL) {ZKY_APPEND((DB), (NAME), (INDEX), lText, (DELIMIT)); ZTM8_Free(lText);}
#define ZKY_APPENDUNSIGNED(DB,NAME,INDEX,APPEND,DELIMIT) ZT_CHAR* lText; if ((lText = ZTC8_Unsigned(APPEND)) != NULL) {ZKY_APPEND((DB), (NAME), (INDEX), lText, (DELIMIT)); ZTM8_Free(lText);}
#define ZKY_APPENDINTEGER(DB,NAME,INDEX,APPEND,DELIMIT) ZT_CHAR* lText; if ((lText = ZTC8_Integer(APPEND)) != NULL) {ZKY_APPEND((DB), (NAME), (INDEX), lText, (DELIMIT)); ZTM8_Free(lText);}
void ZKY_Append(ZKY* iKeyHive, const ZT_CHAR* iName, const ZT_CHAR* iAppend, const ZT_CHAR* iDelimit) {ZKY_APPEND(iKeyHive, iName, 0, iAppend, iDelimit);}
void ZKY_AppendFree(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_CHAR* iAppend, const ZT_CHAR* iDelimit) {ZKY_APPEND(iKeyHive, iName, 0, iAppend, iDelimit); ZTM8_Free(iAppend);}
void ZKY_AppendIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, const ZT_CHAR* iAppend, const ZT_CHAR* iDelimit) {ZKY_APPEND(iKeyHive, iName, iIndex, iAppend, iDelimit);}
void ZKY_AppendIndexedFree(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_CHAR* iAppend, const ZT_CHAR* iDelimit) {ZKY_APPEND(iKeyHive, iName, iIndex, iAppend, iDelimit); ZTM8_Free(iAppend);}
void ZKY_AppendHex(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U iValue, const ZT_CHAR* iDelimit) {ZKY_APPENDHEX(iKeyHive, iName, 0, iValue, iDelimit);}
void ZKY_AppendHexIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U iValue, const ZT_CHAR* iDelimit) {ZKY_APPENDHEX(iKeyHive, iName, iIndex, iValue, iDelimit);}
void ZKY_AppendUnsigned(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U iValue, const ZT_CHAR* iDelimit) {ZKY_APPENDUNSIGNED(iKeyHive, iName, 0, iValue, iDelimit);}
void ZKY_AppendUnsignedIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U iValue, const ZT_CHAR* iDelimit) {ZKY_APPENDUNSIGNED(iKeyHive, iName, iIndex, iValue, iDelimit);}
void ZKY_AppendInteger(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_I iValue, const ZT_CHAR* iDelimit) {ZKY_APPENDINTEGER(iKeyHive, iName, 0, iValue, iDelimit);}
void ZKY_AppendIntegerIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_I iValue, const ZT_CHAR* iDelimit) {ZKY_APPENDINTEGER(iKeyHive, iName, iIndex, iValue, iDelimit);}
/*
#define ZKY_SETFLOAT(DB,NAME,INDEX,VAL) ZT_CHAR* lText; if ((lText = ZTC8_Float(VAL)) != NULL) {ZKY_SET((DB), (NAME), (INDEX), lText); ZTM8_Free(lText);}
#define ZKY_SETDOUBLE(DB,NAME,INDEX,VAL) ZT_CHAR* lText; if ((lText = ZTC8_Double(VAL)) != NULL) {ZKY_SET((DB), (NAME), (INDEX), lText); ZTM8_Free(lText);}
void ZKY_SetFloat(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_FLT iValue) {ZKY_SETFLOAT(iKeyHive, iName, 0, iValue);}
void ZKY_SetFloatIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_FLT iValue) {ZKY_SETFLOAT(iKeyHive, iName, iIndex, iValue);}
void ZKY_SetDouble(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_DBL iValue) {ZKY_SETDOUBLE(iKeyHive, iName, 0, iValue);}
void ZKY_SetDoubleIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_DBL iValue) {ZKY_SETDOUBLE(iKeyHive, iName, iIndex, iValue);}
*/

#endif // ZTMKY_C_INCLUDED
