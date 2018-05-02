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
//TH0141>>>
#if ME_FLASH_OVERRIDE
#include <GrantleyPkg\Include\Guid\SetupVariable.h>
#endif
//TH0141<<<
#include <FoxconnPkg\OemDxeDrivers\ModifyBiosConfigOverBmc\ModifyBiosConfigOverBmc.h>	//TH0153
//TH0155>>>
//DJH002026-- #if OEM_SEL_LOG_SUPPORT == 1
#if (OEM_SEL_LOG_SUPPORT == 1 || OEM_SENSOR_NUMBER_SUPPORT == 1 ) //DJH002026++
#include <AmiIpmiPkg\Include\Include\IpmiNetFnStorageDefinitions.h>
#endif //OEM_SEL_LOG_SUPPORT
//TH0155<<<

//----------------------------------------------------------------------

extern INIT_LPC_BMC INIT_LPC_BMC_HOOK_LIST EndOfInitLpcBmcHookListFunctions;
INIT_LPC_BMC* InitLpcBmcHookList[] = {INIT_LPC_BMC_HOOK_LIST NULL};
//TH0090>>>>
#if PSU_REDUNDANCY_SUPPORT == 1
/*
1. Balanced. 
    0x30 0x45 0x00
2. PSU1 active, PSU2 standby.
    0x30 0x45 0x01
3. PSU1 standby, PSU2 active.
    0x30 0x45 0x02
*/
#define EFI_SM_INTEL_OEM    0x30   
EFI_STATUS PsuOperatingModeFunction (
  IN  EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance,
  IN  UINT8 CommandData);
#endif
//TH0090<<<<

//TH0092>>>>
#if POWER_RESTORE_POLICY_SUPPORT
#include <SetupVariable.h>
EFI_STATUS SetPowerRestorePolicy(
  IN  CONST EFI_PEI_SERVICES    **PeiServices,
  IN  EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance
);
#endif
//TH0092<<<<

//TH0118>>>>
#if NCSI_SELECT_SUPPORT
BOOLEAN CheckNcsiLinkChange(
  IN	EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance,
  IN	UINT8						  NcsiLinkSelect
);

BOOLEAN	CheckLanOcpCardPresent(
);

VOID lpc_read(
  IN	UINT32        Address,
  OUT	UINT32         *Value
);
#endif
//TH0118<<<<

//TH0155>>>
UINT8 ReadCmos( UINT8 Index );
VOID WriteCmos( UINT8 Index, UINT8 Data );
//DJH002026-- #if OEM_SEL_LOG_SUPPORT == 1
#if (OEM_SEL_LOG_SUPPORT == 1 || OEM_SENSOR_NUMBER_SUPPORT == 1 ) //DJH002026++
VOID AddWarmResetSEL( IN EFI_IPMI_BMC_INSTANCE_DATA *IpmiInstance );
#endif //OEM_SEL_LOG_SUPPORT
//TH0155<<<

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
    UINT32									                LVL1_SEL;//TH0076A

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
//ZA0017>>>
#if Foxconn_SUPPORT
         ServerMgmtConfiguration.WaitForBmc = DEFAULT_WAIT_BMC_TIMEOUT; 
#else
//ZA0017<<<
         ServerMgmtConfiguration.WaitForBmc = 0; //Load default value.
#endif	//ZA0017
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

//TH0155>>>
//DJH002026-- #if OEM_SEL_LOG_SUPPORT == 1
#if (OEM_SEL_LOG_SUPPORT == 1 || OEM_SENSOR_NUMBER_SUPPORT == 1 ) //DJH002026++
    AddWarmResetSEL( IpmiInstance );
