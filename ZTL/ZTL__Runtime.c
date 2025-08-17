/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL__RUNTIME_C_INCLUDED
#define ZTL__RUNTIME_C_INCLUDED

#include "ZTL__Runtime.h"

ZT_FLAG             rZTL__QPC_FLAG = ZTL_FLAG_QPC_INIT;
ZT_U64              rZTL__QPC_RATE = 1;
ZT_TIME             rZTL__TICK_RES = 0;
ZT_FLAG             rZTL__SELECT_FLAG = ZTL_FLAG_SELECT_INIT;
ZT_INDEX            rZTL__SELECT_COUNT = 0;
rZT_SELECT          rZTL__SELECT_RUNTIME = {0x0};
rZT_THREAD*         rZTL__SELECT_THREAD = NULL;
ZT_CHAR             rZTL__SELECT_PATH[ZTL_BUFFER_PATH] = {ZTM_CHAR_NT};
ZT_CHAR             rZTL__SELECT_DIR[ZTL_BUFFER_PATH] = {ZTM_CHAR_NT};
ZT_CHAR             rZTL__SELECT_FILE[ZTL_BUFFER_PATH] = {ZTM_CHAR_NT};
ZT_CHAR             rZTL__SELECT_TYPE[ZTL_BUFFER_PATH] = {ZTM_CHAR_NT};

#endif // ZTL__RUNTIME_C_INCLUDED
