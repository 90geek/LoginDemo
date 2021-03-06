//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/*++

Copyright (c)  2012 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  Msct.h

Abstract:

  This file describes the contents of the ACPI Maximum System Characteristics Table (MSCT).
  Some additional ACPI values are defined in Acpi1_0.h, Acpi2_0.h, and Acpi3_0.h.
  All changes to the MPST contents should be done in this file.

--*/

#ifndef _MSCT_H_
#define _MSCT_H_

//
// Statements that include other files
//
#include <IndustryStandard\Acpi.h>
#include "Platform.h"

//
// MSCT Definitions, see specification for details.
//
#ifndef EFI_ACPI_4_0_MAXIMUM_SYSTEM_CHARACTERISTICS_TABLE_SIGNATURE
#define EFI_ACPI_4_0_MAXIMUM_SYSTEM_CHARACTERISTICS_TABLE_SIGNATURE       0x5443534D
#endif
#define EFI_ACPI_MAXIMUM_SYSTEM_CHARACTERISTICS_TABLE_REVISION            0x01
#define EFI_ACPI_OEM_MSCT_REVISION                                        0x00000001
#define EFI_ACPI_MAXIMUM_PROXIMITY_DOMAIN_INFORMATION_STRUCTURE_REVISION  0x01


//
// MSCT Table definition
//
#pragma pack(1)

typedef struct {
  UINT8   Revision;
  UINT8   Length;
  UINT32  ProxDomRangeLow;
  UINT32  ProxDomRangeHigh;
  UINT32  MaxProcessorCapacity;
  UINT64  MaxMemoryCapacity;
} EFI_ACPI_MAXIMUM_PROXIMITY_DOMAIN_INFORMATION_STRUCTURE;

typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER                              Header;
  UINT32                                                   OffsetProxDomInfo;
  UINT32                                                   MaxNumProxDom;
  UINT32                                                   MaxNumClockDom;
  UINT64                                                   MaxPhysicalAddress;
  EFI_ACPI_MAXIMUM_PROXIMITY_DOMAIN_INFORMATION_STRUCTURE  ProxDomInfoStructure[MAX_SOCKET];
} EFI_ACPI_MAXIMUM_SYSTEM_CHARACTERISTICS_TABLE;

#pragma pack()

#endif  //_MSCT_H_
