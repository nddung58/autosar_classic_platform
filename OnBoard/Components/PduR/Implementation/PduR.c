#include "PduR.h"
#include "PduR_CanTp.h"
#include "PduR_Com.h"
#include "PduR_Cfg.h"

#include "Com.h"
#include "CanTp.h"
#include "Dio.h"

extern const PduR_ConfigType PduR_PCConfig;

static PduR_StateType PduR_State = PDUR_UNINIT;

static const PduR_ConfigType *PduR_ConfigPtr = (const PduR_ConfigType *)0;

void PduR_Init(const PduR_ConfigType *ConfigPtr)
{
#if (STD_ON == PDUR_PRECOMPILE_SUPPORT)
    PduR_ConfigPtr = &PduR_PCConfig;
    (void)ConfigPtr;
#else
    PduR_ConfigPtr = ConfigPtr;
#endif

    if ((PduR_ConfigPtr->Routes == (const PduR_RouteType *)0) ||
        (PduR_ConfigPtr->RouteCount == 0u))
    {
        PduR_State = PDUR_UNINIT;
        return;
    }

    PduR_State = PDUR_ONLINE;
}

Std_ReturnType PduR_ComTransmit(PduIdType TxPduId,
                                const PduInfoType *PduInfoPtr)
{
    if ((PduR_State != PDUR_ONLINE) ||
        (PduR_ConfigPtr == NULL_PTR) ||
        (PduInfoPtr == NULL_PTR))
    {
        return E_NOT_OK;
    }

    if ((PduInfoPtr->SduLength > 0U) &&
        (PduInfoPtr->SduDataPtr == NULL_PTR))
    {
        return E_NOT_OK;
    }

    for (uint16 i = 0U; i < PduR_ConfigPtr->RouteCount; i++)
    {
        if (PduR_ConfigPtr->Routes[i].SrcPduId == TxPduId)
        {
            return CanTp_Transmit(
                PduR_ConfigPtr->Routes[i].DstPduId,
                PduInfoPtr);
        }
    }

    return E_NOT_OK;
}

void PduR_CanTpRxIndication(PduIdType RxPduId,
                            Std_ReturnType result)
{
    if ((PduR_State != PDUR_ONLINE) ||
        (PduR_ConfigPtr == NULL_PTR))
    {
        return;
    }

    for (uint16 i = 0U; i < PduR_ConfigPtr->RouteCount; i++)
    {
        if (PduR_ConfigPtr->Routes[i].DstPduId == RxPduId)
        {
            // Dio_WriteChannel(DioConf_DioChannel_DioChannel_LedBlue, STD_HIGH);
            /* Forward lên COM bằng SrcPduId */
            Com_TpRxIndication(PduR_ConfigPtr->Routes[i].SrcPduId,
                               result);

            break;
        }
    }
}

void PduR_CanTpTxConfirmation(PduIdType TxPduId,
                              Std_ReturnType result)
{
    if ((PduR_State != PDUR_ONLINE) ||
        (PduR_ConfigPtr == NULL_PTR))
    {
        return;
    }

    for (uint16 i = 0U; i < PduR_ConfigPtr->RouteCount; i++)
    {
        if (PduR_ConfigPtr->Routes[i].DstPduId == TxPduId)
        {
            /* Forward lên COM bằng SrcPduId */
            Com_TpTxConfirmation(PduR_ConfigPtr->Routes[i].SrcPduId,
                                 result);

            break;
        }
    }
}

BufReq_ReturnType PduR_CanTpStartOfReception(
    PduIdType id,
    const PduInfoType *info,
    PduLengthType TpSduLength,
    PduLengthType *bufferSizePtr)
{
    if ((PduR_State != PDUR_ONLINE) ||
        (PduR_ConfigPtr == NULL_PTR) ||
        (bufferSizePtr == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    for (uint16 i = 0U; i < PduR_ConfigPtr->RouteCount; i++)
    {
        if (PduR_ConfigPtr->Routes[i].SrcPduId == id)
        {
            /* Forward lên COM bằng SrcPduId */
            return Com_StartOfReception(
                PduR_ConfigPtr->Routes[i].DstPduId,
                info,
                TpSduLength,
                bufferSizePtr);
        }
    }

    return BUFREQ_E_NOT_OK;
}

BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr)
{
    if ((PduR_State != PDUR_ONLINE) ||
        (PduR_ConfigPtr == NULL_PTR) ||
        (bufferSizePtr == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    for (uint16 i = 0U; i < PduR_ConfigPtr->RouteCount; i++)
    {
        if (PduR_ConfigPtr->Routes[i].DstPduId == id)
        {
            /* Forward lên COM bằng SrcPduId */
            return Com_CopyRxData(
                PduR_ConfigPtr->Routes[i].SrcPduId,
                info,
                bufferSizePtr);
        }
    }

    return BUFREQ_E_NOT_OK;
}

BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType id, const PduInfoType *info, const RetryInfoType *retry, PduLengthType *availableDataPtr)
{
    if ((PduR_State != PDUR_ONLINE) ||
        (PduR_ConfigPtr == NULL_PTR) ||
        (availableDataPtr == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    for (uint16 i = 0U; i < PduR_ConfigPtr->RouteCount; i++)
    {
        if (PduR_ConfigPtr->Routes[i].DstPduId == id)
        {
            /* Forward lên COM bằng SrcPduId */
            return Com_CopyTxData(
                PduR_ConfigPtr->Routes[i].SrcPduId,
                info,
                retry,
                availableDataPtr);
        }
    }

    return BUFREQ_E_NOT_OK;
}
