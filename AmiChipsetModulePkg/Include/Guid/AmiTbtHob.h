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
// $Log: $
//
//*************************************************************************

/** @file AmiTbtHob.h
    AMI Thunderbolt HOB header file, define all the Thunderbolt 
    HOB equates and structures in this file.

**/

#ifndef _AMI_TBT_HOB_H_
#define _AMI_TBT_HOB_H_

#include <Hob.h>

#define AMI_TBT_HOB_GUID { 0xf85db11d, 0x69bd, 0x4019, { 0x9d, 0x57, 0x72, 0x1c, 0x9f, 0x43, 0xb2, 0xc8 } }

typedef struct {
  EFI_HOB_GUID_TYPE        Header;                 ///< AMI Thunderbolt Hob GUID header
  UINT8                    TbtSecurityLevelFlag;   ///< If need programming Thunderbolt security level in DXE phase, this flag will be set
  UINT8                    TbtSxExitFlowInDxe;     ///< If need doing Thunderbolt Sx_Exit flow in DXE phase, this flag will be set
} TBT_HOB;

extern EFI_GUID gAmiTbtHobGuid;

#endif // _THUNDERBOLT_OEM_PROTOCOL_
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
