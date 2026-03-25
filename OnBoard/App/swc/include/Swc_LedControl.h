#ifndef SWC_LED_CONTROL_H_
#define SWC_LED_CONTROL_H_

#include "Std_Types.h"

typedef enum
{
    LED_STABLE = 0,
    LED_UNSTABLE
} LedControlStatusType;

typedef struct
{
    boolean inited;
    uint8 potentPct;
    LedControlStatusType status;
} LedControl_StateType;

void Swc_LedControl_Init(void);
void Swc_LedControl_Run10ms(void);

#endif