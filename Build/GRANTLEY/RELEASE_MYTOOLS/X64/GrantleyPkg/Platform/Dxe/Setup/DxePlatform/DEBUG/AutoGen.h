/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_ABBCE13D_E25A_4d9f_A1F9_2F7710786892
#define _AUTOGENH_ABBCE13D_E25A_4d9f_A1F9_2F7710786892

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xABBCE13D, 0xE25A, 0x4d9f, {0xA1, 0xF9, 0x2F, 0x77, 0x10, 0x78, 0x68, 0x92}}

// Guids
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gMainPkgListGuid;
extern EFI_GUID gAdvancedPkgListGuid;
extern EFI_GUID gTpmPkgListGuid;
extern EFI_GUID gEfiCpuHtCapableGuid;
extern EFI_GUID gEfiMemorySetupGuid;
extern EFI_GUID gEfiMemoryMapGuid;
extern EFI_GUID gBootOptionsPkgListGuid;
extern EFI_GUID gMeSetupInfoGuid;
extern EFI_GUID gSetupFwUpdChgGuid;
extern EFI_GUID gSetupMngChgGuid;
extern EFI_GUID gMeStateChgGuid;
extern EFI_GUID gMeSetupPolicyUpdate;
extern EFI_GUID gIccDataGuid;
extern EFI_GUID gEfiSetupEnterGuid;
extern EFI_GUID gEfiAdminPasswordHobGuid;
extern EFI_GUID gServerCommonTokenSpaceGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiIntelFrameworkModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiCpuTokenSpaceGuid;
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
extern EFI_GUID gChipsetInitInfoHobGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gEfiMeBiosExtensionSetupGuid;
extern EFI_GUID gDxePlatformMePolicyGuid;
extern EFI_GUID gEfiStatusCodeDataTypeStringGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

// Protocols
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiHiiDatabaseProtocolGuid;
extern EFI_GUID gEfiHiiConfigAccessProtocolGuid;
extern EFI_GUID gEfiHiiConfigRoutingProtocolGuid;
extern EFI_GUID gEfiFormBrowser2ProtocolGuid;
extern EFI_GUID gEfiTcgProtocolGuid;
extern EFI_GUID gEfiPlatformPolicyProtocolGuid;
extern EFI_GUID gEfiPlatformTypeProtocolGuid;
extern EFI_GUID gEfiPciRootBridgeIoProtocolGuid;
extern EFI_GUID gDxePchPlatformPolicyProtocolGuid;
extern EFI_GUID gEfiPs2PolicyProtocolGuid;
extern EFI_GUID gEfiIsaIoProtocolGuid;
extern EFI_GUID gEfiDiskInfoProtocolGuid;
extern EFI_GUID gEfiDataHubProtocolGuid;
extern EFI_GUID gEfiIioUdsProtocolGuid;
extern EFI_GUID gEfiLegacyBootMarkerGuid;
extern EFI_GUID gEfiWindowsInt10Workaround;
extern EFI_GUID gEfiSmbiosProtocolGuid;
extern EFI_GUID gDxePchPlatformResetPolicyProtocolGuid;
extern EFI_GUID gEfiIioSystemProtocolGuid;
extern EFI_GUID gEfiMpServiceProtocolGuid;
extern EFI_GUID gWdtProtocolGuid;
extern EFI_GUID gPchResetProtocolGuid;
extern EFI_GUID gIccDataProtocolGuid;
extern EFI_GUID gEfiCpuCsrAccessGuid;
extern EFI_GUID gEfiHiiPackageListProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
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
extern EFI_GUID gEfiHiiStringProtocolGuid;
extern EFI_GUID gEfiHiiImageProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiHeciProtocolGuid;
extern EFI_GUID gPlatformMeHookProtocolGuid;
extern EFI_GUID gMeBiosPayloadDataProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdUefiOptimizedBoot  25U
#define _PCD_GET_MODE_BOOL_PcdUefiOptimizedBoot  LibPcdGetBool(_PCD_TOKEN_PcdUefiOptimizedBoot)
#define _PCD_GET_MODE_SIZE_PcdUefiOptimizedBoot  LibPcdGetSize(_PCD_TOKEN_PcdUefiOptimizedBoot)
#define _PCD_SET_MODE_BOOL_PcdUefiOptimizedBoot(Value)  LibPcdSetBool(_PCD_TOKEN_PcdUefiOptimizedBoot, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdUefiOptimizedBoot(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdUefiOptimizedBoot, (Value))

#define _PCD_TOKEN_PcdWakeOnRTCS5  57U
#define _PCD_GET_MODE_BOOL_PcdWakeOnRTCS5  LibPcdGetBool(_PCD_TOKEN_PcdWakeOnRTCS5)
#define _PCD_GET_MODE_SIZE_PcdWakeOnRTCS5  LibPcdGetSize(_PCD_TOKEN_PcdWakeOnRTCS5)
#define _PCD_SET_MODE_BOOL_PcdWakeOnRTCS5(Value)  LibPcdSetBool(_PCD_TOKEN_PcdWakeOnRTCS5, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdWakeOnRTCS5(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdWakeOnRTCS5, (Value))

