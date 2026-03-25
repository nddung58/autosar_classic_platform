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

    s_safety.lastSafe.throttlePct = 0;
    s_safety.lastSafe.gear = 0;
    s_safety.lastSafe.driveMode = 0;
    s_safety.lastSafe.brake = FALSE;

    s_safety.inited = TRUE;
}

static boolean gear_is_valid(Gear_Type gear)
{
    return (gear >= GEAR_P) && (gear <= GEAR_D);
}

static uint8_t Safety_ApplyBrakeOverride(uint8_t throttle, uint8 brake)
{
    static boolean brakeActiveLatch = FALSE;

    if (brake >= 50U)
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

static Gear_Type Safety_ApplyGearInterlock(Gear_Type requested, boolean brake, Gear_Type current)
{
    Gear_Type safeGear = current;

    switch (current)
    {
    case GEAR_P:
        if ((requested == GEAR_R) || (requested == GEAR_D))
        {
            safeGear = (brake == TRUE) ? requested : GEAR_P;
        }
        else if (requested == GEAR_N)
        {
            safeGear = GEAR_N;
        }
        else
        {
            safeGear = GEAR_P;
        }
        break;

    case GEAR_R:
        if (requested == GEAR_P)
        {
            safeGear = (brake == TRUE) ? GEAR_P : GEAR_R;
        }
        else if (requested == GEAR_N)
        {
            safeGear = GEAR_N;
        }
        else if (requested == GEAR_D)
        {
            safeGear = GEAR_D;
        }
        else
        {
            safeGear = GEAR_R;
        }
        break;

    case GEAR_N:
        if (requested == GEAR_P)
        {
            safeGear = GEAR_P;
        }
        else if (requested == GEAR_R)
        {
            safeGear = (brake == TRUE) ? GEAR_R : GEAR_N;
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
        if (requested == GEAR_P)
        {
            safeGear = (brake == TRUE) ? GEAR_P : GEAR_D;
        }
        else if (requested == GEAR_N)
        {
            safeGear = GEAR_N;
        }
        else if (requested == GEAR_R)
        {
            safeGear = GEAR_R;
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
        Safety_Seed();

    uint8 pedalPctTmp;
    uint8 brakePctTmp;
    Gear_Type gearTmp;
    DriveMode_Type modeTmp;

    boolean havePedal = (Rte_Read_SafetyManager_PedalOut(&pedalPctTmp) == E_OK);
    boolean haveBrake = (Rte_Read_SafetyManager_BrakeOut(&brakePctTmp) == E_OK);
    boolean haveGear = (Rte_Read_SafetyManager_GearOut((uint8 *)&gearTmp) == E_OK);
    boolean haveMode = (Rte_Read_SafetyManager_DriveModeOut((uint8 *)&modeTmp) == E_OK);

    const boolean pedalTimeout = (s_safety.missPedal >= SAFETY_TIMEOUT_TICKS);
    const boolean brakeTimeout = (s_safety.missBrake >= SAFETY_TIMEOUT_TICKS);
    const boolean gearTimeout = (s_safety.missGear >= SAFETY_TIMEOUT_TICKS);
    const boolean modeTimeout = (s_safety.missMode >= SAFETY_TIMEOUT_TICKS);

    uint8_t reqThrottle = pedalTimeout ? 0u : (havePedal ? (uint8_t)clamp_0_100((int)pedalPctTmp) : s_safety.lastSafe.throttlePct);
    uint8 reqBrake = brakeTimeout ? 0U : (haveBrake ? (uint8_t)clamp_0_100((int)brakePctTmp) : s_safety.lastSafe.brake);
    Gear_Type reqGear = gearTimeout ? GEAR_P : (haveGear && gear_is_valid(gearTmp) ? gearTmp : s_safety.lastSafe.gear);
    DriveMode_Type reqMode = modeTimeout ? DMODE_ECO : (haveMode ? modeTmp : s_safety.lastSafe.driveMode);

    /* Apply safety restraints*/
    /* Brake overide with throttle*/
    uint8 safeThrottle = Safety_ApplyBrakeOverride(reqThrottle, reqBrake);

    /* Interlock change gear P <-> R/D right brake*/
    Gear_Type safeGear = Safety_ApplyGearInterlock(reqGear, reqBrake, gearTmp);

    /* Pack Safe_s and transfer to RTE*/
    SafetyType out;
    out.throttlePct = safeThrottle;
    out.gear = safeGear;
    out.brake = reqBrake;
    out.driveMode = reqMode;
    (void)Rte_Write_SafetyManager_SafeOut(out);
}
