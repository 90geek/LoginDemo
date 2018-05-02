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

/** @file HddSMART.c
    HDD SMART Support

**/

//---------------------------------------------------------------------------

#include "HddSMART.h"
#include <Setup.h>
#include <SmartfailureFunctionList.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiString.h>

//---------------------------------------------------------------------------

EFI_GUID gSetupGuid = SETUP_GUID;

EFI_HII_HANDLE               HiiPostHandle;
AMI_POST_MANAGER_PROTOCOL    *pAmiPostMgr;
SETUP_DATA                   gSetupData;

//
// Generic function in this file that will call function specified via elink
//
VOID 
ReportSmartFailure (
    BOOLEAN     Mode, 
    VOID        *Interface
);

//
// ELINK defined function that will be called.  Function name 'OemReportSmartFailureFunction'
//   is #defined via the makefile /D to be the ELINK function name
//
VOID 
OemReportSmartFailureFunction (
    BOOLEAN     Mode, 
    VOID        *Interface
);

/**
    This function is the entry point for IDE SMART Driver.

    @param  EFI_HANDLE          ImageHandle     Image handle.
    @param  EFI_SYSTEM_TABLE    *SystemTable    Pointer to the EFI system table.

    @retval EFI_STATUS
    @retval EFI_SUCCESS         When everything is going on fine!

    @note   Entry Points are used to locate or install protocol interfaces and
            notification events.

**/

EFI_STATUS 
HddSmartEntryPoint (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_HANDLE    Handle = NULL;
    EFI_STATUS    Status;

    InitAmiLib( ImageHandle, SystemTable );

    Status = LoadStrings( ImageHandle, &HiiPostHandle );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(AMI_HDD_SMART_INIT_PROTOCOL),
                                (VOID**)&gHddSmartInitProtocol );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    gHddSmartInitProtocol->InstallSmartInterface   = InstallSmartInterface;
    gHddSmartInitProtocol->UnInstallSmartInterface = UnInstallSmartInterface;
    gHddSmartInitProtocol->InitSmartSupport        = InitSmartSupport;
    gHddSmartInitProtocol->SmartDiagonasticFlag    = FALSE;
    #if SMART_DIAGNOSTICS_SUPPORT
    gHddSmartInitProtocol->SmartDiagonasticFlag = TRUE;
    #endif

    Status = pBS->InstallProtocolInterface(
                                &Handle,
                                &gAmiHddSmartInitProtocolGuid,
                                EFI_NATIVE_INTERFACE,
                                gHddSmartInitProtocol
                                );
    
    ASSERT_EFI_ERROR( Status );

    return Status;
}

/**
    Initialize Smart functionality

        
    @param BusInterface 
    @param ModeFlag 

    @retval  EFI_STATUS

**/

EFI_STATUS 
InitSmartSupport (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
)
{
    UINT8                   bData;
    EFI_STATUS              Status;
    IDENTIFY_DATA           IdentifyData;
    AMI_IDE_BUS_PROTOCOL    *IdeBusInterface;
    SATA_DEVICE_INTERFACE   *SataDevInterface;
    DEVICE_TYPE             DeviceType;
    COMMAND_STRUCTURE       CommandStructure;
    UINTN                   SetupDataSize = sizeof(SETUP_DATA);

    IdeBusInterface  = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ) {
        IdentifyData = IdeBusInterface->IdeDevice.IdentifyData;
        DeviceType   = IdeBusInterface->IdeDevice.DeviceType;
    } else {
        IdentifyData = SataDevInterface->IdentifyData;
        DeviceType   = SataDevInterface->DeviceType;
    }

    //
    // Check for ATA device
    //
    if  ( DeviceType == ATA ) {
        //
        // Check if SMART is supported, if no exit
        //
        if ( IdentifyData.Command_Set_Supported_82 & 0x1 ) {
            //
            // Whether to Enable or Disable SMART Support
            //
            bData = ENABLE_SMART == 1 ? SMART_ENABLE_CMD : SMART_DISABLE_CMD;

            //
            // Check if current SMART status is what is required
            //
            Status = EFI_SUCCESS;

            if ( !((IdentifyData.Command_Set_Enabled_85 & 0x1) == ENABLE_SMART)) {
                ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
                CommandStructure.Features = bData;
                CommandStructure.LBAMid   = 0x4F;
                CommandStructure.LBAHigh  = 0xC2;
                CommandStructure.Command  = SMART_COMMAND;

                Status = CommonNonDataHook( BusInterface,
                                            CommandStructure,
                                            ModeFlag );

                if ( EFI_ERROR( Status )) {
                    return Status;
                }
            }

            //
            // Enable Autosave feature
            //
            if ((Status == EFI_SUCCESS) && (bData == SMART_ENABLE_CMD)) {
                ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
                CommandStructure.Features    = SMART_AUTOSAVE;
                CommandStructure.SectorCount = 0xF1;
                CommandStructure.LBAMid      = 0x4F;
                CommandStructure.LBAHigh     = 0xC2;
                CommandStructure.Command     = SMART_COMMAND;

                Status = CommonNonDataHook( BusInterface,
                                            CommandStructure,
                                            ModeFlag );

                if ( EFI_ERROR( Status )) {
                    return Status;
                }

                //
                // Get SMART Self test setup option
                //
                Status = pRS->GetVariable(L"Setup", &gSetupGuid, NULL,
                                    &SetupDataSize, &gSetupData);

                if (EFI_ERROR(Status)) {
                    //
                    // If Setup Variable is not found, set Default values
                    //
                    gSetupData.SmartSelfTest = DEFAULT_SMART_SELFTEST;
                }

                if (gSetupData.SmartSelfTest) {

                    //
                    // If SMART threshold exceeded, report it to the user.
                    //
                    Status = SmartReturnStatusWrapper( BusInterface, ModeFlag );

                    if (EFI_ERROR(Status)) {
                        ERROR_CODE( DXE_IDE_SMART_ERROR, EFI_ERROR_MAJOR );
                        ReportSmartFailure(ModeFlag, BusInterface);
                    }
                }
            }
        }
    }
    return EFI_SUCCESS;
}

