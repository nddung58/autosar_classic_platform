#include "Swc_PedalAcq.h"
#include "utils.h"
#include "Rte.h"

#define PEDALEMA_SHIFT_K 3 // 2->5
#define PEDAL_RATE_LIMIT_STEP 10

static Pedal_StateType s_pedal;

static void PedalAcq_SeedFromHw(void)
{
}

void Swc_PedalAcq_Init(void)
{
    s_pedal.filt_q = 0u;
    s_pedal.outPct = 0u;
    s_pedal.inited = FALSE;

    PedalAcq_SeedFromHw();
}

void Swc_PedalAcq_Run10ms(void)
{
    uint8 raw = 0u;
    /* get sample for IoHwAb -> RTE*/
    if (Rte_Call_PedalAcq_IoHwAb_Pedal_ReadPct(&raw) != E_OK)
    {
        return;
    }
    raw = clamp_0_100(raw);

    /* Exponential Moving Average (QK)*/
    /* filt_q += ((raw<<K) - filt_q) >>K ;*/
    uint16 raw_q = ((uint16)raw) << PEDALEMA_SHIFT_K;
    s_pedal.filt_q = (uint16)(s_pedal.filt_q + ((raw_q - s_pedal.filt_q) >> PEDALEMA_SHIFT_K));

    uint8 target = (uint8)(s_pedal.filt_q >> PEDALEMA_SHIFT_K);

    /* Slew Rate Limiter*/
    uint8 step = PEDAL_RATE_LIMIT_STEP;

    uint8 out = s_pedal.outPct;

    if (target > out)
    {
        uint8 inc = (uint8)((target - out) > step ? step : (target - out));
        out = (uint8)(out + inc);
    }
    else if (target < out)
    {
        uint8 dec = (uint8)((out - target) > step ? step : (out - target));
        out = (uint8)(out - dec);
    }

    // Publish
    if (out != s_pedal.outPct)
    {
        s_pedal.outPct = out;
        (void)Rte_Write_PedalAcq_PedalOut(s_pedal.outPct);
    }
}
