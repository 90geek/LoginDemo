//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2014, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/special.c $
//
// $Author: Premkumara $
//
// $Revision: 35 $
//
// $Date: 4/03/12 12:40a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Special.c
//
// Description:	This file contains code to handle special Operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include "special.h"  

#define BOOT_OPTION_SIZE sizeof(UINT16)

extern VOID UefiSetHelpField(VOID *IfrPtr,UINT16 Token);
EFI_STATUS GetFormSetTitleAndHelpWrapper (VOID *Handle, UINT16 *Title, UINT16 *Help);
extern BOOLEAN gSetupUpdated;//EIP:51619 Flag which represents the setup update
VOID _SpecialControlExtras(CONTROL_DATA *ctrlData);
VOID _SpecialFixupBootOrder( CONTROL_INFO *control , UINT16 value);
VOID _SpecialFixupLanguages( CONTROL_INFO *control );
VOID _SpecialFixupBBSOrder( CONTROL_INFO *control, UINT16 value );
VOID _SpecialFixupBBSCondition(UINT16 ControlIndex,CONTROL_INFO *control,UINT16 PrevControlQuestionID);
VOID _SpecialFixupBootCondition(UINT16 ControlIndex,CONTROL_INFO *control,UINT16 PrevControlQuestionID);

UINT32 FindVarFromITKQuestionId(UINT16 QuestionId);
VOID _SpecialFixupAddBootOption( CONTROL_INFO *control);
UINT16 GetNoVarStoreBootCountOffset();

UINT16 BBSGetNonStandardGroupType(UINT16 DeviceType);	//EIP-42520

#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
extern UINT16 OEMSpecialGetControlCount(CONTROL_INFO *controlInfo);
extern VOID OEMSpecialOneOfFixup( CONTROL_INFO *control , UINT16 value );
extern VOID OEMSpecialGotoFixup(CONTROL_INFO *control, UINT16 value );
#endif //#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
extern STYLECOLORS  Colors;

