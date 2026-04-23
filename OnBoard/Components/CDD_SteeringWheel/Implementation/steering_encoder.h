#ifndef INC_STEERING_ENCODER_H_
#define INC_STEERING_ENCODER_H_

#include "Std_Types.h"

#define STEERING_ENCODER_TICKS_PER_REV (80U)
#define STEERING_ENCODER_TWOPI (6.28318530718f)

typedef struct
{
    float position;            /* Steering position in radians */
    float velocity;            /* Steering angular velocity in rad/s */
    sint32 last_counter_value; /* Previous counter value */
    float timer_period;        /* Sampling period in seconds */
    uint8 QdecModuleId;        /* QDEC instance ID */
    uint8 direction;           /* 0: decreasing, 1: increasing */
    uint8 first_time;          /* First run flag */
} steering_encoder_t;

void SteeringEncoder_Get(steering_encoder_t *encoder);
void SteeringEncoder_Reset(steering_encoder_t *encoder);

#endif /* INC_STEERING_ENCODER_H_ */