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
//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//*************************************************************************
// ReviGpion History
// ----------------
// $Log: $
// 
//*************************************************************************
#include <token.h>
#include <Setup.h>
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include <Library/IoLib.h>
#include <Library/AmiChipsetIoLib.h>
#include <Library/TbtOemLib.h>
#include <Protocol/AmiTbtPlatformPolicy.h>
#include <Guid/AmiTbtHrStatus.h>
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
#include <Guid/SetupVariable.h>
#endif
#include <PCI.h>
#include <TbtCommon.h>

// GUID Definition(s)
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
EFI_GUID  IntelSetupGuid            = SYSTEM_CONFIGURATION_GUID;
#endif
EFI_GUID  SetupGuid                 = SETUP_GUID;

// Variable Declaration(s)
AMI_TBT_PLATFORM_POLICY_PROTOCOL  gTbtPlatformPolicy;

/**
    Pull High GPIO_3 and assign temp bus to get Thunderbolt Host
    Chip Series for distinguishing Thunderbolt host is Cactus Ridge, 
    Redwood Ridge or Falcon Ridge

    If your case is only support Redwood Ridge or only support Cactus
    Ridge, you can just return Thunderbolt Host number which is defined
    in AmiTbtHrStatus.h

    According test result, the dynamic detect Thunderbolt HR series
    still has fail rate, so we don't suggest you using the same way
    to decide HR series. sample code is just for testing !!!

    @param VOID

    @retval 1           Cactus Ridge
    @retval 2           Redwood Ridge
    @retval 3           Falcon Ridge
    @retval 4           BDW-TBT-LP(Win Ridge)
**/
UINT8 GetHRInfo( VOID )
{
    UINT8        TBTHostSeries = DEFAULT_TBT_CHIP;
// Sample code for ITE8728F and WTM2
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8        Data8;
#else
    UINT32       Data32;
#endif
    UINT16       HRID;
    UINT32       REG_VAL = 0;
    BOOLEAN      RRCmd = FALSE;

#if !defined BWT1_BOARD || BWT1_BOARD != 2  
    OpenSioConfig();

    SetSioLdn(0x07);

    if(ReadSio (0x62) == 0x00){
       //program Super IO Base Address
       WriteSio(0x62, (UINT8)(IT8728F_GPIO_BASE_ADDRESS >> 8));
       WriteSio(0x63, (UINT8)(IT8728F_GPIO_BASE_ADDRESS & 0xFF));
    }

    //program GP21 as GPIO pin
    Data8 = ReadSio (0x26);
    Data8 |= 0x02;
    WriteSio (0x26, Data8);

    //program GP21 GPIO polarity
    Data8 = ReadSio (0xB1);
    Data8 &= 0xFD;
    WriteSio (0xB1, Data8);

    //program GP21 internal pull-up enable
    Data8 = ReadSio (0xB9);
    Data8 |= 0x02;
    WriteSio (0xB9, Data8);

    //program GP21 Simple I/O enable
    Data8 = ReadSio (0xC1);
    Data8 |= 0x02;
    WriteSio (0xC1, Data8);

    //program GP21 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xC9);
    Data8 |= 0x02;
    WriteSio (0xC9, Data8);
#else
#endif

    // Assign temp bus
    TRACE((-1, "TbtOemBoard: Thunderbolt Host MMIO location:%x\n", TBT_CFG_ADDRESS(TBT_UP_PORT_BUS, TBT_UP_PORT_DEV, TBT_UP_PORT_FUNC, 0)));
    MMIO_WRITE16(TBT_CFG_ADDRESS(TBT_UP_PORT_BUS, TBT_UP_PORT_DEV, TBT_UP_PORT_FUNC, PCI_PBUS+1), 0x0505);
    // Do a dummy Write
    MMIO_WRITE32(TBT_CFG_ADDRESS(5, 0, 0, PCI_VID), 0x12345678);
    
    // Pull High GPIO_3(__FORCE_PWR)
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
    Data8 |= 0x02;
    IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
#else
    Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
    Data32 |= BIT31;
    IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif

    // Delay 100 ms
    CountTime(100000, PM_BASE_ADDRESS);

    //Write OS_UP commond for RR chip
    TbtSetPCIe2TBTCommand(5, 0, TBT_OS_UP, 0x8FFFF);

    // Delay 600 ms
    CountTime(600000, PM_BASE_ADDRESS);

    // Get HR Info
    HRID = MMIO_READ16(TBT_CFG_ADDRESS(5, 0, 0, PCI_DID));
    switch (HRID){
        case 0x1547: // Cactus Ridge 4C
        case 0x1548: // Cactus Ridge 2C
              TBTHostSeries = Cactus_Ridge;
              break;

        case 0x1567: // Redwood Ridge 2C
        case 0x1569: // Redwood Ridge 4C
        case 0x156B: // Falcon Ridge 2C
        case 0x156D: // Falcon Ridge 4C
        case 0x157E: // BDW-TBT-LP(WR)
        default:
              if ((HRID == 0x1567) || (HRID == 0x1569)){
                  TBTHostSeries = Redwood_Ridge;
              } else if ((HRID == 0x156B) || (HRID == 0x156D)){
                  TBTHostSeries = Falcon_Ridge;
              } else {
                  TBTHostSeries = BDW_TBT_LP;
              }

              // Reset FW's security level for RR chip, only for FW rev.26 or above.
              TbtSetPCIe2TBTCommand(5, 0, TBT_SET_SECURITY_LEVEL, 0x8FFFF);
              // Delay 100 ms
              CountTime(100000, PM_BASE_ADDRESS);
    }

    // Pull Low GPIO_3(__FORCE_PWR)
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
    Data8 &= 0xFD;
    IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
#else
    Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
    Data32 &= ~BIT31;
    IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif
    
    // Delay 100 ms
    CountTime(100000, PM_BASE_ADDRESS);

    // Remove temp bus
    MMIO_WRITE32(TBT_CFG_ADDRESS(TBT_UP_PORT_BUS, TBT_UP_PORT_DEV, TBT_UP_PORT_FUNC, PCI_PBUS), 0xFF000000);
//*/
    return TBTHostSeries;
}

