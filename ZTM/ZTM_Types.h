/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_TYPES_H_INCLUDED
#define ZTM_TYPES_H_INCLUDED

#ifndef ZTM__OS__BITS
#define ZTM__OS__BITS 32
#endif // ZTM__OS__BITS

#define ZT_TYPE_FLT float
#define ZT_TYPE_DBL double
#if (ZTM__OS__BITS > 32) // 64-bit
#define ZT_TYPE_I8 char
#define ZT_TYPE_I16 short
#define ZT_TYPE_I32 int
#define ZT_TYPE_I64 long long
#define ZT_TYPE_U8 unsigned ZT_TYPE_I8
#define ZT_TYPE_U16 unsigned ZT_TYPE_I16
#define ZT_TYPE_U32 unsigned ZT_TYPE_I32
#define ZT_TYPE_U64 unsigned ZT_TYPE_I64
#define ZT_TYPE_BL ZT_TYPE_U32
#elif (ZTM__OS__BITS > 16) // 32-bit
#define ZT_TYPE_I8 char
#define ZT_TYPE_I16 short
#define ZT_TYPE_I32 int
#define ZT_TYPE_I64 long long
#define ZT_TYPE_U8 unsigned ZT_TYPE_I8
#define ZT_TYPE_U16 unsigned ZT_TYPE_I16
#define ZT_TYPE_U32 unsigned ZT_TYPE_I32
#define ZT_TYPE_U64 unsigned ZT_TYPE_I64
#define ZT_TYPE_BL ZT_TYPE_U32
#elif (ZTM__OS__BITS > 8) // 16-bit
#define ZT_TYPE_I8 char
#define ZT_TYPE_I16 int
#define ZT_TYPE_I32 long
#define ZT_TYPE_I64 long long
#define ZT_TYPE_U8 unsigned ZT_TYPE_I8
#define ZT_TYPE_U16 unsigned ZT_TYPE_I16
#define ZT_TYPE_U32 unsigned ZT_TYPE_I32
#define ZT_TYPE_U64 unsigned ZT_TYPE_I64 // ?
#define ZT_TYPE_BL ZT_TYPE_U16
#else // 8-bit
#define ZT_TYPE_I8 char
#define ZT_TYPE_I16 int
#define ZT_TYPE_I32 long
#define ZT_TYPE_I64 ZT_TYPE_I32
#define ZT_TYPE_U8 unsigned ZT_TYPE_I8
#define ZT_TYPE_U16 unsigned ZT_TYPE_I16
#define ZT_TYPE_U32 unsigned ZT_TYPE_I32
#define ZT_TYPE_U64 unsigned ZT_TYPE_I64 // ?
#define ZT_TYPE_BL ZT_TYPE_U8
#endif
typedef ZT_TYPE_FLT ZT_FLT;
typedef ZT_TYPE_DBL ZT_DBL;
typedef ZT_TYPE_BL ZT_BOOL;
typedef ZT_TYPE_I8 ZT_I8;
typedef ZT_TYPE_I16 ZT_I16;
typedef ZT_TYPE_I32 ZT_I32;
typedef ZT_TYPE_I64 ZT_I64;
typedef ZT_TYPE_U8 ZT_U8;
typedef ZT_TYPE_U16 ZT_U16;
typedef ZT_TYPE_U32 ZT_U32;
typedef ZT_TYPE_U64 ZT_U64;
#if (ZTM__OS__BITS > 16) // 32-bit and above
typedef ZT_TYPE_I32 ZT_I;
typedef ZT_TYPE_U32 ZT_U;
typedef ZT_TYPE_U32 ZT_TIME;
typedef ZT_TYPE_U32 ZT_COLOR;
typedef ZT_TYPE_U32 ZT_INDEX;
typedef ZT_TYPE_U32 ZT_SIZE;
typedef ZT_TYPE_U32 ZT_FLAG;
typedef ZT_TYPE_U16 ZT_INDEX_HALF;
typedef ZT_TYPE_U16 ZT_FLAG_HALF;
typedef ZT_TYPE_U8 ZT_INDEX_QUARTER;
typedef ZT_TYPE_U8 ZT_FLAG_QUARTER;
#elif (ZTM__OS__BITS > 8) // 16-bit
typedef ZT_TYPE_I16 ZT_I;
typedef ZT_TYPE_U16 ZT_U;
typedef ZT_TYPE_U32 ZT_TIME;
typedef ZT_TYPE_U16 ZT_COLOR;
typedef ZT_TYPE_U16 ZT_INDEX;
typedef ZT_TYPE_U32 ZT_SIZE;
typedef ZT_TYPE_U16 ZT_FLAG;
typedef ZT_TYPE_U8 ZT_INDEX_HALF;
typedef ZT_TYPE_U8 ZT_FLAG_HALF;
typedef ZT_TYPE_U8 ZT_INDEX_QUARTER;
typedef ZT_TYPE_U8 ZT_FLAG_QUARTER;
#else // 8-bit
typedef ZT_TYPE_I16 ZT_I;
typedef ZT_TYPE_U16 ZT_U;
typedef ZT_TYPE_U32 ZT_TIME;
typedef ZT_TYPE_U16 ZT_COLOR;
typedef ZT_TYPE_U8 ZT_INDEX;
typedef ZT_TYPE_U8 ZT_FLAG;
typedef ZT_TYPE_U8 ZT_INDEX_HALF;
typedef ZT_TYPE_U8 ZT_FLAG_HALF;
typedef ZT_TYPE_U8 ZT_INDEX_QUARTER;
typedef ZT_TYPE_U8 ZT_FLAG_QUARTER;
#endif

