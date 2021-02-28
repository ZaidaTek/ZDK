/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_DATA_C_INCLUDED
#define ZDX_DATA_C_INCLUDED

#include "ZDX__Runtime.h"

ZDX_DATA* ZDX_DataNew(ZDX_DEVICE* iDevice, ZT_INDEX iLength) {
    ZDX_DATA* lData = ZTM8_New(sizeof(ZDX_DATA));
    lData->data = ZTM8_New(sizeof(ZT_U) * iDevice->task.number * iLength);
    lData->block.xU = iDevice->task.number;
    lData->block.yU = iLength;
    lData->cursor = 0;
    lData->resolution = iDevice->task.resolution;
    return ZDX_DataSet(lData, 0x0);
}
ZDX_DATA* ZDX_DataSet(ZDX_DATA* iData, ZT_U iValue) {
    ZT_INDEX lLength = ZTM_UPointArea(&(iData->block));
    for (ZT_INDEX i = 0; i < lLength; ++i) {iData->data[i] = iValue;}
	return iData;
}
void ZDX_DataFree(ZDX_DATA* iData) {
    ZTM8_Free(iData->data);
    ZTM8_Free(iData);
}
ZT_U* ZDX_DataGetLastLine(ZDX_DATA* iData) {
    return &(iData->data[(iData->cursor ? (iData->cursor - 1) : (iData->block.yU - 1)) * iData->block.xU]);
}
void ZDX_DataLineAdd(ZDX_DATA* iData, const ZT_U* iSample) {
    ZT_INDEX lOffset = iData->cursor * iData->block.xU;
    for (ZT_INDEX i = 0; i < iData->block.xU; i++) {iData->data[lOffset + i] = iSample[i];}
    iData->cursor = (iData->cursor + 1) % iData->block.yU;
}
/*
ZT_INDEX ZDX_DataLineQueue(ZDX_DATA* iData) {
    if (iData != NULL) {
        if (iData->cursor.write < iData->cursor.read) {
            return (iData->block.yU - iData->cursor.read + iData->cursor.write);
        } else {
            return (iData->cursor.write - iData->cursor.read);
        }
    }
    return 0;
}
ZT_INDEX ZDX_DataLinePoll(ZDX_DATA* iData, ZT_U* oBuffer) {
    ZT_INDEX lQueue;
    if ((lQueue = ZDX_DataLineQueue(iData))) { // implies iData != NULL
        ZT_INDEX lOffset = iData->cursor.read * iData->block.xU;
        for (ZT_INDEX i = 0; i < iData->block.xU; i++) {oBuffer[i] = iData->data[lOffset + i];}
        iData->cursor.read = (iData->cursor.read + 1) % iData->block.yU;
    }
    return lQueue;
}
*/
#endif // ZDX_DATA_C_INCLUDED
