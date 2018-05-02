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
// $Header: /Alaska/Tools/template.c 6     1/13/10 2:13p Felixp $
//
// $Revision: 6 $
//
// $Date: 1/13/10 2:13p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Tools/template.c $
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
/** @file TbtSetupReset.c
    Setup Reset Rountines

**/
//**********************************************************************

#include <Token.h>
#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCSPLib.h>
#include <Guid/AmiTbtHrStatus.h>
#include <Library/TbtOemLib.h>
#include <TbtCommon.h>

//----------------------------------------------------------------------------
// GUID Definition(s)
//----------------------------------------------------------------------------
static EFI_GUID              gEfiSetupGuid = SETUP_GUID;
static EFI_GUID              gAmiTbtHrStatusGuid = AMI_TBT_HR_STATUS_GUID;

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
static SETUP_DATA            gNewSetupData;
static SETUP_DATA            gOldSetupData;

UINTN                        HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
AMI_TBT_HR_STATUS_DATA       HRStatusData;

/**
    This function is a hook called when TSE determines
    that it has to load the boot options in the boot
    order. This function is available as ELINK.

    @param VOID

    @retval VOID

**/
VOID TbtProcessEnterSetup(VOID)
{
    EFI_STATUS              Status;
    UINTN                   VariableSize = sizeof (SETUP_DATA);
    UINT8                   SecurityLevelState;

    TRACE((-1, "TbtSetupReset.c: TbtProcessEnterSetup()...\n"));
    Status = pRS->GetVariable( L"Setup", \
                               &gEfiSetupGuid, \
                               NULL, \
                               &VariableSize, \
                               &gOldSetupData );
    ASSERT_EFI_ERROR (Status);
    
    Status = pRS->GetVariable( L"TbtHRStatusVar", \
                               &gAmiTbtHrStatusGuid, \
                               NULL, \
                               &HRStatusSize, \
                               &HRStatusData );
    ASSERT_EFI_ERROR (Status);

    TRACE((-1, "Before Setup: TbtHostLocation variable is %x\n", gOldSetupData.TbtHostLocation));
    
    //
    // synchronize Thunderbolt security level config between BIOS and Thunderbolt
    // host FW
    if ((gOldSetupData.TbtEnable != 0) && (HRStatusData.TbtHRSeries != Cactus_Ridge)){
        SecurityLevelState = SynchSecurityLevel(gOldSetupData.TbtSecurityLevel, gOldSetupData.TbtHostLocation);
        TRACE((-1, "TbtSetupReset: Synchronizing Security Level between host Fw and BIOS state is %x\n", SecurityLevelState));
    }
}

/**
    This function is a hook called after some control 
    modified in the setup utility by user. This
    function is available as ELINK.

    @param VOID

    @retval VOID

**/
VOID TbtSetupResetHook(VOID)
{
    EFI_STATUS              Status;
    UINT8                   SetSecurityFlag = 0;
    UINT8                   ResetFlag = 0;
    UINTN                   VariableSize = sizeof (SETUP_DATA);
      
    TRACE((-1, "TbtSetupReset.c: TbtSetupResetHook()...\n"));
    Status = pRS->GetVariable( L"Setup", \
                               &gEfiSetupGuid, \
                               NULL, \
                               &VariableSize, \
                               &gNewSetupData );
    ASSERT_EFI_ERROR(Status);
    
    if ((!EFI_ERROR (Status)) && (gNewSetupData.TbtEnable != 0) && \
        (HRStatusData.TbtHRSeries != Cactus_Ridge))
    {
        TRACE((-1, "After Setup: TbtHostLocation variable is %x\n", gNewSetupData.TbtHostLocation));
        
        // Check Security Setup Setting first
        if (gNewSetupData.TbtSecurityLevel != gOldSetupData.TbtSecurityLevel){
            SetSecurityFlag |= 1;
        }
        
        // Set Reset flag to avoid ICC not enable issue
        if ((gNewSetupData.TbtAICSupport != gOldSetupData.TbtAICSupport) || (gNewSetupData.TbtHostLocation != gOldSetupData.TbtHostLocation)){
            //Set reset flag
            ResetFlag |= 1;
        }
        
        // programming Redwood Ridge's/Falcon Ridge's/Win Ridge's Security Level
        TRACE((-1, "TbtSetupReset.c: Security Level = %x\n", gNewSetupData.TbtSecurityLevel));
        if (SetSecurityFlag != 0){
            ProgramTbtSecurityLevel(&(gNewSetupData.TbtSecurityLevel), HRStatusData.TbtHRSeries, gNewSetupData.TbtHostLocation, FALSE);
            
            //Set reset flag
            ResetFlag |= 1;
        }
        
        if(ResetFlag != 0){
            //
            // Powe Cycle Reset
            //
            pRS->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
        
            EFI_DEADLOOP();
        }
    } // Get New Setup Data success && Thunderbolt Function is enable
}

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
