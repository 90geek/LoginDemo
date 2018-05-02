#include <SetupStrDefs.h>
#include <Setup.h>
#include "Token.h"
#include "FxnChangeSKUType.h"

extern UINT8 LastALIConfig;
extern UINTN LastAliConfigVarSize;

//extern EFI_GUID gAmiTseOemTSEVarGuid;
EFI_GUID gEfiSocketPowermanagementVarGuid = SYSTEM_CONFIGURATION_GUID;
EFI_GUID  gSetupGuid = SETUP_GUID; 

//FXNOEMTSEVAR *FxnOemTseVarData;
SETUP_DATA    *SetupData;
SYSTEM_CONFIGURATION *SocketManagementConfig;

UINTN        SetupDataSize;
//UINTN         FxnOemTseVarDataSize;
UINTN        SocketManagementConfigSize;



EFI_STATUS AliConfig_CallBack(
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16 Class, 
    IN UINT16 SubClass, 
    IN UINT16 Key
) {
		EFI_STATUS	Status = EFI_SUCCESS;
		CALLBACK_PARAMETERS *Callback = NULL;
		
//		FxnOemTseVarDataSize = sizeof(FXNOEMTSEVAR);
		SetupDataSize = sizeof(SETUP_DATA);
		SocketManagementConfigSize = sizeof(SYSTEM_CONFIGURATION);
		
		
		Callback = GetCallbackParameters();   	
		DEBUG ((EFI_D_LOAD, "\n AliConfig_CallBack Key=%0X, Action=%0X\n KeyValue:%x Type:%x,Callback->Type:%x,Callback->ActionRequest:%x", Key, Callback->Action,Callback->KeyValue,Callback->Type,Callback->ActionRequest));
	    if ((Key == ALI_CONFIG_KEY) && (Callback->Action == EFI_BROWSER_ACTION_CHANGED ))//|| Callback->Action ==EFI_BROWSER_ACTION_DEFAULT_STANDARD))        
	    {
	    	//Status = gBS->AllocatePool (
	    	 //                   EfiBootServicesData,
	    	 //                   FxnOemTseVarDataSize,
	    	  //                  (VOID **)&FxnOemTseVarData );
	    	//Status = HiiLibGetBrowserData(&FxnOemTseVarDataSize, FxnOemTseVarData, &gAmiTseOemTSEVarGuid, L"OemTSEVar");
	    	//DEBUG((EFI_D_LOAD,"\n AliConfig_CallBack FxnOemTseVarData->AliConfig=%x Status:%r \n",FxnOemTseVarData->AliConfig,Status));
	    	Status = gBS->AllocatePool(
	    					EfiBootServicesData,
	    					SetupDataSize,
	    					(VOID **)&SetupData );
	    	DEBUG((EFI_D_LOAD,"\n AliConfig_CallBack AllocatePool SetupData Status:%r \n",Status));
	    	Status = HiiLibGetBrowserData(&SetupDataSize, SetupData, &gSetupGuid, L"Setup");
	    	DEBUG((EFI_D_LOAD,"\n AliConfig_CallBack HiiLibGetBrowserData SetupData Status:%r \n",Status));
	    	Status = gBS->AllocatePool(
	    		    					EfiBootServicesData,
	    		    					SocketManagementConfigSize,
	    		    					(VOID **)&SocketManagementConfig );
	    	DEBUG((EFI_D_LOAD,"\n AliConfig_CallBack AllocatePool SocketManagementConfig Status:%r \n",Status));
	    	Status = HiiLibGetBrowserData(&SocketManagementConfigSize, SocketManagementConfig, &gEfiSocketPowermanagementVarGuid, L"SocketPowerManagementConfig");
	    	DEBUG((EFI_D_LOAD,"\n AliConfig_CallBack HiiLibGetBrowserData SocketManagementConfig Status:%r \n",Status));
	    	if(SetupData->AliConfig == 0x00)//default
	    	{
	    		//FxnOemTseVarData->PowerState = 0x00;
	    		SetupData->LegacyPriorities[0] = 0;//Bios HDD
	    		SetupData->LegacyPriorities[1] = 1;//bios PXE
	    		SetupData->UefiPriorities[0] = 0;//UEFI Bios HDD
	    		SetupData->UefiPriorities[1] = 1;//UEFI bios PXE
	    		SocketManagementConfig->PowerState = 1;//Power Off
	    		
	    	}
	    	if(SetupData->AliConfig == 0x01)//uc
	    	{
	    		//FxnOemTseVarData->PowerState = 0x01;
	    		SetupData->LegacyPriorities[0] = 1;//Bios pxe
	    		SetupData->LegacyPriorities[1] = 0;//bios HDD
	    		SetupData->UefiPriorities[0] = 1; //UEFI pxe
	    		SetupData->UefiPriorities[1] = 0;  //UEFI HDD
	    		SocketManagementConfig->PowerState = 2;//Last State
	    	}
	    	//Status = HiiLibSetBrowserData(FxnOemTseVarDataSize, FxnOemTseVarData, &gAmiTseOemTSEVarGuid, L"OemTSEVar");
	    	//pBS->FreePool(FxnOemTseVarData);
	    	Status = HiiLibSetBrowserData(SetupDataSize, SetupData, &gSetupGuid, L"Setup");
	    	pBS->FreePool(SetupData);
	    	Status = HiiLibSetBrowserData(SocketManagementConfigSize, SocketManagementConfig, &gEfiSocketPowermanagementVarGuid, L"SocketPowerManagementConfig");
	    	pBS->FreePool(SocketManagementConfig);
	    }
	    
	    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
	            return EFI_UNSUPPORTED;
	return Status;
}
