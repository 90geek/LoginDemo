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

/** @file PeiSelStatusCode.c
    PEIM to provide SEL status code reporting routines .
    This requires the platform portion of status code module to define 
    some values.The conversion table from status codes to SEL is defined in
    StatuscodeConversionlib file. 

**/

//-----------------------------------------------------------------------
#include "PeiSelStatusCode.h"
#include <Include/ServerMgmtSetupVariable.h>

//
//  OEM Status Code to SEL Conversion table.
//  Entries should be added to this table using SDL tokens by OEM to convert to SEL entry.
//
#if (OEM_SEL_SUPPORT == 1)
#include "OemStatusCodeTable.h"
#endif

//-----------------------------------------------------------------------

//
// Notify descriptor
//
static EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList[] = {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiMemoryDiscoveredPpiGuid,
    UpdatedPeiSelPpi
};

/**
    After memory is discovered, Re Install the PEI SEL PPI with updated
    IpmiTransportPpi

        
    @param PeiServices Pointer to the PEI Core data Structure
    @param NotifyDescriptor Pointer to the instance of
        the EFI_PEI_NOTIFY_DESCRIPTOR
    @param Ppi Pointer to the instance of the interface

    @return EFI_STATUS Return Status

**/

EFI_STATUS
EFIAPI
UpdatedPeiSelPpi (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi )
{

    EFI_STATUS                      Status;
    PEI_IPMI_TRANSPORT_PPI          *IpmiTransportPpi;
    EFI_PEI_PPI_DESCRIPTOR          *PeiSelPpiDesc;
    PEI_SEL_STATUS_CODE_PPI         *PeiSelPpi;


    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " UpdatedPeiSelPpi entered........ \n"));
    //
    // Locate PeiSel Ppi.
    //
    Status = (*PeiServices)->LocatePpi (
                (CONST EFI_PEI_SERVICES **)PeiServices,
                &gEfiPeiSelPpiGuid,
                0,
                &PeiSelPpiDesc,
                (VOID **)&PeiSelPpi);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiPeiSelPpiGuid Status: %r \n", Status));
    if (EFI_ERROR (Status)) {
        return Status;
    }

    //
    //Locate IPMI Transport PPI to update new pointer in PeiSelPpi.
    //
    Status = (*PeiServices)->LocatePpi (
            (CONST EFI_PEI_SERVICES **)PeiServices,
                &gEfiPeiIpmiTransportPpiGuid,
                0,
                NULL,
                (VOID **)&IpmiTransportPpi);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiPeiIpmiTransportPpiGuid Status: %r \n", Status));
    if (EFI_ERROR (Status)) {
        return Status;
    }
    //
    // Update IpmiTransportPPI Pointer in PeiSelPpi
    //
    PeiSelPpi->IpmiTransportPpi   = IpmiTransportPpi; //IpmiTransportPPI Pointer

    //
    // Update PeiSelPpi Pointer in PeiSelPpiDesc
    //
    PeiSelPpiDesc->Ppi   = PeiSelPpi; //PeiSelPpi Pointer

    //
    // Re Install the PEI SEL PPI with updated IpmiTransportPpi
    //
    Status = (*PeiServices)->ReInstallPpi (
            (CONST EFI_PEI_SERVICES **)PeiServices,
                PeiSelPpiDesc,
                PeiSelPpiDesc);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " (*PeiServices)->ReInstallPpi Status: %r \n", Status));

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " UpdatedPeiSelPpi Exiting........ \n"));

    return Status;
}

