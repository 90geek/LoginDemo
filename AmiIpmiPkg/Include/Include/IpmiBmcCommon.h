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

/** @file IpmiBmcCommon.h
    IPMI BMC Controller Common Structures and Function Prototypes.

**/

#ifndef _EFI_IPMI_COMMON_BMC_H_
#define _EFI_IPMI_COMMON_BMC_H_

//----------------------------------------------------------------

#include <Token.h>

//----------------------------------------------------------------

//
//    Macros Used
//
#define MAX_TEMP_DATA                    0xFF
#define BMC_SLAVE_ADDRESS                0x20
#define EFI_IPMI_RESPONSE_HEADER_SIZE    3
#define EFI_IPMI_COMMAND_HEADER_SIZE     2

#pragma pack(1)

//
//    KCS Interface Structure
//
typedef struct {
    UINT16                DataPort;
    UINT16                CommandPort;
    UINT16                KcsRetryCounter;
} KCS_SYSTEM_INTERFACE;

//
//    BT Interface Structure definition
//
typedef struct {
    UINT16                CtrlPort;
    UINT16                ComBuffer;
    UINT16                IntMaskPort;
    UINT16                BtDelay;
} BT_SYSTEM_INTERFACE;

//
//    IPMI Interface Union definition
//
typedef union {
    KCS_SYSTEM_INTERFACE         KCS;
    BT_SYSTEM_INTERFACE          BT;
} SYSTEM_INTERFACE;

//
//    BMC Elog instance data
//
typedef struct {
    UINTN                 Signature;
    UINT8                 SlaveAddress;
    UINT8                 TempData[MAX_TEMP_DATA];
    EFI_BMC_STATUS        BmcStatus;
    UINT64                ErrorStatus;
    UINT8                 SoftErrorCount;
    EFI_IPMI_TRANSPORT    IpmiTransport;
    SYSTEM_INTERFACE      Interface;
} EFI_IPMI_BMC_INSTANCE_DATA;

//
//    Structure of IPMI Command buffer
//
typedef struct {
  UINT8 Lun : 2;
  UINT8 NetFunction : 6;
  UINT8 Command;
  UINT8 CommandData[MAX_TEMP_DATA - EFI_IPMI_COMMAND_HEADER_SIZE];
} EFI_IPMI_COMMAND;

//
//    Structure of IPMI Command response buffer
//
typedef struct {
  UINT8 Lun : 2;
  UINT8 NetFunction : 6;
  UINT8 Command;
  UINT8 CompletionCode;
  UINT8 ResponseData[MAX_TEMP_DATA - EFI_IPMI_RESPONSE_HEADER_SIZE];
} EFI_IPMI_RESPONSE;

EFI_STATUS
SendDataToBmcPort (
  IN EFI_IPMI_BMC_INSTANCE_DATA    *IpmiInstance,
  IN VOID                          *Context,
  IN UINT8                         *Data,
  IN UINT8                         DataSize );

//    BT Interface starts
EFI_STATUS
SendDataToBtBmcPort (
  IN EFI_IPMI_BMC_INSTANCE_DATA    *IpmiInstance,
  IN VOID                          *Context,
  IN UINT8                         *Data,
  IN UINT8                         DataSize );

EFI_STATUS
ReceiveBmcDataFromBtPort (
  IN  EFI_IPMI_BMC_INSTANCE_DATA    *IpmiInstance,
  IN  VOID                          *Context,
  OUT UINT8                        *Data,
  OUT UINT8                        *DataSize );
//    BT interface ends

EFI_STATUS
ReceiveBmcDataFromPort (
  IN  EFI_IPMI_BMC_INSTANCE_DATA    *IpmiInstance,
  IN  VOID                          *Context,
  OUT UINT8                         *Data,
  OUT UINT8                         *DataSize );

EFI_STATUS
EfiIpmiSendCommand (
  IN  EFI_IPMI_TRANSPORT     *This,
  IN  UINT8                  NetFunction,
  IN  UINT8                  Lun,
  IN  UINT8                  Command,
  IN  UINT8                  *CommandData,
  IN  UINT8                  CommandDataSize,
  OUT UINT8                 *ResponseData,
  OUT UINT8                 *ResponseDataSize );

EFI_STATUS
IpmiSendCommand (
  IN  EFI_IPMI_TRANSPORT     *This,
  IN  UINT8                  NetFunction,
  IN  UINT8                  Lun,
  IN  UINT8                  Command,
  IN  UINT8                  *CommandData,
  IN  UINT8                  CommandDataSize,
  OUT UINT8                  *ResponseData,
  OUT UINT8                  *ResponseDataSize,
  IN  VOID                   *Common );

//    BT interface starts
EFI_STATUS
IpmiBtSendCommand  (
  IN  EFI_IPMI_TRANSPORT     *This,
  IN  UINT8                  NetFunction,
  IN  UINT8                  Lun,
  IN  UINT8                  Command,
  IN  UINT8                  *CommandData,
  IN  UINT8                  CommandDataSize,
  OUT UINT8                  *ResponseData,
  OUT UINT8                  *ResponseDataSize,
  IN  VOID                   *Common );

//    BT interface ends      
EFI_STATUS
EfiIpmiBmcStatus (
  IN  EFI_IPMI_TRANSPORT    *This,
  OUT EFI_BMC_STATUS        *BmcStatus,
  OUT EFI_SM_COM_ADDRESS    *ComAddress );

EFI_STATUS
IpmiBmcStatus (
  IN  EFI_IPMI_TRANSPORT    *This,
  OUT EFI_BMC_STATUS        *BmcStatus,
  OUT EFI_SM_COM_ADDRESS    *ComAddress,
  IN  VOID                  *Common );

EFI_STATUS
EfiBtIpmiSendCommand (
  IN  EFI_IPMI_TRANSPORT     *This,
  IN  UINT8                  NetFunction,
  IN  UINT8                  Lun,
  IN  UINT8                  Command,
  IN  UINT8                  *CommandData,
  IN  UINT8                  CommandDataSize,
  OUT UINT8                  *ResponseData,
  OUT UINT8                  *ResponseDataSize );

#pragma pack()

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
