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

/** @file Ohci.c
    AMI USB OHCI driver source file

**/

#include "AmiDef.h"
#include "UsbDef.h"
#include "AmiUsb.h"

#pragma warning (disable :4213)
#pragma warning (disable :4706)

UINT8   OHCI_FillHCDEntries(HCD_HEADER*);
UINT8   OHCI_Start (HC_STRUC*);
UINT8   OHCI_Stop (HC_STRUC*);
UINT8   OHCI_DisableInterrupts (HC_STRUC*);
UINT8   OHCI_EnableInterrupts (HC_STRUC*);
UINT8   OHCI_ProcessInterrupt(HC_STRUC*);
UINT8   OHCI_GetRootHubStatus (HC_STRUC*, UINT8, BOOLEAN);
UINT8   OHCI_DisableRootHub (HC_STRUC*,UINT8);
UINT8   OHCI_EnableRootHub (HC_STRUC*,UINT8);
UINT16  OHCI_ControlTransfer (HC_STRUC*,DEV_INFO*,UINT16,UINT16,UINT16,UINT8*,UINT16);
UINT32  OHCI_BulkTransfer (HC_STRUC*,DEV_INFO*,UINT8,UINT8*,UINT32);
UINT16  OHCI_InterruptTransfer (HC_STRUC*,DEV_INFO*,UINT8*,UINT16);
UINT8   OHCI_DeactivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   OHCI_ActivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   OHCI_DisableKeyRepeat (HC_STRUC*);
UINT8   OHCI_EnableKeyRepeat (HC_STRUC*);
UINT8   OHCI_ResetRootHub (HC_STRUC*,UINT8);
UINT8   OHCI_GlobalSuspend (HC_STRUC*);	//(EIP54018+)

UINT8   OHCI_EnumeratePorts(HC_STRUC*);
UINT8   OHCI_StartEDSchedule(HC_STRUC*);
UINT8   OhciAddPeriodicEd (HC_STRUC*, OHCI_ED*);
UINT8   OhciRemovePeriodicEd (HC_STRUC*, OHCI_ED*);
UINT8   OHCI_RepeatTDCallBack(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   OHCI_ResetHC(HC_STRUC*);
UINT8   OHCI_StopUnsupportedHC(HC_STRUC*);
UINT32  OHCI_ProcessRootHubStatusChange(HC_STRUC*);
UINT8   OHCIWaitForTransferComplete(HC_STRUC*, OHCI_ED*, OHCI_TD*,DEV_INFO*);
UINT8   OHCI_ControlTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID    OHCI_ProcessTD(HC_STRUC*, OHCI_TD*);
UINT8   OHCI_GeneralTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   OHCI_PollingTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID    StopControllerType(UINT8);
UINT8   USBCheckPortChange (HC_STRUC*, UINT8, UINT8);
VOID	OHCI_FreeAllStruc(HC_STRUC* fpHCStruc);			//(EIP28707+)
BOOLEAN OhciIsHalted(HC_STRUC*);
UINT8   OhciTranslateInterval(UINT8);

UINT8	UsbGetDataToggle(DEV_INFO*,UINT8);
VOID	UsbUpdateDataToggle(DEV_INFO*, UINT8, UINT8);

extern  USB_GLOBAL_DATA     *gUsbData;

extern  void        USB_InitFrameList (HC_STRUC*, UINT32);

UINT32  HcReadPciReg(HC_STRUC*, UINT32);
VOID    HcWritePciReg(HC_STRUC*, UINT32, UINT32);
UINT32  HcReadHcMem(HC_STRUC*, UINT32);
VOID    HcWriteHcMem(HC_STRUC*, UINT32, UINT32);
VOID    HcClearHcMem(HC_STRUC*, UINT32, UINT32);
VOID    HcSetHcMem(HC_STRUC*, UINT32, UINT32);
UINT32  HcReadOpReg(HC_STRUC*, UINT32);
VOID    HcWriteOpReg(HC_STRUC*, UINT32, UINT32);
VOID    HcClearOpReg(HC_STRUC*, UINT32, UINT32);
VOID    HcSetOpReg(HC_STRUC*, UINT32, UINT32);
UINT8	HcDmaMap(HC_STRUC*, UINT8, UINT8*, UINT32, UINT8**, VOID**);
UINT8	HcDmaUnmap(HC_STRUC*, VOID*);

extern  void        FixedDelay(UINTN);
extern  void*       USB_MemAlloc (UINT16);
extern  UINT8       USB_InstallCallBackFunction (CALLBACK_FUNC);
extern  DEV_INFO*   USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);
extern  UINT8       USB_MemFree(void _FAR_*, UINT16);
extern	UINT8		USB_DisconnectDevice(HC_STRUC*, UINT8, UINT8);	//(EIP28707+)
#if USB_DEV_KBD
extern  void        USBKBDPeriodicInterruptHandler(HC_STRUC*);
extern  void        USBKeyRepeat(HC_STRUC*, UINT8);
#endif

/**
    This function fills the host controller driver
    routine pointers

    @param fpHCDHeader     Ptr to the host controller header structure

    @retval Status: USB_SUCCESS = Success
        USB_ERROR = Failure

**/

UINT8
OHCI_FillHCDEntries(HCD_HEADER *fpHCDHeader)
{
    //
    // Fill the routines here
    //
    fpHCDHeader->pfnHCDStart                = OHCI_Start;
    fpHCDHeader->pfnHCDStop                 = OHCI_Stop;
    fpHCDHeader->pfnHCDEnumeratePorts       = OHCI_EnumeratePorts;
    fpHCDHeader->pfnHCDDisableInterrupts    = OHCI_DisableInterrupts;
    fpHCDHeader->pfnHCDEnableInterrupts     = OHCI_EnableInterrupts;
    fpHCDHeader->pfnHCDProcessInterrupt     = OHCI_ProcessInterrupt;
    fpHCDHeader->pfnHCDGetRootHubStatus     = OHCI_GetRootHubStatus;
    fpHCDHeader->pfnHCDDisableRootHub       = OHCI_DisableRootHub;
    fpHCDHeader->pfnHCDEnableRootHub        = OHCI_EnableRootHub;
    fpHCDHeader->pfnHCDControlTransfer      = OHCI_ControlTransfer;
    fpHCDHeader->pfnHCDBulkTransfer         = OHCI_BulkTransfer;
    fpHCDHeader->pfnHCDInterruptTransfer    = OHCI_InterruptTransfer;
    fpHCDHeader->pfnHCDDeactivatePolling    = OHCI_DeactivatePolling;
    fpHCDHeader->pfnHCDActivatePolling      = OHCI_ActivatePolling;
    fpHCDHeader->pfnHCDDisableKeyRepeat     = OHCI_DisableKeyRepeat;
    fpHCDHeader->pfnHCDEnableKeyRepeat      = OHCI_EnableKeyRepeat;
    fpHCDHeader->pfnHCDEnableEndpoints      = USB_EnableEndpointsDummy;
    fpHCDHeader->pfnHCDInitDeviceData       = USB_InitDeviceDataDummy;
    fpHCDHeader->pfnHCDDeinitDeviceData     = USB_DeinitDeviceDataDummy;
	fpHCDHeader->pfnHCDResetRootHub         = OHCI_ResetRootHub;
	fpHCDHeader->pfnHCDClearEndpointState	= 0;	//(EIP54283+)
	fpHCDHeader->pfnHCDGlobalSuspend        = OHCI_GlobalSuspend;	//(EIP54018+)

    return  USB_SUCCESS;
}


/**
    This API function is called to start a OHCI host controller.
    The input to the routine is the pointer to the HC structure
    that defines this host controller

    @param fpHCStruc   Ptr to the host controller structure

    @retval Status: USB_SUCCESS = Success
        USB_ERROR = Failure

**/

UINT8
OHCI_Start (
    HC_STRUC*   HcStruc
)
{
    UINT32          OhciControlReg = 0;
	UINT32			BaseAddr;
	UINT32			HcFmInterval;

    HcStruc->wAsyncListSize = OHCI_FRAME_LIST_SIZE;
    HcStruc->dMaxBulkDataSize = MAX_OHCI_BULK_DATA_SIZE;

    //
    // Get memory base address of the HC and store it in the HCStruc
    //
    BaseAddr = HcReadPciReg(HcStruc, USB_MEM_BASE_ADDRESS);
    BaseAddr &= 0xFFFFFFF0;    // Mask lower bits
    HcStruc->BaseAddress = BaseAddr;

    //
    // Get the number of ports supported by the host controller (Offset 48h)
    //
    HcStruc->bNumPorts = (UINT8)HcReadHcMem(HcStruc, OHCI_RH_DESCRIPTOR_A);

	USB_InitFrameList(HcStruc, 0);

    //
    // Enable the ED schedules
    //
    if (OHCI_StartEDSchedule(HcStruc) == USB_ERROR) {
        return USB_ERROR;
    }

    //
    // First stop the host controller if it is at all active
    //
    if (OHCI_DisableInterrupts(HcStruc) == USB_ERROR) {
        return USB_ERROR;
    }

	// Save the contents of the HcFmInterval register
	HcFmInterval = HcReadHcMem(HcStruc, OHCI_FRAME_INTERVAL);
	HcFmInterval &= 0x3FFF;
	if (HcFmInterval != 0x2EDF) {
		USB_DEBUG(3, "OHCI: HcFmInterval %x\n", HcFmInterval);
	}
	HcFmInterval |= (((6 * (HcFmInterval - 210)) / 7) & 0x7FFF) << 16;

	// Issue a controller reset
	if (OHCI_ResetHC(HcStruc) != USB_SUCCESS) {
		return USB_ERROR;
	}
	
	// Restore the value of the HcFmInterval register
	HcWriteHcMem(HcStruc, OHCI_FRAME_INTERVAL, HcFmInterval);

    //
    // Program the frame list base address register
    //
    HcWriteHcMem(HcStruc, OHCI_HCCA_REG, (UINT32)(UINTN)HcStruc->fpFrameList);

    //
    // Set the periodic start time = 2A27h (10% off from HcFmInterval-2EDFh)
    //
    HcWriteHcMem(HcStruc, OHCI_PERIODIC_START, (((HcFmInterval & 0x3FFF) * 9) / 10) & 0x3FFF);

	//
	// Start the host controller for periodic list and control list.
	//
    OhciControlReg = (PERIODIC_LIST_ENABLE | CONTROL_LIST_ENABLE |
        BULK_LIST_ENABLE | USBOPERATIONAL);
#if USB_RUNTIME_DRIVER_IN_SMM
    if (!(HcStruc->dHCFlag & HC_STATE_EXTERNAL)) {
        OhciControlReg |= INTERRUPT_ROUTING;
    }
#endif
    HcWriteHcMem(HcStruc, OHCI_CONTROL_REG, OhciControlReg);

    //
    // Enable interrupts from the host controller, enable SOF, WDH, RHSC interrupts
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE,
        MASTER_INTERRUPT_ENABLE | WRITEBACK_DONEHEAD_ENABLE |
        RH_STATUS_CHANGE_ENABLE | OWNERSHIP_CHANGE_ENABLE);

	//
    // Set the HC state to running
    //
    HcStruc->dHCFlag |= HC_STATE_RUNNING;

    // Set USB_FLAG_DRIVER_STARTED flag when HC is running.
    if (!(gUsbData->dUSBStateFlag & USB_FLAG_DRIVER_STARTED)) {
        gUsbData->dUSBStateFlag |= USB_FLAG_DRIVER_STARTED;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    //
    // Register the USB HW SMI handler
    //
    if (!(HcStruc->dHCFlag & HC_STATE_IRQ)) {
        if (!(HcStruc->dHCFlag & HC_STATE_EXTERNAL)) {
            UsbInstallHwSmiHandler(HcStruc);
        } else {
            USBSB_InstallUsbIntTimerHandler();
        }
    }
#endif

    return  USB_SUCCESS;
}


