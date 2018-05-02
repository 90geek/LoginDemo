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

/** @file Spmi.c
    SPMI  ACPI  Table

**/

#include "Spmi.h"

EFI_ACPI_TABLE_PROTOCOL      *gAcpiTable = NULL;
UINTN                        gSpmiTblHandle = 0;

UINT8 SPMI_OEM_ID[6]     = ACPI_OEM_ID_MAK;
UINT8 SPMI_OEM_TBL_ID[8] = ACPI_OEM_TBL_ID_MAK;

//
// Service Processor Management Interface Table definition
//
EFI_ACPI_SERVICE_PROCESSOR_MANAGEMENT_INTERFACE_TABLE Spmi = {
{
  EFI_ACPI_3_0_SERVICE_PROCESSOR_MANAGEMENT_INTERFACE_TABLE_SIGNATURE,
  sizeof (EFI_ACPI_SERVICE_PROCESSOR_MANAGEMENT_INTERFACE_TABLE),
  EFI_ACPI_SERVICE_PROCESSOR_MANAGEMENT_INTERFACE_TABLE_REVISION,
  //
  // Checksum will be updated at runtime
  //
  0x00,
  //
  // It is expected that these values will be programmed at runtime
  //
  ' ', ' ', ' ', ' ', ' ', ' ', // OEM ID
  0,  // OEM Table ID
  EFI_ACPI_OEM_SPMI_REVISION,
  0,  // Creator ID
  0,  // Creator Revision
 },
  //
  // Beginning of SPMI specific fields
  //
 {0,     // Interface Type
  0x01,  // Reserved should be 01h
  0,     // IPMI Specification Version
  SPMI_INTERRUPT_TYPE,
  SPMI_GPE,
  0,//Reserved
  PCI_DEVICE_FLAG,
  GLOBAL_SYSTEM_INTERRUPT,
  { // GAS Structure
    ACPI_ADDRESS_SPACE_TYPE_IO,
    REG_BIT_WIDTH_BYTE,
    REG_BIT_OFFSET0,
    SPMI_ACCESS_BYTE,
    0,  // Address
  },
  UID_BYTE1,
  UID_BYTE2,
  UID_BYTE3,
  UID_BYTE4,
  0 // Reserved
 }
};

/**

    This function will update the IPMI ASL object for IPMI specification Version

    @param IpmiSpecRevision Specification version number

    @return VOID

**/

VOID
UpdateIpmiAslObject (
  IN  UINT16 IpmiSpecRevision )

{
    EFI_STATUS                Status;
    EFI_PHYSICAL_ADDRESS      DsdtAddr = 0;

    SERVER_IPMI_DEBUG ((-1, "IPMI:Getting DSDT\n"));
    Status = LibGetDsdt (&DsdtAddr, EFI_ACPI_TABLE_VERSION_ALL);
    if (EFI_ERROR (Status)){
        DEBUG ((-1,"IPMI:Failed to get DSDT\n"));
        return;
    }

    SERVER_IPMI_DEBUG ((-1, "IPMI:Updating SRVV ASL Object\n"));
    Status = UpdateAslNameObject ((ACPI_HDR*)DsdtAddr,(UINT8*)"SRVV", (UINT64)IpmiSpecRevision);
    if (EFI_ERROR (Status)) {
        DEBUG ((-1, "IPMI:Failed to update SRVV ASL Object\n"));
    }
}

/**
    Updates the SPMI table and creates the SPMI ACPI Table

    @param Event Event details
    @param Context Pointer to additional context

    @return VOID

**/

