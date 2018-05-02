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
/** @file TbtDxe.c

**/
//**********************************************************************

#include <token.h>
#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <PciBus.h>
#include <Acpi20.h>
#include <Protocol/AcpiSupport.h>
#include <Protocol/AmiTbtNvs.h>
#include <Protocol/AmiTbtPlatformPolicy.h>
#include <Guid/HobList.h>
#include <Guid/AmiTbtHrStatus.h>
#include <Guid/AmiTbtHob.h>
#include <Library/AmiSdlLib.h>
#include <Library/TbtDxeLib.h>
#include <Library/TbtOemLib.h>
#include <TbtCommon.h>

#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
#include <Guid/SetupVariable.h>
#endif

#if ACPI_SUPPORT
 #include <Protocol/AcpiSystemDescriptionTable.h>
#endif

#if CSM_SUPPORT
#include <Protocol/LegacyBiosExt.h>
#endif

//----------------------------------------------------------------------------
// GUID Definition(s)
//----------------------------------------------------------------------------
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
static EFI_GUID                     SetupGuid              = SYSTEM_CONFIGURATION_GUID;
#else
static EFI_GUID                     SetupGuid              = SETUP_GUID;
#endif

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
#ifndef EFI_SIGNATURE_16
#define EFI_SIGNATURE_16(A, B)  ((A) | (B << 8))
#endif

#ifndef EFI_SIGNATURE_32
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))
#endif

AMI_TBT_PLATFORM_POLICY_PROTOCOL    *gAmiTbtPlatformPolicy = NULL;
AMI_TBT_NVS_PROTOCOL                AmiTbtNvs;
VOID                                *CsmOpromPolicyRegs;
static EFI_BOOT_MODE                BootMode;
static UINT8                        DefaultTbtLocationAslName[4];

//----------------------------------------------------------------------------
// Function Prototype Definition(s)
//----------------------------------------------------------------------------
EFI_STATUS InstallAmiTbtPlatformPolicy (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  );


/**
    This function will find Thunderbolt host default ASL name in SDL with 
    default host location 
    
    @param[in] LocationBusNum       Default thunderbolt host lcoation bus number
    @param[in] LocationDevNum       Default thunderbolt host lcoation device number
    @param[in] LocationFunNum       Default thunderbolt host lcoation function number
    @param[out] SdlAslName          returned default ASL name

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization

**/
EFI_STATUS FindDefaultTbtAslName (
    IN  UINT8   LocationBusNum,
    IN  UINT8   LocationDevNum,
    IN  UINT8   LocationFunNum,
    OUT UINT8   *SdlAslName)
{
    
    AMI_SDL_PCI_DEV_INFO    *sdltmp       = NULL;
    AMI_SDL_PCI_DEV_INFO    *sdltmpParent = NULL;
    EFI_STATUS              Status        = EFI_SUCCESS;
    UINTN                   i;
    
    //TRACE((-1, "TbtDxe: FindDefaultTbtAslName Entry\n"));
    Status=AmiSdlInitBoardInfo();
    if(EFI_ERROR(Status)) return Status;
    
    //TRACE((-1, "TbtDxe: SDL PCI Dev count = %x\n", gSdlPciData->PciDevCount));
    for(i=0; i<gSdlPciData->PciDevCount; i++){
        sdltmp = &gSdlPciData->PciDevices[i];
        sdltmpParent = &gSdlPciData->PciDevices[sdltmp->ParentIndex];
        if(sdltmpParent->PciDevFlags.Bits.RootBridgeType && sdltmpParent->PciDevFlags.Bits.FixedBus && sdltmpParent->Bus == LocationBusNum){
            if (sdltmp->Device == LocationDevNum && sdltmp->Function == LocationFunNum){
                SdlAslName[0] = *(sdltmp->AslName);
                SdlAslName[1] = *(sdltmp->AslName + 1);
                SdlAslName[2] = *(sdltmp->AslName + 2);
                SdlAslName[3] = *(sdltmp->AslName + 3);
                TRACE((-1, "TbtDxe: Get SDL ASL name %c%c%c%c\n", SdlAslName[0], SdlAslName[1], SdlAslName[2], SdlAslName[3]));
            }
        }
    }
    
    return Status;
}

