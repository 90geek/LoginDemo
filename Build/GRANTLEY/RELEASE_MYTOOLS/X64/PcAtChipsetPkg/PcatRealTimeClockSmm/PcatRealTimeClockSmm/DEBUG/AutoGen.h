/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_378D7B65_8DA9_4773_B6E4_A47826A833E2
#define _AUTOGENH_378D7B65_8DA9_4773_B6E4_A47826A833E2

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x378D7B65, 0x8DA9, 0x4773, {0xB6, 0xE4, 0xA4, 0x78, 0x26, 0xA8, 0x33, 0xE2}}

// Guids
extern EFI_GUID SmmRsTableGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;

// Protocols
extern EFI_GUID gEfiSmmBase2ProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiSmmDebugServiceProtocolGuid;
extern EFI_GUID gEfiSmmAccess2ProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiSmmStatusCodeProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdRealTimeClockUpdateTimeout  236U
#define _PCD_SIZE_PcdRealTimeClockUpdateTimeout 4
#define _PCD_GET_MODE_SIZE_PcdRealTimeClockUpdateTimeout  _PCD_SIZE_PcdRealTimeClockUpdateTimeout 
#define _PCD_VALUE_PcdRealTimeClockUpdateTimeout  100000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdRealTimeClockUpdateTimeout;
#define _PCD_GET_MODE_32_PcdRealTimeClockUpdateTimeout  _gPcd_FixedAtBuild_PcdRealTimeClockUpdateTimeout
//#define _PCD_SET_MODE_32_PcdRealTimeClockUpdateTimeout  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InitializePcRtcSmm (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
