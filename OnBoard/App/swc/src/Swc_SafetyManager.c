#include "Swc_SafetyManager.h"
#include "Swc_DriveModeMgr.h"
#include "Swc_GearSelector.h"
#include "Rte.h"
#include "utils.h"

#define SAFETY_TIMEOUT_TICKS 100U

static SafetyManager_StateType s_safety;

static void Safety_Seed(void)
{
    s_safety.missPedal = 0;
    s_safety.missBrake = 0;
    s_safety.missGear = 0;
    s_safety.missMode = 0;

    s_safety.lastSafe.pedal = 0;
    s_safety.lastSafe.gear = 0;
    s_safety.lastSafe.driveMode = 0;
    s_safety.lastSafe.brake = 0;
    s_safety.lastSafe.speed = 0;

    s_safety.inited = TRUE;
}

static boolean gear_is_valid(Gear_Type gear)
{
    return (gear >= GEAR_P) && (gear <= GEAR_D);
}

static uint8_t Safety_ApplyBrakeOverride(uint8_t throttle, uint8 brake)
{
    static boolean brakeActiveLatch = FALSE;

    if (brake >= 75U)
    {
        brakeActiveLatch = TRUE;
    }
    else if (throttle == 0u)
    {
        brakeActiveLatch = FALSE;
    }

    if (brakeActiveLatch == TRUE)
    {
        return 0u;
    }

    return throttle;
}

static Gear_Type Safety_ApplyGearInterlock(Gear_Type requested,
                                           boolean brake,
                                           Gear_Type current,
                                           uint8 speed)
{
    Gear_Type safeGear = current;
    boolean isStopped = (speed == 0U) ? TRUE : FALSE;

    if ((requested < GEAR_P) || (requested > GEAR_D))
    {
        return current;
    }

    switch (current)
    {
    case GEAR_P:
        if (requested == GEAR_P)
        {
            safeGear = GEAR_P;
        }
        else if (requested == GEAR_N)
        {
            safeGear = GEAR_N;
        }
        else if (requested == GEAR_R)
        {
            safeGear = ((brake == TRUE) && (isStopped == TRUE)) ? GEAR_R : GEAR_P;
        }
        else if (requested == GEAR_D)
        {
            safeGear = GEAR_P;
        }
        else
        {
            safeGear = GEAR_P;
        }
        break;

    case GEAR_R:
        if (requested == GEAR_R)
        {
            safeGear = GEAR_R;
        }
        else if (requested == GEAR_N)
        {
            safeGear = GEAR_N;
        }
        else if (requested == GEAR_P)
        {
            safeGear = ((brake == TRUE) && (isStopped == TRUE)) ? GEAR_P : GEAR_R;
        }
        else if (requested == GEAR_D)
        {
            /* khong cho R -> D truc tiep */
            safeGear = GEAR_R;
        }
        else
        {
            safeGear = GEAR_R;
        }
        break;

    case GEAR_N:
        if (requested == GEAR_N)
        {
            safeGear = GEAR_N;
        }
        else if (requested == GEAR_P)
        {
            safeGear = (isStopped == TRUE) ? GEAR_P : GEAR_N;
        }
        else if (requested == GEAR_R)
        {
            safeGear = ((brake == TRUE) && (isStopped == TRUE)) ? GEAR_R : GEAR_N;
        }
        else if (requested == GEAR_D)
        {
            safeGear = (brake == TRUE) ? GEAR_D : GEAR_N;
        }
        else
        {
            safeGear = GEAR_N;
        }
        break;

    case GEAR_D:
        if (requested == GEAR_D)
        {
            safeGear = GEAR_D;
        }
        else if (requested == GEAR_N)
        {
            safeGear = GEAR_N;
        }
        else if (requested == GEAR_R)
        {
            /* khong cho D -> R truc tiep */
            safeGear = GEAR_D;
        }
        else if (requested == GEAR_P)
        {
            safeGear = ((brake == TRUE) && (isStopped == TRUE)) ? GEAR_P : GEAR_D;
        }
        else
        {
            safeGear = GEAR_D;
        }
        break;

    default:
        safeGear = GEAR_P;
        break;
    }

    return safeGear;
}

