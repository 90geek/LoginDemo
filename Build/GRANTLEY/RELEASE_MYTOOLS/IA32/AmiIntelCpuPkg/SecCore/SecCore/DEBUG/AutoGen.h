/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_1BA0062E_C779_4582_8566_336AE8F78F09
#define _AUTOGENH_1BA0062E_C779_4582_8566_336AE8F78F09

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x1BA0062E, 0xC779, 0x4582, {0x85, 0x66, 0x33, 0x6A, 0xE8, 0xF7, 0x8F, 0x09}}

// Guids
extern EFI_GUID gEfiFirmwarePerformanceGuid;
extern EFI_GUID gEfiCpuTokenSpaceGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiSerialPortTokenSpaceGuid;
extern EFI_GUID gPlatformTokenSpaceGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gCpuUncoreTokenSpaceGuid;
extern EFI_GUID gUefiCpuPkgTokenSpaceGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;

// PPIs
extern EFI_GUID gEfiTemporaryRamSupportPpiGuid;
extern EFI_GUID gAmiEarlyBistPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdSecCoreMaxPpiSupported  132U
#define _PCD_SIZE_PcdSecCoreMaxPpiSupported 4
#define _PCD_GET_MODE_SIZE_PcdSecCoreMaxPpiSupported  _PCD_SIZE_PcdSecCoreMaxPpiSupported 
#define _PCD_VALUE_PcdSecCoreMaxPpiSupported  0x6U
extern const  UINT32  _gPcd_FixedAtBuild_PcdSecCoreMaxPpiSupported;
#define _PCD_GET_MODE_32_PcdSecCoreMaxPpiSupported  _gPcd_FixedAtBuild_PcdSecCoreMaxPpiSupported
//#define _PCD_SET_MODE_32_PcdSecCoreMaxPpiSupported  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdPeiTemporaryRamStackSize  133U
#define _PCD_SIZE_PcdPeiTemporaryRamStackSize 4
#define _PCD_GET_MODE_SIZE_PcdPeiTemporaryRamStackSize  _PCD_SIZE_PcdPeiTemporaryRamStackSize 
#define _PCD_VALUE_PcdPeiTemporaryRamStackSize  0U
extern const  UINT32  _gPcd_FixedAtBuild_PcdPeiTemporaryRamStackSize;
#define _PCD_GET_MODE_32_PcdPeiTemporaryRamStackSize  _gPcd_FixedAtBuild_PcdPeiTemporaryRamStackSize
//#define _PCD_SET_MODE_32_PcdPeiTemporaryRamStackSize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


#ifdef __cplusplus
}
#endif

#endif
