//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file EfiUsbHid.c
    EFI USB HID device Driver

**/

#include "AmiDef.h"
#include "UsbDef.h"
#include "Uhcd.h"
#include "EfiUsbKb.h"
#include "UsbKbd.h"

#include "ComponentName.h"
#include "UsbBus.h" 

extern  USB_GLOBAL_DATA *gUsbData; 

#define AMI_HID_DEVICE_GUID \
	{0x1fede521, 0x31c, 0x4bc5, 0x80, 0x50, 0xf3, 0xd6, 0x16, 0x1e, 0x2e, 0x92}

EFI_GUID gAmiHidDeviceGuid = AMI_HID_DEVICE_GUID;

/**
    USB EFI keyboard driver driver protocol function that
    returns the keyboard controller name.

**/

CHAR16*
UsbHidGetControllerName(
    EFI_HANDLE Controller,
    EFI_HANDLE Child
)
{
    return NULL;
}
 

/**
    HID EFI driver entry point

**/

EFI_STATUS
UsbHidInit(
    EFI_HANDLE  ImageHandle,
    EFI_HANDLE  ServiceHandle
)
{
    //EFI_STATUS        Status;
    static NAME_SERVICE_T Names;
    static EFI_DRIVER_BINDING_PROTOCOL Binding = {
        SupportedUSBHid,
        InstallUSBHid,
        UninstallUSBHid,
        USBKB_DRIVER_VERSION,
        NULL,
        NULL };

    Binding.DriverBindingHandle = ServiceHandle;
    Binding.ImageHandle = ImageHandle;

    InitUSBMouse(); 

    return gBS->InstallMultipleProtocolInterfaces(
        &Binding.DriverBindingHandle,
        &gEfiDriverBindingProtocolGuid, &Binding,
        &gEfiComponentName2ProtocolGuid, InitNamesProtocol(&Names,	//(EIP69250)
              L"USB Hid driver", UsbHidGetControllerName),
        NULL);
}
 
/**
    Verifies if usb hid support can be installed on a device

**/

EFI_STATUS
SupportedUSBHid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath)
{
    EFI_USB_INTERFACE_DESCRIPTOR    Desc;
    EFI_STATUS                      Status;
    EFI_USB_IO_PROTOCOL             *UsbIo;

    Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
        &UsbIo, This->DriverBindingHandle,
        Controller, EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    gBS->CloseProtocol ( Controller, &gEfiUsbIoProtocolGuid,
        This->DriverBindingHandle, Controller);

    Status = UsbIo->UsbGetInterfaceDescriptor(UsbIo, &Desc  );
    if(EFI_ERROR(Status))
        return EFI_UNSUPPORTED;

    if ( Desc.InterfaceClass == BASE_CLASS_HID)
    {
        return EFI_SUCCESS;
    } else {
        return EFI_UNSUPPORTED;
    }
} 

/**
    Installs SimpleTxtIn protocol on a given handle

    @param Controller - controller handle to install protocol on.

    @retval VOID

**/

EFI_STATUS
InstallUSBHid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
)
{
    EFI_STATUS              Status;
    EFI_USB_IO_PROTOCOL     *UsbIo;
	USBDEV_T* HidDev;
	HC_STRUC* HcData;
	UINT8 UsbStatus;
 
    USB_DEBUG(DEBUG_USBHC_LEVEL,
        "USB: InstallUSBHid: starting...\n");
    //
    // Open Protocols
    //
    Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
        &UsbIo, This->DriverBindingHandle,
        Controller, EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR(Status))
        return Status; 
	
	HidDev = UsbIo2Dev(UsbIo); 	
