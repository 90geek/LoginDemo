/** @file
  This file defines variable shared between PCH Init DXE driver and PCH
  Init S3 Resume PEIM.

@copyright
  Copyright (c) 2006 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _PCH_INIT_VAR_H_
#define _PCH_INIT_VAR_H_


#include "Ppi/PchPlatformPolicy.h"

//
// Extern the GUID for PPI users.
//
extern EFI_GUID gPchInitVariableGuid;

#define PCH_INIT_VARIABLE_NAME  L"PchInit"

///
/// Define the Pch Init Variable structure
///
typedef struct {
  UINT32  StorePosition;
  UINT32  ExecutePosition;
} PCH_S3_PARAMETER_HEADER;

#pragma pack(1)
typedef struct _PCH_INIT_VARIABLE {
  PCH_S3_PARAMETER_HEADER *PchS3Parameter;
} PCH_INIT_VARIABLE;
#pragma pack()

#endif
