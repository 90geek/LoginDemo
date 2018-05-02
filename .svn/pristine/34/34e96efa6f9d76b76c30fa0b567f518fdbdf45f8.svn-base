/*++

Copyright (c)  2009- 2013 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:
    SataSgpio.h

Abstract:
   Head file of SataSgpio.c

--*/

#ifndef _SATA_SGPIO_H_
#define _SATA_SGPIO_H_

#include <Uefi/UefiBaseType.h>
#include <PchAccess.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PchPlatformLib.h>
#include <Library/S3BootScriptLib.h>
#include <Protocol/PchInfo.h>
#include <Pi/PiDxeCis.h>

#define LED_TYPE      0x00
#define SAF_TE_TYPE   0x01
#define SES_2_TYPE    0x02
#define SGPIO_TYPE    0x03

#pragma pack(1)
typedef struct _ENCLOSURE_MESSAGE_HEADER {
  UINT8     Reserved;
  UINT8     MessageSize;
  UINT8     DataSize;
  UINT8     MessageType : 4;
  UINT8     Reserved2: 4;
} ENCLOSURE_MESSAGE_HEADER;

typedef struct _LED_TYPE_MESSAGE {
  UINT8     HbaInfo;
  UINT8     PortMuliplierInfo;
  UINT16    ActivityLED : 3;
  UINT16    VendorSpecLED1 : 3;
  UINT16    VendorSpecLED2 : 3;
  UINT16    Reserved: 7;
} LED_TYPE_MESSAGE;
#pragma pack()

#endif
