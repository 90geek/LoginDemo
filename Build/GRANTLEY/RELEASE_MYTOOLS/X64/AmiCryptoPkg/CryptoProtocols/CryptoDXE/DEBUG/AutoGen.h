/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_77EB6C06_FD48_488B_A1B3_AE0A70801369
#define _AUTOGENH_77EB6C06_FD48_488B_A1B3_AE0A70801369

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x77EB6C06, 0xFD48, 0x488B, {0xA1, 0xB3, 0xAE, 0x0A, 0x70, 0x80, 0x13, 0x69}}

// Guids
extern EFI_GUID gEfiCertX509Guid;
extern EFI_GUID gEfiCertSha256Guid;
extern EFI_GUID gEfiCertRsa2048Guid;
extern EFI_GUID gEfiHashAlgorithmSha1Guid;
extern EFI_GUID gEfiHashAlgorithmSha256Guid;
extern EFI_GUID gEfiHashAlgorithmSha384Guid;
extern EFI_GUID gEfiHashAlgorithmSha512Guid;
extern EFI_GUID gEfiHashAlgorithmSha1NoPadGuid;
extern EFI_GUID gEfiHashAlgorithmSha256NoPadGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

// Protocols
extern EFI_GUID gAmiDigitalSignatureProtocolGuid;
extern EFI_GUID gAmiSmmDigitalSignatureProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
CryptoDxe_Init (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
