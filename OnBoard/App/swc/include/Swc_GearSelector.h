#ifndef SWC_GEAR_SELECTOR_H_
#define SWC_GEAR_SELECTOR_H_

#include "Std_Types.h"

typedef enum
{
    GEAR_P,
    GEAR_R,
    GEAR_N,
    GEAR_D
} Gear_Type;

typedef struct
{
    boolean inited;
    Gear_Type gear;
} Gear_StatusType;

void Swc_GearSelector_Init(void);
void Swc_GearSelector_Run10ms(void);

#endif