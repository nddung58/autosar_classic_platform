#ifndef IOHWAB_DIGITAL_H_
#define IOHWAB_DIGITAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
#include "IoHwAb_Types.h"

    /***************************************** API IDs ************************************************/

#define IOHWAB_DIGITAL_SET_ID ((uint8)0x01u)
#define IOHWAB_DIGITAL_GET_ID ((uint8)0x02u)

    /***************************************** Error codes ********************************************/

#define IOHWAB_E_PARAM_SIGNAL ((uint8)0x01u)
#define IOHWAB_E_PARAM_POINTER ((uint8)0x02u)
    /**************************************** Digital outputs *****************************************/

#define IOHWAB_SIGNAL_DIGITALSIGNAL_LEDBLUE ((IoHwAb_SignalType)0u)

    Std_ReturnType IoHwAb_Set_Digital_DigitalSignal_LedBlue(
        IoHwAb_LevelType newValue,
        IoHwAb_StatusType *status);

    Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_LedBlue(
        IoHwAb_LevelType *value,
        IoHwAb_StatusType *status);

#define IOHWAB_SIGNAL_DIGITALSIGNAL_MOTORA_IN1 ((IoHwAb_SignalType)1u)

    Std_ReturnType IoHwAb_Set_Digital_DigitalSignal_MotorA_In1(IoHwAb_LevelType value, IoHwAb_StatusType *status);

#define IOHWAB_SIGNAL_DIGITALSIGNAL_MOTORA_IN2 ((IoHwAb_SignalType)2u)

    Std_ReturnType IoHwAb_Set_Digital_DigitalSignal_MotorA_In2(IoHwAb_LevelType value, IoHwAb_StatusType *status);

#define IOHWAB_SIGNAL_DIGITALSIGNAL_MOTORB_IN1 ((IoHwAb_SignalType)3u)

    Std_ReturnType IoHwAb_Set_Digital_DigitalSignal_MotorB_In1(IoHwAb_LevelType value, IoHwAb_StatusType *status);

#define IOHWAB_SIGNAL_DIGITALSIGNAL_MOTORB_IN2 ((IoHwAb_SignalType)4u)

    Std_ReturnType IoHwAb_Set_Digital_DigitalSignal_MotorB_In2(IoHwAb_LevelType value, IoHwAb_StatusType *status);

    /***************************************** Digital inputs *****************************************/

#define IOHWAB_SIGNAL_DIGITALSIGNAL_GEARP ((IoHwAb_SignalType)1u)
    Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_GearP(
        IoHwAb_LevelType *value,
        IoHwAb_StatusType *status);

#define IOHWAB_SIGNAL_DIGITALSIGNAL_GEARN ((IoHwAb_SignalType)2u)
    Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_GearN(
        IoHwAb_LevelType *value,
        IoHwAb_StatusType *status);

#define IOHWAB_SIGNAL_DIGITALSIGNAL_GEARD ((IoHwAb_SignalType)3u)
    Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_GearD(
        IoHwAb_LevelType *value,
        IoHwAb_StatusType *status);

#define IOHWAB_SIGNAL_DIGITALSIGNAL_GEARR ((IoHwAb_SignalType)4u)
    Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_GearR(
        IoHwAb_LevelType *value,
        IoHwAb_StatusType *status);

#define IOHWAB_SIGNAL_DIGITALSIGNAL_DRIVEMODE ((IoHwAb_SignalType)5u)
    Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_DriveMode(
        IoHwAb_LevelType *value,
        IoHwAb_StatusType *status);

    /************************************* Parameterized digital **************************************/

    Std_ReturnType IoHwAb_Set_Digital(
        IoHwAb_SignalType signal,
        IoHwAb_LevelType newValue,
        IoHwAb_StatusType *status);

    Std_ReturnType IoHwAb_Get_Digital(
        IoHwAb_SignalType signal,
        IoHwAb_LevelType *value,
        IoHwAb_StatusType *status);

/* Validation macros */
#define IOHWAB_SIGNAL_IS_VALID_DIGITAL_OUTPUT(signal)     \
    (((signal) == IOHWAB_SIGNAL_DIGITALSIGNAL_LEDBLUE) || \
     ((signal) == IOHWAB_SIGNAL_DIGITALSIGNAL_LEDBLUE))

#define IOHWAB_SIGNAL_IS_VALID_DIGITAL_INPUT(signal)    \
    (((signal) == IOHWAB_SIGNAL_DIGITALSIGNAL_GEARP) || \
     ((signal) == IOHWAB_SIGNAL_DIGITALSIGNAL_GEARN) || \
     ((signal) == IOHWAB_SIGNAL_DIGITALSIGNAL_GEARD) || \
     ((signal) == IOHWAB_SIGNAL_DIGITALSIGNAL_GEARR) || \
     ((signal) == IOHWAB_SIGNAL_DIGITALSIGNAL_DRIVEMODE))

#ifdef __cplusplus
}
#endif

#endif /* IOHWAB_DIGITAL_H_ */
