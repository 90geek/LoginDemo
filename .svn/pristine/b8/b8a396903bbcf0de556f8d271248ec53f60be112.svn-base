//**********************************************************************
//**********************************************************************
//**                                                                  **
//**     (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                  **
//**                    All Rights Reserved.                       	  **
//**                                                                  **
//**    5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093          **
//**                                                                  **
//**                    Phone: (770)-246-8600                         **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file ErrorDisplayFramework.c
    Contains code that will Display Error Messages that correspond to the 
    errors that are detected in the system.  The Error Display Module will 
    search for logged error codes and the turns them into messages and 
    displays them.  It has porting hooks that allow the OEM to provide any 
    specific functionality.  The messages will be displayed all at once, not as they 
    happen.  The individual messages will be displayed in the order that they 
    are are found in the Data hub.  
    The OEM can provide a module that can plug into this module.  They can 
    Added new errors to display, add new methods to display messages, along
    with adding any customized functionality that needs to happen before or
    after error messages are displayed

**/
//**********************************************************************
#include "Uefi.h"
#include <Efi.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include "Protocol/ErrorDisplayFrameworkProtocol.h"
#include <Protocol/DataHub.h>
#include <Protocol/AMIPostMgr.h>
#include <Protocol/HiiString.h>
#include <Protocol/SimpleTextOut.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/DevicePath.h>
#include <ErrorDisplayFrameworkStrDefs.h>
#include "ErrorDisplayFrameworkPlugins.h"
#include <Token.h>
#include <Library/BaseMemoryLib.h>


//=========================================================================
// GUID definitions

/// Local Definition of the Status Code GUID
#ifndef EFI_STATUS_CODE_GUID
    #define EFI_STATUS_CODE_GUID \
      {0xd083e94c, 0x6560, 0x42e4, 0xb6, 0xd4, 0x2d, 0xf7, 0x5a, 0xdf, 0x6a, 0x2a}
#endif

/// added extern to be able to use the AMI Post Manager GUID for display purposes
extern EFI_GUID	gAmiPostManagerProtocolGuid;


//=========================================================================
// global Variables
EFI_HII_HANDLE      HiiHandle; ///< handle used to load and get strings out of the Hii Database
AMI_POST_MANAGER_PROTOCOL *AmiPostMgr=NULL; ///< Pointer to load the pointer to the AMI Post Manager Protocol.  It is used to display strings on the screen

/// Variable that contains the string that displays a new line on the screen
UINT16  NewLine[] = L"\n\r";

/// Variable that contains the string that displays a empty Character on the screen
UINT16  EmptyString[] = L"";

/// Zero terminated array that contains the list of elinked error structures that can be displayed on the sceeen
ERROR_CODE_LOOKUP_STRUCT   ErrorCodeTable[] = {
    ERROR_LOOKUP_TABLE_PLUGINS 
    {0,0,0,0}
    };                                                                                                                                
                                                                                                                             
/// Calculates total size of the table                                                                                                                                      
UINT32 OemErrorLookUpTableMaxEntry = sizeof(ErrorCodeTable)/sizeof(ERROR_CODE_LOOKUP_STRUCT);                                       


//=======================================================================
// Function Prototypes
EFI_STATUS LookupOemErrorCode( IN UINT32 StatusErrorCode, OUT ERROR_CODE_LOOKUP_STRUCT **Entry);

EFI_STATUS EFIAPI AnyErrorsToDisplay ( 
          IN EFI_ERROR_DISPLAY_PROTOCOL   *This
          );

EFI_STATUS EFIAPI ErrorDisplay(
        IN EFI_ERROR_DISPLAY_PROTOCOL   *This, 
        OUT UINT32                       *Flags
        );


//==================================================================
// Protocol Definitions

/// This is the local structure variable for the EFI_ERROR_DISPLAY_PROTOCOL
EFI_ERROR_DISPLAY_PROTOCOL gErrorDisplay = {
  AnyErrorsToDisplay,
  ErrorDisplay
  };


