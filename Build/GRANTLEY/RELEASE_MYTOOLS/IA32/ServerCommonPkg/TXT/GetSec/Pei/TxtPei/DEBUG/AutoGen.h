/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_CA9D8617_D652_403b_B6C5_BA47570116AD
#define _AUTOGENH_CA9D8617_D652_403b_B6C5_BA47570116AD

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xCA9D8617, 0xD652, 0x403b, {0xB6, 0xC5, 0xBA, 0x47, 0x57, 0x01, 0x16, 0xAD}}

// Guids
extern EFI_GUID gEfiPlatformTxtDeviceMemoryGuid;
extern EFI_GUID gEfiPlatformTxtPolicyDataGuid;
extern EFI_GUID gServerCommonTokenSpaceGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gUefiCpuPkgTokenSpaceGuid;
extern EFI_GUID gEfiSetupVariableGuid;

// PPIs
extern EFI_GUID gEfiPeiStallPpiGuid;
extern EFI_GUID gPeiTxtScleanPpiGuid;
extern EFI_GUID gPeiPostScriptTablePpiGuid;
extern EFI_GUID gEfiPeiMasterBootModePpiGuid;
extern EFI_GUID gPeiTxtMemoryUnlockedPpiGuid;
extern EFI_GUID gEfiPeiReadOnlyVariable2PpiGuid;
extern EFI_GUID gEfiPeiMemoryDiscoveredPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;
extern EFI_GUID gAmiDebugServicePpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;
extern EFI_GUID gPeiMpServicePpiGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdMaxCpuSocketCount  144U
#define _PCD_SIZE_PcdMaxCpuSocketCount 4
#define _PCD_GET_MODE_SIZE_PcdMaxCpuSocketCount  _PCD_SIZE_PcdMaxCpuSocketCount 
#define _PCD_VALUE_PcdMaxCpuSocketCount  ((UINT32)0x04U)
extern const  UINT32  _gPcd_FixedAtBuild_PcdMaxCpuSocketCount;
#define _PCD_GET_MODE_32_PcdMaxCpuSocketCount  _gPcd_FixedAtBuild_PcdMaxCpuSocketCount
//#define _PCD_SET_MODE_32_PcdMaxCpuSocketCount  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
PeimEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );





#ifdef __cplusplus
}
#endif

#endif
