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

#ifndef CDD_QDEC_CFG_H
#define CDD_QDEC_CFG_H

/**
*   @file       CDD_Qdec_Cfg.h
*
*   @brief      AUTOSAR Qdec - contains the configuration data of the Qdec driver
*   @details    Contains the configuration data of the Qdec driver
*
*   @addtogroup qdec Qdec Driver
*   @brief      Qdec HLD
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Std_Types.h"
/* Include all variants header files. */
#include "CDD_Qdec_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define CDD_QDEC_CFG_VENDOR_ID                          43
#define CDD_QDEC_CFG_AR_RELEASE_MAJOR_VERSION           4
#define CDD_QDEC_CFG_AR_RELEASE_MINOR_VERSION           7
#define CDD_QDEC_CFG_AR_RELEASE_REVISION_VERSION        0
#define CDD_QDEC_CFG_SW_MAJOR_VERSION                   3
#define CDD_QDEC_CFG_SW_MINOR_VERSION                   0
#define CDD_QDEC_CFG_SW_PATCH_VERSION                   0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Std_Types.h are of the same AUTOSAR version */
    #if ((CDD_QDEC_CFG_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_QDEC_CFG_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of CDD_Qdec_Cfg.h and Std_Types.h are different."
    #endif
#endif

/* Check if header file and QDEC configuration header file are of the same vendor */
#if (CDD_QDEC_CFG_VENDOR_ID != CDD_QDEC_PBCFG_VENDOR_ID)
    #error "CDD_Qdec_Cfg.h and CDD_Qdec_PBcfg.h have different vendor IDs"
#endif
    /* Check if header file and Qdec configuration header file are of the same Autosar version */
#if ((CDD_QDEC_CFG_AR_RELEASE_MAJOR_VERSION != CDD_QDEC_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_CFG_AR_RELEASE_MINOR_VERSION != CDD_QDEC_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_CFG_AR_RELEASE_REVISION_VERSION != CDD_QDEC_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of CDD_Qdec_Cfg.h and CDD_Qdec_PBcfg.h are different"
#endif
/* Check if header file and Qdec configuration header file are of the same software version */
#if ((CDD_QDEC_CFG_SW_MAJOR_VERSION != CDD_QDEC_PBCFG_SW_MAJOR_VERSION) || \
     (CDD_QDEC_CFG_SW_MINOR_VERSION != CDD_QDEC_PBCFG_SW_MINOR_VERSION) || \
     (CDD_QDEC_CFG_SW_PATCH_VERSION != CDD_QDEC_PBCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Qdec_Cfg.h and CDD_Qdec_PBcfg.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/**
 *   @brief Pre-compile configuration constants
 */
#define QDEC_PRECOMPILE_SUPPORT     (STD_ON)

/**
*   @brief  Switches the Development Error Detection and Notification on or off.
*           STD_ON: Enabled.
*           STD_OFF: Disabled.
*/
#define QDEC_DEV_ERROR_DETECT       (STD_OFF)

#if (QDEC_DEV_ERROR_DETECT == STD_ON)
/**
 *   @brief Maximum number of QDEC instances configured
 */
#define QDEC_MAX_INSTANCE           ((uint8)1U)
#endif

/**
*   @brief      Adds or removes the service Qdec_DeInit() from the code.
*               STD_ON:  Qdec_DeInit() can be used.
*               STD_OFF: Qdec_DeInit() can not be used.
*/
#define QDEC_DEINIT_API             (STD_ON)

#define QDEC_MULTIPARTITION_ENABLED      (STD_OFF)

#if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
/**
* @brief        QDEC_MAX_PARTITIONS.
* @details      Number of maximum partitions.
*/
#define QDEC_MAX_PARTITIONS         (1U)
#endif

/**
*   @brief      Qdec instance symbolic names
*   @details    Get All Symbolic Names from configuration tool
*/
#define QdecInstanceConfig_0                                 (QdecConf_QdecInstanceConfig_QdecInstanceConfig_0)
#define QdecConf_QdecInstanceConfig_QdecInstanceConfig_0     ((uint8)0U)


#ifndef QDEC_SET_CLOCK_MODE_API
/** @brief  Switch for enabling the dual clock functionality (Qdec_SetClockMode() API) */
#define QDEC_SET_CLOCK_MODE_API      (STD_OFF)
#endif

#define QDEC_NOTIFICATION_SUPPORTED  (STD_OFF)

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

#endif    /* CDD_QDEC_CFG_H */
