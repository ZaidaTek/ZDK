/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX_RT_H_INCLUDED
#define ZTX_RT_H_INCLUDED

#include "ZTX.h"
    #include <zlib.h>
    #include <png.h>
    #include <jpeglib.h>
    #include <jerror.h>
#if defined(ZTL_BUILD_WINDOWS) && (ZTL_BUILD_WINDOWS)
	#define ZTX_LIBRARY_ZLIB (const ZT_CHAR*)"zlib.dll"
	#define ZTX_LIBRARY_PNG (const ZT_CHAR*)"libpng.dll"
	#define ZTX_LIBRARY_JPG (const ZT_CHAR*)"libjpeg.dll"
#elif defined(ZTL_BUILD_LINUX) && (ZTL_BUILD_LINUX)
	#define ZTX_LIBRARY_ZLIB (const ZT_CHAR*)"libz.so.1"
	#define ZTX_LIBRARY_PNG (const ZT_CHAR*)"libpng16.so.16"
	#define ZTX_LIBRARY_JPG (const ZT_CHAR*)"libjpeg.so.62"
#else // ZTL_BUILD_UNKNOWN
	#define ZTX_LIBRARY_ZLIB (const ZT_CHAR*)""
	#define ZTX_LIBRARY_PNG (const ZT_CHAR*)""
	#define ZTX_LIBRARY_JPG (const ZT_CHAR*)""
#endif // ZTL_BUILD_OS

#define ZTX_MODE_DEFLATE 0x0
#define ZTX_MODE_INFLATE 0x1
#define ZTX_MODE_SIZE 0x2
#define ZTX_MODE_FILE_READ 0x4
#define ZTX_MODE_FILE_WRITE 0x8

#define ZTX_GZIP_CHUNK 16384
#define ZTX_GZIP_CACHE (ZTX_GZIP_CHUNK << 4)
#define ZTX_GZIP_WINDOW_BITS 15
#define ZTX_GZIP_ENCODING 16
#define ZTX_GZIP_ENABLE 32

typedef struct {
    ZT_FLAG flag;
    struct {
        ZT_LIBRARY* library;
        int (*f_inflateInit)(z_stream*, int, const char*, int);
        int (*f_deflateInit)(z_stream*, int, int, int, int, int, const char*, int);
        int (*f_inflate)(z_stream*, int);
        int (*f_deflate)(z_stream*, int);
        int (*f_inflateEnd)(z_stream*);
        int (*f_deflateEnd)(z_stream*);
    } zlib;
    struct {
        ZT_LIBRARY* library;
        int (*f_sig_cmp)(png_const_bytep, size_t, size_t);
        png_structp (*f_create_read_struct)(png_const_charp, png_voidp, png_error_ptr, png_error_ptr);
        void (*f_set_sig_bytes)(png_structrp, int);
        png_infop (*f_create_info_struct)(png_const_structrp);
        void (*f_init_io)(png_structrp, png_FILE_p);
        void (*f_read_info)(png_structrp, png_inforp);
        png_uint_32 (*f_get_IHDR)(png_const_structrp, png_const_inforp, png_uint_32*, png_uint_32*, int*, int*, int*, int*, int*);
        void (*f_set_strip_16)(png_structrp);
        void (*f_set_palette_to_rgb)(png_structrp);
        void (*f_set_gray_to_rgb)(png_structrp);
        png_uint_32 (*f_get_valid)(png_const_structrp, png_const_inforp, png_uint_32);
        void (*f_set_tRNS_to_alpha)(png_structrp);
        void (*f_set_filler)(png_structrp, png_uint_32, int);
        void (*f_read_image)(png_structrp, png_bytepp);
        void (*f_destroy_read_struct)(png_structpp, png_infopp, png_infopp);
        png_structp (*f_create_write_struct)(png_const_charp, png_voidp, png_error_ptr, png_error_ptr);
        void (*f_set_IHDR)(png_const_structrp, png_inforp, png_uint_32, png_uint_32, int, int, int, int, int);
        void (*f_set_rows)(png_const_structrp, png_inforp, png_bytepp);
        void (*f_write_png)(png_structrp, png_inforp, int, png_voidp);
        void (*f_destroy_write_struct)(png_structpp, png_infopp);
    } png;
    struct {
        ZT_LIBRARY* library;
        void (*f_destroy_decompress)(j_decompress_ptr);
        struct jpeg_error_mgr* (*f_std_error)(struct jpeg_error_mgr*);
        void (*f_CreateDecompress)(j_decompress_ptr, int, size_t);
        void (*f_stdio_src)(j_decompress_ptr, FILE*);
        int (*f_read_header)(j_decompress_ptr, boolean);
        boolean (*f_start_decompress)(j_decompress_ptr);
        JDIMENSION (*f_read_scanlines)(j_decompress_ptr, JSAMPARRAY, JDIMENSION);
        boolean (*f_finish_decompress)(j_decompress_ptr);
        void (*f_destroy_compress)(j_compress_ptr);
        void (*f_CreateCompress)(j_compress_ptr, int, size_t);
        void (*f_stdio_dest)(j_compress_ptr, FILE*);
        void (*f_set_defaults)(j_compress_ptr);
        void (*f_set_quality)(j_compress_ptr, int, boolean);
        void (*f_start_compress)(j_compress_ptr, boolean);
        JDIMENSION (*f_write_scanlines)(j_compress_ptr, JSAMPARRAY, JDIMENSION);
        void (*f_finish_compress)(j_compress_ptr);
    } jpg;
} ZTX_HOST;

extern ZT_FLAG rZTX__INIT;
extern ZTX_HOST rZTX_Host;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTX_InitZlib(void);
void ZTX_ExitZlib(void);
void ZTX_InitPNG(void);
void ZTX_ExitPNG(void);
void ZTX_InitJPG(void);
void ZTX_ExitJPG(void);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTX_RT_H_INCLUDED
