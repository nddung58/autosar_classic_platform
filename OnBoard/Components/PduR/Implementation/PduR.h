#ifndef PDUR_H__
#define PDUR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
#include "ComStack_Types.h"

    typedef enum
    {
        PDUR_UP_MODULES = 0,
        PDUR_COM,
        PDUR_DCM,

        PDUR_LOIF_MODULES,
        PDUR_CANIF,
        PDUR_LINIF,
        PDUR_SOADIF,

        PDUR_LOTP_MODULES,
        PDUR_CANTP,
        PDUR_LINTP,
        PDUR_SOADTP,
        PDUR_SOAD,
        PDUR_J1939TP,

        PDUR_END_OF_MODULES
    } PduR_ModuleType;

    typedef struct
    {
        uint16 SrcPduId;
        PduR_ModuleType SrcModule;
        uint16 DstPduId;
        PduR_ModuleType DstModule;
    } PduR_RouteType;

    typedef struct
    {
        const PduR_RouteType *Routes;
        uint16 RouteCount;
    } PduR_ConfigType;

    typedef enum
    {
        PDUR_UNINIT,
        PDUR_ONLINE
    } PduR_StateType;

    void PduR_Init(const PduR_ConfigType *ConfigPtr);

#ifdef __cplusplus
}
#endif

#endif