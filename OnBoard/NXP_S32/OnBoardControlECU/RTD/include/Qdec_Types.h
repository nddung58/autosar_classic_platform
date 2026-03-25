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

#ifndef QDEC_TYPES_H
#define QDEC_TYPES_H

/**
*     @file       Qdec_Types.h
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
#include "Std_Types.h"
#include "CDD_Qdec_Cfg.h"
#include "Qdec_Ipw_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QDEC_TYPES_VENDOR_ID                          43
#define QDEC_TYPES_AR_RELEASE_MAJOR_VERSION           4
#define QDEC_TYPES_AR_RELEASE_MINOR_VERSION           7
#define QDEC_TYPES_AR_RELEASE_REVISION_VERSION        0
#define QDEC_TYPES_SW_MAJOR_VERSION                   3
#define QDEC_TYPES_SW_MINOR_VERSION                   0
#define QDEC_TYPES_SW_PATCH_VERSION                   0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Std_Types.h are of the same AUTOSAR version */
    #if ((QDEC_TYPES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (QDEC_TYPES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of Qdec_Types.h and Std_Types.h are different."
    #endif
#endif

/* Check if header file and Qdec_Cfg header file are of the same vendor */
#if (QDEC_TYPES_VENDOR_ID != CDD_QDEC_CFG_VENDOR_ID)
#error "Qdec_Types.h and CDD_Qdec_Cfg.h have different vendor IDs"
#endif
/* Check if header file and Qdec_Cfg header file are of the same Autosar version */
#if ((QDEC_TYPES_AR_RELEASE_MAJOR_VERSION != CDD_QDEC_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (QDEC_TYPES_AR_RELEASE_MINOR_VERSION != CDD_QDEC_CFG_AR_RELEASE_MINOR_VERSION) || \
     (QDEC_TYPES_AR_RELEASE_REVISION_VERSION != CDD_QDEC_CFG_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of Qdec_Types.h and CDD_Qdec_Cfg.h are different"
#endif
/* Check if header file and Qdec_Cfg header file are of the same Software Version */
#if ((QDEC_TYPES_SW_MAJOR_VERSION != CDD_QDEC_CFG_SW_MAJOR_VERSION) || \
     (QDEC_TYPES_SW_MINOR_VERSION != CDD_QDEC_CFG_SW_MINOR_VERSION) || \
     (QDEC_TYPES_SW_PATCH_VERSION != CDD_QDEC_CFG_SW_PATCH_VERSION))
#error "Software Version Numbers of Qdec_Types.h and CDD_Qdec_Cfg.h are different"
#endif

