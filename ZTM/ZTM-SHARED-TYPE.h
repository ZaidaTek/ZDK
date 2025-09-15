/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_SHARED_TYPE_H_INCLUDED
#define ZTM_SHARED_TYPE_H_INCLUDED

#ifndef ZTM_BUILD_WIDTH
	#define ZTM_BUILD_WIDTH 32
#endif // ZTM_BUILD_WIDTH

#define ZT_TYPE_FLT float
#define ZT_TYPE_DBL double
typedef ZT_TYPE_FLT ZT_FLT;
typedef ZT_TYPE_DBL ZT_DBL;
#if (ZTM_BUILD_WIDTH > 32) // 64-bit
	#define ZT_TYPE_I8 char
	#define ZT_TYPE_I16 short
	#define ZT_TYPE_I32 int
	#define ZT_TYPE_I64 long long
	#define ZT_TYPE_U8 unsigned ZT_TYPE_I8
	#define ZT_TYPE_U16 unsigned ZT_TYPE_I16
	#define ZT_TYPE_U32 unsigned ZT_TYPE_I32
	#define ZT_TYPE_U64 unsigned ZT_TYPE_I64
	#define ZT_TYPE_BL ZT_TYPE_U32
#elif (ZTM_BUILD_WIDTH > 16) // 32-bit
	#define ZT_TYPE_I8 char
	#define ZT_TYPE_I16 short
	#define ZT_TYPE_I32 int
	#define ZT_TYPE_I64 long long
	#define ZT_TYPE_U8 unsigned ZT_TYPE_I8
	#define ZT_TYPE_U16 unsigned ZT_TYPE_I16
	#define ZT_TYPE_U32 unsigned ZT_TYPE_I32
	#define ZT_TYPE_U64 unsigned ZT_TYPE_I64
	#define ZT_TYPE_BL ZT_TYPE_U32
#elif (ZTM_BUILD_WIDTH > 8) // 16-bit
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
#endif // ZTM_BUILD_WIDTH
typedef ZT_TYPE_BL ZT_BOOL;
typedef ZT_TYPE_BL ZT_BLTG;
typedef ZT_TYPE_I8 ZT_I8;
typedef ZT_TYPE_I16 ZT_I16;
typedef ZT_TYPE_I32 ZT_I32;
typedef ZT_TYPE_I64 ZT_I64;
typedef ZT_TYPE_U8 ZT_U8;
typedef ZT_TYPE_U16 ZT_U16;
typedef ZT_TYPE_U32 ZT_U32;
typedef ZT_TYPE_U64 ZT_U64;

#if (ZTM_BUILD_WIDTH > 16) // 32-bit and above
	typedef ZT_TYPE_U64 ZT_SIZE;
	typedef ZT_TYPE_I32 ZT_I;
	typedef ZT_TYPE_U32 ZT_U;
	typedef ZT_TYPE_U32 ZT_TIME;
	typedef ZT_TYPE_U32 ZT_COLOR;
	typedef ZT_TYPE_U32 ZT_INDEX;
	typedef ZT_TYPE_U32 ZT_FLAG;
	typedef ZT_TYPE_U16 ZT_INDEX_HALF;
	typedef ZT_TYPE_U16 ZT_FLAG_HALF;
	typedef ZT_TYPE_U8 ZT_INDEX_QUARTER;
	typedef ZT_TYPE_U8 ZT_FLAG_QUARTER;
#elif (ZTM_BUILD_WIDTH > 8) // 16-bit
	typedef ZT_TYPE_U32 ZT_SIZE;
	typedef ZT_TYPE_I16 ZT_I;
	typedef ZT_TYPE_U16 ZT_U;
	typedef ZT_TYPE_U32 ZT_TIME;
	typedef ZT_TYPE_U16 ZT_COLOR;
	typedef ZT_TYPE_U16 ZT_INDEX;
	typedef ZT_TYPE_U16 ZT_FLAG;
	typedef ZT_TYPE_U8 ZT_INDEX_HALF;
	typedef ZT_TYPE_U8 ZT_FLAG_HALF;
	typedef ZT_TYPE_U8 ZT_INDEX_QUARTER;
	typedef ZT_TYPE_U8 ZT_FLAG_QUARTER;
#else // 8-bit
	typedef ZT_TYPE_U32 ZT_SIZE;
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
#endif // ZTM_BUILD_WIDTH

#define ZT_TRUE ((ZT_BOOL)0x1)
#define ZT_FALSE ((ZT_BOOL)0x0)
#define ZT_TOGGLE ((ZT_BLTG)~0x0)

