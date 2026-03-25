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
*     @file       Ftm_Qdec_Ip.c
*
*     @addtogroup ftm_qdec_ip Ftm_Qdec_Ip Driver
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
#include "Ftm_Qdec_Ip.h"
#include "Ftm_Qdec_Ip_Irq.h"
#include "OsIf.h"
#include "SchM_Qdec.h"

#if(FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
#include "Devassert.h"
#endif

#if (STD_ON == FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT)
#define USER_MODE_REG_PROT_ENABLED  (FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT)
#include "RegLockMacros.h"
#endif

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FTM_QDEC_IP_VENDOR_ID_C                       43
#define FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION_C        4
#define FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION_C        7
#define FTM_QDEC_IP_AR_RELEASE_REVISION_VERSION_C     0
#define FTM_QDEC_IP_SW_MAJOR_VERSION_C                3
#define FTM_QDEC_IP_SW_MINOR_VERSION_C                0
#define FTM_QDEC_IP_SW_PATCH_VERSION_C                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Ftm_Qdec_Ip header file are of the same vendor */
#if (FTM_QDEC_IP_VENDOR_ID_C != FTM_QDEC_IP_VENDOR_ID)
    #error "Ftm_Qdec_Ip.c and Ftm_Qdec_Ip.h have different vendor IDs"
#endif
/* Check if source file and Ftm_Qdec_Ip header file are of the same AutoSar version */
#if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION_C != FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION_C != FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_AR_RELEASE_REVISION_VERSION_C != FTM_QDEC_IP_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Ftm_Qdec_Ip.c and Ftm_Qdec_Ip.h are different"
#endif
/* Check if source file and Ftm_Qdec_Ip header file are of the same Software version */
#if ((FTM_QDEC_IP_SW_MAJOR_VERSION_C != FTM_QDEC_IP_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_SW_MINOR_VERSION_C != FTM_QDEC_IP_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_SW_PATCH_VERSION_C != FTM_QDEC_IP_SW_PATCH_VERSION))
    #error "Software Version Numbers of Ftm_Qdec_Ip.c and Ftm_Qdec_Ip.h are different"
#endif

/* Check if source file and Ftm_Qdec_Ip_Irq header file are of the same vendor */
#if (FTM_QDEC_IP_VENDOR_ID_C != FTM_QDEC_IP_IRQ_VENDOR_ID)
    #error "Ftm_Qdec_Ip.c and Ftm_Qdec_Ip_Irq.h have different vendor IDs"
