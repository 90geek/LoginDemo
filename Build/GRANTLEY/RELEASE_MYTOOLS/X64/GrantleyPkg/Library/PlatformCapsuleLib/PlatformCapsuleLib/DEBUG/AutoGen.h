/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_425AFDC9_4B2B_4ef6_BD4E_7B9977AA0FE9
#define _AUTOGENH_425AFDC9_4B2B_4ef6_BD4E_7B9977AA0FE9

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern EFI_GUID gEfiServerCapsuleGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiGlobalNvsAreaProtocolGuid;

// PCD definitions
#define _PCD_TOKEN_PcdPchAcpiIoPortBaseAddress  94U
extern const UINT16 _gPcd_FixedAtBuild_PcdPchAcpiIoPortBaseAddress;
#define _PCD_GET_MODE_16_PcdPchAcpiIoPortBaseAddress  _gPcd_FixedAtBuild_PcdPchAcpiIoPortBaseAddress
//#define _PCD_SET_MODE_16_PcdPchAcpiIoPortBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_PcdPchAcpiIoPortBaseAddress 2
#define _PCD_GET_MODE_SIZE_PcdPchAcpiIoPortBaseAddress _PCD_SIZE_PcdPchAcpiIoPortBaseAddress


#ifdef __cplusplus
}
#endif

#endif