/**
    This function is the entry point for TbtOemBoard.

    @param[in] ImageHandleImage     handle
    @param[in] SystemTable          Pointer to the system table

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization
**/
EFI_STATUS InstallAmiTbtPlatformPolicy (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable )
{
    //
    // OEM Porting is required.
    //
    EFI_STATUS              Status             = EFI_SUCCESS;
    EFI_HANDLE              Handle             = NULL;
    UINTN                   VariableSize       = sizeof(SETUP_DATA);
    UINTN                   HRStatusSize       = sizeof(AMI_TBT_HR_STATUS_DATA);
    UINT32                  Attributes;
    CHAR16                  TbtHRStatusVar[]   = TBT_HR_STATUS_VARIABLE;
    UINT16                  counter = 0;
    UINT8                   TbtSetVariableFlag = 0;
    AMI_TBT_HR_STATUS_DATA  HRStatusData;
    SETUP_DATA              SetupData;
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
    SYSTEM_CONFIGURATION    IntelSetupData;
    UINTN                   IntelVariableSize  = sizeof (SYSTEM_CONFIGURATION);
    UINT32                  IntelAttributes;
    UINT8                   TbtSetIntelVariableFlag = 0;
#endif
    
    InitAmiLib(ImageHandle, SystemTable);
    
    //Initial Host Router information
    Status = pRS->GetVariable( L"TbtHRStatusVar", \
                               &gAmiTbtHrStatusGuid, \
                               NULL, \
                               &HRStatusSize, \
                               &HRStatusData );
    if (EFI_ERROR(Status)){
        TRACE((-1, "TbtOemBoard: Can not get Thunderbolt Host Router Information !!! \n"));
        HRStatusData.TbtHRStatus   = 0;
        //Get Thunderbolt host Series
        HRStatusData.TbtHRSeries = GetHRInfo();
        TRACE((-1, "TbtOemBoard: Thunderbolt Host Router Chip: %x \n", HRStatusData.TbtHRSeries));

        Status = pRS->SetVariable( TbtHRStatusVar, \
                                   &gAmiTbtHrStatusGuid, \
                                   EFI_VARIABLE_NON_VOLATILE | \
                                   EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                                   EFI_VARIABLE_RUNTIME_ACCESS, \
                                   HRStatusSize, \
                                   &HRStatusData );
        if (!EFI_ERROR(Status))
            TRACE((-1, "TbtOemBoard: Create Thunderbolt Host Router Information !!! \n"));
    }

    Status = pRS->GetVariable( L"Setup",
                               &SetupGuid,
                               &Attributes,
                               &VariableSize,
                               &SetupData );
    ASSERT_EFI_ERROR (Status);

    Status = pBS->AllocatePool( \
                    EfiBootServicesData, \
                    sizeof(AMI_TBT_PLATFORM_POLICY_PROTOCOL), \
                    (VOID**)&gTbtPlatformPolicy );
    ASSERT_EFI_ERROR (Status);

    TRACE((-1, "TbtOemBoard: Start install Thunderbolt Platform Policy !!! \n"));
    pBS->SetMem( &gTbtPlatformPolicy, sizeof(AMI_TBT_PLATFORM_POLICY_PROTOCOL), 0 );

    //
    // OEM Porting required.
    //
//AptioV server override start
//* Sample Code
    gTbtPlatformPolicy.TbtEnable             = SetupData.TbtEnable;
    gTbtPlatformPolicy.TbtGO2SX              = TBT_GO2SX;
    gTbtPlatformPolicy.TbtForcePWR           = TBT_ForcePWR;
    gTbtPlatformPolicy.TbtHotPlugEvt         = TBT_HotPlugEvt;
    gTbtPlatformPolicy.TbtOK2GO2SX_N         = TBT_OK2GO2SX_N;
    gTbtPlatformPolicy.CacheLineSize         = SetupData.TbtCacheLineSize;
    gTbtPlatformPolicy.TbtWakeupSupport      = SetupData.TbtWakeupSupport;
    gTbtPlatformPolicy.TbtAICSupport         = SetupData.TbtAICSupport;
    gTbtPlatformPolicy.TbtHandlePOC          = SetupData.TbtHandlePOC;
    gTbtPlatformPolicy.TbtSecurityLevel      = SetupData.TbtSecurityLevel;
    gTbtPlatformPolicy.Bus                   = TBT_UP_PORT_BUS;
    gTbtPlatformPolicy.Dev                   = TBT_UP_PORT_DEV;
    gTbtPlatformPolicy.Fun                   = TBT_UP_PORT_FUNC;
    if (gTbtPlatformPolicy.TbtAICSupport == 1){
        if (SetupData.TbtHostLocation < 8){
            gTbtPlatformPolicy.Fun           = SetupData.TbtHostLocation;
        } else if((SetupData.TbtHostLocation >= 0x20) && (SetupData.TbtHostLocation < 0x30)){
            gTbtPlatformPolicy.Dev           = ((SetupData.TbtHostLocation) & 0x0F) / 4 + 1;
            gTbtPlatformPolicy.Fun           = ((SetupData.TbtHostLocation) & 0x0F) % 4;
        }
    }
    gTbtPlatformPolicy.ReserveMemoryPerSlot  = SetupData.ReserveMemoryPerSlot;
    gTbtPlatformPolicy.ReservePMemoryPerSlot = SetupData.ReservePMemoryPerSlot;
    gTbtPlatformPolicy.ReserveIOPerSlot      = SetupData.ReserveIOPerSlot;
    gTbtPlatformPolicy.SmiNotifyEnabled      = SetupData.SmiNotifyEnabled;
    gTbtPlatformPolicy.SwSmiEnabled          = SetupData.SwSmiEnabled;
    gTbtPlatformPolicy.NotifyEnabled         = SetupData.NotifyEnabled;
    gTbtPlatformPolicy.TbtRmvReturnValue     = SetupData.TbtRmvReturnValue;
    gTbtPlatformPolicy.TbtOptionRom          = SetupData.TbtOptionRom;
    gTbtPlatformPolicy.TbtIOresourceEnable   = SetupData.TbtIOresourceEnable;

    Status = pBS->InstallProtocolInterface (
                      &Handle,
                      &gAmiTbtPlatformPolicyProtocolGuid,
                      EFI_NATIVE_INTERFACE,
                      &gTbtPlatformPolicy
                      );
    ASSERT_EFI_ERROR (Status);
    
    TRACE((-1, "====Dump Thunderbolt Policy Data====\n"));
    TRACE((-1, "TbtEnable: %x\n", gTbtPlatformPolicy.TbtEnable));
    TRACE((-1, "TbtGO2SX: %x\n", gTbtPlatformPolicy.TbtGO2SX));
    TRACE((-1, "TbtForcePWR: %x\n", gTbtPlatformPolicy.TbtForcePWR));
    TRACE((-1, "TbtHotPlugEvt: %x\n", gTbtPlatformPolicy.TbtHotPlugEvt));
    TRACE((-1, "TbtOK2GO2SX_N: %x\n", gTbtPlatformPolicy.TbtOK2GO2SX_N));
    TRACE((-1, "CacheLineSize: %x\n", gTbtPlatformPolicy.CacheLineSize));
    TRACE((-1, "TbtWakeupSupport: %x\n", gTbtPlatformPolicy.TbtWakeupSupport));
    TRACE((-1, "TbtAICSupport: %x\n", gTbtPlatformPolicy.TbtAICSupport));
    TRACE((-1, "TbtHandlePOC: %x\n", gTbtPlatformPolicy.TbtHandlePOC));
    TRACE((-1, "TbtSecurityLevel: %x\n", gTbtPlatformPolicy.TbtSecurityLevel));
    TRACE((-1, "Bus: %x\n", gTbtPlatformPolicy.Bus));
    TRACE((-1, "Dev: %x\n", gTbtPlatformPolicy.Dev));
    TRACE((-1, "Fun: %x\n", gTbtPlatformPolicy.Fun));
    TRACE((-1, "ReserveMemoryPerSlot: %x\n", gTbtPlatformPolicy.ReserveMemoryPerSlot));
    TRACE((-1, "ReservePMemoryPerSlot: %x\n", gTbtPlatformPolicy.ReservePMemoryPerSlot));
    TRACE((-1, "ReserveIOPerSlot: %x\n", gTbtPlatformPolicy.ReserveIOPerSlot));
    TRACE((-1, "SmiNotifyEnabled: %x\n", gTbtPlatformPolicy.SmiNotifyEnabled));
    TRACE((-1, "SwSmiEnabled: %x\n", gTbtPlatformPolicy.SwSmiEnabled));
    TRACE((-1, "NotifyEnabled: %x\n", gTbtPlatformPolicy.NotifyEnabled));
    TRACE((-1, "TbtRmvReturnValue: %x\n", gTbtPlatformPolicy.TbtRmvReturnValue));
    TRACE((-1, "TbtOptionRom: %x\n", gTbtPlatformPolicy.TbtOptionRom));
    TRACE((-1, "TbtIOresourceEnable: %x\n", gTbtPlatformPolicy.TbtIOresourceEnable));
    TRACE((-1, "=============== End ===============\n"));
//AptioV server override end
//*/
    //synchronize Thunderbolt Host Router Information with Setup Data
    if (HRStatusData.TbtHRSeries != SetupData.TbtHRSeries){
        TRACE((-1, "TbtOemBoard: Setting Thunderbolt Host Router Information into Setup Data!!! \n"));
        SetupData.TbtHRSeries = HRStatusData.TbtHRSeries;
        TbtSetVariableFlag |= 1;
    }
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
    Status = pRS->GetVariable (L"IntelSetup",
                               &IntelSetupGuid,
                               &IntelAttributes,
                               &IntelVariableSize,
                               &IntelSetupData);
    ASSERT_EFI_ERROR (Status);
#endif
    
#if defined TBT_INTEL_RC_CONFIG && TBT_INTEL_RC_CONFIG == 1
    if (gTbtPlatformPolicy.TbtEnable){
#if !defined TBT_HIGHLAND_PLATFORM_CONFIG || TBT_HIGHLAND_PLATFORM_CONFIG == 0
        // For Normal DT/MB platform
        if (gTbtPlatformPolicy.TbtAICSupport){
            if ((gTbtPlatformPolicy.Bus == 0) && (gTbtPlatformPolicy.Dev == 0x1C))
            {   // Thunderbolt AIC is at SB PCIE root port
                if ((SetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun] != 353) || \
                    (SetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun] != 737))
                {
                    // Change PCIE root port resource to correct location
                    SetupData.PcieRootPortHPE[gTbtPlatformPolicy.Fun]   = 1;
                    SetupData.ExtraBusRsvd[gTbtPlatformPolicy.Fun]      = TBT_DEFAULT_EXTRA_BUS_RESERVED;
                    SetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun]       = TBT_DEFAULT_PCIE_MEM_RESERVED;
                    SetupData.PcieMemRsvdalig[gTbtPlatformPolicy.Fun]   = 26;
                    SetupData.PciePFMemRsvd[gTbtPlatformPolicy.Fun]     = TBT_DEFAULT_PCIE_PF_MEM_RESERVED;
                    SetupData.PciePFMemRsvdalig[gTbtPlatformPolicy.Fun] = 28;
                    SetupData.PcieIoRsvd[gTbtPlatformPolicy.Fun]        = TBT_DEFAULT_PCIE_IO_RESERVED;
                    
                    // Double check resource on other PCIE root port is disable
                    for(counter=0;counter<=10;counter++){
                        if((counter != gTbtPlatformPolicy.Fun) && (counter < 8)){
                            if((SetupData.PcieMemRsvd[counter] == 353) || \
                               (SetupData.PcieMemRsvd[counter] == 737))
                            {
                                SetupData.PcieRootPortHPE[counter]         = 0;
                                SetupData.ExtraBusRsvd[counter]            = 0;
                                SetupData.PcieMemRsvd[counter]             = 10;
                                SetupData.PcieMemRsvdalig[counter]         = 1;
                                SetupData.PciePFMemRsvd[counter]           = 10;
                                SetupData.PciePFMemRsvdalig[counter]       = 1;
                                SetupData.PcieIoRsvd[counter]              = 4;
                            }
                        } // counter != gTbtPlatformPolicy.Fun
                    } // for loop
                    
                    TbtSetVariableFlag |= 1;
                } // Thunderbolt PCIE root port resource is at incorrect location
            } else {
                // Thunderbolt AIC is at NB PCIE root port
                // Double check resource on other PCIE root port is disable
                for(counter=0;counter<=7;counter++){
                    if((SetupData.PcieMemRsvd[counter] == 353) || \
                       (SetupData.PcieMemRsvd[counter] == 737))
                    {
                        SetupData.PcieRootPortHPE[counter]      = 0;
                        SetupData.ExtraBusRsvd[counter]         = 0;
                        SetupData.PcieMemRsvd[counter]          = 10;
                        SetupData.PcieMemRsvdalig[counter]      = 1;
                        SetupData.PciePFMemRsvd[counter]        = 10;
                        SetupData.PciePFMemRsvdalig[counter]    = 1;
                        SetupData.PcieIoRsvd[counter]           = 4;
                        
                        TbtSetVariableFlag |= 1;
                    }
                } // end of for loop
            }
        } else {
            if ((SetupData.PcieMemRsvd[TBT_UP_PORT_FUNC] != 353) || \
                (SetupData.PcieMemRsvd[TBT_UP_PORT_FUNC] != 737))
            {
                SetupData.TbtHostLocation                     = TBT_UP_PORT_FUNC;
                SetupData.PcieRootPortEn[TBT_UP_PORT_FUNC]    = 1;
                SetupData.PcieRootPortHPE[TBT_UP_PORT_FUNC]   = 1;
                SetupData.ExtraBusRsvd[TBT_UP_PORT_FUNC]      = TBT_DEFAULT_EXTRA_BUS_RESERVED;
                SetupData.PcieMemRsvd[TBT_UP_PORT_FUNC]       = TBT_DEFAULT_PCIE_MEM_RESERVED;
                SetupData.PcieMemRsvdalig[TBT_UP_PORT_FUNC]   = 26;
                SetupData.PciePFMemRsvd[TBT_UP_PORT_FUNC]     = TBT_DEFAULT_PCIE_PF_MEM_RESERVED;
                SetupData.PciePFMemRsvdalig[TBT_UP_PORT_FUNC] = 28;
                SetupData.PcieIoRsvd[TBT_UP_PORT_FUNC]        = TBT_DEFAULT_PCIE_IO_RESERVED;
                
                // Double check resource on other PCIE root port is disable
                for(counter=0;counter<=10;counter++){
                    if((counter != TBT_UP_PORT_FUNC) && (counter < 8)){
                        if((SetupData.PcieMemRsvd[counter] == 353) || (SetupData.PcieMemRsvd[counter] == 737)){
                            SetupData.PcieRootPortHPE[counter]         = 0;
                            SetupData.ExtraBusRsvd[counter]            = 0;
                            SetupData.PcieMemRsvd[counter]             = 10;
                            SetupData.PcieMemRsvdalig[counter]         = 1;
                            SetupData.PciePFMemRsvd[counter]           = 10;
                            SetupData.PciePFMemRsvdalig[counter]       = 1;
                            SetupData.PcieIoRsvd[counter]              = 4;
                        }
                    } // counter != TBT_UP_PORT_FUNC
                } // for loop
                
                TbtSetVariableFlag |= 1;
            } // PCIE root port resource is not at default location
        } // gTbtPlatformPolicy.TbtAICSupport
