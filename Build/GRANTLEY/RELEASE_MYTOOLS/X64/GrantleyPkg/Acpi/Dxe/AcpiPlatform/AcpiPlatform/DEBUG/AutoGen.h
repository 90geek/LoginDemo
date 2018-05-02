/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_87AB821C_79B8_4ef6_A913_21D22063F55F
#define _AUTOGENH_87AB821C_79B8_4ef6_A913_21D22063F55F

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x87AB821C, 0x79B8, 0x4ef6, {0xA9, 0x13, 0x21, 0xD2, 0x20, 0x63, 0xF5, 0x5F}}

// Guids
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gEfiAcpiTableStorageGuid;
extern EFI_GUID gEfiMemoryMapGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiAcpiHwpStorageGuid;
extern EFI_GUID gPlatformTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiCpuTokenSpaceGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

// Protocols
extern EFI_GUID gEfiMpServiceProtocolGuid;
extern EFI_GUID gEfiIioUdsProtocolGuid;
extern EFI_GUID gEfiGlobalNvsAreaProtocolGuid;
extern EFI_GUID gEfiPciIoProtocolGuid;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gEfiAcpiSupportProtocolGuid;
extern EFI_GUID gEfiSerialIoProtocolGuid;
extern EFI_GUID gDxeEnhancedSpeedstepProtocolGuid;
extern EFI_GUID gEfiPlatformTypeProtocolGuid;
extern EFI_GUID gEfiDmaRemapProtocolGuid;
extern EFI_GUID gEfiMpstSupportProtocolGuid;
extern EFI_GUID gEfiCpuCsrAccessGuid;
extern EFI_GUID gEfiSmbiosProtocolGuid;
extern EFI_GUID gEfiIioSystemProtocolGuid;
extern EFI_GUID gEfiPciRootBridgeIoProtocolGuid;
extern EFI_GUID gEfiAcpiTableProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
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
extern EFI_GUID gEfiS3SaveStateProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdAcpiOemId  246U
#define _PCD_SIZE_PcdAcpiOemId 8
#define _PCD_GET_MODE_SIZE_PcdAcpiOemId  _PCD_SIZE_PcdAcpiOemId 
#define _PCD_VALUE_PcdAcpiOemId  0x0000204C45544E49ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdAcpiOemId;
#define _PCD_GET_MODE_64_PcdAcpiOemId  _gPcd_FixedAtBuild_PcdAcpiOemId
//#define _PCD_SET_MODE_64_PcdAcpiOemId  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdAcpiTableOemId  247U
#define _PCD_SIZE_PcdAcpiTableOemId 8
#define _PCD_GET_MODE_SIZE_PcdAcpiTableOemId  _PCD_SIZE_PcdAcpiTableOemId 
#define _PCD_VALUE_PcdAcpiTableOemId  0x4449204C45544E49ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdAcpiTableOemId;
#define _PCD_GET_MODE_64_PcdAcpiTableOemId  _gPcd_FixedAtBuild_PcdAcpiTableOemId
//#define _PCD_SET_MODE_64_PcdAcpiTableOemId  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
AcpiPlatformEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