/**
    Update the DSDT table

    @param[in] DsdtTable        The table points to DSDT table.

    @retval VOID

**/
VOID TbtDsdtTableUpdate (
  IN ACPI_HDR   *DsdtTable )
{
    EFI_STATUS  Status           = EFI_SUCCESS;
    UINT8       *CurrPtr;
    UINT8       *DsdtPointer;
    UINT32      *Signature       = NULL;
    UINT8       DoneFlag         = 0;
    UINT8       TbtAslStartPoint = 0;
    UINT8       HexStr[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H',\
                              'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    UINT8       TbtPcieSlotAslName[4];
    
    CurrPtr = (UINT8 *) DsdtTable;
    if (gAmiTbtPlatformPolicy != NULL && (!(gAmiTbtPlatformPolicy->TbtAICSupport))) {
        TRACE((-1, "TbtDxe: Updating DSDT table for Thunderbolt\n"));
        
        for (DsdtPointer = CurrPtr;
                 DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
                 DsdtPointer++ )
        {
            Signature = (UINT32 *) DsdtPointer;
            if (*Signature == EFI_SIGNATURE_32 ('O', 'E', '1', 'X')) {
                TRACE((-1, "TbtDxe: Found OE1X ....\n"));
                *DsdtPointer = '_';
                
                // BIOS support of Thunderbolt devices Specification Update Revision 1.0
                // Change ACPI method from level trigger to edge trigger(_L1x to _E1x)
#if defined ULT_SUPPORT && ULT_SUPPORT == 1
                if(IsULTPchSeries()){
                    *(DsdtPointer + 2) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt/16];
                    *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt%16];
                } else {
                    *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt];
                }
#else
                *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt];
#endif
                DoneFlag = DoneFlag | 0x0f;
                TRACE((-1, "TbtDxe: Update Thunderbolt GPE event method\n"));
            } // GPE OE1X event
            if(DoneFlag == 0x0F)  return;
        } // end for loop
    } // !(gAmiTbtPlatformPolicy->TbtAICSupport)
    
    if (gAmiTbtPlatformPolicy != NULL && gAmiTbtPlatformPolicy->TbtAICSupport) {
        TRACE((-1, "TbtDxe: Updating DSDT table for Thunderbolt AIC\n"));

        Status = FindDefaultTbtAslName(gAmiTbtPlatformPolicy->Bus, gAmiTbtPlatformPolicy->Dev, gAmiTbtPlatformPolicy->Fun, TbtPcieSlotAslName);
        TRACE((-1, "TbtDxe: Get SDL ASL Name for PCIE slot which Thunderbolt host occupied %r\n", Status));
        ASSERT_EFI_ERROR(Status);
        
        for (DsdtPointer = CurrPtr;
                 DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
                 DsdtPointer++ )
        {
            Signature = (UINT32 *) DsdtPointer;
            switch(*Signature){
#if defined TBT_PCI0_INI_SUPPORT && TBT_PCI0_INI_SUPPORT == 1
                case (EFI_SIGNATURE_32 ('T', 'I', 'N', 'I')):
                    if((gAmiTbtPlatformPolicy->Bus != TBT_UP_PORT_BUS) ||
                       (gAmiTbtPlatformPolicy->Dev != TBT_UP_PORT_DEV) ||
                       (gAmiTbtPlatformPolicy->Fun != TBT_UP_PORT_FUNC))
                    {
                        *(DsdtPointer - 4) = TbtPcieSlotAslName[0];
                        *(DsdtPointer - 3) = TbtPcieSlotAslName[1];
                        *(DsdtPointer - 2) = TbtPcieSlotAslName[2];
                        *(DsdtPointer - 1) = TbtPcieSlotAslName[3];
                        DoneFlag++;
                        TRACE((-1, "TbtDxe: Update TINI method Thunderbolt Host ASL location to %c%c%c%c\n", TbtPcieSlotAslName[0], TbtPcieSlotAslName[1], TbtPcieSlotAslName[2], TbtPcieSlotAslName[3]));
                    }
                    break;
#endif  // TBT_PCI0_INI_SUPPORT
                case (EFI_SIGNATURE_32 ('O', 'E', '1', 'X')):
                    *DsdtPointer = '_';
                    // BIOS support of Thunderbolt devices Specification Updateh
                    // Revision 1.00
                    // Change ACPI method from level trigger to edge trigger(_L1x to _E1x)
#if defined ULT_SUPPORT && ULT_SUPPORT == 1
                    if(IsULTPchSeries()){
                        *(DsdtPointer + 2) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt/16];
                        *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt%16];
                    } else {
                        *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt];
                    }