/**
    This API function is called to stop the OHCI controller.
    The input to the routine is the pointer to the HC structure
    that defines this host controller.

    @param fpHCStruc   Ptr to the host controller structure

    @retval Status: USB_SUCCESS = Success
        USB_ERROR = Failure

**/

UINT8
OHCI_Stop(
    HC_STRUC* HcStruc
)
{
    UINT8 Port;

    for (Port = 1; Port <= HcStruc->bNumPorts; Port++) {
        USB_DisconnectDevice(HcStruc, (UINT8)(HcStruc->bHCNumber | BIT7), Port); 
    }

    //
    // Reset Host Controller
    //
    HcWriteHcMem(HcStruc, OHCI_CONTROL_REG, USBRESET);
    FixedDelay(gUsbData->UsbTimingPolicy.OhciHcResetDelay * 1000);   // Wait 10ms for assertion of reset

    //
    // Disable interrupts
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_DISABLE, 0xffffffff);

    //
    // Disable OHCI KBC Emulation
    //
    HcWriteHcMem(HcStruc, OHCI_HCE_CONTROL, 0);

    USB_InitFrameList(HcStruc, 0);
	OHCI_FreeAllStruc(HcStruc);		//(EIP28707+)

	USBKeyRepeat(HcStruc, 3);

    HcStruc->dHCFlag &= ~HC_STATE_RUNNING;

    CheckBiosOwnedHc();

    return USB_SUCCESS;
}


/**
    This function is called when TdRepeat/TD32ms completes
    a transaction.  This TD runs a dummy interrupt transaction
    to a non-existant device address for the purpose of
    generating a periodic timeout interrupt which in turn
    is used to generate keyboard repeat or update LED status.

    @param fpHCStruc   Pointer to the HCStruc structure
        fpDevInfo   NULL (pDevInfo is not valid)
        fpTD        Pointer to the TD that completed
        fpBuffer    Not used

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_RepeatTDCallBack(
    HC_STRUC	*HcStruc,
    DEV_INFO	*DevInfo,
    UINT8		*Td,
    UINT8		*Buffer,
    UINT16      DataLength
)
{
    OHCI_DESC_PTRS  *DescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;

    DescPtrs->fpTDRepeat->bActiveFlag = FALSE;

#if USB_DEV_KBD
    USBKBDPeriodicInterruptHandler(HcStruc);
#endif

	if (!(DescPtrs->fpEDRepeat->dControl & ED_SKIP_TDQ)) {
	    //
	    // Rebind the TD to its parent ED
	    //
	    DescPtrs->fpEDRepeat->fpHeadPointer = (UINT32)(UINTN)DescPtrs->fpTDRepeat;

	    //
	    // Clear the link pointer. It may point to some other TD
	    //
	    DescPtrs->fpTDRepeat->fpLinkPointer = OHCI_TERMINATE;

	    //
	    // Reactivate the TD
	    //
	    DescPtrs->fpTDRepeat->dControlStatus = DescPtrs->fpTDRepeat->dCSReloadValue;
	    DescPtrs->fpTDRepeat->bActiveFlag = TRUE;
	}

    return USB_SUCCESS;
}


/**
    This API function is called to disable the interrupts
    generated by the OHCI host controller. The input to the
    routine is the pointer to the HC structure that defines this
    host controller.  This routine will stop the HC to avoid
    further interrupts.

    @param fpHCStruc   Ptr to the host controller structure

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_DisableInterrupts(
    HC_STRUC* HcStruc
)
{
    //
    // Disable interrupt generation (global) bit (Set bit31)
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_DISABLE, MASTER_INTERRUPT_ENABLE);
    //
    // Disable periodic, isochronous, control and bulk list processing, reset bits 2 to 5
    //
    HcWriteHcMem(HcStruc, OHCI_CONTROL_REG, BIT2 + BIT3 + BIT4 + BIT5);

    return USB_SUCCESS;
}


/**
    This function enables the HC interrupts

    @param fpHCStruc   Pointer to the HCStruc structure

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_EnableInterrupts(
    HC_STRUC* HcStruc
)
{
    //
    // Enable periodic, control and bulk list processing
    // Set bit 2, 4 & 5
    //
    HcSetHcMem(HcStruc, OHCI_CONTROL_REG, BIT2 + BIT4 + BIT5);
    //
    // Enable interrupt generation (global) bit
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE, MASTER_INTERRUPT_ENABLE);

    return  USB_SUCCESS;
}


/**
    This function is called when the USB interrupt bit is
    set. This function will parse through the TDs and QHs to
    find out completed TDs and call their respective call
    back functions

    @param fpHCStruc   Pointer to the HCStruc structure

    @retval USB_ERROR Interrupt not processed
    @retval USB_SUCCESS Interrupt processed

**/

UINT8
OHCI_ProcessInterrupt(
    HC_STRUC* HcStruc
)
{
    OHCI_TD *Td;
    OHCI_TD *NextTd;
    UINT8 IntProcessFlag = USB_ERROR;  // Set as interrupt not processed

    // Make sure MEMIO & Bus mastering are enabled
    if (((UINT8)HcReadPciReg(HcStruc, USB_REG_COMMAND) & 0x6) != 0x6) {
        return IntProcessFlag;
    }

    if ((HcReadPciReg(HcStruc, USB_MEM_BASE_ADDRESS) & ~(0x7F)) != 
        (UINT32)HcStruc->BaseAddress) {
        return IntProcessFlag;
    }
    //
    // Check the interrupt status register for an ownership change.  If this bit
    // is set, it means that the O/S USB device driver is attempting to takeover
    // control of the host controller. In this case the host controller is
    // shut down and the interrupt routing bit in the control register is cleared
    // (this disables SMI generation and enebles standard IRQ generation from
    // the USB host controller.
    //
    if (HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & OWNERSHIP_CHANGE) {
        HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, OWNERSHIP_CHANGE);
        if (HcReadHcMem(HcStruc, OHCI_HCCA_REG) == (UINT32)(UINTN)HcStruc->fpFrameList) {
            //
            // OS tries to take the control over HC
            //
            gUsbData->dUSBStateFlag &= (~USB_FLAG_ENABLE_BEEP_MESSAGE);

			OHCI_StopUnsupportedHC(HcStruc);

            OHCI_Stop(HcStruc);
            return USB_SUCCESS; // Set interrupt as processed
        } else {    // Ownership comes back to the driver - reinit
            gUsbData->bHandOverInProgress = FALSE;
            gUsbData->dUSBStateFlag  |= (USB_FLAG_ENABLE_BEEP_MESSAGE);
            OHCI_Start(HcStruc);
            return USB_SUCCESS; // Set interrupt as processed
        }
    }   // ownership change

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (OhciIsHalted(HcStruc)) {
        // Clear All bits of the interrupt status
        HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, 
            HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS));
		return IntProcessFlag;
	}
    //
    // Check whether the controller is still under BIOS control
    // Read the base address of the Periodic Frame List to the OHCI HCCA
    // register and compare with stored value
    //
    if ((HcReadHcMem(HcStruc, OHCI_HCCA_REG) & 0xFFFFFF00) !=
            (UINT32)(UINTN)HcStruc->fpFrameList) {
        return IntProcessFlag;
    }
    //
    // Check the interrupt status register for a root hub status change.  If
    // this bit is set, then a device has been attached or removed from one of
    // the ports on the root hub.
    //
    if (HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & RH_STATUS_CHANGE) {
        //
        // Stop the periodic list processing to avoid more interrupts from HC
        //
        HcClearHcMem(HcStruc, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);
//        USB_DEBUG(3, "before OHCI_ProcessRootHubStatusChange\n");
        // Handle root hub change
        IntProcessFlag = (UINT8)OHCI_ProcessRootHubStatusChange(HcStruc);
//        USB_DEBUG(3, "after OHCI_ProcessRootHubStatusChange\n");
        //
        // Re-enable the periodic list processing
        //
        HcSetHcMem(HcStruc, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);
    }

    //
    // Check the interrupt status register for a one or more TDs completing.
    //
    if (!(HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & WRITEBACK_DONEHEAD)) {
        return USB_SUCCESS;
    }
    IntProcessFlag = USB_SUCCESS;  // Set interrupt as processed

    //
    // The memory dword at HCCADONEHEAD has been updated to contain the head
    // pointer of the linked list of TDs that have completed.  Walk through
    // this list processing TDs as we go.
    //
    for (;;) {
        Td = (OHCI_TD*)(UINTN)(((OHCI_HCCA_PTRS*)HcStruc->fpFrameList)->dHccaDoneHead);
        ((OHCI_HCCA_PTRS*)HcStruc->fpFrameList)->dHccaDoneHead = 0;

        //
        // Clear the WRITEBACK_DONEHEAD bit of the interrupt status register
        // in the host controller
        //
        HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, WRITEBACK_DONEHEAD);

        if (!Td) {
            break;   // no TDs in the list
        }

        do {
            Td = (OHCI_TD*)((UINTN)Td & 0xfffffff0);
            NextTd = (OHCI_TD*)Td->fpLinkPointer;
            OHCI_ProcessTD(HcStruc, Td);
            Td = NextTd;
        } while (Td);
    }   // Check if any TDs completed while processing

    return IntProcessFlag;
}


