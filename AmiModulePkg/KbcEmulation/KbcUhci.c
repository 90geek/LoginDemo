//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        KbcUhci.c
//
// Description: Handles the SMI events for port 60/64
//
//****************************************************************************
//<AMI_FHDR_END>

#include "Token.h"
#include "KbcEmul.h"
#include "KbcUhci.h"
#include "KbcEmulLib.h"
#include "Kbc.h"

extern KBC* gVirtualKBC;

#if ICH10_WORKAROUND
EFI_STATUS  EnableAllUhciController();
EFI_STATUS  RestoreUhciControllerStatus();
#endif

//Carries the LEGKEY status information saved before enable/disable trapping from outside trap handler is
//performed; The saving of the status allows recovering legacy I/O accesss event in case when multiple
//sources are serviced at signle SMI# ( legacy I/O and USB keyboard interupt, for example)

static UINT16 SavedLegcyStatus = 0;

static BOOLEAN gInTrapHandler = FALSE;


UHCI_EMUL_DEVICE Uhci_Hc_Array[] = { 
#if defined(UHCI_EMUL_PCI_DEVICES)
		UHCI_EMUL_PCI_DEVICES, 
#endif
		{ 0xFFFF, 0xFF, 0xFF, 0xFF, 0xFF }
};

UINTN Uhci_Hc_Array_Size = sizeof(Uhci_Hc_Array) / sizeof(Uhci_Hc_Array[0]);

void DisableLegKeyRegs();
void trap64w();
void trap60w();
void trap64r();
void trap60r();

TRAPDISPATCH trap_dispatcher[] = {
    { UHCI_TRAPBY64W,  trap64w },
    { UHCI_TRAPBY64R,  trap64r },
    { UHCI_TRAPBY60W,  trap60w },
    { UHCI_TRAPBY60R,  trap60r },
};

#define trap_dispatcher_size  (sizeof(trap_dispatcher)/sizeof(trap_dispatcher[0]))


void Trap6064_Handler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_REGISTER_CONTEXT  * DispatchContext
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ValidateUhc
//
// Description: Validate the UHCI controller.
//
// Input:       Boolean
//
// Output:      Boolean
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
ValidateUhc (
    UHCI_EMUL_DEVICE  *Uhc
)
{
    UINT32  Data32 = 0;

    // End of the Device List.
    if(Uhc->BusDevFunc == 0xFFFF) {
    	return FALSE;
    }
    
    if (ReadPCIConfig (Uhc->BusDevFunc, 0) == 0xFFFFFFFF) {
        return FALSE;
    }

    Data32 = ReadPCIConfig (Uhc->BusDevFunc, 8) >> 8;
    if (Data32 != (*((UINT32*)&Uhc->InterfaceType) & 0x00FFFFFF)) {
        return FALSE;
    }

	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Smm_Register
//
// Description: Enable the SMI for port 6064 access.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Smm_Register()
{
	EFI_SMM_USB_REGISTER_CONTEXT    context;
    EFI_SMM_USB_DISPATCH2_PROTOCOL*  pDispatch;
    EFI_HANDLE hDisp;
    EFI_STATUS Status;
    static FULL_USB_DEVICE_PATH hc_dp = USB1_1_DEVICE_PATH;
    UINTN UhciCount;

    //
    // Register the USB HW SMI handler
    //
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    Status = gSmst1->SmmLocateProtocol(
            &gEfiSmmUsbDispatch2ProtocolGuid,
            NULL,
            &pDispatch);
#else
    Status = gBS->LocateProtocol(
            &gEfiSmmUsbDispatchProtocolGuid,
            NULL,
            &pDispatch);
#endif
    ASSERT_EFI_ERROR(Status);
    //
    // SMI registration routines will install the handlers, set enable bit
    // and clear status in PM IO space.
    //
    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        //
        //Validate the PCI device before regsiter the SMI callback.
        //
        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }
        hc_dp.pci.Device=(Uhci_Hc_Array[UhciCount].BusDevFunc >> 3);
        hc_dp.pci.Function=(Uhci_Hc_Array[UhciCount].BusDevFunc & 07);
        context.Type = UsbLegacy;
        context.Device = (EFI_DEVICE_PATH_PROTOCOL *)&hc_dp;
        Status = pDispatch->Register(pDispatch,(EFI_SMM_HANDLER_ENTRY_POINT2)Trap6064_Handler, &context, &hDisp);
        ASSERT_EFI_ERROR(Status);
    }

    SavedLegcyStatus = 0;
    //
    //The SMI source for the port6064 is disabled. it will be enabled when we are in legacy enviorment. EFI enviorment Emulation is
    //Disabled.
    //
    DisableLegKeyRegs();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WriteLegKeyReg
//
// Description: Write the Value in to all the UHCI controller Legacy Regsiters.
//
// Input:       UINT8 Value
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void WriteLegKeyReg ( UINT16 Value)
{
    UINTN UhciCount;
    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        WordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc, 
                        Uhci_Hc_Array[UhciCount].LegacyRegOffset, Value);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ClearLegKeyStatusReg
