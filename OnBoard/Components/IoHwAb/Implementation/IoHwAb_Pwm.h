#ifndef IOHWAB_PWM_H_
#define IOHWAB_PWM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
#include "IoHwAb_Types.h"

/* PWM signal identifiers */
#define IOHWAB_SIGNAL_PWMSIGNAL_LED_RED ((IoHwAb_SignalType)0U)
#define IOHWAB_SIGNAL_PWMSIGNAL_MOTOR1 ((IoHwAb_SignalType)1U)
#define IOHWAB_SIGNAL_PWMSIGNAL_MOTOR2 ((IoHwAb_SignalType)2U)

    /* PWM specific API */
    Std_ReturnType IoHwAb_Set_Duty_PwmSignal_LedRed(
        IoHwAb_DutyType duty,
        IoHwAb_StatusType *status);
#if defined(ECU_CONTROL)
    Std_ReturnType IoHwAb_Set_Duty_PwmSignal_Motor1(
        IoHwAb_DutyType duty,
        IoHwAb_StatusType *status);

    Std_ReturnType IoHwAb_Set_Duty_PwmSignal_Motor2(
        IoHwAb_DutyType duty,
        IoHwAb_StatusType *status);

    /* Generic PWM API */
    Std_ReturnType IoHwAb_Set_Duty(
        IoHwAb_SignalType signal,
        IoHwAb_DutyType duty,
        IoHwAb_StatusType *status);

    Std_ReturnType IoHwAb_Set_FrequencyAndDuty(
        IoHwAb_SignalType signal,
        IoHwAb_FrequencyType frequency,
        IoHwAb_DutyType duty,
        IoHwAb_StatusType *status);
#endif
#define IOHWAB_SIGNAL_IS_VALID_PWM_DUTY_OUTPUT(signal) \
    (((signal) == IOHWAB_SIGNAL_PWMSIGNAL_MOTOR1) ||   \
     ((signal) == IOHWAB_SIGNAL_PWMSIGNAL_MOTOR2) ||   \
     ((signal) == IOHWAB_SIGNAL_PWMSIGNAL_LED_RED))

#define IOHWAB_SIGNAL_IS_VALID_PWM_FREQUENCYANDDUTY_OUTPUT(signal) \
    (((signal) == IOHWAB_SIGNAL_PWMSIGNAL_MOTOR1) ||               \
     ((signal) == IOHWAB_SIGNAL_PWMSIGNAL_MOTOR2) ||               \
     ((signal) == IOHWAB_SIGNAL_PWMSIGNAL_LED_RED))

#ifdef __cplusplus
}
#endif

#endif /* IOHWAB_PWM_H_ */