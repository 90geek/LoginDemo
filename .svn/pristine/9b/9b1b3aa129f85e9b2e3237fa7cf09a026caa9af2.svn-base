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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/MessageBox.c $
//
// $Author: Arunsb $
//
// $Revision: 23 $
//
// $Date: 5/24/12 9:02a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		MessageBox.c
//
// Description:	This file contains code to handle Message Box operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


MSGBOX_METHODS gMsgBox =
{
	(OBJECT_METHOD_CREATE)MsgBoxCreate,
	(OBJECT_METHOD_DESTROY)MsgBoxDestroy,
	(OBJECT_METHOD_INITIALIZE)MsgBoxInitialize,
	(OBJECT_METHOD_DRAW)MsgBoxDraw,
	(OBJECT_METHOD_HANDLE_ACTION)MsgBoxHandleAction,
	(OBJECT_METHOD_SET_CALLBACK)MsgBoxSetCallback,
	(CONTROL_METHOD_SET_FOCUS)MsgBoxSetFocus,
	(CONTROL_METHOD_SET_POSITION)MsgBoxSetPosition,
	(CONTROL_METHOD_SET_DIMENSIONS)MsgBoxSetDimensions,
	(CONTROL_METHOD_SET_ATTRIBUTES)MsgBoxSetAttributes,
	(CONTROL_METHOD_GET_CONTROL_HIGHT)MsgBoxGetControlHight,
	MsgBoxSetType
};

MSGBOX_EX_CATAGORY gMsgBoxType = MSGBOX_EX_CATAGORY_NORMAL;

