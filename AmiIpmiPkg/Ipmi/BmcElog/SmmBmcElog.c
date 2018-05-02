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

/** @file SmmBmcElog.c
    Server Management SMM BMC ELOG Driver. This driver is
    able to talk to the IPMI aware controller and logs the data into a
    SEL repository.

**/

//----------------------------------------------------------------------

#include <Include/BmcElog.h>
#include <Library/SmmServicesTableLib.h>

//----------------------------------------------------------------------

//
// Module Global variables
//
EFI_BMC_ELOG_INSTANCE_DATA        *gRedirProtoPrivate = NULL;
EFI_IPMI_TRANSPORT                *gIpmiTransport = NULL;

/**
    This function checks for the erasure status

    @param  ReserveID Reservation Id for SEL Access

    @retval EFI_SUCCESS SEL is erased successfully
    @retval EFI_NO_RESPONSE If time out occurred and still SEL is not erased successfully

**/

EFI_STATUS
WaitTillErased (
  UINT8            *ReserveId )
{
    EFI_STATUS              Status;
    INTN                    Counter = 0x200;
    EFI_CLEAR_SEL           ClearSelData;
    UINT8                   ClearSelResponse;
    UINT8                   ClearSelResponseDataSize;

    while ( TRUE ) {

        ClearSelResponseDataSize = sizeof (ClearSelResponse);
        ClearSelData.Reserve[0] = ReserveId[0];
        ClearSelData.Reserve[1] = ReserveId[1];
        ClearSelData.AscC = C_CHAR_ASCII_VALUE;
        ClearSelData.AscL = L_CHAR_ASCII_VALUE;
        ClearSelData.AscR = R_CHAR_ASCII_VALUE;
        ClearSelData.Erase = GET_ERASE_STATUS;

        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_STORAGE,
                    BMC_LUN,
                    EFI_STORAGE_CLEAR_SEL,
                    (UINT8 *) &ClearSelData,
                    sizeof (EFI_CLEAR_SEL),
                    (UINT8 *) &ClearSelResponse,
                    (UINT8 *) &ClearSelResponseDataSize );

        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_STORAGE_CLEAR_SEL Status: %r ClearSelResponse: %x Counter: %x\n", Status, ClearSelResponse, Counter));
        if ( (!EFI_ERROR(Status)) && (ClearSelResponse == ERASURE_COMPLETED) ) {
            return EFI_SUCCESS;
        }
        if ( (EFI_ERROR(Status)) && (gIpmiTransport->CommandCompletionCode == INVALID_RESERVATION_ID)) {
           //
           // Get New Reservation Id and process further.
           //
           Status = GetReservationId (ReserveId);
           if (EFI_ERROR(Status)) {
               return Status;
           }
        }
        //
        //  If there is not a response from the BMC controller we need to return and not hang.
        //
        --Counter;
        if (Counter == 0x0) {
            return EFI_NO_RESPONSE;
        }
    }
}

/**
    This function verifies if the BMC SEL is full.

    @param VOID

    @retval TRUE If SEL is full
    @retval False If SEL is not full

**/

BOOLEAN
IsSELFull (
  VOID )
{
    EFI_SEL_INFO         SelInfo = {0};
    UINT8                SelInfoSize = sizeof (SelInfo);
    EFI_STATUS           Status;

    //
    // Get SEL information from the BMC.
    //
    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_STORAGE,
                BMC_LUN,
                EFI_STORAGE_GET_SEL_INFO,
                NULL,
                0,
                (UINT8 *) &SelInfo,
                (UINT8 *) &SelInfoSize );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_STORAGE_GET_SEL_INFO Status: %r (SelInfo.OperationSupport & OVERFLOW_FLAG_MASK): %x\n", Status, (SelInfo.OperationSupport & OVERFLOW_FLAG_MASK)));
    if ( EFI_ERROR (Status) ) {
        return FALSE;
    }

    return  (SelInfo.OperationSupport & OVERFLOW_FLAG_MASK);
}

