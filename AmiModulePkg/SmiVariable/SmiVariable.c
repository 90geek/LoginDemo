//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//****************************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: SmiVariable.c
//
// Description: Interface to a subset of EFI Framework protocols using 
// legacy interfaces that will allow external software to access EFI 
// protocols in a legacy environment.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>


//---------------------------------------------------------------------------

#include <AmiDxeLib.h>
#include <AmiSmm.h>
#include <Token.h>
#include <AmiCspLib.h>
#include <AmiHobs.h>
#include "SmiVariable.h"
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmControl2.h>
#include <Protocol/SmmCpu.h>
#include <Library/AmiBufferValidationLib.h>

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CheckDestinationMemoryRange
//
// Description: Check destination address range if it's cleared by zero.
//
// Input: 
//  Address - starting address
//  Range   - length of the area
//
// Output: 
//  EFI_SUCCESS         - Access granted
//  EFI_ACCESS_DENIED   - Access denied!
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CheckDestinationMemoryRange( IN UINT8 *Address, IN UINTN Range )
{
    while (Range--)
        if (*Address++)
            return EFI_ACCESS_DENIED;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CheckAddressRangeHiiDb
//
// Description: Check source address range if it's not out of the HiiDb space.
//
// Input: 
//  Address - starting address
//  Range   - length of the area
//
// Output: 
//  EFI_SUCCESS         - Access granted
//  EFI_ACCESS_DENIED   - Access denied!
//
// NOTE: Remove this function after COPY_MEMORY_SUBFUNCTION will be removed.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CheckAddressRangeHiiDb( IN UINT8 *Address, IN UINTN Range )
{
    EFI_STATUS Status;
    EFI_GUID ExportDatabaseGuid = EFI_HII_EXPORT_DATABASE_GUID;
    EXPORT_HIIDB_BLOCK ExportHiiDbBlock;
    UINTN  DataSize = sizeof(EXPORT_HIIDB_BLOCK);
    UINT32 Attributes;

    // Get HII DB variable
    Status = pRS->GetVariable(
        L"HiiDB",
        &ExportDatabaseGuid,
        &Attributes,
        &DataSize,
        &ExportHiiDbBlock
    );
    if (EFI_ERROR(Status))
        return EFI_ACCESS_DENIED;

    // Check the size and range
    if ( (Range > ExportHiiDbBlock.DataSize) ||
         ((UINT32)Address < ExportHiiDbBlock.Data) || 
         ( ((UINT32)Address + Range) > (ExportHiiDbBlock.Data + ExportHiiDbBlock.DataSize)) )
        return EFI_ACCESS_DENIED;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: VariableInterface
//
// Description:
//  Calling the SMI Interface. The caller will write AL (the value 0xef) to 
//  the SMI Command Port as defined in the ACPI FADT. The SMI handler will 
//  update the callers' buffer(s) and return.
//
// Input: 
//  DispatchHandle
//  DispatchContext
//
// Output: VOID
//
// Notes:
// The function will clear the carry bit if it is successful (CF = 0). 
// If the function is unsuccessful, it will set the carry bit and set the 
// error code in the AH register as indicated by the error table below.
// The function returns the following data in the provided parameter block. 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS VariableInterface( 
    IN EFI_HANDLE DispatchHandle,
    IN CONST VOID  *Context OPTIONAL,
    IN OUT   VOID  *CommBuffer OPTIONAL,
    IN OUT   UINTN *CommBufferSize OPTIONAL )
{
    EFI_STATUS Status = EFI_SUCCESS;
    REG_BLOCK* RegBlockPtr = NULL;
    VARIABLE_BLOCK *VariableBlock = NULL;
    GET_NEXT_VARIABLE_BLOCK *GetNextVariableBlock = NULL;
    UINTN  DataSize;
    EFI_SMM_SW_CONTEXT *SmmSwContext = ((EFI_SMM_SW_CONTEXT*)CommBuffer);
    EFI_GUID EfiSmmCpuProtocolGuid = EFI_SMM_CPU_PROTOCOL_GUID;
    EFI_SMM_CPU_PROTOCOL *SmmCpuProtocol = NULL;
    EFI_PHYSICAL_ADDRESS Register = 0;

    Status = pSmst->SmmLocateProtocol(
        &EfiSmmCpuProtocolGuid,
        NULL, 
        &SmmCpuProtocol 
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status))
        return Status;

    // Read the RSI register
    Status = SmmCpuProtocol->ReadSaveState( 
        SmmCpuProtocol,
        sizeof(UINT32), 
        EFI_SMM_SAVE_STATE_REGISTER_RSI,
        SmmSwContext->SwSmiCpuIndex,
        &Register
    );
    if (EFI_ERROR(Status))
        return Status;

    RegBlockPtr = (REG_BLOCK*)Register;

    switch((RegBlockPtr->EAX & 0xff00) >> 8) {

        case GET_VARIABLE_SUBFUNCTION: 
            // Address of the VARIABLE_BLOCK parameter block
            VariableBlock = (VARIABLE_BLOCK*)RegBlockPtr->EBX;
            DataSize = VariableBlock->DataSize;

            // check destination address range if it's cleared by zero
            Status = CheckDestinationMemoryRange((UINT8*)(UINTN)VariableBlock->Data, DataSize);
            if (!EFI_ERROR(Status)) {
                // check address range to avoid TSEG area (return EFI_ACCESS_DENIED)
                Status = AmiValidateMemoryBuffer((VOID*)(UINTN)VariableBlock->Data, DataSize);
                if (!EFI_ERROR(Status)) {
                    Status = pRS->GetVariable( 
                        (CHAR16*)(UINTN)VariableBlock->VariableName, 
                        &VariableBlock->VendorGuid, 
                        &VariableBlock->Attributes, 
                        &DataSize, 
                        (VOID*)(UINTN)VariableBlock->Data 
                    );
                    VariableBlock->DataSize = (UINT32)DataSize;
                }
            }
        break;

        case GET_NEXT_VARIABLE_SUBFUNCTION:
            // Address of the GET_NEXT_VARIABLE_BLOCK parameter block
            GetNextVariableBlock = (GET_NEXT_VARIABLE_BLOCK*)RegBlockPtr->EBX;
            DataSize = GetNextVariableBlock->VariableNameSize;

            // check address range to avoid TSEG area (return EFI_ACCESS_DENIED)
            Status = AmiValidateMemoryBuffer((VOID*)GetNextVariableBlock->VariableName, DataSize);
            if (!EFI_ERROR(Status)) {
                Status = pRS->GetNextVariableName( 
                    &DataSize,
                    (CHAR16*)(UINTN)GetNextVariableBlock->VariableName,
                    &GetNextVariableBlock->VendorGuid 
                );
                GetNextVariableBlock->VariableNameSize = (UINT32)DataSize;
            }
        break;

        case SET_VARIABLE_SUBFUNCTION:
            // Address of the VARIABLE_BLOCK parameter block
            VariableBlock = (VARIABLE_BLOCK*)RegBlockPtr->EBX;

            // check address range to avoid TSEG area (return EFI_ACCESS_DENIED)
            Status = AmiValidateMemoryBuffer((VOID*)(UINTN)VariableBlock->Data, VariableBlock->DataSize);
            if (!EFI_ERROR(Status))
                Status = pRS->SetVariable( 
                    (CHAR16*)(UINTN)VariableBlock->VariableName, 
                    &VariableBlock->VendorGuid, 
                    VariableBlock->Attributes, 
                    VariableBlock->DataSize, 
                    (VOID*)(UINTN)VariableBlock->Data 
                );
        break;

        // Remove this sub-function after Utility will be able do not use it for Export HII DB!!!
        case COPY_MEMORY_SUBFUNCTION:
        {
            COPY_MEMORY_BLOCK *CopyMemBlock = NULL;

            // Address of the COPY_MEMORY_BLOCK parameter block
            CopyMemBlock = (COPY_MEMORY_BLOCK*)RegBlockPtr->EBX;

            if ( CopyMemBlock->Size == 0 )
                Status = EFI_INVALID_PARAMETER;
            else {

                // Check source address range if it's not out of the HiiDb space
                Status = CheckAddressRangeHiiDb((UINT8*)(UINTN)CopyMemBlock->SrcAddr, CopyMemBlock->Size);
                if (!EFI_ERROR(Status)) {
                
                    // check destination address range if it's cleared by zero
                    Status = CheckDestinationMemoryRange((UINT8*)(UINTN)CopyMemBlock->DestAddr, CopyMemBlock->Size);
                    if (!EFI_ERROR(Status)) {
                    
                        // check address range to avoid TSEG area (return EFI_ACCESS_DENIED)
                        Status = AmiValidateMemoryBuffer((VOID*)(UINTN)CopyMemBlock->DestAddr, CopyMemBlock->Size);
                        if (!EFI_ERROR(Status)) {
                            Status = AmiValidateMemoryBuffer((VOID*)(UINTN)CopyMemBlock->SrcAddr, CopyMemBlock->Size);
                            if (!EFI_ERROR(Status)) {
                                MemCpy( 
                                    (UINT8*)(UINTN)CopyMemBlock->DestAddr, 
                                    (UINT8*)(UINTN)CopyMemBlock->SrcAddr, 
                                    CopyMemBlock->Size
                                );
                                Status = EFI_SUCCESS;
                            }
                        }
                    }
                }
            }
        }
        break;

        default: 
            Status = EFI_INVALID_PARAMETER;
        break;
    }

    RegBlockPtr->EAX &= 0xffff0000; 

    if (EFI_ERROR(Status)) {

        RegBlockPtr->EFLAGS |= CARRY_FLAG;  // set CF

        // Convertation of the EFI Status to standard INT 0x15 error codes.
        RegBlockPtr->EAX |= (Status | 0x80) << 8; 

    } else
        RegBlockPtr->EFLAGS &= ~CARRY_FLAG; // clear CF

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InSmmFunction
//
// Description: Registration of the SMI function
//
// Input: 
//  ImageHandle - Image handle
//  SystemTable - Pointer to the system table
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;
    EFI_HANDLE Handle = 0;
    EFI_GUID EfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID;
    EFI_SMM_SW_DISPATCH2_PROTOCOL *SwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT   SwContext;
    
    Status = pSmst->SmmLocateProtocol(
        &EfiSmmSwDispatchProtocolGuid, 
        NULL, 
        &SwDispatch 
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status))
        return Status;

    SwContext.SwSmiInputValue = FUNCTION_NUMBER;
    Status = SwDispatch->Register( 
        SwDispatch, 
        VariableInterface, 
        &SwContext, 
        &Handle 
    );
    ASSERT_EFI_ERROR(Status);
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmiVariableEntryPoint
//
// Description: Entry point of the SMI variable interface
// 
// Input: 
//  ImageHandle - Image handle
//  SystemTable - Pointer to the system table
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmiVariableEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;

    InitAmiLib( ImageHandle, SystemTable );

    // Initialize the SMM handler 
    Status = InitSmmHandler( 
        ImageHandle, 
        SystemTable, 
        InSmmFunction, 
        NULL
    );
    ASSERT_EFI_ERROR(Status);

    return Status;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
