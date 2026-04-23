#ifndef CDD_PID_CONTROL_H_
#define CDD_PID_CONTROL_H_

#include "Std_Types.h"
#include "motor_encoder.h"
#include "pid_control.h"

typedef struct
{

} PID_ConfigType;

Std_ReturnType PIDControl_Init(const PID_ConfigType *config);

Std_ReturnType PIDControl_Compute(sint16 rpmTarget,
                                  sint16 wheelAngle,
                                  sint16 *mPctA,
                                  sint16 *mPctB);

#endif
