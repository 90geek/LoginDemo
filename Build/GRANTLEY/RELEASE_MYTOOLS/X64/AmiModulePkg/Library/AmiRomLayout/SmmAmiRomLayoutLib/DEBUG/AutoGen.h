/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_4372B10C_D641_4EE4_8214_D3104A524693
#define _AUTOGENH_4372B10C_D641_4EE4_8214_D3104A524693

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern EFI_GUID gAmiRomLayoutFfsFileGuid;
extern EFI_GUID gAmiRomLayoutGuid;

EFI_STATUS
EFIAPI
SmmAmiRomLayoutLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