/**
    Sends the Event-Log data to the destination. Destination can be a remote
    target like LAN, ICMB, local targets BMC,IPMB or a Firmware-Volume.
    A Redirect Protocol Driver resolves final destination.

    @param This - Instance of EFI_SM_ELOG_PROTOCOL
    @param ElogData - Pointer to the Event-Log data that needs to be recorded.
    @param DataType - Type of Elog Data that is being recorded.
                 Elog is redirected based upon this information.
    @param AlertEvent - This is an indication that the input data type is an Alert.
                  The underlying drivers to decide if they need to listen to the
                  DataType and send it on an appropriate channel as an alert
                  use this information. Any Alert event logs are not
                  guaranteed to be retrieved or erased.
    @param Size - Size of the data to be logged.
    @param RecordId - This is the array of record IDs sent by the target.
                       This can be used to retrieve the records or erase the records.

    @return EFI_STATUS Return Status
    @retval EFI_SUCCESS Event-Log was recorded successfully
    @retval EFI_NOT_FOUND Event-Log target not found.
    @retval EFI_NO_RESPONSE Event-Log Target not responding.
    @retval EFI_PROTOCOL_ERROR Data Format Error found
    @retval EFI_INVALID_PARAMETER Invalid Parameter
    @retval EFI_OUT_OF_RESOURCES Not enough resources to record data.

**/

EFI_STATUS
EfiSetBmcElogData (
  IN  EFI_SM_ELOG_REDIR_PROTOCOL        *This,
  IN  UINT8                             *ElogData,
  IN  EFI_SM_ELOG_REDIR_TYPE            DataType,
  IN  BOOLEAN                           AlertEvent,
  IN  UINTN                             Size,
  OUT UINT64                            *RecordId )
{
    EFI_BMC_ELOG_INSTANCE_DATA      *BmcElogPrivateData;
    UINT8                           ResponseDataSize;
    UINT8                           ResponseData[2];
    EFI_STATUS                      Status;

    BmcElogPrivateData = INSTANCE_FROM_EFI_SM_ELOG_REDIR_THIS (This);

    if (BmcElogPrivateData->DataType != DataType) {
        return EFI_NOT_FOUND;
    }

    //
    // Check if SEL is full before logging any entries.
    // If SEL is full, then return EFI_OUT_OF_RESOURCES.
    //
    if ( IsSELFull()) {
        return EFI_OUT_OF_RESOURCES;
    }

#if USE_PLATFORM_EVENT_MESSAGE

{
    EFI_PLATFORM_EVENT_MESSAGE_DATA         EventMessage;

    if ( Size > sizeof (EFI_PLATFORM_EVENT_MESSAGE_DATA) ) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Request data field length limit exceeded. Status: EFI_UNSUPPORTED \n"));
        return EFI_UNSUPPORTED;
    }
    CopyMem ((UINT8 *) &EventMessage, ElogData, sizeof (EFI_PLATFORM_EVENT_MESSAGE_DATA));
    ResponseDataSize = 0;

    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_SENSOR,
                BMC_LUN,
                EFI_SENSOR_PLATFORM_EVENT_MESSAGE,
                (UINT8 *) &EventMessage,
                sizeof (EFI_PLATFORM_EVENT_MESSAGE_DATA),
                NULL,
                &ResponseDataSize );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_SENSOR_PLATFORM_EVENT_MESSAGE Status: %r \n", Status));

}
#else
{
    EFI_SEL_RECORD_DATA                SelRecordData;
    if ( Size > sizeof (EFI_SEL_RECORD_DATA) ) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Request data field length limit exceeded. Status: EFI_UNSUPPORTED \n"));
        return EFI_UNSUPPORTED;
    }
    CopyMem ((UINT8 *) &SelRecordData, ElogData, sizeof (EFI_SEL_RECORD_DATA));
    ResponseDataSize = sizeof (ResponseData);

    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_STORAGE,
                BMC_LUN,
                EFI_STORAGE_ADD_SEL_ENTRY,
                (UINT8 *) &SelRecordData,
                sizeof (EFI_SEL_RECORD_DATA),
                //TH0032 (UINT8 *) &ResponseData,
				        (UINT8 *) ResponseData, //TH0032
                (UINT8 *) &ResponseDataSize );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_STORAGE_ADD_SEL_ENTRY Status: %r RecordId: %x \n", Status, *((UINT16*) (&ResponseData) )));
    if ( !EFI_ERROR (Status) ) {
        *RecordId = *((UINT16*) (&ResponseData));
    }
}
#endif

    return Status;
}