#define _PCD_TOKEN_PcdRtcWakeupTimeHour  58U
#define _PCD_GET_MODE_8_PcdRtcWakeupTimeHour  LibPcdGet8(_PCD_TOKEN_PcdRtcWakeupTimeHour)
#define _PCD_GET_MODE_SIZE_PcdRtcWakeupTimeHour  LibPcdGetSize(_PCD_TOKEN_PcdRtcWakeupTimeHour)
#define _PCD_SET_MODE_8_PcdRtcWakeupTimeHour(Value)  LibPcdSet8(_PCD_TOKEN_PcdRtcWakeupTimeHour, (Value))
#define _PCD_SET_MODE_8_S_PcdRtcWakeupTimeHour(Value)  LibPcdSet8S(_PCD_TOKEN_PcdRtcWakeupTimeHour, (Value))

#define _PCD_TOKEN_PcdRtcWakeupTimeMinute  59U
#define _PCD_GET_MODE_8_PcdRtcWakeupTimeMinute  LibPcdGet8(_PCD_TOKEN_PcdRtcWakeupTimeMinute)
#define _PCD_GET_MODE_SIZE_PcdRtcWakeupTimeMinute  LibPcdGetSize(_PCD_TOKEN_PcdRtcWakeupTimeMinute)
#define _PCD_SET_MODE_8_PcdRtcWakeupTimeMinute(Value)  LibPcdSet8(_PCD_TOKEN_PcdRtcWakeupTimeMinute, (Value))
#define _PCD_SET_MODE_8_S_PcdRtcWakeupTimeMinute(Value)  LibPcdSet8S(_PCD_TOKEN_PcdRtcWakeupTimeMinute, (Value))

#define _PCD_TOKEN_PcdRtcWakeupTimeSecond  60U
#define _PCD_GET_MODE_8_PcdRtcWakeupTimeSecond  LibPcdGet8(_PCD_TOKEN_PcdRtcWakeupTimeSecond)
#define _PCD_GET_MODE_SIZE_PcdRtcWakeupTimeSecond  LibPcdGetSize(_PCD_TOKEN_PcdRtcWakeupTimeSecond)
#define _PCD_SET_MODE_8_PcdRtcWakeupTimeSecond(Value)  LibPcdSet8(_PCD_TOKEN_PcdRtcWakeupTimeSecond, (Value))
#define _PCD_SET_MODE_8_S_PcdRtcWakeupTimeSecond(Value)  LibPcdSet8S(_PCD_TOKEN_PcdRtcWakeupTimeSecond, (Value))

#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress  _PCD_SIZE_PcdPciExpressBaseAddress 
#define _PCD_VALUE_PcdPciExpressBaseAddress  0x80000000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdPlatformBootTimeOut  26U
#define _PCD_GET_MODE_16_PcdPlatformBootTimeOut  LibPcdGet16(_PCD_TOKEN_PcdPlatformBootTimeOut)
#define _PCD_GET_MODE_SIZE_PcdPlatformBootTimeOut  LibPcdGetSize(_PCD_TOKEN_PcdPlatformBootTimeOut)
#define _PCD_SET_MODE_16_PcdPlatformBootTimeOut(Value)  LibPcdSet16(_PCD_TOKEN_PcdPlatformBootTimeOut, (Value))
#define _PCD_SET_MODE_16_S_PcdPlatformBootTimeOut(Value)  LibPcdSet16S(_PCD_TOKEN_PcdPlatformBootTimeOut, (Value))

#define _PCD_TOKEN_PcdUse1GPageTable  112U
#define _PCD_SIZE_PcdUse1GPageTable 1
#define _PCD_GET_MODE_SIZE_PcdUse1GPageTable  _PCD_SIZE_PcdUse1GPageTable 
#define _PCD_VALUE_PcdUse1GPageTable  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdUse1GPageTable;
#define _PCD_GET_MODE_BOOL_PcdUse1GPageTable  _gPcd_FixedAtBuild_PcdUse1GPageTable
//#define _PCD_SET_MODE_BOOL_PcdUse1GPageTable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable  24U
#define _PCD_GET_MODE_BOOL_PcdCpuSmmMsrSaveStateEnable  LibPcdGetBool(_PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable)
#define _PCD_GET_MODE_SIZE_PcdCpuSmmMsrSaveStateEnable  LibPcdGetSize(_PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable)
#define _PCD_SET_MODE_BOOL_PcdCpuSmmMsrSaveStateEnable(Value)  LibPcdSetBool(_PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdCpuSmmMsrSaveStateEnable(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdCpuSmmMsrSaveStateEnable, (Value))

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

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
SetupDriverEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );



#include "PlatformStrDefs.h"


#ifdef __cplusplus
}
#endif

#endif
