#ifndef SWC_STEERING_WHEEL_ACQ_H_
#define SWC_STEERING_WHEEL_ACQ_H_

#include "Std_Types.h"

typedef struct
{
    boolean inited;
    sint16 steeringAngle; // -12566 → 12566 mRad
    sint16 wheelAngle;     // -524 -> 524 mRad
    uint8 ratio;
} SteeringWheel_StateType;

void Swc_SteeringWheelAcq_Init(void);

void Swc_SteeringWheelAcq_10ms(void);

#endif
