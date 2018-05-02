//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// Name:  		KbcUhciDxe.c
//
// Description:	Functions for UHCI in Non-Smm mode .
//
//<AMI_FHDR_END>
//**********************************************************************

#include "KbcEmulDxe.h"
#include "KbcUhci.h"

static UINT16 SavedLegcyStatus = 0;

UHCI_EMUL_DEVICE Uhci_Hc_Array[] = { 
#if defined(UHCI_EMUL_PCI_DEVICES)
		UHCI_EMUL_PCI_DEVICES, 
#endif
		{ 0xFFFF, 0xFF, 0xFF, 0xFF, 0xFF }
};

UINTN Uhci_Hc_Array_Size = sizeof(Uhci_Hc_Array) / sizeof(Uhci_Hc_Array[0]);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmValidateUhc
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
NonSmmValidateUhc (
    UHCI_EMUL_DEVICE  *Uhc
)
{
    UINT32  Data32 = 0;

    // End of the Device List.
    if(Uhc->BusDevFunc == 0xFFFF) {
    	return FALSE;
    }
    
    if (NonSmmReadPCIConfig (Uhc->BusDevFunc, 0) == 0xFFFFFFFF) {
        return FALSE;
    }

    Data32 = NonSmmReadPCIConfig (Uhc->BusDevFunc, 8) >> 8;
    if (Data32 != (*((UINT32*)&Uhc->InterfaceType) & 0x00FFFFFF)) {
        return FALSE;
    }

	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWriteLegKeyReg
//
// Description: Write the Value in to all the UHCI controller Legacy Regsiters.
//
// Input:       UINT8 Value
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void NonSmmWriteLegKeyReg ( UINT16 Value)
{
    UINTN UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!NonSmmValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }
        NonSmmWordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc, 
                        Uhci_Hc_Array[UhciCount].LegacyRegOffset, Value);
    }
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmClearLegKeyStatusReg
//
// Description: Clear the Port6064 SMI Status 
//
// Input:       UINT8 Value
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void NonSmmClearLegKeyStatusReg ( UINT16 Value)
{

    UINTN UhciCount;

#if ICH10_WORKAROUND
    //
    // Enable all the UCHI controller 
    // In ICH10 chipset, we need to clear the Port 6064 SMI status in disabled controller 
    // also. Otherwise it's keep on generating SMI
    //
    EnableAllUhciController();
#endif

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!NonSmmValidateUhc(&Uhci_Hc_Array[UhciCount])) {
             continue;
        }
        NonSmmWordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc,  
                        Uhci_Hc_Array[UhciCount].LegacyRegOffset, Value);
    }

#if ICH10_WORKAROUND
    //
    // Restore the UCHI controller's in RCBA Reg
    //
    RestoreUhciControllerStatus();
#endif

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmUhci_TrapEnable
//
// Description: Enable/Disable traping in UHCI HC.
//
// Input:       Boolean
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN    NonSmmUhci_TrapEnable(BOOLEAN TrapEnable)
{

    UINT16    LegcyKeyStatus;
    EFI_TPL     OldTpl;
    UINT16      UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!NonSmmValidateUhc(&Uhci_Hc_Array[UhciCount])) {
             continue;
        }

        LegcyKeyStatus =(UINT16) NonSmmReadPCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc , 
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

        OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);

        if(TrapEnable){
            //
            // Clear the status
            //
            NonSmmClearLegKeyStatusReg(LegcyKeyStatus | UHCI_TRAPBY_MASK);
            //
            // Enable Traps 
            //
            NonSmmWriteLegKeyReg( LegcyKeyStatus | UHCI_TRAPEN_MASK);
        } else {
            //
            // Clear the status
            //
            NonSmmClearLegKeyStatusReg(LegcyKeyStatus | UHCI_TRAPBY_MASK);

            //
            // Disable the Trap
            //
            NonSmmWriteLegKeyReg( (LegcyKeyStatus & ~UHCI_TRAPEN_MASK) );
        }
        pBS->RestoreTPL(OldTpl);
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
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
