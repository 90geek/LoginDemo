/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_A3FF0EF5_0C28_42f5_B544_8C7DE1E80014
#define _AUTOGENH_A3FF0EF5_0C28_42f5_B544_8C7DE1E80014

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xA3FF0EF5, 0x0C28, 0x42f5, {0xB5, 0x44, 0x8C, 0x7D, 0xE1, 0xE8, 0x00, 0x14}}

// Guids
extern EFI_GUID gEfiAcpiVariableGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gEfiAcpi20TableGuid;
extern EFI_GUID gEfiAcpi10TableGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiCpuTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiSerialPortTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gUefiCpuPkgTokenSpaceGuid;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;

// Protocols
extern EFI_GUID gEfiSmmAccess2ProtocolGuid;
extern EFI_GUID gEfiMpServiceProtocolGuid;
extern EFI_GUID gEfiSmmConfigurationProtocolGuid;
extern EFI_GUID gEfiSmmCpuProtocolGuid;
extern EFI_GUID gEfiSmmReadyToLockProtocolGuid;
extern EFI_GUID gSmmCpuSyncProtocolGuid;
extern EFI_GUID gSmmCpuSync2ProtocolGuid;
extern EFI_GUID gEfiSmmCpuServiceProtocolGuid;
extern EFI_GUID gEfiSmmCpuSaveStateProtocolGuid;
extern EFI_GUID gEfiSmmBase2ProtocolGuid;
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
extern EFI_GUID gEfiSmmStatusCodeProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdFrameworkCompatibilitySupport  119U
#define _PCD_SIZE_PcdFrameworkCompatibilitySupport 1
#define _PCD_GET_MODE_SIZE_PcdFrameworkCompatibilitySupport  _PCD_SIZE_PcdFrameworkCompatibilitySupport 
#define _PCD_VALUE_PcdFrameworkCompatibilitySupport  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdFrameworkCompatibilitySupport;
#define _PCD_GET_MODE_BOOL_PcdFrameworkCompatibilitySupport  _gPcd_FixedAtBuild_PcdFrameworkCompatibilitySupport
//#define _PCD_SET_MODE_BOOL_PcdFrameworkCompatibilitySupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmBlockStartupThisAp  249U
#define _PCD_SIZE_PcdCpuSmmBlockStartupThisAp 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmBlockStartupThisAp  _PCD_SIZE_PcdCpuSmmBlockStartupThisAp 
#define _PCD_VALUE_PcdCpuSmmBlockStartupThisAp  ((BOOLEAN)1U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmBlockStartupThisAp;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmBlockStartupThisAp  _gPcd_FixedAtBuild_PcdCpuSmmBlockStartupThisAp
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmBlockStartupThisAp  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmEnableBspElection  250U
#define _PCD_SIZE_PcdCpuSmmEnableBspElection 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmEnableBspElection  _PCD_SIZE_PcdCpuSmmEnableBspElection 
#define _PCD_VALUE_PcdCpuSmmEnableBspElection  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmEnableBspElection;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmEnableBspElection  _gPcd_FixedAtBuild_PcdCpuSmmEnableBspElection
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmEnableBspElection  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmDebug  251U
#define _PCD_SIZE_PcdCpuSmmDebug 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmDebug  _PCD_SIZE_PcdCpuSmmDebug 
#define _PCD_VALUE_PcdCpuSmmDebug  ((BOOLEAN)1U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmDebug;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmDebug  _gPcd_FixedAtBuild_PcdCpuSmmDebug
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmDebug  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmUncacheCpuSyncData  252U
#define _PCD_SIZE_PcdCpuSmmUncacheCpuSyncData 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmUncacheCpuSyncData  _PCD_SIZE_PcdCpuSmmUncacheCpuSyncData 
#define _PCD_VALUE_PcdCpuSmmUncacheCpuSyncData  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmUncacheCpuSyncData;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmUncacheCpuSyncData  _gPcd_FixedAtBuild_PcdCpuSmmUncacheCpuSyncData
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmUncacheCpuSyncData  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuHotPlugSupport  253U
#define _PCD_SIZE_PcdCpuHotPlugSupport 1
#define _PCD_GET_MODE_SIZE_PcdCpuHotPlugSupport  _PCD_SIZE_PcdCpuHotPlugSupport 
#define _PCD_VALUE_PcdCpuHotPlugSupport  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuHotPlugSupport;
#define _PCD_GET_MODE_BOOL_PcdCpuHotPlugSupport  _gPcd_FixedAtBuild_PcdCpuHotPlugSupport
//#define _PCD_SET_MODE_BOOL_PcdCpuHotPlugSupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmStackGuard  254U
#define _PCD_SIZE_PcdCpuSmmStackGuard 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmStackGuard  _PCD_SIZE_PcdCpuSmmStackGuard 
#define _PCD_VALUE_PcdCpuSmmStackGuard  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmStackGuard;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmStackGuard  _gPcd_FixedAtBuild_PcdCpuSmmStackGuard
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmStackGuard  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmProfileEnable  255U
#define _PCD_SIZE_PcdCpuSmmProfileEnable 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmProfileEnable  _PCD_SIZE_PcdCpuSmmProfileEnable 
#define _PCD_VALUE_PcdCpuSmmProfileEnable  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmProfileEnable;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmProfileEnable  _gPcd_FixedAtBuild_PcdCpuSmmProfileEnable
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmProfileEnable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmProfileRingBuffer  256U
#define _PCD_SIZE_PcdCpuSmmProfileRingBuffer 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmProfileRingBuffer  _PCD_SIZE_PcdCpuSmmProfileRingBuffer 
#define _PCD_VALUE_PcdCpuSmmProfileRingBuffer  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmProfileRingBuffer;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmProfileRingBuffer  _gPcd_FixedAtBuild_PcdCpuSmmProfileRingBuffer
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmProfileRingBuffer  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmFeatureControlMsrLock  257U
#define _PCD_SIZE_PcdCpuSmmFeatureControlMsrLock 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmFeatureControlMsrLock  _PCD_SIZE_PcdCpuSmmFeatureControlMsrLock 
#define _PCD_VALUE_PcdCpuSmmFeatureControlMsrLock  ((BOOLEAN)1U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmFeatureControlMsrLock;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmFeatureControlMsrLock  _gPcd_FixedAtBuild_PcdCpuSmmFeatureControlMsrLock
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmFeatureControlMsrLock  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuMaxLogicalProcessorNumber  138U
#define _PCD_SIZE_PcdCpuMaxLogicalProcessorNumber 4
#define _PCD_GET_MODE_SIZE_PcdCpuMaxLogicalProcessorNumber  _PCD_SIZE_PcdCpuMaxLogicalProcessorNumber 
#define _PCD_VALUE_PcdCpuMaxLogicalProcessorNumber  192U
extern const  UINT32  _gPcd_FixedAtBuild_PcdCpuMaxLogicalProcessorNumber;
#define _PCD_GET_MODE_32_PcdCpuMaxLogicalProcessorNumber  _gPcd_FixedAtBuild_PcdCpuMaxLogicalProcessorNumber
//#define _PCD_SET_MODE_32_PcdCpuMaxLogicalProcessorNumber  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmProfileSize  258U
#define _PCD_SIZE_PcdCpuSmmProfileSize 4
#define _PCD_GET_MODE_SIZE_PcdCpuSmmProfileSize  _PCD_SIZE_PcdCpuSmmProfileSize 
#define _PCD_VALUE_PcdCpuSmmProfileSize  0x200000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdCpuSmmProfileSize;
#define _PCD_GET_MODE_32_PcdCpuSmmProfileSize  _gPcd_FixedAtBuild_PcdCpuSmmProfileSize
//#define _PCD_SET_MODE_32_PcdCpuSmmProfileSize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuIEDEnabled  259U
#define _PCD_SIZE_PcdCpuIEDEnabled 1
#define _PCD_GET_MODE_SIZE_PcdCpuIEDEnabled  _PCD_SIZE_PcdCpuIEDEnabled 
#define _PCD_VALUE_PcdCpuIEDEnabled  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuIEDEnabled;
#define _PCD_GET_MODE_BOOL_PcdCpuIEDEnabled  _gPcd_FixedAtBuild_PcdCpuIEDEnabled
//#define _PCD_SET_MODE_BOOL_PcdCpuIEDEnabled  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuIEDRamSize  260U
#define _PCD_SIZE_PcdCpuIEDRamSize 4
#define _PCD_GET_MODE_SIZE_PcdCpuIEDRamSize  _PCD_SIZE_PcdCpuIEDRamSize 
#define _PCD_VALUE_PcdCpuIEDRamSize  0x400000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdCpuIEDRamSize;
#define _PCD_GET_MODE_32_PcdCpuIEDRamSize  _gPcd_FixedAtBuild_PcdCpuIEDRamSize
//#define _PCD_SET_MODE_32_PcdCpuIEDRamSize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmStackSize  261U
#define _PCD_SIZE_PcdCpuSmmStackSize 4
#define _PCD_GET_MODE_SIZE_PcdCpuSmmStackSize  _PCD_SIZE_PcdCpuSmmStackSize 
#define _PCD_VALUE_PcdCpuSmmStackSize  0x4000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdCpuSmmStackSize;
#define _PCD_GET_MODE_32_PcdCpuSmmStackSize  _gPcd_FixedAtBuild_PcdCpuSmmStackSize
//#define _PCD_SET_MODE_32_PcdCpuSmmStackSize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmApSyncTimeout  262U
#define _PCD_SIZE_PcdCpuSmmApSyncTimeout 8
#define _PCD_GET_MODE_SIZE_PcdCpuSmmApSyncTimeout  _PCD_SIZE_PcdCpuSmmApSyncTimeout 
#define _PCD_VALUE_PcdCpuSmmApSyncTimeout  10000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdCpuSmmApSyncTimeout;
#define _PCD_GET_MODE_64_PcdCpuSmmApSyncTimeout  _gPcd_FixedAtBuild_PcdCpuSmmApSyncTimeout
//#define _PCD_SET_MODE_64_PcdCpuSmmApSyncTimeout  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuS3DataAddress  43U
#define _PCD_GET_MODE_64_PcdCpuS3DataAddress  LibPcdGet64(_PCD_TOKEN_PcdCpuS3DataAddress)
#define _PCD_GET_MODE_SIZE_PcdCpuS3DataAddress  LibPcdGetSize(_PCD_TOKEN_PcdCpuS3DataAddress)
#define _PCD_SET_MODE_64_PcdCpuS3DataAddress(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuS3DataAddress, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuS3DataAddress(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuS3DataAddress, (Value))

