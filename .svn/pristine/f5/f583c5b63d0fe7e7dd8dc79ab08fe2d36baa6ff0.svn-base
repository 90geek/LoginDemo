//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file Xhci.c
    AMI XHCI driver.

**/

#include "AmiUsb.h"
#include "AmiDef.h"
#include "UsbDef.h"

UINT8   XHCI_Start (HC_STRUC*);
UINT8   XHCI_Stop (HC_STRUC*);
UINT8   XHCI_EnumeratePorts (HC_STRUC*);
UINT8   XHCI_DisableInterrupts (HC_STRUC*);
UINT8   XHCI_EnableInterrupts (HC_STRUC*);
UINT8   XHCI_ProcessInterrupt(HC_STRUC*);
UINT8   XHCI_GetRootHubStatus (HC_STRUC*, UINT8, BOOLEAN);
UINT8   XHCI_DisableRootHub (HC_STRUC*,UINT8);
UINT8   XHCI_EnableRootHub (HC_STRUC*,UINT8);
UINT16  XHCI_ControlTransfer (HC_STRUC*,DEV_INFO*,UINT16,UINT16,UINT16,UINT8*,UINT16);
UINT32  XHCI_BulkTransfer (HC_STRUC*,DEV_INFO*,UINT8,UINT8*,UINT32);
UINT16  XHCI_InterruptTransfer (HC_STRUC*,DEV_INFO*,UINT8*,UINT16);
UINT8   XHCI_DeactivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   XHCI_ActivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   XHCI_DisableKeyRepeat (HC_STRUC*);
UINT8   XHCI_EnableKeyRepeat (HC_STRUC*);
UINT8   XHCI_EnableEndpoints (HC_STRUC*, DEV_INFO*, UINT8*);
UINT8   XHCI_InitDeviceData (HC_STRUC*,DEV_INFO*,UINT8,UINT8**);
UINT8   XHCI_DeinitDeviceData (HC_STRUC*,DEV_INFO*);
UINT8   XHCI_ResetRootHub (HC_STRUC*,UINT8);
UINT8	XHCI_ClearEndpointState(HC_STRUC*,DEV_INFO*,UINT8);		//(EIP54283+)
UINT8   XHCI_GlobalSuspend (HC_STRUC*);	//(EIP54018+)
UINT8   XhciResetHc(HC_STRUC*);

UINT8		XHCI_WaitForEvent(HC_STRUC*,XHCI_TRB*,TRB_TYPE,UINT8,UINT8,UINT8*,UINT16,VOID*);
TRB_RING*   XHCI_InitXfrRing(USB3_HOST_CONTROLLER*, UINT8, UINT8);
TRB_RING*   XHCI_GetXfrRing(USB3_HOST_CONTROLLER*, UINT8, UINT8);
UINT8       XHCI_GetSlotId(USB3_HOST_CONTROLLER*, DEV_INFO*);
UINT64      XHCI_Mmio64Read(HC_STRUC*, USB3_HOST_CONTROLLER*, UINTN);
VOID        XHCI_Mmio64Write(HC_STRUC*, USB3_HOST_CONTROLLER*, UINTN, UINT64);
EFI_STATUS  XHCI_InitRing(TRB_RING*, UINTN, UINT32, BOOLEAN);
UINT32*     XHCI_GetTheDoorbell(USB3_HOST_CONTROLLER*, HC_STRUC*, UINT8);
UINT32      XhciGetTheDoorbellOffset(USB3_HOST_CONTROLLER*, HC_STRUC*, UINT8);
VOID        UpdatePortStatusSpeed(UINT8, UINT8*);
UINT8		XHCI_ResetPort(HC_STRUC*, USB3_HOST_CONTROLLER*, UINT8, BOOLEAN);
BOOLEAN		XHCI_IsUsb3Port(USB3_HOST_CONTROLLER*, UINT8);
UINT8		XhciRingDoorbell(USB3_HOST_CONTROLLER*, HC_STRUC*, UINT8, UINT8);
UINT8		XhciAddressDevice (HC_STRUC*, DEV_INFO*, UINT8);

DEV_INFO*   XHCI_GetDevInfo(UINTN);
VOID*		XHCI_GetDeviceContext(USB3_HOST_CONTROLLER*, UINT8);
VOID*		XHCI_GetContextEntry(USB3_HOST_CONTROLLER*, VOID*, UINT8);

UINT8		UsbHubGetHubDescriptor(HC_STRUC*, DEV_INFO*, VOID*, UINT16);

UINT8		USB_ResetHubPort(HC_STRUC*, UINT8, UINT8);
UINT8		USB_DisconnectDevice (HC_STRUC*, UINT8, UINT8);
UINT8       USB_GetHubPortStatus(HC_STRUC*, UINT8, UINT8, BOOLEAN);

UINT32      HcReadPciReg(HC_STRUC*, UINT32);
UINT32	    HcReadOpReg(HC_STRUC*, UINT32);
UINT32	    HcReadHcMem(HC_STRUC*, UINT32);
VOID	    HcWriteHcMem(HC_STRUC*, UINT32, UINT32);
VOID        HcSetHcMem(HC_STRUC*, UINT32, UINT32);
VOID        HcClearHcMem(HC_STRUC*, UINT32, UINT32);
VOID	    HcWriteOpReg(HC_STRUC*, UINT32, UINT32);
VOID	    HcClearOpReg(HC_STRUC*, UINT32, UINT32);
VOID	    HcSetOpReg(HC_STRUC*, UINT32, UINT32);
UINT8	    HcDmaMap(HC_STRUC*, UINT8, UINT8*, UINT32, UINT8**, VOID**);
UINT8	    HcDmaUnmap(HC_STRUC*, VOID*);


VOID	    USBKeyRepeat(HC_STRUC*, UINT8);

extern  USB_GLOBAL_DATA     *gUsbData;
extern  EFI_EMUL6064TRAP_PROTOCOL *gEmulationTrap;

#if USB_DEV_KBD
VOID    USBKBDPeriodicInterruptHandler(HC_STRUC*);
#endif

/**
    This function fills the host controller driver routine pointers.

    @param 
        Ptr to the host controller header structure

    @retval 
  Status: USB_SUCCESS = Success, USB_ERROR = Failure

**/

UINT8
XHCI_FillHCDEntries (
    HCD_HEADER *fpHCDHeader
)
{
    fpHCDHeader->pfnHCDStart                = XHCI_Start;
    fpHCDHeader->pfnHCDStop                 = XHCI_Stop;
    fpHCDHeader->pfnHCDEnumeratePorts       = XHCI_EnumeratePorts;
    fpHCDHeader->pfnHCDDisableInterrupts    = XHCI_DisableInterrupts;
    fpHCDHeader->pfnHCDEnableInterrupts     = XHCI_EnableInterrupts;
    fpHCDHeader->pfnHCDProcessInterrupt     = XHCI_ProcessInterrupt;
    fpHCDHeader->pfnHCDGetRootHubStatus     = XHCI_GetRootHubStatus;
    fpHCDHeader->pfnHCDDisableRootHub       = XHCI_DisableRootHub;
    fpHCDHeader->pfnHCDEnableRootHub        = XHCI_EnableRootHub;
    fpHCDHeader->pfnHCDControlTransfer      = XHCI_ControlTransfer;
    fpHCDHeader->pfnHCDBulkTransfer         = XHCI_BulkTransfer;
    fpHCDHeader->pfnHCDInterruptTransfer    = XHCI_InterruptTransfer;
    fpHCDHeader->pfnHCDDeactivatePolling    = XHCI_DeactivatePolling;
    fpHCDHeader->pfnHCDActivatePolling      = XHCI_ActivatePolling;
    fpHCDHeader->pfnHCDDisableKeyRepeat     = XHCI_DisableKeyRepeat;
    fpHCDHeader->pfnHCDEnableKeyRepeat      = XHCI_EnableKeyRepeat;
    fpHCDHeader->pfnHCDEnableEndpoints      = XHCI_EnableEndpoints;
    fpHCDHeader->pfnHCDInitDeviceData       = XHCI_InitDeviceData;
    fpHCDHeader->pfnHCDDeinitDeviceData     = XHCI_DeinitDeviceData;
	fpHCDHeader->pfnHCDResetRootHub         = XHCI_ResetRootHub;
	fpHCDHeader->pfnHCDClearEndpointState	= XHCI_ClearEndpointState;	//(EIP54283+)
	fpHCDHeader->pfnHCDGlobalSuspend        = XHCI_GlobalSuspend;	//(EIP54018+)

    return  USB_SUCCESS;
}


/**
    This API function is called to start a XHCI host controller. The input
    to the routine is the pointer to the HC structure that defines this host
    controller. The procedure flow is followed as it is described in 4.2 of
    XHCI specification.

    @param 
        HcStruc  - Pointer to the HC structure

    @retval 
        USB_SUCCESS = Success, USB_ERROR = Failure

**/

UINT8
XHCI_Start (
    HC_STRUC    *HcStruc
)
{
    XHCI_INTERRUPTER_REGS   *Interrupter;
    XHCI_ER_SEGMENT_ENTRY   *Erst0Entry;
    UINT32      i;
    BOOLEAN     PpSet = FALSE;
    UINT8       PortNumber;
    UINT32      XhciPortSts;
    XHCI_PORTSC *PortSts = (XHCI_PORTSC*)&XhciPortSts;
    UINT8       Status;

    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    
	// Wait controller ready
	for (i = 0; i < 1000; i++) {
        if (!(HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_CNR)) {
            break;
        }
		FixedDelay(100);        // 100 us delay
    }
//    ASSERT(Usb3Hc->OpRegs->UsbSts.Field.Cnr == 0);
    if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_CNR) {
        return USB_ERROR;
    }

	// Check if the xHC is halted
	if (!(HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED)) {
        HcClearOpReg(HcStruc, XHCI_USBCMD_OFFSET, XHCI_CMD_RS);
		// The xHC should halt within 16 ms. Section 5.4.1.1
        for (i = 0; i < 160; i++) {
            if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED) {
                break;
            }
            FixedDelay(100);        // 100 us delay
		}
		ASSERT(HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED);
        if (!(HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED)) {
            return USB_ERROR;
        }
	}
#if XHCI_COMPLIANCE_MODE_WORKAROUND
	for (PortNumber = 1; PortNumber <= Usb3Hc->CapRegs.HcsParams1.MaxPorts; PortNumber++) {
        XhciPortSts = HcReadOpReg(HcStruc, XHCI_PORTSC_OFFSET + (0x10 * (PortNumber - 1)));
        if (PortSts->Field.Pls == XHCI_PORT_LINK_COMPLIANCE_MODE) {
            XHCI_ResetPort(HcStruc, Usb3Hc, PortNumber, FALSE);
        }
	}
#endif

    Status = XhciResetHc(HcStruc);

    if (Status == USB_ERROR) {
        return Status;
    }

    Usb3Hc->RtRegs = (XHCI_HC_RT_REGS*)(HcStruc->BaseAddress + Usb3Hc->CapRegs.RtsOff);
    USB_DEBUG(3, "XHCI: RT registers are at %x\n", Usb3Hc->RtRegs);

    // Max device slots enabled
    HcWriteOpReg(HcStruc, XHCI_CONFIG_OFFSET, Usb3Hc->CapRegs.HcsParams1.MaxSlots);
 
    XHCI_Mmio64Write(HcStruc, Usb3Hc, (UINTN)&Usb3Hc->OpRegs->DcbAap, (UINT64)(UINTN)Usb3Hc->DcbaaPtr);

	// Check if xHC support 64bit access capability
	if (Usb3Hc->CapRegs.HccParams1.Ac64) {
		if (XHCI_Mmio64Read(HcStruc, Usb3Hc, (UINTN)&Usb3Hc->OpRegs->DcbAap) != (UINT64)(UINTN)Usb3Hc->DcbaaPtr) {
			Usb3Hc->CapRegs.HccParams1.Ac64 = 0;
			XHCI_Mmio64Write(HcStruc, Usb3Hc, (UINTN)&Usb3Hc->OpRegs->DcbAap, (UINT64)(UINTN)Usb3Hc->DcbaaPtr);
		}
	}
	
    // Define the Command Ring Dequeue Pointer by programming the Command Ring
    // Control Register (5.4.5) with a 64-bit address pointing to the starting
    // address of the first TRB of the Command Ring.

    // Initialize Command Ring Segment: Size TRBS_PER_SEGMENT*16, 64 Bytes aligned
    XHCI_InitRing(&Usb3Hc->CmdRing, (UINTN)Usb3Hc->DcbaaPtr + 0x2000, TRBS_PER_SEGMENT, TRUE);
    USB_DEBUG(3, "CMD Ring is at %x\n", (UINTN)&Usb3Hc->CmdRing);

    // Write CRCR HC register with the allocated address. Set Ring Cycle State to 1.
    XHCI_Mmio64Write(HcStruc, Usb3Hc, (UINTN)&Usb3Hc->OpRegs->Crcr,
            (UINT64)(UINTN)Usb3Hc->CmdRing.Base + CRCR_RING_CYCLE_STATE);

    // Initialize and assign Event Ring
    XHCI_InitRing(&Usb3Hc->EvtRing, (UINTN)Usb3Hc->DcbaaPtr + 0x2400, TRBS_PER_SEGMENT, FALSE);
    USB_DEBUG(3, "EVT Ring is at %x\n", (UINTN)&Usb3Hc->EvtRing);

    // NOTE: This driver supports one Interrupter, hence it uses
    // one Event Ring segment with TRBS_PER_SEGMENT TRBs in it.

    // Initialize ERST[0]
    Erst0Entry = (XHCI_ER_SEGMENT_ENTRY*)((UINTN)Usb3Hc->DcbaaPtr + 0x1200);
    Erst0Entry->RsBase = (UINT64)(UINTN)Usb3Hc->EvtRing.Base;
    Erst0Entry->RsSize = TRBS_PER_SEGMENT;

    Interrupter = Usb3Hc->RtRegs->IntRegs;

    // Initialize Interrupter fields
    HcWriteHcMem(HcStruc, 
        (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->Erstz - HcStruc->BaseAddress), 1);
    // ER dequeue pointer
    XHCI_Mmio64Write(HcStruc, Usb3Hc, (UINTN)&Interrupter->Erdp, (UINT64)(UINTN)Usb3Hc->EvtRing.QueuePtr);
    // Seg Table location
    XHCI_Mmio64Write(HcStruc, Usb3Hc, (UINTN)&Interrupter->Erstba, (UINT64)(UINTN)Erst0Entry);
    HcWriteHcMem(HcStruc, 
        (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMod - HcStruc->BaseAddress), XHCI_IMODI);
    HcSetOpReg(HcStruc, XHCI_USBCMD_OFFSET, XHCI_CMD_INTE);
    // Enable interrupt
    HcSetHcMem(HcStruc, 
        (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMan - HcStruc->BaseAddress), BIT1);

    USB_DEBUG(3, "Transfer Rings structures start at %x\n", Usb3Hc->XfrRings);

    // Set PortPower unless PowerPortControl indicates otherwise
    if (Usb3Hc->CapRegs.HccParams1.Ppc != 0) {
		for (PortNumber = 1; PortNumber <= Usb3Hc->CapRegs.HcsParams1.MaxPorts; PortNumber++) {
            if (!(HcReadOpReg(HcStruc, XHCI_PORTSC_OFFSET + (0x10 * (PortNumber - 1))) & XHCI_PCS_PP)) {
                // Set port power
                HcSetOpReg(HcStruc, XHCI_PORTSC_OFFSET + (0x10 * (PortNumber - 1)), XHCI_PCS_PP);
                PpSet = TRUE;
            }
        }
        if (PpSet) {
            FixedDelay(20 * 1000);   // Wait for 20 ms, Section 5.4.8
        }
    }

	// If xHC doesn't support HW SMI, should not touch USB Legacy Support Capability registers
	//if (((HcStruc->dHCFlag & HC_STATE_EXTERNAL) && (XHCI_EVENT_SERVICE_MODE == 0)) ||
	//	(USB_RUNTIME_DRIVER_IN_SMM == 0)) {
	//	Usb3Hc->UsbLegSupOffSet = 0;
	//}
		
    // Check if USB Legacy Support Capability is present.
	if (Usb3Hc->UsbLegSupOffSet) {
		// Set HC BIOS Owned Semaphore flag
		HcSetHcMem(HcStruc, Usb3Hc->UsbLegSupOffSet, XHCI_BIOS_OWNED_SEMAPHORE);
        //If XHCI doesn't support HW SMI, should not enable USB SMI in Legacy Support Capability register.
        if (((!(HcStruc->dHCFlag & HC_STATE_EXTERNAL)) || (XHCI_EVENT_SERVICE_MODE != 0)) &&
            (USB_RUNTIME_DRIVER_IN_SMM != 0) && (!(HcStruc->dHCFlag & HC_STATE_IRQ))) {
		    // Enable USB SMI, Ownership Change SMI and clear all status
		    HcSetHcMem(HcStruc, Usb3Hc->UsbLegSupOffSet + XHCI_LEGACY_CTRL_STS_REG, 
		            XHCI_SMI_ENABLE | XHCI_SMI_OWNERSHIP_CHANGE_ENABLE |
		            XHCI_SMI_OWNERSHIP_CHANGE | XHCI_SMI_PCI_CMD |
		            XHCI_SMI_PCI_BAR);
        }
    }
    HcSetOpReg(HcStruc, XHCI_USBCMD_OFFSET, XHCI_CMD_RS);

	for (i = 0; i < 100; i++) {
        if (!(HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED)) {
            break;
        }
        FixedDelay(100);
	}
    ASSERT(!(HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED));

    HcStruc->dHCFlag |= HC_STATE_RUNNING;

    // Set USB_FLAG_DRIVER_STARTED flag when HC is running.
    if (!(gUsbData->dUSBStateFlag & USB_FLAG_DRIVER_STARTED)) {
        gUsbData->dUSBStateFlag |= USB_FLAG_DRIVER_STARTED;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (!(HcStruc->dHCFlag & HC_STATE_IRQ)) {
    	if (!(HcStruc->dHCFlag & HC_STATE_EXTERNAL)) {
            UsbInstallHwSmiHandler(HcStruc);
        }
        if (HcStruc->HwSmiHandle != NULL) {
            USBKeyRepeat(HcStruc, 0);
        } else {
#if XHCI_EVENT_SERVICE_MODE != 1
            USBSB_InstallUsbIntTimerHandler();
#endif
        }
    }
#endif

    return  USB_SUCCESS;
}