/* Check if header file and Qdec_Ipw_Types header file are of the same vendor */
#if (QDEC_TYPES_VENDOR_ID != QDEC_IPW_TYPES_VENDOR_ID)
#error "Qdec_Types.h and Qdec_Ipw_Types.h have different vendor IDs"
#endif
/* Check if header file and Qdec_Ipw_Types header file are of the same Autosar version */
#if ((QDEC_TYPES_AR_RELEASE_MAJOR_VERSION != QDEC_IPW_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (QDEC_TYPES_AR_RELEASE_MINOR_VERSION != QDEC_IPW_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (QDEC_TYPES_AR_RELEASE_REVISION_VERSION != QDEC_IPW_TYPES_AR_RELEASE_REVISION_VERSION))
#error "Autosar Version Numbers of Qdec_Types.h and Qdec_Ipw_Types.h are different"
#endif
/* Check if header file and Qdec_Ipw_Types header file are of the same Software Version */
#if ((QDEC_TYPES_SW_MAJOR_VERSION != QDEC_IPW_TYPES_SW_MAJOR_VERSION) || \
     (QDEC_TYPES_SW_MINOR_VERSION != QDEC_IPW_TYPES_SW_MINOR_VERSION) || \
     (QDEC_TYPES_SW_PATCH_VERSION != QDEC_IPW_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of Qdec_Types.h and Qdec_Ipw_Types.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/
/**
* @brief    Encoding mode used in the Quadrature Decoder Mode.
*/
typedef enum
{
  MODE_NOT_INITIALIZED       = 0x00U,  /**< driver is not initialized */
  MODE_PHASE_ENCODE          = 0x01U,  /**< Phase A and phase B encoding mode */
  MODE_COUNT_AND_DIR_ENCODE  = 0x02U   /**< Count and direction encoding mode */
} Qdec_EncodingModeType;

/**
* @brief    Quadrature phase polarities, normal or inverted polarity
*/
typedef enum
{
  PHASE_NORMAL = 0x00U,  /**< Phase input signal is not inverted before identifying
                          *   the rising and falling edges of this signal */
  PHASE_INVERT = 0x01U   /**< Phase input signal is inverted before identifying
                          *   the rising and falling edges of this signal */
} Qdec_PhasePolarityType;

#if (QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief      Prescaler type
* @details    This enum specifies the possible types of prescallers used to configure base-clock timers
*
*/
typedef enum
{
    /** @brief Selected value is the default/primary prescaler */
    QDEC_NORMAL_PRESCALER = 0U,
    /** @brief Selected value is the alternative configured prescaler */
    QDEC_ALTERNATIVE_PRESCALER
} Qdec_SelectPrescalerType;
#endif
/**
* @brief    Qdec counter state type
*/
typedef enum
{
    /** When the counting starts again to count */
    QDEC_RESUME_COUNTER = 0U,
    /** When counting is paused */
    QDEC_PAUSE_COUNTER
} Qdec_CounterStateType;

/**
* @brief    Qdec mode type include: QDEC_MODE_NORMAL and QDEC_MODE_SLEEP
*/
typedef enum
{
    QDEC_MODE_NORMAL = 0U,      /**< @brief Normal operation, all used interrupts are enabled
                                 *          according to the notification requests. */
    QDEC_MODE_SLEEP              /**< @brief Reduced power operation. */
} Qdec_ModeType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief    Quadrature decode state (counter value and flags)
*/
typedef struct
{
  uint32  mCounter;           /**< Counter value */
  boolean mTimerOverflow;     /**< True if timer overflow occurred, False otherwise */
  boolean mTimerOverflowDir;  /**< Timer Overflow Direction:
                               *   False if there was a counter decrement and counter changes from its minimum value to its maximum value,
                               *   True if there was a counter increment and counter changes from its maximum value to its minimum value */
  boolean mCountDir;          /**< Counter Direction in QDEC mode:
                               *   False if counting direction is decreasing (counter decrement),
                               *   True if counting direction is increasing (counter increment) */
  boolean mOverRun;           /**< True if overrun has occurred, False otherwise */
  boolean mMatchEv;           /**< True if a match event in the comparators occurred, False otherwise */
} Qdec_StateType;

/**
* @brief    Quadrature decoder channel parameters
*/
typedef struct
{
  boolean mEnPhaseFilter;                 /**< Enables the filter for the quadrature decoder phase A,B inputs
                                           *   False: disable phase filter,
                                           *   True : enable phase filter */
  uint8 mPhaseFilterVal;                  /**< Filter value (if input filter is enabled) */
  Qdec_PhasePolarityType mPhasePolarity;  /**< Phase polarity */
} Qdec_PhaseParamsType;

#if (QDEC_NOTIFICATION_SUPPORTED == STD_ON)
/**
* @brief        Instance notification typedef
*
*/
typedef void (*Qdec_NotificationType)(void);
#endif /* QDEC_NOTIFICATION_SUPPORTED */

/**
* @brief    Quadrature instance configuration
*/
typedef struct
{
  Qdec_EncodingModeType mEncMode;     /**< MODE_PHASE_ENCODE or MODE_COUNT_AND_DIR_ENCODE */
  uint16                mMinCntVal;   /**< Minimum counter value */
  uint16                mMaxCntVal;   /**< Maximum counter value */
  boolean               mEnTofIsr;    /**< True: Timer Overflow Interrupt is enabled,
                                       *   False: Timer Overflow Interrupt is disabled */
  Qdec_PhaseParamsType  mPhaseAConfig; /**< Configuration of input phase A */
  Qdec_PhaseParamsType  mPhaseBConfig; /**< Configuration of input phase B */
#if (QDEC_NOTIFICATION_SUPPORTED == STD_ON)
  Qdec_NotificationType pfInsNotification;
#endif /* QDEC_NOTIFICATION_SUPPORTED */
} Qdec_InstanceConfigType;

/**
* @brief    Qdec high level configuration structure
*/
typedef struct
{
  uint8                       PartitionIndex;              /**< Partition Index */
  uint8                       Instances;           /**< Number of QDEC instances used */
  const Qdec_InstanceConfigType    (*InstanceConfigType)[];  /**< Pointer to user configuration(HLD) */
  const Qdec_Ipw_ConfigType *Ipw_ConfigType;      /**< Pointer to wrapper layer */
} Qdec_ConfigType;

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

#endif  /* QDEC_TYPES_H */
