/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_F3B38282_B951_4e2a_8DF5_DE01FC527AE4
#define _AUTOGENH_F3B38282_B951_4e2a_8DF5_DE01FC527AE4

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xF3B38282, 0xB951, 0x4e2a, {0x8D, 0xF5, 0xDE, 0x01, 0xFC, 0x52, 0x7A, 0xE4}}

// Guids
extern EFI_GUID gEfiSetupVariableGuid;
extern EFI_GUID gEfiPchTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiSmmBase2ProtocolGuid;
extern EFI_GUID gEfiSmmSxDispatch2ProtocolGuid;
extern EFI_GUID gAmiSmmDebugServiceProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdWakeOnRTCS5  57U
#define _PCD_GET_MODE_BOOL_PcdWakeOnRTCS5  LibPcdGetBool(_PCD_TOKEN_PcdWakeOnRTCS5)
#define _PCD_GET_MODE_SIZE_PcdWakeOnRTCS5  LibPcdGetSize(_PCD_TOKEN_PcdWakeOnRTCS5)
#define _PCD_SET_MODE_BOOL_PcdWakeOnRTCS5(Value)  LibPcdSetBool(_PCD_TOKEN_PcdWakeOnRTCS5, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdWakeOnRTCS5(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdWakeOnRTCS5, (Value))

#define _PCD_TOKEN_PcdRtcWakeupTimeHour  58U
#define _PCD_GET_MODE_8_PcdRtcWakeupTimeHour  LibPcdGet8(_PCD_TOKEN_PcdRtcWakeupTimeHour)
#define _PCD_GET_MODE_SIZE_PcdRtcWakeupTimeHour  LibPcdGetSize(_PCD_TOKEN_PcdRtcWakeupTimeHour)
#define _PCD_SET_MODE_8_PcdRtcWakeupTimeHour(Value)  LibPcdSet8(_PCD_TOKEN_PcdRtcWakeupTimeHour, (Value))
#define _PCD_SET_MODE_8_S_PcdRtcWakeupTimeHour(Value)  LibPcdSet8S(_PCD_TOKEN_PcdRtcWakeupTimeHour, (Value))

#define _PCD_TOKEN_PcdRtcWakeupTimeMinute  59U
#define _PCD_GET_MODE_8_PcdRtcWakeupTimeMinute  LibPcdGet8(_PCD_TOKEN_PcdRtcWakeupTimeMinute)
#define _PCD_GET_MODE_SIZE_PcdRtcWakeupTimeMinute  LibPcdGetSize(_PCD_TOKEN_PcdRtcWakeupTimeMinute)
#define _PCD_SET_MODE_8_PcdRtcWakeupTimeMinute(Value)  LibPcdSet8(_PCD_TOKEN_PcdRtcWakeupTimeMinute, (Value))
#define _PCD_SET_MODE_8_S_PcdRtcWakeupTimeMinute(Value)  LibPcdSet8S(_PCD_TOKEN_PcdRtcWakeupTimeMinute, (Value))

#define _PCD_TOKEN_PcdRtcWakeupTimeSecond  60U
#define _PCD_GET_MODE_8_PcdRtcWakeupTimeSecond  LibPcdGet8(_PCD_TOKEN_PcdRtcWakeupTimeSecond)
#define _PCD_GET_MODE_SIZE_PcdRtcWakeupTimeSecond  LibPcdGetSize(_PCD_TOKEN_PcdRtcWakeupTimeSecond)
#define _PCD_SET_MODE_8_PcdRtcWakeupTimeSecond(Value)  LibPcdSet8(_PCD_TOKEN_PcdRtcWakeupTimeSecond, (Value))
#define _PCD_SET_MODE_8_S_PcdRtcWakeupTimeSecond(Value)  LibPcdSet8S(_PCD_TOKEN_PcdRtcWakeupTimeSecond, (Value))

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InitializeRtcWakeup (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
