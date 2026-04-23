#include "Os.h"
#include "Std_Types.h"
#include "Com.h"

volatile uint32 Os_Tick = 0u;

void Gpt_LpitNotification(void)
{
    Os_Tick++;
}

extern void Task_Init(void);

extern void Task_10ms_Test(void);
extern void Task_100ms(void);
#if defined(ECU_CENTRAL)
extern void Task_EcuCentral_10ms(void);
#elif defined(ECU_CONTROL)
extern void Task_EcuControl_10ms(void);
#endif

void Os_Run(void)
{
    static uint32 lastTick = 0u;

    Task_Init();
    while (1)
    {
        Com_MainFunctionRx();
        Com_MainFunctionTx();
        if (Os_Tick != lastTick)
        {
            lastTick = Os_Tick;

            if ((Os_Tick % 10u) == 0u)
            {
                Task_10ms_Test();

#if defined(ECU_CENTRAL)
                Task_EcuCentral_10ms();
#elif defined(ECU_CONTROL)
                Task_EcuControl_10ms();
#endif
            }

            if ((Os_Tick % 100u) == 0u)
            {
                Task_100ms();
            }
        }
    }
}
