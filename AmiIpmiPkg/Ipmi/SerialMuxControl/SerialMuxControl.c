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

/** @file SerialMuxControl.c
    Functions to switch the serial port MUX

**/

#include "Token.h"

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>

#include <Include/IpmiNetFnTransportDefinitions.h>
#include <Include/IpmiNetFnAppDefinitions.h>
#include <Include/IpmiNetFnChassisDefinitions.h>
#include <Protocol/IPMITransportProtocol.h>
#include <Include/ServerMgmtSetupVariable.h>

//
// Macro defines
//
#define MAX_IPMI_CHANNELS       0x10
#define REQUEST_ACCEPTED        0x01
#define REQUEST_REJECTED        0x00
#define SELCECTOR_NONE          0x00 // No Selector is used

#define REQUEST_TO_SYSTEM       0x00
#define FORCE_TO_BMC            0x01
#define FORCE_TO_SYSTEM         0x02

//
// Global variables
//
EFI_IPMI_TRANSPORT      *gIpmiTransport = NULL;
UINT8                   gSerialChannel;

/**
    switch the serial port MUX.

    @param  MuxSetting - MUX Setting

    @return EFI_STATUS Return Status
    @retval EFI_ABORTED IPMI command failure
    @retval EFI_NOT_FOUND Incorrect Port Number

**/

EFI_STATUS
SwitchSerialMux (
  IN EFI_MUX_SETTING    MuxSetting )
{
    EFI_STATUS              Status;
    EFI_SET_MUX_COMMAND     SetMux = {0};
    EFI_MUX_CONFIG          MuxConfig;
    UINT32                  Size;
    UINT8                   RetryCount = 0;

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " SwitchSerialMux() MuxSetting: %x \n", MuxSetting));

    SetMux.ChannelNo = gSerialChannel;
    SetMux.MuxSetting = MuxSetting;

    Size = sizeof (EFI_MUX_CONFIG);
    //
    // Set serial MUX command
    //
    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_TRANSPORT,
                BMC_LUN,
                EFI_TRANSPORT_SET_SERIAL_MUX,
                (UINT8 *) &SetMux,
                sizeof(EFI_SET_MUX_COMMAND),
                (UINT8 *) &MuxConfig,
                (UINT8 *) &Size );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_TRANSPORT_SET_SERIAL_MUX Status: %r CommandStatus: %x \n", Status, MuxConfig.CommandStatus));

    if ( !EFI_ERROR(Status) && (MuxConfig.CommandStatus == REQUEST_REJECTED) ) {

        while ( RetryCount++ < 5 ) {
            //
            // Try five times, if failure on the command
            //
            Size = sizeof (EFI_MUX_CONFIG);
            //
            // Set serial MUX command
            //
            Status = gIpmiTransport->SendIpmiCommand (
                        gIpmiTransport,
                        EFI_SM_NETFN_TRANSPORT,
                        BMC_LUN,
                        EFI_TRANSPORT_SET_SERIAL_MUX,
                        (UINT8 *) &SetMux,
                        sizeof(EFI_SET_MUX_COMMAND),
                        (UINT8 *) &MuxConfig,
                        (UINT8 *) &Size );
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, " RetryCount: %x EFI_TRANSPORT_SET_SERIAL_MUX Status: %r CommandStatus: %x \n", RetryCount, Status, MuxConfig.CommandStatus));
            if ( !EFI_ERROR(Status) && (MuxConfig.CommandStatus == REQUEST_ACCEPTED) ) {
                return Status;
            }
        }
        return EFI_ABORTED;
    }
    return Status;
}

/**
    Switch the MUX Depends on the BIOS MUX Control bits

    @param  Event - Event which caused this handler
    @param  Context - Context passed during Event Handler registration

    @retval EFI_SUCCESS Successful return

**/

