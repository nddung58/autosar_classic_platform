#ifndef SWC_ECHO_REVERSE_H_
#define SWC_ECHO_REVERSE_H_

#include "Std_Types.h"

typedef struct
{
    boolean inited;
} EchoReverse_StateType;

void Swc_EchoReverse_Init(void);
void Swc_EchoReverse_Run10ms(void);

#endif