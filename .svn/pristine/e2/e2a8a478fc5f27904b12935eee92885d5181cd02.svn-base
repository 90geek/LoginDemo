//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file SmbiosPei.c
    This file provides function to update "Wake-up Type"
    data field in Smbios Type 1 structure

**/

#include <AmiPeiLib.h>
#include <Protocol\AmiSmbios.h>
#include <Ppi\ReadOnlyVariable2.h>
#include <Ppi\MemoryDiscovered.h>
// Aptiov server override start
#include <Library\HobLib.h>
#include <Hob.h>
#include <Guid\TcgDataHob.h>
// Aptiov server override end
//extern VOID		OemRuntimeShadowRamWrite(IN BOOLEAN Enable);
//extern UINT8	getWakeupTypeForSmbios(VOID);  // Aptiov server override
extern VOID     NbRuntimeShadowRamWrite(IN BOOLEAN Enable);
UINT8    getWakeupTypeForSmbios(VOID);  // Aptiov server override

EFI_STATUS
SmbiosAfterInitMemory(
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *NullPpi
);

static EFI_GUID gPeiPermanentMemInstalledPpiGuid = EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI_GUID;

static EFI_PEI_NOTIFY_DESCRIPTOR SmbiosPeiNotify[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiPermanentMemInstalledPpiGuid,
        SmbiosAfterInitMemory
    }
};

/**
    Detect and update SMBIOS Type 1 structure "Wake-up Type"
    data field

    @param PeiServices

    @retval VOID Updated SMBIOS Type 1 "Wake-up Type"

**/
VOID
UpdateSmbiosWakeupType(
    IN EFI_PEI_SERVICES **PeiServices
)
{
    EFI_STATUS                          Status;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable;
    UINTN                               DataSize = 4;
    UINT32                              WakeupTypePtr;

    Status = (*PeiServices)->LocatePpi(
                                        PeiServices,
                                        &gEfiPeiReadOnlyVariable2PpiGuid,
                                        0,
                                        NULL,
                                        &ReadOnlyVariable);
    ASSERT_PEI_ERROR(PeiServices, Status);

    if (Status == EFI_SUCCESS){
        Status = ReadOnlyVariable->GetVariable(
                                        ReadOnlyVariable,
                                        L"WakeUpType",
                                        &gAmiSmbiosNvramGuid,
                                        NULL,
                                        &DataSize,
                                        &WakeupTypePtr);
        ASSERT_PEI_ERROR(PeiServices, Status);

        PEI_TRACE((-1, PeiServices, "WakeupType location: %x", WakeupTypePtr));

        if (Status == EFI_SUCCESS) {
            if (WakeupTypePtr > 0xf0000) {
                *(UINT8*)WakeupTypePtr = getWakeupTypeForSmbios();
            }
            else {
//                OemRuntimeShadowRamWrite(TRUE);
                NbRuntimeShadowRamWrite(TRUE);
                *(UINT8*)WakeupTypePtr = getWakeupTypeForSmbios();
//                OemRuntimeShadowRamWrite(FALSE);
                NbRuntimeShadowRamWrite(FALSE);
            }
        }
    }
}

// Aptiov server override start
#if SMBIOS_SUPPORT && SB_WAKEUP_TYPE_FN
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: getWakeupTypeForSmbios
//
// Description: Detect and return SMBIOS wake-up type
//
// Input:  None
//
// Output: 0x01 = Other
//         0x02 = Unknown
//         0x03 = APM Timer
//         0x04 = Modem Ring
//         0x05 = LAN Remote
//         0x06 = Power Switch
//         0x07 = PCI PME#
//         0x08 = AC Power Retored
//
// Notes: Porting required 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
getWakeupTypeForSmbios (VOID)
{
	   UINTN           *GuidHob;
	   UINT8           *GuidHobData;
	   GuidHob  = GetFirstGuidHob (&gEfiTcgWakeEventDataHobGuid);
	   GuidHobData=GET_GUID_HOB_DATA (GuidHob);
	   
	   return *GuidHobData ;
}
#endif
// Aptiov server override end
/**

    @param PeiServices
    @param NotifyDescriptor
    @param NullPpi

    @retval EFI_STATUS Status

**/
EFI_STATUS
SmbiosAfterInitMemory(
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *NullPpi
)
{
    EFI_STATUS Status;
    EFI_BOOT_MODE BootMode;

    // Determine boot mode
    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);

    if (BootMode == BOOT_ON_S3_RESUME) {
        UpdateSmbiosWakeupType(PeiServices);
    }

    return EFI_SUCCESS;
}

/**
    Driver entry point for SmbiosPei

    @param FfsHeader
    @param PeiServices

    @retval EFI_STATUS Status

**/
EFI_STATUS
SmbiosPeiEntryPoint(
	IN EFI_FFS_FILE_HEADER       *FfsHeader,
  	IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS Status;

    // Set the Smbios Notify PPI
    Status = (*PeiServices)->NotifyPpi(PeiServices, SmbiosPeiNotify);
    ASSERT_PEI_ERROR(PeiServices, Status);

	return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
