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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/callback.c $
//
// $Author: Rajashakerg $
//
// $Revision: 22 $
//
// $Date: 9/17/12 6:20a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		callback.c
//
// Description:	This file contains code to handle callbacks
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

ACTION_DATA *gMsgBoxAction;
//ZYY006008- static EFI_GUID gSetupGuid = SETUP_GUID;//CDL002042++

UINTN _CallbackGetValue( MSGBOX_DATA *msgbox );
VOID _CallbackMsgbox( VOID *container, VOID *object, VOID *cookie );
VOID _LoadDefaults( NVRAM_VARIABLE *defaults, UINTN data );
BOOLEAN _SaveValues( UINTN data );
BOOLEAN LoadDefaultsFromDefaultBuffer( VOID );

extern UINTN gPreviousMsgBox;
extern UINTN gFailsafeMsgBox;
extern UINTN gOptimalMsgBox;
extern UINTN gSaveMsgBox;
extern UINTN gSaveExitMsgBox;
extern UINTN gExitMsgBox;
extern UINTN gSaveResetMsgBox;
extern UINTN gResetMsgBox;
extern UINTN gHelpMsgBox;
extern UINTN gSaveUserMsgBox;
extern UINTN gLoadUserMsgBox;
extern BOOLEAN gBrowserCallbackEnabled;

