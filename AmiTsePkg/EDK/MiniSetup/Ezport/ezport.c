//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2011, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                     Phone: (770)-246-8600                   **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/ezport.c $
//
// $Author: Rajashakerg $
//
// $Revision: 12 $
//
// $Date: 5/24/12 7:29a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		ezport.c
//
// Description:	Main file for ezport style module.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "minisetup.h"
#include "ezport.h"

extern	STYLECOLORS  Colors ;
extern 	AMI_IFR_MENU gMenuData ;

extern UINTN gLabelLeftMargin ;
extern UINTN gControlLeftMargin ;
extern UINTN gControlLeftPad ;
extern UINTN gControlRightAreaWidth ;
static CALLBACK_SUBMENU gMenuCallbackData = { { CALLBACK_TYPE_MENU, sizeof(CALLBACK_MENU) }, 0 };
static CALLBACK_SUBMENU gSubmenuCallbackData = { { CALLBACK_TYPE_SUBMENU, sizeof(CALLBACK_SUBMENU) }, 0 };
static CALLBACK_VARIABLE gVariableCallbackData = { { CALLBACK_TYPE_VARIABLE, sizeof(CALLBACK_VARIABLE) }, 0, 0, 0, NULL };
static CALLBACK_PASSWORD gPasswordCallbackData = { { CALLBACK_TYPE_PASSWORD, sizeof(CALLBACK_PASSWORD) }, 0, 0, 0, NULL, TRUE };

VOID _FrameSubmenuCallback( FRAME_DATA *frame, SUBMENU_DATA *submenu, VOID *cookie );
VOID _FrameMenuCallback( FRAME_DATA *frame, MENU_DATA *menu, VOID *cookie );
VOID HotclickESCaction(VOID);

BOOLEAN   gotoExitOnEscKey(EFI_GUID *exitFormGuid, UINT16 *pageClass, UINT16 *pageSubclass, UINT16 *pageFormID); //EIP-112628

#if SETUP_STYLE_EZPORT

#if SETUP_STYLE_FULL_SCREEN
static FRAME_INFO _gStyleFullSubFrames[] =
{
//	{ FrameType		Drawable	Border,		BorderType,	Width,			Height,			Top,			Left,			FGColor,		BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE,		0,		TITLE_FULL_W,		TITLE_FULL_H,		TITLE_FULL_Y,		TITLE_FULL_X,		TITLE_FGCOLOR,		TITLE_BGCOLOR		},// TITLE
	{ SUBTITLE_FRAME,	TRUE,		FALSE,		0,		MENU_FULL_W,		MENU_FULL_H,		MENU_FULL_Y,		MENU_FULL_X,		MENU_FGCOLOR,		MENU_BGCOLOR		},// SUBTITLE (MENU)
	{ MAIN_FRAME,		TRUE,		FALSE,		0,		MAIN_FULL_W,		MAIN_FULL_H,		MAIN_FULL_Y,		MAIN_FULL_X,		PAGE_FGCOLOR,		MAIN_BGCOLOR		},// Main
	{ HELP_FRAME,		TRUE,		FALSE,		0,		HELP_FULL_W,		HELP_FULL_H,		HELP_FULL_Y,		HELP_FULL_X,		HELP_FGCOLOR,		HELP_BGCOLOR		},// HELP
	{ NAV_FRAME,		TRUE,		FALSE,		0,		NAV_FULL_W,		NAV_FULL_H,		NAV_FULL_Y,		NAV_FULL_X,		NAV_FGCOLOR,		NAV_BGCOLOR		},// NAVIGATION
	{ HELPTITLE_FRAME,	TRUE,		FALSE,		0,		HELPTITLE_FULL_W,	HELPTITLE_FULL_H,	HELPTITLE_FULL_Y,	HELPTITLE_FULL_X,	HELPTITLE_FGCOLOR,	HELPTITLE_BGCOLOR	} // HELP TITLE (Copyright)
};
#endif