/**
    Return SMART Status

        
    @param BusInterface 
    @param ModeFlag 

    @retval EFI_STATUS

    @note  Returns EFI_SUCCESS if threshold is not exceeded.

**/

EFI_STATUS 
SmartReturnStatusWrapper (
    IN VOID         *BusInterface,
    IN BOOLEAN      ModeFlag
)
{
    UINT8                   bData;
    UINT16                  wData = THRESHOLD_NOT_EXCEEDED;
    EFI_STATUS              Status;
    COMMAND_STRUCTURE       CommandStructure;
    AMI_IDE_BUS_PROTOCOL    *IdeBusInterface;
    SATA_DEVICE_INTERFACE   *SataDevInterface;
    EFI_PCI_IO_PROTOCOL     *PciIo = NULL;

    IdeBusInterface  = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    //
    // Read the SMART return Status
    //
    ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Features = SMART_RETURN_STATUS;
    CommandStructure.LBAMid   = 0x4F;
    CommandStructure.LBAHigh  = 0xC2;
    CommandStructure.Command  = SMART_COMMAND;

    Status = CommonNonDataHook( BusInterface, CommandStructure, ModeFlag );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    if ( ModeFlag == FALSE ) {
        if ( !EFI_ERROR( Status )) {
            PciIo = IdeBusInterface->PciIO;

            PciIo->Io.Read(
                IdeBusInterface->PciIO,
                EfiPciIoWidthFifoUint8,
                EFI_PCI_IO_PASS_THROUGH_BAR,
                IdeBusInterface->IdeDevice.Regs.CommandBlock.
                LBAHighReg,
                1,
                &bData
                );

            //
            // Get the LBA Mid/High register contends.
            //
            wData = bData << 8;
            PciIo->Io.Read(
                IdeBusInterface->PciIO,
                EfiPciIoWidthFifoUint8,
                EFI_PCI_IO_PASS_THROUGH_BAR,
                IdeBusInterface->IdeDevice.Regs.CommandBlock.
                LBAMidReg,
                1,
                &bData
                );
            wData |= bData;
        }
    } else {
        volatile AHCI_RECEIVED_FIS *FISReceiveAddress;
        FISReceiveAddress = (AHCI_RECEIVED_FIS*)SataDevInterface->PortFISBaseAddr;

        //
        // Get the pointer to RFIS
        //
        if ( !EFI_ERROR( Status ) && (FISReceiveAddress->Ahci_Rfis[0] == FIS_REGISTER_D2H))
            wData = (FISReceiveAddress->Ahci_Rfis[6] << 8) + FISReceiveAddress->Ahci_Rfis[5];
    }

    if ( wData == THRESHOLD_NOT_EXCEEDED ) {
        Status = EFI_SUCCESS;
    } else {
        Status = EFI_DEVICE_ERROR;
    }

    return Status;
}

/**
    Default function to report SMART failures to the POST screen

    @param  BOOLEAN Mode - TRUE - Device is in IDE mode
    @param  FALSE - Device is in AHCI mode
    @param  VOID *Interface - Interface.  Should be cast into SATA_DEVICE_INTERFACE
        or AMI_IDE_BUS_PROTOCOL depending on Mode parameter

    @retval VOID
    @retval VOID

**/