#define __ZTM_BUILD_BASE_DATE() \
	ZT_U16 year;\
	ZT_U8 month;\
	ZT_U8 day;\
	ZT_U8 weekday;\
	ZT_U8 hour;\
	ZT_U8 minute;\
	ZT_U8 second
typedef union { // TODO unify both
	struct {
		ZT_U8 byte[0];
	};
	struct {__ZTM_BUILD_BASE_DATE();};
} ZT_DATE;
#define __ZTM_BUILD_BASE_HASH_8(COUNT) \
	ZT_U8 u8[(COUNT) >> 3]
#define __ZTM_BUILD_BASE_HASH_16(COUNT) \
	__ZTM_BUILD_BASE_HASH_8(COUNT);\
	ZT_U16 u16[(COUNT) >> 4]
#define __ZTM_BUILD_BASE_HASH_32(COUNT) \
	__ZTM_BUILD_BASE_HASH_16(COUNT);\
	ZT_U32 u32[(COUNT) >> 5]
#define __ZTM_BUILD_BASE_HASH_64(COUNT) \
	__ZTM_BUILD_BASE_HASH_32(COUNT);\
	ZT_U64 u64[(COUNT) >> 6]
typedef union {__ZTM_BUILD_BASE_HASH_8(8);} ZT_HASH8;
typedef union {__ZTM_BUILD_BASE_HASH_16(16);} ZT_HASH16;
typedef union {__ZTM_BUILD_BASE_HASH_32(32);} ZT_HASH32;
#if !defined(ZTM_BUILD_EMBED) || !(ZTM_BUILD_EMBED)
	typedef ZT_U8 ZT_CHAR;
	typedef union {
		struct {
			ZT_U8 byte[sizeof(ZT_DATE)];
			ZT_U16 ordinal;
			ZT_U8 week;
			ZT_U8 reserveFree;
			ZT_TIME epoch;
			ZT_TIME zone;
		};
		struct {__ZTM_BUILD_BASE_DATE();};
	} ZT_DATE_FULL;
	typedef union {__ZTM_BUILD_BASE_HASH_64(64);} ZT_HASH64;
	typedef union {__ZTM_BUILD_BASE_HASH_64(128);} ZT_HASH128;
	typedef union {__ZTM_BUILD_BASE_HASH_64(256);} ZT_HASH256;
	typedef union {__ZTM_BUILD_BASE_HASH_64(512);} ZT_HASH512;
	typedef union {__ZTM_BUILD_BASE_HASH_64(1024);} ZT_HASH1024;
	#define __ZTM_BUILD_BASE_DATA() \
		ZT_SIZE length;\
		ZT_SIZE reserveCapacity;\
		union {\
			ZT_U64* u64;\
			ZT_U32* u32;\
			ZT_U16* u16;\
			ZT_U8* u8;\
			void* ptr;\
		}
	typedef union {
		// struct {
			// ZT_U8 byte[0]; // TODO disabled due to 'byte' keyword previously used for 'u8' 
		// };
		struct {__ZTM_BUILD_BASE_DATA();};
	} ZT_DATA;
	typedef union {
		struct {
			ZT_U8 byte[sizeof(ZT_DATA)];
			ZT_U8 data[0];
		};
		struct {__ZTM_BUILD_BASE_DATA();};
	} ZT_SDATA;
	typedef struct {
		ZT_INDEX length;
		ZT_INDEX reserveCapacity;
		ZT_INDEX reserveFree0;
		ZT_INDEX reserveFree1;
		void** items;
	} ZT_LIST;
	typedef struct {
		ZT_INDEX length;
		ZT_INDEX reserveCapacity;
		ZT_INDEX data;
		ZT_INDEX user;
		void** items;
	} ZT_QLIST;
	typedef struct {
		ZT_INDEX length;
		ZT_INDEX capacity;
		ZT_INDEX reserveFree0;
		ZT_INDEX reserveFree1;
		void** list;
		void* item[0];
	} ZT_SLIST; // NOT IMPLEMENT
	typedef struct {
		ZT_INDEX length;
		ZT_INDEX capacity;
		ZT_INDEX data;
		ZT_INDEX user;
		void** qlist;
		void* item[0];
	} ZT_QSLIST; // NOT IMPLEMENT
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
		ZT_POINT block;
		ZT_COLOR* pixels;
	} ZT_SURFACE;
#endif // !ZTM_BUILD_EMBED

#endif // ZTM_SHARED_TYPE_H_INCLUDED
