/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTX_LIBJPEG_C_INCLUDED
#define ZTX_LIBJPEG_C_INCLUDED

#include "ZTX-RT.h"
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

ZT_SURFACE* ZTX_SurfaceNewFromJPGFile(const ZT_CHAR* iPath, ZT_FLAG iPalette) {
	if (rZTX__INIT || !(rZTX_Host.flag & ZTX_JPG)) {return NULL;}
	ZT_SURFACE* lSurface = NULL;
	FILE* lFile = fopen((const char*)iPath, "rb");
	if(lFile != NULL) {
		ZT_U8* lBuffer = NULL;
		struct jpeg_decompress_struct lInfo;
		struct jpeg_error_mgr lError;
		jmp_buf lErrorJump;
		void lErrorFunc(j_common_ptr iInfo) {(void)iInfo; longjmp(lErrorJump, 1);}
		if (setjmp(lErrorJump)) {
			rZTX_Host.jpg.f_destroy_decompress(&lInfo);
			fclose(lFile);
			if (lSurface != NULL) {ZTM_SurfaceFree(lSurface);}
			if (lBuffer != NULL) {ZTM8_Free(lBuffer);}
			return NULL;
		}
		lInfo.err = rZTX_Host.jpg.f_std_error(&lError);
		lError.error_exit = lErrorFunc;
		rZTX_Host.jpg.f_CreateDecompress(&lInfo, JPEG_LIB_VERSION, sizeof(lInfo));
		//jpeg_mem_src(&lInfo, lFileBuffer, lFileBufferSize); // imlement me!
		rZTX_Host.jpg.f_stdio_src(&lInfo, lFile);
		rZTX_Host.jpg.f_read_header(&lInfo, TRUE);
		rZTX_Host.jpg.f_start_decompress(&lInfo);
		ZT_INDEX lMaskA = ZTM_ColorMaskA(iPalette);
		ZT_INDEX lShiftR = ZTM_ColorShiftR(iPalette);
		ZT_INDEX lShiftG = ZTM_ColorShiftG(iPalette);
		ZT_INDEX lShiftB = ZTM_ColorShiftB(iPalette);
		lSurface = ZTM_SurfaceNewFromIntegers(lInfo.output_width, lInfo.output_height, NULL);
		lBuffer = ZTM8_New(sizeof(ZT_U8) * 3 * lSurface->block.x);
		while (lInfo.output_scanline < lInfo.output_height) {
			ZT_I lOffset = lInfo.output_scanline * lSurface->block.x;
			rZTX_Host.jpg.f_read_scanlines(&lInfo, &lBuffer, 1);
			ZT_INDEX lIndexData = -1;
			for (ZT_I x = 0; x < lSurface->block.x; x++) {
				ZT_COLOR lR = lBuffer[++lIndexData];
				ZT_COLOR lG = lBuffer[++lIndexData];
				ZT_COLOR lB = lBuffer[++lIndexData];
				lSurface->pixels[lOffset + x] = (lR << lShiftR) | (lG << lShiftG) | (lB << lShiftB) | lMaskA;
			}
		}
		rZTX_Host.jpg.f_finish_decompress(&lInfo);
		rZTX_Host.jpg.f_destroy_decompress(&lInfo);
		fclose(lFile);
		ZTM8_Free(lBuffer);
	}
	return lSurface;
}
ZT_BOOL ZTX_SurfaceSaveToJPGFileQuality(const ZT_SURFACE* iSurface, const ZT_CHAR* iPath, ZT_FLAG iPalette, ZT_INDEX iQuality) {
	if (rZTX__INIT || !(rZTX_Host.flag & ZTX_JPG)) {return ZT_FALSE;}
	FILE* lFile = fopen((const char*)iPath, "wb");
	if(lFile != NULL) {
		ZT_U8* lBuffer = NULL;
		struct jpeg_compress_struct lInfo;
		struct jpeg_error_mgr lError;
		jmp_buf lErrorJump;
		void lErrorFunc(j_common_ptr iInfo) {(void)iInfo; longjmp(lErrorJump, 1);}
		if (setjmp(lErrorJump)) {
			rZTX_Host.jpg.f_destroy_compress(&lInfo);
			fclose(lFile);
			if (lBuffer != NULL) {ZTM8_Free(lBuffer);}
			return ZT_FALSE;
		}
		lInfo.err = rZTX_Host.jpg.f_std_error(&lError);
		lError.error_exit = lErrorFunc;
		rZTX_Host.jpg.f_CreateCompress(&lInfo, JPEG_LIB_VERSION, sizeof(lInfo));
		//jpeg_mem_src(&lInfo, lFileBuffer, lFileBufferSize); // imlement me in write variant, too!
		rZTX_Host.jpg.f_stdio_dest(&lInfo, lFile);
		lInfo.image_width = iSurface->block.x;
		lInfo.image_height = iSurface->block.y;
		lInfo.input_components = 3;
		lInfo.in_color_space = JCS_RGB;
		rZTX_Host.jpg.f_set_defaults(&lInfo);
		rZTX_Host.jpg.f_set_quality(&lInfo, (iQuality > 100) ? 100 : iQuality, TRUE);
		ZT_INDEX lShiftR = ZTM_ColorShiftR(iPalette);
		ZT_INDEX lShiftG = ZTM_ColorShiftG(iPalette);
		ZT_INDEX lShiftB = ZTM_ColorShiftB(iPalette);
		lBuffer = ZTM8_New(sizeof(ZT_U8) * 3 * iSurface->block.x);
		rZTX_Host.jpg.f_start_compress(&lInfo, TRUE);
		while (lInfo.next_scanline < lInfo.image_height) {
			ZT_I lOffset = lInfo.next_scanline * iSurface->block.x;
			ZT_INDEX lIndexData = -1;
			for (ZT_I x = 0; x < iSurface->block.x; x++) {
				ZT_COLOR lColor = iSurface->pixels[lOffset + x];
				lBuffer[++lIndexData] = lColor >> lShiftR;
				lBuffer[++lIndexData] = lColor >> lShiftG;
				lBuffer[++lIndexData] = lColor >> lShiftB;
			}
			rZTX_Host.jpg.f_write_scanlines(&lInfo, &lBuffer, 1);
		}
		rZTX_Host.jpg.f_finish_compress(&lInfo);
		rZTX_Host.jpg.f_destroy_compress(&lInfo);
		fclose(lFile);
		ZTM8_Free(lBuffer);
		return ZT_TRUE;
	}
	return ZT_FALSE;
}

#endif // ZTX_LIBJPEG_C_INCLUDED
