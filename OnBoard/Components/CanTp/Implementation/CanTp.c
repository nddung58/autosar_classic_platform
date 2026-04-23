#include "CanTp.h"
#include "CanIf.h"
#include "PduR.h"
#include "PduR_CanTp.h"
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "string.h"

#define CAN_STANDARD_SIZE 8

// TX
static const uint8_t *TX_appPtr = NULL;
static PduLengthType TX_totalLen = 0;
static PduLengthType TX_sentLen = 0;
static uint8_t TX_SN = 0;

static CanTpState txState = IDLE;

// RX
static PduLengthType RX_bufferSizePtr;
static uint8_t RX_SN = 0;
static PduLengthType totalLen;
static PduLengthType copiedLen;

Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    if (!PduInfoPtr || !PduInfoPtr->SduDataPtr || PduInfoPtr->SduLength == 0u)
        return E_NOT_OK;
    if (txState != IDLE)
        return E_NOT_OK;

    if (PduInfoPtr->SduLength <= 7u) // Single Frame
    {
        PduInfoType info;
        static uint8_t sfBuf[8];
        info.SduDataPtr = sfBuf;
        info.MetaDataPtr = NULL;
        info.SduDataPtr[0] = (uint8_t)((PCI_TYPE_SF << 4) | (PduInfoPtr->SduLength & 0x0F));
        memcpy(&info.SduDataPtr[1], PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
        info.SduLength = (PduLengthType)(1u + PduInfoPtr->SduLength);

        txState = SF;
        return CanIf_Transmit(TxPduId, &info);
    }

    if (PduInfoPtr->SduLength > 0x0FFFu)
        return E_NOT_OK;
    // Multiple Frame (First Frame)
    PduInfoType infoFirstFrame;
    static uint8_t ffBuf[8];

    infoFirstFrame.SduDataPtr = ffBuf;
    infoFirstFrame.MetaDataPtr = NULL;

    infoFirstFrame.SduDataPtr[0] = (uint8_t)((PCI_TYPE_FF << 4) | ((PduInfoPtr->SduLength >> 8) & 0x0F));
    infoFirstFrame.SduDataPtr[1] = (uint8_t)(PduInfoPtr->SduLength & 0xFF);

    memcpy(&infoFirstFrame.SduDataPtr[2], PduInfoPtr->SduDataPtr, 6u);
    infoFirstFrame.SduLength = 8u;

    TX_appPtr = PduInfoPtr->SduDataPtr;
    TX_totalLen = PduInfoPtr->SduLength;
    TX_sentLen = 6u;
    TX_SN = 1u;

    txState = FF;
    return CanIf_Transmit(TxPduId, &infoFirstFrame);
}

void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    if (result != E_OK)
    {
        txState = IDLE;
        PduR_CanTpTxConfirmation(TxPduId, result);
        return;
    }
    switch (txState)
    {
    case SF:
        txState = IDLE;
        PduR_CanTpTxConfirmation(TxPduId, result);
        break;

    case FF:
        txState = WAIT_FC;
        break;

    case CF: // Update: set flag & transmit on main function
    {
        PduLengthType left_before = (PduLengthType)(TX_totalLen - TX_sentLen);
        PduLengthType just = (left_before > 7u) ? 7u : left_before;
        TX_sentLen += just;
        TX_SN = (uint8_t)((TX_SN + 1u) & 0x0F);

        if (TX_sentLen >= TX_totalLen)
        {
            txState = IDLE;
            PduR_CanTpTxConfirmation(TxPduId, E_OK);
            break;
        }

        static uint8_t cfBuf[8];
        PduInfoType info;
        PduLengthType chunk = (PduLengthType)((TX_totalLen - TX_sentLen) > 7u ? 7u : (TX_totalLen - TX_sentLen));

        info.SduDataPtr = cfBuf;
        info.MetaDataPtr = NULL;
        info.SduDataPtr[0] = (uint8_t)((PCI_TYPE_CF << 4) | (TX_SN & 0x0F));
        memcpy(&info.SduDataPtr[1], &TX_appPtr[TX_sentLen], chunk);
        info.SduLength = (PduLengthType)(1u + chunk);

        if (CanIf_Transmit(TxPduId, &info) != E_OK)
        {
            txState = IDLE;
            PduR_CanTpTxConfirmation(TxPduId, E_NOT_OK);
        }
        break;
    }

    case WAIT_FC:
    case IDLE:
    default:
        break;
    }
}

void CanTp_MainFunction(void)
{
}

static void PrepareFC_AllowAll(PduIdType TxPduId)
{
    static uint8_t fc_buf[3];
    PduInfoType pdu;

    /* PCI: FT=FC(0x3) | FS=CTS(0x0) */
    fc_buf[0] = (uint8_t)((PCI_TYPE_FC << 4) | 0);
    fc_buf[1] = 0x00;
    fc_buf[2] = 0x00;

    pdu.SduDataPtr = fc_buf;
    pdu.MetaDataPtr = NULL;
    pdu.SduLength = (PduLengthType)sizeof(fc_buf); /* 3 byte */

    (void)CanIf_Transmit(TxPduId, &pdu);
}