/**
    This function returns the port connect status for the
    root hub port

    @param pHCStruc    Pointer to HCStruc of the host controller
        bPortNum    Port in the HC whose status is requested

**/

UINT8
OHCI_GetRootHubStatus(
    HC_STRUC*   HcStruc, 
    UINT8       PortNum,
    BOOLEAN     ClearChangeBits
)
{
    UINT8   RhStatus = USB_PORT_STAT_DEV_OWNER;
    UINT32  PortStatus;
    UINT16  PortReg = ((UINT16)PortNum << 2) + (OHCI_RH_PORT1_STATUS - 4);
    
    PortStatus = HcReadHcMem(HcStruc, PortReg);
	USB_DEBUG(3, "Ohci port[%d] status: %08x\n", PortNum, PortStatus);

    if (PortStatus & CURRENT_CONNECT_STATUS) {
        RhStatus |= USB_PORT_STAT_DEV_CONNECTED;
		if (PortStatus & PORT_ENABLE_STATUS) {
			RhStatus |= USB_PORT_STAT_DEV_ENABLED;
		}
    }

    RhStatus |= USB_PORT_STAT_DEV_FULLSPEED;   // Assume full speed and set the flag
    if (PortStatus & LOW_SPEED_DEVICE_ATTACHED) {
        RhStatus &= ~USB_PORT_STAT_DEV_FULLSPEED;  // Reset full speed
        RhStatus |= USB_PORT_STAT_DEV_LOWSPEED;    // Set low speed flag
    }

    if (PortStatus & CONNECT_STATUS_CHANGE) {
        if (ClearChangeBits == TRUE) {
            HcWriteHcMem(HcStruc, PortReg, CONNECT_STATUS_CHANGE);	//(EIP66448+)
        }
        RhStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED; // Set connect status change flag
    }
										//(EIP66448+)>
	if (PortStatus & PORT_ENABLE_STATUS_CHANGE) {
	    if (ClearChangeBits == TRUE) {
	        HcWriteHcMem(HcStruc, PortReg, PORT_ENABLE_STATUS_CHANGE);
	    }
	}
										//<(EIP66448+)
    return RhStatus;
}


/**
    This function disables the specified root hub port.

    @param fpHCStruc   Pointer to HCStruc of the host controller
        bPortNum    Port in the HC to be disabled.

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_DisableRootHub(
    HC_STRUC*   HcStruc,
    UINT8       PortNum
)
{
    UINT32 PortReg = ((UINT32)PortNum << 2) + (OHCI_RH_PORT1_STATUS - 4);
    
    HcWriteHcMem(HcStruc, (UINT16)PortReg, CLEAR_PORT_ENABLE);
    
    return USB_SUCCESS;
}


/**
    This function enables the specified root hub port.

    @param fpHCStruc   Pointer to HCStruc of the host controller
        bPortNum    Port in the HC to be enabled.

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_EnableRootHub(
    HC_STRUC    *HcStruc,
    UINT8       PortNum
)
{
    return  USB_SUCCESS;
}

/**
    This function resets the specified root hub port.

    @param HcStruc   Pointer to HCStruc of the host controller
        PortNum    Port in the HC to be disabled.

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_ResetRootHub (
    HC_STRUC*   HcStruc, 
    UINT8       PortNum
)
{
	UINT16	PortReg = ((UINT16)PortNum << 2) + (OHCI_RH_PORT1_STATUS - 4);
	UINT32	i;
	
    HcWriteHcMem(HcStruc, PortReg, SET_PORT_RESET);    // Reset the port

    // The reset signaling must be driven for a minimum of 10ms
    FixedDelay(10 * 1000);

    //
    // Wait for reset to complete
    //
    for (i = 0; i < 500; i++) {
		if (HcReadHcMem(HcStruc, PortReg) & PORT_RESET_STATUS_CHANGE) {
			break;
		}
        FixedDelay(100);       // 100 us delay
    }

	if (!(HcReadHcMem(HcStruc, PortReg) & PORT_RESET_STATUS_CHANGE)) {
		USB_DEBUG(3, "OHCI: port reset timeout, status: %08x\n", 
			HcReadHcMem(HcStruc, PortReg));
		return USB_ERROR;
	}

    //
    // Clear the reset status change status
    //
    HcWriteHcMem(HcStruc, PortReg, PORT_RESET_STATUS_CHANGE);

    // Some devices need a delay here
	FixedDelay(3 * 1000);  // 3 ms delay

    return  USB_SUCCESS;
}

										//(EIP54018+)>
/**
    This function suspend the OHCI HC.

**/

UINT8
OHCI_GlobalSuspend(
    HC_STRUC*	HcStruc
)
{
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE, RESUME_DETECTED_ENABLE);
    
    FixedDelay(40 * 1000);
    
    HcWriteHcMem(HcStruc, OHCI_CONTROL_REG, USBSUSPEND | REMOTE_WAKEUP_ENABLE);
    
    FixedDelay(20 * 1000);

    HcStruc->dHCFlag &= ~(HC_STATE_RUNNING);
    HcStruc->dHCFlag |= HC_STATE_SUSPEND;

    return  USB_SUCCESS;
}
										//<(EIP54018+)

/**
    This function executes a device request command transaction
    on the USB. One setup packet is generated containing the
    device request parameters supplied by the caller.  The setup
    packet may be followed by data in or data out packets
    containing data sent from the host to the device
    or vice-versa. This function will not return until the
    request either completes successfully or completes in error
    (due to time out, etc.)

    @param fpHCStruc   Pointer to HCStruc of the host controller
        pDevInfo    DeviceInfo structure (if available else 0)
        wRequest    Request type (low byte)
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
        Request code, a one byte code describing
        the actual device request to be executed
        (ex: Get Configuration, Set Address etc)
        wIndex      wIndex request parameter (meaning varies)
        wValue      wValue request parameter (meaning varies)
        fpBuffer    Buffer containing data to be sent to the
        device or buffer to be used to receive data
        wLength     wLength request parameter, number of bytes
        of data to be transferred in or out
        of the host controller


    @retval Number of bytes transferred


    @note  Do not use USB_SUCCESS or USB_ERROR as returned values

**/

