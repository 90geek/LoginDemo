//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file HddSMART.h
    This file contains the Includes, Definitions, typedefs,
    Variable and External Declarations, Structure and
    function prototypes needed for the IdeSMART driver

**/

#ifndef _HDD_SMART_
#define _HDD_SMART_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include "Protocol/PciIo.h"
#include "Protocol/DevicePath.h"
#include "protocol/DriverBinding.h"
#include "protocol/BlockIo.h"
#include <Protocol/AMIPostMgr.h>
#include <Protocol/SimpleTextIn.h>
#include "HddSmartCommon.h"

//---------------------------------------------------------------------------

AMI_HDD_SMART_INIT_PROTOCOL *gHddSmartInitProtocol;

#define     ZeroMemory( Buffer, Size ) pBS->SetMem( Buffer, Size, 0 )

#define     FIS_REGISTER_D2H    0x34        // Device To Host

#pragma pack(1)
typedef struct
{
    UINT8   Ahci_Dsfis[0x1C];               // DMA Setup Fis
    UINT8   Ahci_Dsfis_Rsvd[0x04];
    UINT8   Ahci_Psfis[0x14];               // PIO Setup Fis
    UINT8   Ahci_Psfis_Rsvd[0x0C];
    UINT8   Ahci_Rfis[0x14];                // D2H Register Fis
    UINT8   Ahci_Rfis_Rsvd[0x04];
    UINT64  Ahci_Sdbfis;                    // Set Device Bits Fis
    UINT8   Ahci_Ufis[0x40];                // Unknown FIS
    UINT8   Ahci_Ufis_Rsvd[0x60];
} AHCI_RECEIVED_FIS;
#pragma pack()

UINTN 
EfiValueToString (
    IN OUT CHAR16   *Buffer,
    IN INT64    Value,
    IN UINTN    Flags,
    IN UINTN    Width
);

EFI_STATUS 
GetHiiString (
    IN EFI_HII_HANDLE   HiiHandle,
    IN STRING_REF   Token,
    IN OUT UINTN    *pDataSize,
    OUT EFI_STRING  *ppData
);

EFI_STATUS 
CommonNonDataHook (
    IN VOID                 *BusInterface,
    IN COMMAND_STRUCTURE    CommandStructure,
    IN BOOLEAN              ModeFlag
);

EFI_STATUS 
InitSmartSupport (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

EFI_STATUS 
SmartReturnStatusWrapper (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

EFI_STATUS 
InstallSmartInterface (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

EFI_STATUS 
UnInstallSmartInterface (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

//---------------------------------------------------------------------------
// SMART DIAGNOSTICS SUPPORT START
//---------------------------------------------------------------------------

EFI_STATUS 
SmartSelfTest (
    IN AMI_HDD_SMART_PROTOCOL   *This,
    IN UINT8                    SelfTestType,
    OUT UINT16                  *PollPeriod
);

EFI_STATUS 
SmartSelfTestStatus (
    IN AMI_HDD_SMART_PROTOCOL   *This,
    OUT UINT8                   *TestStatus
);

EFI_STATUS 
SmartReturnStatus (
    IN AMI_HDD_SMART_PROTOCOL   *This
);

EFI_STATUS 
SendSmartCommand (
    IN AMI_HDD_SMART_PROTOCOL   *This,
    IN UINT8                    SubCommand,
    IN UINT8                    AutoSaveEnable,    //OPTIONAL
    IN UINT8                    SelfTestType       //OPTIONAL
);

EFI_STATUS 
SmartReadData (
    IN  AMI_HDD_SMART_PROTOCOL  *This,
    IN  UINT8                   SubCommand,
    OUT VOID                    *Buffer,
    IN  UINT8                   LogAddress,   //OPTIONAL
    IN  UINT8                   SectorCount   //OPTIONAL
);

EFI_STATUS 
SmartWriteData (
    IN AMI_HDD_SMART_PROTOCOL   *This,
    IN UINT8                    SubCommand,
    IN VOID                     *Buffer,
    IN UINT8                    LogAddress,
    IN UINT8                    SectorCount
);

EFI_STATUS 
SmartAbortSelfTest (
    IN  AMI_HDD_SMART_PROTOCOL  *This
);

EFI_STATUS 
SmartGetSmartData (
    IN  AMI_HDD_SMART_PROTOCOL  *This,
    OUT UINT8                   **SmartData
);

extern 
CHAR16 
*HiiGetString ( 
    VOID*  handle, 
    UINT16 token 
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
