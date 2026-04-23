#include "steering_wheel.h"
#include "steering_encoder.h"
#include "Dio.h"
#include "CDD_Qdec.h"

#define EncBtn_Channel (Dio_ChannelType) DioConf_DioChannel_EncBtn

static void Steering_Wheel_GetResetBtn(uint8 *value)
{
    Dio_LevelType readLevel;
    readLevel = Dio_ReadChannel(EncBtn_Channel);
    *value = (readLevel == STD_HIGH) ? 0x01U : 0x00U;
}

static steering_encoder_t s_enc =
{
    .position = 0.0f,
    .velocity = 0.0f,
    .last_counter_value = 0,
    .timer_period = 0.01f,
    .QdecModuleId = QdecInstanceConfig_0,
    .direction = 0U,
    .first_time = 1U
};

void Steering_Wheel_Init(void)
{
    SteeringEncoder_Reset(&s_enc);
}

Std_ReturnType Steering_Wheel_GetAngle(sint16 *angle)
{
    uint8 v;

    if (angle == NULL_PTR)
    {
        return E_NOT_OK;
    }

    Steering_Wheel_GetResetBtn(&v);

    if (v == 0U) /* Reset button pressed, active-low */
    {
        SteeringEncoder_Reset(&s_enc);
        *angle = 0;
    }
    else
    {
        SteeringEncoder_Get(&s_enc);
        *angle = (sint16)(s_enc.position * 1000.0f);
    }

    return E_OK;
}