extern BOOLEAN gTseCacheUpdated;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadPreviousValues
//
// Description:	Callback function for LoadPreviousValue.
//
// Input:		Bool ShowMsgBox.
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadPreviousValues( BOOLEAN showMsgBox )
{
	UINT8 result = MSGBOX_YES;
	UINT16 CurrentBootOption=0;

//- Fix for Screen corruption while editing Date/edit controls.
	FRAME_DATA *MainFrame=NULL;
//-

	if ( showMsgBox )
		result = CallbackShowMessageBox( (UINTN)gPreviousMsgBox, MSGBOX_TYPE_YESNO );

	if ( result == MSGBOX_YES )
	{
		if(gCurrLegacyBootData)
		{
			UINT16 CurLegBootDataValid = 0;
			UINT32 i;

			// Check is gCurrLegacyBootData valid one
		    for (i = 0; i < gBootOptionCount; i++ )
		    {
		        if ( &gBootData[i] == gCurrLegacyBootData )
		            CurLegBootDataValid = 1;
		    }
			// If valid
			if(CurLegBootDataValid)
				CurrentBootOption = gCurrLegacyBootData->Option;
			else
				gCurrLegacyBootData = NULL;
		}

		CleanTempNvramVariableList(); //EIP 76381 : Reset to read the variable from NVRAM
		VarLoadVariables( (VOID **)&gVariableList, NULL );

		// special provisions needed for language
		//VarSetValue( VARIABLE_ID_LANGUAGE, 0, 3, gPrevLanguage );
		VarSetNvram ( VARIABLE_ID_LANGUAGE, gPrevLanguage,gPrevLangSize );

		///Hook to Load previous saved values 
		LoadedPreviousValuesHook();

		PasswordCommitChanges( FALSE );

		TseDiscardAddDelBootOptions();
		TseDiscardAddDelDriverOptions();			//EIP70421 & 70422 Support for driver order
		// reinit the gCurrLegacyBootData
		//if(gCurrLegacyBootData)
		//{
			gCurrLegacyBootData = BootGetBootData(CurrentBootOption);
			if(gCurrLegacyBootData) //EIP-127017 Avoid crashing when press F3 to load previous values
				VarSetValue(VARIABLE_ID_LEGACY_GROUP_INFO, 0, sizeof(UINT16), &(gCurrLegacyBootData->LegacyDevCount));
		//}

		if ( ! gVariableChanged )
			gResetRequired = FALSE;

		UEFICallSetupFormCallBack(AMI_CALLBACK_RETRIEVE);//EIP-53480: Calling the Wraper function with action AMI_CALLBACK_RETRIEVE

		//EIP-126057
		if(gApp!=NULL)
		{
	        //Recreate the special controls to reflect changes
	        gApp->CompleteRedraw = TRUE;

	//- Fix for Screen corruption while editing Date/edit controls.
	        MainFrame = gApp->PageList[gApp->CurrentPage]->FrameList[StyleFrameIndexOf(MAIN_FRAME)];
	        if(MainFrame->ControlCount)
	        if(MainFrame->CurrentControl != FRAME_NONE_FOCUSED)
	            if(MainFrame->ControlList[MainFrame->CurrentControl]->ControlActive == TRUE)
	                MainFrame->ControlList[MainFrame->CurrentControl]->ControlActive = FALSE;
	// -    
		}
		gTseCacheUpdated = FALSE;
	}
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadOptimalDefaults
//
// Description:	Loads the optimal defaults.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadOptimalDefaults( VOID )
{
	///Load optimal defaults modified as a hook
	LoadSetupDefaultsHook( gOptimalDefaults, (UINTN)gOptimalMsgBox );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadFailsafeDefaults
//
// Description:	Loads the failsafe defaults.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadFailsafeDefaults( VOID )
{
	///Load Failsafe defaults modified as a hook
	LoadSetupDefaultsHook( gFailsafeDefaults, (UINTN)gFailsafeMsgBox );
}

BOOLEAN TSEDonotLoadPasswordOnDefaults(VOID);//EIP 93881 & 93873 : Save pwd to nvram and not loading empty pwd on loading defaults.

//EIP 105167 : START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_LoadDefaults
//
// Description:	Loads the defaults with optimal or Failsafe data.
//
// Input:		Bool ShowMsgBox.
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CsmRearrangeBBSOrder (VOID *nvPtr, VOID *DefaultBuffer);
UINT16 EvaluateControlDefault (CONTROL_INFO *CtrlInfo, UINT64 *Defaults);
VOID _LoadDefaults( NVRAM_VARIABLE *defaults, UINTN data )
{
	UINT32 i;
	UINT16 CurrentBootOption=0;
	EFI_STATUS Status;
//- Fix for Screen corruption while editing Date/edit controls.
	FRAME_DATA *MainFrame;
//-

	if ( data == (UINTN)NULL ?1:(CallbackShowMessageBox( data, MSGBOX_TYPE_YESNO ) == MSGBOX_YES) ) //EIP:57547 To avoid draw MessageBox when data is passed as NULL to load Defaults silently
	{
		UINT32	page, control;
		gBrowserCallbackEnabled = TRUE;
		if(gCurrLegacyBootData)
		{
			UINT16 CurLegBootDataValid = 0;

			// Check is gCurrLegacyBootData valid one
		    for ( i = 0; i < gBootOptionCount; i++ )
		    {
		        if ( &gBootData[i] == gCurrLegacyBootData )
		            CurLegBootDataValid = 1;
		    }
			// If valid
			if(CurLegBootDataValid)
				CurrentBootOption = gCurrLegacyBootData->Option;
			else
				gCurrLegacyBootData = NULL;
		}

	

		for ( page = 0; page < gPages->PageCount; page++ )
		{
			PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[page]);
			UINTN Action;
		
			if ( (NULL != pageInfo) && (0 == pageInfo->PageHandle) )
				continue;
		
			for ( control= 0; control < pageInfo->PageControls.ControlCount; control++ )
			{
				CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);
				
				if( NULL == controlInfo || NULL == controlInfo->ControlPtr)		//Suppressing inconsistent and nosubmit controls so added check for ControlPtr
					continue;	
				
				Status = EFI_SUCCESS;
				if (UefiIsInteractive (controlInfo))
				{
					Action = UefiGetActionWapper (AMI_CALLBACK_FORM_DEFAULT_STANDARD);
					Status = CallFormCallBack (controlInfo, UefiGetControlKey (controlInfo), FALSE, Action);
				}
				if (
						(!UefiIsInteractive (controlInfo) || (EFI_UNSUPPORTED == Status)) &&
						(!controlInfo->ControlFlags.ControlEvaluateDefault) &&
						(defaults[controlInfo->ControlVariable].Size > 0)
						)
				{
					UINT32 offset = 0, size = 0;
					
					if ((!LoadDefaultsFromDefaultBuffer ()) && (controlInfo->ControlDataWidth ==  0))		//If defaults not present for a control but if the offset present
					{																						//in the variable which has atleast default then
						continue;																			//try to load it if TSE_LOAD_DEFAULTS_FROM_DEFAULTS_BUFFER
					}																						//is enabled.	
					if (CONTROL_TYPE_ORDERED_LIST != controlInfo->ControlType)
					{
						size = UefiGetWidth(controlInfo->ControlPtr);
					}
					else
					{
						size = controlInfo->ControlDataWidth;
					}
					if (0 == size)			//For text and submenu skip loading defaults
					{
						continue;
					}
					offset = UefiGetQuestionOffset(controlInfo->ControlPtr);
					if ((0xFFFF == offset) || ((offset + size) > defaults [controlInfo->ControlVariable].Size))		//QF_DATE_STORAGE_TIME and QF_TIME_STORAGE_TIME offsets will be 0xFFFF so we need to skip it
					{
						continue;
					}
					if ( ( controlInfo->ControlVariable == VARIABLE_ID_LANGUAGE) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_DEL_BOOT_OPTION) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_ADD_BOOT_OPTION) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_USER_DEFAULTS) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_IDE_SECURITY) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_LEGACY_DEV_INFO) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_LEGACY_GROUP_INFO) ||
					 ( controlInfo->ControlVariable == VARIABLE_ID_ADD_DRIVER_OPTION) ||			//EIP70421 & 70422 Support for driver order
					 (controlInfo->ControlVariable == VARIABLE_ID_DEL_DRIVER_OPTION) ||
					( (TSEDonotLoadPasswordOnDefaults()) && (controlInfo->ControlVariable == VARIABLE_ID_AMITSESETUP) ) ) //EIP 93881 & 93873 : Save pwd to nvram and not loading empty pwd on loading defaults.
						continue;
					else if(	((defaults[controlInfo->ControlVariable].Buffer != NULL) && (defaults[controlInfo->ControlVariable].Size))
								&&((VARIABLE_ID_BOOT_ORDER == controlInfo->ControlVariable) || (VARIABLE_ID_DRIVER_ORDER == controlInfo->ControlVariable))
							)
					{
						MemCopy (gVariableList[controlInfo->ControlVariable].Buffer, defaults[controlInfo->ControlVariable].Buffer, defaults[controlInfo->ControlVariable].Size);
						gVariableList[controlInfo->ControlVariable].Size = defaults[controlInfo->ControlVariable].Size;
					}
					else if (VARIABLE_ID_BBS_ORDER == controlInfo->ControlVariable)      //EIP109382: Since boot order loads first legacydevorder corrupted so restructuring with gbootdata 
					{
						if((defaults[controlInfo->ControlVariable].Buffer != NULL) && (defaults[controlInfo->ControlVariable].Size))
							CsmRearrangeBBSOrder (&(gVariableList [controlInfo->ControlVariable]), &(defaults[controlInfo->ControlVariable]));
					}
					else
					{
						if((defaults[controlInfo->ControlVariable].Buffer != NULL) && (defaults[controlInfo->ControlVariable].Size))
							MemCopy (gVariableList [controlInfo->ControlVariable].Buffer + offset, defaults[controlInfo->ControlVariable].Buffer + offset, size);
					}
				}
				if(controlInfo->ControlFlags.ControlEvaluateDefault)
				{
					UINT64 Defaults = 0 ;
					UINT16 size = 0;
					UINT32 offset = 0;
					
					offset = UefiGetQuestionOffset(controlInfo->ControlPtr);

					//EIP: 57402 Evaluating the Control Default
					size = EvaluateControlDefault(controlInfo,&Defaults);
					 VarSetValue(controlInfo->ControlVariable, offset, size, &Defaults );
					// EIP: 57402 Setiing the Evaluated value to the gOptimalDefaults
					//if(DefaultId == EFI_HII_DEFAULT_CLASS_MANUFACTURING)
						_VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, controlInfo->ControlVariable, offset, size, &Defaults );
				}
			}
		}
		
		gBrowserCallbackEnabled = FALSE;
		PasswordCommitChanges( FALSE );

		TseDiscardAddDelBootOptions();
		TseDiscardAddDelDriverOptions();							//EIP70421 & 70422 Support for driver order

		// reinit the gCurrLegacyBootData