/**
    This function walks through the table based upon Value field of
    Status Code and extract EFI status code to SEL conversion entry.

    @param  EfiStatusCode - EFI status code Value
    @param  StatusCodeType - EFI status code type

    @return EFI_STATUS_CODE_TO_SEL_ENTRY*
    @retval Pointer to conversion entry if found.
    @retval NULL if conversion entry is not found.

**/
EFI_STATUS_CODE_TO_SEL_ENTRY *
ConvertEfiStatusCodeToSelEntry (
  IN  EFI_STATUS_CODE_VALUE   EfiStatusCode,
  IN  EFI_STATUS_CODE_TYPE    StatusCodeType )
{
    UINTN         TableSize;
    UINTN         Index;

#if (OEM_SEL_SUPPORT == 1)
    //
    // OEM to SEl Status code List
    //
    TableSize = (sizeof (OemStatusCodeToSelTable)/sizeof (EFI_STATUS_CODE_TO_SEL_ENTRY));

    for (Index = 0; Index < TableSize-1; Index++) {
        if (EfiStatusCode == OemStatusCodeToSelTable[Index].StatusCode &&\
            StatusCodeType == OemStatusCodeToSelTable[Index].StatusCodeType ) {
            return &OemStatusCodeToSelTable[Index];
        }
    }
#endif
    //
    // EFI to SEl Status code List
    //
    TableSize = (sizeof(EfiStatusCodeToSelTable)/sizeof(EFI_STATUS_CODE_TO_SEL_ENTRY));

    for (Index = 0; Index < TableSize; Index++) {
        if (EfiStatusCode == EfiStatusCodeToSelTable[Index].StatusCode &&\
            StatusCodeType == EfiStatusCodeToSelTable[Index].StatusCodeType ) {
            return &EfiStatusCodeToSelTable[Index];
        }
    }

  return NULL;
}

/**
    Locates SEL PPi and calls SEL Report status code function to log SEL in BMC

    @param PeiServices - Pointer to the PEI Core data Structure
    @param Value - EFI status code Value
    @param CodeType - EFI status code type
    @param Instance - The enumeration of a hardware or software entity within
                    the system. A system may contain multiple entities that
                    match a class/subclass pairing. The instance differentiates
                    between them. An instance of 0 indicates that instance
                    information is unavailable, not meaningful, or not relevant.
                    Valid instance numbers start with 1.
    @param CallerId - This optional parameter may be used to identify the caller.
                           This parameter allows the status code driver to apply different
                           rules to different callers.
    @param Data - This optional parameter may be used to pass additional data.

    @return EFI_STATUS
    @retval EFI_SUCCESS  Status code reported to BMC successfully.

**/

EFI_STATUS
PeiSelStatusCodeReportWorker (
  IN CONST  EFI_PEI_SERVICES        **PeiServices,
  IN EFI_STATUS_CODE_TYPE           CodeType,
  IN EFI_STATUS_CODE_VALUE          Value,
  IN UINT32                         Instance,
  IN CONST EFI_GUID                 *CallerId,
  IN CONST EFI_STATUS_CODE_DATA     *Data OPTIONAL )
{
    PEI_SEL_STATUS_CODE_PPI *PeiSelPpi;
    EFI_STATUS          Status=EFI_SUCCESS;

    if (((CodeType & EFI_STATUS_CODE_TYPE_MASK) == EFI_PROGRESS_CODE)||
            ((CodeType & EFI_STATUS_CODE_TYPE_MASK)==EFI_ERROR_CODE)) {
        //
        // Check if status code to equivalent SEL entry found in table,If not found return.
        //
        if ( ConvertEfiStatusCodeToSelEntry (Value, CodeType & EFI_STATUS_CODE_TYPE_MASK) == NULL ) {
            return EFI_NOT_FOUND;
        }
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Entered .... PeiSelStatusCodeReportWorker Value: %x \n", Value));

        //
        //Locate PeiSel Ppi.
        //
        Status = (*PeiServices)->LocatePpi (
                    PeiServices,
                    &gEfiPeiSelPpiGuid,
                    0,
                    NULL,
                    (VOID **)&PeiSelPpi );
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiPeiSelPpiGuid Status: %r \n", Status));
        if (!EFI_ERROR (Status)) {
            Status = PeiSelPpi->EfiSelReportStatusCode (
                        PeiServices,
                        PeiSelPpi,
                        CodeType,
                        Value,
                        Instance,
                        CallerId,
                        Data );
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EfiSelReportStatusCode Status: %r \n", Status));
        }

    }
    return Status;
}

/**
    This function fills the SEL record format.

    @param EfiStatusCode - EFI status code Value
    @param StatusCodeType - EFI status code type
    @param SelRecordData - Pointer to SEL record data

    @return EFI_SUCCESS
    @retval EFI_DEVICE_ERROR If status code is not found in the conversion table

**/