#else
        // For High Land Platform(Grantley)
        if (gTbtPlatformPolicy.TbtAICSupport){
            if ((gTbtPlatformPolicy.Bus == 0) && (gTbtPlatformPolicy.Dev == 0x1C))
            {   // Thunderbolt AIC is at SB PCIE root port
                if ((IntelSetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun] != 353) || \
                    (IntelSetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun] != 737))
                {
                    // Change PCIE root port resource to correct location
                    IntelSetupData.PcieRootPortHPE[gTbtPlatformPolicy.Fun]   = 1;
                    IntelSetupData.PcieExtraBusRsvd[gTbtPlatformPolicy.Fun]  = TBT_DEFAULT_EXTRA_BUS_RESERVED;
                    IntelSetupData.PcieMemRsvd[gTbtPlatformPolicy.Fun]       = TBT_DEFAULT_PCIE_MEM_RESERVED;
                    IntelSetupData.PcieMemRsvdalig[gTbtPlatformPolicy.Fun]   = 26;
                    IntelSetupData.PciePFMemRsvd[gTbtPlatformPolicy.Fun]     = TBT_DEFAULT_PCIE_PF_MEM_RESERVED;
                    IntelSetupData.PciePFMemRsvdalig[gTbtPlatformPolicy.Fun] = 28;
                    IntelSetupData.PcieIoRsvd[gTbtPlatformPolicy.Fun]        = TBT_DEFAULT_PCIE_IO_RESERVED;
                    
                    // Double check resource on other PCIE root port is disable
                    for(counter=0;counter<8;counter++){
                        if(counter != gTbtPlatformPolicy.Fun){
                            if((IntelSetupData.PcieMemRsvd[counter] == 353) || \
                               (IntelSetupData.PcieMemRsvd[counter] == 737))
                            {
                                IntelSetupData.PcieRootPortHPE[counter]      = 0;
                                IntelSetupData.PcieExtraBusRsvd[counter]     = 0;
                                IntelSetupData.PcieMemRsvd[counter]          = 10;
                                IntelSetupData.PcieMemRsvdalig[counter]      = 1;
                                IntelSetupData.PciePFMemRsvd[counter]        = 10;
                                IntelSetupData.PciePFMemRsvdalig[counter]    = 1;
                                IntelSetupData.PcieIoRsvd[counter]           = 4;
                            }
                        } // counter != gTbtPlatformPolicy.Fun
                    } // for loop for SB PCIE root port
                    /*  AptioV server override start - Commenting temporarily as below 
                    //setup options are not a part of IntelSetup variable
                    for(counter=0;counter<=44;counter++){
                        if ((IntelSetupData.IioPcieMemRsvd[counter] == 353) || \
                            (IntelSetupData.IioPcieMemRsvd[counter] == 737))
                        {
                            IntelSetupData.SLOTHPCAP[counter]                = 0;
                            IntelSetupData.ACPIHP[counter]                   = 0;
                            IntelSetupData.IioPcieExtraBusRsvd[counter]      = 0;
                            IntelSetupData.IioPcieMemRsvd[counter]           = 10;
                            IntelSetupData.IioPcieMemRsvdalig[counter]       = 1;
                            IntelSetupData.IioPciePFMemRsvd[counter]         = 10;
                            IntelSetupData.IioPciePFMemRsvdalig[counter]     = 1;
                            IntelSetupData.IioPcieIoRsvd[counter]            = 0;
                        }
                    }// end for loop for NB PCIE root port
                    //AptioV server override end */
                    TbtSetIntelVariableFlag |= 1;
                }// Thunderbolt PCIE root port resource is at incorrect location
            } else {
               /*  AptioV server override start - Commenting temporarily as below 
               //setup options are not a part of IntelSetup variable
                // Thunderbolt AIC is at NB PCIE root port
                UINT8       NbIndex;
                
                NbIndex = gTbtPlatformPolicy.Dev * (gTbtPlatformPolicy.Dev - 1) + gTbtPlatformPolicy.Fun + 1;
                
                if ((IntelSetupData.IioPcieMemRsvd[NbIndex] != 353) || \
                    (IntelSetupData.IioPcieMemRsvd[NbIndex] != 737))
                {
                    // Change PCIE root port resource to correct location
                    IntelSetupData.SLOTHPCAP[NbIndex]            = 1;
                    IntelSetupData.ACPIHP[NbIndex]               = 1;
                    IntelSetupData.IioPcieExtraBusRsvd[NbIndex]  = TBT_DEFAULT_EXTRA_BUS_RESERVED;
                    IntelSetupData.IioPcieMemRsvd[NbIndex]       = TBT_DEFAULT_PCIE_MEM_RESERVED;
                    IntelSetupData.IioPcieMemRsvdalig[NbIndex]   = 26;
                    IntelSetupData.IioPciePFMemRsvd[NbIndex]     = TBT_DEFAULT_PCIE_PF_MEM_RESERVED;
                    IntelSetupData.IioPciePFMemRsvdalig[NbIndex] = 28;
                    IntelSetupData.IioPcieIoRsvd[NbIndex]        = TBT_DEFAULT_PCIE_IO_RESERVED;
                    
                    // Double check resource on other PCIE root port is disable
                    for(counter=0;counter<8;counter++){
                        if((IntelSetupData.PcieMemRsvd[counter] == 353) || \
                           (IntelSetupData.PcieMemRsvd[counter] == 737))
                        {
                            IntelSetupData.PcieRootPortHPE[counter]          = 0;
                            IntelSetupData.PcieExtraBusRsvd[counter]         = 0;
                            IntelSetupData.PcieMemRsvd[counter]              = 10;
                            IntelSetupData.PcieMemRsvdalig[counter]          = 1;
                            IntelSetupData.PciePFMemRsvd[counter]            = 10;
                            IntelSetupData.PciePFMemRsvdalig[counter]        = 1;
                            IntelSetupData.PcieIoRsvd[counter]               = 4;
                        }
                    } // end for loop for SB PCIE root port
                    
                    for(counter=0;counter<=44;counter++){
                        if(counter != NbIndex){
                            if ((IntelSetupData.IioPcieMemRsvd[counter] == 353) || \
                                (IntelSetupData.IioPcieMemRsvd[counter] == 737))
                            {
                                IntelSetupData.SLOTHPCAP[counter]            = 0;
                                IntelSetupData.ACPIHP[counter]               = 0;
                                IntelSetupData.IioPcieExtraBusRsvd[counter]  = 0;
                                IntelSetupData.IioPcieMemRsvd[counter]       = 10;
                                IntelSetupData.IioPcieMemRsvdalig[counter]   = 1;
                                IntelSetupData.IioPciePFMemRsvd[counter]     = 10;
                                IntelSetupData.IioPciePFMemRsvdalig[counter] = 1;
                                IntelSetupData.IioPcieIoRsvd[counter]        = 0;
                            }
                        }
                    }// end for loop for NB PCIE root port
                    
                    TbtSetIntelVariableFlag |= 1;
                }// Thunderbolt PCIE root port resource is at incorrect location
            //AptioV server override end*/
            }
        } else {
            if ((IntelSetupData.PcieMemRsvd[TBT_UP_PORT_FUNC] != 353) || \
                (IntelSetupData.PcieMemRsvd[TBT_UP_PORT_FUNC] != 737))
            {
                SetupData.TbtHostLocation                          = TBT_UP_PORT_FUNC;
                IntelSetupData.PcieRootPortEn[TBT_UP_PORT_FUNC]    = 1;
                IntelSetupData.PcieRootPortHPE[TBT_UP_PORT_FUNC]   = 1;
                IntelSetupData.PcieExtraBusRsvd[TBT_UP_PORT_FUNC]  = TBT_DEFAULT_EXTRA_BUS_RESERVED;
                IntelSetupData.PcieMemRsvd[TBT_UP_PORT_FUNC]       = TBT_DEFAULT_PCIE_MEM_RESERVED;
                IntelSetupData.PcieMemRsvdalig[TBT_UP_PORT_FUNC]   = 26;
                IntelSetupData.PciePFMemRsvd[TBT_UP_PORT_FUNC]     = TBT_DEFAULT_PCIE_PF_MEM_RESERVED;
                IntelSetupData.PciePFMemRsvdalig[TBT_UP_PORT_FUNC] = 28;
                IntelSetupData.PcieIoRsvd[TBT_UP_PORT_FUNC]        = TBT_DEFAULT_PCIE_IO_RESERVED;
                
                // Double check resource on other PCIE root port is disable
                for(counter=0;counter<=10;counter++){
                    if((counter != TBT_UP_PORT_FUNC) && (counter < 8)){
                        if((IntelSetupData.PcieMemRsvd[counter] == 353) || (IntelSetupData.PcieMemRsvd[counter] == 737)){
                            IntelSetupData.PcieRootPortHPE[counter]         = 0;
                            IntelSetupData.PcieExtraBusRsvd[counter]        = 0;
                            IntelSetupData.PcieMemRsvd[counter]             = 10;
                            IntelSetupData.PcieMemRsvdalig[counter]         = 1;
                            IntelSetupData.PciePFMemRsvd[counter]           = 10;
                            IntelSetupData.PciePFMemRsvdalig[counter]       = 1;
                            IntelSetupData.PcieIoRsvd[counter]              = 4;
                        }
                    } // counter != TBT_UP_PORT_FUNC
                } // for loop
                
                TbtSetVariableFlag |= 1;
                TbtSetIntelVariableFlag |= 1;
            } // PCIE root port resource is not at default location
        } // gTbtPlatformPolicy.TbtAICSupport
        if (TbtSetIntelVariableFlag != 0){
            Status = pRS->SetVariable( L"IntelSetup", &IntelSetupGuid, IntelAttributes, 
                                       IntelVariableSize, &IntelSetupData );
        }
#endif // TBT_HIGHLAND_PLATFORM_CONFIG
    }// gTbtPlatformPolicy.TbtEnable
#endif // TBT_INTEL_RC_CONFIG
    
    if (TbtSetVariableFlag != 0){
        Status = pRS->SetVariable( L"Setup", &SetupGuid, Attributes, 
                                   VariableSize, &SetupData );
    }
    
    return EFI_SUCCESS;
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
