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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupPassword.c $
//
// $Author: Rajashakerg $
//
// $Revision: 27 $
//
// $Date: 9/17/12 6:20a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		PopupPassword.c
//
// Description:	This file contains code to handle Popup Passwords
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
////////////////////////////////////////////////////////////////
////	Extern Variables
////////////////////////////////////////////////////////////////
extern UINTN gInvalidPasswordFailMsgBox;
//EIP-73226 Extended Password support
extern UINTN gClearPasswordMsgBox;
extern UINTN gInvalidRangeFailMsgBox;
extern UINTN gClearLabelPasswordMsgBox;

CALLBACK_VARIABLE  gPopupEditCb = { { CALLBACK_TYPE_VARIABLE, sizeof(CALLBACK_VARIABLE) }, 0,0,0,NULL };
UINT8 res = (UINT8)-1;

POPUP_PASSWORD_METHODS gPopupPassword =
{
		(OBJECT_METHOD_CREATE)PopupPasswordCreate,
		(OBJECT_METHOD_DESTROY)PopupPasswordDestroy,
		(OBJECT_METHOD_INITIALIZE)PopupPasswordInitialize,
		(OBJECT_METHOD_DRAW)PopupPasswordDraw,
		(OBJECT_METHOD_HANDLE_ACTION)PopupPasswordHandleAction,
		(OBJECT_METHOD_SET_CALLBACK)PopupPasswordSetCallback,
		(CONTROL_METHOD_SET_FOCUS)PopupPasswordSetFocus,
		(CONTROL_METHOD_SET_POSITION)PopupPasswordSetPosition,
		(CONTROL_METHOD_SET_DIMENSIONS)PopupPasswordSetDimensions,
		(CONTROL_METHOD_SET_ATTRIBUTES)PopupPasswordSetAttributes,
		(CONTROL_METHOD_GET_CONTROL_HIGHT)PopupPasswordGetControlHeight

};
VOID 	GetCoordinates(INT32 *x, INT32 *y, INT32 *z);
VOID 	SetPwdKeyboardLayout(VOID);//EIP-88912
VOID 	ResetPwdKeyboardLayout(VOID);//EIP-88912
BOOLEAN IsTSECursorSupport(); //EIP-91364
VOID 	SavePswdString (CONTROL_INFO *ControlData, CHAR16 *String);
BOOLEAN	IsPasswordSupportNonCaseSensitive();
BOOLEAN	IsShowPromptStringAsTitle(VOID);//EIP-116315 password string
BOOLEAN IsMouseOnSoftkbd(VOID);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordCreate
//
// Description:	this function uses the create function of control
//					and creates the popup password
//
// Input:	POPUP_PASSWORD_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordCreate( POPUP_PASSWORD_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(POPUP_PASSWORD_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create( (void**)object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gPopupPassword;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys the popup password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordDestroy( POPUP_PASSWORD_DATA *popuppassword, BOOLEAN freeMem )
{
	if(NULL == popuppassword)
	  return EFI_SUCCESS;

	gControl.Destroy( popuppassword, FALSE );

	MemFreePointer( (VOID **)&popuppassword->Text );

	if( freeMem )
		MemFreePointer( (VOID **)&popuppassword );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordInitialize
//
// Description:	this function uses the initialize function of control
//					and initializes the popup password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordInitialize( POPUP_PASSWORD_DATA *popuppassword, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( popuppassword, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	SetControlColorsHook(NULL, NULL,  
				NULL, NULL,
				&(popuppassword->SelBGColor), &(popuppassword->SelFGColor),
			        &(popuppassword->BGColor), &(popuppassword->FGColor),
				NULL, NULL,
				NULL,
				NULL ,NULL,
				NULL,NULL );

	popuppassword->ControlData.ControlHelp = UefiGetHelpField(popuppassword->ControlData.ControlPtr);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordDraw
