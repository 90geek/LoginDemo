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
//
// $Header: $
//
// $Revision: $
//
// $Date: $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: $
// 
// 
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:  SBPEI.C
//
// Description: This file contains code for Template Southbridge initialization
//    in the PEI stage
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#pragma warning ( disable : 4090 )//CONST warning
// Module specific Includes
#include <Efi.h>
#include <Pei.h>
#include <token.h>
#include <Hob.h>
#if ATAPI_RECOVERY_SUPPORT
#include <Include\Setup\IioUniversalData.h>
#include <Library\HobLib.h>
#endif
#include <Setup.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <SB.h>
// Produced/used PPI interfaces
#include <ppi\PciCfg2.h> //[EIP64769_04]
#include <PCI.h>
//#include <ppi\SBPPI.h>
#include <ppi\CpuIo.h>
#include <ppi\CspLibPpi.h>
#include <Ppi\SmmControl.h>
#include <Ppi\ReadOnlyVariable2.h>  
#include <ppi\reset.h>
#if ATAPI_RECOVERY_SUPPORT
#include <ppi\AtaController.h>
#endif

//-----------------------------------------------------------------------
// SB : GPIO Initialize Table
//-----------------------------------------------------------------------
AMI_INIT_GPIO_TABLE_STRUCT stSB_GPIOInitTable[] =
{
    //  { Register, AND Mask, OR Mask}
#include <GPIO.h>
    {0xFFFF}
};

UINT16 wSB_GPIOInitTableSize = sizeof(stSB_GPIOInitTable) / sizeof(AMI_INIT_GPIO_TABLE_STRUCT);

// {95E8152B-1B98-4f11-8A77-DB26583EBC42}
#define AMI_PEI_SBINIT_POLICY_PPI_GUID  \
 {0x95e8152b, 0x1b98, 0x4f11, 0x8a, 0x77, 0xdb, 0x26, 0x58, 0x3e, 0xbc, 0x42}

typedef struct _AMI_PEI_SBINIT_POLICY_PPI   AMI_PEI_SBINIT_POLICY_PPI;

struct _AMI_PEI_SBINIT_POLICY_PPI {
    UINTN         unFlag;
};

/*
extern VOID SBLib_ResetSystem(IN EFI_RESET_TYPE ResetType);

extern AMI_PEI_PCI_INIT_TABLE_STRUCT stSBH2P_PCIInitTable [];
extern UINT16 wSBH2P_PCIInitTableSize;

extern AMI_INIT_MMIO_TABLE_STRUCT stSBMMIO_RCBAInitTable[];
extern UINT16 wSBMMIO_RCBAInitTableSize;

extern AMI_INIT_GPIO_TABLE_STRUCT stSB_GPIOInitTable[];
extern UINT16 wSB_GPIOInitTableSize;

VOID ProgramSSIDTable(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI *PciCfg,
    IN SB_PCI_DEVICE_SSID *SSIDRegTable); // (P040809A)
*/

EFI_STATUS SBBeforeInitMemory(
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID    *NullPpi);

EFI_STATUS SBAfterInitMemory(
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID    *NullPpi);

VOID SBGbE_Init(VOID);
VOID SBUsbPeiInit(IN CONST EFI_PEI_SERVICES  **PeiServices);  // (P020309E)

EFI_STATUS InitializeSATA(
    IN CONST EFI_PEI_SERVICES **PeiServices); // (P030309E)
/*
                                        // (P051509A)>
EFI_STATUS InitAcpiPmRegAfterMemory(
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  SB_SETUP_CONFIGURATION *SbSetupPtr
);

EFI_STATUS PchUhciAxPatch(
  IN CONST EFI_PEI_SERVICES    **PeiServices
);

EFI_STATUS RmhPatchForRecoveryMode(
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  SB_SETUP_CONFIGURATION *SbSetupPtr);
                                        // <(P051509A)

                                        // (P010609A)>
EFI_STATUS SbCreateConfiguration(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    OUT SB_SETUP_CONFIGURATION **SbSetup);

EFI_STATUS SbGetConfiguration(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    OUT SB_SETUP_CONFIGURATION **SbSetup);

//EFI_STATUS SbUpdateSetupToHob(        // [ EIP53941 ]
//    IN EFI_PEI_SERVICES **PeiServices,
//    IN OUT SB_SETUP_CONFIGURATION *SbSetup);
                                        // <(P010609A)

//Defined in OEMPort.c
//BOOLEAN
//IsRecovery(
//    CONST EFI_PEI_SERVICES  **PeiServices,
//    EFI_PEI_PCI_CFG2_PPI  *PciCfg,
//    EFI_PEI_CPU_IO_PPI  *CpuIo
//);

VOID H55_3420_UsbPortsWA(VOID);         // (P121409A)

// [ EIP61250 ]                                      
#if HPET_SUPPORT
VOID HPETWorkaround(VOID);           
#endif

// PPI produced by this PEIM

EFI_STATUS SBPEI_CspResetSystem(IN CONST EFI_PEI_SERVICES **PeiServices, IN EFI_RESET_TYPE ResetType);

EFI_GUID gPeiCspResetPpiGuid = AMI_PEI_CSP_RESET_PPI_GUID;

static AMI_CSP_PEI_RESET_PPI gCspResetPpi =
{
    SBPEI_CspResetSystem
};

#if SB_RESET_PPI_SUPPORT
// Define everything related to RESET PPI here (function is defined at the end)

EFI_STATUS SBPEI_ResetSystem(IN CONST EFI_PEI_SERVICES **PeiServices);

EFI_GUID gPeiResetPpiGuid = EFI_PEI_RESET_PPI_GUID;

static EFI_PEI_RESET_PPI mResetPpi =
{
    SBPEI_ResetSystem
};

#endif //SB_RESET_PPI_SUPPORT

#if SB_STALL_PPI_SUPPORT

#include <ppi\stall.h>

// Constants related to template Stall code
#define TIMER_RESOLUTION  1

EFI_STATUS SBPEI_Stall(IN CONST EFI_PEI_SERVICES **PeiServices,
                       IN CONST EFI_PEI_STALL_PPI *This, IN UINTN  Microseconds);

EFI_GUID gStallPpiGuid = EFI_PEI_STALL_PPI_GUID;

extern EFI_STATUS CountTime(IN UINTN DelayTime, IN UINT16 BaseAddr);

static EFI_PEI_STALL_PPI mStallPpi =
{
    TIMER_RESOLUTION,
    SBPEI_Stall
};

#endif //SB_STALL_PPI_SUPPORT
*/
// Produced PPIs

// GUID Definitions

// Portable Constants

// Function Prototypes

// PPI interface definition
EFI_GUID gAmiPEISBInitPolicyGuid     = AMI_PEI_SBINIT_POLICY_PPI_GUID;
EFI_GUID gAmiPEIPCITableInitPpiGuid = AMI_PEI_PCI_TABLE_INIT_PPI_GUID;
EFI_GUID gMasterBootModeGuid        = EFI_PEI_MASTER_BOOT_MODE_PEIM_PPI;
EFI_GUID gRecoveryBootModeGuid      = EFI_PEI_BOOT_IN_RECOVERY_MODE_PEIM_PPI;
EFI_GUID gPeiSmmControlPpiGuid      = PEI_SMM_CONTROL_PPI_GUID;
#if ATAPI_RECOVERY_SUPPORT
EFI_GUID gPeiAtaControllerPpiGuid   = PEI_ATA_CONTROLLER_PPI_GUID;
#endif
EFI_GUID gEfiPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;
EFI_GUID gSetupGuid = SETUP_GUID;

//EFI_GUID gPeiPreMRCGuid = AMI_PEI_PRE_MRC_GUID;
EFI_GUID gPeiPermanentMemInstalled  = EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI;
//EFI_GUID gPeiSBPpiGuid = AMI_PEI_SB_PPI_GUID; // (P111708A)

                                        // (P010609A)>
EFI_GUID gSbSetupHobGuid = AMI_SB_CONFIGURATION_GUID;
#if defined SB_GET_SETUP_SUPPORT && SB_GET_SETUP_SUPPORT == 1
EFI_GUID gEfiSetupGuid = SETUP_GUID;
#endif
                                        // <(P010609A)
//----------------------------------------------------------------------------
// PPI Definition
//----------------------------------------------------------------------------

static AMI_PEI_SBINIT_POLICY_PPI mAmiPeiSbInitPolicyPpi =
{
    TRUE
};

static EFI_PEI_PPI_DESCRIPTOR mBootModePpi[] =
{
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiMasterBootModePpiGuid,//&gMasterBootModeGuid,
    0
};

static EFI_PEI_PPI_DESCRIPTOR mRecoveryModePpi[] =
{
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gRecoveryBootModeGuid,
    0
};

#if ATAPI_RECOVERY_SUPPORT
EFI_STATUS EFIAPI EnableAtaChannel(
    IN CONST EFI_PEI_SERVICES           **PeiServices,
    IN PEI_ATA_CONTROLLER_PPI     *This,
    IN UINT8                      ChannelIndex
);

static PEI_ATA_CONTROLLER_PPI mAtaControllerPpi =
{
    EnableAtaChannel
};
#endif
/*
#if SMM_SUPPORT
EFI_STATUS PeiActivate(
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    IN PEI_SMM_CONTROL_PPI *This,
    IN OUT INT8       *ArgumentBuffer OPTIONAL,
    IN OUT UINTN      *ArgumentBufferSize OPTIONAL,
    IN BOOLEAN        Periodic OPTIONAL,
    IN UINTN          ActivationInterval OPTIONAL
);

EFI_STATUS PeiDeactivate(
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    IN PEI_SMM_CONTROL_PPI *This,
    IN BOOLEAN    Periodic OPTIONAL
);

static PEI_SMM_CONTROL_PPI mSmmControlPpi =
{
    PeiActivate,
    PeiDeactivate
};
#endif

EFI_STATUS SBTaskProcess(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN UINT32 TaskCode,
    IN OUT VOID *DataPtr);

static AMI_PEI_SB_PPI gSBPpi =
{
    SBTaskProcess
};
*/
EFI_STATUS GetChipsetSKU(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    OUT UINT8 *RevisionID);

EFI_STATUS EnableDisplayPort(
    IN CONST EFI_PEI_SERVICES **PeiServices);


