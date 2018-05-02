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
// $Header:  $
//
// $Revision:  $
//
// $Date:  $
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  OemVtdRmrr.c
//
// Description:
//  OemVtdRmrr driver implementation
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------

#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>

#include <Protocol/OemVtdRmrrProtocol.h>

#include "OemVtdRmrr.h"

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

static EFI_GUID gBdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;

static EFI_GUID gEfiOemVtdRmrrProtocolGuid = EFI_OEM_VTD_RMRR_PROTOCOL_GUID;

EFI_OEM_VTD_RMRR_PROTOCOL gOemVtdRmrrProtocol = { InsertOemVtdRmrr };

//----------------------------------------------------------------------

//
// Module global values
//
extern OEM_VTD_RMRR_HOOK OEM_VTD_RMRR_HOOK_LIST EndOfOemVtdRmrrHookListFunctions;
OEM_VTD_RMRR_HOOK* OemVtdRmrrHookList[] = {OEM_VTD_RMRR_HOOK_LIST NULL};

//
// Function implementations
//
EFI_STATUS
InsertOemVtdRmrr (
  IN VOID *DmaRemap )
{
    EFI_STATUS          Status;
    UINTN               Index;

    OEM_RMMR_DEBUG ((EFI_D_LOAD, "InsertOemVtdRmrr entered  \n"));

    if ( DmaRemap == NULL ) {
        DEBUG ((EFI_D_LOAD, "DmaRemap is NULL so return EFI_UNSUPPORTED \n"));
        return EFI_UNSUPPORTED;
    }

    for(Index=0; OemVtdRmrrHookList[Index]; Index++) {
        OEM_RMMR_DEBUG ((EFI_D_ERROR, "Calling Index: %x  function\n", Index));
        Status = OemVtdRmrrHookList[Index](OemVtdRmrrInsertRmrr, DmaRemap);
        OEM_RMMR_DEBUG ((EFI_D_ERROR, "Status: %r \n", Status));
    }

    OEM_RMMR_DEBUG ((EFI_D_ERROR, "InsertOemVtdRmrr Exiting  \n"));

    return EFI_SUCCESS;
}

VOID
EFIAPI
InstallOemVtdRmrrProtocol (
  IN  EFI_EVENT     Event,
  IN  VOID          *Context )
{
    EFI_STATUS          Status;
    UINTN               Index;
    BOOLEAN             InstallProtocol = FALSE;
    VOID                *BdsProtocol;

    OEM_RMMR_DEBUG ((EFI_D_ERROR, "InstallOemVtdRmrrProtocol entered  \n"));

    Status = gBS->LocateProtocol (
                &gBdsAllDriversConnectedProtocolGuid,
                NULL,
                &BdsProtocol);
    OEM_RMMR_DEBUG ((EFI_D_ERROR, "gBS->LocateProtocol gBdsAllDriversConnectedProtocolGuid protocol  status %r\n", Status));
    if (EFI_ERROR (Status)) {
        return;
    } 
    Status = gBS->CloseEvent (Event);
    OEM_RMMR_DEBUG ((EFI_D_ERROR, "CloseEvent Status:%r \n", Status));

    for ( Index=0; OemVtdRmrrHookList[Index]; Index++ ) {
        OEM_RMMR_DEBUG ((EFI_D_ERROR, "Calling Index: %x  function\n", Index));
        Status = OemVtdRmrrHookList[Index](OemVtdRmrrCollectInfo, NULL);
        if ( !EFI_ERROR(Status) && (InstallProtocol != TRUE) ) {
            InstallProtocol = TRUE;
        }
        OEM_RMMR_DEBUG ((EFI_D_ERROR, "Status: %r InstallProtocol: %x \n", Status, InstallProtocol));
    }

    DEBUG ((EFI_D_ERROR, "InstallProtocol: %x \n", InstallProtocol));

    //
    // Install the protocol
    //
    if ( InstallProtocol ) {
        EFI_HANDLE          NewHandle = NULL;
        Status = gBS->InstallProtocolInterface (
                    &NewHandle,
                    &gEfiOemVtdRmrrProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gOemVtdRmrrProtocol);
        OEM_RMMR_DEBUG ((EFI_D_ERROR, "gEfiOemVtdRmrrProtocolGuid protocol  status %r\n", Status));
    }

    OEM_RMMR_DEBUG ((EFI_D_ERROR, "InstallOemVtdRmrrProtocol exiting  \n"));

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name : InitializeOemVtdRmrr
//
// Description:
//  Entry point for OemVtdRmrr driver
//
// Input: 
//  IN EFI_HANDLE         ImageHandle     - Handle for the image of this driver
//  IN EFI_SYSTEM_TABLE   *SystemTable    - Pointer to the EFI System Table
//
// Output:
//   EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
InitializeOemVtdRmrr (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable )
{
    VOID        *Registration;

    OEM_RMMR_DEBUG ((EFI_D_ERROR, "InitializeOemVtdRmrr entered   \n"));

    //
    // Create Notification event for BdsAllDriversConnectedProtocol GUID
    //
    EfiCreateProtocolNotifyEvent (
        &gBdsAllDriversConnectedProtocolGuid,
        TPL_CALLBACK,
        InstallOemVtdRmrrProtocol,
        NULL,
        &Registration
        );

    OEM_RMMR_DEBUG ((EFI_D_ERROR, "InitializeOemVtdRmrr exiting.......\n"));

    return EFI_SUCCESS;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