/**
    Gets the Event-Log data from the destination. Destination can be a remote
    target like LAN, ICMB, local targets BMC,IPMB or a Firmware-Volume.
    A Redirect Protocol Driver resolves final destination.

    @param This - Instance of EFI_SM_ELOG_PROTOCOL
    @param ElogData - Pointer to the Event-Log data buffer that will contain
                     the data to be retrieved.
    @param DataType - Type of Elog Data that is being recorded.
                     Elog is redirected based upon this information.
    @param AlertEvent - This is an indication that the input data type is an Alert.
                      The underlying drivers to decide if they need to listen to the
                      DataType and send it on an appropriate channel as an alert
                      use this information. Any Alert event logs are not
                      guaranteed to be retrieved or erased.
    @param Size - Size of the data to be retrieved. This size should be equal to
                      or more than the size of data to be retrieved. On return, it
                      contains the actual data retrieved.
    @param RecordId - This is the RecordId of the next record. If ElogData is
                      NULL, this gives the RecordId of the first record available
                      in the database with the correct DataSize. A value of 0 on
                      return indicates the last record if the EFI_STATUS
                      indicates a success

    @return EFI_STATUS Return Status
    @retval EFI_SUCCESS Event-Log was retrieved successfully
    @retval EFI_NOT_FOUND Event-Log target not found.
    @retval EFI_NO_RESPONSE Event-Log Target not responding.
    @retval EFI_INVALID_PARAMETER Invalid Parameter
    @retval EFI_BUFFER_TOO_SMALL Target buffer is too small to retrieve the data.

**/

EFI_STATUS
EfiGetBmcElogData(
  IN EFI_SM_ELOG_REDIR_PROTOCOL         *This,
  IN UINT8                              *ElogData,
  IN EFI_SM_ELOG_REDIR_TYPE             DataType,
  IN OUT UINTN                          *Size,
  IN OUT UINT64                         *RecordId )
{
    EFI_BMC_ELOG_INSTANCE_DATA     *BmcElogPrivateData;
    EFI_GET_SEL_ENTRY               SelEntry = {0};
    EFI_GET_SEL_RESPONSE            SelResponseData;
    UINT8                           SelResponseSize = sizeof(EFI_GET_SEL_RESPONSE);
    EFI_STATUS                      Status;

    BmcElogPrivateData = INSTANCE_FROM_EFI_SM_ELOG_REDIR_THIS (This);

    if (BmcElogPrivateData->DataType != DataType) {
        return EFI_NOT_FOUND;
    }

    if ( *Size < sizeof (EFI_SEL_RECORD_DATA) ) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Response data field length is small. Status: EFI_BUFFER_TOO_SMALL \n"));
        return EFI_BUFFER_TOO_SMALL;
    }

    //
    // Reserve ID only required for partial Get. Use 0000h otherwise
    //
    SelEntry.ReserveId[0] = 0x00;
    SelEntry.ReserveId[1] = 0x00;

    SelEntry.SelRecID[0] = * ( (UINT8*)RecordId );
    SelEntry.SelRecID[1] = * (UINT8*) ( (UINT8*)RecordId + 1 );

    SelEntry.Offset = 0x00;
    SelEntry.BytesToRead = EFI_COMPLETE_SEL_RECORD;

    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_STORAGE,
                BMC_LUN,
                EFI_STORAGE_GET_SEL_ENTRY,
                (UINT8 *) &SelEntry,
                sizeof (EFI_GET_SEL_ENTRY),
                (UINT8 *) (&SelResponseData),
                (UINT8 *) &SelResponseSize );
  SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_STORAGE_GET_SEL_ENTRY Status: %r Next RecordId: %x \n", Status, SelResponseData.NextSelRecordId ));
  if ( EFI_ERROR (Status) ) {
      return Status;
  }
  //
  // Copy the response data and Record Id
  //
  *RecordId = SelResponseData.NextSelRecordId;
  CopyMem (ElogData, (UINT8 *) &(SelResponseData.RecordData), sizeof (EFI_SEL_RECORD_DATA));
  return EFI_SUCCESS;
}

