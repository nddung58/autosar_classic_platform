#include "Swc_GearSelector.h"
#include "Rte.h"

static Gear_StatusType s_gear;

void Swc_GearSelector_Init(void)
{
    s_gear.gear = GEAR_P;
    s_gear.inited = TRUE;
}

void Swc_GearSelector_Run10ms(void)
{
    if (s_gear.inited != TRUE)
    {
        Swc_GearSelector_Init();
    }

    Gear_Type g;

    Std_ReturnType ret = Rte_Call_Gear_Digital_ReadGearSel((uint8*)&g);

    if (ret != E_OK)
        return;

    (void)Rte_Write_Gear_GearOut(g);
}
