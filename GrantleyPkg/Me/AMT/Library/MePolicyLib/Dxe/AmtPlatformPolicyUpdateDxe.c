/*++
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/*++

Copyright (c) 2012, Intel Corporation. All rights reserved.
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

--*/
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include "MeState.h"
#include "AmtPlatformPolicyUpdateDxe.h"

EFI_STATUS
EFIAPI
UpdateDxeAmtPlatformPolicy (
  IN OUT  DXE_AMT_POLICY_PROTOCOL   *DxeAmtPlatformPolicy
  )
/*++

Routine Description:

  Install DxeAmtPlatformPolicy with setup values

Arguments:

  DxeAmtPlatformPolicy - DXE Amt Platform Policy

Returns:

  EFI_SUCCESS           Initialization complete.
  EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  EFI_DEVICE_ERROR      Device error, driver exits abnormally.

--*/
{
  EFI_STATUS              Status;
  UINT32                  MeMode;
  EFI_HECI_PROTOCOL       *Heci;
  SYSTEM_CONFIGURATION    SetupDataBuffer;
  SYSTEM_CONFIGURATION    *SetupData;
  UINTN                   SetupVariableSize;
  UINT32                  SetupVariableAttributes;
  UINT8                   Index;

  SetupData = &SetupDataBuffer;
  Index     = 0;

  DEBUG ((EFI_D_INFO, "Enter InstallDxeAmtPlatformPolicy\n"));

  Status = gBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  &Heci
                  );
  ASSERT_EFI_ERROR (Status);

  Status = Heci->GetMeMode (&MeMode);
  ASSERT_EFI_ERROR (Status);

  SetupVariableSize = sizeof (SYSTEM_CONFIGURATION);

  //
  // Get Management configuration from Setup Data
  //
  // AptioV Server Override: Changed variable name to IntelSetup
  Status = gRT->GetVariable (
                  L"IntelSetup",
                  &gEfiSetupVariableGuid,
                  &SetupVariableAttributes,
                  &SetupVariableSize,
                  &SetupDataBuffer
                  );

  if (!EFI_ERROR (Status)) {
    DxeAmtPlatformPolicy->AmtConfig.AsfEnabled                = SetupData->Asf;
    DxeAmtPlatformPolicy->AmtConfig.iAmtEnabled               = SetupData->Amt;
    DxeAmtPlatformPolicy->AmtConfig.WatchDog                  = SetupData->WatchDog;
    DxeAmtPlatformPolicy->AmtConfig.WatchDogOs                = SetupData->WatchDogOs;
    DxeAmtPlatformPolicy->AmtConfig.WatchDogTimerOs           = SetupData->WatchDogTimerOs;
    DxeAmtPlatformPolicy->AmtConfig.WatchDogTimerBios         = SetupData->WatchDogTimerBios;
    DxeAmtPlatformPolicy->AmtConfig.CiraRequest               = SetupData->AmtCiraRequest;
    DxeAmtPlatformPolicy->AmtConfig.CiraTimeout               = SetupData->AmtCiraTimeout;
    DxeAmtPlatformPolicy->AmtConfig.UnConfigureMe             = SetupData->UnConfigureMe;
    DxeAmtPlatformPolicy->AmtConfig.HideUnConfigureMeConfirm  = SetupData->HideUnConfigureMeConfirm;
    DxeAmtPlatformPolicy->AmtConfig.MebxDebugMsg              = SetupData->MebxDebugMsg;
    DxeAmtPlatformPolicy->AmtConfig.USBProvision              = SetupData->USBProvision;
    DxeAmtPlatformPolicy->AmtConfig.FWProgress                = SetupData->FWProgress;
    DxeAmtPlatformPolicy->AmtConfig.iAmtbxSelectionScreen     = SetupData->AmtbxSelectionScreen;
    DxeAmtPlatformPolicy->AmtConfig.iAmtbxHotkeyPressed       = SetupData->AmtbxHotKeyPressed;
    DxeAmtPlatformPolicy->AmtConfig.MebxNonUiTextMode         = SetupData->MebxNonUiTextMode;
    DxeAmtPlatformPolicy->AmtConfig.MebxUiTextMode            = SetupData->MebxUiTextMode;
    DxeAmtPlatformPolicy->AmtConfig.MebxGraphicsMode          = SetupData->MebxGraphicsMode;

    //
    // Reset CIRA and UnConfigureMe setting if either one got set
    //
    if (SetupData->UnConfigureMe == 1 || SetupData->AmtCiraRequest == 1) {
      SetupData->UnConfigureMe  = 0;
      SetupData->AmtCiraRequest = 0;
    }
    //AptioV server override start : A vulnerability allows the takeover of the system.
    if(SetupData->Amt ==0)
    {
       DxeAmtPlatformPolicy->AmtConfig.USBProvision  = USB_PROVISION_DEFAULT_WITHOUT_AMT;
    }
    //AptioV server override end : A vulnerability allows the takeover of the system.
    // AptioV Server Override: Changed variable name to IntelSetup
    Status = gRT->SetVariable (
                    L"IntelSetup",
                    &gEfiSetupVariableGuid,
                    SetupVariableAttributes,
                    SetupVariableSize,
                    &SetupDataBuffer
                    );
  }
  return Status;
}
