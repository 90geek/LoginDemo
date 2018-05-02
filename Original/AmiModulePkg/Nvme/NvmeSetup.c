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
    SETUP_DATA                          *SetupData;
    EFI_GUID                            SetupGuid = SETUP_GUID;
    UINTN                               SetupSize = sizeof(SETUP_DATA);
    UINT32                              Attribute =0;

    
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
        
        for (Index = 0; Index < HandleCount; Index++) {
            
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
                
                for (IndexOpenInfo = 0; IndexOpenInfo < OpenInfoCount; IndexOpenInfo++) {
                    
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
    }

    return;
}

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
