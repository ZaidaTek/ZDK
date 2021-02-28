/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_ID_H_INCLUDED
#define ZTK_ID_H_INCLUDED

#define ZTK_AID_MASK 0xffff0000
#define ZTK_AID_SHIFT 16
#define ZTK_EID_MASK 0x0000ffff
#define ZTK_EID_SHIFT 0
#define ZTK_HID_MASK 0xffff0000
#define ZTK_HID_SHIFT 16
#define ZTK_SID_MASK 0x0000ffff
#define ZTK_SID_SHIFT 0

#define ZTK_AID_NONE 0x0
#define ZTK_AID_MOVE_LEFT 0x1
#define ZTK_AID_MOVE_RIGHT 0x2
#define ZTK_AID_MOVE_UP 0x4
#define ZTK_AID_MOVE_DOWN 0x8
#define ZTK_AID_MOVE (ZTK_AID_MOVE_LEFT | ZTK_AID_MOVE_RIGHT | ZTK_AID_MOVE_UP | ZTK_AID_MOVE_DOWN)
#define ZTK_AID_STRIKE 0x10
#define ZTK_AID_DOUBLE 0x20
#define ZTK_AID_RELEASE 0x40
#define ZTK_AID_PRESS 0x80
#define ZTK_AID_CLICK (ZTK_AID_STRIKE | ZTK_AID_DOUBLE | ZTK_AID_RELEASE | ZTK_AID_PRESS)
#define ZTK_AID_REPEAT 0x100

#define ZTK_EID_NONE 0x0
#define ZTK_EID_WINDOW_ACTIVATE 0x101
#define ZTK_EID_WINDOW_DEACTIVATE 0x102
#define ZTK_EID_WINDOW_MINIMIZE 0x103
#define ZTK_EID_WINDOW_RESTORE 0x105
#define ZTK_EID_WINDOW_REPOSITION 0x106
#define ZTK_EID_WINDOW_RESIZE 0x107
#define ZTK_EID_WINDOW_CREATE 0x108
#define ZTK_EID_WINDOW_CLOSE 0x109
#define ZTK_EID_WINDOW_DESTROY 0x109
#define ZTK_EID_WINDOW_SHOW 0x110
#define ZTK_EID_WINDOW_HIDE 0x111
#define ZTK_EID_WINDOW_INITIALIZE 0x112
#define ZTK_EID_WINDOW_REGISTER 0x113
#define ZTK_EID_WINDOW_RUN 0x114
//#define ZTK_EID_TIMER_HEARTBEAT 0x201
//#define ZTK_EID_TIMER_WAKE 0x202
#define ZTK_EID_MOUSE_MOVE 0x401
#define ZTK_EID_MOUSE_BUTTON_L_DOWN 0x410
#define ZTK_EID_MOUSE_BUTTON_R_DOWN 0x411
#define ZTK_EID_MOUSE_BUTTON_M_DOWN 0x412
#define ZTK_EID_MOUSE_BUTTON_X1_DOWN 0x413
#define ZTK_EID_MOUSE_BUTTON_X2_DOWN 0x414
#define ZTK_EID_MOUSE_BUTTON_L_UP 0x420
#define ZTK_EID_MOUSE_BUTTON_R_UP 0x421
#define ZTK_EID_MOUSE_BUTTON_M_UP 0x422
#define ZTK_EID_MOUSE_BUTTON_X1_UP 0x423
#define ZTK_EID_MOUSE_BUTTON_X2_UP 0x424
#define ZTK_EID_MOUSE_WHEEL_DOWN 0x430
#define ZTK_EID_MOUSE_WHEEL_UP 0x440
#define ZTK_EID_KEYBOARD_FOCUS_GAIN 0x801
#define ZTK_EID_KEYBOARD_FOCUS_LOSE 0x802
#define ZTK_EID_KEYBOARD_KEY_DOWN 0x810
#define ZTK_EID_KEYBOARD_KEY_UP 0x820

#define ZTK_EID_GUI_HOVER_ON 0x1
#define ZTK_EID_GUI_HOVER_OFF 0x2
#define ZTK_EID_GUI_STRIKE 0x11
#define ZTK_EID_GUI_DOUBLE 0x12
#define ZTK_EID_GUI_RELEASE 0x13
#define ZTK_EID_GUI_PRESS 0x14