#endif //OEM_SEL_LOG_SUPPORT
//TH0155<<<

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
            //TH0076>>>
            //
            // Turn on FP power LED before iBMC initialization during AC Power Cycle On.
            // FP_PWR_LED_N signal is controlled by PCH GPIO25 and asserted low.
            //
            *(volatile UINT16*) ((UINTN) (PcdGet64(PcdPciExpressBaseAddress)) + \
                    (UINTN) PCI_LIB_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, LPC_GPIO_BASE)) = (UINT16) GPIO_BASE_ADDRESS;
            *(volatile UINT8*) ((UINTN) (PcdGet64(PcdPciExpressBaseAddress)) + \
                    (UINTN) PCI_LIB_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, LPC_GPIO_CNT)) |= (UINT8) LPC_GPIO_CNT_GPIO_EN;
        
            LVL1_SEL = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL);//TH0076A
            LVL1_SEL &= (UINT32)(~BIT25);//TH0076A
            IoWrite32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL, LVL1_SEL);//TH0076A
        
            *(volatile UINT8*) ((UINTN) (PcdGet64(PcdPciExpressBaseAddress)) + \
                    (UINTN) PCI_LIB_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, LPC_GPIO_CNT)) &= (UINT8)(~LPC_GPIO_CNT_GPIO_EN);
            *(volatile UINT16*) ((UINTN) (PcdGet64(PcdPciExpressBaseAddress)) + \
                    (UINTN) PCI_LIB_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, LPC_GPIO_BASE)) &= (UINT16)(~LPC_GPIO_BASE_BAR);
            //TH0076<<<
        //
        // Check whether WaitForBmc setup option is enabled or not
        //
        if (ServerMgmtConfiguration.WaitForBmc) {
            SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Giving DELAY_OF_THIRTY_SECOND sec delay.. start \n"));
//ZA0017>>>
#if Foxconn_SUPPORT
			      MicroSecondDelay (ServerMgmtConfiguration.WaitForBmc*1000000); //ZA0017
#else
//ZA0017<<<
            MicroSecondDelay (DELAY_OF_THIRTY_SECOND);
#endif	//ZA0017
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

//TH0118>>>
#if NCSI_SELECT_SUPPORT     
   BMC_SELF_TEST:
#endif
//TH0118<<<

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
    
//TH0118>>>
#if NCSI_SELECT_SUPPORT
    if ( CheckNcsiLinkChange (IpmiInstance, ServerMgmtConfiguration.NcsiLinkSelect) )
    	goto BMC_SELF_TEST;
#endif
//TH0118<<<

//TH0141>>>
#if ME_FLASH_OVERRIDE
    {
       	UINTN  					VarSize;
    	UINT8               	MeUpdateData[2];
    	UINT8					MeResponseData;
    	UINT8               	MeResponseDataSize = 1;
    	SYSTEM_CONFIGURATION 	SystemConfiguration;
    	EFI_GUID 				SystemConfigurationGuid = SYSTEM_CONFIGURATION_GUID;

    	//
    	// Get MeFalshOverride.
    	//
    	VarSize = sizeof(SYSTEM_CONFIGURATION);
    	Status = PeiVariable->GetVariable (
    				PeiVariable,
    				L"IntelSetup",
    				&SystemConfigurationGuid,
    				NULL,
    				&VarSize,
    				&SystemConfiguration);		
    	
    	if(!EFI_ERROR(Status)) {
    		MeUpdateData[0] = 0x02;		//get me flash override from BMC
    		Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
    						&IpmiInstance->IpmiTransport,
    						0x30,
    						BMC_LUN,
    						0x75,
    						MeUpdateData,
    						sizeof(MeUpdateData),
    						&MeResponseData,
    						&MeResponseDataSize);

    		if(!EFI_ERROR(Status) && (MeResponseData != SystemConfiguration.MeFalshOverride)){
    			
    			MeUpdateData[0] = 0x01;		//set me falsh override to bmc
    			MeUpdateData[1] = SystemConfiguration.MeFalshOverride;
    			
    			Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
    						&IpmiInstance->IpmiTransport,
    						0x30,
    						BMC_LUN,
    						0x75,
    						MeUpdateData,
    						sizeof(MeUpdateData),
    						&MeResponseData,
    						&MeResponseDataSize);
    			
    			if(!EFI_ERROR (Status)){
    				 PciOr32 (PCI_LIB_ADDRESS(0, 31, 0, 0xAC),BIT20); //set global reset bit
    				 IoWrite8(0xCF9,0x0E);
    			}
    		}
    	}
    }
