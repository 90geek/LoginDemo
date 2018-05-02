/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_FD236AE7_0791_48c4_B29E_29BDEEE1A838
#define _AUTOGENH_FD236AE7_0791_48c4_B29E_29BDEEE1A838

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xFD236AE7, 0x0791, 0x48c4, {0xB2, 0x9E, 0x29, 0xBD, 0xEE, 0xE1, 0xA8, 0x38}}

// Guids
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;
extern EFI_GUID gChipsetInitInfoHobGuid;

// PPIs
extern EFI_GUID gPchInitPpiGuid;
extern EFI_GUID gPchPlatformPolicyPpiGuid;
extern EFI_GUID gPchUsbPolicyPpiGuid;
extern EFI_GUID gPchPeiInitDonePpiGuid;
extern EFI_GUID gEfiPeiMemoryDiscoveredPpiGuid;
extern EFI_GUID gWdtPpiGuid;
extern EFI_GUID gPchDmiTcVcMapPpiGuid;
extern EFI_GUID gPchResetPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;
extern EFI_GUID gAmiDebugServicePpiGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress  _PCD_SIZE_PcdPciExpressBaseAddress 
#define _PCD_VALUE_PcdPciExpressBaseAddress  0x80000000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdPchSataInitReg78Data  2U
#define _PCD_GET_MODE_32_PcdPchSataInitReg78Data  LibPcdGet32(_PCD_TOKEN_PcdPchSataInitReg78Data)
#define _PCD_GET_MODE_SIZE_PcdPchSataInitReg78Data  LibPcdGetSize(_PCD_TOKEN_PcdPchSataInitReg78Data)
#define _PCD_SET_MODE_32_PcdPchSataInitReg78Data(Value)  LibPcdSet32(_PCD_TOKEN_PcdPchSataInitReg78Data, (Value))
#define _PCD_SET_MODE_32_S_PcdPchSataInitReg78Data(Value)  LibPcdSet32S(_PCD_TOKEN_PcdPchSataInitReg78Data, (Value))

#define _PCD_TOKEN_PcdPchSataInitReg88Data  3U
#define _PCD_GET_MODE_32_PcdPchSataInitReg88Data  LibPcdGet32(_PCD_TOKEN_PcdPchSataInitReg88Data)
#define _PCD_GET_MODE_SIZE_PcdPchSataInitReg88Data  LibPcdGetSize(_PCD_TOKEN_PcdPchSataInitReg88Data)
#define _PCD_SET_MODE_32_PcdPchSataInitReg88Data(Value)  LibPcdSet32(_PCD_TOKEN_PcdPchSataInitReg88Data, (Value))
#define _PCD_SET_MODE_32_S_PcdPchSataInitReg88Data(Value)  LibPcdSet32S(_PCD_TOKEN_PcdPchSataInitReg88Data, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InstallPchInitPpi (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );





#ifdef __cplusplus
}
#endif

#endif