//----------------------------------------------------------------------------
// PPI that are installed
//----------------------------------------------------------------------------
static EFI_PEI_PPI_DESCRIPTOR gPpiList[] =
{
//    {EFI_PEI_PPI_DESCRIPTOR_PPI, &gPeiSBPpiGuid, &gSBPpi}, // (P111708A)
//    {EFI_PEI_PPI_DESCRIPTOR_PPI, &gPeiCspResetPpiGuid, &gCspResetPpi},
#if ATAPI_RECOVERY_SUPPORT
    { EFI_PEI_PPI_DESCRIPTOR_PPI, \
      &gPeiAtaControllerPpiGuid, &mAtaControllerPpi },
#endif    
/*
#if SMM_SUPPORT
    {EFI_PEI_PPI_DESCRIPTOR_PPI, &gPeiSmmControlPpiGuid, &mSmmControlPpi},
#endif
#if SB_RESET_PPI_SUPPORT
    {EFI_PEI_PPI_DESCRIPTOR_PPI, &gPeiResetPpiGuid, &mResetPpi},
#endif
#if SB_STALL_PPI_SUPPORT
    {EFI_PEI_PPI_DESCRIPTOR_PPI, &gStallPpiGuid, &mStallPpi},
#endif
*/
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPEISBInitPolicyGuid, &mAmiPeiSbInitPolicyPpi }

};
/*

//----------------------------------------------------------------------------
// Notify list that are installed
//----------------------------------------------------------------------------
                                        // (P111708A)>
static EFI_PEI_NOTIFY_DESCRIPTOR SBPeiNotify[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK,
        &gPeiPreMRCGuid,
        SBBeforeInitMemory
    },
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiPermanentMemInstalled,
        SBAfterInitMemory
    }
};
                                     // <(P111708A)

                                        // (P040809A)>
SB_PCI_DEVICE_SSID PciDevSSIDRegTable[] =
{
// PCI Bridge
    {(UINT32)SB_PCIE_CFG_ADDRESS(P2P_BUS, P2P_DEV, P2P_FUNC, ICH_REG_P2P_SVID), PCIBR_SSID},
// LPC Bridge, SATA0, SATA1, SMBUS, THERMAL
    {(UINT32)SB_PCIE_CFG_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_SSID), LPC_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SVID), SATA0_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SMBUS_BUS, SMBUS_DEV, SMBUS_FUNC, PCI_SVID), SMBUS_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SATA1_BUS, SATA1_DEV, SATA1_FUNC, ICH_REG_SATA_SVID), SATA1_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(THERMAL_BUS, THERMAL_DEV, THERMAL_FUNC, R_PCH_THERMAL_SVID), THERMAL_SSID},
// USB(B0:D29)
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_0, PCI_SVID), EHCI0_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_1, PCI_SVID), UHCI0_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_2, PCI_SVID), UHCI1_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_3, PCI_SVID), UHCI2_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_4, PCI_SVID), UHCI3_SSID},
// USB(B0:D26)
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_26, USB_FUNC_0, PCI_SVID), EHCI1_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_26, USB_FUNC_1, PCI_SVID), UHCI4_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_26, USB_FUNC_2, PCI_SVID), UHCI5_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_26, USB_FUNC_3, PCI_SVID), UHCI6_SSID},
// PCIE Root(B0:D26)
    {(UINT32)SB_PCIE_CFG_ADDRESS(SBPCIE_BUS, SBPCIE_DEV, SBPCIE_FUNC_0, ICH_REG_PCIE_SVID), SBPCIE0_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SBPCIE_BUS, SBPCIE_DEV, SBPCIE_FUNC_1, ICH_REG_PCIE_SVID), SBPCIE1_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SBPCIE_BUS, SBPCIE_DEV, SBPCIE_FUNC_2, ICH_REG_PCIE_SVID), SBPCIE2_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SBPCIE_BUS, SBPCIE_DEV, SBPCIE_FUNC_3, ICH_REG_PCIE_SVID), SBPCIE3_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SBPCIE_BUS, SBPCIE_DEV, SBPCIE_FUNC_4, ICH_REG_PCIE_SVID), SBPCIE4_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SBPCIE_BUS, SBPCIE_DEV, SBPCIE_FUNC_5, ICH_REG_PCIE_SVID), SBPCIE5_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SBPCIE_BUS, SBPCIE_DEV, SBPCIE_FUNC_6, ICH_REG_PCIE_SVID), SBPCIE6_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(SBPCIE_BUS, SBPCIE_DEV, SBPCIE_FUNC_7, ICH_REG_PCIE_SVID), SBPCIE7_SSID},
// HDA(B0:D27)
    {(UINT32)SB_PCIE_CFG_ADDRESS(HDA_BUS, HDA_DEV, HDA_FUNC, R_ICH_HDA_SVID), HDA_SSID},
// GbE(B0:D25)
    {(UINT32)SB_PCIE_CFG_ADDRESS(LAN_BUS, LAN_DEV, LAN_FUNC, ICH_REG_LAN_SVID), GbE_SSID},
// ME Devices(B0:D22)                   // (P072709B)>
    {(UINT32)SB_PCIE_CFG_ADDRESS(ME_BUS, ME_DEV, ME_FUNC0, ICH_REG_ME_SVID), ME_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(ME_BUS, ME_DEV, ME_FUNC1, ICH_REG_ME_SVID), ME1_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(ME_BUS, ME_DEV, ME_FUNC2, ICH_REG_ME_SVID), ME2_SSID},
    {(UINT32)SB_PCIE_CFG_ADDRESS(ME_BUS, ME_DEV, ME_FUNC3, ICH_REG_ME_SVID), ME3_SSID},
// VECI Device(B0:D23)
    {(UINT32)SB_PCIE_CFG_ADDRESS(VE_BUS, VE_DEV, VE_FUNC, PCI_SVID), VE_SSID},
                                        // <(P072709B)
    {0, 0},
};
                                        // <(P040809A)

                                        // (P010609A)>
//EFI_PEI_SB_TASK_FUNCTION SbUpdateConfigFuncTbl[] =
//{
//    0
//};
                                        // <(P010609A)
//----------------------------------------------------------------------------
// MACRO and Constant Definitions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Function Definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Function Definitions
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsS3
//
// Description: This function determines if the system is resuming from an S3
//  sleep state.
//
// Input:
//  **PeiServices - pointer to the Pei Services function and data structure
//
// Output: TRUE - It is an S3 Resume
//   FALSE - It is not an S3 Resume
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsS3(VOID)
{
    if ((MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) & BIT01) != 0)
        return FALSE;

    if ((IoRead16(PM_BASE_ADDRESS + ICH_IOREG_PM1_STS) & BIT11) != 0)
        return FALSE;

    // Check WAK_STS bit
    if (IoRead16(PM_BASE_ADDRESS + ICH_IOREG_PM1_STS) & BIT_WAK_STS)
    {
        // Check the sleep type
        if (((IoRead16(PM1A_CNT_BLK_ADDRESS) & BIT_SLP_TYP_MASK) >> 10) == S3_SLP_TYP)
        {
            return TRUE;
        }
    }
    return FALSE;
}

                                        // (P030309F)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsS4
//
// Description: This function determines if the system is resuming from the
//    ACPI S4 sleep state
//
// Input:  None
//
// Output:  TRUE If it is a S4 resume
//    FALSE if it is a normal boot
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsS4(VOID)
{
    if ((MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) & BIT01) != 0) //LPC 0xA4
        return FALSE;

    if ((IoRead16(PM_BASE_ADDRESS + ICH_IOREG_PM1_STS) & BIT11) != 0)
        return FALSE;

    // Check WAK_STS bit
    if (IoRead16(PM_BASE_ADDRESS + ICH_IOREG_PM1_STS) & BIT_WAK_STS)
    {
        // Check the sleep type
        if (((IoRead16(PM1A_CNT_BLK_ADDRESS) & BIT_SLP_TYP_MASK) >> 10) == S4_SLP_TYP)
        {
            return TRUE;
        }
    }
    return FALSE;
} // End_Of_IsS4
                                        // <(P030309F)

#ifdef LOAD_DEFAULTS_IF_CMOS_BAD
#if LOAD_DEFAULTS_IF_CMOS_BAD
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsCMOSBad
//
// Description: This function determines if the system is resuming from an S3
//  sleep state.
//
// Input:
//  **PeiServices - pointer to the Pei Services function and data structure
//
// Output: TRUE - It is an S3 Resume
//   FALSE - It is not an S3 Resume
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
// CMOS test
BOOLEAN  IsCMOSBad(VOID)
{
    IoWrite8(CMOS_ADDR_PORT, CMOS_BAD_REG);
    if (IoRead8(CMOS_DATA_PORT) & (BIT06 + BIT07))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif
#endif

//AlexP test....
BOOLEAN 
IsFlashUpdateS3Capsule (
    CONST EFI_PEI_SERVICES    **PeiServices,
    EFI_BOOT_MODE       *BootMode
)
#if defined(SecFlashUpd_SUPPORT) && SecFlashUpd_SUPPORT == 1
;
#else
{ return FALSE; }
#endif
*/
/*
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: UpdateBootMode
//
// Description: This function determines the boot mode of the system.  After
//  the correct boot mode has been determined, the PEI Service function
//  SetBootMode is called and then the MasterBootModePpi is installed
//
// Input:
//  **PeiServices - pointer to the Pei Services function and data structure
//
// Output: always returns EFI_SUCCESS
//   Also defines the boot mode for the system
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UpdateBootMode(
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    IN EFI_PEI_CPU_IO_PPI *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI *PciCfg
)
{
    EFI_BOOT_MODE    BootMode;

#ifdef LOAD_DEFAULTS_IF_CMOS_BAD
#if LOAD_DEFAULTS_IF_CMOS_BAD
    UINT8             Buff8;
#endif
#endif

    // Check for changes in the possible boot modes.  This should be made in
    // prioritized order.  At the end of this function the boot mode is
    // determined.  The EFI_BOOT_MODE is defined in the PEI Spec

    BootMode = BOOT_WITH_FULL_CONFIGURATION;

    // Returns 0 if no S3 resume detected returns -1 if this is an S3 boot
    if (IsS3())
    {
        BootMode = BOOT_ON_S3_RESUME;

        IsFlashUpdateS3Capsule(PeiServices, &BootMode);
        if(BootMode==BOOT_ON_FLASH_UPDATE)
            PEI_TRACE((-1, PeiServices, "Boot mode = BOOT_ON_FLASH_UPDATE\n"));
        else
        PEI_TRACE((-1, PeiServices, "Boot mode = BOOT_ON_S3_RESUME\n"));
    }
                                        // (P032509A)>

    else if (IsS4())
    {
        BootMode = BOOT_ON_S4_RESUME;
        PEI_TRACE((-1, PeiServices, "Boot mode = BOOT_ON_S4_RESUME"));
    }                                   // <(P032509A)

    // Check for recovery mode
//    else if (IsRecovery(PeiServices, PciCfg, CpuIo))
//    {
//        BootMode = BOOT_IN_RECOVERY_MODE;
//    }

#ifdef LOAD_DEFAULTS_IF_CMOS_BAD
#if LOAD_DEFAULTS_IF_CMOS_BAD
    // Check for Default setting
    else
    {
        PciCfg->Read(
            PeiServices,
            PciCfg,
            EfiPeiPciCfgWidthUint8,
            LPC_BUS_DEV_FUNC | ICH_REG_GEN_PMCON_3,  // 0xA4
            &Buff8
        );

                                        // (P032409C)>
        if (Buff8 & BIT02)
        {
            BootMode = BOOT_WITH_DEFAULT_SETTINGS;

            Buff8 &= ~(BIT02);          // Clear RTC_PWR_STS
            PciCfg->Write(
                PeiServices,
                PciCfg,
                EfiPeiPciCfgWidthUint8,
                LPC_BUS_DEV_FUNC | ICH_REG_GEN_PMCON_3,  // 0xA4
                &Buff8
            );
                                        // <(P032409C)

            // Write 0xFF to CMOS register
            IoWrite8(CMOS_ADDR_PORT, CMOS_BAD_REG);
            IoWrite8(CMOS_DATA_PORT, 0xFF);
        }
    }

    //
    // if CMOS is bad, change boot mode to BOOT_WITH_DEFAULT_SETTINGS
    //
    if (IsCMOSBad())
    {
        BootMode = BOOT_WITH_DEFAULT_SETTINGS;
    }
#endif
#endif

//####
//#### // check for configuration changes - use Setup and chassis intrusion jumper
//#### else if (NoConfigChanges(PeiServices, PciCfg, CpuIo))
//#### {
//####  BootMode = BOOT_ASSUMING_NO_CONFIGURATION_CHANGES;
//#### }

    // Set the system BootMode
    (*PeiServices)->SetBootMode(PeiServices, BootMode);

    // Let everyone know that boot mode has been determined by installing the
    // MasterBootMode PPI
    (*PeiServices)->InstallPpi(PeiServices, mBootModePpi);

    if (BootMode == BOOT_IN_RECOVERY_MODE) //Recovery Boot Mode PPI
        (*PeiServices)->InstallPpi(PeiServices, mRecoveryModePpi);

    return EFI_SUCCESS;
}
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBPEI_Init
//
// Description: This function is the entry point for this PEI. This function
//    initializes the chipset SB
//
// Input:  FfsHeader Pointer to the FFS file header
//         PeiServices Pointer to the PEI services table
//
// Output:  Return Status based on errors that occurred while waiting for
//          time to expire.
//
// Notes:  This function should initialize South Bridge for memory detection.
//    Install AMI_PEI_SBINIT_POLICY_PPI to indicate that SB Init PEIM
//    is installed
//    Following things can be done at this point:
//     - Enabling top of 4GB decode for full flash ROM
//     - Programming South Bridge ports to enable access to South
//      Bridge and other I/O bridge access
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
EFIAPI
SBPEI_Init(
    IN       EFI_PEI_FILE_HANDLE   FileHandle,
    IN CONST EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS                  Status;
    EFI_PEI_PCI_CFG2_PPI         *PciCfg;
    EFI_PEI_CPU_IO_PPI          *CpuIo;
//    AMI_PEI_PCI_TABLE_INIT_PPI  *AMIPCITableInit;
//    SB_SETUP_CONFIGURATION      *SbSetupPtr; // (P010609A)

//    UINT8                       Buffer8;
                                        // (P071409A)>
//    UINT16                      Data16;
//    UINT32                      Buffer32;
//    UINT32                      Addr;
                                        // <(P071409A)

    PciCfg = (*PeiServices)->PciCfg;
    CpuIo = (*PeiServices)->CpuIo;

    PEI_PROGRESS_CODE(PeiServices, PEI_CAR_SB_INIT);
/*
    // Locate AMI PCI Table Init PPI
    Status = (*PeiServices)->LocatePpi(
                 PeiServices,
                 &gAmiPEIPCITableInitPpiGuid,
                 0,
                 0,
                 &AMIPCITableInit
             );
    // Assert if not found - the AMI PCI Table Init PPI should exist
    ASSERT_PEI_ERROR(PeiServices, Status);

                                        // (P010609A)>
    Status = SbCreateConfiguration(PeiServices, &SbSetupPtr);
    ASSERT_PEI_ERROR(PeiServices, Status);
                                        // <(P010609A)

    // Init LPC Bridge regs at PEI.
    AMIPCITableInit->AMIPEIProgramPCITable(
        PeiServices,
        AMIPCITableInit, PciCfg,
        EFI_SB_PCI_CFG_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, 0),
        stSBH2P_PCIInitTable,
        wSBH2P_PCIInitTableSize
    );

    // Init PCI Bridge regs at PEI.
    Addr = PEI_PCI_CFG_ADDRESS(P2P_BUS, P2P_DEV, P2P_FUNC, ICH_REG_P2P_IOBASE); //P2P bridge Io base
    PciCfgModify(PeiServices, EfiPeiPciCfgWidthUint8, Addr, 0xf0, 0);

    Addr = PEI_PCI_CFG_ADDRESS(P2P_BUS, P2P_DEV, P2P_FUNC, (ICH_REG_P2P_PSTS + 1)); //Status bits. Cleare Detected Parity Error.
    PciCfgModify(PeiServices, EfiPeiPciCfgWidthUint8, Addr, 0x80, 0);

    Addr = PEI_PCI_CFG_ADDRESS(P2P_BUS, P2P_DEV, P2P_FUNC, ICH_REG_P2P_PCICMD); //CMD disable everything except Bus Master and I/O
    PciCfgModify(PeiServices, EfiPeiPciCfgWidthUint8, Addr, 5, 0xfb);

//=============================================================================
//  Program SB devices Subsystem ID.
//=============================================================================
    ProgramSSIDTable(PeiServices, PciCfg, PciDevSSIDRegTable);  // (P111809A)
*/
//=============================================================================
//  Program GPIOs.
//=============================================================================
    ProgramGPIOTable(GPIO_BASE_ADDRESS, stSB_GPIOInitTable, wSB_GPIOInitTableSize);
/*
//=============================================================================
//  Program SB RCBA
//=============================================================================
    ProgramMMIOTable(SB_RCBA, stSBMMIO_RCBAInitTable, wSBMMIO_RCBAInitTableSize);
//=============================================================================
// Program SB USB.
//=============================================================================
    SBUsbPeiInit(PeiServices);            // (P020309E)

    // Configurate SB GbE LAN
    SBGbE_Init();

#if SB_SMBUS_PPI_SUPPORT
    Addr = SMBUS_BUS_DEV_FUNC;
    // Write the Base address to the PCI Config space
    Buffer32 = SMBUS_BASE_ADDRESS;
    PciCfg->Write(
        PeiServices,
        PciCfg,
        EfiPeiPciCfgWidthUint32,
        Addr | R_BASE_ADDRESS,
        &Buffer32
    );

    PciCfgModify(
        PeiServices,
        EfiPeiPciCfgWidthUint16,            // Width
        SMBUS_BUS_DEV_FUNC | R_COMMAND,     // Register offset
        (B_IOSE | B_MSE),                   // Set bits, (P111609B)
        (B_IOSE | B_MSE)                    // Clear bits, (P111609B)
    );

    Buffer8 = B_HST_EN;
    PciCfg->Write(
        PeiServices,
        PciCfg,
        EfiPeiPciCfgWidthUint8,
        Addr | R_HOST_CONFIGURATION,
        &Buffer8
    );

    // Clear errors on the SmBus
    IoWrite8(SMBUS_BASE_ADDRESS + SMB_HST_STS, 0xFF);

#endif //SB_SMBUS_PPI_SUPPORT

    // Set the SB Notify PPI
                                        // (P111708A)>
    Status = (*PeiServices)->NotifyPpi(PeiServices, SBPeiNotify);
    ASSERT_PEI_ERROR(PeiServices, Status);
                                        // <(P111708A)
*/
    // Install the SB Init Policy PPI
    Status = (*PeiServices)->InstallPpi(PeiServices, gPpiList);
    ASSERT_PEI_ERROR(PeiServices, Status);