#else 
                    *(DsdtPointer + 3) = HexStr[gAmiTbtPlatformPolicy->TbtHotPlugEvt];
#endif
                    DoneFlag++;
                    TbtAslStartPoint = 1;
                    TRACE((-1, "TbtDxe: Update Thunderbolt GPE event method\n"));
                    break;
                case (EFI_SIGNATURE_32 ('T', 'W', 'A', 'K')):
                    if((gAmiTbtPlatformPolicy->Bus != TBT_UP_PORT_BUS) ||
                       (gAmiTbtPlatformPolicy->Dev != TBT_UP_PORT_DEV) ||
                       (gAmiTbtPlatformPolicy->Fun != TBT_UP_PORT_FUNC))
                    {
                        *(DsdtPointer - 4) = TbtPcieSlotAslName[0];
                        *(DsdtPointer - 3) = TbtPcieSlotAslName[1];
                        *(DsdtPointer - 2) = TbtPcieSlotAslName[2];
                        *(DsdtPointer - 1) = TbtPcieSlotAslName[3];
                        DoneFlag++;
                        TRACE((-1, "TbtDxe: Update TWAK method Thunderbolt Host ASL location to %c%c%c%c\n", TbtPcieSlotAslName[0], TbtPcieSlotAslName[1], TbtPcieSlotAslName[2], TbtPcieSlotAslName[3]));
                    }
                    break;
                case (EFI_SIGNATURE_32 ('T', 'P', 'T', 'S')):
                    if((gAmiTbtPlatformPolicy->Bus != TBT_UP_PORT_BUS) ||
                       (gAmiTbtPlatformPolicy->Dev != TBT_UP_PORT_DEV) ||
                       (gAmiTbtPlatformPolicy->Fun != TBT_UP_PORT_FUNC))
                    {
                        *(DsdtPointer - 4) = TbtPcieSlotAslName[0];
                        *(DsdtPointer - 3) = TbtPcieSlotAslName[1];
                        *(DsdtPointer - 2) = TbtPcieSlotAslName[2];
                        *(DsdtPointer - 1) = TbtPcieSlotAslName[3];
                        DoneFlag++;
                        TRACE((-1, "TbtDxe: Update TPTS method Thunderbolt Host ASL location to %c%c%c%c\n", TbtPcieSlotAslName[0], TbtPcieSlotAslName[1], TbtPcieSlotAslName[2], TbtPcieSlotAslName[3]));
                    }
                    break;
                default:
                    if(TbtAslStartPoint && (*Signature == *((UINT32 *)(&DefaultTbtLocationAslName)))){
                        if((gAmiTbtPlatformPolicy->Bus != TBT_UP_PORT_BUS) ||
                           (gAmiTbtPlatformPolicy->Dev != TBT_UP_PORT_DEV) ||
                           (gAmiTbtPlatformPolicy->Fun != TBT_UP_PORT_FUNC))
                        {
                            *DsdtPointer       = TbtPcieSlotAslName[0];
                            *(DsdtPointer + 1) = TbtPcieSlotAslName[1];
                            *(DsdtPointer + 2) = TbtPcieSlotAslName[2];
                            *(DsdtPointer + 3) = TbtPcieSlotAslName[3];
                            DoneFlag++;
                            TRACE((-1, "TbtDxe: Update Thunderbolt Host ASL location to %c%c%c%c\n", TbtPcieSlotAslName[0], TbtPcieSlotAslName[1], TbtPcieSlotAslName[2], TbtPcieSlotAslName[3]));
                        }
                    } // end if
            } // end switch
            
#if defined TBT_S3_WAK_SMI && TBT_S3_WAK_SMI == 1 && TBT_PCI0_INI_SUPPORT == 1
            if(DoneFlag == 0x06)  return;
#elif defined TBT_PCI0_INI_SUPPORT && TBT_PCI0_INI_SUPPORT == 1
            if(DoneFlag == 0x05)  return;
#else
            if(DoneFlag == 0x04)  return;
