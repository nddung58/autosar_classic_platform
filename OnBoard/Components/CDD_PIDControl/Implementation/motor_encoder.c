#include "motor_encoder.h"
#include "CDD_Qdec.h"

#define QDEC_COUNTER_MIN ((uint32)0U)
#define QDEC_COUNTER_MAX ((uint32)65535U)
#define QDEC_COUNTER_RANGE (QDEC_COUNTER_MAX - QDEC_COUNTER_MIN + 1U)

static float MotorEncoder_GetScaling(const encoder_inst *encoder);
static sint32 MotorEncoder_ComputeDelta(const encoder_inst *encoder, const Qdec_StateType *qdecState);

static float MotorEncoder_GetScaling(const encoder_inst *encoder)
{
    return (TWOPI / ((float)NUMBER_OF_TICKS_PER_REV * encoder->timer_period));
}

static sint32 MotorEncoder_ComputeDelta(const encoder_inst *encoder, const Qdec_StateType *qdecState)
{
    uint32 currentCounter;
    uint32 lastCounter;

    currentCounter = qdecState->mCounter;
    lastCounter = (uint32)encoder->last_counter_value;

    if (currentCounter == lastCounter)
    {
        return 0;
    }

    if (qdecState->mTimerOverflow != FALSE)
    {
        if (qdecState->mTimerOverflowDir != FALSE)
        {
            return (sint32)currentCounter +
                   (sint32)(QDEC_COUNTER_RANGE - lastCounter);
        }
        else
        {
            return -((sint32)lastCounter +
                     (sint32)(QDEC_COUNTER_RANGE - currentCounter));
        }
    }

    return ((sint32)currentCounter - (sint32)lastCounter);
}

void MotorEncoder_GetSpeed(encoder_inst *encoder)
{
    Qdec_StateType qdecState;
    sint32 delta;
    float scaling;

    if (encoder == NULL_PTR)
    {
        return;
    }

    qdecState = Qdec_GetState(encoder->QdecModuleId);

    if (encoder->first_time != 0U)
    {
        encoder->velocity = 0.0f;
        encoder->first_time = 0U;
    }
    else
    {
        delta = MotorEncoder_ComputeDelta(encoder, &qdecState);
        scaling = MotorEncoder_GetScaling(encoder);
        encoder->velocity = scaling * (float)delta;
    }

    apply_average_filter(&encoder->motor_vel_filter,
                         encoder->velocity,
                         &encoder->velocity);

    encoder->position += encoder->velocity * encoder->timer_period;
    encoder->last_counter_value = (sint32)qdecState.mCounter;
}

void MotorEncoder_Reset(encoder_inst *encoder)
{
    Qdec_StateType qdecState;

    if (encoder == NULL_PTR)
    {
        return;
    }

    Qdec_ResetState(encoder->QdecModuleId);
    qdecState = Qdec_GetState(encoder->QdecModuleId);

    encoder->position = 0.0f;
    encoder->velocity = 0.0f;
    encoder->first_time = 1U;
    encoder->last_counter_value = (sint32)qdecState.mCounter;

    reset_average_filter(&encoder->motor_vel_filter, MOVING_AVERAGE_ENCODER);
}