EFI_STATUS
EFIAPI
OnBootSharedModeMuxSwitching (
  IN EFI_EVENT        Event,
  IN VOID             *Context )
{
    EFI_STATUS                  Status;
    GET_BOOT_FLAG_RESPONSE      BootFlagsResponse;
    UINT8                       ResponseSize;
    GET_BOOT_OPTIONS_REQUEST    GetRequest;

    //
    // Read Boot options command request
    //
    ResponseSize = sizeof (GET_BOOT_FLAG_RESPONSE);

    GetRequest.ParameterSelector = BootFlags;
    GetRequest.SetSelector = SELCECTOR_NONE;
    GetRequest.BlockSelector = SELCECTOR_NONE;

    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_CHASSIS,
                BMC_LUN,
                EFI_CHASSIS_GET_SYSTEM_BOOT_OPTIONS,
                (UINT8*) &GetRequest,
                sizeof (GET_BOOT_OPTIONS_REQUEST),
                (UINT8*) &BootFlagsResponse,
                &ResponseSize );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_CHASSIS_GET_SYSTEM_BOOT_OPTIONS Status: %r\n", Status));
    if ( EFI_ERROR (Status) ) {
        return Status;
    }
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " BootFlagValid: %x BiosMuxCtrlOverride: %x \n", BootFlagsResponse.Param5.BootFlagValid, BootFlagsResponse.Param5.BiosMuxCtrlOverride));

    //
    // Check for Boot Flag valid bit
    // Based on BiosMuxCtrlOverride bit, Set MUX accordingly.
    //
    if ( BootFlagsResponse.Param5.BootFlagValid ) {
        if ( BootFlagsResponse.Param5.BiosMuxCtrlOverride == REQUEST_TO_SYSTEM ) {
            SwitchSerialMux (ReqMuxToSystem);
        } else if ( BootFlagsResponse.Param5.BiosMuxCtrlOverride == FORCE_TO_BMC ) {
            SwitchSerialMux (ForceMuxToBmc);
        } else if ( BootFlagsResponse.Param5.BiosMuxCtrlOverride == FORCE_TO_SYSTEM ) {
            SwitchSerialMux (ForceMuxToSystem);
        }
    } //if ( BootFlagsResponse.Param5.BootFlagValid )

    return EFI_SUCCESS;
}

/**
    On the Boot to the OS switch MUX to the system.

    @param Event - Event which caused this handler
    @param *Context - Context passed during Event Handler registration

    @retval EFI_SUCCESS Successful return

**/

EFI_STATUS
EFIAPI
OnBootForceMuxToSystem (
  IN EFI_EVENT        Event,
  IN VOID             *Context )
{
    return SwitchSerialMux (ForceMuxToSystem);
}

/**
    Control the serial MUX to System or BMC depending on Channel Access Mode.

    @param VOID

    @retval EFI_SUCCESS Successful return

**/

EFI_STATUS
EFIAPI
SerialMuxSwitching (
  VOID )
{

    EFI_STATUS                              Status;
    EFI_GET_CHANNEL_ACCESS_COMMAND          CommandData = {0};
    UINT32                                  Size;
    EFI_GET_CHANNEL_ACCESS_RESPONSE         ResponseData = {0};
    EFI_EVENT                               ReadyToBootEvent;

    Size = sizeof (EFI_GET_CHANNEL_ACCESS_RESPONSE);
    CommandData.ChannelNo = gSerialChannel;
    CommandData.MemoryType = NonVolatile;
    //
    // Get Channel Access command
    //
    Status = gIpmiTransport->SendIpmiCommand (
                gIpmiTransport,
                EFI_SM_NETFN_APP,
                BMC_LUN,
                EFI_APP_GET_CHANNEL_ACCESS,
                (UINT8 *) &CommandData,
                sizeof(EFI_GET_CHANNEL_ACCESS_COMMAND),
                (UINT8 *) &ResponseData,
                (UINT8 *) &Size );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_APP_GET_CHANNEL_ACCESS Status: %r AccessMode: %x \n", Status, ResponseData.AccessMode));
    if ( EFI_ERROR (Status) ) {
        return EFI_DEVICE_ERROR;
    }

    switch ( ResponseData.AccessMode ) {
        //
        // At power-on by default MUX is Set to System
        //
        case ChannelAccesDisabled:
            break;

        case ChannelAccesPreBootOnly:
            //
            // Switch MUX for system use
            //
            SwitchSerialMux (ReqMuxToSystem);

            //
            // Switch the Serial MUX to the system before Boot to OS.
            //
            Status = EfiCreateEventReadyToBootEx (
                        TPL_CALLBACK,
                        (EFI_EVENT_NOTIFY)OnBootForceMuxToSystem,
                        NULL,
                        &ReadyToBootEvent );
            break;

        case ChannelAccesAlwaysAvailable:
            //
            //TODO: In order to avoid confusion with run-time software, BIOS will
            // typically hide or disable serial port when the OS load process starts.
            //
            break;

        case ChannelAccesShared:
            //
            // Switch MUX for system use
            //
            SwitchSerialMux (ReqMuxToSystem);

            //
            // Switch the Serial MUX depends on the BootFlag before OS Boot.
            //
            Status = EfiCreateEventReadyToBootEx (
                        TPL_CALLBACK,
                        (EFI_EVENT_NOTIFY)OnBootSharedModeMuxSwitching,
                        NULL,
                        &ReadyToBootEvent );
            break;
        default:
            break;
    }

    return EFI_SUCCESS;
}

