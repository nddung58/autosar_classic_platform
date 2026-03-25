#ifndef PDUR_CANTP_H__
#define PDUR_CANTP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "PduR.h"

    void PduR_CanTpRxIndication(PduIdType RxPduId, Std_ReturnType result);
    void PduR_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

    // Advanced: Transmit sporadic
    // Std_ReturnType PduR_CanTpTriggerTransmit(PduIdType txPduId, PduInfoType *PduInfoPtr);

    BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr);

    BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType *info, PduLengthType TpSdulength, PduLengthType *bufferSizePtr);

    BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType id, const PduInfoType *info, const RetryInfoType *retry, PduLengthType *availableDataPtr);

#ifdef __cplusplus
}
#endif

#endif
