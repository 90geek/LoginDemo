//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file IpmiBmc.c
    IPMI Transport Driver.

**/

#include "IpmiBmc.h"

/**
    Updates the SoftErrorCount variable based on the BMC Error input

    @param BmcError - BMC Error
    @param IpmiInstance - Data structure describing BMC
                variables and used for sending commands

    @return EFI_STATUS 
    @retval EFI_SUCCESS is returned

**/
EFI_STATUS
UpdateSoftErrorCount (
  IN        UINT8                       BmcError,
  IN OUT    EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance )
{
    UINT8   Errors[] = {0xC0, 0xC3, 0xC4, 0xC9, 0xCE, 0xCF, 0xFF, 0x00};
    UINT8   i;

    i = 0;
    while (Errors[i] != 0) {
        if (Errors[i] == BmcError) {
            IpmiInstance->SoftErrorCount++;
            break;
        }
        i++;
    }
    return EFI_SUCCESS;
}

/**
    BT interface IPMI send command Implementation

    @param This -  Pointer to IPMI Protocol/PPI
    @param NetFunction - Net function of the command
    @param LUN - Logical Unit number of the command
    @param Command - Command to be sent to BMC
    @param CommandData - Command data to be sent along with Command
    @param CommandDataSize - Command Data size
    @param ResponseData - Response Data from BMC
    @param ResponseDataSize - Size of the Response data
    @param Context - NULL here

    @return EFI_STATUS Status returned from BMC while executing the command.

**/
EFI_STATUS
IpmiBtSendCommand (
  IN EFI_IPMI_TRANSPORT               *This,
  IN UINT8                            NetFunction,
  IN UINT8                            Lun,
  IN UINT8                            Command,
  IN UINT8                            *CommandData,
  IN UINT8                            CommandDataSize,
  OUT UINT8                           *ResponseData,
  OUT UINT8                           *ResponseDataSize,
  IN VOID                             *Context )
{
    EFI_IPMI_BMC_INSTANCE_DATA          *IpmiInstance;
    UINT8                               DataSize;
    EFI_STATUS                          Status;
    UINT8                               Seq = 0;

    if (!ResponseDataSize || (!ResponseData && *ResponseDataSize)) {
        return EFI_INVALID_PARAMETER;
    }

    IpmiInstance = INSTANCE_FROM_EFI_SM_IPMI_BMC_THIS (This);

    IpmiInstance->TempData[0] = 0x03 + CommandDataSize;//netfn+cmd+seq+data
    IpmiInstance->TempData[1] = (UINT8) ((NetFunction << 2) | (Lun & 0xfc));
    IpmiInstance->TempData[2] = Seq;
    IpmiInstance->TempData[3] = Command;

    if (CommandDataSize > 0) {
        if (CommandData == NULL) {
            return EFI_INVALID_PARAMETER;
        }
        if (CommandDataSize <= (MAX_TEMP_DATA - 4) ) {
            CopyMem (&IpmiInstance->TempData[4], CommandData, CommandDataSize);
        } else {
            return EFI_BAD_BUFFER_SIZE;
        }
    }
    if ((Status = SendDataToBtBmcPort (IpmiInstance, Context, IpmiInstance->TempData,
                                   (CommandDataSize + 4))) != EFI_SUCCESS ) {
        IpmiInstance->BmcStatus = EFI_BMC_SOFTFAIL;
        IpmiInstance->SoftErrorCount++;
        return Status;
    }
    DataSize = MAX_TEMP_DATA;
    if ((Status = ReceiveBmcDataFromBtPort (IpmiInstance, Context,
                IpmiInstance->TempData, &DataSize)) != EFI_SUCCESS) {
        IpmiInstance->BmcStatus = EFI_BMC_SOFTFAIL;
        IpmiInstance->SoftErrorCount++;
        return Status;
    }
    This->CommandCompletionCode = IpmiInstance->TempData[4];
    if (ERROR_COMPLETION_CODE(This->CommandCompletionCode)) {
        UpdateSoftErrorCount (This->CommandCompletionCode, IpmiInstance);
        // Write completion code into return buffer if an IPMI command returns an error
        if (*ResponseDataSize) {
            *ResponseData = This->CommandCompletionCode;
            *ResponseDataSize = 1;
        }
        return EFI_DEVICE_ERROR;
    }

    if (DataSize < 4) {
        return EFI_DEVICE_ERROR;
    }

    if ((DataSize - 4) > *ResponseDataSize) {
        *ResponseDataSize = (UINT8) (DataSize - 4);
        return EFI_BUFFER_TOO_SMALL;
    }

    //
    // Copying the response data into ResponseData buffer
    //
    CopyMem (ResponseData, &IpmiInstance->TempData[5], (DataSize - 4));
    *ResponseDataSize = (UINT8) (DataSize - 4);

    return EFI_SUCCESS;
}