EFI_STATUS
FillSelRecord (
  IN EFI_STATUS_CODE_VALUE        Value,
  IN EFI_STATUS_CODE_TYPE        CodeType,
  IN OUT  EFI_SEL_RECORD_DATA    *SelRecordData )
{
    EFI_STATUS_CODE_TO_SEL_ENTRY         *SelEntry;

    SelEntry = ConvertEfiStatusCodeToSelEntry (Value, CodeType);

    if (SelEntry != NULL) {
        SelRecordData->RecordId = 0x00;
        SelRecordData->RecordType = EFI_SEL_SYSTEM_RECORD;   // Discrete
        SelRecordData->TimeStamp = 0x00;
        SelRecordData->GeneratorId= (UINT16) EFI_GENERATOR_ID (BIOS_SOFTWARE_ID);
        SelRecordData->EvMRevision = EFI_EVM_REVISION;
        SelRecordData->SensorType = SelEntry->SensorTypeCode;
//TH0179>>>        
		    if(SelRecordData->SensorType == 0x0F){
		//DJH002027++>>
		#if OEM_SENSOR_NUMBER_SUPPORT == 1
		        SelRecordData->SensorNumber = 0xF4;
		#else
		//DJH002027++<<
			    SelRecordData->SensorNumber = 0xE1;
		#endif //DJH002027++
		    }
		    else{  
//TH0179<<<   
        SelRecordData->SensorNumber = BIOS_SOFTWARE_ID;
        } //TH0179++
        SelRecordData->EventDirType = EFI_SENSOR_TYPE_EVENT_CODE_DISCRETE;
        SelRecordData->OEMEvData1 = SelEntry->EventData1;
        SelRecordData->OEMEvData2 = SelEntry->EventData2;
        SelRecordData->OEMEvData3= SelEntry->EventData3;

        return EFI_SUCCESS;
    }
    return EFI_DEVICE_ERROR;
}

/**
    Convert status code value and extended data to BMC SEL record format and
    send the command to log SEL in BMC.

    @param PeiServices - Pointer to the PEI Core data Structure
    @param PeiSelPpi - Pointer to the PEI SEL PPI
    @param Value - EFI status code Value
    @param CodeType - EFI status code type
    @param Instance - The enumeration of a hardware or software entity within
                      the system. A system may contain multiple entities that
                      match a class/subclass pairing. The instance differentiates
                      between them. An instance of 0 indicates that instance
                      information is unavailable, not meaningful, or not relevant.
                      Valid instance numbers start with 1.
    @param CallerId - This optional parameter may be used to identify the caller.
                      This parameter allows the status code driver to apply different
                      rules to different callers.
    @param Data - This optional parameter may be used to pass additional data.

    @return EFI_STATUS Return Status

**/

EFI_STATUS
EFIAPI
EfiSelReportStatusCode (
  IN CONST EFI_PEI_SERVICES         **PeiServices,
  IN PEI_SEL_STATUS_CODE_PPI        *PeiSelPpi,
  IN EFI_STATUS_CODE_TYPE           CodeType,
  IN EFI_STATUS_CODE_VALUE          Value,
  IN UINT32                         Instance,
  IN CONST EFI_GUID                 *CallerId,
  IN CONST EFI_STATUS_CODE_DATA     *Data OPTIONAL )
{
    EFI_STATUS                  Status;
    EFI_SEL_RECORD_DATA         SelRecordData;
    UINT8                       ResponseDataSize;
    UINT16                      RecordId = 0;
    BOOLEAN                     LogProgressCode;
    BOOLEAN                     LogErrorCode;

#if USE_PLATFORM_EVENT_MESSAGE
    EFI_PLATFORM_EVENT_MESSAGE_DATA         EventMessage;
#endif

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Entered .... EfiSelReportStatusCode Value: %x \n", Value));
    //
    // Check if we are called during PEI.
    //
    if (PeiServices == NULL) {
        return EFI_SUCCESS;
    }
    LogProgressCode = (PeiSelPpi->LogSelStatusCodes == LOG_BOTH_PROGRESS_AND_ERROR_CODES) || \
                       (PeiSelPpi->LogSelStatusCodes == LOG_PROGRESS_CODE_ONLY);
    LogErrorCode = (PeiSelPpi->LogSelStatusCodes == LOG_BOTH_PROGRESS_AND_ERROR_CODES) || \
                   (PeiSelPpi->LogSelStatusCodes == LOG_ERROR_CODE_ONLY);

    //
    // Check if logging only progress code,only error code or both is opted by user
    //
    switch (CodeType & EFI_STATUS_CODE_TYPE_MASK) {

        case EFI_PROGRESS_CODE:
            if  ( !LogProgressCode ) {
                return EFI_SUCCESS;
            }
            break;
        case EFI_ERROR_CODE:
            if  ( !LogErrorCode ) {
                return EFI_SUCCESS;
            }
            break;
        default:
            break;
    }

    //
    // Check if status code to equivalent SEL entry found in table,If not found return.
    //
    Status = FillSelRecord ( Value, CodeType & EFI_STATUS_CODE_TYPE_MASK, &SelRecordData);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " FillSelRecord Status: %r \n", Status));
    if (EFI_ERROR (Status)) {
        return EFI_SUCCESS;
    }

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " (PeiSelPpi->IpmiTransportPpi): %X \n", (PeiSelPpi->IpmiTransportPpi)));
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " (PeiSelPpi->IpmiTransportPpi)-> SendIpmiCommand: %X \n", (PeiSelPpi->IpmiTransportPpi)-> SendIpmiCommand));