/**
    Erases the Event-Log data from the destination. Destination can be a remote
    target like LAN, ICMB, local targets BMC,IPMB or a Firmware-Volume. A
    Redirect Protocol Driver resolves final destination.

    @param This - Instance of EFI_SM_ELOG_PROTOCOL
    @param DataType - Type of Elog Data that is being Erased.
                   Elog is redirected based upon this information.
    @param RecordId - This is the RecordId of the data to be erased.
                  If RecordId is NULL, all the records on the database are
                  erased if permitted by the target. Contains the deleted
                  RecordId on return.

    @return EFI_STATUS Return Status
    @retval EFI_SUCCESS Event-Log was Erased successfully
    @retval EFI_NOT_FOUND Event-Log target not found.
    @retval EFI_NO_RESPONSE Event-Log Target not responding.
    @retval EFI_INVALID_PARAMETER Invalid Parameter

**/

EFI_STATUS
EfiEraseBmcElogData (
  IN EFI_SM_ELOG_REDIR_PROTOCOL         *This,
  IN EFI_SM_ELOG_REDIR_TYPE             DataType,
  IN OUT UINT64                         *RecordId )
{
    EFI_BMC_ELOG_INSTANCE_DATA      *BmcElogPrivateData;
    EFI_STATUS                       Status = EFI_SUCCESS;
    EFI_SEL_INFO                     SelInfo;
    UINT8                            SelInfoSize = sizeof(EFI_SEL_INFO);
    UINT8                            ReserveId[2];
    UINT8                            ReserveIdSize = sizeof (ReserveId);
    EFI_CLEAR_SEL                    ClearSelData;
    UINT8                            ClearSelResponse;
    UINT8                            ClearSelResponseDataSize = sizeof (ClearSelResponse);
    BmcElogPrivateData = INSTANCE_FROM_EFI_SM_ELOG_REDIR_THIS (This);

    if (BmcElogPrivateData->DataType != DataType) {
        return EFI_NOT_FOUND;
    }

    //
    // Before issuing  SEL reservation ID, Check whether this command is supported or not by issuing the
    // GetSelInfoCommand. If it does not supported ResvId should be 0000h
    //
    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_STORAGE,
                BMC_LUN,
                EFI_STORAGE_GET_SEL_INFO,
                NULL,
                0,
                (UINT8 *) &SelInfo,
                (UINT8 *) &SelInfoSize );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_STORAGE_GET_SEL_INFO Status: %r\n", Status));
    if (EFI_ERROR (Status)) {
        return Status;
    }

    //
    // Check Delete SEL Entry command support and return EFI_UNSUPPORTED
    // if it is not supported
    //
    if ( (RecordId != NULL) && ( (SelInfo.OperationSupport & DELETE_SEL_ENTRY_COMMAND_SUPPORTED_MASK) == FALSE) ) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Deleting Single record is not supported. Status: EFI_UNSUPPORTED\n"));
        return EFI_UNSUPPORTED;
    }

    //
    // if SelReserveIdcommand not supported do not issue the RESERVE_SEL_ENTRY command, and set the ResvId value to 0000h
    // else Get the SEL reservation ID
    //
    if ( SelInfo.OperationSupport & RESERVE_SEL_COMMAND_SUPPORTED_MASK ) {
        //
        // Get Reservation Id value for accessing SEL area.
        //
        Status = GetReservationId (ReserveId);

        if ( EFI_ERROR (Status) ) {
            return Status;
        }
        ClearSelData.Reserve[0] = ReserveId[0];
        ClearSelData.Reserve[1] = ReserveId[1];
    } else {
        ClearSelData.Reserve[0] = 0x00;
        ClearSelData.Reserve[1] = 0x00;
    }
    //
    // Clear the SEL
    //
    ClearSelData.AscC = C_CHAR_ASCII_VALUE;
    ClearSelData.AscL = L_CHAR_ASCII_VALUE;
    ClearSelData.AscR = R_CHAR_ASCII_VALUE;
    ClearSelData.Erase = INITIALIZE_ERASE;

    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_STORAGE,
                BMC_LUN,
                EFI_STORAGE_CLEAR_SEL,
                (UINT8 *) &ClearSelData,
                sizeof (EFI_CLEAR_SEL),
                (UINT8 *) &ClearSelResponse,
                (UINT8 *) &ClearSelResponseDataSize );

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_STORAGE_CLEAR_SEL Status: %r ClearSelResponse: %x\n", Status, ClearSelResponse));
    Status =  WaitTillErased (ReserveId);

    return Status;
}

