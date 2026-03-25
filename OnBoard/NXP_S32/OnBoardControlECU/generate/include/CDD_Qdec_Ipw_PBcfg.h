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
 =================================================================================================*/

#ifndef CDD_QDEC_IPW_PBCFG_H
#define CDD_QDEC_IPW_PBCFG_H
/**
 *   @file       CDD_Qdec_Ipw_PBcfg.h
 *   @version    3.0.0
 *
 *   @brief      Qdec IPW
 *   @details    AUTOSAR Qdec
 *
 *   @addtogroup
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

#include "Qdec_Ipw_Types.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/
#define CDD_QDEC_IPW_PBCFG_VENDOR_ID                          43
#define CDD_QDEC_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION           4
#define CDD_QDEC_IPW_PBCFG_AR_RELEASE_MINOR_VERSION           7
#define CDD_QDEC_IPW_PBCFG_AR_RELEASE_REVISION_VERSION        0
#define CDD_QDEC_IPW_PBCFG_SW_MAJOR_VERSION                   3
#define CDD_QDEC_IPW_PBCFG_SW_MINOR_VERSION                   0
#define CDD_QDEC_IPW_PBCFG_SW_PATCH_VERSION                   0

/*==================================================================================================
 *                                      FILE VERSION CHECKS
 *================================================================================================*/
/* Check if header file and Qdec_Ipw_Types header file are of the same vendor */
#if (CDD_QDEC_IPW_PBCFG_VENDOR_ID != QDEC_IPW_TYPES_VENDOR_ID)
#error "CDD_Qdec_Ipw_PBcfg.h and Qdec_Ipw_Types.h have different vendor IDs"
#endif
/* Check if header file and Qdec_Ipw_Types header file are of the same Autosar version */
#if ((CDD_QDEC_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION != QDEC_IPW_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_AR_RELEASE_MINOR_VERSION != QDEC_IPW_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_AR_RELEASE_REVISION_VERSION != QDEC_IPW_TYPES_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of CDD_Qdec_Ipw_PBcfg.h and Qdec_Ipw_Types.h are different"
#endif
/* Check if header file and Qdec_Ipw_Types header file are of the same Software Version */
#if ((CDD_QDEC_IPW_PBCFG_SW_MAJOR_VERSION != QDEC_IPW_TYPES_SW_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_SW_MINOR_VERSION != QDEC_IPW_TYPES_SW_MINOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_SW_PATCH_VERSION != QDEC_IPW_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec_Ipw_PBcfg.h and Qdec_Ipw_Types.h are different"
#endif

/*================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL VARIABLES
 *================================================================================================*/

#define QDEC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

extern const Qdec_Ipw_ConfigType Qdec_Ipw_Config[2U];

#define QDEC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* CDD_QDEC_IPW_PBCFG_H */
