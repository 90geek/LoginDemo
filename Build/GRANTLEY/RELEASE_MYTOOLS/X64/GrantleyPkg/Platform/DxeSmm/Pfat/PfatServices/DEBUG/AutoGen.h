/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_6D4BAA0B_F431_4370_AF19_99D6209239F6
#define _AUTOGENH_6D4BAA0B_F431_4370_AF19_99D6209239F6

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x6D4BAA0B, 0xF431, 0x4370, {0xAF, 0x19, 0x99, 0xD6, 0x20, 0x92, 0x39, 0xF6}}

// Guids
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gPfatModuleGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gPlatformTokenSpaceGuid;
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
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gEfiDataHubStatusCodeRecordGuid;
extern EFI_GUID gEfiFileInfoGuid;

// Protocols
extern EFI_GUID gEfiGlobalNvsAreaProtocolGuid;
extern EFI_GUID gEfiSmmSpiProtocolGuid;
extern EFI_GUID gEfiSmmSwDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmCpuProtocolGuid;
extern EFI_GUID gEfiSmmFirmwareVolumeBlockProtocolGuid;
extern EFI_GUID gEfiSmmBase2ProtocolGuid;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gSmmPfatProtocolGuid;
extern EFI_GUID gEfiAcpiTableProtocolGuid;
extern EFI_GUID gEfiAcpiSupportProtocolGuid;
extern EFI_GUID gEfiSmmIoTrapDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmVariableProtocolGuid;
extern EFI_GUID gAmiSmmDebugServiceProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiSmmAccess2ProtocolGuid;
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
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiS3SmmSaveStateProtocolGuid;
extern EFI_GUID gEfiStatusCodeRuntimeProtocolGuid;
extern EFI_GUID gEfiDataHubProtocolGuid;
extern EFI_GUID gEfiLoadFileProtocolGuid;
extern EFI_GUID gEfiLoadFile2ProtocolGuid;
extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdMaxSizeNonPopulateCapsule  154U
#define _PCD_SIZE_PcdMaxSizeNonPopulateCapsule 4
#define _PCD_GET_MODE_SIZE_PcdMaxSizeNonPopulateCapsule  _PCD_SIZE_PcdMaxSizeNonPopulateCapsule 
#define _PCD_VALUE_PcdMaxSizeNonPopulateCapsule  0x900000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdMaxSizeNonPopulateCapsule;
#define _PCD_GET_MODE_32_PcdMaxSizeNonPopulateCapsule  _gPcd_FixedAtBuild_PcdMaxSizeNonPopulateCapsule
//#define _PCD_SET_MODE_32_PcdMaxSizeNonPopulateCapsule  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdFlashAreaBaseAddress  267U
#define _PCD_SIZE_PcdFlashAreaBaseAddress 4
#define _PCD_GET_MODE_SIZE_PcdFlashAreaBaseAddress  _PCD_SIZE_PcdFlashAreaBaseAddress 
#define _PCD_VALUE_PcdFlashAreaBaseAddress  0xFF800000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdFlashAreaBaseAddress;
#define _PCD_GET_MODE_32_PcdFlashAreaBaseAddress  _gPcd_FixedAtBuild_PcdFlashAreaBaseAddress
//#define _PCD_SET_MODE_32_PcdFlashAreaBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InstallPfatProtocol (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