#define _PCD_TOKEN_PcdCpuHotPlugDataAddress  77U
#define _PCD_GET_MODE_64_PcdCpuHotPlugDataAddress  LibPcdGet64(_PCD_TOKEN_PcdCpuHotPlugDataAddress)
#define _PCD_GET_MODE_SIZE_PcdCpuHotPlugDataAddress  LibPcdGetSize(_PCD_TOKEN_PcdCpuHotPlugDataAddress)
#define _PCD_SET_MODE_64_PcdCpuHotPlugDataAddress(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuHotPlugDataAddress, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuHotPlugDataAddress(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuHotPlugDataAddress, (Value))

#define _PCD_TOKEN_PcdCpuSmmCodeAccessCheckEnable  263U
#define _PCD_SIZE_PcdCpuSmmCodeAccessCheckEnable 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmCodeAccessCheckEnable  _PCD_SIZE_PcdCpuSmmCodeAccessCheckEnable 
#define _PCD_VALUE_PcdCpuSmmCodeAccessCheckEnable  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmCodeAccessCheckEnable;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmCodeAccessCheckEnable  _gPcd_FixedAtBuild_PcdCpuSmmCodeAccessCheckEnable
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmCodeAccessCheckEnable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable  24U
#define _PCD_GET_MODE_BOOL_PcdCpuSmmMsrSaveStateEnable  LibPcdGetBool(_PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable)
#define _PCD_GET_MODE_SIZE_PcdCpuSmmMsrSaveStateEnable  LibPcdGetSize(_PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable)
#define _PCD_SET_MODE_BOOL_PcdCpuSmmMsrSaveStateEnable(Value)  LibPcdSetBool(_PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdCpuSmmMsrSaveStateEnable(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable, (Value))