/**
    This function stops the XHCI controller.

    @param 
        HcStruc  - Pointer to the HC structure

    @retval 
        USB_SUCCESS or USB_ERROR

**/

UINT8
XHCI_Stop (
    HC_STRUC    *HcStruc
)
{
	UINT8   Port;
    UINT32  i;
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
	UINT32	LegCtlStsReg = 0;
	UINT8	CompletionCode = 0;

	// Set the flag to aviod port enumeration
	gUsbData->bEnumFlag = TRUE;     // disable recursive enumeration

	for (Port = 1; Port <= Usb3Hc->CapRegs.HcsParams1.MaxPorts; Port++) {
		USB_DisconnectDevice(HcStruc, HcStruc->bHCNumber | BIT7, Port);
	}

	// Port Change Detect bit may set by disabling ports.
	//Usb3Hc->OpRegs->UsbSts.AllBits = XHCI_STS_PCD;

	if (XHCI_Mmio64Read(HcStruc, Usb3Hc, (UINTN)&Usb3Hc->OpRegs->Crcr) & CRCR_COMMAND_RUNNING) {
		// Stop the command ring
		XHCI_Mmio64Write(HcStruc, Usb3Hc, (UINTN)&Usb3Hc->OpRegs->Crcr, CRCR_COMMAND_STOP);

		CompletionCode = XHCI_TRB_CMDRINGSTOPPED;
		XHCI_WaitForEvent(
			HcStruc, NULL, XhciTCmdCompleteEvt, 0, 0,
			&CompletionCode, XHCI_CMD_COMPLETE_TIMEOUT_MS, NULL);
	}

	XHCI_ProcessInterrupt(HcStruc);

	// Clear the port enumeration flag
	gUsbData->bEnumFlag = FALSE;

	// Disable interrupt
	HcClearOpReg(HcStruc, XHCI_USBCMD_OFFSET, XHCI_CMD_INTE);
    HcClearHcMem(HcStruc, 
        (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMan - HcStruc->BaseAddress), BIT1);

	// Clear the Run/Stop bit
	HcClearOpReg(HcStruc, XHCI_USBCMD_OFFSET, XHCI_CMD_RS);

	// The xHC should halt within 16 ms. Section 5.4.1.1
    for (i = 0; i < 160; i++) {
        if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED) {
            break;
        }
        FixedDelay(100);
    }
	ASSERT(HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED);
    //if (Usb3Hc->OpRegs->UsbSts.Field.HcHalted == 0) return USB_ERROR;

    // Check if USB Legacy Support Capability is present.
    if (Usb3Hc->UsbLegSupOffSet != 0) {
		// Clear HC BIOS Owned Semaphore flag
		HcClearHcMem(HcStruc, Usb3Hc->UsbLegSupOffSet, XHCI_BIOS_OWNED_SEMAPHORE);
        if (((!(HcStruc->dHCFlag & HC_STATE_EXTERNAL)) || (XHCI_EVENT_SERVICE_MODE != 0)) &&
            (USB_RUNTIME_DRIVER_IN_SMM != 0) && (!(HcStruc->dHCFlag & HC_STATE_IRQ))) {	
		    // Disable USB SMI and Clear all status
		    LegCtlStsReg = HcReadHcMem(HcStruc, Usb3Hc->UsbLegSupOffSet + XHCI_LEGACY_CTRL_STS_REG);
		    LegCtlStsReg &= ~XHCI_SMI_ENABLE;
		    LegCtlStsReg |= XHCI_SMI_OWNERSHIP_CHANGE | XHCI_SMI_PCI_CMD | XHCI_SMI_PCI_BAR;
    	    HcWriteHcMem(HcStruc, Usb3Hc->UsbLegSupOffSet + XHCI_LEGACY_CTRL_STS_REG, LegCtlStsReg);
        }
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (HcStruc->HwSmiHandle != NULL) {
        USBKeyRepeat(HcStruc, 3);
    }
#endif
    
    // Set the HC state to stopped
    HcStruc->dHCFlag  &= ~(HC_STATE_RUNNING);

    CheckBiosOwnedHc();

    return  USB_SUCCESS;
}


/**
    This function enumerates the HC ports for devices.

    @param 
        HcStruc  - Pointer to the HC structure

    @retval 
        USB_SUCCESS or USB_ERROR

**/

UINT8
XHCI_EnumeratePorts(
    HC_STRUC    *HcStruc
)
{
										//(EIP60327)>
	UINT8	Count;
    UINT8   Port;
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;

    if (gUsbData->bEnumFlag == TRUE) {
        return USB_SUCCESS;
    }

	USB_DEBUG(3, "XHCI_EnumeratePorts..\n");
    gUsbData->bIgnoreConnectStsChng = TRUE; //(EIP71962+)
    gUsbData->bEnumFlag = TRUE;     // disable recursive enumeration

	if (Usb3Hc->Usb2Protocol.PortCount) {
		for (Count = 0; Count < Usb3Hc->Usb2Protocol.PortCount; Count++) {
			Port = Count + Usb3Hc->Usb2Protocol.PortOffset;
			USBCheckPortChange(HcStruc, HcStruc->bHCNumber | BIT7, Port);
		}
	}

	if (Usb3Hc->Usb3Protocol.PortCount) {
		for (Count = 0; Count < Usb3Hc->Usb3Protocol.PortCount; Count++) {
			Port = Count + Usb3Hc->Usb3Protocol.PortOffset;
			if (Usb3Hc->Vid == XHCI_VL800_VID && Usb3Hc->Did == XHCI_VL800_DID) {
				XHCI_ResetPort(HcStruc, Usb3Hc, Port , TRUE);
			}
			USBCheckPortChange(HcStruc, HcStruc->bHCNumber | BIT7, Port);
		}
	}
	
//	Usb3Hc->OpRegs->UsbSts.AllBits = XHCI_STS_PCD;	// Clear PortChangeDetect

    gUsbData->bIgnoreConnectStsChng = FALSE;    //(EIP71962+)
    gUsbData->bEnumFlag = FALSE;    // enable enumeration

	XHCI_ProcessInterrupt(HcStruc);
										//<(EIP60327)
    return USB_SUCCESS;
}


/**
    This function enables the HC interrupts

    @param 
        HcStruc  - Pointer to the HC structure

    @retval 
        USB_ERROR   On error, USB_SUCCESS On success

**/

UINT8
XHCI_EnableInterrupts (
    HC_STRUC* HcStruc
)
{
    return  USB_SUCCESS;
}


/**
    This function disables the HC interrupts

    @param 
        HcStruc  - Pointer to the HC structure

    @retval 
        USB_ERROR on error, USB_SUCCESS on success

**/

UINT8
XHCI_DisableInterrupts (
    HC_STRUC* HcStruc
)
{
    return  USB_SUCCESS;
}


/**
    This function advances returns the pointer to the current TRB and anvances
    dequeue pointer. If the advance pointer is Link TRB, then it: 1) activates
    Link TRB by updating its cycle bit, 2) updates dequeue pointer to the value
    pointed by Link TRB.

    @param 
        Ring - TRB ring to be updated

    @retval 
        TRB that can be used for command, transfer, etc.

**/

XHCI_TRB*
XHCI_AdvanceEnqueuePtr(
    TRB_RING    *Ring
)
{
    XHCI_TRB* Trb = Ring->QueuePtr;

    if (Trb->TrbType == XhciTLink) {
        Trb->CycleBit = Ring->CycleBit;
        Ring->CycleBit ^= 1;
        Ring->QueuePtr = Ring->Base;

        Trb = Ring->QueuePtr;
    }
    // Clear the TRB
    *(UINT32*)Trb = 0;
	*((UINT32*)Trb + 1) = 0;
	*((UINT32*)Trb + 2) = 0;
	*((UINT32*)Trb + 3) &= BIT0;	// Keep cycle bit

    //Trb->CycleBit = Ring->CycleBit;
    Ring->QueuePtr++;

    return Trb;
}


/**
    This function walks through the active TRBs in the event ring and looks for
    the command TRB to be complete. If found, returns SlotId and CompletionCode
    from the completed event TRB. In the end it processes the event ring,
    adjusting its Dequeue Pointer.

**/
										//(EIP62376)>
UINT8
XHCI_WaitForEvent(
    HC_STRUC    *HcStruc,
    XHCI_TRB    *TrbToCheck,
    TRB_TYPE    EventType,
    UINT8		SlotId,
    UINT8		Dci,
    UINT8       *CompletionCode,
    UINT16      TimeOutMs,
    VOID        *Data
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;

    XHCI_TRB    *Trb;
    UINT32      Count;
    UINT8       Status;
    UINT8       CycleBit;
	UINT32		TimeoutValue = ((UINT32)TimeOutMs) * 100;	// in 10 macrosecond unit
    XHCI_NORMAL_XFR_TRB		*ResidualTrb;					//(EIP82555+)
	
    for (Count = 0; TimeoutValue == 0 || Count < TimeoutValue; Count++) {
        for (Trb = Usb3Hc->EvtRing.QueuePtr,
			CycleBit = Usb3Hc->EvtRing.CycleBit;;) {
            if (Trb->CycleBit != CycleBit) {
                // Command is not complete, break and retry
                break;
            }

            // Active TRB found
            if (Trb->TrbType == EventType) {
				if (EventType == XhciTCmdCompleteEvt) {
					if (TrbToCheck) {
						if((*(UINTN*)&Trb->Param1) == (UINTN)TrbToCheck) {
							if (Data != NULL) {
								*(UINT8*)Data = ((XHCI_CMDCOMPLETE_EVT_TRB*)Trb)->SlotId;
							}
							*CompletionCode = Trb->CompletionCode;
							Status = Trb->CompletionCode == XHCI_TRB_SUCCESS? USB_SUCCESS:USB_ERROR;
							goto DoneWaiting;
						}
					} else {
						if (*CompletionCode != 0 && Trb->CompletionCode == *CompletionCode) {
							Status = USB_SUCCESS;
							goto DoneWaiting;
						}
					}
				} else if (EventType == XhciTTransferEvt) {
					if (((XHCI_TRANSFER_EVT_TRB*)Trb)->SlotId == SlotId &&
						((XHCI_TRANSFER_EVT_TRB*)Trb)->EndpointId == Dci) {
                        if (Data != NULL) {
                            *(UINT32*)Data = ((XHCI_TRANSFER_EVT_TRB*)Trb)->TransferLength;
                                        //(EIP82555+)>
                            if (Trb->CompletionCode == XHCI_TRB_SHORTPACKET) {
                                ResidualTrb = (XHCI_NORMAL_XFR_TRB*)(UINTN)((XHCI_TRANSFER_EVT_TRB*)Trb)->TrbPtr;
                                 while (1) {
                                    ResidualTrb->Isp = 0;
                                    ResidualTrb->Ioc = 0;
                                    if (ResidualTrb->Chain != 1) {
                                        break;
                                    }
                                    ResidualTrb++;
                                    if (ResidualTrb->TrbType == XhciTLink) {
                                        ResidualTrb = (XHCI_NORMAL_XFR_TRB*)(UINTN)((XHCI_LINK_TRB*)ResidualTrb)->NextSegPtr;
                                    }
                                    *(UINT32*)Data += ResidualTrb->XferLength;
                                }
                             }
                                        //<(EIP82555+)
                        }
						*CompletionCode = Trb->CompletionCode;
						Status = (Trb->CompletionCode == XHCI_TRB_SUCCESS ||
							Trb->CompletionCode == XHCI_TRB_SHORTPACKET)? USB_SUCCESS:USB_ERROR;
						goto DoneWaiting;
					}
				}
            }
            // Advance TRB pointer
            if (Trb == Usb3Hc->EvtRing.LastTrb) {
                Trb = Usb3Hc->EvtRing.Base;
                CycleBit ^= 1;
            } else {
                Trb++;
            }
            if (Trb == Usb3Hc->EvtRing.QueuePtr) {
                // Event ring is full, return error
                USB_DEBUG(3, "XHCI: Event Ring is full...\n");
                ASSERT(0);
                *CompletionCode = XHCI_TRB_EVENTRINGFULL_ERROR;
                Status = USB_ERROR;
                break;
            }
        }
        FixedDelay(10);    // 10 us out of TimeOutMs
    }

    USB_DEBUG(3, "XHCI: execution time-out.\n");

    *CompletionCode = XHCI_TRB_EXECUTION_TIMEOUT_ERROR;
    Status = USB_ERROR;

DoneWaiting:
    XHCI_ProcessInterrupt(HcStruc);

    return Status;
}
										//<(EIP62376)

/**
    This function places a given command in the Command Ring, rings HC doorbell,
    and waits for the command completion.

         
        USB_ERROR on execution failure, otherwise USB_SUCCESS
    @retval Params pointer to the command specific data.

    @note  
  Caller is responsible for a data placeholder.

**/

