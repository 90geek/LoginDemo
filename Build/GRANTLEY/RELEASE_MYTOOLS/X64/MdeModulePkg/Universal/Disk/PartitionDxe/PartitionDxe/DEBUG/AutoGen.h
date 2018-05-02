/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_1FA1F39E_FEFF_4aae_BD7B_38A070A3B609
#define _AUTOGENH_1FA1F39E_FEFF_4aae_BD7B_38A070A3B609

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Uefi.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x1FA1F39E, 0xFEFF, 0x4aae, {0xBD, 0x7B, 0x38, 0xA0, 0x70, 0xA3, 0xB6, 0x09}}

// Guids
extern EFI_GUID gEfiPartTypeUnusedGuid;
extern EFI_GUID gEfiPartTypeSystemPartGuid;
extern EFI_GUID gAmiIso9660MediaGuid;
extern EFI_GUID gAmiUdfMediaGuid;
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

// Protocols
extern EFI_GUID gEfiBlockIoProtocolGuid;
extern EFI_GUID gEfiBlockIo2ProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiDiskIoProtocolGuid;
extern EFI_GUID gEfiDiskIo2ProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
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
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdIso9660Support  162U
#define _PCD_SIZE_PcdIso9660Support 1
#define _PCD_GET_MODE_SIZE_PcdIso9660Support  _PCD_SIZE_PcdIso9660Support 
#define _PCD_VALUE_PcdIso9660Support  0U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdIso9660Support;
#define _PCD_GET_MODE_BOOL_PcdIso9660Support  _gPcd_FixedAtBuild_PcdIso9660Support
//#define _PCD_SET_MODE_BOOL_PcdIso9660Support  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUdfSupport  163U
#define _PCD_SIZE_PcdUdfSupport 1
#define _PCD_GET_MODE_SIZE_PcdUdfSupport  _PCD_SIZE_PcdUdfSupport 
#define _PCD_VALUE_PcdUdfSupport  0U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdUdfSupport;
#define _PCD_GET_MODE_BOOL_PcdUdfSupport  _gPcd_FixedAtBuild_PcdUdfSupport
//#define _PCD_SET_MODE_BOOL_PcdUdfSupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_AmiPcdNumberOfRetriesOnNoMedia  164U
#define _PCD_SIZE_AmiPcdNumberOfRetriesOnNoMedia 4
#define _PCD_GET_MODE_SIZE_AmiPcdNumberOfRetriesOnNoMedia  _PCD_SIZE_AmiPcdNumberOfRetriesOnNoMedia 
#define _PCD_VALUE_AmiPcdNumberOfRetriesOnNoMedia  1U
extern const  UINT32  _gPcd_FixedAtBuild_AmiPcdNumberOfRetriesOnNoMedia;
#define _PCD_GET_MODE_32_AmiPcdNumberOfRetriesOnNoMedia  _gPcd_FixedAtBuild_AmiPcdNumberOfRetriesOnNoMedia
//#define _PCD_SET_MODE_32_AmiPcdNumberOfRetriesOnNoMedia  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InitializePartition (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
