/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_AAECDC89_2A49_46f1_A163_F7979C039998
#define _AUTOGENH_AAECDC89_2A49_46f1_A163_F7979C039998

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Uefi.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xAAECDC89, 0x2A49, 0x46f1, {0xA1, 0x63, 0xF7, 0x97, 0x9C, 0x03, 0x99, 0x98}}

// Guids
extern EFI_GUID gEfiDiskInfoIdeInterfaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

// Protocols
extern EFI_GUID gAmiIdeBusInitProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiDiskInfoProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiBlockIoProtocolGuid;
extern EFI_GUID gAmiHddSecurityInitProtocolGuid;
extern EFI_GUID gAmiHddSecurityEndProtocolGuid;
extern EFI_GUID gAmiHddSecurityProtocolGuid;
extern EFI_GUID gAmiHddSmartInitProtocolGuid;
extern EFI_GUID gAmiHddSmartProtocolGuid;
extern EFI_GUID gAmiHddOpalSecInitProtocolGuid;
extern EFI_GUID gEfiStorageSecurityCommandProtocolGuid;
extern EFI_GUID gAmiAtaPassThruInitProtocolGuid;
extern EFI_GUID gAmiScsiPassThruInitProtocolGuid;
extern EFI_GUID gAmiPlatformIdeProtocolGuid;
extern EFI_GUID gEfiPciIoProtocolGuid;
extern EFI_GUID gAmiHddHpaProtocolGuid;
extern EFI_GUID gAmiHddPowerMgmtProtocolGuid;
extern EFI_GUID gAmiBlockIoWriteProtectionProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
IdeBusEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
