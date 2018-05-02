/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_D71C8BA4_4AF2_4d0d_B1BA_F2409F0C20D3
#define _AUTOGENH_D71C8BA4_4AF2_4d0d_B1BA_F2409F0C20D3

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xD71C8BA4, 0x4AF2, 0x4d0d, {0xB1, 0xBA, 0xF2, 0x40, 0x9F, 0x0C, 0x20, 0xD3}}

// Guids
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiAcpiVariableGuid;
extern EFI_GUID gEfiMemoryConfigDataGuid;
extern EFI_GUID gEfiGenericVariableGuid;
extern EFI_GUID gEfiMemoryConfigDataHobGuid;
extern EFI_GUID gEfiMemoryOverwriteControlDataGuid;
extern EFI_GUID gPrevBootErrSrcHobGuid;
extern EFI_GUID gEfiOcDataGuid;
extern EFI_GUID gEfiPprVariableGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gEfiMemoryMapGuid;
extern EFI_GUID gEfiSmmPeiSmramMemoryReserveGuid;
extern EFI_GUID gEfiMpstNodeDataGuid;
extern EFI_GUID gEfiMemoryTypeInformationGuid;
extern EFI_GUID gEfiPlatformTxtDeviceMemoryGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiCpuCsrAccessGuid;
extern EFI_GUID gEfiSmbusHcProtocolGuid;

// PPIs
extern EFI_GUID gEfiPeiCpuIoPpiInstalledGuid;
extern EFI_GUID gEfiPciCfg2PpiGuid;
extern EFI_GUID gEfiPeiReadOnlyVariable2PpiGuid;
extern EFI_GUID gPeiBaseMemoryTestPpiGuid;
extern EFI_GUID gPeiPlatformMemorySizePpiGuid;
extern EFI_GUID gEfiPeiIpmiTransportPpiGuid;
extern EFI_GUID gEfiPeiResetPpiGuid;
extern EFI_GUID gEfiPeiSmbus2PpiGuid;
extern EFI_GUID gPchDmiTcVcMapPpiGuid;
extern EFI_GUID gPchInitPpiGuid;
extern EFI_GUID gMeUmaPpiGuid;
extern EFI_GUID gEfiPeiStallPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;
extern EFI_GUID gPeiTxtScleanPpiGuid;
extern EFI_GUID gSsaBiosServicesPpiGuid;

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
UncoreInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );





#ifdef __cplusplus
}
#endif

#endif
