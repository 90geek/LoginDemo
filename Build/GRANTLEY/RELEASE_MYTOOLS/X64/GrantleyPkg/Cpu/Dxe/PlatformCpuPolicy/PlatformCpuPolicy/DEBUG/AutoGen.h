/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_76A7B4FC_C8D5_462d_A4D2_6E88338A772A
#define _AUTOGENH_76A7B4FC_C8D5_462d_A4D2_6E88338A772A

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x76A7B4FC, 0xC8D5, 0x462d, {0xA4, 0xD2, 0x6E, 0x88, 0x33, 0x8A, 0x77, 0x2A}}

// Guids
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiCpuTokenSpaceGuid;
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
extern EFI_GUID gIntelCpuPcdsSetDoneProtocolGuid;
extern EFI_GUID gEfiPlatformTypeProtocolGuid;
extern EFI_GUID gEfiCpuCsrAccessGuid;
extern EFI_GUID gExitPmAuthProtocolGuid;
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

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration  34U
#define _PCD_GET_MODE_32_PcdCpuProcessorFeatureUserConfiguration  LibPcdGet32(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration)
#define _PCD_GET_MODE_SIZE_PcdCpuProcessorFeatureUserConfiguration  LibPcdGetSize(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration)
#define _PCD_SET_MODE_32_PcdCpuProcessorFeatureUserConfiguration(Value)  LibPcdSet32(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration, (Value))
#define _PCD_SET_MODE_32_S_PcdCpuProcessorFeatureUserConfiguration(Value)  LibPcdSet32S(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfiguration, (Value))

#define _PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1  37U
#define _PCD_GET_MODE_32_PcdCpuProcessorFeatureUserConfigurationEx1  LibPcdGet32(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1)
#define _PCD_GET_MODE_SIZE_PcdCpuProcessorFeatureUserConfigurationEx1  LibPcdGetSize(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1)
#define _PCD_SET_MODE_32_PcdCpuProcessorFeatureUserConfigurationEx1(Value)  LibPcdSet32(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1, (Value))
#define _PCD_SET_MODE_32_S_PcdCpuProcessorFeatureUserConfigurationEx1(Value)  LibPcdSet32S(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1, (Value))

#define _PCD_TOKEN_PcdCpuEnergyPolicy  45U
#define _PCD_GET_MODE_8_PcdCpuEnergyPolicy  LibPcdGet8(_PCD_TOKEN_PcdCpuEnergyPolicy)
#define _PCD_GET_MODE_SIZE_PcdCpuEnergyPolicy  LibPcdGetSize(_PCD_TOKEN_PcdCpuEnergyPolicy)
#define _PCD_SET_MODE_8_PcdCpuEnergyPolicy(Value)  LibPcdSet8(_PCD_TOKEN_PcdCpuEnergyPolicy, (Value))
#define _PCD_SET_MODE_8_S_PcdCpuEnergyPolicy(Value)  LibPcdSet8S(_PCD_TOKEN_PcdCpuEnergyPolicy, (Value))

#define _PCD_TOKEN_PcdCpuAcpiLvl2Addr  47U
#define _PCD_GET_MODE_16_PcdCpuAcpiLvl2Addr  LibPcdGet16(_PCD_TOKEN_PcdCpuAcpiLvl2Addr)
#define _PCD_GET_MODE_SIZE_PcdCpuAcpiLvl2Addr  LibPcdGetSize(_PCD_TOKEN_PcdCpuAcpiLvl2Addr)
#define _PCD_SET_MODE_16_PcdCpuAcpiLvl2Addr(Value)  LibPcdSet16(_PCD_TOKEN_PcdCpuAcpiLvl2Addr, (Value))
#define _PCD_SET_MODE_16_S_PcdCpuAcpiLvl2Addr(Value)  LibPcdSet16S(_PCD_TOKEN_PcdCpuAcpiLvl2Addr, (Value))

#define _PCD_TOKEN_PcdCpuPackageCStateLimit  48U
#define _PCD_GET_MODE_8_PcdCpuPackageCStateLimit  LibPcdGet8(_PCD_TOKEN_PcdCpuPackageCStateLimit)
#define _PCD_GET_MODE_SIZE_PcdCpuPackageCStateLimit  LibPcdGetSize(_PCD_TOKEN_PcdCpuPackageCStateLimit)
#define _PCD_SET_MODE_8_PcdCpuPackageCStateLimit(Value)  LibPcdSet8(_PCD_TOKEN_PcdCpuPackageCStateLimit, (Value))
#define _PCD_SET_MODE_8_S_PcdCpuPackageCStateLimit(Value)  LibPcdSet8S(_PCD_TOKEN_PcdCpuPackageCStateLimit, (Value))

