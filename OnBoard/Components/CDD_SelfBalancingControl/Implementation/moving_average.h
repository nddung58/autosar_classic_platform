#ifndef INC_MOVING_AVERAGE_H_
#define INC_MOVING_AVERAGE_H_

#include "Std_Types.h"

#define MOVING_AVERAGE_LENGTH 16

typedef float32 filter_type;
typedef struct
{
    filter_type buffer[MOVING_AVERAGE_LENGTH];
    uint16 counter;
    filter_type out;
    filter_type sum;
    uint16_t length;
} mov_aver_instance;

void reset_average_filter(mov_aver_instance *instance, uint16 length);
void apply_average_filter(mov_aver_instance *instance, filter_type input, filter_type *out);

#endif /* INC_MOVING_AVERAGE_H_ */
