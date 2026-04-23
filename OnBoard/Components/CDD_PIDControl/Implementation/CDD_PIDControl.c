#include "CDD_PIDControl.h"
#include "CDD_PIDControl_Cfg.h"
#include "Std_Types.h"
#include "motor_encoder.h"
#include "pid_control.h"

#define TWOPI (6.28318530718f)
#define RPM_TO_RADPS (TWOPI / 60.0f)

static const PID_ConfigType *SelfBalancing_ConfigPtr = (const PID_ConfigType *)0;

extern const PID_ConfigType SelfBalancing_PCConfig;

/* Motor encoders */
static encoder_inst motora_enc =
    {
        .first_time = 1U,
        .QdecModuleId = 0U,
        .last_counter_value = 0,
        .position = 0.0f,
        .timer_period = 0.01f,
        .velocity = 0.0f};

static encoder_inst motorb_enc =
    {
        .first_time = 1U,
        .QdecModuleId = 1U,
        .last_counter_value = 0,
        .position = 0.0f,
        .timer_period = 0.01f,
        .velocity = 0.0f};

/* Speed PID */
static pid_instance motor_pid =
    {
        .d_gain = 0.0f,
        .error_integral = 0.0f,
        .i_gain = 25.0f,
        .integral_max = 5000.0f,
        .last_error = 0.0f,
        .output = 0.0f,
        .p_gain = 20.0f,
        .pid_max = 100.0f, /* PID output limited to [-100, 100] */
        .sam_rate = 100.0f /* 100 Hz */
};

static float CDD_PIDControl_RpmToRadPerSec(sint16 rpm);
static sint16 CDD_PIDControl_OutputToMotorPct(float pidOutput);
static float CDD_PIDControl_GetAverageVelocity(void);

static float CDD_PIDControl_RpmToRadPerSec(sint16 rpm)
{
    return ((float)rpm) * RPM_TO_RADPS;
}

static sint16 CDD_PIDControl_OutputToMotorPct(float pidOutput)
{
    float scaledOutput = pidOutput * 10.0f; /* [-100..100] -> [-1000..1000] */

    if (scaledOutput > 1000.0f)
    {
        scaledOutput = 1000.0f;
    }
    else if (scaledOutput < -1000.0f)
    {
        scaledOutput = -1000.0f;
    }

    return (sint16)scaledOutput;
}

static float CDD_PIDControl_GetAverageVelocity(void)
{
    return (motora_enc.velocity + motorb_enc.velocity) * 0.5f;
}

Std_ReturnType PIDControl_Init(const PID_ConfigType *config)
{
#if (STD_ON == PIDCONTROL_PRECOMPILE_SUPPORT)
    SelfBalancing_ConfigPtr = &SelfBalancing_PCConfig;
    (void)config;
#else
    if (config == NULL_PTR)
    {
        return E_NOT_OK;
    }
    SelfBalancing_ConfigPtr = config;
#endif

    MotorEncoder_Reset(&motora_enc);
    MotorEncoder_Reset(&motorb_enc);
    reset_pid(&motor_pid);

    return E_OK;
}

Std_ReturnType PIDControl_Compute(sint16 rpmTarget,
                                  sint16 wheelAngle,
                                  sint16 *mPctA,
                                  sint16 *mPctB)
{
    float targetVelocity;
    float actualVelocity;
    float speedError;
    pid_typedef pidStatus;
    sint16 motorCommand;

    (void)wheelAngle;

    if ((mPctA == NULL_PTR) || (mPctB == NULL_PTR))
    {
        return E_NOT_OK;
    }

    /* Update encoder speed */
    MotorEncoder_GetSpeed(&motora_enc);
    MotorEncoder_GetSpeed(&motorb_enc);

    /* Encoder velocity is assumed in rad/s */
    actualVelocity = CDD_PIDControl_GetAverageVelocity();

    /* Convert target RPM to rad/s */
    targetVelocity = CDD_PIDControl_RpmToRadPerSec(rpmTarget);

    /* PID error */
    speedError = targetVelocity - actualVelocity;

    /* Apply PID */
    pidStatus = apply_pid(&motor_pid, speedError);
    if (pidStatus != pid_ok)
    {
        *mPctA = 0;
        *mPctB = 0;
        return E_NOT_OK;
    }

    /* Convert PID output to motor command in range [-1000 .. 1000] */
    motorCommand = CDD_PIDControl_OutputToMotorPct(motor_pid.output);

    *mPctA = motorCommand;
    *mPctB = motorCommand;

    return E_OK;
}