#endif	//ME_FLASH_OVERRIDE
//TH0141<<<

//TH0153>>>
{
    UINTN  					VarSize;
	SYSTEM_CONFIGURATION 	SystemConfiguration;
	EFI_GUID 				SystemConfigurationGuid = SYSTEM_CONFIGURATION_GUID;
	EFI_GUID				mPreviousSetupBiosConfgGuid = PREVIOUS_SETUP_BIOS_CONFIG_GUID;
	BIOS_CONFIG_PART	    PreviousBiosConfig;
	UINT8					PreviousNumaConfig;
	UINT8					NMI_EN;
	
	VarSize = sizeof(SYSTEM_CONFIGURATION);
	Status = PeiVariable->GetVariable (
				PeiVariable,
				L"IntelSetup",
				&SystemConfigurationGuid,
				NULL,
				&VarSize,
				&SystemConfiguration);
	
	if(!EFI_ERROR(Status)) {
		VarSize = sizeof(BIOS_CONFIG_PART);
		Status = PeiVariable->GetVariable (
					PeiVariable,
					L"PreviousSetupBiosConfg",
					&mPreviousSetupBiosConfgGuid,
					NULL,
					&VarSize,
					&PreviousBiosConfig);
		
		if(!EFI_ERROR(Status)) {
			
			if( SystemConfiguration.NumaEn != PreviousBiosConfig.NumaEn ) {
				
				NMI_EN = IoRead8(0x70) & 0x80;	//Bit 7 is the NMI bit -- it should be protected.
				IoWrite8(0x70, NUMA_CMOS_INDEX | NMI_EN);
				PreviousNumaConfig = IoRead8(0x71);
				
				if( SystemConfiguration.NumaEn != PreviousNumaConfig ) {
					NMI_EN = IoRead8(0x70) & 0x80;
					IoWrite8(0x70, NUMA_CMOS_INDEX | NMI_EN);
					IoWrite8(0x71, SystemConfiguration.NumaEn);
					IoWrite8(0xCF9, 0x0E);
				}
			}
			
		}else {
			NMI_EN = IoRead8(0x70) & 0x80;
			IoWrite8(0x70, NUMA_CMOS_INDEX | NMI_EN);
			IoWrite8(0x71, SystemConfiguration.NumaEn);
		}
	}
}
//TH0153<<<

//TH0090>>>>
#if PSU_REDUNDANCY_SUPPORT == 1
    if ( ServerMgmtConfiguration.Redundancy == 0 ) {
    	//Balanced
    	PsuOperatingModeFunction ( IpmiInstance, 0 );
    }else if ( ServerMgmtConfiguration.Redundancy == 1 ){
    	//PSU1 active, PSU2 standby / PSU1 standby, PSU2 active.
    	PsuOperatingModeFunction ( IpmiInstance, ServerMgmtConfiguration.PsuOperatingMode );
    }
#endif
//TH0090<<<<
//TH0092>>>>
#if POWER_RESTORE_POLICY_SUPPORT
    SetPowerRestorePolicy ( PeiServices, IpmiInstance );
#endif
//TH0092<<<<

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