#endif
        } // end for loop
    }
}
/**
    This function will create all ACPI components for SB when
    ACPI support protocol is available.

    @param[in] Event            Event of callback
    @param[in] Context          Context of callback.

    @retval VOID
**/
VOID UpdateTbtAsl (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
    EFI_STATUS                 Status       = EFI_SUCCESS;
    ACPI_HDR                   *DsdtPtr     = NULL;
    ASL_OBJ_INFO               ObjInfo;
    EFI_PHYSICAL_ADDRESS       DsdtAddr;
    UINTN                      HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    AMI_TBT_HR_STATUS_DATA     HRStatusData;
    UINT32                     Length;
    UINT8                      *ptr;
    UINT8                      TbtSmiNotifyEnable;
    UINT8                      TbtBus;
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
    SYSTEM_CONFIGURATION       *SetupData   = NULL;
    UINTN                      VariableSize = sizeof (SYSTEM_CONFIGURATION);
#else
    SETUP_DATA                 *SetupData   = NULL;
    UINTN                      VariableSize = sizeof(SETUP_DATA);
#endif
    
    // Find DSDT ACPI Table
    Status = LibGetDsdt(&DsdtAddr, EFI_ACPI_TABLE_VERSION_ALL);
    if (EFI_ERROR(Status)) {
        TRACE((TRACE_ALWAYS, "TbtDxe: Fail to Get DSDT - returned %r\n", Status));
        ASSERT_EFI_ERROR(Status);
    } 
    DsdtPtr = (ACPI_HDR*)(UINTN)DsdtAddr;
    TRACE((-1, "TbtDxe: Found DSDT Table at 0x%08X\n", DsdtPtr));
    
    // Find Default Thunderbolt host location ASL Name
    Status = FindDefaultTbtAslName(TBT_UP_PORT_BUS, TBT_UP_PORT_DEV, TBT_UP_PORT_FUNC, DefaultTbtLocationAslName);
    if (EFI_ERROR(Status)) {
        TRACE((TRACE_ALWAYS, "TbtDxe: Fail to Get default Thunderbolt host location ASL name...\n"));
        ASSERT_EFI_ERROR(Status);
    }
    
    // Update Thunderbolt GPE event in ASL
    TbtDsdtTableUpdate (DsdtPtr);

    // Update Thunderbolt Nvs Address and length
    Length = DsdtPtr->Length - sizeof(ACPI_HDR);
    ptr = (UINT8*)((UINTN)DsdtPtr + sizeof(ACPI_HDR));
    Status = GetAslObj(ptr, Length, "TBNV", otOpReg, &ObjInfo);
    if (!(EFI_ERROR(Status))){
        ptr = (UINT8*)ObjInfo.DataStart;
        *(UINT32*)(ptr + 2) = (UINT32)(UINTN)(AmiTbtNvs.TbtNvsArea);      
        *(UINT16*)(ptr + 2 + 5) = sizeof (AMI_TBT_NVS_DATA);
        TRACE((-1, "TbtDxe: Update Thunderbolt NVS area address = 0x%X, length = 0x%X\n", (UINT32)(UINTN)AmiTbtNvs.TbtNvsArea, sizeof (AMI_TBT_NVS_DATA)));
    } else TRACE((-1, "TbtDxe: Fail find TBNV...\n"));
    
    // Thunderbolt BIOS Implementation guide for Redwood Ridge/Falcon Ridge 
    // based devices rev 1.0
    // 2.1.3.2 BIOS setup options for Thunderbolt
    // Switch between Native PCIe Enable and Disabled with the following settings:
    // --------------------------------------------------------------------
    // Native PCIe support disabled (default) | Native PCIe support enabled
    // --------------------------------------------------------------------
    //           SCI Call Enabled             |      SCI Call Enabled
    // --------------------------------------------------------------------
    //           SMI Call Enabled             |      SMI Call Disabled
    // --------------------------------------------------------------------
    //          Notify Call Enabled           |     Notify Call Enabled
    // --------------------------------------------------------------------
    
    Status = pBS->AllocatePool( EfiBootServicesData,
                                VariableSize,
                                &SetupData );
    TRACE((-1, "TbtDxe: Locate memory pool for Setup Data %r\n", Status));
    ASSERT_EFI_ERROR(Status);
    
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
    Status = GetEfiVariable(L"IntelSetup", &SetupGuid, NULL, &VariableSize, &SetupData);
#else
    Status = GetEfiVariable(L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData);
#endif
    ASSERT_EFI_ERROR (Status);
    
    if (SetupData->PciExpNative){
        TbtSmiNotifyEnable = gAmiTbtPlatformPolicy->NotifyEnabled << 1;
        TRACE((-1, "TbtDxe: Native PCIE is enable... so disable TBT SwSMI\n"));
    } else {
        TbtSmiNotifyEnable = gAmiTbtPlatformPolicy->SwSmiEnabled | (gAmiTbtPlatformPolicy->NotifyEnabled << 1);
    }
    
    // Update TSNE object in ASL code
    Status = UpdateAslNameObject( DsdtPtr, "TSNE", TbtSmiNotifyEnable);
    TRACE((-1, "TbtDxe: Update TSNE ASL object value = %x, %r\n", TbtSmiNotifyEnable, Status));
    ASSERT_EFI_ERROR(Status);

#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
    // Update PCIEX_BASE_ADDRESS
    Status = UpdateAslNameObject(DsdtPtr, "PEMA", PcdGet64(PcdPciExpressBaseAddress));
    TRACE((-1, "TbtDxe: Updating PEMA Name Object to %x %r\n", PcdGet64(PcdPciExpressBaseAddress), Status));
    ASSERT_EFI_ERROR(Status);
#endif
    
    //Update TBT Host location bus in ASL code
    if (gAmiTbtPlatformPolicy->TbtAICSupport){
        if (gAmiTbtPlatformPolicy->Bus == 0 && gAmiTbtPlatformPolicy->Dev == 0x1c){
            // Host at SB PCIE slot
            Status = UpdateAslNameObject(DsdtPtr, "TBRP", gAmiTbtPlatformPolicy->Fun);
            TRACE((-1, "TbtDxe: Updating TBRP Name Object %r\n", Status));
            ASSERT_EFI_ERROR(Status);
#if defined TBT_NB_PCIE_SLOT_SUPPORT && TBT_NB_PCIE_SLOT_SUPPORT == 1
        } else if(gAmiTbtPlatformPolicy->Bus == 0 && gAmiTbtPlatformPolicy->Dev < 0x1c){
            // Host at CPU0 NB PCIE slot
            Status = UpdateAslNameObject(DsdtPtr, "TBRP", (0x20 + ((gAmiTbtPlatformPolicy->Dev - 1)*4) + gAmiTbtPlatformPolicy->Fun));
            TRACE((-1, "TbtDxe: Updating TBRP Name Object %r\n", Status));
            ASSERT_EFI_ERROR(Status);
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
        } else {
            //Host at CPU1 ~ CPU3 NB PCIE slot
#endif // TBT_HIGHLAND_PLATFORM_CONFIG
#endif // TBT_NB_PCIE_SLOT_SUPPORT
        }
    }
    TRACE((-1, "TbtDxe: Thunderbolt Host MMIO location:%x\n", TBT_CFG_ADDRESS(gAmiTbtPlatformPolicy->Bus, gAmiTbtPlatformPolicy->Dev, gAmiTbtPlatformPolicy->Fun, 0)));
    TbtBus = MMIO_READ8(TBT_CFG_ADDRESS(gAmiTbtPlatformPolicy->Bus, gAmiTbtPlatformPolicy->Dev, gAmiTbtPlatformPolicy->Fun, PCI_SBUS));
    Status = UpdateAslNameObject(DsdtPtr, "TBUS", TbtBus);
    TRACE((-1, "TbtDxe: Updating TBUS Name Object %r\n", Status));
    ASSERT_EFI_ERROR(Status);
    
    //Update TBT Host Information in ASL code
    Status = pRS->GetVariable( L"TbtHRStatusVar", \
                               &gAmiTbtHrStatusGuid, \
                               NULL, \
                               &HRStatusSize, \
                               &HRStatusData );
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)){
        Status = UpdateAslNameObject( DsdtPtr, "TBHR", HRStatusData.TbtHRSeries);
        TRACE((-1, "TbtDxe: Update TBT Host Information in ASL code %r\n", Status));
        ASSERT_EFI_ERROR(Status);
    }

    // Update _RMV method return value for Thunderbolt
    Status = UpdateAslNameObject( DsdtPtr, "TBMV", gAmiTbtPlatformPolicy->TbtRmvReturnValue);
    TRACE((-1, "TbtDxe: Update TRMV ASL object value = %x, %r\n", gAmiTbtPlatformPolicy->TbtRmvReturnValue, Status));
    ASSERT_EFI_ERROR(Status);

    TRACE((-1, "TbtDxe: Free memory Pool\n"));
    pBS->FreePool( SetupData );
    
    // Kill the Event
    pBS->CloseEvent(Event);
}

