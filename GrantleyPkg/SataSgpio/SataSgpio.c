/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/*++

Copyright (c) 2006 - 2014 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  SataSgpio.c

Abstract:

  Initialize Sata Sgpio for each Sata port

Revision History

--*/

#include "SataSgpio.h"
#include <PchCommonDefinitions.h>

/**

  A callback at ReadyToBoot event to check and launch the internal EFI shell.

  @param[in] Event      This EFI_EVENT object.
  @param[in] Context    A pointer to VOID for the generic context delivery purpose.

**/
VOID
ClearSATASGPIOLEDByDevice (
  IN UINTN           Bus,
  IN UINTN           Dev,
  IN UINTN           Func
  )
{
  UINTN                       PciD31F2RegBase;
  UINT8                       SubClassCode;
  UINT16                      OldCommand;
  UINT32                      AhciBar;
  UINT32                      HostCapability;
  UINT16                      EnclosureMgmtLoc;
  UINT8                       Index;
  UINTN                       TimeoutCnt;
  UINT32                      EnclosureMgmtCtrl;
  PCH_SERIES                  PchSeries;
  UINTN                       MaxPorts;
  ENCLOSURE_MESSAGE_HEADER    *MessageHeader;
  LED_TYPE_MESSAGE            *LedMessage;
  UINT32                      AHCI_PI;
  UINT16                      DeviceId;

  DEBUG ((EFI_D_INFO, "ClearSATASGPIOLEDByDevice () Enter\n"));

  PciD31F2RegBase = PchPciDeviceMmBase (
                      Bus,
                      Dev,
                      Func
                      );
  //
  // Store register before operation
  //
  AhciBar = MmioRead32 (PciD31F2RegBase + R_PCH_SATA_AHCI_BAR);
  OldCommand = MmioRead16 (PciD31F2RegBase + R_PCH_SATA_COMMAND);

  //
  // Return if it's not in AHCI mode
  //
  SubClassCode = MmioRead8 (PciD31F2RegBase + R_PCH_SATA_SUB_CLASS_CODE);
  if (SubClassCode != V_PCH_SATA_SUB_CLASS_CODE_AHCI) {
    return;
  }

  //
  // Enable command register memory space decoding
  //
  if ((OldCommand & B_PCH_SATA_COMMAND_MSE) != 1) {
     MmioOr16 ((UINTN) (PciD31F2RegBase + R_PCH_SATA_COMMAND), (UINT16) B_PCH_SATA_COMMAND_MSE);
  }

  //
  // Check enclosure management support
  //
  HostCapability = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_CAP);
  if (!(HostCapability & B_PCH_SATA_AHCI_CAP_EMS)) {
    goto Done;
  }

  EnclosureMgmtLoc = ((UINT16) (MmioRead32 (AhciBar + R_PCH_SATA_AHCI_EM_LOC) >> 16))*4;

  //
  // Set message type for AHCI ports
  //
  MaxPorts = LPTLP_AHCI_MAX_PORTS;
  PchSeries = GetPchSeries ();
  DeviceId = MmioRead16 (PciD31F2RegBase + R_PCH_SATA_DEVICE_ID);
  if (PchSeries == PchH && !(IS_PCH_WBG_SSATA_AHCI_DEVICE_ID (DeviceId))) {
    MaxPorts = LPTH_AHCI_MAX_PORTS;
  } else if (PchSeries == PchLp) {
    MaxPorts = LPTLP_AHCI_MAX_PORTS;
  }
  AHCI_PI = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_PI);
  for (Index = 0; Index < MaxPorts; Index++) {
     if (AHCI_PI & (1 << Index) ) {
       //
       // Make sure message transmission is completed
       // before setting message type (Timeout = 16 * 640ms)
       //
       for (TimeoutCnt = 0; TimeoutCnt < 0x10; TimeoutCnt++) {
         EnclosureMgmtCtrl = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_EM_CTRL);
         if (!(EnclosureMgmtCtrl & B_PCH_SATA_AHCI_EM_CTRL_CTL_TM)) {
           break;
         }

         gBS->Stall (640);
       }

       //
       // Set message type (For Pch: 4 bytes message size, 0 byte data size)
       //
       MessageHeader = (ENCLOSURE_MESSAGE_HEADER *) (UINTN) (AhciBar + EnclosureMgmtLoc);
       MessageHeader->MessageType = LED_TYPE;
       MessageHeader->MessageSize = 4;
       MessageHeader->DataSize = 0;


       //
       // LED message type setting
       //
       LedMessage = (LED_TYPE_MESSAGE *) (UINTN) (AhciBar + EnclosureMgmtLoc + 4);
       LedMessage->HbaInfo = Index;
       LedMessage->PortMuliplierInfo = 0;
       LedMessage->ActivityLED = 0;
       LedMessage->VendorSpecLED1 = 0;
       LedMessage->VendorSpecLED2 = 0;

       //
       // Transmit message
       //
       EnclosureMgmtCtrl = MmioRead32 (AhciBar + R_PCH_SATA_AHCI_EM_CTRL);
       EnclosureMgmtCtrl |= B_PCH_SATA_AHCI_EM_CTRL_CTL_TM;
       MmioWrite32 (AhciBar + R_PCH_SATA_AHCI_EM_CTRL, EnclosureMgmtCtrl);
     }
  }

Done:
  //
  // Restroe to privious setting
  //
  if ((OldCommand & B_PCH_SATA_COMMAND_MSE) != 1) {
     MmioWrite16 (PciD31F2RegBase + R_PCH_SATA_COMMAND, OldCommand);
  }

  DEBUG ((EFI_D_INFO, "ClearSATASGPIOLEDByDevice () Exit\n"));
   
  return ;
}

VOID
ClearSATASGPIOLED (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_STATUS                  Status;
  EFI_PCH_INFO_PROTOCOL       *PchInfo;

  Status = gBS->LocateProtocol (&gEfiPchInfoProtocolGuid, NULL, &PchInfo);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((EFI_D_INFO, "ClearSATASGPIOLED () Enter\n"));

  ClearSATASGPIOLEDByDevice(
                             PchInfo->BusNumber,
                             PCI_DEVICE_NUMBER_PCH_SATA,
                             PCI_FUNCTION_NUMBER_PCH_SATA); 

  ClearSATASGPIOLEDByDevice(
                             PchInfo->BusNumber,
                             PCI_DEVICE_NUMBER_PCH_SSATA,
                             PCI_FUNCTION_NUMBER_PCH_SSATA);

  DEBUG ((EFI_D_INFO, "ClearSATASGPIOLED () Exit\n"));

  return ;
}

/**

  Initialize SATA SGPIO for each SATA port

  @param ImageHandle     The image handle.
  @param SystemTable     The system table.

  @retval  EFI_SUCEESS  SATA SGPIO is initialized successfully.
  @retval  Other        SATA SGPIO initialization fail.

**/
EFI_STATUS
EFIAPI
InitalizeEntryPoint (
  IN EFI_HANDLE                            ImageHandle,
  IN EFI_SYSTEM_TABLE                      *SystemTable
  )
{
  EFI_STATUS Status;
  EFI_EVENT  ReadyToBootEvent;

  Status = EfiCreateEventReadyToBootEx (
                      TPL_CALLBACK, 
                      ClearSATASGPIOLED, 
                      NULL, 
                      &ReadyToBootEvent
                      );

  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
