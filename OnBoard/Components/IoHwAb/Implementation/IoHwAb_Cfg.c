#include "IoHwAb.h"

#if defined(ECU_CENTRAL)
const Dio_ChannelType IoHwAb_Dio_Channel[6] =
    {
        DioConf_DioChannel_LedBlue,
        DioConf_DioChannel_GearP,
        DioConf_DioChannel_GearN,
        DioConf_DioChannel_GearD,
        DioConf_DioChannel_GearR,
        DioConf_DioChannel_DriveMode};

const Pwm_ChannelType IoHwAb_Pwm_Channel[1] =
    {
        PwmChannel_LedRed};

const IoHwAb_ConfigType IoHwAb_Config =
    {
        /* .NumDigitalSignal*/
        (uint8)6,
        /* .NumAnalogSignal*/
        (uint8)3,
        /* .NumPwmSignal*/
        (uint8)3,
        AdcGroup_0,
        IoHwAb_Dio_Channel,
        IoHwAb_Pwm_Channel};

#elif defined(ECU_CONTROL)
const Dio_ChannelType IoHwAb_Dio_Channel[1] =
    {
        DioConf_DioChannel_LedBlue,
};
const Pwm_ChannelType IoHwAb_Pwm_Channel[3] =
    {
        PwmChannel_LedRed,
        PwmChannel_Motor1,
        PwmChannel_Motor2};

const IoHwAb_ConfigType IoHwAb_Config =
    {
        /* .NumDigitalSignal*/
        (uint8)1,
        /* .NumAnalogSignal*/
        (uint8)1,
        /* .NumPwmSignal*/
        (uint8)3,
        AdcGroup_0,
        IoHwAb_Dio_Channel,
        IoHwAb_Pwm_Channel};

#endif