#define _PCD_TOKEN_PcdCpuClockModulationDutyCycle  46U
#define _PCD_GET_MODE_8_PcdCpuClockModulationDutyCycle  LibPcdGet8(_PCD_TOKEN_PcdCpuClockModulationDutyCycle)
#define _PCD_GET_MODE_SIZE_PcdCpuClockModulationDutyCycle  LibPcdGetSize(_PCD_TOKEN_PcdCpuClockModulationDutyCycle)
#define _PCD_SET_MODE_8_PcdCpuClockModulationDutyCycle(Value)  LibPcdSet8(_PCD_TOKEN_PcdCpuClockModulationDutyCycle, (Value))
#define _PCD_SET_MODE_8_S_PcdCpuClockModulationDutyCycle(Value)  LibPcdSet8S(_PCD_TOKEN_PcdCpuClockModulationDutyCycle, (Value))

#define _PCD_TOKEN_PcdCpuHwCoordination  44U
#define _PCD_GET_MODE_BOOL_PcdCpuHwCoordination  LibPcdGetBool(_PCD_TOKEN_PcdCpuHwCoordination)
#define _PCD_GET_MODE_SIZE_PcdCpuHwCoordination  LibPcdGetSize(_PCD_TOKEN_PcdCpuHwCoordination)
#define _PCD_SET_MODE_BOOL_PcdCpuHwCoordination(Value)  LibPcdSetBool(_PCD_TOKEN_PcdCpuHwCoordination, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdCpuHwCoordination(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdCpuHwCoordination, (Value))

#define _PCD_TOKEN_PcdPlatformCpuSocketCount  30U
#define _PCD_GET_MODE_32_PcdPlatformCpuSocketCount  LibPcdGet32(_PCD_TOKEN_PcdPlatformCpuSocketCount)
#define _PCD_GET_MODE_SIZE_PcdPlatformCpuSocketCount  LibPcdGetSize(_PCD_TOKEN_PcdPlatformCpuSocketCount)
#define _PCD_SET_MODE_32_PcdPlatformCpuSocketCount(Value)  LibPcdSet32(_PCD_TOKEN_PcdPlatformCpuSocketCount, (Value))
#define _PCD_SET_MODE_32_S_PcdPlatformCpuSocketCount(Value)  LibPcdSet32S(_PCD_TOKEN_PcdPlatformCpuSocketCount, (Value))

#define _PCD_TOKEN_PcdPlatformCpuSocketNames  29U
#define _PCD_GET_MODE_64_PcdPlatformCpuSocketNames  LibPcdGet64(_PCD_TOKEN_PcdPlatformCpuSocketNames)
#define _PCD_GET_MODE_SIZE_PcdPlatformCpuSocketNames  LibPcdGetSize(_PCD_TOKEN_PcdPlatformCpuSocketNames)
#define _PCD_SET_MODE_64_PcdPlatformCpuSocketNames(Value)  LibPcdSet64(_PCD_TOKEN_PcdPlatformCpuSocketNames, (Value))
#define _PCD_SET_MODE_64_S_PcdPlatformCpuSocketNames(Value)  LibPcdSet64S(_PCD_TOKEN_PcdPlatformCpuSocketNames, (Value))

#define _PCD_TOKEN_PcdPlatformCpuAssetTags  28U
#define _PCD_GET_MODE_64_PcdPlatformCpuAssetTags  LibPcdGet64(_PCD_TOKEN_PcdPlatformCpuAssetTags)
#define _PCD_GET_MODE_SIZE_PcdPlatformCpuAssetTags  LibPcdGetSize(_PCD_TOKEN_PcdPlatformCpuAssetTags)
#define _PCD_SET_MODE_64_PcdPlatformCpuAssetTags(Value)  LibPcdSet64(_PCD_TOKEN_PcdPlatformCpuAssetTags, (Value))
#define _PCD_SET_MODE_64_S_PcdPlatformCpuAssetTags(Value)  LibPcdSet64S(_PCD_TOKEN_PcdPlatformCpuAssetTags, (Value))

#define _PCD_TOKEN_PcdIsPowerOnReset  40U
#define _PCD_GET_MODE_BOOL_PcdIsPowerOnReset  LibPcdGetBool(_PCD_TOKEN_PcdIsPowerOnReset)
#define _PCD_GET_MODE_SIZE_PcdIsPowerOnReset  LibPcdGetSize(_PCD_TOKEN_PcdIsPowerOnReset)
#define _PCD_SET_MODE_BOOL_PcdIsPowerOnReset(Value)  LibPcdSetBool(_PCD_TOKEN_PcdIsPowerOnReset, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdIsPowerOnReset(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdIsPowerOnReset, (Value))

#define _PCD_TOKEN_PcdCpuDcuMode  49U
#define _PCD_GET_MODE_8_PcdCpuDcuMode  LibPcdGet8(_PCD_TOKEN_PcdCpuDcuMode)
#define _PCD_GET_MODE_SIZE_PcdCpuDcuMode  LibPcdGetSize(_PCD_TOKEN_PcdCpuDcuMode)
#define _PCD_SET_MODE_8_PcdCpuDcuMode(Value)  LibPcdSet8(_PCD_TOKEN_PcdCpuDcuMode, (Value))
#define _PCD_SET_MODE_8_S_PcdCpuDcuMode(Value)  LibPcdSet8S(_PCD_TOKEN_PcdCpuDcuMode, (Value))