VOID 
SmartErrorThresholdExceeded (
    BOOLEAN     ModeFlag, 
    VOID        *Interface
)
{
    EFI_STATUS      Status;
    UINTN           StringSize = 0;
    CHAR16          *StrBuffer = NULL;
    CHAR16          *Str1 = NULL;
    CHAR16          *Str2 = NULL;
    CHAR16          *DeviceName = NULL;
    UINT8           ChannelorPort;
    UINT8           DeviceorPMPort;

    STRING_REF  Token;

    EFI_INPUT_KEY   Key;

    //
    // Get the Port/Channel information from the interface
    //
    if (ModeFlag) {
        //
        // Sata Mode
        //
        DeviceName = ((SATA_DEVICE_INTERFACE*)Interface)->UDeviceName->UnicodeString;
        ChannelorPort = ((SATA_DEVICE_INTERFACE*)Interface)->PortNumber;
        DeviceorPMPort = ((SATA_DEVICE_INTERFACE*)Interface)->PMPortNumber;
    } else {
        //
        // IDE Mode
        //
        DeviceName = ((AMI_IDE_BUS_PROTOCOL*)Interface)->IdeDevice.UDeviceName->UnicodeString;
        ChannelorPort = ((AMI_IDE_BUS_PROTOCOL*)Interface)->IdeDevice.Channel;
        DeviceorPMPort = ((AMI_IDE_BUS_PROTOCOL*)Interface)->IdeDevice.Device;
    }

  
    //
    // Locate the AMI Post Manger protocol for displaying information on the post screen
    //
    Status = pBS->LocateProtocol(&gAmiPostManagerProtocolGuid,
                                 NULL,
                                 (VOID**)&pAmiPostMgr );

    //
    // Check if we could locate the AMI post manager
    //
    if (!EFI_ERROR(Status) && pST->ConOut != NULL) {
        //
        // Depending on the mode, get different strings to identify the port the failing
        //  device is connected to
        //
        if (ModeFlag) {
            // Sata Mode

            //
            // Print the SATA port that the device is connected
            //  so get the "Port" string
            //
            Str2 = HiiGetString(HiiPostHandle, STRING_TOKEN(STR_SMART_PORT));

            //
            // allocate enough space to print the "port %d" string 
            //
            Status = pBS->AllocatePool(EfiBootServicesData,
                                       sizeof(CHAR16)*(Wcslen(Str2)+4),
                                       (VOID**)&Str1);
            if ( EFI_ERROR( Status )) {
                return;
            }

            //
            // Create the "Port <0|1|2|3|4|5>" string in Str1
            //
            Swprintf(Str1, L"%s %01d", Str2, ChannelorPort);

            //
            // Fill string 2 with a null
            //
            Str2[0] = L'\0';
        } else {
            // IDE Mode

            //
            // Determine if we need to get the "Primary" or "Secondary" string
            //
            if (ChannelorPort == PRIMARY_CHANNEL) Token = STRING_TOKEN(STR_PRIMARY);  
            else Token = STRING_TOKEN(STR_SECONDARY);  

            //
            // Get the string out of the Hiidatabase into Str1
            //
            Str1 = HiiGetString(HiiPostHandle, Token);

            //
            // Determine if we need to get the "Master" or "Slave" string
            //
            if (DeviceorPMPort == MASTER_DRIVE) Token = STRING_TOKEN(STR_MASTER);  
            else Token = STRING_TOKEN(STR_SLAVE);  

            //
            // Get the string out of the Hiidatabase into Str1
            //
            Str2 = HiiGetString(HiiPostHandle, Token);

        }

        //
        // Determine the size of all the components we are trying to print
        //  and additional spaces for the newline, Carriage return, the two spaces
        //  the colon and the null termination
        //
        StringSize = Wcslen(Str1) + Wcslen(Str2) + Wcslen(DeviceName) + 7;

        Status = pBS->AllocatePool(EfiBootServicesData,
                                   StringSize*sizeof(CHAR16),
                                   (VOID**)&StrBuffer);
        if ( EFI_ERROR( Status )) {
            return;
        }

        //
        // Build the string for IDE or SATA: 
        // Ide string looks like - "<Primary|Secondary> <Master|Slave> : <Device Name String>"
        // sata string looks like - "Port <0|1|2|3|4|5> : <Device Name String>"
        //
        Swprintf(StrBuffer, L"\n\r%s %s: %s", Str1, Str2, DeviceName);

        //
        // free the helper buffers
        //
        pBS->FreePool(Str1);
        pBS->FreePool(Str2);
        Str2 = NULL;

        //
        // Display the post message
        //
        pAmiPostMgr->SwitchToPostScreen();
        pAmiPostMgr->DisplayPostMessage(StrBuffer);

        //
        // and free the buffer that was used
        //
        pBS->FreePool(StrBuffer);    
        StrBuffer = NULL;

        //
        // get the smart failure string from the HiiDatabase
        //
        
	Str1 = HiiGetString(HiiPostHandle, STRING_TOKEN(STR_SMART_FAILURE));

        //
        // And display it below the drive information strings, then free the space allocated
        //
        pAmiPostMgr->DisplayPostMessage(Str1);
        pBS->FreePool(Str1);
        Str1 = NULL;

        //
        // If keyboard input is available, pause for user input
        //
        if (pST->ConIn != NULL) {
            //
            // Get the pause string from the HiiDatabase
            //
	    	Str1 = HiiGetString(HiiPostHandle, STRING_TOKEN(STR_SMART_FAILURE_PROMPT));
            //
            // Display the pause message on the screen
            //
            pAmiPostMgr->DisplayPostMessage( Str1 );

            //
            // Free the space allocated by GetHiiString
            //
            pBS->FreePool(Str1);

            //
            // And wait for the user to press the input key
            //
            Key.UnicodeChar = 0;
            do {
                //
                // Pause for 1/2 a second between key press reads
                //
                pBS->Stall(50000);

                pST->ConIn->ReadKeyStroke( pST->ConIn, &Key );
            } while ( Key.ScanCode != WAIT_FOR_ERROR_KEY );
        }//if(pST->ConIn != NULL)
    }//if(!EFI_ERROR(Status) && pST->ConOut != NULL)
}

/**
    Installs SmartInterface Protocol

    @param  BusInterface 
    @param  ModeFlag 

    @retval EFI_STATUS

    @note   Already SMART support capability has been established.

**/

