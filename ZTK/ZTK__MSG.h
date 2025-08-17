/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__MSG_H_INCLUDED
#define ZTK__MSG_H_INCLUDED

#include "ZTK__Runtime.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_MSG_MouseMove(ZT_I iX, ZT_I iY);
void ZTK_MSG_MouseButton(ZT_FLAG iButton, ZT_FLAG iState);
void ZTK_MSG_MouseState(ZT_FLAG iState);
void ZTK_MSG_MouseWheel(ZT_I iIncrement);
void ZTK_MSG_Key(ZT_BOOL iDown, ZT_INDEX iKey);
void ZTK_MSG_Move(ZT_I iX, ZT_I iY);
void ZTK_MSG_Size(ZT_I iWidth, ZT_I iHeight);
void ZTK_MSG_NCCreate(void);
void ZTK_MSG_Create(void);
void ZTK_MSG_Close(void);
void ZTK_MSG_NCDestroy(void);
void ZTK_MSG_Show(ZT_BOOL iEnabled);
void ZTK_MSG_Activate(ZT_BOOL iEnabled);
void ZTK_MSG_User(void);
void ZTK_MSG_KeyFocus(ZT_BOOL iEnabled);
void ZTK_MSG_Minimize(ZT_BOOL iEnabled);
void ZTK_MSG_Char(ZT_CHAR iChar);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTK__MSG_H_INCLUDED