//		if(gCurrLegacyBootData)                 //(EIP61172) If defaults is loaded, boot order defaults is not loading after a restart. So commented.
//		{                                       //(EIP61172)
			gCurrLegacyBootData = BootGetBootData(CurrentBootOption);
			if(gCurrLegacyBootData) //EIP-127017 Avoid crashing when press F3 to load defaults
				VarSetValue(VARIABLE_ID_LEGACY_GROUP_INFO, 0, sizeof(UINT16), &(gCurrLegacyBootData->LegacyDevCount));
//		}                                       //(EIP61172)

		gResetRequired = TRUE;

        LoadedConfigDefaultsHook();
        
        //EIP-126057
        if(gApp!=NULL)
        {
            //Recreate the special controls to reflect changes
              gApp->CompleteRedraw = TRUE;

      //- Fix for Screen corruption while editing Date/edit controls.
              MainFrame = gApp->PageList[gApp->CurrentPage]->FrameList[StyleFrameIndexOf(MAIN_FRAME)];

          //EIP-25987: Load Optimized Defaults(F3)hangs in a empty page || Fix: Check whether the frame has any controls before doing any operation on a control. 
          if(MainFrame->ControlCount)
              if(MainFrame->CurrentControl != FRAME_NONE_FOCUSED)
                  if(MainFrame->ControlList[MainFrame->CurrentControl]->ControlActive == TRUE)
                      MainFrame->ControlList[MainFrame->CurrentControl]->ControlActive = FALSE;
      // -      
        }
	}
}
//EIP 105167 : END
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveAndExit
//
// Description:	Function to save and exit
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SaveAndExit( VOID )
{
	if ( _SaveValues( (UINTN)gSaveExitMsgBox ) )
	{
		gVariableChanged = TRUE;
		return TRUE;
	}

	return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveWithoutExit
//
// Description:	Function to save without exit
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveWithoutExit( VOID )
{
	if ( _SaveValues( (UINTN)gSaveMsgBox ) )
		gVariableChanged = TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveAndReset
//
// Description:	Function to save and reset
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SaveAndReset( VOID )
{
	if ( _SaveValues( (UINTN)gSaveResetMsgBox ) )
	{
		gVariableChanged = TRUE;
        gResetRequired = TRUE;
		return TRUE;
	}

	return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ResetSys
//
// Description:	Function to reset
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ResetSys( VOID )
{
	if ( CallbackShowMessageBox( (UINTN)gResetMsgBox, MSGBOX_TYPE_YESNO ) == MSGBOX_YES )
	{
        	gResetRequired = TRUE; // force a reset 
		gVariableChanged = FALSE;
		return TRUE;
	}

	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SaveValues
//
// Description:	Function to save the given values
//
// Input:	UINTN data
//
// Output:	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _SaveValues( UINTN data )
{
	UINT32 i;
	NVRAM_VARIABLE *nvPtr;
	EFI_GUID AmitseNvramUpdateGuid = AMITSE_NVRAM_UPDATE_GUID;
	EFI_GUID AmitseBootOrderChangeGuid = AMITSE_BOOT_ORDER_CHANGE_GUID;
//ZYY006008 - START
/*
	//CDL002042++ >>
	SETUP_DATA *pSetup; 
	CHAR16 SetupName[] = L"Setup"; 
	UINTN  Setup_Size;
	EFI_STATUS Status; 
	//CDL002042++ <<
*/
//ZYY006008 - END	
	if (data == (UINTN)NULL ? 1 : (CallbackShowMessageBox (data, MSGBOX_TYPE_YESNO) == MSGBOX_YES) ) //To avoid draw MessageBox when data is passed as NULL to save data silently EIP114800
	{
		//Check for NO_SUBMIT_IF before saving data in every page
		if(CheckNoSubmitIf())
		{
			return FALSE; //cant save Invalid Submit value
		}
		//EIP-126057
		if(gApp!=NULL)
		{
	        //Check for inconsistency before saving data
	        if(CheckInconsistence((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[gApp->CurrentPage])))
	        {
	            return FALSE; //cant save inconsistent value
	        }
		}

		if(gResetRequired)
		{	//Let's update the SaveState Variable 
			UINT32 SaveStateVarNum;
			UINT16 SaveState=SETUP_SAVED_AND_RESET_REQUIRED;
			if(VarGetVariableInfoId( SETUP_SAVE_STATE_INFO_KEY_ID, &SaveStateVarNum ))
				VarSetValue(SaveStateVarNum,0,sizeof(UINT16),&SaveState);
		}

		nvPtr = gVariableList;
		for ( i = 0; i < gVariables->VariableCount; i++, nvPtr++ )
		{
			if(VARIABLE_ID_BOOT_ORDER == i)
			{
                UINTN j,k=0,n=0, CurrSize = 0;
                UINT16 *BootOrder = NULL, *CurrOrder = NULL;
                BOOT_DATA *pBootData = NULL;

				TseSaveAddDelBootOptions();

                BootOrder = EfiLibAllocateZeroPool(nvPtr->Size);
                MemCopy(BootOrder,nvPtr->Buffer,nvPtr->Size);

                //Disable all options
                for(j=0;j<gBootOptionCount;j++)
				{
					if (!(gBootData[j].Active & LOAD_OPTION_HIDDEN))		//TSE will not do the option anything if it is hidden
					{	
	                    gBootData[j].Active &= ~(LOAD_OPTION_ACTIVE);
					}
				}
                //Enable options in BootOrder
                for(j=0;j<gBootOptionCount;j++)
                {
                    pBootData = BootGetBootData(BootOrder[j]);
                    if(pBootData)
					{
						if (!(pBootData->Active & LOAD_OPTION_HIDDEN))		//TSE will not do the option anything if it is hidden	
						{
	                        pBootData->Active |= LOAD_OPTION_ACTIVE;
						}
					}
                }

                //Save boot options
                for(j=0;j<gBootOptionCount;j++)
                {
                    CHAR16 varName[] = L"BootXXXX";
                    BOOT_OPTION *pOption;
                    UINTN OptionSize;

                    OptionSize = 0; pOption = NULL;
                    SPrint( varName, sizeof(CHAR16) * (EfiStrLen( varName )+1),gBootFormarSpecifier, gBootData[j].Option );
                    pOption = (BOOT_OPTION *)VarGetNvramName( varName, &gEfiGlobalVariableGuid, NULL, &OptionSize );

                    pOption->Active = gBootData[j].Active;

                    VarSetNvramName(varName,
                        &gEfiGlobalVariableGuid,
                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        pOption,
                        OptionSize);
                    
                    MemFreePointer((VOID **)&pOption);
                }
				n=0;
                //Enabled options first
                for(k=0;k<gBootOptionCount;k++)
                {
                    if(DISABLED_BOOT_OPTION == BootOrder[k])
				    {	
			//add Disabled options
	                	for(j=n; j < gBootOptionCount; j++ )
	                	{
	                    		if ( (!(gBootData[j].Active & LOAD_OPTION_ACTIVE)) && (!(gBootData[j].Active & LOAD_OPTION_HIDDEN)) )
	                    		{
									BootOrder[k] = gBootData[j].Option;
									n=j;
									n++;
									break;
	                       		}
	                	}
				    }		
                        
                }

                ASSERT(k==gBootOptionCount);

                //Signal TPM if Boot order has changed
				CurrOrder = VarGetNvramName(L"BootOrder", &gEfiGlobalVariableGuid, NULL, &CurrSize);

                if( CurrSize != (k*sizeof(UINT16)) )
                    EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
                else if(CurrOrder)
                {
                    if (MemCmp((UINT8 *)CurrOrder, (UINT8 *)BootOrder, CurrSize))
						EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
                }

                MemFreePointer((VOID **)&CurrOrder);

                //Save boot order
                VarSetNvramName(L"BootOrder",
                    &gEfiGlobalVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    BootOrder,
                    k * sizeof(UINT16));

                MemFreePointer((VOID **) &BootOrder);

                //Continue to next variable
                continue;
			}
			//EIP70421 & 70422  Support for driver order starts
			if(VARIABLE_ID_DRIVER_ORDER == i)
			{
                UINTN 	j, k=0, n=0;
                UINT16 	*DriverOrder = NULL;
                BOOT_DATA *pDriverData = NULL;

				TseSaveAddDelDriverOptions ();

                DriverOrder = EfiLibAllocateZeroPool (nvPtr->Size);
                MemCopy (DriverOrder,nvPtr->Buffer,nvPtr->Size);

                //Disable all options
                for (j = 0; j < gDriverOptionCount; j ++)
				{
					if (!(gDriverData [j].Active & LOAD_OPTION_HIDDEN))		//TSE will not do the option anything if it is hidden
					{
                    	gDriverData [j].Active &= ~(LOAD_OPTION_ACTIVE);
					}
				}
                //Enable options in DriverOrder
                for (j = 0; j < gDriverOptionCount; j ++)
                {
                    pDriverData = DriverGetDriverData (DriverOrder [j]);
                    if(pDriverData)
					{
						if (!(pDriverData->Active & LOAD_OPTION_HIDDEN))		//TSE will not do the option anything if it is hidden
						{	
	                        pDriverData->Active |= LOAD_OPTION_ACTIVE;
						}
					}
                }
                //Save driver options
                for (j  = 0; j < gDriverOptionCount; j ++)
                {
                    CHAR16 varName[] = L"DriverXXXX";
                    BOOT_OPTION *pOption;
                    UINTN OptionSize;

                    OptionSize = 0; pOption = NULL;
                    SPrint (varName, sizeof (CHAR16) * (EfiStrLen (varName) + 1), gDriverFormarSpecifier, gDriverData [j].Option );
                    pOption = (BOOT_OPTION *)VarGetNvramName (varName, &gEfiGlobalVariableGuid, NULL, &OptionSize );

                    pOption->Active = gDriverData [j].Active;

                    VarSetNvramName (varName,
                        &gEfiGlobalVariableGuid,
                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        pOption,
                        OptionSize);
                    
                    MemFreePointer((VOID **)&pOption);
                }
				n=0;
                //Enabled options first
                for (k = 0; k < gDriverOptionCount; k ++)
                {
                    if(DISABLED_BOOT_OPTION == DriverOrder [k])
				    {	
			//add Disabled options
	                	for (j = n; j < gDriverOptionCount; j++ )
	                	{
                    		if ( (!(gDriverData [j].Active & LOAD_OPTION_ACTIVE)) && (!(gDriverData [j].Active & LOAD_OPTION_HIDDEN)) )
                    		{
								DriverOrder [k] = gDriverData [j].Option;
								n = j;
								n ++;
								break;
                       		}
	                	}
				    }		
                        
                }

                ASSERT (k == gDriverOptionCount);

                //Signal TPM if Boot order has changed			//No need of signalling the event for driver order change
/*				CurrOrder = VarGetNvramName (L"DriverOrder", &gEfiGlobalVariableGuid, NULL, &CurrSize);

                if (CurrSize != (k*sizeof(UINT16)))
                    EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
                else if (CurrOrder)
                {
                    if (MemCmp ((UINT8 *)CurrOrder, (UINT8 *)DriverOrder, CurrSize) )
						EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
                }

                MemFreePointer((VOID **)&CurrOrder);*/

                //Save boot order
                VarSetNvramName(L"DriverOrder",
                    &gEfiGlobalVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    DriverOrder,
                    k * sizeof(UINT16));

                MemFreePointer((VOID **) &DriverOrder);

                //Continue to next variable
                continue;
			}
			//EIP70421 & 70422  Support for driver order ends

			if(VARIABLE_ID_BBS_ORDER == i)
			{
				CsmSaveBBSOrder(nvPtr);
                //Continue to Next variable
                continue;
			}

			VarSetNvram( i, nvPtr->Buffer, nvPtr->Size );
		}
//ZYY006008 - START
/*		
		//CDL002042 ++ >>      
		pSetup = (SETUP_DATA*)EfiLibAllocateZeroPool(sizeof(SETUP_DATA));
		Status = pRS->GetVariable(L"Setup", &gSetupGuid, NULL, &Setup_Size, pSetup);
		if (Status != EFI_SUCCESS){
		  TRACE((-1,"FxMsg: Fail To Get Setup Variable ...\n"));
		  
		} else {
		    if(pSetup->BootMode == 0){         // Legacy Mode
		      pSetup->BootOptionFilter = 1;
			} else if (pSetup->BootMode == 1){ // UEFI Mode
		      pSetup->BootOptionFilter = 2;		  
			} else if (pSetup->BootMode == 2){ // MIX Mode
		      pSetup->BootOptionFilter = 0;
			}
				
			// Save Setup Variable
			Status = pRS->SetVariable( L"Setup", &gSetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE, Setup_Size, pSetup);
			if (Status == EFI_SUCCESS){
		      TRACE((-1,"FxMsg: Setup Variable Update Successfully ...\n"));
			}else {
		      TRACE((-1,"FxMsg: Setup Variable Update Fail ...\n"));
			}
			MemFreePointer((VOID **) &pSetup);
		}
		//CDL002042 ++ <<	
*/
//ZYY006008 - START
		PasswordCommitChanges( TRUE );

		TSESetHDDPassword();

        SavedConfigChangesHook();

		EfiLibNamedEventSignal (&AmitseNvramUpdateGuid);
		gTseCacheUpdated = FALSE;
		
		return TRUE;
	}
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveBBSOrder
//
// Description:	Function to save the bbs device order
//
// Input:	NVRAM_VARIABLE *nvPtr
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveBBSOrder(NVRAM_VARIABLE *nvPtr)
{
    UINT16 *BootOrder;
    UINTN BootOrderSize,p;
    BBS_ORDER_TABLE *NewLegacyOrder, *NewDevEntry, *BufferDevEntry;
    UINT8 *NewBuffer, *NewBuffEntry;
    BOOT_DATA *pBootData;
    BBS_ORDER_LIST *BBSList = NULL;
    UINT16 count,r,s;
    UINT8 *CurrOrder = NULL;
    UINTN CurrSize = 0;
    UINTN DPSize = 0;                
    VOID *DisDPs = NULL;
    EFI_GUID BootManGuid = BOOT_MANAGER_GUID;
    EFI_GUID AmitseBootOrderChangeGuid = AMITSE_BOOT_ORDER_CHANGE_GUID;
    UINT32 LegDevOrderAttribute = 7;

    BootOrderSize = 0;
    BootOrder = VarGetNvramName(L"BootOrder", &gEfiGlobalVariableGuid, NULL, &BootOrderSize);

    if (0 == BootOrderSize)
        return; //continue;

    NewLegacyOrder = EfiLibAllocateZeroPool(nvPtr->Size);
    NewBuffer = EfiLibAllocateZeroPool(nvPtr->Size);

    //NOTE: Taking advantage of the fact that
    //VARIABLE_ID_BBS_ORDER is after
    //VARIABLE_ID_BOOT_ORDER
    NewDevEntry = NewLegacyOrder;
    NewBuffEntry = NewBuffer;
    for(p=0; p<(BootOrderSize/sizeof(UINT16)); p++)
    {
        pBootData = BootGetBootData(BootOrder[p]);
		//EIP:59417 - Error Handling in case of pBootData is NULL. If its NULL the setupgets a CRASH
		if(pBootData == NULL)
		 goto DONE;

        if(BBSValidDevicePath(pBootData->DevicePath))
        {
            BufferDevEntry = (BBS_ORDER_TABLE *)(nvPtr->Buffer + pBootData->LegacyEntryOffset);

				if ( (BufferDevEntry->Length >= nvPtr->Size) || (0 == BufferDevEntry->Length) ) //EIP-120011
				{
					goto DONE;
				}

            BBSList = pBootData->OrderList;

            count = pBootData->LegacyDevCount;

            MemCopy(NewDevEntry, BufferDevEntry, sizeof(UINT32)+(count+1)*sizeof(UINT16));
            MemCopy(NewBuffEntry, BufferDevEntry, sizeof(UINT32)+(count+1)*sizeof(UINT16));
        
	        //----------------------------------------------------------------------------------//       
	        // EIP-35863: This block considers the case of legacy devices being positioned	//
	        // anywhere in the LegacyDevOrder (whether enabled or disabled)			//
	        //----------------------------------------------------------------------------------// 
	        if(count>0) //Disabled boot options exist
            {
                for(r=0;r<count;r++)
                {
      		        //See if a given index in BBSList exist in TypeEntry              
		            for(s=0;s<count;s++)
                    {
                        if(BBSList[r].Index == NewDevEntry->Data[s])
			            {
    				        break;
			            }
                    }

		            if(s>=count) //Index Not present
                    {
			            //Find the first disabled slot
			            for(s=0;s<count;s++)
              		    {
                      	    if(NewDevEntry->Data[s] == DISABLED_BOOT_OPTION)
			                {
				                //Add device path to Nvram variable
                                if(gIsSaveDisabledBBSDevicePath)
                  			        CsmBBSSetDisabled(BBSList[r].Index, &DisDPs, &DPSize);
				                NewDevEntry->Data[s] = BBSList[r].Index;
               			        NewDevEntry->Data[s] |= BBS_ORDER_DISABLE_MASK;
				                break;
			                }
               		    }
                    }
                }
            }

            pBootData->LegacyEntryOffset = (UINTN)NewDevEntry - (UINTN)NewLegacyOrder;

            NewDevEntry = (BBS_ORDER_TABLE *)((UINTN)NewDevEntry + sizeof(UINT32)+(count+1)*sizeof(UINT16));
            NewBuffEntry = NewBuffEntry + sizeof(UINT32)+(count+1)*sizeof(UINT16);
        }
    }

DONE:
    //Update the nv buffer with the re ordered list
    MemFreePointer((VOID **) &(nvPtr->Buffer));
    nvPtr->Buffer = NewBuffer;

    //Signal TPM if BBS order has changed
	CurrOrder = VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, &LegDevOrderAttribute, &CurrSize );

	if(CurrOrder)
	{
		if(MemCmp((UINT8 *)CurrOrder, (UINT8 *)NewLegacyOrder, CurrSize))
			EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);

		MemFreePointer((VOID **) &CurrOrder);
	}

    //Save BBS order
    VarSetNvramName(L"LegacyDevOrder",
        &gLegacyDevGuid,
        LegDevOrderAttribute,
        NewLegacyOrder,
        nvPtr->Size);

    if(gIsSaveDisabledBBSDevicePath)
    {
        //Save disabled device paths
        VarSetNvramName(L"DisabledDevs",
            &BootManGuid,
            EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
            DisDPs,
            DPSize);
    
        MemFreePointer((VOID **) &DisDPs);
        MemFreePointer((VOID **) &BootOrder);
    }
    MemFreePointer((VOID **) &NewLegacyOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ExitApplication
//
// Description:	Function to exit form the setup application
//
// Input:	None
//
// Output:	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ExitApplication( VOID )
{
	if ( CallbackShowMessageBox( (UINTN)gExitMsgBox, MSGBOX_TYPE_YESNO ) == MSGBOX_YES )
	{
		if ( ! gVariableChanged )
			gResetRequired = FALSE;

		LoadPreviousValues( FALSE );
		gVariableChanged = FALSE;
		return TRUE;
	}

	return FALSE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