#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
/**
    Doing Sx_Exit flow of RR, FR and BDW-TBT-LP(WR) in DXE phase
    
    @param[in] Event            Event of callback
    @param[in] Context          Context of callback.

    @retval VOID
**/
VOID TbtSxExitInDxe (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
    static EFI_GUID            TbtSetupGuid = SETUP_GUID;
    EFI_STATUS                 Status;
    SETUP_DATA                 *SetupData   = NULL;
    UINTN                      VariableSize = sizeof(SETUP_DATA);
    UINTN                      Counter;
    UINT8                      TempBus      = 0x05;
    
    TRACE((-1, "TbtDxe: TbtSxExitInDxe Entry\n"));
    
    // For Debug, out put 80 port CP 0x14
    IoWrite8(0x80, (TBT_SX_EXIT_TBT_CONNECTED | 0x10));
    
    // Assign temp bus to PCIE root port thunderbolt host occupied
    MMIO_WRITE16(TBT_CFG_ADDRESS(gAmiTbtPlatformPolicy->Bus, gAmiTbtPlatformPolicy->Dev, gAmiTbtPlatformPolicy->Fun, PCI_SBUS), ((TempBus << 8) | TempBus));
    
    // Do a dummy Write
    MMIO_WRITE32(TBT_CFG_ADDRESS(TempBus, 0, 0, PCI_VID), 0x12345678);
    
    // Get Thunderbolt setup setting
    Status = GetEfiVariable(L"Setup", &TbtSetupGuid, NULL, &VariableSize, &SetupData);
    if (EFI_ERROR(Status)) goto Exit;
    
    if (!(SetupData->TbtWakeupSupport)){
        // BIOS support of Thunderbolt devices Specification for 
        // RR Revision 1.0 / FR Revision 1.1 / WR Revision 1.0
        // 2.2.2.4 Sx exit flow for Hosts without Thunderbolt wake support
        // If BIOS saved pre-Sx Host Router state as active
        // (system went to sleep with attached devices),
        // BIOS should add 500ms delay before proceeding to next step
        pBS->Stall(550 * 1000);
    } // Not Support wake from Thunderbolt device
    
    // BIOS support of Thunderbolt devices Specification for 
    // RR Revision 1.0 / FR Revision 1.1 / WR Revision 1.0
    // 2.2.2.5 Sx exit flow for Hosts with and without Thunderbolt wake support
    // Upon wake, if BIOS saved pre-Sx Host Router state as active, BIOS sholud:
    // 1. Apply "PCIE2TBT <-> TBT2PCIE" handshake procedure with 
    //    "Sx_Exit_TBT_Connected" command.
    // 2. If procedure above returns true, BIOS sholud perform 
    //    "wait for fast link bring-up" loop.
    if (MMIO_READ32(TBT_CFG_ADDRESS(TempBus, 0, 0, PCI_RID)) != 0xFFFFFFFF){
        if (TbtSetPCIe2TBTCommand(TempBus, 0, TBT_SX_EXIT_TBT_CONNECTED, 0x8FFFFF)){
            for(Counter = 0; Counter < 0x2000; Counter++){
                if (MMIO_READ32(TBT_CFG_ADDRESS(TempBus, 0, 0, PCI_VID)) != 0xFFFFFFFF){
                    break;
                }
                
                pBS->Stall(1000);
            } // end for loop
        }
    }
    
    // Remove temp bus
    MMIO_WRITE32(TBT_CFG_ADDRESS(gAmiTbtPlatformPolicy->Bus, gAmiTbtPlatformPolicy->Dev, gAmiTbtPlatformPolicy->Fun, PCI_PBUS), 0xFF0000FF);

Exit:
    TRACE((-1, "TbtDxe: TbtSxExitInDxe Exit\n"));
    
    // Kill the Event
    pBS->CloseEvent(Event);
}
#endif // TBT_HIGHLAND_PLATFORM_CONFIG

