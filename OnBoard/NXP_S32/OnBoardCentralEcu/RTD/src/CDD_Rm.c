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
*   @file CDD_Rm.c
*
*   @addtogroup RM_MODULE RM Driver
*   @{
*/


#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
 *                                          INCLUDE FILES
 *  1) system and project includes
 *  2) needed interfaces from external units
 *  3) internal and external interfaces from this unit
==================================================================================================*/
#include "CDD_Rm.h"
#include "Mcal.h"

#if (RM_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif

/*==================================================================================================
 *                                      SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RM_VENDOR_ID_C                      43

#define RM_AR_RELEASE_MAJOR_VERSION_C       4
#define RM_AR_RELEASE_MINOR_VERSION_C       7
#define RM_AR_RELEASE_REVISION_VERSION_C    0
#define RM_SW_MAJOR_VERSION_C               3
#define RM_SW_MINOR_VERSION_C               0
#define RM_SW_PATCH_VERSION_C               0

/*==================================================================================================
 *                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against CDD_Rm.h */
#if (RM_VENDOR_ID_C != RM_VENDOR_ID)
    #error "CDD_Rm.c and CDD_Rm.h have different vendor ids"
#endif
#if ((RM_AR_RELEASE_MAJOR_VERSION_C    != RM_AR_RELEASE_MAJOR_VERSION) || \
     (RM_AR_RELEASE_MINOR_VERSION_C    != RM_AR_RELEASE_MINOR_VERSION) || \
     (RM_AR_RELEASE_REVISION_VERSION_C != RM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of CDD_Rm.c and CDD_Rm.h are different"
#endif
#if ((RM_SW_MAJOR_VERSION_C != RM_SW_MAJOR_VERSION) || \
     (RM_SW_MINOR_VERSION_C != RM_SW_MINOR_VERSION) || \
     (RM_SW_PATCH_VERSION_C != RM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Rm.c and CDD_Rm.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((RM_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (RM_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of CDD_Rm.c and Mcal.h are different"
    #endif

    #if (RM_DEV_ERROR_DETECT == STD_ON)
        /* Checks against Det.h */
        #if ((RM_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
             (RM_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
            )
            #error "AUTOSAR Version Numbers of CDD_Rm.c and Det.h are different"
        #endif
    #endif
#endif

/*==================================================================================================
 *                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#if (RM_DEV_ERROR_DETECT == STD_ON)
#define RM_MODULES_INITIALIZED 10U
#endif
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define RM_START_SEC_CODE
#include "Rm_MemMap.h"
#if (RM_DEV_ERROR_DETECT == STD_ON)
static Std_ReturnType Rm_ValidateGlobalCall(uint8 u8ServiceId,
                                            Rm_Init_Type eInit_Type);
static Std_ReturnType Rm_ValidatePtrInitAndPartitionId(Rm_ConfigType const * ConfigPtr);
#endif /*#if (RM_DEV_ERROR_DETECT == STD_ON)*/

#if (STD_ON == RM_ENABLE_GLOBAL_INIT)
/**
 * @brief Init function for Group 1 Ip: Mscm, Dmamux, Canhub and Pflash
 * 
 * @param ConfigPtr Pointer to a selected configuration structure.
 * @return void
 */
static void Rm_InitGroup1(Rm_ConfigType const *ConfigPtr);
#endif /* STD_ON == RM_ENABLE_GLOBAL_INIT */

#define RM_STOP_SEC_CODE
#include "Rm_MemMap.h"

/*==================================================================================================
 *                                        LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
 *                                        LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
 *                                        GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
 *                                        GLOBAL VARIABLES
==================================================================================================*/
#define RM_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Rm_MemMap.h"
/**
* @brief          Global variable (pointer) used for storing the Rm driver configuration data.
*/
static Rm_ConfigType const *Rm_pConfig  = NULL_PTR;

#if (RM_DEV_ERROR_DETECT == STD_ON)
static boolean Rm_abInitializedModules[RM_MODULES_INITIALIZED] = {(boolean)FALSE, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE};
#endif

#define RM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Rm_MemMap.h"

/*==================================================================================================
 *                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/*==================================================================================================
 *                                        LOCAL FUNCTIONS
==================================================================================================*/
#define RM_START_SEC_CODE
#include "Rm_MemMap.h"

#if (RM_DEV_ERROR_DETECT == STD_ON)
/**
 * @brief      This function validates the global call
 * @details    This service is a non reentrant function used for validating the calls for Rm_Init.
 *
 * @param[in]  u8ServiceId The service id of the caller function
 *
 * @return          The validity of the function call
 * @retval          E_OK      The function call is valid
 * @retval          E_NOT_OK The function call is invalid
 * @implements
 * */
static Std_ReturnType Rm_ValidateGlobalCall(uint8 u8ServiceId,
                                            Rm_Init_Type eInit_Type)
{
    Std_ReturnType valid = (Std_ReturnType)E_NOT_OK;

    if (TRUE == Rm_abInitializedModules[eInit_Type]) /* Check if already initialized */
    {
        if (RM_INIT_ID_U8 == u8ServiceId) /* If caller is the initialization function, error */
        {
            (void)Det_ReportError((uint16)RM_MODULE_ID, 0U, (uint8)u8ServiceId, RM_E_ALREADY_INITIALIZED_U8);
        }
        else
        {
            valid = (Std_ReturnType)E_OK;
        }
    }
    else
    {
        if (RM_INIT_ID_U8 == u8ServiceId) /* If caller is the initialization function, ok */
        {
            valid = (Std_ReturnType)E_OK;
        }
        else
        {
            (void)Det_ReportError((uint16)RM_MODULE_ID, 0U, (uint8)u8ServiceId, RM_E_UNINIT_U8);
        }
    }

    return valid;
}

/**
 * @brief              This function validate the initialization pointer.
 *
 * @param[in]         ConfigPtr        Pointer to a selected configuration structure.
 *
 * @return         The validity of the function call
 * @retval      E_OK      The function call is valid
 * @retval      E_NOT_OK The function call is invalid
 *
 *
 * */
static Std_ReturnType Rm_ValidatePtrInitAndPartitionId(Rm_ConfigType const * ConfigPtr)
{
    Std_ReturnType valid = (Std_ReturnType)E_OK;
#if defined(RM_MULTIPARTITION_SUPPORT)
#if (STD_ON == RM_MULTIPARTITION_SUPPORT)
    uint8 u8UserID;
#endif /* STD_ON == RM_MULTIPARTITION_SUPPORT */
#endif /* RM_MULTIPARTITION_SUPPORT */

#if (RM_DEV_ERROR_DETECT == STD_ON)
    #if (RM_PRECOMPILE_SUPPORT == STD_OFF)
    if (NULL_PTR == ConfigPtr)
    {
        valid = (Std_ReturnType)E_NOT_OK;
        (void)Det_ReportError((uint16)RM_MODULE_ID, 0U, (uint8)RM_INIT_ID_U8, (uint8)RM_E_INIT_FAILED_U8);
    }
    else
    {
        /** do nothing */
    }
    #elif (RM_PRECOMPILE_SUPPORT == STD_ON)
    if (NULL_PTR != ConfigPtr)
    {
        valid = (Std_ReturnType)E_NOT_OK;
        (void)Det_ReportError((uint16)RM_MODULE_ID, 0U, (uint8)RM_INIT_ID_U8, (uint8)RM_E_INIT_FAILED_U8);
    }
    else
    {
        /** do nothing */
    }
    #endif /*(RM_PRECOMPILE_SUPPORT == STD_OFF)*/
#endif /*(RM_DEV_ERROR_DETECT == STD_ON)*/

    if (valid == (Std_ReturnType)E_OK)
    {
        /* Check partition config */
#if defined(RM_MULTIPARTITION_SUPPORT)
#if (STD_ON == RM_MULTIPARTITION_SUPPORT)
        u8UserID = Rm_GetPartitionID();

#if (RM_PRECOMPILE_SUPPORT == STD_ON)
        if (u8UserID != Rm_Config.u8PartitionId)
        {
            valid = (Std_ReturnType)E_NOT_OK;
            (void) Det_ReportError((uint16)RM_MODULE_ID, 0U, (uint8)RM_INIT_ID_U8, (uint8)RM_E_PARAM_CONFIG);
        }
#else
        if (u8UserID != ConfigPtr->u8PartitionId)
        {
            valid = (Std_ReturnType)E_NOT_OK;
            (void) Det_ReportError((uint16)RM_MODULE_ID, 0U, (uint8)RM_INIT_ID_U8, (uint8)RM_E_PARAM_CONFIG);
        }
#endif /* RM_PRECOMPILE_SUPPORT == STD_ON */
#endif /* STD_ON == RM_MULTIPARTITION_SUPPORT */
#endif /* RM_MULTIPARTITION_SUPPORT */
    }
    
    return valid;
}

#endif /*#if (RM_DEV_ERROR_DETECT == STD_ON)*/


#if (STD_ON == RM_ENABLE_GLOBAL_INIT)
/**
 * @brief Init function for Group 1 Ip: Mscm, Dmamux and Canhub
 * 
 * @param ConfigPtr Pointer to a selected configuration structure.
 * @return void
 */
static void Rm_InitGroup1(Rm_ConfigType const *ConfigPtr)
{
#if (RM_ENABLE_DMA_MUX == STD_ON)
    Rm_Ipw_Dma_Mux_Init(ConfigPtr->Rm_pIpwConfig);
#endif
    (void)ConfigPtr;
}
#endif /* STD_ON == RM_ENABLE_GLOBAL_INIT */

#define RM_STOP_SEC_CODE
#include "Rm_MemMap.h"
/*==================================================================================================
 *                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define RM_START_SEC_CODE
#include "Rm_MemMap.h"

#if (STD_ON == RM_ENABLE_GLOBAL_INIT)
/**
 * @brief          This function initializes the RM hardware components.
 * @details        This service is a non reentrant function used for driver initialization.
 *        The  Initialization function  shall initialize  all relevant  registers of  the configured
 *        hardware with the  values of the  structure referenced by  the parameter ConfigPtr.
 *        If  the  hardware  allows  for   only  one  usage   of  the  register,   the  driver module
 *        implementing that functionality is responsible for initializing the register.
 *        The initialization function of this module shall always have a pointer as a parameter, even
 *        though for Variant PC no configuration set shall be given.
 *        Instead a NULL pointer shall be passed to the initialization function.
 *
 * @param[in]         ConfigPtr        Pointer to a selected configuration structure.
 *
 * @return             void
 * @api
 *
 *
 */
/* @implements         Rm_Init_Activity */
void Rm_Init(Rm_ConfigType const *ConfigPtr)
{
#if (RM_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType valid;

    valid = Rm_ValidateGlobalCall(RM_INIT_ID_U8, RM_GLOBAL_INIT);
    Rm_abInitializedModules[RM_GLOBAL_INIT] = TRUE;
    if ((Std_ReturnType)E_OK == valid)
    {
        valid = Rm_ValidatePtrInitAndPartitionId(ConfigPtr);
        if ((Std_ReturnType)E_OK == valid)
        {
#endif /*#if (RM_DEV_ERROR_DETECT == STD_ON)*/

#if (RM_PRECOMPILE_SUPPORT == STD_ON)
            Rm_pConfig = &Rm_Config;
            (void)ConfigPtr;
#else
            Rm_pConfig = ConfigPtr;
#endif

            /* Initialize Group1 IP */
            Rm_InitGroup1(Rm_pConfig);
#if (RM_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /*#if (RM_DEV_ERROR_DETECT == STD_ON)*/
}
#endif/*#if (STD_ON == RM_ENABLE_GLOBAL_INIT)*/


#if (RM_ENABLE_DMA_MUX == STD_ON)
#if (STD_ON != RM_ENABLE_GLOBAL_INIT)
/**
 * @brief          Initialize DmaMux module
 * @details
 *
 * @param[in]         ConfigPtr        Pointer to a selected configuration structure.
 * @param[out]      none
 *
 * @return          void
 *
 * @api
 */
void Rm_DmaMuxInit(Rm_ConfigType const *ConfigPtr)
{
#if (RM_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType valid;

    valid = Rm_ValidateGlobalCall(RM_INIT_ID_U8, RM_DMA_MUX_INIT);
    Rm_abInitializedModules[RM_DMA_MUX_INIT] = TRUE;

    if ((Std_ReturnType)E_OK == valid)
    {
        valid = Rm_ValidatePtrInitAndPartitionId(ConfigPtr);
        if ((Std_ReturnType)E_OK == valid)
        {
#endif /*#if (RM_DEV_ERROR_DETECT == STD_ON)*/

    if (NULL_PTR == Rm_pConfig)
    {
        #if (RM_PRECOMPILE_SUPPORT == STD_ON)
            Rm_pConfig = &Rm_Config;
            (void)ConfigPtr;
        #else
            Rm_pConfig = ConfigPtr;
        #endif
    }

    Rm_Ipw_Dma_Mux_Init(Rm_pConfig->Rm_pIpwConfig);

#if (RM_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /*#if (RM_DEV_ERROR_DETECT == STD_ON)*/
}
#endif/*#if (STD_ON != RM_ENABLE_GLOBAL_INIT) */
#endif /*#if (RM_ENABLE_DMA_MUX == STD_ON)*/

#if (RM_GET_VERSION_INFO_API == STD_ON)
/**
 * @brief   This service returns the version information of this module.
 * @details This  service is Non reentrant and returns the version information of this module.
 *          The version information includes:
 *          - Module Id
 *          - Vendor Id
 *          - Vendor specific version numbers
 *          If source code for caller and callee of this function is available this function should
 *          be realized as a macro. The macro should be defined in the modules header file.
 *
 * @param[out]    versioninfo      Pointer to location to store version info
 *
 * @return void
 *
 * @api
 *
 * */
/* @implements         Rm_GetVersionInfo_Activity */
void Rm_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (RM_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == versioninfo)
    {
        (void)Det_ReportError((uint16)RM_MODULE_ID, 0U, RM_GETVERSIONINFO_ID, RM_E_PARAM_POINTER);
    }
    else
#endif /* (RM_DEV_ERROR_DETECT == STD_ON) */
    {
        (versioninfo)->vendorID         = (uint16)RM_VENDOR_ID;
        (versioninfo)->moduleID         = (uint8)RM_MODULE_ID;
        (versioninfo)->sw_major_version = (uint8)RM_SW_MAJOR_VERSION;
        (versioninfo)->sw_minor_version = (uint8)RM_SW_MINOR_VERSION;
        (versioninfo)->sw_patch_version = (uint8)RM_SW_PATCH_VERSION;
    }
}

#endif  /* RM_GET_VERSION_INFO_API == STD_ON */

#define RM_STOP_SEC_CODE
#include "Rm_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
