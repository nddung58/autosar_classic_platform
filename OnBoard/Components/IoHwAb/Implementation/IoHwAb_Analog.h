#ifndef IOHWAB_ANALOG_H_
#define IOHWAB_ANALOG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
#include "IoHwAb_Types.h"

    /***************************************** Analog inputs ******************************************/
#define IOHWAB_SIGNAL_ANALOGSIGNAL_POTENT_PCT ((IoHwAb_SignalType)8u)
#if defined(ECU_CENTRAL)
#define IOHWAB_SIGNAL_ANALOGSIGNAL_PEDAL_PCT ((IoHwAb_SignalType)9u)
#define IOHWAB_SIGNAL_ANALOGSIGNAL_BRAKE_PCT ((IoHwAb_SignalType)10u)
#endif

    void IoHwAb_Analog_Init(void);

    /* Signal-specific APIs */

    Std_ReturnType IoHwAb_Get_Analog_AnalogSignal_PotentPct(
        uint8 *value,
        IoHwAb_StatusType *status);
#if defined(ECU_CENTRAL)
    Std_ReturnType IoHwAb_Get_Analog_AnalogSignal_PedalPct(
        uint8 *value,
        IoHwAb_StatusType *status);

    Std_ReturnType IoHwAb_Get_Analog_AnalogSignal_BrakePct(
        uint8 *value,
        IoHwAb_StatusType *status);
#endif

    /********************************** Parameterized analog inputs ***********************************/

    Std_ReturnType IoHwAb_Get_Analog(
        IoHwAb_SignalType signal,
        IoHwAb_AnalogValueType *value,
        IoHwAb_StatusType *status);

/************************************ Analog validation macros ************************************/

/* Percent range */
#define IOHWAB_ANALOG_PEDAL_PCT_MIN ((uint8)0u)
#define IOHWAB_ANALOG_PEDAL_PCT_MAX ((uint8)100u)

#define IOHWAB_ANALOG_BRAKE_PCT_MIN ((uint8)0u)
#define IOHWAB_ANALOG_BRAKE_PCT_MAX ((uint8)100u)

#define IOHWAB_IS_VALID_ANALOG_POTENT_PCT(value) \
    (((value) >= IOHWAB_ANALOG_BRAKE_PCT_MIN) && ((value) <= IOHWAB_ANALOG_BRAKE_PCT_MAX))
#if defined(ECU_CENTRAL)
#define IOHWAB_IS_VALID_ANALOG_PEDAL_PCT(value) \
    (((value) >= IOHWAB_ANALOG_PEDAL_PCT_MIN) && ((value) <= IOHWAB_ANALOG_PEDAL_PCT_MAX))

#define IOHWAB_IS_VALID_ANALOG_BRAKE_PCT(value) \
    (((value) >= IOHWAB_ANALOG_BRAKE_PCT_MIN) && ((value) <= IOHWAB_ANALOG_BRAKE_PCT_MAX))
#endif
#define IOHWAB_SIGNAL_IS_VALID_ANALOG_INPUT(signal)        \
    (((signal) == IOHWAB_SIGNAL_ANALOGSIGNAL_PEDAL_PCT) || \
     ((signal) == IOHWAB_SIGNAL_ANALOGSIGNAL_BRAKE_PCT) || \
     ((signal) == IOHWAB_SIGNAL_ANALOGSIGNAL_POTENT_PCT))

#ifdef __cplusplus
}
#endif

#endif /* IOHWAB_ANALOG_H_ */