UINT16
OHCI_ControlTransfer (
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT16      wRequest,
    UINT16      wIndex,
    UINT16      wValue,
    UINT8       *fpBuffer,
    UINT16      wLength
)
{
    UINT16  *fpData;
    OHCI_DESC_PTRS *fpDescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;
    OHCI_ED *fpED;
    OHCI_TD *fpTD;
    UINT32 dData;
    UINT16 wData;
	UINT8 CompletionCode;
    UINT32 TransferLength;
    UINT8   *BufPhyAddr = NULL;
    VOID    *BufferMapping = NULL;

	if (OhciIsHalted(HcStruc)) {
		return 0;
	}
    //FixedDelay(5 * 1000);    // 5 ms delay is necessary for OHCI host controllers

    if (!VALID_DEVINFO(DevInfo)) {
        return 0;
    }

	gUsbData->dLastCommandStatusExtended = 0;

    //
    // Build the device request in the data area of the control setup qTD
    //
    fpData = (UINT16*)fpDescPtrs->fpTDControlSetup->aSetupData;
    *fpData++ = wRequest;
    *fpData++ = wValue;
    *fpData++ = wIndex;
    *fpData++ = wLength;
    //*(UINTN*)fpData = (UINTN)BufPhyAddr;
    //
    // Prepare some registers that will be used in building the TDs below.
    // wLength  contains the data length.
    // fpBuffer contains the absolute address of the data buffer.
    // wRequest contains the request type (bit 7 = 0/1 for Out/In).
    // fpDevInfo will contain a pointer to the DeviceInfo structure for the given device.
    //
    // Ready the EDControl for the control transfer.
    //
    fpED = fpDescPtrs->fpEDControl;
    //
    // The ED control field will be set so
    //   Function address & Endpoint number = ESI,
    //   Direction = From TD,
    //   Speed = DeviceInfo.bEndpointSpeed,
    //   Skip = 1, Format = 0,
    //   Max packet size  = DeviceInfo.wEndp0MaxPacket
    // The HeadPointer field will be set to TDControlSetup
    // The TailPointer field will be set to OHCI_TERMINATE
    // The LinkPointer field will be set to OHCI_TERMINATE
    //
    dData = (UINT32)DevInfo->wEndp0MaxPacket;
    if (dData > 0x40) dData = 0x40; // Force the max packet size to 64 bytes
    dData <<= 16;                   // dData[26:16] = device's packet size
    wData = (UINT16)DevInfo->bEndpointSpeed;  // 00/01/10 for HI/LO/FULL
    wData = (wData & 1) << 13;      // wData[13] = full/low speed flag
    wData |= DevInfo->bDeviceAddress | ED_SKIP_TDQ;
    fpED->dControl = dData | wData;
    fpED->fpTailPointer = 0;
    fpED->fpEDLinkPointer = 0;

    fpTD = fpDescPtrs->fpTDControlSetup;
    //
    // The ControlStatus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_SETUP_PACKET,
    //   Delay Interrupt = GTD_IntD,
    //   Data Toggle = GTD_SETUP_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to the TD's SetupData buffer
    //   which was before initialized to contain a DeviceRequest struc.
    // The BufferEnd field will point to the last byte of the TD's SetupData
    //   buffer.
    // The LinkPointer field will point to the TDControlData if data will
    //   be sent/received or to the TDControlStatus if no data is expected.
    // The CSReloadValue field will contain 0 because this is a "one shot" packet.
    // The pCallback will be set to point to the OHCI_ControlTDCallback routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control TDs do
    //   not need rebinding to the EDControl.
    //
    fpTD->dControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_SETUP_PACKET | GTD_SETUP_TOGGLE |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));

    fpTD->fpCurrentBufferPointer = (UINT32)(UINTN)fpTD->aSetupData;
    fpTD->fpBufferEnd = (UINT32)(UINTN)fpTD->aSetupData + 7; // size of aSetupData - 1

    wData = wLength ;                   //(EIP67230)

    if (wLength) {  // some data to transfer
        fpTD = fpDescPtrs->fpTDControlData;     // Fill in various fields in the TDControlData.
        //
        // The ControlStatus field will be set so
        //   Buffer Rounding = 1,
        //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
        //   Delay Interrupt = GTD_IntD,
        //   Data Toggle = GTD_DATA1_TOGGLE,
        //   Error Count = GTD_NO_ERRORS,
        //   Condition Code = GTD_NOT_ACCESSED
        // The CurrentBufferPointer field will point to the caller's buffer
        //   which is now in EBP.
        // The BufferEnd field will point to the last byte of the caller's buffer.
        // The LinkPointer field will point to the TDControlStatus.
        // The CSReloadValue field will contain 0 because this is a "one shot" packet.
        // The pCallback will be set to point to the OHCI_ControlTDCallback routine.
        // The ActiveFlag field will be set to TRUE.
        // The DeviceAddress field does not need to be set since the Control TDs do
        //   not need rebinding to the EDControl.
        // The CSReloadValue field will contain 0 because this is a "one shot" packet.
        // The pCallback will be set to point to the OHCI_ControlTDCallback routine.
        // The ActiveFlag field will be set to TRUE.    return  USB_SUCCESS;
        // The DeviceAddress field does not need to be set since the Control TDs do}
        //   not need rebinding to the EDControl.
        //
        HcDmaMap(HcStruc, (UINT8)(wRequest & BIT7), fpBuffer, wLength, 
                &BufPhyAddr, &BufferMapping);
        dData = (UINT32)(GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
        dData = (wRequest & BIT7)? (dData | GTD_IN_PACKET | GTD_IntD) : (dData | GTD_OUT_PACKET);
        fpTD->dControlStatus = dData;
        fpTD->fpCurrentBufferPointer = (UINT32)(UINTN)BufPhyAddr;
        fpTD->fpBufferEnd = (UINT32)((UINTN)fpBuffer + wData - 1);
    }
    fpTD = fpDescPtrs->fpTDControlStatus;   // Fill in various fields in the TDControlStatus.
    //
    // The ControlStaus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
    //   Delay Interrupt = GTD_IntD,
    //   Data Toggle = GTD_DATA1_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to NULL
    // The BufferEnd field will point to NULL.
    // The LinkPointer field will point to OHCI_TERMINATE.
    // The CSReloadValue field will contain 0 because this is a "one shot" packet.
    // The pCallback will be set to point to the OHCI_ControlTdCallback routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control TDs do
    //   not need rebinding to the EdControl.
    //
    // Note: For OUT control transfer status should be IN and
    //       for IN cotrol transfer, status should be OUT.
    //
    dData = (UINT32)(GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
    dData = (wRequest & BIT7)? (dData | GTD_OUT_PACKET) : (dData | GTD_IN_PACKET | GTD_IntD);
    fpTD->dControlStatus = dData;
    fpTD->fpCurrentBufferPointer = 0;
    fpTD->fpBufferEnd = 0;
    fpTD->fpLinkPointer = 0;
    //
    // Link all the pointers together
    //
    fpTD = fpDescPtrs->fpTDControlSetup;
    fpED->fpHeadPointer = (UINT32)(UINTN)fpTD;
    if (wLength) {  // chain in data TD
        fpTD->fpLinkPointer = (UINT32)(UINTN)fpDescPtrs->fpTDControlData;
        fpTD = fpDescPtrs->fpTDControlData;
    }
    fpTD->fpLinkPointer = (UINT32)(UINTN)fpDescPtrs->fpTDControlStatus;

    fpDescPtrs->fpTDControlStatus->fpLinkPointer = 0;

    fpTD = fpDescPtrs->fpTDControlSetup;
    do {
        fpTD->dCSReloadValue = 0;
        fpTD->bCallBackIndex = USB_InstallCallBackFunction(OHCI_ControlTDCallback);
        fpTD->bActiveFlag = TRUE;
        fpTD = (OHCI_TD*)fpTD->fpLinkPointer;
    } while (fpTD);
    //
    // Now control queue is complete, so set ED_SKIP_TDQ=0
    //
    fpED->dControl &= ~ED_SKIP_TDQ;
    //
    // Set the HcControlHeadED register to point to the EDControl.
    //
    HcWriteHcMem(HcStruc, OHCI_CONTROL_HEAD_ED, (UINT32)(UINTN)fpED);
    //
    // Now put the control setup, data and status into the HC's schedule by
    // setting the ControllListFilled field of HcCommandStatus reg.
    // This will cause the HC to execute the transaction in the next active frame.
    //
    HcWriteHcMem(HcStruc, OHCI_COMMAND_STATUS, CONTROL_LIST_FILLED);
    //
    // Now wait for the control status TD to complete.  When it has completed,
    // the OHCI_ControlTDCallback will set its active flag to FALSE.
    //
    OHCIWaitForTransferComplete(HcStruc, fpED, fpDescPtrs->fpTDControlStatus, DevInfo);
    //
    // Stop the HC from processing the EDControl by setting its Skip bit.
    //
    fpED->dControl |= ED_SKIP_TDQ;

    //
    // Finally check for any error bits set in both the TDControlStatus.
    // If the TD did not complete successfully, return STC.
    //
    CompletionCode = (UINT8)(fpDescPtrs->fpTDControlStatus->dControlStatus >> 28);    // dData[3:0] = Completion status
    gUsbData->bLastCommandStatus &= ~USB_CONTROL_STALLED;

    fpTD = fpDescPtrs->fpTDControlData;
    TransferLength = wLength ; 
    if( fpTD->fpCurrentBufferPointer != 0){
        TransferLength = fpTD->fpCurrentBufferPointer - (UINT32)(UINTN)fpBuffer;
    }


	wData = 0;
	switch (CompletionCode) {
        case GTD_NO_ERROR:
            wData = TransferLength;
			break;
		case GTD_STALL:
			gUsbData->bLastCommandStatus |= USB_CONTROL_STALLED;
			gUsbData->dLastCommandStatusExtended |= USB_TRSFR_STALLED;
			break;
		case GTD_NOT_ACCESSED:
			gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
			break;
		default:
			break;
	}
    
    if (wLength) {
        HcDmaUnmap(HcStruc, BufferMapping);
    }

    return wData;
}


/**
    This function executes a bulk transaction on the USB. The
    transfer may be either DATA_IN or DATA_OUT packets containing
    data sent from the host to the device or vice-versa. This
    function wil not return until the request either completes
    successfully or completes with error (due to time out, etc.)
    Size of data can be upto 64K

    @param pHCStruc    Pointer to HCStruc of the host controller
        pDevInfo    DeviceInfo structure (if available else 0)
        bXferDir    Transfer direction
        Bit 7: Data direction
        0 Host sending data to device
        1 Device sending data to host
        Bit 6-0 : Reserved
        fpBuffer    Buffer containing data to be sent to the
        device or buffer to be used to receive data
        value in Segment:Offset format
        dwLength    dwLength request parameter, number of bytes
        of data to be transferred in or out
        of the host controller

    @retval Amount of data transferred

**/

UINT32
OHCI_BulkTransfer (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       bXferDir,
    UINT8       *fpBuffer,
    UINT32      dwLength
)
{
    UINT32      dData;
    UINT8   bData;
    OHCI_DESC_PTRS *fpDescPtrs;
    UINT16      wMaxPkt;
    UINT8       bEndp;
    UINT8       bDatToggle;
    UINT32      dBytesToTransfer, dBytesRemaining;
    UINT32      dBytesTransferred;
    UINT32      Buffer;
    UINT8       *BufPhyAddr = NULL;
    VOID        *BufferMapping = NULL;

	if (OhciIsHalted(HcStruc)) {
		return 0;
	}
    
    if (!VALID_DEVINFO(DevInfo)) {
        return 0;
    }

	gUsbData->dLastCommandStatusExtended = 0;

    fpDescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;
    wMaxPkt = (bXferDir & 0x80)? DevInfo->wBulkInMaxPkt : DevInfo->wBulkOutMaxPkt;
    bEndp = (bXferDir & 0x80)? DevInfo->bBulkInEndpoint : DevInfo->bBulkOutEndpoint;
	bDatToggle = UsbGetDataToggle(DevInfo, bEndp | bXferDir);

    if( wMaxPkt == 0){
        return 0;
    }

    dBytesRemaining = dwLength;
    dBytesTransferred = 0;
    dBytesToTransfer = 0;

    HcDmaMap(HcStruc, bXferDir, fpBuffer, dwLength, &BufPhyAddr, &BufferMapping);

    for (;dBytesRemaining != 0; dBytesRemaining -= dBytesToTransfer) {
        dBytesToTransfer = 
             (dBytesRemaining < FULLSPEED_MAX_BULK_DATA_SIZE_PER_FRAME)?
                    dBytesRemaining : FULLSPEED_MAX_BULK_DATA_SIZE_PER_FRAME;

        Buffer = (UINT32)(UINTN)BufPhyAddr + dBytesTransferred;

        //
        //  Set the SKIP bit in the EdBulk to avoid accidental scheduling
        //
        fpDescPtrs->fpEDBulk->dControl = ED_SKIP_TDQ;
        //
        // Set the ED's head pointer field to bulk data TD and tail pointer field to
        // OHCI_TERMINATE. Also set ED's link pointer to OHCI_TERMINATE.
        //
        fpDescPtrs->fpEDBulk->fpHeadPointer = (UINT32)(UINTN)fpDescPtrs->fpTDBulkData;
        fpDescPtrs->fpEDBulk->fpTailPointer = OHCI_TERMINATE;
        fpDescPtrs->fpEDBulk->fpEDLinkPointer = OHCI_TERMINATE;
        //
        // Form the data needed for ED's control field with the available information
        //
        dData = (bXferDir & 0x80)? ED_IN_PACKET : ED_OUT_PACKET;
        dData |= DevInfo->bDeviceAddress;
        dData |= (UINT16)bEndp << 7;
        dData |= (UINT32)wMaxPkt << 16;
        //
        // Update the ED's control field with the data formed
        // ASSUME ALL MASS DEVICES ARE FULL SPEED DEVICES.
        //
        fpDescPtrs->fpEDBulk->dControl = dData;
        //
        // Fill the general bulk data TD with relevant information.  Set the
        //  TD's control field with buffer rounding set to 1, direction PID to
        //  don't care, delay interrupt to INTD, data toggle to the latest data
        //  toggle value, error count to no errors and condition code to not accessed.
        //
        // Set the data toggle to DATA0 (SETUP_TOGGLE)
        fpDescPtrs->fpTDBulkData->dControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET |
            GTD_IntD | GTD_SETUP_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
        fpDescPtrs->fpTDBulkData->dControlStatus |= (UINT32)bDatToggle << 24;
        //
        // GTD current buffer pointer field will point to the caller's buffer which
        // now in the variable fpBuffer
        //
        fpDescPtrs->fpTDBulkData->fpCurrentBufferPointer = Buffer;
        fpDescPtrs->fpTDBulkData->fpBufferEnd = Buffer + dBytesToTransfer - 1;
        fpDescPtrs->fpTDBulkData->fpLinkPointer = OHCI_TERMINATE;
        //
        // GTD's CSReloadValue field will contain 0 because this is a "one shot" packet
        //
        fpDescPtrs->fpTDBulkData->dCSReloadValue = 0;
        fpDescPtrs->fpTDBulkData->bCallBackIndex = USB_InstallCallBackFunction(OHCI_GeneralTDCallback);
        fpDescPtrs->fpTDBulkData->bActiveFlag = TRUE;
    
        fpDescPtrs->fpEDBulk->dControl &= ~ED_SKIP_TDQ;
        //
        // Set the HCBulkHeadED register to point to the bulk ED
        //
        HcWriteHcMem(HcStruc, OHCI_BULK_HEAD_ED, (UINT32)(UINTN)fpDescPtrs->fpEDBulk);
        //
        // Clear bulk stall/time out condition flag
        //
        gUsbData->bLastCommandStatus &= ~(USB_BULK_STALLED + USB_BULK_TIMEDOUT);
        //
        // Enable the bulk list processing
        //
        HcWriteHcMem(HcStruc, OHCI_COMMAND_STATUS, BULK_LIST_FILLED);
    
        OHCIWaitForTransferComplete(HcStruc, fpDescPtrs->fpEDBulk, fpDescPtrs->fpTDBulkData, DevInfo);
        //
        // Stop the HC from processing the EDBulk by setting its Skip bit.
        //
        fpDescPtrs->fpEDBulk->dControl |= ED_SKIP_TDQ;
        //
        // Update the data toggle value into the mass info structure
        //
		UsbUpdateDataToggle(DevInfo, bEndp | bXferDir, 
			(UINT8)(((fpDescPtrs->fpTDBulkData->dControlStatus & GTD_DATA_TOGGLE) >> 24) & 1));
        //
        // Check for the error conditions - if possible recover from them
        //
        bData = (UINT8)(fpDescPtrs->fpTDBulkData->dControlStatus >> 28);
		switch (bData) {
			case GTD_STALL:
				gUsbData->bLastCommandStatus |= USB_BULK_STALLED;
				gUsbData->dLastCommandStatusExtended |= USB_TRSFR_STALLED;
				break;
			case GTD_NOT_ACCESSED:
				gUsbData->bLastCommandStatus |= USB_BULK_TIMEDOUT;
				gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
				break;
			default:
				break;
		}

		if (bData != GTD_NO_ERROR) {
			break;
		}

        //
        // Get the size of data transferred
        //
        dData = fpDescPtrs->fpTDBulkData->fpCurrentBufferPointer;
        if (dData != 0)
        {
            //
            // Device sent less data than requested, calculate the
            // transferred size and exit
            //
            //dBytesTransferred += (UINT32)(UINTN)fpDescPtrs->fpTDBulkData->fpBufferEnd - dData; //(EIP55025-)
     	    dBytesTransferred += dData - Buffer;   //Short Packet (OHCI Spec 4.3.1.3.5  Transfer Completion, Pg.23) //<(EIP55025)+    
            break;
        }

        //
        // CurrentBufferPointer equals 0. This indicates the successfull TD completion,
        // all data is transferred. Adjust the total amount and continue.
        //
        dBytesTransferred += dBytesToTransfer;
    }

    HcDmaUnmap(HcStruc, BufferMapping);
    
    return  dBytesTransferred;
}


/**
    This function executes an interrupt transaction on the USB.
    The data transfer direction is always DATA_IN. This
    function wil not return until the request either completes
    successfully or completes in error (due to time out, etc.)

    @param fpHCStruc   Pointer to HCStruc of the host controller
        fpDevInfo   DeviceInfo structure (if available else 0)
        fpBuffer    Buffer containing data to be sent to the
        device or buffer to be used to receive data
        wLength     wLength request parameter, number of bytes
        of data to be transferred in

    @retval Number of bytes transferred


    @note  DO NOT TOUCH THE LINK POINTER OF THE TDInterruptData. It is
              statically allocated and linked with other items in the
              1ms schedule

**/

UINT16
OHCI_InterruptTransfer (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *fpBuffer,
    UINT16      wLength)
{
    UINT16 wMaxPkt;
    UINT8 bEndp, bDatToggle;
    UINT32 dData;
    OHCI_ED	*IntEd;
	OHCI_TD	*IntTd;
	UINT8	CompletionCode;
	UINT32	BytesTransferred;
	UINT8   *BufPhyAddr = NULL;
	VOID    *BufferMapping = NULL;
	
	if (OhciIsHalted(HcStruc)) {
		return 0;
	}

    if (!VALID_DEVINFO(DevInfo)) {
        return 0;
    }

	gUsbData->dLastCommandStatusExtended = 0;

	IntEd = USB_MemAlloc(GET_MEM_BLK_COUNT(sizeof(OHCI_ED) + sizeof(OHCI_TD)));

	if (IntEd == NULL) {
		return 0;
	}

	IntTd = (OHCI_TD*)((UINTN)IntEd + sizeof(OHCI_ED));

    //
    // Set the SKIP bit to avoid accidental scheduling
    //
    IntEd->dControl = ED_SKIP_TDQ;
    //
    // Set the ED's head pointer field to interrupt data TD and tail pointer
    // field to OHCI_TERMINATE. Also set ED's link pointer to OHCI_TERMINATE.
    //
    IntEd->fpHeadPointer = (UINT32)(UINTN)IntTd;
    IntEd->fpTailPointer = OHCI_TERMINATE;
    IntEd->fpEDLinkPointer = OHCI_TERMINATE;
    IntEd->Interval = OhciTranslateInterval(DevInfo->bPollInterval);

    //
    // Get maximum packet size from device info structure
    //
    wMaxPkt = DevInfo->wIntMaxPkt;
    bEndp = DevInfo->bIntEndpoint & 0xF;
	bDatToggle = UsbGetDataToggle(DevInfo, DevInfo->bIntEndpoint);
	
    //
    // Form the data needed for ED's control field with the available information
    //
    dData = (DevInfo->bIntEndpoint & BIT7)? ED_IN_PACKET : ED_OUT_PACKET;
    dData |= DevInfo->bDeviceAddress | ((UINT16)bEndp << 7);
    dData |= ((UINT32)wMaxPkt << 16);
	dData |= (UINT32)(DevInfo->bEndpointSpeed & 1) << 13;
    //
    // Update the ED's control field with the data formed
    // ASSUME ALL MASS DEVICES ARE FULL SPEED DEVICES.
    //
    IntEd->dControl = dData;
    //
    // Fill the general interrupt data TD with relevant information.  Set the
    //  TD's control field with buffer rounding set to 1, direction PID to
    //  don't care, delay interrupt to INTD, data toggle to the latest data
    //  toggle value, error count to no errors and condition code to not accessed.
    //
    // Set the data toggle to DATA0 (SETUP_TOGGLE)
    //
    dData = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET  | GTD_IntD | GTD_SETUP_TOGGLE |
        GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
    IntTd->dControlStatus = dData;
    //
    // Set the data toggle depending on the bDatToggle value
    //
    IntTd->dControlStatus |= ((UINT32)bDatToggle << 24);
    //
    // GTD current buffer pointer field will point to the caller's buffer
    //
    HcDmaMap(HcStruc, DevInfo->bIntEndpoint & BIT7, fpBuffer, wLength, 
		&BufPhyAddr, &BufferMapping);
    IntTd->fpCurrentBufferPointer = (UINT32)(UINTN)BufPhyAddr;
    //
    // GTD's buffer end field will point to the last byte of the caller's buffer
    //
    IntTd->fpBufferEnd = (UINT32)(UINTN)(BufPhyAddr + wLength - 1);
    //
    // GTD's link pointer field will be set to OHCI_TERMINATE
    //
    IntTd->fpLinkPointer = OHCI_TERMINATE;
    //
    // GTD's CSReloadValue field will contain 0 because this is a "one shot" packet
    //
    IntTd->dCSReloadValue = 0;
    //
    // GTD's pCallback will point to the OHCI_GeneralTDCallback routine
    //
    IntTd->bCallBackIndex = USB_InstallCallBackFunction(OHCI_GeneralTDCallback);
    //
    // GTD's ActiveFlag field will be set to TRUE.
    //
	OhciAddPeriodicEd(HcStruc, IntEd);

	IntTd->bActiveFlag = TRUE;
    IntEd->dControl &= ~ED_SKIP_TDQ;

    //
    // Now wait for the interrupt data TD to complete.
    //
    OHCIWaitForTransferComplete(HcStruc, IntEd, IntTd, DevInfo);
    //
    // Stop the HC from processing the EDInterrupt by setting its Skip bit.
    //
    OhciRemovePeriodicEd(HcStruc, IntEd);
    //
    // Get appropriate data sync shift value
    //
    bDatToggle = (UINT8)((IntTd->dControlStatus & GTD_DATA_TOGGLE) >> 24) & 1;
	UsbUpdateDataToggle(DevInfo, DevInfo->bIntEndpoint, bDatToggle);
	
    //
    // Check for the error conditions - if possible recover from them
    //
	CompletionCode = (UINT8)(IntTd->dControlStatus >> 28);
	switch (CompletionCode) {
		case GTD_STALL:
			gUsbData->dLastCommandStatusExtended |= USB_TRSFR_STALLED;
			break;
		case GTD_NOT_ACCESSED:
			gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
			break;
		default:
			break;
	}

	BytesTransferred = IntTd->fpCurrentBufferPointer == 0 ? wLength :
		IntTd->fpCurrentBufferPointer - (UINT32)BufPhyAddr;

    HcDmaUnmap(HcStruc, BufferMapping);

	USB_MemFree(IntEd, GET_MEM_BLK_COUNT(sizeof(OHCI_ED) + sizeof(OHCI_TD)));

    return (UINT16)BytesTransferred;
}


/**
    This function activates the polling TD for the requested
    device. The device may be a USB keyboard or USB hub

    @param fpHCStruc   Pointer to the HC structure
        fpDevInfo   Pointer to the device information structure

    @retval USB_SUCCESS or USB_ERROR

    @note  For the keyboard device this routine allocates TDRepeat
              also, if it is not already allocated. This routine allocate
              a polling TD and schedule it to 8ms schedule for keyboards
              and to 1024ms schedule for hubs.
**/

UINT8
OHCI_ActivatePolling (
    HC_STRUC* fpHCStruc,
    DEV_INFO* fpDevInfo)
{
    UINT32 dData;
    UINT8   *fpPtr;
    OHCI_DESC_PTRS *fpDescPtrs = fpHCStruc->stDescPtrs.fpOHCIDescPtrs;
	UINT8	bDatToggle;

	if (OhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}
    
    if( !VALID_DEVINFO( fpDevInfo) )
        return USB_ERROR;

	bDatToggle = UsbGetDataToggle(fpDevInfo, fpDevInfo->bIntEndpoint);

    fpPtr = USB_MemAlloc(1);
    ASSERT(fpPtr);
    fpDevInfo->fpPollEDPtr  = fpPtr;
    fpPtr = USB_MemAlloc(1);
    ASSERT(fpPtr);
    fpDevInfo->fpPollTDPtr  = fpPtr;

    dData = (fpDevInfo->bIntEndpoint & BIT7)? ED_IN_PACKET : ED_OUT_PACKET;
    dData |= (UINT32)fpDevInfo->bDeviceAddress | ((fpDevInfo->bIntEndpoint & 0xF) << 7);
    dData |= ((UINT32)fpDevInfo->wIntMaxPkt << 16);
	dData |= (UINT32)(fpDevInfo->bEndpointSpeed & 1) << 13;
	dData |= ED_SKIP_TDQ;

    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->dControl = dData;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->fpHeadPointer = (UINT32)(UINTN)fpDevInfo->fpPollTDPtr;
	((OHCI_ED*)fpDevInfo->fpPollEDPtr)->fpHeadPointer |= bDatToggle << 1;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->fpEDLinkPointer = OHCI_TERMINATE;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->fpTailPointer = OHCI_TERMINATE;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->Interval = OhciTranslateInterval(fpDevInfo->bPollInterval);

	fpDevInfo->fpPollDataBuffer = USB_MemAlloc(GET_MEM_BLK_COUNT(fpDevInfo->PollingLength));  
	ASSERT(fpDevInfo->fpPollDataBuffer);

    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->dControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->dCSReloadValue = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->fpCurrentBufferPointer =
    			(UINT32)(fpDevInfo->fpPollDataBuffer); 					//(EIP54782)
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->fpBufferEnd =
    			(UINT32)(fpDevInfo->fpPollDataBuffer + fpDevInfo->PollingLength - 1);
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->fpLinkPointer = OHCI_TERMINATE;
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->bCallBackIndex = USB_InstallCallBackFunction(OHCI_PollingTDCallback);

    OhciAddPeriodicEd(fpHCStruc, (OHCI_ED*)fpDevInfo->fpPollEDPtr);

    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->bActiveFlag = TRUE;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->dControl &= ~ED_SKIP_TDQ;
    return  USB_SUCCESS;
}

/**
    This function de-activates the polling TD for the requested
    device. The device may be a USB keyboard or USB hub

    @param fpHCStruc   Pointer to the HC structure
        fpDevInfo   Pointer to the device information structure

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_DeactivatePolling (
    HC_STRUC* fpHCStruc,
    DEV_INFO* fpDevInfo)
{
    OHCI_ED *fpOHCIED = (OHCI_ED*)fpDevInfo->fpPollEDPtr;
    OHCI_TD *fpOHCITD = (OHCI_TD*)fpDevInfo->fpPollTDPtr;

	if (OhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}
	
    if(!fpOHCIED) {
        return USB_SUCCESS;
    }

    fpOHCITD->dControlStatus = 0;
    fpOHCITD->dCSReloadValue = 0;
    fpOHCITD->bActiveFlag    = FALSE;

    OhciRemovePeriodicEd(fpHCStruc, fpOHCIED);

	UsbUpdateDataToggle(fpDevInfo, fpDevInfo->bIntEndpoint, 
			(UINT8)((fpOHCIED->fpHeadPointer & ED_TOGGLE_CARRY) >> 1));

    USB_MemFree(fpOHCITD, GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
    fpDevInfo->fpPollTDPtr = NULL;

    USB_MemFree(fpOHCIED, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    fpDevInfo->fpPollEDPtr = NULL;

	if(fpDevInfo->fpPollDataBuffer) {
		USB_MemFree(fpDevInfo->fpPollDataBuffer, 
			GET_MEM_BLK_COUNT(fpDevInfo->PollingLength)); 
    	fpDevInfo->fpPollDataBuffer = 0;
	} 

    return  USB_SUCCESS;
}

/**
    This function is called when a polling TD from the TD pool
    completes an interrupt transaction to its assigned device.
    This routine should process any data in the TD's data buffer,
    handle any errors, and then copy the TD's CSReloadValue
    field into its control status field to put the TD back
    into service.



    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_PollingTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
)
{
    UINT8   i;
    UINT16  BytesTransferred;

    if (((OHCI_TD*)Td)->bActiveFlag == FALSE) {
        return USB_SUCCESS;
    }

	((OHCI_TD*)Td)->bActiveFlag = FALSE;
	HcClearHcMem(HcStruc, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);

    for (i = 1; i < MAX_DEVICES; i++) {
        DevInfo = &gUsbData->aDevInfoTable[i];
        if (DevInfo->Flag & DEV_INFO_DEV_PRESENT) {
            if (DevInfo->fpPollTDPtr == Td) {
                break;
            }
        }
    }

    if (i == MAX_DEVICES) {
        return USB_ERROR;
    }

	UsbUpdateDataToggle(DevInfo, DevInfo->bIntEndpoint, 
			(UINT8)((((OHCI_ED*)DevInfo->fpPollEDPtr)->fpHeadPointer & ED_TOGGLE_CARRY) >> 1));

										//(EIP59707)>
	if ((((OHCI_TD*)Td)->dControlStatus & GTD_STATUS_FIELD) == GTD_NO_ERROR) {
        //
        // Get the size of data transferred
        //
        if (((OHCI_TD*)Td)->fpCurrentBufferPointer != 0) {
            BytesTransferred = ((OHCI_TD*)Td)->fpCurrentBufferPointer -
                (UINT32)(UINTN)(DevInfo->fpPollDataBuffer);
        } else {
            BytesTransferred = DevInfo->PollingLength;
        }
	    (*gUsbData->aCallBackFunctionTable[DevInfo->bCallBackIndex-1])(
	                HcStruc,
	                DevInfo,
	                (UINT8*)Td,
	                DevInfo->fpPollDataBuffer,
	                BytesTransferred);
	}
										//<(EIP59707)
    HcSetHcMem(HcStruc, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);

    // Clear the link pointer. It may point to some other TD
    ((OHCI_TD*)Td)->fpLinkPointer = OHCI_TERMINATE;
    ((OHCI_TD*)Td)->dControlStatus = ((OHCI_TD*)Td)->dCSReloadValue;
    ((OHCI_TD*)Td)->fpCurrentBufferPointer = (UINT32)(UINTN)(DevInfo->fpPollDataBuffer);		//(EIP54782)
    ((OHCI_ED*)DevInfo->fpPollEDPtr)->fpHeadPointer &= ED_TOGGLE_CARRY;
    ((OHCI_ED*)DevInfo->fpPollEDPtr)->fpHeadPointer |= (UINTN)((OHCI_TD*)Td);
    ((OHCI_TD*)Td)->bActiveFlag = TRUE;
    // Reset the TD's control and buffer pointer fields to their original values.
    return USB_SUCCESS;
}

/**
    This function disables the keyboard repeat rate logic by
    enabling the repeat TD

    @param fpHCStruc   Pointer to the HCStruc structure

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_DisableKeyRepeat (
	HC_STRUC	*HcStruc
)
{
    OHCI_DESC_PTRS  *DescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;

    if (DescPtrs->fpEDRepeat == NULL) {
		return USB_ERROR;
    }

    DescPtrs->fpEDRepeat->dControl |= ED_SKIP_TDQ;    // Inactive
	DescPtrs->fpTDRepeat->bActiveFlag = FALSE;

    return  USB_SUCCESS;
}


/**
    This function enables the keyboard repeat rate logic by
    enabling the repeat TD

    @param fpHCStruc   Pointer to the HCStruc structure

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_EnableKeyRepeat (
	HC_STRUC	*HcStruc
)
{
    OHCI_DESC_PTRS  *DescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;

    if (DescPtrs->fpEDRepeat == NULL) {
		return USB_ERROR;
    }

	DescPtrs->fpTDRepeat->fpLinkPointer = OHCI_TERMINATE;
	DescPtrs->fpEDRepeat->fpHeadPointer = (UINT32)(UINTN)DescPtrs->fpTDRepeat;
	DescPtrs->fpTDRepeat->dControlStatus = 
						DescPtrs->fpTDRepeat->dCSReloadValue;
	DescPtrs->fpTDRepeat->bActiveFlag = TRUE;
	DescPtrs->fpEDRepeat->dControl &= (~ED_SKIP_TDQ); // Active

    return  USB_SUCCESS;
}


/**
    This API function is called to enumerate the root hub ports
    in the OHCI controller. The input to the routine is the
    pointer to the HC structure  that defines this host controller

    @param fpHCStruc   Ptr to the host controller structure

    @retval Status: USB_SUCCESS = Success
        USB_ERROR = Failure

**/

UINT8
OHCI_EnumeratePorts(
    HC_STRUC* HcStruc
)
{
	UINT32  RhDescriptorA = 0;
	UINT8	PowerOnDelay = 0;
	UINT8	Index = 0;
	UINT16	PortReg = OHCI_RH_PORT1_STATUS;

	RhDescriptorA = HcReadHcMem(HcStruc, OHCI_RH_DESCRIPTOR_A);
	if (!(RhDescriptorA & NO_POWER_SWITCH)) {
		if (!(RhDescriptorA & POWER_SWITCH_MODE)) {
			// All ports are powered at the same time, enable global port power
	    	HcWriteHcMem(HcStruc, OHCI_RH_STATUS, SET_GLOBAL_POWER);
		} else {
			// Each port is powered individually, enable individual port's power
			for (Index = 0; Index < HcStruc->bNumPorts; PortReg+=4, Index++) {
                // Set PortPowerControlMask bit 
                HcSetHcMem(HcStruc, OHCI_RH_DESCRIPTOR_B, ((1 << (Index + 1)) << 16));
                // Set PortPower bit
				HcWriteHcMem(HcStruc, PortReg, SET_PORT_POWER);
			}
		}
		PowerOnDelay = ((RhDescriptorA & POWERON2POWERGOOD_TIME) >> 24) << 1;
		FixedDelay(PowerOnDelay * 1000);
	}

    OHCI_ProcessRootHubStatusChange(HcStruc);

    return  USB_SUCCESS;
}


/**
    This function adds a ED to the frame list

    @param HcStruc - Ptr to the host controller structure
        Ed - ED will be added in periodic schedule

**/

UINT8
OhciAddPeriodicEd (
    HC_STRUC    *HcStruc,
    OHCI_ED     *Ed
)
{
    UINT16  Index;
    UINT32  *PrevPtr;
    OHCI_ED *Current;

    if (Ed == NULL || Ed->Interval == 0) {
        return USB_ERROR;
    }

    for (Index = 0; Index < HcStruc->wAsyncListSize; Index += Ed->Interval) {
        PrevPtr = &HcStruc->fpFrameList[Index]; 
        Current = (OHCI_ED*)(*PrevPtr);

        while (Current != NULL) {
            if (Current->Interval <= Ed->Interval) {
                break;
            }

            PrevPtr = &Current->fpEDLinkPointer; 
            Current = (OHCI_ED*)Current->fpEDLinkPointer;
        }

        if (Current == Ed) {
            continue;
        }
        Ed->fpEDLinkPointer = (UINT32)(UINTN)Current;
        *PrevPtr = (UINT32)(UINTN)Ed;
    }

    return USB_SUCCESS;
}

/**
    This function removes a ED from the frame list

    @param HcStruc - Ptr to the host controller structure
        Ed - ED will be removed from periodic schedule

**/

UINT8
OhciRemovePeriodicEd(
    HC_STRUC    *HcStruc,
    OHCI_ED     *Ed
)
{
    UINT16  Index;
    UINT32  *PrevPtr;
    OHCI_ED *Current;

    if (Ed == NULL || Ed->Interval == 0) {
        return USB_ERROR;
    }

    Ed->dControl |= ED_SKIP_TDQ;

    for (Index = 0; Index < HcStruc->wAsyncListSize; Index += Ed->Interval) {
        PrevPtr = &HcStruc->fpFrameList[Index]; 
        Current = (OHCI_ED*)(*PrevPtr);

        while (Current != NULL) {
            if (Current == Ed) {
                break;
            }

            PrevPtr = &Current->fpEDLinkPointer; 
            Current = (OHCI_ED*)Current->fpEDLinkPointer;
        }

        if (Current == NULL) {
            continue;
        }
        *PrevPtr = Ed->fpEDLinkPointer;
    }

    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, START_OF_FRAME);
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE, START_OF_FRAME_ENABLE);

    for (Index = 0; Index < 100; Index++) {
        if (HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & START_OF_FRAME) {
            break;
        }
        FixedDelay(10);   // 10 us delay
    }
    ASSERT(Index < 100);
    ASSERT(HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & START_OF_FRAME);
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_DISABLE, START_OF_FRAME_DISABLE);

    return USB_SUCCESS;
}

