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
*    @file       CDD_Qdec_PBcfg.c
*
*    @brief      AUTOSAR Qdec - QDEC post-build configuration file.
*    @details    Post-build configuration structure instances.
*
*    @addtogroup qdec Qdec Driver
*    @brief      Qdec HLD
*   @{
*/


#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "CDD_Qdec_PBcfg.h"
#include "CDD_Qdec_Ipw.h"
#include "CDD_Qdec.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_QDEC_PBCFG_VENDOR_ID_C                           43
#define CDD_QDEC_PBCFG_AR_RELEASE_MAJOR_VERSION_C            4
#define CDD_QDEC_PBCFG_AR_RELEASE_MINOR_VERSION_C            7
#define CDD_QDEC_PBCFG_AR_RELEASE_REVISION_VERSION_C         0
#define CDD_QDEC_PBCFG_SW_MAJOR_VERSION_C                    3
#define CDD_QDEC_PBCFG_SW_MINOR_VERSION_C                    0
#define CDD_QDEC_PBCFG_SW_PATCH_VERSION_C                    0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and CDD_Qdec_PBcfg header file are of the same vendor */
#if (CDD_QDEC_PBCFG_VENDOR_ID_C != CDD_QDEC_PBCFG_VENDOR_ID)
#error "CDD_Qdec_PBcfg.c and CDD_Qdec_PBcfg.h have different vendor IDs"
#endif
/* Check if source file and CDD_Qdec_PBcfg header file are of the same Autosar version */
#if ((CDD_QDEC_PBCFG_AR_RELEASE_MAJOR_VERSION_C != CDD_QDEC_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_PBCFG_AR_RELEASE_MINOR_VERSION_C != CDD_QDEC_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_PBCFG_AR_RELEASE_REVISION_VERSION_C != CDD_QDEC_PBCFG_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of CDD_Qdec_PBcfg.c and CDD_Qdec_PBcfg.h are different"
#endif
/* Check if source file and CDD_Qdec_PBcfg header file are of the same Software Version */
#if ((CDD_QDEC_PBCFG_SW_MAJOR_VERSION_C != CDD_QDEC_PBCFG_SW_MAJOR_VERSION) || \
     (CDD_QDEC_PBCFG_SW_MINOR_VERSION_C != CDD_QDEC_PBCFG_SW_MINOR_VERSION) || \
     (CDD_QDEC_PBCFG_SW_PATCH_VERSION_C != CDD_QDEC_PBCFG_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec_PBcfg.c and CDD_Qdec_PBcfg.h are different"
#endif

/* Check if source file and CDD_Qdec_Ipw header file are of the same vendor */
#if (CDD_QDEC_PBCFG_VENDOR_ID_C != CDD_QDEC_IPW_VENDOR_ID)
#error "CDD_Qdec_PBcfg.c and CDD_Qdec_Ipw.h have different vendor IDs"
#endif
/* Check if source file and CDD_Qdec_Ipw header file are of the same Autosar version */
#if ((CDD_QDEC_PBCFG_AR_RELEASE_MAJOR_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_PBCFG_AR_RELEASE_MINOR_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_PBCFG_AR_RELEASE_REVISION_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of CDD_Qdec_PBcfg.c and CDD_Qdec_Ipw.h are different"
#endif
/* Check if source file and CDD_Qdec_Ipw header file are of the same Software Version */
#if ((CDD_QDEC_PBCFG_SW_MAJOR_VERSION_C != CDD_QDEC_IPW_SW_MAJOR_VERSION) || \
     (CDD_QDEC_PBCFG_SW_MINOR_VERSION_C != CDD_QDEC_IPW_SW_MINOR_VERSION) || \
     (CDD_QDEC_PBCFG_SW_PATCH_VERSION_C != CDD_QDEC_IPW_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec_PBcfg.c and CDD_Qdec_Ipw.h are different"
#endif

/* Check if source file and CDD_Qdec header file are of the same vendor */
#if (CDD_QDEC_PBCFG_VENDOR_ID_C != CDD_QDEC_VENDOR_ID)
    #error "CDD_Qdec_PBcfg.c and CDD_Qdec.h have different vendor IDs"
#endif
/* Check if source file and CDD_Qdec header file are of the same AutoSar version */
#if ((CDD_QDEC_PBCFG_AR_RELEASE_MAJOR_VERSION_C != CDD_QDEC_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_PBCFG_AR_RELEASE_MINOR_VERSION_C != CDD_QDEC_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_PBCFG_AR_RELEASE_REVISION_VERSION_C != CDD_QDEC_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of CDD_Qdec_PBcfg.c and CDD_Qdec.h are different"
#endif
/* Check if source file and CDD_Qdec header file are of the same Software version */
#if ((CDD_QDEC_PBCFG_SW_MAJOR_VERSION_C != CDD_QDEC_SW_MAJOR_VERSION) || \
     (CDD_QDEC_PBCFG_SW_MINOR_VERSION_C != CDD_QDEC_SW_MINOR_VERSION) || \
     (CDD_QDEC_PBCFG_SW_PATCH_VERSION_C != CDD_QDEC_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec_PBcfg.c and CDD_Qdec.h are different"
#endif

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define QDEC_START_SEC_CODE
#include "Qdec_MemMap.h"

#if (QDEC_NOTIFICATION_SUPPORTED == STD_ON)
#endif

#define QDEC_STOP_SEC_CODE
#include "Qdec_MemMap.h"

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

#define QDEC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

/**
* @brief    Configurations for QDEC instances on Partition 
*/
static const Qdec_InstanceConfigType Qdec_InstanceConfig[1U] =
{
    /* QdecInstanceConfig_0 -> FTM_1 */
    {
        (Qdec_EncodingModeType) MODE_PHASE_ENCODE,   /** @brief */
        (uint16) 0,   /** @brief Minimum counter value */
        (uint16) 65535,   /** @brief Maximum counter value */
        (boolean) FALSE,   /** @brief Timer Overflow Interrupt */
        /** @brief Configuration of input phase A */
        {
            (boolean) TRUE,    /** @brief Enables the filter for the quadrature decoder phase A,B inputs */
            (uint8) 6,   /** @brief Filter value (if input filter is enabled) */
            (Qdec_PhasePolarityType) PHASE_NORMAL    /** @brief Phase polarity */
        },
        /** @brief Configuration of input phase B */
        {
            (boolean) TRUE,    /** @brief Enables the filter for the quadrature decoder phase A,B inputs */
            (uint8) 6,   /** @brief Filter value (if input filter is enabled) */
            (Qdec_PhasePolarityType) PHASE_NORMAL    /** @brief Phase polarity */
        },
#if (QDEC_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief  Qdec notification function */
          NULL_PTR
#endif
    }
};

/*
*   @brief Pre-Compile Default Configuration for Partition 
*/
#if (STD_ON == QDEC_PRECOMPILE_SUPPORT)
const Qdec_ConfigType Qdec_Config =
{
    (uint8) 0U,    /* Partition index */
    (uint8) 1U, /* Number of QDEC instances on this Partition */
    &Qdec_InstanceConfig,   /* Qdec_InstanceConfigTypePtr */
    Qdec_Ipw_Config
};

#endif /*STD_ON == QDEC_PRECOMPILE_SUPPORT*/
#define QDEC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

#ifdef __cplusplus
}
#endif
/**@}*/
