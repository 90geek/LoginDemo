//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

#include <SetupPlatform.h>

extern EFI_GUID mSystemConfigurationGuid;

//AptioV Server Override Start: To fix ASSERT issue when supported language is changed.
EFI_STATUS HiiLibGetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, 
	IN OUT UINTN *StringSize, OUT EFI_STRING String
);
EFI_STATUS HiiLibSetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, IN EFI_STRING String
);

//AptioV Server Override End: To fix ASSERT issue when supported language is changed.

#define MSR_IA32_MISC_ENABLE 0x1A0
/* AptioV server Override - Commented declaration.Available in SetupPlatform.h
typedef struct {
    UINT8 ProcessorEistEnable;
    UINT8 TurboMode;
    UINT8 ProcessorEistPsdFunc;
    UINT8 BootPState;
    UINT8 PackageCState;
    UINT8 C3Enable;
    UINT8 C6Enable;
    UINT8 TStateEnable;
} PWR_MGT_CUST_CONFIG;
*/

VOID AmiCollectSupportedFeatures()
{
    AMI_SETUP_SUPPORTED_FEATURES Supported;
    UINT64 MsrValue;
    UINT32 RegEax;
    UINT32 RegEbx;
    UINT32 RegEcx;
    EFI_STATUS Status;

    AsmCpuidEx(0xb, 0, NULL, &RegEbx, NULL, NULL);
    Supported.Ht = (UINT8)RegEbx > 1;
    
    AsmCpuid(1, NULL, NULL, &RegEcx, NULL);
    Supported.Vmx = !!(RegEcx & BIT5);
    Supported.Smx = !!(RegEcx & BIT6);

    AsmCpuid(6, &RegEax, NULL, NULL, NULL);
    MsrValue = AsmReadMsr64(MSR_IA32_MISC_ENABLE);
    Supported.Turbo = RegEax & BIT1 || MsrValue & BIT38;

    Status = gRT->SetVariable(
            L"AmiSetupSupportedFeatures",
            &mSystemConfigurationGuid,
            EFI_VARIABLE_BOOTSERVICE_ACCESS,
            sizeof(Supported),
            &Supported
    );
    ASSERT_EFI_ERROR(Status);
}

VOID AmiPowerMgtCallback(IN OUT EFI_IFR_TYPE_VALUE *Value)
{
    BOOLEAN HiiStatus;
    EFI_STATUS Status;
    SYSTEM_CONFIGURATION SystemConfiguration;
    UINTN SysConfSize = sizeof(SYSTEM_CONFIGURATION);
    
    HiiStatus = HiiGetBrowserData (&gEfiSetupVariableGuid, L"IntelSetup", SysConfSize, (UINT8*)&SystemConfiguration);
    ASSERT(HiiStatus);
    if (!HiiStatus) return;

    if (SystemConfiguration.CpuPm == 2) {   //If previous was custom.
        PWR_MGT_CUST_CONFIG Config;
        
        if (Value->u8 == 2) return; //Change from custom to custom. Not sure if this branch is possible.

        //Save configuration values.
        Config.ProcessorEistEnable = SystemConfiguration.ProcessorEistEnable;
        Config.TurboMode = SystemConfiguration.TurboMode;
        Config.ProcessorEistPsdFunc = SystemConfiguration.ProcessorEistPsdFunc;
        Config.BootPState = SystemConfiguration.BootPState;
        Config.PackageCState = SystemConfiguration.PackageCState;
        Config.C3Enable = SystemConfiguration.C3Enable;
        Config.C6Enable = SystemConfiguration.C6Enable;
        Config.TStateEnable = SystemConfiguration.TStateEnable;
    
        Status = gRT->SetVariable(
                L"PwrMgtCustConfig",
                &mSystemConfigurationGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                sizeof(PWR_MGT_CUST_CONFIG),
                &Config
        );
        ASSERT_EFI_ERROR(Status);
    }
    
    if (Value->u8 == 0) {  //Disabled
        SystemConfiguration.ProcessorEistEnable = 0;
        SystemConfiguration.TurboMode = 0;
        SystemConfiguration.ProcessorEistPsdFunc = 0;
        SystemConfiguration.BootPState = 0;     //Set to max boot -- Question is suppressed.
        SystemConfiguration.PackageCState = 0;
        SystemConfiguration.C3Enable = 0;
        SystemConfiguration.C6Enable = 0;
        SystemConfiguration.TStateEnable = 0;
    } else if (Value->u8 == 1) {    //Enabled
        SystemConfiguration.ProcessorEistEnable = 1;
        SystemConfiguration.TurboMode = 1;
        SystemConfiguration.ProcessorEistPsdFunc = 0;
        SystemConfiguration.BootPState = 0;     //Set to max boot -- Question is suppressed.
        SystemConfiguration.PackageCState = 3;  //C6 retention
        SystemConfiguration.C3Enable = 0;
        SystemConfiguration.C6Enable = 1;
        SystemConfiguration.TStateEnable = 1;
    } else {    //Custom
        PWR_MGT_CUST_CONFIG Config;
        UINTN DataSize = sizeof(PWR_MGT_CUST_CONFIG);

        Status = gRT->GetVariable(
                L"PwrMgtCustConfig",
                &mSystemConfigurationGuid,
                NULL,
                &DataSize,
                &Config
        );        
        if (EFI_ERROR(Status)) {
            SystemConfiguration.ProcessorEistEnable = 1;
            SystemConfiguration.TurboMode = 1;
            SystemConfiguration.ProcessorEistPsdFunc = 0;
            SystemConfiguration.BootPState = 0;     //Set to max boot -- Question is suppressed.
            SystemConfiguration.PackageCState = 3;  //C6 retention
            SystemConfiguration.C3Enable = 0;
            SystemConfiguration.C6Enable = 1;
            SystemConfiguration.TStateEnable = 1;
        } else {
            SystemConfiguration.ProcessorEistEnable = Config.ProcessorEistEnable;
            SystemConfiguration.TurboMode = Config.TurboMode;
            SystemConfiguration.ProcessorEistPsdFunc = Config.ProcessorEistPsdFunc;
            SystemConfiguration.BootPState = Config.BootPState;
            SystemConfiguration.PackageCState = Config.PackageCState;
            SystemConfiguration.C3Enable = Config.C3Enable;
            SystemConfiguration.C6Enable = Config.C6Enable;
            SystemConfiguration.TStateEnable = Config.TStateEnable;
        }
    }

    HiiStatus = HiiSetBrowserData(&gEfiSetupVariableGuid, L"IntelSetup", SysConfSize, (UINT8*)&SystemConfiguration, NULL);
    ASSERT(HiiStatus);
}

