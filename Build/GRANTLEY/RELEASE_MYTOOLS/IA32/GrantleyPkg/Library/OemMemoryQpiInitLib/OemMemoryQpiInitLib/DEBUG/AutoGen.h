/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_FBC62E13_365E_43cb_AE4E_EA56107F8F0E
#define _AUTOGENH_FBC62E13_365E_43cb_AE4E_EA56107F8F0E

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern GUID gEfiAcpiVariableGuid;
extern GUID gEfiMemoryConfigDataGuid;
extern GUID gEfiSetupVariableGuid;
extern GUID gEfiGenericVariableGuid;
extern GUID gEfiMemoryConfigDataHobGuid;
extern GUID gEfiMemoryOverwriteControlDataGuid;
extern GUID gPrevBootErrSrcHobGuid;
extern GUID gEfiOcDataGuid;
extern GUID gEfiPprVariableGuid;
extern GUID gEfiMdePkgTokenSpaceGuid;

// PPIs
extern GUID gMeUmaPpiGuid;
extern GUID gEfiPeiStallPpiGuid;
extern GUID gEfiPeiIpmiTransportPpiGuid;

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