//
// Description: Clear the Port6064 SMI Status Reg 
//
// Input:       UINT8 Value
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void ClearLegKeyStatusReg ( UINT16 Value)
{

#if ICH10_WORKAROUND
        //
        // Enable all the UCHI controller 
        // In ICH10 chipset, we need to clear the Port 6064 SMI status in disabled controller 
        // also. Otherwise it's keep on generating SMI
        //
        EnableAllUhciController();
#endif
    
    WriteLegKeyReg(Value);

#if ICH10_WORKAROUND
        //
        // Restore the UCHI controller's in RCBA Reg
        //
        RestoreUhciControllerStatus();
#endif

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableLegKeyRegs
//
// Description: Disable the port6064 SMI source based on the Trap enable mask.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void DisableLegKeyRegs()
{
    UINT16  legkeyStatus;
    UINTN   UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){

        //
        // Skip for Invalid Pci Devices
        //
        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }

        //
        //Read the Legacy Keyboard and mouse control register
        //
        legkeyStatus =(UINT16) ReadPCIConfig(Uhci_Hc_Array[UhciCount].BusDevFunc , 
                            Uhci_Hc_Array[UhciCount].LegacyRegOffset );      // Read the status

        //
        //Clear the enable bits
        //

        WordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc , 
            Uhci_Hc_Array[UhciCount].LegacyRegOffset, legkeyStatus & ~UHCI_TRAPEN_MASK);

        //
        //Disable the trap
        //
        WordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc,  
            Uhci_Hc_Array[UhciCount].LegacyRegOffset, legkeyStatus & (~UHCI_TRAPEN_MASK));
    }
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Trap6064_Handler
//
// Description: SMI handler to handle the 64write, 64read, 60 write and 60 read SMI.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Trap6064_Handler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_REGISTER_CONTEXT  * DispatchContext
  )
{
    UINT16 LegcyKeyStatus;
    UINT32 TrapFunCount;
    UINTN UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){

        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }

        //
        // Read UHCI_PCI_LEGKEY
        //
        LegcyKeyStatus = (UINT16) ReadPCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc , 
                                    Uhci_Hc_Array[UhciCount].LegacyRegOffset );
        SavedLegcyStatus |= LegcyKeyStatus;

        if(SavedLegcyStatus==0xFFFF) {
            SavedLegcyStatus=0;
            continue;
        }

        if( (SavedLegcyStatus & UHCI_TRAPBY_MASK) != 0 ) {
            break;
        }

        SavedLegcyStatus=0;
    }

    if(UhciCount >=Uhci_Hc_Array_Size) {
        return;
    }
    //
    // External application has chaned UHCI trap enable configuration, exit
    //
    if ((LegcyKeyStatus & UHCI_TRAPEN_MASK) != UHCI_TRAPEN_MASK)
        return;

    //
    // Set the variable that we are processing the Trap
     //
    gInTrapHandler = TRUE;

    //
    // Clear the status
    //
    ClearLegKeyStatusReg( LegcyKeyStatus | UHCI_TRAPBY_MASK);

    //
    // Disable Traps ( in responce to i/o handler can try to access a real KBC)
    //
    WriteLegKeyReg( (LegcyKeyStatus & ~UHCI_TRAPEN_MASK));

    //
    // Dispatch the interrupt depending on saved status
    //
    for( TrapFunCount = 0; TrapFunCount < trap_dispatcher_size; ++TrapFunCount ){
        if( (LegcyKeyStatus & trap_dispatcher[TrapFunCount].status_bit  ) != 0){
            (*trap_dispatcher[TrapFunCount].trap_function)();
        }
    }

    //
    // Clear the Status
    //
    ClearLegKeyStatusReg( LegcyKeyStatus | UHCI_TRAPBY_MASK);

    //
    // Enable Traps 
    //
    WriteLegKeyReg( LegcyKeyStatus | UHCI_TRAPEN_MASK);

    SavedLegcyStatus = 0;
    gInTrapHandler = FALSE;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  Uhci_HasTrapStatus
//
// Description: Check if trap status is set in UHCI HC.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN Uhci_HasTrapStatus()
{
    UINT16 LegcyKeyStatus = 0;
    UINTN UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }

        LegcyKeyStatus |= (UINT16) ReadPCIConfig(Uhci_Hc_Array[UhciCount].BusDevFunc,  
                                    Uhci_Hc_Array[UhciCount].LegacyRegOffset );
    }
    return ((LegcyKeyStatus & UHCI_TRAPBY_MASK) != 0 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Uhci_TrapEnable
//
// Description: Enable/Disable traping in UHCI HC.
//
// Input:       Boolean
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN    Uhci_TrapEnable(BOOLEAN TrapEnable)
{
    UINT16    LegcyKeyStatus;
    UINTN       UhciCount;

    if(gInTrapHandler)
        return FALSE;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }

        LegcyKeyStatus =(UINT16) ReadPCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc , 
                                        Uhci_Hc_Array[UhciCount].LegacyRegOffset );
        
        //
        //Record first time that trapping is disabled. Record only trap status bits handled by Trap handler
        //
        if( (LegcyKeyStatus & UHCI_TRAPEN_MASK)== UHCI_TRAPEN_MASK &&
            ( LegcyKeyStatus & UHCI_TRAPBY_MASK) != 0 ){
            //If legacy I/O caused SMI# and this is first time we are in uhci_trapEnable
            //then trapping in LEGKEY reg must have been enabled and one trap status is set.
            //Any port 60/64 operation within SMI# must be wrapped into
            //enable/ disable&clear status. So subsequent trapEnable will not produce any
            //trap statuses
            SavedLegcyStatus |= LegcyKeyStatus;
        }
        if(TrapEnable){
        
            //
            //clear status(es) that might be asserted by our handlers
            //
            ClearLegKeyStatusReg( LegcyKeyStatus | UHCI_TRAPBY_MASK);
            //
            // Enable Traps
            //
            WriteLegKeyReg( LegcyKeyStatus | UHCI_TRAPEN_MASK);
        } else {
        
            //
            //clear status(es) that might be asserted by our handlers
            //
            ClearLegKeyStatusReg( LegcyKeyStatus | UHCI_TRAPBY_MASK);
            //
            // Disable Traps
            //
            WriteLegKeyReg( (LegcyKeyStatus & ~UHCI_TRAPEN_MASK) );
        }
    }
    return TRUE;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
