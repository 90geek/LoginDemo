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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Action.c $
//
// $Author: Rajashakerg $
//
// $Revision: 7 $
//
// $Date: 9/21/12 12:34p $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Action.c
//
// Description:	This file contains code to handle different actions.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

///////////////////////////////////
//VARIABLES DECLARATION
//////////////////////////////////
ACTION_METHODS gAction =
{
	ActionCreate,
	ActionDestroy,
	ActionGetAction,
	ActionClearAction
};
///////////////////////////////////
//FUNCTIONS DECLARATION
//////////////////////////////////
EFI_STATUS 		_ActionReadMouse(MOUSE_INFO *MouseInfo);
BOOLEAN   		FlushKeysAfterRead(void);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActionCreate
//
// Description:	Function to create an action.
//
// Input:	ACTION_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActionCreate( ACTION_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
		*object = EfiLibAllocateZeroPool( sizeof(ACTION_DATA) );

	if ( *object == NULL )
		return EFI_OUT_OF_RESOURCES;

	(*object)->Methods = &gAction;

	_ActionInstallTimer( *object, ONE_SEC / 10 );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActionDestroy
//
// Description:	Function to destroy an action.
//
// Input:	ACTION_DATA *action, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActionDestroy( ACTION_DATA *action, BOOLEAN freeMem )
{
	TimerStopTimer( &action->TimerEvent );

	if ( freeMem )
		MemFreePointer( (VOID **)&action );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActionGetAction
//
// Description:	Function to get an action.
//
// Input:	ACTION_DATA *action
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActionGetAction( ACTION_DATA *action )
{
	EFI_STATUS Status;
	AMI_EFI_KEY_DATA AmiKey;
	MOUSE_INFO MouseInfo;	  

	if ( action->Input.Type != ACTION_TYPE_NULL )
		return EFI_SUCCESS;

	if ( action->TimerCount > 0 )
	{
		action->Input.Type = ACTION_TYPE_TIMER;
		action->Input.Data.TimerCount = action->TimerCount;
		action->TimerCount = 0;
		return EFI_SUCCESS;
	}
	
	MemSet(&AmiKey, sizeof(AMI_EFI_KEY_DATA), 0);	//makesure AmiKey does not have any garbage data
	Status = ActionReadKey( &AmiKey, TIMER_ONE_SECOND / 20 );

	if ( ! EFI_ERROR( Status ) )
	{	//If Key press return that first.
		action->Input.Type = ACTION_TYPE_KEY;
		MemCopy( &action->Input.Data.AmiKey, &AmiKey, sizeof(AMI_EFI_KEY_DATA) );
		return Status;
	}

	//Read the Mouse Movement Co-ordinates and the Mouse Click
    Status = _ActionReadMouse(&MouseInfo);
    if ( ! EFI_ERROR( Status ) )
    {
		//EIP77467 & 78929: Not updating the action data for TSEMOUSE_RIGHT_DOWN and TSEMOUSE_RIGHT_UP
        if((MouseInfo.ButtonStatus!=TSEMOUSE_NULL_CLICK)&&(MouseInfo.ButtonStatus != TSEMOUSE_RIGHT_DOWN)&&(MouseInfo.ButtonStatus != TSEMOUSE_RIGHT_UP))
        {
            action->Input.Type = ACTION_TYPE_MOUSE;
            MemCopy( &action->Input.Data.MouseInfo, &MouseInfo, sizeof(MOUSE_INFO) );
			return Status;
        }
    }


	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActionClearAction
//
// Description:	Function to clear actions 
//
// Input:		ACTION_DATA *action
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActionClearAction( ACTION_DATA *action )
{
	MemSet( &action->Input, sizeof(ACTION_INPUT), 0 );
	return EFI_SUCCESS;
}

//
// Internal functions
//
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ActionReadKey
//
// Description:	Function to read a key.
//
// Input:	AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _ActionReadKey( AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout )
{
	EFI_STATUS Status;
	EFI_STATUS StatusFlush;
	EFI_EVENT EventList[2] = { NULL, NULL };
	UINTN Count = 1, Index = 1;
    AMI_EFI_KEY_DATA    KeyFlush;

	if ( Timeout )
	{
		EventList[0] = gST->ConIn->WaitForKey;

		Status = TimerCreateTimer( &EventList[1], NULL, NULL, TimerRelative, Timeout, EFI_TPL_CALLBACK );
		if ( EFI_ERROR( Status ) )
			return Status;

		Count++;

		gBS->WaitForEvent( Count, EventList, &Index );
	
		TimerStopTimer( &EventList[1] );

		if ( Index == 1 )
			return EFI_NOT_READY;
	}

      Status = gST->ConIn->ReadKeyStroke( gST->ConIn, (EFI_INPUT_KEY*)pAmiKey);

	if ( ! EFI_ERROR( Status ) && FlushKeysAfterRead())//EIP 99022 :check for the FLUSH_KEYS_AFTER_READ token before flushing the keys
	{
		do
		{
			StatusFlush = gST->ConIn->ReadKeyStroke( gST->ConIn, &KeyFlush.Key );
		} while ( ! EFI_ERROR( StatusFlush ) );

	}

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ActionTimer
//
// Description:	Function action timer
//
// Input:		EFI_EVENT Event, VOID *Context
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _ActionTimer( EFI_EVENT Event, VOID *Context )
{
	(*(UINT32 *)Context)++;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ActionInstallTimer
//
// Description:	Function to install action timer
//
// Input:		ACTION_DATA *action, UINT64 TriggerTime
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _ActionInstallTimer( ACTION_DATA *action, UINT64 TriggerTime )
{
	TimerCreateTimer( &action->TimerEvent, _ActionTimer, &action->TimerCount, TimerPeriodic, TriggerTime, EFI_TPL_CALLBACK );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ActionReadMouse
//
// Description:	Function to get mouse action
//
// Input:		MOUSE_INFO *MouseInfo
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//Function Which gets the Mouse action
EFI_STATUS _ActionReadMouse(MOUSE_INFO *MouseInfo)
{
	return MouseReadInfo(MouseInfo);
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
