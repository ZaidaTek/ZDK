/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_C_INCLUDED
#define ZDX_C_INCLUDED

#include "ZDX__Runtime.h"

void ZDX_Free(ZDX_DEVICE* iDevice) {
    ZDX_InterfaceFree(iDevice);
    ZTM8_Free(iDevice->address);
    ZTM8_Free(iDevice);
}
ZDX_DEVICE* ZDX_New(const ZT_CHAR* iAddress, ZT_FLAG iType) {
    switch(iType) {
        case ZDX_DEVICE_TYPE_AT328P: break;
        default: return NULL;
    }
    ZDX_DEVICE* lDevice = ZTM8_New(sizeof(ZDX_DEVICE));
    ZTM8_Zero(&lDevice->interface, sizeof(lDevice->interface));
    ZTM8_Zero(&lDevice->task, sizeof(lDevice->task));
    lDevice->flag = ZDX_FLAG_NONE;// | ZDX_DEVICE_FLAG_UNBUFFERED;
    lDevice->type = iType;
    lDevice->address = ZTC8_Copy(iAddress);
    return lDevice;
}
void ZDX_Assign(ZDX_DEVICE* iDevice, ZT_FLAG iType, ZT_FLAG iConfig, ZT_INDEX iSpeed) {
    ZT_INDEX lResolution;
    switch (iDevice->type) {
        case ZDX_DEVICE_TYPE_AT328P:
            iType &= ZDX_AT328_TASK;
            if ((iSpeed > ZDX_AT328_ADC_RATE_MAX) || (iSpeed < ZDX_AT328_ADC_RATE_MIN)) {iSpeed = ZDX_CHANNEL_SPEED_NONE;}
            iConfig &= ZDX_AT328_ADC_MASK;
            lResolution = ZDX_AT328_ADC_RESOLUTION;
            break;
        default:
            return;
    }
    ZTM8_Zero(&iDevice->task, sizeof(iDevice->task));
    iDevice->task.type = iType;
    iDevice->task.speed = iSpeed;
    iDevice->task.config = iConfig;
    iDevice->task.number = ZTM_BitCount(iConfig);
    iDevice->task.resolution = lResolution;
}
void ZDX_Connect(ZDX_DEVICE* iDevice) {
    ZDX_InterfaceNew(iDevice);
    ZDX_InterfaceStart(iDevice);
}
void ZDX_Disconnect(ZDX_DEVICE* iDevice) {
    ZDX_InterfaceStop(iDevice);
}
ZT_INDEX ZDX_Read(ZDX_DEVICE* iDevice, ZDX_DATA* oData) {
    return ZDX_InterfaceRead(iDevice, oData);
}
ZT_INDEX ZDX_GetSpeed(ZDX_DEVICE* iDevice) {
    switch (iDevice->task.type) {
        case ZDX_TASK_ADC: return iDevice->task.speed;
        default: return 0;
    }
}
ZT_FLAG ZDX_GetChannels(ZDX_DEVICE* iDevice) {
    switch (iDevice->task.type) {
        case ZDX_TASK_ADC: return iDevice->task.config;
        case ZDX_TASK_DIO: return iDevice->task.config;
        default: return 0x0;
    }
}
void ZDX_TriggerFree(ZDX_TRIGGER* iTrigger) {
    ZTM8_Free(iTrigger);
}
ZDX_TRIGGER* ZDX_TriggerNew(void) {
    ZDX_TRIGGER* lTrigger = ZTM8_New(sizeof(ZDX_TRIGGER));
    lTrigger->type = ZDX_TYPE_NONE;
    lTrigger->cursor = 0;
    lTrigger->level.xU = 0;
    lTrigger->level.yU = 0;
    return lTrigger;
}

//#include <stdio.h>
ZT_INDEX ZDX_TriggerCheck(ZDX_TRIGGER* iTrigger, ZDX_DATA* iData, ZT_INDEX iChannel) {
    ZT_INDEX lTriggered = 0;
    ZT_INDEX lChannels = iData->block.xU;
    ZT_INDEX lCheck = (iTrigger->cursor > iData->cursor) ? (iData->block.yU - iTrigger->cursor + iData->cursor) : (iData->cursor - iTrigger->cursor);
    ZT_INDEX lIndexPrev = iTrigger->cursor ? iTrigger->cursor - 1 : (iData->block.yU - 1);
    //printf("%u\n", lCheck);
    for (ZT_INDEX i = 0; i < lCheck; i++) {
        if (iTrigger->cursor == iTrigger->level.xU) {iTrigger->level.xU = -1;}
        if (iTrigger->type & ZDX_TRIGGER_TYPE_FALLING) {
            if (iData->data[iTrigger->cursor * lChannels + iChannel] <= iTrigger->level.yU && iData->data[lIndexPrev * lChannels + iChannel] > iTrigger->level.yU) {
                ++lTriggered;
                iTrigger->level.xU = iTrigger->cursor;
            }
        } else if (iTrigger->type & ZDX_TRIGGER_TYPE_RISING) {
            if (iData->data[iTrigger->cursor * lChannels + iChannel] >= iTrigger->level.yU && iData->data[lIndexPrev * lChannels + iChannel] < iTrigger->level.yU) {
                ++lTriggered;
                iTrigger->level.xU = iTrigger->cursor;
            }
        }
        lIndexPrev = iTrigger->cursor;
        iTrigger->cursor = (iTrigger->cursor + 1) % iData->block.yU;
    }
    return lTriggered;
}

#endif // ZDX_C_INCLUDED
