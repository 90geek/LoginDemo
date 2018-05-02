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

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        KbcEmulDxe.c
//
// Description:	KBC emulation driver entry point and installs
//              NonSmmEmul6064TrapProtocol
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include "KbcEmulDxe.h"
#include "Protocol/UsbPolicy.h"
#include <Setup.h>
#if UHCI_EMUL_SUPPORT
#include "KbcUhci.h"
#endif
#if OHCI_EMUL_SUPPORT
#include "KbcOhci.h"
#endif
#if SB_EMUL_SUPPORT
#include "KbcSb.h"
#endif
#if IOTRAP_EMUL_SUPPORT
#include "KbcIoTrap.h"
#endif


extern  EFI_GUID    gEfiLoadedImageProtocolGuid;
extern  EFI_GUID    gEfiDevicePathProtocolGuid;
EFI_GUID    gEfiSetupGuid = SETUP_GUID;

UINT32      KbcEmulationFeature (EFI_EMUL6064TRAP_PROTOCOL * This);
BOOLEAN     NonSmmEmulation6064TrapEnable(EFI_EMUL6064TRAP_PROTOCOL *This);
BOOLEAN     NonSmmEmulation6064TrapDisable(EFI_EMUL6064TRAP_PROTOCOL *This);

EFI_EMUL6064TRAP_PROTOCOL       NonSmmEmulation6064Trap= {
    NonSmmEmulation6064TrapEnable,
    NonSmmEmulation6064TrapDisable,
    KbcEmulationFeature
};

EFI_CPU_IO2_PROTOCOL *CpuIo;

EFI_HANDLE      EmulationTrapHandle=NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EmulationDxeEntryPoint
//
// Description: Entry point for Emulation driver. If the port 6064 emulation enabled by setup
//              it enables the SMI event for port 6064 and install the Trap handle protocol.
//
//
// Input:       Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT
//
// Output:      Status: EFI_SUCCESS = Success
//                      EFI_ERROR = Failure
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EmulationDxeEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                  Status;
    UINTN                       VariableSize;
    USB_SUPPORT_SETUP           SetupData;

	//
	// Load this driver's image to memory
	//
	InitAmiLib(ImageHandle,SystemTable);

	//
	//Check the setup option, if the emulation disabled in setup return with EFI_SUCCESS
	//
	VariableSize = sizeof(USB_SUPPORT_SETUP);
	Status = pRS->GetVariable( L"UsbSupport", &gEfiSetupGuid, NULL, &VariableSize, &SetupData );

	if (EFI_ERROR(Status) || (SetupData.UsbEmul6064 == 0)) {
		return EFI_SUCCESS;
	}

	Status = pBS->LocateProtocol (&gEfiCpuIo2ProtocolGuid, NULL, (VOID **)&CpuIo);

	if (EFI_ERROR(Status)) {
		return Status;
	}

	Status=pBS->InstallProtocolInterface(&EmulationTrapHandle,
							  &gNonSmmEmul6064TrapProtocolGuid,EFI_NATIVE_INTERFACE,&NonSmmEmulation6064Trap);


    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmEmulation6064TrapEnable
//
// Description: Enable the SMI source for port 6064 in Non SMM
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
NonSmmEmulation6064TrapEnable (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    return NonSmmTrapEnable(TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmEmulation6064TrapDisable
//
// Description: Disable the SMI source for port 6064 in Non SMM
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
NonSmmEmulation6064TrapDisable (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    return NonSmmTrapEnable(FALSE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   KbcEmulationFeature
//
// Description: Returns all the feature supported by Emulation
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
KbcEmulationFeature (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    UINT32          KbcEmulFeature=0;

#if IRQ_EMUL_SUPPORT
    KbcEmulFeature |= IRQ_SUPPORTED;
#endif
    return  KbcEmulFeature;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmTrapEnable
//
// Description: Enable/disable the port6064 trap in Non SMM
//
// Input:       TRUE : enable the trap.
//              FALSE: Disable the trap.
//
// Output:      TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN NonSmmTrapEnable(BOOLEAN b)
{
#if UHCI_EMUL_SUPPORT
    return NonSmmUhci_TrapEnable(b);
#endif
#if OHCI_EMUL_SUPPORT
    return NonSmmOhci_TrapEnable(b);
#endif
#if SB_EMUL_SUPPORT
    return NonSmmSb_TrapEnable(b);
#endif    
#if IOTRAP_EMUL_SUPPORT
    return NonSmmIoTrapEnable(b);
#endif
	return TRUE;
}

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