//
// Description:	function to draw the popup password with attributes
//
// Input:	POPUP_PASSWORD_DATA *popuppassword
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordDraw(POPUP_PASSWORD_DATA *popuppassword )
{
	CHAR16 *text;
	EFI_STATUS Status = EFI_SUCCESS;

	UINT8 ColorLabel = popuppassword->FGColor;
	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( popuppassword->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &popuppassword->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorLabel = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	text = HiiGetString( popuppassword->ControlData.ControlHandle, UefiGetPromptField(popuppassword->ControlData.ControlPtr));
	if ( text == NULL )
		return EFI_OUT_OF_RESOURCES;

	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(popuppassword->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( popuppassword->Left , popuppassword->Top, 
				(UINTN)(popuppassword->Width),(UINTN) popuppassword->Height,
				text,(UINT8)( (popuppassword->ControlFocus) ? 
						 popuppassword->SelBGColor  | popuppassword->SelFGColor : 
						 popuppassword->BGColor | ColorLabel));
	}
	else
	{
		// use frame width minus margins as available space
		// boundary overflow  check
		if ( (TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(popuppassword->Width  ))
				text[HiiFindStrPrintBoundary(text,(UINTN)(popuppassword->Width  ))] = L'\0';
	
		DrawStringWithAttribute( popuppassword->Left  , popuppassword->Top, text, 
				(UINT8)( (popuppassword->ControlFocus) ? 
						 popuppassword->SelBGColor  | popuppassword->SelFGColor : 
						 popuppassword->BGColor | ColorLabel   ));
	}
	
	MemFreePointer( (VOID **)&text );
	FlushLines( popuppassword->Top  , popuppassword->Top );

	return Status;
}

EFI_STATUS PopupPasswordSetCallback( POPUP_PASSWORD_DATA *popuppassword, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( popuppassword, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordCheckInstalledLocal
//
// Description:	function to check the local installation of popup password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword
//
// Output:	True/False
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 PopupPasswordCheckInstalledLocal(POPUP_PASSWORD_DATA *popuppassword)
{
    VOID *data = popuppassword->ControlData.ControlPtr;
    CHAR16 *RealPassword=NULL;
	UINT32 Installed=0;
	// read real password from nvram
	RealPassword = EfiLibAllocateZeroPool( ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16) );
	if ( RealPassword == NULL )
        return Installed;
	MemSet( RealPassword, ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16), 0 );

	VarGetValue( popuppassword->ControlData.ControlVariable, 
		UefiGetQuestionOffset(data), 
		(UINT8)UefiGetMaxValue(data)*2, RealPassword );

	if ( RealPassword[0] != L'\0' )
		Installed = 1;
	MemFreePointer( (VOID **)&RealPassword );

	return Installed;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordAuthenticateLocal
//
// Description:	function to check authentication of the password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, CHAR16 *Password
//
// Output:	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN PopupPasswordAuthenticateLocal( POPUP_PASSWORD_DATA *popuppassword, CHAR16 *Password )
{
    VOID *data = popuppassword->ControlData.ControlPtr;
    CHAR16 *RealPassword=NULL,*TempEncoded=NULL;
	BOOLEAN AuthenticateStatus=FALSE;
	UINTN	ii;

	// read real password from nvram
	RealPassword = EfiLibAllocateZeroPool( ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16) );
	if ( RealPassword == NULL )
        return AuthenticateStatus;
	MemSet( RealPassword, ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16), 0 );

	VarGetValue( popuppassword->ControlData.ControlVariable, 
		UefiGetQuestionOffset(data), 
		(UINT8)UefiGetMaxValue(data)*2, RealPassword );

	TempEncoded = EfiLibAllocateZeroPool( ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16) );
	if ( TempEncoded == NULL )
        return AuthenticateStatus;

	MemSet( TempEncoded, ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16), 0 );
	EfiStrCpy(TempEncoded,Password);

//EIP106950
	if (
      (IsPasswordSupportNonCaseSensitive ()) && 
      ( (VARIABLE_ID_AMITSESETUP == popuppassword->ControlData.ControlVariable) || (VARIABLE_ID_IDE_SECURITY == popuppassword->ControlData.ControlVariable) )
      )
	{
		for (ii = 0; ii < (UefiGetMaxValue(data)); ii++)
			TempEncoded [ii] = ((TempEncoded [ii]>=L'a')&&(TempEncoded [ii]<=L'z'))?(TempEncoded [ii]+L'A'-L'a'):TempEncoded [ii];
	}
