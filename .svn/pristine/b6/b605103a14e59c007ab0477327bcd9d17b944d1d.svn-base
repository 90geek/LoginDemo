/*++
  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/*++

Copyright (c)  2006 - 2013 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  HeciHpetLib.h

Abstract:

  Definitions for HECI driver

--*/
#ifndef _HECI_HPET_LIB_H
#define _HECI_HPET_LIB_H

//
// Driver Produced Protocol Prototypes
//

VOID
StartTimer (
  OUT UINT32 *Start,
  OUT UINT32 *End,
  IN  UINT32 Time
  )
/*++

  Routine Description:

    Used for calculating timeouts

  Arguments:

    Start - Snapshot of the HPET timer
    End   - Calculated time when timeout period will be done
    Time  - Timeout period in microseconds

  Returns:

    VOID

--*/
;

EFI_STATUS
Timeout (
  IN  UINT32 Start,
  IN  UINT32 End
  )
/*++

  Routine Description:
    Used to determine if a timeout has occured.

  Arguments:
    Start - Snapshot of the HPET timer when the timeout period started.
    End   - Calculated time when timeout period will be done.

  Returns:
    EFI_STATUS

--*/
;


#endif // _HECI_HPET_H
