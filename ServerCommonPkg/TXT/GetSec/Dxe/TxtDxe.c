/**
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
/**

  Copyright (c) 2007 - 2014 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.


    @file LtDxe.c

  This is the main DXE file for LT.  It represents an abstract outline of the
  steps required during DXE for enabling LT.  Each individual step is further
  abstracted behind a function call interface.  This is intended to minimize
  the need to modify this file when porting LT to future platforms.

**/

#include "TxtDxeLib.h"
#include <Protocol/PciEnumerationComplete.h> //AptioV Server override: Use AMI PCI bus driver protocol that indicate resources assigned.
#include <Library/LtDxeLib.h>
#include <Library/PlatformHooksLib.h> //for IsSimicsPlatform()

LT_DXE_LIB_CONTEXT          mLtDxeCtx ;
EFI_LEGACY_REGION2_PROTOCOL *mLegacyRegion = NULL;
BOOLEAN                    ScheckDone = FALSE;
BOOLEAN                     LtDxeEnabled = TRUE;
BOOLEAN                     DisableBIOSACMFlag = FALSE;

VOID WA_UnLock()
{
  UINT32              RegEax;
  UINT8               SteppingId;

  //
  // Do nothing if >= JKT-C1 stepping
  //
  AsmCpuid (EFI_CPUID_VERSION_INFO, &RegEax, NULL, NULL, NULL);
  SteppingId = (UINT8) (RegEax & 0xF);

  if (SteppingId > 5) return;
  if (mLegacyRegion) {
    //
    // Unlock Legacy region segment to let LockConfig not to block legacy boot
    //
    mLegacyRegion->UnLock (mLegacyRegion,
                           LEGACY_BIOS_MEMORY_SEGMENT,
                           LEGACY_BIOS_MEMORY_LENGTH,
                           NULL
                           );
  }
}

