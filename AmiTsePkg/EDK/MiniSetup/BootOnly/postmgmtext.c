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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/postmgmtext.c $
//
// $Author: Premkumara $
//
// $Revision: 3 $
//
// $Date: 5/28/12 11:27a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		PostMgmtExt.c
//
// Description:	This file contains code extended post management operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
//TH0053>>>
#include <Protocol\GenericElogProtocol.h>
#include <AmiGpnvErrorLoggingPkg\Include\Protocol\SmbiosElogSupport.h>
//TH0053<<<

////////////////////////////////////////////////////////////////////
//		Function Declarations
////////////////////////////////////////////////////////////////////
//EIP-70175 Set Password Popup Window and PopupTextBox color
UINT8 GetPasswordPopupTextBoxColor(VOID);
UINT8 GetPasswordPopupWindowColor(VOID);
UINT8 GetPasswordReportInboxcolor(VOID);
BOOLEAN IsMouseSupported(VOID);
BOOLEAN IsSoftKbdSupported(VOID);
VOID SetPwdKeyboardLayout(VOID);//EIP-88912
VOID ResetPwdKeyboardLayout(VOID);//EIP-88912
BOOLEAN IsTSECursorSupport(); //EIP-91364
void 			ClearGrphxScreen (void);
BOOLEAN  IsTSEMultilineControlSupported (VOID); //EIP-135665 Multiline support for Password and String control
EFI_STATUS SaveCurrentTextGOP ( UINTN *currenttextModeCols, UINTN *currenttextModeRows, UINT32 *currentGOPMode );//EIP-197833
EFI_STATUS RestoreTextGOPMode ( UINTN prevTextModeCols, UINTN prevTextModeRows, UINT32 prevGOPMode );

