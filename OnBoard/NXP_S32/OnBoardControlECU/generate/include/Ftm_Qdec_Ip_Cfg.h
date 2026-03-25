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

#ifndef FTM_QDEC_IP_CFG_H
#define FTM_QDEC_IP_CFG_H

/**
*   @file
*
*   @addtogroup group_name
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/* Standard Types */
#include "Std_Types.h"

/* Include all variants header files. */
#include "Ftm_Qdec_Ip_PBcfg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FTM_QDEC_IP_CFG_VENDOR_ID                                   43
#define FTM_QDEC_IP_CFG_AR_RELEASE_MAJOR_VERSION                    4
#define FTM_QDEC_IP_CFG_AR_RELEASE_MINOR_VERSION                    7
#define FTM_QDEC_IP_CFG_AR_RELEASE_REVISION_VERSION                 0
#define FTM_QDEC_IP_CFG_SW_MAJOR_VERSION                            3
#define FTM_QDEC_IP_CFG_SW_MINOR_VERSION                            0
#define FTM_QDEC_IP_CFG_SW_PATCH_VERSION                            0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Std_Types.h are of the same AUTOSAR version */
    #if ((FTM_QDEC_IP_CFG_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (FTM_QDEC_IP_CFG_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of Ftm_Qdec_Ip_Cfg.h and Std_Types.h are different."
    #endif
#endif

    /* Check if header file and Ftm_Qdec_Ip_PBcfg header file are of the same vendor */
#if (FTM_QDEC_IP_CFG_VENDOR_ID != FTM_QDEC_IP_PBCFG_VENDOR_ID)
    #error "Ftm_Qdec_Ip_Cfg.h and Ftm_Qdec_Ip_PBcfg.h have different vendor IDs"
#endif
    /* Check if header file and Ftm_Qdec_Ip_PBcfg header file are of the same Autosar version */
#if ((FTM_QDEC_IP_CFG_AR_RELEASE_MAJOR_VERSION != FTM_QDEC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_CFG_AR_RELEASE_MINOR_VERSION != FTM_QDEC_IP_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_CFG_AR_RELEASE_REVISION_VERSION != FTM_QDEC_IP_PBCFG_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Ftm_Qdec_Ip_Cfg.h and Ftm_Qdec_Ip_PBcfg.h are different"
#endif
/* Check if header file and Ftm_Qdec_Ip_PBcfg header file are of the same Software version */
#if ((FTM_QDEC_IP_CFG_SW_MAJOR_VERSION != FTM_QDEC_IP_PBCFG_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_CFG_SW_MINOR_VERSION != FTM_QDEC_IP_PBCFG_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_CFG_SW_PATCH_VERSION != FTM_QDEC_IP_PBCFG_SW_PATCH_VERSION))
#error "Software Version Numbers of Ftm_Qdec_Ip_Cfg.h and Ftm_Qdec_Ip_PBcfg.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/** @brief Switch to enable the development error detection. */
#define FTM_QDEC_IP_DEV_ERROR_DETECT            (STD_OFF)

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
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* FTM_QDEC_IP_CFG_H */
