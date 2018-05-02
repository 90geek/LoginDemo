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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/screen.c $
//
// $Author: Madhans $
//
// $Revision: 5 $
//
// $Date: 9/16/10 8:38p $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		screen.c
//
// Description:	This file contains code for screen operations.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

VOID MouseStop(VOID);
VOID MouseRefresh(VOID);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ClearScreenWithoutFlush
//
// Description:	function to clear screen without flushing.
//
// Input:		UINT8 Attrib
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearScreenWithoutFlush( UINT8 Attrib )
{

	gActiveBuffer->ScreenTag = ACTIVE_SCREEN_TAG;
	MemSet( gActiveBuffer->Attribs, sizeof(gActiveBuffer->Attribs), Attrib );

	MemFillUINT16Buffer( gActiveBuffer->Chars, MAX_DIMENSIONS, (UINT16)L' ' );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ClearLinesWithoutFlush
//
// Description:	function to clear lines without flushing.
//
// Input:		UINT8 LineStart, UINT8 NumLines, UINT8 Attrib
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearLinesWithoutFlush( UINT8 LineStart, UINT8 NumLines, UINT8 Attrib )
{

	gActiveBuffer->ScreenTag = ACTIVE_SCREEN_TAG;
	MemSet(&( gActiveBuffer->Attribs[LineStart*gMaxCols]), NumLines*gMaxCols /*sizeof(gActiveBuffer->Attribs)*/, Attrib );

	MemFillUINT16Buffer( &(gActiveBuffer->Chars[LineStart*gMaxCols]), NumLines*gMaxCols/*MAX_ROWS * MAX_COLS*/, (UINT16)L' ' );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ClearScreen
//
// Description:	function to clear the screen.
//
// Input:		UINT8 Attrib
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearScreen( UINT8 Attrib )
{
	ClearScreenWithoutFlush( Attrib );

	if(gST->ConOut!=NULL)
	{
		gST->ConOut->EnableCursor( gST->ConOut, FALSE );
		gST->ConOut->SetAttribute( gST->ConOut, Attrib );
		gST->ConOut->ClearScreen( gST->ConOut);
	}

	FlushLines( 0, gMaxRows - 1 );

}  

EFI_UGA_PIXEL *gPostscreenwithlogo;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveScreen
//
// Description:	function to get the backup of the screen.
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *SaveScreen( VOID )
{
	SCREEN_BUFFER *Buffer;

	Buffer = EfiLibAllocatePool( sizeof(SCREEN_BUFFER) );

	if ( Buffer != NULL )
	{
		MemCopy( Buffer, gActiveBuffer, sizeof(SCREEN_BUFFER) );
		Buffer->ScreenTag = SAVE_SCREEN_TAG;
	}

	return (VOID *)Buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RestoreScreen
//
// Description:	function to restore the screen from the saved screen buffer.
//
// Input:		VOID *ScreenBuffer
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreScreen( VOID *ScreenBuffer )
{
	SCREEN_BUFFER *Buffer = (SCREEN_BUFFER *)ScreenBuffer;

	MouseStop();

	if ( ( Buffer == NULL ) || ( Buffer->ScreenTag != SAVE_SCREEN_TAG ) )
		return;

	///Clear Original data in the buffers before restoring with saved screen buffer.
	MemSet(gActiveBuffer, sizeof(SCREEN_BUFFER), 0);
	MemSet(gFlushBuffer, sizeof(SCREEN_BUFFER), 0);

	MemCopy( gActiveBuffer, Buffer, sizeof(SCREEN_BUFFER) );
	gActiveBuffer->ScreenTag = ACTIVE_SCREEN_TAG;

	FlushLines( 0, gMaxRows - 1 );
	DoRealFlushLines();

	MemFreePointer( (VOID **)&Buffer );

	MouseRefresh();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveGraphicsScreen
//
// Description:	Saves post graphics screen
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveGraphicsScreen(VOID)
{
	   UINTN HorizontalResolution = 0;
 	   UINTN VerticalResolution = 0;
		
		GetScreenResolution(&HorizontalResolution, &VerticalResolution);
		gPostscreenwithlogo = EfiLibAllocateZeroPool( HorizontalResolution * VerticalResolution * sizeof(EFI_UGA_PIXEL)); 

		if (NULL == gPostscreenwithlogo)
		{
			return;
		}
		 MouseStop();
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
    if ( gGOP)
	    gGOP->Blt (
	        gGOP,
	        gPostscreenwithlogo,
	        EfiBltVideoToBltBuffer,
	       (UINTN)0, (UINTN)0,
			 (UINTN)0, (UINTN)0,
	       HorizontalResolution, VerticalResolution,
	       0
	        );
#else
    if ( gUgaDraw)
	    gUgaDraw->Blt (
	        gUgaDraw,
	        gPostscreenwithlogo,
	        EfiUgaVideoToBltBuffer,
	       (UINTN)0, (UINTN)0,
			 (UINTN)0, (UINTN)0,
	       HorizontalResolution, VerticalResolution,
	       0
	        );
#endif
      MouseRefresh();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RestoreGraphicsScreen
//
// Description:	Restores the saved post graphics screen
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreGraphicsScreen (VOID)
{
   
   if( gPostscreenwithlogo != NULL )
   {
      UINTN HorizontalResolution = 0;
      UINTN VerticalResolution = 0;
      
      GetScreenResolution(&HorizontalResolution, &VerticalResolution);
      MouseStop();
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
      if ( gGOP)
         gGOP->Blt (
         gGOP,
         gPostscreenwithlogo,
         EfiBltBufferToVideo,
         (UINTN)0, (UINTN)0,
         (UINTN)0, (UINTN)0,
         HorizontalResolution, VerticalResolution,
         0
      );
#else
      if ( gUgaDraw)
         gUgaDraw->Blt (
         gUgaDraw,
         gPostscreenwithlogo,
         EfiUgaBltBufferToVideo,
         (UINTN)0, (UINTN)0,
         (UINTN)0, (UINTN)0,
         HorizontalResolution, VerticalResolution,
         0
      );
#endif
      MouseRefresh();
      MemFreePointer( (VOID **)&gPostscreenwithlogo );
   }
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
