/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX_LIBPNG_H_INCLUDED
#define ZTX_LIBPNG_H_INCLUDED

#include "ZTX.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_SURFACE* ZTX_SurfaceNewFromPNGFile(const ZT_CHAR* iPath, ZT_FLAG iPalette);
ZT_BOOL ZTX_SurfaceSaveToPNGFile(const ZT_SURFACE* iSurface, const ZT_CHAR* iPath, ZT_FLAG iPalette);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTX_LIBPNG_H_INCLUDED