UINT8
XHCI_ExecuteCommand(
    HC_STRUC    *HcStruc,
    TRB_TYPE    Cmd,
    VOID        *Params
)
{
    UINT8       CompletionCode = 0;
    UINT8       SlotId;
    UINT8       Status;
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    XHCI_TRB    *Trb = XHCI_AdvanceEnqueuePtr(&Usb3Hc->CmdRing);
	UINT16		TimeOut = XHCI_CMD_COMPLETE_TIMEOUT_MS;

    Trb->TrbType = Cmd; // Set TRB type

    // Fill in the command TRB fields
    switch (Cmd) {
        case XhciTAddressDeviceCmd:
            TimeOut = XHCI_ADDR_CMD_COMPLETE_TIMEOUT_MS;
            ((XHCI_ADDRESSDEV_CMD_TRB*)Trb)->InpCtxAddress = (UINT64)(UINTN)Usb3Hc->InputContext;
            ((XHCI_ADDRESSDEV_CMD_TRB*)Trb)->SlotId = *((UINT8*)Params);
            ((XHCI_ADDRESSDEV_CMD_TRB*)Trb)->Bsr = *((UINT8*)Params + 1);
            break;
        case XhciTEvaluateContextCmd:
        case XhciTConfigureEndpointCmd:
            ((XHCI_CONFIGURE_EP_CMD_TRB*)Trb)->InpCtxAddress = (UINT64)(UINTN)Usb3Hc->InputContext;
            ((XHCI_CONFIGURE_EP_CMD_TRB*)Trb)->SlotId = *((UINT8*)Params);
            ((XHCI_CONFIGURE_EP_CMD_TRB*)Trb)->Dc = 0;
            break;
        case XhciTResetEndpointCmd:
			((XHCI_RESET_EP_CMD_TRB*)Trb)->Tsp = 0;
            ((XHCI_RESET_EP_CMD_TRB*)Trb)->SlotId = *((UINT8*)Params);
            ((XHCI_RESET_EP_CMD_TRB*)Trb)->EndpointId = *((UINT8*)Params+1);
            break;
        case XhciTSetTRDequeuePointerCmd:
            ((XHCI_SET_TRPTR_CMD_TRB*)Trb)->TrPointer = ((XHCI_SET_TRPTR_CMD_TRB*)Params)->TrPointer;
            ((XHCI_SET_TRPTR_CMD_TRB*)Trb)->EndpointId = ((XHCI_SET_TRPTR_CMD_TRB*)Params)->EndpointId;
            ((XHCI_SET_TRPTR_CMD_TRB*)Trb)->SlotId = ((XHCI_SET_TRPTR_CMD_TRB*)Params)->SlotId;
            break;
        case XhciTDisableSlotCmd:
            ((XHCI_DISABLESLOT_CMD_TRB*)Trb)->SlotId = *((UINT8*)Params);
            break;
                                                        //(EIP54300+)>
        case XhciTStopEndpointCmd:
            ((XHCI_STOP_EP_CMD_TRB*)Trb)->SlotId = *((UINT8*)Params);
            ((XHCI_STOP_EP_CMD_TRB*)Trb)->EndpointId = *((UINT8*)Params+1);
            break;
                                                        //<(EIP54300+)
    }

	Trb->CycleBit = Usb3Hc->CmdRing.CycleBit;

    // Ring the door bell and see Event Ring update
    HcWriteHcMem(HcStruc, Usb3Hc->CapRegs.DbOff, 0);

    Status = XHCI_WaitForEvent(
                HcStruc, Trb, XhciTCmdCompleteEvt, 0, 0,					//(EIP62376)
                &CompletionCode, TimeOut, &SlotId);

    if (Status == USB_ERROR) {
        USB_DEBUG(3, "XHCI command completion error code: %d\n", CompletionCode);
		if (CompletionCode == XHCI_TRB_EXECUTION_TIMEOUT_ERROR) {
			XHCI_Mmio64Write(HcStruc, Usb3Hc, (UINTN)&Usb3Hc->OpRegs->Crcr, CRCR_COMMAND_ABORT);

			CompletionCode = XHCI_TRB_COMMANDABORTED;
			XHCI_WaitForEvent(
				HcStruc, Trb, XhciTCmdCompleteEvt, 0, 0,
				&CompletionCode, XHCI_CMD_COMPLETE_TIMEOUT_MS, NULL);
		}
        return Status;
    }

    switch (Cmd) {
        case XhciTEnableSlotCmd:
            USB_DEBUG(3, "XHCI: Enable Slot command complete, SlotID %d\n", SlotId);
            *((UINT8*)Params) = SlotId;
            break;
        case XhciTEvaluateContextCmd:
            USB_DEBUG(3, "XHCI: Evaluate Context command complete.\n");
            break;
        case XhciTConfigureEndpointCmd:
            USB_DEBUG(3, "XHCI: Configure Endpoint command complete.\n");
            break;
        case XhciTResetEndpointCmd:
            USB_DEBUG(3, "XHCI: Reset Endpoint command complete (slot#%x dci#%x).\n",
                *((UINT8*)Params), *((UINT8*)Params+1));
            break;
        case XhciTSetTRDequeuePointerCmd:
            USB_DEBUG(3, "XHCI: Set TR pointer command complete.\n");
            break;
        case XhciTDisableSlotCmd:
            USB_DEBUG(3, "XHCI: DisableSlot command complete.\n");
            break;
                                                        //(EIP54300+)>
        case XhciTStopEndpointCmd:
            USB_DEBUG(3, "XHCI: Stop Endpoint command complete (slot#%x dci#%x).\n",
                *((UINT8*)Params), *((UINT8*)Params+1));
            break;
                                                        //<(EIP54300+)
    }

    return USB_SUCCESS;
}

/**
    This function process root hub port changes.

    @param 
        HcStruc  - Pointer to the HC structure

    @retval 
        USB_SUCCESS or USB_ERROR

**/

UINT8
XHCI_ProcessPortChanges(
	HC_STRUC    			*HcStruc,
	USB3_HOST_CONTROLLER    *Usb3Hc
)
{
	UINT8   	Port;
	BOOLEAN		PortChanged;

    if (gUsbData->bEnumFlag == TRUE) {
        return USB_SUCCESS;
    }

	gUsbData->bEnumFlag = TRUE;     // disable recursive enumeration

    FixedDelay(XHCI_WAIT_PORT_STABLE_DELAY_MS * 1000);

	do {
		PortChanged = FALSE;

		for (Port = 1; Port <= Usb3Hc->CapRegs.HcsParams1.MaxPorts; Port++) {
            if (HcReadOpReg(HcStruc, XHCI_PORTSC_OFFSET + (0x10 * (Port - 1))) & XHCI_PCS_CSC) {
				USBCheckPortChange(HcStruc, HcStruc->bHCNumber | BIT7, Port);
				PortChanged = TRUE;
			}
		}
	} while (PortChanged);

    // Clear PortChangeDetect
    HcWriteOpReg(HcStruc, XHCI_USBSTS_OFFSET, XHCI_STS_PCD);  

    gUsbData->bEnumFlag = FALSE;    // enable enumeration

	return USB_SUCCESS;
}

										//(EIP54283+)>
/**
    This function is called to reset endpoint.

    @param 
        Stalled EP data - SlotId and DCI

**/

UINT8
XHCI_ResetEndpoint(
    USB3_HOST_CONTROLLER *Usb3Hc,
    HC_STRUC    *HcStruc,
    UINT8       SlotId,
    UINT8       Dci
)
{
	UINT16      EpInfo;
	UINT8       Status = USB_SUCCESS;
    XHCI_EP_CONTEXT *EpCtx;

    EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, 
					XHCI_GetDeviceContext(Usb3Hc, SlotId), Dci);
       
    // The Reset Endpoint Command is issued by software to recover 
    // from a halted condition on an endpoint.
    if (EpCtx->EpState == XHCI_EP_STATE_HALTED) {   
        // Reset stalled endpoint
        EpInfo = (Dci << 8) + SlotId;
        Status = XHCI_ExecuteCommand(HcStruc, XhciTResetEndpointCmd, &EpInfo);
    }
    //ASSERT(Status == USB_SUCCESS);
	return Status;
}
										//<(EIP54283+)

/**
    This function is called to restart endpoint. After Endpoint STALLs, it
    transitions from Halted to Stopped state. It is restored back to Running
    state by moving the endpoint ring dequeue pointer past the failed control
    transfer with a Set TR Dequeue Pointer. Then it is restarted by ringing the
    doorbell. Alternatively endpint is restarted using Configure Endpoint command.

    @param 
        Stalled EP data - SlotId and DCI

**/

UINT8
XHCI_ClearStalledEp(
    USB3_HOST_CONTROLLER *Usb3Hc,
    HC_STRUC    *HcStruc,
    UINT8       SlotId,
    UINT8       Dci
)
{
    UINT16      EpInfo;
    TRB_RING    *XfrRing;
    UINT8       Status;
    XHCI_SET_TRPTR_CMD_TRB  Trb;
    XHCI_EP_CONTEXT *EpCtx;
//	volatile UINT32 *Doorbell;	        //(EIP61849-)

/*
Stalled Endpoints       By Sarah Sharp, Linux XHCI driver developer
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 When a control endpoint stalls, the next control transfer will clear the stall.
The USB core doesn't call down to the host controller driver's endpoint_reset()
method when control endpoints stall, so the xHCI driver has to do all its stall
handling for internal state in its interrupt handler.

 When the host stalls on a control endpoint, it may stop on the data phase or
status phase of the control transfer. Like other stalled endpoints, the xHCI
driver needs to queue a Reset Endpoint command and move the hardware's control
endpoint ring dequeue pointer past the failed control transfer (with a Set TR
Dequeue Pointer or a Configure Endpoint command).

 Since the USB core doesn't call usb_hcd_reset_endpoint() for control endpoints,
we need to do this in interrupt context when we get notified of the stalled
transfer. URBs may be queued to the hardware before these two commands complete.
The endpoint queue will be restarted once both commands complete. 

 When an endpoint on a device under an xHCI host controller stalls, the host
controller driver must let the hardware know that the USB core has successfully
cleared the halt condition. The HCD submits a Reset Endpoint Command, which will
clear the toggle bit for USB 2.0 devices, and set the sequence number to zero for
USB 3.0 devices.

  The xHCI urb_enqueue will accept new URBs while the endpoint is halted, and
will queue them to the hardware rings. However, the endpoint doorbell will not
be rung until the Reset Endpoint Command completes. Don't queue a reset endpoint
command for root hubs. khubd clears halt conditions on the roothub during the
initialization process, but the roothub isn't a real device, so the xHCI host
controller doesn't need to know about the cleared halt. 
*/
    EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, 
					XHCI_GetDeviceContext(Usb3Hc, SlotId), Dci);
       
    // The Reset Endpoint Command is issued by software to recover 
    // from a halted condition on an endpoint.
    if (EpCtx->EpState == XHCI_EP_STATE_HALTED) {
        // Reset stalled endpoint
        EpInfo = (Dci << 8) + SlotId;
        Status = XHCI_ExecuteCommand(HcStruc, XhciTResetEndpointCmd, &EpInfo);
    }
    //ASSERT(Status == USB_SUCCESS);

    // Set TR Dequeue Pointer command may be executed only if the target 
    // endpoint is in the Error or Stopped state.
    if ((EpCtx->EpState == XHCI_EP_STATE_STOPPED) || 
        (EpCtx->EpState == XHCI_EP_STATE_ERROR)) {

        XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, Dci-1);

        Trb.TrPointer = (UINT64)((UINTN)XfrRing->QueuePtr + XfrRing->CycleBit); // Set up DCS
        Trb.EndpointId = Dci;
        Trb.SlotId = SlotId;

        Status = XHCI_ExecuteCommand(HcStruc, XhciTSetTRDequeuePointerCmd, &Trb);
        //ASSERT(Status == USB_SUCCESS);
    }

//	Doorbell = XHCI_GetTheDoorbell(Usb3Hc, SlotId);		//(EIP61849-)
//	*Doorbell = Dci;									//(EIP61849-)

    return USB_SUCCESS;
}


/**
    This function processes a transfer event and gives control to the device
    specific routines.

**/

VOID
XHCI_ProcessXferEvt(
    USB3_HOST_CONTROLLER    *Usb3Hc,
    HC_STRUC                *HcStruc,
    XHCI_TRANSFER_EVT_TRB	*XferEvtTrb
)
{
    DEV_INFO                *DevInfo;
	UINT8                   SlotId = XferEvtTrb->SlotId;
	UINT8                   Dci = XferEvtTrb->EndpointId;
    XHCI_NORMAL_XFR_TRB *Trb = (XHCI_NORMAL_XFR_TRB*)XferEvtTrb->TrbPtr;
    UINT32                  DoorbellOffset = XhciGetTheDoorbellOffset(Usb3Hc, HcStruc, SlotId);
    TRB_RING                *XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, Dci-1);
    UINT16                  BytesTransferred;
    UINT8                   PortStatus = USB_PORT_STAT_DEV_ENABLED;

    DevInfo = XHCI_GetDevInfo((UINTN)Trb->DataBuffer);
    if (DevInfo == NULL) return;

	switch (XferEvtTrb->CompletionCode) {
		case XHCI_TRB_SUCCESS:
		case XHCI_TRB_SHORTPACKET:
		    // Check for the keyboard event
										//(EIP38434+)>
			if ((DevInfo->bCallBackIndex) && (DevInfo->fpPollTDPtr != NULL)) {
				if (gUsbData->aCallBackFunctionTable[DevInfo->bCallBackIndex-1]) {
                    //
                    // Get the size of data transferred
                    //
                    BytesTransferred = DevInfo->PollingLength - XferEvtTrb->TransferLength;
					(*gUsbData->aCallBackFunctionTable[DevInfo->bCallBackIndex-1])
									(HcStruc, DevInfo, NULL, DevInfo->fpPollTDPtr,
                                    BytesTransferred);
				}
			}
										//<(EIP38434+)
			break;

		case XHCI_TRB_BABBLE_ERROR:
		case XHCI_TRB_TRANSACTION_ERROR:
		case XHCI_TRB_STALL_ERROR:
            // When the device is disconnecting, the transaction will be error, 
            // we need to check the port status
            PortStatus = USB_GetHubPortStatus(HcStruc, DevInfo->bHubDeviceNumber, DevInfo->bHubPortNumber, FALSE);
            if (PortStatus == USB_ERROR) {
                PortStatus = 0;
            }
            if (PortStatus & USB_PORT_STAT_DEV_ENABLED) {
			    XHCI_ClearStalledEp(Usb3Hc, HcStruc, SlotId, Dci);
            }
			break;	
	}
    // Check if this device is still enabled
    if ((PortStatus & USB_PORT_STAT_DEV_ENABLED) && (DevInfo->fpPollTDPtr != NULL)) {
        Trb = (XHCI_NORMAL_XFR_TRB*)XHCI_AdvanceEnqueuePtr(XfrRing);
        Trb->TrbType = XhciTNormal;
        Trb->DataBuffer = (UINT64)(UINTN)DevInfo->fpPollTDPtr;
        Trb->XferLength = DevInfo->PollingLength;
    	Trb->Isp = 1;					//(EIP51478+)
    	Trb->Ioc = 1;
    	Trb->CycleBit = XfrRing->CycleBit;

        // Ring the door bell to start polling interrupt endpoint
        HcWriteHcMem(HcStruc, DoorbellOffset, Dci);
    }
}

										//(EIP60460+)>
/**

**/

VOID
XHCI_ProcessPortStsChgEvt(
    USB3_HOST_CONTROLLER    *Usb3Hc,
    HC_STRUC                *HcStruc,
    XHCI_PORTSTSCHG_EVT_TRB	*PortStsChgEvtTrb
)
{
    DEV_INFO	*DevInfo;
	UINT8		i;

	if (((Usb3Hc->Vid != XHCI_FL100X_VID) || (Usb3Hc->Did != XHCI_FL1000_DID &&
		Usb3Hc->Did != XHCI_FL1009_DID)) && (Usb3Hc->Vid != XHCI_INTEL_VID)) {
		return;
	}

	if (!(HcReadOpReg(HcStruc, XHCI_PORTSC_OFFSET + (0x10 * (PortStsChgEvtTrb->PortId - 1))) & XHCI_PCS_CCS)) {
		for (i = 1; i < MAX_DEVICES; i++) {
			DevInfo = &gUsbData->aDevInfoTable[i];
		    if ((DevInfo->Flag & DEV_INFO_VALIDPRESENT)
                != DEV_INFO_VALIDPRESENT) {
			    continue;
		    }
			if ((DevInfo->bHubDeviceNumber == (HcStruc->bHCNumber | BIT7)) &&
				DevInfo->bHubPortNumber == PortStsChgEvtTrb->PortId) {
				DevInfo->Flag |= DEV_INFO_DEV_DISCONNECTING;
			}
		}
	}
}
										//<(EIP60460+)

/**
    This is the XHCI controller event handler. It walks through
    the Event Ring and executes the event associated code if needed. Updates
    the Event Ring Data Pointer in the xHC to let it know which events are
    completed.

    @param 
        HcStruc  - Pointer to the HC structure

         
    @retval USB_ERROR Need more Interrupt processing
    @retval USB_SUCCESS No interrupts pending

**/