/**

  This function gets registered as a callback to run the SCHECK function
  from the LT BIOS ACM as a result of Boot Events.

  @param Event     - A pointer to the Event that triggered the callback.
  @param Context   - A pointer to private data registered with the callback function.

  @retval EFI_SUCCESS   - Always.

**/
EFI_STATUS
EFIAPI
ScheckCallback (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_STATUS          Status;
  UINT32              Data32;
  UINT8               BiosAcmErrorResetBit;
  UINT8               AcmTypeValue;

/*
  if (IsSimicsPlatform()) {
    DEBUG ((EFI_D_ERROR, "LT w/a for Simics - Skip ScheckCallback\n"));
//    return EFI_SUCCESS ;
     while (Context){};
  }
*/

  DEBUG ((EFI_D_ERROR, "DXE DoScheck ...\n"));
  DoScheck(&mLtDxeCtx) ;
  DEBUG ((EFI_D_ERROR, "DoScheck Done!\n"));

  WA_UnLock();
  
  // Aptio V Server Override Start : TXT Error and status Register message printing.
    PrintLtsxErrors();
  // Aptio V Server Override end : TXT Error and status Register message printing.

  // If LT_SPAD_HIGH 0xFED300A0 bit63 = 0, do legacy boot
  Data32 = *(volatile UINT32 *)(UINTN)LT_SPAD_HIGH;
  DEBUG ((EFI_D_ERROR, "LT_SPAD_HIGH (0xFED300A4): %r\n", Data32));

  if ( (BIT31 & (*(volatile UINT32 *)(UINTN)LT_SPAD_HIGH)) == 0 ) {
    // BIOS ACM DoScheck error
    DEBUG ((EFI_D_ERROR, "Bios Acm DoScheck Failed. Reboot in non-ltsx mode\n"));

    // When BIOS ACM error occurs, If BiosAcmErrorReset setup option is enabled,
    // Disable LT-SX and reset system
    Status = GetBiosAcmErrorReset (&BiosAcmErrorResetBit);

    if ( (Status != EFI_SUCCESS) || BiosAcmErrorResetBit) {
      DisableLtsxAndReset();
    }

    // When BIOS ACM error occurs, If BiosAcmErrorReset setup option is disabled,
    // Ignore BIOS ACM errors and continue booting with no further BIOSACM being called
    //
    else {
      Status = GetAcmType (&AcmTypeValue);

      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "ERROR: No LtDxe Lib file, no platform funtions available\n"));
      } else {
        DEBUG ((EFI_D_ERROR, "ERROR: IGNORING ACM ERROR - ACM Type %x detected  - BIOS setup option is set to ignore ACM error\n",
          AcmTypeValue));
      }

      gBS->CloseEvent(Event);
      return EFI_SUCCESS;
    }
  }

  DEBUG ((EFI_D_ERROR, "DoLockConfig ...\n"));
  TxtLockConfigForAll(&mLtDxeCtx) ;
  DEBUG ((EFI_D_ERROR, "DoLockConfig Done!\n"));
  
  // Aptio V Server Override Start : TXT Error and status Register message printing.
    PrintLtsxErrors();
  // Aptio V Server Override end : TXT Error and status Register message printing.

  // If LT_SPAD_HIGH 0xFED300A0 bit63 = 0, do legacy boot
  //
  Data32 = *(volatile UINT32 *)(UINTN)LT_SPAD_HIGH;
  DEBUG ((EFI_D_ERROR, "LT_SPAD_HIGH (0xFED300A4): %r\n", Data32));

  if ( (BIT31 & (*(volatile UINT32 *)(UINTN)LT_SPAD_HIGH)) == 0 ) {

    // BIOS ACM DoScheck error
    //
    DEBUG ((EFI_D_ERROR, "Bios Acm LockConfig Failed. Reboot in non-ltsx mode\n"));

    // When BIOS ACM error occurs, If BiosAcmErrorReset setup option is enabled,
    // Disable LT-SX and reset system
    //
    Status = GetBiosAcmErrorReset(&BiosAcmErrorResetBit);

    if ( (Status != EFI_SUCCESS) || BiosAcmErrorResetBit) {
      DisableLtsxAndReset();
    }

    // When BIOS ACM error occurs, If BiosAcmErrorReset setup option is disabled,
    // Ignore BIOS ACM errors and continue booting with no further BIOSACM being called
    //
    else {
      Status = GetAcmType (&AcmTypeValue);

      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "ERROR: No LtDxe Lib file, no platform funtions available\n"));
      } else {
        DEBUG ((EFI_D_ERROR, "ERROR: IGNORING ACM ERROR - ACM Type %x detected  - BIOS setup option is set to ignore ACM error\n",
          AcmTypeValue));
      }

      gBS->CloseEvent(Event);
      return EFI_SUCCESS;
    }
  }
  return EFI_SUCCESS ;
}

/**

  Lock MSR for this thread.

  @param None

  @retval EFI_SUCCESS           - MSR Locked

**/
EFI_STATUS
LockLTPatch (
  IN  EFI_MP_SERVICES_PROTOCOL  *MpService

  )
{
  UINT64              LtCtrl;

  //
  // Set LT_CONTROL_LOCK
  //
  LtCtrl = 0x1;
  AsmWriteMsr64 (EFI_MSR_LT_CONTROL, LtCtrl);

  return EFI_SUCCESS;
}

/**

  Lock LT MSR.

  @param None

  @retval EFI_SUCCESS           - Multiple processors re-load microcode patch

**/
EFI_STATUS
LockLtMsr (
  VOID
  )
{
  EFI_STATUS              Status;

  LockLTPatch (mLtDxeCtx.MpService);
  ASSERT (mLtDxeCtx.MpService);
  Status = mLtDxeCtx.MpService->StartupAllAPs (
                        mLtDxeCtx.MpService,
                        LockLTPatch,
                        TRUE,
                        NULL,
                        0,
                        (VOID *)mLtDxeCtx.MpService,
                        NULL
                        );

  return EFI_SUCCESS;
}

