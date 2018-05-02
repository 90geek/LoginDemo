/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_274F0C8F_9E57_41d8_9966_29CCD48D31C2
#define _AUTOGENH_274F0C8F_9E57_41d8_9966_29CCD48D31C2

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x274F0C8F, 0x9E57, 0x41d8, {0x99, 0x66, 0x29, 0xCC, 0xD4, 0x8D, 0x31, 0xC2}}

// Guids
extern EFI_GUID gEfiSmmPeiSmramMemoryReserveGuid;
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

// Protocols
extern EFI_GUID gEfiPciRootBridgeIoProtocolGuid;
extern EFI_GUID gEfiIioUdsProtocolGuid;
extern EFI_GUID gEfiSmmAccess2ProtocolGuid;
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

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdCboDev  231U
#define _PCD_SIZE_PcdCboDev 4
#define _PCD_GET_MODE_SIZE_PcdCboDev  _PCD_SIZE_PcdCboDev 
#define _PCD_VALUE_PcdCboDev  0x0fU
extern const  UINT32  _gPcd_FixedAtBuild_PcdCboDev;
#define _PCD_GET_MODE_32_PcdCboDev  _gPcd_FixedAtBuild_PcdCboDev
//#define _PCD_SET_MODE_32_PcdCboDev  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCboFunc  232U
#define _PCD_SIZE_PcdCboFunc 1
#define _PCD_GET_MODE_SIZE_PcdCboFunc  _PCD_SIZE_PcdCboFunc 
#define _PCD_VALUE_PcdCboFunc  0x04U
extern const  UINT8  _gPcd_FixedAtBuild_PcdCboFunc;
#define _PCD_GET_MODE_8_PcdCboFunc  _gPcd_FixedAtBuild_PcdCboFunc
//#define _PCD_SET_MODE_8_PcdCboFunc  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdRUncoreCrSmram2  233U
#define _PCD_SIZE_PcdRUncoreCrSmram2 1
#define _PCD_GET_MODE_SIZE_PcdRUncoreCrSmram2  _PCD_SIZE_PcdRUncoreCrSmram2 
#define _PCD_VALUE_PcdRUncoreCrSmram2  0x4CU
extern const  UINT8  _gPcd_FixedAtBuild_PcdRUncoreCrSmram2;
#define _PCD_GET_MODE_8_PcdRUncoreCrSmram2  _gPcd_FixedAtBuild_PcdRUncoreCrSmram2
//#define _PCD_SET_MODE_8_PcdRUncoreCrSmram2  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
SmmAccessDriverEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
