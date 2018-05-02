/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_7C609448_E20C_4fb2_8003_0ECF015913F0
#define _AUTOGENH_7C609448_E20C_4fb2_8003_0ECF015913F0

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern EFI_GUID gAmiPerformanceProfilingGuid;
extern EFI_GUID gAmiGlobalVariableGuid;
extern EFI_GUID gAmiModulePkgTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiVariableWriteArchProtocolGuid;

// PCD definitions
#define _PCD_TOKEN_AmiPcdPerformanceProfilingSupport  158U
extern const BOOLEAN _gPcd_FixedAtBuild_AmiPcdPerformanceProfilingSupport;
#define _PCD_GET_MODE_BOOL_AmiPcdPerformanceProfilingSupport  _gPcd_FixedAtBuild_AmiPcdPerformanceProfilingSupport
//#define _PCD_SET_MODE_BOOL_AmiPcdPerformanceProfilingSupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_AmiPcdPerformanceProfilingSupport 1
#define _PCD_GET_MODE_SIZE_AmiPcdPerformanceProfilingSupport _PCD_SIZE_AmiPcdPerformanceProfilingSupport

EFI_STATUS
EFIAPI
DxeCoreAmiPerformanceProfilingLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
