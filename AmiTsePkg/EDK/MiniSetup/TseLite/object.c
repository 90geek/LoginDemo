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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/object.c $
//
// $Author: Madhans $
//
// $Revision: 3 $
//
// $Date: 2/19/10 1:04p $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Object.c
//
// Description:	This file contains code to handle Objects
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

OBJECT_METHODS gObject = 
{
	ObjectCreate,
	ObjectDestroy,
	ObjectInitialize,
	ObjectDraw,
	ObjectHandleAction,
	ObjectSetCallback
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectCreate
//
// Description:	function to create an object
//
// Input:	 OBJECT_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ObjectCreate( VOID **AnyObject )
{
	OBJECT_DATA **object = (OBJECT_DATA **)AnyObject;
	if ( *object == NULL )
		*object = EfiLibAllocateZeroPool( sizeof(OBJECT_DATA) );

	if ( *object == NULL )
		return EFI_OUT_OF_RESOURCES;

	(*object)->Methods = &gObject;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectDestroy
//
// Description:	function to Destroy an object
//
// Input:	 OBJECT_DATA **object, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//EFI_STATUS ObjectDestroy( OBJECT_DATA *object, BOOLEAN freeMem )
EFI_STATUS ObjectDestroy( VOID *object, BOOLEAN freeMem )
{
	if ( freeMem )
		MemFreePointer( (VOID **)&object );

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectInitialize
//
// Description:	Function to initialize an object
//
// Input:	 OBJECT_DATA *object, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//EFI_STATUS ObjectInitialize( OBJECT_DATA *object, VOID *data )
EFI_STATUS ObjectInitialize( VOID *object, VOID *data )
{
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectDraw
//
// Description:	Function to draw an object
//
// Input:		OBJECT_DATA *object
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//EFI_STATUS ObjectDraw( OBJECT_DATA *object )
EFI_STATUS ObjectDraw( VOID *object )
{
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectHandleAction
//
// Description:	Function to handle object action
//
// Input:		OBJECT_DATA *object, ACTION_DATA *Data
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//EFI_STATUS ObjectHandleAction( OBJECT_DATA *object, ACTION_DATA *Data )
EFI_STATUS ObjectHandleAction( VOID *object, ACTION_DATA *Data )
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectSetCallback
//
// Description:	Function to set  object callback
//
// Input:		OBJECT_DATA *object, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//EFI_STATUS ObjectSetCallback( VOID *object, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
EFI_STATUS ObjectSetCallback( VOID *AnyObject, VOID * container, OBJECT_CALLBACK callback, VOID *cookie )
{
	 OBJECT_DATA *object = (OBJECT_DATA *)AnyObject;
	object->Callback = callback;
	object->Container = container,
	object->Cookie = cookie;

	return EFI_SUCCESS;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
