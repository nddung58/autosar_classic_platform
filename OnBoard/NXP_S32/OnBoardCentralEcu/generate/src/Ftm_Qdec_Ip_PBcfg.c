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

/**
 *   @file       Ftm_Qdec_Ip_PBcfg.c
 *
 *   @brief      Qdec - contains information about IP PB configuration.
 *   @details
 *
 *   @addtogroup ftm_qdec_ip Qdec IPL
 *   @{
 */

#ifdef __cplusplus
extern "C"{
#endif

 /*==================================================================================================
 *                                         INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *================================================================================================*/
#include "Ftm_Qdec_Ip_PBcfg.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/
#define FTM_QDEC_IP_PBCFG_VENDOR_ID_C                       43
#define FTM_QDEC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C        4
#define FTM_QDEC_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C        7
#define FTM_QDEC_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C     0
#define FTM_QDEC_IP_PBCFG_SW_MAJOR_VERSION_C                3
#define FTM_QDEC_IP_PBCFG_SW_MINOR_VERSION_C                0
#define FTM_QDEC_IP_PBCFG_SW_PATCH_VERSION_C                0

/*==================================================================================================
 *                                      FILE VERSION CHECKS
 *================================================================================================*/
/* Check if source file and Ftm_Qdec_Ip_PBcfg header file are of the same vendor */
#if (FTM_QDEC_IP_PBCFG_VENDOR_ID_C != FTM_QDEC_IP_PBCFG_VENDOR_ID)
    #error "Ftm_Qdec_Ip_PBcfg.c and Ftm_Qdec_Ip_PBcfg.h have different vendor IDs"
#endif
/* Check if source file and Ftm_Qdec_Ip_PBcfg header file are of the same AutoSar version */
#if ((FTM_QDEC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C != FTM_QDEC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C != FTM_QDEC_IP_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != FTM_QDEC_IP_PBCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Ftm_Qdec_Ip_PBcfg.c and Ftm_Qdec_Ip_PBcfg.h are different"
#endif
/* Check if source file and Ftm_Qdec_Ip_PBcfg header file are of the same Software version */
#if ((FTM_QDEC_IP_PBCFG_SW_MAJOR_VERSION_C != FTM_QDEC_IP_PBCFG_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_PBCFG_SW_MINOR_VERSION_C != FTM_QDEC_IP_PBCFG_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_PBCFG_SW_PATCH_VERSION_C != FTM_QDEC_IP_PBCFG_SW_PATCH_VERSION))
#error "Software Version Numbers of Ftm_Qdec_Ip_PBcfg.c and Ftm_Qdec_Ip_PBcfg.h are different"
#endif

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 *================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL VARIABLES
 *================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL CONSTANTS
 *================================================================================================*/

#define QDEC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

/**
* @brief    Configurations for QDEC modules which use FTM
*/

const Ftm_Qdec_Ip_ConfigType Ftm_Qdec_Ip_InstanceConfig[1U] =
{
    /* QdecInstanceConfig_0 -> FTM_1 */
    {
        (Ftm_Qdec_Ip_EncodingModeType) FTM_MODE_PHASE_ENCODE,       /** @brief Encoding mode used by FTM in the QDEC mode */
        (uint16) 0,       /** @brief Minimum counter value */
        (uint16) 65535,       /** @brief Maximum counter value */
        (boolean) FALSE,     /** @brief Timer Overflow Interrupt */
        /** @brief Configuration of input phase A */
        {
            (boolean) TRUE,      /** @brief Enables the filter for the quadrature decoder phase A,B inputs */
            (uint8) 6,       /** @brief Filter value (if input filter is enabled) */
            (Ftm_Qdec_Ip_PhasePolarityType) FTM_PHASE_NORMAL        /** @brief Phase polarity */
        },
        /** @brief Configuration of input phase B */
        {
            (boolean) TRUE,       /** @brief Enables the filter for the quadrature decoder phase A,B inputs */
            (uint8) 6,       /** @brief Filter value (if input filter is enabled) */
            (Ftm_Qdec_Ip_PhasePolarityType) FTM_PHASE_NORMAL        /** @brief Phase polarity */
        },
        {
            /** @brief Callback function for instances. */
            NULL_PTR,
            /** @brief Parameters used by callback function. */
            (uint8) 0U
        },
#if (FTM_QDEC_SET_CLOCK_MODE_API == STD_ON)
        /** @brief Ftm instance Alternate Prescaler parameters */
        (uint8)((uint32)(FTM_SC_PS_DIV1_U32) << QDEC_FTM_ALT_CLOCK_DIV_SHIFT),
        /** @brief  Ftm Control Value */
        (uint8)
        (
            ((uint8)(FTM_CLOCK_SOURCE_SYSTEMCLK) << QDEC_FTM_CLOCK_SOURCE_SHIFT)   |   /* Clock source */
            (uint8)((uint32)(FTM_SC_PS_DIV1_U32) << QDEC_FTM_CLOCK_DIV_SHIFT)         /* Timer clock prescaler configuration */
        ),
#endif
        (Ftm_Qdec_Ip_ClockSourceType) FTM_CLOCK_SOURCE_SYSTEMCLK,     /**< @brief FlexTimer Clock Source */
        (Ftm_Qdec_Ip_ClockFilterPrescType) FTM_CLOCK_FILTER_PRESCALER_DIV1       /**< @brief FlexTimer Clock Filter Prescaler */

    }
};

#define QDEC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

/*==================================================================================================
 *                                   GLOBAL VARIABLES
 *================================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 *================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
