/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
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
*   @file CDD_Rm_Ipw.c
*
*   @addtogroup RM_MODULE
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "CDD_Rm_Ipw.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RM_IPW_VENDOR_ID_C                      43
#define RM_IPW_AR_RELEASE_MAJOR_VERSION_C       4
#define RM_IPW_AR_RELEASE_MINOR_VERSION_C       7
#define RM_IPW_AR_RELEASE_REVISION_VERSION_C    0
#define RM_IPW_SW_MAJOR_VERSION_C               3
#define RM_IPW_SW_MINOR_VERSION_C               0
#define RM_IPW_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against CDD_Rm_Ipw.h */
#if (RM_IPW_VENDOR_ID_C != RM_IPW_VENDOR_ID)
    #error "CDD_Rm_Ipw.c and CDD_Rm_Ipw.h have different vendor ids"
#endif
#if ((RM_IPW_AR_RELEASE_MAJOR_VERSION_C    != RM_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (RM_IPW_AR_RELEASE_MINOR_VERSION_C    != RM_IPW_AR_RELEASE_MINOR_VERSION) || \
     (RM_IPW_AR_RELEASE_REVISION_VERSION_C != RM_IPW_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of CDD_Rm_Ipw.c and CDD_Rm_Ipw.h are different"
#endif
#if ((RM_IPW_SW_MAJOR_VERSION_C != RM_IPW_SW_MAJOR_VERSION) || \
     (RM_IPW_SW_MINOR_VERSION_C != RM_IPW_SW_MINOR_VERSION) || \
     (RM_IPW_SW_PATCH_VERSION_C != RM_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Rm_Ipw.c and CDD_Rm_Ipw.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define RM_START_SEC_CODE
#include "Rm_MemMap.h"

#if (RM_IPW_ENABLE_DMA_MUX == STD_ON)
/**
* @brief        Rm_Ipw_Dma_Mux_Init
* @details      
*
* @param[in]    
*
* @param[out]   
*
* @return       
*
* @api
*
*/
void Rm_Ipw_Dma_Mux_Init(Rm_Ipw_ConfigType const * pIpwConfig)
{
    Dma_Mux_Ip_Init(pIpwConfig->Rm_Ipw_pDma_MuxConfig);
}
#endif

#define RM_STOP_SEC_CODE
#include "Rm_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
