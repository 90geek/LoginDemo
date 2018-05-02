/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_B1DA0ADF_4F77_4070_A88E_BFFE1C60529A
#define _AUTOGENH_B1DA0ADF_4F77_4070_A88E_BFFE1C60529A

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xB1DA0ADF, 0x4F77, 0x4070, {0xA8, 0x8E, 0xBF, 0xFE, 0x1C, 0x60, 0x52, 0x9A}}

// Guids
extern EFI_GUID gAmiTseSetupEnterGuid;
extern EFI_GUID gAmiTseAfterFirstBootOptionGuid;
extern EFI_GUID gAmiTseEventBeforeBootGuid;
extern EFI_GUID gAmiTseBootOrderChangeGuid;
extern EFI_GUID gAmiTseNVRAMUpdateGuid;
extern EFI_GUID gAmiTsePasswordPromptEnterGuid;
extern EFI_GUID gAmiTsePasswordPromptExitGuid;
extern EFI_GUID gAmiTseUserPasswordValidGuid;
extern EFI_GUID gAmiTseAdminPasswordValidGuid;
extern EFI_GUID gAmiTseInvalidPasswordGuid;
extern EFI_GUID gAmiTseBeforeTimeOutGuid;
extern EFI_GUID gAmiTseAfterTimeOutGuid;
extern EFI_GUID gAmiTseOemTSEVarGuid;
extern EFI_GUID gAmiTseOemPortingVar1Guid;
extern EFI_GUID gAmiTseOemPortingVar2Guid;
extern EFI_GUID gAmiTseOemPortingVar3Guid;
extern EFI_GUID gAmiTseOemPortingVar4Guid;
extern EFI_GUID gAmiTseOemPortingVar5Guid;
extern EFI_GUID gAmiTseOemPortingGuid1;
extern EFI_GUID gAmiTseOemPortingGuid2;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiIpmiBootGuid;
extern EFI_GUID gEfiServerMgmtSetupVariableGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gPerformanceExProtocolGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gAmiGlobalVariableGuid;
extern EFI_GUID gEfiConsoleOutDeviceGuid;

// Protocols
extern EFI_GUID gEfiConsoleControlProtocolGuid;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gEfiUnicodeCollation2ProtocolGuid;
extern EFI_GUID gEfiUnicodeCollationProtocolGuid;
extern EFI_GUID gEfiOEMBadgingProtocolGuid;
extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;
extern EFI_GUID gEfiBlockIoProtocolGuid;
extern EFI_GUID gEfiLegacyBiosProtocolGuid;
extern EFI_GUID gEfiFirmwareVolumeProtocolGuid;
extern EFI_GUID gEfiSimpleTextInProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gAmiPostManagerProtocolGuid;
extern EFI_GUID gTSEInvalidateBgrtStatusProtocolGuid;
extern EFI_GUID gEsaInterfacesForTseProtocolGuid;
extern EFI_GUID gEfiHiiDatabaseProtocolGuid;
extern EFI_GUID gEfiHiiStringProtocolGuid;
extern EFI_GUID gEfiHiiConfigRoutingProtocolGuid;
extern EFI_GUID gEfiFormBrowser2ProtocolGuid;
extern EFI_GUID gOpromStartEndProtocolGuid;
extern EFI_GUID gAmiLegacyBootProtocolGuid;
extern EFI_GUID gEfiSmFrbProtocolGuid;
extern EFI_GUID gEfiDxeIpmiTransportProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiStatusCodeRuntimeProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gEfiGraphicsOutputProtocolGuid;
extern EFI_GUID gEfiHiiFontProtocolGuid;
extern EFI_GUID gEfiUgaDrawProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gEfiDriverConfigurationProtocolGuid;
extern EFI_GUID gEfiDriverConfiguration2ProtocolGuid;
extern EFI_GUID gEfiDriverDiagnosticsProtocolGuid;
extern EFI_GUID gEfiDriverDiagnostics2ProtocolGuid;
extern EFI_GUID gEfiUsbIoProtocolGuid;
extern EFI_GUID gEfiDiskIoProtocolGuid;
extern EFI_GUID gEfiDriverHealthProtocolGuid;
extern EFI_GUID gAmiAhciBusProtocolGuid;
extern EFI_GUID gEfiDiskInfoProtocolGuid;
extern EFI_GUID gAmiHddSecurityEndProtocolGuid;
extern EFI_GUID gAmiHddSecurityProtocolGuid;
extern EFI_GUID gAmiHddPasswordVerifiedGuid;

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
MiniSetupApplication (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );



#include "AMITSEStrDefs.h"


#ifdef __cplusplus
}
#endif

#endif
