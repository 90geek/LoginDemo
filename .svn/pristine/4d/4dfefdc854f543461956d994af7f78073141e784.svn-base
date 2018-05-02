//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmul.c 12    1/09/12 1:24a Rameshr $
//
// $Revision: 12 $
//
// $Date: 1/09/12 1:24a $
//
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:  KbcEmul.c
//
// Description: KBC emulation driver entry point and initilize the SMI for port 6064
//****************************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "KbcDevEmul.h"
#include "Token.h"
#include "Protocol/UsbPolicy.h"
#include <Setup.h>


KBC*    gVirtualKBC = NULL;
void    Emulation_Init();
void    Smm_Register();

EFI_GUID    gEfiSetupGuid= SETUP_GUID;

//
//KBC Emulation TRAP protocol.
//
BOOLEAN     Emulation6064TrapEnable(EFI_EMUL6064TRAP_PROTOCOL *This);
BOOLEAN     Emulation6064TrapDisable(EFI_EMUL6064TRAP_PROTOCOL *This);
UINT32      KbcEmulationFeature (EFI_EMUL6064TRAP_PROTOCOL * This);

EFI_EMUL6064TRAP_PROTOCOL       Emulation6064Trap= {
    Emulation6064TrapEnable,
    Emulation6064TrapDisable,

    KbcEmulationFeature
};


EFI_HANDLE      EmulationTrapHandle=NULL;

#if PI_SPECIFICATION_VERSION >= 0x0001000A
EFI_SMM_CPU_PROTOCOL            *SmmCpuProtocol=NULL;
#endif

EFI_SMM_BASE2_PROTOCOL*         gSMM = NULL;
EFI_SMM_SYSTEM_TABLE2*          gSmst1 = NULL;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EmulationEntryPoint
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
EmulationEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                  Status      = 0;
    UINTN                       VariableSize;    
    USB_SUPPORT_SETUP           SetupData;


    Status = InitAmiSmmLib( ImageHandle, SystemTable );

    if (EFI_ERROR(Status)) {
    	return EFI_SUCCESS;
    }

    //
    //Check the setup option, if the emulation disabled in setup return with EFI_SUCCESS
    //
    VariableSize = sizeof(USB_SUPPORT_SETUP);
    Status = pRS->GetVariable( L"UsbSupport", &gEfiSetupGuid, NULL, &VariableSize, &SetupData );

    if (EFI_ERROR(Status) || (SetupData.UsbEmul6064 == 0)) {
    	return EFI_SUCCESS;
    }

    Status = pBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (void **) &gSMM);
    if (EFI_ERROR(Status)) {
    	return EFI_SUCCESS;
    }

    gSMM->GetSmstLocation (gSMM, &gSmst1);


    //
    // We're now in SMM, registering all USB SMM callback functions
    //
    Emulation_Init();

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    Status = gSmst1->SmmInstallProtocolInterface(&EmulationTrapHandle,
                   &gEmul6064TrapProtocolGuid,EFI_NATIVE_INTERFACE,&Emulation6064Trap);

    Status= gSmst1->SmmLocateProtocol(&gEfiSmmCpuProtocolGuid, NULL, (void**) &SmmCpuProtocol);

#else
 	Status = gBS->InstallProtocolInterface(&EmulationTrapHandle,
                    &gEmul6064TrapProtocolGuid,EFI_NATIVE_INTERFACE,&Emulation6064Trap);
	ASSERT_EFI_ERROR(Status);
	
	
 	Status= gBS->LocateProtocol(&gEfiSmmCpuProtocolGuid, NULL, &SmmCpuProtocol);
	ASSERT_EFI_ERROR(Status);
#endif

    RegisterAcpiEnableCallBack();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Emulation_Init
//
// Description: Initilize the Keyboard Controller, Keyboard and Mouse device.Regsiter the SMI for port 6064
//              access.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Emulation_Init()
{
    static      VIRTKBC     VirtualKBC;
    static      VIRTMOUSE   VirtualMouse;
    static      VIRTKBD     VirtualKbd;
    static      LEGACYKBC       LegacyKbc;
    static      LEGACYKBD       LegacyKbd;
    static      LEGACYMOUSE LegacyMouse;
    BOOLEAN     KbcPresent;
    UINT8       port64 = IoRead8(0x64);
    UINT16      IrqMask;
    EFI_STATUS  Status;

    //
    //Detect the KBC presence by reading port 64.
    //    
    KbcPresent = ((port64==0xFF))? 0 : 1; 

    if(KbcPresent) {

        gVirtualKBC = &LegacyKbc.kbc_;

        //
        //Initialize the Legacy Mouse Device
        //
        InitLegacyMouse(gVirtualKBC,&LegacyMouse);

        //
        //Initialize the Legacy Keyboard Device
        //
        InitLegacyKbd(gVirtualKBC,&LegacyKbd);

        //
        //Initialize the Legacy Keyboard Controller
        //
        InitLegacyKBC(&LegacyKbc,&LegacyKbd.sink,&LegacyMouse.sink);


    } else {

        gVirtualKBC = &VirtualKBC.kbc;

        //
        //Initialize the Virtual Mouse Device
        //
        InitVirtualMouse(gVirtualKBC,&VirtualMouse);

        //
        //Initialize the Virtual Keyboard Device
        //
        InitVirtualKbd(gVirtualKBC,&VirtualKbd);

        //
        //Initialize the Virtual Keyboard Controller
        //
        InitVirtualKBC(&VirtualKBC,&VirtualKbd.sink,&VirtualMouse.sink);

        //
        // Reserve IRQ1 if the Emulation enabled
        //
        Status=AmiIsaIrqMask(&IrqMask, TRUE);

	    if(Status==EFI_NOT_FOUND){
		    IrqMask=ISA_IRQ_MASK;
            IrqMask |= 2;
		    Status = AmiIsaIrqMask(&IrqMask, FALSE);
	    } else {
            IrqMask |= 2;
            Status=AmiIsaIrqMask(&IrqMask, FALSE);
			ASSERT_EFI_ERROR(Status);
        }

    }

    //
    // Hardware specific SMM registration
    Smm_Register();

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Emulation6064TrapEnable
//
// Description: Enable the SMI source for port 6064
//
// Input:       None
//
// Output:      TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Emulation6064TrapEnable (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    return TrapEnable(TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Emulation6064TrapDisable
//
// Description: Disable the SMI source for port 6064
//
// Input:       None
//
// Output:      TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Emulation6064TrapDisable (
    EFI_EMUL6064TRAP_PROTOCOL           * This
    )
{
    return TrapEnable(FALSE);
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

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
