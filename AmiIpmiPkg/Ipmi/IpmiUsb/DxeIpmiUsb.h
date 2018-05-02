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

/** @file DxeIpmiUsb.h
    This file contains definitions and includes for IpmiUsb.

**/

#ifndef _EFI_DXE_IPMI_USB_H
#define _EFI_DXE_IPMI_USB_H

//----------------------------------------------------------------------

#include "Token.h"
#include <Protocol/IpmiUsbTransportProtocol.h>
#include <Include/IpmiUsbDxe.h>
#include <Protocol/IPMITransportProtocol.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/UsbIo.h>
#include <Library/TimerLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Include/IpmiNetFnAppDefinitions.h>

//----------------------------------------------------------------------

//
// Macro definition
//
#define IsBulkInEndPoint(EndPoint)  ( (EndPoint & BIT7) != 0x00 )
#define IsBulkOutEndPoint(EndPoint) ( (EndPoint & BIT7) == 0x00 )

//
// USB macros
//
#define USB_ENDPOINT_BULK       0x02
#define USB_REQ_TYPE_CLASS      0x20  //  01 = Class specific
#define USB_REQ_TYPE_INTERFACE  0x01  //  00001 = Interface
#define USB_REQ_TYPE_ENDPOINT   0x02  //  00010 = End point
#define USB_DEV_CLEAR_FEATURE   0x01

#define EfiUsbEndpointHalt      0x00

//
// Function Prototypes
//

EFI_STATUS
EfiSendIpmiUsbCommand (
  IN  IPMI_USB_TRANSPORT        *This,
  IN  UINT8                     NetFunction,
  IN  UINT8                     Lun,
  IN  UINT8                     Command,
  IN  UINT8                     *CommandData,
  IN  UINT8                     CommandDataSize,
  OUT UINT8                     *ResponseData,
  OUT UINT8                     *ResponseDataSize );

EFI_STATUS
EfiSendOemIpmiUsbCommand (
  IN EFI_IPMI_USB_TRANSPORT         *This,
  IN UINT8                          NetFunction,
  IN UINT8                          Lun,
  IN UINT8                          Command,
  IN UINT8                          *CommandData,
  IN UINT32                         CommandDataSize,
  OUT UINT8                         *ResponseData,
  OUT UINT32                        *ResponseDataSize );

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
