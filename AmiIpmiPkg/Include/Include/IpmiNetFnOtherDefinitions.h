//
// This file contains an 'Intel Peripheral Driver' and is
// licensed for Intel CPUs and chipsets under the terms of your
// license agreement with Intel or your vendor.  This file may
// be modified by the user, subject to additional terms of the
// license agreement
//
/*++

Copyright (c)  1999 - 2009 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:
  IpmiNetFnOtherDefinitions.h
  
Abstract:
  The file has all the other Net funcion definitions
--*/

#ifndef _IPMINETFNOTHERDEFINITIONS_H_
#define _IPMINETFNOTHERDEFINITIONS_H_


//
// LUN definition
//
#ifndef BMC_LUN 
    #define BMC_LUN     0x00
#endif 

//
// Net function definition for Bridge command
//
#ifndef EFI_SM_NETFN_BRIDGE
	#define EFI_SM_NETFN_BRIDGE 0x02
#endif

//
// Net function definition for Firmware command
//
#ifndef EFI_SM_NETFN_FIRMWARE
	#define EFI_SM_NETFN_FIRMWARE 0x08
#endif

//
// Net function definition for Group Extension command
//
#ifndef EFI_SM_NETFN_GROUP_EXT
	#define EFI_SM_NETFN_GROUP_EXT  0x2C
#endif

//
// Net function definition for OEM Group command
//
#ifndef EFI_SM_NETFN_OEM_GROUPT
	#define EFI_SM_NETFN_OEM_GROUP  0x2E
#endif

//
// Net function definition for Intel OEM specific command
//
#ifndef EFI_SM_NETFN_INTEL_OEM
	#define EFI_SM_NETFN_INTEL_OEM  0x30
#endif

//
// Net function definition for SOL OEM command
//
#ifndef EFI_SM_NETFN_SOL_OEM
	#define EFI_SM_NETFN_SOL_OEM  0x34
#endif

#endif
