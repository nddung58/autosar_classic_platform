#include "IoHwAb.h"
#include "Dio.h"

/***************************************** Signal states ******************************************/

IoHwAb_LockType IoHwAb_DigitalSignal_LedBlue_Locked = IOHWAB_UNLOCKED;
IoHwAb_LevelType IoHwAb_DigitalSignal_LedBlue_Saved = IOHWAB_LOW;
const IoHwAb_LevelType IoHwAb_DigitalSignal_LedRed_Default = IOHWAB_LOW;

/*************************************** Local functions ******************************************/

static Dio_LevelType IoHwAb_MapToDioLevel(IoHwAb_LevelType level)
{
    return (level == IOHWAB_HIGH) ? STD_HIGH : STD_LOW;
}

static IoHwAb_LevelType IoHwAb_MapFromDioLevel(Dio_LevelType level)
{
    return (level == STD_HIGH) ? IOHWAB_HIGH : IOHWAB_LOW;
}

/**************************************** Digital outputs *****************************************/

/********************************* DigitalSignal_LedRed functions *********************************/

Std_ReturnType IoHwAb_Set_Digital_DigitalSignal_LedBlue(
    IoHwAb_LevelType newValue,
    IoHwAb_StatusType *status)
{
    Dio_LevelType setLevel;

    IOHWAB_VALIDATE_RETURN((status != NULL_PTR),
                           IOHWAB_DIGITAL_SET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    if (IoHwAb_DigitalSignal_LedBlue_Locked == IOHWAB_UNLOCKED)
    {
        IoHwAb_DigitalSignal_LedBlue_Saved = newValue;
        setLevel = IoHwAb_MapToDioLevel(newValue);
    }
    else
    {
        setLevel = IoHwAb_MapToDioLevel(IoHwAb_DigitalSignal_LedBlue_Saved);
    }

    Dio_WriteChannel(IoHwAb_ConfigPtr->Dio_Channel[IOHWAB_SIGNAL_DIGITALSIGNAL_LEDBLUE], setLevel);

    status->quality = IOHWAB_GOOD;
    return E_OK;
}

Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_LedBlue(
    IoHwAb_LevelType *value,
    IoHwAb_StatusType *status)
{
    Dio_LevelType readLevel;

    IOHWAB_VALIDATE_RETURN((value != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    IOHWAB_VALIDATE_RETURN((status != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    readLevel = Dio_ReadChannel(IoHwAb_ConfigPtr->Dio_Channel[IOHWAB_SIGNAL_DIGITALSIGNAL_LEDBLUE]);
    *value = IoHwAb_MapFromDioLevel(readLevel);
    status->quality = IOHWAB_GOOD;

    return E_OK;
}

/***************************************** Digital inputs *****************************************/

Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_GearP(
    IoHwAb_LevelType *value,
    IoHwAb_StatusType *status)
{
    Dio_LevelType readLevel;

    IOHWAB_VALIDATE_RETURN((value != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    IOHWAB_VALIDATE_RETURN((status != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    readLevel = Dio_ReadChannel(IoHwAb_ConfigPtr->Dio_Channel[IOHWAB_SIGNAL_DIGITALSIGNAL_GEARP]);
    *value = IoHwAb_MapFromDioLevel(readLevel);
    status->quality = IOHWAB_GOOD;

    return E_OK;
}

Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_GearN(
    IoHwAb_LevelType *value,
    IoHwAb_StatusType *status)
{
    Dio_LevelType readLevel;

    IOHWAB_VALIDATE_RETURN((value != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    IOHWAB_VALIDATE_RETURN((status != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    readLevel = Dio_ReadChannel(IoHwAb_ConfigPtr->Dio_Channel[IOHWAB_SIGNAL_DIGITALSIGNAL_GEARN]);
    *value = IoHwAb_MapFromDioLevel(readLevel);
    status->quality = IOHWAB_GOOD;

    return E_OK;
}

Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_GearD(
    IoHwAb_LevelType *value,
    IoHwAb_StatusType *status)
{
    Dio_LevelType readLevel;

    IOHWAB_VALIDATE_RETURN((value != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    IOHWAB_VALIDATE_RETURN((status != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    readLevel = Dio_ReadChannel(IoHwAb_ConfigPtr->Dio_Channel[IOHWAB_SIGNAL_DIGITALSIGNAL_GEARD]);
    *value = IoHwAb_MapFromDioLevel(readLevel);
    status->quality = IOHWAB_GOOD;

    return E_OK;
}

Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_GearR(
    IoHwAb_LevelType *value,
    IoHwAb_StatusType *status)
{
    Dio_LevelType readLevel;

    IOHWAB_VALIDATE_RETURN((value != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    IOHWAB_VALIDATE_RETURN((status != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    readLevel = Dio_ReadChannel(IoHwAb_ConfigPtr->Dio_Channel[IOHWAB_SIGNAL_DIGITALSIGNAL_GEARR]);
    *value = IoHwAb_MapFromDioLevel(readLevel);
    status->quality = IOHWAB_GOOD;

    return E_OK;
}

Std_ReturnType IoHwAb_Get_Digital_DigitalSignal_DriveMode(
    IoHwAb_LevelType *value,
    IoHwAb_StatusType *status)
{
    Dio_LevelType readLevel;

    IOHWAB_VALIDATE_RETURN((value != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    IOHWAB_VALIDATE_RETURN((status != NULL_PTR),
                           IOHWAB_DIGITAL_GET_ID,
                           IOHWAB_E_PARAM_POINTER,
                           E_NOT_OK);

    readLevel = Dio_ReadChannel(IoHwAb_ConfigPtr->Dio_Channel[IOHWAB_SIGNAL_DIGITALSIGNAL_DRIVEMODE]);
    *value = IoHwAb_MapFromDioLevel(readLevel);
    status->quality = IOHWAB_GOOD;

    return E_OK;
}

/************************************* Parameterized digital **************************************/

Std_ReturnType IoHwAb_Set_Digital(
    IoHwAb_SignalType signal,
    IoHwAb_LevelType newValue,
    IoHwAb_StatusType *status)
{
    IOHWAB_VALIDATE_RETURN(IOHWAB_SIGNAL_IS_VALID_DIGITAL_OUTPUT(signal),
                           IOHWAB_DIGITAL_SET_ID,
                           IOHWAB_E_PARAM_SIGNAL,
                           E_NOT_OK);

    switch (signal)
    {
    case IOHWAB_SIGNAL_DIGITALSIGNAL_LEDBLUE:
    {
        return IoHwAb_Set_Digital_DigitalSignal_LedBlue(newValue, status);
    }

    default:
    {
        return E_NOT_OK;
    }
    }
}

Std_ReturnType IoHwAb_Get_Digital(
    IoHwAb_SignalType signal,
    IoHwAb_LevelType *value,
    IoHwAb_StatusType *status)
{
    IOHWAB_VALIDATE_RETURN(
        (IOHWAB_SIGNAL_IS_VALID_DIGITAL_INPUT(signal) ||
         (signal == IOHWAB_SIGNAL_DIGITALSIGNAL_LEDBLUE)),
        IOHWAB_DIGITAL_GET_ID,
        IOHWAB_E_PARAM_SIGNAL,
        E_NOT_OK);

    switch (signal)
    {
    case IOHWAB_SIGNAL_DIGITALSIGNAL_LEDBLUE:
    {
        return IoHwAb_Get_Digital_DigitalSignal_LedBlue(value, status);
    }

    case IOHWAB_SIGNAL_DIGITALSIGNAL_GEARP:
    {
        return IoHwAb_Get_Digital_DigitalSignal_GearP(value, status);
    }

    case IOHWAB_SIGNAL_DIGITALSIGNAL_GEARN:
    {
        return IoHwAb_Get_Digital_DigitalSignal_GearN(value, status);
    }

    case IOHWAB_SIGNAL_DIGITALSIGNAL_GEARD:
    {
        return IoHwAb_Get_Digital_DigitalSignal_GearD(value, status);
    }

    case IOHWAB_SIGNAL_DIGITALSIGNAL_GEARR:
    {
        return IoHwAb_Get_Digital_DigitalSignal_GearR(value, status);
    }

    case IOHWAB_SIGNAL_DIGITALSIGNAL_DRIVEMODE:
    {
        return IoHwAb_Get_Digital_DigitalSignal_DriveMode(value, status);
    }

    default:
    {
        return E_NOT_OK;
    }
    }
}