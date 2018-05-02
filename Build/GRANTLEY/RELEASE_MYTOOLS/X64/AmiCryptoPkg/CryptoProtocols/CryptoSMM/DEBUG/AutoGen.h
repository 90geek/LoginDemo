/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_2AD511C7_1B60_4002_841D_2998DDC138EE
#define _AUTOGENH_2AD511C7_1B60_4002_841D_2998DDC138EE

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x2AD511C7, 0x1B60, 0x4002, {0x84, 0x1D, 0x29, 0x98, 0xDD, 0xC1, 0x38, 0xEE}}

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
extern EFI_GUID gSmmPerformanceProtocolGuid;
extern EFI_GUID gSmmPerformanceExProtocolGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

// Protocols
extern EFI_GUID gAmiDigitalSignatureProtocolGuid;
extern EFI_GUID gAmiSmmDigitalSignatureProtocolGuid;
extern EFI_GUID gEfiSmmBase2ProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiSmmDebugServiceProtocolGuid;
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
