/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTGL__RUNTIME_H_INCLUDED
#define ZTGL__RUNTIME_H_INCLUDED

#include "ZTGL.h"
#include <GL/gl.h>
#include <GL/glu.h>

#define ZTGL_FLAG_INIT 0x1
#define ZTGL_MIPMAP_LEVEL 0 // not yet implemented

typedef struct {
    void* runtime;
} rZTGL_HOST;

ZT_FLAG rZTGL__FLAG;
rZTGL_HOST rZTGL_Host;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ZTGL__RUNTIME_H_INCLUDED

