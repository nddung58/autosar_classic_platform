#include "Swc_CmdComposer.h"
#include "Rte.h"

static CmdComposer_StateType s_cmd;

void Swc_CmdComposer_Init(void)
{
    s_cmd.inited = TRUE;
}
void Swc_CmdComposer_Run10ms(void)
{
    if (s_cmd.inited == FALSE)
        Swc_CmdComposer_Init();

    CmdComposer_Type cmd;
    boolean haveSafe = (Rte_Read_CmdComposer_Cmd(&cmd) == E_OK);

#if defined(ECU_CENTRAL)
    uint8 pedal = haveSafe ? cmd.throttlePedal : s_cmd.lastCmd.throttlePedal;
    uint8 brake = haveSafe ? cmd.throttleBrake : s_cmd.lastCmd.throttleBrake;
    uint8 gear = haveSafe ? cmd.gear : s_cmd.lastCmd.gear;
    uint8 mode = haveSafe ? cmd.mode : s_cmd.lastCmd.mode;
    sint16 rpmTarget = haveSafe ? cmd.rpmTarget : s_cmd.lastCmd.rpmTarget;
    sint16 steeringAngle = haveSafe ? cmd.steeringAngle : s_cmd.lastCmd.steeringAngle;
    sint16 wheelAngle = haveSafe ? cmd.wheelAngle : s_cmd.lastCmd.wheelAngle;

    /* Write to shadow buffer Rte each signal*/
    (void)Rte_Write_CmdComposer_VcuCmdTx_PedalReq_pct(pedal);
    (void)Rte_Write_CmdComposer_VcuCmdTx_BrakeReq_pct(brake);
    (void)Rte_Write_CmdComposer_VcuCmdTx_GearSel(gear);
    (void)Rte_Write_CmdComposer_VcuCmdTx_DriveMode(mode);
    (void)Rte_Write_CmdComposer_VcuCmdTx_SpeedTarget_rpm(rpmTarget);
    (void)Rte_Write_CmdComposer_VcuCmdTx_Steering_Angle(steeringAngle);
    (void)Rte_Write_CmdComposer_VcuCmdTx_Wheel_Angle(wheelAngle);

    s_cmd.lastCmd.throttlePedal = pedal;
    s_cmd.lastCmd.throttleBrake = brake;
    s_cmd.lastCmd.gear = gear;
    s_cmd.lastCmd.mode = mode;
    s_cmd.lastCmd.rpmTarget = rpmTarget;
    s_cmd.lastCmd.steeringAngle = steeringAngle;
    s_cmd.lastCmd.wheelAngle = wheelAngle;
#elif defined(ECU_CONTROL)
    uint8 speed = haveSafe ? cmd.speed : s_cmd.lastCmd.speed;
    (void)Rte_Write_CmdComposer_VcuCmdTx_Speed(speed);
    s_cmd.lastCmd.speed = speed;
#endif

    (void)Rte_Trigger_CmdComposer_VcuCmdTx();
}
