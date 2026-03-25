/******************************************** Includes ********************************************/

#include "IoHwAb_Analog.h"
#include "IoHwAb.h"
#include "Adc.h"

/***************************************** Private macros *****************************************/
#define IOHWAB_ANALOG_MAX_SIG 10
#if defined(ECU_CENTRAL)
#define IOHWAB_ADC_CHIDX_POTENT_PCT (0U)
#define IOHWAB_ADC_CHIDX_PEDAL_PCT (1U)
#define IOHWAB_ADC_CHIDX_BRAKE_PCT (2U)
#elif defined(ECU_CONTROL)
#define IOHWAB_ADC_CHIDX_POTENT_PCT (0U)
#endif

#define IOHWAB_ADC_CONVERSION_TIMEOUT (1000000UL)

/*************************************** Private variables ****************************************/
#define ADC_START_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Adc_MemMap.h"
__attribute__((aligned(32))) Adc_ValueGroupType IoHwAb_AdcBuffer[IOHWAB_ANALOG_MAX_SIG] = {0U, 0U, 0u};
#define ADC_STOP_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Adc_MemMap.h"

static volatile boolean IoHwAb_AnalogNotification = FALSE;

static boolean IoHwAb_AnalogInitialized = FALSE;

/*************************************** Private functions ****************************************/

static uint8 IoHwAb_Analog_ConvertAdcToPercent(Adc_ValueGroupType adcValue)
{
    uint32 percent;

    if (adcValue >= ADC_MAX_VALUE)
    {
        percent = 100U;
    }
    else
    {
        /* Integer rounding: round((adcValue * 100) / ADC_MAX_VALUE) */
        percent = (((uint32)adcValue * 100U) + ((uint32)ADC_MAX_VALUE / 2U)) / (uint32)ADC_MAX_VALUE;
    }

    if (percent > 100U)
    {
        percent = 100U;
    }

    return (uint8)percent;
}

static Std_ReturnType IoHwAb_Analog_WaitForNotification(IoHwAb_StatusType *status)
{
    uint32 timeout = IOHWAB_ADC_CONVERSION_TIMEOUT;

    while ((IoHwAb_AnalogNotification == FALSE) && (timeout > 0UL))
    {
        timeout--;
    }

    if (timeout == 0UL)
    {
        status->quality = IOHWAB_ERR;
        return E_NOT_OK;
    }

    return E_OK;
}

static Std_ReturnType IoHwAb_Analog_ReadPercent(
    uint8 channelIndex,
    uint8 *value,
    IoHwAb_StatusType *status)
{
    Std_ReturnType ret;

    if ((value == NULL_PTR) || (status == NULL_PTR))
    {
        if (status != NULL_PTR)
        {
            status->quality = IOHWAB_INIVAL;
        }
        return E_NOT_OK;
    }

    if (IoHwAb_AnalogInitialized == FALSE)
    {
        status->quality = IOHWAB_ERR;
        return E_NOT_OK;
    }

    if (channelIndex >= IoHwAb_ConfigPtr->NumAnalogSignal)
    {
        status->quality = IOHWAB_INIVAL;
        return E_NOT_OK;
    }

    status->quality = IOHWAB_ERR;
    IoHwAb_AnalogNotification = FALSE;

    Adc_StartGroupConversion(IoHwAb_ConfigPtr->Adc_Group);

    ret = IoHwAb_Analog_WaitForNotification(status);
    if (ret != (Std_ReturnType)E_OK)
    {
        return E_NOT_OK;
    }

    *value = IoHwAb_Analog_ConvertAdcToPercent(IoHwAb_AdcBuffer[channelIndex]);
    status->quality = IOHWAB_GOOD;

    return E_OK;
}

/***************************************** Analog inputs ******************************************/

void IoHwAb_Analog_Init(void)
{
    Std_ReturnType ret;

    IoHwAb_AnalogNotification = FALSE;

    ret = Adc_SetupResultBuffer(IoHwAb_ConfigPtr->Adc_Group, IoHwAb_AdcBuffer);
    if (ret == (Std_ReturnType)E_OK)
    {
        Adc_EnableGroupNotification(IoHwAb_ConfigPtr->Adc_Group);
        IoHwAb_AnalogInitialized = TRUE;
    }
    else
    {
        IoHwAb_AnalogInitialized = FALSE;
    }
}

