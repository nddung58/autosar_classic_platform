#include "math_utils.h"

uint8_t clamp_0_100(int value)
{
    if (value < 0)
    {
        return 0u;
    }
    else if (value > 100)
    {
        return 100u;
    }
    else
    {
        return (uint8_t)value;
    }
}