/*==================================================================================================
*   Project             : RTD AUTOSAR 4.7
*   Platform            : CORTEXM
*   Peripheral          : Ftm
*   Dependencies        : none
*
*   Autosar Version     : 4.7.0
*   Autosar Revision    : ASR_REL_4_7_REV_0000
*   Autosar ConfVariant
*   SWVersion           : 3.0.0
*   BuildVersion        : S32K1_RTD_3_0_0_QLP02_D2505_ASR_REL_4_7_REV_0000_20250530
*
*   Copyright 2020-2025 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*     @file       CDD_Qdec_Ipw.c
*
*     @internal
*     @addtogroup qdec_ipw Qdec_Ipw Driver
*     @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
*  1) system and project includes
*  2) needed interfaces from external units
*  3) internal and external interfaces from this unit
==================================================================================================*/

#include "CDD_Qdec_Ipw.h"

/*==================================================================================================
*                                  SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define CDD_QDEC_IPW_VENDOR_ID_C                     43
#define CDD_QDEC_IPW_AR_RELEASE_MAJOR_VERSION_C      4
#define CDD_QDEC_IPW_AR_RELEASE_MINOR_VERSION_C      7
#define CDD_QDEC_IPW_AR_RELEASE_REVISION_VERSION_C   0
#define CDD_QDEC_IPW_SW_MAJOR_VERSION_C              3
#define CDD_QDEC_IPW_SW_MINOR_VERSION_C              0
#define CDD_QDEC_IPW_SW_PATCH_VERSION_C              0

/*==================================================================================================
 *                                       FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Qdec_Ipw header file are of the same vendor */