#define ZT_TRUE 0x1u
#define ZT_FALSE 0x0u

typedef union {
    struct {
        ZT_I x;
        ZT_I y;
    };
    struct {
        ZT_I mn;
        ZT_I mx;
    };
    struct {
        ZT_U xU;
        ZT_U yU;
    };
    struct {
        ZT_U mnU;
        ZT_U mxU;
    };
} ZT_2I, ZT_2U, ZT_POINT, ZT_UPOINT, ZT_MINMAX;
typedef union {
    struct {
        ZT_U xU;
        ZT_U yU;
        ZT_U zU;
    };
    struct {
        ZT_I x;
        ZT_I y;
        ZT_I z;
    };
} ZT_3U, ZT_3I;
typedef union {
    struct {
        ZT_POINT pos;
        ZT_POINT size;
    };
    struct {
        ZT_U x0U;
        ZT_U x1U;
        ZT_U y0U;
        ZT_U y1U;
    };
    struct {
        ZT_I x0;
        ZT_I x1;
        ZT_I y0;
        ZT_I y1;
    };
    struct {
        ZT_U aU;
        ZT_U bU;
        ZT_U cU;
        ZT_U dU;
    };
    struct {
        ZT_I a;
        ZT_I b;
        ZT_I c;
        ZT_I d;
    };
    struct {
        ZT_U xU;
        ZT_U yU;
        ZT_U wU;
        ZT_U hU;
    };
    struct {
        ZT_I x;
        ZT_I y;
        ZT_I w;
        ZT_I h;
    };
} ZT_2X2U, ZT_2X2I, ZT_4U, ZT_4I, ZT_URECT, ZT_RECT;

typedef struct {
    ZT_U16 year;
    ZT_U8 month;
    ZT_U8 day;
    ZT_U8 hour;
    ZT_U8 minute;
    ZT_U16 second;
} ZT_DATE;
typedef struct {
    ZT_U16 year;
    ZT_U8 month;
    ZT_U8 day;
    ZT_U8 hour;
    ZT_U8 minute;
    ZT_U16 second;
	struct {
		ZT_TIME timestamp;
		ZT_TIME timezone;
		ZT_U16 ordinal;
		ZT_U8 week;
		ZT_U8 weekday;
	} extra;
} ZT_DATE_EXTRA;

typedef union {
    ZT_U8 byte[4];
    ZT_U16 word[2];
    ZT_U32 data[1];
} ZT_HASH32;
typedef union {
    ZT_U8 byte[8];
    ZT_U16 word[4];
    ZT_U32 data[2];
    ZT_U64 quad[1];
    //ZT_U64 dummy64; //???
} ZT_HASH64;
typedef union {
    ZT_U8 byte[16];
    ZT_U16 word[8];
    ZT_U32 data[4];
    ZT_U64 quad[2];
} ZT_HASH128;
typedef union {
    ZT_U8 byte[32];
    ZT_U16 word[16];
    ZT_U32 data[8];
    ZT_U64 quad[4];
} ZT_HASH256;
typedef union {
    ZT_U8 byte[64];
    ZT_U16 word[32];
    ZT_U32 data[16];
    ZT_U64 quad[8];
} ZT_HASH512;
typedef union {
    ZT_U8 byte[128];
    ZT_U16 word[64];
    ZT_U32 data[32];
    ZT_U64 quad[16];
} ZT_HASH1024;

typedef ZT_U8 ZT_CHAR;

typedef struct {
	ZT_SIZE length;
	union {
		ZT_U64* quad;
		ZT_U32* data;
		ZT_U16* word;
		ZT_U8* byte;
		void* payload;
	};
} ZT_DATA;// ZT_DATA_U8, ZT_DATA_U16, ZT_DATA_U32, ZT_DATA_U64;

typedef struct {
    ZT_POINT block;
    ZT_COLOR* pixels;
} ZT_SURFACE;

typedef struct {
	void** items;
	ZT_INDEX length;
} ZT_LIST;
typedef struct {
	void** items;
    ZT_INDEX length;
    ZT_INDEX data;
    ZT_INDEX user;
} ZT_QLIST;

typedef struct {
    void* handle;
    const ZT_CHAR* path;
    ZT_SIZE length;
    ZT_SIZE alloc;
    ZT_U64 id;
    ZT_INDEX owner;
    ZT_INDEX group;
    ZT_FLAG type;
    ZT_FLAG perm;
    ZT_FLAG flag;
    ZT_FLAG attr;
    struct {
        ZT_U64 meta_a;
        ZT_U64 meta_b;
        ZT_U64 meta_m;
        ZT_U64 file_a;
        ZT_U64 file_b;
        ZT_U64 file_m;
    } time;
} ZT_META_FILE;

#endif // ZTM_TYPES_H_INCLUDED
