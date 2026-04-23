#include "IoHwAb.h"
#include "IoHwAb_Pwm.h"
#include "Pwm.h"

#define DUTTY_CYCLE_MAX 0x8000U

#define IOHWAB_PWM_LED_RED 0U
#define IOHWAB_PWM_MOTOR_1 1U
#define IOHWAB_PWM_MOTOR_2 2U

static uint16 IoHwAb_Pwm_ConvertDuty(IoHwAb_DutyType duty)
{
    return (uint16)((((uint32)duty * (uint32)DUTTY_CYCLE_MAX) + ((uint32)IOHWAB_DUTY_MAX / 2U)) / (uint32)IOHWAB_DUTY_MAX);
}

Std_ReturnType IoHwAb_Set_Duty_PwmSignal_LedRed(
    IoHwAb_DutyType duty,
    IoHwAb_StatusType *status)
{
    uint16 pwmDuty;

    if (status == NULL_PTR)
    {
        return E_NOT_OK;
    }

    if (duty > IOHWAB_DUTY_MAX)
    {
        status->quality = IOHWAB_INIVAL;
        return E_NOT_OK;
    }

    pwmDuty = IoHwAb_Pwm_ConvertDuty(duty);

    Pwm_SetDutyCycle(
        IoHwAb_ConfigPtr->Pwm_Channel[IOHWAB_PWM_LED_RED],
        pwmDuty);

    status->quality = IOHWAB_GOOD;
    return E_OK;
}

void IoHwAb_Pwm_Init(void)
{
    Pwm_SetPeriodAndDuty(IoHwAb_ConfigPtr->Pwm_Channel[IOHWAB_PWM_LED_RED], DUTTY_CYCLE_MAX, 0x0000U);
#if defined(ECU_CONTROL)
    Pwm_SetPeriodAndDuty(IoHwAb_ConfigPtr->Pwm_Channel[IOHWAB_PWM_MOTOR_1], DUTTY_CYCLE_MAX, 0x0000U);
    Pwm_SetPeriodAndDuty(IoHwAb_ConfigPtr->Pwm_Channel[IOHWAB_PWM_MOTOR_2], DUTTY_CYCLE_MAX, 0x0000U);
#endif
}

#if defined(ECU_CONTROL)
Std_ReturnType IoHwAb_Set_Duty_PwmSignal_Motor1(
    IoHwAb_DutyType duty,
    IoHwAb_StatusType *status)
{
    uint16 pwmDuty;

    if (status == NULL_PTR)
    {
        return E_NOT_OK;
    }

    if (duty > IOHWAB_DUTY_MAX)
    {
        status->quality = IOHWAB_INIVAL;
        return E_NOT_OK;
    }

    pwmDuty = IoHwAb_Pwm_ConvertDuty(duty);

    Pwm_SetDutyCycle(
        IoHwAb_ConfigPtr->Pwm_Channel[IOHWAB_PWM_MOTOR_1],
        pwmDuty);

    status->quality = IOHWAB_GOOD;
    return E_OK;
}

Std_ReturnType IoHwAb_Set_Duty_PwmSignal_Motor2(
    IoHwAb_DutyType duty,
    IoHwAb_StatusType *status)
{
    uint16 pwmDuty;

    if (status == NULL_PTR)
    {
        return E_NOT_OK;
    }

    if (duty > IOHWAB_DUTY_MAX)
    {
        status->quality = IOHWAB_INIVAL;
        return E_NOT_OK;
    }

    pwmDuty = IoHwAb_Pwm_ConvertDuty(duty);

    Pwm_SetDutyCycle(
        IoHwAb_ConfigPtr->Pwm_Channel[IOHWAB_PWM_MOTOR_2],
        pwmDuty);

    status->quality = IOHWAB_GOOD;
    return E_OK;
}
#endif

Std_ReturnType IoHwAb_Set_Duty(
    IoHwAb_SignalType signal,
    IoHwAb_DutyType duty,
    IoHwAb_StatusType *status)
{
    IOHWAB_VALIDATE_RETURN(
        IOHWAB_SIGNAL_IS_VALID_PWM_DUTY_OUTPUT(signal),
        IOHWAB_PWMDUTY_SET_ID,
        IOHWAB_E_PARAM_SIGNAL,
        E_NOT_OK);

    IOHWAB_VALIDATE_RETURN(
        (status != NULL_PTR),
        IOHWAB_PWMDUTY_SET_ID,
        IOHWAB_E_PARAM_POINTER,
        E_NOT_OK);

    switch (signal)
    {
    case IOHWAB_SIGNAL_PWMSIGNAL_LED_RED:
    {
        return IoHwAb_Set_Duty_PwmSignal_LedRed(duty, status);
    }
#if defined(ECU_CONTROL)
    case IOHWAB_SIGNAL_PWMSIGNAL_MOTOR1:
    {
        return IoHwAb_Set_Duty_PwmSignal_Motor1(duty, status);
    }

    case IOHWAB_SIGNAL_PWMSIGNAL_MOTOR2:
    {
        return IoHwAb_Set_Duty_PwmSignal_Motor2(duty, status);
    }
#endif
    default:
    {
        status->quality = IOHWAB_INIVAL;
        return E_NOT_OK;
    }
    }
}

Std_ReturnType IoHwAb_Set_FrequencyAndDuty(
    IoHwAb_SignalType signal,
    IoHwAb_FrequencyType frequency,
    IoHwAb_DutyType duty,
    IoHwAb_StatusType *status)
{
    uint16 pwmDuty;

    IOHWAB_VALIDATE_RETURN(
        IOHWAB_SIGNAL_IS_VALID_PWM_FREQUENCYANDDUTY_OUTPUT(signal),
        IOHWAB_PWMFREQUENCYANDDUTY_SET_ID,
        IOHWAB_E_PARAM_SIGNAL,
        E_NOT_OK);

    IOHWAB_VALIDATE_RETURN(
        (status != NULL_PTR),
        IOHWAB_PWMFREQUENCYANDDUTY_SET_ID,
        IOHWAB_E_PARAM_POINTER,
        E_NOT_OK);

    if (duty > IOHWAB_DUTY_MAX)
    {
        status->quality = IOHWAB_INIVAL;
        return E_NOT_OK;
    }

    pwmDuty = IoHwAb_Pwm_ConvertDuty(duty);

    switch (signal)
    {
    case IOHWAB_SIGNAL_PWMSIGNAL_MOTOR1:
    {
        Pwm_SetPeriodAndDuty(
            IoHwAb_ConfigPtr->Pwm_Channel[IOHWAB_PWM_MOTOR_1],
            frequency,
            pwmDuty);
        status->quality = IOHWAB_GOOD;
        return E_OK;
    }

    case IOHWAB_SIGNAL_PWMSIGNAL_MOTOR2:
    {
        Pwm_SetPeriodAndDuty(
            IoHwAb_ConfigPtr->Pwm_Channel[IOHWAB_PWM_MOTOR_2],
            frequency,
            pwmDuty);
        status->quality = IOHWAB_GOOD;
        return E_OK;
    }

    default:
    {
        status->quality = IOHWAB_INIVAL;
        return E_NOT_OK;
    }
    }
}
