/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_8F5A2E02_538C_4D59_B920_C4786ACBC552
#define _AUTOGENH_8F5A2E02_538C_4D59_B920_C4786ACBC552

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x8F5A2E02, 0x538C, 0x4D59, {0xB9, 0x20, 0xC4, 0x78, 0x6A, 0xCB, 0xC5, 0x52}}

// Guids
extern EFI_GUID gEfiDiskInfoIdeInterfaceGuid;
extern EFI_GUID gEfiDiskInfoAhciInterfaceGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gAmiModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

// Protocols
extern EFI_GUID gEfiPciIoProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiIdeControllerInitProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiBlockIoProtocolGuid;
extern EFI_GUID gEfiDiskInfoProtocolGuid;
extern EFI_GUID gAmiAhciBusProtocolGuid;
extern EFI_GUID gAint13ProtocolGuid;
extern EFI_GUID gAmiAhciPlatformPolicyProtocolGuid;
extern EFI_GUID gAmiIdeBusInitProtocolGuid;
extern EFI_GUID gEfiStorageSecurityCommandProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gAmiHddSecurityProtocolGuid;
extern EFI_GUID gAmiHddSecurityInitProtocolGuid;
extern EFI_GUID gAmiHddSecurityEndProtocolGuid;
extern EFI_GUID gAmiHddSmartProtocolGuid;
extern EFI_GUID gAmiHddSmartInitProtocolGuid;
extern EFI_GUID gAmiHddOpalSecInitProtocolGuid;
extern EFI_GUID gAmiAtaPassThruInitProtocolGuid;
extern EFI_GUID gAmiScsiPassThruInitProtocolGuid;
extern EFI_GUID gAmiBlockIoWriteProtectionProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_DiskController  61U
#define _PCD_GET_MODE_8_DiskController  LibPcdGet8(_PCD_TOKEN_DiskController)
#define _PCD_GET_MODE_SIZE_DiskController  LibPcdGetSize(_PCD_TOKEN_DiskController)
#define _PCD_SET_MODE_8_DiskController(Value)  LibPcdSet8(_PCD_TOKEN_DiskController, (Value))
#define _PCD_SET_MODE_8_S_DiskController(Value)  LibPcdSet8S(_PCD_TOKEN_DiskController, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
AhciBusEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
