/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : Ftm
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar ConfVariant
*   SWVersion            : 3.0.0
*   BuildVersion         : S32K1_RTD_3_0_0_QLP02_D2505_ASR_REL_4_7_REV_0000_20250530
*
*   Copyright         2020-2025 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef QDEC_IPW_TYPES_H
#define QDEC_IPW_TYPES_H

/**
*     @file       Qdec_Ipw_Types.h
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
#include "Std_Types.h"
#include "Ftm_Qdec_Ip_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define QDEC_IPW_TYPES_VENDOR_ID                          43
#define QDEC_IPW_TYPES_AR_RELEASE_MAJOR_VERSION           4
#define QDEC_IPW_TYPES_AR_RELEASE_MINOR_VERSION           7
#define QDEC_IPW_TYPES_AR_RELEASE_REVISION_VERSION        0
#define QDEC_IPW_TYPES_SW_MAJOR_VERSION                   3
#define QDEC_IPW_TYPES_SW_MINOR_VERSION                   0
#define QDEC_IPW_TYPES_SW_PATCH_VERSION                   0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Std_Types.h are of the same AUTOSAR version */
    #if ((QDEC_IPW_TYPES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (QDEC_IPW_TYPES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of Qdec_Ipw_Types.h and Std_Types.h are different."
    #endif
#endif

/* Check if header file and Ftm_Qdec_Ip_Types header file are of the same vendor */
#if (QDEC_IPW_TYPES_VENDOR_ID != FTM_QDEC_IP_TYPES_VENDOR_ID)
#error "Qdec_Ipw_Types.h and Ftm_Qdec_Ip_Types.h have different vendor IDs"
#endif
/* Check if header file and Ftm_Qdec_Ip_Types header file are of the same Autosar version */
#if ((QDEC_IPW_TYPES_AR_RELEASE_MAJOR_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (QDEC_IPW_TYPES_AR_RELEASE_MINOR_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (QDEC_IPW_TYPES_AR_RELEASE_REVISION_VERSION != FTM_QDEC_IP_TYPES_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of Qdec_Ipw_Types.h and Ftm_Qdec_Ip_Types.h are different"
#endif
/* Check if header file and Ftm_Qdec_Ip_Types header file are of the same Software Version */
#if ((QDEC_IPW_TYPES_SW_MAJOR_VERSION != FTM_QDEC_IP_TYPES_SW_MAJOR_VERSION) || \
     (QDEC_IPW_TYPES_SW_MINOR_VERSION != FTM_QDEC_IP_TYPES_SW_MINOR_VERSION) || \
     (QDEC_IPW_TYPES_SW_PATCH_VERSION != FTM_QDEC_IP_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of Qdec_Ipw_Types.h and Ftm_Qdec_Ip_Types.h are different"
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

typedef enum
{
    QDEC_IPW_IPTYPE_FTM,
    QDEC_IPW_IPTYPE_EMIOS
} Qdec_Ipw_IpType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

typedef struct
{
    Qdec_Ipw_IpType IpType;
    uint8           IpInstance;
} Qdec_Ipw_MapElType;

typedef struct
{
    uint8                           Ftm_ConfigSize;
    const Ftm_Qdec_Ip_ConfigType    *Ftm_Qdec_Ip_ConfigInstance;

    const Qdec_Ipw_MapElType        *Logic2HwMap;
} Qdec_Ipw_ConfigType;

typedef struct
{
    uint16  Counter;
    boolean TimerOverflow;
    boolean TimerOverflowDir;
    boolean CountDir;
} Qdec_Ipw_State;

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* QDEC_IPW_TYPES_H */