//============================================================================
// Type definitions
/// Function typedefs for the DISPLAY_ERROR_FUNCTION Elink
typedef EFI_STATUS (DISPLAY_ERROR_FUNCTION) ( IN ERROR_CODE_LOOKUP_STRUCT *Entry, UINT32 *Flags );
/// Function typedefs for the OEM_PRE_DISPLAY_FUNCTION elink
typedef VOID (OEM_PRE_DISPLAY_FUNCTION) ( VOID );
/// Function typedefs for the OEM_POST_DISPLAY_FUNCTION elink
typedef VOID (OEM_POST_DISPLAY_FUNCTION) ( IN UINT32 Flags );


//=============================================================================
// elink function lists
extern DISPLAY_ERROR_FUNCTION DisplayErrorFunction EndOfDisplayErrorList;
extern OEM_PRE_DISPLAY_FUNCTION OemPreDisplayFunction EndOfPreDisplayList;
extern OEM_POST_DISPLAY_FUNCTION OemPostDisplayFunction EndOfPostDisplayList;

/// Array of eLinked functions for DisplayErrorFunction
DISPLAY_ERROR_FUNCTION* DisplayErrorFunctionList[] = {DisplayErrorFunction NULL};

/// Array of eLinked functions for OemPreDisplayFunction
OEM_PRE_DISPLAY_FUNCTION* OemPreDisplayFunctionList[] = {OemPreDisplayFunction NULL};
/// Array of eLinked functions for OemPostDisplayFunction
OEM_POST_DISPLAY_FUNCTION* OemPostDisplayFunctionList[] = {OemPostDisplayFunction NULL};


//=============================================================================
// Function Definitions
/**
    This function calls all functions linked into the OemPreDisplayFunction eLINK.
    It is called before any errors are displayed to the screen.  If any OEMs require 
    any special functionality before error messages are displayed, They should write 
    a function that links into the OemPreDisplayFunction eLINK
           
    @retval VOID
*/
VOID Oem_PreDisplayHook( VOID )
{
	UINTN i;

	for(i=0; OemPreDisplayFunctionList[i]; i++)
    {
        OemPreDisplayFunctionList[i]();
    }
}


/**
    This function calls all functions linked into the OemPostDisplayFunction eLINK.
    It is called after all errors are displayed to the screen.  If any OEMs require 
    any special functionality after error messages are displayed, They should write 
    a function that links into the OemPostDisplayFunction eLINK
           
    @param Flags flags value for all the errors displayed
           
    @retval VOID
**/
VOID Oem_PostDisplayHook( IN UINT32 Flags )
{
	UINTN i;

	for(i=0; OemPostDisplayFunctionList[i]; i++)
    {
        OemPostDisplayFunctionList[i]( Flags );
    }
}

/**
    This function is called to display error message everytime an error found in 
    the data hub matches up to a error in the Error Table. This function calls the 
    list of functions defined by the DisplayErrorFunction eLINK.  If an OEM wants
    to have their own function to display messages based off of the errors that 
    they want reported, they need to write a function and link it into the 
    DisplayErrorFunction eLINK.

    @param Entry pointer to the entry in the table that matches the current error found in the Data Hub
    @param Flags current flags value for all the errors displayed so far

    @retval EFI_SUCCESS All eLink Functions returned successfully
 */
EFI_STATUS DisplayErrorHook( 
            IN ERROR_CODE_LOOKUP_STRUCT *Entry,
            OUT UINT32      *Flags)
{
    EFI_STATUS  Status = EFI_SUCCESS;
	UINTN i;

   
	for(i=0; DisplayErrorFunctionList[i]; i++)
    {
        Status = DisplayErrorFunctionList[i]( Entry, Flags );
    }

    Entry->AlreadyDisplayed = 1;

    return Status;
}

//=================================================================================
// helper functions

/**
    This function looks up the status code error in the ErrorCodeTable
           
    @param StatusErrorCode error that was found in the DataHub
    @param Entry pointer to the entry in the array that corresponds to the Status code passed in
           
    @retval EFI_SUCCESS error code found in table
    @retval EFI_NOT_FOUND error code found in table, but error was already displayed
    @retval EFI_INVALID_PARAMETER Error code was not found in the table
 */
