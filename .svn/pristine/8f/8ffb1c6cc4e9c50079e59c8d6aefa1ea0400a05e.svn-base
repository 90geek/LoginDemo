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
/** @file TbtPei.c
    Thunderbolt initialization in the PEI stage

**/
//**********************************************************************

#include <Token.h>
#include <Setup.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <Ppi/Stall.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PeiServicesLib.h>
#include <Library/AmiChipsetIoLib.h>
#include <Library/TbtOemLib.h>
#include <Guid/AmiTbtHrStatus.h>
#include <Guid/AmiTbtHob.h>
#include <Pci.h>
#if !defined TBT_HIGHLAND_PLATFORM_CONFIG || TBT_HIGHLAND_PLATFORM_CONFIG == 0
#include <Ppi/NbPpi.h>
#endif
#include <TbtCommon.h>

//----------------------------------------------------------------------------
// GUID Definition(s)
//----------------------------------------------------------------------------
EFI_GUID SetupGuid                      = SETUP_GUID;

//----------------------------------------------------------------------------
// Function Prototype Definition(s)
//----------------------------------------------------------------------------
BOOLEAN IsSocPchSeries( VOID );

EFI_STATUS TbtCRSxExitFlow (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadOnlyVariable,
    IN AMI_TBT_HR_STATUS_DATA           *TbtHostInfo);

EFI_STATUS TbtSxExitFlow (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadOnlyVariable,
    IN AMI_TBT_HR_STATUS_DATA           *TbtHostInfo);

EFI_STATUS TbtPeiAfterNbPcieReady(
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR        *NotifyDescriptor,
    IN VOID                             *InvokePpi );

//----------------------------------------------------------------------------
// Notified PPI Definition(s)
//----------------------------------------------------------------------------
#if !defined TBT_HIGHLAND_PLATFORM_CONFIG || TBT_HIGHLAND_PLATFORM_CONFIG == 0
static EFI_PEI_NOTIFY_DESCRIPTOR TbtNotifyList[] = {
        { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
          EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
          &gAmiPeiBeforeMrcGuid, TbtPeiAfterNbPcieReady },
};
#else
static EFI_PEI_NOTIFY_DESCRIPTOR TbtNotifyList[] = {
        { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
          EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
          &gEfiEndOfPeiSignalPpiGuid, TbtPeiAfterNbPcieReady },
};
#endif

