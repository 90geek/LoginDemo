/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_7EB7126D_C45E_4BD0_9357_7F507C5C9CF9
#define _AUTOGENH_7EB7126D_C45E_4BD0_9357_7F507C5C9CF9

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x7EB7126D, 0xC45E, 0x4BD0, {0x93, 0x57, 0x7F, 0x50, 0x7C, 0x5C, 0x9C, 0xF9}}

// Guids
extern EFI_GUID gAmiRecoveryImageHobGuid;
extern EFI_GUID gAmiRomLayoutFfsFileGuid;
extern EFI_GUID gAmiRomLayoutGuid;
extern EFI_GUID gAmiModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;

// PPIs
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiBootInRecoveryModePpiGuid;
extern EFI_GUID gEfiPeiMemoryDiscoveredPpiGuid;
extern EFI_GUID gAmiReadyToLoadDxeCorePpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;
extern EFI_GUID gAmiDebugServicePpiGuid;

// Definition of PCDs used in this module

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
RomLayoutPeiEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );





#ifdef __cplusplus
}
#endif

#endif