//EIP 57661 Driver health support
CHAR16 *FindDriverHealthDriverName (UINT16);
CHAR16 *GetCtrlNameAndHealth (UINT16 ControllerEntry);
//EIP 57661 Ends
//EIP70421 Support for Driver Order starts
VOID	*gDriverPageHandle = NULL;
UINTN 	gDriverOptionTokenCount;
UINT16 	*gDriverOptionTokenArray;
BOOLEAN CheckForAddDelDriverOption (VOID);
VOID _SpecialFixupDriverOrder (CONTROL_INFO *control, UINT16 value);
//EIP70421 Support for Driver Order ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialGetIfrPtr
//
// Description:	function to handle the operation of getting the Ifr Pointer.
//
// Input:		VOID* conditional, 
//				UINT32 variable, 
//				GUID_INFO **guidInfo
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *_SpecialGetIfrPtr( CONTROL_INFO *controlInfo, UINT32 * variable, GUID_INFO **guidInfo )
{
    *variable = (UINT32)GetControlConditionVarId(controlInfo);
	return UefiGetSpecialEqIDIfrPtr(controlInfo, variable, guidInfo);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialGetValue
//
// Description:	function to handle the operation of getting the Ifr Value.
//
// Input:		CONTROL_DATA *control, 
//				GUID_INFO **guidInfo 
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 SpecialGetValue( CONTROL_DATA *control, GUID_INFO **guidInfo )
{
	return UefiGetSpecialEqIDValue(&control->ControlData, guidInfo);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialGetValue
//
// Description:	function to handle the operation of getting the Ifr Value.
//
// Input:		CONTROL_INFO *controlinfo, 
//				GUID_INFO **guidInfo 
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _SpecialGetValue( CONTROL_INFO *controlinfo, GUID_INFO **guidInfo )
{
	return UefiGetSpecialEqIDValue(controlinfo, guidInfo);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialAddControl
//
// Description:	function to Handle adding a control.
//
// Input:		FRAME_DATA *frame , 
//				CONTROL_INFO *controlinfo, 
//				BOOLEAN *SetFocus
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _SpecialAddControl(FRAME_DATA *frame , CONTROL_INFO *ControlInfo, BOOLEAN *SetFocus)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	STYLECOLORS saveColors ;
	

	//Save original style colors
	saveColors = Colors ; 

	//Special control color scheme...
	StyleControlColor(frame, &Colors);
		
	//Adds controls to this frame...
	Status = gFrame.AddControl( frame, ControlInfo  );
	
	//Restore original style colors
	Colors = saveColors;	

	if ( EFI_ERROR(Status) )
		return Status;

	if ( *SetFocus  )
	{
        if ( _FrameSetControlFocus( frame, frame->ControlCount-1 ) )
		{
            frame->CurrentControl = frame->ControlCount-1;
			*SetFocus = FALSE;
		}
	}

	return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoAddBootOptionFixup
//
// Description:	
//
// Input:		CONTROL_INFO *newControlInfo  
//
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DoAddBootOptionFixup( CONTROL_INFO *newControlInfo )
{
		_SpecialFixupAddBootOption(newControlInfo);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialAddMultipleControls
//
// Description:	Adds Multiple controls for special controls
//
// Input:		FRAME_DATA *frame , CONTROL_INFO *controlInfo, GUID_INFO *guidInfo, BOOLEAN *SetFocus 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialAddMultipleControls( FRAME_DATA *frame , CONTROL_INFO *controlInfo, GUID_INFO *guidInfo, BOOLEAN *SetFocus )
{
	CONTROL_INFO *newControlInfo;
	VARIABLE_INFO *varInfo = NULL;
	UINT8 *dataPtr;
  	VOID *ifrPtr;
	CHAR16 *name = NULL;

	UINT16 count, max = 0, value = 0, HiddenBootOptionCount=0;//EIP : 59417 Declaration for the Hidden Boot option count 
	UINT16 PrevControlQuestionID=0;

	UINT32 varnum=0;
	UINTN condSize;

	if ( frame == NULL )
		return;

	if ( guidInfo->GuidFlags.GuidLaunchCallbackUpdateTemplate )
    {
		UefiSpecialGuidCallback( controlInfo->ControlHandle, 0xFFFE, &guidInfo->GuidValue);
   	}

    varnum = GetControlConditionVarId(controlInfo); //controlInfo->ControlConditionalVariable[0];
    ifrPtr = _SpecialGetIfrPtr( controlInfo, &varnum, NULL ); // TO get the special variable.

  if(NoVarStoreSupport())
  {
    //More info needed.
    if(varnum == VARIABLE_ID_SETUP)
    {
      ifrPtr = _SpecialGetIfrPtr( controlInfo, &varnum, NULL );

      //The variable supplied is setup find the right variable
      varnum = FindVarFromITKQuestionId(UefiGetEqIDQuestionID(ifrPtr));
    }
  }

	if( varnum == VARIABLE_ID_ERROR_MANAGER )  // if it is error manager variable, get the real updated nvram data.
		VarUpdateVariable(varnum);

  	varInfo = ((VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[varnum]));
  	name = GetGUIDNameByID(VARIABLE_ID_LANGUAGE);
    //The following is replaced by Name comparision
    //if ( ((VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[varnum]))->VariableID == LANGUAGE_CODES_KEY_ID )
    if(EfiStrCmp(varInfo->VariableName, name) == 0)
    {
		MemFreePointer((void**)&name);
        max = 1;
    }
    else if (
			(
			CheckForAddDelBootOption () &&
            ((VARIABLE_ID_DEL_BOOT_OPTION  == controlInfo->ControlVariable) || (VARIABLE_ID_ADD_BOOT_OPTION == controlInfo->ControlVariable))
			) ||
			(
			CheckForAddDelDriverOption () &&			//EIP70421 & 70422
            ((VARIABLE_ID_DEL_DRIVER_OPTION == controlInfo->ControlVariable) || (VARIABLE_ID_ADD_DRIVER_OPTION == controlInfo->ControlVariable))
			)
			) 
	{
        max = 1;
	}
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
    else if(varnum == VARIABLE_ID_OEM_TSE_VAR )
	{
        max = OEMSpecialGetControlCount(controlInfo);
	}
#endif
    else
	{
        VarGetValue( varnum, 0, sizeof(UINT16), &max );
	}
	for (count = 0; count < max; count++)
	{
    	if ( ( controlInfo->ControlPtr == 0 ) || ( controlInfo->ControlConditionalPtr == 0 ) )
      		continue;
		if (
			(gLoadOptionHidden && ((VARIABLE_ID_BOOT_MANAGER == varnum) || (VARIABLE_ID_BOOT_NOW == varnum) || (VARIABLE_ID_DRIVER_MANAGER == varnum))) &&
			(VARIABLE_ID_DEL_BOOT_OPTION  != controlInfo->ControlVariable) && 		//For deleting the boot/driver option max is 1 so if first option is hidden nothing will proceed
			(VARIABLE_ID_ADD_BOOT_OPTION != controlInfo->ControlVariable) &&
			(VARIABLE_ID_DEL_DRIVER_OPTION != controlInfo->ControlVariable) && 
			(VARIABLE_ID_ADD_DRIVER_OPTION != controlInfo->ControlVariable)
			)
		{
			if (count < gBootOptionCount)			//EIP-91817 To avoid comparing garbage gBootData for LoadOptionHidden when SETUP_SHOW_ALL_BBS_DEVICES = 1
			{
			 	if ((VARIABLE_ID_DRIVER_MANAGER == varnum) ? (LoadOptionhidden (count, DRIVER_ORDER_OPTION)) : (LoadOptionhidden (count, BOOT_ORDER_OPTION)))
				{
					HiddenBootOptionCount ++; // If the Boot option has the attribute Hidden increment the HiddenBootOptionCount 
					continue;
				}
			}
		}
		newControlInfo = EfiLibAllocatePool( sizeof( CONTROL_INFO ) );
		if ( newControlInfo == NULL )
			continue;

    	MemCopy( newControlInfo, controlInfo, sizeof( CONTROL_INFO ) );
    	condSize = (UINTN)controlInfo->ControlPtr - (UINTN)controlInfo->ControlConditionalPtr;

    	// 256 should be replaced by ControlDataLength, but HPKTool currently does not set it
    	dataPtr = EfiLibAllocateZeroPool( 256 + condSize );
    	if(dataPtr == NULL)
    	{
     	 	MemFreePointer((void**)&newControlInfo);
      		continue;
    	}

		newControlInfo->ControlConditionalPtr = dataPtr;
		MemCopy( dataPtr, (VOID *)controlInfo->ControlConditionalPtr, condSize );
		dataPtr += condSize;
		newControlInfo->ControlPtr = dataPtr;
		MemCopy( dataPtr, (VOID *)controlInfo->ControlPtr, 256 );

		ifrPtr = _SpecialGetIfrPtr( newControlInfo, &varnum, NULL );

		if ( ifrPtr != NULL )
		{
			//if TSE_BOOT_NOW_IN_BOOT_ORDER = 1 then,set the ID Value as (count - HiddenBootOptionCount)
			//since TSE using Boot order variable to display the option and hiddens boot options are present at the end of the Boot order var
			if ((BootNowInBootOrderSupport()) || (UefiIsOneOfControl ((VOID *)dataPtr)) && ((VARIABLE_ID_BOOT_MANAGER == varnum) || (VARIABLE_ID_DRIVER_MANAGER == varnum)))
			{
        		UefiSetEqIDValue (ifrPtr, count - HiddenBootOptionCount);
			}
			else
			{
				UefiSetEqIDValue (ifrPtr, count);
			}
		}
		ifrPtr = (VOID *)dataPtr;

		// EIP:51671 START 
		//Depending on the value of the token hide of the disabled boot options is done
		if (gSetupHideDisableBootOptions)
		{
			if(((VARIABLE_ID_BOOT_MANAGER == varnum)||(VARIABLE_ID_BOOT_NOW == varnum))&&(!(UefiIsOneOfControl( ifrPtr ))))
			{		
				//if TSE_BOOT_NOW_IN_BOOT_ORDER = 1 then,set the BootOptionIndex Value as (count - HiddenBootOptionCount)
				//since TSE using Boot order variable to display the option and hiddens boot options are present at the end of the Boot order var
				UINT16 BootOptionIndex = 0;
				BootOptionIndex = ((BootNowInBootOrderSupport())? count - HiddenBootOptionCount : count);
				if (IsBootDeviceEnabled (BootOptionIndex, gShowAllBbsDev, BootNowInBootOrderSupport (), 1))
					continue;
			}
		}
		// EIP:51671 END
		// EIP:59417 START 
		//Checking for the  Bootmanger variable and the token for Load Option hidden
		
		// EIP:59417 END
	    if (UefiIsOneOfControl (ifrPtr))
		{
			UINTN size;
			CHAR16 *newText;
			CHAR16 *text ;

	      	text = HiiGetString( controlInfo->ControlHandle, UefiGetPromptField(ifrPtr) );
			//EIP-75351 Suppress the warnings from static code analyzer
			if (NULL == text) {
				text = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
				if(!text)
					return;
				EfiStrCpy(text,L" ");
	        }
	
			size = sizeof(CHAR16) * ( EfiStrLen( text ) + 10 );
			newText = EfiLibAllocateZeroPool( size );

			SPrint( newText, size, text, count + 1 - HiddenBootOptionCount );
			
			value = _SpecialGetValue( newControlInfo, &guidInfo );
		    UefiSetPromptField(ifrPtr, HiiAddString( controlInfo->ControlHandle, newText ));

			// update boot order , bbs and language tokens, prevent double initialization
			// this code was part of AddControlExtras().
      		UefiUpdateControlVarOffset (newControlInfo->ControlPtr, value * sizeof(UINT16));

       	     switch ( guidInfo->GuidKey )
       	     {
                 case GUID_KEY_BOOT_NOW:
			        if (NoVarStoreSupport())
			        {
			          _SpecialFixupBootOrder (newControlInfo, value);
			        }
			        else
					{
	                    if (newControlInfo->ControlVariable == VARIABLE_ID_BOOT_ORDER)
						{
					          _SpecialFixupBootOrder (newControlInfo, value);
					          //if count not eq to 0 and count-1 Control is Disabled then supress the current control.
							  _SpecialFixupBootCondition(count,newControlInfo,PrevControlQuestionID);
							  PrevControlQuestionID = UefiGetQuestionID(newControlInfo);
						}
	                    else if (newControlInfo->ControlVariable == VARIABLE_ID_DEL_BOOT_OPTION)
	                    {
							TSESpecialFixupDelBootOption (newControlInfo);
	                    }
					}
					break;
                case GUID_KEY_ADD_BOOT_OPTION:
                    if ((CheckForAddDelBootOption()) && (newControlInfo->ControlVariable == VARIABLE_ID_ADD_BOOT_OPTION))
                    {
						UefiUpdateControlVarOffset(newControlInfo->ControlPtr, UefiGetQuestionOffset(controlInfo->ControlPtr));
						TseDoAddBootOptionFixup( newControlInfo );
                    }
					break;
			
				case GUID_KEY_LANG_CODES:
					if ( gLangCount > 0 )
						_SpecialFixupLanguages( newControlInfo );
					break;

				case GUID_KEY_BBS_ORDER:
					_SpecialFixupBBSOrder( newControlInfo, value);
			        if(!NoVarStoreSupport())
			        {
			          //if count not eq to 0 and count-1 Control is Disabled then supress the current control.
			          _SpecialFixupBBSCondition(count,newControlInfo,PrevControlQuestionID);
					  PrevControlQuestionID = UefiGetQuestionID(newControlInfo);
			        }
					break;
				case GUID_KEY_DRIVER_OPTION:			//EIP70421 & 70422
                    if (VARIABLE_ID_DRIVER_ORDER == newControlInfo->ControlVariable)
					{
				          _SpecialFixupDriverOrder (newControlInfo, value);
				          //if count not eq to 0 and count-1 Control is Disabled then supress the current control.
						  _SpecialFixupBootCondition (count, newControlInfo, PrevControlQuestionID);
						  PrevControlQuestionID = UefiGetQuestionID(newControlInfo);
					}
					else if (VARIABLE_ID_DEL_DRIVER_OPTION == newControlInfo->ControlVariable)
					{
						TSESpecialFixupDelDriverOption (newControlInfo);
					}
					break;
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
				case GUID_KEY_OEM_CONTROL:
					// Do the OEM Special Control's OneOf Fixup
					OEMSpecialOneOfFixup( newControlInfo, value);
					break;
#endif
				default:
					break;
			}			

			MemFreePointer( (VOID **)&newText );
			MemFreePointer( (VOID **)&text );
		}
		_SpecialAddControl( frame, newControlInfo, SetFocus );
		// update optional info specially for boot order controls
        _SpecialControlExtras((frame->ControlList[frame->ControlCount-1]));
		MemFreePointer( (VOID **)&newControlInfo );
	}

	gSetupUpdated = FALSE; //EIP:51619 Reset the SetupUpdated Flag here.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupLanguages
//
// Description:	function to fixup the languages
//
// Input:		CONTROL_INFO *control 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupLanguages( CONTROL_INFO *control )
{
	VOID *ifrPtr, *templatePtr, *oneOf;
	VOID *tempPtr;
	UINTN i,  length = 0;
  	BOOLEAN flag = FALSE;

	ifrPtr = (VOID *)control->ControlPtr;
	length = UefiGetIfrLength(ifrPtr);

	if(PlatformLangVerSupport())	
 	 	UefiSetWidth(ifrPtr, 6);
	else
 	 	UefiSetWidth(ifrPtr, 3);

	tempPtr = UefiCreateOneOfWithOptionsTemplate( gLangCount, control );
	if ( tempPtr == NULL )
		return;

	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
  	length = UefiGetIfrLength(templatePtr);
	for ( i = 0; i < gLangCount; i++ )
	{
		MemCopy( oneOf, templatePtr, length );
    	flag = 0;
        gLanguages[i].Token = HiiChangeString( gHiiHandle, gLanguages[i].Token, gLanguages[i].LangString );
    	UefiSetOneOfOption(oneOf, i, BOOT_OPTION_SIZE, flag, gLanguages[i].Token);
    	oneOf = (UINT8*)oneOf +length;
	}

  	// Add an End op to close scope of the One of control
  	UefiAddEndOp(oneOf);

	tempPtr = HiiGetString( control->ControlHandle, UefiGetPromptField(ifrPtr) );
	UefiSetPromptField (control->ControlPtr,HiiAddString( gHiiHandle, tempPtr ));

	MemFreePointer( (VOID **)&tempPtr );
	tempPtr = HiiGetString( control->ControlHandle, UefiGetHelpField(ifrPtr) );

	control->ControlHelp = HiiAddString( gHiiHandle, tempPtr );
	control->ControlHandle = gHiiHandle;

	MemFreePointer( (VOID **)&tempPtr );
}

//EIP-48391: Start

static VOID		*gBootPageHandle = NULL;
static UINTN 	gBootOptionTokenCount;
static UINT16 	*gBootOptionTokenArray;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetSpecialBootoptionToken
//
// Description:	function to get the boot option token properly when loading the boot page
//
// Input:		VOID* handle, UINTN Index
//
// Output:		TOKEN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetSpecialBootoptionToken(VOID* handle, UINTN Index) 
{
	UINTN i;

	// EIP:51619 TO make sure it is called by _SpecialFixupBootOrder() and Boot page not modified
	if (gBootPageHandle == handle)
	{
		if(FALSE == gSetupUpdated)
		{
			if(!gBootOptionTokenCount)
			{
				// Create the gBootOptionTokenArray
				gBootOptionTokenArray = EfiLibAllocateZeroPool (sizeof(UINT16) * gBootOptionCount);
				gBootOptionTokenCount = gBootOptionCount;
				for(i=0;i< gBootOptionTokenCount;i++)
				{
					gBootOptionTokenArray[i] = INVALID_TOKEN;
				}
			}
			else if(gBootOptionTokenCount < gBootOptionCount)
			{ // Boot options added. Update gBootOptionTokenArray
				gBootOptionTokenArray = MemReallocateZeroPool(gBootOptionTokenArray, (sizeof(UINT16) * gBootOptionTokenCount), (sizeof(UINT16) * gBootOptionCount));
				for(i= gBootOptionTokenCount; i< gBootOptionCount ;i++)
				{
					gBootOptionTokenArray[i] = INVALID_TOKEN;
				}
				gBootOptionTokenCount = gBootOptionCount;
			}
			
			if(gBootOptionTokenArray[Index] == INVALID_TOKEN)
				gBootOptionTokenArray[Index] = HiiAddString(handle, BootGetOptionName( &(gBootData[Index]) ) );
            else
            {
                // Check if Update is needed
                CHAR16 *text;
                text = HiiGetString( handle, gBootOptionTokenArray[Index]);
					 
				if (NULL == text) //EIP-131549
					return (UINT16)EFI_OUT_OF_RESOURCES;
						 
                if(EfiStrCmp(text, BootGetOptionName( &(gBootData[Index]) )) != 0)
                {
                    // need to update the token with new BootoptionName.
                    UINT16  Token = HiiChangeString( handle, gBootOptionTokenArray[Index], BootGetOptionName( &(gBootData[Index]) ));
                    if(Token != gBootOptionTokenArray[Index])
                        gBootOptionTokenArray[Index] = Token;
                }
                MemFreePointer((VOID **)&text);
            }
		}
		else {
			//If the some control modified with respect to boot page..
	 		gBootOptionTokenArray[Index] = HiiAddString(handle, BootGetOptionName( &(gBootData[Index]) ) );
		}
		return gBootOptionTokenArray[Index];

	}
	else
		//If the call is not from _SpecialFixupBootOrder() 
	 	return	HiiAddString(handle, BootGetOptionName( &(gBootData[Index]) ) );
}
//EIP-48391: End

//EIP70421 & 70422 Support for Driver Order starts
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------
// Procedure:	_GetSpecialDriveroptionToken
//
// Description:	function to get the boot option token properly when loading the boot page
//
// Input:		VOID* handle, UINTN Index
//
// Output:		TOKEN
//
//-------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetSpecialDriveroptionToken (VOID* handle, UINTN Index) 
{
	UINTN i;

	if (gDriverPageHandle == handle)
	{
		if(FALSE == gSetupUpdated)
		{
			if (!gDriverOptionTokenCount)
			{
				// Create the gDriverOptionTokenArray
				gDriverOptionTokenArray = EfiLibAllocateZeroPool (sizeof(UINT16) * gDriverOptionCount);
				gDriverOptionTokenCount = gDriverOptionCount;
				for (i = 0; i < gDriverOptionTokenCount; i ++)
				{
					gDriverOptionTokenArray [i] = INVALID_TOKEN;
				}
			}
			else if (gDriverOptionTokenCount < gDriverOptionCount)
			{ // Drivers options added. Update gDriverOptionTokenArray
				gDriverOptionTokenArray = MemReallocateZeroPool (gDriverOptionTokenArray, (sizeof (UINT16) * gDriverOptionTokenCount), (sizeof (UINT16) * gDriverOptionCount) );
				for (i = gDriverOptionTokenCount; i < gDriverOptionCount ; i ++)
				{
					gDriverOptionTokenArray [i] = INVALID_TOKEN;
				}
				gDriverOptionTokenCount = gDriverOptionCount;
			}
			
			if (gDriverOptionTokenArray [Index] == INVALID_TOKEN)
				gDriverOptionTokenArray [Index] = HiiAddString (handle, DriverGetOptionName (&(gDriverData [Index]) ) );
			else
            {
                // Check if Update is needed
                CHAR16 *text;
                text = HiiGetString( handle, gDriverOptionTokenArray [Index]);
                if(EfiStrCmp(text, DriverGetOptionName ( &(gDriverData[Index]) )) != 0)
                {
                    // need to update the token with new DriveroptionName.
                    UINT16  Token = HiiChangeString( handle, gDriverOptionTokenArray [Index], DriverGetOptionName( &(gDriverData[Index]) ));
                    if(Token != gDriverOptionTokenArray [Index])
                        gDriverOptionTokenArray [Index] = Token;
                }
                MemFreePointer((VOID **)&text);
            }
		}
		else {
			//If the some control modified with respect to boot page..
	 		gDriverOptionTokenArray [Index] = HiiAddString (handle, DriverGetOptionName (&(gDriverData [Index]) ) );
		}
		return gDriverOptionTokenArray [Index];

	}
	else
		//If the call is not from _SpecialFixupBootOrder() 
	 	return	HiiAddString(handle, DriverGetOptionName (&(gDriverData [Index]) ) );
}
//EIP70421 & 70422 Support for Driver Order ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupBootOrder
//
// Description:	function to fixup the Boot device order
//
// Input:		CONTROL_INFO *control,
//				UINT16 value	 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupBootOrder (CONTROL_INFO *control, UINT16 value)
{
	VOID 	*tempPtr, *ifrPtr;
	VOID 	*templatePtr, *oneOf;
	UINTN 	i;
	CHAR16 	*text;
	UINT8 	length = 0;
	UINT16 	option = 0;
	UINT8 	flag = 0;

	ifrPtr = control->ControlPtr;
	length = UefiGetIfrLength(ifrPtr);
	//Create one one_of_option for each boot option + 1 for Disable option
	tempPtr = UefiCreateOneOfWithOptionsTemplate (gBootOptionCount+1, control);
	if ( tempPtr == NULL )
		return;

	templatePtr = ((UINT8*)ifrPtr + length);
	oneOf = ((UINT8*)tempPtr + length);
  length = UefiGetIfrLength(templatePtr); 

//EIP-48391: Start
	gBootPageHandle = control->ControlHandle;		//++
	for ( i = 0; i < gBootOptionCount; i++ ) {
		flag = (i == value)? (UINT8)HiiGetDefaultMask() : 0;
		//option = HiiAddString( control->ControlHandle, BootGetOptionName( &(gBootData[i]) ) );		// --
		//EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
		if (gLoadOptionHidden && (gBootData [i].Active & LOAD_OPTION_HIDDEN) )
			continue;
		option = GetSpecialBootoptionToken (control->ControlHandle, i);
		MemCopy (oneOf, templatePtr, length);
		// Add one of option
		UefiSetOneOfOption (oneOf, gBootData[i].Option, BOOT_OPTION_SIZE, flag, option);
		oneOf = (UINT8*)oneOf +length;
	}
//EIP-48391: End

  //Create one of option for Disabled
	flag = 0;
	MemCopy (oneOf, templatePtr, length);
	text = HiiGetString (gHiiHandle, STR_CTRL_CHKBOX_DISABLE);
	option = HiiAddString (control->ControlHandle, text);

	//UefiSetOneOfOption (oneOf, 0xFFFF, BOOT_OPTION_SIZE, flag, option); //EIP-97704 BootFFFF
	UefiSetOneOfOption (oneOf, DISABLED_BOOT_OPTION, BOOT_OPTION_SIZE, flag, option);

	MemFreePointer((VOID **)&text);
	oneOf = (UINT8*)oneOf +length;

	// Add an End op to close scope of the One of control
	UefiAddEndOp(oneOf);

	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);

	if(NoVarStoreSupport())
	{
		VOID *ifrPtr;
		UINT16  QuestionId;
		
		control->ControlVariable = VARIABLE_ID_BOOT_ORDER;
		control->ControlConditionalVariable[0] = VARIABLE_ID_BOOT_MANAGER;
		
		ifrPtr = _SpecialGetIfrPtr( control,  VARIABLE_ID_SETUP, NULL);
		QuestionId = UefiGetEqIDQuestionID(ifrPtr);
		QuestionId = QuestionId - GetNoVarStoreBootCountOffset();
		UefiSetEqIDQuestionID(ifrPtr, QuestionId);
	}
}

//EIP70421 & 70422  Support for driver order starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupDriverOrder
//
// Description:	Function to fixup the driver order
//
// Input:		CONTROL_INFO *control,
//				UINT16 value	 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupDriverOrder (CONTROL_INFO *control, UINT16 value)
{
	VOID 	*tempPtr, *ifrPtr;
	VOID 	*templatePtr, *oneOf;
	UINTN 	i;
	CHAR16 	*text;
	UINT8 	length = 0;
	UINT16 	option = 0;
	UINT8 	flag = 0;

	ifrPtr = control->ControlPtr;
	length = UefiGetIfrLength(ifrPtr);
	//Create one one_of_option for each driver option + 1 for Disable option
	tempPtr = UefiCreateOneOfWithOptionsTemplate (gDriverOptionCount+1, control);
	if (NULL == tempPtr)
		return;
	templatePtr = ((UINT8*)ifrPtr + length);
	oneOf = ((UINT8*)tempPtr + length);
	length = UefiGetIfrLength(templatePtr); 
	gDriverPageHandle = control->ControlHandle;
	
	for ( i = 0; i < gDriverOptionCount; i++ )
	{
		flag = (i == value)? (UINT8)HiiGetDefaultMask() : 0;
		if (gLoadOptionHidden && (gDriverData [i].Active & LOAD_OPTION_HIDDEN))
			continue;
		option = _GetSpecialDriveroptionToken (control->ControlHandle, i);
		MemCopy (oneOf, templatePtr, length);
			// Add one of option
		UefiSetOneOfOption (oneOf, gDriverData [i].Option, BOOT_OPTION_SIZE, flag, option);
		oneOf = (UINT8*)oneOf +length;
	}
	//Create one of option for Disabled
	flag = 0;
	MemCopy (oneOf, templatePtr, length);
	text = HiiGetString (gHiiHandle, STR_CTRL_CHKBOX_DISABLE);
	option = HiiAddString (control->ControlHandle, text);

	//UefiSetOneOfOption (oneOf, 0xFFFF, BOOT_OPTION_SIZE, flag, option); //EIP-97704 DriverFFFF
	UefiSetOneOfOption (oneOf, DISABLED_DRIVER_OPTION, BOOT_OPTION_SIZE, flag, option);

	MemFreePointer((VOID **)&text);
	oneOf = (UINT8*)oneOf +length;

	// Add an End op to close scope of the One of control
	UefiAddEndOp(oneOf);

	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);
}
//EIP70421 & 70422  Support for driver order ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupBootCondition
//
// Description:	This function updates the Condition to avoid more then one 
//				disabled option in Boot order.
//
// Input:		ControlIndex, Control Info, PrevControlQuestionID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupBootCondition (UINT16 ControlIndex,CONTROL_INFO *control,UINT16 PrevControlQuestionID)
{
	// Don't Update the Condition for First option
    if(!ControlIndex)
		return;
	else
	{
        UINT8 u8ChkResult = CheckControlCondition( control );
        if(u8ChkResult == COND_NONE)
        {
    		VARIABLE_INFO *VarInfo;
    		VarInfo = VarGetVariableInfoIndex(control->ControlVariable);
			if(NULL != VarInfo){//EIP-75352 Suppress the warnings from static code analyzer
				UefiCreateDynamicControlCondition(control,(UINT16)VarInfo->VariableID,PrevControlQuestionID,DISABLED_BOOT_OPTION);
			}
        }
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupBBSCondition
//
// Description:	This function updates the Condition to avoid more then one 
//				disabled option in BBS Dev order.
//
// Input:		ControlIndex, Control Info, PrevControlQuestionID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupBBSCondition(UINT16 ControlIndex,CONTROL_INFO *control,UINT16 PrevControlQuestionID)
{
	// Don't Update the Condition for First option
    if(!ControlIndex)
		return;
	else
	{
        UINT8 u8ChkResult = CheckControlCondition( control );
        if(u8ChkResult == COND_NONE)
        {
    		VARIABLE_INFO *VarInfo;
    		VarInfo = VarGetVariableInfoIndex(control->ControlVariable);
			if(NULL != VarInfo){//EIP-75352 Suppress the warnings from static code analyzer
	    		UefiCreateDynamicControlCondition(control,(UINT16)VarInfo->VariableID,PrevControlQuestionID,DISABLED_BOOT_OPTION);
			}
        }
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupBBSOrder
//
// Description:	function to fixup the Legacy Boot device order
//
// Input:		CONTROL_INFO *control,
//				UINT16 value	 
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupBBSOrder( CONTROL_INFO *control, UINT16 value )
{
	VOID *ifrPtr, *templatePtr, *oneOf, *tempPtr;
	UINTN i;
	UINT16 count,option;
  UINT16 length = 0;
  CHAR16 *text;
	UINT8 flag;

	count = gCurrLegacyBootData->LegacyDevCount;

	ifrPtr = (VOID *)control->ControlPtr;
  length = UefiGetIfrLength(ifrPtr);
	//Create one one_of_option for each device + 1 for Disable option
  tempPtr = UefiCreateOneOfWithOptionsTemplate(count + 1, control);
	if ( tempPtr == NULL )
		return;


	// set real offset into bbs variable for this control. 
  BBSUpdateControlOffset(control);

	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
  length = UefiGetIfrLength(templatePtr);

	for ( i = 0; i < count; i++)
	{
    UINT16 bbsOptionVal = 0;

		MemCopy( oneOf, templatePtr, length );
    flag = (i == value)? (UINT8)HiiGetDefaultMask() : 0;
		option = HiiAddString( control->ControlHandle, BBSGetOptionName( &bbsOptionVal,(UINT16)i ) );
		MemCopy( oneOf, templatePtr, length );
    // Add one of option
    UefiSetOneOfOption(oneOf, bbsOptionVal, BOOT_OPTION_SIZE, flag, option);
    	oneOf = (UINT8*)oneOf +length;
	}

  //Create one of option for Disabled
  flag = 0;
  MemCopy( oneOf, templatePtr, length );
  text = HiiGetString(gHiiHandle,STR_CTRL_CHKBOX_DISABLE);
  option = HiiAddString( control->ControlHandle, text );

	//UefiSetOneOfOption(oneOf, 0xFFFF, BOOT_OPTION_SIZE, flag, option); //EIP-97704 BootFFFF
	UefiSetOneOfOption(oneOf, DISABLED_BOOT_OPTION, BOOT_OPTION_SIZE, flag, option);

  MemFreePointer((VOID **)&text);
 	oneOf = (UINT8*)oneOf +length;

  // Add an End op to close scope of the One of control
  UefiAddEndOp(oneOf);

	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialFixupDelBootOption
//
// Description:	function to fixup the deletion of a boot device option
//
// Input:		CONTROL_INFO *control,
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SpecialFixupDelBootOption (CONTROL_INFO *control)
{
	VOID *ifrPtr, *templatePtr, *oneOf;
	VOID *tempPtr;
	UINTN i, length = 0;
	
	ifrPtr = (VOID *)control->ControlPtr;
	length = UefiGetIfrLength(ifrPtr);
	//Create one one_of_option for each boot option + 1 for Disable option
	tempPtr = UefiCreateOneOfWithOptionsTemplate (gBootOptionCount + 1, control);
	if ( tempPtr == NULL )
		return;
	
	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
	length = UefiGetIfrLength (templatePtr);
	
	//Copy the first option and skip to next
	MemCopy( oneOf, templatePtr, length );
	oneOf = (UINT8*)oneOf +length;
	
	for ( i = 0; i < gBootOptionCount; i++ )
	{
		if(
			((gBootData[i].DevicePath->Type == BBS_DEVICE_PATH) && (gBootData[i].DevicePath->SubType == BBS_BBS_DP)) ||
			(gLoadOptionHidden && (gBootData [i].Active & LOAD_OPTION_HIDDEN))	
			)
		{
			continue;
		}
		else
		{
			UINT16 option = 0;
			UINT8 flag = 0;
	
			MemCopy( oneOf, templatePtr, length );
			option = HiiAddString (control->ControlHandle, BootGetOptionName (&(gBootData[i])));
			// Add one of option
			UefiSetOneOfOption (oneOf, gBootData[i].Option, BOOT_OPTION_SIZE, flag, option);
			oneOf = (UINT8*)oneOf +length;
		}
	}

	// Add an End op to close scope of the One of control
	UefiAddEndOp (oneOf);
	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField (ifrPtr);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialFixupAddBootOption
//
// Description:	function to fixup the adding of a boot device option
//
// Input:		CONTROL_INFO *control,
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialFixupAddBootOption( CONTROL_INFO *control)
{
	VOID *ifrPtr, *templatePtr, *oneOf;
	VOID *tempPtr;
	UINTN i,  length = 0;

	ifrPtr = (VOID *)control->ControlPtr;
   	length = UefiGetIfrLength(ifrPtr);
  	//Create one one_of_option for each file sys
	tempPtr = UefiCreateOneOfWithOptionsTemplate( gFsCount, control );
	if ( tempPtr == NULL )
		return;

	UefiUpdateControlVarOffset(control, STRUCT_OFFSET(NEW_BOOT_OPTION, SelFs));

	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
  	length = UefiGetIfrLength(templatePtr);

	for ( i = 0; i < gFsCount; i++)
	{
    UINT16 option = 0;
    UINT8 flag = 0;

    MemCopy( oneOf, templatePtr, length );
    // Add one of option
		option = HiiAddString( control->ControlHandle, gFsList[i].FsId);
    UefiSetOneOfOption(oneOf, (UINT16)i, BOOT_OPTION_SIZE, flag, option);
     	oneOf = (UINT8*)oneOf +length;

	}

  // Add an End op to close scope of the One of control
  UefiAddEndOp(oneOf);
	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);
}

//EIP70421 & 70422  Support for driver order starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialFixupDelDriverOption
//
// Description:	Function to fixup the deletion of a driver option
//
// Input:		CONTROL_INFO *control,
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SpecialFixupDelDriverOption (CONTROL_INFO *control)
{
	VOID *ifrPtr, *templatePtr, *oneOf;
	VOID *tempPtr;
	UINTN i, length = 0;

	ifrPtr = (VOID *)control->ControlPtr;
	length = UefiGetIfrLength (ifrPtr);
	//Create one one_of_option for each driver option + 1 for Disable option
	tempPtr = UefiCreateOneOfWithOptionsTemplate (gDriverOptionCount + 1, control);
	if (NULL == tempPtr)
		return;
	
	templatePtr = (UINT8*)ifrPtr + length;
	oneOf = (UINT8*)tempPtr + length;
	length = UefiGetIfrLength (templatePtr);
	
	//Copy the first option and skip to next
	MemCopy (oneOf, templatePtr, length);
	oneOf = (UINT8*)oneOf +length;
	
	for (i = 0; i < gDriverOptionCount; i++)
	{
		if(
			((gDriverData [i].DevicePath->Type == BBS_DEVICE_PATH) && (gDriverData [i].DevicePath->SubType == BBS_BBS_DP)) ||
			(gLoadOptionHidden && (gDriverData [i].Active & LOAD_OPTION_HIDDEN))	
			)
		{
			continue;
		}
		else
		{
			UINT16 	option = 0;
			UINT8 	flag = 0;
			MemCopy (oneOf, templatePtr, length);
			option = HiiAddString (control->ControlHandle, DriverGetOptionName (&(gDriverData [i])));
			// Add one of option
			UefiSetOneOfOption (oneOf, gDriverData [i].Option, BOOT_OPTION_SIZE, flag, option);
			oneOf = (UINT8*)oneOf +length;
		}
	}
	// Add an End op to close scope of the One of control
	UefiAddEndOp (oneOf);
	ifrPtr = control->ControlPtr;
	control->ControlHelp = UefiGetHelpField(ifrPtr);
}
//EIP70421 & 70422  Support for driver order ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialExplodeControl
//
// Description:	function to explode a perticular contorller
//
// Input:		FRAME_DATA *frame, 
//				CONTROL_INFO *ctrlData, 
//				BOOLEAN *SetFocus
//
// Output:		control Value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INT16 _SpecialExplodeControl( FRAME_DATA *frame, CONTROL_INFO *ctrlData, BOOLEAN *SetFocus )
{
	UINT16 value;
	GUID_INFO *guidInfo;

	value = _SpecialGetValue( ctrlData, &guidInfo );
	if ( value == (UINT16)-1 )
		_SpecialAddMultipleControls( frame,ctrlData, guidInfo, SetFocus );

	return value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SpecialControlExtras
//
// Description:	special handling of extra operations
//
// Input:		CONTROL_DATA *ctrlData
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SpecialControlExtras(CONTROL_DATA *ctrlData)
{
	GUID_INFO *guidInfo = NULL;
  UINT16 token = 0;

	UINT16 value = _SpecialGetValue( &ctrlData->ControlData, &guidInfo );
    if ( value != (UINT16)-2 )
	{
		switch(ctrlData->ControlData.ControlType) 
		{
            case CONTROL_TYPE_SUBMENU:// submenu control
				if (guidInfo->GuidKey != GUID_KEY_ADD_BOOT_OPTION)//EIP-79955 To draw GEOMETRICSHAPE_RIGHT_TRIANGLE for AddBootOption
                	((SUBMENU_DATA*)ctrlData)->SubMenuType = 2;
                if (guidInfo->GuidKey == GUID_KEY_BOOT_NOW)
                {
///EIP - 24971
                    token = HiiAddString( ctrlData->ControlData.ControlHandle, BootGetBootNowName(value,gShowAllBbsDev,BootNowInBootOrderSupport()));
///EIP - 24971
                  //Update the submenu prompt field.
                  UefiSetPromptField(ctrlData->ControlData.ControlPtr, token);
                }
		        else if ( guidInfo->GuidKey == GUID_KEY_ERROR_MANAGER )
		        {
			        UINTN size = 0;
                    ERROR_MANAGER *errManager = VarGetNvram( VARIABLE_ID_ERROR_MANAGER, &size );
                    
                    if ( ( errManager != NULL ) && ( value < errManager->ErrorCount ) )
                    {
                        ERROR_LIST *errList = &(errManager->ErrorList[value]);

                        // Update the submenu prompt field.
                        UefiSetPromptField(ctrlData->ControlData.ControlPtr, errList->Summary);
                        ctrlData->ControlData.ControlHelp = errList->DetailInfo;
                        ctrlData->ControlData.ControlHandle = (VOID*)errList->Handle;
                        MemFreePointer( (VOID **)&errManager );
			        }
		        }
                else if (guidInfo->GuidKey == GUID_KEY_DYNAMIC_PAGE)
				{
					UINTN i = 0,j;
					UINTN Index=0;
                    PAGE_INFO *pageInfo;
                    PAGE_INFO *tmppageInfo;
				    PAGE_DATA **page;

                    //EIP 78627: To maintain consistency, show arrow when displaying submenu (SubMenuType=0).  
                    ((SUBMENU_DATA*)ctrlData)->SubMenuType = 0; 

					//Scan for dynamic pages					
					for(i = 0; i < gPages->PageCount; i++)
					{
						pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[i]);
            

						if((pageInfo->PageFlags.PageDynamic == TRUE) && (pageInfo->PageHandle != NULL))
					 	{
							if(Index == value)
							{
								
                                CHAR16 *text;
                                UINT16 Title=0, Help=0 ;
                                
                                // Get Formset Title and Help for Dynamic page
                                GetFormSetTitleAndHelpWrapper (pageInfo->PageHandle, &Title, &Help);
                                
								// Add the Prompt
								text = HiiGetString( pageInfo->PageHandle, pageInfo->PageSubTitle);
		                        token = HiiAddString( ctrlData->ControlData.ControlHandle, text);
                        		UefiSetPromptField(ctrlData->ControlData.ControlPtr, token);
                                                                
                                //EIP# 72333, Display Formset Help for Dynamic page
                                if(Help != 0)
                                {
                                    MemFreePointer( (VOID **)&text );
                                    text = HiiGetString( pageInfo->PageHandle, Help);
		                            token = HiiAddString( ctrlData->ControlData.ControlHandle, text);
                        		    UefiSetHelpField(ctrlData->ControlData.ControlPtr, token);
                                    ctrlData->ControlData.ControlHelp = token ;
                                }//EIP# 72333 End
                            
								// Fix the parent pageID
								ctrlData->ControlData.ControlDestPageID = pageInfo->PageID ;
								pageInfo->PageParentID = gApp->CurrentPage;
                                gDynamicParentPage = gApp->CurrentPage;
                                // Reinitilize the Page.
            					for(j = i; j < gPages->PageCount; j++)
            					{
                                    tmppageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[j]);
                                    if(pageInfo->PageHandle == tmppageInfo->PageHandle )
                                    {
                                        page = &gApp->PageList[tmppageInfo->PageID];
                                        gPage.Destroy( *page, FALSE );
                                        gPage.Initialize( *page, tmppageInfo );
                                    }
                                }
								MemFreePointer( (VOID **)&text );
							}
							Index++;
					    }
					}
					
				}
				else if (guidInfo->GuidKey == GUID_KEY_IDE_SECURITY)
				{             
					CHAR16 *text;
					UINT16 IDEStrToken = TSEIDEPasswordGetName(value);
					

					if(IDEStrToken)
					{
						UINTN size;						
						IDE_SECURITY_CONFIG *ideSecConfig;						
						size = 0;
						//Update mem copy of the IDE sec variable
						ideSecConfig = VarGetVariable( VARIABLE_ID_IDE_SECURITY, &size );					
						if (NULL == ideSecConfig) {
							break;
						}
						TSEIDEUpdateConfig(ideSecConfig, value);
						VarSetValue( VARIABLE_ID_IDE_SECURITY, 0, size, ideSecConfig ); //EIP-83704 to update VARIABLE_ID_IDE_SECURITY variable when HDD is frozen in setup
						MemFreePointer((VOID **)&ideSecConfig);
						
						//VarUpdateVariable (VARIABLE_ID_IDE_SECURITY);
						text = HiiGetString( gHiiHandle, IDEStrToken);
						token = HiiAddString( ctrlData->ControlData.ControlHandle, text);
						//Update the submenu prompt field.
						UefiSetPromptField(ctrlData->ControlData.ControlPtr, token);
						MemFreePointer( (VOID **)&text );
					}
				}
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
		        else if ( guidInfo->GuidKey == GUID_KEY_OEM_CONTROL )
				{
					OEMSpecialGotoFixup(&ctrlData->ControlData,value);
				}
#endif
/**/
                else if (guidInfo->GuidKey == GUID_KEY_BBS_ORDER)
                {
                    CHAR16 *text = NULL;
                    UINTN i,j;
                    BOOT_DATA *bootData;

                    for(i=0,j=0; i<gBootOptionCount; i++)
                    {
                        bootData = &(gBootData[i]);
						 //EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
						if(gLoadOptionHidden && (bootData->Active & LOAD_OPTION_HIDDEN))
						  continue;
				
                        if ( BBSValidDevicePath(bootData->DevicePath) )
                        {
                            if(value == j)
                            {
                                BBS_BBS_DEVICE_PATH *DevPath = (BBS_BBS_DEVICE_PATH *)bootData->DevicePath;

                                switch(DevPath->DeviceType)
                                {
                                    case BBS_TYPE_FLOPPY:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_FLOPPY_DISK_ORDER));
                                    break;
                                    case BBS_TYPE_HARDDRIVE:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_HARD_DISK_ORDER));
                                    break;
                                    case BBS_TYPE_CDROM:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_CDROM_ORDER));
                                    break;

                                    case BBS_TYPE_PCMCIA:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_PCMCIA_ORDER));
                                    break;

                                    case BBS_TYPE_USB:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_USB_ORDER));
                                    break;

                                    case BBS_TYPE_EMBEDDED_NETWORK:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_NETWORK_ORDER));
                                    break;
                                    case BBS_TYPE_DEV:
                                        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_BEV_ORDER));
                                    break;
                                    default:
                                        /// EIP-42520: Updated to get the BBS group type from the Board module in case of a non standard type.
                                        text = HiiGetString( gHiiHandle, BBSGetNonStandardGroupType(DevPath->DeviceType));
                                    break;
                                }

                                token = HiiAddString( ctrlData->ControlData.ControlHandle, text);
                                //Update the submenu prompt field.
                                UefiSetPromptField(ctrlData->ControlData.ControlPtr, token);

                      			MemFreePointer( (VOID **)&text );

                                break;
                            }
                            j++;
                        }
                    }
                }
				else if (GUID_KEY_DRIVER_HEALTH == guidInfo->GuidKey)
				{
					CHAR16	*text;
					((SUBMENU_DATA*)ctrlData)->SubMenuType = 0;		//EIP100099 showing submenu triangle
					text = FindDriverHealthDriverName (value);
					if (NULL != text)
					{
						token = HiiAddString (ctrlData->ControlData.ControlHandle, text);
						UefiSetPromptField (ctrlData->ControlData.ControlPtr, token);
					}
				}
				else if (GUID_KEY_DRV_HEALTH_CTRL_COUNT == guidInfo->GuidKey)
				{
					CHAR16	*text;
					text = GetCtrlNameAndHealth (value);
					if (NULL != text)
					{
						token = HiiAddString (ctrlData->ControlData.ControlHandle, text);
						UefiSetPromptField (ctrlData->ControlData.ControlPtr, token);
					}
				}
				else if (GUID_KEY_DRIVER_HEALTH_ENB == guidInfo->GuidKey)
				{
					((SUBMENU_DATA*)ctrlData)->SubMenuType = 0;				//EIP100099 showing submenu triangle
				}
				break;
			default:
				break;
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SpecialUpdatePageControls
//
// Description:	special fucntion to update the page controls
//
// Input:		UINT32 CurrentPage
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SpecialUpdatePageControls(UINT32 CurrentPage)
{
	PAGE_INFO *thisPage;
    UINT16 i=MAIN_FRAME,j=0, k=0;
	INT16 Value=0;
    CONTROL_INFO *control;
	CONTROL_DATA **ControlData;
	CONTROL_INFO *ControlInfo;
    GUID_INFO *guidInfo;
    FRAME_DATA *fdata;
    BOOLEAN ExitUpdate=FALSE, SetFocus =TRUE;
//Fix EIP:18142	- start
	UINT32			tmpControlCount,tmpCurrentControl,tmpFirstVisibleCtrl;
//Fix EIP:18142	- end

	i = (UINT16) StyleFrameIndexOf(MAIN_FRAME) ;
	thisPage = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[CurrentPage]);
	// find if controls in page need to be exploded 
	// i=0;
    //while(i< thisPage->FrameCount )
	//{
      // for now search main frame only, if needed uncomment code above to do this for all frames in page
			for(j=0;j < thisPage->PageControls.ControlCount;j++)
			{
				control = (CONTROL_INFO*)((UINT8 *)(gControlInfo) + thisPage->PageControls.ControlList[j]);

				switch( _SpecialGetValue( control, &guidInfo ))
				{
				    case (UINT16)-2:
					     break;
				    default:
						// special case, need to reinitialize this frame
						//pdata = (PAGE_DATA*)gApp->PageList[CurrentPage];
						fdata = ((PAGE_DATA*)gApp->PageList[CurrentPage])->FrameList[i]; 
						//clist = ((PAGE_DATA*)gApp->PageList[CurrentPage])->FrameList[i]->ControlList;
						ControlData = ((PAGE_DATA*)gApp->PageList[CurrentPage])->FrameList[i]->ControlList;

//Fix EIP:18142	- Start
						tmpControlCount = fdata->ControlCount;
						tmpCurrentControl = fdata->CurrentControl;
						tmpFirstVisibleCtrl = fdata->FirstVisibleCtrl;
//Fix EIP:18142	- End
	                    for ( k = 0; k < fdata/*gApp->PageList[CurrentPage]->FrameList[i]*/->ControlCount; k++, ControlData++ )
                            (*ControlData)->Methods->Destroy( *ControlData, TRUE );
						
                        fdata/*gApp->PageList[CurrentPage]->FrameList[i]*/->ControlCount =0;
					    fdata/*gApp->PageList[CurrentPage]->FrameList[i]*/->CurrentControl =0;
                        fdata/*gApp->PageList[CurrentPage]->FrameList[i]*/->NullCount =0;
						fdata->FirstVisibleCtrl = 0;

					    // loop for al acontrols to either add it "as is" or explode it
	                    for ( k = 0; k < thisPage->PageControls.ControlCount; k++  )
						{
                            ControlInfo = (CONTROL_INFO*)((UINT8 *)gControlInfo + (UINT32)thisPage->PageControls.ControlList[k]);
                            switch(Value=_SpecialExplodeControl(fdata,ControlInfo, &SetFocus))
							{
							case -1:
								break;
							default:
						        if( _SpecialAddControl(fdata,ControlInfo, &SetFocus ) == EFI_SUCCESS)	//EIP-34679: Typo error fix
                                    _SpecialControlExtras((fdata->ControlList[fdata->ControlCount-1])); 
	                           break;
							}

						}
//Fix EIP:18142	- Start
//	To retains the Control Focues in page with has special control
// 	If the control count is different the we will focus to first control as we don't know 
// 	What is added or missing.
						if(fdata->ControlCount == tmpControlCount)
						{
							fdata->CurrentControl=tmpCurrentControl;
							fdata->FirstVisibleCtrl=tmpFirstVisibleCtrl;
							_FrameSetControlFocus( fdata, tmpCurrentControl );
						}
//Fix EIP:18142	- End

						ExitUpdate =TRUE;
					     break;
				}
				if(ExitUpdate)
					break;
			}
    //}
}
//#endif

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2014, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           5555 Oakbrook Pkwy, Norcross, Georgia 30093       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