/*
    // RTC workaround
    IoWrite8(CMOS_ADDR_PORT, 0x0B);
    Buffer8 = IoRead8(CMOS_DATA_PORT);
    Buffer8 &= ~(BIT07);
    IoWrite8(CMOS_DATA_PORT, Buffer8);
    Buffer8 |= BIT7;
    IoWrite8(CMOS_DATA_PORT, Buffer8);
    Buffer8 &= ~(BIT07);
    IoWrite8(CMOS_DATA_PORT, Buffer8);

    // Disable Watchdog timer reset (halt the timer)
    // also enable NMI's to instead generate SMIs.
    Data16 = CpuIo->IoRead16(
                 PeiServices,
                 CpuIo,
                 TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT
             );
    Data16 |= (BIT_TCO_TMR_HLT);
    CpuIo->IoWrite16(
        PeiServices,
        CpuIo,
        TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT,
        Data16
    );


// [ EIP40776 ]
#if defined ME_SUPPORT && ME_SUPPORT == 1
#if THERMAL_REPORTING_SUPPORT
#if THERMAL_REPORTING_INIT_SBPEI >= 1
    Buffer32 = THERMAL_BASE_ADDRESS;

    Status = gSBPpi.TaskProcess(PeiServices, AMI_SB_ENABLE_THERMAL_CONTROLLER, &Addr);
    ASSERT_PEI_ERROR(PeiServices, Status);

    MmPci32(THERMAL_BUS, THERMAL_DEV, THERMAL_FUNC, R_PCH_THERMAL_TBARB) = (Buffer32 | B_PCH_THERMAL_SPTYPEN);

    Status = gSBPpi.TaskProcess(PeiServices, AMI_SB_INIT_THERMAL_CONTROLLER, &Buffer32);
    ASSERT_PEI_ERROR(PeiServices, Status);

#if THERMAL_REPORTING_INIT_SBPEI == 1
    Status = gSBPpi.TaskProcess(PeiServices, AMI_SB_DISABLE_THERMAL_CONTROLLER, &Addr);
    ASSERT_PEI_ERROR(PeiServices, Status);
#endif  // #if THERMAL_REPORTING_INIT_SBPEI == 1
#endif  // #if THERMAL_REPORTING_INIT_SBPEI >= 1
#endif  // #if THERMAL_REPORTING_SUPPORT
#endif  // #if defined ME_SUPPORT && ME_SUPPORT == 1

// [ EIP61250 ]
#if HPET_SUPPORT
    HPETWorkaround();
#endif

    UpdateBootMode(PeiServices, CpuIo, PciCfg);
*/
    return EFI_SUCCESS;
}