/**
    This function is the entry point for this PEI. This function
    initializes Intel Thunderbolt function

    @param[in] FfsHeader            Pointer to the FFS file header
    @param[in] PeiServices          Pointer to the PEI services table

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization

**/
EFI_STATUS
EFIAPI TbtPeiEntry (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
    EFI_STATUS                      Status;
    EFI_BOOT_MODE                   BootMode;
    AMI_TBT_HR_STATUS_DATA          HRStatusData;
    SETUP_DATA                      SetupData;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    UINT8                           TBus         = TBT_UP_PORT_BUS;
    UINT8                           TDev         = TBT_UP_PORT_DEV;
    UINT8                           TFun         = TBT_UP_PORT_FUNC;
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
#if !defined TBT_ASL_HANDLE_SX_EXIT || TBT_ASL_HANDLE_SX_EXIT == 0
    TBT_HOB                         *tHob;
#endif // TBT_ASL_HANDLE_SX_EXIT
#endif // TBT_HIGHLAND_PLATFORM_CONFIG
    
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Entry !!!\n"));
    
    Status = PeiServicesGetBootMode (&BootMode);
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "BootMode = %X\n", BootMode));
    
    if (BootMode > BOOT_ON_S3_RESUME){
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "Thunderbolt dones't support working with this Boot mode !!!\n"));
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Exit !!!\n"));
        return EFI_SUCCESS;
    }
    
    // Locate PeiReadOnlyVariable ppi
    Status = PeiServicesLocatePpi ( &gEfiPeiReadOnlyVariable2PpiGuid, 0,
                                    NULL, (VOID **) &ReadOnlyVariable );
    PEI_TRACE((TRACE_ALWAYS, PeiServices,"TbtPei: Locate PeiReadOnlyVariable Ppi Status = %r\n", Status));
    if(EFI_ERROR(Status)) return Status;
    
    Status = ReadOnlyVariable->GetVariable ( ReadOnlyVariable, L"Setup",
                                             &SetupGuid, NULL,
                                             &VariableSize, &SetupData );
    PEI_TRACE((TRACE_ALWAYS, PeiServices,"TbtPei: Locate Get Setup ReadOnlyVariable Status = %r\n", Status));
    if(EFI_ERROR(Status)) return Status;
    
    if ((!EFI_ERROR(Status)) && (SetupData.TbtEnable == 0)){
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Thunderbolt function is disable in Setup...\n"));
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Skip all action for TBT in PEI phase\n"));
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Exit !!!\n"));
        return EFI_SUCCESS;
    }
    
    // Thunderbolt BIOS Implementation guide for Redwood Ridge/Falcon Ridge based devices
    // Specification Update Revision 1.0
    // 2.1.3.7 PCH configuration for hosts with Add-In Card support
    // During boot, reboot and wake T218 field (bits [1:0]) of PCH PM_CFG register should be set to
    // 11b - 10 ms (default value is 0b - 10 us)
    if (SetupData.TbtAICSupport){
        if(IsSocPchSeries()){
            MmioOr8((PMC_BASE_ADDRESS + R_PCH_PMC_PM_CFG), (BIT00 | BIT01));
        } else {
            SET_MEM8_RCRB(R_PCH_RCRB_PM_CFG, (BIT00 | BIT01));
        }
    } // AIC Support enable
    
    Status = ReadOnlyVariable->GetVariable ( ReadOnlyVariable, L"TbtHRStatusVar",
                                             &gAmiTbtHrStatusGuid, NULL,
                                             &HRStatusSize, &HRStatusData );
    PEI_TRACE((TRACE_ALWAYS, PeiServices,"TbtPei: Locate Get TbtHRStatusVar ReadOnlyVariable Status = %r\n", Status));
    if (!EFI_ERROR(Status)){
        // For OEM doing anything before Thunderbolt Sx Exit flow
        PEI_TRACE((TRACE_ALWAYS, PeiServices,"TbtPei: Execute TbtBeforeSxExitFlow function...\n"));
        TbtBeforeSxExitFlow(PeiServices, HRStatusData.TbtHRSeries);
        
        // Check Thunderbolt host record location
        if (SetupData.TbtHostLocation >= 0x20){
#if !defined TBT_HIGHLAND_PLATFORM_CONFIG || TBT_HIGHLAND_PLATFORM_CONFIG == 0
            // Thunderbolt host is at NB PCIE root port
            Status = (*PeiServices)->NotifyPpi( PeiServices, TbtNotifyList );
            PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Thunderbolt host is at NB PCIE slot, create notify event %r\n", Status));
#else
            if(BootMode == BOOT_ON_S3_RESUME){
                Status = (*PeiServices)->NotifyPpi( PeiServices, TbtNotifyList );
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Thunderbolt host is at NB PCIE slot, create notify event for S3 %r\n", Status));
#if defined TBT_RR_S5_SXEXIT && TBT_RR_S5_SXEXIT == 1
            } else {
#else
            } else if (BootMode == BOOT_ON_S4_RESUME){
#endif // TBT_RR_S5_SXEXIT
                if (HRStatusData.TbtHRStatus){
#if !defined TBT_ASL_HANDLE_SX_EXIT || TBT_ASL_HANDLE_SX_EXIT == 0
                    Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(TBT_HOB), &tHob);;
                    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Thunderbolt host is at NB PCIE slot, create Thunderbolt Hob %r\n", Status));
                    if(!EFI_ERROR(Status)){
                        tHob->Header.Name = gAmiTbtHobGuid;
                        tHob->TbtSecurityLevelFlag = 0;
                        tHob->TbtSxExitFlowInDxe   = 1;
                    }
#endif // TBT_ASL_HANDLE_SX_EXIT
                } // host status is active
            }
#endif // TBT_HIGHLAND_PLATFORM_CONFIG
            
            ASSERT_PEI_ERROR(PeiServices, Status);
            PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Exit !!!\n"));
            return Status;
        }
        switch(HRStatusData.TbtHRSeries){
            case Cactus_Ridge:
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Cactus Ridge wake flow ...\n"));
                Status = TbtCRSxExitFlow(PeiServices, ReadOnlyVariable, &HRStatusData);
                break;
            case Redwood_Ridge:
            case Falcon_Ridge:
            case BDW_TBT_LP:
#if !defined TBT_ASL_HANDLE_SX_EXIT || TBT_ASL_HANDLE_SX_EXIT == 0
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Redwood Ridge/Falcon Ridge/Win Ridge wake flow ...\n"));
                Status = TbtSxExitFlow(PeiServices, ReadOnlyVariable, &HRStatusData);
#endif // TBT_ASL_HANDLE_SX_EXIT
                break;
            default:
                Status = EFI_UNSUPPORTED;
        } //end switch
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: After Thunderbolt wake flow %r...\n", Status));
    } // Get Thunderbolt host information success
    
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "Intel Thunderbolt PEI Exit !!!\n"));
	return EFI_SUCCESS;
}

