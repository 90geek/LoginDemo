/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_62D171CB_78CD_4480_8678_C6A2A797A8DE
#define _AUTOGENH_62D171CB_78CD_4480_8678_C6A2A797A8DE

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x62D171CB, 0x78CD, 0x4480, {0x86, 0x78, 0xC6, 0xA2, 0xA7, 0x97, 0xA8, 0xDE}}

// Guids
extern EFI_GUID gEfiCpuTokenSpaceGuid;
extern EFI_GUID gUefiCpuPkgTokenSpaceGuid;
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
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

// Protocols
extern EFI_GUID gEfiMpServiceProtocolGuid;
extern EFI_GUID gEfiCpuArchProtocolGuid;
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
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiStatusCodeRuntimeProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdCpuPageTableAddress  41U
#define _PCD_GET_MODE_64_PcdCpuPageTableAddress  LibPcdGet64(_PCD_TOKEN_PcdCpuPageTableAddress)
#define _PCD_GET_MODE_SIZE_PcdCpuPageTableAddress  LibPcdGetSize(_PCD_TOKEN_PcdCpuPageTableAddress)
#define _PCD_SET_MODE_64_PcdCpuPageTableAddress(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuPageTableAddress, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuPageTableAddress(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuPageTableAddress, (Value))

#define _PCD_TOKEN_PcdCpuMtrrTableAddress  42U
#define _PCD_GET_MODE_64_PcdCpuMtrrTableAddress  LibPcdGet64(_PCD_TOKEN_PcdCpuMtrrTableAddress)
#define _PCD_GET_MODE_SIZE_PcdCpuMtrrTableAddress  LibPcdGetSize(_PCD_TOKEN_PcdCpuMtrrTableAddress)
#define _PCD_SET_MODE_64_PcdCpuMtrrTableAddress(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuMtrrTableAddress, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuMtrrTableAddress(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuMtrrTableAddress, (Value))

#define _PCD_TOKEN_PcdCpuLocalApicBaseAddress  170U
#define _PCD_SIZE_PcdCpuLocalApicBaseAddress 4
#define _PCD_GET_MODE_SIZE_PcdCpuLocalApicBaseAddress  _PCD_SIZE_PcdCpuLocalApicBaseAddress 
#define _PCD_VALUE_PcdCpuLocalApicBaseAddress  0xfee00000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdCpuLocalApicBaseAddress;
#define _PCD_GET_MODE_32_PcdCpuLocalApicBaseAddress  _gPcd_FixedAtBuild_PcdCpuLocalApicBaseAddress
//#define _PCD_SET_MODE_32_PcdCpuLocalApicBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InitializeCpu (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
