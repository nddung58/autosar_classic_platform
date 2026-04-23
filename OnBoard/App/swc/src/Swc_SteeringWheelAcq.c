#include "Swc_SteeringWheelAcq.h"
#include "Rte.h"

#define STEERING_WHEEL_RATIO        (24U)
#define STEERING_ANGLE_MIN_MRAD     ((sint16)-12566)
#define STEERING_ANGLE_MAX_MRAD     ((sint16)12566)
#define WHEEL_ANGLE_MIN_MRAD        ((sint16)-524)
#define WHEEL_ANGLE_MAX_MRAD        ((sint16)524)

static SteeringWheel_StateType steering_s;

static sint16 SteeringWheel_Clamp(sint16 value, sint16 min, sint16 max)
{
    if (value < min)
    {
        return min;
    }

    if (value > max)
    {
        return max;
    }

    return value;
}

void Swc_SteeringWheelAcq_Init(void)
{
    steering_s.ratio = STEERING_WHEEL_RATIO;
    steering_s.steeringAngle = 0;
    steering_s.wheelAngle = 0;
    steering_s.inited = TRUE;
}

void Swc_SteeringWheelAcq_10ms(void)
{
    sint16 steering_angle;
    sint16 wheel_angle;

    if (steering_s.inited != TRUE)
    {
        Swc_SteeringWheelAcq_Init();
    }

    if (Rte_Call_SteeringWheelAcq_Steering_ReadAngle(&steering_angle) != E_OK)
    {
        return;
    }

    steering_angle = SteeringWheel_Clamp(
        steering_angle,
        STEERING_ANGLE_MIN_MRAD,
        STEERING_ANGLE_MAX_MRAD);

    wheel_angle = (sint16)(steering_angle / (sint16)steering_s.ratio);

    wheel_angle = SteeringWheel_Clamp(
        wheel_angle,
        WHEEL_ANGLE_MIN_MRAD,
        WHEEL_ANGLE_MAX_MRAD);

    steering_s.steeringAngle = steering_angle;
    steering_s.wheelAngle = wheel_angle;

    (void)Rte_Write_SteeringWheelAcq_SteeringAngle(steering_s.steeringAngle);
    (void)Rte_Write_SteeringWheelAcq_WheelAngle(steering_s.wheelAngle);
}
