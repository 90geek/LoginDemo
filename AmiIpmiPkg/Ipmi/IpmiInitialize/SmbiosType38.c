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

/** @file SmbiosType38.c
    Installs SMBIOS type 38 structure

**/

//----------------------------------------------------------------------

#include "IpmiBmc.h"
#include <Library/UefiLib.h>
#include <Protocol/Smbios.h>
#include <IndustryStandard/SmBios.h>
#include <Protocol/IPMISelfTestLogProtocol.h>

//----------------------------------------------------------------------

//
// Extern Variables
//
extern EFI_IPMI_BMC_INSTANCE_DATA   *gIpmiInstance;

//
// NV Storage Device Address
//
#define NV_STORAGE_DEVICE_ADDRESS  0xFF
//
// Base Address Map Bit
//
#define BASE_ADDRESS_MAP_BIT_MASK     (~BIT0)
#define MMIO_MAPPED_BASE_ADDRESS      0x00
#define IO_MAPPED_BASE_ADDRESS        0x01

//
// Byte difference
//
#define DIFFERENCEBYTE    0x1
#define DIFFERENCE4BYTE   0x4
#define DIFFERENCE16BYTE  0x10

//
// Base Address Modifier (This field is unused and set to 00h for SSIF)
//    bit  7:6 - Register spacing
//        00b =  interface registers are on successive byte boundaries
//        01b = interface registers are on 32-bit boundaries
//        10b =  interface registers are on 16-byte boundaries
//        11b = reserved
//
#define REGISTER_SPACING_BYTE_BOUNDARY              ( 0x00 << 6 )
#define REGISTER_SPACING_4BYTE_BOUNDARY             ( 0x01 << 6 )
#define REGISTER_SPACING_16BYTE_BOUNDARY            ( 0x02 << 6 )
#define REGISTER_SPACING_BYTE_BOUNDARY_RESERVED     ( 0x03 << 6 )

//
//    bit 5 - reserved. Return as 0b.
//    bit 4 -  LS-bit for addresses
//        0b = Address bit 0 = 0b
//        1b = Address bit 0 = 1b
//
#define BASE_ADDRESS_MODIFIER_LS_BIT_FOR_ADDRESS(BaseAddress) ( (BaseAddress & BIT0) << 4)

//
// Interrupt Info Identifies the type and polarity of the interrupt
// associated with the IPMI system interface, if any.
//    bit 3 - 1b =  interrupt info specified
//        0b = interrupt info not specified
//    bit 2 - reserved. Return as 0b.
//    bit 1 - Interrupt Polarity.
//        1b = active high, 0b = active low.
//    bit 0 - Interrupt Trigger Mode.
//        1b = level, 0b = edge.
//
#define INTERRUPT_INFO_NOT_SPECIFIED          0x00
//
// Interrupt number for IPMI System Interface.
// 00h = unspecified / unsupported 
//

#define INTERRUPT_NUMBER_UNSPECIFIED          0x00

//
// Finding Register spacing value
//

#if (IPMI_SYSTEM_INTERFACE == KCS_INTERFACE)

#define REGISTERDIFFERNCE ( IPMI_KCS_COMMAND_PORT - IPMI_KCS_DATA_PORT )

#elif (IPMI_SYSTEM_INTERFACE == BT_INTERFACE)

#define REGISTERDIFFERNCE ( IPMI_BT_BUFFER_PORT - IPMI_BT_CTRL_PORT )

#endif

#if REGISTERDIFFERNCE == DIFFERENCEBYTE
#define  REGISTER_SPACING  REGISTER_SPACING_BYTE_BOUNDARY
#endif

#if REGISTERDIFFERNCE == DIFFERENCE4BYTE
#define REGISTER_SPACING  REGISTER_SPACING_4BYTE_BOUNDARY
#endif

#if REGISTERDIFFERNCE == DIFFERENCE16BYTE
#define  REGISTER_SPACING REGISTER_SPACING_16BYTE_BOUNDARY
#endif

//
// Base address Modifier and Interrupt INFO defines
//
#if (IPMI_SYSTEM_INTERFACE == KCS_INTERFACE)
#define BASE_ADDRESS_MODIFIER_INTERRUPT_INFO   \
              ( REGISTER_SPACING |\
                BASE_ADDRESS_MODIFIER_LS_BIT_FOR_ADDRESS(IPMI_KCS_BASE_ADDRESS) |\
                INTERRUPT_INFO_NOT_SPECIFIED \
               )
#elif (IPMI_SYSTEM_INTERFACE == BT_INTERFACE)
#define BASE_ADDRESS_MODIFIER_INTERRUPT_INFO   \
              ( REGISTER_SPACING |\
                BASE_ADDRESS_MODIFIER_LS_BIT_FOR_ADDRESS(IPMI_BT_BASE_ADDRESS) |\
                INTERRUPT_INFO_NOT_SPECIFIED \
              )
#else
#define BASE_ADDRESS_MODIFIER_INTERRUPT_INFO   0x00
#endif


//
// Macro represent size of SmBios structure end value.
// Every SmBios type ends with 0x0000.
//
#define SIZE_OF_SMBIOS_STRUCTURE_END_MACRO    sizeof(UINT16)

/**
    Notification function for SMBIOS protocol.
    Installs SMBIOS type 38 structure

    @param Event Event which caused this handler
    @param Context Context passed during Event Handler registration

    @return VOID

**/

