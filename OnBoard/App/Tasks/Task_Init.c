#include "Mcu.h"
#include "Platform.h"
#include "Port.h"
#include "Can_43_FLEXCAN.h"
#include "SchM_Can_43_FLEXCAN.h"
#include "Dio.h"
#include "CanIf.h"
#include "PduR.h"
#include "PduR_Com.h"
#include "Com.h"
#include "ComStack_Types.h"
#include "IoHwAb.h"
#include "Mcl.h"
#include "Pwm.h"
#include "CDD_Rm.h"
#include "Adc.h"

#include "Swc_LedControl.h"
#include "Swc_EchoReverse.h"
#include "Swc_PedalAcq.h"
#include "Swc_BrakeAcq.h"
#include "Swc_GearSelector.h"
#include "Swc_DriveModeMgr.h"
#include "Swc_SafetyManager.h"
#include "Swc_ComputeSpeed.h"
#include "Swc_CmdComposer.h"

void Task_Init(void)
{
#if (MCU_PRECOMPILE_SUPPORT == STD_ON)
    Mcu_Init(NULL_PTR);
#else
    Mcu_Init(&Mcu_Config);
#endif

    Mcu_InitClock(McuClockSettingConfig_0);

#if (MCU_NO_PLL == STD_OFF)
    while (MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
    }
    Mcu_DistributePllClock();
#endif

    Mcu_SetMode(McuModeSettingConf_0);

    Platform_InstallIrqHandler(DMA1_IRQn, Dma0_Ch1_IRQHandler, NULL_PTR);
    Platform_SetIrq(DMA1_IRQn, TRUE);

#if (PORT_PRECOMPILE_SUPPORT == STD_ON)
    Port_Init(NULL_PTR);
#else
    Port_Init(&Port_Config);
#endif

#if (CAN_43_FLEXCAN_PRECOMPILE_SUPPORT == STD_ON)
    Can_43_FLEXCAN_Init(NULL_PTR);
#else
    Can_43_FLEXCAN_Init(&Can_43_FLEXCAN_Config);
#endif

    Can_43_FLEXCAN_SetControllerMode(
        Can_43_FLEXCANConf_CanController_CanController_0,
        CAN_CS_STARTED);
    CanIf_Init(NULL_PTR);

    PduR_Init(&PduR_Config);
    Com_Init(NULL_PTR);

#ifdef ADC_DMA_SUPPORTED
    Mcl_Init(&Mcl_Config);
    Rm_Init(NULL_PTR);
#endif

    /* Initialize ADC */
#if (ADC_PRECOMPILE_SUPPORT == STD_ON)
    Adc_Init(NULL_PTR);
#else
    Adc_Init(&Adc_Config);
#endif

    Adc_Calibrate(AdcHwUnit_0, &CalibStatus);
    if (CalibStatus.AdcUnitSelfTestStatus != E_OK)
    {
        while (1)
        {
            /* Calibration fail */
        }
    }
    IoHwAb_Init(NULL_PTR);
    Pwm_Init(&Pwm_Config);

    Swc_LedControl_Init();
    Swc_EchoReverse_Init();
    Swc_PedalAcq_Init();
    Swc_BrakeAcq_Init();
    Swc_GearSelector_Init();
    Swc_DriveModeMgr_Init();
    Swc_SafetyManager_Init();
    Swc_ComputeSpeed_Init();
    Swc_CmdComposer_Init();
}