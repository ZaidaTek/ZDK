/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_OPERATORS_H_INCLUDED
#define ZTM_OPERATORS_H_INCLUDED

#include "ZTM.h"

#ifdef __cplusplus
bool operator!= (const ZT_2U& param0, const ZT_2U& param1);
bool operator== (const ZT_2U& param0, const ZT_2U& param1);
ZT_2U operator+ (const ZT_2U& param0, const ZT_2U& param1);
ZT_2U operator- (const ZT_2U& param0, const ZT_2U& param1);
void operator+= (ZT_2U& param0, const ZT_2U& param1);
void operator-= (ZT_2U& param0, const ZT_2U& param1);
void operator+= (ZT_2U& param0, const ZT_I& param1);
void operator-= (ZT_2U& param0, const ZT_I& param1);
void operator*= (ZT_2U& param0, const ZT_I& param1);
void operator/= (ZT_2U& param0, const ZT_I& param1);

ZT_2I operator- (const ZT_2I& param0);
bool operator!= (const ZT_2I& param0, const ZT_2I& param1);
bool operator== (const ZT_2I& param0, const ZT_2I& param1);
ZT_2I operator+ (const ZT_2I& param0, const ZT_2I& param1);
ZT_2I operator- (const ZT_2I& param0, const ZT_2I& param1);
ZT_2I operator* (const ZT_2I& param0, const ZT_2I& param1);
ZT_2I operator/ (const ZT_2I& param0, const ZT_2I& param1);
void operator+= (ZT_2I& param0, const ZT_2I& param1);
void operator-= (ZT_2I& param0, const ZT_2I& param1);

ZT_2I operator+ (const ZT_2I& param0, const ZT_I& param1);
ZT_2I operator- (const ZT_2I& param0, const ZT_I& param1);
ZT_2I operator* (const ZT_2I& param0, const ZT_I& param1);
ZT_2I operator/ (const ZT_2I& param0, const ZT_I& param1);
ZT_2I operator<< (const ZT_2I& param0, const ZT_I& param1);
ZT_2I operator>> (const ZT_2I& param0, const ZT_I& param1);
void operator+= (ZT_2I& param0, const ZT_I& param1);
void operator-= (ZT_2I& param0, const ZT_I& param1);
void operator*= (ZT_2I& param0, const ZT_I& param1);
void operator/= (ZT_2I& param0, const ZT_I& param1);
void operator<<= (ZT_2I& param0, const ZT_I& param1);
void operator>>= (ZT_2I& param0, const ZT_I& param1);

bool operator== (const ZT_RECT& param0, const ZT_I& param1);
bool operator!= (const ZT_RECT& param0, const ZT_I& param1);

bool operator== (const ZT_RECT& param0, const ZT_RECT& param1);
bool operator!= (const ZT_RECT& param0, const ZT_RECT& param1);
#endif // __cplusplus

#endif // ZTM_OPERATORS_H_INCLUDED

