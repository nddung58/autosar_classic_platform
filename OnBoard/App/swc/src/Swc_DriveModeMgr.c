#include "Swc_DriveModeMgr.h"
#include "Rte.h"

static DriveMode_StatusType mode_s;

void Swc_DriveModeMgr_Init(void)
{
    mode_s.mode = DMODE_NOR;
    mode_s.inited = TRUE;
}
void Swc_DriveModeMgr_Run10ms(void)
{
    if (mode_s.inited != TRUE)
    {
        Swc_DriveModeMgr_Init();
    }
    DriveMode_Type mod;
    Std_ReturnType ret = Rte_Call_DriveMode_Digital_ReadDriveMode((uint8 *)&mod);
    if (mode_s.mode != mod)
    {
        if (Rte_Write_DriveMode_ModeOut((uint8)mod) == E_OK)
        {
            mode_s.mode = mod;
        }
    }
}