/**
    This API enables/Disables Event Log.
 
    @param This - Instance of EFI_SM_ELOG_PROTOCOL
    @param DataType -Type of Elog Data that is being Activated.
                   Activation (Enable/Disable) is redirected based upon this information.
    @param EnableElog - Enables (TRUE)/Disables(FALSE) Event Log. If NULL
                  just returns the Current ElogStatus.
    @param  ElogStatus - Current (New) Status of Event Log. Enabled (TRUE),
            Disabled (FALSE).

    @return EFI_STATUS Return Status
    @retval EFI_SUCCESS Event-Log was activated successfully
    @retval EFI_NOT_FOUND Event-Log target not found.
    @retval EFI_NO_RESPONSE Event-Log Target not responding.
    @retval EFI_INVALID_PARAMETER Invalid Parameter

**/

EFI_STATUS
EfiActivateBmcElog (
  IN  EFI_SM_ELOG_REDIR_PROTOCOL         *This,
  IN  EFI_SM_ELOG_REDIR_TYPE             DataType,
  IN  BOOLEAN                            *EnableElog,
  OUT BOOLEAN                            *ElogStatus )
{
    EFI_BMC_ELOG_INSTANCE_DATA      *BmcElogPrivateData;
    EFI_BMC_GLOBAL_ENABLES          BmcGlobalEnables;
    UINT8                           CompletionCode = 0;
    UINT32                          ResponseDataSize = sizeof (EFI_BMC_GLOBAL_ENABLES);
    EFI_STATUS                      Status = EFI_SUCCESS;

    BmcElogPrivateData = INSTANCE_FROM_EFI_SM_ELOG_REDIR_THIS (This);

    if (BmcElogPrivateData->DataType != DataType) {
        return EFI_NOT_FOUND;
    }

    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_APP,
                BMC_LUN,
                EFI_APP_GET_BMC_GLOBAL_ENABLES,
                NULL,
                0,
                (UINT8 *) (&BmcGlobalEnables),
                (UINT8 *) &ResponseDataSize );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_APP_GET_BMC_GLOBAL_ENABLES Status: %r BmcGlobalEnables.SystemEventLogging: %x \n", Status, BmcGlobalEnables.SystemEventLogging ));
    if ( EFI_ERROR (Status) ) {
        return Status;
    }
    //
    // EnableElog: Enables (TRUE)/Disables(FALSE) Event Log. If NULL just returns the Current ElogStatus.
    //
    if (EnableElog == NULL) {
        *ElogStatus = BmcGlobalEnables.SystemEventLogging;
    } else if (BmcGlobalEnables.SystemEventLogging != *EnableElog){

        BmcGlobalEnables.SystemEventLogging = *EnableElog;
        ResponseDataSize = sizeof (CompletionCode);
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_APP,
                    BMC_LUN,
                    EFI_APP_SET_BMC_GLOBAL_ENABLES,
                    (UINT8 *) (&BmcGlobalEnables),
                    sizeof (EFI_BMC_GLOBAL_ENABLES),
                    (UINT8 *) (&CompletionCode),
                    (UINT8 *) &ResponseDataSize );
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_APP_SET_BMC_GLOBAL_ENABLES Status: %r CompletionCode: %x \n", Status, CompletionCode ));
    }
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " BmcGlobalEnables.SystemEventLogging: %x \n", BmcGlobalEnables.SystemEventLogging ));
    return Status;
}

/**
    This is the standard EFI driver point.
    1. Get the device ID information from the BMC and check for SEL device support
    2. Install the SMM version of Redir Elog protocol for EfiElogRedirSmIPMI data type
    3. Activate BMC event logging capability
 
    @param  ImageHandle     - Handle for the image of this driver
    @param  SystemTable     - Pointer to the EFI System Table

    @retval EFI_SUCCESS Protocol successfully started and installed
    @retval EFI_UNSUPPORTED Protocol can't be started

**/

