/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_E99342E1_B01B_4f0f_A4A5_73D64A94EA92
#define _AUTOGENH_E99342E1_B01B_4f0f_A4A5_73D64A94EA92

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern EFI_GUID gAmiIpmiPkgTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiDxeIpmiTransportProtocolGuid;
extern EFI_GUID gEfiDxeIpmiUsbTransportProtocolGuid;

// PCD definitions
#define _PCD_TOKEN_BulkDataTransferInterfaceType  75U
#define _PCD_GET_MODE_8_BulkDataTransferInterfaceType  LibPcdGet8(_PCD_TOKEN_BulkDataTransferInterfaceType)
#define _PCD_GET_MODE_SIZE_BulkDataTransferInterfaceType  LibPcdGetSize(_PCD_TOKEN_BulkDataTransferInterfaceType)
#define _PCD_SET_MODE_8_BulkDataTransferInterfaceType(Value)  LibPcdSet8(_PCD_TOKEN_BulkDataTransferInterfaceType, (Value))
#define _PCD_SET_MODE_8_S_BulkDataTransferInterfaceType(Value)  LibPcdSet8S(_PCD_TOKEN_BulkDataTransferInterfaceType, (Value))

EFI_STATUS
EFIAPI
IpmiInterfaceLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


#ifdef __cplusplus
}
#endif

#endif
