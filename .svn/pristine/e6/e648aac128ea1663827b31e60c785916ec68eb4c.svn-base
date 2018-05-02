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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Text.c $
//
// $Author: Blaines $
//
// $Revision: 12 $
//
// $Date: 2/01/12 5:54p $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		text.c
//
// Description:	This file contains code to handle text operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

TEXT_METHODS gText =
{
	(OBJECT_METHOD_CREATE)TextCreate,
	(OBJECT_METHOD_DESTROY)TextDestroy,
	(OBJECT_METHOD_INITIALIZE)TextInitialize,
	(OBJECT_METHOD_DRAW)TextDraw,
	(OBJECT_METHOD_HANDLE_ACTION)TextHandleAction,
	(OBJECT_METHOD_SET_CALLBACK)TextSetCallback,
	(CONTROL_METHOD_SET_FOCUS)TextSetFocus,
	(CONTROL_METHOD_SET_POSITION)TextSetPosition,
	(CONTROL_METHOD_SET_DIMENSIONS)TextSetDimensions,
	(CONTROL_METHOD_SET_ATTRIBUTES)TextSetAttributes,
	(CONTROL_METHOD_GET_CONTROL_HIGHT)TextGetControlHeight,
	TextSetText
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextCreate
//
// Description:	this function uses the create function of control
//					and creates text
//
// Input:	TEXT_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextCreate( TEXT_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(TEXT_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create((void**) object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gText;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys the text
//
// Input:	TEXT_DATA *text, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextDestroy( TEXT_DATA *text, BOOLEAN freeMem )
{
	if(NULL == text)
	  return EFI_SUCCESS;

	gControl.Destroy( text, FALSE );

	MemFreePointer( (VOID **)&text->LabelText );
	MemFreePointer( (VOID **)&text->Text );

	if ( freeMem )
		MemFreePointer( (VOID **)&text );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextDestroy
//
// Description:	this function uses the initialize function of control
//					and initializes the text
//
// Input:	TEXT_DATA *text, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextInitialize( TEXT_DATA *text, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( text, data );
	if (EFI_ERROR(Status))
		return Status;

	SetControlColorsHook(&(text->BGColor), &(text->FGColor), 
						NULL, NULL, 
						NULL, NULL,
	                    			NULL, NULL,
						NULL, NULL,
						NULL, 
						NULL, NULL,
						NULL,NULL);

	// add extra initialization here...
	text->ControlData.ControlHelp = UefiGetHelpField ((VOID*)text->ControlData.ControlPtr);
	//text->FGColor= EFI_DARKGRAY;
	StyleGetSpecialColor( CONTROL_TYPE_TEXT, &(text->FGColor)) ;

	text->LabelMargin = (UINT8)gControlLeftMargin;


	text->Interval = (UINT8)text->ControlData.ControlFlags.ControlRefresh;
	text->LabelText = HiiGetString( text->ControlData.ControlHandle, UefiGetTextField((VOID*)text->ControlData.ControlPtr));
//	if ( text->LabelText == NULL )						//EIP122907 In some case in init hiigetstring is failing but in draw its passing so commented this check.
//		return EFI_OUT_OF_RESOURCES;

	text->Text = HiiGetString( text->ControlData.ControlHandle, UefiGetTextTwoField((VOID *)text->ControlData.ControlPtr));
//	if ( text->Text == NULL )
//		return EFI_OUT_OF_RESOURCES;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextDraw
//
// Description:	function to draw the text with attributes.
//
// Input:	TEXT_DATA *text
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextDraw( TEXT_DATA *text )
{
	CHAR16 *txt =NULL, *txt2 = NULL;
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 ColorText = text->FGColor ;


	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( text->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &text->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorText = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	txt = HiiGetString( text->ControlData.ControlHandle, UefiGetTextField((VOID*)text->ControlData.ControlPtr));
	if ( txt == NULL )
		return EFI_OUT_OF_RESOURCES;

 	txt2 = HiiGetString( text->ControlData.ControlHandle, UefiGetTextTwoField((VOID*)text->ControlData.ControlPtr));
	if ( txt2 == NULL )
		return EFI_OUT_OF_RESOURCES;

	gText.SetText(text,txt,txt2);
	MemFreePointer ((VOID **)&txt);
	MemFreePointer ((VOID **)&txt2);

	if ( text->LabelText == NULL )
	{ 
		Status = EFI_UNSUPPORTED;
		return Status;
	}

		// labeltext boundary overflow  check	
	if(text->Height>1 && IsTSEMultilineControlSupported())//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	{
		DrawMultiLineStringWithAttribute( (UINTN)text->Left, (UINTN) text->Top, 
					(UINTN)(text->LabelMargin - text->Left),(UINTN)text->Height,
					text->LabelText, text->BGColor |ColorText );
	}
	else
	{
		if ( (TestPrintLength( text->LabelText ) / (NG_SIZE)) > (UINTN)(text->LabelMargin - text->Left  )/*21*/ )
				text->LabelText[HiiFindStrPrintBoundary(text->LabelText ,(UINTN)(text->LabelMargin - text->Left  ))] = L'\0';
	
		DrawStringWithAttribute( text->Left , text->Top, text->LabelText, text->BGColor |  ColorText /*text->FGColor*/  );
	}

	if ( text->Text != NULL )
	{
		//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
		if(text->Height>1 && IsTSEMultilineControlSupported())
		{
				DrawMultiLineStringWithAttribute( (UINTN)text->Left + text->LabelMargin, (UINTN) text->Top, 
						(UINTN)((text->Width + text->Left)  - text->LabelMargin -2),(UINTN)text->Height,
						text->Text, text->BGColor |ColorText );//EIP 73391 : Adjusted the cordinates to show maximum string in control left area

						
		}
		else
		{
			// text boundary overflow check
			//EIP 73391 : Adjusted the cordinates to show maximum string in control left area
	        if ( (TestPrintLength( text->Text ) / (NG_SIZE)) >= (UINTN)((text->Width + text->Left) - text->LabelMargin -2) )
	            text->Text[HiiFindStrPrintBoundary(text->Text ,(UINTN)((text->Width + text->Left) - text->LabelMargin -2))] = L'\0';
	        DrawStringWithAttribute( text->Left + text->LabelMargin , text->Top, text->Text, text->BGColor |ColorText );
		}
	}

	//EIP-72610 if TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		FlushLines(text->Top, text->Top + text->Height - 1);
	}
	else
	{
		FlushLines(text->Top, text->Top);
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextHandleAction
//
// Description:	function to handle the text actions
//
// Input:	TEXT_DATA *text, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextHandleAction( TEXT_DATA *text, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if ( (Data->Input.Type == ACTION_TYPE_TIMER) && ((UINT8)text->ControlData.ControlFlags.ControlRefresh != 0))
	{
		Status = CallTextCallBack(text, Data);
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetCallback
//
// Description:	Function to set callback.
//
// Input:		TEXT_DATA *text, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie 
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetCallback( TEXT_DATA *text, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( text, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetFocus
//
// Description:	Function to set focus.
//
// Input:		TEXT_DATA *text, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetFocus(TEXT_DATA *text, BOOLEAN focus)
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetPosition
//
// Description:	Function to set position.
//
// Input:		TEXT_DATA *text, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetPosition(TEXT_DATA *text, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition((CONTROL_DATA*) text, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetDimensions
//
// Description:	Function to set text dimension.
//
// Input:		TEXT_DATA *text, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetDimensions(TEXT_DATA *text, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( (CONTROL_DATA*)text, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetAttributes
//
// Description:	Function to set text attributes.
//
// Input:		TEXT_DATA *text, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetAttributes(TEXT_DATA *text, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes((CONTROL_DATA*) text, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetText
//
// Description:	function to set the text
//
// Input:	TEXT_DATA *text, CHAR16 *label, CHAR16 *value
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetText( TEXT_DATA *text, CHAR16 *label, CHAR16 *value )
{
	if ( label != NULL )
	{
		MemFreePointer( (void**)&text->LabelText );
		text->LabelText = StrDup( label );
	}

	if ( value != NULL )
	{
		MemFreePointer( (void**)&text->Text );
		text->Text = StrDup( value );
	}

	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextGetControlHeight
//
// Description:	function to get the text height
//
// Input:	TEXT_DATA *text, Frame,  UINT16 *height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextGetControlHeight( TEXT_DATA *text, VOID* frame,  UINT16 *height )
{
	//EIP-72610 if TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL;
		UINT16 tmpHeight=0;
		UINT16 Width;
	
		//EIP-147142  
		//Make sure text->Label and text->text are updated before computing the control height 		
		gText.SetText(text,
		        HiiGetString( text->ControlData.ControlHandle, UefiGetTextField((VOID*)text->ControlData.ControlPtr)),
		        HiiGetString( text->ControlData.ControlHandle, UefiGetTextTwoField((VOID*)text->ControlData.ControlPtr))
		        );
    
		Width = (UINT16)(text->LabelMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gLabelLeftMargin));
		newText = StringWrapText( text->Text, (UINT16)(((FRAME_DATA *)frame)->FrameData.Width - text->LabelMargin -2), &tmpHeight );
		*height = tmpHeight;
	    MemFreePointer( (VOID **)&newText );
	
		newText = StringWrapText( text->LabelText, Width, &tmpHeight );
	
		if(tmpHeight > *height)
			*height = tmpHeight;
	
		(*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
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
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
