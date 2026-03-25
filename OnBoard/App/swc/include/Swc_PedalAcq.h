#ifndef SWC_PEDAL_ACQ_H_
#define SWC_PEDAL_ACQ_H_
#include "Std_Types.h"

typedef struct
{
    boolean inited;
    uint8 outPct;
    uint16 filt_q;
} Pedal_StateType;

void Swc_PedalAcq_Init(void);
void Swc_PedalAcq_Run10ms(void);

#endif