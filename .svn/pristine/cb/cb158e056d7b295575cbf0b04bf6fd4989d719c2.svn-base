//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file ErrorDisplayFramework.c
 * Contains code to trigger the Error Display Framework

 * Contains code for the default trigger function for the Error Display 
 *  Framework eModule.  This will be called after InitConVars in the BDS 
 *  Control Flow.  The Callback can be disabled by setting the token:
 *  USE_APTIO_DEFAULT_TRIGGER_EVENT to '0'.  If the user chooses to do this
 *  They must provide their own trigger to call the display of errors.
 *  One concern is a first boot condition when no ConIn devices are detected
 *  The system must execute after InitConVars
**/

#include <AmiDxeLib.h>
#include <Protocol\AMIPostMgr.h>
#include "Protocol\ErrorDisplayFrameworkProtocol.h"

/**
  This function is the default callback function that looks for errors registered
  in the system.  If any errors are found,  then the display is switched to the 
  text screen and the errors are displayed.

  @param IN EFI_EVENT Event - the event that triggered this function
  @param IN VOID *Context - context information registered with the function

  @retval None
*/
VOID ErrorDisplayCallbackEvent(IN EFI_EVENT Event, IN VOID *Context)
{
	EFI_STATUS Status;

	EFI_GUID PostMangerGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
	AMI_POST_MANAGER_PROTOCOL *PostManager = NULL;
	EFI_GUID ErrorDisplayGuid = EFI_ERROR_DISPLAY_FRAMEWORK_PROTOCOL_GUID;
	EFI_ERROR_DISPLAY_PROTOCOL *pErrorDisplay = NULL;

	UINT32 Flags = 0;

	TRACE((-1,"ErrorDisplayFrameworkCallback : ErrorDisplayCallbackEvent \n\r"));

	// Attempt to locate the Ami Post Manager Protocol
	Status = pBS->LocateProtocol(&PostMangerGuid, NULL, (VOID **)&PostManager);
	if(EFI_ERROR(Status)) return;

	Status = pBS->LocateProtocol(&ErrorDisplayGuid, NULL, (VOID **)&pErrorDisplay);
	if(EFI_ERROR(Status)) return;

	// Call the error display protocol to determine if any errors exist
	Status = pErrorDisplay->AnyErrorsToDisplay(pErrorDisplay);

	// If errors exist, call to display them
	if(!EFI_ERROR(Status))
	{
		// Ensure screen is in Verbose mode and then attempt to display errors
		PostManager->SwitchToPostScreen();

		pErrorDisplay->ErrorDisplay(pErrorDisplay, &Flags);
	}
}
    

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
