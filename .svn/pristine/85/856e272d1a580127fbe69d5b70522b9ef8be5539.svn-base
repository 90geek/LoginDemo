#include "TseElinks.h"
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h> 
#include <Library/DebugLib.h>
#include <Library/PciLib.h>
#include <Library/BaseLib.h>

#include <Token.h> 
#include <Include/ServerMgmtSetupVariable.h> 
#include <Protocol/IPMITransportProtocol.h>
#include <Guid/SetupVariable.h>                  
#include <Include/IpmiNetFnChassisDefinitions.h> 

extern EFI_BOOT_SERVICES        *gBS;
extern EFI_RUNTIME_SERVICES     *gRT;
EFI_IPMI_TRANSPORT              *gIpmiTransport = NULL;

#define EFI_SM_NETFN_CHASSIS  0x00
#define FX_IPMI_OEM_COMMAND     0x30  // NetFun: 30h = OEM Request
#define FX_BIOS_REPORT_TO_BMC   0xF0  // Command: F0h = BIOS report to BMC command
//STS001002-#define FX_IPMI_BIOS_VERSION_COMMAND  0x38 //NetFun: 38h  //ZCH001012+
//STS001002-#define FX_BIOS_VERSION_REPORT_TO_BMC 0x0B //Command: 0Bh //ZCH001012+
#define FX_ENABLE_BIOS_REPORT_TO_BMC  0xF0  // F0h = Enable BIOS report to BMC command
#define FX_DISABLE_BIOS_REPORT_TO_BMC 0xF1  // F1h = Disable BIOS report to BMC command

/*typedef struct {
  UINT8   SubCmd; // 7h = RandomPowerOnEnable
  UINT8   Value;  // 0:Disable  1:Enable 
} FX_RANDOM_POWER_ON;*/
typedef struct {
  UINT8   SubCmd; // F0h = Enable BIOS report to BMC command
  UINT8   Data1;  // 0x55
  UINT8   Data2;  // 0xAA
} FX_ENABLE_BIOS_REPORT_DATA;

//VOID UpdateSystemInfoToBmc ();
//VOID GetRandomPowerOnInfo();
//VOID UpdateRestorePower();
VOID FxHandleSaveAndExit()
{ 
  DEBUG ((-1, "FxHandleSaveAndExit\n"));
  HandleSaveAndExit();
  UpdateSystemInfoToBmc();
};
VOID FxHandleSaveWithoutExit()
{ 
  DEBUG ((-1, "FxHandleSaveWithoutExit\n"));
  HandleSaveWithoutExit();
  UpdateSystemInfoToBmc();
};
VOID FxHandleSaveAndReset()
{
  DEBUG ((-1, "FxHandleSaveAndReset\n"));
  HandleSaveAndReset();
  UpdateSystemInfoToBmc();
}
/*VOID SendPSUStateToBMC()
{
  EFI_STATUS                      Status;
  SERVER_MGMT_CONFIGURATION_DATA  ServerMgmtConfiguration;
  UINTN                           Size;
  UINT8                           PSURequestData[2];
  UINT8                           ResponseData = 0;
  UINT8                           ResponseDataSize;
  EFI_GUID gEfiServerMgmtSetupVariableGuid = { {0x1239999}, {0xfc0e}, {0x4b6e}, { 0x9e, 0x79, 0xd5, 0x4d, 0x5d, 0xb6, 0xcd, 0x20 } };
	    
  Size = sizeof (SERVER_MGMT_CONFIGURATION_DATA);
  Status = gRT->GetVariable (
	            L"ServerSetup",
	            &gEfiServerMgmtSetupVariableGuid,
	            NULL,
	            &Size,
	            &ServerMgmtConfiguration);
  if(ServerMgmtConfiguration.PsuMode==2)   //no need change
      return;
  DEBUG ((-1, "Get ServerSetup Status: %r\n", Status));
  PSURequestData[0] = 0x01;
  PSURequestData[1] = ServerMgmtConfiguration.PsuMode;
  DEBUG ((-1, "ServerMgmtConfiguration.PsuOperatingMode: %d\n", ServerMgmtConfiguration.PsuMode));
  Status =gIpmiTransport->SendIpmiCommand(
              gIpmiTransport,
              0x30,//EFI_SM_INTEL_OEM
              0,//BMC_LUN
              0x72,
              PSURequestData,
              0x02,
              &ResponseData,
              &ResponseDataSize );
  DEBUG ((-1, "SendPSUStateToBMC Status: %r Response: %x\n", Status,ResponseData));
}*/
EFI_STATUS
SendPSUStateToBMC(VOID)
{
	EFI_STATUS          		Status;
	EFI_GUID                        EfiServerMgmtSetupVariableGuid = { {0x1239999}, {0xfc0e}, {0x4b6e}, { 0x9e, 0x79, 0xd5, 0x4d, 0x5d, 0xb6, 0xcd, 0x20 } };
	SERVER_MGMT_CONFIGURATION_DATA  ServerMgmtConfiguration;
	UINTN                           VarSize;	
	UINT8                           ResponseDataSize = 1;
	UINT8                           SetPsuRequestData[2];
	UINT8               		ResponseDate;

    //
    // Get PSU configure from setup
    //
    VarSize = sizeof(SERVER_MGMT_CONFIGURATION_DATA);
	Status = gRT->GetVariable (
					L"ServerSetup",
					&EfiServerMgmtSetupVariableGuid,
					NULL,
					&VarSize,
					&ServerMgmtConfiguration
					);
	DEBUG ((-1, " Send psu state to BMC Status: %r\n",Status));
    if(!EFI_ERROR(Status) && (ServerMgmtConfiguration.PsuMode !=2)) {				
    	SetPsuRequestData[0] = 0x01;
    	SetPsuRequestData[1] = ServerMgmtConfiguration.PsuMode;   
    	DEBUG ((-1, " Send psu state to BMC PsuMode:%d \n",ServerMgmtConfiguration.PsuMode));	
    	if(!EFI_ERROR(Status)) {
		//
		// Set PSU mode
		//
		Status = gIpmiTransport->SendIpmiCommand (
					gIpmiTransport,
					0x30,
					BMC_LUN,
					0x72,
					SetPsuRequestData,
					0x02,
					&ResponseDate,
					&ResponseDataSize );
		DEBUG ((-1, " Send psu state to BMC Status: %r,PsuMode:%d \n",Status,ServerMgmtConfiguration.PsuMode));
	}                       	    
    } 
    
   return Status;
}
VOID
EFIAPI
UpdateSystemInfoToBmc ()
{
  EFI_STATUS                  Status;                        
  EFI_GUID gEfiDxeIpmiTransportProtocolGuid = {{0x4a1d0e66},{0x5271}, {0x4e22}, {0x83, 0xfe, 0x90, 0x92, 0x1b, 0x74, 0x82, 0x13}}; 


  DEBUG((DEBUG_INFO, "%a: Entering...\n", __FUNCTION__));

  Status = gBS->LocateProtocol (
                      &gEfiDxeIpmiTransportProtocolGuid,
                      NULL,
                      (VOID**)&gIpmiTransport );

  DEBUG ((-1, " Locate gEfiDxeIpmiTransportProtocolGuid Status: %r \n",Status));
  
  if(EFI_ERROR (Status)) {
    return;
  }
  DEBUG ((-1, " start to SendPSUStateToBMC\n"));
  SendPSUStateToBMC();
  DEBUG((DEBUG_INFO, "%a: Exiting...\n", __FUNCTION__));
  return;
  
}
