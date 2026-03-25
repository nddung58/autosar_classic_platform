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
#ifndef FTM_QDEC_IP_TYPES_H
#define FTM_QDEC_IP_TYPES_H

/**
*    @file       Ftm_Qdec_Ip_Types.h
*
*    @addtogroup ftm_qdec_ip Ftm_Qdec_Ip Driver
*    @{
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
#include "Ftm_Qdec_Ip_CfgDefines.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FTM_QDEC_IP_TYPES_VENDOR_ID                         43
#define FTM_QDEC_IP_TYPES_AR_RELEASE_MAJOR_VERSION          4
#define FTM_QDEC_IP_TYPES_AR_RELEASE_MINOR_VERSION          7
#define FTM_QDEC_IP_TYPES_AR_RELEASE_REVISION_VERSION       0
#define FTM_QDEC_IP_TYPES_SW_MAJOR_VERSION                  3
#define FTM_QDEC_IP_TYPES_SW_MINOR_VERSION                  0
#define FTM_QDEC_IP_TYPES_SW_PATCH_VERSION                  0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if header file and Ftm_Qdec_Ip_CfgDefines configuration header file are of the same vendor */
#if (FTM_QDEC_IP_TYPES_VENDOR_ID != FTM_QDEC_IP_CFGDEFINES_VENDOR_ID)
    #error "Ftm_Qdec_Ip_Types.h and Ftm_Qdec_Ip_CfgDefines.h have different vendor IDs"
#endif
    /* Check if header file and Ftm_Qdec_Ip_CfgDefines configuration header file are of the same Autosar version */
#if ((FTM_QDEC_IP_TYPES_AR_RELEASE_MAJOR_VERSION != FTM_QDEC_IP_CFGDEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_TYPES_AR_RELEASE_MINOR_VERSION != FTM_QDEC_IP_CFGDEFINES_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_TYPES_AR_RELEASE_REVISION_VERSION != FTM_QDEC_IP_CFGDEFINES_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Ftm_Qdec_Ip_Types.h and Ftm_Qdec_Ip_CfgDefines.h are different"
#endif
/* Check if header file and Ftm_Qdec_Ip_CfgDefines configuration header file are of the same Software version */
#if ((FTM_QDEC_IP_TYPES_SW_MAJOR_VERSION != FTM_QDEC_IP_CFGDEFINES_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_TYPES_SW_MINOR_VERSION != FTM_QDEC_IP_CFGDEFINES_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_TYPES_SW_PATCH_VERSION != FTM_QDEC_IP_CFGDEFINES_SW_PATCH_VERSION))
#error "Software Version Numbers of Ftm_Qdec_Ip_Types.h and Ftm_Qdec_Ip_CfgDefines.h are different"
#endif

/*==================================================================================================
*                                        DEFINES AND MACROS
==================================================================================================*/
#if (FTM_QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief Ftm register define used to configure counter clock source.
*/
#ifndef QDEC_FTM_CLOCK_SOURCE_SHIFT
#define QDEC_FTM_CLOCK_SOURCE_SHIFT         (6U)
#endif

#ifndef QDEC_FTM_CLOCK_DIV_SHIFT
#define QDEC_FTM_CLOCK_DIV_SHIFT            (3U)
#define QDEC_FTM_CLOCK_DIV_MASK_U8          (0x07U << QDEC_FTM_CLOCK_DIV_SHIFT)
#endif

#ifndef QDEC_FTM_ALT_CLOCK_DIV_SHIFT
#define QDEC_FTM_ALT_CLOCK_DIV_SHIFT        (5U)
#define QDEC_FTM_ALT_CLOCK_DIV_MASK_U8      (0x07U << QDEC_FTM_ALT_CLOCK_DIV_SHIFT)
#endif

#define FTM_SC_PS_DIV1_U32                  (0UL)
#define FTM_SC_PS_DIV2_U32                  (1UL)
#define FTM_SC_PS_DIV4_U32                  (2UL)
#define FTM_SC_PS_DIV8_U32                  (3UL)
#define FTM_SC_PS_DIV16_U32                 (4UL)
#define FTM_SC_PS_DIV32_U32                 (5UL)
#define FTM_SC_PS_DIV64_U32                 (6UL)
#define FTM_SC_PS_DIV128_U32                (7UL)
#endif

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/
/**
* @brief        FlexTimer Clock Source Selection
*/
typedef enum
{
    FTM_CLOCK_SOURCE_NONE           = 0x00U,    /**< None use clock for FTM  */
    FTM_CLOCK_SOURCE_SYSTEMCLK      = 0x01U,    /**< System clock            */
    FTM_CLOCK_SOURCE_FIXEDCLK       = 0x02U,    /**< Fixed clock             */
    FTM_CLOCK_SOURCE_EXTERNALCLK    = 0x03U     /**< External clock          */
} Ftm_Qdec_Ip_ClockSourceType;

