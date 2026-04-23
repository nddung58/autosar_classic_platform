#include "PduR_Cfg.h"
#include "PduR.h"

static const PduR_RouteType PduR_Routes[] =
    {
        {0x000U, PDUR_CANTP, 0x000U, PDUR_COM}, // Control Led Blue Cmd
        {0x001U, PDUR_COM, 0x001U, PDUR_CANTP}, // Control Led Blue Rsp
        {0x002U, PDUR_CANTP, 0x002U, PDUR_COM}, // Echo reverse cmd
        {0x003U, PDUR_COM, 0x003U, PDUR_CANTP}, // Echo reverse rsp
        {0x004U, PDUR_COM, 0x004, PDUR_CANTP},  // Pedal ntf
        {0x005U, PDUR_COM, 0x005, PDUR_CANTP},  // brake ntf
        {0x006U, PDUR_COM, 0x006, PDUR_CANTP},  // gear
        {0x007U, PDUR_COM, 0x007, PDUR_CANTP},  // mode
        {0x008U, PDUR_COM, 0x008, PDUR_CANTP},  // Rpm now ntf
#if defined(ECU_CENTRAL)
        {0x009U, PDUR_COM, 0x009, PDUR_CANTP}, // Rpm target cmd
#elif (ECU_CONTROL)
        {0x009U, PDUR_CANTP, 0x009, PDUR_COM}, // Rpm target cmd
#endif
        {0x00AU, PDUR_COM, 0x00AU, PDUR_CANTP}, // Steering angle ntf
        {0x00BU, PDUR_COM, 0x00BU, PDUR_CANTP}, // Wheel angle ntf
#if defined(ECU_CENTRAL)
        {0x00CU, PDUR_CANTP, 0x00C, PDUR_COM}, // Speed Ntf
#elif (ECU_CONTROL)
        {0x00CU, PDUR_COM, 0x00C, PDUR_CANTP}, // Speed Ntf
#endif

};

const PduR_ConfigType PduR_PCConfig =
    {
        PduR_Routes,
        13U};