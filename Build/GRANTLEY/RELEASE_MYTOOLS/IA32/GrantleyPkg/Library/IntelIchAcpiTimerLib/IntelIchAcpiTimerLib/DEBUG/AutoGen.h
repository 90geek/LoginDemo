/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_0C0AC8C1_E368_4d20_85FE_23EFB3DB094E
#define _AUTOGENH_0C0AC8C1_E368_4d20_85FE_23EFB3DB094E

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

RETURN_STATUS
EFIAPI
IntelIchAcpiTimerLibConstructor (
  VOID
  );


#ifdef __cplusplus
}
#endif

#endif
