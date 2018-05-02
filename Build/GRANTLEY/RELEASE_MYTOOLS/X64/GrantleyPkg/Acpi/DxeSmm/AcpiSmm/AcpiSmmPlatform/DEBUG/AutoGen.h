/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_F5AC7057_5650_466e_B692_76A47223EFB0
#define _AUTOGENH_F5AC7057_5650_466e_B692_76A47223EFB0

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xF5AC7057, 0x5650, 0x466e, {0xB6, 0x92, 0x76, 0xA4, 0x72, 0x23, 0xEF, 0xB0}}

// Guids
extern EFI_GUID gEfiAcpiVariableCompatiblityGuid;
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiSmmPeiSmramMemoryReserveGuid;
extern EFI_GUID gPchS3CodeInLockBoxGuid;
extern EFI_GUID gPchS3ContextInLockBoxGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiIntelFrameworkModulePkgTokenSpaceGuid;
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
extern EFI_GUID gEfiSmmLockBoxCommunicationGuid;

// Protocols
extern EFI_GUID gEfiSmmSxDispatch2ProtocolGuid;
extern EFI_GUID gEfiPciRootBridgeIoProtocolGuid;
extern EFI_GUID gEfiVariableArchProtocolGuid;
extern EFI_GUID gEfiVariableWriteArchProtocolGuid;
extern EFI_GUID gEfiGlobalNvsAreaProtocolGuid;
extern EFI_GUID gEfiIioUdsProtocolGuid;
extern EFI_GUID gEfiSmmSwDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmSpiProtocolGuid;
extern EFI_GUID gEfiCpuIoProtocolGuid;
extern EFI_GUID gEfiPlatformTypeProtocolGuid;
extern EFI_GUID gEfiSmmBase2ProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiSmmDebugServiceProtocolGuid;
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

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdProgressCodeS3SuspendStart  240U
#define _PCD_SIZE_PcdProgressCodeS3SuspendStart 4
#define _PCD_GET_MODE_SIZE_PcdProgressCodeS3SuspendStart  _PCD_SIZE_PcdProgressCodeS3SuspendStart 
#define _PCD_VALUE_PcdProgressCodeS3SuspendStart  0x03078000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdProgressCodeS3SuspendStart;
#define _PCD_GET_MODE_32_PcdProgressCodeS3SuspendStart  _gPcd_FixedAtBuild_PcdProgressCodeS3SuspendStart
//#define _PCD_SET_MODE_32_PcdProgressCodeS3SuspendStart  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdS3AcpiReservedMemorySize  248U
#define _PCD_SIZE_PcdS3AcpiReservedMemorySize 4
#define _PCD_GET_MODE_SIZE_PcdS3AcpiReservedMemorySize  _PCD_SIZE_PcdS3AcpiReservedMemorySize 
#define _PCD_VALUE_PcdS3AcpiReservedMemorySize  0xC0000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdS3AcpiReservedMemorySize;
#define _PCD_GET_MODE_32_PcdS3AcpiReservedMemorySize  _gPcd_FixedAtBuild_PcdS3AcpiReservedMemorySize
//#define _PCD_SET_MODE_32_PcdS3AcpiReservedMemorySize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress  _PCD_SIZE_PcdPciExpressBaseAddress 
#define _PCD_VALUE_PcdPciExpressBaseAddress  0x80000000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InitAcpiSmmPlatform (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