/**
    This function starts the standard TD schedules for the
    USB host controller

    @param HCStruc for the controller

    @retval USB_ERROR on error, USB_SUCCESS on success

    @note  This routine creates 1, 2, 8, 32 and 1024ms schedules

**/

UINT8
OHCI_StartEDSchedule(
    HC_STRUC    *HcStruc
)
{
    OHCI_DESC_PTRS  *DescPtrs;
    UINT8           *Ptr;

    //
    // Allocate descriptor structure and fill it in HCStruc
    //
    DescPtrs = (OHCI_DESC_PTRS*)USB_MemAlloc (GET_MEM_BLK_COUNT_STRUC(OHCI_DESC_PTRS));
    ASSERT(DescPtrs);
    if (!DescPtrs) return USB_ERROR;

    //
    // Save the value in the HC struc
    //
    HcStruc->stDescPtrs.fpOHCIDescPtrs = DescPtrs;

    //
    // Allocate 4 EDs + 1 TDs and put them in Descriptor list
    //
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    ASSERT(Ptr);
    if (!Ptr) return USB_ERROR;

    DescPtrs->PeriodicEd = (OHCI_ED*)Ptr;
    DescPtrs->PeriodicEd->dControl = ED_SKIP_TDQ;
    DescPtrs->PeriodicEd->fpEDLinkPointer = 0;
    DescPtrs->PeriodicEd->Interval = 1;

    // Initialize each entry of Interrupt Table as statically disable ED
    OhciAddPeriodicEd(HcStruc, DescPtrs->PeriodicEd);

    //
    // Allocate ED/TD for EDControl, TDControlSetup, TDControlData,
    // TDControlStatus, EDBulk, TDBulkData, EDInterrupt and TDInterruptData
    //
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT(2 * sizeof(OHCI_ED) + 4 * sizeof(OHCI_TD)));
    ASSERT(Ptr);
    if (!Ptr) return USB_ERROR;

    //
    // Save the 8 ED/TD in their proper position. Note: fpHCStruc->stDescPtrs.fpEHCIDescPtrs
    // is initialized earlier in OHCI_StartEDSchedule.
    //
    DescPtrs->fpEDControl = (OHCI_ED*)Ptr;
    Ptr += sizeof (OHCI_ED);

    DescPtrs->fpTDControlSetup = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->fpTDControlData = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->fpTDControlStatus = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->fpEDBulk = (OHCI_ED*)Ptr;
    Ptr += sizeof (OHCI_ED);

    DescPtrs->fpTDBulkData = (OHCI_TD*)Ptr;

	if (HcStruc->dHCFlag & HC_STATE_EXTERNAL) {
		return USB_SUCCESS;
	}

    // Allocate a ED/TD for EDRepeat/TDRepeat
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    ASSERT(Ptr);
    DescPtrs->fpEDRepeat  = (OHCI_ED*)Ptr;
 
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
    ASSERT(Ptr);
    DescPtrs->fpTDRepeat  = (OHCI_TD*)Ptr;

    DescPtrs->fpEDRepeat->dControl = (DUMMY_DEVICE_ADDR |
            ED_IN_PACKET | ED_SKIP_TDQ | (DEFAULT_PACKET_LENGTH << 16));
    DescPtrs->fpEDRepeat->fpHeadPointer = (UINT32)(UINTN)DescPtrs->fpTDRepeat;
    DescPtrs->fpEDRepeat->fpEDLinkPointer = OHCI_TERMINATE;
    DescPtrs->fpEDRepeat->fpTailPointer = OHCI_TERMINATE;
    DescPtrs->fpEDRepeat->Interval = 8;

    DescPtrs->fpTDRepeat->dControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
        GTD_TWO_ERRORS | (GTD_NOT_ACCESSED << 28));
    DescPtrs->fpTDRepeat->dCSReloadValue = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
        GTD_TWO_ERRORS | (GTD_NOT_ACCESSED << 28));

    DescPtrs->fpTDRepeat->fpCurrentBufferPointer =
                (UINT32)(UINTN)DescPtrs->fpTDRepeat->aSetupData;
    DescPtrs->fpTDRepeat->fpBufferEnd =
                (UINT32)(UINTN)DescPtrs->fpTDRepeat->aSetupData;
    DescPtrs->fpTDRepeat->fpLinkPointer = OHCI_TERMINATE;
    DescPtrs->fpTDRepeat->bCallBackIndex = USB_InstallCallBackFunction(OHCI_RepeatTDCallBack);
    DescPtrs->fpTDRepeat->bActiveFlag = FALSE;

    OhciAddPeriodicEd(HcStruc, DescPtrs->fpEDRepeat);
	
	USBKeyRepeat(HcStruc, 0);

    return USB_SUCCESS;
}