void Swc_SafetyManager_Init(void)
{
    s_safety.inited = FALSE;
    Safety_Seed();
}

void Swc_SafetyManager_Run10ms(void)
{
    if (!s_safety.inited)
    {
        Safety_Seed();
    }

    uint8 pedalPctTmp = 0U;
    uint8 brakePctTmp = 0U;
    Gear_Type gearTmp = s_safety.lastSafe.gear;
    DriveMode_Type modeTmp = s_safety.lastSafe.driveMode;
    uint8 speedTmp;

    boolean havePedal = (Rte_Read_SafetyManager_PedalOut(&pedalPctTmp) == E_OK);
    boolean haveBrake = (Rte_Read_SafetyManager_BrakeOut(&brakePctTmp) == E_OK);
    boolean haveGear = (Rte_Read_SafetyManager_GearOut((uint8 *)&gearTmp) == E_OK);
    boolean haveMode = (Rte_Read_SafetyManager_DriveModeOut((uint8 *)&modeTmp) == E_OK);
    boolean haveSpeed = (Rte_Read_SafetyManager_ComNtf_Speed(&speedTmp) == E_OK);

    if (havePedal)
        s_safety.missPedal = 0U;
    else if (s_safety.missPedal < SAFETY_TIMEOUT_TICKS)
        s_safety.missPedal++;

    if (haveBrake)
        s_safety.missBrake = 0U;
    else if (s_safety.missBrake < SAFETY_TIMEOUT_TICKS)
        s_safety.missBrake++;

    if (haveGear)
        s_safety.missGear = 0U;
    else if (s_safety.missGear < SAFETY_TIMEOUT_TICKS)
        s_safety.missGear++;

    if (haveMode)
        s_safety.missMode = 0U;
    else if (s_safety.missMode < SAFETY_TIMEOUT_TICKS)
        s_safety.missMode++;

    {
        const boolean pedalTimeout = (s_safety.missPedal >= SAFETY_TIMEOUT_TICKS);
        const boolean brakeTimeout = (s_safety.missBrake >= SAFETY_TIMEOUT_TICKS);
        const boolean gearTimeout = (s_safety.missGear >= SAFETY_TIMEOUT_TICKS);
        const boolean modeTimeout = (s_safety.missMode >= SAFETY_TIMEOUT_TICKS);

        uint8 reqPedal = pedalTimeout ? 0U : (havePedal ? (uint8)clamp_0_100((int)pedalPctTmp) : s_safety.lastSafe.pedal);

        uint8 reqBrake = brakeTimeout ? 0U : (haveBrake ? (uint8)clamp_0_100((int)brakePctTmp) : s_safety.lastSafe.brake);

        Gear_Type reqGear = gearTimeout ? GEAR_P : ((haveGear && gear_is_valid(gearTmp)) ? gearTmp : s_safety.lastSafe.gear);

        DriveMode_Type reqMode = modeTimeout ? DMODE_ECO : (haveMode ? modeTmp : s_safety.lastSafe.driveMode);

        sint8 reqSpeed = haveSpeed ? speedTmp : s_safety.lastSafe.speed;

        uint8 safePedal = Safety_ApplyBrakeOverride(reqPedal, reqBrake);
        boolean brakePressed = (reqBrake > 0U) ? TRUE : FALSE;
        Gear_Type safeGear = Safety_ApplyGearInterlock(reqGear, brakePressed, s_safety.lastSafe.gear, reqSpeed);

        SafetyType out;
        out.pedal = safePedal;
        out.gear = safeGear;
        out.brake = reqBrake;
        out.driveMode = reqMode;
        out.speed = reqSpeed;

        s_safety.lastSafe.pedal = safePedal;
        s_safety.lastSafe.gear = safeGear;
        s_safety.lastSafe.driveMode = reqMode;
        s_safety.lastSafe.brake = reqBrake;
        s_safety.lastSafe.speed = reqSpeed;

        (void)Rte_Write_SafetyManager_SafeOut(out);
    }
}
