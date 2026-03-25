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
#include "Swc_EchoReverse.h"
#include "IoHwAb.h"
#include "Mcl.h"
#include "Pwm.h"
#include "CDD_Rm.h"

#include "Adc.h"
#include "Swc_LedControl.h"

uint8 Can_au8Sdu[8U] = {0x01U,0x02U,0x03U,0x04U,0x05U,0x06U,0x07U,0x08U};

#define PWM_DUTY_MAX    (0x8000u)

void Delay(uint32 delay)
{
    static volatile uint32 DelayTimer = 0U;
    while (DelayTimer < delay)
    {
        DelayTimer++;
    }
    DelayTimer = 0U;
}

/* ===== PduR Route Config: COM TxPduId -> CanIf TxPduId ===== */
static const PduR_RouteType PduR_Routes[] =
{
    { .SrcPduId = 0U, .DstPduId = 0U }   /* COM(0) -> CanIf(0) */
};

static const PduR_ConfigType PduR_Config =
{
    .Routes     = PduR_Routes,
    .RouteCount = (uint16)(sizeof(PduR_Routes) / sizeof(PduR_Routes[0]))
};
extern ISR(Dma0_Ch1_IRQHandler);
int main(void)
{
//    uint8 pinValue_FlexIO = STD_LOW;

	Adc_CalibrationStatusType CalibStatus;
    Platform_Init(NULL_PTR);


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

    /* Start CAN controller */
    Can_43_FLEXCAN_SetControllerMode(
        Can_43_FLEXCANConf_CanController_CanController_0,
        CAN_CS_STARTED
    );
    CanIf_Init(NULL_PTR);

    PduR_Init(&PduR_Config);
    Com_Init(NULL_PTR);
    Swc_EchoReverse_Init();


#ifdef ADC_DMA_SUPPORTED
    /* Initialize Mcl Driver and Resource Manager */
    Mcl_Init(&Mcl_Config);
    Rm_Init(NULL_PTR);
#endif

    /* Initialize ADC */
#if (ADC_PRECOMPILE_SUPPORT == STD_ON)
    Adc_Init(NULL_PTR);
#else
    Adc_Init(&Adc_Config);
#endif


    /* Calibrate ADC unit 0 */
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

            /* Set PWM period for RED LED channel */
            Pwm_SetPeriodAndDuty(PwmChannel_LedRed, PWM_DUTY_MAX, 0x0000U);
            Pwm_SetPeriodAndDuty(PwmChannel_Motor1, PWM_DUTY_MAX, 0x0000U);
            Pwm_SetPeriodAndDuty(PwmChannel_Motor2, PWM_DUTY_MAX, 0x0000U);



    /* PduInfo for transmit */
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = Can_au8Sdu;
    pduInfo.SduLength  = 8U;


//    const PduIdType ComTxPduId = 0U; /* match SrcPduId trong route */

    while (1)
    {
    	Com_MainFunctionRx();
    	Com_MainFunctionTx();
//        (void)PduR_ComTransmit(ComTxPduId, &pduInfo);
    	Swc_EchoReverse_Run10ms();
    	Swc_LedControl_Run10ms();
        /* Blink LED mỗi lần gửi */
//        pinValue_FlexIO = (STD_LOW == pinValue_FlexIO) ? STD_HIGH : STD_LOW;
        Dio_WriteChannel(DioConf_DioChannel_LedBlue, STD_HIGH);

        Delay(2000000U);
    }

    return 0;
}