VOID UpdateNumCoresSetupQuestion(EFI_HII_PACKAGE_HEADER *IfrPackagePtr)
{
    UINT8 *EndPtr = (UINT8*)IfrPackagePtr + IfrPackagePtr->Length;
    EFI_IFR_OP_HEADER *IfrOpHdr = (EFI_IFR_OP_HEADER *)(IfrPackagePtr + 1);

    UINT32 Eax, Ebx, Ecx, Edx;
    UINT8  CoreThreadCount;
    UINT8  TotalThreadCount;
    UINT8  CoreCount;
    
    ASSERT(IfrOpHdr->OpCode == EFI_IFR_FORM_SET_OP);
    ASSERT(CompareGuid((GUID *)&((EFI_IFR_FORM_SET *) IfrOpHdr)->Guid, &mSystemConfigurationGuid) == TRUE);
    
    //Platform requirement is all physical CPUs must have the same max core count.
    AsmCpuidEx(0xb, 1, &Eax, &Ebx, &Ecx, &Edx);
    TotalThreadCount = (UINT8) Ebx;
        
    AsmCpuidEx(0xb, 0, &Eax, &Ebx, &Ecx, &Edx);
    CoreThreadCount = (UINT8)Ebx;
    CoreCount = (UINT8) (TotalThreadCount / CoreThreadCount);
    
    IfrOpHdr = (EFI_IFR_OP_HEADER *)((UINT8*)IfrOpHdr + IfrOpHdr->Length);
    
    for ( ;(UINT8*)IfrOpHdr < EndPtr; IfrOpHdr = (EFI_IFR_OP_HEADER *)((UINT8*)IfrOpHdr + IfrOpHdr->Length)) {
        EFI_IFR_NUMERIC *NumericOpHdr;
        if (IfrOpHdr->OpCode != EFI_IFR_NUMERIC_OP) continue;

        NumericOpHdr = (EFI_IFR_NUMERIC*)IfrOpHdr;

        //0x2850 is for socket 0 to 0x2851 for socket 1.
        if (NumericOpHdr->Question.QuestionId < 0x2850 || NumericOpHdr->Question.QuestionId > (0x2850 + NUMBER_CPU_SOCKETS - 1)) continue;
        
        ASSERT((NumericOpHdr->Flags & EFI_IFR_NUMERIC_SIZE) == EFI_IFR_NUMERIC_SIZE_1);  //Code assumes byte.
        NumericOpHdr->data.u8.MaxValue = CoreCount;

        if (NumericOpHdr->Question.QuestionId - 0x2850 == (NUMBER_CPU_SOCKETS - 1)) break;  //All questions fixed up?
    }

    ASSERT((UINT8*)IfrOpHdr < EndPtr);  //Assert if question not found.
}

#define MAX_STR_STR_CORE_ENABLE_HELP_SIZE 70

VOID SetNumCoresSetupQuestionHelpStr()
{
    UINT32 Eax, Ebx, Ecx, Edx;
    UINT8  CoreThreadCount;
    UINT8  TotalThreadCount;
    UINT8  CoreCount;
    CHAR16 NewString[MAX_STR_STR_CORE_ENABLE_HELP_SIZE];
//AptioV Server Override Start: To fix ASSERT issue when supported language is changed.
    CHAR16 HelpString[MAX_STR_STR_CORE_ENABLE_HELP_SIZE];
    UINTN  StringSize = MAX_STR_STR_CORE_ENABLE_HELP_SIZE * sizeof (CHAR16);
    EFI_STATUS Status;
//AptioV Server Override End: To fix ASSERT issue when supported language is changed.

    //Platform requirement is all physical CPUs must have the same max core count.
    AsmCpuidEx(0xb, 1, &Eax, &Ebx, &Ecx, &Edx);
    TotalThreadCount = (UINT8) Ebx;
        
    AsmCpuidEx(0xb, 0, &Eax, &Ebx, &Ecx, &Edx);
    CoreThreadCount = (UINT8)Ebx;
    CoreCount = (UINT8) (TotalThreadCount / CoreThreadCount);
//AptioV Server Override Start: To fix ASSERT issue when supported language is changed.
    Status = HiiLibGetString (mAdvancedHiiHandle, STRING_TOKEN(STR_CORE_ENABLE_HELP), &StringSize, HelpString);
    if (!EFI_ERROR(Status)) {
        UnicodeSPrint(NewString, sizeof(CHAR16) * MAX_STR_STR_CORE_ENABLE_HELP_SIZE, HelpString, CoreCount);
        HiiLibSetString(mAdvancedHiiHandle, STRING_TOKEN(STR_CORE_ENABLE_HELP), NewString);
    }
//AptioV Server Override End: To fix ASSERT issue when supported language is changed.
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