/**
* @brief        FlexTimer Prescale Factor Selections bits (PS).
* @details      Selects one of 8 division factors for the clock source selected by CLKS.
*               The new prescaler factor affects the clock source on the next FTM input clock cycle
*               after the new value is updated into the register bits.
*               This field is write protected. It can be written only when MODE[WPDIS] = 1.
*                   000b - Divide by 1
*                   001b - Divide by 2
*                   010b - Divide by 4
*                   011b - Divide by 8
*                   100b - Divide by 16
*                   101b - Divide by 32
*                   110b - Divide by 64
*                   111b - Divide by 128
*/
typedef enum
{
    FTM_CLOCK_DIVID_BY_1    = 0x00U,    /**< Divide by 1   */
    FTM_CLOCK_DIVID_BY_2    = 0x01U,    /**< Divide by 2   */
    FTM_CLOCK_DIVID_BY_4    = 0x02U,    /**< Divide by 4   */
    FTM_CLOCK_DIVID_BY_8    = 0x03U,    /**< Divide by 8   */
    FTM_CLOCK_DIVID_BY_16   = 0x04U,    /**< Divide by 16  */
    FTM_CLOCK_DIVID_BY_32   = 0x05U,    /**< Divide by 32  */
    FTM_CLOCK_DIVID_BY_64   = 0x06U,    /**< Divide by 64  */
    FTM_CLOCK_DIVID_BY_128  = 0x07U     /**< Divide by 128 */
} Ftm_Qdec_Ip_ClockPrescType;

/**
* @brief        FlexTimer Filter Prescaler.
* @details      The bits FLTPS selects the clock prescaler used in the FTM filters.
*               Selects one of 16 division factors to affect channel input filters
*               and quadrature decoder phase A and B inputs filters.
*               Writing to the bits FLTPS has immediate effect.
*                   0000b - Divide by 1
*                   0001b - Divide by 2
*                   0010b - Divide by 3
*                   0011b - Divide by 4
*                   0100b - Divide by 5
*                   0101b - Divide by 6
*                   0110b - Divide by 7
*                   0111b - Divide by 8
*                   1000b - Divide by 9
*                   1001b - Divide by 10
*                   1010b - Divide by 11
*                   1011b - Divide by 12
*                   1100b - Divide by 13
*                   1101b - Divide by 14
*                   1110b - Divide by 15
*                   1111b - Divide by 16
*/
typedef enum
{
    FTM_CLOCK_FILTER_PRESCALER_DIV1   = 0x00U,    /**< Divide by 1  */
    FTM_CLOCK_FILTER_PRESCALER_DIV2   = 0x01U,    /**< Divide by 2  */
    FTM_CLOCK_FILTER_PRESCALER_DIV3   = 0x02U,    /**< Divide by 3  */
    FTM_CLOCK_FILTER_PRESCALER_DIV4   = 0x03U,    /**< Divide by 4  */
    FTM_CLOCK_FILTER_PRESCALER_DIV5   = 0x04U,    /**< Divide by 5  */
    FTM_CLOCK_FILTER_PRESCALER_DIV6   = 0x05U,    /**< Divide by 6  */
    FTM_CLOCK_FILTER_PRESCALER_DIV7   = 0x06U,    /**< Divide by 7  */
    FTM_CLOCK_FILTER_PRESCALER_DIV8   = 0x07U,    /**< Divide by 8  */
    FTM_CLOCK_FILTER_PRESCALER_DIV9   = 0x08U,    /**< Divide by 9  */
    FTM_CLOCK_FILTER_PRESCALER_DIV10  = 0x09U,    /**< Divide by 10 */
    FTM_CLOCK_FILTER_PRESCALER_DIV11  = 0x0AU,    /**< Divide by 11 */
    FTM_CLOCK_FILTER_PRESCALER_DIV12  = 0x0BU,    /**< Divide by 12 */
    FTM_CLOCK_FILTER_PRESCALER_DIV13  = 0x0CU,    /**< Divide by 13 */
    FTM_CLOCK_FILTER_PRESCALER_DIV14  = 0x0DU,    /**< Divide by 14 */
    FTM_CLOCK_FILTER_PRESCALER_DIV15  = 0x0EU,    /**< Divide by 15 */
    FTM_CLOCK_FILTER_PRESCALER_DIV16  = 0x0FU     /**< Divide by 16 */
} Ftm_Qdec_Ip_ClockFilterPrescType;

/**
* @brief        Encoding mode used by FTM in the QDEC mode.
*/
typedef enum
{
    FTM_MODE_PHASE_ENCODE          = 0x00U,  /**< Phase A and phase B encoding mode */
    FTM_MODE_COUNT_AND_DIR_ENCODE  = 0x01U   /**< Count and direction encoding mode */
} Ftm_Qdec_Ip_EncodingModeType;

