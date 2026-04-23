#include "Swc_ComputeSpeed.h"
#include "Rte.h"

static Speed_StateType s_speed;

#define PEDAL_DEADZONE_PCT 5U
#define BRAKE_DEADZONE_PCT 5U

#define RPM_UP_STEP_10MS 35
#define RPM_DOWN_STEP_10MS 45

#define RPM_IDLE_P 800U
#define RPM_IDLE_R 850U
#define RPM_IDLE_N 800U
#define RPM_IDLE_D 850U

#define RPM_MAX_P 3500U
#define RPM_MAX_R 2500U
#define RPM_MAX_N 4500U
#define RPM_MAX_D 5000U

#define MODE_GAIN_ECO_PCT 70U
#define MODE_GAIN_NORMAL_PCT 85U
#define MODE_GAIN_SPORT_PCT 100U

#define BRAKE_RPM_DROP_PCT 35U
#define LOAD_GAIN_DRIVE_PCT 12U
#define LOAD_GAIN_REVERSE_PCT 18U

#define ENGINE_BRAKE_DROP_10MS 20
#define CREEP_RPM_D 950U
#define CREEP_RPM_R 900U

static uint16 GetRpmIdle(Gear_Type gear)
{
    switch (gear)
    {
    case GEAR_P:
        return RPM_IDLE_P;
    case GEAR_R:
        return RPM_IDLE_R;
    case GEAR_N:
        return RPM_IDLE_N;
    case GEAR_D:
        return RPM_IDLE_D;
    default:
        return RPM_IDLE_N;
    }
}

static uint16 GetRpmMax(Gear_Type gear)
{
    switch (gear)
    {
    case GEAR_P:
        return RPM_MAX_P;
    case GEAR_R:
        return RPM_MAX_R;
    case GEAR_N:
        return RPM_MAX_N;
    case GEAR_D:
        return RPM_MAX_D;
    default:
        return RPM_MAX_N;
    }
}

static uint8 GetModeGainPct(DriveMode_Type mode)
{
    switch (mode)
    {
    case DMODE_ECO:
        return MODE_GAIN_ECO_PCT;
    case DMODE_NOR:
        return MODE_GAIN_NORMAL_PCT;
    case DMODE_SPT:
        return MODE_GAIN_SPORT_PCT;
    default:
        return MODE_GAIN_NORMAL_PCT;
    }
}

static sint16 ApplyRateLimit(sint16 target, sint16 prev)
{
    sint16 upLimit = prev + RPM_UP_STEP_10MS;
    sint16 downLimit = prev - RPM_DOWN_STEP_10MS;

    if (target > upLimit)
    {
        return upLimit;
    }
    else if (target < downLimit)
    {
        return downLimit;
    }
    else
    {
        return target;
    }
}

static uint16 ShapeThrottlePct(uint8 pedalPct)
{
    return (uint16)(((35U * (uint16)pedalPct) +
                     ((65U * (uint16)pedalPct * (uint16)pedalPct) / 100U)) /
                    100U);
}

void Swc_ComputeSpeed_Init(void)
{
    s_speed.inited = TRUE;
    s_speed.input.throttlePedal = 0U;
    s_speed.input.throttleBrake = 0U;
    s_speed.input.gear = GEAR_P;
    s_speed.input.mode = DMODE_NOR;
    s_speed.rpmTarget = (sint16)RPM_IDLE_P;
}