EFI_STATUS LookupOemErrorCode(
                    IN UINT32 StatusErrorCode, 
                    OUT ERROR_CODE_LOOKUP_STRUCT **Entry
                    )
{
    UINT32  Idx = 0;

    do {
        if (ErrorCodeTable[Idx].StatusCode == StatusErrorCode)
        {
            if (!ErrorCodeTable[Idx].AlreadyDisplayed)
            {
                *Entry = &(ErrorCodeTable[Idx]);
                return EFI_SUCCESS;
            }
            else
            {
                return EFI_NOT_FOUND;
            }
        }
        Idx++;
    } while (Idx < OemErrorLookUpTableMaxEntry);

    return EFI_INVALID_PARAMETER;
}

/**
   Checks for device has installed the Simple Text In Protocol
   
   This function goes through all Simple Text In Protocols and determines if a
   non virtual device has installed it.  If so it returns EFI_SUCCESS otherwise
   it returns EFI_NOT_FOUND to indicate that no keyboard functionality is available
   
    @retval EFI_SUCCESS - a non virtual device has installed the Simple Text In Protocol
    @retval EFI_NOT_FOUND - The Simple Text In Protocol has not been installed by a non virtual device
 */
EFI_STATUS CheckForConInDevices(VOID)
{
	EFI_STATUS Status;
	UINTN Index;
	UINTN HandleCount;
	EFI_HANDLE *HandleBuffer;
	EFI_DEVICE_PATH_PROTOCOL *DevPath;
	
	// check for handles that have simpleTextIn installed on them
	Status = pBS->LocateHandleBuffer(ByProtocol, &gEfiSimpleTextInProtocolGuid,
									  NULL,
									  &HandleCount,
									  &HandleBuffer);
	if (EFI_ERROR(Status))
	{
		return EFI_NOT_FOUND;
	}
	
	// make sure it is not a virtual device, check for a device path
	for (Index = 0; Index < HandleCount; Index++)
	{
//		HandleBuffer[Index] is the current device 
		Status = pBS->HandleProtocol(HandleBuffer[Index], &gEfiDevicePathProtocolGuid, &DevPath);
		if (Status == EFI_SUCCESS)
		{	// device with device path is found, return EFI_SUCCESS
			return EFI_SUCCESS;
		}
	}
	return EFI_NOT_FOUND;
}

//===================================================================================
// Protocol Functions
/** 
 * This function provides the wait for key press/pause functionality
 * 
 * This function checks for input devices and then chooses to either pause
 * the system or wait for a key press.
 * 
 */
VOID ErrorDisplayFramework_WaitForKey(VOID)
{
    CHAR16 *PressToContinueString = L"\n \n Press Any Key to Continue\n \n";
    CHAR16 *PauseString = L"\n \n Pausing for review of errors\n \n";
    EFI_INPUT_KEY KeyData;
    EFI_STATUS Status;

    TRACE((-1,"ErrorDisplayFramework: WaitForKey ConIn Device Check\n\r"));
    Status = CheckForConInDevices();
    if (!EFI_ERROR(Status))
    {
    	TRACE((-1,"Con In device Found wait for key\n\r"));

    	do {
			Status = pST->ConIn->ReadKeyStroke(pST->ConIn, &KeyData);
		} while(Status !=  EFI_NOT_READY);
	
	
		// display Prompt
		AmiPostMgr->DisplayPostMessage(PressToContinueString);
	
		do {
			Status = pST->ConIn->ReadKeyStroke(pST->ConIn, &KeyData);
		} while(Status !=  EFI_SUCCESS);
    }
    else
    {
    	TRACE((-1,"ErrorDisplayFramework: WaitForKey Pause here\n\r"));
		// display Prompt
		AmiPostMgr->DisplayPostMessage(PauseString);

    	// Pause here for three seconds for the customer to see
		pBS->Stall( PAUSE_DELAY_TIME);
    }
}


