/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_DIAGRAM_H_INCLUDED
#define ZDX_DIAGRAM_H_INCLUDED

#include "ZDX.h"

#ifdef __cplusplus
extern 'C' {
#endif // __cplusplus
ZDX_DIAGRAM* ZDX_DiagramNew(ZT_FLAG iType);
void ZDX_DiagramRender(ZDX_DIAGRAM* iDiagram, ZDX_DATA* iData, ZT_SURFACE* oSurface);
void ZDX_DiagramFree(ZDX_DIAGRAM* iDiagram);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZDX_DIAGRAM_H_INCLUDED
