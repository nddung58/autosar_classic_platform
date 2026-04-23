#include "Swc_MotorController.h"
#include "Std_Types.h"
#include "Rte.h"

static Motor_StateType s_sb;

void Swc_MotorController_Init(void)
{
    s_sb.rpmTarget = 0;
    s_sb.wheelAngle = 0;
    s_sb.SB_state = IDLE;
    s_sb.inited = TRUE;
}
void Swc_MotorController_Run10ms(void)
{
    if (s_sb.inited != TRUE)
    {
        Swc_MotorController_Init();
    }

    sint16 rpm, wheelAngle, mPctA, mPctB;
    Std_ReturnType ret = Rte_Read_MotorControl_Inputs(&rpm, &wheelAngle);

    s_sb.rpmTarget = rpm;
    s_sb.wheelAngle = wheelAngle;
    ret = Rte_Call_PIDControl_Process(s_sb.rpmTarget, s_sb.wheelAngle, &mPctA, &mPctB);

    uint16 motorA_duty, motorB_duty;
    if (mPctA > 1000)
    {
        mPctA = 1000;
    }
    else if (mPctA < -1000)
    {
        mPctA = -1000;
    }
    if (mPctA < 0)
    {
        (void)Rte_Call_MotorControl_MotorA_SetDir((uint8)1U);
        motorA_duty = (uint16)((-(sint32)mPctA * 0x8000U) / 1000U);
    }
    else
    {
        (void)Rte_Call_MotorControl_MotorA_SetDir((uint8)0U);
        motorA_duty = (uint16)(((sint32)mPctA * 0x8000U) / 1000U);
    }

    if (mPctB > 1000)
    {
        mPctB = 1000;
    }
    else if (mPctB < -1000)
    {
        mPctB = -1000;
    }
    if (mPctB < 0)
    {
        (void)Rte_Call_MotorControl_MotorB_SetDir((uint8)1U);
        motorB_duty = (uint16)((-(sint32)mPctB * 0x8000U) / 1000U);
    }
    else
    {
        (void)Rte_Call_MotorControl_MotorB_SetDir((uint8)0U);
        motorB_duty = (uint16)(((sint32)mPctB * 0x8000U) / 1000U);
    }

    (void)Rte_Call_MotorControl_Pwm(motorA_duty, motorB_duty);
}