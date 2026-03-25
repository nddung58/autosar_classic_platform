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

#ifndef CDD_QDEC_H
#define CDD_QDEC_H

/**
*     @file       CDD_Qdec.h
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

#include "CDD_Qdec_Cfg.h"
#include "Qdec_Types.h"
#include "Qdec_Ipw_Types.h"

#if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
#include "OsIf.h"
#endif

#if (QDEC_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define CDD_QDEC_VENDOR_ID                          43
#if (QDEC_DEV_ERROR_DETECT == STD_ON)
#define CDD_QDEC_MODULE_ID                          255
#endif
#define CDD_QDEC_AR_RELEASE_MAJOR_VERSION           4
#define CDD_QDEC_AR_RELEASE_MINOR_VERSION           7
#define CDD_QDEC_AR_RELEASE_REVISION_VERSION        0
#define CDD_QDEC_SW_MAJOR_VERSION                   3
#define CDD_QDEC_SW_MINOR_VERSION                   0
#define CDD_QDEC_SW_PATCH_VERSION                   0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/* Check if header file and QDEC configuration header file are of the same vendor */
#if (CDD_QDEC_VENDOR_ID != CDD_QDEC_CFG_VENDOR_ID)
    #error "CDD_Qdec.h and CDD_Qdec_Cfg.h have different vendor IDs"
#endif
    /* Check if header file and QDEC configuration header file are of the same Autosar version */