//Find DEV_INFO 
    ASSERT(HidDev);

    // Usb keyboard data may lost if users press key during POST. We need to prepare 
    // keyboard buffer before installing device driver.
	CreateKeyBuffer(&HidDev->dev_info->KeyCodeBuffer, MAX_KEY_ALLOWED, sizeof(UINT8));
	CreateKeyBuffer(&HidDev->dev_info->UsbKeyBuffer, MAX_KEY_ALLOWED, sizeof(USB_KEY));
    
    HcData = gUsbData->HcTable[HidDev->dev_info->bHCNumber - 1];
    UsbStatus = UsbSmiReConfigDevice(HcData, HidDev->dev_info); 
    if(UsbStatus != USB_SUCCESS) {
        USB_DEBUG(DEBUG_USBHC_LEVEL,
            "InstallUSBHid: failed to Reconfigure Hid: %d\n", UsbStatus );
		gBS->CloseProtocol (
			  Controller, &gEfiUsbIoProtocolGuid,
			  This->DriverBindingHandle, Controller);
        return EFI_DEVICE_ERROR;
    }

    Status = gBS->InstallMultipleProtocolInterfaces (&Controller,
                &gAmiHidDeviceGuid, NULL,
                NULL
                );
    
    if (HidDev->dev_info->HidDevType & HID_DEV_TYPE_KEYBOARD) {
	    InstallUsbKeyboard(This,Controller,DevicePath,HidDev->dev_info,UsbIo);
    } else {
        // Destroy keyboard buffer if it isn't a keyboard device.
        DestroyKeyBuffer(&HidDev->dev_info->UsbKeyBuffer);
        DestroyKeyBuffer(&HidDev->dev_info->KeyCodeBuffer);
    }

    if (HidDev->dev_info->HidDevType & (HID_DEV_TYPE_MOUSE | HID_DEV_TYPE_POINT)) {
        if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
    		if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_RELATIVE_DATA) {
      			InstallUSBMouse(Controller, UsbIo, HidDev->dev_info);
    		}
#if USB_DEV_POINT 
    		if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_ABSOLUTE_DATA) {
    			InstallUSBAbsMouse(Controller, HidDev->dev_info);
    		}
#endif
        } else {
            InstallUSBMouse(Controller, UsbIo, HidDev->dev_info);
        }
    }
    return Status;

} 

/**
    Uninstalls protocol on a given handle

    @param Controller - controller handle.

    @retval VOID

**/

EFI_STATUS
UninstallUSBHid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
)
{
	EFI_STATUS				Status;
	EFI_USB_IO_PROTOCOL 	*UsbIo;
	VOID					*Ptr;
	UINT8		UsbSatus;
	USBDEV_T*	HidDev;
	HC_STRUC*	HcData;
 
	USB_DEBUG(DEBUG_USBHC_LEVEL,
		"\n USB: UnInstallUSBHid: stoping...\n");

	Status = gBS->OpenProtocol ( Controller,  &gAmiHidDeviceGuid,
		&Ptr, This->DriverBindingHandle, Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL );

	if (EFI_ERROR(Status)) {
		return Status; 
	}
	//
	// Open Protocols
	//
	Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
		&UsbIo, This->DriverBindingHandle,
		Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL );
	if (EFI_ERROR(Status)) {
		return Status; 
	}

	HidDev = UsbIo2Dev(UsbIo);	
	HcData = gUsbData->HcTable[HidDev->dev_info->bHCNumber - 1];

	UsbSatus = UsbDevDriverDisconnect(HcData, HidDev->dev_info);
	ASSERT(UsbSatus == USB_SUCCESS);

	if(HidDev->dev_info->HidDevType & HID_DEV_TYPE_KEYBOARD) {
		UninstallUsbKeyboard(This,Controller,NumberOfChildren,Children);
	}

	if (HidDev->dev_info->HidDevType & (HID_DEV_TYPE_MOUSE | HID_DEV_TYPE_POINT)) {
        if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
    		if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_RELATIVE_DATA) {
    			UninstallUSBMouse(This, Controller, NumberOfChildren, Children);
    		}
#if USB_DEV_POINT 
    		if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_ABSOLUTE_DATA) {
    			UninstallUSBAbsMouse(Controller);
    		}
#endif
        } else {
            UninstallUSBMouse(This, Controller, NumberOfChildren, Children);
        }
	}
                                        //<(EIP84455+)
	Status = gBS->UninstallMultipleProtocolInterfaces ( Controller,
				&gAmiHidDeviceGuid, NULL, 
				NULL);

	if (EFI_ERROR(Status)) {
		return Status;
	}
	//Close usbio protocol
    Status = gBS->CloseProtocol ( Controller, &gEfiUsbIoProtocolGuid,
    			This->DriverBindingHandle, Controller); 

 	return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