EFI_STATUS
InstallSmartInterface (
    IN VOID         *BusInterface,
    IN BOOLEAN      ModeFlag
)
{
    EFI_STATUS              Status = EFI_UNSUPPORTED;
    AMI_SMART_INTERFACE     *SmartInterface;
    UINT8                   *Buffer;
    IDENTIFY_DATA           IdentifyData;
    EFI_HANDLE              IdeDeviceHandle;
    AMI_IDE_BUS_PROTOCOL    *IdeBusInterface;
    SATA_DEVICE_INTERFACE   *SataDevInterface;
    DEVICE_TYPE             DeviceType;
    COMMAND_STRUCTURE       CommandStructure;

    IdeBusInterface  = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ) {
        IdentifyData    = IdeBusInterface->IdeDevice.IdentifyData;
        DeviceType      = IdeBusInterface->IdeDevice.DeviceType;
        IdeDeviceHandle = IdeBusInterface->IdeDeviceHandle;
    } else {
        IdentifyData    = SataDevInterface->IdentifyData;
        DeviceType      = SataDevInterface->DeviceType;
        IdeDeviceHandle = SataDevInterface->IdeDeviceHandle;
    }

    //
    // Check for HDD and SMART support
    //
    if  ((DeviceType == ATA)        // It is HDD
         && (IdentifyData.Command_Set_Supported_82 & 0x1)   // SMART supported
         && (IdentifyData.Command_Set_Supported_84 & 0x2))  // SMART Enabled

    {
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    512,
                                    (VOID**)&Buffer );

        if ( EFI_ERROR( Status )) {
            return EFI_OUT_OF_RESOURCES;
        }

        ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
        CommandStructure.Buffer    = Buffer;
        CommandStructure.ByteCount = 512;
        CommandStructure.Features  = SMART_READ_DATA;
        CommandStructure.LBAMid    = 0x4F;
        CommandStructure.LBAHigh   = 0xC2;
        CommandStructure.Command   = SMART_COMMAND;

        if ( ModeFlag == FALSE ) {
            CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;
            Status = IdeBusInterface->AtaPioDataIn(
                            IdeBusInterface,
                            CommandStructure.Buffer,
                            CommandStructure.ByteCount,
                            CommandStructure.Features,
                            (UINT8)CommandStructure.SectorCount,
                            CommandStructure.LBALow,
                            CommandStructure.LBAMid,
                            CommandStructure.LBAHigh,
                            CommandStructure.Device,
                            CommandStructure.Command,
                            FALSE);
        } else {
            Status = SataDevInterface->AhciBusInterface->ExecutePioDataCommand(
                SataDevInterface,
                &CommandStructure,
                FALSE );
        }

        if ( EFI_ERROR( Status )) {
            pBS->FreePool( Buffer );
            return Status;
        }

        //
        // Install the Interface
        //
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    sizeof(AMI_SMART_INTERFACE),
                                    (VOID**)&SmartInterface );

        if ( EFI_ERROR( Status )) {
            pBS->FreePool( Buffer );
            return Status;
        }

        SmartInterface->SmartSelfTest       = SmartSelfTest;
        SmartInterface->SmartSelfTestStatus = SmartSelfTestStatus;
        SmartInterface->SmartReturnStatus   = SmartReturnStatus;
        SmartInterface->SendSmartCommand    = SendSmartCommand;
        SmartInterface->SmartReadData       = SmartReadData;
        SmartInterface->SmartWriteData      = SmartWriteData;
        SmartInterface->SmartAbortSelfTest  = SmartAbortSelfTest;
        SmartInterface->SmartGetSmartData   = SmartGetSmartData;
        SmartInterface->ShortPollingTime    = Buffer[372];
        if(Buffer[373] == 0xFF)
            SmartInterface->ExtPollingTime  = (UINT16)(Buffer[376]<<8 | Buffer[375]);
        else
            SmartInterface->ExtPollingTime  = (UINT16)Buffer[373];

        if ( ModeFlag == FALSE ) {
            IdeBusInterface->SmartInterface = (AMI_HDD_SMART_PROTOCOL*)SmartInterface;
            SmartInterface->BusInterface    = IdeBusInterface;
        } else {
            SataDevInterface->SmartInterface = (AMI_HDD_SMART_PROTOCOL*)SmartInterface;
            SmartInterface->BusInterface     = SataDevInterface;
        }

        //
        // Set ModeFlag to FALSE if IdeBus else TRUE for Ahci Bus.
        //
        SmartInterface->ModeFlag = ModeFlag;  // Ide Bus

        Status = pBS->InstallMultipleProtocolInterfaces(&IdeDeviceHandle,
                                                        &gAmiHddSmartProtocolGuid,
                                                        SmartInterface,
                                                        NULL );

        pBS->FreePool( Buffer );
    }
    return Status;
}

/**
    Uninstall SmartInterface Protocol

    @param  BusInterface 
    @param  ModeFlag 

    @retval EFI_STATUS

**/

