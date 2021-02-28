/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__RUNTIME_C_INCLUDED
#define ZTK__RUNTIME_C_INCLUDED

#include "ZTK__Runtime.h"
const ZT_RECT* ZTK_InternalRect(void) {return &rZTK_Host.rect;}
const ZT_POINT* ZTK_InternalPos(void) {return &rZTK_Host.rect.pos;}
const ZT_POINT* ZTK_InternalSize(void) {return &rZTK_Host.rect.size;}
const ZT_I* ZTK_InternalX(void) {return &rZTK_Host.rect.x;}
const ZT_I* ZTK_InternalY(void) {return &rZTK_Host.rect.y;}
const ZT_I* ZTK_InternalWidth(void) {return &rZTK_Host.rect.w;}
const ZT_I* ZTK_InternalHeight(void) {return &rZTK_Host.rect.h;}
const ZT_TIME* ZTK_InternalTick(void) {return &rZTK_Host.system.last.loop;}
const ZT_FLAG* ZTK_InternalPalette(void) {return &rZTK_Host.user.palette;}
const ZT_FLAG* ZTK_InternalPaletteSystem(void) {return &rZTK_Host.system.palette;}
const ZT_POINT* ZTK_InternalMousePos(void) {return &rZTK_Host.system.input.mouse.pos;}
const ZT_FLAG* ZTK_InternalMouseState(void) {return &rZTK_Host.system.input.mouse.state;}
const ZT_COLOR* ZTK_InternalBackground(void) {return &rZTK_Host.user.background;}
rZT_FONT** ZTK_InternalFont(void) {return &rZTK_Host.user.font;}
rZT_FONT** ZTK_InternalFontSystem(void) {return &rZTK_Host.system.font;}
#endif // ZTK__RUNTIME_C_INCLUDED
