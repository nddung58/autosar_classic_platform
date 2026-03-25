#include "Com.h"
#include "PduR.h"
#include "PduR_Com.h"
#include "Com_Cfg.h"
#include "ComStackTypes.h"
#include "string.h"
#include "Rte_Cbk.h"
#include "Dio.h"

static Com_StatusType Com_Status = COM_UNINIT;
static const Com_ConfigType *Com_ConfigPtr = (const Com_ConfigType *)0;

#ifndef COM_MAX_IPDUS
#define COM_MAX_IPDUS 256u
#endif

static PduLengthType Com_TpRxExpectedLen[COM_MAX_IPDUS]; // Total length message RX
static PduLengthType Com_TpRxReceivedLen[COM_MAX_IPDUS]; // Number of byte received

static PduLengthType Com_TpTxTotalLen[COM_MAX_IPDUS]; // Total length message TX
static PduLengthType Com_TpTxSentLen[COM_MAX_IPDUS];  // Number of byte sent

static Com_IpduRuntimeType Com_IpduRt[COM_MAX_IPDUS];

static const ComIpduType *Com_FindIpdu(PduIdType PduId)
{
    if ((Com_ConfigPtr == NULL_PTR) || (Com_ConfigPtr->PduList == NULL_PTR))
    {
        return NULL_PTR;
    }

    for (uint16 i = 0u; i < Com_ConfigPtr->NumIpdus; i++)
    {
        if ((PduIdType)Com_ConfigPtr->PduList[i].PduId == PduId)
        {
            return &Com_ConfigPtr->PduList[i];
        }
    }
    return NULL_PTR;
}

static uint16 Com_FindIpduIndex(PduIdType PduId)
{
    if ((Com_ConfigPtr == NULL_PTR) || (Com_ConfigPtr->PduList == NULL_PTR))
    {
        return 0xFFFFu;
    }

    for (uint16 i = 0u; i < Com_ConfigPtr->NumIpdus; i++)
    {
        if ((PduIdType)Com_ConfigPtr->PduList[i].PduId == PduId)
        {
            return i;
        }
    }
    return 0xFFFFu;
}

extern const Com_ConfigType Com_PCConfig;

void Com_Init(const Com_ConfigType *config)
{
#if (STD_ON == COM_PRECOMPILE_SUPPORT)
    Com_ConfigPtr = &Com_PCConfig;
    (void)config;
#else
    Com_ConfigPtr = config;
#endif
    Com_Status = COM_INIT;

    // Reset TP tracking + ipdu runtime
    for (uint16 i = 0U; i < COM_MAX_IPDUS; i++)
    {
        Com_TpRxExpectedLen[i] = 0U;
        Com_TpRxReceivedLen[i] = 0u;
        Com_TpTxTotalLen[i] = 0u;
        Com_TpTxSentLen[i] = 0u;

        Com_IpduRt[i].txPending = FALSE;
        Com_IpduRt[i].txBusy = FALSE;
        Com_IpduRt[i].rxUpdated = FALSE;
    }
}

void Com_DeInit(void)
{
    for (uint16 i = 0U; i < COM_MAX_IPDUS; i++)
    {
        Com_TpRxExpectedLen[i] = 0U;
        Com_TpRxReceivedLen[i] = 0U;
        Com_TpTxTotalLen[i] = 0U;
        Com_TpTxSentLen[i] = 0U;

        Com_IpduRt[i].txPending = FALSE;
        Com_IpduRt[i].txBusy = FALSE;
        Com_IpduRt[i].rxUpdated = FALSE;
    }

    Com_ConfigPtr = NULL_PTR;
    Com_Status = COM_UNINIT;
}

/*
E_OK: service has been accepted
COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group
was stopped
COM_BUSY: in case the TP-Buffer is locked for large data types
handling
*/
uint8 Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR) ||
        (SignalDataPtr == NULL_PTR) || (Com_ConfigPtr->PduList == NULL_PTR) ||
        (Com_ConfigPtr->TxBuffer == NULL_PTR))
    {
        return E_NOT_OK; /* fail */
    }

    if (SignalId >= Com_ConfigPtr->NumIpdus)
    {
        return 1u;
    }

    const ComIpduType *ipdu = &Com_ConfigPtr->PduList[SignalId];

    /* bounds check */
    if ((uint32)ipdu->TxBufferOffset + (uint32)ipdu->length > (uint32)Com_ConfigPtr->TxBufferSize)
    {
        return 1u;
    }

    memcpy(&Com_ConfigPtr->TxBuffer[ipdu->TxBufferOffset], SignalDataPtr, ipdu->length);

    // set pending
    Com_IpduRt[SignalId].txPending = TRUE;

    return E_OK;
}

