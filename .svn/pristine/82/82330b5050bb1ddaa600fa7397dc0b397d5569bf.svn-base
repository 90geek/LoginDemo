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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/UefiAction.c $
//
// $Author: Rajashakerg $
//
// $Revision: 13 $
//
// $Date: 12/01/11 7:42a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		UefiAction.c
//
// Description:	This file contains code to handle the uefi actions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

UEFI_ACTION_METHODS gUefiAction =
{
	(OBJECT_METHOD_CREATE)UefiActionCreate,
	(OBJECT_METHOD_DESTROY)LabelDestroy,
	(OBJECT_METHOD_INITIALIZE)UefiActionInitialize,
	(OBJECT_METHOD_DRAW)UefiActionDraw,
	(OBJECT_METHOD_HANDLE_ACTION)UefiActionHandleAction,
	(OBJECT_METHOD_SET_CALLBACK)LabelSetCallback,
	(CONTROL_METHOD_SET_FOCUS)LabelSetFocus,
	(CONTROL_METHOD_SET_POSITION)LabelSetPosition,
	(CONTROL_METHOD_SET_DIMENSIONS)LabelSetDimensions,
	(CONTROL_METHOD_SET_ATTRIBUTES)LabelSetAttributes,
	(CONTROL_METHOD_GET_CONTROL_HIGHT)LabelGetControlHeight
    
};

EFI_STATUS _ProcessActionCallback(CONTROL_INFO * ControlData, BOOLEAN InteractiveText);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiActionCreate
//
// Description:	Function to create an Action Control.
//
// Input:	VOID **object
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiActionCreate( VOID **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(UEFI_ACTION_DATA) );

		if ( *object == NULL )
    {
			Status = EFI_OUT_OF_RESOURCES;
      goto DONE;
    }
	}

	Status = gControl.Create( (void**)object );
	if ( ! EFI_ERROR(Status) )
		((UEFI_ACTION_DATA*)(*object))->Methods = &gUefiAction;