/**
    This function resets the OHCI controller

    @param Pointer to the HCStruc structure

**/

UINT8 OHCI_ResetHC(
    HC_STRUC* HcStruc
)
{
	UINT8	i;
    //
    // Issue a software reset and HC go to UsbSuspend state
    //
    HcWriteHcMem(HcStruc, OHCI_COMMAND_STATUS, HC_RESET);

    // The reset operation must be completed within 10 us
	for (i = 0; i < 100; i++) {
		FixedDelay(1);   // 1 us delay
		if (!(HcReadHcMem(HcStruc, OHCI_COMMAND_STATUS) & HC_RESET)) {
			return USB_SUCCESS;
		}
	}

	return USB_ERROR;
}


/**
    This function is called when TD1024ms completes
    a transaction. This TD runs a dummy interrupt transaction
    to a non-existant device address for the purpose of
    generating a periodic timeout interrupt.  This periodic
    interrupt may be used to check for new devices on the
    root hub etc.

    @param Pointer to HC Struc

**/

UINT32 OHCI_ProcessRootHubStatusChange(
    HC_STRUC*   HcStruc
)
{
    UINT8   HcNumber;
    UINT8   Port;

    //
    // Check bEnumFlag before enumerating devices behind root hub
    //
    if (gUsbData->bEnumFlag == TRUE) {
        return USB_ERROR;
    }
    gUsbData->bEnumFlag = TRUE;    // Set enumeration flag and avoid hub port enumeration
    //
    // Mask the Host Controller interrupt so the ISR does not get re-entered due
    // to an IOC interrupt from any TDs that complete in frames while we are
    // configuring a new device that has just been plugged in.
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_DISABLE, 0x80000000);
    //
    // Check all the ports on the root hub for any change in connect status.
    // If the connect status has been changed on either or both of these ports,
    // then call the  routine UsbHubPortChange for each changed port.
    //
    HcNumber = HcStruc->bHCNumber | BIT7;

    for (Port = 1; Port <= HcStruc->bNumPorts; Port++) {
										//(EIP59663)>
        //bPortStatus = OHCI_GetRootHubStatus (fpHCStruc, bPort+1);
      	//HcClearHcMem(HcStruc, OHCI_RH_PORT1_STATUS+bPort*4, 0xFFFF);
        //if (bPortStatus & USB_PORT_STAT_DEV_CONNECT_CHANGED) {
		USBCheckPortChange(HcStruc, HcNumber, Port);
        //}
        //HcClearHcMem(HcStrucs, OHCI_RH_PORT1_STATUS+bPort*4, 0xFFFF);
										//<(EIP59663)
    }
    //
    // Clear the RH_STATUS_CHANGE bit of the interrupt status register
    // in the host controller: write 1 to bit to clear it
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, RH_STATUS_CHANGE);

    //
    // Renable interrupts from the host controller
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE, MASTER_INTERRUPT_ENABLE);

    gUsbData->bEnumFlag    = FALSE;
    return USB_SUCCESS;
}



