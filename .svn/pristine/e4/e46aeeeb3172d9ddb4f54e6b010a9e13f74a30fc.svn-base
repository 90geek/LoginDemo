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
  Dxe specific version that contains the entry point and the callback for virtual address mode
  switching. 
**/

#include "FlashCommon.h"
#include <Library/UefiRuntimeServicesTableLib.h>

FLASH_DRIVER_MAILBOX MailBox;

/**
  Function that converts the pointers used by this driver to their virtual address equivalents 
  when the system is signaled that it will be entering a virtual addressing mode.
  @param Event Signaled event
  @param Context Calling context for this event
**/
VOID FlashDrvVirtAddressChange (
    IN EFI_EVENT Event, IN VOID *Context
)
{
    VOID **p;
    INT32 i;

    //Fixup protocol member functions
    p=(VOID**)&FlashData.Flash.Write;
    
    do
    {
        gRT->ConvertPointer(0, p++);
    }
    while (p!=(VOID**)&FlashData.Flash.DeviceWriteDisable);
    
    gRT->ConvertPointer(0, &FlashData.MailBox);
    
    for (i=0; i<NumberOfUpdatedAreas; i++)
    {
        gRT->ConvertPointer(0, &UpdatedArea[i].RomArea);
    }
    gRT->ConvertPointer(0,&Cs);
}

/** 
  Initialize the DXE portion of the Flash Driver. 
  
  @param ImageHandle Image handle for this driver
  @param SystemTable Pointer to the system table
  
  @return EFI_STATUS
  @retval EFI_SUCCESS
**/
EFI_STATUS FlashDriverInit(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handler = NULL;
    EFI_EVENT Event;
    
    Status = gBS->CreateEvent(
        EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,TPL_CALLBACK, 
        &FlashDrvVirtAddressChange, NULL, &Event
    );
    ASSERT_EFI_ERROR(Status);

//Initialize mailbox
    FlashData.MailBox = &MailBox;
    FlashData.MailBox->WriteEnableStatus = 0;
    Status = CreateCriticalSection(&Cs);
    ASSERT_EFI_ERROR(Status);
    FlashData.MailBox->Cs = Cs;

    Status = gBS->InstallProtocolInterface(&Handler, &gAmiFlashProtocolGuid, EFI_NATIVE_INTERFACE, &FlashData.Flash);
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