/**
* @brief        Quadrature phase polarities, normal or inverted polarity
*/
typedef enum
{
    FTM_PHASE_NORMAL = 0x00U, /**< Phase input signal is not inverted before identifying
                                *   the rising and falling edges of this signal */
    FTM_PHASE_INVERT = 0x01U  /**< Phase input signal is inverted before identifying
                                *   the rising and falling edges of this signal */
} Ftm_Qdec_Ip_PhasePolarityType;

/**
* @brief    Qdec mode type include: QDEC_MODE_NORMAL and QDEC_MODE_SLEEP
*/
typedef enum
{
    FTM_QDEC_MODE_NORMAL = 0U,      /**< @brief Normal operation, all used interrupts are enabled
                                 *          according to the notification requests. */
    FTM_QDEC_MODE_SLEEP              /**< @brief Reduced power operation. */
} Ftm_ModeType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief      FTM - Register Layout Typedef
*/
typedef FTM_Type Ftm_Qdec_HwAddrType;

/** @brief Callback type for each instance. */
typedef void (*Ftm_Qdec_Ip_CallbackType)(uint8 callbackParam1);

/**
* @brief       Structure for notification
* @details     The structure used to notification
*/
typedef struct
{
    Ftm_Qdec_Ip_CallbackType functionCallback;
    uint8 callbackParam;
} Ftm_Qdec_Ip_CallbackCfgType;

/**
* @brief        Quadrature decoder channel parameters
*/
typedef struct
{
    boolean                       mEnPhaseFilter;  /**< Enables the filter for the quadrature decoder phase A,B inputs
                                                    *   False: disable phase filter,
                                                    *   True : enable phase filter */
    uint8                         mPhaseFilterVal; /**< Filter value (if input filter is enabled) */
    Ftm_Qdec_Ip_PhasePolarityType mPhasePolarity;  /**< Phase polarity */
} Ftm_Qdec_Ip_PhaseParamsType;

/**
* @brief        Quadrature configure structure
*/
typedef struct
{
    Ftm_Qdec_Ip_EncodingModeType        mEncMode;           /**< FTM_MODE_PHASE_ENCODE or FTM_MODE_COUNT_AND_DIR_ENCODE */
    uint16                              mMinCntVal;         /**< Minimum counter value */
    uint16                              mModCntVal;         /**< Maximum counter value */
    boolean                             mEnTofIsr;          /**< True: Timer Overflow Interrupt is enabled,
                                                          *  False: Timer Overflow Interrupt is disabled */
    Ftm_Qdec_Ip_PhaseParamsType         mPhaseAConfig;      /**< Configuration of input phase A */
    Ftm_Qdec_Ip_PhaseParamsType         mPhaseBConfig;      /**< Configuration of input phase B */
    Ftm_Qdec_Ip_CallbackCfgType         overflowCb;         /**< overflow callback */
#if (FTM_QDEC_SET_CLOCK_MODE_API == STD_ON)
    /** @brief Ftm channel parameters */
    /** Bits 7 .. 5 --> Alternate Prescaler configuration
        Bits 4 .. 0 --> Reserved for future use*/
    const uint8 AlternateCtrVal;
    /** @brief Ftm module parameters */
    /** Bits 7 .. 6   --> Clock source
        Bits 5 .. 3   --> Normal prescale
        Bit  2 .. 0   --> Reserved for future use*/
    const uint8 ModuleControlValue;
#endif
    Ftm_Qdec_Ip_ClockSourceType         eSourceClock;       /**< FlexTimer Clock Source */
    Ftm_Qdec_Ip_ClockFilterPrescType    clockFilterPs;      /**< FlexTimer Clock Filter Prescaler */
} Ftm_Qdec_Ip_ConfigType;

/**
* @brief        FTM Quadrature state (counter value and flags)
*/
typedef struct
{
    uint16  mCounter;           /**< FTM Counter value */
    boolean mTimerOverflow;     /**< True if timer overflow occurred, False otherwise */
    boolean mTimerOverflowDir;  /**< Timer Overflow Direction:
                                *   False if there was an FTM counter decrement and FTM counter changes from its minimum value to its maximum value,
                                *   True if there was an FTM counter increment and FTM counter changes from its maximum value to its minimum value */
    boolean mCountDir;          /**< FTM Counter Direction in QDEC mode:
                                *   False if counting direction is decreasing (counter decrement),
                                *   True if counting direction is increasing (counter increment) */
} Ftm_Qdec_Ip_StateType;

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define QDEC_START_SEC_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
#include "Qdec_MemMap.h"

/** @brief Quadrature ftm initialization state variable */
extern boolean gQdecFtmInitState;

#define QDEC_STOP_SEC_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
#include "Qdec_MemMap.h"

#define QDEC_START_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

/** @brief Array with notification handlers for all configurable instances */
extern Ftm_Qdec_Ip_CallbackCfgType Ftm_Qdec_Ip_pOverflowIrqCallback[FTM_INSTANCE_COUNT];

#define QDEC_STOP_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"
/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* FTM_QDEC_IP_TYPES_H */
