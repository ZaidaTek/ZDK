/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL_DEFINE_H_INCLUDED
#define ZTL_DEFINE_H_INCLUDED

#define ZTL_EXECUTE_SHOW 0x0
#define ZTL_EXECUTE_OPEN 0x1
#define ZTL_EXECUTE_ADMIN 0x2
#define ZTL_EXECUTE_EDIT 0x10
#define ZTL_EXECUTE_PRINT 0x100
#define ZTL_EXECUTE_HIDE 0x80000000

#define ZTL_SELECT_CANCEL 0x0
#define ZTL_SELECT_READY 0x1
#define ZTL_SELECT_WAIT 0x2

#define ZTL_FILE_NONE 0x0
#define ZTL_FILE_VALID 0x1
#define ZTL_FILE_READONLY 0x2
#define ZTL_FILE_HIDDEN 0x4
#define ZTL_FILE_SYSTEM 0x8
#define ZTL_FILE_DIRECTORY 0x10
#define ZTL_FILE_ARCHIVE 0x20
#define ZTL_FILE_COMPRESSED 0x40
#define ZTL_FILE_ENCRYPTED 0x80

#define ZTL_FILE_TYPE_REG   0x00000001
#define ZTL_FILE_TYPE_DIR   0x00000002
#define ZTL_FILE_TYPE_SYM   0x00000100
#define ZTL_FILE_TYPE_BLK   0x00010000
#define ZTL_FILE_TYPE_CHAR  0x00020000
#define ZTL_FILE_TYPE_FIFO  0x01000000
#define ZTL_FILE_TYPE_SKT   0x02000000

#define ZTL_THREAD_FINISH 0x0
#define ZTL_THREAD_RUNNING 0x1

#endif // ZTL_DEFINE_H_INCLUDED