//TH0090>>>>
#if PSU_REDUNDANCY_SUPPORT == 1
//<OEM_PHDR_START>
//----------------------------------------------------------------------------
// Name: PsuOperatingModeFunction
//
// Description:
//   Execute the send command for PSU operating mode.
//
//1. When CommandData is 0x00,PSU work on Balanced mode. 
//2. When CommandData is 0x01,PSU work on PSU1 active, PSU2 standby mode.
//3. When CommandData is 0x02,PSU work on PSU1 standby, PSU2 active mode.
//
// Input:
//  IN  EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance
//  IN  UINT8 CommandData
// Output:
//  EFI_STATUS
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
EFI_STATUS
PsuOperatingModeFunction (
  IN  EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance,
  IN  UINT8 CommandData)
{
    EFI_STATUS          Status;
    UINT8               DataSize =0;
    
    Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
                &IpmiInstance->IpmiTransport,
                EFI_SM_INTEL_OEM,
                BMC_LUN,
                0x45,	//EFI_STORAGE_PARTIAL_ADD_SEL_ENTRY
                (UINT8 *) &CommandData,
                1,
                NULL,
                &DataSize );

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "send PSU operating mode command status %r\n", Status));

    return Status;
}
#endif
//TH0090<<<<

//TH0092>>>>
#if POWER_RESTORE_POLICY_SUPPORT
//----------------------------------------------------------------------------
// Procedure: SetPowerRestorePolicy
//
// Description:	Set Power Restore Policy command by this function
//
// Input:  IN  EFI_PEI_SERVICES    **PeiServices	
//         IN  EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance
// Output:
//
//----------------------------------------------------------------------------
EFI_STATUS
SetPowerRestorePolicy(
  IN  CONST EFI_PEI_SERVICES    **PeiServices,
  IN  EFI_IPMI_BMC_INSTANCE_DATA  *IpmiInstance
)
{
	EFI_STATUS						Status;
	UINTN							VariableSize;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI	*PeiVariable;
	SYSTEM_CONFIGURATION			SystemConfiguration;
	UINT8							RequestData[1];
	UINT8 							ResponseDataSize = 0; 

	Status = (**PeiServices).LocatePpi (
			PeiServices,
			&gEfiPeiReadOnlyVariable2PpiGuid,
			0,
			NULL,
			&PeiVariable
			);  

	ASSERT_EFI_ERROR (Status);

	VariableSize = sizeof (SYSTEM_CONFIGURATION);

	// AptioV server override: Changed variable name to IntelSetup
	Status = PeiVariable->GetVariable (
			PeiVariable,
			L"IntelSetup",
			&gEfiSetupVariableGuid,
			NULL,
			&VariableSize,
			&SystemConfiguration
			);

	if(!EFI_ERROR(Status)){
		switch ( SystemConfiguration.PowerState ){
			case 0:
				RequestData[0] = 0x02;
				break;
			case 1:
				RequestData[0] = 0x00;
				break;
			default:
				break;
		}
	}else{
		RequestData[0] = 0x00;
	}

	Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
			&IpmiInstance->IpmiTransport,	// *This
			0x30,				// NetFunction
			BMC_LUN,						// LUN
			0x44,							// Command
			(UINT8 *) RequestData,			//*CommandData
			0x01,							// CommandDataSize
			NULL,							// *ResponseData
			(UINT8 *) &ResponseDataSize		// ResponseDataSize							
			);

	SERVER_IPMI_DEBUG ((EFI_D_LOAD, "send power Restore Policy command status %r\n", Status));
	
	return Status;
}
#endif
//TH0092<<<<

