//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file PeiIpmiBmcInitialize.c
    PEI IPMI Transport Driver.

**/

//----------------------------------------------------------------------

#include "Token.h"
#include "IpmiBmc.h"
#include "InitLpcBmcHook.h"
#include <Include/ServerMgmtSetupVariable.h>

//----------------------------------------------------------------------

extern INIT_LPC_BMC INIT_LPC_BMC_HOOK_LIST EndOfInitLpcBmcHookListFunctions;
INIT_LPC_BMC* InitLpcBmcHookList[] = {INIT_LPC_BMC_HOOK_LIST NULL};

/**
    This routine calls the InitLpcBmc function or platform hooked function.

    @param PeiServices Pointer to PEI Services.

    @return EFI_STATUS Return Status

**/
EFI_STATUS
InitLpcBmcHook (
  IN CONST EFI_PEI_SERVICES          **PeiServices )
{
    EFI_STATUS Status;
    UINTN i;

    for(i = 0; InitLpcBmcHookList[i]; i++) {
        Status = InitLpcBmcHookList[i](PeiServices);
    }

    return Status;
}

/**
    Execute the Get Device ID command to determine whether or not the BMC is in
    Force Update Mode. If it is, then report it to the error manager.

    @param IpmiInstance Data structure describing BMC
               variables and used for sending commands

    @return EFI_STATUS Return Status of the Sent Command
    @retval EFI_SUCCESS Command executed Successfully

**/
EFI_STATUS
GetDeviceId (
  IN  OUT  EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance )
{
    EFI_STATUS                            Status;
    UINT8                                 DataSize;
    EFI_SM_CTRL_INFO                      ControllerInfo;

    DataSize = sizeof (EFI_SM_CTRL_INFO);

    //
    // Get the device ID information for the BMC.
    //
    Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
                &IpmiInstance->IpmiTransport,
                EFI_SM_NETFN_APP,
                BMC_LUN,
                EFI_APP_GET_DEVICE_ID,
                NULL,
                0,
                (UINT8*)&ControllerInfo,
                &DataSize );

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Get Device ID Command: Status %r\n", Status));
    //
    // If there is no error then proceed to check the data returned by the BMC
    //
    if (!EFI_ERROR(Status)) {

        //
        // If the controller is in Update Mode then set the BMC Status to indicate
        // the BMC is in force update mode.
        //
        if (ControllerInfo.UpdateMode != 0) {
            IpmiInstance->BmcStatus = EFI_BMC_UPDATE_IN_PROGRESS;
        }
    }
    return Status;
}

/**
    Setup and initialize the BMC for the DXE phase. In order to
    verify the BMC is functioning as expected, the BMC Self-test is performed.
    The results are then checked and any errors are reported to the error manager.
    Errors are collected throughout this routine and reported just prior to 
    installing the driver.  If there are more errors than BST_LOG_SIZE, then they
    will be ignored.

    @param FileHandle    Pointer to image file handle.
    @param PeiServices   Pointer to the PEI Core data Structure

    @return EFI_STATUS  Status of Driver execution
    @retval EFI_SUCCESS Successful driver initialization

**/
EFI_STATUS
InitializeIpmiPhysicalLayer (
  IN        EFI_PEI_FILE_HANDLE     FileHandle,
  IN  CONST EFI_PEI_SERVICES        **PeiServices )
{

    EFI_STATUS                              Status = EFI_SUCCESS;
    EFI_IPMI_BMC_INSTANCE_DATA              *IpmiInstance = NULL;
    UINT8                                   DataSize;
    UINT8                                   Index;
    EFI_PEI_PPI_DESCRIPTOR                  *PeiIpmiPpiDesc = NULL;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI         *PeiVariable;
    SERVER_MGMT_CONFIGURATION_DATA          ServerMgmtConfiguration;
    EFI_GET_SELF_TEST_STATUS                BstStatus;
    UINTN                                   Size;

    //
    // Locate the Setup configuration value.
    //
    Status = (*PeiServices)->LocatePpi (
                PeiServices,
                &gEfiPeiReadOnlyVariable2PpiGuid,
                0,
                NULL,
                (VOID **)&PeiVariable);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "gEfiPeiReadOnlyVariable2PpiGuid Status %r\n", Status));
    ASSERT_EFI_ERROR (Status);

    if (!EFI_ERROR(Status)) {
        Size = sizeof(SERVER_MGMT_CONFIGURATION_DATA);
        Status = PeiVariable->GetVariable (
                    PeiVariable,
                    L"ServerSetup",
                    &gEfiServerMgmtSetupVariableGuid,
                    NULL,
                    &Size,
                    &ServerMgmtConfiguration);
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "PeiVariable->GetVariable Status %r ServerMgmtConfiguration.BmcSupport: %x \n", Status, ServerMgmtConfiguration.BmcSupport));

        if (!EFI_ERROR(Status) && !ServerMgmtConfiguration.BmcSupport) {
            return EFI_UNSUPPORTED;
        }
    }

