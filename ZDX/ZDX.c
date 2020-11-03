/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_C_INCLUDED
#define ZDX_C_INCLUDED

#include "ZDX.h"

void ZDX_Free(ZDX_DEVICE* iDevice) {
	if (iDevice != NULL) {
        ZDX_InterfaceFree(iDevice);
		if (iDevice->channel != NULL) {ZTM8_Free(iDevice->channel);}
		if (iDevice->address != NULL) {ZTM8_Free(iDevice->address);}
		ZTM8_Free(iDevice);
	}
}
ZDX_DEVICE* ZDX_New(const ZT_CHAR* iAddress, ZT_FLAG iType) {
	ZDX_DEVICE* lDevice = NULL;
	if (iAddress != NULL) {
        ZT_FLAG lType = ZDX_TYPE_NONE;
		switch(iType) {
			case ZDX_DEVICE_TYPE_AT328P: lType = ZDX_DEVICE_TYPE_AT328P; break;
			default: break;
		}
        if (lType != ZDX_TYPE_NONE) {
            if ((lDevice = (ZDX_DEVICE*)ZTM8_New(sizeof(ZDX_DEVICE))) != NULL) {
                lDevice->address = ZTC8_Copy(iAddress);
                lDevice->type = lType;
                lDevice->channel = NULL;
                lDevice->interface = NULL;
                lDevice->flag = ZDX_FLAG_NONE;
            }
        }
	}
	return lDevice;
}
void ZDX_Assign(ZDX_DEVICE* iDevice, ZT_FLAG iType, ZT_FLAG iConfig, ZT_INDEX iSpeed) {
	if (iDevice != NULL) {
		if (iDevice->interface == NULL) {
            ZT_FLAG lType = ZDX_CHANNEL_TYPE_NONE;
            ZT_INDEX lSpeed = ZDX_CHANNEL_SPEED_NONE;
            ZT_FLAG lConfig = ZDX_CHANNEL_CONFIG_NONE;
            ZT_INDEX lResolution = ZDX_CHANNEL_RESOLUTION_NONE;
            switch (iDevice->type) {
                case ZDX_DEVICE_TYPE_AT328P:
                    lType = iType & ZDX_CHANNEL_AT328P_TYPES;
                    if (!((iSpeed > ZDX_CHANNEL_AT328P_MAXSPEED) || (iSpeed < ZDX_CHANNEL_AT328P_MINSPEED))) {lSpeed = iSpeed;}
                    lConfig = iConfig & ZDX_CHANNEL_AT328P_MASK;
                    lResolution = ZDX_CHANNEL_AT328P_RESOLUTION;
                    break;
                default:
                    break;
            }
            if ((lType != ZDX_CHANNEL_TYPE_NONE) && (lSpeed != ZDX_CHANNEL_SPEED_NONE) && (lConfig != ZDX_CHANNEL_CONFIG_NONE)) {
                if (iDevice->channel == NULL) {iDevice->channel = ZTM8_New(sizeof(ZDX_CHANNEL));}
                if (iDevice->channel != NULL) {
                    iDevice->channel->type = lType;
                    iDevice->channel->speed = lSpeed;
                    iDevice->channel->config = lConfig;
                    iDevice->channel->number = ZTM_BitCount(lConfig);
                    iDevice->channel->resolution = lResolution;
                    iDevice->channel->counter.sample = 0;
                    iDevice->channel->counter.line = 0;
                    iDevice->channel->counter.error.header = 0;
                    iDevice->channel->counter.error.payload = 0;
                    iDevice->channel->counter.error.sanity = 0;
                    iDevice->channel->counter.error.unknown = 0;
                    iDevice->channel->counter.total = 0;
                }
            }
        }
	}
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
    if (iDevice != NULL) {
        if (iDevice->channel != NULL) {
            switch (iDevice->channel->type) {
                case ZDX_CHANNEL_TYPE_ANALOG_IN: return iDevice->channel->speed;
                default: break;
            }
        }
    }
    return 0;
}
ZT_FLAG ZDX_GetChannels(ZDX_DEVICE* iDevice) {
    if (iDevice != NULL) {
        if (iDevice->channel != NULL) {
            switch (iDevice->channel->type) {
                case ZDX_CHANNEL_TYPE_ANALOG_IN: return iDevice->channel->config;
                case ZDX_CHANNEL_TYPE_DIGITAL_OUT: return iDevice->channel->config;
                default: break;
            }
        }
    }
    return 0x0;
}
void ZDX_TriggerFree(ZDX_TRIGGER* iTrigger) {
    ZTM8_Free(iTrigger);
}
ZDX_TRIGGER* ZDX_TriggerNew(void) {
    ZDX_TRIGGER* lTrigger;
    if ((lTrigger = ZTM8_Init(sizeof(ZDX_TRIGGER), 0x0)) != NULL) {
        lTrigger->type = ZDX_TYPE_NONE;
        lTrigger->level.xU = 0;
        lTrigger->level.yU = 0;
    }
    return lTrigger;
}

ZT_INDEX ZDX_TriggerCheck(ZDX_TRIGGER* iTrigger, ZDX_DATA* iData, ZT_INDEX iChannel) {
    ZT_INDEX lTriggered = 0;
    if (iTrigger != NULL && iData != NULL) {
        ZT_INDEX lChannels = iData->block.xU;
        if (iChannel < lChannels) {
            ZT_INDEX lCheck = (iTrigger->cursor > iData->cursor) ? (iData->block.yU - iTrigger->cursor + iData->cursor) : (iData->cursor - iTrigger->cursor);
            ZT_INDEX lIndexPrev = iTrigger->cursor ? iTrigger->cursor - 1 : (iData->block.yU - 1);
            for (ZT_INDEX i = 0; i < lCheck; i++) {
                if (iTrigger->cursor == iTrigger->level.xU) {iTrigger->level.xU = -1;}
                if (iTrigger->type & ZDX_TRIGGER_TYPE_FALLING) {
                    if (iData->data[iTrigger->cursor * lChannels + iChannel] <= iTrigger->level.yU && iData->data[lIndexPrev * lChannels + iChannel] > iTrigger->level.yU) {
                        lTriggered++;
                        iTrigger->level.xU = iTrigger->cursor;
                    }
                } else if (iTrigger->type & ZDX_TRIGGER_TYPE_RISING) {
                    if (iData->data[iTrigger->cursor * lChannels + iChannel] >= iTrigger->level.yU && iData->data[lIndexPrev * lChannels + iChannel] < iTrigger->level.yU) {
                        lTriggered++;
                        iTrigger->level.xU = iTrigger->cursor;
                    }
                }
                lIndexPrev = iTrigger->cursor;
                iTrigger->cursor = (iTrigger->cursor + 1) % iData->block.yU;
            }
        }
    }
    return lTriggered;
}

#endif // ZDX_C_INCLUDED
