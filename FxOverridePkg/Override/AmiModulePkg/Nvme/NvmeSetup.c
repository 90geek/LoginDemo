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

/** @file NvmeSetup.c
    Display the Nvme Controller and device information in the Setup

**/

//---------------------------------------------------------------------------

#include <Setup.h>
#include "NvmeIncludes.h"
#include "Nvme/NvmeBus.h"
#include "AmiProtocol.h"
#include "AmiLib.h"

//---------------------------------------------------------------------------

#define     MSG_NVME_DP     23
#define     DRIVEMAXCOUNT   4

extern EFI_RUNTIME_SERVICES     *pRS;

typedef struct {
    STRING_REF  ControllerString;
    STRING_REF  DeviceString;
} NVME_SETUP_STRUC;

NVME_SETUP_STRUC   NVMeSetupStruc[] = {
    {STRING_TOKEN(STR_NVME0_CONTROLLER), STRING_TOKEN(STR_NVME0_NAME)},
    {STRING_TOKEN(STR_NVME1_CONTROLLER), STRING_TOKEN(STR_NVME1_NAME)},
    {STRING_TOKEN(STR_NVME2_CONTROLLER), STRING_TOKEN(STR_NVME2_NAME)},
    {STRING_TOKEN(STR_NVME3_CONTROLLER), STRING_TOKEN(STR_NVME3_NAME)},
};

//TH0182>>>
UINT8
OemGetBoardID();

VOID
lpc_read (
  IN	UINT32 ulAddress,
  OUT	UINT32  *Value);
//TH0182<<<

extern EFI_GUID gAmiNvmeControllerProtocolGuid;