void Swc_ComputeSpeed_Run10ms(void)
{
    ComputeSpeed_InputType input;
    uint16 rpmIdle;
    uint16 rpmMax;
    uint16 rpmSpan;
    uint16 throttleShapedPct;
    uint8 modeGainPct;
    sint32 rpmMagRaw;
    sint16 rpmMagCmd;
    sint16 rpmSignedCmd;
    Std_ReturnType ret;

    if (s_speed.inited == FALSE)
    {
        Swc_ComputeSpeed_Init();
    }

    ret = Rte_Read_ComputeSpeed_GetInput(&input);
    if (ret != E_OK)
    {
        return;
    }

    s_speed.input = input;

    if (input.throttlePedal < PEDAL_DEADZONE_PCT)
    {
        input.throttlePedal = 0U;
    }

    if (input.throttleBrake < BRAKE_DEADZONE_PCT)
    {
        input.throttleBrake = 0U;
    }

    rpmIdle = GetRpmIdle(input.gear);
    rpmMax = GetRpmMax(input.gear);
    modeGainPct = GetModeGainPct(input.mode);

    if (rpmMax <= rpmIdle)
    {
        /* fallback an toàn */
        s_speed.rpmTarget = 0;
        (void)Rte_Write_ComputeSpeed_RpmTarget(s_speed.rpmTarget);
        return;
    }

    rpmSpan = rpmMax - rpmIdle;
    throttleShapedPct = ShapeThrottlePct(input.throttlePedal);

    /* magnitude RPM base */
    rpmMagRaw = (sint32)rpmIdle;

    /* đạp ga thì tua tăng ở mọi số, kể cả P/N */
    rpmMagRaw += (sint32)(((uint32)modeGainPct *
                           (uint32)throttleShapedPct *
                           (uint32)rpmSpan) /
                          10000U);

    /* D/R có tải nên tua nhỉnh hơn nhẹ */
    if (input.gear == GEAR_D)
    {
        rpmMagRaw += (sint32)(((uint32)LOAD_GAIN_DRIVE_PCT * (uint32)rpmSpan) / 100U);
    }
    else if (input.gear == GEAR_R)
    {
        rpmMagRaw += (sint32)(((uint32)LOAD_GAIN_REVERSE_PCT * (uint32)rpmSpan) / 100U);
    }

    /* creep nhẹ chỉ ở D/R khi không ga không phanh */
    if ((input.throttlePedal == 0U) && (input.throttleBrake == 0U))
    {
        if (input.gear == GEAR_D)
        {
            if (rpmMagRaw < (sint32)CREEP_RPM_D)
            {
                rpmMagRaw = (sint32)CREEP_RPM_D;
            }
        }
        else if (input.gear == GEAR_R)
        {
            if (rpmMagRaw < (sint32)CREEP_RPM_R)
            {
                rpmMagRaw = (sint32)CREEP_RPM_R;
            }
        }
    }

    /* brake kéo tua xuống nhưng không thấp hơn idle */
    if (input.throttleBrake > 0U)
    {
        rpmMagRaw -= (sint32)(((uint32)input.throttleBrake *
                               (uint32)rpmSpan *
                               (uint32)BRAKE_RPM_DROP_PCT) /
                              10000U);
    }

    /* nhả ga ở D/R có engine braking nhẹ */
    if ((input.throttlePedal == 0U) &&
        (input.throttleBrake == 0U) &&
        ((input.gear == GEAR_D) || (input.gear == GEAR_R)))
    {
        rpmMagRaw -= ENGINE_BRAKE_DROP_10MS;
    }

    if (rpmMagRaw < (sint32)rpmIdle)
    {
        rpmMagCmd = (sint16)rpmIdle;
    }
    else if (rpmMagRaw > (sint32)rpmMax)
    {
        rpmMagCmd = (sint16)rpmMax;
    }
    else
    {
        rpmMagCmd = (sint16)rpmMagRaw;
    }

    /* custom control:
       - P/N: RPM dương, lên tua bình thường
       - D  : RPM dương
       - R  : RPM âm để dễ điều khiển
    */
    switch (input.gear)
    {
    case GEAR_R:
        rpmSignedCmd = (sint16)(-rpmMagCmd);
        break;

    case GEAR_P:
    case GEAR_N:
    case GEAR_D:
    default:
        rpmSignedCmd = rpmMagCmd;
        break;
    }

    s_speed.rpmTarget = ApplyRateLimit(rpmSignedCmd, s_speed.rpmTarget);

    (void)Rte_Write_ComputeSpeed_RpmTarget(s_speed.rpmTarget);
}