VOID InvalidateStatusInBgrtWrapper (VOID);
//TH0160>>>
VOID *SavePostScreen( UINTN *SizeOfX, UINTN *SizeOfY );
VOID RestorePostScreen( VOID *UgaBlt, UINTN SizeOfX, UINTN SizeOfY );
//TH0160<<<

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetSystemAccessValue
//
// Description:	function to set the system access  Value
//
// Input:	UINT8 sysAccessValue
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetSystemAccessValue(UINT8 sysAccessValue)
{
	EFI_GUID sysAccessGuid = SYSTEM_ACCESS_GUID;
	if(NoVarStoreSupport())
	{
		NoVarStoreUpdateSystemAccess(sysAccessValue);
	}
	else
		VarSetNvramName( L"SystemAccess", &sysAccessGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &sysAccessValue, sizeof(sysAccessValue) );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetPasswordType
//
// Description:	function to set the type of password
//
// Input:	UINT32 PasswordType
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetPasswordType( UINT32 PasswordType )
{
	UINT8 sysAccessValue = SYSTEM_PASSWORD_ADMIN;

	gPasswordType = PasswordType;

	if ( gPasswordType == AMI_PASSWORD_USER )
		sysAccessValue = SYSTEM_PASSWORD_USER;

	if ( gPasswordType != AMI_PASSWORD_NONE )
	{
		if(ItkSupport())
		{
			SetSystemAccessValueItk(sysAccessValue);
		}
		else
		{	
			SetSystemAccessValue(sysAccessValue);
		}
	}

	return;
}
/*Removed from BootOnly
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckEnableQuietBoot
//
// Description:	Function to check the quick boot enable option
//
// Input:	void
//
// Output:	void
//
// Notes		:	if NVRAM variable field AMISilentBoot = 0, then disable silent
//					mode else enable In case of error reading the Setup variable,
//					then return as silent boot disable
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CheckEnableQuietBoot( VOID )
{
#ifndef STANDALONE_APPLICATION
	if(ItkSupport())
	    gQuietBoot = TRUE;
	else
	{
		UINT8 *setupvar=NULL;
		UINT8 *setup=NULL;
		UINTN size = 0;
		UINTN offset;
	
		GetAMITSEVariable((AMITSESETUP**)&setup,&setupvar,&size);
	
		offset = STRUCT_OFFSET( AMITSESETUP, AMISilentBoot );
		if ( ( setup == NULL ) || ( size < offset ) )
			gQuietBoot = FALSE;
		else
			gQuietBoot = (BOOLEAN)setup[offset];
	
		if(setupvar)
			MemFreePointer( (VOID **)&setupvar );
		else
			MemFreePointer( (VOID **)&setup );
	}
#endif //#ifndef STANDALONE_APPLICATION
}
*/
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckSystemPassword
//
// Description:	Function to check the system password
//
// Input:	UINT32 EmptyPasswordType, UINTN *NoOfRetries, UINTN *TimeOut
//
// Output:	PasswordCheck
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 CheckSystemPassword(UINT32 EmptyPasswordType, UINTN *NoOfRetries, UINTN *TimeOut)
{
	UINTN PasswordCheck = AMI_PASSWORD_NONE;
	UINTN CurrXPos, CurrYPos;
	CHAR16 *PasswordEntered;
	UINT32 PasswordInstalled;
	SCREEN_BUFFER *TempScreenBuffer = NULL;
	CHAR16 *BoxStr=NULL;
	UINTN BoxLength = TsePasswordLength;

	UINTN currenttextModeCols = 0, currenttextModeRows = 0;
	UINT32 currentGOPMode = 0;

	EFI_STATUS Status = EFI_SUCCESS;
	//TH0160>>>   
		VOID *UgaBlt = NULL;   
		UINTN SizeOfX=0, SizeOfY=0;   
//TH0160<<< 
  //TH0053>>>
	EFI_GUID gEfiGenericElogProtocolGuid = EFI_SM_ELOG_PROTOCOL_GUID;
	EFI_SM_ELOG_PROTOCOL	   *mGenericElogProtocol = NULL;
	UINT64                     RecordId;
	UINT8 Record = EFI_EVENT_LOG_TYPE_PASSWORD_INVALIDED;   //Example for Error Type. You could modify for need.
	//TH0053<<<
	
	EFI_GUID AmitsePasswordPromptEnterGuid = AMITSE_PASSWORD_PROMPT_ENTER_GUID;
	EFI_GUID AmitsePasswordPromptExitGuid = AMITSE_PASSWORD_PROMPT_EXIT_GUID;
	EFI_GUID AmitseUserPasswordValidGuid = AMITSE_USER_PASSWORD_VALID_GUID;
	EFI_GUID AmitseAdminPasswordValidGuid = AMITSE_ADMIN_PASSWORD_VALID_GUID;
	EFI_GUID AmitseInvalidPasswordGuid = AMITSE_INVALID_PASSWORD_GUID;

    EfiLibNamedEventSignal (&AmitsePasswordPromptEnterGuid);
	// Report the Status code DXE_SETUP_VERIFYING_PASSWORD
	EfiLibReportStatusCode(EFI_PROGRESS_CODE, DXE_SETUP_VERIFYING_PASSWORD,0,NULL,NULL);

    CheckForKeyHook( (EFI_EVENT)NULL, NULL );
	if( IsMouseSupported() && IsSoftKbdSupported())
    	CheckForClickHook( (EFI_EVENT)NULL, NULL );//EIP 62763 : Checking for mouse and softkbd.

	gST->ConIn->Reset( gST->ConIn, FALSE );

  UgaBlt = SavePostScreen(&SizeOfX, &SizeOfY);	//TH0160
    // Copy the contents of Active buffer so password code can use it
	TempScreenBuffer = EfiLibAllocateZeroPool( sizeof(SCREEN_BUFFER) );
	if(TempScreenBuffer != NULL)
		MemCopy(TempScreenBuffer, gActiveBuffer, sizeof(SCREEN_BUFFER));

    BoxStr = HiiGetString( gHiiHandle, STRING_TOKEN(STR_ERROR_PSWD));
    if ( BoxStr ){
        if ((TestPrintLength( BoxStr ) / NG_SIZE) > BoxLength ){
            BoxLength = TestPrintLength( BoxStr ) / NG_SIZE;
        }
    }
    MemFreePointer((VOID**) &BoxStr );

	SaveCurrentTextGOP (&currenttextModeCols, &currenttextModeRows, &currentGOPMode); //EIP-197833 Saving current text mode and GOP before set 100x31 and 800x600 text mode and resolution respectively

    //Draw password window
    _DrawPasswordWindow(STRING_TOKEN(STR_PASSWORD_PROMPT), BoxLength, &CurrXPos, &CurrYPos);

    PasswordEntered = EfiLibAllocatePool((TsePasswordLength + 1)*sizeof(CHAR16));
    PasswordInstalled = PasswordCheckInstalled();
    PasswordCheck = AMI_PASSWORD_NONE;

    //Give retries based on NoOfRetries
    while(*NoOfRetries)
    {
	//EIP:51621 Handling ESC key for the the input password
		Status = _GetPassword (PasswordEntered, TsePasswordLength, CurrXPos, CurrYPos, TimeOut);
		if (EFI_ABORTED == Status)		//Status should be aborted, success or timeout. If time out we should not go for another iteration
		{								//If user presses ESC TSE handle that as invalid case so let it for another iteration.	
			continue;					
		}
		else if (EFI_TIMEOUT == Status)
		{
			break;						//EIP 62754; Breaking if time out occurs
		}
        PasswordCheck = PasswordAuthenticate( PasswordEntered );
        PasswordCheck &= PasswordInstalled;

        if((PasswordEntered[0] == L'\0') && (AMI_PASSWORD_NONE == PasswordCheck))
        {
            //Honour EmptyPasswordType
            if(
                (!(PasswordInstalled & AMI_PASSWORD_USER ))&&
                (EmptyPasswordType & AMI_PASSWORD_USER)
                )
                PasswordCheck = AMI_PASSWORD_USER;
            if(
                (!(PasswordInstalled & AMI_PASSWORD_ADMIN ))&&
                (EmptyPasswordType & AMI_PASSWORD_ADMIN)
                )
                PasswordCheck = AMI_PASSWORD_ADMIN;
        }

        if(AMI_PASSWORD_NONE != PasswordCheck)
            break;
        else
        {
            if (1 == *NoOfRetries) // Do not wait for key if it is the lastest try
                _ReportInBox( TsePasswordLength, STRING_TOKEN(STR_ERROR_PSWD), CurrXPos, CurrYPos, FALSE);
            else
                _ReportInBox( TsePasswordLength, STRING_TOKEN(STR_ERROR_PSWD), CurrXPos, CurrYPos, TRUE);
        }

        (*NoOfRetries)--;
    }

    MemFreePointer((VOID **)&PasswordEntered);

    if(AMI_PASSWORD_NONE == PasswordCheck)
    {
        EfiLibNamedEventSignal (&AmitseInvalidPasswordGuid);
		    //TH0053  EfiLibReportStatusCode(EFI_ERROR_CODE| EFI_ERROR_MAJOR, DXE_INVALID_PASSWORD,0,NULL,NULL);
        //TH0053>>>
        Status = pBS->LocateProtocol (
                                &gEfiGenericElogProtocolGuid, 
                                NULL,(VOID **)&mGenericElogProtocol ); 

        if(!EFI_ERROR(Status)) {	     
        	Status = mGenericElogProtocol->SetEventLogData(
											mGenericElogProtocol,
											(UINT8*)&Record,
											EfiElogSmSMBIOS,
											FALSE,
											sizeof(UINT8),
											&RecordId);
        }   	    
        //TH0053<<<
        //Report Invalid password
        _ReportInBox( TsePasswordLength, STRING_TOKEN(STR_ERROR_PSWD), CurrXPos, CurrYPos, FALSE);
    }
    else
    {
        MouseStop();
    	ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );
		DoRealFlushLines();
        MouseRefresh();
        if(IsMouseSupported()&& IsSoftKbdSupported())//Initializing the mouse at post when mouse and softkbd present
        	MouseInit();
        if (!( PasswordInstalled & AMI_PASSWORD_ADMIN ))
		    PasswordCheck = AMI_PASSWORD_ADMIN;
	    SetPasswordType( (UINT32)PasswordCheck );

      	if(AMI_PASSWORD_ADMIN == PasswordCheck)
    		EfiLibNamedEventSignal (&AmitseAdminPasswordValidGuid);

    	if(AMI_PASSWORD_USER == PasswordCheck)
		    EfiLibNamedEventSignal (&AmitseUserPasswordValidGuid);
    }

	RestoreTextGOPMode (currenttextModeCols, currenttextModeRows, currentGOPMode); //EIP-197833 Restoring previous text mode and GOP
    EfiLibNamedEventSignal (&AmitsePasswordPromptExitGuid);

   	//Copy the original active buffer contents
	if(TempScreenBuffer != NULL)
	{
		MemCopy(gActiveBuffer, TempScreenBuffer, sizeof(SCREEN_BUFFER));
		MemFreePointer((VOID **) &TempScreenBuffer);
	}
	
//TH0160>>>	
	    if (*NoOfRetries != 0)
	    RestorePostScreen (UgaBlt, SizeOfX, SizeOfY);
	    else MemFreePointer((VOID **) &UgaBlt);
//TH0160<<<
	
	return ((UINT32)PasswordCheck);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DrawPasswordWindow
//
// Description:	Function to draw password window with attributes
//
// Input:	UINT16 PromptToken, UINTN PasswordLength, UINTN *CurrXPos, UINTN *CurrYPos
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DrawPasswordWindow(UINT16 PromptToken, UINTN PasswordLength, UINTN *CurrXPos, UINTN *CurrYPos)
{
	UINTN	DlogWidth = PasswordLength + 4;
	UINTN Height=1;
   	CHAR16 *PasswordPrompt;
	EFI_STATUS Status = EFI_SUCCESS;
	
   InvalidateStatusInBgrtWrapper ();
   
   Status =	InitEsaTseInterfaces ();	

   if (!EFI_ERROR (Status))
	{
		gEsaInterfaceForTSE->DrawPasswordWindow (PromptToken, PasswordLength, CurrXPos, CurrYPos);
	}
	else
	{
#ifndef STANDALONE_APPLICATION
		if ( gConsoleControl != NULL )
			gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenText );
#endif

    //Set desired Mode.
#if !APTIO_4_00
		SetDesiredTextMode();
#else
		//  In Aptio use the Text mode as is it in post screen 
		if(gST->ConOut!=NULL)
		{
			UINTN Rows, Cols;
			if(EFI_ERROR(gST->ConOut->QueryMode( gST->ConOut, gST->ConOut->Mode->Mode, &Cols, &Rows )))
			{ 
				gMaxRows = STYLE_STD_MAX_ROWS; 
				gMaxCols = STYLE_STD_MAX_COLS; 
			}
			 else if ((gMaxRows != Rows) || (gMaxCols != Cols))
			{
				//Setting the Desired text mode as is it in post screen 
				SetDesiredTextMode ();
			}
	
		}
		else
		{ 
			gMaxRows = STYLE_STD_MAX_ROWS; 
			gMaxCols = STYLE_STD_MAX_COLS; 
		}
	#endif
	if(IsMouseSupported()&& IsSoftKbdSupported())//Initializing the mouse at post when mouse and softkbd present
		MouseInit();
		MouseStop();
		// Clear the Screen
		ClearGrphxScreen ();//To clear screen while drawing logo at (0,0) co-ordinates
		ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY ); //EIP-135029,136209 To clear screen before showing passwordwindow
		DoRealFlushLines();
		MouseRefresh();
	
		PasswordPrompt = HiiGetString( gHiiHandle, PromptToken);
		if ( PasswordPrompt != NULL )
		{
			if ( (TestPrintLength(PasswordPrompt) / NG_SIZE +6) > DlogWidth )
				DlogWidth = TestPrintLength(PasswordPrompt) / NG_SIZE +6;
		}
		if (DlogWidth >= (gMaxCols-2)) //EIP-135665 If string is more than gMaxCols 80/100
		{
			if ( IsTSEMultilineControlSupported() ) //If multiline supported
				{
					Height=(DlogWidth / (gMaxCols-2))+(((DlogWidth % (gMaxCols-2)) > 0)?1:0);
					DlogWidth = gMaxCols-2;
				}
			else
				{
					DlogWidth = gMaxCols-2;
					PasswordPrompt[DlogWidth-4]=L'\0';
					PasswordPrompt[DlogWidth-5]=L'.';
					PasswordPrompt[DlogWidth-6]=L'.';
					PasswordPrompt[DlogWidth-7]=L'.';
				}
		}

		*CurrYPos = (gMaxRows - 5) / 2;
		*CurrXPos = (gMaxCols-2 - DlogWidth) / 2;
	
		//EIP-70175 Set Password Window color
		//DrawWindow( *CurrXPos, *CurrYPos, DlogWidth, 5, EFI_BACKGROUND_BLUE | EFI_WHITE, TRUE, FALSE );
		DrawWindow( *CurrXPos, *CurrYPos, DlogWidth, 4+Height, GetPasswordPopupWindowColor(), TRUE, FALSE );	
	
		if ( PasswordPrompt != NULL )
		{
			if ( IsTSEMultilineControlSupported() ) //If multiline supported
				DrawMultiLineStringWithAttribute ((*CurrXPos)+2, *CurrYPos, DlogWidth-3, Height, PasswordPrompt, 0);
			else
				DrawStringJustified( 0, gMaxCols-2, *CurrYPos, JUSTIFY_CENTER, PasswordPrompt );
		}
		MemFreePointer( (VOID **)&PasswordPrompt );

	    //Record position of the Box
   	*CurrXPos = ((gMaxCols - DlogWidth) / 2)+1; //EIP-173320 HDD password prompt issue
		*CurrYPos += Height+1;

		FlushLines( *CurrYPos - Height-1, *CurrYPos + 2);
	    MouseStop();
		DoRealFlushLines();
	    MouseRefresh();
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ReportInBox
//
// Description:	Function to report using Box
//
// Input:	UINTN PasswordLength, UINT16 BoxToken, UINTN CurrXPos,
//					UINTN CurrYPos, BOOLEAN bWaitForReturn
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _ReportInBox(
        UINTN PasswordLength,
        UINT16 BoxToken,
        UINTN CurrXPos,
        UINTN CurrYPos,
        BOOLEAN bWaitForReturn
        )
{
    CHAR16 *BoxStr=NULL;
   	EFI_INPUT_KEY Key;
   	EFI_STATUS Status = EFI_SUCCESS;
   	
	Status =	InitEsaTseInterfaces ();
	
	if (!EFI_ERROR (Status))
	{
		gEsaInterfaceForTSE->ReportInBox (
		        PasswordLength,
		        BoxToken,
		        CurrXPos,
		        CurrYPos,
		        bWaitForReturn
		        );
	}
	else
	{
	
		//Draw Box
		//EIP-70175 Set Password ReportInbox color
		//DrawBox( CurrXPos, CurrYPos,  PasswordLength, 1, EFI_BACKGROUND_BLUE | EFI_WHITE );
		DrawBox( CurrXPos, CurrYPos,  PasswordLength, 1, GetPasswordReportInboxcolor());
		
		//Draw Box string
		if(BoxToken != INVALID_TOKEN)
		{
			BoxStr = HiiGetString( gHiiHandle, BoxToken );
			DrawString( CurrXPos, CurrYPos, BoxStr);
		}
		 
		 SetPwdKeyboardLayout();//EIP-88912
		TSEStringReadLoopEntryHook();
	
		FlushLines( CurrYPos - 2, CurrYPos + 2 );
		MouseStop();
		DoRealFlushLines();
		MouseRefresh();
	
		if(bWaitForReturn)
		{
			MemFillUINT16Buffer(BoxStr, (TestPrintLength(BoxStr)/ NG_SIZE), L' ');
	
			Key.UnicodeChar = 0;
			do
			{
				gST->ConIn->ReadKeyStroke( gST->ConIn, &Key );
			} while( Key.UnicodeChar != CHAR_CARRIAGE_RETURN );
	
			DrawString( CurrXPos, CurrYPos, BoxStr);
			MemFreePointer((VOID **) &BoxStr);
		}
	
		TSEStringReadLoopExitHook();
		ResetPwdKeyboardLayout();//EIP-88912
	
		MemFreePointer((VOID **)&BoxStr);
	}
}

VOID SetPwdTimeOut( EFI_EVENT Event, BOOLEAN *timeout )
{
	if ( timeout != NULL )
		*timeout = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_GetPassword
//
// Description:	Function to get password from the user
//
// Input:	CHAR16 *PasswordEntered, UINTN PasswordLength, UINTN CurrXPos,
//					UINTN CurrYPos, UINTN *pTimeOut
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetPassword(
        CHAR16 *PasswordEntered,
        UINTN PasswordLength,
        UINTN CurrXPos,
        UINTN CurrYPos,
        UINTN *pTimeOut
        )
{
   	EFI_INPUT_KEY Key = {0,0};
	UINTN StrIndex;
    CHAR16 *StrStar;
    UINTN i;
    volatile BOOLEAN bTimeOut = FALSE;
    UINTN TimeOutValue;
    EFI_EVENT timer;
    EFI_STATUS Status;
    AMI_EFI_KEY_DATA    KeyData;
    EFI_TPL CurrentTpl = 0;
    
    //Spec recommends to use simple input protocol in application level. So changing TPL here. HDD module will call _GetPassword in notfiy TPL level.
	CurrentTpl = gBS->RaiseTPL( TPL_HIGH_LEVEL ); //we store the current TPL
	gBS->RestoreTPL( TPL_APPLICATION); //setting the TPL level as application Level TPL
	
	Status =	InitEsaTseInterfaces ();
	
	if (!EFI_ERROR (Status))
	{
		Status = gEsaInterfaceForTSE->GetPassword (
		        PasswordEntered,
		        PasswordLength,
		        CurrXPos,
		        CurrYPos,
		        pTimeOut
		        );
		goto DONE;
		
	}
	else
	{
		MemSet( PasswordEntered, (PasswordLength + 1)*sizeof(CHAR16), 0 );
		StrStar = EfiLibAllocatePool((PasswordLength + 1)*sizeof(CHAR16));
		StrIndex = 0;
		
		//EIP-70175 Set Password PopupTextBox color
		//DrawBox( CurrXPos, CurrYPos,  PasswordLength, 1, EFI_BACKGROUND_LIGHTGRAY | EFI_BLUE );
		DrawBox( CurrXPos, CurrYPos,  PasswordLength, 1, GetPasswordPopupTextBoxColor() );	
		
		FlushLines( CurrYPos, CurrYPos );
		MouseStop();
		DoRealFlushLines();
		MouseRefresh();
	
		SetPwdKeyboardLayout();//EIP-88912
	   TSEStringReadLoopEntryHook();
	
		if (IsTSECursorSupport()) //EIP-91364
		{
			gST->ConOut->SetCursorPosition( gST->ConOut, CurrXPos, CurrYPos);	//EIP:67695 Cursor support for msg boxes
			gST->ConOut->EnableCursor(gST->ConOut, TRUE);//EIP:67695 Enable Cursor support for msg boxes
		}
		do
		{
			TimeOutValue = pTimeOut ? *pTimeOut : 0;
	
			if(TimeOutValue)
			{
				timer = NULL;
				Status = TimerCreateTimer( &timer, (EFI_EVENT_NOTIFY)SetPwdTimeOut, (VOID *)&bTimeOut, TimerRelative, TimeOutValue * TIMER_ONE_SECOND, EFI_TPL_NOTIFY );
			}
	
			// While the timeout has not expired
			while ( ! bTimeOut )
			{
				Status = AMIReadKeyStroke(&Key,&KeyData);
				if ( !(EFI_ERROR(Status)) )
					break;
			}
	
			if(TimeOutValue)
				TimerStopTimer( &timer );
	
			if(bTimeOut)
			{
				Status = gST->ConIn->Reset( gST->ConIn, FALSE );
				MemFreePointer((VOID **)&StrStar);
				PasswordEntered[0] = L'\0';
				break;
			}
	
			switch (Key.UnicodeChar)
			{
				case CHAR_NULL:
					if (Key.ScanCode == SCAN_ESC) 
				{
					Status = gST->ConIn->Reset( gST->ConIn, FALSE );
						MemFreePointer((VOID **)&StrStar);
						PasswordEntered[0] = L'\0';
						TSEStringReadLoopExitHook();
						ResetPwdKeyboardLayout();//EIP-88912
					   Status =  EFI_ABORTED;
					   goto DONE;
				}
					if (Key.ScanCode != SCAN_NULL) {
						if(HelperIsPasswordCharValid(&Key,&KeyData,StrIndex,PasswordLength,&PasswordEntered[StrIndex]) == EFI_SUCCESS)
							StrIndex++;
					}
					else {
						InvalidActionHookHook();
					}
					break;
	
				case CHAR_CARRIAGE_RETURN:
					Status = gST->ConIn->Reset( gST->ConIn, FALSE );
				MemFreePointer((VOID **)&StrStar);
				TSEStringReadLoopExitHook();
				ResetPwdKeyboardLayout();//EIP-88912
				Status =  EFI_SUCCESS;
				goto DONE;
	
				case CHAR_BACKSPACE:
					if ( StrIndex != 0 )
						PasswordEntered[--StrIndex] = L'\0';	
					break;
				
				default:
					if(HelperIsPasswordCharValid(&Key,&KeyData,StrIndex,PasswordLength,&PasswordEntered[StrIndex]) == EFI_SUCCESS)
						StrIndex++;
					break; 
			}
			if ( StrIndex > PasswordLength  ) {
				InvalidActionHookHook();
			}
			//Draw stars for entered characters
			for ( i = 0; i < PasswordLength; i++ )
				StrStar[i] = (i<StrIndex) ? L'*': L' ';
			StrStar[PasswordLength] = L'\0';
	
			DrawString( CurrXPos, CurrYPos, StrStar );
			FlushLines( CurrYPos, CurrYPos );
			MouseStop();
			DoRealFlushLines();
	
			if (IsTSECursorSupport()) //EIP-91364
			{
				gST->ConOut->SetCursorPosition( gST->ConOut, ((PasswordLength!=StrIndex)?(CurrXPos + StrIndex):(CurrXPos + StrIndex-1)), CurrYPos);	//EIP:67695 For restricting the cursor within the limit
				gST->ConOut->EnableCursor(gST->ConOut, TRUE);		//EIP:67695 Enable Cursor support for msg boxes
			}
			MouseRefresh();
		}
		while( 1 );
	
		TSEStringReadLoopExitHook();
		ResetPwdKeyboardLayout();//EIP-88912
	
		//EIP-75379 Suppress the warnings from static code analyzer
		if (pTimeOut)
			*pTimeOut = 0;
		Status = EFI_TIMEOUT;
		goto DONE;
	}
DONE:
	gBS->RaiseTPL( TPL_HIGH_LEVEL ); // Raising the TPL before reverting back as TPL may be changes in between
	gBS->RestoreTPL( CurrentTpl );	//reverting back the original TPL
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
