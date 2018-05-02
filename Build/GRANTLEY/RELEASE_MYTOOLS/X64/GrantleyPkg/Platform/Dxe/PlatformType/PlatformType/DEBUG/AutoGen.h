/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_2E6A521C_F697_402d_9774_98B2B7E140F3
#define _AUTOGENH_2E6A521C_F697_402d_9774_98B2B7E140F3

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x2E6A521C, 0xF697, 0x402d, {0x97, 0x74, 0x98, 0xB2, 0xB7, 0xE1, 0x40, 0xF3}}

// Guids
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiMfgUUIDHobGuid;
extern EFI_GUID gPlatformTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gAmiGlobalVariableGuid;
extern EFI_GUID gEfiHobListGuid;

// Protocols
extern EFI_GUID gEfiPlatformTypeProtocolGuid;
extern EFI_GUID gEfiVariableArchProtocolGuid;
extern EFI_GUID gEfiSpiProtocolGuid;
extern EFI_GUID gEfiCpuIoProtocolGuid;
extern EFI_GUID gEfiIioUdsProtocolGuid;
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

#define _PCD_TOKEN_PcdPostCompleteGpio  266U
#define _PCD_SIZE_PcdPostCompleteGpio 8
#define _PCD_GET_MODE_SIZE_PcdPostCompleteGpio  _PCD_SIZE_PcdPostCompleteGpio 
#define _PCD_VALUE_PcdPostCompleteGpio  32ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdPostCompleteGpio;
#define _PCD_GET_MODE_64_PcdPostCompleteGpio  _gPcd_FixedAtBuild_PcdPostCompleteGpio
//#define _PCD_SET_MODE_64_PcdPostCompleteGpio  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUartDefaultBaudRate  1U
#define _PCD_GET_MODE_64_PcdUartDefaultBaudRate  LibPcdGet64(_PCD_TOKEN_PcdUartDefaultBaudRate)
#define _PCD_GET_MODE_SIZE_PcdUartDefaultBaudRate  LibPcdGetSize(_PCD_TOKEN_PcdUartDefaultBaudRate)
#define _PCD_SET_MODE_64_PcdUartDefaultBaudRate(Value)  LibPcdSet64(_PCD_TOKEN_PcdUartDefaultBaudRate, (Value))
#define _PCD_SET_MODE_64_S_PcdUartDefaultBaudRate(Value)  LibPcdSet64S(_PCD_TOKEN_PcdUartDefaultBaudRate, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
PlatformTypeInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
