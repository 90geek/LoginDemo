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
// Name:        KbcSbIoTrap.h
//
// Description: Header file IO Trap SMI's 
//
//****************************************************************************
//<AMI_FHDR_END>

#ifndef _KBC_SB_IO_TRAP_H_
#define _KBC_SB_IO_TRAP_H_

#define PchPciDeviceMmBase(Bus, Device, Function) \
( \
      (UINTN) PcdGet64 (PcdPciExpressBaseAddress) + (UINTN) (Bus << 20) + (UINTN) (Device << 15) + (UINTN) \
        (Function << 12) \
)

VOID ClearIoTrapStatusReg ();
VOID WriteIoTrapCfg (BOOLEAN);

VOID NonSmmWriteIoTrapCfg (BOOLEAN);
VOID NonSmmClearIoTrapStatusReg ();

UINT32 IoTrapBaseAddr();
UINT32 GetIoTrapRegister(UINT8);

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
