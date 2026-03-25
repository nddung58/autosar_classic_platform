/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : Ftm
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K1_RTD_3_0_0_QLP02_D2505_ASR_REL_4_7_REV_0000_20250530
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
#ifndef FTM_QDEC_IP_H
#define FTM_QDEC_IP_H

/**
*    @file       Ftm_Qdec_Ip.h
*
*    @addtogroup ftm_qdec_ip Ftm_Qdec_Ip Driver
*    @{
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
#include "Ftm_Qdec_Ip_Cfg.h"
#include "Ftm_Qdec_Ip_Types.h"

#if (FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT == STD_ON)
    #include "Reg_eSys.h"
#endif

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FTM_QDEC_IP_VENDOR_ID                       43
#define FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION        4
#define FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION        7
#define FTM_QDEC_IP_AR_RELEASE_REVISION_VERSION     0
#define FTM_QDEC_IP_SW_MAJOR_VERSION                3
#define FTM_QDEC_IP_SW_MINOR_VERSION                0
#define FTM_QDEC_IP_SW_PATCH_VERSION                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if header file and Ftm_Qdec_Ip_Cfg configuration header file are of the same vendor */
#if (FTM_QDEC_IP_VENDOR_ID != FTM_QDEC_IP_CFG_VENDOR_ID)
    #error "Ftm_Qdec_Ip.h and Ftm_Qdec_Ip_Cfg.h have different vendor IDs"
#endif
    /* Check if header file and Ftm_Qdec_Ip_Cfg configuration header file are of the same Autosar version */
#if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION != FTM_QDEC_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION != FTM_QDEC_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_AR_RELEASE_REVISION_VERSION != FTM_QDEC_IP_CFG_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Ftm_Qdec_Ip.h and Ftm_Qdec_Ip_Cfg.h are different"
#endif
/* Check if header file and Ftm_Qdec_Ip_Cfg configuration header file are of the same Software version */
#if ((FTM_QDEC_IP_SW_MAJOR_VERSION != FTM_QDEC_IP_CFG_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_SW_MINOR_VERSION != FTM_QDEC_IP_CFG_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_SW_PATCH_VERSION != FTM_QDEC_IP_CFG_SW_PATCH_VERSION))
#error "Software Version Numbers of Ftm_Qdec_Ip.h and Ftm_Qdec_Ip_Cfg.h are different"
#endif

/* Check if header file and Ftm_Qdec_Ip_Types header file are of the same vendor */
#if (FTM_QDEC_IP_VENDOR_ID != FTM_QDEC_IP_TYPES_VENDOR_ID)
    #error "Ftm_Qdec_Ip.h and Ftm_Qdec_Ip_Types.h have different vendor IDs"
#endif
    /* Check if header file and Ftm_Qdec_Ip_Types header file are of the same Autosar version */
#if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_AR_RELEASE_REVISION_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Ftm_Qdec_Ip.h and Ftm_Qdec_Ip_Types.h are different"
#endif
/* Check if header file and Ftm_Qdec_Ip_Types header file are of the same Software version */
#if ((FTM_QDEC_IP_SW_MAJOR_VERSION != FTM_QDEC_IP_TYPES_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_SW_MINOR_VERSION != FTM_QDEC_IP_TYPES_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_SW_PATCH_VERSION != FTM_QDEC_IP_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of Ftm_Qdec_Ip.h and Ftm_Qdec_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Reg_eSys.h file are of the same Autosar version */
    #if (FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT == STD_ON)
        #if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
             (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION))
            #error "AutoSar Version Numbers of Ftm_Qdec_Ip.h and Reg_eSys.h are different"
        #endif
    #endif /* FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT == STD_ON */
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/
#define QDEC_START_SEC_CODE
#include "Qdec_MemMap.h"

/**
* @brief    Configures the quadrature mode and starts measurement
*
* @param    [in] module     FTM hardware instance number.
* @param    [in] config     Configuration structure(Quadrature Decoder Mode, polarity for both phases,
*                minimum and maximum value for the counter, filter configuration).
*
* @return   No return.
*/
void Ftm_Qdec_Ip_Init(uint8 module, const Ftm_Qdec_Ip_ConfigType * config);
/*=========================================================================================================*/
/**
* @brief    De-activates the Quadrature Decoder Mode.
*
* @param    [in] module     FTM hardware instance number.
*
* @return   No return.
*/
void Ftm_Qdec_Ip_Deinit(uint8 module);
/*=========================================================================================================*/
/**
* @brief    Return the current quadrature decoder state (counter value, timer overflow, TOF direction and counting direction flags)
*
* @param    [in] module     FTM hardware instance number.
*
* @return   Structure with the state of FTM module
*/
Ftm_Qdec_Ip_StateType Ftm_Qdec_Ip_GetState(uint8 module);
/*=========================================================================================================*/
#if(FTM_QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief    The function changes the prescaler of FTM channel.
* @details  This function changes the value prescaler in SC registers
*
* @param[in]    module         FTM hardware number.
* @param[in]    FtmPrescaler   Prescaler type: normal or alternative
*
* @return       No return.
*/
void Ftm_Qdec_Ip_SetClockMode(const uint8 module, uint8 prescalerValue);
#endif
/*=========================================================================================================*/
/**
* @brief    Set state of counter
*
* @param    [in] module FTM hardware number.
*
* @return   void
*/
void Ftm_Qdec_Ip_CounterState(const uint8 module);
/*=========================================================================================================*/
/**
* @brief    Reset state of module to default value
*
* @param    [in] module FTM hardware number.
*
* @return   void
*/
void Ftm_Qdec_Ip_ResetState(const uint8 module);
/*=========================================================================================================*/
#if (FTM_QDEC_NOTIFICATION_SUPPORTED == STD_ON)
/**
* @brief        This function disables QDEC overflow notification.
*
*/
void Ftm_Qdec_Ip_DisableOverFlowNotification(const uint8 module);
/*=========================================================================================================*/
/**
* @brief        This function enables QDEC overflow notification.
*
*/
void Ftm_Qdec_Ip_EnableOverFlowNotification(const uint8 module);
#endif
/*=========================================================================================================*/
/**
* @brief    Set mode of Qdec module
*
* @param    [in] module     FTM hardware number.
* @param    [in] mode       Given mode: QDEC_NORMAL_MODE or QDEC_SLEEP_MODE.
*
* @return   void
*/
void Ftm_Qdec_Ip_SetMode(const uint8 module, Ftm_ModeType mode);

#define QDEC_STOP_SEC_CODE
#include "Qdec_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* FTM_QDEC_IP_H */
