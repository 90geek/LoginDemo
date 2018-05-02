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
//**********************************************************************
//
// $Header: $
//
// $Revision: $
//
// $Date: $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: $
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		AmtLockUsbKBD.c
//
// Description:	AMT Lock USB KeyBoard Functions.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <AmiDxeLib.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\AmiUsbController.h>
#include <Protocol\AlertStandardFormat.h>
//============================================================================
// Type definitions
//======================================================================
//Function Prototypes
//======================================================================
// Global and extern variables
EFI_SMM_SYSTEM_TABLE2   *gSmst2 = NULL;
EFI_USB_PROTOCOL        *gAmiUsbProtocol = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AMTLockUsbKBDSmi
//
// Description: Use UsbRtKbcAccessControl() to lock keyboard.
//
// Input:
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AMTLockUsbKBDSmi (
  IN     EFI_HANDLE     DispatchHandle,
  IN     CONST VOID     *Context,
  IN OUT VOID           *CommBuffer,
  IN OUT UINTN          *CommBufferSize
  )
{
    gAmiUsbProtocol->UsbRtKbcAccessControl(1);

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AmiUsbSmmProtocolCallback
//
// Description: While USB_RUNTIME_DRIVER_IN_SMM is on, the
//              UsbRtKbcAccessControl() will be ready after the
//              gAmiUsbSmmProtocolGuid is installed.
//              Register the AMTLockUsbKBDSmi after gAmiUsbSmmProtocolGuid is installed.
//
// Input:
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AmiUsbSmmProtocolCallback (
    CONST EFI_GUID  *Protocol,
    VOID            *Interface,
    EFI_HANDLE      Handle
)
{
    EFI_STATUS      Status;
    EFI_HANDLE      SmiHandle = NULL;

    Status = gSmst2->SmiHandlerRegister( &AMTLockUsbKBDSmi,
                                         &gEfiEventLegacyBootGuid, &SmiHandle );
    if( EFI_ERROR(Status) ) return Status;
    
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InSmmFunction
//
// Description: If the BootOption is set with LockKeyboard, register the
//              event with gEfiEventLegacyBootGuid or register SMI directly.
//              The PiSmmIpl will trigger it to lock keyboard.
//
// Input:
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS Status;
    EFI_SMM_BASE2_PROTOCOL          *pEfiSmmBase2Protocol = NULL;
    EFI_ALERT_STANDARD_FORMAT_PROTOCOL  *pAlertStandardFormatProtocol = NULL;
    AMI_USB_SMM_PROTOCOL            *pAmiUsbSmmProtocol = NULL;
    VOID	                        *AmiUsbSmmProtocolReg = NULL;
    EFI_ASF_BOOT_OPTIONS                *pAsfBootOptions = NULL;
    EFI_HANDLE                      SmiHandle = NULL;
    
    Status = pBS->LocateProtocol( &gEfiUsbProtocolGuid, NULL,
                                  &gAmiUsbProtocol );
	if(EFI_ERROR(Status)) return Status;
    
    Status = pBS->LocateProtocol( &gEfiSmmBase2ProtocolGuid, NULL,
                                  &pEfiSmmBase2Protocol );
    if( !EFI_ERROR(Status) )
    {
        Status = pEfiSmmBase2Protocol->GetSmstLocation(
                    pEfiSmmBase2Protocol, &gSmst2 );
        if( EFI_ERROR(Status) ) return Status;
    }

    Status = pBS->LocateProtocol( &gEfiAlertStandardFormatProtocolGuid, NULL,
                                  &pAlertStandardFormatProtocol );
    if( !EFI_ERROR(Status) )
    {
        Status = pAlertStandardFormatProtocol->GetBootOptions (
                        pAlertStandardFormatProtocol, &pAsfBootOptions) ;
        if( EFI_ERROR(Status) ) return Status;
    }
    
    if( pAsfBootOptions->BootOptions & LOCK_KEYBOARD )
    {
#if USB_RUNTIME_DRIVER_IN_SMM
        Status = gSmst2->SmmLocateProtocol( &gAmiUsbSmmProtocolGuid , NULL,
                                            &pAmiUsbSmmProtocol);
        if( !EFI_ERROR(Status) )
        {
            Status = gSmst2->SmiHandlerRegister( &AMTLockUsbKBDSmi,
                                                 &gEfiEventLegacyBootGuid,
                                                 &SmiHandle );
        }
        else
        {
            Status = gSmst2->SmmRegisterProtocolNotify (
                                &gAmiUsbSmmProtocolGuid,
                                AmiUsbSmmProtocolCallback,
                                &AmiUsbSmmProtocolReg );
        }
#else
        Status = gSmst2->SmiHandlerRegister( &AMTLockUsbKBDSmi,
                                             &gEfiEventLegacyBootGuid,
                                             &SmiHandle );
#endif
    }
    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AMTLockUsbKBDEntryPoint
//
// Description: Lock USB Keyboard Entrypoint.
//
// Input:
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AMTLockUsbKBDEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandlerEx (ImageHandle, SystemTable, InSmmFunction, NULL);
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
