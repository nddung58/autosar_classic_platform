#include "steering_encoder.h"
#include "CDD_Qdec.h"

#define QDEC_COUNTER_MAX   ((uint32)65535U)
#define QDEC_COUNTER_RANGE (QDEC_COUNTER_MAX + 1U)

static float SteeringEncoder_GetScaling(const steering_encoder_t *encoder);
static sint32 SteeringEncoder_ComputeDelta(const steering_encoder_t *encoder, const Qdec_StateType *qdecState);

static float SteeringEncoder_GetScaling(const steering_encoder_t *encoder)
{
    if ((encoder == NULL_PTR) ||
        (encoder->timer_period <= 0.0f) ||
        (STEERING_ENCODER_TICKS_PER_REV == 0U))
    {
        return 0.0f;
    }

    return (STEERING_ENCODER_TWOPI /
            ((float)STEERING_ENCODER_TICKS_PER_REV * encoder->timer_period));
}

static sint32 SteeringEncoder_ComputeDelta(const steering_encoder_t *encoder, const Qdec_StateType *qdecState)
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

void SteeringEncoder_Get(steering_encoder_t *encoder)
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
        delta = SteeringEncoder_ComputeDelta(encoder, &qdecState);
        scaling = SteeringEncoder_GetScaling(encoder);
        encoder->velocity = scaling * (float)delta;
        encoder->position += ((float)delta * STEERING_ENCODER_TWOPI) /
                             (float)STEERING_ENCODER_TICKS_PER_REV;
    }

    encoder->direction = (qdecState.mCountDir != FALSE) ? 1U : 0U;
    encoder->last_counter_value = (sint32)qdecState.mCounter;
}

void SteeringEncoder_Reset(steering_encoder_t *encoder)
{
    Qdec_StateType qdecState;

    if (encoder == NULL_PTR)
    {
        return;
    }

    Qdec_SetMode(encoder->QdecModuleId, QDEC_MODE_NORMAL);
    Qdec_ResetState(encoder->QdecModuleId);
    qdecState = Qdec_GetState(encoder->QdecModuleId);

    encoder->position = 0.0f;
    encoder->velocity = 0.0f;
    encoder->first_time = 1U;
    encoder->direction = (qdecState.mCountDir != FALSE) ? 1U : 0U;
    encoder->last_counter_value = (sint32)qdecState.mCounter;
}
