//**********************************************************************
//<OEM_FHDR_START>
//
// Name:    OemPsuPolicy.c
//
// Description:
//  Change PSU mode
//
//<OEM_FHDR_END>
//**********************************************************************
#include "OemPsuPolicy.h"

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SavePsuState
//
// Description: Save current PSU state
//
//				OEM Ipmi Command:
//				1. Balanced. 
//					0x30 0x72 0x03
//				2. PSU1 active, PSU2 standby.
//					0x30 0x72 0x04
//				3. PSU1 standby, PSU2 active.
//					0x30 0x72 0x05
//
// Input:
//
// Output:      EFI_STATUS - Return Status
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
EFI_STATUS
SavePsuState(VOID)
{
	EFI_STATUS          			Status;
	EFI_IPMI_TRANSPORT      		*IpmiTransport=NULL;
	EFI_GUID						EfiDxeIpmiTransportProtocolGuid  = EFI_DXE_IPMI_TRANSPORT_PROTOCOL_GUID;
	EFI_GUID                        EfiServerMgmtSetupVariableGuid = SERVER_MGMT_CONFIGURATION_GUID;
	SERVER_MGMT_CONFIGURATION_DATA  ServerMgmtConfiguration;
	EFI_GUID 						SetupHideGuid = SETUP_HIDE_GUID;	
	SETUP_HIDE_FEATURES				SetupHideFeatures;					
	UINTN                           VarSize;
 	UINT8              				GetPsuRequestData[2] = {0x02, 0x00};
	UINT8                           GetPsuRequestDataSize = 2;
	UINT8                           ResponseDate[2] = {0x01,0x02};
	UINT8                           ResponseDateSize = 2;
	
    Status = pBS->LocateProtocol (
                &EfiDxeIpmiTransportProtocolGuid,
                NULL,
                (VOID **)&IpmiTransport 
             	);
    
    if(!EFI_ERROR(Status)) {
		//
		// Get PSU mode from BMC
		//
		Status = IpmiTransport->SendIpmiCommand (
						IpmiTransport,
						0x30,
						BMC_LUN,
						0x72,
						GetPsuRequestData,  
						GetPsuRequestDataSize,
						ResponseDate,
						&ResponseDateSize );
						
		if(!EFI_ERROR(Status)) {
			//
			// Set PSU mode item to unspecified if 2 PSU are detected.
			//
			if(ResponseDate[0] == 2) {
				VarSize = sizeof(SERVER_MGMT_CONFIGURATION_DATA);
				Status = pRS->GetVariable (
								L"ServerSetup",
								&EfiServerMgmtSetupVariableGuid,
								NULL,
								&VarSize,
								&ServerMgmtConfiguration );
				
				if(!EFI_ERROR(Status) && (ServerMgmtConfiguration.PsuMode != 2)) {
					ServerMgmtConfiguration.PsuMode = 2;
					Status = pRS->SetVariable (
									L"ServerSetup",
									&EfiServerMgmtSetupVariableGuid,
									EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
									VarSize,
									&ServerMgmtConfiguration );
				}
			}

			//
			// Save PSU count and initial PSU mode string.
			//
			VarSize = sizeof(SETUP_HIDE_FEATURES);
			Status = pRS->GetVariable (
							L"SetupHideFeatures",
							&SetupHideGuid,
							NULL,
							&VarSize,
							&SetupHideFeatures );

			if(!EFI_ERROR(Status)) {
				SetupHideFeatures.PsuCount = ResponseDate[0];
				SetupHideFeatures.PsuMode = ResponseDate[1];
				Status = pRS->SetVariable (
								L"SetupHideFeatures",
								&SetupHideGuid,
								EFI_VARIABLE_BOOTSERVICE_ACCESS,
								VarSize,
								&SetupHideFeatures );
			}
		}
    }
            
    return Status;
}

//----------------------------------------------------------------------------
//
// Procedure:   SetPsuPolicy
//
// Description: Change PSU mode over BIOS Setup
//
//				OEM Ipmi Command:
//				1. Balanced. 
//					0x30 0x72 0x03
//				2. PSU1 active, PSU2 standby.
//					0x30 0x72 0x04
//				3. PSU1 standby, PSU2 active.
//					0x30 0x72 0x05
//
// Input:       None
//
// Output:      EFI_STATUS - Return Status
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
EFI_STATUS
SetPsuPolicy(VOID)
{
	EFI_STATUS          			Status;
	EFI_IPMI_TRANSPORT      		*IpmiTransport = NULL;
	EFI_GUID						EfiDxeIpmiTransportProtocolGuid  = EFI_DXE_IPMI_TRANSPORT_PROTOCOL_GUID;
	EFI_GUID                        EfiServerMgmtSetupVariableGuid = SERVER_MGMT_CONFIGURATION_GUID;
	SERVER_MGMT_CONFIGURATION_DATA  ServerMgmtConfiguration;
	UINTN                           VarSize;	
	UINT8                           ResponseDataSize = 1;
	UINT8                           SetPsuRequestData[2];
	UINT8               			ResponseDate;

    //
    // Get PSU configure from setup
    //
    VarSize = sizeof(SERVER_MGMT_CONFIGURATION_DATA);
	Status = pRS->GetVariable (
					L"ServerSetup",
					&EfiServerMgmtSetupVariableGuid,
					NULL,
					&VarSize,
					&ServerMgmtConfiguration
					);
	
    if(!EFI_ERROR(Status) && (ServerMgmtConfiguration.PsuMode !=2)) {				
    	SetPsuRequestData[0] = 0x01;
    	SetPsuRequestData[1] = ServerMgmtConfiguration.PsuMode;   
	
		Status = pBS->LocateProtocol (
					&EfiDxeIpmiTransportProtocolGuid,
					NULL,
					(VOID **)&IpmiTransport 
					);
		
	    if(!EFI_ERROR(Status)) {
			//
			// Set PSU mode
			//
			Status = IpmiTransport->SendIpmiCommand (
						IpmiTransport,
						0x30,
						BMC_LUN,
						0x72,
						SetPsuRequestData,
						0x02,
						&ResponseDate,
						&ResponseDataSize );
		}                       	    
    } 
    
   return Status;
}
