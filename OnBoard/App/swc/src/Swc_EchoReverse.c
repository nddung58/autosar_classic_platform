#include "Swc_EchoReverse.h"
#include "Rte.h"

#define ECHOREVERSE_LEN 7u

static EchoReverse_StateType echoReverse_s;

void Swc_EchoReverse_Init(void)
{
    echoReverse_s.inited = TRUE;
}

void Swc_EchoReverse_Run10ms(void)
{
    uint8 data[ECHOREVERSE_LEN];
    uint8 reversed[ECHOREVERSE_LEN];
    uint8 i;
    Std_ReturnType ret;

    if (echoReverse_s.inited != TRUE)
    {
        return;
    }

    /* Get data Com -> RTE */
    ret = Rte_Read_EchoReverse_Echo_EchoCmd(data);
    if (ret != E_OK)
    {
        return;
    }

    /* Reverse data */
    for (i = 0u; i < ECHOREVERSE_LEN; i++)
    {
        reversed[i] = data[ECHOREVERSE_LEN - 1u - i];
    }

    /* Publish reversed data RTE -> Com */
    (void)Rte_Write_EchoReverse_Echo_EchoRsp(reversed);
}