/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_995A438A_1331_480C_A0FE_FD129A902496
#define _AUTOGENH_995A438A_1331_480C_A0FE_FD129A902496

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern EFI_GUID gAmiModulePkgTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gEfiPciIoProtocolGuid;
extern EFI_GUID gEfiBlockIoProtocolGuid;
extern EFI_GUID gEfiBlockIo2ProtocolGuid;
extern EFI_GUID gEfiLoadFileProtocolGuid;
extern EFI_GUID gEfiDxeSmmReadyToLockProtocolGuid;

// PCD definitions
#define _PCD_TOKEN_AmiPcdLoadUnsignedEmbeddedApplications  169U
extern const BOOLEAN _gPcd_FixedAtBuild_AmiPcdLoadUnsignedEmbeddedApplications;
#define _PCD_GET_MODE_BOOL_AmiPcdLoadUnsignedEmbeddedApplications  _gPcd_FixedAtBuild_AmiPcdLoadUnsignedEmbeddedApplications
//#define _PCD_SET_MODE_BOOL_AmiPcdLoadUnsignedEmbeddedApplications  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_AmiPcdLoadUnsignedEmbeddedApplications 1
#define _PCD_GET_MODE_SIZE_AmiPcdLoadUnsignedEmbeddedApplications _PCD_SIZE_AmiPcdLoadUnsignedEmbeddedApplications

EFI_STATUS
EFIAPI
AmiImageTypeLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
