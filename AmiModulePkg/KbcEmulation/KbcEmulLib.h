//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulLib.h 4     2/10/11 12:59a Rameshr $
//
// $Revision: 4 $
//
// $Date: 2/10/11 12:59a $
//
//****************************************************************************

//<AMI_FHDR_START>
//**********************************************************************
// Name:        KbcEmullib.h
//
// Description:	KBC emulation Lib header file used in other files
//
//**********************************************************************
//<AMI_FHDR_END>

#ifndef _EMUL6064LIB_H_INC_

UINT8       ByteReadIO(UINT16 wIOAddr);
void        ByteWriteIO (UINT16 wIOAddr, UINT8 bValue);
UINT16      WordReadIO(UINT16 wIOAddr);
void        WordWriteIO (UINT16 wIOAddr, UINT16 wValue);
UINT32      DwordReadIO(UINT16 wIOAddr);
void        DwordWriteIO(UINT16 wIOAddr, UINT32 dValue);
UINT32      ReadPCIConfig(UINT16 BusDevFunc, UINT8 Register);
void        ByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value);
void        WordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value);
void        DwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value);
UINT32      ReadPCIConfig(UINT16 BusDevFunc, UINT8 Register);

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