/*
E_OK: service has been accepted
COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group
was stopped
COM_BUSY: in case the TP-Buffer is locked for large data types
handling
*/
uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR) ||
        (SignalDataPtr == NULL_PTR) || (Com_ConfigPtr->PduList == NULL_PTR) ||
        (Com_ConfigPtr->RxBuffer == NULL_PTR))
    {
        return E_NOT_OK;
    }

    if (SignalId >= Com_ConfigPtr->NumIpdus)
    {
        return 1u;
    }

    const ComIpduType *ipdu = &Com_ConfigPtr->PduList[SignalId];

    if ((uint32)ipdu->RxBufferOffset + (uint32)ipdu->length > (uint32)Com_ConfigPtr->RxBufferSize)
    {
        return 1u;
    }

    memcpy(SignalDataPtr, &Com_ConfigPtr->RxBuffer[ipdu->RxBufferOffset], ipdu->length);
    return E_OK;
}

/*
E_OK: I-PDU was triggered for transmission
E_NOT_OK: I-PDU is stopped, the transmission could not be
triggered
*/
Std_ReturnType Com_TriggerIPDUSend(PduIdType PduId)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR))
    {
        return E_NOT_OK;
    }

    uint16 idx = Com_FindIpduIndex(PduId);
    const ComIpduType *ipdu = Com_FindIpdu(PduId);

    if ((ipdu == NULL_PTR) || (idx == 0xFFFFu) || (idx >= COM_MAX_IPDUS) ||
        (Com_ConfigPtr->TxBuffer == NULL_PTR))
    {
        return E_NOT_OK;
    }

    if ((ipdu == NULL_PTR) || (Com_ConfigPtr->TxBuffer == NULL_PTR))
    {
        return E_NOT_OK;
    }

    if ((uint32)ipdu->TxBufferOffset + (uint32)ipdu->length > (uint32)Com_ConfigPtr->TxBufferSize)
    {
        return E_NOT_OK;
    }

    PduInfoType pduInfo;
    pduInfo.SduDataPtr = &Com_ConfigPtr->TxBuffer[ipdu->TxBufferOffset];
    pduInfo.SduLength = (PduLengthType)ipdu->length;

    if (PduR_ComTransmit(PduId, &pduInfo) == E_OK)
    {
        Com_IpduRt[idx].txBusy = TRUE;
        Com_IpduRt[idx].txPending = FALSE;
        return E_OK;
    }

    return E_NOT_OK;
}

/*
E_OK: SDU has been copied and SduLength indicates the
number of copied bytes.
E_NOT_OK: No SDU data has been copied. PduInfoPtr must not
be used since it may contain a NULL pointer or point to invalid
data.

*/
Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType *PduInfoPtr)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR) || (PduInfoPtr == NULL_PTR))
    {
        return E_NOT_OK;
    }

    const ComIpduType *ipdu = Com_FindIpdu(TxPduId);
    if ((ipdu == NULL_PTR) || (Com_ConfigPtr->TxBuffer == NULL_PTR))
    {
        return E_NOT_OK;
    }

    if ((uint32)ipdu->TxBufferOffset + (uint32)ipdu->length > (uint32)Com_ConfigPtr->TxBufferSize)
    {
        return E_NOT_OK;
    }

    PduInfoPtr->SduDataPtr = &Com_ConfigPtr->TxBuffer[ipdu->TxBufferOffset];
    PduInfoPtr->SduLength = (PduLengthType)ipdu->length;

    return E_OK;
}

void Com_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPrt)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR) ||
        (PduInfoPrt == NULL_PTR) ||
        ((PduInfoPrt->SduLength > 0U) && (PduInfoPrt->SduDataPtr == NULL_PTR)))
    {
        return;
    }

    uint16 idx = Com_FindIpduIndex(RxPduId);
    const ComIpduType *ipdu = Com_FindIpdu(RxPduId);
    if ((ipdu == NULL_PTR) || (Com_ConfigPtr->RxBuffer == NULL_PTR) ||
        (idx == 0xFFFFu) || (idx >= COM_MAX_IPDUS))
    {
        return;
    }

    PduLengthType copyLen = PduInfoPrt->SduLength;
    if (copyLen > (PduLengthType)ipdu->length)
    {
        copyLen = (PduLengthType)ipdu->length;
    }

    if ((uint32)ipdu->RxBufferOffset + (uint32)copyLen > (uint32)Com_ConfigPtr->RxBufferSize)
    {
        return;
    }

    if (copyLen > 0U)
    {
        memcpy(&Com_ConfigPtr->RxBuffer[ipdu->RxBufferOffset],
               PduInfoPrt->SduDataPtr,
               copyLen);
    }

    Com_IpduRt[idx].rxUpdated = TRUE;
}

