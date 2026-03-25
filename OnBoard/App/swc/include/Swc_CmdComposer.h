#ifndef SWC_CMD_COMPOSER_H_
#define SWC_CMD_COMPOSER_H_

#include "Std_Types.h"

typedef struct
{
    uint8 throttlePedal;
    uint8 throttleBrake;
    uint8 gear;
    uint8 mode;
    uint16 rpmTarget;
} CmdComposer_Type;

typedef struct
{
    boolean inited;
    CmdComposer_Type lastCmd;
} CmdComposer_StateType;

void Swc_CmdComposer_Init(void);
void Swc_CmdComposer_Run10ms(void);

#endif