/**
    This function executes a device request command transaction

    @param fpHCStruc   Pointer to HCStruc of the host controller
        fpTD        Pointer to the TD which has to be completed

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCIWaitForTransferComplete(
	HC_STRUC	*HcStruc, 
	OHCI_ED		*XferEd,
	OHCI_TD		*LastTd,
    DEV_INFO*	DevInfo
)
{
    UINT32 Count ;
    UINT32 Timeout = gUsbData->wTimeOutValue << 4; // *16, makes it number of 60mcs units

    //
    // Check status change loop iteration
    //
    for (Count = 0; !Timeout || Count < Timeout; Count++) {
        OHCI_ProcessInterrupt(HcStruc);
        if (!LastTd->bActiveFlag ) {
           return USB_SUCCESS;
        } else if (!VALID_DEVINFO(DevInfo)){
            USB_DEBUG (DEBUG_LEVEL_3, "OHCI Abort: devinfo: %x\n", DevInfo);
            return USB_ERROR;
        }
        FixedDelay(60);  // 60 microseconds
    }

	XferEd->dControl |= ED_SKIP_TDQ;
	OHCI_ProcessInterrupt(HcStruc);

	if (!LastTd->bActiveFlag) {
		return USB_SUCCESS;
	}

    USB_DEBUG (DEBUG_LEVEL_3, "OHCI Time-Out\n");

    return USB_ERROR;
}


/**
    This routine is called, from host controllers that supports
    OS handover functionality (currently from OHCI driver only), when OS
    wants the BIOS to hand-over the host controllers to the OS.  This routine
    will stop HC that does not support this functionality.

**/

