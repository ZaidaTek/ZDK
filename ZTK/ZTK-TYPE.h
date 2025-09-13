/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_TYPES_H_INCLUDED
#define ZTK_TYPES_H_INCLUDED

typedef union {
    struct {
        ZT_INDEX_HALF S;
        ZT_INDEX_HALF H;
        ZT_INDEX_HALF E;
        ZT_FLAG_HALF A;
    };
    struct {
        ZT_FLAG device;
        ZT_FLAG event;
    };
} ZT_ID;
typedef struct {
    ZT_ID id;
    struct {
        ZT_FLAG d0;
        ZT_FLAG d1;
        ZT_FLAG d2;
        ZT_FLAG d3;
    } data;
} ZT_EVENT;

typedef void ZT_SPRITE;
typedef void ZT_FONT;

#endif // ZTK_TYPES_H_INCLUDED