UINT8
XHCI_ProcessInterrupt(
    HC_STRUC    *HcStruc
)
{
    XHCI_TRB        *Trb;
    UINTN           XhciBaseAddress;
    UINT32          XhciLegCtrlSts;
    UINT32          XhciLegSup;
    UINT32          Imod;

    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;

    
	if (!(HcReadPciReg(HcStruc, USB_REG_COMMAND) & BIT1)) {
		return USB_SUCCESS;
	}

    XhciBaseAddress = HcReadPciReg(HcStruc, USB_MEM_BASE_ADDRESS);
    if (((XhciBaseAddress & (BIT1 | BIT2)) == BIT2) && ((sizeof(VOID*) / sizeof(UINT32) == 2))){
        XhciBaseAddress |= LShiftU64((UINTN)HcReadPciReg(HcStruc, USB_MEM_BASE_ADDRESS + 0x04), 32);
    }

    XhciBaseAddress &= ~(0x7F);

	if (XhciBaseAddress != HcStruc->BaseAddress) {
	    HcStruc->BaseAddress = XhciBaseAddress;
        Usb3Hc->OpRegs = (XHCI_HC_OP_REGS*)(XhciBaseAddress + Usb3Hc->CapRegs.CapLength);
        Usb3Hc->RtRegs = (XHCI_HC_RT_REGS*)(XhciBaseAddress + Usb3Hc->CapRegs.RtsOff);
	}
	
    // Check if host controller interface version number is valid.
    if (Usb3Hc->CapRegs.HciVersion == 0xFFFF) {
        return USB_SUCCESS;
    }
	
	// Check if USB Legacy Support Capability is present.
    if (Usb3Hc->UsbLegSupOffSet) {
        // Is ownership change?
        XhciLegCtrlSts = HcReadHcMem(HcStruc, Usb3Hc->UsbLegSupOffSet + XHCI_LEGACY_CTRL_STS_REG);
        if ((XhciLegCtrlSts & (XHCI_SMI_OWNERSHIP_CHANGE_ENABLE | XHCI_SMI_OWNERSHIP_CHANGE))
            == (XHCI_SMI_OWNERSHIP_CHANGE_ENABLE | XHCI_SMI_OWNERSHIP_CHANGE)) {
            // Clear Ownership change SMI status
            HcSetHcMem(HcStruc, Usb3Hc->UsbLegSupOffSet + XHCI_LEGACY_CTRL_STS_REG,
                            XHCI_SMI_OWNERSHIP_CHANGE);
            // Process ownership change event
            XhciLegSup = HcReadHcMem(HcStruc, Usb3Hc->UsbLegSupOffSet);
            if ((XhciLegSup & XHCI_OS_OWNED_SEMAPHORE) && 
                    (HcStruc->dHCFlag & HC_STATE_RUNNING)) {
                gUsbData->dUSBStateFlag &= (~USB_FLAG_ENABLE_BEEP_MESSAGE);
                USB_DEBUG(3, "XHCI: Ownership change to XHCD\n");
                XHCI_Stop(HcStruc);
                if ((gUsbData->UsbXhciHandoff == 0) && (gEmulationTrap != NULL)) {
                    if (!(gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI)) {
                        gEmulationTrap->TrapDisable(gEmulationTrap);
                    }
                }
            } else if (!(XhciLegSup & XHCI_OS_OWNED_SEMAPHORE) &&
                    (HcStruc->dHCFlag & HC_STATE_RUNNING) == 0) {
                gUsbData->dUSBStateFlag |= USB_FLAG_ENABLE_BEEP_MESSAGE;
                USB_DEBUG(3, "XHCI: Ownership change to BIOS\n");
                XHCI_Start(HcStruc);
                if ((gUsbData->UsbXhciHandoff == 0) && (gEmulationTrap != NULL)) {
                    if (!(gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI)) {
                        gEmulationTrap->TrapEnable(gEmulationTrap);
                    }
                }
		    }
			return USB_SUCCESS;
        }
    }
	
    if ((HcStruc->dHCFlag & HC_STATE_RUNNING) == 0) {
        return USB_SUCCESS;
    }

    if (XHCI_Mmio64Read(HcStruc, Usb3Hc, (UINTN)&Usb3Hc->OpRegs->DcbAap) != 
        (UINT64)(UINTN)Usb3Hc->DcbaaPtr) {
        return USB_SUCCESS;
    }

    if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_PCD) {
        //XHCI_EnumeratePorts(HcStruc);
        XHCI_ProcessPortChanges(HcStruc, Usb3Hc);
    }

//    if (Usb3Hc->OpRegs->UsbSts.Field.Eint == 0) return USB_SUCCESS;
//    Usb3Hc->OpRegs->UsbSts.AllBits = XHCI_STS_EVT_INTERRUPT;    // Clear event interrupt
    if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_EVT_INTERRUPT) {
        HcWriteOpReg(HcStruc, XHCI_USBSTS_OFFSET, XHCI_STS_EVT_INTERRUPT);  
        HcSetHcMem(HcStruc, 
            (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs[0].IMan - HcStruc->BaseAddress), BIT0);
    }
    
    if (gUsbData->fpKeyRepeatHCStruc == HcStruc) {
        Imod = HcReadHcMem(HcStruc, (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMod - HcStruc->BaseAddress));
        if ((Imod & XHCI_KEYREPEAT_IMODI) == XHCI_KEYREPEAT_IMODI) {
            if ((Imod >> 16) >= (XHCI_KEYREPEAT_IMODC & 0xF000)) {
                USBKBDPeriodicInterruptHandler(HcStruc);
            }
        }
    }
    
    // Check for pending interrupts:
    // check the USBSTS[3] and IMAN [0] to determine if any interrupt generated
    if (Usb3Hc->EvtRing.QueuePtr->CycleBit != Usb3Hc->EvtRing.CycleBit) {
        if (gUsbData->fpKeyRepeatHCStruc == HcStruc) {
            Imod = HcReadHcMem(HcStruc, (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMod - HcStruc->BaseAddress));
            if ((Imod & XHCI_KEYREPEAT_IMODI) == XHCI_KEYREPEAT_IMODI) {
                XHCI_Mmio64Write(HcStruc, Usb3Hc,
                    (UINTN)&Usb3Hc->RtRegs->IntRegs->Erdp, (UINT64)(UINTN)0 | BIT3);
                HcWriteHcMem(HcStruc, 
                    (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMod - HcStruc->BaseAddress),
                    XHCI_KEYREPEAT_IMODC << 16 | XHCI_KEYREPEAT_IMODI);
            }
        }
        return USB_SUCCESS;
    }

    // See if there are any TRBs waiting in the event ring
    //for (Count = 0; Count < Usb3Hc->EvtRing.Size; Count++) {
    for (;;) {
        Trb = Usb3Hc->EvtRing.QueuePtr;

        if (Trb->CycleBit != Usb3Hc->EvtRing.CycleBit) {
            break;  // past the last
        }

		if (Usb3Hc->EvtRing.QueuePtr == Usb3Hc->EvtRing.LastTrb) {
			// Reached the end of the ring, wrap around
			Usb3Hc->EvtRing.QueuePtr = Usb3Hc->EvtRing.Base;
			Usb3Hc->EvtRing.CycleBit ^= 1;
		} else {
			Usb3Hc->EvtRing.QueuePtr++;
		}
        // error manager
        if (Trb->CompletionCode == XHCI_TRB_SHORTPACKET) {
            USB_DEBUG(3, "XHCI: short packet detected.");
        }

        if (Trb->CompletionCode == XHCI_TRB_STALL_ERROR) {
            USB_DEBUG(3, "XHCI: device STALLs.");
        }

        if (Trb->CompletionCode != XHCI_TRB_SUCCESS
                && Trb->CompletionCode != XHCI_TRB_STALL_ERROR
                && Trb->CompletionCode != XHCI_TRB_SHORTPACKET) {
            USB_DEBUG(3, "Trb completion code: %d\n", Trb->CompletionCode);
            //ASSERT(FALSE);
        }

        switch (Trb->TrbType) {
            case XhciTTransferEvt:
// very frequent, debug message here might affect timings,
// uncomment only when needed
//              USB_DEBUG(3, "TransferEvt\n");
                XHCI_ProcessXferEvt(Usb3Hc, HcStruc, (XHCI_TRANSFER_EVT_TRB*)Trb);
                break;
            case XhciTCmdCompleteEvt:
                USB_DEBUG(3, "CmdCompleteEvt\n");
                break;
            case XhciTPortStatusChgEvt:
                USB_DEBUG(3, "PortStatusChgEvt, port #%d\n", ((XHCI_PORTSTSCHG_EVT_TRB*)Trb)->PortId);
				XHCI_ProcessPortStsChgEvt(Usb3Hc, HcStruc, (XHCI_PORTSTSCHG_EVT_TRB*)Trb);	//(EIP60460+)
                break;
            case XhciTDoorbellEvt:
                USB_DEBUG(3, "DoorbellEvt\n");
                break;
            case XhciTHostControllerEvt:
                USB_DEBUG(3, "HostControllerEvt\n");
                break;
            case XhciTDevNotificationEvt:
                USB_DEBUG(3, "DevNotificationEvt\n");
                break;
            case XhciTMfIndexWrapEvt:
                USB_DEBUG(3, "MfIndexWrapEvt\n");
                break;
            default:
                USB_DEBUG(3, "UNKNOWN EVENT\n");
        }
    }
    //ASSERT(Count<Usb3Hc->EvtRing.Size);    // Event ring is full

	// Update ERDP to inform xHC that we have processed another TRB
    if ((gUsbData->fpKeyRepeatHCStruc == HcStruc) && 
        ((HcReadHcMem(HcStruc, (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMod - HcStruc->BaseAddress))
            & XHCI_KEYREPEAT_IMODI) == XHCI_KEYREPEAT_IMODI)) {
        XHCI_Mmio64Write(HcStruc, Usb3Hc,
                (UINTN)&Usb3Hc->RtRegs->IntRegs->Erdp, (UINT64)(UINTN)0 | BIT3);
    } else {
        XHCI_Mmio64Write(HcStruc, Usb3Hc,
                (UINTN)&Usb3Hc->RtRegs->IntRegs->Erdp, (UINT64)(UINTN)Usb3Hc->EvtRing.QueuePtr | BIT3);
    }

    return  USB_SUCCESS;    // Set as interrupt processed
}


/**
    This function returns the port connect status for the root hub port

    @param 
        HcStruc  - Pointer to the HC structure
        PortNum  - Port in the HC whose status is requested

    @retval 
        Port status flags (see USB_PORT_STAT_XX equates)

**/

UINT8
XHCI_GetRootHubStatus(
    HC_STRUC*   HcStruc,
    UINT8       PortNum,
    BOOLEAN     ClearChangeBits
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    UINT32  i;
    UINT8   PortStatus = USB_PORT_STAT_DEV_OWNER;
    UINT32  PortStsOffset = XHCI_PORTSC_OFFSET + (0x10 * (PortNum-1));
    UINT32  XhciPortSts;
    XHCI_PORTSC *PortSts = (XHCI_PORTSC*)(&XhciPortSts);

    // Find the proper MMIO access offset for a given port

    XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);

	USB_DEBUG(3, "XHCI port[%d] status: %08x\n", PortNum, XhciPortSts);

    for (i = 0; i < 200; i++) {
        if (PortSts->Field.Pr == 0) {
            break;
        }
		FixedDelay(1 * 1000);
        XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
	}
	
	switch (PortSts->Field.Pls) {
		case XHCI_PORT_LINK_U0:
		case XHCI_PORT_LINK_RXDETECT:
			break;
		case XHCI_PORT_LINK_RECOVERY:
			for (i = 0; i < 200; i++) {
				FixedDelay(1 * 1000);
                XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
				if (PortSts->Field.Pls != XHCI_PORT_LINK_RECOVERY) {
					break;
				}
			}
			break;
		case XHCI_PORT_LINK_POLLING:
			if (!XHCI_IsUsb3Port(Usb3Hc, PortNum)) {
				break;
			}
			for (i = 0; i < 500; i++) {
				FixedDelay(1 * 1000);
                XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
				if (PortSts->Field.Pls != XHCI_PORT_LINK_POLLING) {
					break;
				}
			}
			if (PortSts->Field.Pls == XHCI_PORT_LINK_U0 || 
				PortSts->Field.Pls == XHCI_PORT_LINK_RXDETECT) {
				break;
			}
            XHCI_ResetPort(HcStruc, Usb3Hc, PortNum, TRUE);
			break;
		case XHCI_PORT_LINK_INACTIVE:
			for (i = 0; i < 12; i++) {
				FixedDelay(1 * 1000);
                XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
				if (PortSts->Field.Pls != XHCI_PORT_LINK_INACTIVE) {
					break;
				}
			}
            if (PortSts->Field.Pls == XHCI_PORT_LINK_RXDETECT) {
                break;
			}
		case XHCI_PORT_LINK_COMPLIANCE_MODE:
			XHCI_ResetPort(HcStruc, Usb3Hc, PortNum, TRUE);
			break;
		default:
			PortStatus |= USB_PORT_STAT_DEV_CONNECTED;
			break;
	}
	
    XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
    
    if (PortSts->Field.Ccs != 0) {
        PortStatus |= USB_PORT_STAT_DEV_CONNECTED;
		UpdatePortStatusSpeed(PortSts->Field.PortSpeed, &PortStatus);
        
        // USB 3.0 device may not set Connect Status Change bit after reboot,
        // set the connect change flag when we enumerate HC ports for devices.
        if (gUsbData->bIgnoreConnectStsChng == TRUE) {
            PortStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED;
        }

		if (PortSts->Field.Ped) {
			PortStatus |= USB_PORT_STAT_DEV_ENABLED;
		}
    }

    if (PortSts->Field.Csc != 0) {
										//(EIP58979+)>
		if (Usb3Hc->Vid == XHCI_TUSB73X0_VID && Usb3Hc->Did == XHCI_TUSB73X0_DID) {
			if (PortSts->Field.Ccs != 0) {
				FixedDelay(20 * 1000);
			}
		}
										//<(EIP58979+)
        PortStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED;

		// Clear connect status change bit
		HcWriteOpReg(HcStruc, PortStsOffset, XHCI_PCS_CSC | XHCI_PCS_PP);
    }
    if (ClearChangeBits == TRUE) {
        // Clear all status change bits
        XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
        HcWriteOpReg(HcStruc, PortStsOffset, XhciPortSts & ~XHCI_PCS_PED); // DO NOT TOUCH PED
    }
    return PortStatus;
}


/**
    This function enables the XHCI HC Root hub port.

    @param 
        HcStruc   - Pointer to the HC structure
        PortNum   - Port in the HC to enable

    @retval 
        USB_SUCCESS on success, USB_ERROR on error

**/

UINT8
XHCI_EnableRootHub(
    HC_STRUC*   HcStruc,
    UINT8       PortNum
)
{
    return USB_SUCCESS;
}


/**
    This function disables the XHCI HC Root hub port.

    @param 
        HcStruc - Pointer to the HC structure
        PortNum - Port in the HC to disable

    @retval 
        USB_SUCCESS on success, USB_ERROR on error

**/

UINT8
XHCI_DisableRootHub(
    HC_STRUC    *HcStruc,
    UINT8       PortNum
)
{
	USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    UINT32  PortStsOffset = XHCI_PORTSC_OFFSET + (0x10 * (PortNum - 1));
    UINT8	i = 0;

    USB_DEBUG(3, "Disable XHCI root port %d\n", PortNum);

    if (HcReadOpReg(HcStruc, PortStsOffset) & XHCI_PCS_PED) {
		if (XHCI_IsUsb3Port(Usb3Hc, PortNum)) {
			XHCI_ResetPort(HcStruc, Usb3Hc, PortNum, FALSE);
		} else {
		    HcWriteOpReg(HcStruc, PortStsOffset, XHCI_PCS_PED | XHCI_PCS_PP);
			for (i = 0; i < 200; i++) {
                if (!(HcReadOpReg(HcStruc, PortStsOffset) & XHCI_PCS_PED)) {
					break;
				}
				FixedDelay(100);
			}
		}
	}

    return USB_SUCCESS;
}

/**
    This function resets the XHCI HC Root hub port.

    @param 
        HcStruc - Pointer to the HC structure
        PortNum - Port in the HC to disable

    @retval 
        USB_SUCCESS on success, USB_ERROR on error

**/

