/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTMKY_H_INCLUDED
#define ZTMKY_H_INCLUDED

#include "../ZTM.h"
#include "../ZTMIO/ZTMIO.h"

typedef struct {
    const ZT_CHAR* name;
    const ZT_CHAR* value;
} ZKY_KEYPAIR;

typedef ZT_LIST ZKY;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZKY* ZKY_New(void);
void ZKY_Free(ZKY* iKeyFile);
ZT_INDEX ZKY_GetLength(const ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign);
ZT_INDEX ZKY_Deserialize(ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, const ZT_CHAR* iString);
ZT_INDEX ZKY_Serialize(const ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, ZT_CHAR* oString); // OUTPUT *NOT!* NULL-TERMNITATED
ZT_INDEX ZKY_FileRead(ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, const ZT_CHAR* iPath);
ZT_INDEX ZKY_FileReadAndDeletePath(ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, ZT_CHAR* iPath);
ZT_INDEX ZKY_FileWrite(const ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, const ZT_CHAR* iPath);
ZT_INDEX ZKY_FileWriteDiscardKeys(ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, const ZT_CHAR* iPath);
ZT_INDEX ZKY_FileWriteDiscardPath(const ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, ZT_CHAR* iPath);
ZT_INDEX ZKY_FileWriteDiscardKeysPath(ZKY* iKeyFile, const ZT_CHAR* iDelimit, const ZT_CHAR* iAssign, ZT_CHAR* iPath);
ZKY_KEYPAIR* ZKY_GetKey(const ZKY* iKeyFile, const ZT_CHAR* iName, ZT_INDEX iIndex);
const ZT_CHAR* ZKY_Get(const ZKY* iKeyFile, const ZT_CHAR* iName);
ZT_U ZKY_GetHex(const ZKY* iKeyHive, const ZT_CHAR* iName);
ZT_U ZKY_GetUnsigned(const ZKY* iKeyHive, const ZT_CHAR* iName);
ZT_I ZKY_GetInteger(const ZKY* iKeyHive, const ZT_CHAR* iName);
ZT_FLT ZKY_GetFloat(const ZKY* iKeyHive, const ZT_CHAR* iName);
ZT_DBL ZKY_GetDouble(const ZKY* iKeyHive, const ZT_CHAR* iName);
const ZT_CHAR* ZKY_GetIndexed(const ZKY* iKeyFile, const ZT_CHAR* iName, ZT_INDEX iIndex);
ZT_U ZKY_GetHexIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex);
ZT_U ZKY_GetUnsignedIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex);
ZT_I ZKY_GetIntegerIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex);
ZT_FLT ZKY_GetFloatIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex);
ZT_DBL ZKY_GetDoubleIndex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex);
ZT_FLAG ZKY_Read(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_CHAR* oTarget);
ZT_FLAG ZKY_ReadHex(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U* oTarget);
ZT_FLAG ZKY_ReadUnsigned(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U* oTarget);
ZT_FLAG ZKY_ReadInteger(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_I* oTarget);
ZT_FLAG ZKY_ReadFloat(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_FLT* oTarget);
ZT_FLAG ZKY_ReadDouble(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_DBL* oTarget);
ZT_FLAG ZKY_ReadIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_CHAR* oTarget);
ZT_FLAG ZKY_ReadHexIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U* oTarget);
ZT_FLAG ZKY_ReadUnsignedIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U* oTarget);
ZT_FLAG ZKY_ReadIntegerIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_I* oTarget);
ZT_FLAG ZKY_ReadFloatIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_FLT* oTarget);
ZT_FLAG ZKY_ReadDoubleIndexed(const ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_DBL* oTarget);
void ZKY_Set(ZKY* iKeyHive, const ZT_CHAR* iName, const ZT_CHAR* iValue);
void ZKY_SetFree(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_CHAR* iValue);
void ZKY_SetHex(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U iValue);
void ZKY_SetUnsigned(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U iValue);
void ZKY_SetInteger(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_I iValue);
void ZKY_SetFloat(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_FLT iValue);
void ZKY_SetDouble(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_DBL iValue);
void ZKY_SetIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, const ZT_CHAR* iValue);
void ZKY_SetIndexedFree(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_CHAR* iValue);
void ZKY_SetHexIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U iValue);
void ZKY_SetUnsignedIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U iValue);
void ZKY_SetIntegerIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_I iValue);
void ZKY_Append(ZKY* iKeyHive, const ZT_CHAR* iName, const ZT_CHAR* iAppend, const ZT_CHAR* iDelimit);
void ZKY_AppendFree(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_CHAR* iAppend, const ZT_CHAR* iDelimit);
void ZKY_AppendIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, const ZT_CHAR* iAppend, const ZT_CHAR* iDelimit);
void ZKY_AppendIndexedFree(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_CHAR* iAppend, const ZT_CHAR* iDelimit);
void ZKY_AppendHex(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U iValue, const ZT_CHAR* iDelimit);
void ZKY_AppendHexIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U iValue, const ZT_CHAR* iDelimit);
void ZKY_AppendUnsigned(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_U iValue, const ZT_CHAR* iDelimit);
void ZKY_AppendUnsignedIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_U iValue, const ZT_CHAR* iDelimit);
void ZKY_AppendInteger(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_I iValue, const ZT_CHAR* iDelimit);
void ZKY_AppendIntegerIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_I iValue, const ZT_CHAR* iDelimit);
/*void ZKY_SetFloatIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_FLT iValue);
void ZKY_SetDoubleIndexed(ZKY* iKeyHive, const ZT_CHAR* iName, ZT_INDEX iIndex, ZT_DBL iValue);*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTMKY_H_INCLUDED
