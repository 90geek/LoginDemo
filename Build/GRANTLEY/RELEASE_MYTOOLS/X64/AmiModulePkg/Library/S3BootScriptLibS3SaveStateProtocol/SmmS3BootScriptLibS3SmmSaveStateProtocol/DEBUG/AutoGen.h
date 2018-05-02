/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_2E6FECFB_B0E1_4580_8966_29178C72022E
#define _AUTOGENH_2E6FECFB_B0E1_4580_8966_29178C72022E

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Protocols
extern EFI_GUID gEfiS3SmmSaveStateProtocolGuid;

EFI_STATUS
EFIAPI
SmmS3BootScriptLibS3SmmSaveStateProtocolConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
