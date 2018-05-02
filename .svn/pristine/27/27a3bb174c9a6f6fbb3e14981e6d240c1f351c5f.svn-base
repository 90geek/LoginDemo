//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file
  Instance of AmiSmmCorePlatformHookLib for saving and restoring register context.
**/

#include <Library/SmmCorePlatformHookLib.h>
#include <SmmPlatformeLinks.h>
#include <Dxe.h>
#include <AmiDxeLib.h>

typedef VOID (PLATFORMHOOK_FOR_SMMDISPATCH_FUNCTION)(BOOLEAN SaveContext);

extern PLATFORMHOOK_FOR_SMMDISPATCH_FUNCTION PLATFORMHOOK_BEFORE_AFTER_SMMDISPATCH EndOfHookBeforeSmmDispatchFns;

PLATFORMHOOK_FOR_SMMDISPATCH_FUNCTION *HookBeforeAfterSmmDispatchFns[] = {
    PLATFORMHOOK_BEFORE_AFTER_SMMDISPATCH NULL
};


/**
  Performs platform specific tasks before invoking registered SMI handlers.
  
  This function performs platform specific tasks before invoking registered SMI handlers.
  
  @retval EFI_SUCCESS       The platform hook completes successfully.
  @retval Other values      The platform hook cannot complete due to some error.

**/

EFI_STATUS
EFIAPI
PlatformHookBeforeSmmDispatch (
  VOID
  )
{
    UINT32 i;

    for(i = 0; HookBeforeAfterSmmDispatchFns[i] != NULL; i++)
        HookBeforeAfterSmmDispatchFns[i](TRUE);

    return EFI_SUCCESS;
}


/**
  Performs platform specific tasks after invoking registered SMI handlers.
  
  This function performs platform specific tasks after invoking registered SMI handlers.
  
  @retval EFI_SUCCESS       The platform hook completes successfully.
  @retval Other values      The platform hook cannot complete due to some error.

**/
EFI_STATUS
EFIAPI
PlatformHookAfterSmmDispatch (
  VOID
  )
{
    UINT32 i;

    
    for (i = 0; HookBeforeAfterSmmDispatchFns[i] != NULL; ++i); //Count number of entries.
    for (;i > 0; --i) HookBeforeAfterSmmDispatchFns[i-1](FALSE); //Restore in reverse order.
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
