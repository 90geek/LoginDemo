/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_8F2C127E_117D_484B_8A44_FBD911BE125E
#define _AUTOGENH_8F2C127E_117D_484B_8A44_FBD911BE125E

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x8F2C127E, 0x117D, 0x484B, {0x8A, 0x44, 0xFB, 0xD9, 0x11, 0xBE, 0x12, 0x5E}}

// Guids
extern EFI_GUID gEfiEventVirtualAddressChangeGuid;
extern EFI_GUID gAmiIpmiPkgTokenSpaceGuid;
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
extern EFI_GUID gEfiEventExitBootServicesGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiDxeIpmiTransportProtocolGuid;
extern EFI_GUID gEfiSmbiosProtocolGuid;
extern EFI_GUID gEfiRedirFruProtocolGuid;
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

// Definition of PCDs used in this module

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

#define _PCD_TOKEN_PcdSystemUuid  63U
#define _PCD_GET_MODE_PTR_PcdSystemUuid  LibPcdGetPtr(_PCD_TOKEN_PcdSystemUuid)
#define _PCD_GET_MODE_SIZE_PcdSystemUuid  LibPcdGetSize(_PCD_TOKEN_PcdSystemUuid)
#define _PCD_SET_MODE_PTR_PcdSystemUuid(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSystemUuid, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSystemUuid(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSystemUuid, (SizeOfBuffer), (Buffer))

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

#define _PCD_TOKEN_PcdBaseBoardAssetTag  14U
#define _PCD_GET_MODE_PTR_PcdBaseBoardAssetTag  LibPcdGetPtr(_PCD_TOKEN_PcdBaseBoardAssetTag)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardAssetTag  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardAssetTag)
#define _PCD_SET_MODE_PTR_PcdBaseBoardAssetTag(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdBaseBoardAssetTag, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdBaseBoardAssetTag(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdBaseBoardAssetTag, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdBaseBoardFeatureFlag  64U
#define _PCD_GET_MODE_8_PcdBaseBoardFeatureFlag  LibPcdGet8(_PCD_TOKEN_PcdBaseBoardFeatureFlag)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardFeatureFlag  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardFeatureFlag)
#define _PCD_SET_MODE_8_PcdBaseBoardFeatureFlag(Value)  LibPcdSet8(_PCD_TOKEN_PcdBaseBoardFeatureFlag, (Value))
#define _PCD_SET_MODE_8_S_PcdBaseBoardFeatureFlag(Value)  LibPcdSet8S(_PCD_TOKEN_PcdBaseBoardFeatureFlag, (Value))

#define _PCD_TOKEN_PcdBaseBoardChassisLocation  15U
#define _PCD_GET_MODE_PTR_PcdBaseBoardChassisLocation  LibPcdGetPtr(_PCD_TOKEN_PcdBaseBoardChassisLocation)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardChassisLocation  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardChassisLocation)
#define _PCD_SET_MODE_PTR_PcdBaseBoardChassisLocation(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdBaseBoardChassisLocation, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdBaseBoardChassisLocation(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdBaseBoardChassisLocation, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdBaseBoardType  65U
#define _PCD_GET_MODE_8_PcdBaseBoardType  LibPcdGet8(_PCD_TOKEN_PcdBaseBoardType)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardType  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardType)
#define _PCD_SET_MODE_8_PcdBaseBoardType(Value)  LibPcdSet8(_PCD_TOKEN_PcdBaseBoardType, (Value))
#define _PCD_SET_MODE_8_S_PcdBaseBoardType(Value)  LibPcdSet8S(_PCD_TOKEN_PcdBaseBoardType, (Value))