#if (CDD_QDEC_IPW_VENDOR_ID_C != CDD_QDEC_IPW_VENDOR_ID)
#error "CDD_Qdec_Ipw.c and CDD_Qdec_Ipw.h have different vendor IDs"
#endif
/* Check if source file and Qdec_Ipw header file are of the same Autosar version */
#if ((CDD_QDEC_IPW_AR_RELEASE_MAJOR_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_AR_RELEASE_MINOR_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_IPW_AR_RELEASE_REVISION_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of CDD_Qdec_Ipw.c and CDD_Qdec_Ipw.h are different"
#endif
/* Check if source file and Qdec_Ipw header file are of the same Software Version */
#if ((CDD_QDEC_IPW_SW_MAJOR_VERSION_C != CDD_QDEC_IPW_SW_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_SW_MINOR_VERSION_C != CDD_QDEC_IPW_SW_MINOR_VERSION) || \
     (CDD_QDEC_IPW_SW_PATCH_VERSION_C != CDD_QDEC_IPW_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec_Ipw.c and CDD_Qdec_Ipw.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                        LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                        LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                        LOCAL FUNCTIONS
==================================================================================================*/

#define QDEC_START_SEC_CODE
#include "Qdec_MemMap.h"

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

/**
* Function Name : Qdec_Ipw_Init
* Description   : Configures the needed parameters and activates for Quadrature Decoder Mode.
*/
void Qdec_Ipw_Init(uint8 count, const Qdec_Ipw_ConfigType *Config)
{
    uint8 index;
    for(index = 0; index < count; index++)
    {
        Ftm_Qdec_Ip_Init((Config -> Logic2HwMap[index]).IpInstance, &(Config->Ftm_Qdec_Ip_ConfigInstance[index]));
    }
    
}

/**
*
* Function Name : Qdec_Ipw_Deinit
* Description   : Disable Quadrature Decoder Mode.
*/
void Qdec_Ipw_DeInit(uint8 count, const Qdec_Ipw_ConfigType *Config)
{
    uint8 index;
    for(index = 0; index < count; index++)
    {
        Ftm_Qdec_Ip_Deinit((Config -> Logic2HwMap[index]).IpInstance);
    }
}

/**
*
* Function Name : Qdec_Ipw_GetState
* Description   : Get the current quadrature decoder state (counter value and flags).
*/
Qdec_Ipw_State Qdec_Ipw_GetState(uint8 module, const Qdec_Ipw_ConfigType *Config)
{
    Ftm_Qdec_Ip_StateType FtmState = Ftm_Qdec_Ip_GetState(Config->Logic2HwMap[module].IpInstance);
    Qdec_Ipw_State IpwState;

    IpwState.Counter = FtmState.mCounter;
    IpwState.TimerOverflow = FtmState.mTimerOverflow;
    IpwState.TimerOverflowDir = FtmState.mTimerOverflowDir;
    IpwState.CountDir = FtmState.mCountDir;
    
    return IpwState;
}

#if (QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief        Qdec_Ipw_SetClockMode
* @details      This function will call SetClockMode function of all configured hardware eMIOS modules.
*
* @param[in]    prescaler      Pre-scaler type
* @param[in]    ipConfig       Pointer to QDEC top configuration structure
*
* @return       void
*
*/
void Qdec_Ipw_SetClockMode(const Qdec_Ipw_ConfigType *Config, uint8 moduleId, Qdec_SelectPrescalerType prescaler)
{
    uint8 FtmPrescaler;

    if(QDEC_ALTERNATIVE_PRESCALER == prescaler)
    {
        FtmPrescaler = (Config->Ftm_Qdec_Ip_ConfigInstance->AlternateCtrVal & QDEC_FTM_ALT_CLOCK_DIV_MASK_U8) >> QDEC_FTM_ALT_CLOCK_DIV_SHIFT;
    }
    else
    {
        FtmPrescaler = (Config->Ftm_Qdec_Ip_ConfigInstance->ModuleControlValue & QDEC_FTM_CLOCK_DIV_MASK_U8) >> QDEC_FTM_CLOCK_DIV_SHIFT;
    }

    /* Call FTM IP function */
    Ftm_Qdec_Ip_SetClockMode(moduleId, FtmPrescaler);

}
#endif /* QDEC_SET_CLOCK_MODE_API */


/**
* @brief    Set the state of counter.
*/
void Qdec_Ipw_CounterState(const uint8 module, const Qdec_Ipw_ConfigType *Config)
{
    Ftm_Qdec_Ip_CounterState(Config->Logic2HwMap[module].IpInstance);
}

/**
* @brief    Reset to default current state of the QDEC module.
*/
void Qdec_Ipw_ResetState(const uint8 module, const Qdec_Ipw_ConfigType *Config)
{
    Ftm_Qdec_Ip_ResetState(Config->Logic2HwMap[module].IpInstance);
}

#if (QDEC_NOTIFICATION_SUPPORTED == STD_ON)
/**
* @brief    Disables QDEC overflow notification.
*/
void Qdec_Ipw_DisableOverFlowNotification(const uint8 module, const Qdec_Ipw_ConfigType *Config)
{
    Ftm_Qdec_Ip_DisableOverFlowNotification(Config->Logic2HwMap[module].IpInstance);
}

/**
* @brief    Enables QDEC overflow notification.
*/
void Qdec_Ipw_EnableOverFlowNotification(const uint8 module, const Qdec_Ipw_ConfigType *Config)
{

    Ftm_Qdec_Ip_EnableOverFlowNotification(Config->Logic2HwMap[module].IpInstance);
}
#endif

/**
* @brief    Select used mode
*/
void Qdec_Ipw_SetMode(const uint8 module, const Qdec_Ipw_ConfigType *Config, Qdec_ModeType mode)
{
    Ftm_ModeType ftmMode;
    
    if (mode == QDEC_MODE_NORMAL)
    {
        ftmMode = FTM_QDEC_MODE_NORMAL;
    }
    else
    {
        ftmMode = FTM_QDEC_MODE_SLEEP;
    }
    Ftm_Qdec_Ip_SetMode(Config->Logic2HwMap[module].IpInstance, ftmMode);
}

#define QDEC_STOP_SEC_CODE
#include "Qdec_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
