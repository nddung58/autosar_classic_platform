#ifndef IOHWAB_H_
#define IOHWAB_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
#include "Det.h"
#include "IoHwAb_Cfg.h"
#include "IoHwAb_Analog.h"
#include "IoHwAb_Digital.h"
#include "IoHwAb_Pwm.h"
#include "Adc.h"
#include "Dio.h"
#include "Pwm.h"

#if (IOHWAB_DEV_ERROR_DETECT == STD_ON)

#define IOHWAB_DET_REPORT_ERROR(api, error)                          \
    do                                                               \
    {                                                                \
        (void)Det_ReportError(IOHWAB_MODULE_ID, 0u, (api), (error)); \
    } while (0)

#define IOHWAB_VALIDATE(expression, api, error)      \
    do                                               \
    {                                                \
        if (!(expression))                           \
        {                                            \
            IOHWAB_DET_REPORT_ERROR((api), (error)); \
        }                                            \
    } while (0)

#define IOHWAB_VALIDATE_RETURN(expression, api, error, rv) \
    do                                                     \
    {                                                      \
        if (!(expression))                                 \
        {                                                  \
            IOHWAB_DET_REPORT_ERROR((api), (error));       \
            return (rv);                                   \
        }                                                  \
    } while (0)

#define IOHWAB_VALIDATE_RETURN_VOID(expression, api, error) \
    do                                                      \
    {                                                       \
        if (!(expression))                                  \
        {                                                   \
            IOHWAB_DET_REPORT_ERROR((api), (error));        \
            return;                                         \
        }                                                   \
    } while (0)

#else

#define IOHWAB_PWMDUTY_SET_ID 0
#define IOHWAB_PWMFREQUENCYANDDUTY_SET_ID 1

#define IOHWAB_DET_REPORT_ERROR(api, error)
#define IOHWAB_VALIDATE(expression, api, error)
#define IOHWAB_VALIDATE_RETURN(expression, api, error, rv)
#define IOHWAB_VALIDATE_RETURN_VOID(expression, api, error)

#endif /* IOHWAB_DEV_ERROR_DETECT */

    typedef enum
    {
        IOHWAB_UNLOCKED = 0u,
        IOHWAB_LOCKED = 1u
    } IoHwAb_LockType;

#define IoHwAb_LockSave(_x) Irq_Save(_x)
#define IoHwAb_LockRestore(_x) Irq_Restore(_x)

    typedef struct
    {
        const uint8 NumDigitalSignal;
        const uint8 NumAnalogSignal;
        const uint8 NumPwmSignal;
        const Adc_GroupType Adc_Group;
        const Dio_ChannelType *Dio_Channel;
        const Pwm_ChannelType *Pwm_Channel;
    } IoHwAb_ConfigType;

    extern const IoHwAb_ConfigType *IoHwAb_ConfigPtr;

    void IoHwAb_Init(const IoHwAb_ConfigType *ConfigPtr);
    void IoHwAb_MainFunction(void);

#ifdef __cplusplus
}
#endif

#endif /* IOHWAB_H_ */