#define _PCD_TOKEN_PcdBaseBoardChassisLink  16U
#define _PCD_GET_MODE_PTR_PcdBaseBoardChassisLink  LibPcdGetPtr(_PCD_TOKEN_PcdBaseBoardChassisLink)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardChassisLink  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardChassisLink)
#define _PCD_SET_MODE_PTR_PcdBaseBoardChassisLink(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdBaseBoardChassisLink, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdBaseBoardChassisLink(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdBaseBoardChassisLink, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdBaseBoardNumberLinks  17U
#define _PCD_GET_MODE_PTR_PcdBaseBoardNumberLinks  LibPcdGetPtr(_PCD_TOKEN_PcdBaseBoardNumberLinks)
#define _PCD_GET_MODE_SIZE_PcdBaseBoardNumberLinks  LibPcdGetSize(_PCD_TOKEN_PcdBaseBoardNumberLinks)
#define _PCD_SET_MODE_PTR_PcdBaseBoardNumberLinks(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdBaseBoardNumberLinks, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdBaseBoardNumberLinks(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdBaseBoardNumberLinks, (SizeOfBuffer), (Buffer))

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

#define _PCD_TOKEN_PcdChassisAssetTag  21U
#define _PCD_GET_MODE_PTR_PcdChassisAssetTag  LibPcdGetPtr(_PCD_TOKEN_PcdChassisAssetTag)
#define _PCD_GET_MODE_SIZE_PcdChassisAssetTag  LibPcdGetSize(_PCD_TOKEN_PcdChassisAssetTag)
#define _PCD_SET_MODE_PTR_PcdChassisAssetTag(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdChassisAssetTag, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdChassisAssetTag(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdChassisAssetTag, (SizeOfBuffer), (Buffer))

#define _PCD_TOKEN_PcdChassisType  66U
#define _PCD_GET_MODE_8_PcdChassisType  LibPcdGet8(_PCD_TOKEN_PcdChassisType)
#define _PCD_GET_MODE_SIZE_PcdChassisType  LibPcdGetSize(_PCD_TOKEN_PcdChassisType)
#define _PCD_SET_MODE_8_PcdChassisType(Value)  LibPcdSet8(_PCD_TOKEN_PcdChassisType, (Value))
#define _PCD_SET_MODE_8_S_PcdChassisType(Value)  LibPcdSet8S(_PCD_TOKEN_PcdChassisType, (Value))

#define _PCD_TOKEN_PcdChassisBootupState  67U
#define _PCD_GET_MODE_8_PcdChassisBootupState  LibPcdGet8(_PCD_TOKEN_PcdChassisBootupState)
#define _PCD_GET_MODE_SIZE_PcdChassisBootupState  LibPcdGetSize(_PCD_TOKEN_PcdChassisBootupState)
#define _PCD_SET_MODE_8_PcdChassisBootupState(Value)  LibPcdSet8(_PCD_TOKEN_PcdChassisBootupState, (Value))
#define _PCD_SET_MODE_8_S_PcdChassisBootupState(Value)  LibPcdSet8S(_PCD_TOKEN_PcdChassisBootupState, (Value))

#define _PCD_TOKEN_PcdChassisPowerSupplyState  68U
#define _PCD_GET_MODE_8_PcdChassisPowerSupplyState  LibPcdGet8(_PCD_TOKEN_PcdChassisPowerSupplyState)
#define _PCD_GET_MODE_SIZE_PcdChassisPowerSupplyState  LibPcdGetSize(_PCD_TOKEN_PcdChassisPowerSupplyState)
#define _PCD_SET_MODE_8_PcdChassisPowerSupplyState(Value)  LibPcdSet8(_PCD_TOKEN_PcdChassisPowerSupplyState, (Value))
#define _PCD_SET_MODE_8_S_PcdChassisPowerSupplyState(Value)  LibPcdSet8S(_PCD_TOKEN_PcdChassisPowerSupplyState, (Value))

#define _PCD_TOKEN_PcdChassisThermalState  69U
#define _PCD_GET_MODE_8_PcdChassisThermalState  LibPcdGet8(_PCD_TOKEN_PcdChassisThermalState)
#define _PCD_GET_MODE_SIZE_PcdChassisThermalState  LibPcdGetSize(_PCD_TOKEN_PcdChassisThermalState)
#define _PCD_SET_MODE_8_PcdChassisThermalState(Value)  LibPcdSet8(_PCD_TOKEN_PcdChassisThermalState, (Value))
#define _PCD_SET_MODE_8_S_PcdChassisThermalState(Value)  LibPcdSet8S(_PCD_TOKEN_PcdChassisThermalState, (Value))