UINT8
XHCI_ResetPort(
    HC_STRUC                    *HcStruc,
    USB3_HOST_CONTROLLER	    *Usb3Hc,
    UINT8					    Port,
    BOOLEAN                     WarmReset
)
{
	UINT32	i;
    UINT32  PortStsOffset = XHCI_PORTSC_OFFSET + (0x10 * (Port - 1));
    UINT32  XhciPortSts;

    if (WarmReset && XHCI_IsUsb3Port(Usb3Hc, Port)) {
        HcWriteOpReg(HcStruc, PortStsOffset, XHCI_PCS_WPR | XHCI_PCS_PP);			
		for (i = 0; i < 6000; i++) {     //(EIP93368)
		    XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
            if ((XhciPortSts & XHCI_PCS_WRC) || (XhciPortSts & XHCI_PCS_PRC)) {
                break;
            }
            FixedDelay(100);
		}
		//ASSERT((XhciPortSts & XHCI_PCS_WRC) || (XhciPortSts & XHCI_PCS_PRC));
        if ((!(XhciPortSts & XHCI_PCS_WRC)) && (!(XhciPortSts & XHCI_PCS_PRC))) {
			return USB_ERROR;
		}

		if (Usb3Hc->Vid == XHCI_EJ168A_VID && Usb3Hc->Did == XHCI_EJ168A_DID) {
			FixedDelay(20 * 1000);
		}
    } else {
        // Keep port power bit
        HcWriteOpReg(HcStruc, PortStsOffset, XHCI_PCS_PR | XHCI_PCS_PP);
		for (i = 0; i < 3000; i++) {
            XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
            if (XhciPortSts & XHCI_PCS_PRC) {
                break;
            }
            FixedDelay(100);
		}
		//ASSERT(XhciPortSts & XHCI_PCS_PRC);
		if (!(XhciPortSts & XHCI_PCS_PRC)) {
			return USB_ERROR;
		}
	}

	// Clear Warm Port Reset Change and Port Reset Change bits
	HcWriteOpReg(HcStruc, PortStsOffset, XHCI_PCS_WRC | XHCI_PCS_PRC | XHCI_PCS_PP);

	return USB_SUCCESS;	
}

/**
    This function resets the XHCI HC Root hub port.

    @param 
        HcStruc - Pointer to the HC structure
        PortNum - Port in the HC to disable

    @retval 
        USB_SUCCESS on success, USB_ERROR on error

**/

UINT8
XHCI_ResetRootHub(
    HC_STRUC*   HcStruc,
    UINT8		PortNum
)
{
	USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
	UINT8	Status;

	Status = XHCI_ResetPort(HcStruc, Usb3Hc, PortNum, FALSE);
	
	if (!XHCI_IsUsb3Port(Usb3Hc, PortNum)) {
		// After a short delay, SS device that was originally connected to HS port 
		// might get reconnected to the SS port...
		FixedDelay(XHCI_SWITCH2SS_DELAY_MS * 1000);
	}

	return Status;
}

										//(EIP54018+)>
/**
    This function suspend the XHCI HC.

**/

UINT8
XHCI_GlobalSuspend(
    HC_STRUC*	HcStruc
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    UINT32          Port;
    UINT32          i;
    UINT32          XhciPortSts;
    XHCI_PORTSC     *PortSts = (XHCI_PORTSC*)&XhciPortSts;
    UINT32          PortStsOffset;

    for (Port = 1; Port <= Usb3Hc->CapRegs.HcsParams1.MaxPorts; Port++) {

        PortStsOffset = XHCI_PORTSC_OFFSET + (0x10 * (Port - 1));

        XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
        
        USB_DEBUG(3, "XHCI port[%d] status: %08x\n", Port, PortSts->AllBits);
        if ((PortSts->Field.Ped) && (PortSts->Field.Pls <XHCI_PORT_LINK_U3)){
            XhciPortSts |= (XHCI_PCS_LWS | (UINT32)(XHCI_PORT_LINK_U3 << 5));
            HcWriteOpReg(HcStruc, PortStsOffset, XhciPortSts & ~XHCI_PCS_PED);
            for (i = 0;i < 10; i++) {
                XhciPortSts = HcReadOpReg(HcStruc, PortStsOffset);
                if (PortSts->Field.Pls == XHCI_PORT_LINK_U3) {
                    break;
                }
                FixedDelay(1 * 1000);
            }
        }
    }
    
    HcClearOpReg(HcStruc, XHCI_USBCMD_OFFSET, XHCI_CMD_RS);
    
    for (i = 0; i < 16; i++) {
        FixedDelay(1 * 1000);
        if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED) {
            break;
        }
    }

    HcStruc->dHCFlag &= ~(HC_STATE_RUNNING);
    HcStruc->dHCFlag |= HC_STATE_SUSPEND;
   
    return  USB_SUCCESS;
}
										//<(EIP54018+)

/**
    This function resets the XHCI controller

    @param Pointer to the HcStruc structure

    @retval USB_SUCCESS     HC successfully reset
            USB_ERROR       Error
**/

UINT8
XhciResetHc(
    HC_STRUC    *HcStruc
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    UINT32  DbCapDcctrl;
    UINT32  i;

    if (Usb3Hc->DbCapOffset) {
        DbCapDcctrl = HcReadHcMem(HcStruc, Usb3Hc->DbCapOffset + XHCI_DB_CAP_DCCTRL_REG);
        // Don't reset xhci controller if it's Debug Capability is enabled.
        if (DbCapDcctrl & XHCI_DB_CAP_DCE) {
            return USB_SUCCESS;
        }
    }
    // Reset controller
    HcSetOpReg(HcStruc, XHCI_USBCMD_OFFSET, XHCI_CMD_HCRST);
    FixedDelay(1 * 1000); // 1 ms delay
    for (i = 0; i < 8000; i++) {
        if (!(HcReadOpReg(HcStruc, XHCI_USBCMD_OFFSET) & XHCI_CMD_HCRST)) {
            break;
        }
        FixedDelay(100);    // 100 us delay
    }
    ASSERT(!(HcReadOpReg(HcStruc, XHCI_USBCMD_OFFSET) & XHCI_CMD_HCRST));
    if (HcReadOpReg(HcStruc, XHCI_USBCMD_OFFSET) & XHCI_CMD_HCRST) {
        return USB_ERROR;  // Controller can not be reset
    }
    
    return USB_SUCCESS;
}
										
/**
    This function verifies the MaxPacket size of the control pipe. If it does
    not match the one received as a part of GET_DESCRIPTOR, then this function
    updates the MaxPacket data in DeviceContext and HC is notified via
    EvaluateContext command.

    @param 
        HcStruc Pointer to the HC structure
        Device  Evaluated device context pointer
        SlotId  Device context index in DCBAA
        Endp0MaxPacket  Max packet size obtained from the device

**/

VOID
XHCI_UpdateEp0MaxPacket(
    HC_STRUC            *HcStruc,
    UINT8               SlotId,
    UINT8               Endp0MaxPacket
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    UINT8   Status;
	UINT8	*DevCtx;
	XHCI_INPUT_CONTROL_CONTEXT	*CtlCtx;
	XHCI_SLOT_CONTEXT			*SlotCtx;
	XHCI_EP_CONTEXT				*EpCtx;

	DevCtx = (UINT8*)XHCI_GetDeviceContext(Usb3Hc, SlotId);

	SlotCtx = (XHCI_SLOT_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, DevCtx, 0);
	if (SlotCtx->Speed != XHCI_DEVSPEED_FULL) return;

	EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, DevCtx, 1);
	if (EpCtx->MaxPacketSize == Endp0MaxPacket) return;

    // Prepare input context for EvaluateContext comand
	MemSet((UINT8*)Usb3Hc->InputContext, XHCI_INPUT_CONTEXT_ENTRIES * Usb3Hc->ContextSize, 0);

    CtlCtx = (XHCI_INPUT_CONTROL_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 0);
    CtlCtx->AddContextFlags = BIT1;

	EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 2);
    EpCtx->MaxPacketSize = Endp0MaxPacket;

    Status = XHCI_ExecuteCommand(HcStruc, XhciTEvaluateContextCmd, &SlotId);
    ASSERT(Status == USB_SUCCESS);
}


/**
    This function executes a device request command transaction on the USB.
    One setup packet is generated containing the device request parameters
    supplied by the caller.  The setup packet may be followed by data in or
    data out packets containing data sent from the host to the device or
    vice-versa. This function will not return until the request either completes
    successfully or completes in error (due to time out, etc.)

    @param 
        HcStruc     Pointer to the HC structure
        DevInfo     DeviceInfo structure (if available else 0)
        Request     Request type (low byte)
        Bit 7   : Data direction
        0 = Host sending data to device
        1 = Device sending data to host
        Bit 6-5 : Type
        00 = Standard USB request
        01 = Class specific
        10 = Vendor specific
        11 = Reserved
        Bit 4-0 : Recipient
        00000 = Device
        00001 = Interface
        00010 = Endpoint
        00100 - 11111 = Reserved
        Request code, a one byte code describing the actual
        device request to be executed (ex: Get Configuration,
        Set Address, etc.)
        Index   wIndex request parameter (meaning varies)
        Value   wValue request parameter (meaning varies)
        Buffer  Buffer containing data to be sent to the device or buffer
        to be used to receive data
        Length  wLength request parameter, number of bytes of data to be
        transferred in or out of the host controller

    @retval 
        Number of bytes actually transferred

    @note  
  DevInfo->DevMiscInfo points to the device context

**/

UINT16
XHCI_ControlTransfer (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT16      Request,
    UINT16      Index,
    UINT16      Value,
    UINT8       *Buffer,
    UINT16      Length
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    XHCI_TRB    *Trb;
    UINT8       SlotId;
    UINT8       CompletionCode;
    UINT8       Status;
    TRB_RING    *XfrRing;
    UINT16		TimeoutMs;
    XHCI_SLOT_CONTEXT	*SlotCtx = NULL;
    UINT8       *BufPhyAddr = NULL;
    VOID        *BufferMapping = NULL;
	
    if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED) {
        return 0;
    }


    ASSERT(DevInfo != NULL);

	if(DevInfo->Flag & DEV_INFO_DEV_DISCONNECTING) return 0;	//(EIP60460+)
	if(DevInfo->DevMiscInfo == NULL) return 0;

    SlotId = XHCI_GetSlotId(Usb3Hc, DevInfo);

    // Skip SET_ADDRESS request if device is in addressed state
    if (Request == USB_RQ_SET_ADDRESS) {
        SlotCtx = XHCI_GetContextEntry(Usb3Hc, DevInfo->DevMiscInfo, 0);
	
        if (SlotCtx->SlotState == XHCI_SLOT_STATE_DEFAULT) {
            Status = XhciAddressDevice(HcStruc, DevInfo, SlotId);
        }
        return Length;
    }

	TimeoutMs = gUsbData->wTimeOutValue != 0 ? XHCI_CTL_COMPLETE_TIMEOUT_MS : 0;

    gUsbData->bLastCommandStatus &= ~(USB_CONTROL_STALLED);
    gUsbData->dLastCommandStatusExtended = 0;

    // Insert Setup, Data(if needed), and Status TRBs into the transfer ring
    XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, 0);

    // Setup TRB
    Trb = XHCI_AdvanceEnqueuePtr(XfrRing);
    Trb->TrbType = XhciTSetupStage;
    ((XHCI_SETUP_XFR_TRB*)Trb)->Idt = 1;
    *(UINT16*)&((XHCI_SETUP_XFR_TRB*)Trb)->bmRequestType = Request;
    ((XHCI_SETUP_XFR_TRB*)Trb)->wValue = Value;
    ((XHCI_SETUP_XFR_TRB*)Trb)->wIndex = Index;
    ((XHCI_SETUP_XFR_TRB*)Trb)->wLength = Length;
    ((XHCI_SETUP_XFR_TRB*)Trb)->XferLength = 8;

	if (Usb3Hc->CapRegs.HciVersion >= 0x100) {
		if (Length != 0) {
			if (Request & USB_REQ_TYPE_INPUT) {
				((XHCI_SETUP_XFR_TRB*)Trb)->Trt = XHCI_XFER_TYPE_DATA_IN;
			} else {
				((XHCI_SETUP_XFR_TRB*)Trb)->Trt = XHCI_XFER_TYPE_DATA_OUT;
			}
		} else {
			((XHCI_SETUP_XFR_TRB*)Trb)->Trt = XHCI_XFER_TYPE_NO_DATA;
		}
	}
	 ((XHCI_SETUP_XFR_TRB*)Trb)->CycleBit = XfrRing->CycleBit;
	
    // Data TRB
    if (Length != 0) {
        Trb = XHCI_AdvanceEnqueuePtr(XfrRing);
        Trb->TrbType = XhciTDataStage;
        HcDmaMap(HcStruc, (UINT8)(Request & BIT7), Buffer, Length, 
			&BufPhyAddr, &BufferMapping);
        ((XHCI_DATA_XFR_TRB*)Trb)->Dir = ((Request & USB_REQ_TYPE_INPUT) != 0)? 1 : 0;
        ((XHCI_DATA_XFR_TRB*)Trb)->XferLength = Length;
        ((XHCI_DATA_XFR_TRB*)Trb)->DataBuffer = (UINT64)(UINTN)BufPhyAddr;
		((XHCI_DATA_XFR_TRB*)Trb)->CycleBit = XfrRing->CycleBit;
    }

    // Status TRB
    Trb = XHCI_AdvanceEnqueuePtr(XfrRing);
    Trb->TrbType = XhciTStatusStage;
    ((XHCI_STATUS_XFR_TRB*)Trb)->Ioc = 1;
    if ((Request & USB_REQ_TYPE_INPUT) == 0) {
        ((XHCI_STATUS_XFR_TRB*)Trb)->Dir = 1;   // Status is IN
    }
	((XHCI_STATUS_XFR_TRB*)Trb)->CycleBit = XfrRing->CycleBit;

    // Ring the doorbell and see Event Ring update
    Status = XhciRingDoorbell(Usb3Hc, HcStruc, SlotId, 1);

    if (Status != USB_SUCCESS) {
        return 0;
    }

    Status = XHCI_WaitForEvent(
                HcStruc, Trb, XhciTTransferEvt, SlotId, 1,					//(EIP62376)
                &CompletionCode, TimeoutMs, NULL);
    
    if (Length != 0) {
        HcDmaUnmap(HcStruc, BufferMapping);
    }

	if (Status != USB_SUCCESS) {
										//(EIP54283)>
		switch (CompletionCode) {
			case XHCI_TRB_BABBLE_ERROR:								//(EIP62376+)
			case XHCI_TRB_TRANSACTION_ERROR:
				XHCI_ClearStalledEp(Usb3Hc, HcStruc, SlotId, 1);	//(EIP60460+)
				break;												//(EIP60460+)
			case XHCI_TRB_STALL_ERROR:
				XHCI_ClearStalledEp(Usb3Hc, HcStruc, SlotId, 1);
				gUsbData->bLastCommandStatus |= USB_CONTROL_STALLED;
				break;
										//(EIP84790+)>
            case XHCI_TRB_EXECUTION_TIMEOUT_ERROR:
				XHCI_ClearEndpointState(HcStruc, DevInfo, 0);
                gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
                break;
										//<(EIP84790+)
			default:
				break;
		}
										//<(EIP54283)
		Length = 0;
	}

    if (Request == USB_RQ_GET_DESCRIPTOR && Length == 8) {
        // Full speed device requires the update of MaxPacket size
        XHCI_UpdateEp0MaxPacket(HcStruc, SlotId, ((DEV_DESC*)Buffer)->bEndp0MaxPacket);
    }
    
    return Length;
}


/**
    This function executes a bulk transaction on the USB

    @param 
        HcStruc   Pointer to HCStruc of the host controller
        DevInfo   DeviceInfo structure (if available else 0)
        XferDir   Transfer direction
        Bit 7: Data direction
        0 Host sending data to device
        1 Device sending data to host
        Bit 6-0 : Reserved
        Buffer    Buffer containing data to be sent to the device or buffer to
        be used to receive data value
        Length    Length request parameter, number of bytes of data to be
        transferred in or out of the HC

    @retval 
        Amount of data transferred

**/

