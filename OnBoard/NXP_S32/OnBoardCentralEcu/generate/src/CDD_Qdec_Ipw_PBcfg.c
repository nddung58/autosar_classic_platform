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
/**
 *   @file       CDD_Qdec_Ipw_PBcfg.c
 *   @version    3.0.0
 *
 *   @brief      Qdec IPW
 *   @details    AUTOSAR Qdec - configuration structures generated for IPW layer
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

#include "CDD_Qdec_Ipw.h"
#include "CDD_Qdec_Ipw_PBcfg.h"
#include "Ftm_Qdec_Ip_PBcfg.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/
#define CDD_QDEC_IPW_PBCFG_VENDOR_ID_C                          43
#define CDD_QDEC_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION_C           4
#define CDD_QDEC_IPW_PBCFG_AR_RELEASE_MINOR_VERSION_C           7
#define CDD_QDEC_IPW_PBCFG_AR_RELEASE_REVISION_VERSION_C        0
#define CDD_QDEC_IPW_PBCFG_SW_MAJOR_VERSION_C                   3
#define CDD_QDEC_IPW_PBCFG_SW_MINOR_VERSION_C                   0
#define CDD_QDEC_IPW_PBCFG_SW_PATCH_VERSION_C                   0

/*==================================================================================================
 *                                      FILE VERSION CHECKS
 *================================================================================================*/
/* Check if source file and Qdec_Ipw header file are of the same vendor */
#if (CDD_QDEC_IPW_PBCFG_VENDOR_ID_C != CDD_QDEC_IPW_VENDOR_ID)
#error "CDD_Qdec_Ipw_PBcfg.c and CDD_Qdec_Ipw.h have different vendor IDs"
#endif
/* Check if source file and Qdec_Ipw header file are of the same Autosar version */
#if ((CDD_QDEC_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_AR_RELEASE_MINOR_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_AR_RELEASE_REVISION_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of CDD_Qdec_Ipw_PBcfg.c and CDD_Qdec_Ipw.h are different"
#endif
/* Check if source file and Qdec_Ipw header file are of the same Software Version */
#if ((CDD_QDEC_IPW_PBCFG_SW_MAJOR_VERSION_C != CDD_QDEC_IPW_SW_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_SW_MINOR_VERSION_C != CDD_QDEC_IPW_SW_MINOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_SW_PATCH_VERSION_C != CDD_QDEC_IPW_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec_Ipw_PBcfg.c and CDD_Qdec_Ipw.h are different"
#endif

/* Check if source file and Qdec_Ipw_PBcfg header file are of the same vendor */
#if (CDD_QDEC_IPW_PBCFG_VENDOR_ID_C != CDD_QDEC_IPW_PBCFG_VENDOR_ID)
#error "CDD_Qdec_Ipw_PBcfg.c and CDD_Qdec_Ipw_PBcfg.h have different vendor IDs"
#endif
/* Check if source file and Qdec_Ipw_PBcfg header file are of the same Autosar version */
#if ((CDD_QDEC_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION_C != CDD_QDEC_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_AR_RELEASE_MINOR_VERSION_C != CDD_QDEC_IPW_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_AR_RELEASE_REVISION_VERSION_C != CDD_QDEC_IPW_PBCFG_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of CDD_Qdec_Ipw_PBcfg.c and CDD_Qdec_Ipw_PBcfg.h are different"
#endif
/* Check if source file and Qdec_Ipw_PBcfg header file are of the same Software Version */
#if ((CDD_QDEC_IPW_PBCFG_SW_MAJOR_VERSION_C != CDD_QDEC_IPW_PBCFG_SW_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_SW_MINOR_VERSION_C != CDD_QDEC_IPW_PBCFG_SW_MINOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_SW_PATCH_VERSION_C != CDD_QDEC_IPW_PBCFG_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec_Ipw_PBcfg.c and CDD_Qdec_Ipw_PBcfg.h are different"
#endif

/* Check if source file and Ftm_Qdec_Ip_PBcfg header file are of the same vendor */
#if (CDD_QDEC_IPW_PBCFG_VENDOR_ID_C != FTM_QDEC_IP_PBCFG_VENDOR_ID)
#error "CDD_Qdec_Ipw_PBcfg.c and Ftm_Qdec_Ip_PBcfg.h have different vendor IDs"
#endif
/* Check if source file and Ftm_Qdec_Ip_PBcfg header file are of the same Autosar version */
#if ((CDD_QDEC_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION_C != FTM_QDEC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_AR_RELEASE_MINOR_VERSION_C != FTM_QDEC_IP_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_AR_RELEASE_REVISION_VERSION_C != FTM_QDEC_IP_PBCFG_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of CDD_Qdec_Ipw_PBcfg.c and Ftm_Qdec_Ip_PBcfg.h are different"
#endif
/* Check if source file and Ftm_Qdec_Ip_PBcfg header file are of the same Software Version */
#if ((CDD_QDEC_IPW_PBCFG_SW_MAJOR_VERSION_C != FTM_QDEC_IP_PBCFG_SW_MAJOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_SW_MINOR_VERSION_C != FTM_QDEC_IP_PBCFG_SW_MINOR_VERSION) || \
     (CDD_QDEC_IPW_PBCFG_SW_PATCH_VERSION_C != FTM_QDEC_IP_PBCFG_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec_Ipw_PBcfg.c and Ftm_Qdec_Ip_PBcfg.h are different"
#endif

/*================================================================================================*/

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
 *                                       GLOBAL CONSTANTS
 *================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL VARIABLES
 *================================================================================================*/

#define QDEC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"


const Qdec_Ipw_MapElType Logic2HwMap[1U] =
{
    {QDEC_IPW_IPTYPE_FTM, (uint8) 1}
};

/**
* @brief    Configurations of QDEC Ipw layer
*/
const Qdec_Ipw_ConfigType Qdec_Ipw_Config[1U] =
{
    {
        /* FTM details */
        /* Number of FTMs used by current partition */
        (uint8) 1,
        /* Refferenced FTM IP config structure array */
        Ftm_Qdec_Ip_InstanceConfig,
        Logic2HwMap
    }
};

#define QDEC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 *================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *================================================================================================*/

#ifdef __cplusplus
}
#endif
/** @} */
