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
*     @file       CDD_Qdec.c
*
*     @addtogroup qdec Qdec Driver
*     @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
 *                                          INCLUDE FILES
 *  1) system and project includes
 *  2) needed interfaces from external units
 *  3) internal and external interfaces from this unit
==================================================================================================*/

#include "Mcal.h"
#include "CDD_Qdec.h"
#include "CDD_Qdec_Ipw.h"
#include "Qdec_EnvCfg.h"

/*==================================================================================================
*                                  SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define CDD_QDEC_VENDOR_ID_C                     43
#define CDD_QDEC_AR_RELEASE_MAJOR_VERSION_C      4
#define CDD_QDEC_AR_RELEASE_MINOR_VERSION_C      7
#define CDD_QDEC_AR_RELEASE_REVISION_VERSION_C   0
#define CDD_QDEC_SW_MAJOR_VERSION_C              3
#define CDD_QDEC_SW_MINOR_VERSION_C              0
#define CDD_QDEC_SW_PATCH_VERSION_C              0

/*==================================================================================================
 *                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Mcal header file are of the same Autosar version */
    #if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_QDEC_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of CDD_Qdec.c and Mcal.h are different"
    #endif
#endif

/* Check if source file and Qdec header file are of the same vendor */
#if (CDD_QDEC_VENDOR_ID_C != CDD_QDEC_VENDOR_ID)
    #error "CDD_Qdec.c and CDD_Qdec.h have different vendor IDs"