#define _PCD_TOKEN_PcdCpuSmmSmrr2Base  78U
#define _PCD_GET_MODE_32_PcdCpuSmmSmrr2Base  LibPcdGet32(_PCD_TOKEN_PcdCpuSmmSmrr2Base)
#define _PCD_GET_MODE_SIZE_PcdCpuSmmSmrr2Base  LibPcdGetSize(_PCD_TOKEN_PcdCpuSmmSmrr2Base)
#define _PCD_SET_MODE_32_PcdCpuSmmSmrr2Base(Value)  LibPcdSet32(_PCD_TOKEN_PcdCpuSmmSmrr2Base, (Value))
#define _PCD_SET_MODE_32_S_PcdCpuSmmSmrr2Base(Value)  LibPcdSet32S(_PCD_TOKEN_PcdCpuSmmSmrr2Base, (Value))

#define _PCD_TOKEN_PcdCpuSmmSmrr2Size  79U
#define _PCD_GET_MODE_32_PcdCpuSmmSmrr2Size  LibPcdGet32(_PCD_TOKEN_PcdCpuSmmSmrr2Size)
#define _PCD_GET_MODE_SIZE_PcdCpuSmmSmrr2Size  LibPcdGetSize(_PCD_TOKEN_PcdCpuSmmSmrr2Size)
#define _PCD_SET_MODE_32_PcdCpuSmmSmrr2Size(Value)  LibPcdSet32(_PCD_TOKEN_PcdCpuSmmSmrr2Size, (Value))
#define _PCD_SET_MODE_32_S_PcdCpuSmmSmrr2Size(Value)  LibPcdSet32S(_PCD_TOKEN_PcdCpuSmmSmrr2Size, (Value))