EFI_STATUS
UnInstallSmartInterface (
    IN VOID         *BusInterface,
    IN BOOLEAN      ModeFlag
)
{
    EFI_STATUS              Status;
    AMI_SMART_INTERFACE     *SmartInterface;
    AMI_IDE_BUS_PROTOCOL    *IdeBusInterface;
    SATA_DEVICE_INTERFACE   *SataDevInterface;
    EFI_HANDLE              IdeDeviceHandle;

    IdeBusInterface  = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ) {
        SmartInterface  = (AMI_SMART_INTERFACE*)IdeBusInterface->SmartInterface;
        IdeDeviceHandle = IdeBusInterface->IdeDeviceHandle;
    } else {
        SmartInterface  = (AMI_SMART_INTERFACE*)SataDevInterface->SmartInterface;
        IdeDeviceHandle = SataDevInterface->IdeDeviceHandle;
    }

    if ( SmartInterface == NULL ) {
        return EFI_SUCCESS;
    }
    Status = pBS->UninstallMultipleProtocolInterfaces(IdeDeviceHandle,
                                                        &gAmiHddSmartProtocolGuid,
                                                        SmartInterface,
                                                        NULL );

    if ( Status == EFI_SUCCESS ) {
        pBS->FreePool( SmartInterface );
        SmartInterface = NULL;
    }
    return Status;
}

/**
    Starts SMART SelfTest. SelfTestType will indicate whether to run
    short or extended self test.

    @param This 
    @param SelfTestType ( 0 : short, 1 :extended)
    @param PollPeriod (Minutes)

    @retval EFI_STATUS
    @retval PollPeriod will indicate the recommended time interval between polling.
    @retval Frequent polling will either abort the self test or may prolong it.

**/

EFI_STATUS 
SmartSelfTest (
    IN AMI_HDD_SMART_PROTOCOL   *This,
    IN UINT8        SelfTestType,
    OUT UINT16      *PollPeriod
)
{
    EFI_STATUS              Status;
    UINT8                   bData;
    AMI_SMART_INTERFACE     *SmartInterface = (AMI_SMART_INTERFACE*)This;    
    //
    // Check for Short or Extended
    //
    bData = SelfTestType == 0 ? 1 : 2;
    Status = SendSmartCommand( This, SMART_EXECUTE_OFFLINE_IMMEDIATE, 0, bData);

    *PollPeriod = SelfTestType == 0 ? SmartInterface->ShortPollingTime : SmartInterface->ExtPollingTime;

    return Status;
}

/**
    Aborts SMART Self Test. 

    @param  This 

    @retval EFI_STATUS

**/

EFI_STATUS
SmartAbortSelfTest (
    IN  AMI_HDD_SMART_PROTOCOL  *This
)
{
    VOID                *BusInterface = ((AMI_SMART_INTERFACE * )This)->BusInterface;    
    BOOLEAN             ModeFlag = ((AMI_SMART_INTERFACE * )This)->ModeFlag;
    COMMAND_STRUCTURE   CommandStructure;

    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Features = SMART_EXECUTE_OFFLINE_IMMEDIATE;
    CommandStructure.LBALow   = SMART_ABORT_SELF_TEST_SUBROUTINE;
    CommandStructure.LBAMid   = 0x4F;
    CommandStructure.LBAHigh  = 0xC2;
    CommandStructure.Command  = SMART_COMMAND;

    return CommonNonDataHook (BusInterface, CommandStructure, ModeFlag);

}

/**
    Get SMART data of the hard disk.

    @param  This 

    @retval OUT UINT8   **SmartData

**/

EFI_STATUS
SmartGetSmartData (
    IN              AMI_HDD_SMART_PROTOCOL  *This,
    OUT UINT8       **SmartData
)
{
    EFI_STATUS              Status;    
    VOID                    *BusInterface = ((AMI_SMART_INTERFACE * )This)->BusInterface;
    BOOLEAN                 ModeFlag = ((AMI_SMART_INTERFACE * )This)->ModeFlag;
    AMI_IDE_BUS_PROTOCOL    *IdeBusInterface;
    SATA_DEVICE_INTERFACE   *SataDevInterface;
    COMMAND_STRUCTURE       CommandStructure;

    IdeBusInterface         = (AMI_IDE_BUS_PROTOCOL *)BusInterface;
    SataDevInterface        = (SATA_DEVICE_INTERFACE *)BusInterface;

    Status = pBS->AllocatePool (EfiBootServicesData,
                                512,
                                (VOID**)SmartData);

    if (EFI_ERROR(Status)) {
        return EFI_OUT_OF_RESOURCES;
    }

    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
    CommandStructure.Buffer     = *SmartData; 
    CommandStructure.ByteCount  = 512;
    CommandStructure.Features   = SMART_READ_DATA;
    CommandStructure.LBAMid     = 0x4F;
    CommandStructure.LBAHigh    = 0xC2;   
    CommandStructure.Command    = SMART_COMMAND;
    
    if (ModeFlag == FALSE) {
        CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;
        Status = IdeBusInterface->AtaPioDataIn(  IdeBusInterface, 
                                                 CommandStructure.Buffer,
                                                 CommandStructure.ByteCount,
                                                 CommandStructure.Features, 
                                                 (UINT8)CommandStructure.SectorCount,
                                                 CommandStructure.LBALow, 
                                                 CommandStructure.LBAMid, 
                                                 CommandStructure.LBAHigh,
                                                 CommandStructure.Device, 
                                                 CommandStructure.Command,
                                                 FALSE
                                              );
          
    } else {
        Status = SataDevInterface->AhciBusInterface->ExecutePioDataCommand( 
                                                SataDevInterface, 
                                                &CommandStructure, 
                                                FALSE
                                              );
    }

    return Status;
}

