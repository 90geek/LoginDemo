/**
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
*/

/** @file HddSmartCommon.h
    This file contains the Includes, Definitions, typedefs,
    Variable and External Declarations, Structure and
    function prototypes needed for the different module parts in the 
    HddSmart driver

**/

#ifndef _AMI_HDDSMART_COMMON_
#define _AMI_HDDSMART_COMMON_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
#include <Protocol/DiskInfo.h>
#include <IndustryStandard/AmiAtaAtapi.h>
#include <Protocol/AmiIdeBus.h>
#include <Protocol/AmiAhciBus.h>
#include <Protocol/AmiHddSmartInit.h>
//---------------------------------------------------------------------------

typedef struct _AMI_SMART_INTERFACE{
 
    UINT8                             Revision;
    UINT32                            Signature;
    AMI_HDD_SMART_SELF_TEST           SmartSelfTest;
    AMI_HDD_SMART_SELF_TEST_STATUS    SmartSelfTestStatus;
    AMI_HDD_SMART_RETURN_STATUS       SmartReturnStatus;
    AMI_HDD_SEND_SMART_COMMAND        SendSmartCommand;
    AMI_HDD_SMART_READ_DATA           SmartReadData;
    AMI_HDD_SMART_WRITE_DATA          SmartWriteData;
    AMI_HDD_SMART_ABORT_SELF_TEST     SmartAbortSelfTest;
    AMI_HDD_SMART_GET_SMART_DATA      SmartGetSmartData;
    VOID                              *BusInterface;
    UINT8                             ShortPollingTime;
    UINT16                            ExtPollingTime;
    BOOLEAN                           ModeFlag;
} AMI_SMART_INTERFACE;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

/**
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
*/