/**
    This function initializes the SB related setup option values

    @param HiiHandle -- Handle to HII database
    @param Class     -- Indicates the setup class

    @retval VOID

**/
VOID
InitNvmeStrings (
    IN  EFI_HII_HANDLE  HiiHandle, 
    IN  UINT16          Class
)
{

    EFI_STATUS                          Status;
    UINTN                               Index;
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    UINTN                               HandleCountPciIo;
    EFI_HANDLE                          *HandleBufferPciIo;
    EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL            *DevicePathNode;
    EFI_PCI_IO_PROTOCOL                 *PciIO;
    AMI_NVME_CONTROLLER_PROTOCOL    	*NvmeController = NULL;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               IndexPciIo;
    UINTN                               IndexOpenInfo;
    EFI_HANDLE                          DeviceHandle;
    EFI_HANDLE                          ControllerHandle;
    EFI_HANDLE                          DriverBindingHandle;
    EFI_COMPONENT_NAME2_PROTOCOL        *ComponentName2Protocol;
    CHAR16                              *DriveNameUni;
    UINTN                               SegmentNumber;
    UINTN                               BusNumber;
    UINTN                               DeviceNumber;
    UINTN                               FunctionNumber;
    UINT8                               DrivePresence[DRIVEMAXCOUNT] = {0};
    UINT8                               DriveIndex = 0;
/* TH0182
    SETUP_DATA                          *SetupData;
    EFI_GUID                            SetupGuid = SETUP_GUID;
    UINTN                               SetupSize = sizeof(SETUP_DATA);
    UINT32                              Attribute =0;
TH0182 */
//TH0182>>>    
    SETUP_SHOW_NVME_FEATURES		SetupShowNvmeFeatures;
	EFI_GUID 						SetupShowNvmeFeaturesGuid = SETUP_SHOW_NVME_FEATURES_GUID;	
	UINT8							BoardID;
//TH0182<<<

    
    if (Class == ADVANCED_FORM_SET_CLASS) { 
        // Collect all DevicePath protocol and check for NVMe Controller
        Status = gBS->LocateHandleBuffer(
                      ByProtocol,
                      &gEfiDevicePathProtocolGuid,
                      NULL,
                      &HandleCount,
                      &HandleBuffer
                     );
        
        if (EFI_ERROR(Status)) return;
        
//ZYY006015-        for (Index = 0; Index < HandleCount; Index++) {
        for (Index = 0; (Index < HandleCount) && (DriveIndex < DRIVEMAXCOUNT); Index++) {  //ZYY006015+
            
            Status = gBS->HandleProtocol(
                          HandleBuffer[Index],
                          &gEfiDevicePathProtocolGuid,
                          (VOID *)&DevicePath
                          );
            
             ASSERT_EFI_ERROR(Status);
             if(EFI_ERROR(Status)) {
                 continue;
             }
             
             DevicePathNode = DevicePath;
             while (!isEndNode (DevicePathNode)) {
                 if ((DevicePathNode->Type == MESSAGING_DEVICE_PATH) &&
                         (DevicePathNode->SubType == MSG_NVME_DP)) {
                     break;
                 }

                 DevicePathNode = NEXT_NODE(DevicePathNode);
            }
             
            if (DevicePathNode == NULL || isEndNode (DevicePathNode)) {
                continue;
            }
            
            // NVMe Device Handle is found.
            DeviceHandle = HandleBuffer[Index];
            
            // NVMe device is found. Now get the CONTROLLER. Check all the PCIio handles.
            Status = gBS->LocateHandleBuffer(
                         ByProtocol,
                         &gEfiPciIoProtocolGuid,
                         NULL,
                         &HandleCountPciIo,
                         &HandleBufferPciIo
                         );
            
            for (IndexPciIo = 0; IndexPciIo < HandleCountPciIo; IndexPciIo++) {
                Status = gBS->HandleProtocol(
                              HandleBufferPciIo[IndexPciIo],
                              &gEfiPciIoProtocolGuid,
                              (VOID *)&PciIO
                              );
                        
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) {
                    continue;
                }
                
                Status = gBS->HandleProtocol(
                              HandleBufferPciIo[IndexPciIo],
                              &gAmiNvmeControllerProtocolGuid,
                              (VOID *)&NvmeController
                              );
                
                // If Ami Nvme Controller Protocol not found on the Controller handle ( PciIo handle)
                // do not process the Pci Io Handle
                if(EFI_ERROR(Status)) {
                    continue;
                }
                
                OpenInfoCount = 0;
                Status = gBS->OpenProtocolInformation(
                              HandleBufferPciIo[IndexPciIo],
                              &gEfiPciIoProtocolGuid,
                              &OpenInfo,
                              &OpenInfoCount
                              );
                
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) {
                    continue;
                }                
                
//ZYY006015-                for (IndexOpenInfo = 0; IndexOpenInfo < OpenInfoCount; IndexOpenInfo++) {
                for (IndexOpenInfo = 0; (IndexOpenInfo < OpenInfoCount)&& (DriveIndex < DRIVEMAXCOUNT); IndexOpenInfo++) { //ZYY006015+
                    
                    //Check if the handle is opened BY_CHILD and also compare the device handle.
                    if ((OpenInfo[IndexOpenInfo].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) &&
                            (OpenInfo[IndexOpenInfo].ControllerHandle == DeviceHandle)){
                    
                        DriverBindingHandle = OpenInfo[IndexOpenInfo].AgentHandle;
                        // Get the handle for the Controller
                        ControllerHandle = HandleBufferPciIo[IndexPciIo]; 
                        
                        // Now PCI controller and DriverBinding handle is found. Get the Component2Protocol now.
                        Status = gBS->HandleProtocol(
                                      DriverBindingHandle,
                                      &gEfiComponentName2ProtocolGuid,
                                      (VOID *)&ComponentName2Protocol
                                      );
                        
                        ASSERT_EFI_ERROR(Status);
                        if(EFI_ERROR(Status)) {
                            continue;
                        }     
                        
                        Status = ComponentName2Protocol->GetControllerName (
                                                         ComponentName2Protocol,
                                                         ControllerHandle,
                                                         DeviceHandle,
                                                         LANGUAGE_CODE_ENGLISH,
                                                         &DriveNameUni
                                                         );
                        
                        ASSERT_EFI_ERROR(Status);
                        if(EFI_ERROR(Status)) {
                            continue;
                        }     

                        InitString(
                                HiiHandle,
                                NVMeSetupStruc[DriveIndex].DeviceString,
                                L"%s", 
                                DriveNameUni
                                );
                                              
                         Status = PciIO->GetLocation (
                                         PciIO,
                                         &SegmentNumber,
                                         &BusNumber,
                                         &DeviceNumber,
                                         &FunctionNumber
                                         );                                              
          
                         InitString(
                                 HiiHandle,
                                 NVMeSetupStruc[DriveIndex].ControllerString,
                                 L"Bus:%X Dev:%x Func:%x",
                                 BusNumber, DeviceNumber, FunctionNumber
                                 );
                                              
                         //Enable the string to be displayed in setup
                         DrivePresence[DriveIndex] = 1;
                         DriveIndex++;
                    }
                }
                gBS->FreePool(OpenInfo);              
            }
            gBS->FreePool(HandleBufferPciIo);
        }

        gBS->FreePool(HandleBuffer);
 
