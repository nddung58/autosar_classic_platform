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

#ifndef FTM_QDEC_IP_CFGDEFINES_H
#define FTM_QDEC_IP_CFGDEFINES_H

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
#include "Std_Types.h"
/* Include platform header file. */
#include "S32K144_FTM.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define FTM_QDEC_IP_CFGDEFINES_VENDOR_ID                     43
#define FTM_QDEC_IP_CFGDEFINES_AR_RELEASE_MAJOR_VERSION      4
#define FTM_QDEC_IP_CFGDEFINES_AR_RELEASE_MINOR_VERSION      7
#define FTM_QDEC_IP_CFGDEFINES_AR_RELEASE_REVISION_VERSION   0
#define FTM_QDEC_IP_CFGDEFINES_SW_MAJOR_VERSION              3
#define FTM_QDEC_IP_CFGDEFINES_SW_MINOR_VERSION              0
#define FTM_QDEC_IP_CFGDEFINES_SW_PATCH_VERSION              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Std_Types.h are of the same AUTOSAR version */
    #if ((FTM_QDEC_IP_CFGDEFINES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (FTM_QDEC_IP_CFGDEFINES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of Ftm_Qdec_Ip_CfgDefines.h and Std_Types.h are different."
    #endif
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/** @brief Support for User mode.
*          If this parameter has been configured to STD_ON,
*          the FTM driver code can be executed from both supervisor and user mode.
*/
#define FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT   (STD_OFF)

/** @brief Verification for user mode support. */
#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
    #if (defined (FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT))
        #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Qdec in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined
    #endif
#endif

#ifndef FTM_QDEC_SET_CLOCK_MODE_API
/** @brief  Switch for enabling the dual clock functionality (Qdec_SetClockMode() API) */
#define FTM_QDEC_SET_CLOCK_MODE_API      (STD_OFF)
#endif

#define FTM_QDEC_NOTIFICATION_SUPPORTED  (STD_OFF)

#ifndef FTM_1_USED
    #define FTM_1_USED
#else
    #error "FTM_1 instance cannot be used by QDEC. Instance locked by another driver!"
#endif
#ifndef FTM_2_USED
    #define FTM_2_USED
#else
    #error "FTM_2 instance cannot be used by QDEC. Instance locked by another driver!"
#endif

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

#endif /* FTM_QDEC_IP_CFGDEFINES_H */