UINT32
XHCI_BulkTransfer(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       XferDir,
    UINT8       *Buffer,
    UINT32      Length
)
{
    USB3_HOST_CONTROLLER *Usb3Hc;
    XHCI_TRB    *Trb;
    XHCI_TRB    *FirstTrb;
    UINT8       SlotId;
    UINT8       CompletionCode;
    UINT8       Status;
    TRB_RING    *XfrRing;
    UINT8       Endpoint;
    UINT8       Dci;
    UINT64      DataPointer;
    UINT32      ResidualData;       // Transferred amount return by Transfer Event
    UINT32      TransferredSize;    // Total transfer amount
    UINT32      RingDataSize;       // One TRB ring transfer amount
    UINT32      RemainingXfrSize;
    UINT32      RemainingDataSize;
    UINT32      XfrSize;
    UINT32      XfrTdSize;
	UINT16		MaxPktSize;
	UINT32		TdSize;
	UINT16		TimeoutMs;
    UINT8       *BufPhyAddr = NULL;
    VOID        *BufferMapping = NULL;

    // Clear HW source of error
    gUsbData->bLastCommandStatus &= ~(USB_BULK_STALLED | USB_BULK_TIMEDOUT );
    gUsbData->dLastCommandStatusExtended = 0;

    if (DevInfo->Flag & DEV_INFO_DEV_DISCONNECTING) {
        return 0;   //(EIP60460+)
    }
    if (DevInfo->DevMiscInfo == NULL) {
        return 0;
    }

	TimeoutMs = gUsbData->wTimeOutValue;

    Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
	
    if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED) {
        return 0;
    }
	
    SlotId = XHCI_GetSlotId(Usb3Hc, DevInfo);
    Endpoint = (XferDir & BIT7)? DevInfo->bBulkInEndpoint : DevInfo->bBulkOutEndpoint;
	MaxPktSize = (XferDir & BIT7)? DevInfo->wBulkInMaxPkt : DevInfo->wBulkOutMaxPkt;
    Dci = (Endpoint & 0xf)* 2;
    if (XferDir & BIT7) {
        Dci++;
    }

    XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, Dci-1);

    // Make a chain of TDs to transfer the requested amount of data. If necessary,
    // make multiple transfers in a loop.

    HcDmaMap(HcStruc, XferDir, Buffer, Length, &BufPhyAddr, &BufferMapping);

    DataPointer = (UINT64)(UINTN)BufPhyAddr;
    RemainingDataSize = Length;

    // Two loops are executing the transfer:
    // The inner loop creates a transfer ring of chained TDs, XHCI_BOT_TD_MAXSIZE
    // bytes each. This makes a ring capable of transferring
    // XHCI_BOT_TD_MAXSIZE * (TRBS_PER_SEGMENT-1) bytes.
    // The outter loop repeats the transfer if the requested transfer size exceeds
    // XHCI_BOT_TD_MAXSIZE * (TRBS_PER_SEGMENT-1).

    for (TransferredSize = 0; TransferredSize < Length;) {
        // Calculate the amount of data to transfer in the ring
        RingDataSize = (RemainingDataSize > XHCI_BOT_MAX_XFR_SIZE)?
            XHCI_BOT_MAX_XFR_SIZE : RemainingDataSize;

        RemainingXfrSize = RingDataSize;

        for (Trb = NULL, XfrSize = 0, FirstTrb = 0; XfrSize < RingDataSize;)
        {
            Trb = XHCI_AdvanceEnqueuePtr(XfrRing);
            if (FirstTrb == NULL) FirstTrb = Trb;

            Trb->TrbType = XhciTNormal;
            ((XHCI_NORMAL_XFR_TRB*)Trb)->Isp = 1;
            ((XHCI_NORMAL_XFR_TRB*)Trb)->DataBuffer = DataPointer;

            // See if we need a TD chain. Note that we do not need to
            // place the chained TRB into Event Ring, since we will not be
            // looking for it anyway. Set IOC only for the last-in-chain TRB.
            if (RemainingXfrSize > XHCI_BOT_TD_MAXSIZE) {
                XfrTdSize = XHCI_BOT_TD_MAXSIZE;
                ((XHCI_NORMAL_XFR_TRB*)Trb)->Chain = 1;
            } else {
                ((XHCI_NORMAL_XFR_TRB*)Trb)->Ioc = 1;
                XfrTdSize = RemainingXfrSize;
            }
			// Data buffers referenced by Transfer TRBs shall not span 64KB boundaries. 
			// If a physical data buffer spans a 64KB boundary, software shall chain 
			// multiple TRBs to describe the buffer.
			if (XfrTdSize > (UINT32)(0x10000 - (DataPointer & (0x10000 - 1)))) {
				XfrTdSize = (UINT32)(0x10000 - (DataPointer & (0x10000 - 1)));
				((XHCI_NORMAL_XFR_TRB*)Trb)->Chain = 1;
				((XHCI_NORMAL_XFR_TRB*)Trb)->Ioc = 0;
			}

            ((XHCI_NORMAL_XFR_TRB*)Trb)->XferLength = XfrTdSize;

            XfrSize += XfrTdSize;
            DataPointer += XfrTdSize;
            RemainingXfrSize -= XfrTdSize;

			if (Usb3Hc->CapRegs.HciVersion >= 0x100) {
				TdSize = 0;
				if (RemainingXfrSize != 0) {
					TdSize = RemainingXfrSize/MaxPktSize;
					if (RemainingXfrSize % MaxPktSize) {
						TdSize++;
					}
					TdSize = (TdSize > 31)? 31 : TdSize;
				}
			} else {
				TdSize = RemainingXfrSize + XfrTdSize;
				TdSize = (TdSize < 32768)? (TdSize >> 10) : 31;
			}

			((XHCI_NORMAL_XFR_TRB*)Trb)->TdSize = TdSize;
			if (Trb != FirstTrb) {
				((XHCI_NORMAL_XFR_TRB*)Trb)->CycleBit = XfrRing->CycleBit;
			}
        }

        // If transfer ring crossed Link TRB, set its Chain flag
        if (Trb < FirstTrb) {
            ((XHCI_NORMAL_XFR_TRB*)XfrRing->LastTrb)->Chain = 1;
			
        }

		((XHCI_NORMAL_XFR_TRB*)FirstTrb)->CycleBit = XfrRing->CycleBit;
		if (Trb < FirstTrb) {
			((XHCI_NORMAL_XFR_TRB*)FirstTrb)->CycleBit ^= 1;
		}

        // Ring the door bell and see Event Ring update
        Status = XhciRingDoorbell(Usb3Hc, HcStruc, SlotId, Dci);

        if (Status != USB_SUCCESS) {
            break;
        }

        Status = XHCI_WaitForEvent(
                HcStruc, Trb, XhciTTransferEvt, SlotId, Dci,				//(EIP62376)
                &CompletionCode, TimeoutMs, &ResidualData);

        // Clear Link TRB chain flag
        ((XHCI_NORMAL_XFR_TRB*)XfrRing->LastTrb)->Chain = 0;

		if (Status != USB_SUCCESS) {
										//(EIP54283)>
			switch (CompletionCode) {
				case XHCI_TRB_BABBLE_ERROR:								//(EIP62376+)
				case XHCI_TRB_TRANSACTION_ERROR:
					XHCI_ClearStalledEp(Usb3Hc, HcStruc, SlotId, Dci);	//(EIP60460+)
					break;												//(EIP60460+)
				case XHCI_TRB_STALL_ERROR:
					XHCI_ResetEndpoint(Usb3Hc, HcStruc, SlotId, Dci);
					gUsbData->bLastCommandStatus |= USB_BULK_STALLED;
					gUsbData->dLastCommandStatusExtended |= USB_TRSFR_STALLED;
					break;
				case XHCI_TRB_EXECUTION_TIMEOUT_ERROR:
					XHCI_ClearEndpointState(HcStruc, DevInfo, Endpoint | XferDir);
					gUsbData->bLastCommandStatus |= USB_BULK_TIMEDOUT;
                    gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;	//(EIP84790+)
					break;
				default:
					break;
			}
										//<(EIP54283)
			break;
		}

        TransferredSize += (RingDataSize - ResidualData);
        if (ResidualData != 0) break;   // Short packet detected, no more transfers
        RemainingDataSize -= RingDataSize;
    }

    HcDmaUnmap(HcStruc, BufferMapping);
    
    return TransferredSize;
}


/**
    This function executes an interrupt transaction on the USB. The data
    transfer direction is always DATA_IN. This function wil not return until
    the request either completes successfully or completes in error (due to
    time out, etc.)

    @param 
        HcStruc   Pointer to HCStruc of the host controller
        DevInfo   DeviceInfo structure (if available else 0)
        Buffer    Buffer containing data to be sent to the device or buffer to be
        used to receive data
        Length    Length request parameter, number of bytes of data to be transferred

    @retval 
        Number of bytes transferred

**/

UINT16
XHCI_InterruptTransfer (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Buffer,
    UINT16      Length
)
{
    USB3_HOST_CONTROLLER *Usb3Hc;
    XHCI_TRB    *Trb;
    UINT8       SlotId;
    UINT8       CompletionCode;
    UINT8       Status;
    TRB_RING    *XfrRing;
    UINT8       Dci;
	UINT16		TimeoutMs;
    UINT8       *BufPhyAddr = NULL;
    VOID        *BufferMapping = NULL;
	
	gUsbData->dLastCommandStatusExtended = 0;
	
    if (DevInfo->DevMiscInfo == NULL) {
        return 0;
    }

	TimeoutMs = gUsbData->wTimeOutValue != 0 ? XHCI_INT_COMPLETE_TIMEOUT_MS : 0;

    Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    
    if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED) {
        return 0;
    }
    
    SlotId = XHCI_GetSlotId(Usb3Hc, DevInfo);
    Dci = (DevInfo->bIntEndpoint & 0xF) * 2;
    if (DevInfo->bIntEndpoint & BIT7) {
        Dci++;
    }

	HcDmaMap(HcStruc, DevInfo->bIntEndpoint & BIT7, Buffer, Length, 
		&BufPhyAddr, &BufferMapping);
	
    XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, Dci-1);
	Trb = XHCI_AdvanceEnqueuePtr(XfrRing);
	Trb->TrbType = XhciTNormal;
	((XHCI_NORMAL_XFR_TRB*)Trb)->DataBuffer = (UINTN)BufPhyAddr;
	((XHCI_NORMAL_XFR_TRB*)Trb)->XferLength = Length;
	((XHCI_NORMAL_XFR_TRB*)Trb)->Isp = 1;
	((XHCI_NORMAL_XFR_TRB*)Trb)->Ioc = 1;
	((XHCI_NORMAL_XFR_TRB*)Trb)->CycleBit = XfrRing->CycleBit;
	
    // Ring the doorbell and see Event Ring update
	Status = XhciRingDoorbell(Usb3Hc, HcStruc, SlotId, Dci);

    if (Status != USB_SUCCESS) {
        return 0;
    }
   
    Status = XHCI_WaitForEvent(
                HcStruc, Trb, XhciTTransferEvt, SlotId, Dci,				//(EIP62376)
                &CompletionCode, TimeoutMs, NULL);

	if (Status != USB_SUCCESS) {
										//(EIP54283)>
		switch (CompletionCode) {
										//(EIP62376+)>
			case XHCI_TRB_BABBLE_ERROR:
			case XHCI_TRB_TRANSACTION_ERROR:
				XHCI_ClearStalledEp(Usb3Hc, HcStruc, SlotId, Dci);
				break;
										//<(EIP62376+)
			case XHCI_TRB_STALL_ERROR:
				XHCI_ResetEndpoint(Usb3Hc, HcStruc, SlotId, Dci);
				break;
			case XHCI_TRB_EXECUTION_TIMEOUT_ERROR:
				XHCI_ClearEndpointState(HcStruc, DevInfo, DevInfo->bIntEndpoint);
                gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
				break;
			default:
				break;
		}
										//<(EIP54283)
		Length = 0;
	}

    HcDmaUnmap(HcStruc, BufferMapping);
    
    return (UINT8)Length;
}


/**
    This function de-activates the polling QH for the requested device. The
    device may be a USB keyboard or USB hub.

    @param 
        HcStruc   - Pointer to the HC structure
        DevInfo   - Pointer to the device information structure

    @retval 
        USB_ERROR on error, USB_SUCCESS on success

**/

UINT8
XHCI_DeactivatePolling(
    HC_STRUC* HcStruc,
    DEV_INFO* DevInfo
)
{
	USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
	UINT8       SlotId;
	UINT8		Dci;
	UINT16		EpInfo;
    TRB_RING    *XfrRing;
    XHCI_SET_TRPTR_CMD_TRB  Trb;
    XHCI_EP_CONTEXT *EpCtx;

    if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED) {
        return USB_ERROR;
    }


	if (DevInfo->fpPollTDPtr == NULL) {
		return USB_ERROR;
	}

    DevInfo->fpPollTDPtr = NULL;

	SlotId = XHCI_GetSlotId(Usb3Hc, DevInfo);
    Dci = (DevInfo->bIntEndpoint & 0xF) * 2;
    if (DevInfo->bIntEndpoint & BIT7) Dci++;

	EpInfo = (Dci << 8) + SlotId;
    
    EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)DevInfo->DevMiscInfo, Dci);

    if (EpCtx->EpState == XHCI_EP_STATE_RUNNING) {
	    XHCI_ExecuteCommand(HcStruc, XhciTStopEndpointCmd, &EpInfo);
    }
    
    // Set TR Dequeue Pointer command may be executed only if the target 
    // endpoint is in the Error or Stopped state.
    if ((EpCtx->EpState == XHCI_EP_STATE_STOPPED) || 
        (EpCtx->EpState == XHCI_EP_STATE_ERROR)) {
        
    	XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, Dci-1);

    	Trb.TrPointer = (UINT64)((UINTN)XfrRing->QueuePtr + XfrRing->CycleBit); // Set up DCS
    	Trb.EndpointId = Dci;
    	Trb.SlotId = SlotId;
    	XHCI_ExecuteCommand(HcStruc, XhciTSetTRDequeuePointerCmd, &Trb);
    }

	USB_MemFree(DevInfo->fpPollTDPtr, GET_MEM_BLK_COUNT(DevInfo->PollingLength));
	
    return USB_SUCCESS;
}


/**
    This function activates the polling QH for the requested device. The device
    may be a USB keyboard or USB hub.

    @param 
        HcStruc   - Pointer to the HC structure
        DevInfo   - Pointer to the device information structure

    @retval 
        USB_ERROR on error, USB_SUCCESS on success

**/

UINT8
XHCI_ActivatePolling(
    HC_STRUC* HcStruc,
    DEV_INFO* DevInfo
)
{
    USB3_HOST_CONTROLLER *Usb3Hc;
    XHCI_TRB    *Trb;
    UINT32      DoorbellOffset;
    UINT8       SlotId;
    TRB_RING    *XfrRing;
    UINT8		Dci;

    Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    
    if (HcReadOpReg(HcStruc, XHCI_USBSTS_OFFSET) & XHCI_STS_HALTED) {
        return USB_ERROR;
    }
    
    SlotId = XHCI_GetSlotId(Usb3Hc, DevInfo);
    Dci = (DevInfo->bIntEndpoint & 0xF) * 2;
    if (DevInfo->bIntEndpoint & BIT7) {
        Dci++;
    }
    DevInfo->fpPollTDPtr = USB_MemAlloc(GET_MEM_BLK_COUNT(DevInfo->PollingLength));
    XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, Dci - 1);

    Trb = XHCI_AdvanceEnqueuePtr(XfrRing);
    Trb->TrbType = XhciTNormal;
    ((XHCI_NORMAL_XFR_TRB*)Trb)->DataBuffer = (UINT64)(UINTN)DevInfo->fpPollTDPtr;
    ((XHCI_NORMAL_XFR_TRB*)Trb)->XferLength = DevInfo->PollingLength;
	((XHCI_NORMAL_XFR_TRB*)Trb)->Isp = 1;	//(EIP51478+)
    ((XHCI_NORMAL_XFR_TRB*)Trb)->Ioc = 1;
	((XHCI_NORMAL_XFR_TRB*)Trb)->CycleBit = XfrRing->CycleBit;

    // Ring the door bell
    DoorbellOffset = XhciGetTheDoorbellOffset(Usb3Hc, HcStruc,SlotId);
    HcWriteHcMem(HcStruc, DoorbellOffset, Dci);

    return USB_SUCCESS;
}


/**
    This function disables the keyboard repeat rate logic

    @param 
        HcStruc  - Pointer to the HC structure

    @retval 
        USB_ERROR on error, USB_SUCCESS on success

**/

UINT8
XHCI_DisableKeyRepeat (
    HC_STRUC* HcStruc
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;

    XHCI_Mmio64Write(HcStruc, Usb3Hc,
                (UINTN)&Usb3Hc->RtRegs->IntRegs->Erdp, (UINT64)(UINTN)Usb3Hc->EvtRing.QueuePtr | BIT3);

    HcWriteHcMem(HcStruc, 
        (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMod - HcStruc->BaseAddress), XHCI_IMODI);
   
    return USB_SUCCESS;
}


/**
    This function disables the keyboard repeat rate logic

    @param 
        HcStruc  - Pointer to the HC structure

    @retval 
        USB_ERROR on error, USB_SUCCESS on success

**/

UINT8
XHCI_EnableKeyRepeat(
    HC_STRUC* HcStruc
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
 
    XHCI_Mmio64Write(HcStruc, Usb3Hc,
                (UINTN)&Usb3Hc->RtRegs->IntRegs->Erdp, (UINT64)(UINTN)0 | BIT3);

    HcWriteHcMem(HcStruc, 
                (UINT32)((UINTN)&Usb3Hc->RtRegs->IntRegs->IMod - HcStruc->BaseAddress),
                XHCI_KEYREPEAT_IMODC << 16 | XHCI_KEYREPEAT_IMODI);
    
    return USB_SUCCESS;
}