#define ZTK_HID_NONE 0x0
//#define ZTK_HID_WINDOW 0x1
//#define ZTK_HID_TIMER 0x2
#define ZTK_HID_WINDOW 0x2
#define ZTK_HID_MOUSE 0x4
#define ZTK_HID_KEY 0x8
#define ZTK_HID_JOYSTICK 0x10
#define ZTK_HID_CONTROLLER 0x20
#define ZTK_HID_SMARTPHONE 0x40
#define ZTK_HID_OTHER 0x80
#define ZTK_HID_GUI 0x100
//#define ZTK_HID_ALL (ZTK_HID_WINDOW | ZTK_HID_TIMER | ZTK_HID_MOUSE | ZTK_HID_KEY | ZTK_HID_JOYSTICK | ZTK_HID_CONTROLLER | ZTK_HID_SMARTPHONE | ZTK_HID_OTHER | ZTK_HID_GUI)
#define ZTK_HID_FIRST ZTK_HID_WINDOW
#define ZTK_HID_ALL (ZTK_HID_WINDOW | ZTK_HID_MOUSE | ZTK_HID_KEY | ZTK_HID_JOYSTICK | ZTK_HID_CONTROLLER | ZTK_HID_SMARTPHONE | ZTK_HID_OTHER | ZTK_HID_GUI)

#define ZTK_SID_NONE 0x0

#define ZTK_SID_WINDOW_INITIALIZATION 0x1
#define ZTK_SID_WINDOW_REGISTRATION 0x2
#define ZTK_SID_WINDOW_CREATION 0x4
#define ZTK_SID_WINDOW_VISIBILITY 0x8
#define ZTK_SID_WINDOW_ACTIVATION 0x10
#define ZTK_SID_WINDOW_EXECUTION 0x20
#define ZTK_SID_WINDOW_MINIMIZATION 0x40
#define ZTK_SID_WINDOW_HALT 0x80
#define ZTK_SID_WINDOW_DESTRUCTION 0x100
#define ZTK_SID_WINDOW_POSITION 0x1000
#define ZTK_SID_WINDOW_SIZE 0x2000

//#define ZTK_SID_TIMER_HEARTBEAT 0x10
//#define ZTK_SID_TIMER_WAKE 0x20

#define ZTK_SID_MOUSE_LBUTTON 0x1
#define ZTK_SID_MOUSE_RBUTTON 0x2
#define ZTK_SID_MOUSE_MBUTTON 0x4
#define ZTK_SID_MOUSE_X1BUTTON 0x8
#define ZTK_SID_MOUSE_X2BUTTON 0x10
#define ZTK_SID_MOUSE_X3BUTTON 0x20
#define ZTK_SID_MOUSE_X4BUTTON 0x40
#define ZTK_SID_MOUSE_X5BUTTON 0x80
#define ZTK_SID_MOUSE_WHEEL 0x100
#define ZTK_SID_MOUSE_POSITION 0x1000

#define ZTK_SID_KEY_FOCUS 0x1000
#define ZTK_SID_KEY_CHAR 0x100
#define ZTK_SID_KEY_BACK 0x8
#define ZTK_SID_KEY_TAB 0x9
#define ZTK_SID_KEY_LFEED 0xA
#define ZTK_SID_KEY_RETURN 0xD
#define ZTK_SID_KEY_SHIFT 0x10
#define ZTK_SID_KEY_CTRL 0x11
#define ZTK_SID_KEY_ALT 0x12
#define ZTK_SID_KEY_PAUSE 0x13
#define ZTK_SID_KEY_CAPS 0x14
#define ZTK_SID_KEY_ESC 0x1B
#define ZTK_SID_KEY_SPACE 0x20
#define ZTK_SID_KEY_0 0x30
#define ZTK_SID_KEY_1 0x31
#define ZTK_SID_KEY_2 0x32
#define ZTK_SID_KEY_3 0x33
#define ZTK_SID_KEY_4 0x34
#define ZTK_SID_KEY_5 0x35
#define ZTK_SID_KEY_6 0x36
#define ZTK_SID_KEY_7 0x37
#define ZTK_SID_KEY_8 0x38
#define ZTK_SID_KEY_9 0x39
#define ZTK_SID_KEY_A 0x41
#define ZTK_SID_KEY_B 0x42
#define ZTK_SID_KEY_C 0x43
#define ZTK_SID_KEY_D 0x44
#define ZTK_SID_KEY_E 0x45
#define ZTK_SID_KEY_F 0x46
#define ZTK_SID_KEY_G 0x47
#define ZTK_SID_KEY_H 0x48
#define ZTK_SID_KEY_I 0x49
#define ZTK_SID_KEY_J 0x4A
#define ZTK_SID_KEY_K 0x4B
#define ZTK_SID_KEY_L 0x4C
#define ZTK_SID_KEY_M 0x4D
#define ZTK_SID_KEY_N 0x4E
#define ZTK_SID_KEY_O 0x4F
#define ZTK_SID_KEY_P 0x50
#define ZTK_SID_KEY_Q 0x51
#define ZTK_SID_KEY_R 0x52
#define ZTK_SID_KEY_S 0x53
#define ZTK_SID_KEY_T 0x54
#define ZTK_SID_KEY_U 0x55
#define ZTK_SID_KEY_V 0x56
#define ZTK_SID_KEY_W 0x57
#define ZTK_SID_KEY_X 0x58
#define ZTK_SID_KEY_Y 0x59
#define ZTK_SID_KEY_Z 0x5A
#define ZTK_SID_KEY_PGUP 0x21
#define ZTK_SID_KEY_PGDN 0x22
#define ZTK_SID_KEY_END 0x23
#define ZTK_SID_KEY_HOME 0x24
#define ZTK_SID_KEY_LEFT 0x25
#define ZTK_SID_KEY_UP 0x26
#define ZTK_SID_KEY_RIGHT 0x27
#define ZTK_SID_KEY_DOWN 0x28
#define ZTK_SID_KEY_F1 0x70
#define ZTK_SID_KEY_F2 0x71
#define ZTK_SID_KEY_F3 0x72
#define ZTK_SID_KEY_F4 0x73
#define ZTK_SID_KEY_F5 0x74
#define ZTK_SID_KEY_F6 0x75
#define ZTK_SID_KEY_F7 0x76
#define ZTK_SID_KEY_F8 0x77
#define ZTK_SID_KEY_F9 0x78
#define ZTK_SID_KEY_F10 0x79
#define ZTK_SID_KEY_F11 0x7A
#define ZTK_SID_KEY_F12 0x7B
#define ZTK_SID_KEY_CONTROL ZTK_SID_KEY_CTRL
#define ZTK_SID_KEY_CAPITAL ZTK_SID_KEY_CAPS
#define ZTK_SID_KEY_ESCAPE ZTK_SID_KEY_ESC

