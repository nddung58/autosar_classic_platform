#include "Com.h"

#define BUFFER_SIZE (uint16)256u

static const ComIpduType ComIpdu[] =
    {
        {0x000u, 1, 0, 0},  // Control led blue cmd
        {0x001u, 1, 1, 1},  // Control led blue rsp
        {0x002u, 7, 2, 2},  // echo reverse cmd
        {0x003u, 7, 9, 9},  // echo reverse rsp
        {0x004, 1, 16, 16}, // pedal ntf
        {0x005, 1, 17, 17}, // brake ntf
        {0x006, 1, 18, 18}, // gear
        {0x007, 1, 19, 19}, // mode
        {0x008, 1, 20, 20}, // Rpm now ntf
        {0x009, 1, 21, 21}, // Rpm target cmd
};

static uint8 TxBuffer[BUFFER_SIZE];
static uint8 RxBuffer[BUFFER_SIZE];

const Com_ConfigType Com_PCConfig =
    {
        ComIpdu,
        10U,
        TxBuffer,
        BUFFER_SIZE,
        RxBuffer,
        BUFFER_SIZE};