#if defined CSM_SUPPORT && CSM_SUPPORT == 1
/**
    Disable all Tbt devices option ROM to aviod S4 resume problem.

    @param[in] Event            Event of callback
    @param[in] Context          Context of callback.

    @retval VOID
**/
VOID DisableTbtDeviceRomCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context )
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  Handle;
    UINTN                       Size = sizeof(EFI_HANDLE);
    CSM_PLATFORM_POLICY_DATA    *CsmOpromPolicyData;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    PCI_DEV_INFO                *Device;

    TRACE((-1, "TbtDxe: DisableTbtDeviceRomCallback() Entry\n"));

    Status = pBS->LocateHandle(ByRegisterNotify, NULL, CsmOpromPolicyRegs, &Size, &Handle);
    if (EFI_ERROR(Status)) return;

    Status = pBS->HandleProtocol(Handle, &gOpromStartEndProtocolGuid, &CsmOpromPolicyData);
    if (EFI_ERROR(Status)) return;

    if(CsmOpromPolicyData == NULL) return; //post-process OpROM callback
    if(CsmOpromPolicyData->PciIo == NULL) return; // OEM Service ROM

    PciIo = CsmOpromPolicyData->PciIo;
    Device = (PCI_DEV_INFO*)PciIo;
    while ((Device->Type != tPciRootBrg) && (Device->ParentBrg != NULL)) {
        Device = Device->ParentBrg;
        if (Device->Address.Addr.Bus != gAmiTbtPlatformPolicy->Bus) continue;
        if (Device->Address.Addr.Device != gAmiTbtPlatformPolicy->Dev) continue;
        if (Device->Address.Addr.Function != gAmiTbtPlatformPolicy->Fun) continue;
        if (gAmiTbtPlatformPolicy->TbtOptionRom || (BootMode & BOOT_ON_S4_RESUME)){
            CsmOpromPolicyData->ExecuteThisRom = FALSE;  //this attritube default is TRUE
            TRACE((-1, "TbtDxe: ExecuteThisRom is setted FALSE.\n"));
        }
        
        break;
    }

    TRACE((-1, "TbtDxe: DisableTbtDeviceRomCallback() Exit\n"));
}
#endif // CSM_SUPPORT

