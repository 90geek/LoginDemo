/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_899407D7_99FE_43d8_9A21_79EC328CAC21
#define _AUTOGENH_899407D7_99FE_43d8_9A21_79EC328CAC21

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x899407D7, 0x99FE, 0x43d8, {0x9A, 0x21, 0x79, 0xEC, 0x32, 0x8C, 0xAC, 0x21}}

// Guids
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gAmiTseSetupEnterGuid;
extern EFI_GUID gAmiTseOemTSEVarGuid;
extern EFI_GUID gEfiMemoryMapGuid;
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
extern EFI_GUID gAmiGlobalVariableGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gEfiHobListGuid;

// Protocols
extern EFI_GUID gEfiHiiPackageListProtocolGuid;
extern EFI_GUID gEfiHiiStringProtocolGuid;
extern EFI_GUID gEfiHiiDatabaseProtocolGuid;
extern EFI_GUID gEfiLoadedImageDevicePathProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiHiiConfigAccessProtocolGuid;
extern EFI_GUID gEfiHiiConfigRoutingProtocolGuid;
extern EFI_GUID gEfiGraphicsOutputProtocolGuid;
extern EFI_GUID gAmiNvmeControllerProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gEfiPciIoProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gEfiHiiFontProtocolGuid;
extern EFI_GUID gEfiUgaDrawProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiDriverConfigurationProtocolGuid;
extern EFI_GUID gEfiDriverConfiguration2ProtocolGuid;
extern EFI_GUID gEfiDriverDiagnosticsProtocolGuid;
extern EFI_GUID gEfiDriverDiagnostics2ProtocolGuid;
extern EFI_GUID gEfiHiiImageProtocolGuid;
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
SetupEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );



#include "SetupStrDefs.h"


#ifdef __cplusplus
}
#endif

#endif