/**
    Get the channel Info

    @param VOID

    @retval EFI_SUCCESS Successful return

**/

EFI_STATUS
EFIAPI
GetChannelInfo (
  VOID )
{

    EFI_STATUS                  Status;
    EFI_CHANNEL_INFO            ChannelInfo = {0};
    UINT8                       ChannelNumber = 0;
    UINT32                      Size;

    for ( ChannelNumber = 0; ChannelNumber < MAX_IPMI_CHANNELS; ChannelNumber++ ) {
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Channel Number: %x \n", ChannelNumber));
        //
        // According to Get channel info command description, 0x0E is used to get
        // information about the channel this command is being executed from.
        // So do not send command for 0x0E channel number.
        //
        if (ChannelNumber == 0xE) {
            continue;
        }
        Size = sizeof (EFI_CHANNEL_INFO);

        //
        // Get Channel Info command
        //
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_APP,
                    BMC_LUN,
                    EFI_APP_GET_CHANNEL_INFO,
                    &ChannelNumber,
                    sizeof(ChannelNumber),
                    (UINT8 *) &ChannelInfo,
                    (UINT8 *) &Size );
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, " EFI_APP_GET_CHANNEL_INFO Status: %r ChannelMediumType: %x \n", Status, ChannelInfo.ChannelMediumType));
        if ( EFI_ERROR (Status) ) {
            continue;
        }
        //
        // Check for Serial channel number
        //
        if( ChannelInfo.ChannelMediumType == EfiSmRs_232 ){
            gSerialChannel = ChannelInfo.ChannelNo;
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, " Serial Channel Number: %x \n", gSerialChannel));
            break;
        }
    } //for loop
    return EFI_SUCCESS;
}

/**
    Get Channel information and control the MUX based on the
    Channel Access Mode,

    @param ImageHandle - Handle of this driver image
    @param SystemTable - Table containing standard EFI services

    @retval EFI_SUCCESS Protocol successfully started and installed
    @retval EFI_UNSUPPORTED Protocol can't be started

**/

EFI_STATUS
SerialMuxControlEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable )
{
    EFI_STATUS                      Status;
    SERVER_MGMT_CONFIGURATION_DATA  ServerMgmtConfiguration;
    UINTN                           Size;

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " SerialMuxControlEntryPoint entered... \n"));

    Size = sizeof (SERVER_MGMT_CONFIGURATION_DATA);
    Status = gRT->GetVariable (
                L"ServerSetup",
                &gEfiServerMgmtSetupVariableGuid,
                NULL,
                &Size,
                &ServerMgmtConfiguration);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiServerMgmtSetupVariableGuid Status: %r \n", Status));
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " ServerMgmtConfiguration.SerialMux: %X \n", ServerMgmtConfiguration.SerialMux));

    if (EFI_ERROR(Status) || (!ServerMgmtConfiguration.SerialMux)) {
        return EFI_UNSUPPORTED;
    }

    Status = gBS->LocateProtocol (
                &gEfiDxeIpmiTransportProtocolGuid,
                NULL,
                (VOID **)&gIpmiTransport );
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " gEfiDxeIpmiTransportProtocolGuid Status: %r \n", Status));
    if ( EFI_ERROR (Status) ) {
        return Status;
    }

    //
    // Get Channel information
    //
    GetChannelInfo();

    //
    // Depends on the Channel Access Mode, control the MUX
    //
    SerialMuxSwitching ();

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, " SerialMuxControlEntryPoint Exiting... \n"));

    return EFI_SUCCESS;
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
