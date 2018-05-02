/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_34CC6167_7AE7_403e_8AB2_23837F398A30
#define _AUTOGENH_34CC6167_7AE7_403e_8AB2_23837F398A30

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x34CC6167, 0x7AE7, 0x403e, {0x8A, 0xB2, 0x23, 0x83, 0x7F, 0x39, 0x8A, 0x30}}

// Guids
extern EFI_GUID gEfiPlatformInfoGuid;
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;

// PPIs
extern EFI_GUID gPeiSpiPpiGuid;
extern EFI_GUID gEfiPeiReadOnlyVariable2PpiGuid;
extern EFI_GUID gPeiSpiSoftStrapsPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;
extern EFI_GUID gAmiDebugServicePpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress  _PCD_SIZE_PcdPciExpressBaseAddress 
#define _PCD_VALUE_PcdPciExpressBaseAddress  0x80000000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUartDefaultBaudRate  1U
#define _PCD_GET_MODE_64_PcdUartDefaultBaudRate  LibPcdGet64(_PCD_TOKEN_PcdUartDefaultBaudRate)
#define _PCD_GET_MODE_SIZE_PcdUartDefaultBaudRate  LibPcdGetSize(_PCD_TOKEN_PcdUartDefaultBaudRate)
#define _PCD_SET_MODE_64_PcdUartDefaultBaudRate(Value)  LibPcdSet64(_PCD_TOKEN_PcdUartDefaultBaudRate, (Value))
#define _PCD_SET_MODE_64_S_PcdUartDefaultBaudRate(Value)  LibPcdSet64S(_PCD_TOKEN_PcdUartDefaultBaudRate, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
PlatformInfoInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );





#ifdef __cplusplus
}
#endif

#endif
