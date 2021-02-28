/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_DEFINE_H_INCLUDED
#define ZTK_DEFINE_H_INCLUDED

#include "ZTK__ID.h"
#include "ZTK__Res.h"

#define ZTK_RENDERER_NONE 0x0
#define ZTK_RENDERER_SYSTEM 0x1
#define ZTK_RENDERER_OPENGL 0x2
#define ZTK_RENDERER_FLIP_V ZTK_RENDERER_OPENGL

#define ZTK_STATE_NONE 0x0
#define ZTK_STATE_DEFINED 0x1
#define ZTK_STATE_REGISTERED 0x2
#define ZTK_STATE_CREATED 0x4
#define ZTK_STATE_OPENED 0x8
#define ZTK_STATE_RUNNING 0x10
#define ZTK_STATE_EXITING 0x40
#define ZTK_STATE_DESTROYED 0x80
#define ZTK_STATE_KEYFOCUS 0x10000000
#define ZTK_STATE_MINIMIZED 0x20000000
#define ZTK_STATE_SHOW 0x40000000
#define ZTK_STATE_ACTIVATED 0x80000000

#define ZTK_TYPE_UNKNOWN 0x0
#define ZTK_TYPE_WIN32 0x1
#define ZTK_TYPE_WIN64 0x100

#endif // ZTK_DEFINE_H_INCLUDED