EFI_STATUS
InitializeSmmBmcElog (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable )
{

    EFI_HANDLE              NewHandle;
    EFI_STATUS              Status;
    EFI_SM_CTRL_INFO        ControllerInfo = {0};
    UINT8                   ControllerInfoSize = sizeof (ControllerInfo);
    BOOLEAN                 EnableElog = TRUE;
    BOOLEAN                 ElogStatus = TRUE;

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " InitializeSmmBmcElog entered... \n"));

    Status = gSmst->SmmLocateProtocol (
                &gEfiSmmIpmiTransportProtocolGuid,
                NULL,
                &gIpmiTransport);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiSmmIpmiTransportProtocolGuid Status: %r \n", Status));
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_LOAD, "Couldn't find SMM IPMI TRANSPORT protocol: %r\n", Status));
        return Status;
    }

    //
    // Get the device ID information from the BMC.
    //
    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_APP,
                BMC_LUN,
                EFI_APP_GET_DEVICE_ID,
                NULL,
                0,
                (UINT8 *) &ControllerInfo,
                (UINT8 *) &ControllerInfoSize );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Get Device ID status %r\n", Status));
    if ( EFI_ERROR (Status) ) {
        return Status;
    }

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "ControllerInfo.SelDeviceSupport %X\n", ControllerInfo.SelDeviceSupport));
    if ( !ControllerInfo.SelDeviceSupport ) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SEL device is not supported. So returning EFI_UNSUPPORTED \n"));
        return EFI_UNSUPPORTED;
    }

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "ControllerInfo.SpecificationVersion %X\n", ControllerInfo.SpecificationVersion));
    if ( !( (ControllerInfo.SpecificationVersion == IPMI_SPEC_VERSION_1_5) || \
            (ControllerInfo.SpecificationVersion == IPMI_SPEC_VERSION_2_0) ) ) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "IPMI Spec version is not supported. So returning EFI_UNSUPPORTED \n"));
        return EFI_UNSUPPORTED;
    }
    //
    // Allocate memory for Redir Protocol private data
    //
    gRedirProtoPrivate = AllocateRuntimeZeroPool (sizeof (EFI_BMC_ELOG_INSTANCE_DATA));
    if (gRedirProtoPrivate == NULL) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Failed to allocate memory for gRedirProtoPrivate! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    //
    // Fill the Redir Protocol data
    //
    gRedirProtoPrivate->Signature = SM_ELOG_REDIR_SIGNATURE;
    gRedirProtoPrivate->DataType = EfiElogRedirSmIPMI;
    gRedirProtoPrivate->BmcElog.ActivateEventLog  = EfiActivateBmcElog;
    gRedirProtoPrivate->BmcElog.EraseEventLogData = EfiEraseBmcElogData;
    gRedirProtoPrivate->BmcElog.GetEventLogData   = EfiGetBmcElogData;
    gRedirProtoPrivate->BmcElog.SetEventLogData   = EfiSetBmcElogData;

    //
    // Install the protocol
    //
    NewHandle = NULL;
    Status = gSmst->SmmInstallProtocolInterface (
                &NewHandle,
                &gEfiRedirElogProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &gRedirProtoPrivate->BmcElog );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "gEfiRedirElogProtocolGuid protocol  status %r\n", Status));
    if (EFI_ERROR (Status)) {
        //
        // Error in installing the protocol. So free the allocated memory.
        //
        FreePool (gRedirProtoPrivate);
        return Status;
    }

    //
    //Activate BMC event logging capability
    //
    EfiActivateBmcElog (
        &gRedirProtoPrivate->BmcElog,
        EfiElogRedirSmIPMI,
        &EnableElog,
        &ElogStatus);

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " InitializeSmmBmcElog Exiting... \n"));

    return EFI_SUCCESS;
}

/**
    Get Reservation Id to access SEL area. 
 
    @param ReserveId - Reservation Id obtained.

    @return EFI_STATUS Return Status
    @retval EFI_SUCCESS Reservation Id is obtained successfully.

**/

EFI_STATUS
GetReservationId(
  IN OUT UINT8* ReserveId )
{
    EFI_STATUS Status;
    UINT8 ReserveIdSize = sizeof (UINT16);

    Status = gIpmiTransport->SendIpmiCommand (
                              gIpmiTransport,
                              EFI_SM_NETFN_STORAGE,
                              BMC_LUN,
                              EFI_STORAGE_RESERVE_SEL,
                              NULL,
                              0,
                              ReserveId,
                              (UINT8 *) &ReserveIdSize );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_STORAGE_RESERVE_SEL Status: %r ReserveId: %x \n", Status, *((UINT16*)ReserveId)));
    return Status;
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
