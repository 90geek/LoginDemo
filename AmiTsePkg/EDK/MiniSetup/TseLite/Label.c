//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Label.c $
//
// $Author: Premkumara $
//
// $Revision: 9 $
//
// $Date: 2/02/12 1:17p $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Label.c
//
// Description:	This file contains code to handle Label operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

LABEL_METHODS gLabel =
{
		(OBJECT_METHOD_CREATE)LabelCreate,
		(OBJECT_METHOD_DESTROY)LabelDestroy,
		(OBJECT_METHOD_INITIALIZE)LabelInitialize,
		(OBJECT_METHOD_DRAW)LabelDraw,
		(OBJECT_METHOD_HANDLE_ACTION)LabelHandleAction,
		(OBJECT_METHOD_SET_CALLBACK)LabelSetCallback,
		(CONTROL_METHOD_SET_FOCUS)LabelSetFocus,
		(CONTROL_METHOD_SET_POSITION)LabelSetPosition,
		(CONTROL_METHOD_SET_DIMENSIONS)LabelSetDimensions,
		(CONTROL_METHOD_SET_ATTRIBUTES)LabelSetAttributes,
		(CONTROL_METHOD_GET_CONTROL_HIGHT)LabelGetControlHeight
	};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelCreate
//
// Description:	Function to create a Label, which uses the Control functions.
//
// Input:	LABEL_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelCreate( LABEL_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(LABEL_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create((void**) object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gLabel;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelDestroy
//
// Description:	Function to destroy a Label, which uses the Control functions.
//
// Input:	LABEL_DATA *label, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelDestroy( LABEL_DATA *label, BOOLEAN freeMem )
{
	if(NULL == label)
	  return EFI_SUCCESS;

	gControl.Destroy( label, FALSE );

	MemFreePointer( (VOID **)&label->Text );

	if( freeMem )
		MemFreePointer( (VOID **)&label );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelInitialize
//
// Description:	Function to Initialize a Label, which uses the Control functions.
//
// Input:	LABEL_DATA *label, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelInitialize( LABEL_DATA *label, VOID *data )
{
	EFI_STATUS Status =  EFI_UNSUPPORTED;

	Status = gControl.Initialize( label, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	label->ControlData.ControlHelp = ((AMI_IFR_LABEL *)label->ControlData.ControlPtr)->Help;

	SetControlColorsHook(NULL, NULL ,  
						 NULL, NULL ,
						 &(label->SelBGColor), &(label->SelFGColor),
			             &(label->BGColor), &(label->FGColor),
						 NULL,NULL ,
					      NULL,NULL ,NULL,NULL,NULL );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelDraw
//
// Description:	Function to draw a Label.
//
// Input:	LABEL_DATA *label
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelDraw(LABEL_DATA *label )
{
	CHAR16 *text;
	EFI_STATUS Status = EFI_SUCCESS;

	UINT8 ColorLabel = label->FGColor;
	// check conditional ptr if necessary
    
    //EIP 75486 Support grayout condition for readonly controls
	//if( label->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &label->ControlData ) )
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

	text = HiiGetString( label->ControlData.ControlHandle, (UINT16)((AMI_IFR_LABEL*)(label->ControlData.ControlPtr))->Text );
	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == text){
		text = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
		if(!text)
			return EFI_NOT_FOUND;
		EfiStrCpy(text,L" ");
	}
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(label->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( label->Left , label->Top, 
				(UINTN)(label->Width),(UINTN) label->Height,
				text,(UINT8)( (label->ControlFocus) ? 
					 label->SelBGColor  | label->SelFGColor : 
					 label->BGColor | ColorLabel ));
	}
	else
	{
		// use frame width minus margins as available space
		// boundary overflow  check
		if ( (TestPrintLength( text) / (NG_SIZE)) > (UINTN)(label->Width))
				text[HiiFindStrPrintBoundary(text,(UINTN)(label->Width))] = L'\0';
	
		DrawStringWithAttribute( label->Left  , label->Top, text, 
				(UINT8)( (label->ControlFocus) ? 
						 label->SelBGColor  | label->SelFGColor : 
						 label->BGColor | ColorLabel /*label->FGColor*/  ));
	}

	MemFreePointer( (VOID **)&text );
	FlushLines( label->Top  , label->Top );

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelSetCallback
//
// Description:	Function to set callback.
//
// Input:		 LABEL_DATA *label, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelSetCallback( LABEL_DATA *label, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( label, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelHandleAction
//
// Description:	Function to handle the Label actions.
//
// Input:	LABEL_DATA *label, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelHandleAction( LABEL_DATA *label, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;


    if ( Data->Input.Type == ACTION_TYPE_KEY )
    {
        CONTROL_ACTION Action;

        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);

        if(ControlActionSelect == Action)
        {
    		// this notifies container to display a msgbox or boot, etc depending on cookie
    		if(label->Callback != NULL)
    			label->Callback( label->Container,label, label->Cookie );
    
    		Status = EFI_SUCCESS;
        }
    }

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelSetFocus
//
// Description:	Function to set the Label focus.
//
// Input:	LABEL_DATA *label, BOOLEAN focus
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelSetFocus(LABEL_DATA *label, BOOLEAN focus)
{
	UINT8 u8ChkResult;
	
	if(focus != FALSE)
	{
		u8ChkResult = CheckControlCondition( &label->ControlData );
		
		//Setting focus to control which has no control-condtion and token TSE_SETUP_GRAYOUT_SELECTABLE is enable to make GrayoutIf control to focus and selectable
		if ( ((u8ChkResult != COND_NONE) && (u8ChkResult != COND_GRAYOUT)) ||
			(!IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT)) 
		   ){
			return EFI_UNSUPPORTED;
		}
	}



	if( !(label->ControlFocus && focus) )
		label->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelSetPosition
//
// Description:	Function to set position.
//
// Input:		LABEL_DATA *label, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelSetPosition(LABEL_DATA *label, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( (CONTROL_DATA*)label, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		LABEL_DATA *label, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelSetDimensions(LABEL_DATA *label, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( (CONTROL_DATA*)label, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		LABEL_DATA *label, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelSetAttributes(LABEL_DATA *label, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes((CONTROL_DATA*) label, FGColor, BGColor );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LabelGetLabelHeight
//
// Description:	Function to get label height.
//
// Input:		LABEL_DATA *label, UINT16 Width, UINT16 *height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LabelGetControlHeight(LABEL_DATA *label, VOID * frame, UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
		
		*height = 1;
		Width = ((FRAME_DATA*)frame)->FrameData.Width - 2;
	
		text = HiiGetString( label->ControlData.ControlHandle, (UINT16)((AMI_IFR_LABEL*)(label->ControlData.ControlPtr))->Text  );		
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


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
