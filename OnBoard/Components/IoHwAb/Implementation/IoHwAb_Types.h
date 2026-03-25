#ifndef IOHWAB_TYPES_H_
#define IOHWAB_TYPES_H_

#include "Std_Types.h"

/* Digital level type */
typedef uint8 IoHwAb_LevelType;

#define IOHWAB_LOW ((IoHwAb_LevelType)STD_LOW)
#define IOHWAB_HIGH ((IoHwAb_LevelType)STD_HIGH)

/* Generic signal identifier type */
typedef uint16 IoHwAb_SignalType;
#define IOHWAB_SIGNAL_MIN ((IoHwAb_SignalType)0u)
#define IOHWAB_SIGNAL_MAX ((IoHwAb_SignalType)65535u)

/* Analog value base type */
typedef sint32 IoHwAb_AnalogValueType;

/* Frequency type (Hz) */
typedef uint32 IoHwAb_FrequencyType;

/* Duty cycle type (per mille: 0..1000 = 0..100%) */
typedef uint16 IoHwAb_DutyType;
#define IOHWAB_DUTY_MIN ((IoHwAb_DutyType)0u)
#define IOHWAB_DUTY_MAX ((IoHwAb_DutyType)1000u)

/* ADC 12-bit raw result */
#define ADC_MAX_VALUE (4095u)

/* ISO14229 IoControl parameter values */
#define IOHWAB_RETURNCONTROLTOECU (0u)
#define IOHWAB_RESETTODEFAULT (1u)
#define IOHWAB_FREEZECURRENTSTATE (2u)
#define IOHWAB_SHORTTERMADJUST (3u)

/* Signal quality */
typedef enum
{
    IOHWAB_INIVAL = 0u, /* Value not available */
    IOHWAB_ERR,         /* Electrical diagnostic set */
    IOHWAB_BAD,
    IOHWAB_GOOD
} IoHwAb_QualityType;

/* Signal status */
typedef struct
{
    IoHwAb_QualityType quality;
} IoHwAb_StatusType;

#endif /* IOHWAB_TYPES_H_ */