#define _PCD_TOKEN_PcdCpuSmmSmrr2CacheType  80U
#define _PCD_GET_MODE_8_PcdCpuSmmSmrr2CacheType  LibPcdGet8(_PCD_TOKEN_PcdCpuSmmSmrr2CacheType)
#define _PCD_GET_MODE_SIZE_PcdCpuSmmSmrr2CacheType  LibPcdGetSize(_PCD_TOKEN_PcdCpuSmmSmrr2CacheType)
#define _PCD_SET_MODE_8_PcdCpuSmmSmrr2CacheType(Value)  LibPcdSet8(_PCD_TOKEN_PcdCpuSmmSmrr2CacheType, (Value))
#define _PCD_SET_MODE_8_S_PcdCpuSmmSmrr2CacheType(Value)  LibPcdSet8S(_PCD_TOKEN_PcdCpuSmmSmrr2CacheType, (Value))

#define _PCD_TOKEN_PcdCpuSmmUseDelayIndication  81U
#define _PCD_GET_MODE_BOOL_PcdCpuSmmUseDelayIndication  LibPcdGetBool(_PCD_TOKEN_PcdCpuSmmUseDelayIndication)
#define _PCD_GET_MODE_SIZE_PcdCpuSmmUseDelayIndication  LibPcdGetSize(_PCD_TOKEN_PcdCpuSmmUseDelayIndication)
#define _PCD_SET_MODE_BOOL_PcdCpuSmmUseDelayIndication(Value)  LibPcdSetBool(_PCD_TOKEN_PcdCpuSmmUseDelayIndication, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdCpuSmmUseDelayIndication(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdCpuSmmUseDelayIndication, (Value))

#define _PCD_TOKEN_PcdCpuSmmUseBlockIndication  82U
#define _PCD_GET_MODE_BOOL_PcdCpuSmmUseBlockIndication  LibPcdGetBool(_PCD_TOKEN_PcdCpuSmmUseBlockIndication)
#define _PCD_GET_MODE_SIZE_PcdCpuSmmUseBlockIndication  LibPcdGetSize(_PCD_TOKEN_PcdCpuSmmUseBlockIndication)
#define _PCD_SET_MODE_BOOL_PcdCpuSmmUseBlockIndication(Value)  LibPcdSetBool(_PCD_TOKEN_PcdCpuSmmUseBlockIndication, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdCpuSmmUseBlockIndication(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdCpuSmmUseBlockIndication, (Value))

#define _PCD_TOKEN_PcdCpuSmmUseSmmEnableIndication  83U
#define _PCD_GET_MODE_BOOL_PcdCpuSmmUseSmmEnableIndication  LibPcdGetBool(_PCD_TOKEN_PcdCpuSmmUseSmmEnableIndication)
#define _PCD_GET_MODE_SIZE_PcdCpuSmmUseSmmEnableIndication  LibPcdGetSize(_PCD_TOKEN_PcdCpuSmmUseSmmEnableIndication)
#define _PCD_SET_MODE_BOOL_PcdCpuSmmUseSmmEnableIndication(Value)  LibPcdSetBool(_PCD_TOKEN_PcdCpuSmmUseSmmEnableIndication, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdCpuSmmUseSmmEnableIndication(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdCpuSmmUseSmmEnableIndication, (Value))

#define _PCD_TOKEN_PcdCpuSmmProtectedModeEnable  264U
#define _PCD_SIZE_PcdCpuSmmProtectedModeEnable 1
#define _PCD_GET_MODE_SIZE_PcdCpuSmmProtectedModeEnable  _PCD_SIZE_PcdCpuSmmProtectedModeEnable 
#define _PCD_VALUE_PcdCpuSmmProtectedModeEnable  0U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCpuSmmProtectedModeEnable;
#define _PCD_GET_MODE_BOOL_PcdCpuSmmProtectedModeEnable  _gPcd_FixedAtBuild_PcdCpuSmmProtectedModeEnable
//#define _PCD_SET_MODE_BOOL_PcdCpuSmmProtectedModeEnable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
PiCpuSmmEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
