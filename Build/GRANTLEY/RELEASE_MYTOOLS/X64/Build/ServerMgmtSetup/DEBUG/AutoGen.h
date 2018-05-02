/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_1B08A1DB_F91A_4fa1_A911_255C417F1CF7
#define _AUTOGENH_1B08A1DB_F91A_4fa1_A911_255C417F1CF7

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x1B08A1DB, 0xF91A, 0x4fa1, {0xA9, 0x11, 0x25, 0x5C, 0x41, 0x7F, 0x1C, 0xF7}}

// Guids
extern EFI_GUID gEfiServerMgmtSetupVariableGuid;
extern EFI_GUID gAmiIpmiPkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
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

// Protocols
extern EFI_GUID gEfiBmcSelfTestLogProtocolGuid;
extern EFI_GUID gEfiDxeIpmiTransportProtocolGuid;
extern EFI_GUID gAmiPostManagerProtocolGuid;
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
extern EFI_GUID gEfiHiiStringProtocolGuid;
extern EFI_GUID gEfiHiiImageProtocolGuid;
extern EFI_GUID gEfiHiiDatabaseProtocolGuid;
extern EFI_GUID gEfiHiiConfigRoutingProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiFormBrowser2ProtocolGuid;
extern EFI_GUID gEfiDxeIpmiUsbTransportProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdStrMfg  243U
#define _PCD_VALUE_PcdStrMfg  _gPcd_FixedAtBuild_PcdStrMfg
extern const UINT16 _gPcd_FixedAtBuild_PcdStrMfg[6];
#define _PCD_GET_MODE_PTR_PcdStrMfg  _gPcd_FixedAtBuild_PcdStrMfg
#define _PCD_SIZE_PcdStrMfg 12
#define _PCD_GET_MODE_SIZE_PcdStrMfg  _PCD_SIZE_PcdStrMfg 
//#define _PCD_SET_MODE_PTR_PcdStrMfg  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdStrProduct  244U
#define _PCD_VALUE_PcdStrProduct  _gPcd_FixedAtBuild_PcdStrProduct
extern const UINT16 _gPcd_FixedAtBuild_PcdStrProduct[7];
#define _PCD_GET_MODE_PTR_PcdStrProduct  _gPcd_FixedAtBuild_PcdStrProduct
#define _PCD_SIZE_PcdStrProduct 14
#define _PCD_GET_MODE_SIZE_PcdStrProduct  _PCD_SIZE_PcdStrProduct 
//#define _PCD_SET_MODE_PTR_PcdStrProduct  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdSystemManufacturer  6U
#define _PCD_GET_MODE_PTR_PcdSystemManufacturer  LibPcdGetPtr(_PCD_TOKEN_PcdSystemManufacturer)
#define _PCD_GET_MODE_SIZE_PcdSystemManufacturer  LibPcdGetSize(_PCD_TOKEN_PcdSystemManufacturer)
#define _PCD_SET_MODE_PTR_PcdSystemManufacturer(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSystemManufacturer, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSystemManufacturer(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSystemManufacturer, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdSystemProductName  7U
#define _PCD_GET_MODE_PTR_PcdSystemProductName  LibPcdGetPtr(_PCD_TOKEN_PcdSystemProductName)
#define _PCD_GET_MODE_SIZE_PcdSystemProductName  LibPcdGetSize(_PCD_TOKEN_PcdSystemProductName)
#define _PCD_SET_MODE_PTR_PcdSystemProductName(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSystemProductName, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSystemProductName(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSystemProductName, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdSystemVersion  8U
#define _PCD_GET_MODE_PTR_PcdSystemVersion  LibPcdGetPtr(_PCD_TOKEN_PcdSystemVersion)
#define _PCD_GET_MODE_SIZE_PcdSystemVersion  LibPcdGetSize(_PCD_TOKEN_PcdSystemVersion)
#define _PCD_SET_MODE_PTR_PcdSystemVersion(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSystemVersion, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSystemVersion(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSystemVersion, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdSystemSerialNumber  9U
#define _PCD_GET_MODE_PTR_PcdSystemSerialNumber  LibPcdGetPtr(_PCD_TOKEN_PcdSystemSerialNumber)
#define _PCD_GET_MODE_SIZE_PcdSystemSerialNumber  LibPcdGetSize(_PCD_TOKEN_PcdSystemSerialNumber)
#define _PCD_SET_MODE_PTR_PcdSystemSerialNumber(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSystemSerialNumber, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSystemSerialNumber(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSystemSerialNumber, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdBaseBoardManufacturer  10U
#define _PCD_GET_MODE_PTR_PcdBaseBoardManufacturer  LibPcdGetPtr(_PCD_TOKEN_PcdBaseBoardManufacturer)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardManufacturer  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardManufacturer)
#define _PCD_SET_MODE_PTR_PcdBaseBoardManufacturer(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdBaseBoardManufacturer, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdBaseBoardManufacturer(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdBaseBoardManufacturer, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdBaseBoardProductName  11U
#define _PCD_GET_MODE_PTR_PcdBaseBoardProductName  LibPcdGetPtr(_PCD_TOKEN_PcdBaseBoardProductName)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardProductName  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardProductName)
#define _PCD_SET_MODE_PTR_PcdBaseBoardProductName(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdBaseBoardProductName, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdBaseBoardProductName(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdBaseBoardProductName, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdBaseBoardVersion  12U
#define _PCD_GET_MODE_PTR_PcdBaseBoardVersion  LibPcdGetPtr(_PCD_TOKEN_PcdBaseBoardVersion)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardVersion  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardVersion)
#define _PCD_SET_MODE_PTR_PcdBaseBoardVersion(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdBaseBoardVersion, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdBaseBoardVersion(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdBaseBoardVersion, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdBaseBoardSerialNumber  13U
#define _PCD_GET_MODE_PTR_PcdBaseBoardSerialNumber  LibPcdGetPtr(_PCD_TOKEN_PcdBaseBoardSerialNumber)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardSerialNumber  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardSerialNumber)
#define _PCD_SET_MODE_PTR_PcdBaseBoardSerialNumber(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdBaseBoardSerialNumber, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdBaseBoardSerialNumber(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdBaseBoardSerialNumber, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdChassisManufacturer  18U
#define _PCD_GET_MODE_PTR_PcdChassisManufacturer  LibPcdGetPtr(_PCD_TOKEN_PcdChassisManufacturer)
#define _PCD_GET_MODE_SIZE_PcdChassisManufacturer  LibPcdGetSize(_PCD_TOKEN_PcdChassisManufacturer)
#define _PCD_SET_MODE_PTR_PcdChassisManufacturer(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdChassisManufacturer, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdChassisManufacturer(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdChassisManufacturer, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdChassisVersion  19U
#define _PCD_GET_MODE_PTR_PcdChassisVersion  LibPcdGetPtr(_PCD_TOKEN_PcdChassisVersion)
#define _PCD_GET_MODE_SIZE_PcdChassisVersion  LibPcdGetSize(_PCD_TOKEN_PcdChassisVersion)
#define _PCD_SET_MODE_PTR_PcdChassisVersion(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdChassisVersion, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdChassisVersion(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdChassisVersion, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdChassisSerialNumber  20U
#define _PCD_GET_MODE_PTR_PcdChassisSerialNumber  LibPcdGetPtr(_PCD_TOKEN_PcdChassisSerialNumber)
#define _PCD_GET_MODE_SIZE_PcdChassisSerialNumber  LibPcdGetSize(_PCD_TOKEN_PcdChassisSerialNumber)
#define _PCD_SET_MODE_PTR_PcdChassisSerialNumber(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdChassisSerialNumber, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdChassisSerialNumber(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdChassisSerialNumber, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdSdrVersionNo  23U
#define _PCD_GET_MODE_PTR_PcdSdrVersionNo  LibPcdGetPtr(_PCD_TOKEN_PcdSdrVersionNo)
#define _PCD_GET_MODE_SIZE_PcdSdrVersionNo  LibPcdGetSize(_PCD_TOKEN_PcdSdrVersionNo)
#define _PCD_SET_MODE_PTR_PcdSdrVersionNo(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSdrVersionNo, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSdrVersionNo(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSdrVersionNo, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdSystemUuid  63U
#define _PCD_GET_MODE_PTR_PcdSystemUuid  LibPcdGetPtr(_PCD_TOKEN_PcdSystemUuid)
#define _PCD_GET_MODE_SIZE_PcdSystemUuid  LibPcdGetSize(_PCD_TOKEN_PcdSystemUuid)
#define _PCD_SET_MODE_PTR_PcdSystemUuid(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSystemUuid, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSystemUuid(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSystemUuid, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdChassisAssetTag  21U
#define _PCD_GET_MODE_PTR_PcdChassisAssetTag  LibPcdGetPtr(_PCD_TOKEN_PcdChassisAssetTag)
#define _PCD_GET_MODE_SIZE_PcdChassisAssetTag  LibPcdGetSize(_PCD_TOKEN_PcdChassisAssetTag)
#define _PCD_SET_MODE_PTR_PcdChassisAssetTag(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdChassisAssetTag, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdChassisAssetTag(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdChassisAssetTag, (SizeOfBuffer), (Buffer))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InstallServerMgmtSetupScreen (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );



#include "ServerMgmtSetupStrDefs.h"


#ifdef __cplusplus
}
#endif

#endif
