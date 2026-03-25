#ifndef SWC_DRIVE_MODE_MANAGER_H_
#define SWC_DRIVE_MODE_MANAGER_H_

#include "Std_Types.h"

typedef enum
{
    DMODE_NOR = 0x00,
    DMODE_ECO,
    DMODE_SPT,
    DMODE_INVALID
} DriveMode_Type;

typedef struct
{
    boolean inited;
    DriveMode_Type mode;
} DriveMode_StatusType;

void Swc_DriveModeMgr_Init(void);
void Swc_DriveModeMgr_Run10ms(void);

#endif