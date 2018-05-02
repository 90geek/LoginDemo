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

/** @file SmmIpmiBmcInitialize.c
    SMM IPMI Transport Driver.

**/

//----------------------------------------------------------------------

#include "DxeSmmIpmiBmc.h"
#include <Library/SmmServicesTableLib.h>

//----------------------------------------------------------------------

//
// Global Variable
//
EFI_IPMI_BMC_INSTANCE_DATA  *gSmmIpmiInstance = NULL;

#if IPMI_SEPARATE_DXE_SMM_INTERFACES == 0

/**
    Software SMI callback which proxies the DXE calls to SMM IPMI protocol

    @param DispatchHandle The unique handle assigned to this handler by
                           SmiHandlerRegister().
    @param RegisterContext Points to an optional handler context which was
                          specified when the handler was registered.
    @param CommBuffer A pointer to a collection of data in memory that will
                      be conveyed from a non-SMM environment into an SMM environment.
    @param CommBufferSize The size of the CommBuffer.

    @retval EFI_STATUS Return Status

**/

EFI_STATUS
EFIAPI
SmmIpmiBmcHandler (
  IN     EFI_HANDLE         DispatchHandle,
  IN     CONST VOID         *RegisterContext,
  IN OUT VOID               *CommBuffer,
  IN OUT UINTN              *CommBufferSize )
{
    EFI_STATUS                                      Status = EFI_SUCCESS;
    SMM_IPMI_BMC_SEND_COMMAND_COMMUNICATE_DATA      *SmmIpmiBmcData;
    SMM_IPMI_BMC_GET_STATUS_COMMUNICATE_DATA        *SmmIpmiGetBmcStatusData;

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmmIpmiBmcHandler entered  status %r gSmmIpmiInstance: %x \n", Status, gSmmIpmiInstance));

    ASSERT (CommBuffer != NULL);

    SmmIpmiBmcData = (SMM_IPMI_BMC_SEND_COMMAND_COMMUNICATE_DATA *)CommBuffer;

    switch (SmmIpmiBmcData->FunctionNumber) {

        case SMM_IPMI_BMC_FUNCTION_SEND_COMMAND:
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SendIpmiCommand function is called.............. \n"));
            Status = gSmmIpmiInstance->IpmiTransport.SendIpmiCommand (
                        &gSmmIpmiInstance->IpmiTransport,
                        (UINT8)SmmIpmiBmcData->NetFunction,
                        (UINT8)SmmIpmiBmcData->Lun,
                        (UINT8)SmmIpmiBmcData->Command,
                        (UINT8*)SmmIpmiBmcData->CommandData,
                        (UINT8)SmmIpmiBmcData->CommandDataSize,
                        (UINT8*)SmmIpmiBmcData->ResponseData,
                        (UINT8*)SmmIpmiBmcData->ResponseDataSize );
            break;

        case SMM_IPMI_BMC_FUNCTION_GET_BMC_STATUS:
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, "GetBmcStatus function is called.............. \n"));
            SmmIpmiGetBmcStatusData = (SMM_IPMI_BMC_GET_STATUS_COMMUNICATE_DATA *)CommBuffer;
            Status = gSmmIpmiInstance->IpmiTransport.GetBmcStatus (
                        &gSmmIpmiInstance->IpmiTransport,
                        (EFI_BMC_STATUS*)SmmIpmiGetBmcStatusData->BmcStatus,
                        (EFI_SM_COM_ADDRESS*)SmmIpmiGetBmcStatusData->ComAddress );
            break;

        default:
            ASSERT (FALSE);
            Status = EFI_UNSUPPORTED;
    }

    SmmIpmiBmcData->CommandCompletionCode = gSmmIpmiInstance->IpmiTransport.CommandCompletionCode;
    SmmIpmiBmcData->ReturnStatus = Status;

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmmIpmiBmcHandler Exiting Function  Status %r\n", Status));

    return EFI_SUCCESS;
}

