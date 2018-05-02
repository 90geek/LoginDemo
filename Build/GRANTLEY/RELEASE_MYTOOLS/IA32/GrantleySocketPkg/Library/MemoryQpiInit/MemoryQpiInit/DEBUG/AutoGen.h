/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_11777581_2B67_4075_8EB4_F691A47ECEC7
#define _AUTOGENH_11777581_2B67_4075_8EB4_F691A47ECEC7

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern GUID gEfiPlatformInfoGuid;
extern GUID gEfiMemoryMapGuid;
extern GUID gEfiSmmPeiSmramMemoryReserveGuid;
extern GUID gEfiMpstNodeDataGuid;
extern GUID gEfiMemoryTypeInformationGuid;
extern GUID gEfiPlatformTxtDeviceMemoryGuid;
extern GUID gEfiMdePkgTokenSpaceGuid;

// PPIs
extern GUID gEfiPeiCpuIoPpiInstalledGuid;
extern GUID gEfiPciCfg2PpiGuid;
extern GUID gPeiBaseMemoryTestPpiGuid;
extern GUID gPeiPlatformMemorySizePpiGuid;
extern GUID gPeiTxtScleanPpiGuid;
extern GUID gSsaBiosServicesPpiGuid;

// PCD definitions
#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
extern const UINT64 _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress _PCD_SIZE_PcdPciExpressBaseAddress


#ifdef __cplusplus
}
#endif

#endif