/**
    This function initializes transfer ring of given endpoint

    @retval 
        Pointer to the transfer ring

**/

TRB_RING*
XHCI_InitXfrRing(
    USB3_HOST_CONTROLLER* Usb3Hc,
    UINT8   Slot,
    UINT8   Ep
)
{
    TRB_RING    *XfrRing = Usb3Hc->XfrRings + (Slot-1)*32 + Ep;
    UINTN       Base = Usb3Hc->XfrTrbs + ((Slot-1)*32+Ep)*RING_SIZE;

    XHCI_InitRing(XfrRing, Base, TRBS_PER_SEGMENT, TRUE);

    return XfrRing;
}


/**
    This routine calculates the Interval field to be used in device's endpoint
    context. Interval is calculated using the following rules (Section 6.2.3.6):

    For SuperSpeed bulk and control endpoints, the Interval field shall not be
    used by the xHC. For all other endpoint types and speeds, system software
    shall translate the bInterval field in the USB Endpoint Descriptor to the
    appropriate value for this field.

    For high-speed and SuperSpeed Interrupt and Isoch endpoints the bInterval
    field the Endpoint Descriptor is computed as 125æs * 2^(bInterval-1), where
    bInterval = 1 to 16, therefore Interval = bInterval - 1.

    For low-speed Interrupt and full-speed Interrupt and Isoch endpoints the
    bInterval field declared by a Full or Low-speed device is computed as
    bInterval * 1ms., where bInterval = 1 to 255.

    For Full- and Low-speed devices software shall round the value of Endpoint
    Context Interval field down to the nearest base 2 multiple of bInterval * 8.

    @param 
        EpType      Endpoint type, see XHCI_EP_CONTEXT.DW1.EpType field definitions
        Speed       Endpoint speed, 1..4 for XHCI_DEVSPEED_FULL, _LOW, _HIGH, _SUPER
        Interval    Poll interval value from endpoint descriptor

    @retval 
        Interval value to be written to the endpoint context

**/

UINT8
Xhci_TranslateInterval(
    UINT8   EpType,
    UINT8   Speed,
    UINT8   Interval
)
{
    UINT8  TempData;
    UINT8  BitCount;

	if (Interval == 0) {
		return 0;
	}

    if (EpType == XHCI_EPTYPE_CTL || 
        EpType == XHCI_EPTYPE_BULK_OUT || 
        EpType == XHCI_EPTYPE_BULK_IN) {

		if (Speed == XHCI_DEVSPEED_HIGH) {
			for (TempData = Interval, BitCount = 0; TempData != 0; BitCount++) {
				TempData >>= 1;
			}
			return BitCount - 1;
		} else {
			return 0; // Interval field will not be used for LS, FS and SS
		}
    }

    // Control and Bulk endpoints are processed; translate intervals for Isoc and Interrupt
    // endpoints

    // Translate SS and HS endpoints
    if (Speed == XHCI_DEVSPEED_SUPER || 
            Speed == XHCI_DEVSPEED_SUPER_PLUS ||
            Speed == XHCI_DEVSPEED_HIGH) {
        return (Interval - 1);
    }

    // Translate interval for FS and LS endpoints
    ASSERT(Interval > 0);

    for (TempData = Interval, BitCount = 0; TempData != 0; BitCount++) {
        TempData >>= 1;
    }
    return (BitCount + 2);  // return value, where Interval = 0.125*2^value
}


/**
    This function parses the device descriptor data and enables the endpoints
    by 1)assigning the Transfer TRB and 2)executing ConfigureEndpoint command
    for the slot. Section 4.3.5.

    @param 
        DevInfo - A device for which the endpoins are being enabled
        Desc    - Device Configuration Descriptor data pointer

    @retval 
        USB_ERROR on error, USB_SUCCESS on success

    @note  
  1) DevInfo->DevMiscInfo points to the device context
  2) This call is executed before SET_CONFIGURATION control transfer
  3) EP0 information is valid in the Device

**/

UINT8
XHCI_EnableEndpoints (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Desc
)
{
    UINT16          TotalLength;
    UINT16          CurPos;
    UINT8           Dci;
	INTRF_DESC		*IntrfDesc;
    ENDP_DESC       *EpDesc;
	HUB_DESC		*HubDesc; 
    TRB_RING        *XfrRing;
    UINT8           EpType;
    UINT8           Status;
	UINT8			IsHub = 0;			//(EIP73020)
	UINT8			Speed;
	XHCI_INPUT_CONTROL_CONTEXT	*CtlCtx;
	XHCI_SLOT_CONTEXT			*SlotCtx;
	XHCI_EP_CONTEXT 			*EpCtx;

    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    UINT8 SlotId = XHCI_GetSlotId(Usb3Hc, DevInfo);

    if (((CNFG_DESC*)Desc)->bDescType != DESC_TYPE_CONFIG) return USB_ERROR;

	SlotCtx = (XHCI_SLOT_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)DevInfo->DevMiscInfo, 0);
	Speed = SlotCtx->Speed;

    // Note (From 4.6.6): The Add Context flag A1 and Drop Context flags D0 and D1
    // of the Input Control Context (in the Input Context) shall be cleared to 0.
    // Endpoint 0 Context does not apply to the Configure Endpoint Command and
    // shall be ignored by the xHC. A0 shall be set to 1.

    // Note (From 6.2.2.2): If Hub = 1 and Speed = High-Speed (3), then the
    // TT Think Time and Multi-TT (MTT) fields shall be initialized.
    // If Hub = 1, then the Number of Ports field shall be initialized, else
    // Number of Ports = 0.

    // Prepare input context for EvaluateContext comand
	MemSet((UINT8*)Usb3Hc->InputContext, XHCI_INPUT_CONTEXT_ENTRIES * Usb3Hc->ContextSize, 0);

    CtlCtx = (XHCI_INPUT_CONTROL_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 0);
    CtlCtx->AddContextFlags = BIT0;    // EP0

	SlotCtx = (XHCI_SLOT_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, 1);

    // Collect the endpoint information and update the Device Input Context
    TotalLength = ((CNFG_DESC*)Desc)->wTotalLength;

    if (TotalLength > (MAX_CONTROL_DATA_SIZE - 1)) {
        TotalLength = MAX_CONTROL_DATA_SIZE - 1;
    }

    for (CurPos = 0; CurPos < TotalLength; CurPos += EpDesc->bDescLength) {
		EpDesc = (ENDP_DESC*)(IntrfDesc = (INTRF_DESC*)(Desc + CurPos));

		if (IntrfDesc->bDescLength == 0) {
			break;
		}
		
		if ((CurPos + IntrfDesc->bDescLength) > TotalLength) {
			break;
		}
	
		if (IntrfDesc->bDescType == DESC_TYPE_INTERFACE) {
			IsHub = IntrfDesc->bBaseClass == BASE_CLASS_HUB;
			continue;
		}
	
        if (EpDesc->bDescType != DESC_TYPE_ENDPOINT) continue;

        // Found Endpoint, fill up the information in the InputContext

        // Calculate Device Context Index (DCI), Section 4.5.1.
        // 1) For Isoch, Interrupt, or Bulk type endpoints the DCI is calculated
        // from the Endpoint Number and Direction with the following formula:
        //  DCI = (Endpoint Number * 2) + Direction, where Direction = 0 for OUT
        // endpoints and 1 for IN endpoints.
        // 2) For Control type endpoints:
        //  DCI = (Endpoint Number * 2) + 1
        //
        // Also calculate XHCI EP type out of EpDesc->bEndpointFlags

        if ((EpDesc->bEndpointFlags & EP_DESC_FLAG_TYPE_BITS) == EP_DESC_FLAG_TYPE_CONT) {
            Dci = (EpDesc->bEndpointAddr & 0xf) * 2 + 1;
            EpType = XHCI_EPTYPE_CTL;
        } else {
            // Isoc, Bulk or Interrupt endpoint
            Dci = (EpDesc->bEndpointAddr & 0xf) * 2;
            EpType = EpDesc->bEndpointFlags & EP_DESC_FLAG_TYPE_BITS;   // 1, 2, or 3

            if (EpDesc->bEndpointAddr & BIT7) {
                Dci++;          // IN
                EpType += 4;    // 5, 6, or 7
            }
        }

        // Update ContextEntries in the Slot context
        if (Dci > SlotCtx->ContextEntries) {
            SlotCtx->ContextEntries = Dci;
        }

        EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)Usb3Hc->InputContext, Dci + 1);

        EpCtx->EpType = EpType;
        EpCtx->MaxPacketSize = EpDesc->wMaxPacketSize;
        EpCtx->ErrorCount = 3;

        // Set Interval 
        EpCtx->Interval = Xhci_TranslateInterval(EpType, Speed, EpDesc->bPollInterval);

        XfrRing = XHCI_InitXfrRing(Usb3Hc, SlotId, Dci - 1);
        EpCtx->TrDequeuePtr = (UINT64)(UINTN)XfrRing->Base + 1;

        CtlCtx->AddContextFlags |= (1 << Dci);
    }

    // For a HUB update NumberOfPorts and TTT fields in the Slot context. For that get hub descriptor
    // and use bNbrPorts and TT Think time fields (11.23.2.1 of USB2 specification)
    // Notes:
    //  - Slot.Hub field is already updated
    //  - Do not set NumberOfPorts and TTT fields for 0.95 controllers

	if (IsHub) {
		HubDesc = (HUB_DESC*)USB_MemAlloc(sizeof(MEM_BLK));
		UsbHubGetHubDescriptor(HcStruc, DevInfo, HubDesc, sizeof(MEM_BLK));
		//ASSERT(HubDesc->bDescType == DESC_TYPE_HUB || HubDesc->bDescType == DESC_TYPE_SS_HUB);
		if ((HubDesc->bDescType == DESC_TYPE_HUB) || 
			(HubDesc->bDescType == DESC_TYPE_SS_HUB)) {
			SlotCtx->Hub = 1;
			SlotCtx->PortsNum = HubDesc->bNumPorts;
		
			if (Speed == XHCI_DEVSPEED_HIGH) {
				SlotCtx->TThinkTime = (HubDesc->wHubFlags >> 5) & 0x3;
			}
		}
		USB_MemFree(HubDesc, sizeof(MEM_BLK));
	}

    // Input context is updated with the endpoint information. Execute ConfigureEndpoint command.
    Status = XHCI_ExecuteCommand(HcStruc, XhciTConfigureEndpointCmd, &SlotId);
    ASSERT(Status == USB_SUCCESS);

    return Status;
}


/**
    This function returns a root hub number for a given device. If device is
    connected to the root through hub(s), it searches the parent's chain up
    to the root.

**/

UINT8
XHCI_GetRootHubPort(
    DEV_INFO    *DevInfo
)
{
    UINT8       i;

    if ((DevInfo->bHubDeviceNumber & BIT7) != 0) return DevInfo->bHubPortNumber;

    for (i = 1; i < MAX_DEVICES; i++) {
		if ((gUsbData->aDevInfoTable[i].Flag & DEV_INFO_VALIDPRESENT)
            != DEV_INFO_VALIDPRESENT) {
			continue;
		}
        if (gUsbData->aDevInfoTable[i].bDeviceAddress == DevInfo->bHubDeviceNumber) {
            return XHCI_GetRootHubPort(&gUsbData->aDevInfoTable[i]);
        }
    }
    ASSERT(FALSE);  // Device parent hub found
    return 0;
}

/**
    This is an API function for early device initialization.

**/

UINT8
XHCI_InitDeviceData (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       PortStatus,
    UINT8       **DeviceData
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    UINT8	Status;
    UINT8   SlotId;
    VOID	*DevCtx;

    // Obtain device slot using Enable Slot command, 4.3.2, 4.6.3
    Status = XHCI_ExecuteCommand(HcStruc, XhciTEnableSlotCmd, &SlotId);
    //ASSERT(Status == USB_SUCCESS);
    //ASSERT(SlotId != 0);
    if (Status != USB_SUCCESS) {
        return Status;
    }

    DevCtx = XHCI_GetDeviceContext(Usb3Hc, SlotId);	
    MemSet(DevCtx, XHCI_DEVICE_CONTEXT_ENTRIES * Usb3Hc->ContextSize, 0);

    // Update DCBAA with the new device pointer (index = SlotId)
    Usb3Hc->DcbaaPtr->DevCntxtAddr[SlotId-1] = (UINT64)(UINTN)DevCtx;
    USB_DEBUG(3, "XHCI: Slot[%d] enabled, device context at %x\n", SlotId, DevCtx);

    Status = XhciAddressDevice(HcStruc, DevInfo, SlotId);
    if (Status != USB_SUCCESS) {
        return Status;
    }

    *DeviceData = (UINT8*)DevCtx;
    return USB_SUCCESS;
}

/**
    This is an API function for removing device related information from HC.
    For xHCI this means:
    - execute DisableSlot commnand
    - clear all endpoint's transfer rings

**/

UINT8
XHCI_DeinitDeviceData (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo
)
{
    USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    UINT8 SlotId;
    UINT8 Dci;
    TRB_RING *XfrRing;
	XHCI_SLOT_CONTEXT	*SlotCtx;
	XHCI_EP_CONTEXT		*EpCtx;
	UINT16	EpInfo;

	if (DevInfo->DevMiscInfo == NULL) return USB_SUCCESS;

	SlotId = XHCI_GetSlotId(Usb3Hc, DevInfo);
	if (Usb3Hc->DcbaaPtr->DevCntxtAddr[SlotId-1] == 0) return USB_SUCCESS;

	SlotCtx = (XHCI_SLOT_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)DevInfo->DevMiscInfo, 0);
	
    // Stop transfer rings
    for (Dci = 1; Dci <= SlotCtx->ContextEntries; Dci++) {
		EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, (UINT8*)DevInfo->DevMiscInfo, Dci);
        if (EpCtx->TrDequeuePtr != 0) {
			if (EpCtx->EpState == XHCI_EP_STATE_RUNNING) {
				EpInfo = (Dci << 8) + SlotId;
				XHCI_ExecuteCommand(HcStruc, XhciTStopEndpointCmd, &EpInfo);
        	}

			// Clear transfer rings
            XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, Dci - 1);
			MemSet((UINT8*)XfrRing->Base, RING_SIZE, 0);
        }
    }

    XHCI_ExecuteCommand(HcStruc, XhciTDisableSlotCmd, &SlotId);

	Usb3Hc->DcbaaPtr->DevCntxtAddr[SlotId-1] = 0;
	DevInfo->DevMiscInfo = NULL;

    return USB_SUCCESS;
}

										//(EIP54283+)>
/**

**/

UINT8
XHCI_ClearEndpointState(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
	UINT8		Endpoint
)
{
	USB3_HOST_CONTROLLER *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
	UINT8		SlotId;					//(EIP60460)
	UINT8		Dci;					//(EIP60460)
    TRB_RING    *XfrRing;
    UINT8       Status = USB_SUCCESS;
    XHCI_SET_TRPTR_CMD_TRB  Trb;
//	volatile UINT32 *Doorbell;			//(EIP61849-)
										//(EIP54300+)>
    XHCI_EP_CONTEXT     *EpCtx;
	UINT16      EpInfo;
										//(EIP60460+)>
	if (DevInfo->DevMiscInfo == NULL) {
		return Status;
	}

	SlotId = XHCI_GetSlotId(Usb3Hc, DevInfo);
	if (Endpoint != 0) {
		Dci = (Endpoint & 0xF) * 2 + (Endpoint >> 7);
	} else {
		Dci = 1;
	}
										//<(EIP60460+)
	EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, DevInfo->DevMiscInfo, Dci);
                                        
    if (EpCtx->EpState == XHCI_EP_STATE_RUNNING) {                                        
        EpInfo = (Dci << 8) + SlotId;
        Status = XHCI_ExecuteCommand(HcStruc, XhciTStopEndpointCmd, &EpInfo);
    }                                   //<(EIP54300+)

    // Set TR Dequeue Pointer command may be executed only if the target 
    // endpoint is in the Error or Stopped state.
    if ((EpCtx->EpState == XHCI_EP_STATE_STOPPED) ||
        (EpCtx->EpState == XHCI_EP_STATE_ERROR)) {
    
    	XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, Dci-1);

    	Trb.TrPointer = (UINT64)((UINTN)XfrRing->QueuePtr + XfrRing->CycleBit); // Set up DCS
    	Trb.EndpointId = Dci;
    	Trb.SlotId = SlotId;

    	Status = XHCI_ExecuteCommand(HcStruc, XhciTSetTRDequeuePointerCmd, &Trb);
    }
	//ASSERT(Status == USB_SUCCESS);

