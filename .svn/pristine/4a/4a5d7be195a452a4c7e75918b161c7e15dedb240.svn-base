//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: 
//
// $Revision: 
//
// $Date: 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        CrbSmi.c
//
// Description: This file contains code for all CRB SMI events
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Token.h>
#include <Setup.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmSwDispatch2.h>
#include <Protocol\SmmSxDispatch2.h>
#include <Protocol\SmmPowerButtonDispatch2.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBSwSmiHandler
//
// Description: This is a template CRB software SMI Handler for Porting.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CRBSwSmiHandler (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL)
{
    // Porting if needed
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBSxSmiHandler
//
// Description: This is a template CRB Sx SMI Handler for Porting.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SX_DISPATCH_CONTEXT
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CRBSxSmiHandler (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL )
{
    // Porting if needed
    return EFI_SUCCESS;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBPowerButtonSmiHandler
//
// Description: This is a template CRB Power Button SMI Handler for Porting.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the
//                                EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CRBPowerButtonSmiHandler (
    IN EFI_HANDLE    DispatchHandle,
    IN CONST VOID    *Context OPTIONAL,
    IN OUT VOID      *CommBuffer OPTIONAL,
    IN OUT UINTN     *CommBufferSize OPTIONAL)
{
    // Porting if needed
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: Installs CRB SMM Child Dispatcher Handler.
//
// Input:       ImageHandle - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//                  EFI_NOT_FOUND - The SMM Base protocol is not found.
//                  EFI_SUCCESS   - Installs CRB SMM Child Dispatcher Handler
//                                  successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS                              Status;
    EFI_SMM_SW_DISPATCH2_PROTOCOL           *pSwDispatch;
    EFI_SMM_SX_DISPATCH2_PROTOCOL           *pSxDispatch;
    EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *pPwrDispatch;
    EFI_SMM_SW_REGISTER_CONTEXT             SwContext = {CRB_SWSMI};
    EFI_SMM_SX_REGISTER_CONTEXT             SxContext = {SxS3, SxEntry};
    EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT   PwrContext = {EfiPowerButtonEntry};    
    EFI_HANDLE                              Handle;
    
    Status = InitAmiSmmLib (ImageHandle, SystemTable);
    if (EFI_ERROR(Status)) return Status;    

    Status = pSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, &pSwDispatch);
    if (!EFI_ERROR(Status)) {
        Status  = pSwDispatch->Register (pSwDispatch, \
                                         CRBSwSmiHandler, \
                                         &SwContext, \
                                         &Handle);
    }

    Status = pSmst->SmmLocateProtocol (&gEfiSmmSxDispatch2ProtocolGuid, NULL, &pSxDispatch);    
    if (!EFI_ERROR(Status)) {
        Status  = pSxDispatch->Register (pSxDispatch, \
                                         CRBSxSmiHandler, \
                                         &SxContext, \
                                         &Handle);
    }

    Status = pSmst->SmmLocateProtocol ( 
                       &gEfiSmmPowerButtonDispatch2ProtocolGuid, 
                       NULL,
                       &pPwrDispatch);
    if (!EFI_ERROR(Status)) {
        Status  = pPwrDispatch->Register (pPwrDispatch, \
                                          CRBPowerButtonSmiHandler, \
                                          &PwrContext, \
                                          &Handle);
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitializeCrbSmm
//
// Description: Installs CRB SMM Child Dispatcher Handler.
//
// Input:       ImageHandle - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//              EFI_NOT_FOUND - The SMM Base protocol is not found.
//              EFI_SUCCESS   - Installs CRB SMM Child Dispatcher Handler
//                              successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitializeOemSmm (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
