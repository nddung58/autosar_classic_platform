#ifndef PDUR_COM_H__
#define PDUR_COM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "PduR.h"

    Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);

#ifdef __cplusplus
}
#endif

#endif