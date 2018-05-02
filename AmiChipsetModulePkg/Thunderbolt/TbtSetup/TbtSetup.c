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
/** @file TbtSetup.c
    Intel Thunderbolt Setup Routines

**/
//**********************************************************************
//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Guid/AmiTbtHrStatus.h>
#include <TbtCommon.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)
static EFI_GUID gAmiTbtHrStatusGuid = AMI_TBT_HR_STATUS_GUID;
static EFI_GUID gEfiSetupGuid       = SETUP_GUID;
// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

/**
    This function will initial all Thunderbolt setup strings
    
    @param[in] HiiHandle 
    @param[in] Class

    @retval VOID

**/
VOID InitTbtInfoStrings(IN EFI_HII_HANDLE HiiHandle, IN UINT16 Class)
{
    EFI_STATUS              Status;
    UINTN                   HRStatusSize     = sizeof(AMI_TBT_HR_STATUS_DATA);
    CHAR16                  TbtHRStatusVar[] = TBT_HR_STATUS_VARIABLE;
    AMI_TBT_HR_STATUS_DATA  HRStatusData;
    CHAR16                  *TbtCR           = L"Cactus Ridge";
    CHAR16                  *TbtRR           = L"Redwood Ridge";
    CHAR16                  *TbtFR           = L"Falcon Ridge";
    CHAR16                  *TbtWR           = L"BDW-TBT-LP(WR)";

    Status = pRS->GetVariable( L"TbtHRStatusVar", \
                               &gAmiTbtHrStatusGuid, \
                               NULL, \
                               &HRStatusSize, \
                               &HRStatusData );
    TRACE((-1, "TbtSetup: HR is %x series\n", HRStatusData.TbtHRSeries));

    InitString(HiiHandle, STRING_TOKEN(STR_TBT_RC_VERSION_VALUE),
                  L"%d.%d", TBT_RC_VERSION/100, TBT_RC_VERSION%100);

    if (HRStatusData.TbtHRSeries == Cactus_Ridge){
        InitString(HiiHandle, STRING_TOKEN(STR_TBT_SPEC_VERSION_VALUE),
                                  L"%d.%d", Thunderbolt_CR_VERSION/10, Thunderbolt_CR_VERSION%10);

        InitString(HiiHandle, STRING_TOKEN(STR_TBT_HOST_VALUE),
                                  L"%s", TbtCR);
    } else if (HRStatusData.TbtHRSeries == Redwood_Ridge) {
        InitString(HiiHandle, STRING_TOKEN(STR_TBT_SPEC_VERSION_VALUE),
                                  L"%d.%d", Thunderbolt_RR_VERSION/10, Thunderbolt_RR_VERSION%10);

        InitString(HiiHandle, STRING_TOKEN(STR_TBT_HOST_VALUE),
                                  L"%s", TbtRR);
    } else if (HRStatusData.TbtHRSeries == Falcon_Ridge){
        InitString(HiiHandle, STRING_TOKEN(STR_TBT_SPEC_VERSION_VALUE),
                      L"%d.%d", Thunderbolt_FR_VERSION/10, Thunderbolt_FR_VERSION%10);

        InitString(HiiHandle, STRING_TOKEN(STR_TBT_HOST_VALUE),
                      L"%s", TbtFR);
    } else {
        InitString(HiiHandle, STRING_TOKEN(STR_TBT_SPEC_VERSION_VALUE),
                      L"%d.%d", Thunderbolt_WR_VERSION/10, Thunderbolt_WR_VERSION%10);

        InitString(HiiHandle, STRING_TOKEN(STR_TBT_HOST_VALUE),
                      L"%s", TbtWR);
    }
}