/*
Called after an I-PDU has been received via the TP API,
the result indicates whether the transmission was successful or not.
E_OK: The PDU was received
E_NOT_OK: Reception of the PDU failed.
*/
void Com_TpRxIndication(PduIdType id, Std_ReturnType result)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR))
    {
        return;
    }

    uint16 idx = Com_FindIpduIndex(id);
    if ((idx == 0xFFFFu) || (idx >= COM_MAX_IPDUS))
    {
        return;
    }

    if (result == E_OK)
    {
        /* Optional: ensure complete reception */
        if ((Com_TpRxExpectedLen[idx] == 0u) ||
            (Com_TpRxReceivedLen[idx] >= Com_TpRxExpectedLen[idx]))
        {
            Com_IpduRt[idx].rxUpdated = TRUE;
        }
    }
    else
    {
        /* Optional: discard partial data if desired */
        Com_IpduRt[idx].rxUpdated = FALSE;
    }

    /* Reset TP RX tracking */
    Com_TpRxExpectedLen[idx] = 0u;
    Com_TpRxReceivedLen[idx] = 0u;

    // Dio_WriteChannel(DioConf_DioChannel_DioChannel_LedBlue, STD_HIGH);
}

/*
The lower layer communication interface module confirms the transmission
of a PDU, or the failure to transmit a PDU.
E_OK: The PDU was transmitted.
E_NOT_OK: Transmission of the PDU failed.
*/
void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR))
    {
        return;
    }

    uint16 idx = Com_FindIpduIndex(TxPduId);
    if ((idx == 0xFFFFu) || (idx >= COM_MAX_IPDUS))
    {
        return;
    }

    /* Transmission no longer busy */
    Com_IpduRt[idx].txBusy = FALSE;

    if (result == E_OK)
    {
        /* success: nothing more to do */
        Com_IpduRt[idx].txPending = FALSE;
    }
    else
    {
        /* failure: optional retry */
        Com_IpduRt[idx].txPending = TRUE;
    }

    /* Optional: call Tx callback/notification here */
}

/*
This function is called ofter the I_PDU has been transmitted on its network,
the result indicates whether the transmission was successful or not.
E_OK: The PDU was transmitted
E_NOT_OK: Transmission of the PDU failed.
*/
void Com_TpTxConfirmation(PduIdType id, Std_ReturnType result)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR))
    {
        return;
    }

    uint16 idx = Com_FindIpduIndex(id);
    if ((idx == 0xFFFFu) || (idx >= COM_MAX_IPDUS))
    {
        return;
    }

    /* TP transmission finished */
    Com_IpduRt[idx].txBusy = FALSE;

    if (result == E_OK)
    {
        Com_IpduRt[idx].txPending = FALSE;
    }
    else
    {
        /* Optional retry */
        Com_IpduRt[idx].txPending = TRUE;
    }

    /* Reset TP TX tracking */
    Com_TpTxTotalLen[idx] = 0u;
    Com_TpTxSentLen[idx] = 0u;

    /* Optional: call Tx callback/notification here */
}

