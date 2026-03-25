#include "Rte.h"
#include "Rte_Cbk.h"
#include "Com.h"
#include "IoHwAb.h"

#if defined(ECU_CENTRAL)
#include "Swc_SafetyManager.h"
#include "Swc_SpeedCalculation.h"
#elif defined(ECU_CONTROL)
#endif

static Rte_RxSignalStatusType Rte_Buffer_ComRx_Status[RTE_CBK_SIG_MAX];
static Rte_TxSignalStatusType Rte_Buffer_ComTx_Status[RTE_CBK_SIG_MAX];

static uint16 Rte_Buffer_RpmTarget;

#if defined(ECU_CENTRAL)
static uint8 Rte_Buffer_LedBlue = 0;
static uint8 Rte_Buffer_PedalPct = 0;
static uint8 Rte_Buffer_BrakePct = 0;
static uint8 Rte_Buffer_DriveMode = 0;
static uint8 Rte_Buffer_GearSel = 0;

static uint8 Rte_Buffer_VcuCmdTx_PedalThrottle;
static uint8 Rte_Buffer_VcuCmdTx_BrakeThrottle;
static uint8 Rte_Buffer_VcuCmdTx_DriveMode;
static uint8 Rte_Buffer_VcuCmdTx_GearSel;
static uint16 Rte_Buffer_VcuCmdTx_RpmTarget;
#elif defined(ECU_CONTROL)

#endif

/* Callback / Notification Functions*/
/* Successful transmission*/
void Rte_CbkTxAck(CbkHandleIdType ComUserCbkHandleId)
{
    if (ComUserCbkHandleId >= RTE_CBK_SIG_MAX)
    {
        return;
    }

    Rte_Buffer_ComTx_Status[ComUserCbkHandleId].txAck = TRUE;
    Rte_Buffer_ComTx_Status[ComUserCbkHandleId].txErr = FALSE;
    Rte_Buffer_ComTx_Status[ComUserCbkHandleId].txTimeout = FALSE;
    Rte_Buffer_ComTx_Status[ComUserCbkHandleId].updated = FALSE;
}

/* not possible because the corresponding I-PDU is stopped */
void Rte_CbkTxErr(CbkHandleIdType ComUserCbkHandleId)
{
    if (ComUserCbkHandleId >= RTE_CBK_SIG_MAX)
    {
        return;
    }

    Rte_Buffer_ComTx_Status[ComUserCbkHandleId].txAck = FALSE;
    Rte_Buffer_ComTx_Status[ComUserCbkHandleId].txErr = TRUE;
}

/* transmission error has been detected by the deadline monitoring mechanism */
void Rte_CbkTxTOut(CbkHandleIdType ComUserCbkHandleId)
{
    if (ComUserCbkHandleId >= RTE_CBK_SIG_MAX)
    {
        return;
    }

    Rte_Buffer_ComTx_Status[ComUserCbkHandleId].txTimeout = TRUE;
}

/* receive success */
void Rte_CbkRxAck(CbkHandleIdType ComUserCbkHandleId)
{
    if (ComUserCbkHandleId >= RTE_CBK_SIG_MAX)
    {
        return;
    }

    Rte_Buffer_ComRx_Status[ComUserCbkHandleId].updated = TRUE;
    Rte_Buffer_ComRx_Status[ComUserCbkHandleId].timeout = FALSE;
    Rte_Buffer_ComRx_Status[ComUserCbkHandleId].invalid = FALSE;
}

/* receive timeout */
void Rte_CbkRxTOut(CbkHandleIdType ComUserCbkHandleId)
{
    if (ComUserCbkHandleId >= RTE_CBK_SIG_MAX)
    {
        return;
    }

    Rte_Buffer_ComRx_Status[ComUserCbkHandleId].timeout = TRUE;
}

/* Received Invalid Signal */
void Rte_CbkInv(CbkHandleIdType ComUserCbkHandleId)
{
    if (ComUserCbkHandleId >= RTE_CBK_SIG_MAX)
    {
        return;
    }

    Rte_Buffer_ComRx_Status[ComUserCbkHandleId].invalid = TRUE;
}

/* Com request update signal */
void Com_CbkTxPrep(void)
{
}

/* Echo reverse*/

