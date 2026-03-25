#ifndef SWC_BRAKE_ACQ_H_
#define SWC_BRAKE_ACQ_H_

#include "Std_Types.h"

typedef struct
{
    boolean inited;
    uint8 outPct;
    uint16 filt_q;
} Brake_StatusType;

void Swc_BrakeAcq_Init(void);
void Swc_BrakeAcq_Run10ms(void);

#endif