/*
                                        // (P111708A)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBTaskProcess
//
// Description:
//
// Input:IN CONST EFI_PEI_SERVICES **PeiServices,
//       IN UINT32 TaskCode,
//       IN OUT VOID *DataPtr
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBTaskProcess(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN UINT32 TaskCode,
    IN OUT VOID *DataPtr)
{
    EFI_STATUS Status;

    switch (TaskCode)
    {
    case AMI_SB_GET_CHIPSET_REVISION:
        Status = GetChipsetSKU(PeiServices, (UINT8*)DataPtr);
        break;

    case AMI_SB_ENABLE_DISPALY_PORT:
        Status = EnableDisplayPort(PeiServices);
        break;

                                        // (P010609A)>
    case AMI_SB_GET_SETUP_CONFIG:
        Status = SbGetConfiguration(PeiServices, (SB_SETUP_CONFIGURATION**)DataPtr);
        break;
                                        // <(P010609A)

                                        // (P040709B)>
#if defined ME_SUPPORT && ME_SUPPORT == 1
#if THERMAL_REPORTING_SUPPORT
    case AMI_SB_ENABLE_THERMAL_CONTROLLER:
        Status = EnableThermalController(PeiServices, (UINT32*)DataPtr);
        break;

    case AMI_SB_DISABLE_THERMAL_CONTROLLER:
        Status = DisableThermalController(PeiServices);
        break;

    case AMI_SB_INIT_THERMAL_CONTROLLER:
        Status = InitThermalController(PeiServices, (UINT32*)DataPtr);
        break;
#endif
#endif
                                        // <(P040709B)

                                        // (P052109A)>
    case AMI_SB_ENABLE_USBR:
        Status = EnableUsbr();
        break;

    case AMI_SB_DISABLE_USBR:
        Status = DisableUsbr();
        break;
                                        // <(P052109A)

    default:
        Status = EFI_UNSUPPORTED;
        break;
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: GetChipsetSKU
//
// Description:
//
// Input:IN CONST EFI_PEI_SERVICES **PeiServices,
//       OUT UINT8 *RevisionID
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetChipsetSKU(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    OUT UINT8 *RevisionID
)
{
    if (RevisionID == 0)
        return EFI_INVALID_PARAMETER;

    *RevisionID = MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_RID);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: EnableDisplayPort
//
// Description: Enable Display Port for Havendale
//
// Input: IN CONST EFI_PEI_SERVICES **PeiServices
//
// Output: EFI_SUCCESS
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnableDisplayPort(
    IN CONST EFI_PEI_SERVICES **PeiServices)
{
                                        // (P103009A)>
    UINT8 Buffer8;

    Buffer8 = Mmio8(SB_RCBA, 0x2318);
    Buffer8 &= ~(BIT00+BIT01+BIT02);
    Buffer8 |= (BIT00+BIT01+BIT02);
    Mmio8(SB_RCBA, 0x2318) = Buffer8;

    Buffer8 = Mmio8(SB_RCBA, 0x2320);
    Buffer8 &= ~(BIT04+BIT05+BIT06+BIT07);
    Buffer8 |= (BIT04+BIT05+BIT06+BIT07);
    Mmio8(SB_RCBA, 0x2320) = Buffer8;
                                        // <(P103009A)

    Mmio32(SB_RCBA, ICH_RCRB_FD2) |= BIT00;
    Mmio16(SB_RCBA, 0x3424) = 0x0010;   // (P020309A)

    return EFI_SUCCESS;
}
                                        // <(P111708A)

                                        // (P040709B)>
                                        // (P090109B)>
#if defined ME_SUPPORT && ME_SUPPORT == 1
#if THERMAL_REPORTING_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: EnableThermalController
//
// Description: Enalble Thermal Controller.
//
// Input: IN CONST EFI_PEI_SERVICES **PeiServices
//
// Output: OUT UINT32 *ThermalBDF
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnableThermalController(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN OUT UINT32 *ThermalBDF
)
{
    Mmio32(SB_RCBA, R_FUNCTION_DISABLE) &= ~(B_THERMAL_DISABLE);
    *ThermalBDF = (UINT32)SB_PCI_CFG_ADDRESS(THERMAL_BUS, THERMAL_DEV, THERMAL_FUNC, R_PCH_THERMAL_VENDOR_ID);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: DisableThermalController
//
// Description: Disable Thermal Controller.
//
// Input: IN CONST EFI_PEI_SERVICES **PeiServices
//
// Output: EFI_SUCCESS
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS DisableThermalController(
    IN CONST EFI_PEI_SERVICES **PeiServices
)
{
// [ EIP42103 ] BSU rev1.06 - Updated section 21.2 with new steps
// a. Clear the Memory and Bus Master Enable bit of D31:F6
    MmPci16(0, 0x1f, 6, 0x04) &= ~0x6;
// b. Release and clear memory resource assigned in TBAR (D31:F6:10h~13h)
    MmPci32(0, 0x1f, 6, 0x10) = 0;
// c. Hide D31:F6 PCI configuration space by setting FD.TTD (RCBA +3418[24])
    Mmio32(SB_RCBA, R_FUNCTION_DISABLE) |= B_THERMAL_DISABLE;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InitThermalController
//
// Description: Initialize Thermal Controller.
//
// Input: IN CONST EFI_PEI_SERVICES **PeiServices
//        IN UINT32 *TBARB
//
// Output: EFI_SUCCESS
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitThermalController(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN UINT32 *TBARB
)
{
  SB_SETUP_CONFIGURATION   *SbSetupPtr;

  EFI_STATUS Status = EFI_SUCCESS;
  UINT32  RegEax;
  UINT16  TSFUSE;
  UINT8   RegData8;
  UINT16  RegData16;
  UINTN   PciD0F0RegBase = MmPciAddress(PCIEX_BASE_ADDRESS, 0, 0, 0, 0);
  UINTN   MCHBAR;

  Status = gSBPpi.TaskProcess(PeiServices, AMI_SB_GET_SETUP_CONFIG, &SbSetupPtr); // (P010609A)
  ASSERT_PEI_ERROR(PeiServices, Status);

  if(!(Mmio32(SB_RCBA, R_FUNCTION_DISABLE) & B_THERMAL_DISABLE))
  {
    //
    // PCH Bios Spec 0.75, Section 21.3.1 Initializing Ibex Peak Thermal Sensors
    // Step 1
    // Set various trip point by programming TSTTP registers.
    // TSTTP[7:0] should be programmed to 0x2B for 120 degrees centigrade and TSTTP[15:8] should be programmed to 0x3A for
    // 108 degrees centigrade
    //
    Mmio16(*TBARB, R_PCH_TBARB_TSTTP) = 0x3A2B;

    //
    // Step 2
    // Clear trip status from TSES
    //
    Mmio8(*TBARB, R_PCH_TBARB_TSES) = 0xFF;

    //
    // Step 3
    // Enable the desired thermal trip alert methods, i.e. GPE (TSGPEN), SMI (TSPC) or Interrupt (TSPIEN). Only one of the methods
    // should be enabled and the method will be depending on the platform implementation.
    //
    // TSGPEN: BIOS should leave this as default 0x00, unless it is required to enable GPE.
    //
    Mmio8(*TBARB, R_PCH_TBARB_TSGPEN) = 0x00;

    //
    // TSPC: BIOS needs to set TSPC[6] to enable catastrophic power down to protect the system. BIOS should leave TSPC[5:0] as
    // default 0x00, unless the SMI handler is loaded and it's safe to enable SMI for these events.
    //
    Mmio8(*TBARB, R_PCH_TBARB_TSPC) |= B_PCH_TBARB_TSPC_CPDE;

    //
    // TSPIEN: BIOS should leave this as default 0x00, so that a driver can enable later
    //
    Mmio8(*TBARB, R_PCH_TBARB_TSPIEN) = 0x00;

    //
    // Step 4
    // Enable thermal sensor by programming TSE register to 0xB8.
    //
    Mmio8(*TBARB, R_PCH_TBARB_TSE) = 0xB8;

    //
    // PCH Bios Spec 0.75, Section 21.3.2 Initializing CPU Thermal Sensor
    // Program CTA with the value derived from IA32_TEMPERATURE_TARGET.TCC activation temperature. The 16bit value to be programmed
    // is calculated from MSR 01A2h[23:16] << 6.
    //
    RegData16 = (UINT16) Shr64(ReadMsr(0x1A2), 16);
    RegData16 = (RegData16 & 0x00FF) << 6;
    Mmio16(*TBARB, R_PCH_TBARB_CTA) = RegData16;

    //
    // PCH Bios Spec 0.75, Section 21.3.3 Initializing IMC/Graphics Thermal Sensor
    // Enable IMC/Graphics thermal sensor prior to programming MGTA with value from MCHBAR+0x1020-0x1023 (8bit mode slope/offset).
    // BIOS does not need to program this register if it's a single die CPU, such as Lynnfield or Clarkfield.
    //

    //
    // Read the Family, Model and Stepping information.
    //
    CPULib_CpuID(1, &RegEax, 0, 0, 0);

    if (((RegEax & 0x0FFF0FF0) == 0x000106F0) ||
       ((RegEax & 0x0FFF0FF0) == 0x00020650)) {
        MCHBAR = Mmio32 (PciD0F0RegBase , MCH_REG_MCHBAR) & 0xFFFFC000;
        TSFUSE = Mmio16 (MCHBAR , 0x1020);
        Mmio16(*TBARB, R_PCH_TBARB_MGTA) = TSFUSE;
    }


    //
    // PCH Bios Spec 0.75, Section 21.4.1, Step 1
    // Follow section 21.2 Thermal Subsystem Device Initialization to initialize Thermal Subsystem device
    //
    // PCH Bios Spec 0.75, Section 21.2, Step 1
    // Enable Thermal Subsystem device by making sure FD.TTD is cleared.
    //
    // PCH Bios Spec 0.75, Section 21.2, Step 2
    // Optionally program Device 31 Interrupt Pin/Route registers
    // Done in platform code
    //
    // PCH Bios Spec 0.75, Section 21.2, Step 3
    // Go through general PCI enumeration and assign standard PCI resource, including TBARB, TBARBH, etc.
    // Done in platform code
    RegData8 = Mmio8(*TBARB, R_PCH_TBARB_AE);

    if (SbSetupPtr->DIMMAlert)
      RegData8 |= B_PCH_TBARB_AE_DIMM_AltEn;
    else
      RegData8 &= ~B_PCH_TBARB_AE_DIMM_AltEn;

    if (SbSetupPtr->PCHAlert)
      RegData8 |= B_PCH_TBARB_AE_PCH_AltEn;
    else
      RegData8 &= ~B_PCH_TBARB_AE_PCH_AltEn;

    if (SbSetupPtr->MCHAlert)
      RegData8 |= B_PCH_TBARB_AE_MCH_AltEn;
    else
      RegData8 &= ~B_PCH_TBARB_AE_MCH_AltEn;

    if (SbSetupPtr->CPUAlert)
      RegData8 |= B_PCH_TBARB_AE_CPU_AltEn;
    else
      RegData8 &= ~B_PCH_TBARB_AE_CPU_AltEn;

      Mmio8(*TBARB, R_PCH_TBARB_AE) = RegData8;

    //
    // PCH Bios Spec 0.75, Section 21.4.1, Step 5
    // Enable thermal report by programming relevant fields from Table 21-1 Thermal Reporting Data
    //
#if (NB_NUMBER_OF_MEM_MODULE >= 1)
    if (SbSetupPtr->TsOnDimm0)
      Mmio8(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_DIMM0_RDEN;
    else
      Mmio8(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_DIMM0_RDEN;
#endif

#if (NB_NUMBER_OF_MEM_MODULE >= 2)
    if (SbSetupPtr->TsOnDimm1)
      Mmio8(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_DIMM1_RDEN;
    else
      Mmio8(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_DIMM1_RDEN;
#endif

#if (NB_NUMBER_OF_MEM_MODULE >= 3)
    if (SbSetupPtr->TsOnDimm2)
      Mmio8(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_DIMM2_RDEN;
    else
      Mmio8(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_DIMM2_RDEN;
#endif

#if (NB_NUMBER_OF_MEM_MODULE >= 4)
    if (SbSetupPtr->TsOnDimm3)
      Mmio8(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_DIMM3_RDEN;
    else
      Mmio8(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_DIMM3_RDEN;
#endif

    if (SbSetupPtr->MCHTempReadEnable)
      Mmio8(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_MCH_RDEN;
    else
      Mmio8(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_MCH_RDEN;

    if (SbSetupPtr->PCHTempReadEnable)
      Mmio8(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_PCH_RDEN;
    else
      Mmio8(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_PCH_RDEN;

    if (SbSetupPtr->CPUEnergyReadEnable)
      Mmio8(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_CPU_ENGY_RDEN;
    else
      Mmio8(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_CPU_ENGY_RDEN;

    if (SbSetupPtr->CPUTempReadEnable)
      Mmio8(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_CPU_RDEN;
    else
      Mmio8(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_CPU_RDEN;

    if (SbSetupPtr->ThermalDataReportingEnable)
      Mmio16(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_THRM_PRT_EN;
    else
      Mmio16(*TBARB, R_PCH_TBARB_TRC) &= ~B_PCH_TBARB_TRC_THRM_PRT_EN;

    if(CheckLFDPlatform() == EFI_SUCCESS)
      Mmio16(*TBARB, R_PCH_TBARB_TRC) |= B_PCH_TBARB_TRC_C6WA_EN;
    //
    // PCH Bios Spec 0.75, Section 21.4.1, Step 6
    // Locking thermal reporting configurations, please see section 21.4.4 Locking Thermal Reporting Settings
    //
    // PCH Bios Spec 0.75, Section 21.4.4, Step 1
    // Set TSCO[7] to lock down the Catastrophic Trip Point setting. Software is required to preserve the value in TSCO[6:0] while
    // updating bit 7.
    //
    Mmio8(*TBARB, R_PCH_TBARB_TSCO) |= B_PCH_TBARB_TSCO_LBC;

    //
    // PCH Bios Spec 0.75, Section 21.4.4, Step 2
    // Set TSPC[7] to lock down the Thermal Sensor Policy Control(TSPC) and Aux Trip Point Settings
    //
    Mmio8(*TBARB, R_PCH_TBARB_TSPC) |= B_PCH_TBARB_TSPC_PLD;

    //
    // PCH Bios Spec 0.75, Section 21.4.4, Step 3
    // Set TSLOCK[2] to lock down the Hot Trip Point setting
    //
    Mmio8(*TBARB, R_PCH_TBARB_TSLOCK) |= B_PCH_TBARB_TSLOCK_LC;

//////////////////////////////////
#if IBEX_PEAK_SKU == 1
    Mmio16(*TBARB, R_PCH_TBARB_PPEC) = SbSetupPtr->PPEC;

    Mmio16(*TBARB, R_PCH_TBARB_PTL) = SbSetupPtr->PTL;

    Mmio16(*TBARB, R_PCH_TBARB_MMGPC) = SbSetupPtr->MMGPC;

    Mmio16(*TBARB, R_PCH_TBARB_MPCPC) = SbSetupPtr->MPCPC;
#endif

    Mmio8(*TBARB, (R_PCH_TBARB_PTA + 1)) = SbSetupPtr->PTA;
    Mmio8(*TBARB, R_PCH_TBARB_PTA) = SbSetupPtr->PTA_OFFSET;

//####    Mmio8(*TBARB, (R_PCH_TBARB_MGTA + 1)) = SbSetupPtr->MGTA;
//####    Mmio8(*TBARB, R_PCH_TBARB_MGTA) = SbSetupPtr->MGTA_OFFSET;
//////////////////////////////////
    //
    // PCH Bios Spec 0.75, Section 21.4.4, Step 4
    // Set AE[7] to lock down PPEC, CTA, PTA and MGTA
    //
    if (SbSetupPtr->AlertEnableLock)
      Mmio8(*TBARB, R_PCH_TBARB_AE) |= B_PCH_TBARB_AE_LockEnable;
    else
      Mmio8(*TBARB, R_PCH_TBARB_AE) &= ~B_PCH_TBARB_AE_LockEnable;

  } // if(!(Mmio32(SB_RCBA, R_FUNCTION_DISABLE) & B_THERMAL_DISABLE))
                                        // <(P090109B)

  return EFI_SUCCESS;
}
#endif
#endif                                  // <(P040709B)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: ProgramSSIDTable
//
// Description:
//
// Input:IN CONST EFI_PEI_SERVICES **PeiServices,
//       IN EFI_PEI_PCI_CFG2_PPI *PciCfg,
//       IN UINT32 *SSIDRegTable
//
// Output: None
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProgramSSIDTable(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI *PciCfg,
    IN SB_PCI_DEVICE_SSID *SSIDRegTable)// (P040809A)

{
    UINT32 Data32;
    UINT16 wIndex;
                                        // (P040809A)>
    UINT32 D29F0Addr = (UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_0, PCI_SVID);
    UINT32 D26F0Addr = (UINT32)SB_PCIE_CFG_ADDRESS(USB_BUS, USB_DEV_26, USB_FUNC_0, PCI_SVID);

    for (wIndex = 0; (SSIDRegTable + wIndex)->BDFReg != 0; wIndex++)
    {
        Data32 = Mmio32(((SSIDRegTable + wIndex)->BDFReg & ~(0xFF)), PCI_VID);

        if (((SSIDRegTable + wIndex)->BDFReg == D29F0Addr) ||
            ((SSIDRegTable + wIndex)->BDFReg == D26F0Addr))
            Mmio8(((SSIDRegTable + wIndex)->BDFReg & ~(0xFF)), ICH_REG_EHCI_ACCTL) |= BIT00;

        if ((SSIDRegTable + wIndex)->DevSSID != 0xFFFFFFFF && (Data32 != 0xFFFFFFFF))
            Data32 = (SSIDRegTable + wIndex)->DevSSID;

        if (Data32 != 0xFFFFFFFF)
            Mmio32((SSIDRegTable + wIndex)->BDFReg, 0) = Data32;

        if (((SSIDRegTable + wIndex)->BDFReg == D29F0Addr) ||
            ((SSIDRegTable + wIndex)->BDFReg == D26F0Addr))
            Mmio8(((SSIDRegTable + wIndex)->BDFReg & ~(0xFF)), ICH_REG_EHCI_ACCTL) &= ~(BIT00);
                                        // <(P040809A)
    }
}

#if H55_3420_USB_PORTS_WORKAROUND       // (P121409A)>
                                        // [ EIP36182 ] PCH/IbexPeak BSU REV:1.05 - Errata13
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: H55_3420_UsbPortsWA
//
// Description: Intel H55 Express Chipset and Intel 3420 Chipset May Report
//              Incorrect Number of USB Ports.
//              Problem: The Intel H55 Express Chipset and Intel 3420 Chipset
//              support 6 ports on RMH #1 and may incorrectly report 8 USB
//              ports in the bNbrPorts field of the RMH hub descriptor.
//
//              *Intel 5 Series Chipset and Intel 3400 Series Chipset
//               Specification Update, Revision 002, Version 1.4
//              *
// Input: None
//
// Output: None
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID H55_3420_UsbPortsWA(VOID)
{
  UINT16    wPCHDid = MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_DID);
  UINT8     SleepType;

  SleepType = IoRead8(PM_BASE_ADDRESS + ICH_IOREG_PM1_CNT + 1) & 0x1C;

  // H55/3420/HM55
  if ((wPCHDid == 0x3B06) || (wPCHDid == 0x3B14) || (wPCHDid == 0x3B09))
  {
    // PWR_FLR & S4?
    if ((MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) & BIT01) && \
        (SleepType == 0x18))
    {
      if (SBLib_CmosRead(SB_TEMP_CMOS1) != 0xAA)
      {
        SBLib_CmosWrite(SB_TEMP_CMOS1, 0xAA);
        SBLib_ResetSystem(HardReset);
      }
    }
  }
}
#endif                                  // <(P121409A)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBBeforeInitMemory
//
// Description:
//
// Input:IN CONST EFI_PEI_SERVICES  **PeiServices,
//       IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
//       IN VOID    *NullPpi
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBBeforeInitMemory(
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID    *NullPpi
)
{
    EFI_STATUS  Status = EFI_SUCCESS;


#if defined ME_SUPPORT && ME_SUPPORT == 1
    VOID   *pHobList;
    MEINFO_HOB  *MeInfoHob;

                                        // (P072709A)>
 #ifdef HECI_FW_MODE_SECOVR_JMPR
    EFI_GUID gAmiPeiHeciPpiGuid = AMI_PEI_HECI_PROTOCOL_GUID;
    AMI_HECI_PROTOCOL *pPeiHeci;
    UINT32 MeStatus;
 #endif                                 // <(P072709A)


                                        // (P121409A)>
#if H55_3420_USB_PORTS_WORKAROUND
    H55_3420_UsbPortsWA();
#endif                                  // <(P121409A)


    // ME Init Before MRC
    Status = (*PeiServices)->GetHobList(PeiServices, (VOID**) & pHobList);
    ASSERT_PEI_ERROR(PeiServices, Status);

    // Find ME Info Hob.
    MeInfoHob = (MEINFO_HOB*)pHobList;

  while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &MeInfoHob)))
    {
        if (guidcmp(&MeInfoHob->EfiHobGuidType.Name, &MeInfoHobGuid) == 0)
            break;
    }
                                        // (P072709A)>
    if (!EFI_ERROR(Status))
    {
 #ifdef HECI_FW_MODE_SECOVR_JMPR
        Status = (*PeiServices)->LocatePpi(PeiServices, &gAmiPeiHeciPpiGuid, 0, 0, &pPeiHeci);
        if (!EFI_ERROR(Status))
        {
          Status = pPeiHeci->GetMeStatus(&MeStatus);
          if (!EFI_ERROR(Status) && (((MeStatus & HECI_FW_MODE_MASK) >> 16) != HECI_FW_MODE_SECOVR_JMPR))
            return EFI_SUCCESS;
        }
 #else
        return EFI_SUCCESS;
 #endif
    }

    if ((MmPci16(HECI1_BUS, HECI1_DEVICE, HECI1_FUNC, PCI_VID) != 0xffff) &&
        (MmPci16(HECI1_BUS, HECI1_DEVICE, HECI1_FUNC, PCI_CMD) != 0))
        MmPci16(HECI1_BUS, HECI1_DEVICE, HECI1_FUNC, PCI_CMD) = 0;
                                        // <(P072709A)
#endif

    Mmio32(SB_RCBA, ICH_RCRB_FD2) |= (BIT01 + BIT02 + BIT03 + BIT04);

    return EFI_SUCCESS;
}

                                        // (P051509A)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES           **PeiServices,
//        IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
//        IN VOID                       *NullPpi
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SBAfterInitMemory(
  IN CONST EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *NullPpi)
{
  EFI_STATUS   Status;

  SB_SETUP_CONFIGURATION *SbSetupPtr;   // (P010609A)
  EFI_BOOT_MODE          BootMode;      // (P032409A)


  Status = gSBPpi.TaskProcess(PeiServices, AMI_SB_GET_SETUP_CONFIG, &SbSetupPtr); // (P010609A)
  ASSERT_PEI_ERROR(PeiServices, Status);

                                        // (P032409A)>
  // Determine boot mode
  Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
  ASSERT_PEI_ERROR(PeiServices, Status);
                                        // <(P032409A)

  // Initialize SATA specific registers
  InitializeSATA(PeiServices);          // (P030309E)

  if(BootMode != BOOT_ON_S3_RESUME)
    InitAcpiPmRegAfterMemory(PeiServices, SbSetupPtr);

  if(MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_RID) <= PCH_A1)   // (P051109A)
    PchUhciAxPatch(PeiServices);

#if DISABLE_RMH_IN_RECOVERY             // (P051509C), (P032409A)>
  if((BootMode == BOOT_IN_RECOVERY_MODE) &&
     (MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_RID) < PCH_B2))
    RmhPatchForRecoveryMode(PeiServices, BootMode, SbSetupPtr);
#endif                                  // <(P051509C), (P032409A)

  // Clear Global Reset Bit             // (P072709A)

  MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_PMIR + 2) &= ~(BIT04);

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InitAcpiPmRegAfterMemory
//
// Description:
//
// Input:  IN CONST EFI_PEI_SERVICES    **PeiServices,
//         SB_SETUP_CONFIGURATION *SbSetupPtr
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitAcpiPmRegAfterMemory(
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  IN SB_SETUP_CONFIGURATION *SbSetupPtr
)
{
  UINT16   Buffer16;
  UINT32   Buffer32;

  // Restore the SLP_TYP bits in ICH to working state
  IoWrite8(PM_BASE_ADDRESS + ICH_IOREG_PM1_CNT + 1, 0);

                                        // [EIP22149]>
  // Clear the power button status bit in PM space.
  IoWrite16(PM_BASE_ADDRESS + ICH_IOREG_PM1_STS, BIT08);
                                        // <[EIP22149]

  // Global SMI disable
  Buffer32 = IoRead32(PM_BASE_ADDRESS + ICH_IOREG_GPE0_EN);
  Buffer32 &= 0x00008480;
  IoWrite32(PM_BASE_ADDRESS + ICH_IOREG_GPE0_EN, Buffer32);

  Buffer32 = IoRead32(PM_BASE_ADDRESS + ICH_IOREG_GPE0_EN + 4);
  Buffer32 &= 0xFFFFFFFE;
  IoWrite32(PM_BASE_ADDRESS + ICH_IOREG_GPE0_EN + 4, Buffer32);

  // Clear the PWR_FLR bits in the General PM Configuration Register 0A4h
  MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) |= BIT01;

                                        // (P012510B)>
  // Enabling SLP_S3# Stretch
  Buffer16 = MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3);
  Buffer16 &= ~(BIT10 | BIT11);
  Buffer16 |= BIT11;
  MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) = Buffer16;
                                        // <(P012510B)

  // Set SLP_S4# Minimum Assertion Width and enable SLP_S4# Assertion Stretch Enable
                                        // (P121409B)>
  if (SbSetupPtr->SlpS4AsseEn) {
    Buffer16 = MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3);
    Buffer16 |= BIT03;
    Buffer16 &= ~(0x03 << 4);
    Buffer16 |= (SbSetupPtr->SlpS4AsseW << 4);
    MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) = Buffer16;
  } else {
    MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) &= ~BIT03;
  }
                                        // <(P121409B)

  // Set AC power loss
  MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) &= ~(BIT00);
  if (SbSetupPtr->SetupDataValidHob)    // (P010609A)
  {
    if (SbSetupPtr->AfterG3 == 0)       // (P010609A)
      MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) |= BIT00;
  }
  else
    MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3) |= BIT00;

  return EFI_SUCCESS;
}

                                        // (P120408A)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: PchUhciAxPatch
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES           **PeiServices,
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PchUhciAxPatch(
  IN CONST EFI_PEI_SERVICES    **PeiServices
)
{
  EFI_PEI_CPU_IO_PPI     *CpuIo;
  EFI_PEI_PCI_CFG2_PPI    *PciCfg;

  UINT8    Buffer8;
  UINT16   wIndex;
  UINT16   Buffer32;
  UINT32   UhciDevTable[] =
  {
     PEI_PCI_CFG_ADDRESS(USB_BUS, USB_DEV_26, USB_FUNC_1, PCI_VID),
     PEI_PCI_CFG_ADDRESS(USB_BUS, USB_DEV_26, USB_FUNC_2, PCI_VID),
     PEI_PCI_CFG_ADDRESS(USB_BUS, USB_DEV_26, USB_FUNC_3, PCI_VID),
     PEI_PCI_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_1, PCI_VID),
     PEI_PCI_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_2, PCI_VID),
     PEI_PCI_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_3, PCI_VID),
     PEI_PCI_CFG_ADDRESS(USB_BUS, USB_DEV_29, USB_FUNC_4, PCI_VID),
     0
  };

  CpuIo = (*PeiServices)->CpuIo;
  PciCfg = (*PeiServices)->PciCfg;

  for (wIndex = 0; UhciDevTable[wIndex] != 0; wIndex++)
  {
    PciCfg->Read(
                 PeiServices,
                 PciCfg,
                 EfiPeiPciCfgWidthUint32,
                 (UhciDevTable[wIndex] & ~(0xFF)),
                 &Buffer32);

    if (Buffer32 != 0xFFFFFFFF)
    {
     // Write-once UHCI Capabilities Pointer
     PciCfg->Read(PeiServices, PciCfg, EfiPeiPciCfgWidthUint8, (UhciDevTable[wIndex] + PCI_CAPP), &Buffer8);
     PciCfg->Write(PeiServices, PciCfg, EfiPeiPciCfgWidthUint8, (UhciDevTable[wIndex] + PCI_CAPP), &Buffer8);

     PciCfg->Read(PeiServices, PciCfg, EfiPeiPciCfgWidthUint8, (UhciDevTable[wIndex] + 0xC8), &Buffer8);
     Buffer8 |= BIT02;
     PciCfg->Write(PeiServices, PciCfg, EfiPeiPciCfgWidthUint8, (UhciDevTable[wIndex] + 0xC8), &Buffer8);
    }                             // (P051109A)
  }
  return EFI_SUCCESS;
}                                       // <(P120408A)


                                        // (P032409A)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: RmhPatchForRecoveryMode
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES    **PeiServices,
//        SB_SETUP_CONFIGURATION *SbSetupPtr
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RmhPatchForRecoveryMode(
 IN  IN CONST EFI_PEI_SERVICES    **PeiServices,
 IN  SB_SETUP_CONFIGURATION *SbSetupPtr
)
{
  // Disable RMH
  // Once RMH is disabled, EHCI will be mapped to function 7,
  // and UHCI will start from Function 0.(IBX B0)
                                        // (P040209A)>
  MmPci8(USB_BUS, USB_DEV_26, USB_FUNC_0, ICH_REG_EHCI_ACCTL) |= BIT00;  // (P040709C)
  MmPci8(USB_BUS, USB_DEV_29, USB_FUNC_0, ICH_REG_EHCI_ACCTL) |= BIT00;  // (P040709C)

                                        // [EIP21269]>
  MmPci32(USB_BUS, USB_DEV_26, USB_FUNC_0, ICH_REG_EHCI_MEMBASE) = SB_TEMP_MMIO_BASE;
  MmPci32(USB_BUS, USB_DEV_26, USB_FUNC_0, ICH_REG_EHCI_PCICMD) |= BIT01;

  Mmio8(SB_TEMP_MMIO_BASE, 0x20) |= BIT01;  // HCRESET BIT

  MmPci32(USB_BUS, USB_DEV_26, USB_FUNC_0, ICH_REG_EHCI_PCICMD) &= ~BIT01;
  MmPci32(USB_BUS, USB_DEV_26, USB_FUNC_0, ICH_REG_EHCI_MEMBASE) = 0;

  MmPci32(USB_BUS, USB_DEV_29, USB_FUNC_0, ICH_REG_EHCI_MEMBASE) = SB_TEMP_MMIO_BASE;
  MmPci32(USB_BUS, USB_DEV_29, USB_FUNC_0, ICH_REG_EHCI_PCICMD) |= BIT01;

  Mmio8(SB_TEMP_MMIO_BASE, 0x20) |= BIT01;  // HCRESET BIT

  MmPci32(USB_BUS, USB_DEV_29, USB_FUNC_0, ICH_REG_EHCI_PCICMD) &= ~BIT01;
  MmPci32(USB_BUS, USB_DEV_29, USB_FUNC_0, ICH_REG_EHCI_MEMBASE) = 0;
                                        // <[EIP21269]

  Mmio8(SB_RCBA, ICH_RCRB_FD2) |= BIT00;  // Disable RMH.

  MmPci8(USB_BUS, USB_DEV_26, USB_FUNC_7, ICH_REG_EHCI_ACCTL) &= ~(BIT00);
  MmPci8(USB_BUS, USB_DEV_29, USB_FUNC_7, ICH_REG_EHCI_ACCTL) &= ~(BIT00);
                                        // <(P040209A)

  SbSetupPtr->Rmh = 0;

        // Enable All UHCIs
  Mmio32(SB_RCBA, R_FUNCTION_DISABLE) &= ~(B_UHCI_1_DISABLE + // UHCI1
                               B_UHCI_2_DISABLE + // UHCI2
                               B_UHCI_3_DISABLE + // UHCI3
                               B_UHCI_4_DISABLE + // UHCI4
                               B_UHCI_5_DISABLE + // UHCI5
                               B_UHCI_6_DISABLE + // UHCI6
                               B_UHCI_9_DISABLE); // UHCI9

  return EFI_SUCCESS;
}                                       // <(P051509A), (P032409A)


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBPEI_CspResetSystem
//
// Description: This function is the reset call interface function published
//              by the reset PPI.
//
// Input: PeiServices  Pointer to the PEI services table
//
// Output:SYSTEM RESET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SBPEI_CspResetSystem(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN EFI_RESET_TYPE ResetType
)
{
    SBLib_ResetSystem(ResetType);

    // We should never get this far
    return EFI_SUCCESS;
}


                                        // (P030309E),(P020309F)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InitializeSATA
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES **PeiServices,
//
// Output: None
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitializeSATA(
    IN CONST EFI_PEI_SERVICES **PeiServices)
{
    UINT32 dData;
    UINT16 wPCHSku = MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_DID) & BIT00;
    UINT8  bPCHRid = MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_RID);

// off 0x18
    if (bPCHRid >= PCH_B0)
    {
        MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x18;
        MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0x001C7000;
    }


// off 0x28
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x28;
    dData = 0x0A000044;                   // Ax Stepping
    if (bPCHRid >= PCH_B0)
        dData = 0x0A000033;                // B0 Stepping
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = dData;

// off 0x3E
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x3C;
    dData = MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD);
    if (bPCHRid <= PCH_A1)
    {
        dData &= ~(BIT23 + BIT22);
        dData |= BIT22;
    }
    if (bPCHRid >= PCH_B0)
    {
        dData &= 0x0000FFFF;
        dData |= 0x04640000;
    }
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = dData;

// off 0x40
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x40;
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD + 2) = 0x22;

// off 0x50
    if (bPCHRid <= PCH_A1)               // Ax Stepping
    {
        MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x50;
        MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0x39CE739C;
    }

// off 0x54[23:00]=0x00555555
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x54;
    dData = MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD);
    dData &= 0xFF000000;
    dData |= 0x00555555;
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = dData;

// off 0x64[31:00]=0xCCCCCCCC
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x64;
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0xCCCCCCCC;

// off 0x68[15:00]=0xCCCC
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x68;
    MmPci16(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0xCCCC;

//off 0x78[31:16] = 0x8888
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x78;
    MmPci16(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD + 2) = 0x8888;

//off 0x84
    if (bPCHRid >= PCH_B0)                // B0
    {
        MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x84;
        MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0x001C7000;
    }

//off 0x88
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x88;
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0x88888888;

//off 0x8C
    if (bPCHRid >= PCH_B0)                // B0
    {
      MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x8C;
      MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0x55555555;
    }

//off 0x94
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x94;
    MmPci16(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0x5555;

//off 0xA0
    if (bPCHRid >= PCH_B0)                // B0
    {
        MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0xA0;
        MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0x001C7000;
    }

//off 0xA8
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0xA8;
    dData = 0x0C0C0C0C;
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = dData;

//off 0xC4
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0xC4;
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = dData;

//off 0xC8
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0xC8;
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = dData;

//off 0xD4
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0xD4;
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRD) = 0x10000000;

//#### D31:F02:98h should be programmed before D31:F2:92h been set. // (P120408A)

//off 0x00
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_SIRI) = 0x00;

    // SB BIOS Spec(Rev:0.90)
    // 5.1 Miscellaneous Register Setting and Usage Models
    // Step 5.
    MmPci16(SATA0_BUS, SATA0_DEV, SATA0_FUNC, ICH_REG_SATA_PCS) |= BIT15;


                                        // (P051509A)>
                                        // (P101309B), (P120408A)>
// IbexPeak Spec. v0.6, Ch 17.1.6
// D31:F2:98h should be programmed before D31:F2:92h been set.
    dData = MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, 0x98);
    dData &= ~(0x00401FE0);
// Step 5
    dData |= BIT22;  // reg#0x98[22]=1b
// Step 6
                                        // [ EIP36182 ] PCH/IbexPeak BSU REV:1.05 - Errata19 >>
//    dData |= BIT19;  // reg#0x98[19]=1b
    dData |= (BIT20 + BIT19);   // reg#0x98[20:19]=11b
                                        // <<[ EIP36182 ]
// Step 7
    dData |= BIT16;  // reg#0x98[16]=1b
// Step 8
    dData |= (0x04 << 7); // reg#0x98[12:7]=0x04
// Step 9
                                        // [ EIP36182 ] PCH/IbexPeak BSU REV:1.05 - Errata20 >>
//    dData |= BIT5;  // reg#0x98[6:5]=01b
    dData &= ~(BIT6 + BIT5);    // reg#0x98[6:5]=00b
                                        // <<[ EIP36182 ]
    MmPci32(SATA0_BUS, SATA0_DEV, SATA0_FUNC, 0x98) = dData;
                                        // <(P101309B), (P120408A)

    // Enable SATA 1 ports.
    MmPci8(SATA0_BUS, SATA0_DEV, SATA0_FUNC, R_SATA_PCS) = (B_SATA_PORT_0_ENABLED +
                                         B_SATA_PORT_1_ENABLED +
                                         B_SATA_PORT_2_ENABLED +
                                         B_SATA_PORT_3_ENABLED); //0x92
    // Enable SATA 2 ports.
    MmPci8(SATA1_BUS, SATA1_DEV, SATA1_FUNC, R_SATA_PCS) = (B_SATA_PORT_0_ENABLED +
                                         B_SATA_PORT_1_ENABLED); //0x92
                                        // <(P051509A)

    return EFI_SUCCESS;
}
                                        // <(P030309E),(P020309F)


                                        // (P010609A)>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SbCreateConfiguration
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES **PeiServices,
//        OUT SB_SETUP_CONFIGURATION **SbSetup
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SbCreateConfiguration(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    OUT SB_SETUP_CONFIGURATION **SbSetup
)
{
    EFI_STATUS Status;
//    UINT16 wIndex;                    // [ EIP53941 ]
    SB_CONFIGURATION_HOB *SbSetupHob;

    Status = (*PeiServices)->CreateHob(PeiServices,
                                       EFI_HOB_TYPE_GUID_EXTENSION,
                                       sizeof(SB_CONFIGURATION_HOB),
                                       &SbSetupHob);
    ASSERT_PEI_ERROR(PeiServices, Status);
    if (EFI_ERROR(Status))
        return Status;

    SbSetupHob->EfiHobGuidType.Name = gSbSetupHobGuid;

    GetSbSetupData(PeiServices, &SbSetupHob->Configuration, TRUE);  // [ EIP53941 ]
    *SbSetup = &SbSetupHob->Configuration;

// [ EIP53941 ]
//// Initialize the default setting of SbSetupHob.
//// If Setup data is invalid, BIOS code will reference this table.
//    SbSetupHob->Configuration.Smbus     = 1;
//    SbSetupHob->Configuration.SBGbELan  = 1;
//    SbSetupHob->Configuration.SBGbELanLock   = 0;
//    SbSetupHob->Configuration.GbEWakeOnLanS5 = 1;
//    SbSetupHob->Configuration.AfterG3   = 0;
//    SbSetupHob->Configuration.SlpS4AsseEn = 1;  // (P121409B)
//    SbSetupHob->Configuration.SlpS4AsseW  = 0;  // (P121409B)
//    SbSetupHob->Configuration.Azalia    = 0;
//    SbSetupHob->Configuration.HdmiCodec = 0;  // (P042009A)
//#if HPET_SUPPORT
//    SbSetupHob->Configuration.Hpet      = 1;
//#endif
//#if RC_PORT_0                           // (EIP22523)>
//    SbSetupHob->Configuration.PciEPort1 = 1;
//    SbSetupHob->Configuration.PcieHp1   = 0;
//#if RC_PORT_1
//    SbSetupHob->Configuration.PciEPort2 = 1;
//    SbSetupHob->Configuration.PcieHp2   = 0;
//#endif
//#if RC_PORT_2
//    SbSetupHob->Configuration.PciEPort3 = 1;
//    SbSetupHob->Configuration.PcieHp3   = 0;
//#endif
//#if RC_PORT_3
//    SbSetupHob->Configuration.PciEPort4 = 1;
//    SbSetupHob->Configuration.PcieHp4   = 0;
//#endif
//#if RC_PORT_4
//    SbSetupHob->Configuration.PciEPort5 = 1;
//    SbSetupHob->Configuration.PcieHp5   = 0;
//#endif
//#if RC_PORT_5
//    SbSetupHob->Configuration.PciEPort6 = 1;
//    SbSetupHob->Configuration.PcieHp6   = 0;
//#endif
//#if RC_PORT_6
//    SbSetupHob->Configuration.PciEPort7 = 1;
//    SbSetupHob->Configuration.PcieHp7   = 0;
//#endif
//#if RC_PORT_7
//    SbSetupHob->Configuration.PciEPort8 = 1;
//    SbSetupHob->Configuration.PcieHp8   = 0;
//#endif
//#endif                                  // <(EIP22523)
//    SbSetupHob->Configuration.Usb        = 1;
//    SbSetupHob->Configuration.Ehci1      = 1;
//    SbSetupHob->Configuration.Ehci2      = 1;
//    SbSetupHob->Configuration.Rmh        = 2;  // (P020309E)
//    SbSetupHob->Configuration.Uhci1      = 1;
//    SbSetupHob->Configuration.Uhci2      = 1;
//    SbSetupHob->Configuration.Uhci3      = 1;
//    SbSetupHob->Configuration.Uhci4      = 1;
//    SbSetupHob->Configuration.Uhci5      = 1;
//    SbSetupHob->Configuration.Uhci6      = 1;
//    SbSetupHob->Configuration.Uhci7      = 1;
//    SbSetupHob->Configuration.SataMode   = 1;
//    SbSetupHob->Configuration.UsbPort0   = 1;  // (P021709A)>
//    SbSetupHob->Configuration.UsbPort1   = 1;
//    SbSetupHob->Configuration.UsbPort2   = 1;
//    SbSetupHob->Configuration.UsbPort3   = 1;
//    SbSetupHob->Configuration.UsbPort4   = 1;
//    SbSetupHob->Configuration.UsbPort5   = 1;
//    SbSetupHob->Configuration.UsbPort6   = 1;
//    SbSetupHob->Configuration.UsbPort7   = 1;
//    SbSetupHob->Configuration.UsbPort8   = 1;
//    SbSetupHob->Configuration.UsbPort9   = 1;
//    SbSetupHob->Configuration.UsbPort10  = 1;
//    SbSetupHob->Configuration.UsbPort11  = 1;
//    SbSetupHob->Configuration.UsbPort12  = 1;
//    SbSetupHob->Configuration.UsbPort13  = 1;  // <(P021709A)
//    SbSetupHob->Configuration.SataController0 = 2;
//    SbSetupHob->Configuration.SataController1 = 1;
//    SbSetupHob->Configuration.SataSSS    = 0;
//    SbSetupHob->Configuration.ESataPort0 = 0;
//    SbSetupHob->Configuration.ESataPort1 = 0;
//    SbSetupHob->Configuration.ESataPort2 = 0;
//    SbSetupHob->Configuration.ESataPort3 = 0;
//    SbSetupHob->Configuration.ESataPort4 = 0;
//    SbSetupHob->Configuration.ESataPort5 = 0;
//    SbSetupHob->Configuration.SataHpP0   = 0;
//    SbSetupHob->Configuration.SataHpP1   = 0;
//    SbSetupHob->Configuration.SataHpP2   = 0;
//    SbSetupHob->Configuration.SataHpP3   = 0;
//    SbSetupHob->Configuration.SataHpP4   = 0;
//    SbSetupHob->Configuration.SataHpP5   = 0;
//                                        // (P090109B)>
//#if defined ME_SUPPORT && ME_SUPPORT == 1
//#if THERMAL_REPORTING_SUPPORT
//    SbSetupHob->Configuration.MCHTempReadEnable          = 1;
//    SbSetupHob->Configuration.PCHTempReadEnable          = 1;
//    SbSetupHob->Configuration.CPUEnergyReadEnable        = 1;
//    SbSetupHob->Configuration.CPUTempReadEnable          = 1;
//    SbSetupHob->Configuration.ThermalDataReportingEnable = 1;
//#if IBEX_PEAK_SKU == 1
//    SbSetupHob->Configuration.PPEC          = 0;
//    SbSetupHob->Configuration.PTL           = 0;
//    SbSetupHob->Configuration.MMGPC         = 0;
//    SbSetupHob->Configuration.MPPC          = 0;
//    SbSetupHob->Configuration.MPCPC         = 0;
//#endif
//    SbSetupHob->Configuration.PTA           = 128;
//    SbSetupHob->Configuration.PTA_OFFSET    = 140;
//    SbSetupHob->Configuration.MGTA          = 128;
//    SbSetupHob->Configuration.MGTA_OFFSET   = 140;
//
//    SbSetupHob->Configuration.AlertEnableLock = 0;
//    SbSetupHob->Configuration.CPUAlert      = 0;
//    SbSetupHob->Configuration.MCHAlert      = 0;
//    SbSetupHob->Configuration.PCHAlert      = 0;
//    SbSetupHob->Configuration.DIMMAlert     = 0;
//    SbSetupHob->Configuration.TrEnabled     = 0;
//    SbSetupHob->Configuration.SMBusECMsgLen = 1;
//    SbSetupHob->Configuration.SMBusECMsgPEC = 1;
//    SbSetupHob->Configuration.TrSmbusConfig = 0;
//    SbSetupHob->Configuration.TsOnDimm0     = 0;
//    SbSetupHob->Configuration.TsOnDimm1     = 0;
//    SbSetupHob->Configuration.TsOnDimm2     = 0;
//    SbSetupHob->Configuration.TsOnDimm3     = 0;
//#endif
//#endif
//                                        // <(P090109B)
//
//    for (wIndex = 0; SbUpdateConfigFuncTbl[wIndex] != NULL; wIndex++)
//    {
//        Status = SbUpdateConfigFuncTbl[wIndex](PeiServices, &SbSetupHob->Configuration);
//        ASSERT_PEI_ERROR(PeiServices, Status);
//        if (EFI_ERROR(Status))
//            return Status;
//    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SbGetConfiguration
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES **PeiServices,
//        OUT SB_SETUP_CONFIGURATION **SbSetup
//
// Output: Status
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SbGetConfiguration(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    OUT SB_SETUP_CONFIGURATION **SbSetup
)
{
    EFI_STATUS Status;

    SB_CONFIGURATION_HOB *SbSetupHob;
    VOID *pHobList;

    Status = (*PeiServices)->GetHobList(PeiServices, (VOID**) & pHobList);

    SbSetupHob = (SB_CONFIGURATION_HOB*)pHobList;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &SbSetupHob)))
    {
        if (guidcmp(&SbSetupHob->EfiHobGuidType.Name, &gSbSetupHobGuid) == 0)
        {
            break;
        }
    }
    if (EFI_ERROR(Status))
        Status = EFI_NOT_FOUND;
    else
    {
        Status = EFI_SUCCESS;
        *SbSetup = &SbSetupHob->Configuration;
    }

    return Status;
}

// [ EIP53941 ]
//#if defined SB_GET_SETUP_SUPPORT && SB_GET_SETUP_SUPPORT == 1
////<AMI_PHDR_START>
////----------------------------------------------------------------------------
//// Procedure: SbUpdateSetupToHob
////
//// Description:
////
//// Input: IN EFI_PEI_SERVICES **PeiServices,
////        IN OUT SB_SETUP_CONFIGURATION *SbSetup
////
//// Output: None
////
//// Notes:
////
////----------------------------------------------------------------------------
////<AMI_PHDR_END>
//
//EFI_STATUS SbUpdateSetupToHob(
//    IN EFI_PEI_SERVICES **PeiServices,
//    IN OUT SB_SETUP_CONFIGURATION *SbSetup)
//{
//    EFI_STATUS Status;
//    EFI_PEI_READ_ONLY_VARIABLE_PPI *ReadOnlyVariable;
//    SETUP_DATA  SetupData;
//    BOOLEAN     IsSetupDataValid;
//    UINTN       VariableSize;
//    CHAR16      SetupVariable[] = L"Setup";
//
//    Status = (*PeiServices)->LocatePpi(
//                 PeiServices,
//                 &gEfiPeiReadOnlyVariablePpiGuid,
//                 0,
//                 NULL,
//                 &ReadOnlyVariable
//             );
//    ASSERT_PEI_ERROR(PeiServices, Status);
//
//    VariableSize = sizeof(SETUP_DATA);
//    Status = ReadOnlyVariable->GetVariable(
//                 PeiServices,
//                 SetupVariable,
//                 &gEfiSetupGuid,
//                 NULL,
//                 &VariableSize,
//                 &SetupData
//             );
//    IsSetupDataValid = !EFI_ERROR(Status);
//
//    if (!IsSetupDataValid)
//    {
//        PEI_TRACE((-1, PeiServices, "Setup variable not valid.\n"));
//        return Status;
//    }
//
//    SbSetup->Smbus          = SetupData.Smbus;
//    SbSetup->SBGbELan       = SetupData.SBGbELan;
//    SbSetup->SBGbELanLock   = SetupData.SBGbELanLock; // (P072209A)
//    SbSetup->GbEWakeOnLanS5 = SetupData.GbEWakeOnLanS5;
//    SbSetup->AfterG3        = SetupData.AfterG3;
//    SbSetup->SlpS4AsseEn    = SetupData.SlpS4AsseEn;  // (P121409B)
//    SbSetup->SlpS4AsseW     = SetupData.SlpS4AsseW;   // (P121409B)
//    SbSetup->Azalia         = SetupData.Azalia;
//    SbSetup->HdmiCodec      = SetupData.HdmiCodec;    // (P042009A)
//#if HPET_SUPPORT
//    SbSetup->Hpet           = SetupData.Hpet;
//#endif
//#if RC_PORT_0                           // (EIP22523)>
//    SbSetup->PciEPort1      = SetupData.PciEPort1;
//    SbSetup->PcieHp1        = SetupData.PcieHp1;
//#if RC_PORT_1
//    SbSetup->PciEPort2      = SetupData.PciEPort2;
//    SbSetup->PcieHp2        = SetupData.PcieHp2;
//#endif
//#if RC_PORT_2
//    SbSetup->PciEPort3      = SetupData.PciEPort3;
//    SbSetup->PcieHp3        = SetupData.PcieHp3;
//#endif
//#if RC_PORT_3
//    SbSetup->PciEPort4      = SetupData.PciEPort4;
//    SbSetup->PcieHp4        = SetupData.PcieHp4;
//#endif
//#if RC_PORT_4
//    SbSetup->PciEPort5      = SetupData.PciEPort5;
//    SbSetup->PcieHp5        = SetupData.PcieHp5;
//#endif
//#if RC_PORT_5
//    SbSetup->PciEPort6      = SetupData.PciEPort6;
//    SbSetup->PcieHp6        = SetupData.PcieHp6;
//#endif
//#if RC_PORT_6
//    SbSetup->PciEPort7      = SetupData.PciEPort7;
//    SbSetup->PcieHp7        = SetupData.PcieHp7;
//#endif
//#if RC_PORT_7
//    SbSetup->PciEPort8      = SetupData.PciEPort8;
//    SbSetup->PcieHp8        = SetupData.PcieHp8;
//#endif
//#endif                                  // <(EIP22523)
//
//    SbSetup->Usb            = SetupData.Usb;
//    SbSetup->Ehci1          = SetupData.Ehci1;
//    SbSetup->Ehci2          = SetupData.Ehci2;
//    SbSetup->Rmh            = SetupData.Rmh;  // (P020309E)
//    SbSetup->Uhci1          = SetupData.Uhci1;
//    SbSetup->Uhci2          = SetupData.Uhci2;
//    SbSetup->Uhci3          = SetupData.Uhci3;
//    SbSetup->Uhci4          = SetupData.Uhci4;
//    SbSetup->Uhci5          = SetupData.Uhci5;
//    SbSetup->Uhci6          = SetupData.Uhci6;
//    SbSetup->Uhci7          = SetupData.Uhci7;
//    SbSetup->UsbPort0       = SetupData.UsbPort0;   //(P021709A)>
//    SbSetup->UsbPort1       = SetupData.UsbPort1;
//    SbSetup->UsbPort2       = SetupData.UsbPort2;
//    SbSetup->UsbPort3       = SetupData.UsbPort3;
//    SbSetup->UsbPort4       = SetupData.UsbPort4;
//    SbSetup->UsbPort5       = SetupData.UsbPort5;
//    SbSetup->UsbPort6       = SetupData.UsbPort6;
//    SbSetup->UsbPort7       = SetupData.UsbPort7;
//    SbSetup->UsbPort8       = SetupData.UsbPort8;
//    SbSetup->UsbPort9       = SetupData.UsbPort9;
//    SbSetup->UsbPort10      = SetupData.UsbPort10;
//    SbSetup->UsbPort11      = SetupData.UsbPort11;
//    SbSetup->UsbPort12      = SetupData.UsbPort12;//<(P021709A)
//    SbSetup->UsbPort13      = SetupData.UsbPort13;//(P040909A)
//    SbSetup->SataMode       = SetupData.SataMode;
//    SbSetup->SataController0 = SetupData.SataController0;
//    SbSetup->SataController1 = SetupData.SataController1;
//    SbSetup->SataSSS        = SetupData.SataSSS;
//    SbSetup->ESataPort0     = SetupData.ESataPort0;
//    SbSetup->ESataPort1     = SetupData.ESataPort1;
//    SbSetup->ESataPort2     = SetupData.ESataPort2;
//    SbSetup->ESataPort3     = SetupData.ESataPort3;
//    SbSetup->ESataPort4     = SetupData.ESataPort4;
//    SbSetup->ESataPort5     = SetupData.ESataPort5;
//    SbSetup->SataHpP0       = SetupData.SataHpP0;
//    SbSetup->SataHpP1       = SetupData.SataHpP1;
//    SbSetup->SataHpP2       = SetupData.SataHpP2;
//    SbSetup->SataHpP3       = SetupData.SataHpP3;
//    SbSetup->SataHpP4       = SetupData.SataHpP4;
//    SbSetup->SataHpP5       = SetupData.SataHpP5;
//                                        // (P090109B)>
//#if defined ME_SUPPORT && ME_SUPPORT == 1
//#if THERMAL_REPORTING_SUPPORT
//    SbSetup->MCHTempReadEnable   = SetupData.MCHTempReadEnable;
//    SbSetup->PCHTempReadEnable   = SetupData.PCHTempReadEnable;
//    SbSetup->CPUEnergyReadEnable = SetupData.CPUEnergyReadEnable;
//    SbSetup->ThermalDataReportingEnable = SetupData.ThermalDataReportingEnable;
//#if IBEX_PEAK_SKU == 1
//    SbSetup->PPEC           = SetupData.PPEC;
//    SbSetup->PTL            = SetupData.PTL;
//    SbSetup->MMGPC          = SetupData.MMGPC;
//    SbSetup->MPPC           = SetupData.MPPC;
//    SbSetup->MPCPC          = SetupData.MPCPC;
//#endif
//    SbSetup->PTA            = SetupData.PTA;
//    SbSetup->PTA_OFFSET     = SetupData.PTA_OFFSET;
//    SbSetup->MGTA           = SetupData.MGTA;
//    SbSetup->MGTA_OFFSET    = SetupData.MGTA_OFFSET;
//    SbSetup->CPUTempReadEnable = SetupData.CPUTempReadEnable;
//    SbSetup->AlertEnableLock   = SetupData.AlertEnableLock;
//    SbSetup->CPUAlert       = SetupData.CPUAlert;
//    SbSetup->MCHAlert       = SetupData.MCHAlert;
//    SbSetup->PCHAlert       = SetupData.PCHAlert;
//    SbSetup->DIMMAlert      = SetupData.DIMMAlert;
//    SbSetup->TrEnabled      = SetupData.TrEnabled;
//    SbSetup->SMBusECMsgLen  = SetupData.SMBusECMsgLen;
//    SbSetup->SMBusECMsgPEC  = SetupData.SMBusECMsgPEC;
//    SbSetup->TsOnDimm0      = SetupData.TsOnDimm0;
//    SbSetup->TsOnDimm1      = SetupData.TsOnDimm1;
//    SbSetup->TsOnDimm2      = SetupData.TsOnDimm2;
//    SbSetup->TsOnDimm3      = SetupData.TsOnDimm3;
//    if ((SetupData.TsOnDimm0) || (SetupData.TsOnDimm1) || (SetupData.TsOnDimm2) || (SetupData.TsOnDimm3))
//      SbSetup->TrSmbusConfig = 1;
//    else
//      SbSetup->TrSmbusConfig = 0;
//#endif
//#endif
//                                        // <(P090109B)
//    return EFI_SUCCESS;
//}
//#endif
//                                        // <(P010609A)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: Wait_MDIC_Ready
//
// Description: Wait for MDIC ready
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Wait_MDIC_Ready(VOID)
{
    int i;
    UINT32 MBARA = 0xFECE0000;
    UINT32 Data32;

    for (i = 0; i < 64; i++)
    {
        Data32 = Mmio32(MBARA, 0x20);
        if ((Data32 | BIT28) != 0)
            return EFI_SUCCESS;

        CountTime(1, PM_BASE_ADDRESS);
    }

    return 1;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBGbE_Init
//
// Description: Initialize the SB GbE.
//
// Input: None
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SBGbE_Init(VOID)
{
    EFI_STATUS Status;

    UINT8    Data8;
    UINT8    GbePcieRPEn;
    UINT8    GbePcieRPSel;
    UINT32   Data32;

    Data8 = Mmio8(SB_RCBA, ICH_RCRB_BUC);
// [ P20100825 ]
//    if ((Data8 & BIT05) != 0)
//        return;


    Status = ReadSPIDescriptor(0x4, 0x9, &Data32);
    GbePcieRPEn = (UINT8)((Data32 & BIT11) >> 11);
    GbePcieRPSel = (UINT8)((Data32 & 0x0700) >> 8);

// [ P20100825 ]
//    if ((Status == EFI_SUCCESS) && (GbePcieRPEn == 1))
    if ((Status == EFI_SUCCESS) && (GbePcieRPEn == 1) && ((Data8 & BIT05) == 0))
    {
        Mmio16(SB_RCBA, ICH_RCRB_RPC) &= ~(BIT11 | BIT10 | BIT09 | BIT08);

        // Set 'GEBPCIERPEN', RCBA+offset 224h[11], bit to '1b'.
        Mmio16(SB_RCBA, ICH_RCRB_RPC) |= (UINT16)(GbePcieRPEn << 11);

        // Set 'GEBPCIERPSEL', RCBA+offset 224h[10:8],
        // bit to '1b' accordingly base on which port is used
        // for GbE MAC/PHY communication over PCI Express.
        Mmio16(SB_RCBA, ICH_RCRB_RPC) |= (UINT16)(GbePcieRPSel << 8);

        // Disable the Root Port used for GbE
        Mmio32(SB_RCBA, R_FUNCTION_DISABLE) |= (B_PCIE_1_DISABLE << GbePcieRPSel);

                                        // (P012510C)>
        Mmio8(SB_RCBA, ICH_RCRB_BUC) &= ~BIT05;   // Enable LAN
        Data8 = Mmio8(SB_RCBA, ICH_RCRB_BUC);
                                        // <(P012510C)

                                        // (P021909A), (P100908D)>
                                        // < (P021909A), (P100908D)


                                        // [EIP21600]>
        Data8 = MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3 + 1);
        Data8 |= BIT00;                 // 0xA4[8], (P020309D)
        Data8 &= ~(BIT01);              // Prevent GEN_RST_STS(A4h[9]) to be cleared.
        MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3 + 1) = Data8;
    }
    else
    {
        Mmio32(SB_RCBA, ICH_RCRB_GC) |= BIT23;   // Gate LAN static clock

                                        // (P012510C)>
        Mmio8(SB_RCBA, ICH_RCRB_BUC) |= BIT05;   // Disable LAN
        Data8 = Mmio8(SB_RCBA, ICH_RCRB_BUC);
                                        // <(P012510C)

        Data8 = MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3 + 1);
        Data8 &= ~(BIT00 + BIT01);      // 0xA4[8], (P020309D)
                                        // Prevent GEN_RST_STS(A4h[9]) to be cleared.
        MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3 + 1) = Data8;
                                        // <[EIP21600]
    }
}

                                        // (P072309B), (P051109A), (P020309E)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBUsbPeiInit
//
// Description: Initialize the SB USB.
//
// Input: IN CONST EFI_PEI_SERVICES
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SBUsbPeiInit(IN CONST EFI_PEI_SERVICES **PeiServices)
{
  EFI_STATUS               Status;
  SB_SETUP_CONFIGURATION   *SbSetupPtr;

  UINT8   TempDev;
  UINT8   TempFunc;
  UINT8   bPCHRid = MmPci8(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_RID);
  UINT16  wPCHSku = MmPci16(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_DID) & BIT00;
  UINT8   Offset;                       // (P050609A)
  UINT8   Buffer8;
  UINT16  Buffer16;
  UINT32  Buffer32;
  UINT16  USB_TOPOLOGY_SETTING[] = USB_TOPOLOGY_SETTINGS;

  Status = gSBPpi.TaskProcess(PeiServices, AMI_SB_GET_SETUP_CONFIG, &SbSetupPtr);
  ASSERT_PEI_ERROR(PeiServices, Status);

                                        // [EIP23236]>
//####  if((SbSetupPtr->Rmh == 1) ||
//####    ((SbSetupPtr->Rmh == 2) && (bPCHRid >= PCH_B0)) ||
//####     (bPCHRid >= PCH_B3))
  if((SbSetupPtr->Rmh == 1) ||
    ((SbSetupPtr->Rmh == 2) && (bPCHRid >= PCH_B0)))
  {
    Mmio8(SB_RCBA, 0x3598) &= ~(BIT00);
    TempFunc = 0x00;
  } else {
    Mmio8(SB_RCBA, 0x3598) |= BIT00;
    TempFunc = (bPCHRid <= PCH_A1) ? USB_FUNC_0 : USB_FUNC_7;
  }                                     // <[EIP23236]


  for (TempDev = USB_DEV_26; TempDev <= USB_DEV_29; TempDev += 3)
  {
    if (bPCHRid >= PCH_B0)
    {
      IntelEhciWorkaround();            // (P051509B)

      Buffer32 = MmPci32(USB_BUS, TempDev, TempFunc, ICH_REG_EHCI_IR2); // 0xFC
      Buffer32 &= ~(BIT02 | BIT03);
      Buffer32 |= (BIT03);
      Buffer32 |= (BIT05);
      Buffer32 |= (BIT17);

                                   // (P091109E)>
      if(bPCHRid == PCH_B3)
        Buffer32 |= (BIT28);
                                   // <(P091109E)

      Buffer32 |= (BIT29);              // (P100908A)
      Buffer32 &= ~(BIT06 | BIT22);     // (P082009A), Sighting#3305773
      MmPci32(USB_BUS, TempDev, TempFunc, ICH_REG_EHCI_IR2) = Buffer32; // 0xFC

                                        // (P042009E)>
      if(bPCHRid == PCH_B1)
      {
        Buffer32 = MmPci32(USB_BUS, TempDev, TempFunc, ICH_REG_EHCI_IR1);
        Buffer32 &= ~(BIT12 | BIT10 | BIT9 | BIT8);
        Buffer32 |= (BIT4 | BIT11 | BIT18 | BIT28);                 // [ EIP36182 ] PCH/IbexPeak BSU REV:1.05 - Section16.6.1
        MmPci32(USB_BUS, TempDev, TempFunc, ICH_REG_EHCI_IR1) = Buffer32;

        Buffer8 = MmPci8(USB_BUS, TempDev, TempFunc, 0x88);
        Buffer8 |= (BIT07 | BIT05);                                 // [ EIP36182 ] PCH/IbexPeak BSU REV:1.05 - Errata7/17
        MmPci8(USB_BUS, TempDev, TempFunc, 0x88) = Buffer8;
      }

      if(bPCHRid >= PCH_B2)             // (P081709C)
      {
        Buffer32 = MmPci32(USB_BUS, TempDev, TempFunc, ICH_REG_EHCI_IR1);
        Buffer32 &= ~(BIT12 | BIT10 | BIT09 | BIT08);
        Buffer32 |= (BIT04 | BIT08 | BIT11 | BIT18 | BIT28);        // [ EIP36182 ] PCH/IbexPeak BSU REV:1.05 - Section16.6.1
        MmPci32(USB_BUS, TempDev, TempFunc, ICH_REG_EHCI_IR1) = Buffer32;

        Buffer8 = MmPci8(USB_BUS, TempDev, TempFunc, 0x88);
        Buffer8 |= (BIT07 | BIT05);     // (P101309A)               // [ EIP36182 ] PCH/IbexPeak BSU REV:1.05 - Errata7/17
        MmPci8(USB_BUS, TempDev, TempFunc, 0x88) = Buffer8;
      }

        MmPci32(USB_BUS, TempDev, TempFunc, 0xF4) |= BIT31;
      if(bPCHRid == PCH_B0)             // (P051909C)>
      {
        MmPci32(USB_BUS, TempDev, TempFunc, 0xF4) |= (BIT16 + BIT17 + BIT18 + BIT19);
      } else {                          // <(P051909C)
        MmPci32(USB_BUS, TempDev, TempFunc, 0xF4) &= ~(BIT22 | BIT23);
        MmPci32(USB_BUS, TempDev, TempFunc, 0xF4) |= BIT23;
      }
        MmPci32(USB_BUS, TempDev, TempFunc, 0xF4) &= ~(BIT31);
    }
  }

  if (bPCHRid >= PCH_B0)
  {
                                        // (P112609A), (P081709B)>
    // Intel 5 Series Chipset and Intel 3400 Series Chipset
    // Specification Update - NDA Revision - 002 Version 1.2
    // 10.1.69 USBIRA-USB Initialization Register A (RCBA 3570h - 3574h)
    Buffer32 = Mmio32(SB_RCBA, ICH_RCRB_USBIRA);
                                        // (P110309A), (P070609A)>
    Buffer32 &= ~((0x07 << 4) | (0x07 << 8));
    Buffer32 |=  (0x02 | (0x01 << 25));
    if(wPCHSku == PCH_DESKTOP_SKU)
      Buffer32 |=  ((0x06 << 4) | (0x06 << 8));
    else
      Buffer32 |=  ((0x07 << 4) | (0x07 << 8));
                                        // <(P110309A), (P070609A)

    Mmio32(SB_RCBA, ICH_RCRB_USBIRA) = Buffer32;
                                        // <(P081709B)

                                        // (P110309A), (P081709A)>
    // Intel 5 Series Chipset and Intel 3400 Series Chipset
    // Specification Update - NDA Revision - 002 Version 1.2
    // 10.1.70 USBIRB-USB Initialization Register B (RCBA 357Ch - 357Fh)
    Buffer32 = Mmio32(SB_RCBA, ICH_RCRB_USBIRB);
    Buffer32 &= ~((0x0F << 4) | (0x03 << 8));
    Buffer32 |= ((0x03 << 4) | (0x01 << 10) | (0x01 << 12));
    if(wPCHSku == PCH_DESKTOP_SKU)
      Buffer32 |= (0x01 << 8);          // (P072109A)
    else
      Buffer32 |= (0x02 << 8);          // (P072109A)

    Mmio32(SB_RCBA, ICH_RCRB_USBIRB) = Buffer32;
                                        // <(P110309A), (P081709A)

    // Intel 5 Series Chipset and Intel 3400 Series Chipset
    // Specification Update - NDA Revision - 002 Version 1.2
    // 10.1.68 USBIRC-USB Initialization Register C (RCBA 3564h)
    Buffer16 = Mmio16(SB_RCBA, ICH_RCRB_USBIRC);
    Buffer16 &= ~(BIT12 | BIT08 | BIT07 | BIT06 | BIT05 | BIT04 | BIT03);   // [ EIP36182 ] PCH/IbexPeak BSU REV:1.05 - Errata16
    Buffer16 |= (BIT07 | BIT05);        // (P110309A)
    Mmio16(SB_RCBA, ICH_RCRB_USBIRC) = Buffer16;
  }
                                        // <(P112609A)

                                        // (P060309A.1)>
  for (Offset = 0x00; Offset <= 0x34; Offset += 4)
  {
    Mmio16(SB_RCBA, ICH_RCRB_USBIR0 + Offset) &= ~(0x0FFF);
    Mmio16(SB_RCBA, ICH_RCRB_USBIR0 + Offset) |= USB_TOPOLOGY_SETTING[Offset / 4];
  }                                     // <(P060309A.1)
}                                       // <(P072309B), (P020309E)

#if SB_RESET_PPI_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBPEI_ResetSystem
//
// Description: This function is the reset call interface function published
//              by the reset PPI
//
// Input:   PeiServices    Pointer to the PEI services table
//
// Output:  SYSTEM RESET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SBPEI_ResetSystem(
    IN CONST EFI_PEI_SERVICES **PeiServices
)
{

    SBLib_ResetSystem(HardReset);


    // We should never get this far
    return EFI_SUCCESS;
}


#endif //SB_RESET_PPI_SUPPORT


#if SB_STALL_PPI_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SBPEI_Stall
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES  **PeiServices,
//        IN CONST EFI_PEI_STALL_PPI  *This,
//        IN UINTN      MicroSeconds
//
// Output: Status
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SBPEI_Stall(
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    IN CONST EFI_PEI_STALL_PPI  *This,
    IN UINTN      MicroSeconds)
{
    EFI_STATUS    Status;
    EFI_PEI_PCI_CFG2_PPI  *PciCfg; //[EIP64769_04]
//#### UINT32     Buffer32;

    // Locate PciCfg PPI
    PciCfg = (*PeiServices)->PciCfg;

    // At this time no manipulation needed.  The value passed in is in
    // MicroSeconds(us) and that is what the library function uses

    // Call Library function that is shared with Metronome
    // Architecture Protocol

    // Corrected passing the Base Address for CountTime by GiriM (09/16/2005)
    //Status = CountTime(MicroSeconds, IO_REG_ACPI_TIMER);
    Status = CountTime(MicroSeconds, PM_BASE_ADDRESS);

    return Status;
}

#endif //SB_STALL_PPI_SUPPORT
*/
#if ATAPI_RECOVERY_SUPPORT