Std_ReturnType Rte_Read_EchoReverse_Echo_EchoCmd(uint8 *data)
{
    if (Rte_Buffer_ComRx_Status[RTE_CBK_SIG_ECHO_REVERSE_IN].updated == FALSE)
        return E_NOT_OK;
    Std_ReturnType ret = Com_ReceiveSignal(ECHO_REVERSE_CMD, data);
    if (ret == E_OK)
    {
        Rte_Buffer_ComRx_Status[RTE_CBK_SIG_ECHO_REVERSE_IN].updated = FALSE;
        return E_OK;
    }
    return E_NOT_OK;
}

Std_ReturnType Rte_Write_EchoReverse_Echo_EchoRsp(const uint8 *data)
{
    Std_ReturnType ret = Com_SendSignal(ECHO_REVERSE_RSP, data);
    if (ret == E_OK)
        return E_OK;
    return E_NOT_OK;
}

/* LedControl */
Std_ReturnType Rte_Call_LedControl_Analog_PotentPct(uint8 *pct)
{
    IoHwAb_StatusType status;
    Std_ReturnType ret = IoHwAb_Get_Analog_AnalogSignal_PotentPct(pct, &status);
    if (status.quality == IOHWAB_GOOD && ret == E_OK)
        return E_OK;

    return E_NOT_OK;
}

Std_ReturnType Rte_Call_LedControl_Pwm_SetDutty(uint8 dutty)
{
    IoHwAb_StatusType status;
    uint16 duttyCv = (uint16)(dutty * 10);
    Std_ReturnType ret = IoHwAb_Set_Duty_PwmSignal_LedRed(duttyCv, &status);
    if (status.quality == IOHWAB_GOOD && ret == E_OK)
        return E_OK;

    return E_NOT_OK;
}

Std_ReturnType Rte_Read_LedControl_ComCmd_LedBlueCmd(uint8 *level)
{
    if (Rte_Buffer_ComRx_Status[RTE_CBK_SIG_LED_BLUE_IN].updated == FALSE)
        return E_NOT_OK;
    Std_ReturnType ret = Com_ReceiveSignal(LED_BLUE_CMD, level);
    if (ret == E_OK)
    {
        Rte_Buffer_ComRx_Status[RTE_CBK_SIG_LED_BLUE_IN].updated = FALSE;
        return E_OK;
    }
    return E_NOT_OK;
}

Std_ReturnType Rte_Write_LedControl_ComRsp_LedBlueCmd(uint8 rsp)
{
    return (Std_ReturnType)Com_SendSignal(LED_BLUE_RSP, rsp);
}

Std_ReturnType Rte_Call_LedControl_Digital_SetLevel(uint8 level)
{
    if (level == Rte_Buffer_LedBlue)
        return E_OK;
    IoHwAb_StatusType s;

    Std_ReturnType ret = IoHwAb_Set_Digital_DigitalSignal_LedBlue(level, &s);
    if (s.quality == IOHWAB_GOOD)
        return ret;
    return E_NOT_OK;
}

#if defined(ECU_CENTRAL)

/* Pedal Acq Swc*/
Std_ReturnType Rte_Call_PedalAcq_IoHwAb_Pedal_ReadPct(uint8 *pct)
{
    IoHwAb_StatusType status;
    Std_ReturnType ret = IoHwAb_Get_Analog_AnalogSignal_PedalPct(pct, &status);
    if (status.quality == IOHWAB_GOOD && ret == E_OK)
        return E_OK;

    return E_NOT_OK;
}

Std_ReturnType Rte_Read_PedalAcq_PedalOut(uint8 *pct)
{
    if (pct == NULL)
    {
        return E_NOT_OK;
    }

    *pct = Rte_Buffer_PedalPct;
    return E_OK;
}

Std_ReturnType Rte_Write_PedalAcq_PedalOut(uint8 pct)
{
    if (pct >= 0 && pct <= 100)
    {
        Rte_Buffer_PedalPct = pct;
        return E_OK;
    }
    return E_NOT_OK;
}

/* Brake Acq Swc*/
Std_ReturnType Rte_Call_BrakeAcq_IoHwAb_Brake_ReadPct(uint8 *pct)
{
    IoHwAb_StatusType status;
    Std_ReturnType ret = IoHwAb_Get_Analog_AnalogSignal_BrakePct(pct, &status);
    if (status.quality == IOHWAB_GOOD && ret == E_OK)
        return E_OK;

    return E_NOT_OK;
}

