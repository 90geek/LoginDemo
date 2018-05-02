//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file IpmiBmc.h
    IPMI BMC Controller functions.

**/

#ifndef _EFI_IPMI_BMC_H_
#define _EFI_IPMI_BMC_H_

//-----------------------------------------------------------------------
#include "Token.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TimerLib.h>

#include <Protocol/IPMITransportProtocol.h>
#include <Protocol/IPMISelfTestLogProtocol.h>
#include <Include/IpmiBmcCommon.h>
#include <Include/IpmiNetFnAppDefinitions.h>
#include <Include/IpmiNetFnStorageDefinitions.h>
#include <Include/IpmiNetFnSensorDefinitions.h>

//-----------------------------------------------------------------------

//
// Function Prototypes
//
BOOLEAN
IsLeapYear (
  IN UINT16   Year
  );

//
// Some Common Functions
//

EFI_STATUS
InitializeIpmiPhysicalLayerHook (
  VOID
  );

EFI_STATUS
SmbiosType38Support (
  VOID
  );

EFI_STATUS
SpmiSupport (
  VOID
  );

EFI_STATUS
IpmiCmosClear (
  VOID
  );

//
// Completion code related definitions
//
#define COMPLETION_CODE_SUCCESS                     0x00
#define COMPLETION_CODE_DEVICE_SPECIFIC_START       0x01
#define COMPLETION_CODE_DEVICE_SPECIFIC_END         0x7E
#define COMPLETION_CODE_COMMAND_SPECIFIC_START      0x80
#define COMPLETION_CODE_COMMAND_SPECIFIC_END        0xBE

//#define ERROR_COMPLETION_CODE(a) !( (a >= COMPLETION_CODE_SUCCESS) && (a <= COMPLETION_CODE_COMMAND_SPECIFIC_END) )

#define ERROR_COMPLETION_CODE(a)        !( (a == COMPLETION_CODE_SUCCESS) || \
                            ( (a >= COMPLETION_CODE_DEVICE_SPECIFIC_START) &&\
                                (a <= COMPLETION_CODE_DEVICE_SPECIFIC_END) )||\
                            ( (a >= COMPLETION_CODE_COMMAND_SPECIFIC_START) &&\
                                (a <= COMPLETION_CODE_COMMAND_SPECIFIC_END) ) )

//
// IPMI Instance signature
//
#define SM_IPMI_BMC_SIGNATURE SIGNATURE_32 ('i', 'p', 'm', 'i')

#define INSTANCE_FROM_EFI_SM_IPMI_BMC_THIS(a) \
  CR ( \
  a, \
  EFI_IPMI_BMC_INSTANCE_DATA, \
  IpmiTransport, \
  SM_IPMI_BMC_SIGNATURE \
  )

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