#if USE_PLATFORM_EVENT_MESSAGE

    EventMessage.GeneratorId = EFI_GENERATOR_ID (BIOS_SOFTWARE_ID);
    EventMessage.EvMRevision = SelRecordData.EvMRevision;
    EventMessage.SensorType = SelRecordData.SensorType;
    EventMessage.SensorNumber = SelRecordData.SensorNumber;
    EventMessage.EventDirType = SelRecordData.EventDirType;
    EventMessage.OEMEvData1 = SelRecordData.OEMEvData1;
    EventMessage.OEMEvData2 = SelRecordData.OEMEvData2;
    EventMessage.OEMEvData3 = SelRecordData.OEMEvData3;
    ResponseDataSize = 0;

    Status = (PeiSelPpi->IpmiTransportPpi)-> SendIpmiCommand (
                PeiSelPpi->IpmiTransportPpi,
                EFI_SM_NETFN_SENSOR,
                BMC_LUN,
                EFI_SENSOR_PLATFORM_EVENT_MESSAGE,
                (UINT8 *) &EventMessage,
                sizeof (EFI_PLATFORM_EVENT_MESSAGE_DATA),
                NULL,
                &ResponseDataSize );

#else

    ResponseDataSize = sizeof(RecordId);
    Status = (PeiSelPpi->IpmiTransportPpi)-> SendIpmiCommand (
                PeiSelPpi->IpmiTransportPpi,
                EFI_SM_NETFN_STORAGE,
                BMC_LUN,
                EFI_STORAGE_ADD_SEL_ENTRY,
                (UINT8 *) &SelRecordData,
                sizeof (EFI_SEL_RECORD_DATA),
                (UINT8 *) &RecordId,
                &ResponseDataSize );
#endif

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " (PeiSelPpi->IpmiTransportPpi)-> SendIpmiCommand Status: %r \n", Status));

    return Status;
}