/**
    Starts SMART SelfTest. SelfTestType will indicate whether to run
    short or extended self test.

        
    @param This 
    @param TestStatus 

    @retval 
        EFI_STATUS : TestStatus is valid only when EFI_STATUS is EFI_SUCCESS
        TestStatus : Will indicate the % of test completed.
        TestStatus = 0xFF Indicates Self Test Failed and EFI_STATUS = EFI_ERROR
  Example: When TestStatus = 10, 10% of the test has been done.

**/

EFI_STATUS 
SmartSelfTestStatus (
    IN AMI_HDD_SMART_PROTOCOL   *This,
    OUT UINT8                   *TestStatus
)
{
    EFI_STATUS               Status;
    UINT8                    *Buffer;    
    VOID                     *BusInterface = ((AMI_SMART_INTERFACE* )This)->BusInterface;
    BOOLEAN                  ModeFlag = ((AMI_SMART_INTERFACE* )This)->ModeFlag;
    AMI_IDE_BUS_PROTOCOL     *IdeBusInterface;
    SATA_DEVICE_INTERFACE    *SataDevInterface;
    COMMAND_STRUCTURE        CommandStructure;

    IdeBusInterface  = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    Status = pBS->AllocatePool( EfiBootServicesData,
                                512,
                                (VOID**)&Buffer );

    if ( EFI_ERROR( Status )){
        return EFI_OUT_OF_RESOURCES;
    }

    ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer    = Buffer;
    CommandStructure.ByteCount = 512;
    CommandStructure.Features  = SMART_READ_DATA;
    CommandStructure.LBAMid    = 0x4F;
    CommandStructure.LBAHigh   = 0xC2;
    CommandStructure.Command   = SMART_COMMAND;

    if ( ModeFlag == FALSE ) {
        CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;
        Status = IdeBusInterface->AtaPioDataIn(IdeBusInterface,
                                                CommandStructure.Buffer,
                                                CommandStructure.ByteCount,
                                                CommandStructure.Features,
                                                (UINT8)CommandStructure.SectorCount,
                                                CommandStructure.LBALow,
                                                CommandStructure.LBAMid,
                                                CommandStructure.LBAHigh,
                                                CommandStructure.Device,
                                                CommandStructure.Command,
                                                FALSE);
    } else {
        Status = SataDevInterface->AhciBusInterface->ExecutePioDataCommand(
            SataDevInterface,
            &CommandStructure,
            FALSE );
    }

    if ( EFI_ERROR( Status )) {
        *TestStatus = 0xff;
        pBS->FreePool( Buffer );
        return EFI_DEVICE_ERROR;
    }

    //
    // If Bits 7:4 is not equal to 0 or 0xf then there was an error
    // in the previous self test.
    //
    if (((Buffer[363] >> 4) != 0) && ((Buffer[363] >> 4) != 0xf)) {
        *TestStatus = 0xff;
        Status      = EFI_DEVICE_ERROR;
    } else {
        *TestStatus = Buffer[363] & 0xf;
        *TestStatus = 10 - (*TestStatus);
        *TestStatus = 10 * (*TestStatus);
    }
    pBS->FreePool( Buffer );
    return Status;
}

/**
    Returns SMART status

    @param This 

    @retval EFI_STATUS

    @note  Returns EFI_SUCCESS if threshold is not exceeded.

**/

EFI_STATUS 
SmartReturnStatus (
    IN AMI_HDD_SMART_PROTOCOL    *This
)
{
    VOID       *BusInterface = ((AMI_SMART_INTERFACE* )This)->BusInterface;
    BOOLEAN    ModeFlag      = ((AMI_SMART_INTERFACE* )This)->ModeFlag;

    return (SmartReturnStatusWrapper( BusInterface, ModeFlag ));
}

/**
    Sends any Non-Data SMART Command. 

    @param This 
    @param SubCommand 
    @param AutoSaveEnable //OPTIONAL
    @param SelfTestType //OPTIONAL

    @retval EFI_STATUS

    @note  Returns EFI_UNSUPPORTED when SMART feature is not enabled.

**/

