#ifndef STEERING_WHEEL_H_
#define STEERING_WHEEL_H_

#include "Std_Types.h"

void Steering_Wheel_Init(void);
Std_ReturnType Steering_Wheel_GetAngle(sint16 *angle);
Std_ReturnType Steering_wheel_ResetAngle(void);


#endif