VOID
EFIAPI
PublishSpmiAcpiTables(
   IN  EFI_EVENT     Event,
   IN  VOID          *Context )
{
    EFI_STATUS                                                 Status = EFI_SUCCESS;
    EFI_ACPI_SERVICE_PROCESSOR_MANAGEMENT_INTERFACE_TABLE      *SpmiTable = NULL;
    EFI_BMC_SELF_TEST_LOG_PROTOCOL        *BmcSelfTestProtocol = NULL;
    UINT16                                IpmiSpecRevision = 0x00;

    Status = gBS->LocateProtocol (
                &gEfiAcpiTableProtocolGuid,
                NULL,
                (VOID **)&gAcpiTable);
    DEBUG((EFI_D_LOAD, "Locate ACPI Table protocol Status: %r \n", Status));
    if(EFI_ERROR (Status)) {
        return;
    }

    Status = gBS->AllocatePool(
                 EfiRuntimeServicesData,
                 sizeof(EFI_ACPI_SERVICE_PROCESSOR_MANAGEMENT_INTERFACE_TABLE),
                 (VOID **)&SpmiTable);
    ASSERT(SpmiTable);
    if(!SpmiTable) {
        return;
    }

    //
    // Locate the BMC self test protocol
    //
    Status = gBS->LocateProtocol (
                &gEfiBmcSelfTestLogProtocolGuid,
                NULL,
                (VOID **)&BmcSelfTestProtocol );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "gEfiBmcSelfTestLogProtocolGuid: Status:  %r\n", Status));

    //
    // Fill in table
    //
    gBS->CopyMem(
        SpmiTable,
        &Spmi,
        sizeof(EFI_ACPI_SERVICE_PROCESSOR_MANAGEMENT_INTERFACE_TABLE));

    gBS->CopyMem(
            SpmiTable->AcpiHeader.OemId,
            SPMI_OEM_ID,
            6);
    gBS->CopyMem(
            (UINT8 *)&SpmiTable->AcpiHeader.OemTableId,
            SPMI_OEM_TBL_ID,
            8);
    SpmiTable->AcpiHeader.CreatorId = 0x2E494D41;//"AMI."

    //
    // Interface Type
    //
    if (IPMI_SYSTEM_INTERFACE == KCS_INTERFACE) { // KCS
        SpmiTable->SmpiData.InterfaceType = KCS_INTERFACE;
        SpmiTable->SmpiData.BaseAddress.Address = IPMI_KCS_BASE_ADDRESS;
    }

    if (IPMI_SYSTEM_INTERFACE == BT_INTERFACE) { // BT
        SpmiTable->SmpiData.InterfaceType = BT_INTERFACE;
        SpmiTable->SmpiData.BaseAddress.Address = IPMI_BT_BASE_ADDRESS;
    }

    SpmiTable->SmpiData.BaseAddress.AddrSpcID = 0x01; // System I/O
    SpmiTable->SmpiData.BaseAddress.RegBitWidth = 0x00;
    SpmiTable->SmpiData.BaseAddress.RegBitOffs = 0x00;
    SpmiTable->SmpiData.BaseAddress.AccessSize = 0x01; // Byte Access

    //
    // Update IPMI specification version
    //
    if ( BmcSelfTestProtocol != NULL ) {
        IpmiSpecRevision = ((BmcSelfTestProtocol->ControllerInfo.SpecificationVersion & 0x0F) << 8 ) | \
                ((BmcSelfTestProtocol->ControllerInfo.SpecificationVersion & 0xF0) >> 8 );
        SpmiTable->SmpiData.SpecificationRevision = IpmiSpecRevision;
        UpdateIpmiAslObject (IpmiSpecRevision);
    }

    //
    // Add SPMI table
    //
    Status = gAcpiTable->InstallAcpiTable(
                gAcpiTable,
                SpmiTable,
                sizeof (EFI_ACPI_SERVICE_PROCESSOR_MANAGEMENT_INTERFACE_TABLE),
                &gSpmiTblHandle);
    DEBUG((EFI_D_INFO, "AcpiTable->InstallAcpiTable(SPMI) = %r\n", Status));
    ASSERT_EFI_ERROR(Status);

    //
    // Free memory used for table
    //
    gBS->FreePool(SpmiTable);

    gBS->CloseEvent(Event);
}

/**

    Register notification callback on AcpiSupportprotocol and AcpiTableprotocol to publish SPMI table
    and update IPMI Specification Version ASL Object update.

    @return EFI_STATUS
**/

EFI_STATUS 
SpmiSupport (
    VOID )
{
    EFI_STATUS           Status;
    EFI_EVENT            AcpiEvent;
    VOID                 *AcpiReg;

    Status = gBS->CreateEvent (
                EVT_NOTIFY_SIGNAL,
                TPL_CALLBACK,
                PublishSpmiAcpiTables,
                NULL,
                &AcpiEvent );
    ASSERT_EFI_ERROR(Status);

        Status = gBS->RegisterProtocolNotify (
                    &gEfiAcpiTableProtocolGuid,
                    AcpiEvent,
                    &AcpiReg);
    ASSERT_EFI_ERROR(Status); 

    //
    // If AcpiTable protocol has been installed we can use it right away
    //
    PublishSpmiAcpiTables( AcpiEvent, NULL);

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
