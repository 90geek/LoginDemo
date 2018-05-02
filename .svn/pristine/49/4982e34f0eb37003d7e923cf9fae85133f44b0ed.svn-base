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

//<AMI_FHDR_START>
//**********************************************************************
// Name:  KbcIoTrapDxe.c
//
// Description:	Functions for IoTrap in Non-Smm mode .
//**********************************************************************
//<AMI_FHDR_END>

#include "KbcIoTrap.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmIoTrapEnable
//
// Description: Enable/Disable traping in UHCI HC.
//
// Input:       Boolean
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN NonSmmIoTrapEnable(BOOLEAN TrapEnable)
{
    //
    // Call NonSmmClearIoTrapStatusReg
    //
    NonSmmClearIoTrapStatusReg();
    
    //
    // Call NonSmmWriteIoTrapCfg function
    //
    NonSmmWriteIoTrapCfg(TrapEnable);
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
