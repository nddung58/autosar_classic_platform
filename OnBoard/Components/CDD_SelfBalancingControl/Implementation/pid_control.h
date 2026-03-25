#ifndef INC_PID_CONTROL_H_
#define INC_PID_CONTROL_H_

#include "Std_Types.h"

typedef struct
{
    float32 p_gain;         /* p gain */
    float32 i_gain;         /* i gain */
    float32 d_gain;         /* d gain */
    float32 last_error;     /* last error. It is necesary to compute the derivative */
    float32 error_integral; /* integral of an error */
    float32 output;         /* output of the PID */
    uint16 sam_rate;        /* sampling rate */
    float32 integral_max;   /* Maximum of the error integral */
    float32 pid_max;        /* Maximum of the PID */
} pid_instance;

typedef enum
{
    pid_ok = 0,
    pid_numerical
} pid_typedef;

pid_typedef apply_pid(pid_instance *pid, float32 input_error);
void reset_pid(pid_instance *pid);
void set_pid(pid_instance *pid, float32 p, float32 i, float32 d);

#endif /* INC_PID_CONTROL_H_ */
