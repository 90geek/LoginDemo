/** @file 
    This module allows invokes PXE Network Boot.
    
    
        (C)Copyright 1985-2013, American Megatrends, Inc. 
                       All Rights Reserved.               

**/


#include <EFI.h>
#include <Protocol/LegacyBios.h>
#include <Pci.h>
#include <AmiDxeLib.h>


extern EFI_SYSTEM_TABLE *gST; /*!< external global pointer to EFI system table */


/**
    This TSE function used to launch UEFI boot option. 
    @param  u16Option       boot option to launch
    @param  pOrder          optional pointer to option's order
    @param  u16OrderCount   boot order count
    @retval EFI_STATUS      Status code
**/
EFI_STATUS BootLaunchBootOption(UINT16 u16Option, UINT16 *pOrder, UINTN u16OrderCount);

/**
    This TSE function used to launch Legacy PXE boot option. 
    @param  DevicePath      pointer to PXE boot option
    @param  Options         pointer to options
    @param  OptionSize      size of the boot option
    @param  ValidBootOption boolean option to check the boot option
    @retval EFI_STATUS      Status code
**/
EFI_STATUS _BootLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath, VOID *Options, UINTN OptionSize, BOOLEAN ValidBootOption );


/** 
    This function checks if device path belong to PXE boot option. 
    @param  DevicePath      pointer to device path.
    @retval EFI_STATUS      Status code
**/ 
EFI_STATUS IsNetworkDevice( IN EFI_DEVICE_PATH_PROTOCOL *DevicePath )
{
    EFI_DEVICE_PATH_PROTOCOL *Dp;

    for ( Dp=DevicePath; !(isEndNode(Dp)); Dp=NEXT_NODE(Dp) ) 
        if ( Dp->Type == MESSAGING_DEVICE_PATH && Dp->SubType == MSG_MAC_ADDR_DP )
            return EFI_SUCCESS;

    return EFI_UNSUPPORTED;    
}


/** 
    This function attempts for an EFI PXE boot operation. 
    @retval EFI_STATUS      Status code
**/ 
VOID EfiPxeBoot(VOID)
{
    EFI_STATUS Status;
    EFI_GUID EfiVarGuid = EFI_GLOBAL_VARIABLE;
    UINT16 *pBootOrder = NULL;
    UINTN  BootOrderSize = 0;
    UINT16 Index;
    UINTN  Size;
    EFI_LOAD_OPTION *pBootOption = NULL;
    CHAR16 Name[10] = {0};
    CHAR16 *DescriptionStr = NULL;
    EFI_DEVICE_PATH_PROTOCOL *DevicePathNode = NULL;

    Status = GetEfiVariable( L"BootOrder", &EfiVarGuid, NULL, &BootOrderSize, &pBootOrder );
    if (EFI_ERROR(Status))
        return;

    for (Index = 0; Index < BootOrderSize / sizeof(UINT16); Index++) {

        // Get next boot item variable
        Swprintf( Name, L"Boot%04X", pBootOrder[Index] );
        Size = 0;
        if (pBootOption != NULL) {
            pBS->FreePool(pBootOption);
            pBootOption = NULL;
        }
        Status = GetEfiVariable( Name, &EfiVarGuid, NULL, &Size, &pBootOption );
        if (EFI_ERROR(Status))
            continue;

        if ( !(pBootOption->Attributes & LOAD_OPTION_ACTIVE) ) // skip disabled item
            continue;

        // Get device path pointer
        DescriptionStr = (CHAR16*)(pBootOption + 1);
        DevicePathNode = (EFI_DEVICE_PATH_PROTOCOL*)( DescriptionStr + Wcslen(DescriptionStr) + 1 );

        // Check device path
        Status = IsNetworkDevice(DevicePathNode);
        if (!EFI_ERROR(Status)) {

            // Call TSE function to launch the EFI PXE boot option 
            TRACE((TRACE_ALWAYS,"Launch the EFI PXE boot option %S (%S)...\n",Name,DescriptionStr));
            Status = BootLaunchBootOption( pBootOrder[Index], NULL, 0 );
            TRACE((TRACE_ALWAYS,"...%S Status=%r\n",Name,Status));
        }
    }
    pBS->FreePool(pBootOption);
    pBS->FreePool(pBootOrder);
}


