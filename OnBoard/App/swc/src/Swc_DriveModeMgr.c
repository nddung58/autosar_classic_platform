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
    static uint8 prevBtn = 1U; /* release = 1, pressed = 0 */

    if (mode_s.inited != TRUE)
    {
        Swc_DriveModeMgr_Init();
    }

    uint8 btn = 1U;
    Std_ReturnType ret = Rte_Call_DriveMode_Digital_ReadDriveMode(&btn);
    if (ret != E_OK)
    {
        return;
    }

    /* bắt cạnh nhấn: 1 -> 0 */
    if ((prevBtn == 1U) && (btn == 0U))
    {
        DriveMode_Type newMode = mode_s.mode;

        switch (mode_s.mode)
        {
        case DMODE_NOR:
            newMode = DMODE_ECO;
            break;

        case DMODE_ECO:
            newMode = DMODE_SPT;
            break;

        case DMODE_SPT:
        default:
            newMode = DMODE_NOR;
            break;
        }

        if (Rte_Write_DriveMode_ModeOut((uint8)newMode) == E_OK)
        {
            mode_s.mode = newMode;
        }
    }

    prevBtn = btn;
}