#endif
/* Check if source file and Qdec header file are of the same AutoSar version */
#if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION_C != CDD_QDEC_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_MINOR_VERSION_C != CDD_QDEC_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_REVISION_VERSION_C != CDD_QDEC_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of CDD_Qdec.c and CDD_Qdec.h are different"
#endif
/* Check if source file and Qdec header file are of the same Software version */
#if ((CDD_QDEC_SW_MAJOR_VERSION_C != CDD_QDEC_SW_MAJOR_VERSION) || \
     (CDD_QDEC_SW_MINOR_VERSION_C != CDD_QDEC_SW_MINOR_VERSION) || \
     (CDD_QDEC_SW_PATCH_VERSION_C != CDD_QDEC_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec.c and CDD_Qdec.h are different"
#endif

/* Check if source file and Qdec_Ipw header file are of the same vendor */
#if (CDD_QDEC_VENDOR_ID_C != CDD_QDEC_IPW_VENDOR_ID)
    #error "CDD_Qdec.c and CDD_Qdec_Ipw.h have different vendor IDs"
#endif
/* Check if source file and Qdec_Ipw header file are of the same AutoSar version */
#if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_MINOR_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_REVISION_VERSION_C != CDD_QDEC_IPW_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of CDD_Qdec.c and CDD_Qdec_Ipw.h are different"
#endif
/* Check if source file and Qdec_Ipw header file are of the same Software version */
#if ((CDD_QDEC_SW_MAJOR_VERSION_C != CDD_QDEC_IPW_SW_MAJOR_VERSION) || \
     (CDD_QDEC_SW_MINOR_VERSION_C != CDD_QDEC_IPW_SW_MINOR_VERSION) || \
     (CDD_QDEC_SW_PATCH_VERSION_C != CDD_QDEC_IPW_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec.c and CDD_Qdec_Ipw.h are different"
#endif

/* Check if source file and Qdec_EnvCfg header file are of the same vendor */
#if (CDD_QDEC_VENDOR_ID_C != QDEC_ENVCFG_VENDOR_ID)
    #error "CDD_Qdec.c and Qdec_EnvCfg.h have different vendor IDs"
#endif
/* Check if source file and Qdec_EnvCfg header file are of the same AutoSar version */
#if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION_C != QDEC_ENVCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_MINOR_VERSION_C != QDEC_ENVCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_REVISION_VERSION_C != QDEC_ENVCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of CDD_Qdec.c and Qdec_EnvCfg.h are different"
#endif
/* Check if source file and Qdec_EnvCfg header file are of the same Software version */
#if ((CDD_QDEC_SW_MAJOR_VERSION_C != QDEC_ENVCFG_SW_MAJOR_VERSION) || \
     (CDD_QDEC_SW_MINOR_VERSION_C != QDEC_ENVCFG_SW_MINOR_VERSION) || \
     (CDD_QDEC_SW_PATCH_VERSION_C != QDEC_ENVCFG_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec.c and Qdec_EnvCfg.h are different"
#endif

/*==================================================================================================
 *                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

#if ((QDEC_VALIDATE_GLOBAL_CALL == STD_ON) || (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON))

typedef enum
{
    QDEC_STATE_UNINIT = 0x00,
    QDEC_STATE_IDLE
} Qdec_eGlobalStateType;

#endif /* (QDEC_VALIDATE_GLOBAL_CALL == STD_ON) || (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON) */

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

#if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
    #define Qdec_GetUserId()    ((uint32)OsIf_GetUserId())
#else
    #define Qdec_GetUserId()    ((uint32)0UL)
#endif

/*==================================================================================================
 *                                        LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
 *                                        LOCAL VARIABLES
==================================================================================================*/

#define QDEC_START_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

#if ((QDEC_VALIDATE_GLOBAL_CALL == STD_ON) || (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON))
#if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
static Qdec_eGlobalStateType Qdec_GlobalState[QDEC_MAX_PARTITIONS] = {QDEC_STATE_UNINIT};
#else
static Qdec_eGlobalStateType Qdec_GlobalState[1] = {QDEC_STATE_UNINIT};
#endif
#endif /* ((QDEC_VALIDATE_GLOBAL_CALL == STD_ON) || (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)) */

#define QDEC_STOP_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

/*==================================================================================================
 *                                        GLOBAL CONSTANTS
==================================================================================================*/

#define QDEC_START_SEC_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

#if (STD_ON == QDEC_PRECOMPILE_SUPPORT)
    #if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
        extern const Qdec_ConfigType * const Qdec_Config[QDEC_MAX_PARTITIONS];
    #else  /* (QDEC_MULTIPARTITION_ENABLED == STD_ON) */
        extern const Qdec_ConfigType Qdec_Config;
    #endif /* (QDEC_MULTIPARTITION_ENABLED == STD_ON) */
#endif /*STD_ON == QDEC_PRECOMPILE_SUPPORT*/

#define QDEC_STOP_SEC_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

/*==================================================================================================
 *                                        GLOBAL VARIABLES
==================================================================================================*/

#define QDEC_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

#if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
static const Qdec_ConfigType *Qdec_apxConfig[QDEC_MAX_PARTITIONS];
#else
static const Qdec_ConfigType *Qdec_apxConfig[1U];
#endif /* QDEC_MULTIPARTITION_ENABLED == STD_ON */

#define QDEC_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

/*==================================================================================================
 *                                    GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
#define QDEC_START_SEC_CODE
#include "Qdec_MemMap.h"
/*================================================================================================*/


/*==================================================================================================
 *                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#if (QDEC_VALIDATE_GLOBAL_CALL == STD_ON)

static inline Std_ReturnType Qdec_ValidateGlobalCall(uint8 u8ServiceId, uint32 userId);

static inline void Qdec_EndValidateGlobalCall(Std_ReturnType validation, uint8 u8ServiceId, uint32 userId);

#endif /* QDEC_VALIDATE_GLOBAL_CALL == STD_ON */

#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)

static inline Std_ReturnType Qdec_ValidateCallAndInstance(uint8 Instance, uint8 u8ServiceId, uint32 userId);

#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */

#if (QDEC_VALIDATE_PARAMS == STD_ON)

static inline Std_ReturnType Qdec_ValidatePtrInit(uint32 userId, const Qdec_ConfigType * ConfigPtr);

static inline Std_ReturnType Qdec_ValidateMode(Qdec_ModeType mode);

#endif /* (QDEC_VALIDATE_PARAMS == STD_ON) */

/*==================================================================================================
 *                                        LOCAL FUNCTIONS
==================================================================================================*/

#if (QDEC_VALIDATE_GLOBAL_CALL == STD_ON)
/**
* @brief       This function validates the global call
* @details     This service is a non reentrant function used for validating the calls for functions
*              that uses all the instances - Qdec_Init, Qdec_DeInit.
*
* @param[in]   u8ServiceId      The service id of the caller function
* @param[in]   userId           The number of current core ID
*
* @return      The validity of the function call
* @retval      E_OK             The function call is valid
* @retval      E_NOT_OK         The function call is invalid
* @implements  Qdec_ValidateGlobalCall_Activity
*/
static inline Std_ReturnType Qdec_ValidateGlobalCall(uint8 u8ServiceId, uint32 userId)
{
    Std_ReturnType valid = (Std_ReturnType)E_OK;

    if (QDEC_STATE_UNINIT == Qdec_GlobalState[userId])
    {
        if (QDEC_INIT_ID != u8ServiceId)
        {
            (void)Det_ReportError((uint16)CDD_QDEC_MODULE_ID, 0U, u8ServiceId, QDEC_E_UNINIT);
            valid = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        if (QDEC_INIT_ID == u8ServiceId)
        {
            (void)Det_ReportError((uint16)CDD_QDEC_MODULE_ID, 0U, u8ServiceId, QDEC_E_ALREADY_INITIALIZED);
            valid = (Std_ReturnType)E_NOT_OK;
        }
    }
    return valid;
}
#endif /* QDEC_VALIDATE_GLOBAL_CALL == STD_ON */

/*================================================================================================*/
#if (QDEC_VALIDATE_GLOBAL_CALL == STD_ON)
/**
* @brief      This function ends the validation of the global call.
* @details    This service is a non reentrant function used for end the validation the calls for
*             functions that uses all the instances - Qdec_Init, Qdec_DeInit, Qdec_SetMode.
*
* @param[in]   u8ServiceId      The service id of the caller function
* @param[in]   validation       The function call was previously validated
* @param[in]   userId           The number of current core ID
*
* @return void
* @implements  Qdec_EndValidateGlobalCall_Activity
*/
static inline void Qdec_EndValidateGlobalCall(Std_ReturnType validation, uint8 u8ServiceId, uint32 userId)
{
    if ((Std_ReturnType)E_OK == validation)
    {
        if (QDEC_DEINIT_ID == u8ServiceId)
        {
            Qdec_GlobalState[userId] = QDEC_STATE_UNINIT;
        }
        else
        {
            Qdec_GlobalState[userId] = QDEC_STATE_IDLE;
        }
    }
}
#endif /* QDEC_VALIDATE_GLOBAL_CALL == STD_ON */

/*================================================================================================*/
#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
/**
* @brief       This function validates the call for a specific instance
* @details     This service is a non reentrant function on instance used for validating the calls
*              for functions that use one instance
*
* @param[in]   Instance         Logical number of the QDEC instance
* @param[in]   ModeMask         The modes that are valid for the specific instance
* @param[in]   u8ServiceId      The service id of the caller function
* @param[in]   userId           The number of current core ID
* @return      The validity of the function call
* @retval      E_OK      The function call is valid
* @retval      E_NOT_OK The function call is invalid
* @implements  Qdec_ValidateCallAndInstance_Activity
*/
static inline Std_ReturnType Qdec_ValidateCallAndInstance(uint8 Instance, uint8 u8ServiceId, uint32 userId)
{
    Std_ReturnType valid = (Std_ReturnType)E_NOT_OK;

    if (QDEC_STATE_UNINIT == Qdec_GlobalState[userId])
    {
        (void)Det_ReportError((uint16)CDD_QDEC_MODULE_ID, 0U, u8ServiceId, QDEC_E_UNINIT);
    }
    else
    {
        if(QDEC_MAX_INSTANCE <= Instance)
        {
            (void)Det_ReportError((uint16)CDD_QDEC_MODULE_ID, 0U, u8ServiceId, QDEC_E_PARAM_INSTANCE);
        }
        else
        {
            valid = (Std_ReturnType)E_OK;
        }
    }

    return valid;
}
#endif

/*================================================================================================*/
#if (QDEC_VALIDATE_PARAMS == STD_ON)

/**
* @brief       This function validate the initialization pointer.
*
* @param[in]   ConfigPtr   Pointer to a selected configuration structure.
*
* @return                  The validity of the function call
* @retval      E_OK        The function call is valid
* @retval      E_NOT_OK    The function call is invalid
* @implements  Qdec_ValidatePtrInit_Activity
*/
static inline Std_ReturnType Qdec_ValidatePtrInit(uint32 userId, const Qdec_ConfigType * ConfigPtr)
{
    Std_ReturnType valid = (Std_ReturnType)E_OK;

#if (defined(QDEC_PRECOMPILE_SUPPORT) && (STD_ON == QDEC_PRECOMPILE_SUPPORT))
    if (NULL_PTR != ConfigPtr)
    {
#else
    if (NULL_PTR == ConfigPtr)
    {
#endif /*QDEC_PRECOMPILE_SUPPORT*/
        (void)Det_ReportError((uint16)CDD_QDEC_MODULE_ID, 0U, QDEC_INIT_ID, QDEC_E_INIT_FAILED);
        valid = (Std_ReturnType)E_NOT_OK;
    }
#if (STD_OFF == QDEC_PRECOMPILE_SUPPORT)
#if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
    else if (userId != ConfigPtr->PartitionIndex)
    {
        (void)Det_ReportError((uint16) CDD_QDEC_MODULE_ID, 0U, QDEC_INIT_ID, QDEC_E_PARAM_CONFIG);
        valid = (Std_ReturnType)E_NOT_OK;
    }
#endif /*QDEC_MULTIPARTITION_ENABLED*/
    else
    {
        (void)userId;
        /* Do nothing */
    }
#else
    else
    {
#if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
        if (NULL_PTR == Qdec_Config[userId])
        {
            /* Avoid compiler warning */
            (void)userId;
            (void)Det_ReportError((uint16) CDD_QDEC_MODULE_ID, 0U, QDEC_INIT_ID, QDEC_E_INIT_FAILED);
            valid = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* Do nothing */
        }
#endif /*QDEC_MULTIPARTITION_ENABLED*/

        (void)userId;
        /* Do nothing */
    }
#endif /*STD_OFF == QDEC_PRECOMPILE_SUPPORT*/
    return valid;
}

/*================================================================================================*/
/**
 * @brief       This function validate the mode that will be set in the driver.
 *
 * @param[in]   mode        Specifies the operation mode
 *
 * @return                  The validity of the function call
 * @retval      E_OK        The function call is valid
 * @retval      E_NOT_OK    The function call is invalid
 * @implements  Qdec_ValidateMode_Activity
 * */
static inline Std_ReturnType Qdec_ValidateMode(Qdec_ModeType mode)
{
    Std_ReturnType valid =  (Std_ReturnType)E_NOT_OK;

    if ((QDEC_MODE_SLEEP != mode) && (QDEC_MODE_NORMAL != mode))
    {
        (void)Det_ReportError((uint16)CDD_QDEC_MODULE_ID, 0U, QDEC_SETMODE_ID, QDEC_E_PARAM_MODE);
    }
    else
    {
        valid = (Std_ReturnType)E_OK;
    }
    return valid;
}

#endif /* (QDEC_VALIDATE_PARAMS == STD_ON)*/

/*==================================================================================================
 *                                        GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief     This function it is used to intitialize a QDEC instance.
* @details   This function activates your Quadrature Decoder Mode on the selected module.
*
* @param[in] Config - Qdec configuration structure.
* @return    void
*
* @pre       None.
*
* @implements     Qdec_Init_Activity
*/
void Qdec_Init(const Qdec_ConfigType *Config)
{
    uint32 userId = (uint32)Qdec_GetUserId();
#if (QDEC_VALIDATE_GLOBAL_CALL == STD_ON) || (QDEC_VALIDATE_PARAMS == STD_ON)
    Std_ReturnType valid;
#endif
#if (QDEC_VALIDATE_GLOBAL_CALL == STD_ON)
    valid = Qdec_ValidateGlobalCall(QDEC_INIT_ID, userId);
    if ((Std_ReturnType)E_OK == valid)
    {
#endif /* (QDEC_VALIDATE_GLOBAL_CALL == STD_ON */
#if (QDEC_VALIDATE_PARAMS == STD_ON)
        valid = Qdec_ValidatePtrInit(userId ,Config);
        if ((Std_ReturnType)E_OK == valid)
        {
#endif /* (QDEC_VALIDATE_PARAMS == STD_ON) */

#if (STD_ON == QDEC_PRECOMPILE_SUPPORT)
#if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
            Qdec_apxConfig[userId] = Qdec_Config[userId];
#else /* QDEC_MULTIPARTITION_ENABLED == STD_OFF */
            Qdec_apxConfig[0] = &Qdec_Config;
#endif /* QDEC_MULTIPARTITION_ENABLED */
            (void)Config;
#else
            Qdec_apxConfig[userId] = Config;
#endif /*STD_ON == QDEC_PRECOMPILE_SUPPORT*/

            Qdec_Ipw_Init((Qdec_apxConfig[userId]->Instances), (Qdec_apxConfig[userId]->Ipw_ConfigType));

#if (QDEC_VALIDATE_PARAMS == STD_ON)
        }
#endif
#if (STD_ON == QDEC_VALIDATE_GLOBAL_CALL)
    }
    Qdec_EndValidateGlobalCall(valid, QDEC_INIT_ID, userId);
#endif
}

/*================================================================================================*/
#if (QDEC_DEINIT_API == STD_ON)
/**
* @brief     This function it is used to disable QDEC Mode.
* @details   This function disable your Quadrature Decoder Mode on the selected module.
*
* @return    void
*
* @pre       None.
*
* @implements     Qdec_DeInit_Activity
*/
void Qdec_DeInit(void)
{
    uint32 userId = (uint32)Qdec_GetUserId();
#if (QDEC_VALIDATE_GLOBAL_CALL == STD_ON)
    Std_ReturnType valid = Qdec_ValidateGlobalCall(QDEC_DEINIT_ID, userId);
    if ((Std_ReturnType)E_OK == valid)
    {
#endif /* QDEC_VALIDATE_GLOBAL_CALL == STD_ON */

        Qdec_Ipw_DeInit(Qdec_apxConfig[userId]->Instances, Qdec_apxConfig[userId]->Ipw_ConfigType);
        Qdec_apxConfig[userId] = NULL_PTR;
#if (QDEC_VALIDATE_GLOBAL_CALL == STD_ON)
    }
    Qdec_EndValidateGlobalCall(valid, QDEC_DEINIT_ID, userId);
#endif /* QDEC_VALIDATE_GLOBAL_CALL == STD_ON */
}
#endif /* QDEC_DEINIT_API == STD_ON */

/*================================================================================================*/
/**
* @brief     Return the current quadrature decoder state (counter value and flags).
* @details   This function get the current quadrature decoder state (counter value and flags).
*
* @param[in] module - Name of your QDEC instance.
*
* @return    Qdec_StateType
*
* @pre       None.
*
* @implements     Qdec_GetState_Activity
*/
Qdec_StateType Qdec_GetState(const uint8 module)
{
    Qdec_StateType InstanceState = {0x0U, FALSE, FALSE, FALSE, FALSE, FALSE};
    uint32 userId = (uint32)Qdec_GetUserId();

#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    if((Std_ReturnType)E_OK == Qdec_ValidateCallAndInstance(module, QDEC_GETSTATE_ID, userId))
    {
#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */
        Qdec_Ipw_State IpwState = Qdec_Ipw_GetState(module, Qdec_apxConfig[userId]->Ipw_ConfigType);
        InstanceState.mCounter          = IpwState.Counter;
        InstanceState.mTimerOverflow    = IpwState.TimerOverflow;
        InstanceState.mTimerOverflowDir = IpwState.TimerOverflowDir;
        InstanceState.mCountDir         = IpwState.CountDir;
#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    }
#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */
    return InstanceState;
}

/*================================================================================================*/
#if (QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief        Implementation specific function to change the peripheral clock frequency.
* @details      This function is useful to set the prescalers that divide the QDEC channels
*               clock frequency.
*
* @param[in]    selectPrescaler - selectPrescaler type
* @return       void
*
* @implements   Qdec_SetClockMode_Activity
*
*/
void Qdec_SetClockMode(Qdec_SelectPrescalerType selectPrescaler)
{
    uint32 userId;
    uint8 index;

    /* Get core ID of current processor */
    userId = (uint32)Qdec_GetUserId();

#if (STD_ON == QDEC_VALIDATE_GLOBAL_CALL)
    Std_ReturnType valid = Qdec_ValidateGlobalCall(QDEC_SET_CLOCK_MODE_ID, userId);
    if((Std_ReturnType)E_OK == valid)
    {
#endif
        for (index = 0; index < Qdec_apxConfig[userId]->Instances; index++)
        {
            Qdec_Ipw_SetClockMode(Qdec_apxConfig[userId]->Ipw_ConfigType, Qdec_apxConfig[userId]->Ipw_ConfigType->Logic2HwMap[index].IpInstance, selectPrescaler);
        }
#if (STD_ON == QDEC_VALIDATE_GLOBAL_CALL)
    }
    Qdec_EndValidateGlobalCall(valid, QDEC_SET_CLOCK_MODE_ID, userId);
#endif /* STD_ON == QDEC_VALIDATE_GLOBAL_CALL */
}
#endif /* QDEC_SET_CLOCK_MODE_API */

/*================================================================================================*/
/**
* @brief     This function will set the state of counter
* @details   This function will set the state of counter in 2 states:
*               - PAUSE     when counting is paused.
*               - RESUME    when the counting starts again to count.
*
* @param[in] module         Name of your QDEC instance.
* @param[in] counterState   State of counter.
* @return    void
*
* @pre       None.
*
* @implements     Qdec_CounterState_Activity
*/
void Qdec_CounterState(const uint8 module, Qdec_CounterStateType counterState)
{
    static Qdec_CounterStateType Qdec_CurrentCounterState = QDEC_RESUME_COUNTER;
    uint32 userId = (uint32)Qdec_GetUserId();

#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    if((Std_ReturnType)E_OK == Qdec_ValidateCallAndInstance(module, QDEC_COUNTERSTATE_ID, userId))
    {
#endif
        if (Qdec_CurrentCounterState != counterState)
        {
            Qdec_Ipw_CounterState(module, (Qdec_apxConfig[userId]->Ipw_ConfigType));
            /* Hold provided counterState */
            Qdec_CurrentCounterState = counterState;
        }
#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    }
#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */
}

/*================================================================================================*/
/**
* @brief     Reset state of module to default value.
*
* @param[in] module - Qdec instance ID.
* @return    void
*
* @pre       None.
*
* @implements     Qdec_ResetState_Activity
*/
void Qdec_ResetState(const uint8 module)
{
    uint32 userId = (uint32)Qdec_GetUserId();

#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    if((Std_ReturnType)E_OK == Qdec_ValidateCallAndInstance(module, QDEC_RESETSTATE_ID, userId))
    {
#endif
        Qdec_Ipw_ResetState(module, (Qdec_apxConfig[userId]->Ipw_ConfigType));
    #if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    }
#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */
}

/*================================================================================================*/
#if (QDEC_NOTIFICATION_SUPPORTED == STD_ON)
/**
* @brief            This function disables QDEC overflow notification.
*
* @implements       Qdec_DisableOverFlowNotification_Activity
*/
void Qdec_DisableOverFlowNotification(const uint8 module)
{
    uint32 userId = (uint32)Qdec_GetUserId();
#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    if((Std_ReturnType)E_OK == Qdec_ValidateCallAndInstance(module, QDEC_DISABLEOVERFLOWNOTIFICATION_ID, userId))
    {
#endif
        Qdec_Ipw_DisableOverFlowNotification(module, (Qdec_apxConfig[userId]->Ipw_ConfigType));
#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    }
#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */
}

/*================================================================================================*/
/**
* @brief            This function enables QDEC overflow notification.
*
* @implements       Qdec_EnableOverFlowNotification_Activity
*/
void Qdec_EnableOverFlowNotification(const uint8 module)
{
    uint32 userId = (uint32)Qdec_GetUserId();
#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    if((Std_ReturnType)E_OK == Qdec_ValidateCallAndInstance(module, QDEC_ENABLEOVERFLOWNOTIFICATION_ID, userId))
    {
#endif
        Qdec_Ipw_EnableOverFlowNotification(module, (Qdec_apxConfig[userId]->Ipw_ConfigType));
#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    }
#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */
}

#endif /* QDEC_NOTIFICATION_SUPPORTED == STD_ON */

/*================================================================================================*/
/**
* @brief     Set mode.
* @details   Normal operation, all used interrupts are enabled according to the notification requests. Reduced power operation.
*
* @param[in] module - Qdec instance ID.
* @param[in] mode - select QDEC_MODE_NORMAL or QDEC_MODE_SLEEP
* @return    void
*
* @pre       None.
*
* @implements     Qdec_SetMode_Activity
*/
void Qdec_SetMode(const uint8 module, Qdec_ModeType mode)
{
    static Qdec_ModeType Qdec_CurrentMode = QDEC_MODE_NORMAL;
    uint32 userId = (uint32)Qdec_GetUserId();
#if (QDEC_VALIDATE_PARAMS == STD_ON)
    Std_ReturnType valid;
#endif

#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    if((Std_ReturnType)E_OK == Qdec_ValidateCallAndInstance(module, QDEC_SETMODE_ID, userId))
    {
#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */

#if (QDEC_VALIDATE_PARAMS == STD_ON)
        valid = Qdec_ValidateMode(mode);
        if ((Std_ReturnType)E_OK == valid)
        {
#endif /* QDEC_VALIDATE_PARAMS == STD_ON */
            if  (Qdec_CurrentMode != mode)
            {
                Qdec_Ipw_SetMode(module, (Qdec_apxConfig[userId]->Ipw_ConfigType), mode);

                /* Update Qdec mode */
                Qdec_CurrentMode = mode;
            }
#if (QDEC_VALIDATE_PARAMS == STD_ON)
        }
#endif /* (QDEC_VALIDATE_PARAMS == STD_ON) */

#if (QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON)
    }
#endif /* QDEC_VALIDATE_CALL_AND_INSTANCE == STD_ON */
}

/*================================================================================================*/
#if (QDEC_NOTIFICATION_SUPPORTED == STD_ON)
/**
* @brief         Qdec_ReportEvents
*/
void Qdec_ReportEvents(uint8 HwInstance)
{
    Qdec_NotificationType lpfInsNotification;
    uint32 userId = (uint32)Qdec_GetUserId();

    if (Qdec_apxConfig[userId] != NULL_PTR)
    {
        /* Check that there is a logic channel associated with the Hw one */
        lpfInsNotification = (*(Qdec_apxConfig[userId]->InstanceConfigType))[HwInstance].pfInsNotification;

        /* Check that a notification is defined for the associated logic channel.
         *  This is a double check not necessarily needed because if notification were
         *  enabled in IP layer for the channel that generated the interrupt causing this notify to
         *  be called, it means that this channel cannot have a null notification, otherwise notification
         *  could not have been enabled  */
        if ((NULL_PTR != lpfInsNotification))
        {
            lpfInsNotification();
        }
    }
}
#endif /* QDEC_NOTIFICATION_SUPPORTED == STD_ON */

#define QDEC_STOP_SEC_CODE
#include "Qdec_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
