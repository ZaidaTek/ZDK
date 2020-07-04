/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_INTERFACE_C_INCLUDED
#define ZDX_INTERFACE_C_INCLUDED

#include "ZDX_Interface.h"

void ZDX_InterfaceFree(ZDX_DEVICE* iDevice) {
    if (iDevice != NULL) {
        if (iDevice->interface != NULL) {
            ZDX_RuntimeFree(iDevice->interface);
            if (iDevice->interface->buffer.in != NULL) {ZTM8_Free(iDevice->interface->buffer.in);}
            if (iDevice->interface->buffer.out != NULL) {ZTM8_Free(iDevice->interface->buffer.out);}
            ZTM8_Free(iDevice->interface);
            iDevice->interface = NULL;
        }
    }
}
void ZDX_InterfaceNew(ZDX_DEVICE* iDevice) {
    if (iDevice != NULL) {
        ZDX_InterfaceFree(iDevice);
        if (iDevice->interface == NULL && iDevice->channel != NULL) {
            ZT_FLAG lType = ZDX_INTERFACE_TYPE_NONE;
            ZT_INDEX lBufferIn = 0;
            ZT_INDEX lBufferOut = 0;
            ZT_INDEX lBufferCache = 0x0;
            switch(iDevice->type) {
                case ZDX_DEVICE_TYPE_AT328P:
                    lType = ZDX_INTERFACE_TYPE_SERIAL;
                    lBufferIn = ZDX_INTERFACE_SERIAL_BUFFER;
                    lBufferOut = sizeof(ZT_U) * iDevice->channel->number;
                    break;
                default:
                    break;
            }
            if (lType != ZDX_INTERFACE_TYPE_NONE) {
                ZDX_INTERFACE* lInterface = NULL;
                if ((lInterface = ZTM8_New(sizeof(ZDX_INTERFACE))) != NULL) {
                    lInterface->runtime = NULL;
                    lInterface->type = lType;
                    lInterface->buffer.cache = lBufferCache;
                    if (lBufferIn ? ((lInterface->buffer.in = ZTM8_Init(lBufferIn, 0x0)) != NULL) : !lBufferIn) {
                        if (lBufferOut ? ((lInterface->buffer.out = ZTM8_Init(lBufferOut, 0x0)) != NULL) : !lBufferOut) {
                            iDevice->interface = lInterface;
                            return;
                        }
                        ZTM8_Free(lInterface->buffer.in);
                    }
                    ZTM8_Free(lInterface);
                }
            }
        }
    }
}
void ZDX_InterfaceStart(ZDX_DEVICE* iDevice) {
    if (iDevice != NULL) {
        if (iDevice->interface != NULL && iDevice->channel != NULL) {
            void* lPackets = NULL;
            ZT_INDEX lLength = 0;
            switch(iDevice->interface->type) {
                case ZDX_INTERFACE_TYPE_SERIAL: {
                        ZT_U8* lBuffer = iDevice->interface->buffer.in;
                        switch(iDevice->channel->type) {
                            case ZDX_CHANNEL_TYPE_ANALOG_IN:
                                lBuffer[8] = iDevice->channel->config;
                                lBuffer[7] = iDevice->channel->config >> 8;
                                lBuffer[6] = iDevice->channel->config >> 16;
                                lBuffer[5] = iDevice->channel->config >> 24;
                                lBuffer[4] = (1600000000 / iDevice->channel->speed) & 0xff;
                                lBuffer[3] = ((1600000000 / iDevice->channel->speed) >> 8) & 0xff;
                                lBuffer[2] = ((1600000000 / iDevice->channel->speed) >> 16) & 0xff;
                                lBuffer[1] = ((1600000000 / iDevice->channel->speed) >> 24) & 0xff;
                                lBuffer[0] = 0x0;
                                lLength = 9;
                                break;
                            case ZDX_CHANNEL_TYPE_DIGITAL_OUT:
                                lBuffer[2] = 0x0; // init
                                lBuffer[1] = iDevice->channel->config;
                                lBuffer[0] = 0x2;
                                lLength = 3;
                                break;
                            default:
                                break;
                        }
                        if (lLength) {lPackets = lBuffer;}
                    }
                    break;
                default:
                    break;
            }
            if (lPackets != NULL && lLength) {
                ZDX_RuntimeNew(iDevice->interface, iDevice->address);
                ZDX_RuntimeWrite(iDevice->interface, lPackets, lLength);
            }
        }
    }
}
void ZDX_InterfaceStop(ZDX_DEVICE* iDevice) {
    if (iDevice != NULL) {
        if (iDevice->interface != NULL) {
            switch(iDevice->interface->type) {
                case ZDX_INTERFACE_TYPE_SERIAL:
                    ZDX_InterfaceFree(iDevice);
                    break;
                default:
                    break;
            }
        }
    }
}
ZT_INDEX ZDX_InterfaceQueue(ZDX_DEVICE* iDevice) {
    if (iDevice != NULL) {
        return ZDX_RuntimeQueue(iDevice->interface);
    }
    return 0;
}
ZT_INDEX ZDX_InterfaceRead(ZDX_DEVICE* iDevice, ZDX_DATA* oData) {
    if (iDevice != NULL) {
        if (iDevice->interface != NULL && iDevice->channel != NULL) {
            ZT_INDEX lLengthInput = ZDX_RuntimeQueue(iDevice->interface);
            if (lLengthInput && iDevice->interface->buffer.in != NULL && iDevice->interface->buffer.out != NULL) {
                switch(iDevice->interface->type) {
                    case ZDX_INTERFACE_TYPE_SERIAL:
                        if (lLengthInput > ZDX_INTERFACE_SERIAL_BUFFER) {lLengthInput = ZDX_INTERFACE_SERIAL_BUFFER;}
                        lLengthInput = ZDX_RuntimeRead(iDevice->interface, iDevice->interface->buffer.in, lLengthInput);
                        if (lLengthInput) {
                            ZT_FLAG lRXCH = iDevice->interface->buffer.cache & 0xffffff;
                            ZT_INDEX lChannel = iDevice->interface->buffer.cache >> 24;
                            ZT_U* lOutput = iDevice->interface->buffer.out;
                            ZT_FLAG lRXAll = ZTM_BitFillLeft(iDevice->channel->number);
                            ZT_INDEX lCountRead = 0;
                            ZT_INDEX lCountLine = 0;
                            ZT_INDEX lErrorH = 0;
                            ZT_INDEX lErrorL = 0;
                            ZT_INDEX lErrorS = 0;
                            ZT_INDEX lErrorU = 0;
                            for (ZT_INDEX lIndex = 0; lIndex < lLengthInput; lIndex++) {
                                if (iDevice->flag & ZDX_DEVICE_FLAG_UNBUFFERED) {
                                    if (oData != NULL) {
                                        if (oData->data != NULL) {
                                            lOutput = &(oData->data[oData->cursor * oData->block.xU]);
                                        }
                                    }
                                }
                                ZT_U8 lChar = ((ZT_U8*)iDevice->interface->buffer.in)[lIndex];
                                if (lChar & 0x80) {
                                    if (lRXCH & ZDX_INTERFACE_SERIAL_HEADER) {
                                        if (lRXCH & ZDX_INTERFACE_SERIAL_INDEX) {
                                            lRXCH &= ~ZDX_INTERFACE_SERIAL_INDEX;
                                            lErrorU++;
                                        }
                                    } else {
                                        if (lRXCH & ZDX_INTERFACE_SERIAL_INDEX) {
                                            lRXCH &= ~ZDX_INTERFACE_SERIAL_INDEX;
                                            lRXCH |= 0x1 << lChannel;
                                            lErrorL++;
                                        } else {
                                            lErrorU++;
                                        }
                                    }
                                    if ((((ZT_INDEX)lChar & 0x7f) >> 3) < iDevice->channel->number) {
                                        lRXCH |= ZDX_INTERFACE_SERIAL_INDEX;
                                        lChannel = (lChar & 0x7f) >> 3;
                                        lOutput[lChannel] &= 0x7f;
                                        lOutput[lChannel] |= (lChar << 7) & 0x380;
                                    } else {
                                        lErrorS++;
                                    }
                                    lRXCH &= ~ZDX_INTERFACE_SERIAL_HEADER;
                                } else {
                                    if (lRXCH & ZDX_INTERFACE_SERIAL_HEADER) {
                                        if (lRXCH & ZDX_INTERFACE_SERIAL_INDEX) {
                                            lErrorU++;
                                        } else {
                                            lErrorH++;
                                            lChannel++;
                                            lChannel %= iDevice->channel->number;
                                        }
                                    } else {
                                        if (lRXCH & ZDX_INTERFACE_SERIAL_INDEX) {
                                            lRXCH &= ~ZDX_INTERFACE_SERIAL_INDEX;
                                            lCountRead++;
                                        } else {
                                            lRXCH |= ZDX_INTERFACE_SERIAL_INDEX;
                                        }
                                    }
                                    lRXCH |= (0x1 << lChannel);
                                    lOutput[lChannel] &= 0x380;
                                    lOutput[lChannel] |= lChar;
                                    lRXCH |= ZDX_INTERFACE_SERIAL_HEADER;
                                }
                                if ((lRXCH & ZDX_INTERFACE_SERIAL_FLAG_RX) == lRXAll) {
                                    if (oData != NULL) {
                                        if (iDevice->flag & ZDX_DEVICE_FLAG_UNBUFFERED) {
                                            oData->cursor = (oData->cursor + 1) % oData->block.yU;
                                        } else {
                                            ZDX_DataLineAdd(oData, lOutput);
                                        }
                                    }
                                    lCountLine++;
                                    lRXCH &= ~ZDX_INTERFACE_SERIAL_FLAG_RX;
                                }
                            }
                            iDevice->interface->buffer.cache = lChannel << 24;
                            iDevice->interface->buffer.cache |= lRXCH & 0xffffff;
                            iDevice->channel->counter.total += lLengthInput;
                            iDevice->channel->counter.error.header += lErrorH;
                            iDevice->channel->counter.error.payload += lErrorL;
                            iDevice->channel->counter.error.sanity += lErrorS;
                            iDevice->channel->counter.error.unknown += lErrorU;
                            iDevice->channel->counter.line += lCountLine;
                            iDevice->channel->counter.sample += lCountRead;
                            return lCountRead;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return 0;
}

#endif // ZDX_INTERFACE_C_INCLUDED
