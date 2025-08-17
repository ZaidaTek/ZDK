/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_INTERFACE_C_INCLUDED
#define ZDX_INTERFACE_C_INCLUDED

#include "ZDX__Runtime.h"

void ZDX_InterfaceFree(ZDX_DEVICE* iDevice) {
    switch (iDevice->interface.type) {
        case ZDX_INTERFACE_TYPE_SERIAL: ZTL_SerialFree(iDevice->interface.runtime); break;
        default: break;
    }
    ZTM8_Free(iDevice->interface.buffer.in);
    ZTM8_Free(iDevice->interface.buffer.out);
}
void ZDX_InterfaceNew(ZDX_DEVICE* iDevice) {
    ZT_FLAG lType;
    ZT_INDEX lBufferIn;
    ZT_INDEX lBufferOut;
    ZT_INDEX lBufferCache;
    switch(iDevice->type) {
        case ZDX_DEVICE_TYPE_AT328P:
            lType = ZDX_INTERFACE_TYPE_SERIAL;
            lBufferIn = ZDX_INTERFACE_SERIAL_BUFFER;
            lBufferOut = sizeof(ZT_U) * iDevice->task.number;
            lBufferCache = 0x0;
            break;
        default:
            return;
    }
    iDevice->interface.runtime = NULL;
    iDevice->interface.type = lType;
    iDevice->interface.buffer.cache = lBufferCache;
    iDevice->interface.buffer.in = lBufferIn ? ZTM8_New(lBufferIn) : NULL;
    iDevice->interface.buffer.out = lBufferOut ? ZTM8_New(lBufferOut) : NULL;
}
void ZDX_InterfaceStartSerial(ZDX_DEVICE* iDevice) {
    ZT_INDEX lPacketLength;
    ZT_U8* lPacketBuffer = iDevice->interface.buffer.in;
    switch(iDevice->task.type) {
        case ZDX_TASK_ADC:
            lPacketBuffer[8] = iDevice->task.config;
            lPacketBuffer[7] = iDevice->task.config >> 8;
            lPacketBuffer[6] = iDevice->task.config >> 16;
            lPacketBuffer[5] = iDevice->task.config >> 24;
            lPacketBuffer[4] = (1600000000 / iDevice->task.speed) & 0xff;
            lPacketBuffer[3] = ((1600000000 / iDevice->task.speed) >> 8) & 0xff;
            lPacketBuffer[2] = ((1600000000 / iDevice->task.speed) >> 16) & 0xff;
            lPacketBuffer[1] = ((1600000000 / iDevice->task.speed) >> 24) & 0xff;
            lPacketBuffer[0] = 0x0;
            lPacketLength = 9;
            break;
        case ZDX_TASK_DIO:
            lPacketBuffer[2] = 0x0; // init
            lPacketBuffer[1] = iDevice->task.config;
            lPacketBuffer[0] = 0x2;
            lPacketLength = 3;
            break;
        default:
            return;
    }
    iDevice->interface.runtime = ZTL_SerialNew(iDevice->address, ZDX_INTERFACE_SERIAL_BAUD, ZDX_RUNTIME_BUFFER_SERIAL, ZDX_RUNTIME_BUFFER_SERIAL);
    ZTL_SerialWrite(iDevice->interface.runtime, lPacketBuffer, lPacketLength);
}
void ZDX_InterfaceStart(ZDX_DEVICE* iDevice) {
    switch(iDevice->interface.type) {
        case ZDX_INTERFACE_TYPE_SERIAL: ZDX_InterfaceStartSerial(iDevice); return;
        default: return;
    }
}
void ZDX_InterfaceStop(ZDX_DEVICE* iDevice) {
    switch(iDevice->interface.type) {
        case ZDX_INTERFACE_TYPE_SERIAL: ZDX_InterfaceFree(iDevice); return;
        default: return;
    }
}
ZT_INDEX ZDX_InterfaceQueue(ZDX_DEVICE* iDevice) {
    switch (iDevice->interface.type) {
        case ZDX_INTERFACE_TYPE_SERIAL: return ZTL_SerialQueue(iDevice->interface.runtime);
        default: return 0;
    }
}
ZT_INDEX ZDX_InterfaceReadSerial(ZDX_DEVICE* iDevice, ZDX_DATA* oData) {
    ZT_INDEX lCountRead = 0;
    ZT_INDEX lLengthInput;
    if ((lLengthInput = ZTL_SerialQueue(iDevice->interface.runtime)) > ZDX_INTERFACE_SERIAL_BUFFER) {lLengthInput = ZDX_INTERFACE_SERIAL_BUFFER;}
    if ((lLengthInput = ZTL_SerialRead(iDevice->interface.runtime, iDevice->interface.buffer.in, lLengthInput))) {
        ZT_FLAG lRXCH = iDevice->interface.buffer.cache & 0xffffff;
        ZT_INDEX lChannel = iDevice->interface.buffer.cache >> 24;
        ZT_U* lOutput = (iDevice->flag & ZDX_DEVICE_FLAG_UNBUFFERED && oData != NULL) ? &(oData->data[oData->cursor * oData->block.xU]) : iDevice->interface.buffer.out;
        ZT_FLAG lRXAll = ZTM_BitFillLeft(iDevice->task.number);
        ZT_INDEX lCountLine = 0;
        ZT_INDEX lErrorH = 0;
        ZT_INDEX lErrorL = 0;
        ZT_INDEX lErrorS = 0;
        ZT_INDEX lErrorU = 0;
        for (ZT_INDEX lIndex = 0; lIndex < lLengthInput; lIndex++) {
            ZT_U8 lChar = ((ZT_U8*)iDevice->interface.buffer.in)[lIndex];
            if (lChar & 0x80) {
                if (lRXCH & ZDX_INTERFACE_SERIAL_HEADER) {
                    if (lRXCH & ZDX_INTERFACE_SERIAL_INDEX) {
                        lRXCH &= ~ZDX_INTERFACE_SERIAL_INDEX;
                        ++lErrorU;
                    }
                } else {
                    if (lRXCH & ZDX_INTERFACE_SERIAL_INDEX) {
                        lRXCH &= ~ZDX_INTERFACE_SERIAL_INDEX;
                        lRXCH |= 0x1 << lChannel;
                        ++lErrorL;
                    } else {
                        ++lErrorU;
                    }
                }
                if ((((ZT_INDEX)lChar & 0x7f) >> 3) < iDevice->task.number) {
                    lRXCH |= ZDX_INTERFACE_SERIAL_INDEX;
                    lChannel = (lChar & 0x7f) >> 3;
                    lOutput[lChannel] &= 0x7f;
                    lOutput[lChannel] |= (lChar << 7) & 0x380;
                } else {
                    ++lErrorS;
                }
                lRXCH &= ~ZDX_INTERFACE_SERIAL_HEADER;
            } else {
                if (lRXCH & ZDX_INTERFACE_SERIAL_HEADER) {
                    if (lRXCH & ZDX_INTERFACE_SERIAL_INDEX) {
                        ++lErrorU;
                    } else {
                        ++lErrorH;
                        ++lChannel;
                        lChannel %= iDevice->task.number;
                    }
                } else {
                    if (lRXCH & ZDX_INTERFACE_SERIAL_INDEX) {
                        lRXCH &= ~ZDX_INTERFACE_SERIAL_INDEX;
                        ++lCountRead;
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
                        lOutput = &(oData->data[(oData->cursor = (oData->cursor + 1) % oData->block.yU) * oData->block.xU]);
                    } else {
                        ZDX_DataLineAdd(oData, lOutput);
                    }
                }
                ++lCountLine;
                lRXCH &= ~ZDX_INTERFACE_SERIAL_FLAG_RX;
            }
        }
        iDevice->interface.buffer.cache = lChannel << 24;
        iDevice->interface.buffer.cache |= lRXCH & 0xffffff;
        iDevice->task.counter.total += lLengthInput;
        iDevice->task.counter.error.header += lErrorH;
        iDevice->task.counter.error.payload += lErrorL;
        iDevice->task.counter.error.sanity += lErrorS;
        iDevice->task.counter.error.unknown += lErrorU;
        iDevice->task.counter.line += lCountLine;
        iDevice->task.counter.sample += lCountRead;
    }
    return lCountRead;
}
ZT_INDEX ZDX_InterfaceRead(ZDX_DEVICE* iDevice, ZDX_DATA* oData) {
    switch(iDevice->interface.type) {
        case ZDX_INTERFACE_TYPE_SERIAL: return ZDX_InterfaceReadSerial(iDevice, oData);
        default: return 0;
    }
}

#endif // ZDX_INTERFACE_C_INCLUDED
