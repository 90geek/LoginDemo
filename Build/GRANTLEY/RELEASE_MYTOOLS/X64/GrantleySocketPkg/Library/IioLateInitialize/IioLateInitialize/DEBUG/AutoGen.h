/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_74B9CA54_0D70_4510_ABAD_8F7137CA62F5
#define _AUTOGENH_74B9CA54_0D70_4510_ABAD_8F7137CA62F5

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern GUID gReadyForLockProtocolGuid;
extern GUID gEfiEventExitBootServicesGuid;
extern GUID gPlatformTokenSpaceGuid;
extern GUID gEfiCpuTokenSpaceGuid;

// Protocols
extern GUID gEfiPciCallbackProtocolGuid;
extern GUID gEfiIioSystemProtocolGuid;
extern GUID gExitPmAuthProtocolGuid;
extern GUID gEfiIioUdsProtocolGuid;
extern GUID gEfiMpServiceProtocolGuid;
extern GUID gEfiPciEnumerationCompleteProtocolGuid;

// PCD definitions
#define _PCD_TOKEN_PcdLockCsrSsidSvidRegister  230U
extern const BOOLEAN _gPcd_FixedAtBuild_PcdLockCsrSsidSvidRegister;
#define _PCD_GET_MODE_BOOL_PcdLockCsrSsidSvidRegister  _gPcd_FixedAtBuild_PcdLockCsrSsidSvidRegister
//#define _PCD_SET_MODE_BOOL_PcdLockCsrSsidSvidRegister  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1  37U
#define _PCD_GET_MODE_32_PcdCpuProcessorFeatureUserConfigurationEx1  LibPcdGet32(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1)
#define _PCD_GET_MODE_SIZE_PcdCpuProcessorFeatureUserConfigurationEx1  LibPcdGetSize(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1)
#define _PCD_SET_MODE_32_PcdCpuProcessorFeatureUserConfigurationEx1(Value)  LibPcdSet32(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1, (Value))
#define _PCD_SET_MODE_32_S_PcdCpuProcessorFeatureUserConfigurationEx1(Value)  LibPcdSet32S(_PCD_TOKEN_PcdCpuProcessorFeatureUserConfigurationEx1, (Value))


#ifdef __cplusplus
}
#endif

#endif
