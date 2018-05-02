//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/timer.c $
//
// $Author: Madhans $
//
// $Revision: 3 $
//
// $Date: 2/19/10 1:02p $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		timer.c
//
// Description:	This file contains code to handle the timer.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimerCreateTimer
//
// Description:	function to create a timer event and to set the timer
//
// Input:		EFI_EVENT *Event, EFI_EVENT_NOTIFY Callback,
//				VOID *Context, EFI_TIMER_DELAY Delay, UINT64 Trigger,
//				EFI_TPL CallBackTPL
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimerCreateTimer( EFI_EVENT *Event, EFI_EVENT_NOTIFY Callback,
		VOID *Context, EFI_TIMER_DELAY Delay, UINT64 Trigger, EFI_TPL CallBackTPL )
{
	EFI_STATUS Status;
	UINT32 EventType = EFI_EVENT_TIMER;

	if ( Callback != NULL )
		EventType |= EFI_EVENT_NOTIFY_SIGNAL;
	
	Status = gBS->CreateEvent(
			EventType,
			CallBackTPL,
			Callback,
			Context,
			Event
			);

	if ( EFI_ERROR( Status ) )
		return Status;

	Status = gBS->SetTimer( *Event, Delay, Trigger );
	if ( EFI_ERROR( Status ) )
		TimerStopTimer( Event );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimerStopTimer
//
// Description:	function to stop the timer event.
//
// Input:		EFI_EVENT *Event
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TimerStopTimer( EFI_EVENT *Event )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( ( Event == NULL ) || ( *Event == NULL ) )
		return Status;

	gBS->CloseEvent( *Event );
	*Event = NULL;

	return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
