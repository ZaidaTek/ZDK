/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_DATA_C_INCLUDED
#define ZDX_DATA_C_INCLUDED

#include "ZDX_Data.h"

ZDX_DATA* ZDX_DataNew(ZDX_DEVICE* iDevice, ZT_INDEX iLength) {
    if (iDevice != NULL && iLength) {
        if (iDevice->channel != NULL) {
            if (iDevice->channel->number) {
                ZDX_DATA* lData;
                if ((lData = ZTM8_New(sizeof(ZDX_DATA))) != NULL) {
                    if ((lData->data = ZTM8_New(sizeof(ZT_U) * iDevice->channel->number * iLength)) != NULL) {
                        lData->block.xU = iDevice->channel->number;
                        lData->block.yU = iLength;
                        lData->cursor = 0;
                        lData->resolution = 10;
                        return ZDX_DataSet(lData, 0x0);
                    }
					ZTM8_Free(lData);
                }
            }
        }
    }
    return NULL;
}
ZDX_DATA* ZDX_DataSet(ZDX_DATA* iData, ZT_U iValue) {
    if (iData != NULL) {
        if (iData->data != NULL) {
			ZT_INDEX lLength = ZTM_UPointArea(&(iData->block));
            for (ZT_INDEX i = 0; i < lLength; ++i) {iData->data[i] = iValue;}
        }
    }
	return iData;
}
void ZDX_DataFree(ZDX_DATA* iData) {
    if (iData != NULL) {
        if (iData->data != NULL) {ZTM8_Free(iData->data);}
        ZTM8_Free(iData);
    }
}
ZT_U* ZDX_DataGetLastLine(ZDX_DATA* iData) {
    ZT_U* lSample = NULL;
    if (iData != NULL) {return &(iData->data[(iData->cursor ? (iData->cursor - 1) : (iData->block.yU - 1)) * iData->block.xU]);}
    return lSample;
}
void ZDX_DataLineAdd(ZDX_DATA* iData, const ZT_U* iSample) {
    if (iData != NULL && iSample != NULL) {
        ZT_INDEX lOffset = iData->cursor * iData->block.xU;
        for (ZT_INDEX i = 0; i < iData->block.xU; i++) {iData->data[lOffset + i] = iSample[i];}
        iData->cursor = (iData->cursor + 1) % iData->block.yU;
    }
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
