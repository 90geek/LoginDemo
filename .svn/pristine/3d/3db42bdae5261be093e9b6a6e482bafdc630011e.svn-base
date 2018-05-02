//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1987-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file CpuSpSmi.c
Provides CPU MSR writes for S3 Resume.
Detailed description: This file description is OK.  File name is provided.
*/

#include <Library/SmmServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Token.h>

#if ENABLE_ERROR_INJECTOR_SUPPORT
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Guid/SetupVariable.h>
#define MC_ERR_INJ_LCK          0x790
UINT8     UnlockMsr;
#endif

#define MSR_PLATFORM_INFO               0xce
#define EFI_MSR_IA32_PERF_CTL           0x199
#define MSR_IA32_MISC_ENABLES           0x1a0
#define EIST_ENABLE_OFFSET              16
#define EIST_ENABLE                     (1 << EIST_ENABLE_OFFSET)
#define P_STATE_TARGET_MASK             (0xFFULL << 8)
#define P_STATE_TARGET_OFFSET           8

#define RESTORE_MSR_CALLBACK_GUID \
    {0x2b6487ee, 0x6d58, 0x4d83, 0x90, 0xef, 0x79, 0x50, 0xec, 0xb7, 0xd6, 0x8e}


EFI_GUID RestoreMsrCallbackGuid =  RESTORE_MSR_CALLBACK_GUID;

#define EFI_MSR_LT_CONTROL 0x2e7


/**
  Writes MSR value(s) on logical processor.
  
  This function provides a service to send and receive messages from a registered UEFI service.

  @param[in] Buffer     Pointer not used.

  @retval VOID
**/

VOID RestoreMsrOnCpu(IN VOID *Buffer)
{
    UINT32      MsrPlaformInfo;
    UINT64      Ia32MiscEnable;
    UINT64      Ia32PerfCtl;
    BOOLEAN     EistEnabled;
    UINT8       MaxNonTurboRatio;

#if ENABLE_ERROR_INJECTOR_SUPPORT
    UINT64      Data;
    if (UnlockMsr) {
        Data = AsmReadMsr64(MC_ERR_INJ_LCK);
        Data &= ~(BIT0);
        AsmWriteMsr64 (MC_ERR_INJ_LCK, Data);
    }
#endif

    AsmWriteMsr64(EFI_MSR_LT_CONTROL, BIT0);        //MSR 0x2E7


    // Read Max Not Turbo Ratio

    MsrPlaformInfo = (UINT32)AsmReadMsr64 (MSR_PLATFORM_INFO);
    MaxNonTurboRatio = (UINT8)(MsrPlaformInfo >> 8);
    
    //
	// Check whether EIST is enabled
	//
	Ia32MiscEnable = AsmReadMsr64 (MSR_IA32_MISC_ENABLES);
	EistEnabled    = (BOOLEAN)!!((UINT32)Ia32MiscEnable & EIST_ENABLE);
	
	if (!EistEnabled) {
	    Ia32MiscEnable |= EIST_ENABLE;
	    AsmWriteMsr64 (MSR_IA32_MISC_ENABLES, Ia32MiscEnable);
	}

	Ia32PerfCtl = AsmReadMsr64 (EFI_MSR_IA32_PERF_CTL);
	Ia32PerfCtl &= ~P_STATE_TARGET_MASK;
	Ia32PerfCtl |= MaxNonTurboRatio <<  P_STATE_TARGET_OFFSET;
	AsmWriteMsr64 (EFI_MSR_IA32_PERF_CTL, Ia32PerfCtl);

	//
	// Disable EIST because we might have enabled it
	//

	if (!EistEnabled) {
	    Ia32MiscEnable = AsmReadMsr64 (MSR_IA32_MISC_ENABLES);
	    Ia32MiscEnable &= ~EIST_ENABLE;
	    AsmWriteMsr64 (MSR_IA32_MISC_ENABLES, Ia32MiscEnable);
	}
}   

/**
    This function restores the CPU MSRs during S3 resume.
    @param  DispatchHandle      Not Used.
    @param  Context             Not Used.
    @param  CommBuffer          Not Used.
    @param  CommBufferSize      Not Used.

    @retval EFI_SUCCESS         Always
**/

EFI_STATUS RestoreCpuMsr (
    IN  EFI_HANDLE                  DispatchHandle,
	IN CONST VOID                   *Context OPTIONAL,
	IN OUT VOID                     *CommBuffer OPTIONAL,
	IN OUT UINTN                    *CommBufferSize OPTIONAL
)
{
    UINT32  i;

    DEBUG((-1,"Write MSR Lock Bit.\n"));
    
    for (i = 0; i < gSmst->NumberOfCpus; ++i) {
        gSmst->SmmStartupThisAp(RestoreMsrOnCpu, i, NULL);
    }
	
    RestoreMsrOnCpu(NULL);

    return EFI_SUCCESS;
}


/**
    Initializes CPU specific SMM Drivers.

    @param  ImageHandle     Not Used.
    @param  SystemTable     Not Used.

    @retval EFI_SUCCESS     Always
**/

EFI_STATUS CpuSpSmiInit(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_HANDLE  DispatchHandle;

#if ENABLE_ERROR_INJECTOR_SUPPORT
    UINTN                                           VarSize;
    SYSTEM_CONFIGURATION    SetupData;

    VarSize = sizeof(SYSTEM_CONFIGURATION);
    Status = gRT->GetVariable( 
                        L"IntelSetup",
                        &gEfiSetupVariableGuid,
                        NULL,
                        &VarSize,
                        &SetupData 
                        );
    if(EFI_ERROR(Status)) {
        SetupData.UnlockMsr = 0;
    }

    UnlockMsr = SetupData.UnlockMsr;
#endif

    Status = gSmst->SmiHandlerRegister(
        RestoreCpuMsr,
        &RestoreMsrCallbackGuid,
        &DispatchHandle
    );
    ASSERT_EFI_ERROR(Status);
    
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1987-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

