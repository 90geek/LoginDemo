/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_DD415C2F_4193_47d3_A29E_615C5362CD2B
#define _AUTOGENH_DD415C2F_4193_47d3_A29E_615C5362CD2B

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern GUID gEfiPchTokenSpaceGuid;

// PCD definitions
#define _PCD_TOKEN_PcdPchAcpiIoPortBaseAddress  94U
extern const UINT16 _gPcd_FixedAtBuild_PcdPchAcpiIoPortBaseAddress;
#define _PCD_GET_MODE_16_PcdPchAcpiIoPortBaseAddress  _gPcd_FixedAtBuild_PcdPchAcpiIoPortBaseAddress
//#define _PCD_SET_MODE_16_PcdPchAcpiIoPortBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_PcdPchAcpiIoPortBaseAddress 2
#define _PCD_GET_MODE_SIZE_PcdPchAcpiIoPortBaseAddress _PCD_SIZE_PcdPchAcpiIoPortBaseAddress
#define _PCD_TOKEN_PcdSmmActivationData  265U
extern const UINT8 _gPcd_FixedAtBuild_PcdSmmActivationData;
#define _PCD_GET_MODE_8_PcdSmmActivationData  _gPcd_FixedAtBuild_PcdSmmActivationData
//#define _PCD_SET_MODE_8_PcdSmmActivationData  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_PcdSmmActivationData 1
#define _PCD_GET_MODE_SIZE_PcdSmmActivationData _PCD_SIZE_PcdSmmActivationData


#ifdef __cplusplus
}
#endif

#endif
