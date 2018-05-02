/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_FF917E22_A228_448d_BDAA_68EFCCDDA5D3
#define _AUTOGENH_FF917E22_A228_448d_BDAA_68EFCCDDA5D3

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xFF917E22, 0xA228, 0x448d, {0xBD, 0xAA, 0x68, 0xEF, 0xCC, 0xDD, 0xA5, 0xD3}}

// Guids
extern EFI_GUID gEfiPlatformTxtDeviceMemoryGuid;
extern EFI_GUID gEfiPlatformTxtPolicyDataGuid;
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiEndOfDxeEventGroupGuid;
extern EFI_GUID gServerCommonTokenSpaceGuid;
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
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gUefiCpuPkgTokenSpaceGuid;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiGenericVariableGuid;
extern EFI_GUID gEfiPlatformInfoGuid;

// Protocols
extern EFI_GUID gEfiPciRootBridgeIoProtocolGuid;
extern EFI_GUID gEfiMpServiceProtocolGuid;
extern EFI_GUID gEfiLegacyRegion2ProtocolGuid;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gEfiLegacyBiosProtocolGuid;
extern EFI_GUID gEfiCpuIoProtocolGuid;
extern EFI_GUID gEfiPciEnumerationCompleteProtocolGuid;
extern EFI_GUID gEfiIioSystemProtocolGuid;
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
extern EFI_GUID gEfiS3SaveStateProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiSpiProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdSocketBaseBusNumbers  84U
#define _PCD_GET_MODE_PTR_PcdSocketBaseBusNumbers  LibPcdGetPtr(_PCD_TOKEN_PcdSocketBaseBusNumbers)
#define _PCD_GET_MODE_SIZE_PcdSocketBaseBusNumbers  LibPcdGetSize(_PCD_TOKEN_PcdSocketBaseBusNumbers)
#define _PCD_SET_MODE_PTR_PcdSocketBaseBusNumbers(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSocketBaseBusNumbers, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSocketBaseBusNumbers(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSocketBaseBusNumbers, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress  _PCD_SIZE_PcdPciExpressBaseAddress 
#define _PCD_VALUE_PcdPciExpressBaseAddress  0x80000000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdMaxCpuSocketCount  144U
#define _PCD_SIZE_PcdMaxCpuSocketCount 4
#define _PCD_GET_MODE_SIZE_PcdMaxCpuSocketCount  _PCD_SIZE_PcdMaxCpuSocketCount 
#define _PCD_VALUE_PcdMaxCpuSocketCount  ((UINT32)0x04U)
extern const  UINT32  _gPcd_FixedAtBuild_PcdMaxCpuSocketCount;
#define _PCD_GET_MODE_32_PcdMaxCpuSocketCount  _gPcd_FixedAtBuild_PcdMaxCpuSocketCount
//#define _PCD_SET_MODE_32_PcdMaxCpuSocketCount  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
DriverEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