#endif
/* Check if source file and Ftm_Qdec_Ip_Irq header file are of the same AutoSar version */
#if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION_C != FTM_QDEC_IP_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION_C != FTM_QDEC_IP_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_AR_RELEASE_REVISION_VERSION_C != FTM_QDEC_IP_IRQ_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Ftm_Qdec_Ip.c and Ftm_Qdec_Ip_Irq.h are different"
#endif
/* Check if source file and Ftm_Qdec_Ip_Irq header file are of the same Software version */
#if ((FTM_QDEC_IP_SW_MAJOR_VERSION_C != FTM_QDEC_IP_IRQ_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_SW_MINOR_VERSION_C != FTM_QDEC_IP_IRQ_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_SW_PATCH_VERSION_C != FTM_QDEC_IP_IRQ_SW_PATCH_VERSION))
    #error "Software Version Numbers of Ftm_Qdec_Ip.c and Ftm_Qdec_Ip_Irq.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and OsIf.h are of the same AUTOSAR version */
    #if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION_C != OSIF_AR_RELEASE_MAJOR_VERSION) || \
         (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION_C != OSIF_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of Ftm_Qdec_Ip.c and OsIf.h are different."
    #endif

    /* Check if source file and SchM_Qdec.h are of the same AUTOSAR version */
    #if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION_C != SCHM_QDEC_AR_RELEASE_MAJOR_VERSION) || \
         (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION_C != SCHM_QDEC_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of Ftm_Qdec_Ip.c and SchM_Qdec.h are different."
    #endif

    #if(FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
        /* Check if source file and Devassert.h are of the same AUTOSAR version */
        #if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION_C != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
             (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION_C != DEVASSERT_AR_RELEASE_MINOR_VERSION))
            #error "AUTOSAR version numbers of Ftm_Qdec_Ip.c and Devassert.h are different."
        #endif
    #endif /* FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON */

    #if (FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT == STD_ON)
        /* Check if source file and RegLockMacros.h are of the same AUTOSAR version */
        #if ((FTM_QDEC_IP_AR_RELEASE_MAJOR_VERSION_C != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
             (FTM_QDEC_IP_AR_RELEASE_MINOR_VERSION_C != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
            #error "AUTOSAR version numbers of Ftm_Qdec_Ip.c and RegLockMacros.h are different."
        #endif
    #endif /* FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT == STD_ON */
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                         LOCAL MACROS
==================================================================================================*/
/**
* @brief FTM_SC - Read, modify and write to Status And Control (RW)
*/
#define FTM_RMW_SC(base, mask, value) (((base)->SC) = ((((base)->SC) & ~(mask)) | (value)))

/**
* @brief FTM_MODE -  Read, modify and write Counter Features Mode Selection (RW)
*/
#define FTM_RMW_MODE(base, mask, value) (((base)->MODE) = ((((base)->MODE) & ~(mask)) | (value)))

/**
* @brief FILTER -  Read, modify and write Filter (RW)
*/
#define FTM_RMW_FILTER(base, mask, value) (((base)->FILTER) = ((((base)->FILTER) & ~(mask)) | (value)))

/** @brief Channel number for CHAN0 */
#define CHAN0_IDX (0U)
/** @brief Channel number for CHAN1 */
#define CHAN1_IDX (1U)

#if (defined (MCAL_FTM_REG_PROT_AVAILABLE) && (STD_ON == FTM_QDEC_IP_ENABLE_USER_MODE_SUPPORT))
    #define Call_Ftm_Qdec_Ip_SetUserAccessAllowed(FtmBaseAddr)  OsIf_Trusted_Call1param(Ftm_Qdec_Ip_SetUserAccessAllowed,(FtmBaseAddr))
#else
    #define Call_Ftm_Qdec_Ip_SetUserAccessAllowed(FtmBaseAddr)
#endif
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
#define QDEC_START_SEC_CONST_UNSPECIFIED
#include "Qdec_MemMap.h"

/** @brief Array with base addresses for FTM instances available on platform. */
Ftm_Qdec_HwAddrType *const scpFtmBase[FTM_INSTANCE_COUNT] = IP_FTM_BASE_PTRS;

#define QDEC_STOP_SEC_CONST_UNSPECIFIED
#include "Qdec_MemMap.h"

#define QDEC_START_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"
/** @brief Array with notification handlers for all configurable instances */
Ftm_Qdec_Ip_CallbackCfgType Ftm_Qdec_Ip_pOverflowIrqCallback[FTM_INSTANCE_COUNT] = {{NULL_PTR,0}};

#define QDEC_STOP_SEC_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

#define QDEC_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

/** @brief Quadrature ftm configure structure  */
static const Ftm_Qdec_Ip_ConfigType *gFtmConfig;

#define QDEC_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Qdec_MemMap.h"

#define QDEC_START_SEC_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
#include "Qdec_MemMap.h"

/** @brief Quadrature ftm initialization state variable */
boolean gQdecFtmInitState;

#define QDEC_STOP_SEC_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
#include "Qdec_MemMap.h"
/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define QDEC_START_SEC_CODE
#include "Qdec_MemMap.h"

/**
* @brief        Enables or Disables the Quadrature Decoder Mode (set or clear the QUADEN bit).
*               In this mode, the phase A and B input signals control the FTM counter direction.
*               The QDEC mode has precedence over the other modes of FTM.
*               This field is write protected. It can be written only when MODE[WPDIS] = 1.
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aboEn State of channel quadrature decoder
*                   - False: QDEC mode is disabled
*                   - True : QDEC mode is enabled
*/
static inline void Ftm_Qdec_Ip_SetQdecModeEn(Ftm_Qdec_HwAddrType * const acpFtmBase, boolean aboEn);

/*=========================================================================================================*/
/**
* @brief        Get the state of QUADEN Flag.
*               QUADEN Indicates if the QDEC mode is enabled.
*
* @param[in]    acpcFtmBase The FTM base address pointer
*
* @return       The status of QUADEN Flag
*               - True : QDEC mode is enabled.
*               - False: QDEC mode is disabled
*/
static inline boolean Ftm_Qdec_Ip_GetQdecModeEn(const Ftm_Qdec_HwAddrType * const acpcFtmBase);

/*=========================================================================================================*/
/**
* @brief        Set the filter clock prescaler.
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
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aClockFilterPs The FTM peripheral clock pre-scale divider
*/
static inline void Ftm_Qdec_Ip_SetClockFilterPs(Ftm_Qdec_HwAddrType * const acpFtmBase, Ftm_Qdec_Ip_ClockFilterPrescType aClockFilterPs);

/*=========================================================================================================*/
/**
* @brief        Set the Prescale Factor Selections bits (PS).
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
*
* @Note:        In QDEC mode set FTM_CLOCK_DIVID_BY_1
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aClockPresc The FTM peripheral clock pre-scale divider
*/
static inline void Ftm_Qdec_Ip_SetClockPs(Ftm_Qdec_HwAddrType * const acpFtmBase, Ftm_Qdec_Ip_ClockPrescType aClockPresc);

/*==========================================================================================================================*/

/**
* @brief        Enables or disables the filter for the quadrature decoder phase A input.
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aboEn State of phase A input filter
*                   - True : Phase A input filter is enabled
*                   - False: Phase A input filter is disabled
*/
static inline void Ftm_Qdec_Ip_SetPhaseAFilter(Ftm_Qdec_HwAddrType * const acpFtmBase, boolean aboEn);

/*=========================================================================================================*/
/**
* @brief        Enables or disables the filter for the quadrature decoder phase B input.
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aboEn State of phase B input filter
*                   - True : Phase B input filter is enabled
*                   - False: Phase B input filter is disabled
*/
static inline void Ftm_Qdec_Ip_SetPhaseBFilter(Ftm_Qdec_HwAddrType * const acpFtmBase, boolean aboEn);

/*=========================================================================================================*/
/**
* @brief        Get the FTM Counter Direction in QDEC mode (QUADIR)
* @details      QUADIR bit indicates the counting direction.
*                   0b - Counting direction is decreasing (FTM counter decrement).
*                   1b - Counting direction is increasing (FTM counter increment).
*
* @param[in]    acpcFtmBase The FTM base address pointer
*
* @return       The counting direction
*                   - True: if counting direction is increasing (FTM counter increment)
*                   - False: if counting direction is decreasing (FTM counter decrement).
*/
static inline boolean Ftm_Qdec_Ip_GetCountDir(const Ftm_Qdec_HwAddrType * const acpcFtmBase);

/*=========================================================================================================*/
/**
* @brief        Get the Timer Overflow Direction in Quadrature Decoder Mode (TOFDIR flag).
* @details      TOFDIR flag Indicates if the TOF bit was set on the top or the bottom of counting.
*                   0b - TOF bit was set on the bottom of counting. There was an FTM counter decrement and FTM
*                        counter changes from its minimum value (CNTIN register) to its maximum value (MOD register).
*                   1b - TOF bit was set on the top of counting. There was an FTM counter increment and FTM
*                        counter changes from its maximum value (MOD register) to its minimum value (CNTIN register).
*
* @param[in]    acpcFtmBase The FTM base address pointer
*
* @return       The state of Timer Overflow Direction in QDEC mode
*                   - True : TOF bit was set on the top of counting
*                   - False: TOF bit was set on the bottom of counting
*/
static inline boolean Ftm_Qdec_Ip_GetTofDir(const Ftm_Qdec_HwAddrType * const acpcFtmBase);

/*=========================================================================================================*/
/**
* @brief        Clears the Timer Overflow Flag (TOF).
* @Note:        TOF is set by hardware when the FTM counter is up counting and it changes from value in the MOD register to value in the CNTIN register.
*               The TOF bit is cleared by reading the SC register while TOF is set and then writing a 0 to TOF bit.
*               Writing a 1 to TOF has no effect.
* @param[in]    acpcFtmBase The FTM base address pointer
*/
static inline void Ftm_Qdec_Ip_ClearTof(Ftm_Qdec_HwAddrType * const acpcFtmBase);

/*=========================================================================================================*/
/**
* @brief        Get the state of Timer Overflow Flag (TOF).
* @Note:        TOF is set by hardware when the FTM counter passes the value in the MOD register.
*               The TOF bit is cleared by reading the SC register while TOF is set and then writing a 0 to TOF bit.
*               Writing a 1 to TOF has no effect.
* @param[in]    acpcFtmBase The FTM base address pointer
*
* @return       the status of Timer Overflow Flag
*                   - True : FTM counter has overflowed
*                   - False: FTM counter has not overflowed
*/
static inline boolean Ftm_Qdec_Ip_GetTofState(const Ftm_Qdec_HwAddrType * const acpcFtmBase);

/*=========================================================================================================*/
/**
* @brief        Returns the FTM peripheral current counter value.
*
* @param[in]    acpcFtmBase The FTM base address pointer
*
* @return       The current FTM timer counter value
*/
static inline uint16 Ftm_Qdec_Ip_GetCounter(const Ftm_Qdec_HwAddrType * const acpcFtmBase);

/*=========================================================================================================*/
/**
* @brief        Enables or disables the FTM peripheral timer group.
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aboEn FTM mode selection
*                   - True : All registers including FTM-specific registers are available
*                   - False: Only the TPM-compatible registers are available
*/
static inline void Ftm_Qdec_Ip_EnableFtm(Ftm_Qdec_HwAddrType * const acpFtmBase, boolean aboEn);

/*=========================================================================================================*/
/**
* @brief        Sets the filter value for the inputs of channels.
* @details      Sets the filter value for the inputs of channels into Input Capture Filter Control register (FILTER).
*               The filter is disabled when the value is zero.
* @Note:        Channels 4, 5, 6 and 7 do not have an input filter
*               Writing to the FILTER register has immediate effect and must be done only when the channels 0, 1, 2, and 3 are not in input modes.
*               Failure to do this could result in a missing valid signal.
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    au8Channel The FTM peripheral channel number, only 0,1,2,3, channel 4, 5,6, 7 don't have
* @param[in]    au8Value Filter value to be set
*/
static inline void Ftm_Qdec_Ip_SetChnInputCaptureFilter(Ftm_Qdec_HwAddrType * const acpFtmBase, uint8 au8Channel, uint8 au8Value);

/*=========================================================================================================*/
#if(FTM_QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief   Set the Prescale Factor Selections bits (PS).
* @details Selects one of 8 division factors for the clock source selected by CLKS.
*          The new prescaler factor affects the clock source on the next FTM input clock cycle
*          after the new value is updated into the register bits.
*          This field is write protected. It can be written only when MODE[WPDIS] = 1.
*            000b - Divide by 1
*            001b - Divide by 2
*            010b - Divide by 4
*            011b - Divide by 8
*            100b - Divide by 16
*            101b - Divide by 32
*            110b - Divide by 64
*            111b - Divide by 128
*
* @param[in] acpFtmBase - the FTM base address pointer
* @param[in] ClockPresc The FTM peripheral clock pre-scale divider
*/
static inline void Ftm_Qdec_Ip_SetClockPrescaler(Ftm_Qdec_HwAddrType * const acpFtmBase, uint8 ClockPresc);
#endif

/*==================================================================================================
 *                                        LOCAL FUNCTIONS
==================================================================================================*/
/**
* @brief    Enables or Disables the Quadrature Decoder Mode (set or clear the QUADEN bit).
*/
static inline void Ftm_Qdec_Ip_SetQdecModeEn(Ftm_Qdec_HwAddrType * const acpFtmBase, boolean aboEn)
{
    if (aboEn)
    {
        ((acpFtmBase)->QDCTRL) |= (1UL << FTM_QDCTRL_QUADEN_SHIFT);
    }
    else
    {
        ((acpFtmBase)->QDCTRL) &= ~(1UL << FTM_QDCTRL_QUADEN_SHIFT);
    }
}

/*=========================================================================================================*/
/**
* @brief    Get the state of QUADEN Flag.
*/
static inline boolean Ftm_Qdec_Ip_GetQdecModeEn(const Ftm_Qdec_HwAddrType * const acpcFtmBase)
{
    return (acpcFtmBase->QDCTRL & FTM_QDCTRL_QUADEN_MASK) != 0U;
}

/*=========================================================================================================*/
/**
* @brief        Set the filter clock prescaler.
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aClockFilterPs The FTM peripheral clock pre-scale divider
*/
static inline void Ftm_Qdec_Ip_SetClockFilterPs(Ftm_Qdec_HwAddrType * const acpFtmBase, Ftm_Qdec_Ip_ClockFilterPrescType aClockFilterPs)
{
    FTM_RMW_SC(acpFtmBase, FTM_SC_FLTPS_MASK, FTM_SC_FLTPS(aClockFilterPs));
}

/*=========================================================================================================*/
/**
* @brief    Set the Prescale Factor Selections bits (PS).
*/
static inline void Ftm_Qdec_Ip_SetClockPs(Ftm_Qdec_HwAddrType * const acpFtmBase, Ftm_Qdec_Ip_ClockPrescType aClockPresc)
{
    FTM_RMW_SC(acpFtmBase, FTM_SC_PS_MASK, FTM_SC_PS((uint32)aClockPresc));
}

/*=========================================================================================================*/
/**
* @brief        Enables or disables the filter for the quadrature decoder phase A input.
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aboEn State of phase A input filter
*                   - True : Phase A input filter is enabled
*                   - False: Phase A input filter is disabled
*/
static inline void Ftm_Qdec_Ip_SetPhaseAFilter(Ftm_Qdec_HwAddrType * const acpFtmBase, boolean aboEn)
{
    if (aboEn)
    {
        ((acpFtmBase)->QDCTRL) |= (1UL << FTM_QDCTRL_PHAFLTREN_SHIFT);
    }
    else
    {
        ((acpFtmBase)->QDCTRL) &= ~(1UL << FTM_QDCTRL_PHAFLTREN_SHIFT);
    }
}

/*=========================================================================================================*/
/**
* @brief        Enables or disables the filter for the quadrature decoder phase B input.
*
* @param[in]    acpFtmBase The FTM base address pointer
* @param[in]    aboEn State of phase B input filter
*                   - True : Phase B input filter is enabled
*                   - False: Phase B input filter is disabled
*/
static inline void Ftm_Qdec_Ip_SetPhaseBFilter(Ftm_Qdec_HwAddrType * const acpFtmBase, boolean aboEn)
{
    if (aboEn)
    {
        ((acpFtmBase)->QDCTRL) |= (1UL << FTM_QDCTRL_PHBFLTREN_SHIFT);
    }
    else
    {
        ((acpFtmBase)->QDCTRL) &= ~(1UL << FTM_QDCTRL_PHBFLTREN_SHIFT);
    }
}

/*=========================================================================================================*/
/**
* @brief    Get the FTM Counter Direction in QDEC mode (QUADIR)
*/
static inline boolean Ftm_Qdec_Ip_GetCountDir(const Ftm_Qdec_HwAddrType * const acpcFtmBase)
{
    return (acpcFtmBase->QDCTRL & FTM_QDCTRL_QUADIR_MASK) != 0U;
}

/*=========================================================================================================*/
/**
* @brief    Get the Timer Overflow Direction in Quadrature Decoder Mode (TOFDIR flag).
*
*/
static inline boolean Ftm_Qdec_Ip_GetTofDir(const Ftm_Qdec_HwAddrType * const acpcFtmBase)
{
    return (acpcFtmBase->QDCTRL & FTM_QDCTRL_TOFDIR_MASK) != 0U;
}

/*=========================================================================================================*/
/**
* @brief        Clears the Timer Overflow Flag (TOF).
* @Note:        TOF is set by hardware when the FTM counter passes the value in the MOD register.
*               The TOF bit is cleared by reading the SC register while TOF is set and then writing a 0 to TOF bit.
*               Writing a 1 to TOF has no effect.
* @param[in]    acpcFtmBase The FTM base address pointer
*/
static inline void Ftm_Qdec_Ip_ClearTof(Ftm_Qdec_HwAddrType * const acpcFtmBase)
{
    FTM_RMW_SC(acpcFtmBase, FTM_SC_TOF_MASK, FTM_SC_TOF(0U));
#ifdef ERRATA_E9005
    /* Read-after-write sequence to guarantee required serialization of memory operations */
    acpcFtmBase->SC;
#endif
}

/*=========================================================================================================*/
/**
* @brief    Get the state of Timer Overflow Flag (TOF).
*/
static inline boolean Ftm_Qdec_Ip_GetTofState(const Ftm_Qdec_HwAddrType * const acpcFtmBase)
{
    return ((acpcFtmBase->SC & FTM_SC_TOF_MASK) >> FTM_SC_TOF_SHIFT) != 0U;
}

/*=========================================================================================================*/
/**
* @brief        Returns the FTM peripheral current counter value.
*
* @param[in]    acpcFtmBase The FTM base address pointer
*
* @return       The current FTM timer counter value
*/
static inline uint16 Ftm_Qdec_Ip_GetCounter(const Ftm_Qdec_HwAddrType * const acpcFtmBase)
{
    return (uint16)((((acpcFtmBase)->CNT) & FTM_CNT_COUNT_MASK) >> FTM_CNT_COUNT_SHIFT);
}

/*=========================================================================================================*/
/**
* @brief    Enables or disables the FTM peripheral timer group.
*/
static inline void Ftm_Qdec_Ip_EnableFtm(Ftm_Qdec_HwAddrType * const acpFtmBase, boolean aboEn)
{
    FTM_RMW_MODE(acpFtmBase, FTM_MODE_FTMEN_MASK, FTM_MODE_FTMEN(aboEn ? 1UL : 0UL));
}

/*=========================================================================================================*/
/**
* @brief        Sets the filter value for the inputs of channels.
*/
static inline void Ftm_Qdec_Ip_SetChnInputCaptureFilter(Ftm_Qdec_HwAddrType * const acpFtmBase, uint8 au8Channel, uint8 au8Value)
{
    switch (au8Channel)
    {
        case CHAN0_IDX:
            FTM_RMW_FILTER(acpFtmBase, FTM_FILTER_CH0FVAL_MASK, FTM_FILTER_CH0FVAL(au8Value));
        break;
        case CHAN1_IDX:
            FTM_RMW_FILTER(acpFtmBase, FTM_FILTER_CH1FVAL_MASK, FTM_FILTER_CH1FVAL(au8Value));
        break;
        default:
            /* Nothing to do */
        break;
    }
}

/*=========================================================================================================*/
#if(FTM_QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief   Set the Prescale Factor Selections bits (PS).
*
*/
static inline void Ftm_Qdec_Ip_SetClockPrescaler(Ftm_Qdec_HwAddrType * const acpFtmBase, uint8 ClockPresc)
{
    uint32 TmpMask = (acpFtmBase->SC & ~(FTM_SC_PS_MASK)) | FTM_SC_PS((uint32)ClockPresc);
    acpFtmBase->SC = TmpMask;
}
#endif

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief    Configures the quadrature mode and starts measurement
*
* @param    [in] module     FTM hardware instance number.
* @param    [in] config     Configuration structure(Quadrature Decoder Mode, polarity for both phases,
*                minimum and maximum value for the counter, filter configuration).
* @return   No return.
*
* @implements     Ftm_Qdec_Ip_Init_Activity
*/
void Ftm_Qdec_Ip_Init(uint8 module, const Ftm_Qdec_Ip_ConfigType * config)
{
    Ftm_Qdec_HwAddrType *lpFtmBase = scpFtmBase[module];

    /* Initialize for gFtmConfig */
    gFtmConfig = config;

    /* Update init state */
    gQdecFtmInitState = TRUE;

#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(NULL_PTR != config);
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif

    /* Enable register access from user mode, if enabled from configuration file */
    Call_Ftm_Qdec_Ip_SetUserAccessAllowed((uint32)scpFtmBase[module]);

    /* Disable Quadrature Decoder */
    Ftm_Qdec_Ip_SetQdecModeEn(lpFtmBase, FALSE);
    /* Disable the FTM counter */
    lpFtmBase->SC = (lpFtmBase->SC & (~FTM_SC_CLKS_MASK)) | FTM_SC_CLKS(FTM_CLOCK_SOURCE_NONE);
    /* Set the encoding mode used in the QDEC mode */
    lpFtmBase->QDCTRL = (lpFtmBase->QDCTRL & (~FTM_QDCTRL_QUADMODE_MASK)) | FTM_QDCTRL_QUADMODE(config->mEncMode);
    /* Set filter state for Phase A (enable/disable) */
    if(TRUE == config->mPhaseAConfig.mEnPhaseFilter)
    {
        /* Enable phase A input filter */
        Ftm_Qdec_Ip_SetPhaseAFilter(lpFtmBase, TRUE);
        /* Set Phase A filter value. */
        Ftm_Qdec_Ip_SetChnInputCaptureFilter(lpFtmBase, CHAN0_IDX, config->mPhaseAConfig.mPhaseFilterVal);
    }
    else
    {
        /* Disables phase A input filter */
        Ftm_Qdec_Ip_SetPhaseAFilter(lpFtmBase, FALSE);
        /* Set Phase A filter value to be 0. */
        Ftm_Qdec_Ip_SetChnInputCaptureFilter(lpFtmBase, CHAN0_IDX, 0U);
    }
    /* Set filter state for Phase B (enable/disable) */
    if(TRUE == config->mPhaseBConfig.mEnPhaseFilter)
    {
        /* Enable phase B input filter */
        Ftm_Qdec_Ip_SetPhaseBFilter(lpFtmBase, TRUE);
        /* Set Phase B filter value. */
        Ftm_Qdec_Ip_SetChnInputCaptureFilter(lpFtmBase, CHAN0_IDX, config->mPhaseBConfig.mPhaseFilterVal);
    }
    else
    {
        /* Disables phase B input filter */
        Ftm_Qdec_Ip_SetPhaseBFilter(lpFtmBase, FALSE);
        /* Set Phase B filter value to be 0. */
        Ftm_Qdec_Ip_SetChnInputCaptureFilter(lpFtmBase, CHAN1_IDX, 0U);
    }

    if (config->mPhaseAConfig.mEnPhaseFilter || config->mPhaseBConfig.mEnPhaseFilter)
    {
        /* Sets the FTM clock filter prescaler */
        Ftm_Qdec_Ip_SetClockFilterPs(lpFtmBase, config->clockFilterPs);
    }

    /* Set polarity for Phase A and Phase B */
    ((lpFtmBase)->QDCTRL) = (((lpFtmBase)->QDCTRL) & (~FTM_QDCTRL_PHAPOL_MASK)) | FTM_QDCTRL_PHAPOL((uint8)config->mPhaseAConfig.mPhasePolarity);
    ((lpFtmBase)->QDCTRL) = (((lpFtmBase)->QDCTRL) & (~FTM_QDCTRL_PHBPOL_MASK)) | FTM_QDCTRL_PHBPOL((uint8)config->mPhaseBConfig.mPhasePolarity);

    /* Configure the counter (Minimum and maximum value) */
    ((lpFtmBase)->CNTIN) = (((lpFtmBase)->CNTIN) & (~FTM_CNTIN_INIT_MASK)) | FTM_CNTIN_INIT(config->mMinCntVal);
    ((lpFtmBase)->MOD)   = (((lpFtmBase)->MOD)   & (~FTM_MOD_MOD_MASK))    | FTM_MOD_MOD(config->mModCntVal);
    ((lpFtmBase)->CNT)   = (((lpFtmBase)->CNT)   & (~FTM_CNT_COUNT_MASK))  | FTM_CNT_COUNT(config->mMinCntVal);

    /* Use FTM mode */
    Ftm_Qdec_Ip_EnableFtm(lpFtmBase,TRUE);

    /* Clear the timer overflow flag */
    Ftm_Qdec_Ip_ClearTof(lpFtmBase);
    /* Enable the timer overflow interrupt */
    ((lpFtmBase)->SC) = (((lpFtmBase)->SC) & (~FTM_SC_TOIE_MASK)) | FTM_SC_TOIE(config->mEnTofIsr ? 1UL : 0UL);

    /* Enable Quadrature decoder */
    Ftm_Qdec_Ip_SetQdecModeEn(lpFtmBase, TRUE);

    /* Select the FTM counter clock source */
    ((lpFtmBase)->SC) = (((lpFtmBase)->SC) & (~FTM_SC_PS_MASK))   | FTM_SC_PS(FTM_CLOCK_DIVID_BY_1);
    ((lpFtmBase)->SC) = (((lpFtmBase)->SC) & (~FTM_SC_CLKS_MASK)) | FTM_SC_CLKS(FTM_CLOCK_SOURCE_SYSTEMCLK);

    if (TRUE == config->mEnTofIsr)
    {
        Ftm_Qdec_Ip_pOverflowIrqCallback[module].functionCallback = config->overflowCb.functionCallback;
        Ftm_Qdec_Ip_pOverflowIrqCallback[module].callbackParam = config->overflowCb.callbackParam;
    }
}

/*=========================================================================================================*/
/**
* @brief    De-activates the Quadrature Decoder Mode.
*
* @param    [in] module     FTM hardware instance number.
* @return   No return.
*
* @implements   Ftm_Qdec_Ip_Deinit_Activity
*/
void Ftm_Qdec_Ip_Deinit(uint8 module)
{
#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif

    Ftm_Qdec_HwAddrType * lpFtmBase = scpFtmBase[module];
    boolean lboQdecEn = FALSE;

    lboQdecEn = (boolean)Ftm_Qdec_Ip_GetQdecModeEn(lpFtmBase);

    if (!lboQdecEn)
    {
        /* Quadrature Decoder is already disabled */
    }
    else
    {
        /* Disables phase A input filter */
        Ftm_Qdec_Ip_SetPhaseAFilter(lpFtmBase, FALSE);
        Ftm_Qdec_Ip_SetChnInputCaptureFilter(lpFtmBase, CHAN0_IDX, 0U);

        /* Disables phase B input filter */
        Ftm_Qdec_Ip_SetPhaseBFilter(lpFtmBase, FALSE);
        Ftm_Qdec_Ip_SetChnInputCaptureFilter(lpFtmBase, CHAN1_IDX, 0U);

        /* Disables clock filter prescaler */
        Ftm_Qdec_Ip_SetClockFilterPs(lpFtmBase, FTM_CLOCK_FILTER_PRESCALER_DIV1);

        /* Disables FTM mode */
        Ftm_Qdec_Ip_EnableFtm(lpFtmBase, FALSE);
        Ftm_Qdec_Ip_SetClockPs(lpFtmBase, FTM_CLOCK_DIVID_BY_1);

        /* Disable the FTM counter */
        lpFtmBase->SC = (lpFtmBase->SC & (~FTM_SC_CLKS_MASK)) | FTM_SC_CLKS(FTM_CLOCK_SOURCE_NONE);

        /* Reset counter to 0 */
        lpFtmBase->CNT = 0;

        /* Disable Quadrature decoder */
        Ftm_Qdec_Ip_SetQdecModeEn(lpFtmBase, FALSE);

#if (FTM_QDEC_NOTIFICATION_SUPPORTED == STD_ON)
        /* Disable OverFlow Notification */
        Ftm_Qdec_Ip_DisableOverFlowNotification(module);
#endif
        /* Clear the timer overflow flag */
        Ftm_Qdec_Ip_ClearTof(lpFtmBase);

        /* Update init state */
        gQdecFtmInitState = FALSE;
    }
}

/*=========================================================================================================*/
/**
* @brief    Return the current quadrature decoder state (counter value, timer overflow, TOF direction and counting direction flags)
*
* @param    [in] module     FTM hardware instance number.
* @return   Structure with the state of FTM module
*
* @implements   Ftm_Qdec_Ip_GetState_Activity
*/
Ftm_Qdec_Ip_StateType Ftm_Qdec_Ip_GetState(uint8 module)
{
#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif

    Ftm_Qdec_HwAddrType const * lpcFtmBase = scpFtmBase[module];
    Ftm_Qdec_Ip_StateType FtmState;

    /*enter critical section */
    SchM_Enter_Qdec_QDEC_EXCLUSIVE_AREA_01();

    FtmState.mCounter           = Ftm_Qdec_Ip_GetCounter(lpcFtmBase);
    FtmState.mTimerOverflow     = Ftm_Qdec_Ip_GetTofState(lpcFtmBase);
    FtmState.mTimerOverflowDir  = Ftm_Qdec_Ip_GetTofDir(lpcFtmBase);
    FtmState.mCountDir          = Ftm_Qdec_Ip_GetCountDir(lpcFtmBase);

    /*exit critical section*/
    SchM_Exit_Qdec_QDEC_EXCLUSIVE_AREA_01();

    return FtmState;
}

/*=========================================================================================================*/
#if(FTM_QDEC_SET_CLOCK_MODE_API == STD_ON)
/**
* @brief    The function changes the prescaler of FTM channel.
* @details  This function changes the value prescaler in SC registers
*
* @param[in]     pFtmIpConfig   Pointer to configuration structure of FTM channels
* @param[in]     prescalerValue   Prescaler type: normal or alternative
* @return   void
*
* @implements   Ftm_Qdec_Ip_SetClockMode_Activity
*/
void Ftm_Qdec_Ip_SetClockMode(const uint8 module, uint8 prescalerValue)
{
#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif
    /*enter critical section */
    SchM_Enter_Qdec_QDEC_EXCLUSIVE_AREA_02();

    Ftm_Qdec_Ip_SetClockPrescaler(scpFtmBase[module], prescalerValue);

    /*exit critical section*/
    SchM_Exit_Qdec_QDEC_EXCLUSIVE_AREA_02();
}
#endif

/*=========================================================================================================*/
/**
* @brief    Set state of counter
*
* @param    [in] module FTM hardware number.
* @return   void
*
* @implements   Ftm_Qdec_Ip_CounterState_Activity
*/
void Ftm_Qdec_Ip_CounterState(const uint8 module)
{
#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif
    Ftm_Qdec_HwAddrType *lpFtmBase = scpFtmBase[module];

    /*enter critical section */
    SchM_Enter_Qdec_QDEC_EXCLUSIVE_AREA_03();

    /* If write protection is enabled, then disable it. */
    if (0U != (lpFtmBase->FMS & FTM_FMS_WPEN_MASK))
    {
       /* Disable write protection */
       lpFtmBase->MODE |= FTM_MODE_WPDIS_MASK;
    }

    /* Toggle QUADEN bit */
    if (0U == (lpFtmBase->QDCTRL & FTM_QDCTRL_QUADEN_MASK))
    {
        /* Enable Quadrature Decoder */
        Ftm_Qdec_Ip_SetQdecModeEn(lpFtmBase, TRUE);
        /* Enable the FTM counter */
        lpFtmBase->SC = (lpFtmBase->SC & (~FTM_SC_CLKS_MASK)) | FTM_SC_CLKS(gFtmConfig->eSourceClock);
    }
    else
    {
        /* Disable Quadrature Decoder */
        Ftm_Qdec_Ip_SetQdecModeEn(lpFtmBase, FALSE);
        /* Disable the FTM counter */
        lpFtmBase->SC = (lpFtmBase->SC & (~FTM_SC_CLKS_MASK)) | FTM_SC_CLKS(FTM_CLOCK_SOURCE_NONE);
    }

    /*exit critical section*/
    SchM_Exit_Qdec_QDEC_EXCLUSIVE_AREA_03();
}

/*=========================================================================================================*/
/**
* @brief    Reset state of module to default value
*
* @param    [in] module FTM hardware number.
* @return   void
*
* @implements   Ftm_Qdec_Ip_ResetState_Activity
*/
void Ftm_Qdec_Ip_ResetState(const uint8 module)
{
#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif
    Ftm_Qdec_HwAddrType *lpFtmBase = scpFtmBase[module];

    /*enter critical section */
    SchM_Enter_Qdec_QDEC_EXCLUSIVE_AREA_04();

    /* Disable the FTM counter */
    lpFtmBase->SC = (lpFtmBase->SC & (~FTM_SC_CLKS_MASK)) | FTM_SC_CLKS(FTM_CLOCK_SOURCE_NONE);

    /* Set counter to default value */
    ((lpFtmBase)->CNT) = (uint16)((lpFtmBase)->CNTIN);

    /* Clear the timer overflow flag */
    Ftm_Qdec_Ip_ClearTof(lpFtmBase);

    /*exit critical section*/
    SchM_Exit_Qdec_QDEC_EXCLUSIVE_AREA_04();
}

/*=========================================================================================================*/
#if (FTM_QDEC_NOTIFICATION_SUPPORTED == STD_ON)
/**
* @brief        This function disables QDEC overflow notification.
*
* @param        [in] module FTM hardware number.
* @return       void
*
* @implements   Ftm_Qdec_Ip_DisableOverFlowNotification_Activity
*/
void Ftm_Qdec_Ip_DisableOverFlowNotification(const uint8 module)
{
#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif
    Ftm_Qdec_HwAddrType *lpFtmBase = scpFtmBase[module];

    /*enter critical section */
    SchM_Enter_Qdec_QDEC_EXCLUSIVE_AREA_05();

    /* Disable the timer overflow interrupt */
    lpFtmBase->SC = (lpFtmBase->SC & ~FTM_SC_TOIE_MASK) | FTM_SC_TOIE(0);
    /* Clear the timer overflow flag */
    Ftm_Qdec_Ip_ClearTof(lpFtmBase);

    /*exit critical section*/
    SchM_Exit_Qdec_QDEC_EXCLUSIVE_AREA_05();
}

/*=========================================================================================================*/
/**
* @brief        This function enables QDEC overflow notification.
*
* @param        [in] module FTM hardware number.
* @return       void
*
* @implements   Ftm_Qdec_Ip_EnableOverFlowNotification_Activity
*/
void Ftm_Qdec_Ip_EnableOverFlowNotification(const uint8 module)
{
#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif
    Ftm_Qdec_HwAddrType *lpFtmBase = scpFtmBase[module];

    /*enter critical section */
    SchM_Enter_Qdec_QDEC_EXCLUSIVE_AREA_06();

    /* Clear the timer overflow flag */
    Ftm_Qdec_Ip_ClearTof(lpFtmBase);
    /* Enable the timer overflow interrupt */
    lpFtmBase->SC = (lpFtmBase->SC & ~FTM_SC_TOIE_MASK) | FTM_SC_TOIE(1);

    /*exit critical section*/
    SchM_Exit_Qdec_QDEC_EXCLUSIVE_AREA_06();
}
#endif

/*=========================================================================================================*/
/**
* @brief    Set mode of Qdec module
*
* @param    [in] module     FTM hardware number.
* @param    [in] mode       Given mode: QDEC_NORMAL_MODE or QDEC_SLEEP_MODE.
* @return   void
*
* @implements   Ftm_Qdec_Ip_SetMode_Activity
*/
void Ftm_Qdec_Ip_SetMode(const uint8 module, Ftm_ModeType mode)
{
#if (FTM_QDEC_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(FTM_INSTANCE_COUNT > module);
#endif
    Ftm_Qdec_HwAddrType *lpFtmBase = scpFtmBase[module];

    /*enter critical section */
    SchM_Enter_Qdec_QDEC_EXCLUSIVE_AREA_07();

    /* If write protection is enabled, then disable it. */
    if (0U != (lpFtmBase->FMS & FTM_FMS_WPEN_MASK))
    {
       /* Disable write protection */
       lpFtmBase->MODE |= FTM_MODE_WPDIS_MASK;
    }

    if (FTM_QDEC_MODE_NORMAL == mode)
    {
        /* Enable Quadrature Decoder */
        Ftm_Qdec_Ip_SetQdecModeEn(lpFtmBase, TRUE);
        /* Clear the timer overflow flag before enabling the interrupt */
        Ftm_Qdec_Ip_ClearTof(lpFtmBase);
        /* Enable the timer overflow interrupt */
        lpFtmBase->SC = (lpFtmBase->SC & ~FTM_SC_TOIE_MASK) | FTM_SC_TOIE(1);
    }
    else
    {
        /* Disable Quadrature Decoder */
        Ftm_Qdec_Ip_SetQdecModeEn(lpFtmBase, FALSE);
        /* Disable the timer overflow interrupt */
        lpFtmBase->SC = (lpFtmBase->SC & ~FTM_SC_TOIE_MASK) | FTM_SC_TOIE(0);
    }

    /*exit critical section*/
    SchM_Exit_Qdec_QDEC_EXCLUSIVE_AREA_07();
}

#define QDEC_STOP_SEC_CODE
#include "Qdec_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