/**
    This function is the entry point for this PEI.
    This installs the SEL status code PPI

    @param FileHandle Pointer to image file handle.
    @param PeiServices Pointer to the PEI Core data Structure

    @return EFI_STATUS
    @retval EFI_SUCCESS Successful driver initialization

**/
EFI_STATUS
InitializePeiSel (
  IN EFI_PEI_FILE_HANDLE     FileHandle,
  IN CONST EFI_PEI_SERVICES  **PeiServices )
{

    EFI_STATUS                              Status;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI         *PeiVariable;
    SERVER_MGMT_CONFIGURATION_DATA          ServerMgmtConfiguration;
    UINTN                                   Size;
    PEI_IPMI_TRANSPORT_PPI                  *IpmiTransportPpi;
    EFI_PEI_RSC_HANDLER_PPI                 *RscHandlerPpi;
    EFI_PEI_PPI_DESCRIPTOR                  *PeiSelPpiDesc;
    PEI_SEL_STATUS_CODE_PPI                 *PeiSelPpi;

    //
    //Locate IPMI Transport PPI to send commands to BMC.
    //
    Status = (*PeiServices)->LocatePpi (
                PeiServices,
                &gEfiPeiIpmiTransportPpiGuid,
                0,
                NULL,
                (VOID **)&IpmiTransportPpi
                );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiPeiIpmiTransportPpiGuid Status: %r \n", Status));
    if (EFI_ERROR (Status)) {
        return Status;
    }

    //
    // Locate the Setup configuration value.
    //
    Status = (*PeiServices)->LocatePpi (
                PeiServices,
                &gEfiPeiReadOnlyVariable2PpiGuid,
                0,
                NULL,
                (VOID **)&PeiVariable );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiPeiReadOnlyVariable2PpiGuid status %r\n", Status));
    ASSERT_EFI_ERROR (Status);

    if (!EFI_ERROR (Status)) {
        Size = sizeof(SERVER_MGMT_CONFIGURATION_DATA);
        Status = PeiVariable->GetVariable (
                    PeiVariable,
                    L"ServerSetup",
                    &gEfiServerMgmtSetupVariableGuid,
                    NULL,
                    &Size,
                    &ServerMgmtConfiguration );
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " PeiVariable->GetVariable status %r \n", Status));
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " SelLogging: %x LogSelStatusCodes: %x \n", ServerMgmtConfiguration.SelLogging, ServerMgmtConfiguration.LogSelStatusCodes));
    }
    if (EFI_ERROR(Status)) {
        //load default value.
        ServerMgmtConfiguration.SelLogging           = SEL_LOGGING_ENABLED;
        ServerMgmtConfiguration.SelFull              = DO_NOTHING_WHEN_SEL_FULL;
        ServerMgmtConfiguration.SelErase             = DO_NOT_ERASE;
        ServerMgmtConfiguration.LogSelStatusCodes    = LOG_ERROR_CODE_ONLY;
    }

    //
    // Check if SEL components enabled in setup,if not enabled then Return SUCCESS
    //
    if ( (!ServerMgmtConfiguration.SelLogging) || (!ServerMgmtConfiguration.LogSelStatusCodes) ) {
        return EFI_UNSUPPORTED;
    }

    //
    // Install the PEI SEL PPI
    // Allocate descriptor and PPI structures.  Since these are dynamically updated
    //
    PeiSelPpi = (PEI_SEL_STATUS_CODE_PPI *) AllocateZeroPool (sizeof (PEI_SEL_STATUS_CODE_PPI));
    if (PeiSelPpi == NULL) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Failed to allocate memory for PeiSelPpi! \n"));
        return EFI_OUT_OF_RESOURCES;
    }
    PeiSelPpi->LogSelStatusCodes   = ServerMgmtConfiguration.LogSelStatusCodes; //LogSelStatusCodes Setup Option
    PeiSelPpi->IpmiTransportPpi   = IpmiTransportPpi; //IpmiTransportPPI Pointer
    PeiSelPpi->EfiSelReportStatusCode   = EfiSelReportStatusCode;

    PeiSelPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
    if (PeiSelPpiDesc == NULL) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Failed to allocate memory for PeiSelPpiDesc! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    PeiSelPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    PeiSelPpiDesc->Guid  = &gEfiPeiSelPpiGuid;
    PeiSelPpiDesc->Ppi   = PeiSelPpi;

    Status = (*PeiServices)->InstallPpi (
                PeiServices,
                PeiSelPpiDesc );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " (*PeiServices)->InstallPpi Status: %r \n", Status));
    if (EFI_ERROR (Status)) {
        //
        // Error in installing the PPI. So free the allocated memory.
        //
        FreePool (PeiSelPpi);
        FreePool (PeiSelPpiDesc);
        return Status;
    }

    //
    // Install call-back to update IpmiTransportPpi pointer in PeiSelPpi after MRC in PEI phase.
    //
    Status = (*PeiServices)->NotifyPpi (PeiServices, &mNotifyList[0]);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " (*PeiServices)->NotifyPpi Status: %r \n", Status));
    ASSERT_EFI_ERROR (Status);

    Status = (*PeiServices)->LocatePpi (
                PeiServices,
                &gEfiPeiRscHandlerPpiGuid,
                0,
                NULL,
                (VOID **) &RscHandlerPpi );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiPeiRscHandlerPpiGuid Status: %r \n", Status));
    if (!EFI_ERROR (Status)) {
        Status = RscHandlerPpi->Register (PeiSelStatusCodeReportWorker);
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " RscHandlerPpi->Register Status: %r \n", Status));
    }

    return EFI_SUCCESS;
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
