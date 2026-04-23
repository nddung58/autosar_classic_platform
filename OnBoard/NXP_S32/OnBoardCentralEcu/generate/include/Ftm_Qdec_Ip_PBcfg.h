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
#ifndef FTM_QDEC_IP_PBCFG_H
#define FTM_QDEC_IP_PBCFG_H

/**
 *   @file       Ftm_Qdec_Ip_PBcfg.h
 *
 *   @brief      QDEC - contains information about PB configuration on IPL.
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
#include "Ftm_Qdec_Ip_Types.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/
#define FTM_QDEC_IP_PBCFG_VENDOR_ID                       43
#define FTM_QDEC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION        4
#define FTM_QDEC_IP_PBCFG_AR_RELEASE_MINOR_VERSION        7
#define FTM_QDEC_IP_PBCFG_AR_RELEASE_REVISION_VERSION     0
#define FTM_QDEC_IP_PBCFG_SW_MAJOR_VERSION                3
#define FTM_QDEC_IP_PBCFG_SW_MINOR_VERSION                0
#define FTM_QDEC_IP_PBCFG_SW_PATCH_VERSION                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if header file and Ftm_Qdec_Ip_Types header file are of the same vendor */
#if (FTM_QDEC_IP_PBCFG_VENDOR_ID != FTM_QDEC_IP_TYPES_VENDOR_ID)
    #error "Ftm_Qdec_Ip_PBcfg.h and Ftm_Qdec_Ip_Types.h have different vendor IDs"
#endif
    /* Check if header file and Ftm_Qdec_Ip_Types header file are of the same Autosar version */
#if ((FTM_QDEC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_PBCFG_AR_RELEASE_MINOR_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_PBCFG_AR_RELEASE_REVISION_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Ftm_Qdec_Ip_PBcfg.h and Ftm_Qdec_Ip_Types.h are different"
#endif
/* Check if header file and Ftm_Qdec_Ip_Types header file are of the same Software version */
#if ((FTM_QDEC_IP_PBCFG_SW_MAJOR_VERSION != FTM_QDEC_IP_TYPES_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_PBCFG_SW_MINOR_VERSION != FTM_QDEC_IP_TYPES_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_PBCFG_SW_PATCH_VERSION != FTM_QDEC_IP_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of Ftm_Qdec_Ip_PBcfg.h and Ftm_Qdec_Ip_Types.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

#define QDEC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"
extern const Ftm_Qdec_Ip_ConfigType Ftm_Qdec_Ip_InstanceConfig[1U];

#define QDEC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* FTM_QDEC_IP_PBCFG_H */