typedef struct
{
    EFI_PEI_PCI_CFG_PPI_WIDTH PciCfgWidth;
    UINTN Register;
    UINTN Value;
} REG_VALUE_TABLE_ENTRY;

REG_VALUE_TABLE_ENTRY IdeControllerRegValueTable[] =
{
    EfiPeiPciCfgWidthUint16, PCI_CMD, B_ICH_IDE_COMMAND_IOSE,
    EfiPeiPciCfgWidthUint16, R_ICH_IDE_TIMP, B_ICH_IDE_DEC_EN,
    EfiPeiPciCfgWidthUint16, R_ICH_IDE_TIMS, B_ICH_IDE_DEC_EN
};

EFI_GUID gIdeRecoveryNativeModePpiGuid = PEI_IDE_RECOVERY_NATIVE_MODE_PPI_GUID;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: EnableAtaChannel
//
// Description: Enable ATA Channels.
//
// Input: IN CONST EFI_PEI_SERVICES               **PeiServices,
//        IN PEI_ATA_CONTROLLER_PPI         *This,
//        IN UINT8                          ChannelMask
//
// Output: Status
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EnableAtaChannel(
    IN CONST EFI_PEI_SERVICES               **PeiServices,
    IN PEI_ATA_CONTROLLER_PPI         *This,
    IN UINT8                          ChannelMask
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_PEI_PCI_CFG2_PPI *PciCfg = 0;
    UINT8 PciData8 = 0;
    UINT16 PciData16 = 0;
    UINT16 SbTempIoBase = 0;
    UINTN i = 0, NumEntries = 0;
    EFI_PEI_PPI_DESCRIPTOR *IdeRecoveryNativeModePpiDescriptor;
    PEI_IDE_RECOVERY_NATIVE_MODE_PPI *IdeRecoveryNativeModePpi;
    IIO_UDS             *IohUds;
    EFI_GUID            UniversalDataGuid = IIO_UNIVERSAL_DATA_GUID;  
    EFI_HOB_GUID_TYPE   *GuidHob;


    PciCfg = (*PeiServices)->PciCfg;

    PEI_TRACE((-1, PeiServices, "\n In EnableAtaChannel \n"));

    //map register
    PciData8 = V_SATA_MAP_IDE;
    PciCfg->Write(
        PeiServices,
        PciCfg,
        EfiPeiPciCfgWidthUint8,
        (SATA0_BUS_DEV_FUNC | R_ICH_SATA_AMR),
        &PciData8
    );
    PEI_TRACE((-1, PeiServices, "map registerl \n"));
    //programming interface register - default value - legacy mode
    PciData8 = PI_PNE_LEGACY | PI_SNE_LEGACY;
    PciCfg->Write(
        PeiServices,
        PciCfg,
        EfiPeiPciCfgWidthUint8,
        (SATA0_BUS_DEV_FUNC | Programming_Interface),
        &PciData8
    );

    //default: everything is disabled
    PciData8 = B_SATA_PORT_0_ENABLED | B_SATA_PORT_1_ENABLED | B_SATA_PORT_2_ENABLED | B_SATA_PORT_3_ENABLED;
    PciCfg->Write(
        PeiServices,
        PciCfg,
        EfiPeiPciCfgWidthUint8,
        (SATA0_BUS_DEV_FUNC | R_ICH_SIDE_PCS),
        &PciData8);

    PciData16 = 0xF0A0;
    PciCfg->Write(
        PeiServices,
        PciCfg,
        EfiPeiPciCfgWidthUint16,
        (SATA0_BUS_DEV_FUNC | PCI_BAR4),
        &PciData16);

    PciData16 = 0xF0F0;
    PciCfg->Write(
        PeiServices,
        PciCfg,
        EfiPeiPciCfgWidthUint16,
        (SATA0_BUS_DEV_FUNC | PCI_BAR4),
        &PciData16);

    NumEntries = sizeof(IdeControllerRegValueTable) / sizeof(REG_VALUE_TABLE_ENTRY);
    //sata function number - PCI_FUNCTION_NUMBER_ICH_SATA
    for (i = 0; i < NumEntries; i++)
    {
        PciCfg->Write(
            PeiServices,
            PciCfg,
            IdeControllerRegValueTable[i].PciCfgWidth,
            (SATA0_BUS_DEV_FUNC | IdeControllerRegValueTable[i].Register),
            &IdeControllerRegValueTable[i].Value);
    }

    PciCfg->Read(
        PeiServices,
        PciCfg,
        EfiPeiPciCfgWidthUint16,
        (SATA1_BUS_DEV_FUNC),
        &PciData16);

    PEI_TRACE((-1, PeiServices, "before PciData16 loop \n"));
    if (PciData16 != 0xFFFF)
    {
        PEI_TRACE((-1, PeiServices, "inside PciData16 loop \n"));
        //programming interface register
        PciData8 = PI_PNE_NATIVE | PI_SNE_NATIVE;
        PciCfg->Write(
            PeiServices,
            PciCfg,
            EfiPeiPciCfgWidthUint8,
            (SATA1_BUS_DEV_FUNC | Programming_Interface),
            &PciData8
        );

        //default: everything is disabled
        PciData8 = B_SATA_PORT_0_ENABLED | B_SATA_PORT_1_ENABLED;
        PciCfg->Write(
            PeiServices,
            PciCfg,
            EfiPeiPciCfgWidthUint8,
            (SATA1_BUS_DEV_FUNC | R_ICH_SIDE_PCS),
            &PciData8);
/*
    SbTempIoBase = 0x7000;
    IdeRecoveryNativeModePpi.PCMDBarAddress = SbTempIoBase + 0X230 ;
    IdeRecoveryNativeModePpi.PCNLBarAddress = SbTempIoBase + 0X222 ;
    IdeRecoveryNativeModePpi.SCMDBarAddress = SbTempIoBase + 0X210 ;
    IdeRecoveryNativeModePpi.SCNLBarAddress = SbTempIoBase + 0X202 ;
 */
        
        GuidHob    = GetFirstGuidHob (&UniversalDataGuid);
        IohUds = GET_GUID_HOB_DATA (GuidHob);
        ASSERT_PEI_ERROR(PeiServices, IohUds);
        
	    SbTempIoBase = IohUds->PlatformData.IIO_resource[0].PciResourceIoBase;
        PEI_TRACE((-1, PeiServices, "AMI: IohUds->PlatformData.IIO_resource[0].PciResourceIoBase 0x%X \n", IohUds->PlatformData.IIO_resource[0].PciResourceIoBase));
            
	    Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (EFI_PEI_PPI_DESCRIPTOR), &IdeRecoveryNativeModePpiDescriptor);
        ASSERT_PEI_ERROR(PeiServices, Status);

	    Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PEI_IDE_RECOVERY_NATIVE_MODE_PPI), &IdeRecoveryNativeModePpi);
        ASSERT_PEI_ERROR(PeiServices, Status);

	    (*PeiServices)->SetMem((VOID *)IdeRecoveryNativeModePpi, sizeof (PEI_IDE_RECOVERY_NATIVE_MODE_PPI), 0);

	    IdeRecoveryNativeModePpi->PCMDBarAddress = SbTempIoBase + 0X230 ;
	    IdeRecoveryNativeModePpi->PCNLBarAddress = SbTempIoBase + 0X222 ;
	    IdeRecoveryNativeModePpi->SCMDBarAddress = SbTempIoBase + 0X210 ;
	    IdeRecoveryNativeModePpi->SCNLBarAddress = SbTempIoBase + 0X202 ;
        PciData16 = IdeRecoveryNativeModePpi->PCMDBarAddress;
        PciCfg->Write(
            PeiServices,
            PciCfg,
            EfiPeiPciCfgWidthUint16,
            (SATA1_BUS_DEV_FUNC | R_ICH_IDE_PCMD_BAR),
            &PciData16);


        PciData16 = IdeRecoveryNativeModePpi->PCNLBarAddress;
        PciCfg->Write(
            PeiServices,
            PciCfg,
            EfiPeiPciCfgWidthUint16,
            (SATA1_BUS_DEV_FUNC | R_ICH_IDE_PCNL_BAR),
            &PciData16);

        PciData16 = IdeRecoveryNativeModePpi->SCMDBarAddress;
        PciCfg->Write(
            PeiServices,
            PciCfg,
            EfiPeiPciCfgWidthUint16,
            (SATA1_BUS_DEV_FUNC | R_ICH_IDE_SCMD_BAR),
            &PciData16);

        PciData16 = IdeRecoveryNativeModePpi->SCNLBarAddress;
        PciCfg->Write(
            PeiServices,
            PciCfg,
            EfiPeiPciCfgWidthUint16,
            (SATA1_BUS_DEV_FUNC | R_ICH_IDE_SCNL_BAR),
            &PciData16);

        NumEntries = sizeof(IdeControllerRegValueTable) / sizeof(REG_VALUE_TABLE_ENTRY);
        //sata function number - PCI_FUNCTION_NUMBER_ICH_SATA
        for (i = 0; i < NumEntries; i++)
        {
            PciCfg->Write(
                PeiServices,
                PciCfg,
                IdeControllerRegValueTable[i].PciCfgWidth,
                (SATA1_BUS_DEV_FUNC | IdeControllerRegValueTable[i].Register),
                &IdeControllerRegValueTable[i].Value);
        }

	IdeRecoveryNativeModePpiDescriptor->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
 	IdeRecoveryNativeModePpiDescriptor->Guid = &gIdeRecoveryNativeModePpiGuid;
  	IdeRecoveryNativeModePpiDescriptor->Ppi = IdeRecoveryNativeModePpi;
	Status = (*PeiServices)->InstallPpi(PeiServices, IdeRecoveryNativeModePpiDescriptor);

        PEI_TRACE((-1, PeiServices, "LocatePpi->IdeRecoveryNativeModePpiDescriptor: %r", Status));
        if (EFI_ERROR(Status)) return Status;
    }

    return EFI_SUCCESS;
}