/** 
    This function attempts for a Legacy PXE boot operation. 
    @retval EFI_STATUS      Status code
**/ 
EFI_STATUS LegacyPxeBoot(VOID)
{
    EFI_STATUS Status;
    EFI_GUID EfiLegacyBiosProtocolGuid = EFI_LEGACY_BIOS_PROTOCOL_GUID;
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios = NULL;
    HDD_INFO *HddInfo = NULL;
    BBS_TABLE *BbsTable = NULL;
    UINT16 HddCount = 0;
    UINT16 BbsCount = 0;
    static struct {
        BBS_BBS_DEVICE_PATH bbs;
        EFI_DEVICE_PATH_PROTOCOL end;
    } LegacyDp = {
        { {BBS_DEVICE_PATH, BBS_BBS_DP, sizeof(BBS_BBS_DEVICE_PATH)}, BBS_EMBED_NETWORK, 0, 0 },
        {END_DEVICE_PATH, END_ENTIRE_SUBTYPE, sizeof(EFI_DEVICE_PATH_PROTOCOL)} 
    };
    UINT16 Index, i, x;
    UINT16 Priority; 

    // Locate legacy BIOS protocol
    Status = gST->BootServices->LocateProtocol( 
        &EfiLegacyBiosProtocolGuid, 
        NULL, 
        &LegacyBios 
    );
    if (EFI_ERROR(Status))
        return Status;

    // Get BBS information and structures
    Status = LegacyBios->GetBbsInfo( 
        LegacyBios, 
        &HddCount, 
        &HddInfo, 
        &BbsCount, 
        &BbsTable 
    );
    if (EFI_ERROR(Status))
        return Status;

    // Check is there any Network device in the BBS table
    for ( Index = 0; Index < BbsCount; Index++ ) {

        // skip items 
        if ( BbsTable[Index].BootPriority == BBS_IGNORE_ENTRY || 
             BbsTable[Index].BootPriority == BBS_DO_NOT_BOOT_FROM ) 
            continue;
    
        // check if it's search for a Network device
        if (BbsTable[Index].Class == PCI_CL_NETWORK)
            break;
    }
    if (Index == BbsCount)
        return EFI_NOT_FOUND;

    // The sinking sort
    for ( x = 0; x < BbsCount; x++ ) {

        // find a NIC with highest priority
        Priority = 0xFFFF;
        for ( i = 0; i < BbsCount; i++ ) {

            // skip items 
            if ( BbsTable[i].BootPriority == BBS_IGNORE_ENTRY || 
                 BbsTable[i].BootPriority == BBS_DO_NOT_BOOT_FROM ) 
                continue;
        
            // check if it's a next NIC
            if (BbsTable[i].Class == PCI_CL_NETWORK)
                if ( BbsTable[i].BootPriority >= x && 
                     BbsTable[i].BootPriority < Priority ) {
                    Index = i;
                    Priority = BbsTable[i].BootPriority;
                }
        }
        if (Priority == 0xFFFF)
            break;

        // Rise up the NIC priority until the 'x'
        do {  

            // increase item's priority if it's equal 'BbsTable[Index].BootPriority-1'
            for ( i = 0; i < BbsCount; i++ ) {
        
                // skip items 
                if (BbsTable[i].BootPriority >= BBS_DO_NOT_BOOT_FROM)
                    continue;
            
                if ( (BbsTable[i].BootPriority+1) == BbsTable[Index].BootPriority ) {
                    BbsTable[i].BootPriority++;
                    break;
                }
            }

            if (BbsTable[Index].BootPriority)
                BbsTable[Index].BootPriority--;
            else 
                break;

        } while(BbsTable[Index].BootPriority > x);
    }

    // Call TSE function to launch the Net Boot operation 
    TRACE((TRACE_ALWAYS,"Launch the Legacy PXE Boot...\n"));
    Status = _BootLaunchDevicePath(
        (EFI_DEVICE_PATH_PROTOCOL*)&LegacyDp,
        NULL,
        0,
        TRUE
    );

    return Status;
}


/**
    This function is a hook called when user activates
    configurable post hot key 1. This function is
    available as ELINK. Generic implementation is empty.
    OEMs may choose to use different logic here.
    @retval EFI_STATUS      Status code
**/
EFI_STATUS NetBootHotKey(VOID)
{
    EFI_STATUS Status;

    TRACE((TRACE_ALWAYS,"NetBootHotKey hook has been activated\n"));

    // Try the EFI boot option first
    EfiPxeBoot();

    // Attempt for Legacy PXE boot
    Status = LegacyPxeBoot();
    TRACE((TRACE_ALWAYS,"Legacy PXE boot Status=%r\n",Status));

    return Status;
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