EFI_STATUS
SendSmartCommand ( 
    IN AMI_HDD_SMART_PROTOCOL    *This,
    IN UINT8                     SubCommand,
    IN UINT8                     AutoSaveEnable,
    IN UINT8                     SelfTestType
)
{
    EFI_STATUS               Status;    
    VOID                     *BusInterface = ((AMI_SMART_INTERFACE * )This)->BusInterface;
    BOOLEAN                  ModeFlag = ((AMI_SMART_INTERFACE * )This)->ModeFlag;
    AMI_IDE_BUS_PROTOCOL     *IdeBusInterface;
    SATA_DEVICE_INTERFACE    *SataDevInterface;
    COMMAND_STRUCTURE        CommandStructure;
    IDENTIFY_DATA            IdentifyData;
    BOOLEAN                  EnableSmart;

    IdeBusInterface  = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ) {
        IdentifyData = IdeBusInterface->IdeDevice.IdentifyData;
    } else {
        IdentifyData = SataDevInterface->IdentifyData;
    }

    EnableSmart = SubCommand == SMART_ENABLE_CMD ? 1 : 0; 

    if (!((IdentifyData.Command_Set_Enabled_85 & 0x1) == EnableSmart)) {

   	    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE));
        CommandStructure.Features = SubCommand;
        CommandStructure.LBAMid   = 0x4F;
        CommandStructure.LBAHigh  = 0xC2;
        CommandStructure.Command  = SMART_COMMAND;

        switch (SubCommand) {

        case SMART_AUTOSAVE:
          CommandStructure.SectorCount = AutoSaveEnable;
          break;

        case SMART_EXECUTE_OFFLINE_IMMEDIATE:
          CommandStructure.LBALow   = SelfTestType;
          break;

        default:
          break;
        }

        if ( ModeFlag == FALSE ) {
	        CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;

	        //
            // IdeBus API changed from Core 4.6.5.2. Added Core Version check for the OLD 
            // Core support.
            //
            Status = IdeBusInterface->IdeNonDataCommand(IdeBusInterface,
                                                    CommandStructure.Features,
                                                    (UINT8)CommandStructure.SectorCount,
                                                    (UINT8)(CommandStructure.SectorCount >> 8),
                                                    CommandStructure.LBALow,
                                                    CommandStructure.LBALowExp,
                                                    CommandStructure.LBAMid,
                                                    CommandStructure.LBAMidExp,
                                                    CommandStructure.LBAHigh,
                                                    CommandStructure.LBAHighExp,
                                                    CommandStructure.Device,
                                                    CommandStructure.Command);
        } else {
            Status = SataDevInterface->AhciBusInterface->ExecuteNonDataCommand(
                                                            SataDevInterface,
                                                            CommandStructure );
        }
        return Status;

    } else {
        return EFI_UNSUPPORTED;
    }
}

/**
    Sends any Data In SMART command. 

    @param This 
    @param SubCommand 
    @param Buffer 
    @param LogAddress //OPTIONAL    
    @param SectorCount //OPTIONAL 
 
    @retval EFI__STATUS

**/