VOID
EFIAPI
InstallSmbiosType38Structure (
  IN  EFI_EVENT                             Event,
  IN  VOID                                  *Context )
{
    EFI_STATUS                       Status;
    EFI_SMBIOS_HANDLE                SmbiosHandle;
    EFI_SMBIOS_PROTOCOL             *SmbiosProtocol;
    EFI_BMC_SELF_TEST_LOG_PROTOCOL  *BmcSelfTestProtocol = NULL;
    SMBIOS_TABLE_TYPE38             *Type38Record;

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "InstallSmbiosType38Structure entered  \n"));

    Status = gBS->LocateProtocol (
                &gEfiSmbiosProtocolGuid,
                NULL,
                (VOID **) &SmbiosProtocol);
    DEBUG ((EFI_D_LOAD, "gBS->LocateProtocol gEfiSmbiosProtocolGuid protocol  status %r\n", Status));
    if (EFI_ERROR (Status)) {
        return;
    }
    Status = gBS->CloseEvent (Event);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "CloseEvent Status:%r \n", Status));
    //
    // Allocate memory for SmBiosType38 structure
    //
    Type38Record = (SMBIOS_TABLE_TYPE38 *)AllocateZeroPool (sizeof (SMBIOS_TABLE_TYPE38) + SIZE_OF_SMBIOS_STRUCTURE_END_MACRO);
    if (Type38Record == NULL) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Allocating Space for SmBios Type38Record fails...\n"));
        return;
    }

    //
    // Fill Type 38 Structure
    //
    Type38Record->Hdr.Type = EFI_SMBIOS_TYPE_IPMI_DEVICE_INFORMATION;
    Type38Record->Hdr.Length = sizeof (SMBIOS_TABLE_TYPE38);
    Type38Record->Hdr.Handle = 0xFFFF;    //To be updated by SMBIOS driver.
    
    //
    // Update IPMI Specification Version
    //
    //
    // Locate the BMC self test protocol
    //
    Status = gBS->LocateProtocol (
                    &gEfiBmcSelfTestLogProtocolGuid,
                    NULL,
                    (VOID **)&BmcSelfTestProtocol );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "gEfiBmcSelfTestLogProtocolGuid: Status:  %r\n", Status));

    if ((!EFI_ERROR (Status)) && BmcSelfTestProtocol->IsGetDeviceIdCommandPassed) {
        //
        // In IPMI device Id command SpecificationVersion Bits 7:4 hold the least significant digit, while
        // Bits 3:0 hold the most significant digit.
        // Example:  A value of 02h indicates version 2.0.
        // SMBIOS record IPMISpecificationRevision Bits 7:4 hold the most significant digit of the version, while
        // Bits 3:0 hold the least significant bits.
        // Example: A value of 20h indicates version 2.0.
        //
        Type38Record->IPMISpecificationRevision = ( BmcSelfTestProtocol->ControllerInfo.SpecificationVersion << 0x04 | BmcSelfTestProtocol->ControllerInfo.SpecificationVersion >> 0x04 );
    }

#if (IPMI_SYSTEM_INTERFACE == KCS_INTERFACE)        // KCS Interface
    Type38Record->InterfaceType = IPMIDeviceInfoInterfaceTypeKCS;
    Type38Record->BaseAddress = ( (IPMI_KCS_BASE_ADDRESS & BASE_ADDRESS_MAP_BIT_MASK)| IO_MAPPED_BASE_ADDRESS );
#elif (IPMI_SYSTEM_INTERFACE == BT_INTERFACE)   // BT Interface
    Type38Record->InterfaceType = IPMIDeviceInfoInterfaceTypeBT;
    Type38Record->BaseAddress = ( (IPMI_BT_BASE_ADDRESS & BASE_ADDRESS_MAP_BIT_MASK)| IO_MAPPED_BASE_ADDRESS );
#else
    Type38Record->InterfaceType = IPMIDeviceInfoInterfaceTypeUnknown ;//Unknown interface
#endif

    Type38Record->I2CSlaveAddress = gIpmiInstance->SlaveAddress;
    Type38Record->NVStorageDeviceAddress = NV_STORAGE_DEVICE_ADDRESS;
    Type38Record->BaseAddressModifier_InterruptInfo = (UINT8)BASE_ADDRESS_MODIFIER_INTERRUPT_INFO;
    Type38Record->InterruptNumber = INTERRUPT_NUMBER_UNSPECIFIED;
    //
    // Now we have got the full SMBIOS record, call SMBIOS protocol to add this record.
    //
    SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
    Status = SmbiosProtocol->Add (
                SmbiosProtocol,
                NULL,
                &SmbiosHandle,
                (EFI_SMBIOS_TABLE_HEADER*) Type38Record);
    DEBUG ((EFI_D_LOAD, "SmbiosProtocol->Add Type38Record....  Status: %r \n", Status));
    FreePool (Type38Record);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "InstallSmbiosType38Structure Exiting....  \n"));

    return;
}

/**

    Register notification callback on SMBIOS protocol to install SmBios type 38
    structure.

    @param VOID

    @return EFI_STATUS

**/

EFI_STATUS
SmbiosType38Support (
  VOID )
{
    VOID        *SmbiosProtocolRegistration;

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosType38Support entered   \n"));

    //
    // Create Notification event for SmbiosProtocol GUID
    //
    EfiCreateProtocolNotifyEvent (
        &gEfiSmbiosProtocolGuid,
        TPL_CALLBACK,
        InstallSmbiosType38Structure,
        NULL,
        &SmbiosProtocolRegistration
        );

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosType38Support exiting.......\n"));

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