/**

  Callback function to lock down chipset after all chipset config is done

  @param EFI_HANDLE                                   RootBridgeHandle
  @param EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS  PciAddress
  @param EFI_PCI_ENUMERATION_PHASE                    Phase
  @param EFI_PCI_CALLBACK_CONTEXT                     *Context

  @retval EFI_SUCCESS           - Multiple processors re-load microcode patch

**/
VOID
EFIAPI
LaunchAcm (
  IN  EFI_EVENT                             Event,
  IN  VOID                                  *Context
  )
{
  EFI_STATUS                Status;
  UINTN                     SysCfgSize;
  SYSTEM_CONFIGURATION      SysCfg;

    SysCfgSize = sizeof (SysCfg);
    Status = gRT->GetVariable (
                  L"IntelSetup",	//Aptio V Server Override
                  &gEfiSetupVariableGuid,
                  NULL,
                  &SysCfgSize,
                  &SysCfg
                  );
    //
    // If Setup variable cannot be found, lock LtMsr.
    //

    if (EFI_ERROR(Status)) {
      SysCfg.LockChipset = 1;
      SysCfg.EVMode = 0;
    }
    //
    // Only lock when disabled if LockChipset is set and EVMode is disabled
    //
    if (LtDxeEnabled || (!LtDxeEnabled && SysCfg.LockChipset && !SysCfg.EVMode))
      LockLtMsr();

    if ((!ScheckDone) && (LtDxeEnabled)) {
        ScheckCallback (0, NULL);
    ScheckDone = TRUE;
  }
}

