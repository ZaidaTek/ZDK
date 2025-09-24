/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTGL_RT_H_INCLUDED
#define ZTGL_RT_H_INCLUDED

#include "ZTK-RT.h"
#include "ZTGL.h"
#include <GL/gl.h>
#include <GL/glu.h>

#define ZTGL_FLAG_INIT 0x1
#define ZTGL_MIPMAP_LEVEL 0 // not yet implemented

typedef struct {
	void* runtime;
} rZTGL_RUNTIME;

extern ZT_FLAG rZTGL__FLAG;
extern rZTGL_RUNTIME rZTGL_Host;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTGL_RT_H_INCLUDED
