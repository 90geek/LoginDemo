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
// Name:        KbcIoTrap.h
//
// Description: Header file for IoTrap controller for Emulation
//
//****************************************************************************
//<AMI_FHDR_END>

#ifndef _KBC_IO_TRAP_H_
#define _KBC_IO_TRAP_H_

#define EFI_ACPI_EN_DISPATCH_PROTOCOL_GUID \
{ 0xbd88ec68, 0xebe4, 0x4f7b, 0x93, 0x5a, 0x4f, 0x66, 0x66, 0x42, 0xe7, 0x5f }

//
// Trap Dispatcher
//
typedef struct _IOTRAPDISPATCH {
    void (* trap_function)();
} IOTRAPDISPATCH;

BOOLEAN IoTrap_HasTrapStatus ();
BOOLEAN IoTrapEnable (BOOLEAN);
BOOLEAN NonSmmIoTrapEnable (BOOLEAN);

VOID ClearIoTrapStatusReg ();
VOID WriteIoTrapCfg (BOOLEAN);

VOID NonSmmClearIoTrapStatusReg ();
VOID NonSmmWriteIoTrapCfg (BOOLEAN);

VOID CheckTrappedCycleRegister(UINT32 *RegAddr, UINT8 *Type);
BOOLEAN GetIoTrapRegisterStatus();

#endif

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