/**
    This function is to get PCH series is SOC series or not
    for BayTrail platform

    @param VOID

    @retval TRUE            Intel SOC platform
    @retval FALSE           Not Intel SOC platform
**/
BOOLEAN
IsSocPchSeries( VOID ){
    UINT16   PchDeviceId;
    
    PchDeviceId = READ_PCI16 (0x00, LPC_DEVICE, LPC_FUNC, 0x02);
    switch(PchDeviceId){
        case 0x0F1C:
        case 0x0F1D:
        case 0x0F1E:
        case 0x0F1F:
            return TRUE;
    }
    return FALSE;
}

/**
    Thunderbolt host Sx Exit Flow for Cactus Ridge chip

    @param[in] **PeiServices        Pointer to the PEI services table
    @param[in] *ReadOnlyVariable    Pointer to the read only variable table
    @param[in] *TbtHostInfo         Pointer to Thunderbolt vairable

    @retval EFI_STATUS              The function completed successfully
**/
EFI_STATUS TbtCRSxExitFlow (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadOnlyVariable,
    IN AMI_TBT_HR_STATUS_DATA           *TbtHostInfo)
{
    EFI_STATUS                      Status       = EFI_SUCCESS;
    EFI_PEI_STALL_PPI               *StallPpi    = NULL;
    EFI_BOOT_MODE                   BootMode;
    TBT_HOB                         *tHob;
    SETUP_DATA                      SetupData;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           Delay;
    
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    Status = ReadOnlyVariable->GetVariable ( ReadOnlyVariable, L"Setup",
                                             &SetupGuid, NULL,
                                             &VariableSize, &SetupData );
    if(EFI_ERROR(Status)) return Status;
    
    Status = PeiServicesLocatePpi (&gEfiPeiStallPpiGuid, 0, NULL, (VOID **) &StallPpi);
    if(EFI_ERROR(Status)) return Status;
    
    if (TbtHostInfo->TbtHRSeries != Cactus_Ridge) return EFI_INVALID_PARAMETER;
    
    if (BootMode > BOOT_ON_S3_RESUME) return EFI_SUCCESS;
    
    // For Debug, out put 80 port CP 0x14
    IoWrite8(0x80, 0x14);
    
    if (SetupData.TbtWakeupSupport){
        PEI_TRACE((TRACE_ALWAYS,PeiServices,"TbtPei: System supports waking up from Thunderbolt Device\n"));
        // BIOS support of Thunderbolt devices Specification Update
        // Revision 0.90
        // When BIOS decides to wake system the first step that should be
        // performed is deasserting of GO2Sx pin to wake HR.
        Status = InactiveTbtGpio2();
        
        // If remembered HR state was active(system went to sleep status with 
        // attached devices), BIOS should stall wake process for approximately
        // 2.5 seconds to ensure completeness of TBT link to all endpoint devices.
        if (TbtHostInfo->TbtHRStatus){
            PEI_TRACE((TRACE_ALWAYS,PeiServices,"TbtPei: HR status is active, delay 2.5 seconds\n"));
            Delay = (UINTN) ((SetupData.TbtWakeupDelay) * 1000);
            if(Delay != 0) StallPpi->Stall(PeiServices, StallPpi, Delay);
        }
        
        // Create Hob for programming Thunderbolt host security level in Dxe phase
        if (BootMode <= BOOT_ON_S5_RESUME){
            Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(TBT_HOB), &tHob);
            if (!EFI_ERROR(Status)){
                PEI_TRACE((TRACE_ALWAYS,PeiServices,"TbtPei: Create Thunderbolt Hob for Programming Cactus Ridge host Security Level = %x !!!\n", SetupData.TbtSecurityLevel));
                tHob->Header.Name = gAmiTbtHobGuid;
                tHob->TbtSecurityLevelFlag = 1;
                tHob->TbtSxExitFlowInDxe   = 0;
            }
            
            // Program Thunderbolt host security level
            ProgramTbtSecurityLevel(&(SetupData.TbtSecurityLevel), TbtHostInfo->TbtHRSeries, SetupData.TbtHostLocation, TRUE);
        } //end if
    } else {
        PEI_TRACE((TRACE_ALWAYS,PeiServices,"TbtPei: System does not support waking up from Thunderbolt Device\n"));
        // BIOS support of Thunderbolt devices Specification Update Revision 1.2
        // If system does not support "Wake From Thunderbolt Devices" function and
        // remembered HR state was active(system went to sleep status with attached devices),
        // BIOS should:
        // 1. Pull down GPIO_9__OK2GO2SX_N_OD
        // 2. Stall wake process for approximately 2.5 seconds to ensure
        //    completeness of TBT link to all endpoint devices.
        // 3. Release pull down GPIO_9__OK2GO2SX_N_OD (Make control pin as input)
        
#if defined TBT_HR_PWR && TBT_HR_PWR != 0xFF
        // Power on POC of Thunderbolt host chip
        if (SetupData.TbtHandlePOC)  Status = PowerOnPOC();
#endif
        
        if(TbtHostInfo->TbtHRStatus){
            // program GPIO_9 as output low
            Status = PullDownTbtGpio9();
            
            // delay 2.5 seconds
            Delay = (UINTN)((SetupData.TbtWakeupDelay)*1000);
            if(Delay != 0) StallPpi->Stall(PeiServices, StallPpi, Delay);
            
            // release GPIO_9
            Status = ReleaseTbtGpio9();
        }
        
        // Create Hob for programming Thunderbolt host security level in Dxe phase
        if(BootMode != BOOT_ON_S3_RESUME){
            Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(TBT_HOB), &tHob);
            if (!EFI_ERROR(Status)){
                PEI_TRACE((TRACE_ALWAYS,PeiServices,"TbtPei: Create Thunderbolt Hob for Programming Cactus Ridge host Security Level = %x !!!\n", SetupData.TbtSecurityLevel));
                tHob->Header.Name = gAmiTbtHobGuid;
                tHob->TbtSecurityLevelFlag = 1;
                tHob->TbtSxExitFlowInDxe   = 0;
            }
        } //end if
        
        // Program Thunderbolt host security level
        ProgramTbtSecurityLevel(&(SetupData.TbtSecurityLevel), TbtHostInfo->TbtHRSeries, SetupData.TbtHostLocation, TRUE);
        
        // Finish programming security level for S3 path
        if(BootMode == BOOT_ON_S3_RESUME){
            // delay 400ms
            StallPpi->Stall(PeiServices, StallPpi, (400*1000));
            
            // Finish programming security level
            FinialProgramTbtSecurityLevel(SetupData.TbtSecurityLevel);
        } 
    }
    
    return Status;
}

