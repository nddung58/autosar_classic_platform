#ifndef SWC_SAFETY_MANAGER_H_
#define SWC_SAFETY_MANAGER_H_

#include "Std_Types.h"

typedef struct
{
    uint8 speed;
    uint8 pedal;
    uint8 gear;
    uint8 driveMode;
    uint8 brake;
} SafetyType;

typedef struct
{
    boolean inited;
    uint8 missPedal;
    uint8 missBrake;
    uint8 missGear;
    uint8 missMode;
    SafetyType lastSafe;
} SafetyManager_StateType;

void Swc_SafetyManager_Init(void);
void Swc_SafetyManager_Run10ms(void);

#endif