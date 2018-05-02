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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/variable.c $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 9/28/11 10:48p $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		variable.c
//
// Description:	This file contains code to handle bootonly lever variables operations.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

extern UINTN gSetupCount;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarGetNvramName
//
// Description:	function to get the NvRam Variable Name
//
// Input:		CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size
//
// Output:		Name String
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *VarGetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size )
{
	VOID *buffer = NULL;
	UINT32 attrib = 0;
	EFI_STATUS Status = EFI_UNSUPPORTED;

	// NO GET Functionality is taken care by VarGetNvram()

	if ( attributes != NULL )
    {
        attrib = *attributes;
    }

	Status = UefiFormCallbackNVRead(name, guid, &attrib, size, &buffer);

	if(EFI_ERROR(Status))
	{
	    Status = gRT->GetVariable(
			name,
			guid,
			&attrib,
			size,
			buffer
			);

	    if ( Status != EFI_BUFFER_TOO_SMALL )
		    return buffer;

	    buffer = EfiLibAllocateZeroPool ( *size + 1);
	    if ( buffer == NULL )
		   return buffer;

	    Status = gRT->GetVariable(
			name,
			guid,
			&attrib,
			size,
			buffer
			);
	}
	    
	if ( EFI_ERROR( Status ) )
	    MemFreePointer( (VOID *)&buffer );

	if ( attributes != NULL )
		*attributes = attrib;

	return buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarSetNvramName
//
// Description:	function to Set the NvRam Variable Name
//
// Input:		CHAR16 *name, EFI_GUID *guid, UINT32 *attributes,
//					VOID *buffer, UINTN *size
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarSetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	// NO SET Functionality is taken care by VarSetNvram()

	Status = UefiFormCallbackNVWrite(name, guid, attributes, buffer, size);

	if(EFI_ERROR(Status ) )
		Status = gRT->SetVariable(
			name,
			guid,
			attributes,
			size,
			buffer
			);

	return(Status);
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