/**
    IPMI send command API for BT interface

    @param  This -  Pointer to IPMI Protocol/PPI
    @param  NetFunction - Net function of the command
    @param  LUN - Logical Unit number of the command
    @param  Command - Command to be sent to BMC
    @param  CommandData - Command data to be sent along with Command
    @param  CommandDataSize - Command Data size
    @param  ResponseData - Response Data from BMC
    @param  ResponseDataSize - Size of the Response data

    @return EFI_STATUS Status returned from BMC while executing the command.

**/
EFI_STATUS
EfiBtIpmiSendCommand (
  IN EFI_IPMI_TRANSPORT *This,
  IN UINT8              NetFunction,
  IN UINT8              Lun,
  IN UINT8              Command,
  IN UINT8              *CommandData,
  IN UINT8              CommandDataSize,
  OUT UINT8             *ResponseData,
  OUT UINT8             *ResponseDataSize )
{
    return IpmiBtSendCommand (
            This,
            NetFunction,
            Lun,
            Command,
            CommandData,
            CommandDataSize,
            ResponseData,
            ResponseDataSize,
            NULL);
}

/**
    KCS interface IPMI send command Implementation

    @param  This -  Pointer to IPMI Protocol/PPI
    @param  NetFunction - Net function of the command
    @param  LUN - Logical Unit number of the command
    @param  Command - Command to be sent to BMC
    @param  CommandData - Command data to be sent along with Command
    @param  CommandDataSize - Command Data size
    @param  ResponseData - Response Data from BMC
    @param  ResponseDataSize - Size of the Response data
    @param  Context - NULL here

    @return EFI_STATUS Status returned from BMC while executing the command.

**/
EFI_STATUS
IpmiSendCommand (
  IN EFI_IPMI_TRANSPORT               *This,
  IN UINT8                            NetFunction,
  IN UINT8                            Lun,
  IN UINT8                            Command,
  IN UINT8                            *CommandData,
  IN UINT8                            CommandDataSize,
  OUT UINT8                           *ResponseData,
  OUT UINT8                           *ResponseDataSize,
  IN VOID                             *Context )
{
    EFI_IPMI_BMC_INSTANCE_DATA          *IpmiInstance;
    UINT8                               DataSize;
    EFI_STATUS                          Status;

    if (!ResponseDataSize || (!ResponseData && *ResponseDataSize)) {
        return EFI_INVALID_PARAMETER;
    }

    IpmiInstance = INSTANCE_FROM_EFI_SM_IPMI_BMC_THIS (This);

    if (IpmiInstance->SoftErrorCount >= MAX_BMC_CMD_FAIL_COUNT) {
        return EFI_NOT_READY;
    }

    IpmiInstance->TempData[0] = (UINT8) ((NetFunction << 2) | (Lun & 0x03));
    IpmiInstance->TempData[1] = Command;
    if (CommandDataSize > 0) {
        if (CommandData == NULL) {
            return EFI_INVALID_PARAMETER;
        }
        if (CommandDataSize <= (MAX_TEMP_DATA - 2)) {
            CopyMem (&IpmiInstance->TempData[2], CommandData, CommandDataSize);
        } else {
           return EFI_BAD_BUFFER_SIZE;
        }
    }
    if ((Status = SendDataToBmcPort (IpmiInstance, Context, IpmiInstance->TempData,
                                (CommandDataSize + 2))) != EFI_SUCCESS) {
        IpmiInstance->BmcStatus = EFI_BMC_SOFTFAIL;
        IpmiInstance->SoftErrorCount++;
        return Status;
    }
    DataSize = MAX_TEMP_DATA;
    if ((Status = ReceiveBmcDataFromPort (IpmiInstance, Context,
                IpmiInstance->TempData, &DataSize)) != EFI_SUCCESS) {
        IpmiInstance->BmcStatus = EFI_BMC_SOFTFAIL;
        IpmiInstance->SoftErrorCount++;
        return Status;
    }
    This->CommandCompletionCode = IpmiInstance->TempData[2];
    if (ERROR_COMPLETION_CODE(This->CommandCompletionCode)) {
        UpdateSoftErrorCount (This->CommandCompletionCode, IpmiInstance);
        // Write completion code into return buffer if an IPMI command returns an error
        if (*ResponseDataSize) {
            *ResponseData = This->CommandCompletionCode;
            *ResponseDataSize = 1;
        }
        return EFI_DEVICE_ERROR;
    }

    if (DataSize < 3) {
        return EFI_DEVICE_ERROR;
    }

    if ((DataSize - 3) > *ResponseDataSize) {
        *ResponseDataSize = (UINT8) (DataSize - 3);
        return EFI_BUFFER_TOO_SMALL;
    }

    //
    // Copying the response data into ResponseData buffer
    //
    CopyMem (ResponseData, &IpmiInstance->TempData[3], (DataSize - 3));
    *ResponseDataSize = (UINT8) (DataSize - 3);

    return EFI_SUCCESS;
}

