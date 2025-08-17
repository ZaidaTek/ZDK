/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_SHARED_H_INCLUDED
#define ZDX_SHARED_H_INCLUDED

#define ZDX_MSG_PREFIX 0xff
#define ZDX_MSG_VERSION_MAJOR 0x1
#define ZDX_MSG_VERSION_MINOR 0x1
#define ZDX_MSG_VERSION ((ZDX_MSG_VERSION_MAJOR << 8) | ZDX_MSG_VERSION_MINOR)
#define ZDX_MSG_CRC_SALT 0xa5
#define ZDX_MSG_LENGTH_HEADER 8

#define ZDX_MSGX_PREFIX 0
#define ZDX_MSGX_JOB 1
#define ZDX_MSGX_VMAJ 2
#define ZDX_MSGX_VMIN 3
#define ZDX_MSGX_LENH 4
#define ZDX_MSGX_LENL 5
#define ZDX_MSGX_CRCPL 6
#define ZDX_MSGX_CRCHD 7

#define ZDX_JOB_END 0x0
#define ZDX_JOB_WAIT 0x1
#define ZDX_JOB_TASK 0x10
#define ZDX_JOB_ERR_TIMEOUT 0x81
#define ZDX_JOB_ERR_CRC 0x82
#define ZDX_JOB_ERR_VERSION 0x83

#define ZDX_TASK_DII 0x10
#define ZDX_TASK_DIO 0x20
#define ZDX_TASK_PWM 0x21
#define ZDX_TASK_ADC 0x40
#define ZDX_TASK_DAC 0x80

#define ZDX_TASK_AT328P (ZDX_TASK_DIO | ZDX_TASK_PWM | ZDX_TASK_ADC)
#define ZDX_TASK_AT328P_DIO_MASK 0xff
#define ZDX_TASK_AT328P_PWM_MASK 0xff
#define ZDX_TASK_AT328P_PWM_MINRATE 100
#define ZDX_TASK_AT328P_PWM_MAXRATE 50000
#define ZDX_TASK_AT328P_ADC_MASK 0xff
#define ZDX_TASK_AT328P_ADC_RESOLUTION 10
#define ZDX_TASK_AT328P_ADC_MINRATE 100
#define ZDX_TASK_AT328P_ADC_MAXRATE 10000000

#endif // ZDX_SHARED_H_INCLUDED
