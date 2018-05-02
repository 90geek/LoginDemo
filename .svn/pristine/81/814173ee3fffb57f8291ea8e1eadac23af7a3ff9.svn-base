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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/bbs.c $
//
// $Author: Premkumara $
//
// $Revision: 24 $
//
// $Date: 9/24/12 9:04a $
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		bbs.c
//
// Description:	takecare of bbs/legacy boot management.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "minisetup.h"

EFI_GUID gLegacyDevGuid = LEGACY_DEV_ORDER_GUID;
BOOT_DATA *gCurrLegacyBootData;
static EFI_LEGACY_BIOS_PROTOCOL *gLegacyBios = NULL;
extern EFI_GUID gEfiLegacyBiosProtocolGuid;

//Internal functions
EFI_STATUS _BBSInitProtocol( VOID );
VOID _BBSSetDevicePriorities( BBS_TABLE *BBSInfo, UINT16 *Priority, BOOT_DATA *BootData );
VOID _CreateDriveString ( CHAR16 *String, UINT16 *IdentifyDriveData );
VOID BBSBuildName( CHAR16 *String, BBS_TABLE *info, UINTN index, HDD_INFO *HDDInfo );
BOOLEAN _BBSCheckDisabled( BBS_TABLE *BBSEntry );
UINT8   IsBootOptionsGroupingEnabled (void);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BBSInitProtocol
//
// Description:	function to initialize the bbs protocol.
//
// Input:		void
//
// Output:		device path
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _BBSInitProtocol( VOID )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( gLegacyBios != NULL )
		return Status;

	Status = gBS->LocateProtocol( &gEfiLegacyBiosProtocolGuid, NULL, (void**)&gLegacyBios );
	if ( EFI_ERROR( Status ) )
		gLegacyBios = NULL;

	return Status;
}