/**
    IPMI send command API for KCS interface

    @param  This -  Pointer to IPMI Protocol/PPI
    @param  NetFunction - Net function of the command
    @param  LUN - Logical Unit number of the command
    @param  Command - Command to be sent to BMC
    @param  CommandData - Command data to be sent along with Command
    @param  CommandDataSize - Command Data size
    @param  ResponseData - Response Data from BMC
    @param  ResponseDataSize - Size of the Response data

    @return EFI_STATUS Status returned from BMC while executing the command.

**/
EFI_STATUS
EfiIpmiSendCommand (
  IN EFI_IPMI_TRANSPORT *This,
  IN UINT8              NetFunction,
  IN UINT8              Lun,
  IN UINT8              Command,
  IN UINT8              *CommandData,
  IN UINT8              CommandDataSize,
  OUT UINT8             *ResponseData,
  OUT UINT8             *ResponseDataSize )
{
    return IpmiSendCommand (
            This,
            NetFunction,
            Lun,
            Command,
            CommandData,
            CommandDataSize,
            ResponseData,
            ResponseDataSize,
            NULL );
}

/**
    IPMI BMC status Implementation

    @param  This - Pointer to IPMI Protocol/PPI
    @param  BmcStatus - State of the BMC
    @param  ComAddress - BMC Communication address
    @param  Context - NULL here

    @retval EFI_STATUS EFI_SUCCESS Status returned

**/
EFI_STATUS
IpmiBmcStatus (
  IN EFI_IPMI_TRANSPORT               *This,
  OUT EFI_BMC_STATUS                  *BmcStatus,
  OUT EFI_SM_COM_ADDRESS              *ComAddress,
  IN  VOID                            *Context )
{
    EFI_STATUS                            Status;
    UINT8                                 DataSize;
    EFI_SM_CTRL_INFO                      ControllerInfo;
    EFI_IPMI_BMC_INSTANCE_DATA            *IpmiInstance;

    IpmiInstance = INSTANCE_FROM_EFI_SM_IPMI_BMC_THIS (This);

    DataSize = sizeof (EFI_SM_CTRL_INFO);

    //
    // Get the device ID information for the BMC.
    //
    Status = This->SendIpmiCommand (
                &IpmiInstance->IpmiTransport,
                EFI_SM_NETFN_APP,
                BMC_LUN,
                EFI_APP_GET_DEVICE_ID,
                NULL,
                0,
                (UINT8*)&ControllerInfo,
                &DataSize );

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Get Device ID Command: Status %r\n", Status));
    //
    // If there is no error then proceed to check the data returned by the BMC
    //
    if (!EFI_ERROR(Status)) {
        //
        // If the controller is in Update Mode then set the BMC Status to indicate
        // the BMC is in force update mode.
        //
        if (ControllerInfo.UpdateMode != 0) {
            IpmiInstance->BmcStatus = EFI_BMC_UPDATE_IN_PROGRESS;
        } else {
            IpmiInstance->BmcStatus = EFI_BMC_OK;
        }
    } else {
        if (IpmiInstance->SoftErrorCount >= MAX_SOFT_COUNT) {
            IpmiInstance->BmcStatus = EFI_BMC_HARDFAIL;
        } else {
            IpmiInstance->BmcStatus = EFI_BMC_SOFTFAIL;
        }
    }

    *BmcStatus = IpmiInstance->BmcStatus;
    ComAddress->ChannelType = EfiSmBmc;
    ComAddress->Address.BmcAddress.SlaveAddress = IpmiInstance->SlaveAddress;
    ComAddress->Address.BmcAddress.ChannelAddress = 0x0;

    return EFI_SUCCESS;
}

/**
    IPMI BMC status API

    @param  This -  Pointer to IPMI Protocol/PPI
    @param  BmcStatus - State of the BMC
    @param  ComAddress - BMC Communication address

    @return EFI_STATUS
    @retval EFI_SUCCESS Status returned

**/
EFI_STATUS
EfiIpmiBmcStatus (
  IN EFI_IPMI_TRANSPORT               *This,
  OUT EFI_BMC_STATUS                  *BmcStatus,
  OUT EFI_SM_COM_ADDRESS              *ComAddress )
{
    return IpmiBmcStatus (This, BmcStatus, ComAddress, NULL);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
