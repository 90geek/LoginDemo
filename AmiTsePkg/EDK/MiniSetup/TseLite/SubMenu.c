//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/SubMenu.c $
//
// $Author: Rajashakerg $
//
// $Revision: 23 $
//
// $Date: 9/17/12 6:20a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Submenu.c
//
// Description:	This file contains code to handle submenu operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

SUBMENU_METHODS gSubMenu =
{
	(OBJECT_METHOD_CREATE)SubMenuCreate,
	(OBJECT_METHOD_DESTROY)SubMenuDestroy,
	(OBJECT_METHOD_INITIALIZE)SubMenuInitialize,
	(OBJECT_METHOD_DRAW)SubMenuDraw,
	(OBJECT_METHOD_HANDLE_ACTION)SubMenuHandleAction,
	(OBJECT_METHOD_SET_CALLBACK)SubMenuSetCallback,
	(CONTROL_METHOD_SET_FOCUS)SubMenuSetFocus,
	(CONTROL_METHOD_SET_POSITION)SubMenuSetPosition,
	(CONTROL_METHOD_SET_DIMENSIONS)SubMenuSetDimensions,
	(CONTROL_METHOD_SET_ATTRIBUTES)SubMenuSetAttributes,
    (CONTROL_METHOD_GET_CONTROL_HIGHT)SubMenuGetControlHeight

};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuCreate
//
// Description:	this function uses the create function of control
//					and create submenu.
//
// Input:	SUBMENU_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuCreate( SUBMENU_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(SUBMENU_DATA) );

		if ( *object == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Status = gControl.Create( (void**)object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gSubMenu;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys submenu.
//
// Input:	SUBMENU_DATA *submenu, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuDestroy( SUBMENU_DATA *submenu, BOOLEAN freeMem )
{
	if(NULL == submenu)
	  return EFI_SUCCESS;

	gControl.Destroy( submenu, FALSE );

	if ( freeMem )
		MemFreePointer( (VOID **)&submenu );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuDestroy
//
// Description:	this function uses the initialize function of control
//					and initializes the submenu.
//
// Input:	SUBMENU_DATA *submenu, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuInitialize( SUBMENU_DATA *submenu, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( submenu, data );
	if (EFI_ERROR(Status))
		return Status;

    if(UefiIsInteractive(&submenu->ControlData))
	{
		// EIP88031 : Invoking CallFormCallBackon with AMI_CALLBACK_RETRIEVE 
        // caused infinite loop on FormCallBack when UIUpdateCallback is called during pack update.
        /*		
        UINT16 Key = UefiGetControlKey(&(submenu->ControlData));
		UefiPreControlUpdate(NULL);//EIP45464 : Updating the gPrevControlValue buffer to NULLL before invoking CallFormCallBack 	
		CallFormCallBack(&(submenu->ControlData),Key,0,AMI_CALLBACK_RETRIEVE);//EIP-53480: Updated the action to AMI_CALLBACK_RETRIEVE
        */
	}

	// add extra initialization here...
	submenu->ControlData.ControlHelp = UefiGetHelpField((VOID *)submenu->ControlData.ControlPtr); //refPtr->Help;
	submenu->ControlFocus = FALSE;
	submenu->Interval = (UINT8)submenu->ControlData.ControlFlags.ControlRefresh;
	submenu->LabelMargin = (UINT8)gControlLeftMargin;

	// initialize default colors
	SetControlColorsHook(&(submenu->BGColor), &(submenu->FGColor),  
						NULL, NULL,
						&(submenu->SelBGColor), &(submenu->SelFGColor),
			            &(submenu->NSelBGColor), &(submenu->NSelFGColor),  
						NULL,&(submenu->LabelFGColor) ,
					    &(submenu->NSelLabelFGColor),
						NULL,NULL,
						NULL,NULL );
	
	

#if SETUP_STYLE_AWARD
	submenu->SubMenuType = (UINT8)(submenu->ControlData.ControlPageID != 0);
#endif

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuDraw
//
// Description:	function to draw a sub-menu.
//
// Input:	SUBMENU_DATA *submenu
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuDraw( SUBMENU_DATA *submenu )
{
	CHAR16 *text=NULL,*text1;
	UINTN length;
	EFI_STATUS Status = EFI_SUCCESS;
//	UINT8 ColorSubMenu = submenu->NSelFGColor;
	UINT8 ColorLabel = (submenu->ControlFocus) ? submenu->LabelFGColor : submenu->NSelLabelFGColor ;

	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( submenu->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &submenu->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
            if (!submenu->ControlFocus)//setting grayoutif color for grayoutif control based on token TSE_SETUP_GRAYOUT_SELECTABLE
					ColorLabel = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	text1 = HiiGetString( submenu->ControlData.ControlHandle,  UefiGetPromptField((VOID *)(submenu->ControlData.ControlPtr)));
	if ( text1 == NULL )
		return EFI_OUT_OF_RESOURCES;
	// XXX check to see if text1 is not NULL
	length = (3 + (TestPrintLength( text1 ) / (NG_SIZE))) * sizeof(CHAR16);
	text = EfiLibAllocateZeroPool( length );
	if ( text == NULL )
		return EFI_OUT_OF_RESOURCES;

	SPrint( text, length, L"%c %s", (submenu->SubMenuType == 2)?L' ':GEOMETRICSHAPE_RIGHT_TRIANGLE, text1 );
	MemFreePointer( (VOID **)&text1 );

	if ( submenu->SubMenuType != 1 )
	{
		//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
		if(submenu->Height>1 && IsTSEMultilineControlSupported())
		{
			DrawMultiLineStringWithAttribute( submenu->Left , submenu->Top, 
					(UINTN)(submenu->Width),(UINTN) submenu->Height,
					&text[2], (UINT8)(  (submenu->ControlFocus) ? 
							  submenu->SelBGColor  | ColorLabel /*submenu->SelFGColor*/ :
							  submenu->NSelBGColor | ColorLabel /*ColorSubMenu*/ )  );

			if(submenu->SubMenuType != 2)
			{
				text[2]=0;
				DrawStringWithAttribute( submenu->Left - 2, submenu->Top, (CHAR16*)text, 
						(UINT8)(  (submenu->ControlFocus) ? 
								  submenu->SelBGColor  | ColorLabel /*submenu->SelFGColor*/ :
								  submenu->NSelBGColor | ColorLabel /*ColorSubMenu*/ ) );
			}
		}
		else
		{
			
			if(submenu->SubMenuType==0 && !submenu->ControlFocus && ColorLabel != CONTROL_GRAYOUT_COLOR)
				ColorLabel = StyleGetPageLinkColor();
						
			
			if(((TestPrintLength( text ) / (NG_SIZE))-2) > (UINTN)(submenu->Width))//EIP 97333 : Check for width corrected since the text already include spaces in it.
				EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)(submenu->Width-2))],L"...");
	
			DrawStringWithAttribute( submenu->Left - 2, submenu->Top, (CHAR16*)text, 
					(UINT8)(  (submenu->ControlFocus) ? 
							  submenu->SelBGColor  | ColorLabel :
							  submenu->NSelBGColor | ColorLabel ) );
		}
	}
	else
	{
		if((TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(submenu->Width-2))
			EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)(submenu->Width-5))],L"...");

		text1 = HiiGetString( gHiiHandle, STRING_TOKEN(STR_SUBMENU_OPTION) );
		if ( text1 != NULL )
		{
			DrawStringWithAttribute( submenu->Left - 2, submenu->Top, (CHAR16*)text, 
					EFI_BACKGROUND_BLUE | EFI_WHITE );
			MemFreePointer( (VOID **)&text );

			length = (3 + (TestPrintLength( text1 ) / (NG_SIZE))) * sizeof(CHAR16);
			text = EfiLibAllocatePool( length );
			if ( text != NULL )
			{
				SPrint( text, length, L"[%s]", text1 );
		
			 	if ((TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(submenu->Width-2))
					EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)(submenu->Width-5))],L"...");

				DrawStringWithAttribute( submenu->Left  + submenu->LabelMargin , submenu->Top, text,
						(UINT8)(submenu->NSelBGColor | ColorLabel /*ColorSubMenu*/) );

				if ( submenu->ControlFocus )
					DrawStringWithAttribute( submenu->Left + submenu->LabelMargin + 1,
							submenu->Top, text1, (UINT8)(submenu->SelBGColor | submenu->SelFGColor) );
			}
		}
	}

	MemFreePointer( (VOID **)&text );
	MemFreePointer( (VOID **)&text1 );

	FlushLines( submenu->Top, submenu->Top );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuHandleAction
