//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2014, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/minisetup.c $
//
// $Author: Rajashakerg $
//
// $Revision: 9 $
//
// $Date: 4/27/12 5:16a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		MINISETUP.C
//
// Description:	This file contains code for entrypoint and setup loop
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#if TSE_BUILD_AS_APPLICATION
#include "AMITSEElinks.h"
#endif

#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION
// from Resources.c
#if TSE_USE_EDK_LIBRARY
EFI_STATUS LoadStrings(
	EFI_HANDLE ImageHandle, /*EFI_HII_HANDLE*/VOID* *pHiiHandle
);
#endif
#endif

#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION || TSE_FOR_64BIT
EFI_STATUS ReadImageResource(
	EFI_HANDLE ImageHandle, EFI_GUID *pGuid, 
	VOID **ppData, UINTN *pDataSize
);
#endif

//Internal function definitions
#if APTIO_4_00 != 1 && SETUP_USE_GUIDED_SECTION !=1
EFI_STATUS InitMiniSetupStrings( VOID );
#endif

EFI_DRIVER_ENTRY_POINT (MiniSetupApplication)

/////////////////////////////////////////////////////////
//	FUNCTION DECLARATION
////////////////////////////////////////////////////////
VOID InitGlobalPointers( VOID );
VOID UpdategScreenParams (VOID);
VOID StopClickEvent(VOID); //EIP-149734 Hiding softkbd in BBS menu.
AMI_SET_VERSION(TSE_MAJOR,TSE_MINOR,TSE_BUILD,TSE);
VOID        InvalidateStatusInBgrtWrapper (VOID);

//EIP 162981 Providing defaults through sdl tokens
BOOLEAN 	TseDefaultSetupPasswordSupported(VOID);
EFI_STATUS 	SetDefaultPassword (VOID);

#define	TSE_FIRST_BOOT_GUID	\
	{ 0xc5912ed9, 0x83c2, 0x4bff, 0x99, 0x36, 0x23, 0x1f, 0xeb, 0x85, 0xf3, 0xe8 }

