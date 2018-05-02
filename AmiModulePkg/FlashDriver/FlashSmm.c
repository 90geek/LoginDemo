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

/** @file
  Smm specific file of the FlashDriver. Contains the module entry point and initialization code.
**/

#include "FlashCommon.h"
#include <Library/SmmServicesTableLib.h>

/**
  Entry point for the Smm portion of the Flash Driver. Locates the Dxe protocol and copies the 
  mailbox and Critical Section pointers for use by this driver.
  
  @param ImageHandle Image handle for this driver
  @param SystemTable Pointer to the system table
  
  @return EFI_STATUS
  @retval EFI_SUCCESS
**/
EFI_STATUS FlashDriverSmmInit(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handler = NULL;
    FLASH_PROTOCOL_PRIVATE *NotSmmFlash;

    Status = gBS->LocateProtocol(&gAmiFlashProtocolGuid, NULL, &NotSmmFlash);
    ASSERT_EFI_ERROR(Status);

    //Reassign MailBox
    FlashData.MailBox = NotSmmFlash->MailBox;
    Cs = FlashData.MailBox->Cs;

    Status = gBS->InstallProtocolInterface(&Handler, &gAmiSmmFlashProtocolGuid, EFI_NATIVE_INTERFACE, &FlashData.Flash);
    ASSERT_EFI_ERROR(Status);
    Handler = NULL;
    Status = gSmst->SmmInstallProtocolInterface(&Handler, &gAmiSmmFlashProtocolGuid, EFI_NATIVE_INTERFACE, &FlashData.Flash);
    ASSERT_EFI_ERROR(Status);
    
    return Status;
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
