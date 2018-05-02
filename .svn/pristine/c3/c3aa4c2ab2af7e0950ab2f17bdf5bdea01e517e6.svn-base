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
/** @file
  Header file that defines AmiFlashUpdateCallback protocol interface.
  
  AmiFlashUpdateCallback protocol can be used to register callback on update of the specified ROM area.
  The protocol is intended to notify about events such as firmware update when entire ROM area is updated.
  It does not provide notifications about individual flash programming operations.
  AmiFlashUpdateCallback protocol is produced by a driver that publishes AmiFlash protocol.
  The driver detects flash area update events by monitoring sequence of AmiFlash protocol calls.
  Flash area update detection is based on the following assumptions:
  - Flash area update is performed from lower addresses to higher addresses.
  - Flash area is updated with either a single AmiFlash->Update call that spans entire area 
    or a sequence of calls: AmiFlash->DeviceWriteEnable, ..<any other flash protocol functions>.. , AmiFlash->DeviceWriteDisable

  The protocol issues notification callback when update of a ROM area is about to start (BeforeUpdate callback)
  and when update of the area has been completed(AfterUpdate callback).
  There is also a special ReleaseResources callback that is issued to give callback routine a chance to release
  resources allocated in the BeforeUpdate callback.
  
  In many cases ROM area update is part of a larger firmware update transaction.
  If flash driver detects AmiFlash protocol usage that suggests that location or size of the area 
  handled by the callback has changed or the area does not exist in the firmware image being programmed,
  processing of the active callback is terminated.
  Callback is considered active in the time span between BeforeUpdate and AfterUpdate notifications.
  Callback termination involves the following steps:
  - Callback is marked as inactive (which means AfterUpdate callback will not be issued).
  - If callback provided a buffer (see below), buffer content if programmed into a flash device.
  - ReleaseResources callback is issued.
  
  An active callback is terminated is the following cases:
  - A flash update request spans beyond area boundary
    ( FlashAddress >= Area->Address && FlashAddress < Area->Address + Area->Size && FlashAddress + Size > Area->Address + Area->Size )
  - An area is a firmware volume, FlashAddress is equal to the Area->Address, and Size of the DataBuffer is smaller than then the FV header size.
  - An area is a firmware volume(FV), FlashAddress is equal to the Area->Address, and content of the DataBuffer is either 
     not a valid FV header or a header of an FV with a size different from the area size (Fv->FvLength != Area->Size).
  - Callback is uninstalled using AmiFlashUpdate->Unregister call
  
  Callback function may take over the update process by providing a Buffer in the BeforeUpdate callback.
  The Buffer size must be equal to the size of the updated area (Area->Size).
  When buffer is provided, the flash update requests are redirected to the Buffer
  (The content of the DataBuffer passed into AmiFlash protocol calls is copied into a callback provided buffer and 
   is not propagated to a flash device).
  The buffer content is programmed into a flash device when flash update area is completed.
  It can be done either by the callback routine using the AmiFlash protocol or by the Flash driver
  (See ::AMI_FLASH_UPDATE_CALLBACK_ROUTINE description for more details).
  __NOTE: Flash Update Callback routine or a driver that owns the routine must not modify callback buffer between callback invocations.
  __NOTE: AmiFlash protocol calls issued by the callback routine go directly to a flash device. 
    They are not redirected into a callback Buffer. These calls are also not used by the flash driver to detect 
    area update or callback termination events.
**/

#ifndef __AMI_FLASH_UPDATE_CALLBACK_PROTOCOL__H__
#define __AMI_FLASH_UPDATE_CALLBACK_PROTOCOL__H__
#include<AmiRomLayout.h>

#define AMI_FLASH_UPDATE_CALLBACK_PROTOCOL_GUID \
    { 0x93e7608, 0xf56a, 0x42f2, { 0x8c, 0xc8, 0xd1, 0xd0, 0xe3, 0xe8, 0x2, 0x8 } }

#define AMI_SMM_FLASH_UPDATE_CALLBACK_PROTOCOL_GUID \
    { 0xa1ad291a, 0xbe08, 0x4831, { 0xb5, 0x4a, 0xb, 0x69, 0x91, 0x78, 0x53, 0xdb } }

typedef struct _AMI_FLASH_UPDATE_CALLBACK_PROTOCOL AMI_FLASH_UPDATE_CALLBACK_PROTOCOL;

