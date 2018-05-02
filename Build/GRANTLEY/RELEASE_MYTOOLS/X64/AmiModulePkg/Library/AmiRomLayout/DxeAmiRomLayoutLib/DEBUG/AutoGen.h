/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_7A134533_0328_4AC0_9C22_91244C657197
#define _AUTOGENH_7A134533_0328_4AC0_9C22_91244C657197

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
DxeAmiRomLayoutLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
