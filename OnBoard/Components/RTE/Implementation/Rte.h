#ifndef RTE_H__
#define RTE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
#include "Swc_CmdComposer.h"
#if defined(ECU_CENTRAL)
#include "Swc_SafetyManager.h"
#include "Swc_ComputeSpeed.h"

#elif defined(ECU_CONTROL)
#endif

    typedef struct
    {
        boolean updated;
        boolean timeout;
        boolean invalid;
    } Rte_RxSignalStatusType;

    typedef struct
    {
        boolean updated;
        boolean txTimeout;
        boolean txAck;
        boolean txErr;
    } Rte_TxSignalStatusType;

    /* Echo reverse*/

    Std_ReturnType Rte_Read_EchoReverse_Echo_EchoCmd(uint8 *data);
    Std_ReturnType Rte_Write_EchoReverse_Echo_EchoRsp(const uint8 *data);

    /* LedControl*/
    Std_ReturnType Rte_Call_LedControl_Analog_PotentPct(uint8 *pct);
    Std_ReturnType Rte_Call_LedControl_Pwm_SetDutty(uint8 dutty);
    Std_ReturnType Rte_Read_LedControl_ComCmd_LedBlueCmd(uint8 *level);
    Std_ReturnType Rte_Write_LedControl_ComRsp_LedBlueCmd(uint8 rsp);
    Std_ReturnType Rte_Call_LedControl_Digital_SetLevel(uint8 level);

    /* Cmd composer*/
    Std_ReturnType Rte_Read_CmdComposer_Cmd(CmdComposer_Type *cmd);
    Std_ReturnType Rte_Trigger_CmdComposer_VcuCmdTx(void);

#if defined(ECU_CENTRAL)
    /* Pedal Acq Swc*/
    Std_ReturnType Rte_Call_PedalAcq_IoHwAb_Pedal_ReadPct(uint8 *pct);
    Std_ReturnType Rte_Read_PedalAcq_PedalOut(uint8 *pct);
    Std_ReturnType Rte_Write_PedalAcq_PedalOut(uint8 pct);

    /* Brake Acq Swc*/
    Std_ReturnType Rte_Call_BrakeAcq_IoHwAb_Brake_ReadPct(uint8 *pct);
    Std_ReturnType Rte_Read_BrakeAcq_BrakeOut(uint8 *pct);
    Std_ReturnType Rte_Write_BrakeAcq_BrakeOut(uint8 pct);

    /* Drive Mode*/
    Std_ReturnType Rte_Call_DriveMode_Digital_ReadDriveMode(uint8 *mode);
    Std_ReturnType Rte_Read_DriveMode_ModeOut(uint8 *mode);
    Std_ReturnType Rte_Write_DriveMode_ModeOut(uint8 mode);

    /* Gear Selector*/
    Std_ReturnType Rte_Call_Gear_Digital_ReadGearSel(uint8 *gear);
    Std_ReturnType Rte_Read_Gear_GearOut(uint8 *gear);
    Std_ReturnType Rte_Write_Gear_GearOut(uint8 gear);

    /* Safety Manager*/
    Std_ReturnType Rte_Read_SafetyManager_PedalOut(uint8 *pct);
    Std_ReturnType Rte_Read_SafetyManager_BrakeOut(uint8 *pct);
    Std_ReturnType Rte_Read_SafetyManager_GearOut(uint8 *gear);
    Std_ReturnType Rte_Read_SafetyManager_DriveModeOut(uint8 *mode);
    Std_ReturnType Rte_Read_SafetyManager_ComNtf_Speed(uint8 *speed);
    Std_ReturnType Rte_Write_SafetyManager_SafeOut(SafetyType safe);

    /* Compute Speed*/
    Std_ReturnType Rte_Read_ComputeSpeed_GetInput(ComputeSpeed_InputType *input);
    Std_ReturnType Rte_Write_ComputeSpeed_RpmTarget(uint16 rpm);

    /* Cmd composer*/

    Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_PedalReq_pct(uint8 pct);
    Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_BrakeReq_pct(uint8 pct);
    Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_GearSel(uint8 gear);
    Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_DriveMode(uint8 mode);
    Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_SpeedTarget_rpm(sint16 rpm);
    Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_Steering_Angle(sint16 angle);
    Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_Wheel_Angle(sint16 angle);

    /* Steering Wheel */
    Std_ReturnType Rte_Call_SteeringWheelAcq_Steering_ReadAngle(sint16 *angle);

    Std_ReturnType Rte_Read_SteeringWheelAcq_SteeringAngle(sint16 *angle);
    Std_ReturnType Rte_Write_SteeringWheelAcq_SteeringAngle(sint16 angle);

    Std_ReturnType Rte_Read_SteeringWheelAcq_WheelAngle(sint16 *angle);
    Std_ReturnType Rte_Write_SteeringWheelAcq_WheelAngle(sint16 angle);

#elif defined(ECU_CONTROL)
/* Motor control */
Std_ReturnType Rte_Call_MotorControl_PwmMotor1_SetDutty(uint16 dutty);
Std_ReturnType Rte_Call_MotorControl_PwmMotor2_SetDutty(uint16 dutty);

/* Motor Control*/
Std_ReturnType Rte_Read_MotorControl_Inputs(sint16 *rpmTarget, sint16 *wheelAngle);
Std_ReturnType Rte_Call_PIDControl_Process(sint16 rpmTarget, sint16 wheelAngle, sint16 *mPctA, sint16 *mPctB);
Std_ReturnType Rte_Call_MotorControl_MotorA_SetDir(uint8 direction);
Std_ReturnType Rte_Call_MotorControl_MotorB_SetDir(uint8 direction);

Std_ReturnType Rte_Call_MotorControl_Pwm(uint16 motorA_duty, uint16 motorB_duty);

/* Cmd Composer*/
Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_Speed(uint8 speed);
#endif

#ifdef __cplusplus
}
#endif

#endif
