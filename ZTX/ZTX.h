/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX_H_INCLUDED
#define ZTX_H_INCLUDED

#include <ZTL.h>
#include "ZTX-zlib.h"
#include "ZTX-libpng.h"
#include "ZTX-libjpeg.h"

#define ZTX_GZIP 0x1
#define ZTX_PNG 0x2
#define ZTX_JPG 0x4

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTX_Init(ZT_FLAG iFlag);
void ZTX_Exit(void);
ZT_FLAG ZTX_State(void);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ZTX_H_INCLUDED