#if TSE_BUILD_AS_APPLICATION
EFI_STATUS TSELoadStrings(
	EFI_HANDLE ImageHandle, EFI_HII_HANDLE *pHiiHandle
);
VOID GetArgumentsFromImage(EFI_HANDLE ImageHandle, CHAR16 ***pArgv, UINTN *pArgc);
UINTN 			gArgCount = 0;
CHAR16		**gArgv;

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	GetArgumentsFromImage()
//
// Description:	Returns CommandLine Arguments.
//
// Parameter: ImageHandle
//
// Return Value: Fills the Argv and Argc pointers
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetArgumentsFromImage(EFI_HANDLE ImageHandle, CHAR16 ***pArgv, UINTN *pArgc)
{
    EFI_STATUS	status;
    EFI_LOADED_IMAGE	*image;
    EFI_GUID	loadedImageProtocol = LOADED_IMAGE_PROTOCOL;
    CHAR16	*cmdLine;
    UINTN	argc = 0, count;

    status = gBS->HandleProtocol( ImageHandle, &loadedImageProtocol, &image );

    if ( ! EFI_ERROR(status) )
    {
		UINTN	i;

		if ( image->LoadOptions == NULL )
		{
		    *pArgc = 0;
		    return;
		}

		cmdLine = (CHAR16 *)image->LoadOptions;
		count = StrLen (cmdLine);
		//count = image->LoadOptionsSize / sizeof(CHAR16);
		for ( i = 0; i < count; i++ )
		{
		    if ( cmdLine[i] == L' ' )
		    {
				cmdLine[i] = L'\0';
				argc++;
		    }
		}

		*pArgv = EfiLibAllocatePool  ((argc + 1) * sizeof (CHAR16 *));
		if ( *pArgv != NULL )
		{
		    for ( i = 0; i < argc; i++ )
		    {
				(*pArgv)[i] = cmdLine;
				cmdLine += StrLen (cmdLine) + 1;
		    }

		    (*pArgv)[i] = NULL;
		}
    }

    *pArgc = argc;

//	FreePool( cmdLine );
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: LoadStrings
//
// Description:
//  EFI_STATUS LoadStrings(EFI_HANDLE ImageHandle,
// EFI_HII_HANDLE *pHiiHandle) - loads HII string packages associated with
// the specified image and publishes them to the HII database
//
// Input:
//  EFI_HANDLE ImageHandle - Image Handle
//  EFI_HII_HANDLE *pHiiHandle - HII package list handle
//
// Output:
//   EFI_STATUS
//
//<AMI_PHDR_END>
//*************************************************************************
#define EFI_HII_PACKAGE_LIST_PROTOCOL_GUID \
  { 0x6a1ee763, 0xd47a, 0x43b4, {0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc}}
static EFI_GUID gEfiHiiPackageListProtocolGuid = EFI_HII_PACKAGE_LIST_PROTOCOL_GUID;

EFI_STATUS TSELoadStrings(
	EFI_HANDLE ImageHandle, EFI_HII_HANDLE *pHiiHandle
)
{
    EFI_STATUS                      Status;
    EFI_HII_PACKAGE_LIST_HEADER     *PackageList;
    EFI_HII_DATABASE_PROTOCOL       *HiiDatabase;

    //
    // Retrieve HII package list from ImageHandle
    //
    Status = pBS->OpenProtocol (
        ImageHandle,
        &gEfiHiiPackageListProtocolGuid,
        (VOID **) &PackageList,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
    if (EFI_ERROR (Status)) {
        return Status;
    }

    Status = pBS->LocateProtocol (
        &gEfiHiiDatabaseProtocolGuid,
        NULL,
        &HiiDatabase
    );
    if (EFI_ERROR (Status)) {
        return Status;
    }

    //
    // Publish HII package list to HII Database.
    //
    Status = HiiDatabase->NewPackageList (
        HiiDatabase,
        PackageList,
        ImageHandle,
        pHiiHandle
    );

	return Status;
}
#endif   //For TSE_BUILD_AS_APPLICATION

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MiniSetupApplication
//
// Description:	This function is the entry point for TSE. It loads
//              resources like strings and setup-data. It registers
//              notification for console protocols. It Installs TSE
//              protocols.
//
// Input:		EFI_HANDLE ImageHandle
//              EFI_SYSTEM_TABLE *SystemTable
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MiniSetupApplication (
		EFI_HANDLE ImageHandle,
		EFI_SYSTEM_TABLE *SystemTable )
{
	EFI_STATUS	Status;
    UINTN 		OptionSize = 0;
    void 		*FirstBoot = NULL;
    EFI_GUID	TseFirstBootGuid = TSE_FIRST_BOOT_GUID;

	gImageHandle = ImageHandle;

	EfiInitializeDriverLib ( ImageHandle, SystemTable );

	RUNTIME_DEBUG( L"entry" );

#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION
#if TSE_USE_EDK_LIBRARY
	LoadStrings(ImageHandle,&gHiiHandle);
#else
#if TSE_BUILD_AS_APPLICATION	
	TSELoadStrings (ImageHandle,(EFI_HII_HANDLE*)&gHiiHandle);
#else
	LoadStrings (ImageHandle,(EFI_HII_HANDLE*)&gHiiHandle);
#endif	
#endif
#else
#ifdef USE_DEPRICATED_INTERFACE
	// Read in the strings from the GUIDed section
	Status = LoadStringsDriverLib( ImageHandle, &STRING_ARRAY_NAME );
	if ( EFI_ERROR( Status ) )
	{
		return Status;
	}
#endif

	Status = InitMiniSetupStrings();
	if ( EFI_ERROR( Status ) )
	{
		return Status;
	}
#endif

	Status = HiiInitializeProtocol();
	if ( EFI_ERROR ( Status ) )
		return Status;

	// initialize screen buffer
	RUNTIME_DEBUG( L"screen" );
	InitializeScreenBuffer( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );

	RUNTIME_DEBUG( L"guid" );

	Status = InitApplicationData(ImageHandle);
	if ( EFI_ERROR( Status ) )
	{
		return MiniSetupExit( Status );
	}

	RUNTIME_DEBUG( L"globals" );
	InitGlobalPointers();
    UpdategScreenParams ();

	Status = VarLoadVariables( (VOID **)&gVariableList, NULL );
	if ( EFI_ERROR( Status ) )
	{
		return Status;
	}
#if TSE_BUILD_AS_APPLICATION
	GetArgumentsFromImage (ImageHandle, &gArgv, &gArgCount);
#endif	
    MinisetupDriverEntryHookHook();

	gPostStatus = TSE_POST_STATUS_BEFORE_POST_SCREEN;

#ifndef STANDALONE_APPLICATION
	// Install our handshake protocol
	InstallProtocol();

	// Register any notification 'callbacks' that we need
#if !TSE_FOR_EDKII_SUPPORT	
	Status = RegisterNotification();
	if ( EFI_ERROR( Status ) )
		UninstallProtocol();
#endif	
#else
	PostManagerHandshake();
#endif // STANDALONE_APPLICATION

    if (TseDefaultSetupPasswordSupported ())	//EIP 162981 Providing defaults through sdl tokens
    {
    	FirstBoot = (BOOT_OPTION *)VarGetNvramName (L"TseFirstBootFlag", &TseFirstBootGuid, NULL, &OptionSize);
    	if (NULL == FirstBoot)
    	{
    		SetDefaultPassword (); //Get default password, if any present in SDL, and set default pass to NVRAM EIP 162981
    		VarSetNvramName( L"TseFirstBootFlag", &TseFirstBootGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, &OptionSize, sizeof (OptionSize) );
    	}
    }
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MiniSetupExit
//
// Description:	This function is responsible for releasing the memory
//              allocated during MinisetuEntry(). It destroys the
//              application hierarchy; clears the memory used for
//              variables; clears the memory used for fixup of
//              setup-data.
//
// Input:		EFI_STATUS Status: Guideline status for MiniSetupExit
//              to return with.
//
// Output:		Return Status based on input status and errors that
//              occurred in library functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MiniSetupExit( EFI_STATUS Status )
{
	MiniSetupUIExit();

	if(gST->ConOut!=NULL)
	{
		gST->ConOut->Reset( gST->ConOut, FALSE );
		gST->ConOut->ClearScreen( gST->ConOut);
		gST->ConOut->EnableCursor( gST->ConOut, TRUE );
	}

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoPopup
//
// Description:	This function runs the loop for Pop up boot menu.
//              This function is responsible for creating the list
//              box control. It also gathers actions and passes them
//              to list box control and initiates draw sequence.
//
// Input:		BOOT_FLOW *BootFlow: Ptr to BOOT_FLOW responsible for
//              the call.
//
// Output:		Return Status based on errors that occurred in
//              library functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DoPopup(BOOT_FLOW *BootFlow)
{
	EFI_STATUS Status = EFI_SUCCESS;
//TH0028>>>
	UINT8    *pSysPasswordType;
	EFI_GUID sysAccessGuid = SYSTEM_ACCESS_GUID;
	UINTN    size = 0;

	pSysPasswordType = VarGetNvramName( L"SystemAccess", &sysAccessGuid, NULL, &size );
	if((*pSysPasswordType == SYSTEM_PASSWORD_ADMIN) || (gPasswordType == AMI_PASSWORD_NONE)){
//TH0028<<<
  	gPostStatus = TSE_POST_STATUS_IN_BBS_POPUP;
  
  	DoBbsPopupInit() ; 	//minisetupext.c
  
  	if (gClickTimer) //EIP-149734 Stopping ClickEvent timer, if gClickTimer event is not stopped, before drawing BBS menu to avoid drawing softkbd if any mouse action happens during BBS menu
  		StopClickEvent();
  
  	//TSEStringReadLoopEntryHook();//EIP 88454/149734 : Initializing the Softkbd for BBS popup menu 
  	DrawPopupMenuHook() ;	//HookAnchor.c -> DrawBootOnlyBbsPopupMenu (minisetupext.c)
  	BbsBootHook() ;		//HookAnchor.c -> BbsBoot (minisetupext.c)
  }	//TH0028	
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MainSetupLoopInit
//
// Description:	Main function that initializes the setup Loops.
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MainSetupLoopInit(VOID)
{
#ifndef STANDALONE_APPLICATION
//	EFI_CONSOLE_CONTROL_SCREEN_MODE ScreenMode;
#endif
	EFI_GUID AmitseSetupEnterGuid = AMITSE_SETUP_ENTER_GUID;
	static int Initdone =0;

	if(Initdone)
	{
		EfiLibNamedEventSignal ( &AmitseSetupEnterGuid );
		return;
	}
	Initdone = 1;
	
	InvalidateStatusInBgrtWrapper ();					//Anyway entering into setup/bbs popup so invalidating

/*	
#ifndef STANDALONE_APPLICATION
	if ( gConsoleControl != NULL )
	{
		gConsoleControl->GetMode(gConsoleControl, &ScreenMode, NULL, NULL);
		if(EfiConsoleControlScreenGraphics == ScreenMode)
		{
			gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenText );
			InvalidateStatusInBgrtWrapper ();					//EIP93524. Since mode changed invalidating status field in BGRT table. Usefull for boot from BBS Pop up.
		}
	}
#endif
*/
	MouseInit();//EIP 82804 : Initiatializing the Mouse before prompting password
	ProcessEnterSetupHook();
	
	TSEUnlockHDD();			///Modified as a hook 

	EfiLibNamedEventSignal ( &AmitseSetupEnterGuid );
	// Report the Status code DXE_SETUP_START
	EfiLibReportStatusCode(EFI_PROGRESS_CODE, DXE_SETUP_START,0,NULL,NULL);
}

//EIP 162981 starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		GetDefaultPassword
//
// Description:		Getting default password from SDL token based on USER/ADMIN token
//
// Input:			UINT32, AMITSESETUP*
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetDefaultPasswordFromTokens (UINT32 PasswordType);
EFI_STATUS GetDefaultPassword (UINT32 PasswordInstalled, void **DefaultPassword)
{
	CHAR16 *adminPwd = NULL, *usrPwd = NULL;
	EFI_STATUS Status = EFI_NOT_FOUND;
	CHAR16 *tmpPasswd = NULL;
	
	if ((PasswordInstalled == AMI_PASSWORD_ADMIN) || (AMI_PASSWORD_NONE == PasswordInstalled))
	{
		usrPwd = GetDefaultPasswordFromTokens (AMI_PASSWORD_USER);
		if ((NULL != usrPwd) && (EfiStrCmp (usrPwd, L"\"\"")))
		{
			tmpPasswd =  (CHAR16 *)EfiLibAllocateZeroPool (sizeof (AMITSESETUP));
			if (NULL == tmpPasswd)
			{
				return EFI_OUT_OF_RESOURCES;
			}
			EfiStrCpy (tmpPasswd, usrPwd);
			PasswordEncodeHook (tmpPasswd, TsePasswordLength*sizeof(CHAR16));
			MemCopy (*DefaultPassword, tmpPasswd, TsePasswordLength*sizeof(CHAR16));
			MemFreePointer ((VOID **) &tmpPasswd);
			Status = EFI_SUCCESS;
		}
	}

	if ((PasswordInstalled == AMI_PASSWORD_USER) || (AMI_PASSWORD_NONE == PasswordInstalled))
	{
		adminPwd = GetDefaultPasswordFromTokens (AMI_PASSWORD_ADMIN);
		if ((NULL != adminPwd) && (EfiStrCmp (adminPwd, L"\"\"")))
		{
			tmpPasswd = (CHAR16 *) EfiLibAllocateZeroPool (sizeof (AMITSESETUP));
			if (NULL == tmpPasswd)
			{
				return EFI_OUT_OF_RESOURCES;
			}
			EfiStrCpy (tmpPasswd, adminPwd);
			PasswordEncodeHook (tmpPasswd, TsePasswordLength*sizeof(CHAR16));
			MemCopy ((CHAR16*)(*DefaultPassword) + TsePasswordLength, tmpPasswd, TsePasswordLength*sizeof(CHAR16));
			MemFreePointer ((VOID **) &tmpPasswd);			
			Status = EFI_SUCCESS;
		}
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		SetDefaultPassword
//
// Description:		Function to set defaults password in NVRAM, if any present in SDL
//
// Input:			void
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   TseRtAccessSupport (VOID);
EFI_STATUS SetDefaultPassword (VOID)
{
	UINTN 		size = 0;
	UINT32		Installed = AMI_PASSWORD_NONE;
	void 		*DefaultPassword = NULL;
	UINT32 		PasswordInstalled;
	EFI_STATUS  Status = EFI_SUCCESS;
	AMITSESETUP *pSetupVariable = (AMITSESETUP *)NULL;
    EFI_GUID 	amitsesetupGuid = AMITSESETUP_GUID;

	pSetupVariable = HelperGetVariable( VARIABLE_ID_AMITSESETUP, (CHAR16 *)NULL, (EFI_GUID *)NULL, NULL, &size );

	if(size < sizeof(AMITSESETUP))
	{
		pSetupVariable = (AMITSESETUP *) EfiLibAllocateZeroPool(sizeof(AMITSESETUP));
		if(gVariableList && (gVariableList[VARIABLE_ID_AMITSESETUP].Buffer))
			MemCopy( pSetupVariable, gVariableList[VARIABLE_ID_AMITSESETUP].Buffer, gVariableList[VARIABLE_ID_AMITSESETUP].Size );
      if (TseRtAccessSupport ())
      {
   		VarSetNvramName( L"AMITSESetup", &amitsesetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS, pSetupVariable, sizeof (AMITSESETUP));
      }
      else
      {
         VarSetNvramName( L"AMITSESetup", &amitsesetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, pSetupVariable, sizeof (AMITSESETUP));
      }  
//		VarSetNvram( VARIABLE_ID_AMITSESETUP, pSetupVariable, sizeof(AMITSESETUP));
	}
  	PasswordInstalled = PasswordCheckInstalled();
	
	if (AMI_PASSWORD_ANY == PasswordInstalled)
	{
		return EFI_ALREADY_STARTED;
	}
	
	Status = GetDefaultPassword (PasswordInstalled, &pSetupVariable);
	
	if (!EFI_ERROR (Status))
	{
      if (TseRtAccessSupport ())
      {
		   VarSetNvramName( L"AMITSESetup", &amitsesetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS, pSetupVariable, sizeof (AMITSESETUP));
      }
      else
      {
         VarSetNvramName( L"AMITSESetup", &amitsesetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, pSetupVariable, sizeof (AMITSESETUP));
      }
//		VarSetNvram( VARIABLE_ID_AMITSESETUP, pSetupVariable, sizeof(AMITSESETUP));
//		VarUpdateDefaults(VARIABLE_ID_AMITSESETUP);
	}
	return EFI_SUCCESS;
}
//EIP 162981 ends

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