static FRAME_INFO _gStyleStandardSubFrames[] =
{
//	{ FrameType		Drawable	Border,		BorderType,	Width,		Height,		Top,		Left,		FGColor,		BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE,		0,		TITLE_W,	TITLE_H,	TITLE_Y,	TITLE_X,	TITLE_FGCOLOR,		TITLE_BGCOLOR		},// TITLE
	{ SUBTITLE_FRAME,	TRUE,		FALSE,		0,		MENU_W,		MENU_H,		MENU_Y,		MENU_X,		MENU_FGCOLOR,		MENU_BGCOLOR		},// SUBTITLE (MENU)
	{ MAIN_FRAME,		TRUE,		FALSE,		0,		MAIN_W,		MAIN_H,		MAIN_Y,		MAIN_X,		PAGE_FGCOLOR,		MAIN_BGCOLOR		},// Main
	{ HELP_FRAME,		TRUE,		FALSE,		0,		HELP_W,		HELP_H,		HELP_Y,		HELP_X,		HELP_FGCOLOR,		HELP_BGCOLOR		},// HELP
	{ NAV_FRAME,		TRUE,		FALSE,		0,		NAV_W,		NAV_H,		NAV_Y,		NAV_X,		NAV_FGCOLOR,		NAV_BGCOLOR		},// NAVIGATION
	{ HELPTITLE_FRAME,	TRUE,		FALSE,		0,		HELPTITLE_W,	HELPTITLE_H,	HELPTITLE_Y,	HELPTITLE_X,	HELPTITLE_FGCOLOR,	HELPTITLE_BGCOLOR	} // HELP TITLE (Copyright)
};

