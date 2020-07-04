/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_RUNTIME_C_INCLUDED
#define ZDX_RUNTIME_C_INCLUDED

#include "ZDX_Runtime.h"

#include <windows.h>

void ZDX_RuntimeFlush(ZDX_INTERFACE* iInterface) {
    if (iInterface != NULL) {
        if (iInterface->runtime != NULL) {
            switch (iInterface->type) {
                case ZDX_INTERFACE_TYPE_SERIAL: {
                        ZDX_RUNTIME_SERIAL* lSerial = iInterface->runtime;
                        if (lSerial->device != NULL) {
                            PurgeComm((HANDLE)lSerial->device, PURGE_RXCLEAR | PURGE_TXCLEAR);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
ZT_INDEX ZDX_RuntimeQueue(ZDX_INTERFACE* iInterface) {
    if (iInterface != NULL) {
        if (iInterface->runtime != NULL) {
            switch (iInterface->type) {
                case ZDX_INTERFACE_TYPE_SERIAL: {
                        ZDX_RUNTIME_SERIAL* lSerial = iInterface->runtime;
                        if (lSerial->device != NULL) {
                            DWORD lError = 0x0;
                            COMSTAT lStatus;
                            ClearCommError((HANDLE)lSerial->device, &lError, &lStatus);
                            return lStatus.cbInQue;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
ZT_INDEX ZDX_RuntimeRead(ZDX_INTERFACE* iInterface, void* iBuffer, ZT_INDEX iLength) {
    ZT_INDEX lRead = 0;
    if (iInterface != NULL && iBuffer != NULL && iLength) {
        if (iInterface->runtime != NULL) {
            ZT_INDEX lLength = iLength;
            switch (iInterface->type) {
                case ZDX_INTERFACE_TYPE_SERIAL: {
                        ZDX_RUNTIME_SERIAL* lSerial = iInterface->runtime;
                        if (lSerial->device != NULL) {
                            ReadFile((HANDLE)lSerial->device, (void*)iBuffer, lLength, (DWORD*)&lRead, NULL);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return lRead;
}
ZT_INDEX ZDX_RuntimeWrite(ZDX_INTERFACE* iInterface, void* iBuffer, ZT_INDEX iLength) {
    if (iInterface != NULL && iBuffer != NULL && iLength) {
        if (iInterface->runtime != NULL) {
            switch (iInterface->type) {
                case ZDX_INTERFACE_TYPE_SERIAL: {
                        ZDX_RUNTIME_SERIAL* lSerial = iInterface->runtime;
                        if (lSerial->device != NULL) {
                            DWORD lSent = 0;
                            WriteFile((HANDLE)lSerial->device, (void*)iBuffer, iLength, &lSent, NULL);
                            return lSent;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
void ZDX_RuntimeNew(ZDX_INTERFACE* iInterface, const ZT_CHAR* iAddress) {
    if (iInterface != NULL && iAddress != NULL) {
        if (iInterface->runtime == NULL) {
            void* lCache = NULL;
            switch (iInterface->type) {
                case ZDX_INTERFACE_TYPE_SERIAL:
                    if ((lCache = (ZDX_RUNTIME_SERIAL*)ZTM8_Init(sizeof(ZDX_RUNTIME_SERIAL), 0x0)) != NULL) {
                        ZDX_RUNTIME_SERIAL* lSerial = lCache;
                        lSerial->device = NULL;
                        if ((lSerial->device = CreateFileA((const char*)iAddress, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE) {
                            DCB lDCB;
                            if (SetupComm((HANDLE)lSerial->device, ZDX_RUNTIME_WINDOWS_SERIAL_BUFFER, ZDX_RUNTIME_WINDOWS_SERIAL_BUFFER) && GetCommState((HANDLE)lSerial->device, &lDCB)) {
                                lDCB.BaudRate = (DWORD)ZDX_INTERFACE_SERIAL_BAUD;
                                lDCB.ByteSize = 8;
                                lDCB.StopBits = ONESTOPBIT;
                                lDCB.Parity = NOPARITY;
                                lDCB.fDtrControl = DTR_CONTROL_ENABLE;
                                if (SetCommState((HANDLE)lSerial->device, &lDCB)) {
                                    Sleep(ZDX_RUNTIME_WINDOWS_SERIAL_SLEEP);
                                    iInterface->runtime = lSerial;
                                    ZDX_RuntimeFlush(iInterface);
                                    return;
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
            if (lCache != NULL) {ZTM8_Free(lCache);}
        }
    }
}
void ZDX_RuntimeFree(ZDX_INTERFACE* iInterface) {
    if (iInterface != NULL) {
        if (iInterface->runtime != NULL) {
            switch (iInterface->type) {
                case ZDX_INTERFACE_TYPE_SERIAL: {
                        ZDX_RUNTIME_SERIAL* lSerial = iInterface->runtime;
                        if (lSerial->device != NULL) {CloseHandle((HANDLE)lSerial->device); lSerial->device = NULL;}
                    }
                    break;
                default:
                    break;
            }
            ZTM8_Free(iInterface->runtime);
            iInterface->runtime = NULL;
        }
    }
}

#endif // ZDX_RUNTIME_C_INCLUDED