/////////////////////////////////////////////////
/////	Extern variables and functions
/////////////////////////////////////////////////
void ClearGrphxScreen (void);
BOOLEAN SingleClickActivation (VOID); //EIP-139608


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxCreate
//
// Description:	Function to Create Message Box, which uses the Popup functions.
//
// Input:	MSGBOX_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxCreate( MSGBOX_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(MSGBOX_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gPopup.Create( (void**)object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gMsgBox;

	// create the memo 
	gMemo.Create((void**)&((*object)->Memo));

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxDestroy
//
// Description:	Function to Destroy Message Box, which uses the Popup functions.
//
// Input:	MSGBOX_DATA *msgbox, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxDestroy( MSGBOX_DATA *msgbox, BOOLEAN freeMem )
{
	EFI_STATUS Status;

	if(NULL == msgbox)
	  return EFI_SUCCESS;
	
	Status = gPopup.Destroy( msgbox, FALSE );
	MemFreePointer( (VOID **)&(msgbox->Memo->ControlData.ControlPtr) );
	Status = gMemo.Destroy( msgbox->Memo, FALSE );

	if(msgbox->Title)
		MemFreePointer( (VOID **)&msgbox->Title );

	//EIP-197833 Restore saved screen only inside TSE
	if (TSE_POST_STATUS_IN_TSE == gPostStatus)
	{
		if (msgbox->ScreenBuf) //Restore If it has valid data
			RestoreScreen( msgbox->ScreenBuf );
	}

	if (freeMem)
	{
		if (NULL != msgbox->Legend)			//EIP 90379
		{
			MemFreePointer ((VOID **)&msgbox->Legend);//EIP-73236
		}
		if (NULL != msgbox->PtrTokens)
		{	
			MemFreePointer ((VOID **)&msgbox->PtrTokens);
		}
	//        MemFreePointer( (VOID **)&msgbox->HotKeyList );
	//        MemFreePointer( (VOID **)&msgbox->OutKey );
		MemFreePointer( (VOID **)&msgbox );
	}
	return Status ;   
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxInitialize
//
// Description:	Function to Initialize Message Box, which uses the Popup functions.
//
// Input:	MSGBOX_DATA *msgbox, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxInitialize( MSGBOX_DATA *msgbox, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 Length =0 ;
	VOID *buff;
	CONTROL_INFO MemoCtrlData;
	MEMO_DATA *memo;
	UINT8 Color ;

	UINT16 titleToken;
    VOID* TextHandle =((AMI_IFR_MSGBOX*)(((CONTROL_INFO*)data)->ControlPtr))->TextHandle;

	// initializes the heigth and width
	Status = gPopup.Initialize( msgbox, data );
	if (EFI_ERROR(Status))
		return Status;

	gMsgBoxType = msgbox->MsgBoxCatagory;
	Status = StyleGetMessageboxColor(msgbox->MsgBoxCatagory, &Color) ; 
	
	if ( EFI_ERROR( Status ) == EFI_SUCCESS)
	{
		msgbox->FGColor = Color & 0x0f ; 
		msgbox->BGColor = Color & 0xf0 ; 
	}else
	// add extra initialization here...
	SetControlColorsHook( NULL, NULL, NULL , NULL, NULL , NULL, NULL ,
	                      NULL , NULL,  NULL,NULL ,
						  NULL,NULL ,&(msgbox->FGColor),&(msgbox->BGColor)  );


	msgbox->Container = NULL;
	
	msgbox->Border =TRUE;

	titleToken = (UINT16)(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Title);
	if ( titleToken != 0 ) {
		msgbox->Title = HiiGetString(msgbox->ControlData.ControlHandle, titleToken);
		//EIP-75351 Suppress the warnings from static code analyzer
		if(NULL == msgbox->Title){
			msgbox->Title = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
			if(!msgbox->Title)
				return EFI_OUT_OF_RESOURCES;
			EfiStrCpy(msgbox->Title,L" ");
		}
	}

	Length = (UINT16)HiiMyGetMultiLineStringLength(msgbox->ControlData.ControlHandle, (UINT16)(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Text));

	if ( ( msgbox->Title != NULL) && ( Length < (TestPrintLength( msgbox->Title )/ (NG_SIZE)) ) )
		Length = (UINT16)(TestPrintLength( msgbox->Title ) / (NG_SIZE));

	msgbox->Width = (UINT16)(Length + 4);

	if(( msgbox->MsgBoxType == MSGBOX_TYPE_NULL ) && ( msgbox->Legend != NULL ))
	{ 
		if ( msgbox->Width < (UINT16)(TestPrintLength( msgbox->Legend )/ (NG_SIZE)) )
			msgbox->Width = (UINT16)(TestPrintLength( msgbox->Legend ) / (NG_SIZE)) + 8;
	}	
//EIP74963 : MAX_MSGBOX_WIDTH macro changed as token and handled from binary
	if ( msgbox->Width > GetMsgboxWidth())
		msgbox->Width = GetMsgboxWidth();

	//EIP-197833 Save the screen only insied TSE not for PostInterfaces outside TSE
	if (TSE_POST_STATUS_IN_TSE == gPostStatus)
		msgbox->ScreenBuf = SaveScreen();

	//EIP-197833 Clear screen before displaying msgbox when PROCEED_TO_BOOT not inside TSE
	if (TSE_POST_STATUS_PROCEED_TO_BOOT == gPostStatus)
	{
		ClearGrphxScreen(); //Clearing full screen when image is drawn in quietBoot mode
		ClearScreen(EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY);
	}

	// initialize memo control 
	memo = msgbox->Memo;

	buff = UefiCreateSubTitleTemplate(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Text );

	
	MemSet( &MemoCtrlData, sizeof(MemoCtrlData), 0 );
	MemoCtrlData.ControlPtr = (VOID*)buff;
	MemoCtrlData.ControlHandle = TextHandle;
	MemoCtrlData.ControlFlags.ControlVisible = TRUE;
	gMemo.Initialize(memo,(VOID *)&(MemoCtrlData));
	memo->Width = msgbox->Width - 2;
	gMemo.GetControlHeight((CONTROL_DATA*) memo, NULL, &msgbox->Height );
	msgbox->Height += 4;

	gMemo.SetAttributes((CONTROL_DATA*) memo,msgbox->FGColor ,msgbox->BGColor);
	gMemo.SetDimensions( (CONTROL_DATA*) memo, msgbox->Width-2 , msgbox->Height-3 );
	gMemo.SetJustify( memo, JUSTIFY_CENTER );
	memo->ParentFrameType = MESSAGEBOX_FRAME ;  // EIP 180755 

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_MsgBoxOptSize
//
// Description:	Function returns and fix the option string
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _MsgBoxOptSize(CHAR16 *txt)
{
	UINTN Size = (TestPrintLength( txt ) / (NG_SIZE));
	if( Size > 10)
	{
		txt[HiiFindStrPrintBoundary(txt,10)] = L'\0';
		Size = (TestPrintLength( txt ) / (NG_SIZE)); // Need to do this. instead of assigning 10;
	}
	return Size;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_MsgBoxDrawOpts
//
// Description:	Function to Draw Message box options
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _MsgBoxDrawOpts(MSGBOX_DATA *msgbox)
{
	UINT16 Index, W;
	CHAR16 Line[MAX_COLS] ,*txt;
	UINTN printLength, pos ;

	if ( msgbox->MsgBoxType != MSGBOX_TYPE_NULL )
	{ 
		for ( Index = 1; Index < msgbox->Width -1 ; Index++ )
			Line[Index] = BOXDRAW_HORIZONTAL;

		Line[0] = BOXDRAW_VERTICAL_RIGHT;
		Line[Index] = BOXDRAW_VERTICAL_LEFT;
		Line[Index+1] = 0x0;

		DrawString( msgbox->Left, msgbox->Top + msgbox->Height - 3, Line );

		// draw the buttons
		switch ( msgbox->MsgBoxType & MSGBOX_TYPE_MASK )
		{

			case MSGBOX_TYPE_YESNO:
				txt =  HiiGetString( msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_YES));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}

				msgbox->Button1Len = (UINT8)_MsgBoxOptSize(txt );
				DrawStringWithAttribute((UINTN) (msgbox->Left + msgbox->Width/3 -2) , (UINTN)(msgbox->Top + msgbox->Height -2), txt, (UINT8) (((msgbox->MsgboxSel==0)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
				MemFreePointer( (VOID **)&txt);

				txt =  HiiGetString( msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_NO));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}

				msgbox->Button2Len = (UINT8)_MsgBoxOptSize(txt );

				DrawStringWithAttribute((UINTN)( msgbox->Left + 2*(msgbox->Width/3) -2) ,(UINTN)(msgbox->Top + msgbox->Height -2), txt, (UINT8) (((msgbox->MsgboxSel==1)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
				MemFreePointer( (VOID **)&txt);

				break;
			case MSGBOX_TYPE_OKCANCEL:
				txt =  HiiGetString( msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_OK));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}
				msgbox->Button1Len = (UINT8)_MsgBoxOptSize(txt );
				DrawStringWithAttribute((UINTN) (msgbox->Left + msgbox->Width/3 -2) , (UINTN)(msgbox->Top + msgbox->Height -2), txt, (UINT8) (((msgbox->MsgboxSel==0)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
				MemFreePointer( (VOID **)&txt);

				txt =  HiiGetString( msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_CANCEL));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}
				msgbox->Button2Len = (UINT8)_MsgBoxOptSize(txt );
				DrawStringWithAttribute((UINTN)( msgbox->Left + 2*(msgbox->Width/3) -2) ,(UINTN)(msgbox->Top + msgbox->Height -2), txt, (UINT8) (((msgbox->MsgboxSel==1)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
				MemFreePointer( (VOID **)&txt);
				break;
			
			case MSGBOX_TYPE_CUSTOM:

				if ( (msgbox->OptionCount != 0) && (msgbox->PtrTokens != NULL ))
				{ 
					W = ( msgbox->Width)/(msgbox->OptionCount) ;


					for ( Index = 0; Index < msgbox->OptionCount ; Index++ )
					{
						txt =  HiiGetString( msgbox->ControlData.ControlHandle, msgbox->PtrTokens[Index]);
						//EIP-75351 Suppress the warnings from static code analyzer
						if (NULL == txt){
							break;
						}
						pos = (UINTN) (msgbox->Left + (Index * W) ) ;

						printLength = (TestPrintLength( txt ) / (NG_SIZE));
				
						if( printLength > W)
						{
							txt[HiiFindStrPrintBoundary(txt, W)] = L'\0';
							printLength = (TestPrintLength( txt ) / (NG_SIZE));
						}
								
						DrawStringWithAttribute(pos + (W-printLength)/2 , (UINTN)(msgbox->Top + msgbox->Height -2 ), txt, (UINT8) (((msgbox->MsgboxSel==Index)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
						MemFreePointer( (VOID **)&txt);
					}
				}

				break;
						
			case MSGBOX_TYPE_PROGRESS:
				//Draw the progress bar based on percent complete, for example

				//----------------------- Title ------------------------//
				//							//									
				// 	Message Body will be printerd here		//
				//							//
				//------------------------------------------------------//
				// ##################### 10% ####			// <--- This section is where to use DrawStringWithAttribute 
				//--------------------- Legend -------------------------//

				{
					CHAR16 Box[2] = {0};
					CHAR16 PercentStr[5] = {0};
					UINT16 Index = 0;
					UINT16 ChrIdx=msgbox->Left;
					UINT16 ProgPos=0;
					
					//symbol character to show during progress update
					Box[0] = (CHAR16)BLOCKELEMENT_FULL_BLOCK ; //L'#';
					Box[1] = (CHAR16)L'\0';
				

					//max percentage should be 100
					if( msgbox->Percent > 100) {
						msgbox->Percent = 100;
					}

					//percentage to update on the progress bar
					if( msgbox->Percent / 100)
					{
						PercentStr[Index++] = (CHAR16)(msgbox->Percent / 100) + L'0';
						PercentStr[Index++] = (CHAR16)((msgbox->Percent % 100) / 10) + L'0';

					}
					if( (msgbox->Percent % 100) / 10)
						PercentStr[Index++] = (CHAR16)((msgbox->Percent % 100) / 10) + L'0';

					PercentStr[Index++] =  (CHAR16)((msgbox->Percent % 100) % 10) + L'0';
					PercentStr[Index] = L'%';

					/// some sample logic to fill the progress bar symbol character properly without hard coded values...
					ProgPos = msgbox->Width - 2;
					while ( ProgPos < 100 )
					{
						if ( 100  % ProgPos != 0){
							if ( 99  % ProgPos != 0){
								if ( 98  % ProgPos != 0) {
									ProgPos--;
								}
								else
								break;//EIP74965 : Progress bar now can show the 100% status 
							}
							else
								break;
						}
						else
							break;
					}

					ProgPos = 100/ProgPos;
			

					//Fill progress bar for the given percentage
					for( Index = 0; Index < msgbox->Percent; Index++ ) {
						//fill the symbol character based on the segment value for the given percentage
						if( ( msgbox->Percent != 0 ) && ( Index % ProgPos == 0 ) && (ChrIdx < msgbox->Left+msgbox->Width-2) )
							DrawStringWithAttribute((UINTN) ++ChrIdx, (UINTN)(msgbox->Top + msgbox->Height - 2), Box, (UINT8) msgbox->BGColor|EFI_CYAN/*| msgbox->FGColor*/);
					}

					if( msgbox->Percent == 100 ) {
						//to fill the progress bar completely for the box width in case of 100 percentage.
						for( ; (ChrIdx - msgbox->Left) < (msgbox->Width - 2); )
							DrawStringWithAttribute((UINTN) ++ChrIdx, (UINTN)(msgbox->Top + msgbox->Height - 2), Box, (UINT8) msgbox->BGColor|EFI_CYAN/*| msgbox->FGColor*/);
					}

					//draw percentage string on the progress bar
					DrawStringWithAttribute( msgbox->Left + msgbox->Width / 2 -	EfiStrLen(PercentStr)/2, msgbox->Top + msgbox->Height - 3,PercentStr, (UINT8) /*msgbox->BGColor|EFI_RED */msgbox->BGColor | msgbox->FGColor);

					//Draw the given legend
					DrawStringWithAttribute( msgbox->Left + msgbox->Width / 2 -	EfiStrLen(msgbox->Legend)/2, msgbox->Top + msgbox->Height - 1,msgbox->Legend, (UINT8) msgbox->BGColor | msgbox->FGColor);
				}

				break;

			case MSGBOX_TYPE_OK:

			default:
				txt =  HiiGetString(msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_OK));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}

				msgbox->Button1Len = (UINT8)_MsgBoxOptSize(txt );
				msgbox->Button2Len = 0;
				DrawStringWithAttribute( msgbox->Left + msgbox->Width/2  , msgbox->Top + msgbox->Height -2, txt, EFI_BACKGROUND_BLACK|EFI_WHITE );
				MemFreePointer( (VOID **)&txt);
				break;
		} 

		FlushLines( msgbox->Top + msgbox->Height -3, msgbox->Top + msgbox->Height);
	} 

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxDraw
//
// Description:	Function to Draw Message box
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxDraw( MSGBOX_DATA *msgbox )
{
	EFI_STATUS Status;
	CHAR16 *PadTitle = NULL, *Str = NULL;
	Str = msgbox->Legend ;

	MouseFreeze();

	Status = gPopup.Draw( msgbox );
	if(EFI_ERROR(Status))
		return Status;

	_MsgBoxDrawOpts(msgbox);

	// draw memo
	gMemo.SetPosition((CONTROL_DATA*)  msgbox->Memo, msgbox->Left + 1, msgbox->Top + 2 );
	gMemo.SetJustify( msgbox->Memo, (msgbox->MsgBoxType & MSGBOX_STYLE_MASK) >> 4 );
	gMemo.Draw( msgbox->Memo );

	

	if ((Str != NULL) && ( msgbox->MsgBoxType == MSGBOX_TYPE_NULL ) )
	{
		PadTitle = EfiLibAllocateZeroPool( (msgbox->Width + 3) * sizeof(CHAR16) );

		if( (UINT16)(TestPrintLength( Str ) / (NG_SIZE)) > (UINT16)(msgbox->Width-2))
				EfiStrCpy( &Str[HiiFindStrPrintBoundary(Str,(msgbox->Width-5))],L"...");

		if ( PadTitle != NULL )
			SPrint( PadTitle,  msgbox->Width * sizeof(CHAR16), L" %s ",Str );
	}

	if ( PadTitle )
	{
		DrawStringJustified( 0, gMaxCols, msgbox->Top+msgbox->Height-1, JUSTIFY_CENTER, PadTitle );
		//DrawStringJustified( msgbox->Left+1, msgbox->Left+msgbox->Width-1, msgbox->Top+msgbox->Height, JUSTIFY_CENTER, PadTitle );
		MemFreePointer((VOID **)&PadTitle);
	}

	FlushLines( msgbox->Top, msgbox->Top + msgbox->Height );
	DoRealFlushLines();

	MouseRefresh();

	return  EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_MsgBoxCallCallback
//
// Description:	Internal Helper Function to Call the callback
//
// Input:		MENU_DATA *menu, UINT8 MenuEntry
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _MsgBoxCallCallback(MSGBOX_DATA *msgbox,UINT8 MsgboxSel)
{
    if ( ( msgbox->Callback != NULL ) && (msgbox->Cookie != NULL) )
    {
	    CALLBACK_MESSAGEBOX *callbackData = (CALLBACK_MESSAGEBOX *)msgbox->Cookie;
	    callbackData->Result = MsgboxSel;
        msgbox->Callback( msgbox->Container, msgbox, msgbox->Cookie );
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxHandleAction
//
// Description:	Function to Handle the Message Box Actions.
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxHandleAction( MSGBOX_DATA *msgbox, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_SUCCESS;
	BOOLEAN Redraw = FALSE; 
	//Always return success to consume the message, the messagebox is always modal.
	if ( Data->Input.Type == ACTION_TYPE_TIMER )
		return EFI_UNSUPPORTED;

    if ( Data->Input.Type == ACTION_TYPE_MOUSE )
    {
		Status = MouseMsgBoxHandleAction( msgbox, Data,&Redraw);
    }

	if(Data->Input.Type == ACTION_TYPE_KEY)
	{
        CONTROL_ACTION Action;

        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);

		if( TsePrintScreenEventSupport(Data->Input.Data.AmiKey.Key.ScanCode))
		{
			gApplication.HandleAction( gApp, Data );
			return EFI_UNSUPPORTED;//EIP-123432
		}

        switch(Action)
        {
            case ControlActionSelect:
				// EIP 34545 : If MSGBOX_TYPE_NULL, nothing to select Only Esc can control
                if (msgbox->MsgBoxType == MSGBOX_TYPE_NULL)
                    break;
				_MsgBoxCallCallback(msgbox,msgbox->MsgboxSel);
            break;

            case ControlActionNextLeft:
		if( ( (msgbox->MsgBoxType & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_OK )&&
				( (msgbox->MsgBoxType & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_CUSTOM ))
    		{
    				if ( msgbox->MsgboxSel == 1 )
    					msgbox->MsgboxSel = 0;
    				
    		}
		else if((msgbox->MsgBoxType & MSGBOX_TYPE_MASK) == MSGBOX_TYPE_CUSTOM )
		{
    				if ( msgbox->MsgboxSel > 0 )
    					msgbox->MsgboxSel--;
    				
    		}
    
    		Redraw = TRUE;
            	break;
            
	   case ControlActionNextRight:
    		if( ( (msgbox->MsgBoxType & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_OK )&&
				( (msgbox->MsgBoxType & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_CUSTOM ))
   		{
   			if ( msgbox->MsgboxSel == 0 )
   				msgbox->MsgboxSel = 1;
   			
   		}
		else if((msgbox->MsgBoxType & MSGBOX_TYPE_MASK) == MSGBOX_TYPE_CUSTOM )
		{
    				if ( msgbox->MsgboxSel < msgbox->OptionCount-1 )
    					msgbox->MsgboxSel++;
    		}
    
   		Redraw = TRUE;
                break;

            case ControlActionAbort:
    			msgbox->MsgboxSel = MSGBOX_CANCEL;
    			_MsgBoxCallCallback(msgbox,msgbox->MsgboxSel);
    			gAction.ClearAction( Data );
            break;
            default : // All Enumeration values are not handled
        	    break;
        }
    }

	if ( Redraw == TRUE )
		gMsgBox.Draw( msgbox );

	return Status; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetCallback
//
// Description:	Function to set callback.
//
// Input:		MSGBOX_DATA *msgbox, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetCallback( MSGBOX_DATA *msgbox, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( msgbox, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetType
//
// Description:	Function to set message box type.
//
// Input:		MSGBOX_DATA *msgbox, UINT8 Type
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetType( MSGBOX_DATA *msgbox, UINT8 Type )
{
	msgbox->MsgBoxType = Type;
	if ( (Type & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_NULL )
		msgbox->Height += 2;

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetFocus
//
// Description:	Function to set focus.
//
// Input:		MSGBOX_DATA *msgbox, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetFocus(MSGBOX_DATA *msgbox, BOOLEAN focus)
{
	msgbox->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetPosition
//
// Description:	Function to set position.
//
// Input:		MSGBOX_DATA *msgbox, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetPosition(MSGBOX_DATA *msgbox, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( (CONTROL_DATA*)msgbox, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetDimensions
//
// Description:	Function to set dimensions.
//
// Input:		MSGBOX_DATA *msgbox, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetDimensions(MSGBOX_DATA *msgbox, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( (CONTROL_DATA*)msgbox, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetAttributes
//
// Description:	Function to set attrinutes.
//
// Input:		MSGBOX_DATA *msgbox, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetAttributes(MSGBOX_DATA *msgbox, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( (CONTROL_DATA*)msgbox, FGColor, BGColor );
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseMsgBoxHandleAction
//
// Description:	Function to hadnle Message Box using mouse
//
// Input:		MSGBOX_DATA *msgbox, 
//				ACTION_DATA *action,
//				BOOLEAN * pRedraw
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEMouseMsgBoxHandleAction( MSGBOX_DATA *msgbox, ACTION_DATA *Data,BOOLEAN * pRedraw)
{
    BOOLEAN ButtonClicked = FALSE;
	CONTROL_ACTION Action;

	UINT16 Index, W;
	CHAR16 *txt=NULL;
	UINTN printLength, pos ;

	//EIP 103449  : In Setup click\Touch from navigation window, option are not displayed properly
	Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);

    if((
        (Data->Input.Data.MouseInfo.Top < msgbox->Top) ||
        (Data->Input.Data.MouseInfo.Top > (UINT32)(msgbox->Top + msgbox->Height)) ||
        (Data->Input.Data.MouseInfo.Left < msgbox->Left) ||
        (Data->Input.Data.MouseInfo.Left > (UINT32)(msgbox->Left + msgbox->Width)) 
     	)&&( (SingleClickActivation() &&  (ControlActionSelect ==Action)) ||  //If singleClickActivation is enabled/Disable
	 		 (ControlActionAbort == Action) || (ControlActionChoose ==Action ) //EIP-139608 Closing listbox whn mouse action happens outside listbox
	 		)
	  )
    {
		msgbox->MsgboxSel = MSGBOX_CANCEL;
		_MsgBoxCallCallback(msgbox,msgbox->MsgboxSel);
		gAction.ClearAction( Data );
		return EFI_SUCCESS;
    }

	
	if( (Action == ControlActionChoose ) || (Action == ControlActionSelect) )
    {
        if(Data->Input.Data.MouseInfo.Top == (UINT32)(msgbox->Top + msgbox->Height -2))
        {
            switch(msgbox->MsgBoxType & MSGBOX_TYPE_MASK)
            {
				case MSGBOX_TYPE_CUSTOM:

					if ( (msgbox->OptionCount != 0) && (msgbox->PtrTokens != NULL ))
					{ 
						W = ( msgbox->Width)/(msgbox->OptionCount) ;

						for ( Index = 0; Index < msgbox->OptionCount ; Index++ )
						{
							txt =  HiiGetString( msgbox->ControlData.ControlHandle, msgbox->PtrTokens[Index]);
							pos = (UINTN) (msgbox->Left + (Index * W) ) ;

							printLength = (TestPrintLength( txt ) / (NG_SIZE));
				
							if( printLength > W)
							{
								txt[HiiFindStrPrintBoundary(txt, W)] = L'\0';
								printLength = (TestPrintLength( txt ) / (NG_SIZE));
							}

							MemFreePointer( (VOID **)&txt);

							if( (Data->Input.Data.MouseInfo.Left)>=(UINT32)(pos + (W-printLength)/2 -2)  &&
				        			(Data->Input.Data.MouseInfo.Left)<=(UINT32)((pos + (W-printLength)/2 -2)+printLength))	
				    			{
					        		msgbox->MsgboxSel = (UINT8)Index;
                            					ButtonClicked = TRUE;
								break;	
				    			}
						}
					}

					break;				

			    case MSGBOX_TYPE_YESNO:
    			case MSGBOX_TYPE_OKCANCEL:

				    if( (Data->Input.Data.MouseInfo.Left)>=(UINT32)(msgbox->Left + msgbox->Width/3 -2)   &&
				        (Data->Input.Data.MouseInfo.Left)<=(UINT32)((msgbox->Left + msgbox->Width/3 -2)+msgbox->Button1Len))
					    {
					        msgbox->MsgboxSel = 0;
                            ButtonClicked = TRUE;
					    }

    				if( (Data->Input.Data.MouseInfo.Left)>=(UINT32)( msgbox->Left + 2*(msgbox->Width/3) -2)   &&
				        (Data->Input.Data.MouseInfo.Left)<=(UINT32)(( msgbox->Left + 2*(msgbox->Width/3) -2)+msgbox->Button2Len) )	
					    {
					        msgbox->MsgboxSel = 1;
                            ButtonClicked = TRUE;
    					}
     		    break;              
    			case MSGBOX_TYPE_OK:
    			default:
    				// EIP 46143 - Updated the msg box position to slect with click properly
    				if( (Data->Input.Data.MouseInfo.Left)>=(UINT32)(msgbox->Left + msgbox->Width/2 -1)   &&
    				    (Data->Input.Data.MouseInfo.Left)<=(UINT32)((msgbox->Left + msgbox->Width/2 -1)+msgbox->Button1Len) )	
				    	{
        					msgbox->MsgboxSel = 0;
                            ButtonClicked = TRUE;
    					}
    			break;
			}

            if(ButtonClicked)
            {
				if(ControlActionChoose == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
                    *pRedraw = TRUE;
                else
					_MsgBoxCallCallback(msgbox,msgbox->MsgboxSel);
            }
        }
    }
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxGetControlHight
//
// Description:	Function unsupported.
//
// Input:		VOID *object,VOID *frame, UINT16 *height 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxGetControlHight( MSGBOX_DATA *object,VOID *frame, UINT16 *height )
{
	return EFI_UNSUPPORTED;
}

///Moved the following function callback.c for ESA compatibility starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowHelpMessageBox
//
// Description:	Function to Display the help message box
//
// Input:	None
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
extern UINTN gHelpMsgBox;
VOID ShowHelpMessageBox( VOID )
{
	CallbackShowMessageBox( (UINTN)gHelpMsgBox, MSGBOX_TYPE_OK | MSGBOX_STYLE_LEFT );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CallbackShowMessageBox
//
// Description:	Callback function to Display the message box
//
// Input		:	UINTN data, 
//					UINT8 type
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _CallbackGetValue( MSGBOX_DATA *msgbox );
UINT8 CallbackShowMessageBox( UINTN data, UINT8 type )
{
	EFI_STATUS Status;
	UINT8 retValue = (UINT8)-1;
	MSGBOX_DATA *msgbox = NULL;

	CONTROL_INFO dummy;

	Status = gMsgBox.Create((void**) &msgbox );
	if ( EFI_ERROR( Status ) )
		return retValue;

	MemSet( &dummy, sizeof(dummy), 0 );
	dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;
	dummy.ControlPtr = (VOID*)data;
	dummy.ControlFlags.ControlVisible = TRUE;

	Status = gMsgBox.Initialize( msgbox, &dummy );
	if ( EFI_ERROR( Status ) )
		goto Done;

	gMsgBox.SetType( msgbox, type );
	retValue = (UINT8)_CallbackGetValue( msgbox );

Done:
	gMsgBox.Destroy( msgbox, TRUE );

	return retValue;
}


static UINT8 result = (UINT8)-1;
static CALLBACK_MESSAGEBOX  gCbMsgBox = { { CALLBACK_TYPE_MESSAGEBOX, sizeof(CALLBACK_MESSAGEBOX) }, 0 }; 

VOID _CallbackMsgbox( VOID *container, VOID *object, VOID *cookie )
{
	if ( (cookie != NULL) && ( ((CALLBACK_MESSAGEBOX*)cookie)->Header.Type == CALLBACK_TYPE_MESSAGEBOX) )
		result = (UINT8)(((CALLBACK_MESSAGEBOX*)cookie)->Result);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_CallbackGetValue
//
// Description:	Callback function to get the message box return value
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	Message box return value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _CallbackGetValue( MSGBOX_DATA *msgbox )
{
	ACTION_DATA *action = gMsgBoxAction;
	EFI_STATUS Status = EFI_SUCCESS;
	result = (UINT8)-1;
	gMsgBox.SetCallback( msgbox, NULL, _CallbackMsgbox, &gCbMsgBox );

	while ( result == (UINT8)-1 )
	{
		if ( action->Input.Type != ACTION_TYPE_NULL )
			gAction.ClearAction( action );

		gMsgBox.Draw( msgbox );

		if ( gAction.GetAction( action ) != EFI_SUCCESS )
			continue;

		Status = gMsgBox.HandleAction( msgbox, action );

		if (EFI_ERROR(Status))//EIP-123432
			result = 0xff;

		DoRealFlushLines();
	}

	return result;
}

///Moved the following function callback.c for ESA compatibility ends

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------------------------------------------
// Procedure:   GetMessageBoxType
//
// Description:  Function to return the current message box type
//
// Input:   void
//
// Output:  MSGBOX_EX_CATAGORY
//
//--------------------------------------------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
MSGBOX_EX_CATAGORY GetMessageBoxType (void)
{	//EIP131739 : Modified MainSetupLoopInit as module hook for TSE
	return gMsgBoxType;
}

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**       (C)Copyright 1985-2014, American Megatrends, Inc.     **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**    5555 Oakbrook Pkwy, Norcross, Suite 200, Georgia 30093   **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

