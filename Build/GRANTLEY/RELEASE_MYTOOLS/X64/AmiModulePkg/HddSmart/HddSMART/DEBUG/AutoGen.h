/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_D57C852E_809F_45cf_A377_D77BC0CB78EE
#define _AUTOGENH_D57C852E_809F_45cf_A377_D77BC0CB78EE

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xD57C852E, 0x809F, 0x45cf, {0xA3, 0x77, 0xD7, 0x7B, 0xC0, 0xCB, 0x78, 0xEE}}

// Guids
extern EFI_GUID gAmiModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

// Protocols
extern EFI_GUID gAmiHddSmartInitProtocolGuid;
extern EFI_GUID gAmiHddSmartProtocolGuid;
extern EFI_GUID gAmiPostManagerProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiHiiFontProtocolGuid;
extern EFI_GUID gEfiHiiStringProtocolGuid;
extern EFI_GUID gEfiHiiImageProtocolGuid;
extern EFI_GUID gEfiHiiDatabaseProtocolGuid;
extern EFI_GUID gEfiHiiConfigRoutingProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gEfiGraphicsOutputProtocolGuid;
extern EFI_GUID gEfiUgaDrawProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gEfiDriverConfigurationProtocolGuid;
extern EFI_GUID gEfiDriverConfiguration2ProtocolGuid;
extern EFI_GUID gEfiDriverDiagnosticsProtocolGuid;
extern EFI_GUID gEfiDriverDiagnostics2ProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiFormBrowser2ProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_DiskController  61U
#define _PCD_GET_MODE_8_DiskController  LibPcdGet8(_PCD_TOKEN_DiskController)
#define _PCD_GET_MODE_SIZE_DiskController  LibPcdGetSize(_PCD_TOKEN_DiskController)
#define _PCD_SET_MODE_8_DiskController(Value)  LibPcdSet8(_PCD_TOKEN_DiskController, (Value))
#define _PCD_SET_MODE_8_S_DiskController(Value)  LibPcdSet8S(_PCD_TOKEN_DiskController, (Value))

#define _PCD_TOKEN_PchDiskError  62U
#define _PCD_GET_MODE_16_PchDiskError  LibPcdGet16(_PCD_TOKEN_PchDiskError)
#define _PCD_GET_MODE_SIZE_PchDiskError  LibPcdGetSize(_PCD_TOKEN_PchDiskError)
#define _PCD_SET_MODE_16_PchDiskError(Value)  LibPcdSet16(_PCD_TOKEN_PchDiskError, (Value))
#define _PCD_SET_MODE_16_S_PchDiskError(Value)  LibPcdSet16S(_PCD_TOKEN_PchDiskError, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
HddSmartEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );



#include "HddSmartStrDefs.h"


#ifdef __cplusplus
}
#endif

#endif
