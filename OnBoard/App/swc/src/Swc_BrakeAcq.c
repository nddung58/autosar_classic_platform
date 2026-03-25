#include "Swc_BrakeAcq.h"
#include "utils.h"
#include "Rte.h"

#define BRAKEEMA_SHIFT_K 1u

static Brake_StatusType s_brake;
static uint16 s_brakeFiltQ;

static void BrakeAcq_SeedFromHw(void)
{
    uint8 raw = 0u;

    if (Rte_Call_BrakeAcq_IoHwAb_Brake_ReadPct(&raw) == E_OK)
    {
        raw = clamp_0_100(raw);

        s_brakeFiltQ = ((uint16)raw) << BRAKEEMA_SHIFT_K;
        s_brake.outPct = raw;
        s_brake.filt_q = raw;

        (void)Rte_Write_BrakeAcq_BrakeOut(s_brake.outPct);
    }
}

void Swc_BrakeAcq_Init(void)
{
    s_brake.inited = FALSE;
    s_brake.outPct = 0u;
    s_brake.filt_q = 0u;
    s_brakeFiltQ = 0u;

    BrakeAcq_SeedFromHw();
}

void Swc_BrakeAcq_Run10ms(void)
{
    uint8 raw = 0u;
    uint16 raw_q;
    uint8 out;

    /* get sample from IoHwAb -> RTE */
    if (Rte_Call_BrakeAcq_IoHwAb_Brake_ReadPct(&raw) != E_OK)
    {
        return;
    }

    raw = clamp_0_100(raw);

    /* first valid sample after init */
    if (s_brake.inited == FALSE)
    {
        s_brakeFiltQ = ((uint16)raw) << BRAKEEMA_SHIFT_K;
        s_brake.outPct = raw;
        s_brake.filt_q = raw;
        s_brake.inited = TRUE;

        (void)Rte_Write_BrakeAcq_BrakeOut(s_brake.outPct);
        return;
    }

    /* Exponential Moving Average (QK) */
    /* filt_q += ((raw<<K) - filt_q) >> K; */
    raw_q = ((uint16)raw) << BRAKEEMA_SHIFT_K;
    s_brakeFiltQ = (uint16)(s_brakeFiltQ + ((raw_q - s_brakeFiltQ) >> BRAKEEMA_SHIFT_K));

    out = (uint8)(s_brakeFiltQ >> BRAKEEMA_SHIFT_K);

    s_brake.filt_q = out;
    if (out != s_brake.outPct)
    {
        s_brake.outPct = out;
        (void)Rte_Write_BrakeAcq_BrakeOut(s_brake.outPct);
    }
}