/**
    This function is the default function provided to display the correct POST 
    error message if an error is detected in the system.  This function can be 
    turned off by token if a customer wants to provide their own message Display 
    routine.  Their routine would need to eLink into the OemDisplayErrorFunction
    Parent eLink.  To turn off this function's eLink, use ENABLE_DEFAULT_DISPLAY_ERROR_FUNCTION

           
    @param CurrentEntry pointer to the current entry in the ErrorCodeTable that should be displayed
    @param Flags current flags value for all the errors displayed so far

    @retval 
        Status returns the value returned from HiiLibGetString

**/
EFI_STATUS DisplayMessage(
            IN ERROR_CODE_LOOKUP_STRUCT *CurrentEntry,
            OUT UINT32      *Flags
            )
{
    EFI_STATUS  Status;
    UINTN   Size = 0;
    UINT16  *String = NULL;


    Status = HiiLibGetString(HiiHandle, 
                             CurrentEntry->ErrorStringToken,
                             &Size,
                             String);

    if (Status == EFI_BUFFER_TOO_SMALL)
    {
        pBS->AllocatePool(EfiBootServicesData, sizeof(CHAR16) * (Size + 1), (VOID **)&String);
        Status = HiiLibGetString(HiiHandle,
                                 CurrentEntry->ErrorStringToken,
                                 &Size,
                                 String);
    }


    // only display error if String was found
    if (!EFI_ERROR(Status))
    {
        AmiPostMgr->DisplayPostMessage(String);
    
        // cause empty line to be displayed
        AmiPostMgr->DisplayPostMessage(NewLine); 

        // return Flags value assigned to the error, do not overwrite previous flags
        *Flags |= CurrentEntry->Flags;
    }

    pBS->FreePool(String);

    return Status;
}


/**
    This function determines if there are any errors that need to be displayed 
    and returns a value to indicate it

           
    @param This Pointer to the protocol

           
    @retval EFI_SUCCESS An error that needs to be displayed has been found
    @retval EFI_NOT_FOUND No errors to display

**/
EFI_STATUS 
EFIAPI
AnyErrorsToDisplay ( 
            IN EFI_ERROR_DISPLAY_PROTOCOL   *This
           )
{
    EFI_STATUS                          Status;
    EFI_DATA_HUB_PROTOCOL               *DataHub;
    EFI_DATA_RECORD_HEADER              *Record;
    DATA_HUB_STATUS_CODE_DATA_RECORD    *pRecord;
    UINT64                              LocalLogCount = 0;
    EFI_STATUS                          OemStatus;
    ERROR_CODE_LOOKUP_STRUCT               *CurrentEntry = NULL; 


    Status = pBS->LocateProtocol (&gEfiDataHubProtocolGuid, NULL, (VOID **)&DataHub);
    if (EFI_ERROR(Status))
        ASSERT_EFI_ERROR (Status);

    Record = NULL;
    // Search DataHub
    do {
	        Status = DataHub->GetNextRecord (DataHub, &LocalLogCount, NULL, &Record);
        if ((!EFI_ERROR(Status)) 
            && (CompareGuid (&Record->DataRecordGuid, &gEfiDataHubStatusCodeRecordGuid))
            && (Record->DataRecordClass == EFI_ERROR_CODE) )
        {
            pRecord = ( DATA_HUB_STATUS_CODE_DATA_RECORD *) (Record+1);
            // see if the error is in the Array.  The NULL value is to indicate
            OemStatus = LookupOemErrorCode(pRecord->Value, &CurrentEntry);
            if (!(EFI_ERROR(OemStatus)))
            {
                return EFI_SUCCESS;
            }
        }
    } while (!EFI_ERROR(Status) && (LocalLogCount != 0));

    return EFI_NOT_FOUND;
}


