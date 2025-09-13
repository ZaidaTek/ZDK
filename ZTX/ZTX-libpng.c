/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX_LIBPNG_C_INCLUDED
#define ZTX_LIBPNG_C_INCLUDED

#include "ZTX-RT.h"
#include <stdio.h>

ZT_SURFACE* ZTX_SurfaceNewFromPNGFile(const ZT_CHAR* iPath, ZT_FLAG iPalette) {
    if (rZTX__INIT || !(rZTX_Host.flag & ZTX_PNG)) {return NULL;}
    ZT_SURFACE* lSurface = NULL;
    FILE* lFile = fopen((const char*)iPath, "rb");
    if (lFile != NULL) {
        ZT_U8 lHeader[8];
        fread(lHeader, 4, 2, lFile);
        if (!rZTX_Host.png.f_sig_cmp(lHeader, 0, 8)) {
            png_struct* lPNG = rZTX_Host.png.f_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            if (lPNG != NULL) {
                rZTX_Host.png.f_set_sig_bytes(lPNG, 8);
                png_info* lInfo = rZTX_Host.png.f_create_info_struct (lPNG);
                if (lInfo != NULL) {
                    rZTX_Host.png.f_init_io(lPNG, lFile);
                    rZTX_Host.png.f_read_info(lPNG, lInfo);
                    ZT_POINT lSize;
                    ZT_INDEX lDepth;
                    ZT_FLAG lPalette;
                    ZT_FLAG lFilter;
                    ZT_FLAG lCompression;
                    ZT_FLAG lInterlace;
                    rZTX_Host.png.f_get_IHDR(lPNG, lInfo, &lSize.xU, &lSize.yU, (int*)&lDepth, (int*)&lPalette, (int*)&lFilter, (int*)&lCompression, (int*)&lInterlace);
                    //printf("%d %d %u %x %x %x %x\n", lSize.x, lSize.y, lDepth, lPalette, lFilter, lCompression, lInterlace);
                    if (lDepth == 16) {rZTX_Host.png.f_set_strip_16(lPNG);}
                    if (lPalette == PNG_COLOR_TYPE_PALETTE) {rZTX_Host.png.f_set_palette_to_rgb(lPNG);}
                    if (lPalette == PNG_COLOR_TYPE_GRAY || lPalette == PNG_COLOR_TYPE_GRAY_ALPHA) {rZTX_Host.png.f_set_gray_to_rgb(lPNG);}
                    if (rZTX_Host.png.f_get_valid(lPNG, lInfo, PNG_INFO_tRNS)) {rZTX_Host.png.f_set_tRNS_to_alpha(lPNG);}
                    rZTX_Host.png.f_set_filler(lPNG, 0xff, PNG_FILLER_AFTER);
                    lSurface = ZTM_SurfaceNew(&lSize, NULL);
                    ZT_U8** lRows = ZTM8_New(sizeof(ZT_U8*) * lSize.y);
                    for (ZT_I y = 0; y < lSize.y; y++) {lRows[y] = (ZT_U8*)&lSurface->pixels[y * lSize.x];}
                    rZTX_Host.png.f_read_image(lPNG, lRows);
                    ZTM_SurfaceConvert(lSurface, ZTM_PALETTE_ABGR, iPalette);
                    ZTM8_Free(lRows);
                }
                rZTX_Host.png.f_destroy_read_struct(&lPNG, &lInfo, NULL);
            }
        }
        fclose(lFile);
    }
    return lSurface;
}
ZT_BOOL ZTX_SurfaceSaveToPNGFile(const ZT_SURFACE* iSurface, const ZT_CHAR* iPath, ZT_FLAG iPalette) {
    if (rZTX__INIT || !(rZTX_Host.flag & ZTX_PNG)) {return ZT_FALSE;}
    ZT_BOOL lWriteOK;
    FILE* lFile = fopen((const char*)iPath, "wb");
    if ((lWriteOK = (lFile != NULL) ? ZT_TRUE : ZT_FALSE)) {
        png_struct* lPNG = rZTX_Host.png.f_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if ((lWriteOK = (lPNG != NULL) ? ZT_TRUE : ZT_FALSE)) {
            png_info* lInfo = rZTX_Host.png.f_create_info_struct(lPNG);
            if ((lWriteOK = (lInfo != NULL) ? ZT_TRUE : ZT_FALSE)) {
                ZT_COLOR* lPixels;
                if (iPalette != ZTM_PALETTE_ABGR) {
                    ZTM_PixelsConvert(iSurface->pixels, (lPixels = ZTM32_NewBlock(&iSurface->block)), ZTM_UPointArea(&iSurface->block), iPalette, ZTM_PALETTE_ABGR);
                } else {
                    lPixels = iSurface->pixels;
                }
                ZT_U8** lRows = ZTM8_New(sizeof(ZT_U8*) * iSurface->block.y);
                for (ZT_I y = 0; y < iSurface->block.y; y++) {lRows[y] = (ZT_U8*)&lPixels[y * iSurface->block.x];}
                rZTX_Host.png.f_set_IHDR(lPNG, lInfo, iSurface->block.x, iSurface->block.y, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
                //png_set_compression_level(lPNG, 6);
                rZTX_Host.png.f_init_io(lPNG, lFile);
                rZTX_Host.png.f_set_rows(lPNG, lInfo, lRows);
                rZTX_Host.png.f_write_png(lPNG, lInfo, PNG_TRANSFORM_IDENTITY, NULL);
                if (iPalette != ZTM_PALETTE_ABGR) {ZTM32_Free(lPixels);}
                ZTM8_Free(lRows);
            }
            rZTX_Host.png.f_destroy_write_struct(&lPNG, &lInfo);
        }
        fclose(lFile);
    }
    return lWriteOK;
}

#endif // ZTX_LIBPNG_C_INCLUDED
