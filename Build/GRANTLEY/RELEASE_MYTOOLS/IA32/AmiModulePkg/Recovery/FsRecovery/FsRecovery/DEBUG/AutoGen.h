/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_7ecd9c20_68b9_4a6f_b515_d64ff500b109
#define _AUTOGENH_7ecd9c20_68b9_4a6f_b515_d64ff500b109

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x7ecd9c20, 0x68b9, 0x4a6f, {0xb5, 0x15, 0xd6, 0x4f, 0xf5, 0x00, 0xb1, 0x09}}

// Guids
extern EFI_GUID gBlockDeviceCapsuleGuid;
extern EFI_GUID gAmiModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiHobMemoryAllocStackGuid;
extern EFI_GUID gEfiHobMemoryAllocBspStoreGuid;
extern EFI_GUID gEfiHobMemoryAllocModuleGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiFirmwareFileSystem2Guid;
extern EFI_GUID gAmiGlobalVariableGuid;

// PPIs
extern EFI_GUID gEfiPeiDeviceRecoveryModulePpiGuid;
extern EFI_GUID gEfiPeiVirtualBlockIoPpiGuid;
extern EFI_GUID gAmiDebugServicePpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfoPpiGuid;
extern EFI_GUID gEfiPeiFirmwareVolumeInfo2PpiGuid;
extern EFI_GUID gPcdPpiGuid;
extern EFI_GUID gEfiPeiPcdPpiGuid;
extern EFI_GUID gGetPcdInfoPpiGuid;
extern EFI_GUID gEfiGetPcdInfoPpiGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdRecoveryImageSize  140U
#define _PCD_SIZE_PcdRecoveryImageSize 4
#define _PCD_GET_MODE_SIZE_PcdRecoveryImageSize  _PCD_SIZE_PcdRecoveryImageSize 
#define _PCD_VALUE_PcdRecoveryImageSize  0x800000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdRecoveryImageSize;
#define _PCD_GET_MODE_32_PcdRecoveryImageSize  _gPcd_FixedAtBuild_PcdRecoveryImageSize
//#define _PCD_SET_MODE_32_PcdRecoveryImageSize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdCdRecoverySupport  141U
#define _PCD_SIZE_PcdCdRecoverySupport 1
#define _PCD_GET_MODE_SIZE_PcdCdRecoverySupport  _PCD_SIZE_PcdCdRecoverySupport 
#define _PCD_VALUE_PcdCdRecoverySupport  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdCdRecoverySupport;
#define _PCD_GET_MODE_BOOL_PcdCdRecoverySupport  _gPcd_FixedAtBuild_PcdCdRecoverySupport
//#define _PCD_SET_MODE_BOOL_PcdCdRecoverySupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdFatRecoverySupport  142U
#define _PCD_SIZE_PcdFatRecoverySupport 1
#define _PCD_GET_MODE_SIZE_PcdFatRecoverySupport  _PCD_SIZE_PcdFatRecoverySupport 
#define _PCD_VALUE_PcdFatRecoverySupport  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdFatRecoverySupport;
#define _PCD_GET_MODE_BOOL_PcdFatRecoverySupport  _gPcd_FixedAtBuild_PcdFatRecoverySupport
//#define _PCD_SET_MODE_BOOL_PcdFatRecoverySupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdRecoveryImageName  143U
#define _PCD_VALUE_PcdRecoveryImageName  _gPcd_FixedAtBuild_PcdRecoveryImageName
extern const UINT8 _gPcd_FixedAtBuild_PcdRecoveryImageName[13];
#define _PCD_GET_MODE_PTR_PcdRecoveryImageName  _gPcd_FixedAtBuild_PcdRecoveryImageName
#define _PCD_SIZE_PcdRecoveryImageName 13
#define _PCD_GET_MODE_SIZE_PcdRecoveryImageName  _PCD_SIZE_PcdRecoveryImageName 
//#define _PCD_SET_MODE_PTR_PcdRecoveryImageName  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
FsRecoveryPeimEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );





#ifdef __cplusplus
}
#endif

#endif