AMITSE_CONTROL_MAP gTseControlMap[] =
{
//	ControlType			 ControlMethods		 	CallbackSuppored 	CallbackFunction		CallbackContext		
 { CONTROL_TYPE_MENU, 	 (CONTROL_METHODS*)&gMenu, 	TRUE, (VOID*)(UINTN)&_FrameMenuCallback, (VOID*)(UINTN)&gMenuCallbackData},
 { CONTROL_TYPE_SUBMENU, (CONTROL_METHODS*)&gSubMenu,TRUE, (VOID*)(UINTN)&_FrameSubmenuCallback, (VOID*) &gSubmenuCallbackData},
 { CONTROL_TYPE_LABEL, 	 (CONTROL_METHODS*)&gLabel, 	TRUE, (VOID*)(UINTN)&StyleLabelCallback, (VOID*) NULL},
 { CONTROL_TYPE_TEXT, 	 (CONTROL_METHODS*)&gText, 	FALSE,(VOID*)NULL, (VOID*) NULL},
 { CONTROL_TYPE_POPUP_STRING, (CONTROL_METHODS*)&gPopupString, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
 { CONTROL_TYPE_DATE, (CONTROL_METHODS*)&gDate, FALSE, (VOID*)NULL, (VOID*) NULL},
 { CONTROL_TYPE_TIME, (CONTROL_METHODS*)&gTime, FALSE, (VOID*)NULL, (VOID*) NULL},
 { CONTROL_TYPE_POPUPSEL, (CONTROL_METHODS*)&gPopupSel, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
	// Checkbox is just popup sel
 { CONTROL_TYPE_CHECKBOX, (CONTROL_METHODS*)&gPopupSel, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
 { CONTROL_TYPE_MEMO, (CONTROL_METHODS*)&gMemo, FALSE, (VOID*)NULL, (VOID*)NULL},
 { CONTROL_TYPE_NUMERIC, (CONTROL_METHODS*)&gNumeric, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
 { CONTROL_TYPE_ORDERED_LIST, (CONTROL_METHODS*)&gOrdListBox, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
 { CONTROL_TYPE_PASSWORD, (CONTROL_METHODS*)&gPopupPassword, TRUE, (VOID*)(UINTN)&_FramePasswordCallback, (VOID*)&gPasswordCallbackData},
 { CONTROL_TYPE_ACTION, (CONTROL_METHODS*)&gUefiAction, TRUE, (VOID*)(UINTN) &StyleLabelCallback, (VOID*) NULL},
 { CONTROL_TYPE_RESET, (CONTROL_METHODS*)&gResetButton, TRUE, (VOID*)(UINTN) &StyleLabelCallback, (VOID*) NULL},//EIP:56413 Updated the Reset Button Control information
	// CONTROL_TYPE_NULL need to be last member 
 { CONTROL_TYPE_NULL, (CONTROL_METHODS*)NULL, FALSE, (VOID*)NULL, (VOID*) NULL}
};

static FRAME_INFO *_gStyleSubFrames = _gStyleStandardSubFrames ;

UINT8 gVerticalMainDivider = VERTICAL_MAIN_DIVIDER ;
UINT8 gHorizontalHelpDivider = HORIZONTAL_HELP_DIVIDER ;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleInit	
//
// Description:	Function to initialize style
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID	OverRideStyleInit( VOID )
{

	gLabelLeftMargin = STYLE_LABEL_LEFT_MARGIN ;
	gControlLeftMargin = STYLE_CONTROL_LEFT_MARGIN ;
	gControlLeftPad = STYLE_CONTROL_LEFT_PAD ;
	gControlRightAreaWidth 	= STYLE_CONTROL_RIGHT_AREA_WIDTH ;
		

#if SETUP_STYLE_FULL_SCREEN
	if ( gMaxCols == STYLE_FULL_MAX_COLS )
	{
		_gStyleSubFrames 	= _gStyleFullSubFrames;

		gVerticalMainDivider 	= FULL_VERTICAL_MAIN_DIVIDER ;
		gHorizontalHelpDivider 	= FULL_HORIZONTAL_HELP_DIVIDER ;

		gLabelLeftMargin 	= FULL_STYLE_LABEL_LEFT_MARGIN ;
		gControlLeftMargin 	= FULL_STYLE_CONTROL_LEFT_MARGIN ;
		gControlLeftPad 	= FULL_STYLE_CONTROL_LEFT_PAD ;
		gControlRightAreaWidth 	= FULL_STYLE_CONTROL_RIGHT_AREA_WIDTH ;
	}
#endif

	if(gLabelLeftMargin < 2)
		gLabelLeftMargin = 2 ;
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameIndexOf	
//
// Description:	Function to get frame index
//
// Input:		UINT32 frameType
//
// Output:		UINT32 index
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32	StyleFrameIndexOf( UINT32 frameType )
{
	UINT32 FrameCount ;
	UINT32 i;
	
	FrameCount = sizeof(_gStyleStandardSubFrames) / sizeof(FRAME_INFO);
	

	for ( i = 0; i < FrameCount; i++ )
	{
		if( _gStyleSubFrames[i].FrameType == frameType ){
			return i ;
			break ;
		}
	}
	
	return i ;
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetPageFrames	
//
// Description:	Function to number of frames
//
// Input:		UINT32 page
//
// Output:		UINT32 number of frames
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32	StyleGetPageFrames( UINT32 page )
{
	return sizeof(_gStyleStandardSubFrames) / sizeof(FRAME_INFO);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleDrawPageBorder	
//
// Description:	Function to draw page border
//
// Input:		UINT32 page
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OverRideStyleDrawPageBorder( UINT32 page )
{
	PAGE_DATA *Page ;
	FRAME_DATA *fTitle, *fMenu, *fHelptitle, *fMain;

	CHAR16 *line;
	UINT8 lineNumber;
	UINT8 start, end, col;
	UINT8 pbx,pby,pbw,pbh;
	UINT8 vertDivider = VERTICAL_MAIN_DIVIDER ;
	UINT8 horzDivider = HORIZONTAL_HELP_DIVIDER;

	Page = gApp->PageList[page];
	
	fTitle = Page->FrameList[StyleFrameIndexOf(TITLE_FRAME)];
	fHelptitle = Page->FrameList[StyleFrameIndexOf(HELPTITLE_FRAME)];
	fMenu = Page->FrameList[StyleFrameIndexOf(SUBTITLE_FRAME)];
	fMain = Page->FrameList[StyleFrameIndexOf(MAIN_FRAME)];//EIP-123006

	pbx = PAGEBORDER_X;
	pby = PAGEBORDER_Y;
	pbw = PAGEBORDER_W;
	pbh = PAGEBORDER_H;

	if ( gMaxCols == STYLE_FULL_MAX_COLS )
	{
		vertDivider = FULL_VERTICAL_MAIN_DIVIDER ;
		horzDivider = FULL_HORIZONTAL_HELP_DIVIDER;
		pbx = PAGEBORDER_FULL_X;
		pby = PAGEBORDER_FULL_Y;
		pbw = PAGEBORDER_FULL_W;
		pbh = PAGEBORDER_FULL_H;
	}
		

	line = EfiLibAllocateZeroPool( (gMaxCols + 1) * sizeof(CHAR16) );
	if ( line == NULL )
		return;

	ClearLinesWithoutFlush( fTitle->FrameData.Top, fTitle->FrameData.Height, fTitle->FrameData.BGColor | fTitle->FrameData.FGColor );
	ClearLinesWithoutFlush( fHelptitle->FrameData.Top, fHelptitle->FrameData.Height, fHelptitle->FrameData.BGColor | fHelptitle->FrameData.FGColor );
	ClearLinesWithoutFlush( fMenu->FrameData.Top, fMenu->FrameData.Height, fMenu->FrameData.BGColor | fMenu->FrameData.FGColor );

	//EIP-123006 Clearing gFlushBuffer with attribute(0) and chars(' ')
	MemSet( &(gFlushBuffer->Attribs[fMain->FrameData.Top*gMaxCols]), fMain->FrameData.Height*gMaxCols, 0 );
	MemFillUINT16Buffer( &(gFlushBuffer->Chars[fMain->FrameData.Top*gMaxCols]), fMain->FrameData.Height*gMaxCols, (UINT16)L' ' );

	ClearLinesWithoutFlush( pby, pbh, PAGE_BGCOLOR | PAGE_FGCOLOR );
	
	
	DrawWindow( pbx, pby, pbw, pbh, PAGE_BGCOLOR| PAGE_FGCOLOR, TRUE, FALSE );



	MemFillUINT16Buffer( &line[1], gMaxCols - 1, BOXDRAW_HORIZONTAL );

	line[0] = BOXDRAW_DOWN_HORIZONTAL;
	line[1] = L'\0';
	DrawString( vertDivider, pby, line );

	line[0] = BOXDRAW_UP_HORIZONTAL;
	DrawString( vertDivider, pby+pbh-1, line );
		
	// center divider
	line[0] = BOXDRAW_VERTICAL;

	col = vertDivider ;
	start = pby+1; 
	end = pby+pbh-1 ;

	for ( lineNumber = start; lineNumber < end ; lineNumber++ )
		DrawString( col, lineNumber, line );

	// Horizontal Help divider 
	MemFillUINT16Buffer( &line[1], gMaxCols - 1, BOXDRAW_HORIZONTAL );
	line[0] = BOXDRAW_VERTICAL;
	//line[1] = BOXDRAW_HORIZONTAL;
	line[gMaxCols - vertDivider-1] = L'\0';
	DrawString(col, horzDivider, line );

	FlushLines( 0, end-1 );

	gBS->FreePool( line );
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleGetFrameInitData	
//
// Description:	Function to get frame initialization data
//
// Input:		UINT32 page, UINT32 frame
//
// Output:		VOID* 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *OverRideStyleGetFrameInitData( UINT32 page, UINT32 frame )
{
	return &_gStyleSubFrames[frame];
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameAddTitle	
//
// Description:	Function to add frame title 
//
// Input:		FRAME_DATA *frame, UINT32 frameType, CONTROL_INFO * dummy
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleFrameAddTitle( FRAME_DATA *frame, UINT32 frameType,CONTROL_INFO * dummy )
{
	return EFI_UNSUPPORTED;
}

#endif /* SETUP_STYLE_EZPORT */

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleEscKey	
//
// Description:	Function to handle ESC Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID HandleEscKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
extern BOOLEAN gTseCacheUpdated;
VOID HandleEscKey( VOID *vapp, VOID  *hotkey, VOID *cookie )
{
	APPLICATION_DATA *app = (APPLICATION_DATA *)vapp;
	UINT16 pageClass = 0, pageSubclass = 0, pageFormID = 0;
	EFI_GUID ExitPageGuid;
	UINT8 	Sel = 0;
	CHAR16 	*Title = NULL;

	if(FormBrowserHandleValid())
	{
		if (gTseCacheUpdated)
		{
			Title = HiiGetString (gHiiHandle, STRING_TOKEN (STR_TSE_CACHE_CHANGE_WARNING));
			PostManagerDisplayMsgBox (L"Warning!!!", Title, MSGBOX_TYPE_OK, &Sel);
			MemFreePointer ((VOID **)&Title);
		}
		else
		{
			app->Quit = TRUE;
		}
	}

	else if ( gotoExitOnEscKey (&ExitPageGuid, &pageClass, &pageSubclass, &pageFormID) )//EIP-112628
	{
    	UINT32 i=0;
    	PAGE_INFO *pageInfo;

		for ( i = 0; i < gPages->PageCount; i++ )
		{
			pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[i]);
			if (
	         	( EfiCompareGuid(&ExitPageGuid,&(gPageIdInfo[pageInfo->PageIdIndex].PageGuid)) ) &&
					( pageClass == gPageIdInfo[pageInfo->PageIdIndex].PageClass ) 							&&
					( pageSubclass == gPageIdInfo[pageInfo->PageIdIndex].PageSubClass ) 					&&
					( pageFormID == pageInfo->PageFormID ) 
			   )
			{
				gApp->CurrentPage = i; // Page found go to exit page
	            gApp->CompleteRedraw = TRUE;
	            gApp->Fixed = FALSE;
				break;
			}
		}
		if(i >= gPages->PageCount) //Page not found exit application
			app->Quit = ExitApplication();
	}

	else
		app->Quit = ExitApplication();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleSaveExitKey	
//
// Description:	Function to handle Save and Exit Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID HandleSaveExitKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
VOID HandleSaveExitKey( VOID *vapp, VOID *hotkey, VOID *cookie )
{
	APPLICATION_DATA *app = (APPLICATION_DATA *)vapp;
	app->Quit = SaveAndExit();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandlePrevValuesKey	
//
// Description:	Function to handle Load Previous value Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID HandlePrevValuesKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
VOID HandlePrevValuesKey( VOID *vapp, VOID *hotkey, VOID *cookie )
{
	APPLICATION_DATA *app = (APPLICATION_DATA *)vapp;
	//TH0031+++>>>
	UINT8    *pSysPasswordType;
	EFI_GUID sysAccessGuid = SYSTEM_ACCESS_GUID;
	UINTN    size = 0;
	UINT32 PasswordInstalled = PasswordCheckInstalled();//TH0031A
	pSysPasswordType = VarGetNvramName( L"SystemAccess", &sysAccessGuid, NULL, &size );
//TH0031A	if((*pSysPasswordType == SYSTEM_PASSWORD_ADMIN) || (gPasswordType == AMI_PASSWORD_NONE)){
	if((*pSysPasswordType == SYSTEM_PASSWORD_ADMIN) || (PasswordInstalled == AMI_PASSWORD_NONE)){ //TH0031A
//TH0031+++<<<
	if ( app->CurrentPage != 0 )
		LoadPreviousValues( TRUE );
	}//TH0031
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleFailsafeKey	
//
// Description:	Function to handle Load Failsafe values Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID HandleFailsafeKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
VOID HandleFailsafeKey( VOID *vapp, VOID *hotkey, VOID *cookie )
{
	APPLICATION_DATA *app = (APPLICATION_DATA *)vapp;
	if ( app->CurrentPage != 0 )
		LoadFailsafeDefaults();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleOptimalKey	
//
// Description:	Function to handle Load Optimal values Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID HandleOptimalKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
VOID HandleOptimalKey( VOID *vapp, VOID *hotkey, VOID *cookie )
{
	APPLICATION_DATA *app = (APPLICATION_DATA *)vapp;
//TH0031+++>>>>
	UINT8    *pSysPasswordType;  
	EFI_GUID sysAccessGuid = SYSTEM_ACCESS_GUID;
	UINTN    size = 0;
	UINT32 PasswordInstalled = PasswordCheckInstalled();//TH0031A
		
	pSysPasswordType = VarGetNvramName( L"SystemAccess", &sysAccessGuid, NULL, &size );
	//TH0031A if((*pSysPasswordType == SYSTEM_PASSWORD_ADMIN) || (gPasswordType == AMI_PASSWORD_NONE)){
	if((*pSysPasswordType == SYSTEM_PASSWORD_ADMIN) || (PasswordInstalled == AMI_PASSWORD_NONE)){ //TH0031A
//TH0031+++<<<<
	if ( app->CurrentPage != 0 )
		LoadOptimalDefaults();
	} //TH0031
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleHelpKey	
//
// Description:	Function to handle Help Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID HandleHelpKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
VOID HandleHelpKey( VOID *vapp, VOID *hotkey, VOID *cookie )
{
	APPLICATION_DATA *app = (APPLICATION_DATA *)vapp;
	if ( app->CurrentPage != 0 )
		ShowHelpMessageBox();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandlePrnScrnKey	
//
// Description:	Function to handle print screen Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID HandlePrnScrnKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
VOID HandlePrnScrnKey( VOID  *app, VOID *hotkey, VOID *cookie )
{
	TseHotkeyPrintScreenSupport();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------------------------------------------------------
// Procedure:	SetupShowDebugScreen	
//
// Description:	Function to handle debug infrastructure Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//-----------------------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetupShowDebugScreenWrapper (VOID *app, VOID *hotkey, VOID *cookie );
VOID SetupShowDebugScreen( VOID  *app, VOID *hotkey, VOID *cookie )
{
	SetupShowDebugScreenWrapper (app, hotkey, cookie);
}

//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
//EIP:47086 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MainFrameHandlewithMouse	
//
// Description:	Function to handle Main Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID MainFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
VOID MainFrameHandlewithMouse( VOID *vapp, VOID *hotclick, VOID *cookie )
{
	APPLICATION_DATA *app = (APPLICATION_DATA *)vapp;
	NumericSoftKbdExit();
	if(app->Action->Input.Data.MouseInfo.ButtonStatus == TSEMOUSE_RIGHT_CLICK)
		app->Quit = ExitApplication();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HelpFrameHandlewithMouse	
//
// Description:	Function to handle Help Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID HelpFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
VOID HelpFrameHandlewithMouse( VOID *app, VOID *hotclick, VOID *cookie )
{
	NumericSoftKbdExit();
	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NavFrameHandlewithMouse	
//
// Description:	Function to handle Navigation Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//VOID NavFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
VOID NavFrameHandlewithMouse( VOID *vapp, VOID *vhotclick, VOID *cookie )
{
	APPLICATION_DATA *app = (APPLICATION_DATA *) vapp;
	HOTCLICK_DATA *hotclick = ( HOTCLICK_DATA *)vhotclick;
	UINT32 Action;

// EIP :62098 -Handling mouse hot click operations
	NumericSoftKbdExit();
	Action = MapControlMouseActionHook(&app->Action->Input.Data.MouseInfo);
//EIP 88811 : When pop-up window is invoked in setup and Click on ESC icon or ESC/Right Click, it will respond as two times ESC is clicked
	if(( ControlActionChoose == Action )||( ControlActionSelect == Action ))//EIP 103449  : In Setup click\Touch from navigation window, option are not displayed properly
	{
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 4)
			if ( app->CurrentPage != 0 )
			{
				ShowHelpMessageBox();
				return;
			}
		
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 5)
			if ( app->CurrentPage != 0 )
			{	
				LoadPreviousValues( TRUE );
				return;
			}
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 6)
			if ( app->CurrentPage != 0 )
			{	
				LoadOptimalDefaults();
				return;
			}
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 7)
			{
				app->Quit = SaveAndExit();
				return;
			}
		
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 8)		
			HotclickESCaction();	
		//app->Quit = ExitApplication();	
	
	}	
}
//EIP:47086 END

//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2011, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                     Phone: (770)-246-8600                   **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
