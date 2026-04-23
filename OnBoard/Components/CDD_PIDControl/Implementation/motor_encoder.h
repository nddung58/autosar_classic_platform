#ifndef INC_MOTOR_ENCODER_H_
#define INC_MOTOR_ENCODER_H_

#include "Std_Types.h"
#include "moving_average.h"

#define NUMBER_OF_TICKS_PER_REV (1980U)
#define ONE_REV_LENGTH_CM (22U)
#define TWOPI (6.28318530718f)
#define MOVING_AVERAGE_ENCODER (70U)

typedef struct
{
    float velocity;            /* velocity of the motor radians/sec*/
    float position;            /* position of the motor (radians) */
    sint32 last_counter_value; /* counter value for the last iteration*/
    float timer_period;        /* period */
    uint8 QdecModuleId;
    uint8 first_time;                   /*flag that shows whether it has been run for the first time*/
    mov_aver_instance motor_vel_filter; /* filter to smooth the velocity values*/
} encoder_inst;

void MotorEncoder_GetSpeed(encoder_inst *encoder);
void MotorEncoder_Reset(encoder_inst *encoder);
#endif /* INC_MOTOR_ENCODER_H_ */
