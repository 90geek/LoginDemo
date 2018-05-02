/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_D28D4CB5_DAFA_48BD_BB53_21818511732A
#define _AUTOGENH_D28D4CB5_DAFA_48BD_BB53_21818511732A

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern EFI_GUID gEfiGenericVariableGuid;
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gServerCommonTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiSpiProtocolGuid;
extern EFI_GUID gEfiPciRootBridgeIoProtocolGuid;

// PCD definitions
#define _PCD_TOKEN_PcdPchAcpiIoPortBaseAddress  94U
extern const UINT16 _gPcd_FixedAtBuild_PcdPchAcpiIoPortBaseAddress;
#define _PCD_GET_MODE_16_PcdPchAcpiIoPortBaseAddress  _gPcd_FixedAtBuild_PcdPchAcpiIoPortBaseAddress
//#define _PCD_SET_MODE_16_PcdPchAcpiIoPortBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_VALUE_PcdPchAcpiIoPortBaseAddress 0x0400
#define _PCD_SIZE_PcdPchAcpiIoPortBaseAddress 2
#define _PCD_GET_MODE_SIZE_PcdPchAcpiIoPortBaseAddress _PCD_SIZE_PcdPchAcpiIoPortBaseAddress
#define _PCD_TOKEN_PcdSocketBaseBusNumbers  84U
#define _PCD_GET_MODE_PTR_PcdSocketBaseBusNumbers  LibPcdGetPtr(_PCD_TOKEN_PcdSocketBaseBusNumbers)
#define _PCD_GET_MODE_SIZE_PcdSocketBaseBusNumbers  LibPcdGetSize(_PCD_TOKEN_PcdSocketBaseBusNumbers)
#define _PCD_SET_MODE_PTR_PcdSocketBaseBusNumbers(SizeOfBuffer, Buffer)  LibPcdSetPtr(_PCD_TOKEN_PcdSocketBaseBusNumbers, (SizeOfBuffer), (Buffer))
#define _PCD_SET_MODE_PTR_S_PcdSocketBaseBusNumbers(SizeOfBuffer, Buffer)  LibPcdSetPtrS(_PCD_TOKEN_PcdSocketBaseBusNumbers, (SizeOfBuffer), (Buffer))
#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
extern const UINT64 _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress _PCD_SIZE_PcdPciExpressBaseAddress

EFI_STATUS
EFIAPI
LtDxeLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