Std_ReturnType Rte_Read_BrakeAcq_BrakeOut(uint8 *pct)
{
    if (pct == NULL)
    {
        return E_NOT_OK;
    }

    *pct = Rte_Buffer_BrakePct;
    return E_OK;
}

Std_ReturnType Rte_Write_BrakeAcq_BrakeOut(uint8 pct)
{
    if (pct >= 0 && pct <= 100)
    {
        Rte_Buffer_BrakePct = pct;
        return E_OK;
    }
    return E_NOT_OK;
}

/* Drive mode*/
Std_ReturnType Rte_Call_DriveMode_Digital_ReadDriveMode(uint8 *mode)
{
    IoHwAb_StatusType status;
    Std_ReturnType ret = IoHwAb_Get_Digital_DigitalSignal_DriveMode(mode, &status);
    if (status.quality == IOHWAB_GOOD)
        return ret;
    return E_NOT_OK;
}

Std_ReturnType Rte_Read_DriveMode_ModeOut(uint8 *mode)
{
    if (mode == NULL)
    {
        return E_NOT_OK;
    }

    *mode = Rte_Buffer_DriveMode;
    return E_OK;
}

Std_ReturnType Rte_Write_DriveMode_ModeOut(uint8 mode)
{
    Rte_Buffer_DriveMode = mode;
    return E_OK;
}

/* Gear Selector*/
Std_ReturnType Rte_Call_Gear_Digital_ReadGearSel(uint8 *gear)
{
    IoHwAb_StatusType statusP, statusR, statusN, statusD;
    uint8 gearP, gearR, gearN, gearD;
    uint8 mask = 0U;

    if (gear == NULL)
    {
        return E_NOT_OK;
    }

    /* Read all gear inputs */
    IoHwAb_Get_Digital_DigitalSignal_GearP(&gearP, &statusP);
    IoHwAb_Get_Digital_DigitalSignal_GearR(&gearR, &statusR);
    IoHwAb_Get_Digital_DigitalSignal_GearN(&gearN, &statusN);
    IoHwAb_Get_Digital_DigitalSignal_GearD(&gearD, &statusD);

    /* Check HW read status */
    if ((statusP.quality != IOHWAB_GOOD) ||
        (statusR.quality != IOHWAB_GOOD) ||
        (statusN.quality != IOHWAB_GOOD) ||
        (statusD.quality != IOHWAB_GOOD))
    {
        return E_NOT_OK;
    }

    /* Build bitmask */
    if (gearP != 0U)
    {
        mask |= 0x01U;
    }
    if (gearR != 0U)
    {
        mask |= 0x02U;
    }
    if (gearN != 0U)
    {
        mask |= 0x04U;
    }
    if (gearD != 0U)
    {
        mask |= 0x08U;
    }

    /* Decode */
    switch (mask)
    {
    case 0x01U:
        *gear = 0x00U;
        break;

    case 0x02U:
        *gear = 0x01U;
        break;

    case 0x04U:
        *gear = 0x02U;
        break;

    case 0x08U:
        *gear = 0x03U;
        break;

    default:
        /* 0 or multiple buttons pressed */
        return E_NOT_OK;
    }

    return E_OK;
}

Std_ReturnType Rte_Read_Gear_GearOut(uint8 *gear)
{
    if (gear == NULL)
    {
        return E_NOT_OK;
    }

    *gear = Rte_Buffer_GearSel;
    return E_OK;
}

Std_ReturnType Rte_Write_Gear_GearOut(uint8 gear)
{
    Rte_Buffer_GearSel = gear;
    return E_OK;
}

/* Safety Manager*/
Std_ReturnType Rte_Read_SafetyManager_PedalOut(uint8 *pct)
{
    if (pct == NULL)
        return E_NOT_OK;
    *pct = Rte_Buffer_PedalPct;
    return E_OK;
}
Std_ReturnType Rte_Read_SafetyManager_BrakeOut(uint8 *pct)
{
    if (pct == NULL)
        return E_NOT_OK;
    *pct = Rte_Buffer_BrakePct;
    return E_OK;
}
Std_ReturnType Rte_Read_SafetyManager_GearOut(uint8 *gear)
{
    if (gear == NULL)
        return E_NOT_OK;
    *gear = Rte_Buffer_GearSel;
    return E_OK;
}
Std_ReturnType Rte_Read_SafetyManager_DriveModeOut(uint8 *mode)
{
    if (mode == NULL)
        return E_NOT_OK;
    *mode = Rte_Buffer_DriveMode;
    return E_OK;
}