#endif //IPMI_SEPARATE_DXE_SMM_INTERFACES == 0

/**
    Setup and initialize the BMC for the SMM phase.
    1. In order to verify the BMC is functioning as expected, the BMC Self-test
    is performed. Updates the BMC status in Private data
    2. Installs SMM IPMI transport protocol.
    3. Registers Software SMI callback to proxy the DXE calls to SMM IPMI protocol.
    This applicable only when both DXE and SMM uses same KCS interface.
    4. Notify the DxeIpmiBmc driver that SmmIpmiBmcTransport protocol is ready.

        
    @param ImageHandle Handle of this driver image
    @param SystemTable Table containing standard EFI services

    @retval EFI_SUCCESS Successful driver initialization

**/

EFI_STATUS
InitializeIpmiSmmPhysicalLayer (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
  )
{
    EFI_STATUS                            Status = EFI_SUCCESS;
    EFI_HANDLE                            NewHandle = NULL;
    UINT8                                 DataSize;
    UINT8                                 Index;
    EFI_GET_SELF_TEST_STATUS              BstStatus;

    //
    // Allocate memory for IPMI Instance
    //
    gSmmIpmiInstance = AllocateRuntimeZeroPool (sizeof (EFI_IPMI_BMC_INSTANCE_DATA));
    if (gSmmIpmiInstance == NULL) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Failed to allocate memory for gSmmIpmiInstance! \n"));
        return EFI_OUT_OF_RESOURCES;
    }
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "gSmmIpmiInstance: %x \n", gSmmIpmiInstance));

    //
    // Initialize IPMI Instance Data
    //
    #if IPMI_SYSTEM_INTERFACE == KCS_INTERFACE
        gSmmIpmiInstance->Interface.KCS.DataPort = IPMI_SMM_KCS_DATA_PORT;          // KCS Data Port
        gSmmIpmiInstance->Interface.KCS.CommandPort = IPMI_SMM_KCS_COMMAND_PORT;    // KCS Command Port
        gSmmIpmiInstance->Interface.KCS.KcsRetryCounter = IPMI_SMM_KCS_COMMAND_PORT_READ_RETRY_COUNTER;
        gSmmIpmiInstance->IpmiTransport.SendIpmiCommand = EfiIpmiSendCommand;       // KCS SendCommand
    #else
        gSmmIpmiInstance->Interface.BT.CtrlPort = IPMI_BT_CTRL_PORT;     // BT Control Port
        gSmmIpmiInstance->Interface.BT.ComBuffer = IPMI_BT_BUFFER_PORT;  // BT Buffer Port
        gSmmIpmiInstance->Interface.BT.IntMaskPort = IPMI_BT_INTERRUPT_MASK_PORT; // BT IntMask Port
        gSmmIpmiInstance->Interface.BT.BtDelay = (UINT16)BT_DELAY;       // BT Delay
        gSmmIpmiInstance->IpmiTransport.SendIpmiCommand = EfiBtIpmiSendCommand;   // BT SendCommand
    #endif

    gSmmIpmiInstance->Signature     = SM_IPMI_BMC_SIGNATURE;
    gSmmIpmiInstance->SlaveAddress  = IPMI_BMC_SLAVE_ADDRESS;
    gSmmIpmiInstance->BmcStatus     = EFI_BMC_OK;
    gSmmIpmiInstance->IpmiTransport.GetBmcStatus = EfiIpmiBmcStatus;

    //
    // Get the BMC SELF TEST Results.
    //

    for ( Index = 0; Index < IPMI_SELF_TEST_COMMAND_RETRY_COUNT; Index++ )  {
        DataSize = sizeof (EFI_GET_SELF_TEST_STATUS);
        Status = gSmmIpmiInstance->IpmiTransport.SendIpmiCommand (
                    &gSmmIpmiInstance->IpmiTransport,
                    EFI_SM_NETFN_APP,
                    BMC_LUN,
                    EFI_APP_GET_SELFTEST_RESULTS,
                    NULL,
                    0,
                    (UINT8*)&BstStatus ,
                    &DataSize );
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SMM: Get Self test results status %r\n", Status));
        if ( Status != EFI_NOT_READY ) {
            break;
        }
    }

    //
    // If Status indicates a Device error, then the BMC is not responding, so send an error.
    //
    if ( EFI_ERROR (Status) ) {
        gSmmIpmiInstance->BmcStatus = EFI_BMC_HARDFAIL;
    } else {

        //
        // Check the self test results.  Cases 55h - 58h are IPMI defined test results.
        // Additional Cases are device specific test results.
        //
        switch ( BstStatus.Status ) {
            case EFI_APP_SELFTEST_NO_ERROR: // 0x55
            case EFI_APP_SELFTEST_NOT_IMPLEMENTED: // 0x56
            case EFI_APP_SELFTEST_RESERVED: // 0xFF
                gSmmIpmiInstance->BmcStatus = EFI_BMC_OK;
                break;

            case EFI_APP_SELFTEST_ERROR: // 0x57
                gSmmIpmiInstance->BmcStatus = EFI_BMC_SOFTFAIL;
                break;

            default: // 0x58 and Other Device Specific Hardware Error
                gSmmIpmiInstance->BmcStatus = EFI_BMC_HARDFAIL;
                break;
        }
    }
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SMM BMC status %x\n", gSmmIpmiInstance->BmcStatus));

    //
    // Now install the Protocol if the BMC is not in a Hard Fail State
    //
    if ( gSmmIpmiInstance->BmcStatus != EFI_BMC_HARDFAIL ) {
        NewHandle = NULL;
        Status = gSmst->SmmInstallProtocolInterface (
                    &NewHandle,
                    &gEfiSmmIpmiTransportProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gSmmIpmiInstance->IpmiTransport );
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SMM gEfiSmmIpmiTransportProtocolGuid protocol status %r\n", Status));
        if (EFI_ERROR (Status)) {

            //
            // Error in installing the protocol. So free the allocated memory.
            //
            FreePool (gSmmIpmiInstance);
            return Status;
        }

#if IPMI_SEPARATE_DXE_SMM_INTERFACES == 0

        //
        // Same Interface used for both SMM and DXE phases so proxy the DXE calls to SMM
        //
        if ( !EFI_ERROR(Status) ) {

            //
            // Register SMM IPMI BMC SMI handler
            //
            NewHandle = NULL;
            Status = gSmst->SmiHandlerRegister (
                        SmmIpmiBmcHandler,
                        &gEfiSmmIpmiTransportProtocolGuid,
                        &NewHandle);
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, "gSmst->SmiHandlerRegister  status %r\n", Status));
            ASSERT_EFI_ERROR (Status);

            if ( !EFI_ERROR(Status) ) {

                //
                // Notify the DxeIpmiBmc driver that SmmIpmiBmcTransport protocol is ready
                //
                NewHandle = NULL;
                Status = gBS->InstallProtocolInterface (
                            &NewHandle,
                            &gEfiSmmIpmiTransportProtocolGuid,
                            EFI_NATIVE_INTERFACE,
                            NULL );
                SERVER_IPMI_DEBUG ((EFI_D_LOAD, "gBS->Install: gEfiSmmIpmiTransportProtocolGuid protocol  status %r\n", Status));
                ASSERT_EFI_ERROR (Status);
            }
        }
#endif //IPMI_SEPARATE_DXE_SMM_INTERFACES == 0

        return EFI_SUCCESS;

    } else {

        //
        // SELF test has failed, so free the memory and return EFI_UNSUPPORTED to unload driver from memory.
        //
        gSmst->SmmFreePool (gSmmIpmiInstance);
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
