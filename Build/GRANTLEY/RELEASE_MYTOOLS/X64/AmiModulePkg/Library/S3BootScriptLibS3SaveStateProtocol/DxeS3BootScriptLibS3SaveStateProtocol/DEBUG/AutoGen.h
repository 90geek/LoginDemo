/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_9CB0F5CC_B0F3_4ADD_8583_3C8AF6C00DE0
#define _AUTOGENH_9CB0F5CC_B0F3_4ADD_8583_3C8AF6C00DE0

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Protocols
extern EFI_GUID gEfiS3SaveStateProtocolGuid;

EFI_STATUS
EFIAPI
DxeS3BootScriptLibS3SaveStateProtocolConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