void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    PduLengthType TpSduLength = 0;
    PduInfoType info;
    BufReq_ReturnType bufferReq;
    switch ((PduInfoPtr->SduDataPtr[0] >> 4) & 0x0F)
    {
    case PCI_TYPE_SF:

        TpSduLength = PduInfoPtr->SduDataPtr[0] & 0x0F;
        if (TpSduLength == 0 || TpSduLength > 7 || TpSduLength > (PduInfoPtr->SduLength - 1))
        {
            return;
        }

        info.SduDataPtr = (uint8_t *)&PduInfoPtr->SduDataPtr[1];
        info.SduLength = TpSduLength;

        bufferReq = PduR_CanTpStartOfReception(RxPduId, &info, TpSduLength, &RX_bufferSizePtr);

        if (bufferReq != BUFREQ_OK || (RX_bufferSizePtr < info.SduLength))
        {
            return;
        }
        if (PduR_CanTpCopyRxData(RxPduId, &info, &RX_bufferSizePtr) == BUFREQ_OK)
        {

            PduR_CanTpRxIndication(RxPduId, E_OK);
        }

        break;

    case PCI_TYPE_FF:

        TpSduLength = ((PduInfoPtr->SduDataPtr[0] & 0x0F) << 8) | (PduInfoPtr->SduDataPtr[1]);
        if (TpSduLength == 0)
            return;

        PduLengthType firstChunk = (PduInfoPtr->SduLength > 2) ? (PduInfoPtr->SduLength - 2) : 0;
        if (firstChunk > 6)
            firstChunk = 6;
        info.SduDataPtr = (uint8_t *)&PduInfoPtr->SduDataPtr[2];
        info.MetaDataPtr = NULL;
        info.SduLength = firstChunk;

        bufferReq = PduR_CanTpStartOfReception(RxPduId, &info, TpSduLength, &RX_bufferSizePtr);

        if (bufferReq != BUFREQ_OK || RX_bufferSizePtr < info.SduLength)
            return;

        if (PduR_CanTpCopyRxData(RxPduId, &info, &RX_bufferSizePtr) == BUFREQ_OK)
        {
            PrepareFC_AllowAll(RxPduId);

            totalLen = TpSduLength;
            copiedLen = firstChunk;
            RX_SN = 0;
        }
        break;

    case PCI_TYPE_CF:
        if (totalLen == 0 || copiedLen >= totalLen) // Not received or already completed
        {
            PduR_CanTpRxIndication(RxPduId, E_NOT_OK);
            break;
        }

        uint8_t sn_expect = (uint8_t)((RX_SN + 1U) & 0x0Fu);
        uint8_t sn_rx = (uint8_t)(PduInfoPtr->SduDataPtr[0] & 0x0F);
        if (sn_rx != sn_expect) // Error sequence number
        {
            PduR_CanTpRxIndication(RxPduId, E_NOT_OK);
            break;
        }

        PduLengthType chunk = (PduInfoPtr->SduLength > 1u) ? (PduInfoPtr->SduLength - 1u) : 0u;
        PduLengthType left = (PduLengthType)(totalLen - copiedLen);
        if (chunk > left)
            chunk = left;

        PduInfoType info;
        info.SduDataPtr = (uint8_t *)&PduInfoPtr->SduDataPtr[1];
        info.MetaDataPtr = NULL;
        info.SduLength = chunk;

        if (PduR_CanTpCopyRxData(RxPduId, &info, &RX_bufferSizePtr) != BUFREQ_OK)
        {
            PduR_CanTpRxIndication(RxPduId, E_NOT_OK);
            break;
        }

        copiedLen = (PduLengthType)(copiedLen + chunk);
        RX_SN = sn_expect;

        if (copiedLen >= totalLen) // Reception complete
        {
            PduR_CanTpRxIndication(RxPduId, E_OK);
            totalLen = 0u;
            copiedLen = 0u;
            RX_SN = 0u;
        }
        break;
    case PCI_TYPE_FC:
        if (txState == WAIT_FC && PduInfoPtr->SduLength >= 3u)
        {
            uint8_t fs = (uint8_t)(PduInfoPtr->SduDataPtr[0] & 0x0F);

            if (fs == FC_FS_CTS)
            {
                static uint8_t cfBuf[8];
                PduInfoType info;

                PduLengthType left = (PduLengthType)(TX_totalLen - TX_sentLen);
                PduLengthType chunk = (left > 7u) ? 7u : left;

                info.SduDataPtr = cfBuf;
                info.MetaDataPtr = NULL;
                info.SduDataPtr[0] = (uint8_t)((PCI_TYPE_CF << 4) | (TX_SN & 0x0F));
                memcpy(&info.SduDataPtr[1], &TX_appPtr[TX_sentLen], chunk);
                info.SduLength = (PduLengthType)(1u + chunk);

                txState = CF;
                if (CanIf_Transmit(RxPduId, &info) != E_OK) // send first CF
                {
                    txState = IDLE;
                    PduR_CanTpTxConfirmation(RxPduId, E_NOT_OK);
                }
            }
            else if (fs == FC_FS_WT)
            {
            }
            else
            {
                txState = IDLE;
                PduR_CanTpTxConfirmation(RxPduId, E_NOT_OK);
            }
        }
        break;
    }
}