INTN CompareDevicePath(EFI_DEVICE_PATH_PROTOCOL *pDp1, EFI_DEVICE_PATH_PROTOCOL *pDp2){
	UINTN	len;
//---------------------
	if(!pDp1 && !pDp2) return 0; //if both is NULL than Dp1==Dp2
	if(!pDp1 || !pDp2) return -1; // if one is NULL than Dp1!=Dp2
	len=EfiDevicePathSize(pDp1);
	if(EfiDevicePathSize(pDp2)!=len) return -1;
	return MemCmp(pDp1,pDp2, len);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MatchDevicePath
//
// Description:	Matches the Device path from the BootOption to BBS Device path to locate the 
//              right Device
//
// Input:		pBootData - Boot Data of Boot Option
//              LegacyOrder - LegacyDevOrder Entry for Boot Option
//              DevHandle   - BBS device Handle
//
// Output:		BOOLEAN - TRUE - Device path matched betweend LegacyOrder and pBootData.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchDevicePath(BOOT_DATA *pBootData, BBS_ORDER_TABLE* LegacyOrder, EFI_HANDLE DevHandle)
{
    CHAR16 *varName = L"BootXXXX";
    BOOT_OPTION *pOption;
    UINTN OptionSize;
    EFI_DEVICE_PATH_PROTOCOL *Path;
    EFI_DEVICE_PATH_PROTOCOL *BBSDevDP;
    EFI_STATUS Status;
    BOOLEAN bRet=FALSE; 

    OptionSize = 0; pOption = NULL;
    SPrint( varName, sizeof(CHAR16) * (EfiStrLen( varName )+1),gBootFormarSpecifier, pBootData->Option );
    pOption = (BOOT_OPTION *)VarGetNvramName( varName, &gEfiGlobalVariableGuid, NULL, &OptionSize );

    if(EfiDevicePathSize(pBootData->DevicePath) == pOption->PathLength)
    {   // Device path Length Matches
        // Not Flex Boot 
        bRet=TRUE;
        goto DONE;
    }

    //For Flex Boot try to match Device path of BBS Device

	// Skip the BBS Devicepath
	Path = (EFI_DEVICE_PATH_PROTOCOL*)(((UINTN)pBootData->DevicePath) + EfiDevicePathSize(pBootData->DevicePath));

    Status = gBS->HandleProtocol( DevHandle, &gEfiDevicePathProtocolGuid, (void**)&BBSDevDP );
 	// Not able to locate just matched the Device type
 	if ( EFI_ERROR( Status ) )
	{
	  bRet=TRUE; 
	  goto DONE;
	}

	//Comparing device path length if MATCH_BOOT_OPTION_BY_LOCATION = 1 devicepath(BBSDevDP) and DevicePath length are equal
	if(CompareDevicePath(Path, BBSDevDP) == 0)
	{
		bRet=TRUE;
	}

	//EIP-151484 If MATCH_BOOT_OPTION_BY_LOCATION = 0 then devicepath(BBSDevDP) and Device Pathlength will be different so matching with DeviceType
	else if( ( ((BBS_ORDER_TABLE*)LegacyOrder)->Type == BBSDevDP->Type ) || 
				( ((BBS_BBS_DEVICE_PATH*)pBootData->DevicePath)->DeviceType == BBSDevDP->Type )
	)
	{
		bRet = TRUE;
	}

DONE:
    MemFreePointer((VOID **)&pOption);

    return bRet;
}

//EIP109382 Starts
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------
// Procedure:	RearrangeBBSOrder
//
// Description:	Rearranges the bootdata legacy entries with legacydevorder defaults
//
// Input:		VOID * - Cache Buffer
//
// Output:		VOID
//
//--------------------------------------------------------------------------------------
//<AMI_PHDR_END>
//UINT8   IsBootOptionsGroupingEnabled (VOID);
EFI_STATUS _BBSInitProtocol (VOID);
BOOLEAN MatchDevicePath(BOOT_DATA *pBootData, BBS_ORDER_TABLE* LegacyOrder, EFI_HANDLE DevHandle);
VOID RearrangeBBSOrder (NVRAM_VARIABLE *nvPtr, NVRAM_VARIABLE *DefaultBuffer)
{
   EFI_STATUS  Status;
   UINT16      HDDCount = 0, BBSCount = 0;
   HDD_INFO    *HDDInfo = NULL;
   BBS_TABLE   *BBSInfo = NULL;
   UINT16      *BootOrder;
   UINTN       BootOrderSize,p;
   BOOT_DATA   *pBootData;
   UINT16      count = 0;
   UINTN       CurrSize = 0, iIndex = 0;
   EFI_GUID    AmitseBootOrderChangeGuid = AMITSE_BOOT_ORDER_CHANGE_GUID;
   BBS_ORDER_TABLE      *DevEntry = NULL, *CurrOrder = NULL, *NewLegacyOrder = NULL, *NewDevEntry = NULL;
   BBS_BBS_DEVICE_PATH  *DevPath = NULL;
   
   Status = _BBSInitProtocol ();
   if (EFI_ERROR (Status))
      return;

   Status = gLegacyBios->GetBbsInfo (
               gLegacyBios,
               &HDDCount,
               &HDDInfo,
               &BBSCount,
               &BBSInfo
               );
   if (EFI_ERROR (Status))
   {
      return;
   }
   BootOrderSize = 0;
   BootOrder = VarGetNvramName (L"BootOrder", &gEfiGlobalVariableGuid, NULL, &BootOrderSize);
   
   if ((NULL == BootOrder) || (0 == BootOrderSize))
      return; //continue;

   NewLegacyOrder = EfiLibAllocateZeroPool (DefaultBuffer->Size);
   if (NULL == NewLegacyOrder)
   {
      MemFreePointer((VOID **) &BootOrder);
      return;
   }   
   
   //NOTE: Taking advantage of the fact that
   //VARIABLE_ID_BBS_ORDER is after
   //VARIABLE_ID_BOOT_ORDER
   NewDevEntry = NewLegacyOrder;
   for (p=0; p<(BootOrderSize/sizeof(UINT16)); p++)
   {
      pBootData = BootGetBootData (BootOrder[p]);
      //EIP:59417 - Error Handling in case of pBootData is NULL. If its NULL the setupgets a CRASH
      if (pBootData == NULL)
         goto DONE;
   
      if (BBSValidDevicePath (pBootData->DevicePath))
      {
         DevPath = (BBS_BBS_DEVICE_PATH *)pBootData->DevicePath;
         DevEntry = (BBS_ORDER_TABLE *)DefaultBuffer->Buffer;
         for (iIndex = 0; iIndex < DefaultBuffer->Size; )
         {
				if ( (DevEntry->Length >= DefaultBuffer->Size) || (0 == DevEntry->Length) ) //EIP-120011
				{
					return;
				}

            count = DevEntry->Length / sizeof(UINT16) - 1;

            if (count)
            {
               if (DevPath->DeviceType == DevEntry->Type)
               {
                  if (MatchDevicePath (pBootData, DevEntry, (EFI_HANDLE)*(UINTN*)&BBSInfo[(UINT8)DevEntry->Data[0]].IBV1) )
                  //Found a valid dev entry group.
                     break;
               }
            }
            count = sizeof (UINT32) + DevEntry->Length;
            DevEntry = (BBS_ORDER_TABLE *)((UINTN)DevEntry + count);
            iIndex += count;
         }
         if (iIndex < DefaultBuffer->Size)
         {
            MemCopy (NewDevEntry, DevEntry, sizeof(UINT32) + DevEntry->Length);
         }
         pBootData->LegacyEntryOffset = (UINTN)NewDevEntry - (UINTN)NewLegacyOrder;
         //create boot data order list
         NewDevEntry = (BBS_ORDER_TABLE *)((UINTN)NewDevEntry + sizeof (UINT32) + DevEntry->Length);
      }
   }
   MemFreePointer ((VOID **)&nvPtr->Buffer);
   nvPtr->Buffer = (UINT8 *)NewLegacyOrder;
DONE:
   //Update the nv buffer with the re ordered list
   
   //Signal TPM if BBS order has changed
   CurrOrder = VarGetNvramName (L"LegacyDevOrder", &gLegacyDevGuid, NULL, &CurrSize);
   if (NULL == CurrOrder)
   {
      MemFreePointer((VOID **) &BootOrder);
      return;
   }
   if (CurrOrder)
   {
      if (MemCmp ((UINT8 *)CurrOrder, (UINT8 *)NewLegacyOrder, CurrSize))
         EfiLibNamedEventSignal (&AmitseBootOrderChangeGuid);
      
      MemFreePointer((VOID **) &CurrOrder);
   }
   MemFreePointer((VOID **) &BootOrder);
}
//EIP109382 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSGetDeviceList
//
// Description:	function to get the list of all the devices
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSGetDeviceList( VOID )
{
    EFI_STATUS Status;

    UINT16 HDDCount = 0, BBSCount = 0;
    HDD_INFO *HDDInfo = NULL;
    BBS_TABLE *BBSInfo = NULL;

    BBS_ORDER_TABLE *LegacyOrder = NULL, *NewLegacyOrder = NULL, *DevEntry, *NewDevEntry;
    UINTN NewLegacyOrderSize, LegacyOrderSize=0, j, l;
    UINT16 count = 0,u16Tmp;
    UINT16 *BootOrder = NULL, *NewBootOrder = NULL;
    UINTN NewBootOrderSize, BootOrderSize=0, i, k;
    BOOT_DATA *pBootData;
    BBS_BBS_DEVICE_PATH * DevPath;
    UINT16 NoOfLegacyGroups = 0;
	UINT32 LegDevOrderAttribute = 7;
    
    Status = _BBSInitProtocol();
    if ( EFI_ERROR( Status ) )
        return;

    Status = gLegacyBios->GetBbsInfo(
            gLegacyBios,
            &HDDCount,
            &HDDInfo,
            &BBSCount,
            &BBSInfo
            );

    LegacyOrderSize = 0;

    LegacyOrder = VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, &LegDevOrderAttribute, &LegacyOrderSize );
    if ( LegacyOrder == NULL )
        goto DONE;

    BootOrderSize = 0;
    BootOrder = VarGetNvramName( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &BootOrderSize );
    if(NULL == BootOrder)
        goto DONE;

    //Check if the Master boot order and Legacy dev order match.
    //Create corrected new orders if not.
    NewLegacyOrder = EfiLibAllocateZeroPool(LegacyOrderSize);
    NewBootOrder = EfiLibAllocateZeroPool(BootOrderSize);

    //NOTE: Device count will not be initialised here. It will be
    //initialised with the number of devices in a group when the user
    //switches to a page specific to that group.
    NoOfLegacyGroups = 0;
    k = 0;
    NewDevEntry = NewLegacyOrder;
    for(i=0; i<(BootOrderSize/sizeof(UINT16)); i++)
    {
        pBootData = BootGetBootData(BootOrder[i]);
        if(pBootData)
        {
            if(BBSValidDevicePath(pBootData->DevicePath))
            {
                //BBS boot order entry
                DevPath = (BBS_BBS_DEVICE_PATH *)pBootData->DevicePath;

                DevEntry = LegacyOrder;
                for(j=0; j<LegacyOrderSize; )
                {
					if ( (DevEntry->Length >= LegacyOrderSize) || (0 == DevEntry->Length) ) //EIP-120011
					{
						return;
					}
                    count = DevEntry->Length / sizeof(UINT16) - 1;
                    if(count)
                    {
                        if(DevPath->DeviceType == DevEntry->Type)
                        {
                            if(MatchDevicePath(pBootData, DevEntry,(EFI_HANDLE)*(UINTN*)&BBSInfo[(UINT8)DevEntry->Data[0]].IBV1 ))
                                //Found a valid dev entry group.
                                break;
                        }
                    }

                    //Go to next entry
                    count = sizeof(UINT32) + DevEntry->Length;
                    DevEntry = (BBS_ORDER_TABLE *)((UINTN)DevEntry + count);
                    j += count;
                }

                if(j<LegacyOrderSize)
                {
                    //Found a valid BBS entry. Take dev entry and boot option.
                    NewBootOrder[k] = BootOrder[i];
                    k++;

                    MemCopy(NewDevEntry, DevEntry, sizeof(UINT32) + DevEntry->Length);
                    NoOfLegacyGroups++;

                    pBootData->LegacyEntryOffset = (UINTN)NewDevEntry - (UINTN)NewLegacyOrder;
                    pBootData->LegacyDevCount = count;


                    if(gIsSaveDisabledBBSDevicePath)
                    {
                        //Make sure the right devices are disabled
                        for(j=0;j<count;j++)//Caution: destroying contents of j
                        {
                            if(BBS_ORDER_DISABLE_MASK == (NewDevEntry->Data[j] & BBS_ORDER_DISABLE_MASK))
                            {
                            	//BBS Type Network Device does not publish any Handle hence, directly assigning the actual Index
								if(BBS_TYPE_EMBEDDED_NETWORK == NewDevEntry->Type)//EIP-175119
									NewDevEntry->Data[j] = (UINT8)(NewDevEntry->Data[j]);
								//Make sure we have the device path in NVRAM for this legacy option
								else if( !_BBSCheckDisabled( &(BBSInfo[(UINT8)(NewDevEntry->Data[j])]) ) )
								{
									NewDevEntry->Data[j] = (UINT8)(NewDevEntry->Data[j]);
								}
                            }
                        }
                    }

    				if(!IsPreservedDisabledBootOptionOrder())
    				{
	                    //Correct LegacyDevOrder variable if necessary. Move
		                //disabled devices to end.
			            for ( j = 0; j < count; j++ )
				        {
							if(BBS_ORDER_DISABLE_MASK == (NewDevEntry->Data[j] & BBS_ORDER_DISABLE_MASK))
							{
								for(l=j+1; l<count; l++)
								{
									if(BBS_ORDER_DISABLE_MASK != (NewDevEntry->Data[l] & BBS_ORDER_DISABLE_MASK))
									{
										u16Tmp = NewDevEntry->Data[l];
										NewDevEntry->Data[l] = NewDevEntry->Data[j];
										NewDevEntry->Data[j] = u16Tmp;
										break;
									}
								}
								if(l>=count)
	                                break;
		                    }
                        }
                    }

                    //create boot data order list
                    pBootData->OrderList = EfiLibAllocateZeroPool( count * sizeof(BBS_ORDER_LIST) );
                    for ( j = 0; j < count; j++ )
                    {
                        pBootData->OrderList[j].Index = NewDevEntry->Data[j] & (~BBS_ORDER_DISABLE_MASK);
                        BBSBuildName(
                                    pBootData->OrderList[j].Name,
                                    &BBSInfo[pBootData->OrderList[j].Index],
                                    pBootData->OrderList[j].Index,
                                    HDDInfo
                                    );
                    }

                    //Move pointer to the unused portion
                    count = sizeof(UINT32) + NewDevEntry->Length;
                    NewDevEntry = (BBS_ORDER_TABLE *)((UINTN)NewDevEntry + count);

                    //Mark it used in DevEntry by assigning device type
                    //to BBS_TYPE_UNKNOWN
                    DevEntry->Type = BBS_TYPE_UNKNOWN;
                }
            }
            else
            {
                //A valid non bbs boot order entry
                NewBootOrder[k] = BootOrder[i];
                k++;
            }
        }
    }

    //Set corrected variables
    NewLegacyOrderSize = (UINTN)NewDevEntry - (UINTN)NewLegacyOrder;
    VarSetNvramName(L"LegacyDevOrder",
                    &gLegacyDevGuid,
                    LegDevOrderAttribute,
                    NewLegacyOrder,
                    NewLegacyOrderSize);

    NewBootOrderSize = k*sizeof(UINT16);
    VarSetNvramName(L"BootOrder",
                    &gEfiGlobalVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    NewBootOrder,
                    NewBootOrderSize);

    MemFreePointer( (VOID **)&BootOrder );
    MemFreePointer( (VOID **)&NewBootOrder );
    MemFreePointer( (VOID **)&LegacyOrder );
    MemFreePointer( (VOID **)&NewLegacyOrder );

DONE:
    //Set LegacyDev variable with number of groups
	UpdateLegacyDevVariable(NoOfLegacyGroups);

    //Set the LegacyGroup variable to zero for now
    NoOfLegacyGroups = 0;
    VarSetNvramName( L"LegacyGroup", &gLegacyDevGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &NoOfLegacyGroups, sizeof(NoOfLegacyGroups) );

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSSetBootPriorities_BootOrder
//
// Description:	Assign priority as per boot order other than 0 priority devices
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSSetBootPriorities_BootOrder(UINT16 Priority)
{
	EFI_STATUS	Status;
	UINT16		*pBootOrder=NULL;
	UINT16		BootOrderCount = 0;
//	UINT16        DevType=0; unused Variable
	UINTN         size=0;
	UINT16        HDDCount = 0;
	UINT16        BBSCount = 0;
	HDD_INFO      *HDDInfo = NULL;
	BBS_TABLE     *BBSInfo = NULL;
	BOOT_DATA     *pBootData;
//[RDBG-]	UINT16        i,index,index1;
  UINT16        i = 0,index,index1;  //[RDBG+]	
	UINT16        j;
    UINT8   *pDevOrder;
    BBS_ORDER_TABLE	*pDevEntry;
	
	Status = _BBSInitProtocol();
	if ( EFI_ERROR( Status ) )
		return;
	
	Status = gLegacyBios->GetBbsInfo(
										gLegacyBios,
										&HDDCount,
										&HDDInfo,
										&BBSCount,
										&BBSInfo
									);
	
	if ( EFI_ERROR( Status ) )
		return;
	
	size =0 ;
	pBootOrder = (UINT16 *)VarGetNvramName( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
	BootOrderCount=(UINT16)(size/sizeof(UINT16));

	if (pBootOrder==NULL) 
		return;

    size = 0;
    pDevOrder = (UINT8 *)VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size );

	if (pDevOrder==NULL) 
    {
        MemFreePointer((VOID **) &pBootOrder);
		return;
    }

	for(j=0;j<BootOrderCount;j++)
	{
		pBootData = BootGetBootData(pBootOrder[j]);
		if(!pBootData)
			continue;

        if ( BBSValidDevicePath( pBootData->DevicePath ) )
        {
            pDevEntry = (BBS_ORDER_TABLE *)(pDevOrder + pBootData->LegacyEntryOffset);

			if ( (pDevEntry->Length >= size) || (0 == pDevEntry->Length) ) //EIP-120011
			{
				return;
			}
			
			//[RDBG+]>
			//
			//Setting BBSInfo BootPriority as BBS_DO_NOT_BOOT_FROM when any BBSOption disabled in BootPage
			//
			if (0 == pBootData->Active)
			{
				UINT16 k = 0;
				for (k=0; k<pBootData->LegacyDevCount; k++)
				{
					//Setting BBS_DO_NOT_BOOT_FROM for all entry of same BBSType
					BBSInfo[((pBootData->OrderList[k])).Index].BootPriority = BBS_DO_NOT_BOOT_FROM;
				}
			}
			//
			//Setting BBSInfo BootPriority as BBS_DO_NOT_BOOT_FROM when any BBSOption disabled in BBSPage
			//
			else
			{
				UINT16 k = 0;
				for(k=0; k<pBootData->LegacyDevCount; k++)
				{
					//If its DISABLED in BBSPage
					if( BBS_ORDER_DISABLE_MASK == (pDevEntry->Data[k] & BBS_ORDER_DISABLE_MASK) )
					{
						UINT16 bbsIndex = ( pDevEntry->Data[k] & (~BBS_ORDER_DISABLE_MASK) );
						BBSInfo[bbsIndex].BootPriority = BBS_DO_NOT_BOOT_FROM;
						//BBSInfo[((pBootData->OrderList[k])).Index].BootPriority = BBS_DO_NOT_BOOT_FROM;
					}
				}
			}
			//[RDBG+]<	
			
			//search for boot options which are disabled and change their priority to BBS_DO_NOT_BOOT_FROM
			for(index=0;index<pBootData->LegacyDevCount;index++)//EIP-166385
			{
			    for(index1=0;index1<pBootData->LegacyDevCount;index1++)
			    {
					if(((pBootData->OrderList[index])).Index == pDevEntry->Data[index1])
				   		break;
			    }
				if(index1 == pBootData->LegacyDevCount)
					BBSInfo[((pBootData->OrderList[index])).Index].BootPriority = BBS_DO_NOT_BOOT_FROM;
			}
            for(i=0;i<pBootData->LegacyDevCount;i++)
            {
                if(!(pDevEntry->Data[i] & BBS_ORDER_DISABLE_MASK))
                {
                    if(BBSInfo[pDevEntry->Data[i]].BootPriority == BBS_UNPRIORITIZED_ENTRY)
                    {
        	            BBSInfo[pDevEntry->Data[i]].BootPriority = Priority;
        			    Priority++;
                    }
                }
            }
        }
	}

    MemFreePointer((VOID **) &pDevOrder);
    MemFreePointer((VOID **) &pBootOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSSetBootPriorities
//
// Description:	function to set boot priorities
//
// Input:		BOOT_DATA *pBootData, UINT16 *pOrder, UINTN u16OrderCount
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSSetBootPriorities( BOOT_DATA *pBootData, UINT16 *pOrder, UINTN u16OrderCount)
{
	EFI_STATUS	Status;
	UINT16		HDDCount = 0, BBSCount = 0;
    UINT16		i, Priority = 0;
	HDD_INFO	*HDDInfo = NULL;
	BBS_TABLE	*BBSInfo = NULL;
	UINT16		  *pBootOrder=NULL;
	UINT16		  BootOrderCount = 0;
	UINTN         size=0;

	Status = _BBSInitProtocol();
	if ( EFI_ERROR( Status ) )
		return;

	Status = gLegacyBios->GetBbsInfo(
										gLegacyBios,
										&HDDCount,
										&HDDInfo,
										&BBSCount,
										&BBSInfo
									);

	if ( EFI_ERROR( Status ) )
		return;
	pBootOrder = (UINT16 *)VarGetNvramName( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
	BootOrderCount=(UINT16)(size/sizeof(UINT16));
	for ( i = 0; i < BBSCount; i++ )
	{
		switch ( BBSInfo[i].BootPriority )
		{
			case BBS_IGNORE_ENTRY:
			case BBS_LOWEST_PRIORITY:
			case BBS_DO_NOT_BOOT_FROM:						//EIP 64700
				continue;
			default:
				BBSInfo[i].BootPriority = BBS_UNPRIORITIZED_ENTRY;
				break;
		}
	}

    if(pOrder)
    {
        for ( i = 0; i < BootOrderCount; i++ )
	    {
            pBootData = BootGetBootData(pOrder[i]);

		    if(!pBootData)
                continue;
    		
		    if ( BBSValidDevicePath( pBootData->DevicePath ) )
			    _BBSSetDevicePriorities( BBSInfo, &Priority, pBootData);
	    }
    }
    else
    {
        if ( BBSValidDevicePath( pBootData->DevicePath ) )
            _BBSSetDevicePriorities( BBSInfo, &Priority, pBootData );
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BBSSetDevicePriorities
//
// Description:	function to set boot device priorities
//
// Input:		BBS_TABLE *BBSInfo, UINT16 *Priority, BOOT_DATA *BootData
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _BBSSetDevicePriorities( BBS_TABLE *BBSInfo, UINT16 *Priority, BOOT_DATA *BootData )
{
    UINT8   *pDevOrder;
    UINTN	size;
    UINT16	i,index,index1;
    BBS_ORDER_TABLE	*pDevEntry;

    size = 0;
    pDevOrder = (UINT8 *)VarGetNvramName( L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size );
	//EIP-75352 Suppress the warnings from static code analyzer
	if(NULL == pDevOrder)
		return;

    pDevEntry = (BBS_ORDER_TABLE *)(pDevOrder + BootData->LegacyEntryOffset);

	if ( (pDevEntry->Length >= size) || (0 == pDevEntry->Length) ) //EIP-120011
		return;
		
    //[RDBG+]>
	//
	//when any BBSOption disabled in BootPage then set BBSInfo BootPriority as BBS_DO_NOT_BOOT_FROM
	//
	if (0 == BootData->Active)
	{
		UINT16 k = 0;
		for (k=0; k<BootData->LegacyDevCount; k++)
		{
			//Setting BBS_DO_NOT_BOOT_FROM for all entry of same BBSType
			BBSInfo[((BootData->OrderList[k])).Index].BootPriority = BBS_DO_NOT_BOOT_FROM;
		}
	}

	//
	//when any BBSOption disabled in BBSPage then set BBSInfo BootPriority as BBS_DO_NOT_BOOT_FROM
	//
	else
	{
		UINT16 k = 0;
		for(k=0; k<BootData->LegacyDevCount; k++)
		{
			//If its DISABLED in BBSPage
			if( BBS_ORDER_DISABLE_MASK == (pDevEntry->Data[k] & BBS_ORDER_DISABLE_MASK) )
			{
				UINT16 bbsIndex = ( pDevEntry->Data[k] & (~BBS_ORDER_DISABLE_MASK) );
				BBSInfo[bbsIndex].BootPriority = BBS_DO_NOT_BOOT_FROM;
				//BBSInfo[((BootData->OrderList[k])).Index].BootPriority = BBS_DO_NOT_BOOT_FROM;
			}
		}
	}
    //[RDBG+]<		

	//search for boot options which are disabled and change their priority to BBS_DO_NOT_BOOT_FROM
	for(index=0;index<BootData->LegacyDevCount;index++)//EIP-166385
	{
	    for(index1=0;index1<BootData->LegacyDevCount;index1++)
	    {
			if(((BootData->OrderList[index])).Index == pDevEntry->Data[index1])
		   		break;
	    }
		if(index1 == BootData->LegacyDevCount)
			BBSInfo[((BootData->OrderList[index])).Index].BootPriority = BBS_DO_NOT_BOOT_FROM;
	}

	for ( i = 0; i < BootData->LegacyDevCount; i++ )
	{
        if(!(pDevEntry->Data[i] & BBS_ORDER_DISABLE_MASK))
        {
			// don't set the BootPriority if it already the first one.
			//EIP: 64700 Checking current BootPriority before assigning a new BootPriority
			if ( (BBSInfo[pDevEntry->Data[i]].BootPriority != 0)  && (BBSInfo[pDevEntry->Data[i]].BootPriority != BBS_DO_NOT_BOOT_FROM) )	    //EIP 64700
			{
	            BBSInfo[pDevEntry->Data[i]].BootPriority = *Priority;
			    (*Priority)++;
			}
        }
	}

    MemFreePointer((VOID **) &pDevOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSSetBootNowPriority
//
// Description:	Sets BBS priority for the BootNow devices.
//
// Input:		BootData - Boot data
//				uiPrefferedDevice - prefered Device type valid in ShowAllBBSDev case
//				ShowAllBbsDev - SETUP_SHOW_ALL_BBS_DEVICES
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BBSSetBootNowPriority( BOOT_DATA *BootData,UINTN uiPrefferedDevice,BOOLEAN ShowAllBbsDev)
{
    EFI_STATUS	Status = EFI_SUCCESS;
	UINT16		count = 0, offset = 0;
    UINT8   	*pDevOrder = NULL;
    UINTN 		size = 0;
	UINT16 		HDDCount = 0, BBSCount = 0;
    UINT16 		i;
    UINT16 		Priority = 0;

    BBS_ORDER_TABLE	*pDev = NULL;
	HDD_INFO		*HDDInfo = NULL;
	BBS_TABLE		*BBSInfo = NULL;
    BBS_ORDER_LIST	*BBSList = NULL;

	Status = _BBSInitProtocol();
	if ( EFI_ERROR( Status ) )
		return Status;

	Status = gLegacyBios->GetBbsInfo(
										gLegacyBios,
										&HDDCount,
										&HDDInfo,
										&BBSCount,
										&BBSInfo
									);

	if ( EFI_ERROR( Status ) )
		return Status;

	for ( i = 0; i < BBSCount; i++ )
	{
		switch ( BBSInfo[i].BootPriority )
		{
			case BBS_IGNORE_ENTRY:
			case BBS_LOWEST_PRIORITY:
			case BBS_DO_NOT_BOOT_FROM:				//EIP 64700
				continue;
			default:
				BBSInfo[i].BootPriority = BBS_UNPRIORITIZED_ENTRY;
				break;
		}
	}
	if(!ShowAllBbsDev)
	{
	    count = BootData->LegacyDevCount;
	    offset = (UINT16)BootData->LegacyEntryOffset;
	
	    size = 0;
		pDevOrder = HelperGetVariable(VARIABLE_ID_BBS_ORDER,L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size);
		//EIP-75352 Suppress the warnings from static code analyzer
		if(NULL == pDevOrder)
			return EFI_NOT_FOUND;

		pDev = (BBS_ORDER_TABLE *)(pDevOrder + offset);

		if ( (pDev->Length >= size) ||(0 == pDev->Length) ) //EIP-120011
			return EFI_NOT_FOUND;
	
		for ( i = 0; i < count; i++ )
		{
	        if(DISABLED_BOOT_OPTION != pDev->Data[i])
	        {
	            BBSInfo[pDev->Data[i]].BootPriority = Priority;
			    Priority++;
	        }
		}
	}
	else
	{
	   BBSList = BootData->OrderList;
 	   BBSInfo[BBSList[uiPrefferedDevice].Index].BootPriority = Priority;
	   Priority++;
	}


  TseBBSSetBootPriorities_BootOrder(Priority);

  if (0 == Priority ) //EIP-93797
	return EFI_UNSUPPORTED;

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CreateDriveString 
//
// Description:	function to create the device string
//
// Input:		CHAR16 *String, UINT16 *IdentifyDriveData
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _CreateDriveString ( CHAR16 *String, UINT16 *IdentifyDriveData )
{
	UINT8	i, data8;
	UINT16	data16;
	UINT8	s[MAX_DRIVE_NAME] = "APAT :";	// "PATA: "

    //Check if identify drive data is available
    if(NULL == IdentifyDriveData)
        return;

	// Check Word76 for BIT1 and BIT2; set for SATA drives
    data16 = IdentifyDriveData[76];
	if ((data16 != 0xFFFF) && (data16 & 6)) {
		s[1] = 'S';
	}

	// Get the drive name out of IdentifyDrive data word 27..46 (upto 40 chars)
	MemCopy(&s[6], IdentifyDriveData+27, MAX_DRIVE_NAME-5);

	// Swap the bytes
	for (i=0; i<MAX_DRIVE_NAME; i+=2) 
	{
		data8=s[i];
		s[i]=s[i+1];
		s[i+1]=data8;
	}

	s[MAX_DRIVE_NAME-1] = 0;	// terminate with zero

	//Put drive name in CHAR 16 array
	for (i=0; i<(MAX_DRIVE_NAME-1); i++)
	{
		String[i] = s[i];
	}
	String[MAX_DRIVE_NAME-1] = 0; // terminate with 0
}

EFI_STATUS GetAdvanceDeviceName( CHAR16 *String, VOID *info, UINTN index, VOID *HDDInfo );
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSBuildDefaultName
//
// Description:	function to build the default boot device name
//
// Input:		CHAR16 *String, BBS_TABLE *info, UINTN index, HDD_INFO *HDDInfo
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSBuildDefaultName( CHAR16 *String, BBS_TABLE *info, UINTN index, HDD_INFO *HDDInfo )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT8	i, *StringDesc;

	// If current BBS entry has its description then use it.
	StringDesc = (UINT8*)(UINTN)((info->DescStringSegment << 4) + info->DescStringOffset);
	if ( StringDesc != NULL )
	{
		for ( i = 0; (i < (MAX_DRIVE_NAME - 1)) && (StringDesc[i] != L'\0'); i++ )
			String[i] = (CHAR16)StringDesc[i];
		
		String[i] = L'\0';
	}
	else
	{
		Status = GetAdvanceDeviceName(String, info, index, HDDInfo);
		if ( Status != EFI_SUCCESS ) {
			switch ( info->DeviceType )
			{
				case BBS_TYPE_FLOPPY:
					EfiStrCpy(String, L"Floppy");
					break;
		
				case BBS_TYPE_HARDDRIVE:
					EfiStrCpy(String, L"Hard Drive");
	
				case BBS_TYPE_CDROM:
					if(BBS_TYPE_CDROM == info->DeviceType)
						EfiStrCpy(String, L"CDROM");
	
					if((index < 17) && (index > 0)) {
						_CreateDriveString(String, HDDInfo[(index-1)/2].IdentifyDrive[(index-1)%2].Raw);
					}
					break;
		
				case BBS_TYPE_EMBEDDED_NETWORK:
					EfiStrCpy(String, L"Network");
					break;
		
				case BBS_TYPE_DEV:
					EfiStrCpy(String, L"BEV Device");
					break;
		
				case BBS_TYPE_UNKNOWN:
				default:
					EfiStrCpy(String, L"Unknown");
					break;
			}
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSLaunchDevicePath
//
// Description:	function to launch the device path
//
// Input:		EFI_DEVICE_PATH_PROTOCOL *DevicePath
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BBSLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath )
{
	EFI_STATUS Status;

	Status = _BBSInitProtocol();

	if ( EFI_ERROR( Status ) )
		return Status;

	// Performance measurement Pause
	PERF_END (0, AMITSE_TEXT("Boot"), NULL, 0);

	Status = gLegacyBios->LegacyBoot( gLegacyBios, (BBS_BBS_DEVICE_PATH *)DevicePath, 0, NULL );

	// Performance measurement continue
	PERF_START (0, AMITSE_TEXT("Boot"), NULL, 0);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSUpdateBootData
//
// Description:	function to update boot related data
//
// Input:		UINT16 GroupNo
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSUpdateBootData(UINT16 GroupNo)
{
    UINTN i,j;
    BOOT_DATA *bootData;

    for( j=0,i=0; i<gBootOptionCount; i++ )
    {
        bootData = &(gBootData[i]);
		 //EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
		if(gLoadOptionHidden && (bootData->Active & LOAD_OPTION_HIDDEN))
		   continue;

        if ( BBSValidDevicePath(bootData->DevicePath) )
        {
            if(GroupNo == j)
            {
                gCurrLegacyBootData = bootData;
                break;
            }
            j++;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSGetOptionName
//
// Description:	function to get the name of the option
//
// Input:		UINT16 *Option, UINT16 Pos
//
// Output:		string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *BBSGetOptionName( UINT16 *Option, UINT16 Pos  )
{
	UINT16 count;
	BBS_ORDER_LIST *BBSList;

    BBSList = gCurrLegacyBootData->OrderList;
    count = gCurrLegacyBootData->LegacyDevCount;
	
	if(count <= Pos)
	  return( L"");

    if( Option != NULL )
        *Option=(BBSList+Pos)->Index;

	if ( BBSList != NULL )
  	  return (BBSList+Pos)->Name;

	return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BBSCheckDisabled
//
// Description:	function to check whether a perticular entry is disabled.
//
// Input:		UINT16 *Option, UINT16 Pos
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _BBSCheckDisabled( BBS_TABLE *BbsEntry )
{
    EFI_STATUS	Status;
    EFI_HANDLE	Handle;
    UINTN		i,size = 0;
    EFI_GUID	BootManGuid = BOOT_MANAGER_GUID;
    EFI_DEVICE_PATH_PROTOCOL	*dpp = NULL, *NvramDP = NULL, *TmpNvramDP;

    Handle = *(VOID**)(&BbsEntry->IBV1);

    if (Handle == 0)
        return TRUE;

    Status = gBS->HandleProtocol(Handle, &gEfiDevicePathProtocolGuid, (void**)&dpp);

    if(EFI_ERROR(Status))
        return TRUE;

    TmpNvramDP = NvramDP = (EFI_DEVICE_PATH_PROTOCOL *)VarGetNvramName(L"DisabledDevs", &BootManGuid, NULL, &size);

    if(NULL == NvramDP)
        return FALSE;

    for(i=0;i<size;)
    {
        if(EfiDevicePathSize(TmpNvramDP) == EfiDevicePathSize(dpp))
        {
            if(!MemCmp((UINT8 *)TmpNvramDP, (UINT8 *)dpp, EfiDevicePathSize(TmpNvramDP)))
                break;
        }
        i+= EfiDevicePathSize(TmpNvramDP);
        TmpNvramDP = (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *)NvramDP) + i );
    }

    MemFreePointer((VOID **) &NvramDP);

    if(i<size)
        return TRUE;

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSSetDisabled
//
// Description:	function to disable a perticular entry.
//
// Input:		UINT16 Index, VOID **DisDPs, UINTN *DPSize
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSSetDisabled(UINT16 Index, VOID **DisDPs, UINTN *DPSize)
{
    EFI_STATUS	Status;
    EFI_HANDLE	Handle;
   	UINT16		HDDCount = 0, BBSCount = 0;

	HDD_INFO *HDDInfo = NULL;
	BBS_TABLE *BBSInfo = NULL;
    EFI_DEVICE_PATH_PROTOCOL    *dpp = NULL;

   	Status = _BBSInitProtocol();
	if ( EFI_ERROR( Status ) )
		return;

	Status = gLegacyBios->GetBbsInfo(
										gLegacyBios,
										&HDDCount,
										&HDDInfo,
										&BBSCount,
										&BBSInfo
									);

    Handle = *(VOID**)(&(BBSInfo[Index].IBV1));
    if (Handle)
    {
        Status = gBS->HandleProtocol(Handle, &gEfiDevicePathProtocolGuid, (void**)&dpp);
        if(!EFI_ERROR(Status))
        {
            *DisDPs = MemReallocateZeroPool(*DisDPs, *DPSize, *DPSize + EfiDevicePathSize(dpp));
            MemCopy( ((UINT8 *)*DisDPs)+*DPSize, dpp, EfiDevicePathSize(dpp));
            *DPSize += EfiDevicePathSize(dpp);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetBBSBootOptionName
//
// Description:	function to get the Boot option name.
//
// Input:		BOOT_DATA *bootData
//
// Output:		CHAR16* - BootOptionName
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16 *GetBBSBootOptionName( BOOT_DATA *bootData)
{
    UINT16	offset = 0, count = 0, i;
    UINT8	*pDevOrder;
    UINTN	size = 0;
    BBS_ORDER_LIST	*BBSList = NULL;
    BBS_ORDER_TABLE	*pDev;

    BBSList = bootData->OrderList;
    count = bootData->LegacyDevCount;
    offset = (UINT16)bootData->LegacyEntryOffset;

	pDevOrder = HelperGetVariable(VARIABLE_ID_BBS_ORDER,L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size);
	//EIP-75352 Suppress the warnings from static code analyzer
	if(NULL == pDevOrder)
		return NULL;
	
    if (IsBootOptionsGroupingEnabled ())
    {
		pDev = (BBS_ORDER_TABLE *)(pDevOrder + offset); //EIP-81402

		if ( (pDev->Length >= size) || (0 == pDev->Length) ) //EIP-120011
			return NULL;

        if (DISABLED_BOOT_OPTION == pDev->Data[0])  //For grouping only test for disable option
        {
            return  gBBSDisabled;
        }  
		
		for(i=0; i<count; i++)
		{
			if(BBSList[i].Index == pDev->Data[0])
				break;
		}
		if(i<count)
			return BBSList[i].Name;
	}
	else //EIP-81402 If GROUP_BOOT_OPTIONS_BY_TAG == 0 then retrun name
	{
		return BBSList->Name;
	}

    return bootData->Name;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsBBSDevicePath
//
// Description:	function to check for bbs device path support.
//
// Input:		EFI_DEVICE_PATH_PROTOCOL *DevicePath
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsBBSDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath )
{
	return (BOOLEAN)(
			( DevicePathType( DevicePath ) == BBS_DEVICE_PATH ) &&
			( DevicePathSubType( DevicePath ) == BBS_BBS_DP )
			);
}

//EIP-93797 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetBBSOptionStatus
//
// Description:	function to get for bbs option status
//
// Input:		BOOT_DATA
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN GetBBSOptionStatus(BOOT_DATA *pBootData)
{
	UINT32 offset=0;
	UINT8 *pDevOrder;
	BBS_ORDER_TABLE	*pDev;
	UINTN size = 0;
	
 	offset = (UINT16)pBootData->LegacyEntryOffset;

  	pDevOrder = HelperGetVariable(VARIABLE_ID_BBS_ORDER,L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size);

 	pDev = (BBS_ORDER_TABLE *)(pDevOrder + offset);

	if ( (pDev->Length >= size) || (0 == pDev->Length) ) //EIP-120011
		return TRUE;

	//if(((UINT8)pDev->Data[0] == (pBootData->OrderList->Index))&&(BBS_ORDER_DISABLE_MASK == (UINT8)((pDev->Data[0])>>8)))
	if(pDev->Data[0] & BBS_ORDER_DISABLE_MASK)
	{
		 MemFreePointer((VOID **) &pDevOrder);
		    return  TRUE;
	}
	else
	{
		 MemFreePointer((VOID **) &pDevOrder);
    		return  FALSE;
	}
}
//EIP-93797 Ends

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
