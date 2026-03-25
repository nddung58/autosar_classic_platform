#ifndef CANTP_H__
#define CANTP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "ComStack_Types.h"
#include "Std_Types.h"

    typedef enum
    {
        PCI_TYPE_SF = 0b0000, // Single frame
        PCI_TYPE_FF = 0b0001, // First frame
        PCI_TYPE_CF = 0b0010, // Consecutive frame
        PCI_TYPE_FC = 0b0011  // Flow Control
    } FrameType;

    typedef enum
    {
        IDLE,
        SF,
        FF,
        CF,
        WAIT_FC
    } CanTpState;

    typedef enum
    {
        FC_FS_CTS = 0x0u,  // Clear to send : continue sending
        FC_FS_WT = 0x1u,   // Wait
        FC_FS_OVFLW = 0x2u // Overflow: receiver buffer full
    } CanTp_FcFsType;

    Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);

    void CanTp_MainFunction(void);

    void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);

    void CanTp_TxConfirmation(PduIdType CanIfTxPduId, Std_ReturnType result);

#ifdef __cplusplus
}
#endif

#endif