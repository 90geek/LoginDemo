//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
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
// Name: ExportHiiDb.c
//
// Description:
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>


#include <AmiDxeLib.h>
#include "SmiVariable.h"
#include <Protocol/HiiDatabase.h>

//---------------------------------------------------------------------------


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Procedure:   SaveHiiDBBufferAddress
// 
// Description: Routine which executes upon Ready to Boot event - updates
//              HII export database location.
//
// Input: 
//  Event   - Event of this callback function.
//  Context - Pointer to the context of this callback function.
//
// Output:  VOID
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SaveHiiDBBufferAddress(
    IN EFI_EVENT Event,
    IN VOID *Context )
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GUID ExportDatabaseGuid = EFI_HII_EXPORT_DATABASE_GUID;
    EFI_GUID EfiHiiDatabaseProtocolGuid = EFI_HII_DATABASE_PROTOCOL_GUID;
    EXPORT_HIIDB_BLOCK ExportHiiDbBlock;
    EFI_PHYSICAL_ADDRESS ExportDatabaseAddress = 0;
    VOID* ExportDatabasePtr = NULL;
    UINTN ExportDatabaseSize = 0;
    EFI_HII_DATABASE_PROTOCOL *pHiiDatabase = NULL;

    Status = pBS->LocateProtocol(
        &EfiHiiDatabaseProtocolGuid,
        NULL, 
        &pHiiDatabase
    );
    if (EFI_ERROR(Status))
        return;

    // call HII driver export database routine
    Status = pHiiDatabase->ExportPackageLists(
        pHiiDatabase, 
        0, 
        &ExportDatabaseSize, 
        ExportDatabasePtr
    );

    if (Status == EFI_BUFFER_TOO_SMALL) {

        // allocate memory for export database buffer
        Status = pBS->AllocatePool(
            EfiRuntimeServicesData, 
            ExportDatabaseSize, 
            &ExportDatabasePtr
        );
        if (EFI_ERROR(Status))
            return;

        // retrieve export database
        Status = pHiiDatabase->ExportPackageLists(
            pHiiDatabase, 
            0, 
            &ExportDatabaseSize, 
            ExportDatabasePtr
        );
        if (EFI_ERROR(Status))
            return;

        // create HiiDB EFI variable
        ExportHiiDbBlock.DataSize = (UINT32)ExportDatabaseSize;
        ExportHiiDbBlock.Data = (UINT32)ExportDatabasePtr;
        pRS->SetVariable(
            L"HiiDB",
            &ExportDatabaseGuid,
            EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
            sizeof(EXPORT_HIIDB_BLOCK),
            &ExportHiiDbBlock
        );
    }

    pBS->CloseEvent(Event);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: ExportHiiDbEntryPoint
//
// Description: Entry point of the ExportHiiDbEntryPoint 
// 
// Input: 
//  ImageHandle - Image handle
//  SystemTable - Pointer to the system table
//
// Output: EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ExportHiiDbEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;
    EFI_EVENT  ReadyToBootEvent;

    InitAmiLib(ImageHandle, SystemTable);

    Status = CreateReadyToBootEvent(
        TPL_CALLBACK,
        SaveHiiDBBufferAddress,
        NULL,
        &ReadyToBootEvent
    );
    ASSERT_EFI_ERROR(Status);
    return Status;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