/**

  This is the entry point to the LT DXE Driver.  This routine checks to see if
  the platform should be configured for LT and if so, configures the platform
  by reserving and initializing LT Configuration Space and LT Device Memory and
  registering a callback to run SCHECK from the LT BIOS ACM prior to boot.

  If the platform should not be configured for LT, this routine checks the
  establishment bit in the TPM and resets it if it is asserted.

  @param ImageHandle       - A handle for this module
  @param SystemTable       - A pointer to the EFI System Table

  @retval EFI_SUCCESS   - Always.

**/
EFI_STATUS
EFIAPI
DriverEntry (
  IN      EFI_HANDLE          ImageHandle,
  IN      EFI_SYSTEM_TABLE    *SystemTable
  )
{
  EFI_STATUS                  Status;
  UINT32                      Data32;
// Aptio V Server Override - Start : Changes done related to TXT support.
//  EFI_PCI_CALLBACK_PROTOCOL   *PciCallBackProtocol;
  VOID            *PciEnumerationCompleteRegistration;
  EFI_EVENT 	   Event = NULL;
// Aptio V Server Override - End : Changes done related to TXT support.
//  EFI_PCI_CALLBACK_PROTOCOL   *PciCallBackProtocol; //Aptio V Server Override : Changes done related to TXT support.
  UINT8                       BiosAcmErrorResetBit;
  UINT8                       AcmTypeValue;
//Aptio V Server Override Start: Changes done related to TXT support.
/*
  //
  // Find ACM Binary type to Suppress "BIOS ACM Error Reset" setup option, if PW ACM is present.
  //
  Status = FindAcmBinaryType();

  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_INFO, "No LtDxeLib available to execute platform functions\n"));
    DEBUG ((EFI_D_INFO, "LtDxe driver cannot load\n"));
    return (EFI_UNSUPPORTED);
  }

  //
  // Register for protocol notifactions, because ReadyToBoot is too late
  // Need to lock LT config MSR whether it is enabled or not
  //
  Status = gBS->LocateProtocol ( 
                 &gEfiPciCallbackProtocolGuid, 
                 NULL, 
                 &PciCallBackProtocol
                 );
  ASSERT_EFI_ERROR(Status); 

  Status = PciCallBackProtocol->RegisterPciCallback(
                         PciCallBackProtocol,
                         LTLockEventNotify,
                         EfiPciEnumerationResourceAssigned
                         );
  ASSERT_EFI_ERROR (Status);
  DEBUG ((EFI_D_INFO, "Register for Scheck/LockConfig Callback\n"));
*/
// Aptio V Server Override End: Changes done related to TXT support.
  //
  // Initialize the LT DXE Lib functions
  //
  Status = InitializeLtDxeLib (ImageHandle, SystemTable, &mLtDxeCtx);
  if (EFI_ERROR (Status)) {
    LtDxeEnabled = FALSE;
    DEBUG ((EFI_D_ERROR, "InitializeLtDxeLib Error: %r\n", Status));
    return EFI_SUCCESS;
  }

  //
  // Determine TPM presense. If not present - nothing to do.
  // Nothing but presense is precondition of this module since all
  // commands executed by BIOS ACM don't depend on TPM state.
  // TPM_NV_read will be successfully executed even if TPM is disabled
  // and/or deactivated because all indices defined for BIOS ACM
  // usage don't require authorization. TPM_ResetEstablishmentBit
  // doesn't depend on TPM state at all and can
  // be executed with disabled/deactivated TPM always.
  // Case when TPM is comletely not functional is not cinsidered.
  //
#ifndef SOFTSDV_FLAG
  if (!IsTpmPresent (&mLtDxeCtx)) {
    DEBUG ((EFI_D_ERROR, "IsTpmPresent Error\n"));
#ifdef MKF_TPM_PRESENT
    LtDxeEnabled = FALSE;
    return EFI_SUCCESS;
#endif
  }
#endif

  //
  // Detect LT capable Processor
  //
  if (!IsLtProcessor (&mLtDxeCtx)) {
    DEBUG ((EFI_D_ERROR, "LtDxe Error: Not LT processor\n"));
    LtDxeEnabled = FALSE;
    return EFI_SUCCESS ;
  }

  Status = gBS->LocateProtocol (
                 &gEfiLegacyRegion2ProtocolGuid,
                 NULL,
                 &mLegacyRegion
                 );
  ASSERT_EFI_ERROR(Status);

  //
  // If LT is enabled, configure platform appropriately
  //
#ifdef MKF_TPM_PRESENT
  if (IsLtEnabled (&mLtDxeCtx)) {
#else
  if (1) {
#endif

    // If LT_SPAD_HIGH 0xFED300A0 bit63 = 0, do legacy boot
    //
    Data32 = *(volatile UINT32 *)(UINTN)LT_SPAD_HIGH;
    DEBUG ((EFI_D_ERROR, "LT_SPAD_HIGH (0xFED300A4): %r\n", Data32));

    if ( (BIT31 & (*(volatile UINT32 *)(UINTN)LT_SPAD_HIGH)) == 0 ) {

      // BIOS ACM error
      //
      DEBUG ((EFI_D_ERROR, "Bios Acm Failed. Reboot in non-ltsx mode\n"));

      Status = GetBiosAcmErrorReset (&BiosAcmErrorResetBit);

      if ( (Status == EFI_SUCCESS) && BiosAcmErrorResetBit) {
        DisableLtsxAndReset();
      } else {
        Status = GetAcmType (&AcmTypeValue);

        if (Status == EFI_SUCCESS) {
          DEBUG ((EFI_D_ERROR, "ERROR: IGNORING ACM ERROR - ACM Type %x detected  - BIOS setup option is set to ignore ACM error\n",
            AcmTypeValue));
        } else {
          DEBUG ((EFI_D_ERROR, "ERROR: No LtDxe Lib functions installed  - BIOS setup option is set to ignore ACM error\n"));
        }

        DisableBIOSACMFlag = TRUE;
      }
    }

    //
    // Initialize LT Device Memory
    //
    Status = SetupLtDeviceMemory (&mLtDxeCtx);

//Aptio V Server Override - Start 

    //
    // Register for protocol notifactions, because ReadyToBoot is too late
    //

    Status = gBS->CreateEvent (
                         	 	 EVT_NOTIFY_SIGNAL,
                         	 	 TPL_CALLBACK,
                         	 	 LaunchAcm,
                         	 	 NULL,
                         	 	 &Event
                         	  );
    ASSERT_EFI_ERROR (Status);

    //
    // Register for protocol notifications on this event
    //

    Status = gBS->RegisterProtocolNotify (
        		 	 	 	 	 	 	 	&gEfiPciEnumerationCompleteProtocolGuid,
        		 	 	 	 	 	 	 	Event,
        		 	 	 	 	 	 	 	&PciEnumerationCompleteRegistration
                         	 	 	 	 );

    ASSERT_EFI_ERROR (Status);
    DEBUG ((EFI_D_ERROR, "Register for Scheck/LockConfig Callback\n"));
// Aptio V Server Override - End 
    
  } else {
    Status = EFI_UNSUPPORTED;
  }

  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Lt not enabled\n"));

    //
    // LT is not enabled, so make sure TPM Establishment
    // bit is de-asserted
    //
    if (IsLtEstablished (&mLtDxeCtx)) {
      Status = ResetTpmEstBit (&mLtDxeCtx) ;
      ASSERT_EFI_ERROR (Status) ;
    }
  }

  return EFI_SUCCESS ;
}
