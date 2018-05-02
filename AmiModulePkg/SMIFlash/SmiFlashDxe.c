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
  SmiFlash DXE Driver File.
**/

//----------------------------------------------------------------------
// header includes
#include <AmiDxeLib.h>
#include <Token.h>
#include <SMIFlashELinks.h>
#if AMIUSB_SUPPORT == 1
#include <Guid\EventGroup.h>
#include <Protocol\AmiUsbController.h>
#endif

//----------------------------------------------------------------------
// component MACROs

//----------------------------------------------------------------------
// Module defined global variables

//----------------------------------------------------------------------
// Module specific global variable
// oem flash write enable/disable list creation code must be in this order
typedef VOID (SMIFLASH_INIT) (VOID);
extern SMIFLASH_INIT SMIFLASH_NOT_IN_SMM_LIST EndOfNotInSmmList;
SMIFLASH_INIT* SMIFlashNotInSmm[] = {SMIFLASH_NOT_IN_SMM_LIST NULL};

//----------------------------------------------------------------------
// externally defined variables

//----------------------------------------------------------------------
// Function definitions
#if AMIUSB_SUPPORT == 1
/**
 * Callback function executed when the gEfiEventExitBootServicesGuid is installed.
 * Callback code will delete the USBProtocol pointer..
 *
 * @param Event Pointer to the EFI_EVENT
 * @param Context Pointer to the context for this event
 */
VOID
SmiFlashExitBootServicesNotify (
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    EFI_STATUS  Status;
    EFI_GUID    AmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
    UINT32      VarAttr = 0;
    UINTN       VarSize = 0;
    UINTN       gSMIAmiUsb = 0;

    pBS->CloseEvent (Event);

    VarSize = sizeof(UINTN);

    Status = pRS->GetVariable(
                    L"USB_POINT",
                    &AmiGlobalVariableGuid,
                    &VarAttr,
                    &VarSize,
                    &gSMIAmiUsb );
    if( !EFI_ERROR(Status) )
    {
        VarSize = 0;
        gSMIAmiUsb = 0;

        Status = pRS->SetVariable(
                        L"USB_POINT",
                        &AmiGlobalVariableGuid,
                        VarAttr,
                        VarSize,
                        &gSMIAmiUsb );
    }
}
/**
 * Callback function executed when the EFI_USB protocol is installed by the USB Driver.
 * Callback code will save the USBProtocol pointer to Volatile NVRAM.
 *
 * @param Event Pointer to the EFI_EVENT
 * @param Context Pointer to the context for this event
 */
VOID
GetUsbProtocolPoint(
    IN EFI_EVENT   Event,
    IN VOID        *Context
)
{
    EFI_GUID            AmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
    EFI_USB_PROTOCOL    *gSMIAmiUsb = NULL;
    EFI_STATUS          Status;

    Status = pBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, &gSMIAmiUsb);
    if (EFI_ERROR(Status)) return;
    pBS->CloseEvent (Event);
    pRS->SetVariable (  L"USB_POINT",
                        &AmiGlobalVariableGuid,
                        EFI_VARIABLE_RUNTIME_ACCESS |
                        EFI_VARIABLE_BOOTSERVICE_ACCESS,
                        sizeof(UINTN),
                        &(UINTN)gSMIAmiUsb );
    return;
}
#endif //AMIUSB_SUPPORT
/**
 * Entry pointer to the SmiFlashDxeDriver. 
 *
 * @param ImageHandle Pointer to the handle that corresponds to this image
 * @param SystemTable Pointer to the EFI_SYSTEM_TABLE
 *
 * @retval EFI_SUCCESS This driver's entry point executed correctly
 */
EFI_STATUS 
SmiFlashDxeEntry (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    UINTN       i;
    EFI_EVENT   EvtProtocolEvt = NULL;
    VOID        *RgnUsbProtocol = NULL;
    EFI_EVENT   ExitBootEvt = NULL;

    InitAmiLib(ImageHandle, SystemTable);

#if AMIUSB_SUPPORT == 1
    // Register USB Protocol callback for saving USB Protocol address 
    // for runtime used.
    RegisterProtocolCallback (&gEfiUsbProtocolGuid, \
                              GetUsbProtocolPoint, \
                              NULL, \
                              &EvtProtocolEvt, \
                              &RgnUsbProtocol  );

    // Call Callback function for checking USB Protocol is installed or not.
    GetUsbProtocolPoint (EvtProtocolEvt, NULL);

    pBS->CreateEventEx(
            EVT_NOTIFY_SIGNAL,
            TPL_NOTIFY,
            SmiFlashExitBootServicesNotify,
            NULL,
            &gEfiEventExitBootServicesGuid,
            &ExitBootEvt );
#endif //AMIUSB_SUPPORT

    for (i = 0; SMIFlashNotInSmm[i] != NULL; SMIFlashNotInSmm[i++]());
    return EFI_SUCCESS;
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