/**
    This function is for Setup callback to adjust setup item dynamic
    
    @param[in] HiiHandle 
    @param[in] Class
    @param[in] SubClass
    @param[in] Key

    @retval VOID

**/
EFI_STATUS
EFIAPI
TbtSetupItemsCallback (
    IN EFI_HII_HANDLE HiiHandle,
    IN UINT16         Class,
    IN UINT16         SubClass,
    IN UINT16         Key)
{
    EFI_STATUS            Status         = EFI_SUCCESS;
    CALLBACK_PARAMETERS   *pCallbackData = NULL;
    SETUP_DATA            *SetupData     = NULL;
    UINTN                 BufferSize     = sizeof(SETUP_DATA);
    UINT8                 SetBrowserData = 0;
    
    TRACE((-1, "TbtSetupItemsCallback Entry !!!\n"));
    
    pCallbackData = GetCallbackParameters();
    if (pCallbackData == NULL) return EFI_UNSUPPORTED;
    
    // For setup item load default case
    if(pCallbackData->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) return EFI_UNSUPPORTED;
    
    TRACE((-1, "TBT Browser action %x\n", pCallbackData->Action));
    Status = pBS->AllocatePool(EfiBootServicesData, BufferSize, &SetupData);
    if (EFI_ERROR(Status)) return Status;
            
    Status = HiiLibGetBrowserData( &BufferSize, SetupData, &gEfiSetupGuid, L"Setup" );
    if (EFI_ERROR(Status)) return Status;

    if((pCallbackData->Action == EFI_BROWSER_ACTION_CHANGED) || (pCallbackData->Action == EFI_BROWSER_ACTION_CHANGING)){
        switch (Key) {
            case KEY_TBT_LOCATION_GROUP_H:
            case KEY_TBT_LOCATION_GROUP:
                TRACE((-1, "TBT Browser action : New Location Group %x\n", pCallbackData->Value->u8));
                switch(pCallbackData->Value->u8){
                    case 0x00:
                        TRACE((-1, "TBT Browser action : Change TBT host to SB PCIE slot\n"));
                        SetupData->TbtHostLocation = SetupData->TbtHostTempLocationSB;
                        SetBrowserData |= 1;
                        break;
                    case 0x01:
                        TRACE((-1, "TBT Browser action : Change TBT host to CPU0 NB PCIE slot\n"));
                        SetupData->TbtHostLocation = SetupData->TbtHostTempLocationNB0;
                        SetBrowserData |= 1;
                        break;
                    case 0x02:
                        TRACE((-1, "TBT Browser action : Change TBT host to CPU1 NB PCIE slot\n"));
                        SetupData->TbtHostLocation = SetupData->TbtHostTempLocationNB1;
                        SetBrowserData |= 1;
                        break;
                    case 0x03:
                        TRACE((-1, "TBT Browser action : Change TBT host to CPU2 NB PCIE slot\n"));
                        SetupData->TbtHostLocation = SetupData->TbtHostTempLocationNB2;
                        SetBrowserData |= 1;
                        break;
                    case 0x04:
                        TRACE((-1, "Browser action : Change TBT host to CPU3 NB PCIE slot\n"));
                        SetupData->TbtHostLocation = SetupData->TbtHostTempLocationNB3;
                        SetBrowserData |= 1;
                        break;
                } // end switch TbtHostLocationGroup
                break;
            case KEY_TBT_LOCATION_SB:
            case KEY_TBT_LOCATION_NB0H:
            case KEY_TBT_LOCATION_NB0:
            case KEY_TBT_LOCATION_NB1:
            case KEY_TBT_LOCATION_NB2:
            case KEY_TBT_LOCATION_NB3:
                TRACE((-1, "TBT Browser action : New Location:%x of Location Group %x\n", pCallbackData->Value->u8, SetupData->TbtHostLocationGroup));
                SetupData->TbtHostLocation = pCallbackData->Value->u8;
                SetBrowserData |= 1;
                break;
        } // end switch key
    } // EFI_BROWSER_ACTION_CHANGING and EFI_BROWSER_ACTION_CHANGED

    if (SetBrowserData != 0){
        Status = HiiLibSetBrowserData( BufferSize, SetupData, &gEfiSetupGuid, L"Setup" );
        TRACE((-1, "Update TBT Setup Browser Data... %r \n", Status));
    }
    
    pBS->FreePool(SetupData);
    
    return Status;
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