#if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION != CDD_QDEC_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_MINOR_VERSION != CDD_QDEC_CFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_REVISION_VERSION != CDD_QDEC_CFG_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of CDD_Qdec.h and CDD_Qdec_Cfg.h are different"
#endif
/* Check if header file and QDEC configuration header file are of the same Software version */
#if ((CDD_QDEC_SW_MAJOR_VERSION != CDD_QDEC_CFG_SW_MAJOR_VERSION) || \
     (CDD_QDEC_SW_MINOR_VERSION != CDD_QDEC_CFG_SW_MINOR_VERSION) || \
     (CDD_QDEC_SW_PATCH_VERSION != CDD_QDEC_CFG_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec.h and CDD_Qdec_Cfg.h are different"
#endif

/* Check if header file and Qdec_Types header file are of the same vendor */
#if (CDD_QDEC_VENDOR_ID != QDEC_TYPES_VENDOR_ID)
#error "CDD_Qdec.h and Qdec_Types.h have different vendor IDs"
#endif
/* Check if header file and Qdec_Types header file are of the same Autosar version */
#if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION != QDEC_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_MINOR_VERSION != QDEC_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_REVISION_VERSION != QDEC_TYPES_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of Qdec.h and Qdec_Types.h are different"
#endif
/* Check if header file and Qdec_Types header file are of the same Software Version */
#if ((CDD_QDEC_SW_MAJOR_VERSION != QDEC_TYPES_SW_MAJOR_VERSION) || \
     (CDD_QDEC_SW_MINOR_VERSION != QDEC_TYPES_SW_MINOR_VERSION) || \
     (CDD_QDEC_SW_PATCH_VERSION != QDEC_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec.h and Qdec_Types.h are different"
#endif

/* Check if header file and Qdec_Ipw_Types header file are of the same vendor */
#if (CDD_QDEC_VENDOR_ID != QDEC_IPW_TYPES_VENDOR_ID)
#error "CDD_Qdec.h and Qdec_Ipw_Types.h have different vendor IDs"
#endif
/* Check if header file and Qdec_Ipw_Types header file are of the same Autosar version */
#if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION != QDEC_IPW_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_MINOR_VERSION != QDEC_IPW_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_QDEC_AR_RELEASE_REVISION_VERSION != QDEC_IPW_TYPES_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of Qdec.h and Qdec_Ipw_Types.h are different"
#endif
/* Check if header file and Qdec_Ipw_Types header file are of the same Software Version */
#if ((CDD_QDEC_SW_MAJOR_VERSION != QDEC_IPW_TYPES_SW_MAJOR_VERSION) || \
     (CDD_QDEC_SW_MINOR_VERSION != QDEC_IPW_TYPES_SW_MINOR_VERSION) || \
     (CDD_QDEC_SW_PATCH_VERSION != QDEC_IPW_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of CDD_Qdec.h and Qdec_Ipw_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if (QDEC_MULTIPARTITION_ENABLED == STD_ON)
        /* Check if header file and OsIf header file are of the same AutoSar version */
        #if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION != OSIF_AR_RELEASE_MAJOR_VERSION) || \
             (CDD_QDEC_AR_RELEASE_MINOR_VERSION != OSIF_AR_RELEASE_MINOR_VERSION))
            #error "AutoSar Version Numbers of CDD_Qdec.h and OsIf.h are different"
        #endif
    #endif /* QDEC_MULTIPARTITION_ENABLED == STD_ON */

    #if (QDEC_DEV_ERROR_DETECT == STD_ON)
        /* Check if header file and DET header file are of the same AutoSar version */
        #if ((CDD_QDEC_AR_RELEASE_MAJOR_VERSION != DET_AR_RELEASE_MAJOR_VERSION) || \
             (CDD_QDEC_AR_RELEASE_MINOR_VERSION != DET_AR_RELEASE_MINOR_VERSION))
            #error "AutoSar Version Numbers of CDD_Qdec.h and Det.h are different"
        #endif
    #endif /* QDEC_DEV_ERROR_DETECT == STD_ON */
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

#if (QDEC_DEV_ERROR_DETECT == STD_ON)
/**
* @brief   API service used with a value is not in range
* @implements Qdec_ErrorCodes_define
*/
#define QDEC_E_PARAM_CONFIG             ((uint8)0x0C)

/**
* @brief   API Qdec_Init service called with wrong parameter
* @implements Qdec_ErrorCodes_define
*/
#define QDEC_E_INIT_FAILED               ((uint8)0x0D)

/**
* @brief   API service used with an invalid channel identifier or channel was not configured for
*          the functionality of the calling API
* @implements Qdec_ErrorCodes_define
*/
#define QDEC_E_PARAM_INSTANCE             ((uint8)0x0B)

/**
* @brief   API service Qdec_SetMode used with an invalid mode
* @implements Qdec_ErrorCodes_define
*/
#define QDEC_E_PARAM_MODE               ((uint8)0x0F)

/**
* @brief   API service used without module initialization
* @implements Qdec_ErrorCodes_define
*/
#define QDEC_E_UNINIT                    ((uint8)0x14)

/**
* @brief   API Qdec_Init service called when the QDEC driver and the Hardware
*          are already initialized
* @implements Qdec_ErrorCodes_define
*/
#define QDEC_E_ALREADY_INITIALIZED       ((uint8)0x17)


/**
* @brief API service ID for Qdec_Init function
* @details Parameters used when raising an error/exception
*/
#define QDEC_INIT_ID                     ((uint8)0x01)

/**
* @brief API service ID for Qdec_DeInit function
* @details Parameters used when raising an error/exception
*/
#define QDEC_DEINIT_ID                   ((uint8)0x02)

/**
* @brief API service ID for Qdec_GetState function
* @details Parameters used when raising an error/exception
*/
#define QDEC_GETSTATE_ID                  ((uint8)0x03)

/**
* @brief API service ID for Qdec_SetClockMode function
* @details Parameters used when raising an error/exception
*/
#define QDEC_SET_CLOCK_MODE_ID            ((uint8)0x04)

/**
* @brief API service ID for Qdec_CounterState function
* @details Parameters used when raising an error/exception
*/
#define QDEC_COUNTERSTATE_ID              ((uint8)0x05)

/**
* @brief API service ID for Qdec_ResetState function
* @details Parameters used when raising an error/exception
*/
#define QDEC_RESETSTATE_ID                ((uint8)0x06)

/**
* @brief API service ID for Qdec_DisableOverFlowNotification function
* @details Parameters used when raising an error/exception
*/
#define QDEC_DISABLEOVERFLOWNOTIFICATION_ID     ((uint8)0x07)

/**
* @brief API service ID for Qdec_EnableOverFlowNotification function
* @details Parameters used when raising an error/exception
*/
#define QDEC_ENABLEOVERFLOWNOTIFICATION_ID      ((uint8)0x08)

/**
* @brief API service ID for Qdec_SetMode function
* @details Parameters used when raising an error/exception
*/
#define QDEC_SETMODE_ID                   ((uint8)0x09)

#endif /* QDEC_DEV_ERROR_DETECT == STD_ON */

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#if (STD_OFF == QDEC_PRECOMPILE_SUPPORT)
#define QDEC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

QDEC_CONFIG_EXT

#define QDEC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Qdec_MemMap.h"

#endif /*STD_OFF == QDEC_PRECOMPILE_SUPPORT*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#define QDEC_START_SEC_CODE
#include "Qdec_MemMap.h"

/**
* @brief     This function it is used to intitialize a QDEC instance.
* @details   This function activates your Quadrature Decoder Mode on the selected module.
*
* @param[in] Config - Qdec configuration structure.
*
* @return    void
*
* @pre       None.
*
*/
void Qdec_Init(const Qdec_ConfigType * Config);
/*================================================================================================*/
/**
* @brief     This function it is used to disable QDEC Mode.
* @details   This function disable your Quadrature Decoder Mode on the selected module.
*
*
* @return    void
*
* @pre       None.
*
*/
void Qdec_DeInit(void);
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
*/
Qdec_StateType Qdec_GetState(const uint8 module);
/*================================================================================================*/
#if (QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief        Implementation specific function to change the peripheral clock frequency.
* @details      This function is useful to set the prescalers that divide the QDEC instances
*               clock frequency.
*
* @param[in]    selectPrescaler   pre scaler setting ( NORMAL or ALTERNATE )
* @return       void
* @pre          Qdec_Init must be called before.
*
*/
void Qdec_SetClockMode(Qdec_SelectPrescalerType selectPrescaler);
#endif /* QDEC_SET_CLOCK_MODE_API == STD_ON */
/*================================================================================================*/
/**
* @brief     This function will set the state of counter
* @details   This function will set the state of counter in 2 states:
*               - PAUSE     when counting is paused.
*               - RESUME    when the counting starts again to count.
*
* @param[in] module         Name of your QDEC instance.
*
* @param[in] counterState   State of counter.
*
* @return    void
*
* @pre       None.
*
*/
void Qdec_CounterState(const uint8 module, Qdec_CounterStateType counterState);
/*================================================================================================*/
/**
* @brief     Reset state of module to default value.
*
* @param[in] module - Qdec instance ID.
*
* @return    void
*
* @pre       None.
*
*/
void Qdec_ResetState(const uint8 module);
/*================================================================================================*/
#if (QDEC_NOTIFICATION_SUPPORTED == STD_ON)
/**
* @brief            This function disables QDEC overflow notification.
*/
void Qdec_DisableOverFlowNotification(const uint8 module);
/*================================================================================================*/
/**
* @brief            This function disables QDEC overflow notification.
*/
void Qdec_EnableOverFlowNotification(const uint8 module);
#endif
/*================================================================================================*/
/**
* @brief     Set mode.
* @details   Normal operation, all used interrupts are enabled according to the notification requests. Reduced power operation.
*
* @param[in] module - Qdec instance ID.
*            mode - select QDEC_MODE_NORMAL or QDEC_MODE_SLEEP
*
* @return    void
*
* @pre       None.
*
*/
void Qdec_SetMode(const uint8 module, Qdec_ModeType mode);

#define QDEC_STOP_SEC_CODE
#include "Qdec_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* CDD_QDEC_H */
