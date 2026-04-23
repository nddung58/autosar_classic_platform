#include "Swc_PedalAcq.h"
#include "Swc_BrakeAcq.h"
#include "Swc_GearSelector.h"
#include "Swc_DriveModeMgr.h"
#include "Swc_SafetyManager.h"
#include "Swc_ComputeSpeed.h"
#include "Swc_SteeringWheelAcq.h"

void Task_EcuCentral_10ms(void)
{
    Swc_PedalAcq_Run10ms();
    Swc_BrakeAcq_Run10ms();
    Swc_GearSelector_Run10ms();
    Swc_DriveModeMgr_Run10ms();
    Swc_SafetyManager_Run10ms();
    Swc_ComputeSpeed_Run10ms();
    Swc_SteeringWheelAcq_10ms();
}