#define _PCD_TOKEN_PcdChassisSecurityState  70U
#define _PCD_GET_MODE_8_PcdChassisSecurityState  LibPcdGet8(_PCD_TOKEN_PcdChassisSecurityState)
#define _PCD_GET_MODE_SIZE_PcdChassisSecurityState  LibPcdGetSize(_PCD_TOKEN_PcdChassisSecurityState)
#define _PCD_SET_MODE_8_PcdChassisSecurityState(Value)  LibPcdSet8(_PCD_TOKEN_PcdChassisSecurityState, (Value))
#define _PCD_SET_MODE_8_S_PcdChassisSecurityState(Value)  LibPcdSet8S(_PCD_TOKEN_PcdChassisSecurityState, (Value))

#define _PCD_TOKEN_PcdChassisOemDefined  71U
#define _PCD_GET_MODE_32_PcdChassisOemDefined  LibPcdGet32(_PCD_TOKEN_PcdChassisOemDefined)
#define _PCD_GET_MODE_SIZE_PcdChassisOemDefined  LibPcdGetSize(_PCD_TOKEN_PcdChassisOemDefined)
#define _PCD_SET_MODE_32_PcdChassisOemDefined(Value)  LibPcdSet32(_PCD_TOKEN_PcdChassisOemDefined, (Value))
#define _PCD_SET_MODE_32_S_PcdChassisOemDefined(Value)  LibPcdSet32S(_PCD_TOKEN_PcdChassisOemDefined, (Value))

#define _PCD_TOKEN_PcdChassisHeight  72U
#define _PCD_GET_MODE_8_PcdChassisHeight  LibPcdGet8(_PCD_TOKEN_PcdChassisHeight)
#define _PCD_GET_MODE_SIZE_PcdChassisHeight  LibPcdGetSize(_PCD_TOKEN_PcdChassisHeight)
#define _PCD_SET_MODE_8_PcdChassisHeight(Value)  LibPcdSet8(_PCD_TOKEN_PcdChassisHeight, (Value))
#define _PCD_SET_MODE_8_S_PcdChassisHeight(Value)  LibPcdSet8S(_PCD_TOKEN_PcdChassisHeight, (Value))

#define _PCD_TOKEN_PcdChassisElementRecordLength  73U
#define _PCD_GET_MODE_8_PcdChassisElementRecordLength  LibPcdGet8(_PCD_TOKEN_PcdChassisElementRecordLength)
#define _PCD_GET_MODE_SIZE_PcdChassisElementRecordLength  LibPcdGetSize(_PCD_TOKEN_PcdChassisElementRecordLength)
#define _PCD_SET_MODE_8_PcdChassisElementRecordLength(Value)  LibPcdSet8(_PCD_TOKEN_PcdChassisElementRecordLength, (Value))
#define _PCD_SET_MODE_8_S_PcdChassisElementRecordLength(Value)  LibPcdSet8S(_PCD_TOKEN_PcdChassisElementRecordLength, (Value))

#define _PCD_TOKEN_PcdChassisElementCount  74U
#define _PCD_GET_MODE_8_PcdChassisElementCount  LibPcdGet8(_PCD_TOKEN_PcdChassisElementCount)
#define _PCD_GET_MODE_SIZE_PcdChassisElementCount  LibPcdGetSize(_PCD_TOKEN_PcdChassisElementCount)
#define _PCD_SET_MODE_8_PcdChassisElementCount(Value)  LibPcdSet8(_PCD_TOKEN_PcdChassisElementCount, (Value))
#define _PCD_SET_MODE_8_S_PcdChassisElementCount(Value)  LibPcdSet8S(_PCD_TOKEN_PcdChassisElementCount, (Value))

#define _PCD_TOKEN_PcdChassisElements  22U
#define _PCD_GET_MODE_PTR_PcdChassisElements  LibPcdGetPtr(_PCD_TOKEN_PcdChassisElements)
#define _PCD_GET_MODE_SIZE_PcdChassisElements  LibPcdGetSize(_PCD_TOKEN_PcdChassisElements)
#define _PCD_SET_MODE_PTR_PcdChassisElements(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdChassisElements, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdChassisElements(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdChassisElements, (SizeOfBuffer), (Buffer))

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

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InitializeSmRedirFruLayer (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
