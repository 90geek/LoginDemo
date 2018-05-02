/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_AA6FB263_6464_4073_AAE9_AC095A19DEA3
#define _AUTOGENH_AA6FB263_6464_4073_AAE9_AC095A19DEA3

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xAA6FB263, 0x6464, 0x4073, {0xAA, 0xE9, 0xAC, 0x09, 0x5A, 0x19, 0xDE, 0xA3}}

// Guids
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiWheaPcieErrorSectionGuid;
extern EFI_GUID gEfiWheaPlatformMemoryErrorSectionGuid;
extern EFI_GUID gEfiWheaPciDevErrorSectionGuid;
extern EFI_GUID gEfiWheaProcessorGenericErrorSectionGuid;
extern EFI_GUID gEfiWheaPlatformNonStandardErrorSectionGuid;
extern EFI_GUID gEfiSerialPortTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiWheaSupportProtocolGuid;
extern EFI_GUID gEfiSmmBase2ProtocolGuid;
extern EFI_GUID gEfiSmmSwDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmRuntimeProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiSmmDebugServiceProtocolGuid;
extern EFI_GUID gEfiWheaPlatformSupportProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InstallWheaPlatform (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
