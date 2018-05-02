/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_041bf780_dc3e_49ab_1111_4b8607540000
#define _AUTOGENH_041bf780_dc3e_49ab_1111_4b8607540000

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern EFI_GUID gEfiCpuTokenSpaceGuid;

// PCD definitions
#define _PCD_TOKEN_PcdCpuCallbackSignal  39U
#define _PCD_GET_MODE_8_PcdCpuCallbackSignal  LibPcdGet8(_PCD_TOKEN_PcdCpuCallbackSignal)
#define _PCD_GET_MODE_SIZE_PcdCpuCallbackSignal  LibPcdGetSize(_PCD_TOKEN_PcdCpuCallbackSignal)
#define _PCD_SET_MODE_8_PcdCpuCallbackSignal(Value)  LibPcdSet8(_PCD_TOKEN_PcdCpuCallbackSignal, (Value))
#define _PCD_SET_MODE_8_S_PcdCpuCallbackSignal(Value)  LibPcdSet8S(_PCD_TOKEN_PcdCpuCallbackSignal, (Value))
#define _PCD_TOKEN_PcdCpuConfigContextBuffer  38U
#define _PCD_GET_MODE_64_PcdCpuConfigContextBuffer  LibPcdGet64(_PCD_TOKEN_PcdCpuConfigContextBuffer)
#define _PCD_GET_MODE_SIZE_PcdCpuConfigContextBuffer  LibPcdGetSize(_PCD_TOKEN_PcdCpuConfigContextBuffer)
#define _PCD_SET_MODE_64_PcdCpuConfigContextBuffer(Value)  LibPcdSet64(_PCD_TOKEN_PcdCpuConfigContextBuffer, (Value))
#define _PCD_SET_MODE_64_S_PcdCpuConfigContextBuffer(Value)  LibPcdSet64S(_PCD_TOKEN_PcdCpuConfigContextBuffer, (Value))

EFI_STATUS
EFIAPI
CpuConfigLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