/**
    This function will create NVS area for thunderbolt

    @param[in] ImageHandle          Image handle
    @param[in] SystemTable          Pointer to the system table

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization
**/
EFI_STATUS InstallAmiTbtHrStateNvs(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  Handle       = NULL;
    UINTN                       HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    AMI_TBT_HR_STATUS_DATA      HRStatusData;
    
    // Allocate pools for Thunderbolt Global NVS area
    Status = pBS->AllocatePool (EfiReservedMemoryType, sizeof (AMI_TBT_NVS_DATA), &AmiTbtNvs.TbtNvsArea);
    
    if (!(EFI_ERROR(Status))){
        pBS->SetMem(AmiTbtNvs.TbtNvsArea, sizeof (AMI_TBT_NVS_DATA), 0);
        TRACE((-1, "TbtDxe: Allocate pools for Thunderbolt Global NVS area at %x, size:%x\n", (&AmiTbtNvs.TbtNvsArea), sizeof (AMI_TBT_NVS_DATA)));
        
        Status = pRS->GetVariable( L"TbtHRStatusVar", \
                                   &gAmiTbtHrStatusGuid, \
                                   NULL, \
                                   &HRStatusSize, \
                                   &HRStatusData );
        if (!(EFI_ERROR(Status))){
            AmiTbtNvs.TbtNvsArea->TbtHRSeries      = HRStatusData.TbtHRSeries;
            AmiTbtNvs.TbtNvsArea->TbtHRStatus      = HRStatusData.TbtHRStatus;
            AmiTbtNvs.TbtNvsArea->TbtWakeupSupport = gAmiTbtPlatformPolicy->TbtWakeupSupport;
            TRACE((-1, "TbtDxe: Update Thunderbolt Host variable data to NVS area !!!\n"));
        }
    }
    ASSERT_EFI_ERROR(Status);
    
    Status = pBS->InstallProtocolInterface (
                      &Handle,
                      &gAmiTbtNvsProtocolGuid,
                      EFI_NATIVE_INTERFACE,
                      &AmiTbtNvs
                      );
    ASSERT_EFI_ERROR (Status);
    
    return EFI_SUCCESS;
}

