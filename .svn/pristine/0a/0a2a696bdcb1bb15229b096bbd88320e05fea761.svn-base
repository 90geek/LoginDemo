//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: $
//
// $Revision:  $
//
// $Date:  $
//*************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------
//
// Name:        NbSetup.c
//
// Description: This C file contains code related to NB setup routines
//
//-----------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Setup.h>
#include <AmiDxeLib.h>
#include <Guid/MemoryMapData.h>
#include <Library/HobLib.h>
//TH0053>>>
#include <GrantleyPkg\Include\Guid\SetupVariable.h>  
#include <Protocol\GenericElogProtocol.h>
#include <AmiGpnvErrorLoggingPkg\Include\Protocol\SmbiosElogSupport.h>
//TH0053<<<

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitNbStrings
//
// Description: Initializes North Bridge Setup String
//
// Input:       HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
InitNbStrings(
    IN EFI_HII_HANDLE      HiiHandle,
    IN UINT16              Class
)
{
	EFI_HOB_GUID_TYPE             	*GuidHob;
	struct SystemMemoryMapHob     	*SystemMemoryMap;
	UINT32							MemorySize;
  //TH0053>>>
	EFI_STATUS          			Status;
	UINT64                          RecordId;
	UINT8 Record = EFI_EVENT_LOG_TYPE_POST_MEMORY_RESIZE;   //Example for Error Type. You could modify for need.
	EFI_SM_ELOG_PROTOCOL	   		*mGenericElogProtocol = NULL;
	EFI_GUID gEfiGenericElogProtocolGuid = EFI_SM_ELOG_PROTOCOL_GUID;	
	EFI_GUID                        gEfiSetupVariableGuid = SYSTEM_CONFIGURATION_GUID;
	SYSTEM_CONFIGURATION            SystemConfiguration;
	UINT64	                        OldMemorySize = 0;
	UINTN                           VarSize;
	//TH0053<<<

	if(Class == MAIN_FORM_SET_CLASS) {

 	    GuidHob = GetFirstGuidHob (&gEfiMemoryMapGuid);
 		if (GuidHob == NULL) {
 		    return;
 		}

 	    SystemMemoryMap = (struct SystemMemoryMapHob*) GET_GUID_HOB_DATA (GuidHob);
 	    MemorySize = SystemMemoryMap->memSize << 6;  //mamory size in 1MB units

            InitString(
        		    HiiHandle,
        		    STRING_TOKEN(STR_MEMORY_SIZE_VALUE),
        		    L"%4d MB",
        		    MemorySize
            );
        }
      //TH0053>>>
    	VarSize = sizeof(SYSTEM_CONFIGURATION);
    	// AptioV Server Override: Changed variable name to IntelSetup
    	Status = pRS->GetVariable (
    					L"IntelSetup",
    					&gEfiSetupVariableGuid,
    					NULL,
    					&VarSize,
    					&SystemConfiguration
    					);
    	 
    	if ( (!EFI_ERROR(Status)) && (SystemConfiguration.OldMemorySize != 0) ) {
    		if (MemorySize != SystemConfiguration.OldMemorySize) {
    			Status = pBS->LocateProtocol (
    						&gEfiGenericElogProtocolGuid, 
    						NULL, (VOID **)&mGenericElogProtocol ); 
    
    			TRACE((-1, "[Molly] gEfiGenericElogProtocolGuid LocateProtocol Status = [%r]\n", Status));
    			if(!EFI_ERROR(Status)) {	     
    				Status = mGenericElogProtocol->SetEventLogData(
    												mGenericElogProtocol,
    												(UINT8*)&Record,
    												EfiElogSmSMBIOS,
    												FALSE,
    												sizeof(UINT8),
    												&RecordId);
    			}   	    
    		}
    	}
    
    	VarSize = sizeof(SYSTEM_CONFIGURATION);
    	SystemConfiguration.OldMemorySize = MemorySize;
    	
    	Status = pRS->SetVariable(
    					L"IntelSetup",
    					&gEfiSetupVariableGuid,
    					EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
    					VarSize,
    					&SystemConfiguration
    					);
    	//TH0053<<<
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