//TH0118>>>
#if NCSI_SELECT_SUPPORT
BOOLEAN
CheckNcsiLinkChange(
  IN  EFI_IPMI_BMC_INSTANCE_DATA	*IpmiInstance,
  IN  UINT8						  	NcsiLinkSelect
)
{
	UINT8              				RequestData[2];
	UINT8							RequestDataSize = 2;
	UINT8							ResponseData = 0;
	UINT8							ResponseDataSize = 1;
	BOOLEAN							NcsiLinkChange = FALSE;
	EFI_STATUS						Status;

    if ( !CheckLanOcpCardPresent() ) {
    	NcsiLinkSelect = 1;
		SERVER_IPMI_DEBUG ((EFI_D_LOAD, "OEM DEBUG: LAN OCP card has not been found\n"));
    }

	RequestData[0] = 0x02;
	RequestData[1] = 0x00;
	
	Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
			&IpmiInstance->IpmiTransport,
			0x30,
			BMC_LUN,
			0x71,
			RequestData,
			RequestDataSize,
			&ResponseData,
			&ResponseDataSize );

	if ( !EFI_ERROR(Status) && (ResponseData != NcsiLinkSelect) ) {
		RequestData[0] = 0x01;
		RequestData[1] = NcsiLinkSelect;
		
		Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
				&IpmiInstance->IpmiTransport,
				0x30,
				BMC_LUN,
				0x71,
				RequestData,
				RequestDataSize,
				&ResponseData,
				&ResponseDataSize );

		if ( !EFI_ERROR(Status) ) {
			SERVER_IPMI_DEBUG ((EFI_D_LOAD, "OEM DEBUG: Wait for iBMC to switch NCSI link and reinitialize\n"));
			//
			// Delay 20 sec to wait BMC to switch the NCSI, so the total delay is 70 sec.
			//
			MicroSecondDelay ( (20 + DEFAULT_WAIT_BMC_TIMEOUT) * 1000000 );
			NcsiLinkChange = TRUE;
		}
	}
	
	return	NcsiLinkChange;
}


BOOLEAN
CheckLanOcpCardPresent(
)
{
	UINT32		Address;
	UINT32		Value;

    Address = (UINT32)(0x1e780000 | 0x20);
    lpc_read (Address, &Value);
	
    if (Value & BIT29)
    	return	FALSE;
    else
    	return	TRUE;
}


VOID
lpc_read (
  IN	UINT32 ulAddress,
  OUT	UINT32  *Value)
{
    UINT32    uldata = 0;
    UINT8     jtemp;

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_ENTER_VALUE);
    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_ENTER_VALUE);

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_LDN_SEL_REGISTER);
    IoWrite8 (AST2400_CONFIG_DATA, AST2400_LDN_LPC2AHB);

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_ACTIVATE_REGISTER);
    jtemp = IoRead8 (AST2400_CONFIG_DATA); //
    IoWrite8 (AST2400_CONFIG_DATA, (jtemp | 0x01));//Active
//Write Address
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF0);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0xFF000000) >> 24));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF1);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0x00FF0000) >> 16));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF2);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0x0000FF00) >> 8));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF3);
    IoWrite8 (AST2400_CONFIG_DATA, ulAddress & 0xFF);
//Write Mode
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF8);
    jtemp = IoRead8 (AST2400_CONFIG_DATA);
    IoWrite8 (AST2400_CONFIG_DATA, (jtemp & 0xFC) | 0x02);
//Fire
    IoWrite8 (AST2400_CONFIG_INDEX, 0xFE);
    jtemp = IoRead8 (AST2400_CONFIG_DATA);
//Get Data
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF4);
    uldata |= (IoRead8 (AST2400_CONFIG_DATA) << 24);
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF5);
    uldata |= (IoRead8 (AST2400_CONFIG_DATA) << 16);
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF6);
    uldata |= (IoRead8 (AST2400_CONFIG_DATA) << 8);
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF7);
    uldata |= (IoRead8 (AST2400_CONFIG_DATA));
    
    *Value = uldata;

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_EXIT_VALUE);
}
#endif
//TH0118<<<