/**
    Thunderbolt host Sx Exit Flow for Redwood Ridge, Falcon Ridge
    and Win Ridge(BDW-TBT-LP) chips

    @param[in] **PeiServices        Pointer to the PEI services table
    @param[in] *ReadOnlyVariable    Pointer to the read only variable table
    @param[in] *TbtHostInfo         Pointer to Thunderbolt vairable

    @retval EFI_STATUS                   
**/
EFI_STATUS TbtSxExitFlow (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadOnlyVariable,
    IN AMI_TBT_HR_STATUS_DATA           *TbtHostInfo)
{
    EFI_STATUS                      Status       = EFI_SUCCESS;
    EFI_PEI_STALL_PPI               *StallPpi    = NULL;
    EFI_BOOT_MODE                   BootMode;
    SETUP_DATA                      SetupData;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           Delay;
    UINTN                           Counter;
    UINT8                           TBus = TBT_UP_PORT_BUS;
    UINT8                           TDev = TBT_UP_PORT_DEV;
    UINT8                           TFun = TBT_UP_PORT_FUNC;
    UINT8                           TempBus = 0x05;
    UINT8                           AssignTempBusFlag = 1;
    
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    Status = ReadOnlyVariable->GetVariable ( ReadOnlyVariable, L"Setup",
                                             &SetupGuid, NULL,
                                             &VariableSize, &SetupData );
    if(EFI_ERROR(Status)) return Status;
    
    Status = PeiServicesLocatePpi (&gEfiPeiStallPpiGuid, 0, NULL, (VOID **) &StallPpi);
    if(EFI_ERROR(Status)) return Status;
    
    if (TbtHostInfo->TbtHRSeries == Cactus_Ridge) return EFI_INVALID_PARAMETER;
    
    // Get Thunderbolt host location
    if (SetupData.TbtHostLocation < 0x20){
        // Thunderbolt host is at SB PCIE root port
        if(SetupData.TbtHostLocation < 0x8) TFun = SetupData.TbtHostLocation;
        
        // Set assign temp bus flag
        AssignTempBusFlag |= 1;
    } else {
        // Thunderbolt host is at NB PCIE root port
        TDev = (SetupData.TbtHostLocation & 0x0F) / 4 + 1;
        TFun = (SetupData.TbtHostLocation & 0x0F) % 4;
        //if (SetupData.TbtHostLocation >= 0x30){
        //    // Thunderbolt host is at CPU1 ~ CPU3 NB PCIE root port
        //    
        //}
        
        // Set assign temp bus flag
#if !defined TBT_HIGHLAND_PLATFORM_CONFIG || TBT_HIGHLAND_PLATFORM_CONFIG == 0
        AssignTempBusFlag |= 1;
#else
        if(BootMode == BOOT_ON_S3_RESUME) AssignTempBusFlag &= 0;
#endif
    } // Get Thunderbolt host location
    PEI_TRACE((TRACE_ALWAYS, PeiServices,"TbtPei: Thunderbolt Host location: B:%x|D:%x|F:%x, Assign Temp Bus Flag:%x\n", TBus, TDev, TFun, AssignTempBusFlag));
    
    if (AssignTempBusFlag == 1){
        // Assign temp bus
        MMIO_WRITE16(TBT_CFG_ADDRESS(TBus, TDev, TFun, PCI_PBUS+1), ((TempBus << 8) | TempBus));
        
        // Do a dummy Write
        MMIO_WRITE32(TBT_CFG_ADDRESS(TempBus, 0, 0, PCI_VID), 0x12345678);
    } else {
        TempBus = MMIO_READ8(TBT_CFG_ADDRESS(TBus, TDev, TFun, PCI_SBUS));
    } // AssignTempBusFlag
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Host location bus number is %x...\n", TempBus));
    
#if defined TBT_RR_S5_SXEXIT && TBT_RR_S5_SXEXIT == 1
    if (TbtHostInfo->TbtHRStatus){
#else
    if ((TbtHostInfo->TbtHRStatus) && ((BootMode == BOOT_ON_S3_RESUME) || (BootMode == BOOT_ON_S4_RESUME))){
#endif
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: HR status is active...\n"));
        
        // For Debug, out put 80 port CP 0x14
        IoWrite8(0x80, (TBT_SX_EXIT_TBT_CONNECTED | 0x10));
        
        if (!(SetupData.TbtWakeupSupport)){
            // BIOS support of Thunderbolt devices Specification for 
            // RR Revision 1.0 / FR Revision 1.1 / WR Revision 1.0
            // 2.2.2.4 Sx exit flow for Hosts without Thunderbolt wake support
            // If BIOS saved pre-Sx Host Router state as active
            // (system went to sleep with attached devices),
            // BIOS should add 500ms delay before proceeding to next step
            Delay = (UINTN)(550 * 1000);
            StallPpi->Stall(PeiServices, StallPpi, Delay);
        } // Not Support wake from Thunderbolt device
        
        // BIOS support of Thunderbolt devices Specification for 
        // RR Revision 1.0 / FR Revision 1.1 / WR Revision 1.0
        // 2.2.2.5 Sx exit flow for Hosts with and without Thunderbolt wake support
        // Upon wake, if BIOS saved pre-Sx Host Router state as active, BIOS sholud:
        // 1. Apply "PCIE2TBT <-> TBT2PCIE" handshake procedure with 
        //    "Sx_Exit_TBT_Connected" command.
        // 2. If procedure above returns true, BIOS sholud perform 
        //    "wait for fast link bring-up" loop.
        
        // Excute command...
        if (MMIO_READ32(TBT_CFG_ADDRESS(TempBus, 0, 0, PCI_RID))!= 0xFFFFFFFF){
            if (TbtSetPCIe2TBTCommand(TempBus, 0, TBT_SX_EXIT_TBT_CONNECTED, 0x8FFFFF)){
                for(Counter=0;Counter<0x2000;Counter++){
                    if (MMIO_READ32(TBT_CFG_ADDRESS(TempBus, 0, 0, PCI_VID)) != 0xFFFFFFFF){
                        break;
                    }
                    StallPpi->Stall(PeiServices, StallPpi, 1000);
                } // for loop
            } // end if
        } // end if
    } // // Host is active
    
    if (AssignTempBusFlag == 1){
        // Remove temp bus
        MMIO_WRITE32(TBT_CFG_ADDRESS(TBus, TDev, TFun, PCI_PBUS), 0xFF0000FF);
    } // AssignTempBusFlag == 1
    
    return Status;
}

/**
    When Thunderbolt host is at NB PCIE slot, we do Sx_Exit flow 
    here avoiding chipset limitation

    @param[in] **PeiServices            Pointer to the PEI services table
    @param[in] *NotifyDescriptor        Pointer to the Notify descriptor
    @param[in] *InvokePpi               Pointer to Invoke Ppi

    @retval EFI_STATUS                   
**/
EFI_STATUS TbtPeiAfterNbPcieReady(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                      Status       = EFI_SUCCESS;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
    AMI_TBT_HR_STATUS_DATA          HRStatusData;
    SETUP_DATA                      SetupData;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           HRStatusSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPeiAfterNbPcieReady Start.\n"));

    // Locate PeiReadOnlyVariable ppi
    Status = PeiServicesLocatePpi ( &gEfiPeiReadOnlyVariable2PpiGuid, 0,
                                    NULL, (VOID **) &ReadOnlyVariable );
    PEI_TRACE((TRACE_ALWAYS, PeiServices,"TbtPei: Locate PeiReadOnlyVariable Ppi Status = %r\n", Status));
    if(EFI_ERROR(Status)) return Status;
    
    Status = ReadOnlyVariable->GetVariable ( ReadOnlyVariable, L"Setup",
                                             &SetupGuid, NULL,
                                             &VariableSize, &SetupData );
    PEI_TRACE((TRACE_ALWAYS, PeiServices,"TbtPei: Locate Get Setup ReadOnlyVariable Status = %r\n", Status));
    if(EFI_ERROR(Status)) return Status;
    
    Status = ReadOnlyVariable->GetVariable ( ReadOnlyVariable, L"TbtHRStatusVar",
                                             &gAmiTbtHrStatusGuid, NULL,
                                             &HRStatusSize, &HRStatusData );
    PEI_TRACE((TRACE_ALWAYS, PeiServices,"TbtPei: Locate Get TbtHRStatusVar ReadOnlyVariable Status = %r\n", Status));
    
    if(!EFI_ERROR(Status) && (SetupData.TbtHostLocation >= 0x20)){
        switch(HRStatusData.TbtHRSeries){
            case Cactus_Ridge:
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Cactus Ridge wake flow ...\n"));
                Status = TbtCRSxExitFlow(PeiServices, ReadOnlyVariable, &HRStatusData);
                break;
            case Redwood_Ridge:
            case Falcon_Ridge:
            case BDW_TBT_LP:
#if !defined TBT_ASL_HANDLE_SX_EXIT || TBT_ASL_HANDLE_SX_EXIT == 0
                PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: Redwood Ridge/Falcon Ridge/Win Ridge wake flow ...\n"));
                Status = TbtSxExitFlow(PeiServices, ReadOnlyVariable, &HRStatusData);
#endif // TBT_ASL_HANDLE_SX_EXIT
                break;
            default:
                Status = EFI_UNSUPPORTED;
        } //end switch
        PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPei: After Thunderbolt wake flow %r...\n", Status));
    }
    
    PEI_TRACE((TRACE_ALWAYS, PeiServices, "TbtPeiAfterNbPcieReady End.\n"));
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