#define _PCD_TOKEN_PcdCpuDebugInterface  51U
#define _PCD_GET_MODE_8_PcdCpuDebugInterface  LibPcdGet8(_PCD_TOKEN_PcdCpuDebugInterface)
#define _PCD_GET_MODE_SIZE_PcdCpuDebugInterface  LibPcdGetSize(_PCD_TOKEN_PcdCpuDebugInterface)
#define _PCD_SET_MODE_8_PcdCpuDebugInterface(Value)  LibPcdSet8(_PCD_TOKEN_PcdCpuDebugInterface, (Value))
#define _PCD_SET_MODE_8_S_PcdCpuDebugInterface(Value)  LibPcdSet8S(_PCD_TOKEN_PcdCpuDebugInterface, (Value))

#define _PCD_TOKEN_PcdCpuTurboOverride  52U
#define _PCD_GET_MODE_32_PcdCpuTurboOverride  LibPcdGet32(_PCD_TOKEN_PcdCpuTurboOverride)
#define _PCD_GET_MODE_SIZE_PcdCpuTurboOverride  LibPcdGetSize(_PCD_TOKEN_PcdCpuTurboOverride)
#define _PCD_SET_MODE_32_PcdCpuTurboOverride(Value)  LibPcdSet32(_PCD_TOKEN_PcdCpuTurboOverride, (Value))
#define _PCD_SET_MODE_32_S_PcdCpuTurboOverride(Value)  LibPcdSet32S(_PCD_TOKEN_PcdCpuTurboOverride, (Value))

#define _PCD_TOKEN_PcdCpuProcessorMsrLockCtrl  50U
#define _PCD_GET_MODE_8_PcdCpuProcessorMsrLockCtrl  LibPcdGet8(_PCD_TOKEN_PcdCpuProcessorMsrLockCtrl)
#define _PCD_GET_MODE_SIZE_PcdCpuProcessorMsrLockCtrl  LibPcdGetSize(_PCD_TOKEN_PcdCpuProcessorMsrLockCtrl)
#define _PCD_SET_MODE_8_PcdCpuProcessorMsrLockCtrl(Value)  LibPcdSet8(_PCD_TOKEN_PcdCpuProcessorMsrLockCtrl, (Value))
#define _PCD_SET_MODE_8_S_PcdCpuProcessorMsrLockCtrl(Value)  LibPcdSet8S(_PCD_TOKEN_PcdCpuProcessorMsrLockCtrl, (Value))

#define _PCD_TOKEN_PcdCpuIioLlcWaysBitMask  53U
#define _PCD_GET_MODE_64_PcdCpuIioLlcWaysBitMask  LibPcdGet64(_PCD_TOKEN_PcdCpuIioLlcWaysBitMask)
#define _PCD_GET_MODE_SIZE_PcdCpuIioLlcWaysBitMask  LibPcdGetSize(_PCD_TOKEN_PcdCpuIioLlcWaysBitMask)
#define _PCD_SET_MODE_64_PcdCpuIioLlcWaysBitMask(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuIioLlcWaysBitMask, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuIioLlcWaysBitMask(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuIioLlcWaysBitMask, (Value))

#define _PCD_TOKEN_PcdCpuQlruCfgBitMask  54U
#define _PCD_GET_MODE_64_PcdCpuQlruCfgBitMask  LibPcdGet64(_PCD_TOKEN_PcdCpuQlruCfgBitMask)
#define _PCD_GET_MODE_SIZE_PcdCpuQlruCfgBitMask  LibPcdGetSize(_PCD_TOKEN_PcdCpuQlruCfgBitMask)
#define _PCD_SET_MODE_64_PcdCpuQlruCfgBitMask(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuQlruCfgBitMask, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuQlruCfgBitMask(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuQlruCfgBitMask, (Value))

#define _PCD_TOKEN_PcdSbspSelection  55U
#define _PCD_GET_MODE_8_PcdSbspSelection  LibPcdGet8(_PCD_TOKEN_PcdSbspSelection)
#define _PCD_GET_MODE_SIZE_PcdSbspSelection  LibPcdGetSize(_PCD_TOKEN_PcdSbspSelection)
#define _PCD_SET_MODE_8_PcdSbspSelection(Value)  LibPcdSet8(_PCD_TOKEN_PcdSbspSelection, (Value))
#define _PCD_SET_MODE_8_S_PcdSbspSelection(Value)  LibPcdSet8S(_PCD_TOKEN_PcdSbspSelection, (Value))

#define _PCD_TOKEN_PcdCpuPmStructAddr  56U
#define _PCD_GET_MODE_64_PcdCpuPmStructAddr  LibPcdGet64(_PCD_TOKEN_PcdCpuPmStructAddr)
#define _PCD_GET_MODE_SIZE_PcdCpuPmStructAddr  LibPcdGetSize(_PCD_TOKEN_PcdCpuPmStructAddr)
#define _PCD_SET_MODE_64_PcdCpuPmStructAddr(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuPmStructAddr, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuPmStructAddr(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuPmStructAddr, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
PlatformCpuPolicyEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
