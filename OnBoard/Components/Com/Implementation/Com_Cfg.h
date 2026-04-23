#ifndef COM_CFG_H_
#define COM_CFG_H_

#include "Com.h"

#define COM_PRECOMPILE_SUPPORT (STD_ON)

typedef enum
{
    LED_BLUE_CMD = (Com_SignalIdType)0,
    LED_BLUE_RSP = (Com_SignalIdType)1,
    ECHO_REVERSE_CMD = (Com_SignalIdType)2,
    ECHO_REVERSE_RSP = (Com_SignalIdType)3,
    PEDAL_NTF = (Com_SignalIdType)4,
    BRAKE_NTF = (Com_SignalIdType)5,
    GEAR_NTF = (Com_SignalIdType)6,
    MODE_NTF = (Com_SignalIdType)7,
    RPM_NOW_NTF = (Com_SignalIdType)8,
    RPM_TARGET_CMD = (Com_SignalIdType)9,
    STEERING_ANGLE_NTF = (Com_SignalIdType)10,
    WHEEL_ANGLE_NTF = (Com_SignalIdType)11,
    SPEED_NTF = (Com_SignalIdType)12,
} SignalId;

#endif
