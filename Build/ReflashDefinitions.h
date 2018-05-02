//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	ReFlash.txt
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#ifdef  REFLASH_DEFINITIONS_SUPPORT
 

#endif

#define REFLASH_FUNCTION_LIST 
 
#define OEM_BEFORE_FLASH_UPDATE_CALLBACK_LIST RecoveryPreserveDmiEditData,ReflashBeforeUpdateHook,
 
#define OEM_AFTER_FLASH_UPDATE_CALLBACK_LIST RecoveryRestoreDmiEditData,ReflashAfterUpdateHook,
 

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************