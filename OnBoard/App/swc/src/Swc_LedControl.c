#include "Rte.h"
#include "Std_Types.h"
#include "Swc_LedControl.h"

static LedControl_StateType led_s;

void Swc_LedControl_Init(void)
{
    led_s.potentPct = 0;
    led_s.status = LED_STABLE;
    led_s.inited = TRUE;
}

void Swc_LedControl_Run10ms(void)
{
	    if (led_s.inited == FALSE)
	        Swc_LedControl_Init();
    uint8 l;
    Std_ReturnType ret;
    ret = Rte_Read_LedControl_ComCmd_LedBlueCmd(&l);

    if (ret == E_OK)
    {
    	(void)Rte_Call_LedControl_Digital_SetLevel(l);
    }



    uint8 potentPct;
    ret = Rte_Call_LedControl_Analog_PotentPct(&potentPct);

    if (ret == E_OK)
    {
        (void)Rte_Call_LedControl_Pwm_SetDutty(potentPct);
    }
}
