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
// Name:        KbcSbDxe.c
//
// Description:	Functions for UHCI in Non-Smm mode .
//
//<AMI_FHDR_END>
//**********************************************************************

#include "KbcEmulDxe.h"
#include "KbcSb.h"

static UINT16 SavedLegcyStatus = 0;

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

BOOLEAN    NonSmmSb_TrapEnable(BOOLEAN TrapEnable)
{

    EFI_TPL     OldTpl;
    
    OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);

    /// PORTING Needed depend on the SB 
    /// Clear the Trap SMI status Regsiters
    /// Based on the Input Argument enable/Disable the Port 60/64 SMI's.
    
    pBS->RestoreTPL(OldTpl);

    // Enabled Successfully. 
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
