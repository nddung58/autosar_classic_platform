#include "IoHwAb.h"
#include "IoHwAb_Analog.h"
#include "IoHwAb_Digital.h"
#include "IoHwAb_Pwm.h"

extern const IoHwAb_ConfigType IoHwAb_Config;

const IoHwAb_ConfigType *IoHwAb_ConfigPtr = NULL_PTR;

void IoHwAb_Init(const IoHwAb_ConfigType *ConfigPtr)
{
#if (STD_ON == IOHWAB_PRECOMPILE_SUPPORT)
    IoHwAb_ConfigPtr = &IoHwAb_Config;
    (void)ConfigPtr;
#else
    IOHWAB_VALIDATE_RETURN_VOID((ConfigPtr != NULL_PTR),
                                IOHWAB_INIT_ID,
                                IOHWAB_E_PARAM_POINTER);
    IoHwAb_ConfigPtr = ConfigPtr;
#endif
    IoHwAb_Analog_Init();

    IoHwAb_Pwm_Init();
}
