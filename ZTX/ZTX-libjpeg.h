/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX_LIBJPEG_H_INCLUDED
#define ZTX_LIBJPEG_H_INCLUDED

#include "ZTX.h"

#define ZTX_JPG_QUALITY 80

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_SURFACE* ZTX_SurfaceNewFromJPGFile(const ZT_CHAR* iPath, ZT_FLAG iPalette);
ZT_BOOL ZTX_SurfaceSaveToJPGFileQuality(const ZT_SURFACE* iSurface, const ZT_CHAR* iPath, ZT_FLAG iPalette, ZT_INDEX iQuality);
#define ZTX_SurfaceSaveToJPGFile(SURFACE,PATH,PALETTE) ZTX_SurfaceSaveToJPGFileQuality(SURFACE,PATH,PALETTE,ZTX_JPG_QUALITY)
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTX_LIBJPEG_H_INCLUDED