#if BMC_INIT_DELAY
    if (EFI_ERROR(Status)) {
         ServerMgmtConfiguration.WaitForBmc = 0; //Load default value.
    }   
#endif

    //
    // Allocate memory for IPMI Instance
    //
    IpmiInstance = (EFI_IPMI_BMC_INSTANCE_DATA*)AllocateZeroPool (sizeof (EFI_IPMI_BMC_INSTANCE_DATA));
    if (IpmiInstance == NULL) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Failed to allocate memory for IpmiInstance! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    //
    // Allocate memory for PPI Descriptor
    //
    PeiIpmiPpiDesc = (EFI_PEI_PPI_DESCRIPTOR*)AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
    if (PeiIpmiPpiDesc == NULL) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Failed to allocate memory for PeiIpmiPpiDesc! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    //
    //Platform Hook to initialize LPC for BMC and Host interface.
    //
    Status = InitLpcBmcHook (PeiServices);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Initialize IPMI Instance Data
    //
    if (IPMI_SYSTEM_INTERFACE == KCS_INTERFACE) { // KCS Interface
        IpmiInstance->Interface.KCS.DataPort        = IPMI_KCS_DATA_PORT;       // KCS Data Port
        IpmiInstance->Interface.KCS.CommandPort     = IPMI_KCS_COMMAND_PORT;    // KCS Command Port
        IpmiInstance->Interface.KCS.KcsRetryCounter = IPMI_KCS_COMMAND_PORT_READ_RETRY_COUNTER;
        IpmiInstance->IpmiTransport.SendIpmiCommand = EfiIpmiSendCommand;       // KCS SendCommand
    } else { // BT_Interface
        IpmiInstance->Interface.BT.CtrlPort    = IPMI_BT_CTRL_PORT;     // BT Control Port
        IpmiInstance->Interface.BT.ComBuffer   = IPMI_BT_BUFFER_PORT; // BT Buffer Port
        IpmiInstance->Interface.BT.IntMaskPort = IPMI_BT_INTERRUPT_MASK_PORT; // BT IntMask Port
        IpmiInstance->Interface.BT.BtDelay     = (UINT16)BT_DELAY; // BT Delay
        IpmiInstance->IpmiTransport.SendIpmiCommand = EfiBtIpmiSendCommand; // BT SendCommand
    }

    IpmiInstance->Signature     = SM_IPMI_BMC_SIGNATURE;
    IpmiInstance->SlaveAddress  = IPMI_BMC_SLAVE_ADDRESS;
    IpmiInstance->BmcStatus     = EFI_BMC_OK;
    IpmiInstance->IpmiTransport.GetBmcStatus = EfiIpmiBmcStatus;