/*
This function is called at the start of receiving an N-SDU. The N-SDU might
be fragmented into multiple N-PDUs (FF with one or more following CFs) or
might consist of a single N-PDU (SF). The service shall provide the currently
available maximum buffer size when invoked with TpSdu Length equal to 0.

info: Pointer to a PduInfoType structure containing the payload data
(without protocol information) and payload length of the first
frame or single frame of a transport protocol I-PDU reception, and
the MetaData related to this PDU. If neither first/single frame data
nor MetaData are available, this parameter is set to NULL_PTR

BUFREQ_OK: Connection has been accepted. bufferSizePtr
indicates the available receive buffer; reception is continued. If no
buffer of the requested size is available, a receive buffer size of 0
shall be indicated by bufferSizePtr.
BUFREQ_E_NOT_OK: Connection has been rejected; reception is
aborted. bufferSizePtr remains unchanged.
BUFREQ_E_OVFL: No buffer of the required length can be
provided; reception is aborted. bufferSizePtr remains unchanged.
*/
BufReq_ReturnType Com_StartOfReception(PduIdType id,
                                       const PduInfoType *info,
                                       PduLengthType TpSduLength,
                                       PduLengthType *bufferSizePtr)
{
    (void)info;

    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR) || (bufferSizePtr == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    uint16 idx = Com_FindIpduIndex(id);
    const ComIpduType *ipdu = Com_FindIpdu(id);
    if ((ipdu == NULL_PTR) || (idx == 0xFFFFu) || (idx >= COM_MAX_IPDUS) ||
        (Com_ConfigPtr->RxBuffer == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    /* available size from RxBuffer slice */
    if ((uint32)ipdu->RxBufferOffset >= (uint32)Com_ConfigPtr->RxBufferSize)
    {
        return BUFREQ_E_NOT_OK;
    }

    PduLengthType avail = (PduLengthType)((uint32)Com_ConfigPtr->RxBufferSize - (uint32)ipdu->RxBufferOffset);

    /* Nếu muốn chặt chẽ theo ipdu->length: */
    if (avail > (PduLengthType)ipdu->length)
    {
        avail = (PduLengthType)ipdu->length;
    }

    /* Nếu message TP dài hơn buffer slice -> overflow */
    if (TpSduLength > avail)
    {
        // if (id == 0x0000)
        //     Dio_WriteChannel(DioConf_DioChannel_DioChannel_LedBlue, STD_HIGH);

        *bufferSizePtr = avail;
        return BUFREQ_E_OVFL;
    }

    Com_TpRxExpectedLen[idx] = TpSduLength;
    Com_TpRxReceivedLen[idx] = 0u;
    *bufferSizePtr = avail;

    return BUFREQ_OK;
}

/*
This function is called to provide the received data of an I-PDU
segment (N-PDU) to the upper layer. Each call to this function provides
the next part of the I-PDU data. The size of the remaining buffer is
written to the position indicated by bufferSizePtr.

BUFREQ_OK: Data copied successfully
BUFREQ_E_NOT_OK: Data was not copied because an error occurred.
*/
BufReq_ReturnType Com_CopyRxData(PduIdType id,
                                 const PduInfoType *info,
                                 PduLengthType *bufferSizePtr)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR) ||
        (info == NULL_PTR) || (bufferSizePtr == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    uint16 idx = Com_FindIpduIndex(id);
    const ComIpduType *ipdu = Com_FindIpdu(id);
    if ((ipdu == NULL_PTR) || (idx == 0xFFFFu) || (idx >= COM_MAX_IPDUS) ||
        (Com_ConfigPtr->RxBuffer == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    if ((info->SduLength > 0u) && (info->SduDataPtr == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    PduLengthType received = Com_TpRxReceivedLen[idx];
    PduLengthType expected = Com_TpRxExpectedLen[idx];
    PduLengthType sliceSize = (PduLengthType)ipdu->length;

    if ((uint32)ipdu->RxBufferOffset + (uint32)sliceSize > (uint32)Com_ConfigPtr->RxBufferSize)
    {
        return BUFREQ_E_NOT_OK;
    }

    if ((received + info->SduLength) > sliceSize)
    {
        *bufferSizePtr = (PduLengthType)(sliceSize - received);
        return BUFREQ_E_OVFL;
    }

    if ((expected > 0u) && ((received + info->SduLength) > expected))
    {
        *bufferSizePtr = (PduLengthType)(expected - received);
        return BUFREQ_E_OVFL;
    }

    if (info->SduLength > 0u)
    {
        memcpy(&Com_ConfigPtr->RxBuffer[ipdu->RxBufferOffset + received],
               info->SduDataPtr,
               info->SduLength);
    }

    received += info->SduLength;
    Com_TpRxReceivedLen[idx] = received;
    *bufferSizePtr = (PduLengthType)(sliceSize - received);

    return BUFREQ_OK;
}

/*
This function is called to acquire the transmit data of an I-PDU segment (N-PDU). Each call to
this function provides the next part of the I-PDU data unless retry->TpDataState is TP_
DATARETRY. In this case the function restarts to copy the data beginning at the offset from the
current position indicated by retry->TxTpDataCnt. The size of the remaining data is written to
the position indicated by availableDataPtr.

retry: This parameter is used to acknowledge transmitted data or to
retransmit data after transmission problems.
If the retry parameter is a NULL_PTR, it indicates that the
transmit data can be removed from the buffer immediately after it
has been copied. Otherwise, the retry parameter must point to a
valid RetryInfoType element.
If TpDataState indicates TP_CONFPENDING, the previously
copied data must remain in the TP buffer to be available for error
recovery. TP_DATACONF indicates that all data that has been
copied before this call is confirmed and can be removed from the
TP buffer. Data copied by this API call is excluded and will be
confirmed later. TP_DATARETRY indicates that this API call shall
copy previously copied data in order to recover from an error. In
this case TxTpDataCnt specifies the offset in bytes from the
current data copy position.

BUFREQ_OK: Data has been copied to the transmit buffer
completely as requested.
BUFREQ_E_BUSY: Request could not be fulfilled, because the
required amount of Tx data is not available. The lower layer
module may retry this call later on. No data has been copied.
BUFREQ_E_NOT_OK: Data has not been copied. Request failed
*/
BufReq_ReturnType Com_CopyTxData(PduIdType id,
                                 const PduInfoType *info,
                                 const RetryInfoType *retry,
                                 PduLengthType *availableDataPtr)
{
    (void)retry;

    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR) ||
        (info == NULL_PTR) || (availableDataPtr == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    uint16 idx = Com_FindIpduIndex(id);
    const ComIpduType *ipdu = Com_FindIpdu(id);
    if ((ipdu == NULL_PTR) || (idx == 0xFFFFu) || (idx >= COM_MAX_IPDUS) ||
        (Com_ConfigPtr->TxBuffer == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    if ((info->SduLength > 0u) && (info->SduDataPtr == NULL_PTR))
    {
        return BUFREQ_E_NOT_OK;
    }

    PduLengthType total = (PduLengthType)ipdu->length;
    PduLengthType sent = Com_TpTxSentLen[idx];

    if ((uint32)ipdu->TxBufferOffset + (uint32)total > (uint32)Com_ConfigPtr->TxBufferSize)
    {
        return BUFREQ_E_NOT_OK;
    }

    if (sent >= total)
    {
        *availableDataPtr = 0u;
        return BUFREQ_OK;
    }

    PduLengthType copyLen = info->SduLength;
    if ((sent + info->SduLength) > total)
    {
        /* chỉ copy phần còn lại */
        copyLen = (PduLengthType)(total - sent);
    }

    memcpy(info->SduDataPtr,
           &Com_ConfigPtr->TxBuffer[ipdu->TxBufferOffset + sent],
           copyLen);

    sent += copyLen;
    Com_TpTxSentLen[idx] = sent;
    Com_TpTxTotalLen[idx] = total;

    *availableDataPtr = (PduLengthType)(total - sent);
    return BUFREQ_OK;
}

/* Scheduled function */
void Com_MainFunctionRx(void)
{
    if ((Com_Status != COM_INIT) ||
        (Com_ConfigPtr == NULL_PTR) ||
        (Com_ConfigPtr->PduList == NULL_PTR))
    {
        return;
    }

    for (uint16 i = 0U; i < Com_ConfigPtr->NumIpdus; i++)
    {
        if (Com_IpduRt[i].rxUpdated == TRUE)
        {
            /* TODO (optional): call Rx notification callback nếu bạn thêm vào config */

            /* Clear flag */
            Com_IpduRt[i].rxUpdated = FALSE;

            const ComIpduType *ipdu = &Com_ConfigPtr->PduList[i];
            Rte_CbkRxAck((Rte_CbkSignalHandleType)(ipdu->PduId));
        }
    }
}

void Com_MainFunctionTx(void)
{
    if ((Com_Status != COM_INIT) || (Com_ConfigPtr == NULL_PTR) || (Com_ConfigPtr->PduList == NULL_PTR))
    {
        return;
    }

    for (uint16 i = 0U; i < Com_ConfigPtr->NumIpdus; i++)
    {
        const ComIpduType *ipdu = &Com_ConfigPtr->PduList[i];

        if ((Com_IpduRt[i].txPending == TRUE) && (Com_IpduRt[i].txBusy == FALSE))
        {
            PduInfoType pduInfo;
            pduInfo.SduDataPtr = &Com_ConfigPtr->TxBuffer[ipdu->TxBufferOffset];
            pduInfo.SduLength = (PduLengthType)ipdu->length;

            if (PduR_ComTransmit((PduIdType)ipdu->PduId, &pduInfo) == E_OK)
            {
                Com_IpduRt[i].txBusy = TRUE;     /* chờ confirmation */
                Com_IpduRt[i].txPending = FALSE; /* đã trigger rồi */
            }
            else
            {
                /* transmit bị reject → giữ pending để retry ở lần sau */
                Com_IpduRt[i].txPending = TRUE;
            }
        }
    }
}