//EIP106950
//EIP 23354 : Start
	//PasswordEncodeHook( TempEncoded, (UINT8)UefiGetMaxValue(data) * sizeof(CHAR16));
	if( IsPasswordEncodeEnabled( &popuppassword->ControlData )){
		PasswordEncodeHook( TempEncoded, (UINT8)UefiGetMaxValue(data) * sizeof(CHAR16));
	}
//EIP 23354 : END
    if( EfiCompareMem(TempEncoded,RealPassword,(UINT8)UefiGetMaxValue(data) * sizeof(CHAR16)))
		AuthenticateStatus = FALSE;
	else
		AuthenticateStatus = TRUE;

	MemFreePointer( (VOID **)&RealPassword );
	MemFreePointer( (VOID **)&TempEncoded );

	return AuthenticateStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdatePasswordToNonCaseSensitive
//
// Description:	function to update the given password to non case sensitive
//
// Input:	CHAR16 *Password, UINTN PwdLength
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdatePasswordToNonCaseSensitive(CHAR16 *Password, UINTN PwdLength)
{
	UINTN Idx;
	for ( Idx = 0; Idx < PwdLength; Idx++ )
		Password[Idx] = ((Password[Idx]>=L'a')&&(Password[Idx]<=L'z'))?(Password[Idx]+L'A'-L'a'):Password[Idx];
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupPasswordActivate
//
// Description:	function to set and activate a password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _PopupPasswordActivate(POPUP_PASSWORD_DATA *popuppassword)
{
   	EFI_STATUS Status = EFI_UNSUPPORTED;
	BOOLEAN AbortUpdate = FALSE;
    CHAR16 *Text=NULL,*NewPswd=NULL,*ConfirmNewPswd=NULL;
    VOID *data = popuppassword->ControlData.ControlPtr;
	UINTN NewPwLen = 0;
	UINT16 orgtext = 0;
	UINT16 newtoken = 0;

	if( PopupPwdAuthenticateIDEPwd(popuppassword,&AbortUpdate,data) != EFI_SUCCESS)
	{
		AbortUpdate = FALSE;

		if(PopupPasswordCheckInstalled(popuppassword))
		{
            // ask for old password (popupedit)
			Status = _DoPopupEdit( popuppassword, (IsShowPromptStringAsTitle() ? STRING_TOKEN(STR_OLD_PSWD_LABEL): STRING_TOKEN(STR_OLD_PSWD)), &Text);
			if( Status )
				AbortUpdate = TRUE;
			else
			{
				if(!PopupPasswordAuthenticate( popuppassword, Text ))
                {   
					// optional message to user: "wrong password" and  exit                   
					CallbackShowMessageBox( (UINTN)gInvalidPasswordFailMsgBox, MSGBOX_TYPE_OK );
					AbortUpdate = TRUE;
				}
			}
		}
	}
	if(AbortUpdate == FALSE)
	{
Password:
		//ask for new password(1)
		Status = _DoPopupEdit( popuppassword, (IsShowPromptStringAsTitle() ? STRING_TOKEN(STR_NEW_PSWD_LABEL): STRING_TOKEN(STR_NEW_PSWD)), &NewPswd);

        if(!Status)
        {
			NewPwLen = EfiStrLen(NewPswd);
			//EIP-39764 : non case sensitive support during setting password
			//EIP106950
			if (
            (IsPasswordSupportNonCaseSensitive ()) && 
            (NewPwLen != 0) &&
            ( (VARIABLE_ID_AMITSESETUP == popuppassword->ControlData.ControlVariable) || (VARIABLE_ID_IDE_SECURITY == popuppassword->ControlData.ControlVariable) )
            )
         {
				UpdatePasswordToNonCaseSensitive (NewPswd, NewPwLen);
			}
			if (VARIABLE_ID_IDE_SECURITY != popuppassword->ControlData.ControlVariable)
			{
				if (PopupPasswordCheckInstalled (popuppassword))
				{
				 // Override the minmax validation for password clearing
					if(NewPwLen == 0) 
					{
						//EIP-116315 password string Starts
						if ( IsShowPromptStringAsTitle() )
						{
							CHAR16 *temptext = NULL, *tText = NULL;
							CHAR16 *tempTitle = NULL;
							UINTN strlen = 0;

							//Taking backup of original StringID
							orgtext = ((AMI_IFR_MSGBOX*)(gClearLabelPasswordMsgBox))->Text;

							//Get TSE string
							temptext = HiiGetString( (VOID*)(UINTN)INVALID_HANDLE, orgtext);
							strlen = EfiStrLen(temptext);

							tempTitle = EfiLibAllocateZeroPool((strlen+2)*sizeof(CHAR16));
							
							if (NULL == tempTitle)
								return EFI_OUT_OF_RESOURCES;

							EfiStrCpy (tempTitle,temptext);
							strlen = EfiStrLen(tempTitle);
							
							MemFreePointer( (VOID **)&temptext );

							//Get prompt string from controlptr
							temptext = HiiGetString( popuppassword->ControlData.ControlHandle, UefiGetPromptField(popuppassword->ControlData.ControlPtr));
							strlen = EfiStrLen(temptext+2);

							tempTitle = MemReallocateZeroPool (
														tempTitle,
														( (EfiStrLen (tempTitle) + 2) * sizeof (CHAR16) ),
														( ((EfiStrLen (tempTitle) + 2) * sizeof (CHAR16)) + ((EfiStrLen (temptext) + 2) * sizeof (CHAR16)) )    //2 for /n and NULL character
														);

							if (NULL == tempTitle)
								return EFI_OUT_OF_RESOURCES;

							//Eliminate white space character if any precedes
							tText = temptext;
							while(*temptext == L' ')
							{
								temptext++;
							}

							//Appending tse string with controlptr prompt string
							EfiStrCat (tempTitle,temptext);
							EfiStrCat (tempTitle,L"?");

							//Adding string to hiistring
							newtoken = HiiAddString( gHiiHandle, tempTitle );

							//Setting new stringID as current stringID
							((AMI_IFR_MSGBOX*)(gClearLabelPasswordMsgBox))->Text = newtoken;

							MemFreePointer( (VOID **)&tText );
							MemFreePointer( (VOID **)&tempTitle );
						}
						//EIP-116315 password string. Ends

						//Report Message box for Clearing Old password
						if(CallbackShowMessageBox( (IsShowPromptStringAsTitle() ? (UINTN)gClearLabelPasswordMsgBox : (UINTN)gClearPasswordMsgBox), MSGBOX_TYPE_YESNO )!= MSGBOX_YES)
						{
							if ( IsShowPromptStringAsTitle() )
							{
								//Resetting original token
								((AMI_IFR_MSGBOX*)(gClearLabelPasswordMsgBox))->Text = orgtext;
								//Delete created token
								HiiRemoveString(gHiiHandle, newtoken);
							}

							goto Password;
							//Status = EFI_UNSUPPORTED; //Do not clear the password
						} 
						else 
						{
							if ( IsShowPromptStringAsTitle() )
							{
								//Resetting original token
								((AMI_IFR_MSGBOX*)(gClearLabelPasswordMsgBox))->Text = orgtext;
								//Delete created token
								HiiRemoveString(gHiiHandle, newtoken);
							}

							ConfirmNewPswd = EfiLibAllocateZeroPool( sizeof(CHAR16) );
							
							if(ConfirmNewPswd) 
							{
								*ConfirmNewPswd = L'\0'; //Set confirmation password to null string
							} 
							else 
							{
								Status = EFI_OUT_OF_RESOURCES;
							}
						}
					}
				}
			}
			if( 
				NewPwLen && 
				( (NewPwLen < (UINT8)UefiGetMinValue (popuppassword->ControlData.ControlPtr)) ||
				  (NewPwLen > (UINT8)UefiGetMaxValue (popuppassword->ControlData.ControlPtr)) )
				)
            {
                //Report Message box
				CallbackShowMessageBox( (UINTN)gInvalidRangeFailMsgBox, MSGBOX_TYPE_OK );
                Status = EFI_UNSUPPORTED;
            }
        }
		// ask for new password(2)again
		if ( ((!Status) && (NewPwLen != 0)) || ((VARIABLE_ID_IDE_SECURITY == popuppassword->ControlData.ControlVariable) && (!Status)) )
		{
			Status = _DoPopupEdit(  popuppassword, (IsShowPromptStringAsTitle() ? STRING_TOKEN(STR_CONFIRM_NEW_PSWD_LABEL) : STRING_TOKEN(STR_CONFIRM_NEW_PSWD)), &ConfirmNewPswd);			
		}

		if ( !Status )
		{
			//EIP-39764 : non case sensitive support during setting password
			//EIP106950
			if (
					(IsPasswordSupportNonCaseSensitive ()) &&
					( NULL!=ConfirmNewPswd ) && (EfiStrLen (ConfirmNewPswd)) && //EIP-127023 Avoid crashing when give empty password
					( (VARIABLE_ID_AMITSESETUP == popuppassword->ControlData.ControlVariable) || (VARIABLE_ID_IDE_SECURITY == popuppassword->ControlData.ControlVariable) )
            )
         {
				NewPwLen = EfiStrLen (ConfirmNewPswd);
				UpdatePasswordToNonCaseSensitive (ConfirmNewPswd, NewPwLen);
			}
		    if ( ( NULL!=ConfirmNewPswd ) && EfiStrCmp(NewPswd, ConfirmNewPswd)==0 ) //EIP-127023  Avoid crashing when give empty password
		    {
				//EIP-75521 Support for Interactive Password control
				if(popuppassword->Text != NULL){
					MemFreePointer( (VOID **)&popuppassword->Text );
				}
				popuppassword->Text = (CHAR16 *) EfiLibAllocateZeroPool((NewPwLen + 1) * sizeof(CHAR16));
				EfiStrCpy(popuppassword->Text, NewPswd);

				//save new password
                if ( ( popuppassword->Callback != NULL ) && ( popuppassword->Cookie != NULL ) )
				{
                    VOID *ifrData = popuppassword->ControlData.ControlPtr;
					CALLBACK_PASSWORD *callbackData = (CALLBACK_PASSWORD *)popuppassword->Cookie;

					callbackData->Variable = popuppassword->ControlData.ControlVariable;
					callbackData->Offset = UefiGetQuestionOffset(ifrData);
					callbackData->Length = (UINT8)UefiGetMaxValue(ifrData) * sizeof(CHAR16);
					callbackData->Data = (VOID *)NewPswd;
					SavePswdString(&(popuppassword->ControlData),NewPswd);
					UefiPreControlUpdate(&(popuppassword->ControlData));
					popuppassword->Callback( popuppassword->Container,popuppassword, popuppassword->Cookie );

					PopupPwdUpdateIDEPwd ();
				}


				//For interactive control invoke the formcallback function.
				if(UefiIsInteractive(&popuppassword->ControlData))
				{
					VOID *Handle = popuppassword->ControlData.ControlHandle;
					UINT16 Key = UefiGetControlKey(&(popuppassword->ControlData));
					CONTROL_DATA *Control = (CONTROL_DATA *)NULL;

					//Call the callback passing the input value and value size.
					Status = CallFormCallBack( &(popuppassword->ControlData),Key,0,AMI_CALLBACK_CONTROL_UPDATE);

					Control = GetUpdatedControlData((CONTROL_DATA*)popuppassword, CONTROL_TYPE_PASSWORD, Handle, Key);
					if(Control == NULL){ //Control deleted.
						return EFI_SUCCESS;
					}
					if(Control != (CONTROL_DATA *)popuppassword){
						popuppassword = (POPUP_PASSWORD_DATA *)Control; //Control Updated.
					}
				}

				popuppassword->ControlActive = FALSE;
            }
			else
			{
			    CallbackShowMessageBox( (UINTN)gInvalidPasswordFailMsgBox, MSGBOX_TYPE_OK );
			}
	    }
	}
	StringZeroFreeMemory ((VOID **)&Text);		//EIP67735 zeroing the password prompt memories
	StringZeroFreeMemory ((VOID **)&NewPswd);
	StringZeroFreeMemory ((VOID **)&ConfirmNewPswd);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupPasswordHandleAction
//
// Description:	function to handle the password actions
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, , ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _PopupPasswordHandleAction( POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT8 u8ChkResult;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	   return Status;
	
    u8ChkResult = CheckControlCondition( &popuppassword->ControlData );
	 
	 //Not to perform action for control when token TSE_SETUP_GRAYOUT_SELECTABLE is enable to set focus for GrayoutIf control
    if ( IsGrayoutSelectable() && (COND_GRAYOUT == u8ChkResult) ) {
        return EFI_UNSUPPORTED;
    }

	if ( Data->Input.Type == ACTION_TYPE_KEY )
    {
        CONTROL_ACTION Action;

        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);

        if(ControlActionSelect == Action)
        {
			if(UefiIsInteractive(&popuppassword->ControlData))
				if(PopupPasswordFormCallback(&(popuppassword->ControlData),UefiGetControlKey(&(popuppassword->ControlData)),0) == EFI_SUCCESS)
					return EFI_SUCCESS;

            return _PopupPasswordActivate(popuppassword);
        }
    }

    if(Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		if(ControlActionSelect == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
		{
			
			//check whether MouseTop is within the Height and Width of Password Control or not
			if((Data->Input.Data.MouseInfo.Top >= (UINT32)popuppassword->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(popuppassword->Top+popuppassword->Height)) &&
			  (Data->Input.Data.MouseInfo.Left >= (UINT32)popuppassword->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(popuppassword->Left+popuppassword->Width)))//EIP-123727
			{
				if(UefiIsInteractive(&popuppassword->ControlData))
					if(PopupPasswordFormCallback(&(popuppassword->ControlData),UefiGetControlKey(&(popuppassword->ControlData)),0) == EFI_SUCCESS)
						return EFI_SUCCESS;

	                return _PopupPasswordActivate(popuppassword);
	        }
		}
	}
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordHandleAction
//
// Description:	Function to handle the PopupPassword Actions
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordHandleAction( POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	
	Status = PopupPwdHandleActionOverRide(popuppassword, Data);

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordSetFocus
//
// Description:	Function to set focus
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, BOOLEAN focus
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordSetFocus(POPUP_PASSWORD_DATA *popuppassword, BOOLEAN focus)
{
    UINT8 u8ChkResult;

	if(focus != FALSE)
	{
        u8ChkResult = CheckControlCondition( &popuppassword->ControlData );
		if ( ((u8ChkResult != COND_NONE) && (u8ChkResult != COND_GRAYOUT)) ||
             (!IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT)) )
			return EFI_UNSUPPORTED;
	}

	if( !(popuppassword->ControlFocus && focus) )
		popuppassword->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordSetPosition
//
// Description:	Function to set position.
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordSetPosition(POPUP_PASSWORD_DATA *popuppassword, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( (CONTROL_DATA*)popuppassword, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordSetDimensions(POPUP_PASSWORD_DATA *popuppassword, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( (CONTROL_DATA*) popuppassword, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordSetAttributes(POPUP_PASSWORD_DATA *popuppassword, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes(  (CONTROL_DATA*)popuppassword, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordGetControlHeight
//
// Description:	function to get the height of the label
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, frame, UINT16 *height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordGetControlHeight(POPUP_PASSWORD_DATA *popuppassword, VOID *frame, UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
	
		Width = ((FRAME_DATA*)frame)->FrameData.Width - 2;

		text = HiiGetString( popuppassword->ControlData.ControlHandle, UefiGetPromptField(popuppassword->ControlData.ControlPtr));
		if ( text == NULL )
			return EFI_OUT_OF_RESOURCES;
	
		newText = StringWrapText( text, Width, height );
	
	    (*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
		MemFreePointer( (VOID **)&text );
	}
	else
	{
		*height = 1;
	}
	return EFI_SUCCESS;
}





//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_CBPopupEdit
//
// Description:	Function for PopupEdit callback.
//
// Input:		VOID *container, VOID *object, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _CBPopupEdit(VOID *container, VOID *object, VOID *cookie)
{
	EFI_STATUS Status = EFI_SUCCESS;
	if(cookie!=NULL)
	{

		res=0;
	}
	else
 	   res=1; // exit with no changes to string

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupEditGetValue
//
// Description:	Function to get edit value.
//
// Input:		POPUPEDIT_DATA *popupedit
//
// Output:		UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _PopupEditGetValue( POPUPEDIT_DATA *popupedit )
{
	ACTION_DATA *action = gApp->Action;
	EFI_STATUS 	Status = EFI_SUCCESS;//EIP:67695
	BOOLEAN 	DrawCursor = TRUE;//EIP:67695
	INT32  	MousePointerX = 0,MousePointerY = 0,MousePointerZ = 0; //EIP-111918: Modified Declaration for GCC Build 
	
	gPopupEdit.SetCallback( popupedit, NULL,(OBJECT_CALLBACK) _CBPopupEdit, &gPopupEditCb );
	gPopupEdit.SetDimensions( (CONTROL_DATA*)popupedit, popupedit->Width , popupedit->Height );
	res = (UINT8)-1;

	SetPwdKeyboardLayout();//EIP-88912
	TSEStringReadLoopEntryHook();

	while ( res == (UINT8)-1 )
	{
		if ( action->Input.Type != ACTION_TYPE_NULL )
			gAction.ClearAction( action );

		GetCoordinates (&MousePointerX, &MousePointerY, &MousePointerZ);
		if (gST->ConOut)
		{
			if ( 	
				( ((MousePointerX/HiiGetGlyphWidth ()) <= (UINT32)gST->ConOut->Mode->CursorColumn+1) && ((MousePointerX/HiiGetGlyphWidth ()) >= (UINT32)gST->ConOut->Mode->CursorColumn-1) ) && 
				( ((MousePointerY/HiiGetGlyphHeight ()) <= (UINT32)gST->ConOut->Mode->CursorRow+1) && ((MousePointerY/HiiGetGlyphHeight ()) >= (UINT32)gST->ConOut->Mode->CursorRow-1) )			//EIP79486 Stop the mouse if mouse poiner is over the text cursor useful for avoiding corruption
				)
				MouseStop ();
			else
			{
				if ( !IsMouseOnSoftkbd() ) //EIP-164232 
					MouseFreeze ();
			}
		}

		gPopupEdit.Draw( popupedit );
		DoRealFlushLines();

		if (IsTSECursorSupport())//EIP-91364
		{
			if (TRUE == DrawCursor)	//EIP:67695 Enabling at valid times
			{
				gST->ConOut->SetAttribute (gST->ConOut, popupedit->FGColor | popupedit->BGColor);
				gST->ConOut->SetCursorPosition (gST->ConOut, popupedit->Left + EfiStrLen (popupedit->Text)+1, popupedit->Height- (2+ (popupedit->TextWidth/popupedit->Width +1))+popupedit->Top+1);
				gST->ConOut->EnableCursor (gST->ConOut, TRUE);
				DrawCursor = FALSE;
			}
		}
		if  ( !IsMouseOnSoftkbd() ) //EIP-164232 Avoid mouse flickers If mouse pointer is on softkbd area
			MouseRefresh();


		if ( gAction.GetAction( action ) != EFI_SUCCESS )
			continue;
		Status = gPopupEdit.HandleAction( popupedit, action );
		if (IsTSECursorSupport() && !(EFI_ERROR (Status)))//EIP:67695
		{
			DrawCursor = TRUE;			//EIP:67695 If any valid action performed then draw the cursor, usefull for blinking
		}
	}
	TSEStringReadLoopExitHook();
	ResetPwdKeyboardLayout();//EIP-88912

	return res;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DoPopupEdit
//
// Description:	function to perform the edit operations on popup
//
// Input:	POPUP_PASSWORD_DATA *PopupPassword, UINT16 Title, CHAR16 **Text
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _DoPopupEdit( POPUP_PASSWORD_DATA *PopupPassword, UINT16 Title, CHAR16 **Text)
{
	static UINT8 gIFRPopupEdit[50];
	EFI_STATUS Status= EFI_SUCCESS;
	UINT8 retValue = (UINT8)-1;
	UINT16 newtoken = 0;

	POPUPEDIT_DATA *popupedit = NULL;

	CONTROL_INFO dummy;
    BOOLEAN 		PreviousCursorState = gST->ConOut->Mode->CursorVisible;//EIP:67695

	Status = gPopupEdit.Create( (void**)&popupedit );
	if ( EFI_ERROR( Status ) )
		return Status;

	MemSet( &dummy, sizeof(dummy), 0 );

    MemCopy( &gIFRPopupEdit, (VOID*)PopupPassword->ControlData.ControlPtr, UefiGetIfrLength(PopupPassword->ControlData.ControlPtr) );

	//EIP-116315 password string. Starts
	//To show Control prompt string as PopupPassword String instead from AMITSEStr.uni file
	if (IsShowPromptStringAsTitle())
	{
		UINTN strlen = 0;
		CHAR16 *temptext, *tempTitle = NULL, *tText = NULL;		
		dummy.ControlHandle = PopupPassword->ControlData.ControlHandle;
		
		//Get TSE string
		temptext = HiiGetString( (VOID*)(UINTN)INVALID_HANDLE, Title);
		strlen = EfiStrLen(temptext);

		tempTitle = EfiLibAllocateZeroPool((strlen+2)*sizeof(CHAR16));
		
		if (NULL == tempTitle)
			return EFI_OUT_OF_RESOURCES;

		EfiStrCpy (tempTitle,temptext);
		strlen = EfiStrLen(tempTitle);

		MemFreePointer( (VOID **)&temptext );

		//Get Prompt String from ControlPtr
		temptext = HiiGetString( PopupPassword->ControlData.ControlHandle, UefiGetPromptField(PopupPassword->ControlData.ControlPtr));
		strlen = EfiStrLen(temptext+2);

		tempTitle = MemReallocateZeroPool (
									tempTitle,
									( (EfiStrLen (tempTitle) + 2) * sizeof (CHAR16) ),
									( ((EfiStrLen (tempTitle) + 2) * sizeof (CHAR16)) + ((EfiStrLen (temptext) + 2) * sizeof (CHAR16)) )    //2 for /n and NULL character
									);

		if (NULL == tempTitle)
			return EFI_OUT_OF_RESOURCES;

		//Eliminate white space character if any precedes
		tText = temptext;
		while(*temptext == L' ')
		{
			temptext++;
		}

		//Appending TSE string with controlptr string
		EfiStrCat (tempTitle,temptext);
		
		//Create new token for newly created string
		newtoken = HiiAddString( PopupPassword->ControlData.ControlHandle, tempTitle );

		//Set control prompt with newly created token
		UefiSetPromptField ((VOID*)&gIFRPopupEdit,newtoken);

		MemFreePointer( (VOID **)&tText );
		MemFreePointer( (VOID **)&tempTitle );
	}
	else
	{
		dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;
		UefiSetPromptField ((VOID*)&gIFRPopupEdit,Title);
	}
	//EIP-116315 password string. Ends

	dummy.ControlPtr = (VOID*)&gIFRPopupEdit;
	dummy.ControlFlags.ControlVisible = TRUE;
   
	//gPopupEdit.SetTitle(popupedit,Title);
    gPopupEdit.SetText(popupedit,*Text);
	gPopupEdit.SetType( popupedit, POPUPEDIT_TYPE_PASSWORD );
	Status = gPopupEdit.Initialize( popupedit, &dummy );
	if ( EFI_ERROR( Status ) )
		goto Done;

	//gPopupEdit.SetType( popupedit, POPUPEDIT_TYPE_PASSWORD );
	retValue = (UINT8)_PopupEditGetValue( popupedit );
	if (IsTSECursorSupport())//EIP-91364
	{
		gST->ConOut->EnableCursor (gST->ConOut, PreviousCursorState);//EIP:67695
	}
	if(retValue ==0)
	{
		// string changed, save to nvram or do whatever needs to be done
	    MemFreePointer( (VOID **)Text );
	    *Text = EfiLibAllocateZeroPool( (gPopupEditCb.Length+1) * sizeof(CHAR16) );
	     if ( Text == NULL )
		return EFI_OUT_OF_RESOURCES;

	    EfiStrCpy( *Text, gPopupEditCb.Data );			

	}
	else
		Status = EFI_UNSUPPORTED;
Done:
	gPopupEdit.Destroy( popupedit, TRUE );
	if ( IsShowPromptStringAsTitle() )
		HiiRemoveString(gHiiHandle, newtoken);//Delete created token
	return Status;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