#if BMC_INIT_DELAY
{
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "ServerMgmtConfiguration.WaitForBmc: %x \n", ServerMgmtConfiguration.WaitForBmc));
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Check for Power Failure PWR_FLR bit: %x \n",\
      ( *(volatile UINT8*) ((UINTN) (PcdGet64(PcdPciExpressBaseAddress)) + \
      (UINTN) PCI_LIB_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, LPC_GEN_PMCON_3)) & PWR_FLR_BIT )));
    //
    // Add 30 sec delay before sending Self Test command during First AC Power Cycle On.
    // Bmc starts simultaneously with BIOS so BMC takes 30 sec to respond.
    // Check Power Failure PWR_FLR bit for AC power loss.
    //
    if ( *(volatile UINT8*) ((UINTN) (PcdGet64(PcdPciExpressBaseAddress)) + \
            (UINTN) PCI_LIB_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, LPC_GEN_PMCON_3)) & PWR_FLR_BIT ) {
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Power Failure PWR_FLR bit for AC power loss. \n"));
        //
        // Check whether WaitForBmc setup option is enabled or not
        //
        if (ServerMgmtConfiguration.WaitForBmc) {
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Giving DELAY_OF_THIRTY_SECOND sec delay.. start \n"));
            MicroSecondDelay (DELAY_OF_THIRTY_SECOND);
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Giving DELAY_OF_THIRTY_SECOND sec delay.. end \n"));
            //
            // Clear Power Failure PWR_FLR status by writing 1.
            //
            *(volatile UINT8*) ((UINTN) (PcdGet64(PcdPciExpressBaseAddress)) + \
            (UINTN) PCI_LIB_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, LPC_GEN_PMCON_3)) |= CLEAR_BIT;
        }
    }
}
#endif

    //
    // Get the BMC SELF TEST Results.
    //

    for ( Index = 0; Index < IPMI_SELF_TEST_COMMAND_RETRY_COUNT; Index++ ) {

        DataSize = sizeof (EFI_GET_SELF_TEST_STATUS);
        Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
                    &IpmiInstance->IpmiTransport,
                    EFI_SM_NETFN_APP,
                    BMC_LUN,
                    EFI_APP_GET_SELFTEST_RESULTS,
                    NULL,
                    0,
                   (UINT8*) &BstStatus,
                    &DataSize );
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Get Self test results Index: %x Status %r\n", Index, Status));
        if ( !EFI_ERROR(Status) ) {
            break;
        }
    }

    DEBUG ((EFI_D_LOAD, "Self test result Status: %r\n", Status));

    //
    // If Status indicates a Device error, then the BMC is not responding, so send an error.
    //
    if ( EFI_ERROR (Status) ) {
        IpmiInstance->BmcStatus = EFI_BMC_HARDFAIL;
    } else {

        //
        // Check the self test results.  Cases 55h - 58h are IPMI defined test results.
        // Additional Cases are device specific test results.
        //
        switch ( BstStatus.Status ) {
            case EFI_APP_SELFTEST_NO_ERROR: // 0x55
            case EFI_APP_SELFTEST_NOT_IMPLEMENTED: // 0x56
            case EFI_APP_SELFTEST_RESERVED: // 0xFF
                IpmiInstance->BmcStatus = EFI_BMC_OK;
                break;

            case EFI_APP_SELFTEST_ERROR: // 0x57
                IpmiInstance->BmcStatus = EFI_BMC_SOFTFAIL;
                break;

            default: // 0x58 and Other Device Specific Hardware Error
                IpmiInstance->BmcStatus = EFI_BMC_HARDFAIL;
                break;
        }

        //
        // The Device ID information is only retrieved when the self test has passed or generated a SOFTFAIL.
        // The BMC Status may be overwritten to show the BMC is in Force Update mode.
        // But the BMC Status will always be preserved if a hard fail has occurred since this code won't execute.
        //
        if ( (IpmiInstance->BmcStatus == EFI_BMC_OK) || (IpmiInstance->BmcStatus == EFI_BMC_SOFTFAIL) )
        {
            //
            // Send Get Device ID command
            //
            GetDeviceId (IpmiInstance);
        }
    }

    DEBUG ((EFI_D_LOAD, "BMC Status %x\n", IpmiInstance->BmcStatus));

    //
    // Now install the PPI if the BMC is not in a Hard Fail State
    //
    if ( IpmiInstance->BmcStatus != EFI_BMC_HARDFAIL ) {
        PeiIpmiPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
        PeiIpmiPpiDesc->Guid = &gEfiPeiIpmiTransportPpiGuid;
        PeiIpmiPpiDesc->Ppi = &IpmiInstance->IpmiTransport;

        Status = (*PeiServices)->InstallPpi (
                    PeiServices,
                    PeiIpmiPpiDesc);
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "gEfiPeiIpmiTransportPpiGuid PPI  Status %r\n", Status));
        if (EFI_ERROR(Status)) {
            //
            // Error in installing the PPI. So free the allocated memory.
            //
            FreePool (IpmiInstance);
            FreePool (PeiIpmiPpiDesc);
        }
        return Status;

    } else {
        //
        // SELF test has failed, so free the memory and return EFI_UNSUPPORTED to unload driver from memory.
        //
        FreePool (IpmiInstance);
        FreePool (PeiIpmiPpiDesc);
        return EFI_UNSUPPORTED;
    }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
