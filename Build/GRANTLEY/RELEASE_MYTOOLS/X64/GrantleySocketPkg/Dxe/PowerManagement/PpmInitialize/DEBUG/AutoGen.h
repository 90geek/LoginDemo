/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_3FFCAE95_23CF_4967_94F5_16352F68E43B
#define _AUTOGENH_3FFCAE95_23CF_4967_94F5_16352F68E43B

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x3FFCAE95, 0x23CF, 0x4967, {0x94, 0xF5, 0x16, 0x35, 0x2F, 0x68, 0xE4, 0x3B}}

// Guids
extern EFI_GUID gEfiMemoryMapGuid;
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gEfiCpuTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiSerialPortTokenSpaceGuid;
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
extern EFI_GUID gEfiSetupVariableGuid;

// Protocols
extern EFI_GUID gEfiPciCallbackProtocolGuid;
extern EFI_GUID gEfiCpuCsrAccessGuid;
extern EFI_GUID gExitPmAuthProtocolGuid;
extern EFI_GUID gCompletePowerManagementProtocolGuid;
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
extern EFI_GUID gEfiS3SaveStateProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdCpuMaxLogicalProcessorNumber  138U
#define _PCD_SIZE_PcdCpuMaxLogicalProcessorNumber 4
#define _PCD_GET_MODE_SIZE_PcdCpuMaxLogicalProcessorNumber  _PCD_SIZE_PcdCpuMaxLogicalProcessorNumber 
#define _PCD_VALUE_PcdCpuMaxLogicalProcessorNumber  192U
extern const  UINT32  _gPcd_FixedAtBuild_PcdCpuMaxLogicalProcessorNumber;
#define _PCD_GET_MODE_32_PcdCpuMaxLogicalProcessorNumber  _gPcd_FixedAtBuild_PcdCpuMaxLogicalProcessorNumber
//#define _PCD_SET_MODE_32_PcdCpuMaxLogicalProcessorNumber  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuProcessorFeatureCapability  33U
#define _PCD_GET_MODE_32_PcdCpuProcessorFeatureCapability  LibPcdGet32(_PCD_TOKEN_PcdCpuProcessorFeatureCapability)
#define _PCD_GET_MODE_SIZE_PcdCpuProcessorFeatureCapability  LibPcdGetSize(_PCD_TOKEN_PcdCpuProcessorFeatureCapability)
#define _PCD_SET_MODE_32_PcdCpuProcessorFeatureCapability(Value)  LibPcdSet32(_PCD_TOKEN_PcdCpuProcessorFeatureCapability, (Value))
#define _PCD_SET_MODE_32_S_PcdCpuProcessorFeatureCapability(Value)  LibPcdSet32S(_PCD_TOKEN_PcdCpuProcessorFeatureCapability, (Value))

#define _PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration  34U
#define _PCD_GET_MODE_32_PcdCpuProcessorFeatureUserConfiguration  LibPcdGet32(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration)
#define _PCD_GET_MODE_SIZE_PcdCpuProcessorFeatureUserConfiguration  LibPcdGetSize(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration)
#define _PCD_SET_MODE_32_PcdCpuProcessorFeatureUserConfiguration(Value)  LibPcdSet32(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration, (Value))
#define _PCD_SET_MODE_32_S_PcdCpuProcessorFeatureUserConfiguration(Value)  LibPcdSet32S(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration, (Value))

#define _PCD_TOKEN_PcdCpuPmStructAddr  56U
#define _PCD_GET_MODE_64_PcdCpuPmStructAddr  LibPcdGet64(_PCD_TOKEN_PcdCpuPmStructAddr)
#define _PCD_GET_MODE_SIZE_PcdCpuPmStructAddr  LibPcdGetSize(_PCD_TOKEN_PcdCpuPmStructAddr)
#define _PCD_SET_MODE_64_PcdCpuPmStructAddr(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuPmStructAddr, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuPmStructAddr(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuPmStructAddr, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
PpmInitializeEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
