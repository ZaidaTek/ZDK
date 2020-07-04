/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_CPP_INCLUDED
#define ZTM_CPP_INCLUDED

#include "ZTM_Operators.h"
/*
bool operator!= (const ZT_2U& param0, const ZT_2U& param1) {
    return (param0.x != param1.x || param0.y != param1.y);
}

bool operator== (const ZT_2U& param0, const ZT_2U& param1) {
    return (param0.x == param1.x && param0.y == param1.y);
}

ZT_2U operator+ (const ZT_2U& param0, const ZT_2U& param1) {
    ZT_2U sum;
    sum.x = param0.x + param1.x;
    sum.y = param0.y + param1.y;
    return sum;
}

ZT_2U operator- (const ZT_2U& param0, const ZT_2U& param1) {
    ZT_2U diff;
    diff.x = param0.x - param1.x;
    diff.y = param0.y - param1.y;
    return diff;
}

void operator+= (ZT_2U& param0, const ZT_2U& param1) {
    param0.x += param1.x;
    param0.y += param1.y;
}
void operator-= (ZT_2U& param0, const ZT_2U& param1) {
    param0.x -= param1.x;
    param0.y -= param1.y;
}

void operator+= (ZT_2U& param0, const ZT_U& param1) {
    param0.x += param1;
    param0.y += param1;
}
void operator-= (ZT_2U& param0, const ZT_U& param1) {
    param0.x -= param1;
    param0.y -= param1;
}
void operator*= (ZT_2U& param0, const ZT_U& param1) {
    param0.x *= param1;
    param0.y *= param1;
}
void operator/= (ZT_2U& param0, const ZT_U& param1) {
    param0.x /= param1;
    param0.y /= param1;
}
*/

ZT_2I operator- (const ZT_2I& param0) {
    ZT_2I newPoint;
    newPoint.x = -param0.x;
    newPoint.y = -param0.y;
    return newPoint;
}

bool operator!= (const ZT_2I& param0, const ZT_2I& param1) {
    return (param0.x != param1.x || param0.y != param1.y);
}

bool operator== (const ZT_2I& param0, const ZT_2I& param1) {
    return (param0.x == param1.x && param0.y == param1.y);
}

ZT_2I operator+ (const ZT_2I& param0, const ZT_2I& param1) {
    ZT_2I sum;
    sum.x = param0.x + param1.x;
    sum.y = param0.y + param1.y;
    return sum;
}
ZT_2I operator- (const ZT_2I& param0, const ZT_2I& param1) {
    ZT_2I diff;
    diff.x = param0.x - param1.x;
    diff.y = param0.y - param1.y;
    return diff;
}
ZT_2I operator* (const ZT_2I& param0, const ZT_2I& param1) {
    ZT_2I prod;
    prod.x = param0.x * param1.x;
    prod.y = param0.y * param1.y;
    return prod;
}
ZT_2I operator/ (const ZT_2I& param0, const ZT_2I& param1) {
    ZT_2I quot;
    quot.x = param0.x / param1.x;
    quot.y = param0.y / param1.y;
    return quot;
}
ZT_2I operator+ (const ZT_2I& param0, const ZT_I& param1) {
    ZT_2I sum;
    sum.x = param0.x + param1;
    sum.y = param0.y + param1;
    return sum;
}
ZT_2I operator- (const ZT_2I& param0, const ZT_I& param1) {
    ZT_2I diff;
    diff.x = param0.x - param1;
    diff.y = param0.y - param1;
    return diff;
}
ZT_2I operator* (const ZT_2I& param0, const ZT_I& param1) {
    ZT_2I prod;
    prod.x = param0.x * param1;
    prod.y = param0.y * param1;
    return prod;
}
ZT_2I operator/ (const ZT_2I& param0, const ZT_I& param1) {
    ZT_2I quot;
    quot.x = param0.x / param1;
    quot.y = param0.y / param1;
    return quot;
}
ZT_2I operator<< (const ZT_2I& param0, const ZT_I& param1) {
    ZT_2I lshift;
    lshift.x = param0.x << param1;
    lshift.y = param0.y << param1;
    return lshift;
}
ZT_2I operator>> (const ZT_2I& param0, const ZT_I& param1) {
    ZT_2I shift;
    shift.x = param0.x >> param1;
    shift.y = param0.y >> param1;
    return shift;
}

void operator+= (ZT_2I& param0, const ZT_2I& param1) {
    param0.x += param1.x;
    param0.y += param1.y;
}
void operator-= (ZT_2I& param0, const ZT_2I& param1) {
    param0.x -= param1.x;
    param0.y -= param1.y;
}

void operator+= (ZT_2I& param0, const ZT_I& param1) {
    param0.x += param1;
    param0.y += param1;
}
void operator-= (ZT_2I& param0, const ZT_I& param1) {
    param0.x -= param1;
    param0.y -= param1;
}
void operator*= (ZT_2I& param0, const ZT_I& param1) {
    param0.x *= param1;
    param0.y *= param1;
}
void operator/= (ZT_2I& param0, const ZT_I& param1) {
    param0.x /= param1;
    param0.y /= param1;
}
void operator<<= (ZT_2I& param0, const ZT_I& param1) {
    param0.x <<= param1;
    param0.y <<= param1;
}
void operator>>= (ZT_2I& param0, const ZT_I& param1) {
    param0.x >>= param1;
    param0.y >>= param1;
}


bool operator== (const ZT_RECT& param0, const ZT_I& param1) {
    return ((param0.x == param1) && (param0.y == param1) && (param0.w == param1) && (param0.h == param1));
}
bool operator!= (const ZT_RECT& param0, const ZT_I& param1) {
    return ((param0.x != param1) || (param0.y != param1) || (param0.w != param1) || (param0.h != param1));
}

bool operator== (const ZT_RECT& param0, const ZT_RECT& param1) {
    return ((param0.x == param1.x) && (param0.y == param1.y) && (param0.w == param1.w) && (param0.h == param1.h));
}
bool operator!= (const ZT_RECT& param0, const ZT_RECT& param1) {
    return ((param0.x != param1.x) || (param0.y != param1.y) || (param0.w != param1.w) || (param0.h != param1.h));
}

#endif // ZTM_CPP_INCLUDED