DONE:
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiActionInitialize
//
// Description:	Function to Initialize an Action Control.
//
// Input:	VOID *object, VOID *data
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiActionInitialize( VOID *object, VOID *data )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UEFI_ACTION_DATA *Action = (UEFI_ACTION_DATA*) object;

	Status = gControl.Initialize( Action, data );
	if (EFI_ERROR(Status))
  {
    goto DONE;
  }

	// add extra initialization here...
  Action->Interval = (UINT8)Action->ControlData.ControlFlags.ControlRefresh;
  Action->ControlData.ControlHelp = Action->ControlData.ControlHelp? Action->ControlData.ControlHelp :
                                      UefiGetHelpField(Action->ControlData.ControlPtr);

	SetControlColorsHook(NULL, NULL, NULL, NULL, &(Action->SelBGColor), &(Action->SelFGColor),
			               &(Action->BGColor), &(Action->FGColor), NULL, NULL, NULL, NULL, NULL, NULL, NULL );

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiActionDraw
//
// Description:	Function to draw an Action Control.
//
// Input:	VOID *object
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiActionDraw( VOID *object )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UEFI_ACTION_DATA *Action = (UEFI_ACTION_DATA*) object;

	CHAR16 *text;
  UINT16 token = 0;
	UINT8 ColorLabel = Action->FGColor;

  // check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( Action->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &Action->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorLabel = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				Status = EFI_UNSUPPORTED;
        goto DONE;
				break;
		}
	//}

  token = UefiGetPromptField(Action->ControlData.ControlPtr);
	text = HiiGetString( Action->ControlData.ControlHandle, token);
	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == text){
		text = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
		if(!text)
			return EFI_NOT_FOUND;
		EfiStrCpy(text,L" ");
	}

	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(Action->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( Action->Left , Action->Top, 
				(UINTN)(Action->Width),(UINTN) Action->Height,
				text,(UINT8)( (Action->ControlFocus) ? 
					 Action->SelBGColor  | Action->SelFGColor : 
					 Action->BGColor | ColorLabel ));
	}
	else
	{
		// use frame width minus margins as available space
		// boundary overflow  check
		if ( (TestPrintLength( text) / (NG_SIZE)) > (UINTN)(Action->Width))
				text[HiiFindStrPrintBoundary(text,(UINTN)(Action->Width))] = L'\0';
	
		DrawStringWithAttribute( Action->Left  , Action->Top, text, 
				(UINT8)( (Action->ControlFocus) ? 
						 Action->SelBGColor  | Action->SelFGColor : 
						 Action->BGColor | ColorLabel /*Action->FGColor*/  ));
	}

	MemFreePointer( (VOID **)&text );
	FlushLines( Action->Top  , Action->Top );

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiActionHandleAction
//
// Description:	Function to handle the Label actions.
//
// Input:	VOID *object, ACTION_DATA *data
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiActionHandleAction(VOID *object, ACTION_DATA *data)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;
  UEFI_ACTION_DATA *Action = (UEFI_ACTION_DATA*) object;
  UINT16 Value = 0;
  BOOLEAN Selected = FALSE;
  
  if (data->Input.Type == ACTION_TYPE_MOUSE) //EIP-147140
  {
	if(ControlActionSelect == MapControlMouseActionHook(&data->Input.Data.MouseInfo))
	//check whether MouseTop is within the Height and Width of Interactive Text Control or not
		if((data->Input.Data.MouseInfo.Top >= (UINT32)Action->Top) && (data->Input.Data.MouseInfo.Top < (UINT32)(Action->Top+Action->Height)) &&
		   (data->Input.Data.MouseInfo.Left >= (UINT32)Action->Left) && (data->Input.Data.MouseInfo.Left < (UINT32)(Action->Left+Action->Width)))//EIP-123727
		Selected = TRUE;
  }
  
  if ( data->Input.Type == ACTION_TYPE_KEY )
  {
      if ( ControlActionSelect == MapControlKeysHook(data->Input.Data.AmiKey) )
          Selected = TRUE;
  }
	
	if (Selected )
	{
		MouseStop();

		if (Action->ControlData.ControlFlags.ControlReset) //EIP-153045
			gResetRequired = TRUE;

		//Process UefiAction QuestionConfig
		Status = ProcessActionQuestionConfiguration(&Action->ControlData);

		if(EFI_ERROR(Status))
		{
			//goto DONE;
		}
		//Process UefiAction Callback if any
		Status = _ProcessActionCallback(&Action->ControlData, FALSE);
		return EFI_SUCCESS; //EIP75464 :Status from previous functions are already been handled. So return EFI_SUCCESS
	}
  
  if ( data->Input.Type == ACTION_TYPE_TIMER )
  {
    if(--Action->Interval == 0)
    {
      Action->Interval = (UINT8)Action->ControlData.ControlFlags.ControlRefresh;
      Value = UefiTseLiteGetAmiCallbackIndex(Action->ControlData.ControlConditionalPtr,Action->ControlData.ControlPtr );
      if(Value == INTERACTIVE_TEXT_VALUE)
      {
        //Process UefiAction Callback if any
        Status = _ProcessActionCallback(&Action->ControlData, TRUE);
      }
	  else
		return EFI_SUCCESS; // If it is not Interactive Test just do the Redraw
    }
  }

//DONE:
  return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ProcessActionCallback
//
// Description:	Function process action callbacks
//
// Input:		CONTROL_INFO * ControlData, BOOLEAN InteractiveText
//					
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _ProcessActionCallback(CONTROL_INFO * ControlData, BOOLEAN InteractiveText)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(UefiIsInteractive(ControlData))
  {
    if(InteractiveText)
    {
      Status = SpecialActionCallBack(ControlData, UefiGetControlKey(ControlData));
    }else
    {
	  UefiPreControlUpdate(NULL);	  
      Status = CallFormCallBack(ControlData, UefiGetControlKey(ControlData), FALSE, AMI_CALLBACK_CONTROL_UPDATE);////EIP-53480: Implementation of FormBrowser with actions support 
    }
  }

  return Status;
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