UINT8
OHCI_StopUnsupportedHC(
	HC_STRUC*	HcStruc
)
{
    UINT8	i;

	if (!gUsbData->UsbEhciHandoff) {
		return USB_SUCCESS;
	}

//
// Currently this host controller stops only the EHCI host controllers
// Find the EHCI host controller HCStruc
//
    for (i = 0; i < gUsbData->HcTableCount; i++ ) {
        if (gUsbData->HcTable[i] == NULL) {
            continue;
        }
		if (!(gUsbData->HcTable[i]->dHCFlag & HC_STATE_RUNNING) ||
			(gUsbData->HcTable[i]->bHCType != USB_HC_EHCI) ||
			((gUsbData->HcTable[i]->wBusDevFuncNum & ~0x7) != 
			(HcStruc->wBusDevFuncNum & ~0x7))) {
			continue;
		}

		gUsbData->bHandOverInProgress = TRUE;
		(*gUsbData->aHCDriverTable[GET_HCD_INDEX(
			gUsbData->HcTable[i]->bHCType)].pfnHCDStop)(gUsbData->HcTable[i]);
    }

	return USB_SUCCESS;
}

/**
    This function is called when bulk data or interrupt data TD
    is completed. This routine just deactivates the TD.

    @param Pointer to the HCStruc structure
        Pointer to the TD that completed

**/

UINT8
OHCI_GeneralTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
 )
{
    ((OHCI_TD*)Td)->bActiveFlag = FALSE;
    return USB_SUCCESS;
}


/**
    This function is called when the control transfer scheduled
    is completed.

    @param fpHCStruc   Pointer to the HCStruc structure
        fpDevInfo   NULL (pDevInfo is not valid)
        fpTD        Pointer to the TD that completed
        fpBuffer    Not used

    @retval USB_SUCCESS or USB_ERROR

**/

UINT8
OHCI_ControlTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
)
{
    OHCI_DESC_PTRS *DescPtrs;
    //
    // Check to see if the TD that just completed has any error bits set.  If
    // any of the control TDs (Setup, Data, or Status) complete with an error, set
    // ActiveFlag of the control status TD and copy the error information from the
    // TD that just completed into the control status TD.
    //
    if ((UINT8)(((OHCI_TD*)Td)->dControlStatus >> 28)) {
        DescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;
        if (DescPtrs->fpTDControlStatus != (OHCI_TD*)Td) {
            DescPtrs->fpTDControlStatus->dControlStatus = ((OHCI_TD*)Td)->dControlStatus;
            DescPtrs->fpTDControlStatus->bActiveFlag = FALSE;
        }
    }
    //
    // Make the TD that just completed inactive.  It may be the control setup TD,
    // one of the control data TDs, or the control status TD.
    //
    ((OHCI_TD*)Td)->bActiveFlag = FALSE;

    return USB_SUCCESS;
}

/**
    This function will check whether the TD is completed
    if so, it will call the call back routine associated with
    this TD.

    @param HCStruc structure, Pointer to the TD

    @note  For any TD whose ActiveFlag is TRUE and its ControlStatus
      bit 23 is clear (completed), process the TD by calling
      its call back routine, if one is present.
**/

void OHCI_ProcessTD(
    HC_STRUC    *HcStruc,
    OHCI_TD     *Td
)
{
    if (!Td) {
        return;  // Check for NULL
    }
    if (Td->bActiveFlag != TRUE) {
        return;  // TD is not active
    }
    if (gUsbData->aCallBackFunctionTable[Td->bCallBackIndex-1]) {
        (*gUsbData->aCallBackFunctionTable[Td->bCallBackIndex-1])(
            HcStruc,
            0,
            (UINT8*)Td,
            0,
            0);
    }
}

										//(EIP28707+)>
/**
    This function is used to free the all the allocated TDs,
    QH and DescriptorPtr structure. This function only frees
    the entries in the DescriptorPtr and the descriptor pointer
    only.
    ;
    @param fpHCStruc   Pointer to the HCStruc structure

**/

VOID OHCI_FreeAllStruc(HC_STRUC* fpHCStruc)
{
	OHCI_DESC_PTRS  *fpDescPtrs;

	fpDescPtrs = fpHCStruc->stDescPtrs.fpOHCIDescPtrs;

// Free the EDs & TDs
	USB_MemFree(fpDescPtrs->PeriodicEd, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
	if (fpDescPtrs->fpEDRepeat) {
		USB_MemFree(fpDescPtrs->fpEDRepeat, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
	}
	if (fpDescPtrs->fpTDRepeat) {
		USB_MemFree(fpDescPtrs->fpTDRepeat, GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
	}

	USB_MemFree(fpDescPtrs->fpEDControl, 
        GET_MEM_BLK_COUNT(2 * sizeof(OHCI_ED) + 4 * sizeof(OHCI_TD)));
	
// Free descriptor structure (in BX)
	USB_MemFree(fpDescPtrs, GET_MEM_BLK_COUNT_STRUC(OHCI_DESC_PTRS));
}
										//<(EIP28707+)

/**
    This function check whether HC is halted.

**/

BOOLEAN
OhciIsHalted (
	HC_STRUC	*HcStruc
)
{
	return (HcReadHcMem(HcStruc, OHCI_CONTROL_REG) & HC_FUNCTION_STATE) != USBOPERATIONAL;
}

/**
    This function calculates the polling rate.

**/

UINT8
OhciTranslateInterval(
    UINT8   Interval
)
{
    UINT8  BitCount = 0;

    // The Interval value should be from 1 to 255
    ASSERT(Interval >= 1 && Interval <= 255);

    for (BitCount = 0; Interval != 0; BitCount++) {
        Interval >>= 1;
    }
    return (1 << (BitCount - 1));
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