#define ZTK_HSID_WINDOW (ZTK_HID_WINDOW << ZTK_HID_SHIFT)
//#define ZTK_HSID_TIMER (ZTK_HID_TIMER << ZTK_HID_SHIFT)
#define ZTK_HSID_MOUSE (ZTK_HID_MOUSE << ZTK_HID_SHIFT)
#define ZTK_HSID_KEY (ZTK_HID_KEY << ZTK_HID_SHIFT)
#define ZTK_HSID_GAMEPAD (ZTK_HID_CONTROLLER << ZTK_HID_SHIFT)
#define ZTK_HSID_JOYSTICK (ZTK_HID_JOYSTICK << ZTK_HID_SHIFT)
#define ZTK_HSID_SMARTPHONE (ZTK_HID_SMARTPHONE << ZTK_HID_SHIFT)

#define ZTK_HSID_WINDOW_INITIALIZATION (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_INITIALIZATION << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_REGISTRATION (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_REGISTRATION << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_CREATION (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_CREATION << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_VISIBILITY (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_VISIBILITY << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_ACTIVATION (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_ACTIVATION << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_EXECUTION (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_EXECUTION << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_HALT (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_HALT << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_DESTRUCTION (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_DESTRUCTION << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_POSITION (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_POSITION << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_SIZE (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_SIZE << ZTK_SID_SHIFT))
#define ZTK_HSID_WINDOW_MINIMIZATION (ZTK_HSID_WINDOW | (ZTK_SID_WINDOW_MINIMIZATION << ZTK_SID_SHIFT))

//#define ZTK_HSID_TIMER_HEARTBEAT (ZTK_HSID_TIMER | (ZTK_SID_TIMER_HEARTBEAT << ZTK_SID_SHIFT))
//#define ZTK_HSID_TIMER_WAKE (ZTK_HSID_TIMER | (ZTK_SID_TIMER_WAKE << ZTK_SID_SHIFT))

#define ZTK_HSID_MOUSE_LBUTTON (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_LBUTTON << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_RBUTTON (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_RBUTTON << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_MBUTTON (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_MBUTTON << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_X1BUTTON (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_X1BUTTON << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_X2BUTTON (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_X2BUTTON << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_X3BUTTON (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_X3BUTTON << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_X4BUTTON (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_X4BUTTON << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_X5BUTTON (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_X5BUTTON << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_WHEEL (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_WHEEL << ZTK_SID_SHIFT))
#define ZTK_HSID_MOUSE_POSITION (ZTK_HSID_MOUSE | (ZTK_SID_MOUSE_POSITION << ZTK_SID_SHIFT))

#define ZTK_HSID_KEYBOARD_FOCUS (ZTK_HSID_KEY | (ZTK_SID_KEY_FOCUS << ZTK_SID_SHIFT))

#endif // ZTK_ID_H_INCLUDED