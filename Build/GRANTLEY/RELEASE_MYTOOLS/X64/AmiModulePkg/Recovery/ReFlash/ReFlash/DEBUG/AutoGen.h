/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_70e1a818_0be1_4449_bfd4_9ef68c7f02a8
#define _AUTOGENH_70e1a818_0be1_4449_bfd4_9ef68c7f02a8

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x70e1a818, 0x0be1, 0x4449, {0xbf, 0xd4, 0x9e, 0xf6, 0x8c, 0x7f, 0x02, 0xa8}}

// Guids
extern EFI_GUID gAmiRecoveryImageHobGuid;
extern EFI_GUID gAmiModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gAmiGlobalVariableGuid;
extern EFI_GUID gAmiRomLayoutFfsFileGuid;
extern EFI_GUID gAmiRomLayoutGuid;
extern EFI_GUID gAmiSmbiosNvramGuid;

// Protocols
extern EFI_GUID gFlashProtocolGuid;
extern EFI_GUID gAmiReflashProtocolGuid;
extern EFI_GUID gEfiConsoleControlProtocolGuid;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gEfiGraphicsOutputProtocolGuid;
extern EFI_GUID gEfiHiiFontProtocolGuid;
extern EFI_GUID gEfiUgaDrawProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gEfiDriverConfigurationProtocolGuid;
extern EFI_GUID gEfiDriverConfiguration2ProtocolGuid;
extern EFI_GUID gEfiDriverDiagnosticsProtocolGuid;
extern EFI_GUID gEfiDriverDiagnostics2ProtocolGuid;
extern EFI_GUID gEfiAcpiTableProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdRecoveryImageSize  140U
#define _PCD_SIZE_PcdRecoveryImageSize 4
#define _PCD_GET_MODE_SIZE_PcdRecoveryImageSize  _PCD_SIZE_PcdRecoveryImageSize 
#define _PCD_VALUE_PcdRecoveryImageSize  0x800000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdRecoveryImageSize;
#define _PCD_GET_MODE_32_PcdRecoveryImageSize  _gPcd_FixedAtBuild_PcdRecoveryImageSize
//#define _PCD_SET_MODE_32_PcdRecoveryImageSize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_AmiPcdInstallEsrtTable  245U
#define _PCD_SIZE_AmiPcdInstallEsrtTable 1
#define _PCD_GET_MODE_SIZE_AmiPcdInstallEsrtTable  _PCD_SIZE_AmiPcdInstallEsrtTable 
#define _PCD_VALUE_AmiPcdInstallEsrtTable  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_AmiPcdInstallEsrtTable;
#define _PCD_GET_MODE_BOOL_AmiPcdInstallEsrtTable  _gPcd_FixedAtBuild_AmiPcdInstallEsrtTable
//#define _PCD_SET_MODE_BOOL_AmiPcdInstallEsrtTable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
ReFlashEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );



#include "ReFlashStrDefs.h"


#ifdef __cplusplus
}
#endif

#endif
