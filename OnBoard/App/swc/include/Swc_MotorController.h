#ifndef SWC_MOTOR_CONTROLLER_H_
#define SWC_MOTOR_CONTROLLER_H_

#include "Std_Types.h"

typedef enum
{
    IDLE,
    BALANCING,
    MOVING,
    FALLEN,
    ERROR
} Motor_ControlStateType;

typedef struct
{
    boolean inited;
    uint16 rpmTarget;
    sint16 wheelAngle;
    Motor_ControlStateType SB_state;
} Motor_StateType;

void Swc_MotorController_Init(void);
void Swc_MotorController_Run10ms(void);

#endif