//TH0155>>>
//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadCmos
//
// Description: Read CMOS via IoRead8().
//
// Input:       UINT8	Index
//
// Output:      UINT8	Data
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
UINT8
ReadCmos(UINT8 Index){
	UINT8					NMI_EN;
	UINT8					CmosValue;
	
	NMI_EN = IoRead8(0x70) & 0x80;	//Bit 7 is the NMI bit -- it should be protected.
	IoWrite8(0x70, Index | NMI_EN);
	CmosValue = IoRead8(0x71);
	
	return CmosValue;
}

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteCmos
//
// Description: Write CMOS via IoWrite8().
//
// Input:       UINT8	Index,
//				UINT8	Data
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
VOID
WriteCmos(UINT8 Index, UINT8 Data){
	UINT8					NMI_EN;
	
	NMI_EN = IoRead8(0x70) & 0x80;
	IoWrite8(0x70, Index | NMI_EN);
	IoWrite8(0x71, Data);
}

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AddPowerUpSEL
//
// Description: Add warm reset SEL.
//
// Input:       EFI_IPMI_TRANSPORT*	IpmiTransport
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
//DJH002026-- #if OEM_SEL_LOG_SUPPORT == 1
#if (OEM_SEL_LOG_SUPPORT == 1 || OEM_SENSOR_NUMBER_SUPPORT == 1 ) //DJH002026++
VOID
AddWarmResetSEL( IN  EFI_IPMI_BMC_INSTANCE_DATA	*IpmiInstance ) 
{	
	EFI_STATUS					Status;
	BOOLEAN 					WarmReset;
	UINT8	 					ResetCount;
	UINT16                      RecordId = 0;
	UINT8                       ResponseDataSize;
	
	EFI_SEL_RECORD_DATA SelRecordData = {
		0000,      // Record Id
		EFI_SEL_SYSTEM_RECORD,      // Record Type
		00000000,  // Time stamp
		(UINT16) EFI_GENERATOR_ID (BIOS_SOFTWARE_ID),    // GenID:BIOS
		EFI_EVM_REVISION,      // EFI_EVM_REVISION
		0x1D,      // Sensor Type
	//DJH002027++>>
	#if OEM_SENSOR_NUMBER_SUPPORT == 1
		0x9D,      // Sensor No
	#else
	//DJH002027++<<
		0xE0,      // Sensor No
	#endif //DJH002027++
		EFI_SENSOR_TYPE_EVENT_CODE_DISCRETE,      // Event Dir
		02,        // Sensor specific Offset for Timestamp Clock Synch Event.
		00,        // ED2
		00         // ED3
	};
	
	WarmReset = (BOOLEAN) !!(( *(volatile UINT8*) ((UINTN) (PcdGet64(PcdPciExpressBaseAddress)) + \
			  (UINTN) PCI_LIB_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, 0xA2))) & BIT5 );
	
	if (WarmReset) {
		// current boot is warm
		ResetCount = ReadCmos(RESET_COUNTER_CMOS_INDEX);
		ResetCount++;
		
#define WARM_RESET_COUNTER_LIMIT 10
	    if (ResetCount > WARM_RESET_COUNTER_LIMIT) {
	      // limit CmosValue to avoid counter rewind
	      // and false cold reset indication
	    	ResetCount = WARM_RESET_COUNTER_LIMIT;
	    }
#undef WARM_RESET_COUNTER_LIMIT
	    
		if ( ResetCount > 1 ){
			SERVER_IPMI_DEBUG ((EFI_D_ERROR, "Add warm reset SEL record.\n"));
			ResponseDataSize = sizeof (RecordId);
			Status = IpmiInstance->IpmiTransport.SendIpmiCommand (
						&IpmiInstance->IpmiTransport,
						EFI_SM_NETFN_STORAGE,
						BMC_LUN,
						EFI_STORAGE_ADD_SEL_ENTRY,
						(UINT8 *) &SelRecordData,
						sizeof (EFI_SEL_RECORD_DATA),
						(UINT8 *) &RecordId,
						&ResponseDataSize );
		}else{
			SERVER_IPMI_DEBUG ((EFI_D_ERROR, "MRC Warm Reset.\n"));
		}

	}else{	//cold reset
		ResetCount = 0;
	}
    
	WriteCmos(RESET_COUNTER_CMOS_INDEX, ResetCount);
}
#endif //OEM_SEL_LOG_SUPPORT
//TH0155<<<


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