//
// Description:	function to handle the submenu actions
//
// Input:	SUBMENU_DATA *submenu, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
extern BOOLEAN gHiiFormNotFound;
EFI_STATUS SubMenuHandleAction( SUBMENU_DATA *submenu, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	BOOLEAN Selected = FALSE;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		if (submenu->Interval == 0)
			return Status;

		if ( --(submenu->Interval) == 0 )
		{
			// initialize the interval
			submenu->Interval = (UINT8)(submenu->ControlData.ControlFlags.ControlRefresh);
			return EFI_SUCCESS;
		}
		else
			return Status;
	}

	if ( ! submenu->ControlFocus )
		return Status;

	if (Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		//Status = MouseSubMenuHandleAction( submenu, Data);
		//if ( Data->Input.Data.MouseInfo.ButtonStatus==TSEMOUSE_LEFT_DCLICK )
		if(ControlActionSelect == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
		//check whether MouseTop is within the Height and Width of submenu or not
			if((Data->Input.Data.MouseInfo.Top >= (UINT32)submenu->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(submenu->Top+submenu->Height)) &&
				 (Data->Input.Data.MouseInfo.Left >= (UINT32)submenu->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(submenu->Left+submenu->Width)))//EIP-123727
			Selected = TRUE;
	}

	if ( Data->Input.Type == ACTION_TYPE_KEY )
	{
		if ( ControlActionSelect == MapControlKeysHook(Data->Input.Data.AmiKey) )
			Selected = TRUE;
	}
	if(Selected)
	{
		UINT8 u8ChkResult;

		u8ChkResult = CheckControlCondition( &submenu->ControlData );
        
		//Not to perform action for grayoutif-control when token TSE_SETUP_GRAYOUT_SELECTABLE is enable to set focus for GrayoutIf control
		if ( IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT) ) {
		   return EFI_UNSUPPORTED;
		}

		MouseStop();
		
		if ( submenu->Callback )
		{
			if ( submenu->Cookie != NULL )
			{
				CALLBACK_SUBMENU *callbackData = (CALLBACK_SUBMENU *)submenu->Cookie;
				callbackData->DestPage = submenu->ControlData.ControlDestPageID;
			}
			UefiPreControlUpdate(NULL);
			submenu->Callback( submenu->Container, submenu, submenu->Cookie );
		}

		if(UefiIsInteractive(&submenu->ControlData))
		{
			VOID * Handle=submenu->ControlData.ControlHandle;
			UINT16 Key = UefiGetControlKey(&(submenu->ControlData));
			CONTROL_DATA *Control;
		  	
			Status = CallFormCallBack(&(submenu->ControlData),Key,0,AMI_CALLBACK_CONTROL_UPDATE);//EIP-53480: Updated the action to AMI_CALLBACK_CONTROL_UPDATE
			// To support UEFI 2.1.C spec to Not to change page when Callback fails.
			Status = UefiIsProceedWithPageChange(Status);
			if(Status != EFI_SUCCESS)
			{
				if ( submenu->Callback )
				{
					if ( submenu->Cookie != NULL )
					{
						CALLBACK_SUBMENU *callbackData = (CALLBACK_SUBMENU *)submenu->Cookie;
						callbackData->DestPage = submenu->ControlData.ControlPageID;
					}
					submenu->Callback( submenu->Container, submenu, submenu->Cookie );
				}
					// On Error Status Don't Change the Destination page. Skip the user action.
					return EFI_SUCCESS;			
				
			}
			Control = GetUpdatedControlData((CONTROL_DATA*)submenu,CONTROL_TYPE_SUBMENU,Handle,Key);
		
			if(Control == NULL) // Control deleted ?
				return EFI_SUCCESS;
			if(Control != (CONTROL_DATA*)submenu)
				submenu = (SUBMENU_DATA*)Control; //control Updated
		}
		
		if (FormBrowserHandleValid())		//Checking for valid form
		{
			if (NULL == gApp->PageList [submenu->ControlData.ControlDestPageID])
			{
				gApp->Quit = TRUE;
				gHiiFormNotFound = TRUE;
			}
		}
		
		_SubMenuHandleSpecialOp( submenu );
		MouseStart();
		Status = EFI_SUCCESS;
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetCallback
//
// Description:	function to handle the submenu actions
//
// Input:		SUBMENU_DATA *submenu, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetCallback( SUBMENU_DATA *submenu, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( submenu, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetFocus
//
// Description:	Function to handle the submenu actions
//
// Input:		SUBMENU_DATA *submenu, BOOLEAN focus
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetFocus(SUBMENU_DATA *submenu, BOOLEAN focus)
{
	UINT8 u8ChkResult;
	
	if(focus != FALSE)
	{
        u8ChkResult = CheckControlCondition( &submenu->ControlData );
        
		//Setting focus to control which has no control-condtion and token TSE_SETUP_GRAYOUT_SELECTABLE is enable to make GrayoutIf control to set focus and selectable
		if (	((u8ChkResult != COND_NONE) && (u8ChkResult != COND_GRAYOUT)) ||
         	(!IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT))
			){
			return EFI_UNSUPPORTED;
		}
	}

	if( !(submenu->ControlFocus && focus) )
		submenu->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetPosition
//
// Description:	Function to set position.
//
// Input:		SUBMENU_DATA *submenu, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetPosition(SUBMENU_DATA *submenu, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( (CONTROL_DATA*)submenu, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		SUBMENU_DATA *submenu, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetDimensions(SUBMENU_DATA *submenu, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( (CONTROL_DATA*)submenu, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		SUBMENU_DATA *submenu, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetAttributes(SUBMENU_DATA *submenu, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes((CONTROL_DATA*)submenu, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuGetControlHeight
//
// Description:	Function to get the label height of the submenu
//
// Input:		SUBMENU_DATA *submenu, Frame Data, UINT16 *height
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuGetControlHeight(SUBMENU_DATA *submenu, VOID *frame, UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
        UINTN length=0;
	
		Width = ((FRAME_DATA *)frame)->FrameData.Width - (UINT8)gLabelLeftMargin - 2 ;
		text = HiiGetString( submenu->ControlData.ControlHandle, UefiGetPromptField((VOID *)submenu->ControlData.ControlPtr) );
		if ( text == NULL )
			return EFI_OUT_OF_RESOURCES;

        length = (3 + (TestPrintLength( text ) / (NG_SIZE))) * sizeof(CHAR16);
	    newText = EfiLibAllocateZeroPool( length );
	    
        if ( newText == NULL )
		    return EFI_OUT_OF_RESOURCES;

	    SPrint( newText, length, L"%c %s", (submenu->SubMenuType == 2)?L' ':GEOMETRICSHAPE_RIGHT_TRIANGLE, text );
	    MemFreePointer( (VOID **)&text);
	
		text = StringWrapText( newText, Width+2, height );//EIP 97333 : Above we have appeneded the two spaces at begning of sub menu string, so providing proper widht for submenu 
	
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
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