/* TH0182       
        // Update setup data to show whether strings need to be displayed or not
        Status = gBS->AllocatePool(EfiBootServicesData, sizeof (SETUP_DATA),(VOID *) &SetupData);
        ASSERT_EFI_ERROR (Status);
    
        SetupSize = sizeof (SETUP_DATA);
        
        Status = pRS->GetVariable (
                      L"Setup",
                      &SetupGuid,
                      &Attribute,
                      &SetupSize,
                      SetupData
                      );

        if(!EFI_ERROR(Status)){
        
            for (DriveIndex = 0; DriveIndex < DRIVEMAXCOUNT; DriveIndex++){
                SetupData->ShowNVMeDrive[DriveIndex] = DrivePresence[DriveIndex];
            }
        
            Status = pRS->SetVariable (
                          L"Setup",
                          &SetupGuid,
                          Attribute,
                          sizeof (SETUP_DATA),
                          SetupData
                          );
            
            ASSERT_EFI_ERROR (Status);
            
        }
        gBS->FreePool(SetupData);
TH0182 */
//TH0182>>>
	//
	// Update setup data to show whether strings need to be displayed or not
	//
        
	// Show the Nvme configure item according to BoardID.
	BoardID = OemGetBoardID();
	switch(BoardID){
	case 0x00: // SKU-B
			SetupShowNvmeFeatures.ShowNVMeConfig = 0;
			break;
	case 0x03: // SKU-A
			SetupShowNvmeFeatures.ShowNVMeConfig = 1;
			break;
	//DJH002028++>>
	case 0x01: // SKU-C
			SetupShowNvmeFeatures.ShowNVMeConfig = 1;
			break;
	//DJH002028++<<
		default:
			SetupShowNvmeFeatures.ShowNVMeConfig = 0;
			break;
	}
	
	// Show the Nvme Drive
	for (DriveIndex = 0; DriveIndex < DRIVEMAXCOUNT; DriveIndex++){
		SetupShowNvmeFeatures.ShowNVMeDrive[DriveIndex] = DrivePresence[DriveIndex];
	}

	Status = pRS->SetVariable (
				  L"SetupShowNvmeFeatures",
				  &SetupShowNvmeFeaturesGuid,
				  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
				  sizeof (SETUP_SHOW_NVME_FEATURES),
				  &SetupShowNvmeFeatures
				  );
	
	ASSERT_EFI_ERROR (Status);            
//TH0182<<<
    }

    return;
}

//TH0182>>>
UINT8
OemGetBoardID()
{
	UINT32		Address;
	UINT32		Value;
	UINT8       BoardIDNumber;

    Address = (UINT32)(0x1e780000 | 0x78);
    lpc_read (Address, &Value);
	
    BoardIDNumber = (UINT8)(Value & (BIT0 | BIT1));
    
    return	BoardIDNumber;

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
    jtemp = IoRead8 (AST2400_CONFIG_DATA);
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
//TH0182<<<

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
