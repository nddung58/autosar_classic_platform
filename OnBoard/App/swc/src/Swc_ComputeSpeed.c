#include "Swc_ComputeSpeed.h"

static Speed_StateType s_speed;

#define RPM_MAX 5000U
#define PEDAL_DEADZONE_PCT 5U
#define BRAKE_DEADZONE_PCT 5U

#define RPM_UP_STEP_10MS 20U
#define RPM_DOWN_STEP_10MS 30U

#define RPM_IDLE_P 0U
#define RPM_IDLE_N 0U
#define RPM_IDLE_D 0U
#define RPM_IDLE_R 0U

#define RPM_MAX_P 0U
#define RPM_MAX_N 4000U
#define RPM_MAX_D 4500U
#define RPM_MAX_R 2500U

#define MODE_GAIN_ECO_PCT 55U
#define MODE_GAIN_NORMAL_PCT 75U
#define MODE_GAIN_SPORT_PCT 100U

static uint16 GetRpmBase(Gear_Type gear)
{
    switch (gear)
    {
    case GEAR_P:
        return RPM_IDLE_P;
    case GEAR_N:
        return RPM_IDLE_N;
    case GEAR_D:
        return RPM_IDLE_D;
    case GEAR_R:
        return RPM_IDLE_R;
    default:
        return 0U;
    }
}

static uint16 GetRpmMax(Gear_Type gear)
{
    switch (gear)
    {
    case GEAR_P:
        return RPM_MAX_P;
    case GEAR_N:
        return RPM_MAX_N;
    case GEAR_D:
        return RPM_MAX_D;
    case GEAR_R:
        return RPM_MAX_R;
    default:
        return 0U;
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

static uint16 ApplyRateLimit(uint16 target, uint16 prev)
{
    uint16 upLimit = prev + RPM_UP_STEP_10MS;
    uint16 downLimit = (prev > RPM_DOWN_STEP_10MS) ? (prev - RPM_DOWN_STEP_10MS) : 0U;

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

void Swc_ComputeSpeed_Init(void)
{
    s_speed.inited = TRUE;
    s_speed.input.throttlePedal = 0U;
    s_speed.input.throttleBrake = 0U;
    s_speed.input.gear = GEAR_P;
    s_speed.input.mode = DMODE_NOR;
    s_speed.rpmTarget = 0U;
}

void Swc_ComputeSpeed_Run10ms(void)
{
    ComputeSpeed_InputType input;
    uint16 rpmBase;
    uint16 rpmMax;
    uint16 rpmSpan;
    uint16 rpmRaw;
    uint16 rpmCmd;
    uint16 throttleShapedPct;
    uint8 modeGainPct;
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

    rpmBase = GetRpmBase(input.gear);
    rpmMax = GetRpmMax(input.gear);
    modeGainPct = GetModeGainPct(input.mode);

    if (rpmMax <= rpmBase)
    {
        s_speed.rpmTarget = rpmBase;
        return;
    }

    rpmSpan = rpmMax - rpmBase;

    /* throttle shaping: nhẹ ở đầu pedal, mạnh dần về cuối */
    throttleShapedPct =
        (uint16)(((35U * (uint16)input.throttlePedal) +
                  ((65U * (uint16)input.throttlePedal * (uint16)input.throttlePedal) / 100U)) /
                 100U);

    rpmRaw = rpmBase;
    rpmRaw += (uint16)(((uint32)modeGainPct * (uint32)throttleShapedPct * (uint32)rpmSpan) / 10000U);

    /* brake kéo rpm xuống */
    rpmRaw -= (uint16)(((uint32)input.throttleBrake * (uint32)rpmSpan) / 100U);

    /* chống underflow */
    if (rpmRaw > RPM_MAX)
    {
        rpmRaw = 0U;
    }

    if ((sint32)rpmRaw < (sint32)rpmBase)
    {
        rpmCmd = rpmBase;
    }
    else if (rpmRaw > rpmMax)
    {
        rpmCmd = rpmMax;
    }
    else
    {
        rpmCmd = rpmRaw;
    }

    s_speed.rpmTarget = ApplyRateLimit(rpmCmd, s_speed.rpmTarget);

    (void)Rte_Write_ComputeSpeed_RpmTarget(s_speed.rpmTarget);
}