Std_ReturnType IoHwAb_Get_Analog_AnalogSignal_PotentPct(
    uint8 *value,
    IoHwAb_StatusType *status)
{
    Std_ReturnType ret;

    ret = IoHwAb_Analog_ReadPercent(IOHWAB_ADC_CHIDX_POTENT_PCT, value, status);
    if (ret != (Std_ReturnType)E_OK)
    {
        return E_NOT_OK;
    }

    if (IOHWAB_IS_VALID_ANALOG_POTENT_PCT(*value) == FALSE)
    {
        status->quality = IOHWAB_ERR;
        return E_NOT_OK;
    }

    return E_OK;
}
#if defined(ECU_CENTRAL)
Std_ReturnType IoHwAb_Get_Analog_AnalogSignal_PedalPct(
    uint8 *value,
    IoHwAb_StatusType *status)
{
    Std_ReturnType ret;

    ret = IoHwAb_Analog_ReadPercent(IOHWAB_ADC_CHIDX_PEDAL_PCT, value, status);
    if (ret != (Std_ReturnType)E_OK)
    {
        return E_NOT_OK;
    }

    if (IOHWAB_IS_VALID_ANALOG_PEDAL_PCT(*value) == FALSE)
    {
        status->quality = IOHWAB_ERR;
        return E_NOT_OK;
    }

    return E_OK;
}

Std_ReturnType IoHwAb_Get_Analog_AnalogSignal_BrakePct(
    uint8 *value,
    IoHwAb_StatusType *status)
{
    Std_ReturnType ret;

    ret = IoHwAb_Analog_ReadPercent(IOHWAB_ADC_CHIDX_BRAKE_PCT, value, status);
    if (ret != (Std_ReturnType)E_OK)
    {
        return E_NOT_OK;
    }

    if (IOHWAB_IS_VALID_ANALOG_BRAKE_PCT(*value) == FALSE)
    {
        status->quality = IOHWAB_ERR;
        return E_NOT_OK;
    }

    return E_OK;
}
#endif
/********************************** Parameterized analog inputs ***********************************/

Std_ReturnType IoHwAb_Get_Analog(
    IoHwAb_SignalType signal,
    IoHwAb_AnalogValueType *value,
    IoHwAb_StatusType *status)
{
    Std_ReturnType ret;
    uint8 analogPercent = 0U;

    if ((value == NULL_PTR) || (status == NULL_PTR))
    {
        if (status != NULL_PTR)
        {
            status->quality = IOHWAB_INIVAL;
        }
        return E_NOT_OK;
    }

    switch (signal)
    {
    case IOHWAB_SIGNAL_ANALOGSIGNAL_POTENT_PCT:
        ret = IoHwAb_Get_Analog_AnalogSignal_PotentPct(&analogPercent, status);
        if (ret == (Std_ReturnType)E_OK)
        {
            *value = (IoHwAb_AnalogValueType)analogPercent;
        }
        return ret;
#if defined(ECU_CENTRAL)
    case IOHWAB_SIGNAL_ANALOGSIGNAL_PEDAL_PCT:
        ret = IoHwAb_Get_Analog_AnalogSignal_PedalPct(&analogPercent, status);
        if (ret == (Std_ReturnType)E_OK)
        {
            *value = (IoHwAb_AnalogValueType)analogPercent;
        }
        return ret;

    case IOHWAB_SIGNAL_ANALOGSIGNAL_BRAKE_PCT:
        ret = IoHwAb_Get_Analog_AnalogSignal_BrakePct(&analogPercent, status);
        if (ret == (Std_ReturnType)E_OK)
        {
            *value = (IoHwAb_AnalogValueType)analogPercent;
        }
        return ret;
#endif
    default:
        status->quality = IOHWAB_INIVAL;
        return E_NOT_OK;
    }
}

/************************************** Adc group callbacks ***************************************/

void IoHwAb_AdcNotification_0(void)
{
    IoHwAb_AnalogNotification = TRUE;
}
