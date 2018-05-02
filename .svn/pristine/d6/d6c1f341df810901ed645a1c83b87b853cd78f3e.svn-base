//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: $
//
// $Revision: $
//
// $Date: $
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  KbcEmulDxe.h
//
// Description:	KBC emulation header file for Non-Smm Mode
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Efi.h>
#include <AmiDxeLib.h>
#include "Token.h"
#include <Protocol/Emul6064Trap.h>
#include <Protocol/CpuIo2.h>


typedef struct _HC_DEV_STRUC {
    UINT16          wPCIDev;
    UINT16          wHCType;
} HC_DEV_STRUC;

extern EFI_CPU_IO2_PROTOCOL *CpuIo;

//
//Checks if Trap status is set
//
BOOLEAN     NonSmmTrapEnable(BOOLEAN );
UINT8       NonSmmByteReadIO(UINT16 wIOAddr);
void        NonSmmByteWriteIO (UINT16 wIOAddr, UINT8 bValue);
UINT16      NonSmmWordReadIO(UINT16 wIOAddr);
void        NonSmmWordWriteIO (UINT16 wIOAddr, UINT16 wValue);
UINT32      NonSmmDwordReadIO(UINT16 wIOAddr);
void        NonSmmDwordWriteIO(UINT16 wIOAddr, UINT32 dValue);
UINT32      NonSmmReadPCIConfig(UINT16 BusDevFunc, UINT8 Register);
void        NonSmmByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value);
void        NonSmmWordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value);
void        NonSmmDwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value);
UINT32      NonSmmReadPCIConfig(UINT16 BusDevFunc, UINT8 Register);


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
