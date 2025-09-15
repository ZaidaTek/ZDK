/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_RT_PRINTER_H_INCLUDED
#define ZTK_RT_PRINTER_H_INCLUDED

#define ZTK_PRINTER_BUFFER 8192
#define ZTK_PRINTER_FLAG_NONE ZTK_FLAG_NONE
#define ZTK_PRINTER_FLAG_OVERFLOW 0x1
#define ZTK_PRINTER_FLAG_SIZE 0x10
#define ZTK_DEFAULT_PRINTER_FLAG (ZTK_PRINTER_FLAG_OVERFLOW)

typedef struct {
    rZT_FONT* font;
    rZT_FONT* dummy; // alignment
    ZT_POINT cursor;
    ZT_RECT bounds;
} rZTK_PRINTER;
typedef struct {
    ZT_FLAG flag;
    ZT_FLAG type;
    rZTK_PRINTER user;
    struct {
        ZT_RECT rect;
        ZT_CHAR buffer[ZTK_PRINTER_BUFFER];
    } print;
} rZTK_PRINTER_HOST;

extern rZTK_PRINTER_HOST rZTK_PrinterHost;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_PrinterPipe(rZTK_PRINTER* iUser);
void ZTK_PrinterPipeLoop(rZTK_PRINTER* iUser, ZT_CHAR* iText);
void ZTK_PrinterPipeLine(rZTK_PRINTER* iUser, ZT_CHAR* iText, ZT_INDEX iLength);
void ZTK_PrinterPipeFeed(rZTK_PRINTER* iUser);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTK_RT_PRINTER_H_INCLUDED
