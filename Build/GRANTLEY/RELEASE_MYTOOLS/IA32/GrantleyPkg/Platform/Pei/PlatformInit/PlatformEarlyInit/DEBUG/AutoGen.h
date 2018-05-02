/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_EE685731_CFF3_4ee7_9388_7E63FC5A59B0
#define _AUTOGENH_EE685731_CFF3_4ee7_9388_7E63FC5A59B0

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xEE685731, 0xCFF3, 0x4ee7, {0x93, 0x88, 0x7E, 0x63, 0xFC, 0x5A, 0x59, 0xB0}}

// Guids
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiGlobalVariableControlGuid;
extern EFI_GUID gEfiSetupVariableDefaultGuid;
extern EFI_GUID gEfiTcgWakeEventDataHobGuid;
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gEfiMemoryTypeInformationGuid;
extern EFI_GUID gEfiFlashMapHobGuid;
extern EFI_GUID gPeiCapsuleOnDataCDGuid;
extern EFI_GUID gPeiCapsuleOnFatIdeDiskGuid;
extern EFI_GUID gPeiCapsuleOnFatUsbDiskGuid;
extern EFI_GUID gEfiMfgUUIDHobGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiPlatformTxtPolicyDataGuid;
extern EFI_GUID gEfiAdminPasswordHobGuid;
extern EFI_GUID gEfiVariableGuid;
extern EFI_GUID gAmiGlobalVariableGuid;
extern EFI_GUID gEfiIntelFrameworkModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiMePkgTokenSpaceGuid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gChipsetInitInfoHobGuid;

// PPIs
extern EFI_GUID gPeiBaseMemoryTestPpiGuid;
extern EFI_GUID gPchUsbPolicyPpiGuid;
extern EFI_GUID gEfiPeiStallPpiGuid;
extern EFI_GUID gPeiFlashMapPpiGuid;
extern EFI_GUID gEfiPeiBootInRecoveryModePpiGuid;
extern EFI_GUID gEfiPeiRecoveryModulePpiGuid;
extern EFI_GUID gEfiPeiMemoryDiscoveredPpiGuid;
extern EFI_GUID gPeiPlatformMemorySizePpiGuid;
extern EFI_GUID gEfiPeiReadOnlyVariable2PpiGuid;
extern EFI_GUID gEfiPeiMasterBootModePpiGuid;
extern EFI_GUID gEfiPeiResetPpiGuid;
extern EFI_GUID gPeiSmbusPolicyPpiGuid;
extern EFI_GUID gEfiEndOfPeiSignalPpiGuid;
extern EFI_GUID gPeiAtaPolicyPpiGuid;
extern EFI_GUID gPeiCachePpiGuid;
extern EFI_GUID gPchPlatformPolicyPpiGuid;
extern EFI_GUID gEfiPeiVirtualBlockIoPpiGuid;
extern EFI_GUID gEfiPeiDeviceRecoveryModulePpiGuid;
extern EFI_GUID gEfiPeiSmbus2PpiGuid;
extern EFI_GUID gPchInitPpiGuid;
extern EFI_GUID gPeiSpiSoftStrapsPpiGuid;
extern EFI_GUID gPchResetPpiGuid;
extern EFI_GUID gPeiPostScriptTablePpiGuid;
extern EFI_GUID gPeiMpServicePpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdFrameworkCompatibilitySupport  119U
#define _PCD_SIZE_PcdFrameworkCompatibilitySupport 1
#define _PCD_GET_MODE_SIZE_PcdFrameworkCompatibilitySupport  _PCD_SIZE_PcdFrameworkCompatibilitySupport 
#define _PCD_VALUE_PcdFrameworkCompatibilitySupport  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdFrameworkCompatibilitySupport;
#define _PCD_GET_MODE_BOOL_PcdFrameworkCompatibilitySupport  _gPcd_FixedAtBuild_PcdFrameworkCompatibilitySupport
//#define _PCD_SET_MODE_BOOL_PcdFrameworkCompatibilitySupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdBootState  4U
#define _PCD_GET_MODE_BOOL_PcdBootState  LibPcdGetBool(_PCD_TOKEN_PcdBootState)
#define _PCD_GET_MODE_SIZE_PcdBootState  LibPcdGetSize(_PCD_TOKEN_PcdBootState)
#define _PCD_SET_MODE_BOOL_PcdBootState(Value)  LibPcdSetBool(_PCD_TOKEN_PcdBootState, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdBootState(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdBootState, (Value))

