/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX__RUNTIME_C_INCLUDED
#define ZTX__RUNTIME_C_INCLUDED

#include "ZTX__Runtime.h"

ZT_FLAG rZTX__INIT = 0x1;

void ZTX_Init(ZT_FLAG iFlag) {
    ZTM8_Zero(&rZTX_Host, sizeof(rZTX_Host));
    if (iFlag & ZTX_GZIP) {ZTX_InitZlib();}
    if (iFlag & ZTX_PNG) {ZTX_InitPNG();}
    if (iFlag & ZTX_JPG) {ZTX_InitJPG();}
    rZTX__INIT = 0x0;
}
void ZTX_Exit(void) {
    if (rZTX_Host.flag & ZTX_GZIP) {ZTX_ExitZlib();}
    if (rZTX_Host.flag & ZTX_PNG) {ZTX_ExitPNG();}
    if (rZTX_Host.flag & ZTX_JPG) {ZTX_ExitJPG();}
    rZTX__INIT = 0x1;
}
void ZTX_InitZlib(void) {
    if ((rZTX_Host.zlib.library = ZTL_LibraryLoad(ZTX_LIBRARY_ZLIB)) != NULL) {
        ZT_FLAG lLoaded = 0x1;
        lLoaded &= (rZTX_Host.zlib.f_inflateInit = ZTL_LibraryFunction(rZTX_Host.zlib.library, (const ZT_CHAR*)"inflateInit2_")) != NULL;
        lLoaded &= (rZTX_Host.zlib.f_deflateInit = ZTL_LibraryFunction(rZTX_Host.zlib.library, (const ZT_CHAR*)"deflateInit2_")) != NULL;
        lLoaded &= (rZTX_Host.zlib.f_inflate = ZTL_LibraryFunction(rZTX_Host.zlib.library, (const ZT_CHAR*)"inflate")) != NULL;
        lLoaded &= (rZTX_Host.zlib.f_deflate = ZTL_LibraryFunction(rZTX_Host.zlib.library, (const ZT_CHAR*)"deflate")) != NULL;
        lLoaded &= (rZTX_Host.zlib.f_inflateEnd = ZTL_LibraryFunction(rZTX_Host.zlib.library, (const ZT_CHAR*)"inflateEnd")) != NULL;
        lLoaded &= (rZTX_Host.zlib.f_deflateEnd = ZTL_LibraryFunction(rZTX_Host.zlib.library, (const ZT_CHAR*)"deflateEnd")) != NULL;
        if (lLoaded) {rZTX_Host.flag |= ZTX_GZIP;}
    }
}
void ZTX_ExitZlib(void) {
    ZTL_LibraryFree(rZTX_Host.zlib.library);
    rZTX_Host.flag &= ~ZTX_GZIP;
}
void ZTX_InitPNG(void) {
    if ((rZTX_Host.png.library = ZTL_LibraryLoad(ZTX_LIBRARY_PNG)) != NULL) {
        ZT_FLAG lLoaded = 0x1;
        lLoaded &= (rZTX_Host.png.f_sig_cmp = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_sig_cmp")) != NULL;
        lLoaded &= (rZTX_Host.png.f_create_read_struct = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_create_read_struct")) != NULL;
        lLoaded &= (rZTX_Host.png.f_set_sig_bytes = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_set_sig_bytes")) != NULL;
        lLoaded &= (rZTX_Host.png.f_create_info_struct = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_create_info_struct")) != NULL;
        lLoaded &= (rZTX_Host.png.f_init_io = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_init_io")) != NULL;
        lLoaded &= (rZTX_Host.png.f_read_info = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_read_info")) != NULL;
        lLoaded &= (rZTX_Host.png.f_get_IHDR = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_get_IHDR")) != NULL;
        lLoaded &= (rZTX_Host.png.f_set_strip_16 = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_set_strip_16")) != NULL;
        lLoaded &= (rZTX_Host.png.f_set_palette_to_rgb = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_set_palette_to_rgb")) != NULL;
        lLoaded &= (rZTX_Host.png.f_set_gray_to_rgb = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_set_gray_to_rgb")) != NULL;
        lLoaded &= (rZTX_Host.png.f_get_valid = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_get_valid")) != NULL;
        lLoaded &= (rZTX_Host.png.f_set_tRNS_to_alpha = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_set_tRNS_to_alpha")) != NULL;
        lLoaded &= (rZTX_Host.png.f_set_filler = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_set_filler")) != NULL;
        lLoaded &= (rZTX_Host.png.f_read_image = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_read_image")) != NULL;
        lLoaded &= (rZTX_Host.png.f_destroy_read_struct = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_destroy_read_struct")) != NULL;
        lLoaded &= (rZTX_Host.png.f_create_write_struct = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_create_write_struct")) != NULL;
        lLoaded &= (rZTX_Host.png.f_set_IHDR = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_set_IHDR")) != NULL;
        lLoaded &= (rZTX_Host.png.f_set_rows = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_set_rows")) != NULL;
        lLoaded &= (rZTX_Host.png.f_write_png = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_write_png")) != NULL;
        lLoaded &= (rZTX_Host.png.f_destroy_write_struct = ZTL_LibraryFunction(rZTX_Host.png.library, (const ZT_CHAR*)"png_destroy_write_struct")) != NULL;
        if (lLoaded) {rZTX_Host.flag |= ZTX_PNG;}
    }
}
void ZTX_ExitPNG(void) {
    ZTL_LibraryFree(rZTX_Host.png.library);
    rZTX_Host.flag &= ~ZTX_PNG;
}
void ZTX_InitJPG(void) {
    if ((rZTX_Host.jpg.library = ZTL_LibraryLoad(ZTX_LIBRARY_JPG)) != NULL) {
        ZT_FLAG lLoaded = 0x1;
        lLoaded &= (rZTX_Host.jpg.f_destroy_decompress = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_destroy_decompress")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_std_error = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_std_error")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_CreateDecompress = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_CreateDecompress")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_stdio_src = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_stdio_src")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_read_header = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_read_header")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_start_decompress = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_start_decompress")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_read_scanlines = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_read_scanlines")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_finish_decompress = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_finish_decompress")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_destroy_compress = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_destroy_decompress")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_CreateCompress = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_CreateCompress")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_stdio_dest = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_stdio_dest")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_set_defaults = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_set_defaults")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_set_quality = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_set_quality")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_start_compress = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_start_compress")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_write_scanlines = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_write_scanlines")) != NULL;
        lLoaded &= (rZTX_Host.jpg.f_finish_compress = ZTL_LibraryFunction(rZTX_Host.jpg.library, (const ZT_CHAR*)"jpeg_finish_compress")) != NULL;
        if (lLoaded) {rZTX_Host.flag |= ZTX_JPG;}
    }
}
void ZTX_ExitJPG(void) {
    ZTL_LibraryFree(rZTX_Host.jpg.library);
    rZTX_Host.flag &= ~ZTX_JPG;
}

#endif //ZTX__RUNTIME_C_INCLUDED

