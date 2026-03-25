#include "PduR_Cfg.h"
#include "PduR.h"

static const PduR_RouteType PduR_Routes[] =
    {
        {0x000U, PDUR_CANTP, 0x000U, PDUR_COM}, // Control Led Blue Cmd
        {0x001U, PDUR_COM, 0x001U, PDUR_CANTP}, // Control Led Blue Rsp
        {0x002U, PDUR_CANTP, 0x002U, PDUR_COM}, // Echo reverse cmd
        {0x003U, PDUR_COM, 0x003U, PDUR_CANTP}, // Echo reverse rsp
        {0x004, PDUR_COM, 0x004, PDUR_CANTP},   // Pedal ntf
        {0x005, PDUR_COM, 0x004, PDUR_CANTP},   // brake ntf
        {0x006, PDUR_COM, 0x006, PDUR_CANTP},   // gear
        {0x007, PDUR_COM, 0x007, PDUR_CANTP},   // mode
        {0x008, PDUR_COM, 0x008, PDUR_CANTP},   // Rpm now ntf
        {0x009, PDUR_CANTP, 0x009, PDUR_COM},   // Rpm target cmd

};

const PduR_ConfigType PduR_PCConfig =
    {
        PduR_Routes,
        10U};