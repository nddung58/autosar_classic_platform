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
*   @file       Ftm_Qdec_Ip_Irq.c
*
*   @addtogroup ftm_qdec_ip Ftm_Qdec_Ip Driver
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
#include "Ftm_Qdec_Ip_Irq.h"
#include "SchM_Qdec.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FTM_QDEC_IP_IRQ_VENDOR_ID_C                           43
#define FTM_QDEC_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C            4
#define FTM_QDEC_IP_IRQ_AR_RELEASE_MINOR_VERSION_C            7
#define FTM_QDEC_IP_IRQ_AR_RELEASE_REVISION_VERSION_C         0
#define FTM_QDEC_IP_IRQ_SW_MAJOR_VERSION_C                    3
#define FTM_QDEC_IP_IRQ_SW_MINOR_VERSION_C                    0
#define FTM_QDEC_IP_IRQ_SW_PATCH_VERSION_C                    0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Ftm_Qdec_Ip_Irq header file are of the same vendor */
#if (FTM_QDEC_IP_IRQ_VENDOR_ID_C != FTM_QDEC_IP_IRQ_VENDOR_ID)
    #error "Ftm_Qdec_Ip_Irq.c and Ftm_Qdec_Ip_Irq.h have different vendor IDs"
#endif
/* Check if source file and Ftm_Qdec_Ip_Irq header file are of the same AutoSar version */
#if ((FTM_QDEC_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C != FTM_QDEC_IP_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (FTM_QDEC_IP_IRQ_AR_RELEASE_MINOR_VERSION_C != FTM_QDEC_IP_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (FTM_QDEC_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != FTM_QDEC_IP_IRQ_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Ftm_Qdec_Ip_Irq.c and Ftm_Qdec_Ip_Irq.h are different"
#endif
/* Check if source file and Ftm_Qdec_Ip_Irq header file are of the same Software version */
#if ((FTM_QDEC_IP_IRQ_SW_MAJOR_VERSION_C != FTM_QDEC_IP_IRQ_SW_MAJOR_VERSION) || \
     (FTM_QDEC_IP_IRQ_SW_MINOR_VERSION_C != FTM_QDEC_IP_IRQ_SW_MINOR_VERSION) || \
     (FTM_QDEC_IP_IRQ_SW_PATCH_VERSION_C != FTM_QDEC_IP_IRQ_SW_PATCH_VERSION))
#error "Software Version Numbers of Ftm_Qdec_Ip_Irq.c and Ftm_Qdec_Ip_Irq.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and SchM_Qdec.h are of the same AUTOSAR version */
    #if ((FTM_QDEC_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C != SCHM_QDEC_AR_RELEASE_MAJOR_VERSION) || \
         (FTM_QDEC_IP_IRQ_AR_RELEASE_MINOR_VERSION_C != SCHM_QDEC_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of Ftm_Qdec_Ip.c and SchM_Qdec.h are different."
    #endif
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define QDEC_START_SEC_CODE
#include "Qdec_MemMap.h"

#if ((defined FTM_QDEC_0_ISR_USED) || (defined FTM_QDEC_1_ISR_USED) || (defined FTM_QDEC_2_ISR_USED))
static void Ftm_Qdec_Ip_ProcessTofInterrupt (uint8 instance);
#endif

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
#if ((defined FTM_QDEC_0_ISR_USED) || (defined FTM_QDEC_1_ISR_USED) || (defined FTM_QDEC_2_ISR_USED))
/**
 * @brief Processes the overflow interrupt on the FTM instance.
 * @param instance
 *
 * @implements   Ftm_Qdec_Ip_ProcessTofInterrupt_Activity
 */
static void Ftm_Qdec_Ip_ProcessTofInterrupt (uint8 instance)
{
    /* Call ReportEvents for ASR or User_Callback for Edge Detection */
    if(Ftm_Qdec_Ip_pOverflowIrqCallback[instance].functionCallback != NULL_PTR)
    {
        Ftm_Qdec_Ip_pOverflowIrqCallback[instance].functionCallback(Ftm_Qdec_Ip_pOverflowIrqCallback[instance].callbackParam);
    }
}
#endif

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#if (defined FTM_QDEC_1_ISR_USED)
/**
* @brief       Interrupt handler for FTM channels.
* @details     Interrupt Service Routine corresponding to common FTM_1 module.
* @param[in]   none
* @return      none
* @isr
* @pre         The driver needs to be initialized.
*/
ISR(FTM_1_ISR)
{
    uint8  moduleIndex  = 1U;

    if(FALSE == gQdecFtmInitState)
    {
        scpFtmBase[moduleIndex]->SC &= ~(FTM_SC_TOF_MASK);
    }
    else
    {
        if((FTM_SC_TOIE_MASK == (scpFtmBase[moduleIndex]->SC & (uint32)FTM_SC_TOIE_MASK)) &&
           (FTM_SC_TOF_MASK == (scpFtmBase[moduleIndex]->SC & (uint32)FTM_SC_TOF_MASK)))
        {
            scpFtmBase[moduleIndex]->SC &= ~(FTM_SC_TOF_MASK);
            Ftm_Qdec_Ip_ProcessTofInterrupt(moduleIndex);
        }
     }

    EXIT_INTERRUPT();
}
#endif

/*=========================================================================================================*/
#if (defined FTM_QDEC_2_ISR_USED)
/**
* @brief       Interrupt handler for FTM channels.
* @details     Interrupt Service Routine corresponding to common FTM_2 module.
* @param[in]   none
* @return      none
* @isr
* @pre         The driver needs to be initialized.
*/
ISR(FTM_2_ISR)
{
    uint8  moduleIndex  = 2U;

    if(FALSE == gQdecFtmInitState)
    {
        scpFtmBase[moduleIndex]->SC &= ~(FTM_SC_TOF_MASK);
    }
    else
    {
        if((FTM_SC_TOIE_MASK == (scpFtmBase[moduleIndex]->SC & (uint32)FTM_SC_TOIE_MASK)) &&
           (FTM_SC_TOF_MASK == (scpFtmBase[moduleIndex]->SC & (uint32)FTM_SC_TOF_MASK)))
        {
            scpFtmBase[moduleIndex]->SC &= ~(FTM_SC_TOF_MASK);
            Ftm_Qdec_Ip_ProcessTofInterrupt(moduleIndex);
        }
     }

    EXIT_INTERRUPT();
}
#endif


#define QDEC_STOP_SEC_CODE
#include "Qdec_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