EFI_STATUS 
SmartReadData (
    IN  AMI_HDD_SMART_PROTOCOL    *This,
    IN  UINT8                     SubCommand,
    OUT VOID                      *Buffer,
    IN  UINT8                     LogAddress,
    IN  UINT8                     SectorCount
)
{
    EFI_STATUS               Status; 
    VOID                     *BusInterface = ((AMI_SMART_INTERFACE * )This)->BusInterface;
    BOOLEAN                  ModeFlag = ((AMI_SMART_INTERFACE * )This)->ModeFlag;
    AMI_IDE_BUS_PROTOCOL     *IdeBusInterface;
    SATA_DEVICE_INTERFACE    *SataDevInterface;
    COMMAND_STRUCTURE        CommandStructure;
    BOOLEAN                  MultipleSectors = FALSE;

   IdeBusInterface         = (AMI_IDE_BUS_PROTOCOL *)BusInterface;
   SataDevInterface        = (SATA_DEVICE_INTERFACE *)BusInterface;

    //
    //If SubCommand = SMART_READ_DATA then set SectorCount to 1 
    //
    if (SectorCount == 0) {
        SectorCount = 1;
    }

    ZeroMemory(&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer     = Buffer; 

    if ( SubCommand == SMART_READLOG ) {
        CommandStructure.LBALow       = LogAddress ;      // LOG Address to read
        CommandStructure.SectorCount  = SectorCount;      // No.of sectors to read
        CommandStructure.ByteCount    = SectorCount*ATA_SECTOR_BYTES;
        if ( SectorCount>1 ) {
            MultipleSectors = TRUE;
        }
    } else {
        //
        // SubCommand SMART_READ_DATA reads only 512 bytes.
        //
        CommandStructure.ByteCount    = 512;
    }
    CommandStructure.Features   = SubCommand;
    CommandStructure.LBAMid     = 0x4F;
    CommandStructure.LBAHigh    = 0xC2;
    CommandStructure.Command    = SMART_COMMAND;
 
    if (ModeFlag == FALSE) {

        Status = IdeBusInterface->AtaPioDataOut ( 
                                       IdeBusInterface,
                                       CommandStructure.Buffer,
                                       CommandStructure.ByteCount, 
                                       CommandStructure.Features,
                                       CommandStructure.SectorCount, 
                                       CommandStructure.LBALow, 
                                       CommandStructure.LBALowExp, 
                                       CommandStructure.LBAMid, 
                                       CommandStructure.LBAMidExp, 
                                       CommandStructure.LBAHigh,
                                       CommandStructure.LBAHighExp, 
                                       CommandStructure.Device, 
                                       CommandStructure.Command,
                                       FALSE, 
                                       MultipleSectors );
          
    } else {

        Status = SataDevInterface->AhciBusInterface->SataPioDataOut(
                                                        SataDevInterface,
                                                        CommandStructure.Buffer,
                                                        CommandStructure.ByteCount,
                                                        CommandStructure.Features,
                                                        CommandStructure.LBALow, 
                                                        CommandStructure.LBALowExp, 
                                                        CommandStructure.LBAMid, 
                                                        CommandStructure.LBAMidExp, 
                                                        CommandStructure.LBAHigh,
                                                        CommandStructure.LBAHighExp,
                                                        CommandStructure.Command,
                                                        FALSE );
    }

    return Status;
}

/**
    Sends any Data Out SMART command.

    @param This 
    @param SubCommand 
    @param Buffer 
    @param LogAddress 
    @param SectorCount 

    @retval EFI_STATUS

**/

EFI_STATUS 
SmartWriteData (
    IN AMI_HDD_SMART_PROTOCOL *This,
    IN UINT8                  SubCommand,
    IN VOID                   *Buffer,
    IN UINT8                  LogAddress,
    IN UINT8                  SectorCount
)
{
    EFI_STATUS                  Status;
    AMI_IDE_BUS_PROTOCOL        *IdeBusInterface;
    SATA_DEVICE_INTERFACE       *SataDevInterface;
    COMMAND_STRUCTURE           CommandStructure;
    VOID                        *BusInterface = ((AMI_SMART_INTERFACE * )This)->BusInterface;
    BOOLEAN                     ModeFlag = ((AMI_SMART_INTERFACE * )This)->ModeFlag;
    BOOLEAN                     MultipleSectors = FALSE;

   	IdeBusInterface         = (AMI_IDE_BUS_PROTOCOL *)BusInterface;
   	SataDevInterface        = (SATA_DEVICE_INTERFACE *)BusInterface;

    ZeroMemory( &CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer      = Buffer;
    CommandStructure.Features    = SubCommand;
    CommandStructure.ByteCount   = SectorCount * ATA_SECTOR_BYTES;
    CommandStructure.SectorCount = SectorCount;
    CommandStructure.LBALow      = LogAddress;       //LOG address to write on
    CommandStructure.LBAMid      = 0x4F;
    CommandStructure.LBAHigh     = 0xC2;
    CommandStructure.Command     = SMART_COMMAND;

    if ( SectorCount>1 )
        MultipleSectors = TRUE;

    if (ModeFlag == FALSE) {
        Status = IdeBusInterface->AtaPioDataOut ( 
                                       IdeBusInterface,
                                       CommandStructure.Buffer,
                                       CommandStructure.ByteCount, 
                                       CommandStructure.Features,
                                       CommandStructure.SectorCount, 
                                       CommandStructure.LBALow, 
                                       CommandStructure.LBALowExp, 
                                       CommandStructure.LBAMid, 
                                       CommandStructure.LBAMidExp, 
                                       CommandStructure.LBAHigh,
                                       CommandStructure.LBAHighExp, 
                                       CommandStructure.Device, 
                                       CommandStructure.Command,
                                       TRUE, 
                                       MultipleSectors ); 
    } else {

        Status = SataDevInterface->AhciBusInterface->SataPioDataOut (
                                                        SataDevInterface, 
                                                        CommandStructure.Buffer,
                                                        CommandStructure.ByteCount, 
                                                        CommandStructure.Features,
                                                        CommandStructure.LBALow, 
                                                        CommandStructure.LBALowExp, 
                                                        CommandStructure.LBAMid, 
                                                        CommandStructure.LBAMidExp, 
                                                        CommandStructure.LBAHigh,
                                                        CommandStructure.LBAHighExp, 
                                                        CommandStructure.Command,
                                                        TRUE ); 
    }
    
    return Status;
}

/**
    Common Hook which Calls Non Data Command.

    @param BusInterface 
    @param CommandStructure 
    @param ModeFlag 

    @retval EFI_STATUS

**/
EFI_STATUS 
CommonNonDataHook (
    IN VOID                 *BusInterface,
    IN COMMAND_STRUCTURE    CommandStructure,
    IN BOOLEAN              ModeFlag
)
{
    EFI_STATUS               Status;
    AMI_IDE_BUS_PROTOCOL     *IdeBusInterface;
    SATA_DEVICE_INTERFACE    *SataDevInterface;

    IdeBusInterface  = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
    SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;

    if ( ModeFlag == FALSE ) {
        CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;
        //
        // IdeBus API changed from Core 4.6.5.2. Added Core Version check for the OLD 
        // Core support.
        //
        Status = IdeBusInterface->IdeNonDataCommand(IdeBusInterface,
                                                    CommandStructure.Features,
                                                    (UINT8)CommandStructure.SectorCount,
                                                    (UINT8)(CommandStructure.SectorCount >> 8),
                                                    CommandStructure.LBALow,
                                                    CommandStructure.LBALowExp,
                                                    CommandStructure.LBAMid,
                                                    CommandStructure.LBAMidExp,
                                                    CommandStructure.LBAHigh,
                                                    CommandStructure.LBAHighExp,
                                                    CommandStructure.Device,
                                                    CommandStructure.Command);
    } else {
        Status = SataDevInterface->AhciBusInterface->ExecuteNonDataCommand(
            SataDevInterface,
            CommandStructure );
    }

    return Status;
}

/**
    Wrapper Function to call a ELINKed function

    @param  BOOLEAN Mode - TRUE - Device is in IDE mode
    @param  FALSE - Device is in AHCI mode
    @param  VOID *Interface - Interface.  Should be cast into SATA_DEVICE_INTERFACE
        or AMI_IDE_BUS_PROTOCOL depending on Mode parameter

    @retval VOID
    @retval VOID

**/

VOID
ReportSmartFailure (
    BOOLEAN Mode, 
    VOID *Interface
)
{
    OemReportSmartFailureFunction(Mode, Interface);
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
