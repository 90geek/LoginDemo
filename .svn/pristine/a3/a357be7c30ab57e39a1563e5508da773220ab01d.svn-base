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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/mem.c $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 11/10/11 12:52a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		mem.c
//
// Description:	file contains code to handle the memory operations. 
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemFreePointer
//
// Description:	function to free the pointers
//
// Input:		VOID **ptr
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemFreePointer( VOID **ptr )
{
	if ( ( ptr == NULL ) || ( *ptr == NULL ) )
		return;

	gBS->FreePool( *ptr );
	*ptr = NULL;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------
// Procedure:	StringZeroFreeMemory
//
// Description:	Function to free the string pointers and zeroing its memory, used for strings
//				Care should be taken String Length identification function is used
//
// Input:		VOID **ptr
//
// Output:		void
//
//-------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StringZeroFreeMemory (VOID **ptr)
{
	if ( (ptr == NULL) || (*ptr == NULL))
		return;

	MemSet (*ptr, (EfiStrLen ((CHAR16 *)*ptr) * sizeof (CHAR16)), 0);
	gBS->FreePool (*ptr);
	*ptr = NULL;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemCopy
//
// Description:	function to copy a memory
//
// Input:		VOID *dest, VOID *src, UINTN size
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemCopy( VOID *dest, VOID *src, UINTN size )
{
	gBS->CopyMem( dest, src, size );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemSet
//
// Description:	function to set the memory with the specified value
//
// Input:		VOID *buffer, UINTN size, UINT8 value
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if TSE_USE_EDK_LIBRARY
VOID MemSet( VOID *buffer, UINTN size, UINT8 value )
{
	gBS->SetMem( buffer, size, value );
}
#endif //#if TSE_USE_EDK_LIBRARY

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemReallocateZeroPool
//
// Description:	function to reuse a allocated buffer
//
// Input:		VOID *oldBuffer, UINTN oldSize, UINTN newSize
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *MemReallocateZeroPool( VOID *oldBuffer, UINTN oldSize, UINTN newSize )
{
	VOID *buffer;

	buffer = EfiLibAllocateZeroPool( newSize );
	if ( buffer == NULL )
		return buffer;

	if ( newSize < oldSize )
		oldSize = newSize;

	if ( oldBuffer != NULL )
		MemCopy( buffer, oldBuffer, oldSize );

	MemFreePointer( (VOID **)&oldBuffer );

	return buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemFillUINT16Buffer
//
// Description:	function to fill a UINT16 Buffer
//
// Input:		VOID *buffer, UINTN bufferSize, UINT16 value
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemFillUINT16Buffer( VOID *buffer, UINTN bufferSize, UINT16 value )
{
	UINTN	Index;
	UINT16	*bufPtr = (UINT16 *)buffer;

	for ( Index = 0; Index < bufferSize; Index++ )
		*bufPtr++ = value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemCmp
//
// Description:	function to compare the memory of two buffers.
//
// Input:		UINT8 *dest, UINT8 *src, UINTN size
//
// Output:		0/1/-1
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if TSE_USE_EDK_LIBRARY
INTN MemCmp( UINT8 *dest, UINT8 *src, UINTN size )
{
	UINTN i;

	for( i=0; i<size; i++)
	{
		if(dest[i] < src[i])
			return -1;
        if(dest[i] > src[i])
            return 1;
	}
	return 0;
}
#endif //#if TSE_USE_EDK_LIBRARY

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