/**
    This function handles the control flow.  
    1) calls the PreDisplay elinked function
    2) finds all the protocols needed to find the errors
    3) moves cursor to an empty line
    4) Searches through the data hub and calls the DisplayErrorHook eLINK so 
    that everything that needs to be done for the error is done.
    5) Call the PostDisplayHooks
    6) Beeps to inform the user an error has been found if the token to 
    enable beep is turned on

           
    @param This Pointer to the protocol
    @param Flags return values based on the errors found

    @retval 
        EFI_SUCCESS 

**/
EFI_STATUS 
EFIAPI
ErrorDisplay(
        IN EFI_ERROR_DISPLAY_PROTOCOL   *This, 
        OUT UINT32                      *Flags
        )
{
    EFI_STATUS                          Status;
    EFI_DATA_HUB_PROTOCOL               *DataHub;
    EFI_DATA_RECORD_HEADER              *Record;
    DATA_HUB_STATUS_CODE_DATA_RECORD    *pRecord;
    UINT64                              LocalLogCount = 0;

    EFI_STATUS                          OemStatus;
    ERROR_CODE_LOOKUP_STRUCT            *CurrentEntry = NULL; 
    UINT32                              ErrorCount = 0;

    Oem_PreDisplayHook();

    // locate the protocol for access to the Datahub
    Status = pBS->LocateProtocol (&gEfiDataHubProtocolGuid, NULL, (VOID **)&DataHub);
    if (EFI_ERROR(Status))
        ASSERT_EFI_ERROR (Status);

    // guarantee that the error messages start on a new line and Column 0
    AmiPostMgr->DisplayPostMessage(EmptyString); 

    Record = NULL;
    // Search DataHub
    do {
	        Status = DataHub->GetNextRecord (DataHub, &LocalLogCount, NULL, &Record);
        if ((!EFI_ERROR(Status)) 
            && (CompareGuid (&Record->DataRecordGuid, &gEfiDataHubStatusCodeRecordGuid))
            && (Record->DataRecordClass == EFI_ERROR_CODE) )
        {
            pRecord = ( DATA_HUB_STATUS_CODE_DATA_RECORD *) (Record+1);
            OemStatus = LookupOemErrorCode(pRecord->Value, &CurrentEntry);
            if (!(EFI_ERROR(OemStatus)))
            {
                // display the message and return the Flag value stored in the Array for this entry,
                // Since the flags is passed into the function and returned.  The OEM
                //  could potentially program the Flags value with anything they want.
                DisplayErrorHook(CurrentEntry, Flags);

                // keep count of number of errors
                ErrorCount++;
            }
        }

    } while (!EFI_ERROR(Status) && (LocalLogCount != 0));

    Oem_PostDisplayHook(*Flags);

    // beep to indicate errors are to be displayed
    if ((ErrorCount) && (BEEP_FOR_ERROR == 1))
        LibReportStatusCode(EFI_PROGRESS_CODE, AMI_STATUS_CODE_BEEP_CLASS|1, 0, NULL, NULL);

#if defined (PAUSE_AFTER_ALL_ERRORS_DISPLAYED) &&(PAUSE_AFTER_ALL_ERRORS_DISPLAYED ==1)
    // provide wait for key functionality here
    ErrorDisplayFramework_WaitForKey();
#endif


	return EFI_SUCCESS;
}

/**
    This function is the entry point of the module.  It initializes the 
    library, loads the string database, and installs the protocol interface  
    If the USE_APTIO_DEFAULT_TRIGGER_EVENT token is enabled, a callback event
    is installed so that the system can check for and display errors that are 
    found.

           
    @param ImageHandle Handle for this driver's loaded image protocol.
    @param SystemTable pointer to the EFI system table.

    @retval 
        Returns the value that is returned to it by InstallMultipleProtocolInterfaces

**/
EFI_STATUS 
EFIAPI
ErrorDisplayEntryPoint(
    IN EFI_HANDLE		ImageHandle,
    IN EFI_SYSTEM_TABLE	*SystemTable
    )
{
    EFI_STATUS          Status;
    
    InitAmiLib(ImageHandle, SystemTable);
    
    // TODO RSP - this is part of the compatibility package
    Status = LoadStrings( ImageHandle, &HiiHandle);
	if (EFI_ERROR(Status))
    {
        TRACE((-1,"ErrorDisplayFramework:ErrorDisplayEntryPoint Strings were not loaded\n\r"));
    }
    Status = pBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, (VOID **)&AmiPostMgr);
	if(EFI_ERROR(Status)) 
    {
        TRACE((-1,"ErrorDisplayFramework:ErrorDisplayEntryPoint AmiPostMgr protocol is not found\n"));
    }
		
    // Now install the Error Display Protocol
    // initiaize the ImageHandle and DriverBindingHandle
    return pBS->InstallMultipleProtocolInterfaces(  &ImageHandle,
                                                    &gAmiErrorDisplayFrameworkProtocolGuid, &gErrorDisplay,
                                                    NULL);
}




//**********************************************************************
//**********************************************************************
//**                                                                  **
//**     (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                  **
//**                    All Rights Reserved.                       	  **
//**                                                                  **
//**    5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093          **
//**                                                                  **
//**                    Phone: (770)-246-8600                         **
//**                                                                  **
//**********************************************************************
//**********************************************************************
