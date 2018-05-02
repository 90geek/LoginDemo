/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_15B26F43_A389_4bae_BDE3_4BB0719B7D4F
#define _AUTOGENH_15B26F43_A389_4bae_BDE3_4BB0719B7D4F

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern GUID gEfiSerialPortTokenSpaceGuid;
extern GUID gEfiMdePkgTokenSpaceGuid;

// PCD definitions
#define _PCD_TOKEN_PcdSerialBoudRate  125U
extern const UINT32 _gPcd_FixedAtBuild_PcdSerialBoudRate;
#define _PCD_GET_MODE_32_PcdSerialBoudRate  _gPcd_FixedAtBuild_PcdSerialBoudRate
//#define _PCD_SET_MODE_32_PcdSerialBoudRate  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_VALUE_PcdSerialBoudRate 115200
#define _PCD_SIZE_PcdSerialBoudRate 4
#define _PCD_GET_MODE_SIZE_PcdSerialBoudRate _PCD_SIZE_PcdSerialBoudRate
#define _PCD_TOKEN_PcdSerialRegisterBase  126U
extern const UINT64 _gPcd_FixedAtBuild_PcdSerialRegisterBase;
#define _PCD_GET_MODE_64_PcdSerialRegisterBase  _gPcd_FixedAtBuild_PcdSerialRegisterBase
//#define _PCD_SET_MODE_64_PcdSerialRegisterBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_VALUE_PcdSerialRegisterBase 0x3f8
#define _PCD_SIZE_PcdSerialRegisterBase 8
#define _PCD_GET_MODE_SIZE_PcdSerialRegisterBase _PCD_SIZE_PcdSerialRegisterBase
#define _PCD_TOKEN_PcdUartDefaultBaudRate  1U
#define _PCD_GET_MODE_64_PcdUartDefaultBaudRate  LibPcdGet64(_PCD_TOKEN_PcdUartDefaultBaudRate)
#define _PCD_GET_MODE_SIZE_PcdUartDefaultBaudRate  LibPcdGetSize(_PCD_TOKEN_PcdUartDefaultBaudRate)
#define _PCD_SET_MODE_64_PcdUartDefaultBaudRate(Value)  LibPcdSet64(_PCD_TOKEN_PcdUartDefaultBaudRate, (Value))
#define _PCD_SET_MODE_64_S_PcdUartDefaultBaudRate(Value)  LibPcdSet64S(_PCD_TOKEN_PcdUartDefaultBaudRate, (Value))


#ifdef __cplusplus
}
#endif

#endif
