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
//*************************************************************************
// $Header: $
//
// $ReviGpion: $
//
// $Date: $
//*************************************************************************
// ReviGpion History
// ----------------
// $Log: $
// 
//*************************************************************************
/** @file TbtOemLib.h
    AMI Thunderbolt OEM library header file, define all the Thunderbolt 
    function prototype OEM porting required.

**/

#ifndef _THUNDERBOLT_OEM_LIB_
#define _THUNDERBOLT_OEM_LIB_

#include <Guid/AmiTbtHrStatus.h>
#include <TbtCommon.h>

// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
UINT8 ReadSio(
  IN UINT8           Index
);

VOID WriteSio(
  IN UINT8           Index,
  IN UINT8           Value
);

VOID SetSio(
  IN UINT8           Index,
  IN UINT8           Set
);

VOID ResetSio(
  IN UINT8           Index,
  IN UINT8           Rst
);

VOID OpenSioConfig(
  VOID
);

VOID SetSioLdn(
  IN UINT8           Ldn
);
#endif
//*/

BOOLEAN TbtSetPCIe2TBTCommand(
  IN UINT8             UpPortBus,
  IN UINT8             Data,
  IN UINT8             Command,
  IN UINTN             Timeout
);

VOID TbtBeforeSxExitFlow(
  IN VOID              *Services,
  IN UINT8             TbtHostSeries
);

VOID PullHighTbtForcePowerPin( VOID );

VOID PullDownTbtForcePowerPin( VOID );

UINT8 SynchSecurityLevel(
  IN UINT8             BiosSecurityLevel,
  IN UINT8             TbtHostLocation
);

VOID ProgramTbtSecurityLevel(
  IN UINT8             *TbtSecurityLevel,
  IN UINT8             TBTHostSeries,
  IN UINT8             TbtHostLocation,
  IN BOOLEAN           IsPei
);

VOID FinialProgramTbtSecurityLevel(
  IN UINT8             TbtSecurityLevel
);

EFI_STATUS ActiveTbtGpio2(
  VOID
);

EFI_STATUS InactiveTbtGpio2(
  VOID
);

EFI_STATUS PollTbtGpio9(
  VOID
);

EFI_STATUS PullDownTbtGpio9(
  VOID
);

EFI_STATUS ReleaseTbtGpio9(
  VOID
);

EFI_STATUS PowerOnPOC(
  VOID
);

EFI_STATUS PowerOffPOC(
  VOID
);

#endif // _THUNDERBOLT_OEM_LIB_
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