typedef enum {
	/// A callback with this update phase value is triggered by the AmiFlash->Erase or AmiFlash->Update 
	/// call with the FlashAddress equal to Area->Address.
	/// It signifies that the ROM Area is about to be updated.
    AmiFlashUpdatePhaseBeforeUpdate,
	/// This update phase is triggered by the AmiFlash->Write or AmiFlash->Update 
	/// call when last byte of the address range being updated is the last byte of the area
	/// (FlashAddress+Size == Area->Address + Area->Size).
	/// The update phase is also triggered by AmiFlash->DeviceWriteDisable when pending
	/// update operation is in progress (when there are active callbacks in the queue).
	/// This value signifies that update of the ROM Area is completed.
    AmiFlashUpdatePhaseAfterUpdate,
    /// This update phase is used to release resources allocated by the callback function.
    /// It's invoked after the AfterUpdate callback or instead of AfterUpdate callback when active callback is terminated.
    AmiFlashUpdatePhaseReleaseResources
} AMI_FLASH_UPDATE_PHASE;

/**
  Flash update callback function.
  The function is invoked before and after area update.
  
  @param UpdatePhase Update phase. One of the values defined by the ::AMI_FLASH_UPDATE_PHASE type.
  @param Context 	 Context pointer provided during callback registration.
  @param Area 		 Flash area being updated.
  @param Buffer 	 Optional buffer. Handling of this parameter differs depending on UpdataPhase.
          - During the BeforeUpdate callback, Buffer is an optional output parameter. If Buffer is provided, 
            it will be used to redirect subsequent flash area update requests.
            The Buffer is ignored when callback returns an error.
          - During the BeforeUpdate callback, Buffer is an input/output parameter.
            When flash driver invokes the callback, it passes buffer address provided in the BeforeUpdate callback.
            Callback can leave the Buffer unmodified or modify the buffer (including setting it to NULL).
            - If callback returns an error, flash driver propagates the error to the caller of the AmiFlash function that triggered the callback.
            - If callback returns EFI_SUCCESS and buffer value is not NULL, flash driver programms Buffer content into a flash device.
            - If callback returns EFI_SUCCESS and buffer value is NULL, flash driver assumes that Buffer content has been programmed 
              into a flash device by the callback and no additional processing is requried.
          - During the ReleaseResources callback, Buffer is an input parater. 
            When flash driver invokes the callback, it passes buffer address provided in the AfterUpdate callback.
  @return EFI_STATUS
**/ 
typedef EFI_STATUS (EFIAPI *AMI_FLASH_UPDATE_CALLBACK_ROUTINE)(
    IN UINTN UpdatePhase, IN VOID *Context, IN AMI_ROM_AREA *Area, IN OUT VOID **Buffer
);

/** Register flash area update callback.
 @param This       AmiFlashCallback protocol instance
 @param Area       Area to associate callback with.  Callback is invoked when the area is updated. 
                   Use AmiRomLayoutLib to get Area pointer.
 @param Callback   Callback function.
 @param Context    A pointer that will be passed to the Callback function.
 
 @retval EFI_SUCCESS           Callback has been successfully registered.
 @retval EFI_ALREADY_STARTED   The Area already has a callback.
 @retval EFI_NOT_FOUND		   Area is not found in the ROM map.
 @retval EFI_INVALID_PARAMETER This, Area, or Callback is NULL.
 @retval EFI_OUT_OF_RESOURCES  Not enough resources to register the callback.
**/
typedef EFI_STATUS (EFIAPI *AMI_FLASH_UPDATE_CALLBACK_REGISTER)(
    IN AMI_FLASH_UPDATE_CALLBACK_PROTOCOL *This, IN AMI_ROM_AREA *Area, 
    IN AMI_FLASH_UPDATE_CALLBACK_ROUTINE Callback, IN VOID *Context OPTIONAL
);

/** Unregister flash area update callback.
 @param This       AmiFlashCallback protocol instance
 @param Area       Area the callback is associated with.
 @param Callback   Callback function.
 
 @retval EFI_SUCCESS           Callback has been successfully unregistered.
 @retval EFI_NOT_FOUND		   Area is not found in the ROM map, or Callback is not assosiated with the Area.
 @retval EFI_INVALID_PARAMETER This, Area, or Callback is NULL
**/
typedef EFI_STATUS (EFIAPI *AMI_FLASH_UPDATE_CALLBACK_UNREGISTER)(
    IN AMI_FLASH_UPDATE_CALLBACK_PROTOCOL *This, IN AMI_ROM_AREA *Area, 
    IN AMI_FLASH_UPDATE_CALLBACK_ROUTINE Callback
);

struct _AMI_FLASH_UPDATE_CALLBACK_PROTOCOL {
    AMI_FLASH_UPDATE_CALLBACK_REGISTER Register; ///< register callback
    AMI_FLASH_UPDATE_CALLBACK_UNREGISTER Unregister; ///< unregister callback
};

extern EFI_GUID gAmiFlashUpdateCallbackProtocolGuid;
extern EFI_GUID gAmiSmmFlashUpdateCallbackProtocolGuid;

#endif
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