/**
    This function is the entry point for this DXE.

    @param ImageHandle - Image handle
        SystemTable - Pointer to the system table

    @retval Return Status based on errors that occurred while waiting for
        time to expire.
**/
EFI_STATUS TbtDxeInit(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                Status;
    EFI_EVENT                 mAcpiEvent          = NULL;
    EFI_EVENT                 CsmOpromPolicyEvent = NULL;
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
    EFI_EVENT                 TbtSxExitInDxeEvent = NULL;
    VOID                      *TbtSxExitRegistration;
#endif
    TBT_HOB                   *gTbtHob;
    
	InitAmiLib(ImageHandle,SystemTable);
    
    // Perform Thunderbolt OEM DXE Initialization and install 
	// AmiTbtPlatformPolicy Protocol
    //
	TRACE((-1, "TbtDxe: Prepare install AMI Thunderbolt platform policy !!!\n"));
	InstallAmiTbtPlatformPolicy (ImageHandle, SystemTable);
	    
	Status = pBS->LocateProtocol( \
	                    &gAmiTbtPlatformPolicyProtocolGuid, \
	                    NULL, \
	                    &gAmiTbtPlatformPolicy);
	TRACE((-1, "TbtDxe: Locate TBT platform policy %r!!!\n", Status));
	if (!EFI_ERROR(Status)) {
	    BootMode = GetBootMode();
	    if (gAmiTbtPlatformPolicy->TbtEnable){
#if defined CSM_SUPPORT && CSM_SUPPORT == 1
	        Status = RegisterProtocolCallback ( &gOpromStartEndProtocolGuid,
	                                            DisableTbtDeviceRomCallback,
	                                            NULL, &CsmOpromPolicyEvent,
	                                            &CsmOpromPolicyRegs);
	        TRACE((-1, "TbtDxe: Create disable TBT OPROM Callback %r!!!\n", Status));
	        ASSERT_EFI_ERROR(Status);
#endif // CSM_SUPPORT
	    
	        if (gAmiTbtPlatformPolicy->SmiNotifyEnabled) {
#if (ACPI_SUPPORT)
	            Status = CreateReadyToBootEvent( TPL_NOTIFY,
	                                             UpdateTbtAsl,
	                                             NULL,
	                                             &mAcpiEvent);
	            TRACE((-1, "TbtDxe: Create TBT ASL update ReadyToBootEvent %r!!!\n", Status));
	            ASSERT_EFI_ERROR(Status);
#endif // ACPI_SUPPORT
	        } // SmiNotifyEnabled
	        
	        gTbtHob = (TBT_HOB *)GetEfiConfigurationTable(SystemTable, &gEfiHobListGuid);
	        if (gTbtHob){
	            Status = FindNextHobByGuid((EFI_GUID*)&gAmiTbtHobGuid, &gTbtHob);
	            
	            if (!(EFI_ERROR(Status)) && gTbtHob->TbtSecurityLevelFlag){
	                // Only for Cactus Ridge host chip's securty level
	                TRACE((-1, "TbtDxe: Need Finish final programming !!!\n"));
	                FinialProgramTbtSecurityLevel(gAmiTbtPlatformPolicy->TbtSecurityLevel);
	            } // Program CR host security level
	            
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
	            if (!(EFI_ERROR(Status)) && gTbtHob->TbtSxExitFlowInDxe){
	                Status = RegisterProtocolCallback ( &gReadyForLockProtocolGuid,
	                                                    TbtSxExitInDxe,
	                                                    NULL, &TbtSxExitInDxeEvent,
	                                                    &TbtSxExitRegistration);
	                TRACE((-1, "TbtDxe: Create event for Sx Exit flow in Dxe phase %r !!!\n", Status));
	            } // Handle DXE Sx Exit flow for special case 
#endif
            } else TRACE((-1, "TbtDxe: Can not find any Hob list !!!\n"));
	        
	        InstallAmiTbtHrStateNvs (ImageHandle, SystemTable);
	    } // TbtEnable
	} // gAmiTbtPlatformPolicy success
	TRACE((-1, "TbtDxe: TbtDxeInit() Exit !!!\n"));
	return EFI_SUCCESS;
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
