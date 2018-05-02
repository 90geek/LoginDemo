/**
  This file contains an 'Intel Peripheral Driver' and is        
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
**/
/**

  Copyright (c) 2015 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.


    @file LtPeiLib.c

  This has platform-specific code for LT.  It contains hooks used by
  ServerCommon code that must be run during PEI for enabling/disabling/examining
  LT/TXT functions and status.

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Guid/PlatformTxt.h>
#include <Guid/SetupVariable.h>
#include <TXT/GetSec/Pei/TxtPeiLib.h> //AptioV Server Override: To resolve build error

// External variables
//
extern EFI_GUID           gPeiMpServicePpiGuid;

// External PROCs
//

//
// Helper PROCs for ServerCommonPkg/Universal/GetSec
//

/**

  Returns Setup knob that says whether LT lock
   should be done 

  @param  **PeiServices   - pointer to PEI Services pointer
  @param  *LockChipsetBit - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading Setup knob

**/
EFI_STATUS
GetLockChipset (
  IN EFI_PEI_SERVICES                 **PeiServices,
  IN UINT8                            *LockChipsetBit
  )
{
  EFI_STATUS                          Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI     *PeiVariable;
  UINTN                               VariableSize;
  SYSTEM_CONFIGURATION                SystemConfiguration;
  
  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);

  //
  // Locate Variable PPI
  //
  Status = (**PeiServices).LocatePpi (
                  PeiServices,
                  &gEfiPeiReadOnlyVariable2PpiGuid,
                  0,
                  NULL,
                  &PeiVariable
                  );  
  
  //
  // Use variable PPI to get setup data
  //
  if (EFI_ERROR (Status)) {
        DEBUG((EFI_D_ERROR, "LocatePpi Error in GetLockChipset (PEI)\n"));
  } else {
    VariableSize = sizeof (SYSTEM_CONFIGURATION);

    Status = PeiVariable->GetVariable (
                          PeiVariable,
                          L"IntelSetup",//AptioV Server Override
                          &gEfiSetupVariableGuid,
                          NULL,
                          &VariableSize,
                          &SystemConfiguration
                          );
  }

  //
  // Got setup data?
  //
  if (EFI_ERROR (Status)) {
    *LockChipsetBit = TRUE;
  } else {
    *LockChipsetBit = SystemConfiguration.LockChipset;
  }

  return (Status);
}

/**

  Returns Setup knob that says whether platform should be left unlocked
   i.e in Electrical Validation mode

  @param  **PeiServices   - pointer to PEI Services pointer
  @param  *EVModeBit - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading Setup knob

**/
EFI_STATUS
GetEVMode (
  IN EFI_PEI_SERVICES                 **PeiServices,
  IN UINT8                            *EVModeBit
  )
{
  EFI_STATUS                          Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI     *PeiVariable;
  UINTN                               VariableSize;
  SYSTEM_CONFIGURATION                SystemConfiguration;
  
  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);

  //
  // Locate Variable PPI
  //
  Status = (**PeiServices).LocatePpi (
                  PeiServices,
                  &gEfiPeiReadOnlyVariable2PpiGuid,
                  0,
                  NULL,
                  &PeiVariable
                  );  
  
  //
  // Use variable PPI to get setup data
  //
  if (EFI_ERROR (Status)) {
        DEBUG((EFI_D_ERROR, "LocatePpi Error in GetEVMode (PEI)\n"));
  } else {
    VariableSize = sizeof (SYSTEM_CONFIGURATION);

    Status = PeiVariable->GetVariable (
                          PeiVariable,
                          L"IntelSetup",//AptioV Server Override
                          &gEfiSetupVariableGuid,
                          NULL,
                          &VariableSize,
                          &SystemConfiguration
                          );
  }

  //
  // Got setup data?
  //
  if (EFI_ERROR (Status)) {
    *EVModeBit = FALSE;
  } else {
    *EVModeBit = SystemConfiguration.EVMode;
  }

  return (Status);
}

/**

  Returns Setup knob that says whether LT lock
   is enabled in this processor 

  @param  **PeiServices   - pointer to PEI Services pointer
  @param  *ProcessorLtsxEnableBit - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading Setup knob

**/
EFI_STATUS
GetProcessorLtsxEnable (
  IN EFI_PEI_SERVICES                 **PeiServices,
  IN UINT8                            *ProcessorLtsxEnableBit
  )
{
  EFI_STATUS                          Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI     *PeiVariable;
  UINTN                               VariableSize;
  SYSTEM_CONFIGURATION                SystemConfiguration;
  
  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);

  //
  // Locate Variable PPI
  //
  Status = (**PeiServices).LocatePpi (
                  PeiServices,
                  &gEfiPeiReadOnlyVariable2PpiGuid,
                  0,
                  NULL,
                  &PeiVariable
                  );  
  
  //
  // Use variable PPI to get setup data
  //
  if (EFI_ERROR (Status)) {
        DEBUG((EFI_D_ERROR, "LocatePpi Error in GetProcessorLtsxEnable (PEI)\n"));
  } else {
    VariableSize = sizeof (SYSTEM_CONFIGURATION);

    Status = PeiVariable->GetVariable (
                          PeiVariable,
                          L"IntelSetup",//AptioV Server Override
                          &gEfiSetupVariableGuid,
                          NULL,
                          &VariableSize,
                          &SystemConfiguration
                          );
  }

  //
  // Got setup data?
  //
  if (EFI_ERROR (Status)) {
    *ProcessorLtsxEnableBit = FALSE;
  } else {
    *ProcessorLtsxEnableBit = SystemConfiguration.ProcessorLtsxEnable;
  }

  return (Status);
}

/**

  Fills in pointer to PeiMpServices in LT_PEI_LIB_CONTEXT structure
   passsed in from ServerCommonPkg

  @param  **PeiServices - pointer to PEI Services pointer
  @param  *ProcessorLtsxEnableBit - pointer back to LT_PEI_LIB_CONTEXT 
           structure in ServerCommonPkg code where PeiMpServices is copied

  @retval Status - Success/failure reading pointer

**/
EFI_STATUS
GetPeiMpServices (
  IN      CONST EFI_PEI_SERVICES  **PeiServices,
  OUT 	  PEI_MP_SERVICES_PPI 	 **PeiMpServices

  )
{
  //
  // Find PeiMpServices PPI, only need success locating at end of S3 resume
  //
  return ((*PeiServices)->LocatePpi(
                      PeiServices,
                      &gPeiMpServicePpiGuid,
                      0,
                      NULL,
                      PeiMpServices
                      ));
}