#endif //ATAPI_RECOVERY_SUPPORT

/*
#if defined SMM_SUPPORT && SMM_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: PeiActivate
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES    **PeiServices,
//        IN PEI_SMM_CONTROL_PPI *This,
//        IN OUT INT8  *ArgumentBuffer OPTIONAL,
//        IN OUT UINTN *ArgumentBufferSize OPTIONAL,
//        IN BOOLEAN   Periodic OPTIONAL,
//        IN UINTN     ActivationInterval OPTIONAL
//
// Output: Status
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PeiActivate(
    IN CONST EFI_PEI_SERVICES    **PeiServices,
    IN PEI_SMM_CONTROL_PPI *This,
    IN OUT INT8   *ArgumentBuffer OPTIONAL,
    IN OUT UINTN  *ArgumentBufferSize OPTIONAL,
    IN BOOLEAN    Periodic OPTIONAL,
    IN UINTN      ActivationInterval OPTIONAL
)
{
    UINT8 Data;
    UINT8 Value;

    if (Periodic) return EFI_INVALID_PARAMETER;

    if (ArgumentBuffer == 0)
    {
        Data = 0xFF;      //If no data given, use 0xFF to trigger SMI.
    }
    else
    {
        if (ArgumentBufferSize == 0 || *ArgumentBufferSize != 1)
            return EFI_INVALID_PARAMETER; // Only able to send 1 byte.
        Data = *ArgumentBuffer;
    }

// Porting Required.  Include code to generate S/W SMI
    // Enable Software SMIs
    Value = IoRead8(PM_BASE_ADDRESS + ICH_IOREG_SMI_EN) | (1 << 5) | 1;
    IoWrite8(PM_BASE_ADDRESS + ICH_IOREG_SMI_EN, Value);

    IoWrite8(SW_SMI_IO_ADDRESS, Data); //This triggers SMI

// Porting End
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: PeiDeactivate
//
// Description:
//
// Input: IN CONST EFI_PEI_SERVICES     **PeiServices,
//        IN PEI_SMM_CONTROL_PPI  *This,
//        IN BOOLEAN              Periodic OPTIONAL
//
// Output: Status
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PeiDeactivate(
    IN CONST EFI_PEI_SERVICES     **PeiServices,
    IN PEI_SMM_CONTROL_PPI  *This,
    IN BOOLEAN              Periodic OPTIONAL
)
{
    UINT8  Value;

    if (Periodic)
        return EFI_INVALID_PARAMETER;

// Porting Required. Include code to clear all SMI status
    // Clear the Power Button Override Status Bit
    IoWrite16(PM_BASE_ADDRESS, 1 << 8);

    // Clear the APM SMI Status Bit
    IoWrite8(PM_BASE_ADDRESS + ICH_IOREG_SMI_STS, 1 << 5);

    //Set EOS
    Value = IoRead8(PM_BASE_ADDRESS + ICH_IOREG_SMI_EN) | 2;
    IoWrite8(PM_BASE_ADDRESS + ICH_IOREG_SMI_EN, Value);
// Porting end

    return EFI_SUCCESS;
}

#endif //SMM_SUPPORT

                                        // [ EIP61250 ] >
// Intel 5 Series Chipset and Intel 3400 Series Chipset
// Specification Update - NDA Revision - 020 Version 1.0
// Errata#15 Intel 5 Series Chipset and Intelr 3400 Series Chipset HPET Writing
// Timing Issue
#if HPET_SUPPORT
VOID HPETWorkaround (VOID)
{
    UINT32  HPET_AS = 0;

    switch(HPET_BASE_ADDRESS)
    {
        case 0xfed00000:
            HPET_AS = 0;
            break;
        case 0xfed01000:
            HPET_AS = 1;
            break;         
        case 0xfed02000:
            HPET_AS = 2;
            break;
        case 0xfed03000:
            HPET_AS = 3;
            break;
        default:
            return;
    }

    Mmio32(SB_RCBA, R_ICH_HPET_CONFIG) &= ~(BIT00+BIT01+BIT07);
    Mmio32(SB_RCBA, R_ICH_HPET_CONFIG) |= (HPET_AS + BIT07);

    Mmio32(HPET_BASE_ADDRESS, 0);
}
#endif // HPET_SUPPORT
                                        // < [ EIP61250 ]
*/
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

