#ifndef SWC_COMPUTE_SPEED_H_
#define SWC_COMPUTE_SPEED_H_

#include "Std_Types.h"
#include "Swc_GearSelector.h"
#include "Swc_DriveModeMgr.h"

typedef struct
{
    uint8 throttlePedal;
    uint8 throttleBrake;
    Gear_Type gear;
    DriveMode_Type mode;
} ComputeSpeed_InputType;

typedef struct
{
    boolean inited;
    ComputeSpeed_InputType input;
    uint16 rpmTarget;
} Speed_StateType;

void Swc_ComputeSpeed_Init(void);
void Swc_ComputeSpeed_Run10ms(void);

#endif