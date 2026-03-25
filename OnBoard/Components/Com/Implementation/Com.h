#ifndef COM_H__
#define COM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "ComStack_Types.h"
#include "Std_Types.h"

#define COM_SERVICE_NOT_AVAILABLE 0x80U
#define COM_BUSY 0x81U

    typedef enum
    {
        COM_UNINIT = 0x00u,
        COM_INIT
    } Com_StatusType;

    typedef uint16 Com_SignalIdType;

    typedef struct
    {
        uint16 PduId;
        uint16 length;
        uint16 TxBufferOffset;
        uint16 RxBufferOffset;
    } ComIpduType;

    typedef struct
    {
        const ComIpduType *PduList;
        uint16 NumIpdus;

        uint8 *TxBuffer;
        uint16 TxBufferSize;

        uint8 *RxBuffer;
        uint16 RxBufferSize;

    } Com_ConfigType;

    typedef struct
    {
        boolean txPending;
        boolean txBusy;
        boolean rxUpdated;
    } Com_IpduRuntimeType;

    void Com_Init(const Com_ConfigType *config);

    void Com_DeInit(void);

    // Update buffer
    uint8 Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr);

    uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr);

    Std_ReturnType Com_TriggerIPDUSend(PduIdType PduId);

    Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType *PduInfoPtr);

    void Com_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);

    void Com_TpRxIndication(PduIdType id, Std_ReturnType result);

    void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

    void Com_TpTxConfirmation(PduIdType id, Std_ReturnType result);

    BufReq_ReturnType Com_StartOfReception(PduIdType id, const PduInfoType *info,
                                           PduLengthType TpSduLength,
                                           PduLengthType *bufferSizePtr);

    BufReq_ReturnType Com_CopyRxData(PduIdType id, const PduInfoType *info,
                                     PduLengthType *bufferSizePtr);

    BufReq_ReturnType Com_CopyTxData(PduIdType id, const PduInfoType *info,
                                     const RetryInfoType *retry,
                                     PduLengthType *availableDataPtr);

    // Scheduled function

    void Com_MainFunctionRx(void);
    void Com_MainFunctionTx(void);

#ifdef __cplusplus
}
#endif

#endif