//	Doorbell = XHCI_GetTheDoorbell(Usb3Hc, SlotId);		//(EIP61849-)
// 	*Doorbell = Dci;									//(EIP61849-)

	return Status;
}
										//<(EIP54283+)
/**

**/

UINT8
XhciAddressDevice (
	HC_STRUC    *HcStruc,
	DEV_INFO    *DevInfo,
	UINT8		SlotId
)
{
    USB3_HOST_CONTROLLER        *Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->usbbus_data;
    XHCI_INPUT_CONTROL_CONTEXT  *InputCtrl = NULL;
    XHCI_SLOT_CONTEXT           *InputSlot = NULL;
    XHCI_SLOT_CONTEXT           *OutputSlot = NULL;
    XHCI_SLOT_CONTEXT           *ParentHubSlotCtx = NULL;
    XHCI_EP_CONTEXT             *InputEp0 = NULL;
    XHCI_EP_CONTEXT             *OutputEp0 = NULL;
    UINT8                       Status = USB_ERROR;
    VOID                        *DevCtx = XHCI_GetDeviceContext(Usb3Hc, SlotId);
    VOID                        *InputCtx = Usb3Hc->InputContext;
    TRB_RING                    *XfrRing = NULL;
    DEV_INFO                    *ParentHub = NULL;
    UINT8                       HubPortNumber = 0;
    UINT16                      AddrDevParam = 0;
    UINT8                       Bsr = 0;

    OutputSlot = XHCI_GetContextEntry(Usb3Hc, DevCtx, 0);
    if (OutputSlot->SlotState >= XHCI_SLOT_STATE_ADDRESSED) {
        return USB_ERROR;
    }

    // Zero the InputContext and DeviceContext
    MemSet(InputCtx, XHCI_INPUT_CONTEXT_ENTRIES * Usb3Hc->ContextSize, 0);

    // Initialize the Input Control Context of the Input Context
    // by setting the A0 flags to 1
    InputCtrl = XHCI_GetContextEntry(Usb3Hc, InputCtx, 0);
    InputCtrl->AddContextFlags = BIT0 | BIT1;

    // Initialize the Input Slot Context data structure
    InputSlot = XHCI_GetContextEntry(Usb3Hc, InputCtx, 1);
    InputSlot->RouteString = 0;
    InputSlot->ContextEntries = 1;
    InputSlot->RootHubPort = XHCI_GetRootHubPort(DevInfo);

    switch (DevInfo->bEndpointSpeed) {
        case USB_DEV_SPEED_SUPER_PLUS:
            InputSlot->Speed = XHCI_DEVSPEED_SUPER_PLUS;
            break;
        case USB_DEV_SPEED_SUPER:
            InputSlot->Speed = XHCI_DEVSPEED_SUPER;
            break;
        case USB_DEV_SPEED_HIGH:
            InputSlot->Speed = XHCI_DEVSPEED_HIGH; 
            break;
        case USB_DEV_SPEED_LOW:
            InputSlot->Speed = XHCI_DEVSPEED_LOW;
            break;
        case USB_DEV_SPEED_FULL:
            InputSlot->Speed = XHCI_DEVSPEED_FULL;
            break;
    }

    // Initialize Route String and TT fields
    ParentHub = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR,
                            0, DevInfo->bHubDeviceNumber, 0);
    if (ParentHub != NULL) {
        ParentHubSlotCtx = XHCI_GetContextEntry(Usb3Hc, ParentHub->DevMiscInfo, 0);
        HubPortNumber = (DevInfo->bHubPortNumber > 15)? 15 : DevInfo->bHubPortNumber;
        InputSlot->RouteString = ParentHubSlotCtx->RouteString | 
                                (HubPortNumber << (ParentHub->HubDepth * 4));	//(EIP51503)

        // Update TT fields in the Slot context for LS/FS device connected to HS hub
        if (InputSlot->Speed == XHCI_DEVSPEED_FULL || InputSlot->Speed == XHCI_DEVSPEED_LOW) {
            if (ParentHubSlotCtx->Speed == XHCI_DEVSPEED_HIGH) {
                InputSlot->TtHubSlotId = XHCI_GetSlotId(Usb3Hc, ParentHub);
                InputSlot->TtPortNumber = DevInfo->bHubPortNumber;
                InputSlot->MultiTT = ParentHubSlotCtx->MultiTT;
            } else {
                InputSlot->TtHubSlotId = ParentHubSlotCtx->TtHubSlotId;
                InputSlot->TtPortNumber = ParentHubSlotCtx->TtPortNumber;
                InputSlot->MultiTT = ParentHubSlotCtx->MultiTT;
            }
        }
    }

    OutputEp0 = XHCI_GetContextEntry(Usb3Hc, DevCtx, 1);
    switch (OutputEp0->EpState) {
        case XHCI_EP_STATE_DISABLED:
            XfrRing = XHCI_InitXfrRing(Usb3Hc, SlotId, 0);
            break;
        case XHCI_EP_STATE_RUNNING:
        case XHCI_EP_STATE_STOPPED:
            XfrRing = XHCI_GetXfrRing(Usb3Hc, SlotId, 0);
            break;
        default:
            break;
    }

    // Initialize the Input default control Endpoint 0 Context
    InputEp0 = XHCI_GetContextEntry(Usb3Hc, InputCtx, 2);
    InputEp0->EpType = XHCI_EPTYPE_CTL;
    InputEp0->MaxPacketSize = DevInfo->wEndp0MaxPacket;
    InputEp0->TrDequeuePtr = (UINT64)(UINTN)XfrRing->QueuePtr | XfrRing->CycleBit;
    InputEp0->AvgTrbLength = 8;
    InputEp0->ErrorCount = 3;

    Bsr = (InputSlot->Speed != XHCI_DEVSPEED_SUPER &&
            InputSlot->Speed != XHCI_DEVSPEED_SUPER_PLUS && 
            OutputSlot->SlotState == XHCI_SLOT_STATE_DISABLED) ? 1 : 0;

    AddrDevParam = (UINT16)SlotId | (Bsr << 8);

    // Assign a new address 4.3.4, 4.6.5
    Status = XHCI_ExecuteCommand(HcStruc, XhciTAddressDeviceCmd, &AddrDevParam);
    if (Status != USB_SUCCESS) {
        XHCI_ExecuteCommand(HcStruc, XhciTDisableSlotCmd, &SlotId);
        Usb3Hc->DcbaaPtr->DevCntxtAddr[SlotId-1] = 0;
        return Status;
    }

    if (Bsr == 0) {
        USB_DEBUG(3, "XHCI: new device address %d\n", OutputSlot->DevAddr);
    }

    return USB_SUCCESS;
}
									
/**

**/

UINT8
XhciRingDoorbell(
	USB3_HOST_CONTROLLER	    *Usb3Hc,
	HC_STRUC                    *HcStruc,
	UINT8					    SlotId,
	UINT8					    Dci
)
{
    UINT32  DoorbellOffset;
	XHCI_EP_CONTEXT *EpCtx = NULL;
	UINT32	Count;

    DoorbellOffset = XhciGetTheDoorbellOffset(Usb3Hc, HcStruc, SlotId);
    HcWriteHcMem(HcStruc, DoorbellOffset, Dci);

	if (SlotId == 0) {
		return USB_ERROR;
	}

	EpCtx = (XHCI_EP_CONTEXT*)XHCI_GetContextEntry(Usb3Hc, 
					XHCI_GetDeviceContext(Usb3Hc, SlotId), Dci);
	// Wait for the endpoint running
	for (Count = 0; Count < 10 * 1000; Count++) {
		if (EpCtx->EpState == XHCI_EP_STATE_RUNNING) {
			break;
		}
		FixedDelay(1);    // 1 us delay
	}
	//ASSERT(EpCtx->EpState == XHCI_EP_STATE_RUNNING);

    if (EpCtx->EpState != XHCI_EP_STATE_RUNNING) {
        return USB_ERROR;
    }

	return USB_SUCCESS;
}
										//<(EIP54283+)

/**
    HC may or may not support 64-bit writes to MMIO area. If it does, write
    Data directly, otherwise split into two DWORDs.

**/

UINT64
XHCI_Mmio64Read(
	HC_STRUC    			*HcStruc,
	USB3_HOST_CONTROLLER *Usb3Hc,
	UINTN	Address
)
{
	UINT64	Data = 0;
#if USB_RUNTIME_DRIVER_IN_SMM
	if (Usb3Hc->CapRegs.HccParams1.Ac64) {
		Data = *(UINT64*)Address;
	}
	else {
		Data = *(UINT32*)Address;
		Data |= Shl64(*(UINT32*)(Address + sizeof(UINT32)), 32);
	}
#else
    Data = HcReadHcMem(HcStruc, (UINT32)(Address - HcStruc->BaseAddress));
    Data |= Shl64(HcReadHcMem(HcStruc, (UINT32)(Address - HcStruc->BaseAddress + sizeof(UINT32))), 32);
#endif
	return Data;
}

VOID
XHCI_Mmio64Write(
	HC_STRUC    			*HcStruc,
    USB3_HOST_CONTROLLER *Usb3Hc,
    UINTN   Address,
    UINT64  Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    if (Usb3Hc->CapRegs.HccParams1.Ac64) {
        *(UINT64*)Address = Data;
    }
    else {
        *(UINT32*)Address = (UINT32)Data;
        *(UINT32*)(Address + sizeof(UINT32)) = (UINT32)(Shr64(Data, 32));
    }
#else
    HcWriteHcMem(HcStruc, (UINT32)(Address - HcStruc->BaseAddress), (UINT32)Data);
    HcWriteHcMem(HcStruc, (UINT32)(Address - HcStruc->BaseAddress + sizeof(UINT32)),  (UINT32)(Shr64(Data, 32)));
#endif
}

/**
    Transfer ring initialization. There is an option to create a Link TRB in
    the end of the ring.

**/

EFI_STATUS
XHCI_InitRing (
    IN OUT TRB_RING *Ring,
    IN UINTN    RingBase,
    IN UINT32   RingSize,
    IN BOOLEAN  PlaceLinkTrb
)
{
    XHCI_LINK_TRB   *LinkTrb;

    Ring->Base = (XHCI_TRB*)RingBase;
    Ring->Size = RingSize;
    Ring->LastTrb = Ring->Base + RingSize - 1;
    Ring->CycleBit = 1;
    Ring->QueuePtr = (XHCI_TRB*)RingBase;

    // Initialize ring with zeroes
    {
        UINT8   *p = (UINT8*)RingBase;
        UINTN   i;
        for (i = 0; i < RingSize*sizeof(XHCI_TRB); i++, p++) *p = 0;
    }

    if (PlaceLinkTrb) {
        // Place a Link TRB in the end of the ring pointing to the beginning
        LinkTrb = (XHCI_LINK_TRB*)Ring->LastTrb;
        LinkTrb->NextSegPtr = (UINT64)(UINTN)RingBase;
        LinkTrb->ToggleCycle = 1;
        LinkTrb->TrbType = XhciTLink;
    }

    return EFI_SUCCESS;
}


/**
    This function sets USB_PORT_STAT... fields that are related to device
    speed (LS/FS/HS/SS) in a given PortStatus variable.

**/

VOID
UpdatePortStatusSpeed(
    UINT8   Speed,
    UINT8   *PortStatus
)
{
    UINT8   PortSts = *PortStatus;

    ASSERT(Speed < 6);
	PortSts &= ~USB_PORT_STAT_DEV_SPEED_MASK;

    switch (Speed) {
        case XHCI_DEVSPEED_UNDEFINED:
                break;
        case XHCI_DEVSPEED_FULL:
                PortSts |= USB_PORT_STAT_DEV_FULLSPEED;
                break;
        case XHCI_DEVSPEED_LOW:
                PortSts |= USB_PORT_STAT_DEV_LOWSPEED;
                break;
        case XHCI_DEVSPEED_HIGH:
                PortSts |= USB_PORT_STAT_DEV_HISPEED;
                break;
        case XHCI_DEVSPEED_SUPER:
                PortSts |= USB_PORT_STAT_DEV_SUPERSPEED;
                break;
        case XHCI_DEVSPEED_SUPER_PLUS:
                PortSts |= USB_PORT_STAT_DEV_SUPERSPEED_PLUS;
                break;
        default:
                USB_DEBUG(3, "XHCI ERROR: unknown device speed.\n");
    }

    *PortStatus = PortSts;
}

/**

**/

BOOLEAN
XHCI_IsUsb3Port(
	USB3_HOST_CONTROLLER	*Usb3Hc,
	UINT8					Port
)
{
	if ((Port >= Usb3Hc->Usb3Protocol.PortOffset) &&
		(Port < Usb3Hc->Usb3Protocol.PortOffset + Usb3Hc->Usb3Protocol.PortCount)) {
		return TRUE;
	}
	return FALSE;
}

//****************************************************************************
// The following set of functions are the helpers to get the proper locations
// of xHCI data structures using the available pointers.
//****************************************************************************

/**
    This function calculates the slot ID out of a given DEV_INFO data pointer.

**/

UINT8
XHCI_GetSlotId(
    USB3_HOST_CONTROLLER *Usb3Hc,
    DEV_INFO    *DevInfo
)
{
    UINT32 DevCtxSize = XHCI_DEVICE_CONTEXT_ENTRIES * Usb3Hc->ContextSize;
    return (UINT8)(((UINTN)DevInfo->DevMiscInfo - (UINTN)Usb3Hc->DeviceContext)/DevCtxSize) + 1;
}


/**
    This routine calculates the address of the address ring of a particular
    Slot/Endpoint.

    @retval 
        Pointer to the transfer ring

**/

TRB_RING*
XHCI_GetXfrRing(
    USB3_HOST_CONTROLLER* Usb3Hc,
    UINT8   Slot,
    UINT8   Ep
)
{
    return Usb3Hc->XfrRings + (Slot-1)*32 + Ep;
}


/**
    This function calculates and returns the pointer to a doorbell for a
    given Slot.

**/

UINT32*
XHCI_GetTheDoorbell(
    USB3_HOST_CONTROLLER    *Usb3Hc,
    HC_STRUC                *HcStruc,
    UINT8                   SlotId
)
{
    return (UINT32*)(HcStruc->BaseAddress + Usb3Hc->CapRegs.DbOff + sizeof(UINT32)*SlotId);
}

/**
    This function calculates and returns the pointer to a doorbell for a
    given Slot.
**/


UINT32
XhciGetTheDoorbellOffset(
    USB3_HOST_CONTROLLER    *Usb3Hc,
    HC_STRUC                *HcStruc,
    UINT8                   SlotId
)
{
    return (UINT32)(Usb3Hc->CapRegs.DbOff + sizeof(UINT32)*SlotId);
}
/**
    This function searches for DEV_INFO data pointer that belongs to a given XHCI
    device context.

**/

DEV_INFO*
XHCI_GetDevInfo(
    UINTN	PollTdPtr
)
{
    UINT8       i;
    DEV_INFO    *DevInfo;

	if (PollTdPtr == 0) return NULL;

    for (i=1; i<MAX_DEVICES; i++) {
        DevInfo = &gUsbData->aDevInfoTable[i];
		if ((DevInfo->Flag & DEV_INFO_VALIDPRESENT) != DEV_INFO_VALIDPRESENT) {
			continue;
		}
		if (DevInfo->fpPollTDPtr == NULL) {
			continue;
		}
        if ((UINTN)DevInfo->fpPollTDPtr == (UINTN)PollTdPtr) {
            return DevInfo;
        }
    }
    return NULL;    // Device not found
}

/**
    This function calculates and returns the pointer to a device context for
    a given Slot.

**/

VOID*
XHCI_GetDeviceContext(
	USB3_HOST_CONTROLLER	*Usb3Hc,
	UINT8					SlotId
)
{
	UINT32 DevCtxSize = XHCI_DEVICE_CONTEXT_ENTRIES * Usb3Hc->ContextSize;
	return (UINT8*)((UINTN)Usb3Hc->DeviceContext + (SlotId - 1) * DevCtxSize);
}

/**
    This function calculates and returns the pointer to a context entry for
    a given index.

**/

VOID*
XHCI_GetContextEntry(
	USB3_HOST_CONTROLLER	*Usb3Hc,
	VOID					*Context,
	UINT8					Index
)
{
	return (UINT8*)((UINTN)Context + Index * Usb3Hc->ContextSize);
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