Std_ReturnType Rte_Write_SafetyManager_SafeOut(SafetyType safe)
{
    Rte_Buffer_PedalPct = safe.throttlePct;
    Rte_Buffer_BrakePct = safe.brake;
    Rte_Buffer_DriveMode = safe.driveMode;
    Rte_Buffer_GearSel = safe.gear;
    return E_OK;
}

/* Compute Speed*/
Std_ReturnType Rte_Read_ComputeSpeed_GetInput(ComputeSpeed_InputType *input)
{
    if (input == NULL)
        return E_NOT_OK;

    input.throttlePedal = Rte_Buffer_PedalPct;
    input.throttleBrake = Rte_Buffer_BrakePct;
    input.gear = Rte_Buffer_GearSel;
    input.mode = Rte_Buffer_DriveMode;
    return E_OK;
}

Std_ReturnType Rte_Write_ComputeSpeed_RpmTarget(uint16 rpm)
{
    Rte_Buffer_RpmTarget = rpm;
    return E_OK;
}

/* Cmd composer*/
Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_PedalReq_pct(uint8 pct)
{
    Rte_Buffer_VcuCmdTx_PedalThrottle = pct;
    return E_OK;
}
Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_BrakeReq_pct(uint8 pct)
{
    Rte_Buffer_VcuCmdTx_BrakeThrottle = pct;
    return E_OK;
}
Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_GearSel(uint8 gear)
{
    Rte_Buffer_VcuCmdTx_GearSel = gear;
    return E_OK;
}
Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_DriveMode(uint8 mode)
{
    Rte_Buffer_VcuCmdTx_DriveMode = mode;
    return E_OK;
}
Std_ReturnType Rte_Write_CmdComposer_VcuCmdTx_SpeedTarget_rpm(uint16 rpm)
{
    Rte_Buffer_VcuCmdTx_RpmTarget = rpm;
    return E_OK;
}

Std_ReturnType Rte_Trigger_CmdComposer_VcuCmdTx(void)
{
    Std_ReturnType ret = E_OK;
    Std_ReturnType op_ret;
    op_ret = Com_SendSignal(PEDAL_NTF, &Rte_Buffer_VcuCmdTx_PedalThrottle);
    if (op_ret == E_NOT_OK)
        ret = E_NOT_OK;
    op_ret = Com_SendSignal(BRAKE_NTF, &Rte_Buffer_VcuCmdTx_BrakeThrottle);
    if (op_ret == E_NOT_OK)
        ret = E_NOT_OK;
    op_ret = Com_SendSignal(GEAR_NTF, &Rte_Buffer_VcuCmdTx_GearSel);
    if (op_ret == E_NOT_OK)
        ret = E_NOT_OK;
    op_ret = Com_SendSignal(MODE_NTF, &Rte_Buffer_VcuCmdTx_DriveMode);
    if (op_ret == E_NOT_OK)
        ret = E_NOT_OK;
    op_ret = Com_SendSignal(RPM_TARGET_CMD, &Rte_Buffer_VcuCmdTx_RpmTarget);
    if (op_ret == E_NOT_OK)
        ret = E_NOT_OK;

    return ret;
}
#elif defined(ECU_CONTROL)
/* Motor control */
Std_ReturnType Rte_Call_MotorControl_PwmMotor1_SetDutty(uint16 dutty)
{
    IoHwAb_StatusType status;
    Std_ReturnType ret = IoHwAb_Set_Duty_PwmSignal_Motor1(dutty, &status);
    if (status.quality == IOHWAB_GOOD)
        return ret;
    return E_NOT_OK;
}
Std_ReturnType Rte_Call_MotorControl_PwmMotor2_SetDutty(uint16 dutty)
{
    IoHwAb_StatusType status;
    Std_ReturnType ret = IoHwAb_Set_Duty_PwmSignal_Motor2(dutty, &status);
    if (status.quality == IOHWAB_GOOD)
        return ret;
    return E_NOT_OK;
}
#endif
