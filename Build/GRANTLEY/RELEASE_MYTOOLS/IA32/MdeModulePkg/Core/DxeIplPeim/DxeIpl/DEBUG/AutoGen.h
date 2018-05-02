/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_86D70125_BAA3_4296_A62F_602BEBBB9081
#define _AUTOGENH_86D70125_BAA3_4296_A62F_602BEBBB9081

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x86D70125, 0xBAA3, 0x4296, {0xA6, 0x2F, 0x60, 0x2B, 0xEB, 0xBB, 0x90, 0x81}}

// Guids
extern EFI_GUID gEfiMemoryTypeInformationGuid;
extern EFI_GUID gAmiRecoveryImageHobGuid;
extern EFI_GUID gAmiGlobalVariableGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gAmiModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gTianoCustomDecompressGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gLzmaCustomDecompressGuid;

// PPIs
extern EFI_GUID gEfiDxeIplPpiGuid;
extern EFI_GUID gEfiPeiDecompressPpiGuid;
extern EFI_GUID gEfiEndOfPeiSignalPpiGuid;
extern EFI_GUID gEfiPeiReadOnlyVariable2PpiGuid;
extern EFI_GUID gEfiPeiLoadFilePpiGuid;
extern EFI_GUID gEfiPeiS3Resume2PpiGuid;
extern EFI_GUID gEfiPeiRecoveryModulePpiGuid;
extern EFI_GUID gEfiVectorHandoffInfoPpiGuid;
extern EFI_GUID gEfiPeiLoadedImagePpiGuid;
extern EFI_GUID gAmiReadyToLoadDxeCorePpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdDxeIplSwitchToLongMode  110U
#define _PCD_SIZE_PcdDxeIplSwitchToLongMode 1
#define _PCD_GET_MODE_SIZE_PcdDxeIplSwitchToLongMode  _PCD_SIZE_PcdDxeIplSwitchToLongMode 
#define _PCD_VALUE_PcdDxeIplSwitchToLongMode  ((BOOLEAN)1U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdDxeIplSwitchToLongMode;
#define _PCD_GET_MODE_BOOL_PcdDxeIplSwitchToLongMode  _gPcd_FixedAtBuild_PcdDxeIplSwitchToLongMode
//#define _PCD_SET_MODE_BOOL_PcdDxeIplSwitchToLongMode  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdDxeIplSupportUefiDecompress  127U
#define _PCD_SIZE_PcdDxeIplSupportUefiDecompress 1
#define _PCD_GET_MODE_SIZE_PcdDxeIplSupportUefiDecompress  _PCD_SIZE_PcdDxeIplSupportUefiDecompress 
#define _PCD_VALUE_PcdDxeIplSupportUefiDecompress  ((BOOLEAN)1U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdDxeIplSupportUefiDecompress;
#define _PCD_GET_MODE_BOOL_PcdDxeIplSupportUefiDecompress  _gPcd_FixedAtBuild_PcdDxeIplSupportUefiDecompress
//#define _PCD_SET_MODE_BOOL_PcdDxeIplSupportUefiDecompress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUse1GPageTable  112U
#define _PCD_SIZE_PcdUse1GPageTable 1
#define _PCD_GET_MODE_SIZE_PcdUse1GPageTable  _PCD_SIZE_PcdUse1GPageTable 
#define _PCD_VALUE_PcdUse1GPageTable  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdUse1GPageTable;
#define _PCD_GET_MODE_BOOL_PcdUse1GPageTable  _gPcd_FixedAtBuild_PcdUse1GPageTable
//#define _PCD_SET_MODE_BOOL_PcdUse1GPageTable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUseNewImageOnFlashUpdate  106U
#define _PCD_SIZE_PcdUseNewImageOnFlashUpdate 1
#define _PCD_GET_MODE_SIZE_PcdUseNewImageOnFlashUpdate  _PCD_SIZE_PcdUseNewImageOnFlashUpdate 
#define _PCD_VALUE_PcdUseNewImageOnFlashUpdate  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdUseNewImageOnFlashUpdate;
#define _PCD_GET_MODE_BOOL_PcdUseNewImageOnFlashUpdate  _gPcd_FixedAtBuild_PcdUseNewImageOnFlashUpdate
//#define _PCD_SET_MODE_BOOL_PcdUseNewImageOnFlashUpdate  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdForceSetupOnFailedRecovery  107U
#define _PCD_SIZE_PcdForceSetupOnFailedRecovery 1
#define _PCD_GET_MODE_SIZE_PcdForceSetupOnFailedRecovery  _PCD_SIZE_PcdForceSetupOnFailedRecovery 
#define _PCD_VALUE_PcdForceSetupOnFailedRecovery  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdForceSetupOnFailedRecovery;
#define _PCD_GET_MODE_BOOL_PcdForceSetupOnFailedRecovery  _gPcd_FixedAtBuild_PcdForceSetupOnFailedRecovery
//#define _PCD_SET_MODE_BOOL_PcdForceSetupOnFailedRecovery  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
PeimInitializeDxeIpl (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );





#ifdef __cplusplus
}
#endif

#endif
