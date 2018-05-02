/*++
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/** @file

Copyright (c) 2011, Intel Corporation. All rights reserved.
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:
  IpmiNetFnSensorDefinitions.h
  
Abstract:
  The file has all the definitions required for Sensor commands
--*/

#ifndef _IPMINETFNSENSORDEFINITIONS_H_
#define _IPMINETFNSENSORDEFINITIONS_H_

//
// LUN definition
//
#ifndef BMC_LUN
    #define BMC_LUN     0x00
#endif

//
// Net function definition for Sensor command
//
#define EFI_SM_NETFN_SENSOR 0x04

//
// All Sensor commands and their structure definitions to follow here
//

/*----------------------------------------------------------------------------------------
    Definitions for Send Platform Event Message command     
----------------------------------------------------------------------------------------*/
#define EFI_SENSOR_PLATFORM_EVENT_MESSAGE   0x02

#pragma pack(1)
typedef struct {
  UINT8   GeneratorId;
  UINT8   EvMRevision;
  UINT8   SensorType;
  UINT8   SensorNumber;
  UINT8   EventDirType;
  UINT8   OEMEvData1;
  UINT8   OEMEvData2;
  UINT8   OEMEvData3;
} EFI_PLATFORM_EVENT_MESSAGE_DATA;
#pragma pack()
#endif
