#include "Swc_LedControl.h"
#include "Swc_EchoReverse.h"

void Task_10ms_Test(void)
{
    Swc_LedControl_Run10ms();
    Swc_CmdComposer_Run10ms();
}
