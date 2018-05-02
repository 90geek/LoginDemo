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
// $Revision: $
//
// $Date: $
//*************************************************************************
// Revision History
// ----------------
//
//*************************************************************************
/** @file TbtDxeLib.h
    AMI Thunderbolt DXE library header file, define all the Thunderbolt 
    DXE function prototype.

**/

#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <PciBus.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <TbtCommon.h>

#ifndef __TBTDXELIB_H__
#define __TBTDXELIB_H__



#ifdef __cplusplus
extern "C" {
#endif

EFI_STATUS TbtProtectedPciDevice
(
  IN PCI_DEV_INFO *PciDevice
);

VOID TbtDxeInvokeSmiHandler();

BOOLEAN
IsULTPchSeries
( 
  VOID 
);

BOOLEAN
IsSocPchSeries
( 
  VOID 
);

#ifdef __cplusplus
}
#endif

#endif
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
