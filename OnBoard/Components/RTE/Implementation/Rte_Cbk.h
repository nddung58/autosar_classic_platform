#ifndef RTE_CBK_H__
#define RTE_CBK_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
#include "ComStackTypes.h"
#include "Com_Cfg.h"

    typedef enum
    {
        RTE_CBK_SIG_LED_BLUE_IN = (CbkHandleIdType)LED_BLUE_CMD,
        RTE_CBK_SIG_LED_BLUE_OUT = (CbkHandleIdType)LED_BLUE_RSP,
        RTE_CBK_SIG_ECHO_REVERSE_IN = (CbkHandleIdType)ECHO_REVERSE_CMD,
        RTE_CBK_SIG_ECHO_REVERSE_OUT = (CbkHandleIdType)ECHO_REVERSE_RSP,
        RTE_CBK_SIG_PEDAL = (CbkHandleIdType)PEDAL_NTF,
        RTE_CBK_SIG_BRAKE = (CbkHandleIdType)BRAKE_NTF,
        RTE_CBK_SIG_GEAR = (CbkHandleIdType)GEAR_NTF,
        RTE_CBK_SIG_MODE = (CbkHandleIdType)MODE_NTF,
        RTE_CBK_SIG_RPM_NOW = (CbkHandleIdType)RPM_NOW_NTF,
        RTE_CBK_SIG_RPM_TARGET = (CbkHandleIdType)RPM_TARGET_CMD,
        RTE_CBK_SIG_STEERING_ANGLE = (CbkHandleIdType)STEERING_ANGLE_NTF,
        RTE_CBK_SIG_WHEEL_ANGLE = (CbkHandleIdType)WHEEL_ANGLE_NTF,
        RTE_CBK_SIG_SPEED = (CbkHandleIdType)SPEED_NTF,

        RTE_CBK_SIG_MAX
    } Rte_CbkSignalHandleType;

    // Callback / Notification Functions

    //  successful transmission
    void Rte_CbkTxAck(CbkHandleIdType ComUserCbkHandleId);

    // not possible because the corresponding I-PDU is stopped
    void Rte_CbkTxErr(CbkHandleIdType ComUserCbkHandleId);

    // transmission error has been detected by the deadline monitoring mechanism
    void Rte_CbkTxTOut(CbkHandleIdType ComUserCbkHandleId);

    void Rte_CbkRxAck(CbkHandleIdType ComUserCbkHandleId);

    void Rte_CbkRxTOut(CbkHandleIdType ComUserCbkHandleId);

    // Received Invalid Signal
    void Rte_CbkInv(CbkHandleIdType ComUserCbkHandleId);

    // Com request update signal
    void Com_CbkTxPrep(void);

#ifdef __cplusplus
}
#endif

#endif
