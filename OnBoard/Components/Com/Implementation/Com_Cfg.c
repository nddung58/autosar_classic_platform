#include "Com.h"

#define BUFFER_SIZE (uint16)256u

static const ComIpduType ComIpdu[] =
    {
        {0x000u, 1, 0, 0},   // Control led blue cmd
        {0x001u, 1, 1, 1},   // Control led blue rsp
        {0x002u, 7, 2, 2},   // echo reverse cmd
        {0x003u, 7, 9, 9},   // echo reverse rsp
        {0x004u, 1, 16, 16}, // pedal ntf
        {0x005u, 1, 17, 17}, // brake ntf
        {0x006u, 1, 18, 18}, // gear
        {0x007u, 1, 19, 19}, // mode
        {0x008u, 1, 20, 20}, // Rpm now ntf
        {0x009u, 2, 21, 21}, // Rpm target cmd
        {0x00Au, 2, 23, 23}, // Steering angle
        {0x00Bu, 2, 25, 25}, // Wheel angle
        {0x00Cu, 1, 27, 27}, // Speed ntf
};

static uint8 TxBuffer[BUFFER_SIZE];
static uint8 RxBuffer[BUFFER_SIZE];

const Com_ConfigType Com_PCConfig =
    {
        ComIpdu,
        13U,
        TxBuffer,
        BUFFER_SIZE,
        RxBuffer,
        BUFFER_SIZE};