#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress  _PCD_SIZE_PcdPciExpressBaseAddress 
#define _PCD_VALUE_PcdPciExpressBaseAddress  0x80000000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdPchSataInitReg78Data  2U
#define _PCD_GET_MODE_32_PcdPchSataInitReg78Data  LibPcdGet32(_PCD_TOKEN_PcdPchSataInitReg78Data)
#define _PCD_GET_MODE_SIZE_PcdPchSataInitReg78Data  LibPcdGetSize(_PCD_TOKEN_PcdPchSataInitReg78Data)
#define _PCD_SET_MODE_32_PcdPchSataInitReg78Data(Value)  LibPcdSet32(_PCD_TOKEN_PcdPchSataInitReg78Data, (Value))
#define _PCD_SET_MODE_32_S_PcdPchSataInitReg78Data(Value)  LibPcdSet32S(_PCD_TOKEN_PcdPchSataInitReg78Data, (Value))

#define _PCD_TOKEN_PcdPchSataInitReg88Data  3U
#define _PCD_GET_MODE_32_PcdPchSataInitReg88Data  LibPcdGet32(_PCD_TOKEN_PcdPchSataInitReg88Data)
#define _PCD_GET_MODE_SIZE_PcdPchSataInitReg88Data  LibPcdGetSize(_PCD_TOKEN_PcdPchSataInitReg88Data)
#define _PCD_SET_MODE_32_PcdPchSataInitReg88Data(Value)  LibPcdSet32(_PCD_TOKEN_PcdPchSataInitReg88Data, (Value))
#define _PCD_SET_MODE_32_S_PcdPchSataInitReg88Data(Value)  LibPcdSet32S(_PCD_TOKEN_PcdPchSataInitReg88Data, (Value))

#define _PCD_TOKEN_PcdDebugPrintErrorLevel  92U
#define _PCD_PATCHABLE_VALUE_PcdDebugPrintErrorLevel  ((UINT32)0x80000046U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdDebugPrintErrorLevel;
#define _PCD_GET_MODE_32_PcdDebugPrintErrorLevel  _gPcd_BinaryPatch_PcdDebugPrintErrorLevel
#define _PCD_PATCHABLE_PcdDebugPrintErrorLevel_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdDebugPrintErrorLevel  _gPcd_BinaryPatch_Size_PcdDebugPrintErrorLevel 
extern UINTN _gPcd_BinaryPatch_Size_PcdDebugPrintErrorLevel; 
#define _PCD_SET_MODE_32_PcdDebugPrintErrorLevel(Value)  (_gPcd_BinaryPatch_PcdDebugPrintErrorLevel = (Value))
#define _PCD_SET_MODE_32_S_PcdDebugPrintErrorLevel(Value)  ((_gPcd_BinaryPatch_PcdDebugPrintErrorLevel = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdMePlatformWarmResetCounter  5U
#define _PCD_GET_MODE_32_PcdMePlatformWarmResetCounter  LibPcdGet32(_PCD_TOKEN_PcdMePlatformWarmResetCounter)
#define _PCD_GET_MODE_SIZE_PcdMePlatformWarmResetCounter  LibPcdGetSize(_PCD_TOKEN_PcdMePlatformWarmResetCounter)
#define _PCD_SET_MODE_32_PcdMePlatformWarmResetCounter(Value)  LibPcdSet32(_PCD_TOKEN_PcdMePlatformWarmResetCounter, (Value))
#define _PCD_SET_MODE_32_S_PcdMePlatformWarmResetCounter(Value)  LibPcdSet32S(_PCD_TOKEN_PcdMePlatformWarmResetCounter, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
PlatformEarlyInitEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );





#ifdef __cplusplus
}
#endif

#endif
