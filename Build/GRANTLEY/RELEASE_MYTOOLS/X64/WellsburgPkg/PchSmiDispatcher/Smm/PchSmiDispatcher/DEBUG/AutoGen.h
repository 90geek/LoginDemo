/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_B0D6ED53_B844_43f5_BD2F_61095264E77E
#define _AUTOGENH_B0D6ED53_B844_43f5_BD2F_61095264E77E

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xB0D6ED53, 0xB844, 0x43f5, {0xBD, 0x2F, 0x61, 0x09, 0x52, 0x64, 0xE7, 0x7E}}

// Guids
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gEfiStatusCodeSpecificDataGuid;
extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;
extern EFI_GUID gPchOemSmmGuid;

// Protocols
extern EFI_GUID gEfiPciRootBridgeIoProtocolGuid;
extern EFI_GUID gEfiSmmGpiDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmSxDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmSwDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmIchnDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmUsbDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmIchnDispatch2ExProtocolGuid;
extern EFI_GUID gEfiSmmPowerButtonDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmPeriodicTimerDispatch2ProtocolGuid;
extern EFI_GUID gEfiSmmBase2ProtocolGuid;
extern EFI_GUID gEfiSmmCpuProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiSmmDebugServiceProtocolGuid;
extern EFI_GUID gEfiSmmAccess2ProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiSmmStatusCodeProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdPciExpressBaseAddress  105U
#define _PCD_SIZE_PcdPciExpressBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdPciExpressBaseAddress  _PCD_SIZE_PcdPciExpressBaseAddress 
#define _PCD_VALUE_PcdPciExpressBaseAddress  0x80000000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress;
#define _PCD_GET_MODE_64_PcdPciExpressBaseAddress  _gPcd_FixedAtBuild_PcdPciExpressBaseAddress
//#define _PCD_SET_MODE_64_PcdPciExpressBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdProgressCodeS3SuspendEnd  239U
#define _PCD_SIZE_PcdProgressCodeS3SuspendEnd 4
#define _PCD_GET_MODE_SIZE_PcdProgressCodeS3SuspendEnd  _PCD_SIZE_PcdProgressCodeS3SuspendEnd 
#define _PCD_VALUE_PcdProgressCodeS3SuspendEnd  0x03078001U
extern const  UINT32  _gPcd_FixedAtBuild_PcdProgressCodeS3SuspendEnd;
#define _PCD_GET_MODE_32_PcdProgressCodeS3SuspendEnd  _gPcd_FixedAtBuild_PcdProgressCodeS3SuspendEnd
//#define _PCD_SET_MODE_32_PcdProgressCodeS3SuspendEnd  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdProgressCodeS3SuspendStart  240U
#define _PCD_SIZE_PcdProgressCodeS3SuspendStart 4
#define _PCD_GET_MODE_SIZE_PcdProgressCodeS3SuspendStart  _PCD_SIZE_PcdProgressCodeS3SuspendStart 
#define _PCD_VALUE_PcdProgressCodeS3SuspendStart  0x03078000U
extern const  UINT32  _gPcd_FixedAtBuild_PcdProgressCodeS3SuspendStart;
#define _PCD_GET_MODE_32_PcdProgressCodeS3SuspendStart  _gPcd_FixedAtBuild_PcdProgressCodeS3SuspendStart
//#define _PCD_SET_MODE_32_PcdProgressCodeS3SuspendStart  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdLpcGenPmConSwSmiRstl  241U
#define _PCD_SIZE_PcdLpcGenPmConSwSmiRstl 1
#define _PCD_GET_MODE_SIZE_PcdLpcGenPmConSwSmiRstl  _PCD_SIZE_PcdLpcGenPmConSwSmiRstl 
#define _PCD_VALUE_PcdLpcGenPmConSwSmiRstl  0x40U
extern const  UINT8  _gPcd_FixedAtBuild_PcdLpcGenPmConSwSmiRstl;
#define _PCD_GET_MODE_8_PcdLpcGenPmConSwSmiRstl  _gPcd_FixedAtBuild_PcdLpcGenPmConSwSmiRstl
//#define _PCD_SET_MODE_8_PcdLpcGenPmConSwSmiRstl  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InitializePchSmmDispatcher (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
