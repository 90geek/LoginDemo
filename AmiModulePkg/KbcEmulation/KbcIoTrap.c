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

//<AMI_FHDR_START>
//****************************************************************************
// Name:        KbcIOTrap.c
//
// Description: Handles the SMI events for port 60/64
//
//****************************************************************************
//<AMI_FHDR_END>

#include "Token.h"
#include "KbcEmul.h"
#include "KbcIoTrap.h"
#include <Protocol/SmmIoTrapDispatch2.h>

void DisableIoTrapRegs();
void trap64w();
void trap60w();
void trap64r();
void trap60r();

IOTRAPDISPATCH trap_dispatcher[] = {
    { trap64w },
    { trap64r },
    { trap60w },
    { trap60r },
};

EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *IoTrapDispatch;
EFI_SMM_IO_TRAP_REGISTER_CONTEXT IoTrapContext;

void Trap6064_Handler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_IO_TRAP_REGISTER_CONTEXT  * DispatchContext );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IoTrapRegisterInfo
//
// Description: Enable the SMI for port 6064 access.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IoTrapRegisterInfo(){
    EFI_HANDLE IoTrapHandle;
    EFI_STATUS Status;

    // 
    // Register 60 port
    //     
    IoTrapHandle = NULL;
    IoTrapContext.Address = 0x60;
    IoTrapContext.Length = 8;
    IoTrapContext.Type = ReadWriteTrap;
    Status = IoTrapDispatch->Register(IoTrapDispatch,(EFI_SMM_HANDLER_ENTRY_POINT2)Trap6064_Handler, &IoTrapContext, &IoTrapHandle);
	ASSERT_EFI_ERROR(Status);
    // 
    // Register 64 port
    // 	    
    IoTrapHandle = NULL;
    IoTrapContext.Address = 0x64;
    IoTrapContext.Length = 8;
    IoTrapContext.Type = ReadWriteTrap;
    Status = IoTrapDispatch->Register(IoTrapDispatch,(EFI_SMM_HANDLER_ENTRY_POINT2)Trap6064_Handler, &IoTrapContext, &IoTrapHandle);
	ASSERT_EFI_ERROR(Status);
	
    return Status;
}
  
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        IoTrapProtocolEventNotify
//
// Description:
//  This function registers IOTrap Protocol callback function.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
IoTrapProtocolEventNotify (
    IN CONST EFI_GUID  *Protocol,
    IN VOID            *Interface,
    IN EFI_HANDLE      Handle )
{
    EFI_STATUS Status;
        
    Status = gSmst1->SmmLocateProtocol(&gEfiSmmIoTrapDispatch2ProtocolGuid,NULL,&IoTrapDispatch);
	ASSERT_EFI_ERROR(Status);
    // 
    // Register the IO 60/64 port
    // 
    IoTrapRegisterInfo();
    
    //
    // The SMI source for the port6064 is disabled. it will be enabled when we are in legacy enviorment. EFI enviorment Emulation is
    // Disabled.
    //
    DisableIoTrapRegs();
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        ACPIEnableEventNotify
//
// Description:
//  This function registers ACPI enable callback function.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
ACPIEnableEventNotify (
    IN CONST EFI_GUID  *Protocol,
    IN VOID            *Interface,
    IN EFI_HANDLE      Handle )
{
    // 
    // Disable the IOTrap
    //     
    IoTrapEnable(0);
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Smm_Register
//
// Description: Enable the SMI for port 6064 access.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Smm_Register()
{
    EFI_STATUS Status;
    EFI_GUID gEfiAcpiEnDispatchProtocolGuid = EFI_ACPI_EN_DISPATCH_PROTOCOL_GUID;
    VOID                          *IoTrapRegistration;
    VOID                          *AcpiRegistration;

    //
    // Locate IoTrap SMI Protocol
    //
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    Status = gSmst1->SmmLocateProtocol(&gEfiSmmIoTrapDispatch2ProtocolGuid,NULL,&IoTrapDispatch);
#else
    Status = gBS->LocateProtocol(&gEfiSmmIoTrapDispatch2ProtocolGuid,NULL,&IoTrapDispatch);
#endif
    if(Status != EFI_SUCCESS){
	    Status = gSmst1->SmmRegisterProtocolNotify(
                    &gEfiSmmIoTrapDispatch2ProtocolGuid,
                    IoTrapProtocolEventNotify,
                    &IoTrapRegistration
                    );
	    return;
    }
    
    Status = gSmst1->SmmRegisterProtocolNotify(
                    &gEfiAcpiEnDispatchProtocolGuid,
                    ACPIEnableEventNotify,
                    &AcpiRegistration
                    );
	ASSERT_EFI_ERROR(Status);
    
    // 
    // Register the IO 60/64 port
    // 
    IoTrapRegisterInfo();
    
    //
    // The SMI source for the port6064 is disabled. it will be enabled when we are in legacy enviorment. EFI enviorment Emulation is
    // Disabled.
    //
    DisableIoTrapRegs();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableIoTrapRegs
//
// Description: Disable the port6064 SMI source based on the Trap enable mask.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void DisableIoTrapRegs()
{
    
    //
    // Clear the enable bits
    //
    ClearIoTrapStatusReg();
    
    //
    //Disable the trap
    //
    WriteIoTrapCfg(0);
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Trap6064_Handler
//
// Description: SMI handler to handle the 64write, 64read, 60 write and 60 read SMI.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Trap6064_Handler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_IO_TRAP_REGISTER_CONTEXT  * DispatchContext )
{
    UINT8 Type;
    UINT32 RegAddr;
    EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *IoTrapDispatch;
    EFI_STATUS Status;
    
    // 
    // Get TrappedCycleRegister information
    //
    CheckTrappedCycleRegister(&RegAddr, &Type);
    
    //
    // if RegAddre == 0
    // 
    if(RegAddr == 0){
	    Status = gSmst1->SmmLocateProtocol(&gEfiSmmIoTrapDispatch2ProtocolGuid,NULL,&IoTrapDispatch);
		ASSERT_EFI_ERROR(Status);
	    IoTrapDispatch->UnRegister(IoTrapDispatch, DispatchHandle);
    }

    //
    // Clear the status
    //
    ClearIoTrapStatusReg();
    
    //
    // Disable Traps ( in responce to i/o handler can try to access a real KBC)
    //
    WriteIoTrapCfg(0);
    
    //
    // Dispatch the interrupt depending on saved status
    //
    if((RegAddr == 0x64) && (Type == 0)){
	    (*trap_dispatcher[0].trap_function)(); // 64 w
    } else if((RegAddr == 0x64) && (Type == 1)){
	    (*trap_dispatcher[1].trap_function)();
    } else if((RegAddr == 0x60) && (Type == 0)){
	    (*trap_dispatcher[2].trap_function)(); // 60 w
    } else if((RegAddr == 0x60) && (Type == 1)){
	    (*trap_dispatcher[3].trap_function)();
    }
    
    //
    // Clear the Status
    //
    ClearIoTrapStatusReg();

    //
    // Enable Traps 
    //
    WriteIoTrapCfg(1);
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  IoTrap_HasTrapStatus
//
// Description: Check if trap status is set in UHCI HC.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IoTrap_HasTrapStatus()
{
    // 
    // Check IoTrap SMI Enable or not
    // 
    return GetIoTrapRegisterStatus();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IoTrapEnable
//
// Description: Enable/Disable traping in UHCI HC.
//
// Input:       Boolean
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IoTrapEnable(BOOLEAN TrapEnable)
{
    //
    // clear status(es) that might be asserted by our handlers
    //    
    ClearIoTrapStatusReg();
    
    //
    // Enable Traps
    //
    WriteIoTrapCfg(TrapEnable);
    return TRUE;
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
