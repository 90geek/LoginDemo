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
/** @file TbtSmm.c

**/
//**********************************************************************

#include <Token.h>
#include <Setup.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol/AmiTbtNvs.h>
#include <Protocol/AmiTbtPlatformPolicy.h>
#include <Guid/AmiTbtHrStatus.h>
#include <Library/TbtDxeLib.h>
#include <Library/TbtOemLib.h>
#include <Protocol/Variable.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/SmmPowerButtonDispatch2.h>
#include <Pci.h>
//#include <PCIE.h>
#include <TbtCommon.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

#define AMI_SMM_SW_DISPATCH_PROTOCOL           EFI_SMM_SW_DISPATCH2_PROTOCOL
#define AMI_SMM_SW_DISPATCH_CONTEXT            EFI_SMM_SW_REGISTER_CONTEXT
#define AMI_SMM_SX_DISPATCH_PROTOCOL           EFI_SMM_SX_DISPATCH2_PROTOCOL
#define AMI_SMM_SX_DISPATCH_CONTEXT            EFI_SMM_SX_REGISTER_CONTEXT
#define AMI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL
#define AMI_SMM_POWER_BUTTON_DISPATCH_CONTEXT  EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT
#define SMM_CHILD_DISPATCH_SUCCESS             EFI_SUCCESS
#define SMM_CHILD_DISPATCH_TIMEOUT             EFI_TIMEOUT
#define SMM_CHILD_DISPATCH_NO_MEDIA            EFI_NO_MEDIA
#define SMM_CHILD_DISPATCH_DEVICE_ERROR        EFI_DEVICE_ERROR
#define SMM_CHILD_DISPATCH_UNSUPPORTED         EFI_UNSUPPORTED

#ifdef SMI_PROGRESS_CODE
#undef SMI_PROGRESS_CODE
#endif
#define SMI_PROGRESS_CODE(Data)     IoWrite8(0x80, Data)

#define SMM_THUNDERBOLT_CALL        TBT_SWSMI_VALUE

#define MAX_TBT_DEPTH                6

#define P2P_BRIDGE                  (((PCI_CL_BRIDGE) << 8) | (PCI_CL_BRIDGE_SCL_P2P))

#define BAR_ALIGN(v, a)             ((((v) - 1) | (a)) + 1)

#define CMD_BUS_MASTER              BIT2
#define CMD_BM_IO                   (CMD_BUS_MASTER | BIT0)
#define CMD_BM_MEM                  (CMD_BUS_MASTER | BIT1)
#define CMD_BM_MEM_IO               (CMD_BUS_MASTER | BIT1 | BIT0)

//#define DEF_RES_IO_PER_DEV          4    //new setup item
//#define DEF_RES_MEM_PER_DEV         32   //new setup item
//#define DEF_RES_PMEM_PER_DEV        32   //new setup item
#define DOCK_BUSSES                 8

#define DISBL_IO_REG1C              0x01F1
#define DISBL_MEM32_REG20           0x0000FFF0
#define DISBL_PMEM_REG24            0x0001FFF1

// Light Ridge HR device ID
#define LR_HR     0x1513
// Eagle Ridge HR device IDs
#define ER_SFF_HR 0x151A
#define ER_HR     0x151B
// Cactus Ridge HR device IDs
#define CR_HR_2C  0x1548
#define CR_HR_4C  0x1547
// Redwood Ridge HR device IDs
#define RR_HR_2C  0x1567
#define RR_HR_4C  0x1569
// Falcon Ridge HR device IDs
#define FR_HR_2C  0x156B
#define FR_HR_4C  0x156D
// BDW-TBT-LP HR device ID
#define BDW_TBT_LP_HR  0x157E

#define count(x)                    (sizeof(x) / sizeof((x)[0]))

//
// Common Memory mapped Pci access macros -----------------------------------
//
static UINT64 PciExpressBaseAddress = 0;

#define SmiPciAddress( Segment, Bus, Device, Function, Register ) \
  ( (UINTN)PciExpressBaseAddress + \
    (UINTN)(Bus << 20) + \
    (UINTN)(Device << 15) + \
    (UINTN)(Function << 12) + \
    (UINTN)(Register) \
  )
//
// UINT32
//
#define SmiPci32Ptr( Segment, Bus, Device, Function, Register ) \
  ( (volatile UINT32 *)SmiPciAddress( Segment, Bus, Device, Function, Register ) )

#define SmiPci32( Segment, Bus, Device, Function, Register ) \
  *SmiPci32Ptr( Segment, Bus, Device, Function, Register )

#define SmiPci32Or( Segment, Bus, Device, Function, Register, OrData ) \
  SmiPci32( Segment, Bus, Device, Function, Register ) = \
    (UINT32) ( \
      SmiPci32( Segment, Bus, Device, Function, Register ) | \
      (UINT32)(OrData) \
    )

#define SmiPci32And( Segment, Bus, Device, Function, Register, AndData ) \
  SmiPci32( Segment, Bus, Device, Function, Register ) = \
    (UINT32) ( \
      SmiPci32( Segment, Bus, Device, Function, Register ) & \
      (UINT32)(AndData) \
    )

#define SmiPci32AndThenOr( Segment, Bus, Device, Function, Register, AndData, OrData ) \
  SmiPci32( Segment, Bus, Device, Function, Register ) = \
    (UINT32) ( \
      ( SmiPci32( Segment, Bus, Device, Function, Register ) & \
          (UINT32)(AndData) \
      ) | \
      (UINT32)(OrData) \
    )
//
// UINT16
//
#define SmiPci16Ptr( Segment, Bus, Device, Function, Register ) \
  ( (volatile UINT16 *)SmiPciAddress( Segment, Bus, Device, Function, Register ) )

#define SmiPci16( Segment, Bus, Device, Function, Register ) \
  *SmiPci16Ptr( Segment, Bus, Device, Function, Register )

#define SmiPci16Or( Segment, Bus, Device, Function, Register, OrData ) \
  SmiPci16( Segment, Bus, Device, Function, Register ) = \
    (UINT16) ( \
      SmiPci16( Segment, Bus, Device, Function, Register ) | \
      (UINT16)(OrData) \
    )

#define SmiPci16And( Segment, Bus, Device, Function, Register, AndData ) \
  SmiPci16( Segment, Bus, Device, Function, Register ) = \
    (UINT16) ( \
      SmiPci16( Segment, Bus, Device, Function, Register ) & \
      (UINT16)(AndData) \
    )

#define SmiPci16AndThenOr( Segment, Bus, Device, Function, Register, AndData, OrData ) \
  SmiPci16( Segment, Bus, Device, Function, Register ) = \
    (UINT16) ( \
      ( SmiPci16( Segment, Bus, Device, Function, Register ) & \
          (UINT16)(AndData) \
      ) | \
      (UINT16)(OrData) \
    )
//
// UINT8
//
#define SmiPci8Ptr( Segment, Bus, Device, Function, Register ) \
  ( (volatile UINT8 *)SmiPciAddress( Segment, Bus, Device, Function, Register ) )

#define SmiPci8( Segment, Bus, Device, Function, Register ) \
  *SmiPci8Ptr( Segment, Bus, Device, Function, Register )

#define SmiPci8Or( Segment, Bus, Device, Function, Register, OrData ) \
  SmiPci8( Segment, Bus, Device, Function, Register ) = \
    (UINT8) ( \
      SmiPci8( Segment, Bus, Device, Function, Register ) | \
      (UINT8)(OrData) \
    )

#define SmiPci8And( Segment, Bus, Device, Function, Register, AndData ) \
  SmiPci8( Segment, Bus, Device, Function, Register ) = \
    (UINT8) ( \
      SmiPci8( Segment, Bus, Device, Function, Register ) & \
      (UINT8)(AndData) \
    )

#define SmiPci8AndThenOr( Segment, Bus, Device, Function, Register, AndData, OrData ) \
  SmiPci8( Segment, Bus, Device, Function, Register ) = \
    (UINT8) ( \
      ( SmiPci8( Segment, Bus, Device, Function, Register ) & \
          (UINT8)(AndData) \
        ) | \
      (UINT8)(OrData) \
    )

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
UINT16  HostDeviceId;
UINT8   gCacheLineSize;
UINT8   gTbtBus;
UINT8   gTbtDev;
UINT8   gTbtFun;
UINT16  gReserveMemoryPerSlot;
UINT16  gReservePMemoryPerSlot;
UINT8   gReserveIOPerSlot;
UINT8   gTbtHotPlugEvent;
#if !defined TBT_PCIBUS_SKIP || TBT_PCIBUS_SKIP == 0
UINT8   IsFirstEnterFlag     = 1;
#endif
UINT32  AmiTbtHrStatusAttribute = 0;
BOOLEAN gTbtEnable           = FALSE;
BOOLEAN gTbtWakeupSupport    = FALSE;
BOOLEAN gTbtAICSupport       = FALSE;
BOOLEAN gTbtHandlePOC        = FALSE;
BOOLEAN gTbtIOresourceEnable = FALSE;
AMI_TBT_NVS_DATA        *AmiTbtNvs;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//----------------------------------------------------------------------------

#if defined(EFI64) || defined(EFIx64)

/**
    This routine allows a 64 bit value to be divided with a 32 bit
    value returns  64bit result and the Remainder.

    @param[in] Dividend
    @param[in] Divisor

    @retval *Remainder OPTIONAL      

**/
static UINT64 SmiDivU64x32 (
    IN UINT64   Dividend,
    IN UINTN    Divisor,
    OUT UINTN   *Remainder OPTIONAL
)
{
    UINT64  Result = Dividend/Divisor;
    if (Remainder) *Remainder=Dividend%Divisor;
    return Result;
}

#else
/**
    This routine allows a 64 bit value to be divided with a 32 bit
    value returns 64bit result and the Remainder.

    @param[in] Dividend
    @param[in] Divisor

    @retval *Remainder OPTIONAL      

**/
static UINT64 SmiDivU64x32 (
    IN UINT64   Dividend,
    IN UINTN    Divisor,    //Can only be 31 bits.
    OUT UINTN   *Remainder OPTIONAL
)
{
    UINT64  Result;
    UINT32  Rem;
    _asm
    {
        mov     eax, dword ptr Dividend[0]
        mov     edx, dword ptr Dividend[4]
        mov     esi, Divisor
        xor     edi, edi                    ;/// Remainder
        mov     ecx, 64                     ;/// 64 bits
Div64_loop:
        shl     eax, 1                      ;/// Shift dividend left. This clears bit 0.
        rcl     edx, 1    
        rcl     edi, 1                      ;/// Shift remainder left. Bit 0 = previous dividend bit 63.

        cmp     edi, esi                    ;/// If Rem >= Divisor, do not adjust
        cmc                                 ;/// else adjust dividend and subtract divisor.
        sbb     ebx, ebx                    ;/// if Rem >= Divisor, ebx = 0, else ebx = -1.
        sub     eax, ebx                    ;/// if adjust, bit 0 of dividend = 1
        and     ebx, esi                    ;/// if adjust, ebx = Divisor, else ebx = 0. 
        sub     edi, ebx                    ;/// if adjust, subtract divisor from remainder.
        loop    Div64_loop

        mov     dword ptr Result[0], eax
        mov     dword ptr Result[4], edx
        mov     Rem, edi
    }

    if (Remainder) *Remainder = Rem;

    return Result;
}

#endif

/**
    Stalls for the Required Amount of MicroSeconds

    @param[in] Usec - UINTN

    @retval VOID

**/

VOID SmiStall (
    UINTN   Usec                           
)
{
    UINTN   Counter, i;
    UINT32  Data32, PrevData;
    UINTN   Remainder;

    Counter = (UINTN)SmiDivU64x32 ((Usec * 10), 3, &Remainder);

    if (Remainder != 0) {
        Counter++;
    }

    //
    // Call WaitForTick for Counter + 1 ticks to try to guarantee Counter tick
    // periods, thus attempting to ensure Microseconds of stall time.
    //
    if (Counter != 0) {

        PrevData = IoRead32(PM_BASE_ADDRESS + 8);
        for (i = 0; i < Counter; ) {
            Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
            if (Data32 < PrevData) {        // Reset if there is a overlap
                PrevData=Data32;
                continue;
            }
            i += (Data32 - PrevData);        
            PrevData = Data32;
        }
    }
    return;
}

/**
    Check device is Thunderbolt device or not

    @param[in] DeviceID

    @retval TRUE        Is Thunderbolt device
    @retval FALSE       Not Thunderbolt device
**/
BOOLEAN IsTBTDevice(
    IN UINT16       DeviceID )
{
    switch(DeviceID)
    {
    case 0x1513:
    case 0x151A:
    case 0x151B:
    case 0x1547: // Cactus Ridge 4C
    case 0x1548: // Cactus Ridge 2C
    case 0x1567: // Redwood Ridge 2C
    case 0x1569: // Redwood Ridge 4C
    case 0x156B: // Falcon Ridge 2C
    case 0x156D: // Falcon Ridge 4C
        return TRUE;
    }
  return FALSE;
}//IsTBTDevice

/**
    Find the Offset to a given Capabilities 
    ID CAPID list:
    0x01 = PCI Power Management Interface
    0x04 = Slot Identification
    0x05 = MSI Capability
    0x10 = PCI Express Capability

    @param[in] Bus       Pci Bus Number
    @param[in] Dev       Pci Device Number
    @param[in] Fun       Pci Function Number
    @param[in] CapId     CAPID to search for

    @retval 0            CAPID not found
    @retval Other        CAPID found, Offset of desired CAPID
**/
UINT8 PcieFindCapId (
    IN UINT8    Bus,
    IN UINT8    Dev,
    IN UINT8    Fun,
    IN UINT8    CapId)
{
    UINT8 CapHeader;
    
    CapHeader = SmiPci8(0x00, Bus, Dev, Fun, EFI_PCI_CAPABILITY_PTR);
    if (CapHeader == 0xFF) {
        return 0;
    }
    while (CapHeader != 0) {
        // Bottom 2 bits of the pointers are reserved per PCI Local Bus Spec 2.2
        CapHeader &= ~(BIT1 | BIT0);
        
        // Search for desired CapID
        if (SmiPci8 (0x00, Bus, Dev, Fun, CapHeader) == CapId) {
            return CapHeader;
        }
        
        CapHeader = SmiPci8 (0x00, Bus, Dev, Fun, (CapHeader + 1));
    } // while loop
    return 0;
}

/**
    This function will help routing GPIO pin to trigger SCI signal
    @param[in] VOID

    @retval VOID
**/
VOID TbtHotplugPinSciRouting (VOID)
{
#if defined ULT_SUPPORT && ULT_SUPPORT == 1
    UINT8 Data8;

    if (IsULTPchSeries()){
       // Enable Thunderbolt Hotplug Pin SCI route for ULT platform
       Data8 = IoRead8(GPIO_BASE_ADDRESS + R_PCH_LP_LPC_GPI_ROUT0 + gTbtHotPlugEvent/8);
       Data8 = Data8 & ~(BIT00 << (gTbtHotPlugEvent%8));
       IoWrite8(GPIO_BASE_ADDRESS + R_PCH_LP_LPC_GPI_ROUT0 + gTbtHotPlugEvent/8, Data8);
    } else {
       // Enable Thunderbolt Hotplug Pin SCI route
       SmiPci8Or( 0x00, 0x00, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, (R_PCH_LPC_GPI_ROUT + gTbtHotPlugEvent/4), (0x2 << (gTbtHotPlugEvent%4)*2) );
    }
#else
    UINT32      PmcBaseAddr;
    UINT8       Data8;
    
    if (IsSocPchSeries()){
        TRACE((-1, "Hotplug Pin SCI route for BayTrial platform...\n"));
        // Get PMC_BASE_ADDRESS
        PmcBaseAddr = SmiPci32(0x00, 0x00, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, R_PCH_LPC_PMC_BASE);
        PmcBaseAddr &= 0xFFFFFE00;
        
        // Enable Thunderbolt Hotplug Pin SCI route
        Data8 = MMIO_READ8(PmcBaseAddr + R_PCH_PMC_GPI_ROUT + (gTbtHotPlugEvent/4));
        Data8 |= (0x2 << (gTbtHotPlugEvent%4)*2);
        MMIO_WRITE8((PmcBaseAddr + R_PCH_PMC_GPI_ROUT + (gTbtHotPlugEvent/4)), Data8);
    } else {
        // Enable Thunderbolt Hotplug Pin SCI route
        SmiPci8Or( 0x00, 0x00, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, (R_PCH_LPC_GPI_ROUT + gTbtHotPlugEvent/4), (0x2 << (gTbtHotPlugEvent%4)*2) );
    }
#endif
}

BOOLEAN
IsTBTHostRouter(
    IN        UINT16  DeviceID
)
{
    switch(DeviceID)
    {
        case LR_HR:
        case ER_SFF_HR:
        case ER_HR:
        case CR_HR_4C:
        case CR_HR_2C:
        case RR_HR_2C: 
        case RR_HR_4C:
        case FR_HR_2C:
        case FR_HR_4C:
        case BDW_TBT_LP_HR:
            return TRUE;
    }
  return FALSE;
}//IsTBTHostRouter

typedef struct _PortInfo
{
    UINT8      IOBase;
    UINT8      IOLimit;
    UINT16     MemBase;
    UINT16     MemLimit;
    UINT64     PMemBase64;
    UINT64     PMemLimit64;
    UINT8      BusNumLimit;
    UINT8      ConfedEP;
} PortInfo;

typedef struct _MEM_REGS
{
    UINT32 Base;
    UINT32 Limit;
} MEM_REGS;

typedef struct _PMEM_REGS
{
    UINT64 Base64;
    UINT64 Limit64;
} PMEM_REGS;

typedef struct _IO_REGS
{
    UINT16 Base;
    UINT16 Limit;
} IO_REGS;

VOID
PortInfoInit(
    IN    OUT    PortInfo *pi
)
{
    pi->BusNumLimit = 4;
}//PortInfoInit

BOOLEAN isLegacyDevice = FALSE;

#define MEM_PER_SLOT  gReserveMemoryPerSlot
#define PMEM_PER_SLOT gReservePMemoryPerSlot

UINT16
MemPerSlot(
    IN      UINT16 currUsage
)
{
    if(currUsage == 0)
        return 0;
    
    if(currUsage <= 16)
        return 16;
    if(currUsage <= 64)
        return 64;
    if(currUsage <= 128)
        return 128;
    if(currUsage <= 256)
        return 256;
    if(currUsage <= 512)
        return 512;
    if(currUsage <= 1024)
        return 1024;

    return currUsage;
}//MemPerSlot

UINT64
PMemPerSlot(
    IN      UINT64 currUsage
)
{
    if(currUsage == 0)
        return 0;
    
    if(currUsage <= 1024ULL)
        return 1024ULL;
    if(currUsage <= 4096ULL)
        return 4096ULL;

    return currUsage;
}//PMemPerSlot

VOID
SetPHYPortResources(
    IN        UINT8 Bus, 
    IN        UINT8 Dev, 
    IN        UINT8 SubBus, 
    IN        INT8  Depth, 
    IN        PortInfo* CurrentPi,
    IN    OUT PortInfo* pi
)
{
    UINT8    Cmd = CMD_BUS_MASTER;
    UINT16   deltaMEM;
    UINT64   deltaPMEM;
    UINT8    deltaIO;

    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_SUBUS) = SubBus;
    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_CMD) = Cmd;

    deltaIO = pi->IOBase - CurrentPi->IOBase;
    if(Depth >= 0 && gReserveIOPerSlot && deltaIO < gReserveIOPerSlot)
        pi->IOBase += gReserveIOPerSlot - deltaIO;

    if (pi->IOBase > CurrentPi->IOBase && (pi->IOBase - 0x10) <= pi->IOLimit)
    {
        SmiPci8  (0x00, Bus, Dev, 0x00, PCI_IOBASE) = CurrentPi->IOBase;
        SmiPci8  (0x00, Bus, Dev, 0x00, PCI_IOLIMIT) = pi->IOBase - 0x10;
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_IOBASE_U) = 0x00000000;
        Cmd |= CMD_BM_IO;
    }
    else
    {
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_IOBASE) = DISBL_IO_REG1C;
        pi->IOBase = CurrentPi->IOBase;
    }

    deltaMEM = pi->MemBase - CurrentPi->MemBase;

    if(isLegacyDevice)
    {
        if(Depth >= 0 && gReserveMemoryPerSlot && deltaMEM < MEM_PER_SLOT)
            pi->MemBase += MEM_PER_SLOT - deltaMEM;
    }
    else
    {
        if(deltaMEM < MemPerSlot(deltaMEM))
            pi->MemBase += MemPerSlot(deltaMEM) - deltaMEM;
    }

    if (pi->MemBase > CurrentPi->MemBase && (pi->MemBase - 0x10) <= pi->MemLimit)
    {
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_MEMBASE) = CurrentPi->MemBase;
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_MEMLIMIT) = pi->MemBase - 0x10;
        Cmd |= CMD_BM_MEM;
    }
    else
    {
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_MEMBASE) = DISBL_MEM32_REG20;
        pi->MemBase = CurrentPi->MemBase;
    }

    deltaPMEM = pi->PMemBase64 - CurrentPi->PMemBase64;
    if(isLegacyDevice)
    {
        if(Depth >= 0 && gReservePMemoryPerSlot && deltaPMEM < PMEM_PER_SLOT)
            pi->PMemBase64 += PMEM_PER_SLOT - deltaPMEM;
    }
    else
    {
        if(deltaPMEM < PMemPerSlot(deltaPMEM))
            pi->PMemBase64 += PMemPerSlot(deltaPMEM) - deltaPMEM;
    }

    if (pi->PMemBase64 > CurrentPi->PMemBase64 && (pi->PMemBase64 - 0x10) <= pi->PMemLimit64)
    {
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE) = (UINT16)(CurrentPi->PMemBase64 & 0xFFFF);
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMLIMIT) = (UINT16)((pi->PMemBase64 - 0x10) & 0xFFFF);
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE_U) = (UINT32)(CurrentPi->PMemBase64 >> 16);
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMLIMIT_U) = (UINT32)((pi->PMemBase64 - 0x10) >> 16);
        Cmd |= CMD_BM_MEM;
    }
    else
    {
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE) = DISBL_PMEM_REG24;
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE_U) = 0;
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMLIMIT_U) = 0;
        pi->PMemBase64 = CurrentPi->PMemBase64;
    }

    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_CMD) = Cmd;
    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_CLS) = gCacheLineSize;
}//SetPHYPortResources

UINT32
SaveSetGetRestoreBAR(
    IN        volatile UINT32* BAR
)
{
    UINT32  BarReq;
    UINT32  OrigBar = *BAR;// Save BAR
    *BAR = 0xFFFFFFFF;       // Set BAR
    BarReq = *BAR;           // Get BAR
    *BAR = OrigBar;           // Restore BAR
    
    return BarReq;
}//SaveSetGetRestoreBAR

VOID
SetIOBAR(
    IN        volatile
            UINT32*  BAR,
    IN        UINT32   BarReq,
    IN    OUT    UINT8*   Cmd,
    IN    OUT    IO_REGS* io_r
)
{
    UINT16 Alignment = ~(BarReq & 0xFFFC);
    UINT16 Size = Alignment + 1;
    UINT16 NewBase;

    if(io_r->Base > io_r->Limit || !Size)
        return;

    NewBase = BAR_ALIGN(io_r->Base, Alignment);
    if(NewBase > io_r->Limit || NewBase + Size - 1 > io_r->Limit)
        return;

    *BAR = NewBase; // Set BAR
    io_r->Base = NewBase + Size; // Advance to new position
    *Cmd |= CMD_BM_IO; // Set IO Space Enable
}//SetIOBAR

VOID
SetMemBAR(
    IN        volatile 
            UINT32*   BAR,
    IN        UINT32    BarReq,
    IN    OUT    UINT8*    Cmd,
    IN    OUT    MEM_REGS* mem_r
)
{
    UINT32 Alignment = ~(BarReq & 0xFFFFFFF0);
    UINT32 Size = Alignment + 1;
    UINT32 NewBase;

    if(mem_r->Base > mem_r->Limit || !Size)
        return;

    NewBase = BAR_ALIGN(mem_r->Base, Alignment);
    if(NewBase > mem_r->Limit || NewBase + Size - 1 > mem_r->Limit)
        return;

    *BAR = NewBase; // Set BAR
    mem_r->Base = NewBase + Size; // Advance to new position
    *Cmd |= CMD_BM_MEM; // Set Memory Space Enable
}//SetMemBAR

VOID
SetPMem64BAR(
    IN        volatile 
            UINT32*   BAR,
    IN      BOOLEAN   IsMaxBAR,
    IN        UINT32    BarReq,
    IN    OUT    UINT8*    Cmd,
    IN    OUT    PMEM_REGS* mem_r
)
{
    UINT32 Alignment = ~(BarReq & 0xFFFFFFF0);
    UINT32 Size = Alignment + 1;
    UINT64 NewBase;

    if(mem_r->Base64 > mem_r->Limit64 || !Size)
        return;

    NewBase = BAR_ALIGN(mem_r->Base64, Alignment);
    if(NewBase > mem_r->Limit64 || NewBase + Size - 1 > mem_r->Limit64)
        return;

    *BAR = (UINT32)(NewBase & 0xFFFFFFFF); // Set BAR
    if(!IsMaxBAR)
    {
        BAR++;
        *BAR = (UINT32)(NewBase >> 32); // Set BAR U
    }
    mem_r->Base64 = NewBase + Size; // Advance to new position
    *Cmd |= CMD_BM_MEM; // Set Memory Space Enable
}//SetPMem64BAR

VOID
SetDevResources(
    IN        UINT8      Bus,
    IN        UINT8      Dev,
    IN        UINT8      FUNC_MAX, // PCI_MAX_FUNC for devices, 1 for bridge
    IN        UINT8      BAR_MAX, // PCI_BAR5 for devices, PCI_BAR1 for bridge
    IN    OUT    PortInfo   *pi
)
{
    UINT8       Fun;
    UINT8       Reg;
    UINT8       BCC; //Base Class Code
    UINT16      VendorID;
    UINT16      DeviceID;
    UINT32      BarReq;
    IO_REGS IO;
    MEM_REGS Mem;
    PMEM_REGS PMem;

    IO.Base = pi->IOBase << 8;
    IO.Limit = (pi->IOLimit << 8) | 0xFF;
    Mem.Base = pi->MemBase << 16;
    Mem.Limit = (pi->MemLimit << 16) | 0xFFFF;
    PMem.Base64 = pi->PMemBase64 << 16;
    PMem.Limit64 = (pi->PMemLimit64 << 16) | 0xFFFF;

    for (Fun = 0; Fun < FUNC_MAX; ++Fun)
    {
        UINT8 Cmd = SmiPci8 (0x00, Bus, Dev, Fun, PCI_CMD) = CMD_BUS_MASTER;
        BCC      = SmiPci8 (0x00, Bus, Dev, Fun, PCI_BCC);
        VendorID = SmiPci16 (0x00, Bus, Dev, Fun, PCI_VID);
        DeviceID = SmiPci16 (0x00, Bus, Dev, Fun, PCI_DID);

        if (0xFFFF == DeviceID)
            continue;

        for (Reg = PCI_BAR0; Reg <= BAR_MAX; Reg += 4)
        {
            BarReq = SaveSetGetRestoreBAR(SmiPci32Ptr (0x00, Bus, Dev, Fun, Reg));// Perform BAR sizing

            if (BarReq & BIT0) // I/O BAR
            {
                SetIOBAR(SmiPci32Ptr(0x00, Bus, Dev, Fun, Reg),
                    BarReq, &Cmd, &IO);
                continue;
            }

            if(BarReq & BIT3)// P-Memory BAR
            {
                SetPMem64BAR(SmiPci32Ptr(0x00, Bus, Dev, Fun, Reg), BAR_MAX == Reg, BarReq, &Cmd, &PMem);
            }
            else
            {
                SetMemBAR(SmiPci32Ptr(0x00, Bus, Dev, Fun, Reg), BarReq, &Cmd, &Mem);
            }

            if (BIT2 == (BarReq & (BIT2 | BIT1))) // Base address is 64 bits wide
            {
                Reg += 4;
                if(!(BarReq & BIT3))// 64-bit memory bar
                    SmiPci32 (0x00, Bus, Dev, Fun, Reg) = 0; // Allocate from 32 bit space
            }
        }

        // Assign ROM BAR
        if (!(IsTBTDevice(DeviceID) && VendorID == 0x8086)){
            TRACE((-1, "Start Assign ROM BAR for device....\n"));
            if (BCC == PCI_CL_BRIDGE)
                Reg = PCI_P2P_ROM_BAR;
            else
                Reg = PCI_DEV_ROM_BAR;

            BarReq = SaveSetGetRestoreBAR(SmiPci32Ptr (0x00, Bus, Dev, Fun, Reg));// Perform BAR sizing
            SetMemBAR(SmiPci32Ptr(0x00, Bus, Dev, Fun, Reg), BarReq, &Cmd, &Mem);
            TRACE((-1, "Assign rom bar end....\n"));
        }

        if(Cmd & BIT1) // If device uses I/O and MEM mapping use only MEM mepping
            Cmd &= ~BIT0;

        SmiPci8  (0x00, Bus, Dev, Fun, PCI_CMD) = Cmd;
        SmiPci8  (0x00, Bus, Dev, Fun, PCI_CLS) = gCacheLineSize;
    }// Fun < PCI_MAX_FUNC
    
    // Update pi if any changes
    if (IO.Base > ((UINT32)pi->IOBase << 8))
        pi->IOBase = (UINT8)(BAR_ALIGN(IO.Base, 0xFFF) >> 8);

    if (Mem.Base > ((UINT32)pi->MemBase << 16))
        pi->MemBase = (UINT16)(BAR_ALIGN(Mem.Base, 0xFFFFF) >> 16);

    if (PMem.Base64 > (pi->PMemBase64 << 16))
        pi->PMemBase64 = (BAR_ALIGN(PMem.Base64, 0xFFFFF) >> 16);
}// SetDevResources

typedef struct _DEV_ID
{
  UINT8     Bus;
  UINT8     Dev;
  UINT8     Fun;
} DEV_ID;

DEV_ID HR_Slots[] = 
{
    {0x00, 0x1C, 0x00},// PCH slot 0
    {0x00, 0x1C, 0x01},// PCH slot 1
    {0x00, 0x1C, 0x02},// PCH slot 2
    {0x00, 0x1C, 0x03},// PCH slot 3
    {0x00, 0x1C, 0x04},// PCH slot 4
    {0x00, 0x1C, 0x05},// PCH slot 5
    {0x00, 0x1C, 0x06},// PCH slot 6
    {0x00, 0x1C, 0x07},// PCH slot 7
#if !defined TBT_NB_PCIE_SLOT_SUPPORT || TBT_NB_PCIE_SLOT_SUPPORT == 0
    {0x00, 0x01, 0x00},// PEG0 slot
#else
#if !defined TBT_HIGHLAND_PLATFORM_CONFIG || TBT_HIGHLAND_PLATFORM_CONFIG == 0
    {0x00, 0x01, 0x00},// PEG0 slot
    {0x00, 0x01, 0x01},// PEG1 slot
    {0x00, 0x01, 0x02},// PEG2 slot
#else
    {0x00, 0x01, 0x00},// CPU0 NB D01F0 slot
    {0x00, 0x01, 0x01},// CPU0 NB D01F1 slot
    {0x00, 0x02, 0x00},// CPU0 NB D02F0 slot
    {0x00, 0x02, 0x01},// CPU0 NB D02F1 slot
    {0x00, 0x02, 0x02},// CPU0 NB D02F2 slot
    {0x00, 0x02, 0x03},// CPU0 NB D02F3 slot
    {0x00, 0x03, 0x00},// CPU0 NB D03F0 slot
    {0x00, 0x03, 0x01},// CPU0 NB D03F1 slot
    {0x00, 0x03, 0x02},// CPU0 NB D03F2 slot
    {0x00, 0x03, 0x03},// CPU0 NB D03F3 slot
#endif
#endif // TBT_NB_PCIE_SLOT_SUPPORT
};

//#define count(x) (sizeof(x) / sizeof((x)[0]))

typedef struct _BRDG_RES_CONFIG
{
    UINT8    Cmd;
    UINT8    Cls;
    UINT8    IOBase;
    UINT8    IOLimit;
    UINT16   MemBase;
    UINT16   MemLimit;
    UINT64   PMemBase64;
    UINT64   PMemLimit64;
} BRDG_RES_CONFIG;

const
BRDG_RES_CONFIG NOT_IN_USE_BRIDGE = 
{
    CMD_BUS_MASTER,
    0,
    DISBL_IO_REG1C & 0xFF,
    DISBL_IO_REG1C >> 8,
    DISBL_MEM32_REG20 & 0xFFFF,
    DISBL_MEM32_REG20 >> 16,
    DISBL_PMEM_REG24 & 0xFFFF,
    DISBL_PMEM_REG24 >> 16
};

typedef struct _BRDG_CONFIG
{
    DEV_ID           DevId;
    UINT8            PBus;
    UINT8            SBus;
    UINT8            SubBus;
    BRDG_RES_CONFIG  Res;
} BRDG_CONFIG;

enum {
HR_US_PORT, 
HR_DS_PORT0,
HR_DS_PORT3,
HR_DS_PORT4,
HR_DS_PORT5,
HR_DS_PORT6,
MAX_CFG_PORTS
};

enum {
	HR_DS_PORT1 = HR_DS_PORT3
};

BRDG_CONFIG HRConfigs[MAX_CFG_PORTS];// US(X:0:0), DS(X+1:3:0),DS(X+1:4:0),DS(X+1:5:0),DS(X+1:6:0)

typedef struct _HR_CONFIG
{
	UINT16           DeviceId;
	UINT8            HRBus;
	UINT8            MinDSNumber;
	UINT8            MaxDSNumber;
	UINT8            BridgeLoops;
} HR_CONFIG;

VOID
InitCommonHRConfigs(
    IN        HR_CONFIG *HR_Config,
    IN        UINT8 BusNumLimit,
    IN    OUT    BRDG_RES_CONFIG* HRResConf
)
{
    UINT8 i,j;
    // US(HRBus:0:0)
    HRConfigs[HR_US_PORT].DevId.Bus = HR_Config->HRBus;
    HRConfigs[HR_US_PORT].DevId.Dev = 0;
    HRConfigs[HR_US_PORT].DevId.Fun = 0;
    HRConfigs[HR_US_PORT].Res = *HRResConf;
    if (gTbtIOresourceEnable == FALSE){
       HRConfigs[HR_US_PORT].Res.IOBase = 0xF1;
       HRConfigs[HR_US_PORT].Res.IOLimit = 0x01;
    }
    HRConfigs[HR_US_PORT].PBus = HRConfigs[HR_US_PORT].DevId.Bus;
    HRConfigs[HR_US_PORT].SBus = HRConfigs[HR_US_PORT].PBus + 1;
    HRConfigs[HR_US_PORT].SubBus = BusNumLimit;

    // NHI resides here
    HRConfigs[HR_DS_PORT0].DevId.Bus = HRConfigs[HR_US_PORT].DevId.Bus + 1;
    HRConfigs[HR_DS_PORT0].DevId.Dev = 0;
    HRConfigs[HR_DS_PORT0].DevId.Fun = 0;
    HRConfigs[HR_DS_PORT0].Res = NOT_IN_USE_BRIDGE;
    HRConfigs[HR_DS_PORT0].Res.MemBase = HRResConf->MemLimit;
    HRConfigs[HR_DS_PORT0].Res.MemLimit = HRResConf->MemLimit;
    HRResConf->MemLimit -= 0x10; //This 1 MB chunk will be used by NHI
    HRConfigs[HR_DS_PORT0].Res.Cmd = CMD_BM_MEM;
    HRConfigs[HR_DS_PORT0].Res.Cls = gCacheLineSize;
    HRConfigs[HR_DS_PORT0].PBus = HRConfigs[HR_DS_PORT0].DevId.Bus;
    HRConfigs[HR_DS_PORT0].SBus = HRConfigs[HR_DS_PORT0].PBus + 1;
    HRConfigs[HR_DS_PORT0].SubBus = HRConfigs[HR_DS_PORT0].PBus + 1;

	switch(HR_Config->DeviceId)
	{
		case BDW_TBT_LP_HR:// HR with 1 DS only
			HRConfigs[HR_DS_PORT1].DevId.Bus = HRConfigs[HR_US_PORT].DevId.Bus + 1;
			HRConfigs[HR_DS_PORT1].DevId.Dev = 1;
			HRConfigs[HR_DS_PORT1].DevId.Fun = 0;
			HRConfigs[HR_DS_PORT1].Res = *HRResConf;
			HRConfigs[HR_DS_PORT1].PBus = HRConfigs[HR_DS_PORT1].DevId.Bus;
			HRConfigs[HR_DS_PORT1].SBus = HRConfigs[HR_DS_PORT0].SubBus + 1;
			HRConfigs[HR_DS_PORT1].SubBus = BusNumLimit;
			HR_Config->MinDSNumber = HRConfigs[HR_DS_PORT1].DevId.Dev;
			HR_Config->MaxDSNumber = HRConfigs[HR_DS_PORT1].DevId.Dev;
			HR_Config->BridgeLoops = 3;
			break;
		default:
		// DS(HRBus+2:3-6:0)
		HR_Config->MinDSNumber = 3;
		HR_Config->MaxDSNumber = 6;
		HR_Config->BridgeLoops = count(HRConfigs);

		for(j = 2, i = HR_Config->MinDSNumber; j < count(HRConfigs) && i <= HR_Config->MaxDSNumber; ++j, ++i)
		{
			HRConfigs[j].DevId.Bus = HRConfigs[HR_US_PORT].DevId.Bus + 1;
			HRConfigs[j].DevId.Dev = i;
			HRConfigs[j].DevId.Fun = 0;
			HRConfigs[j].PBus = HRConfigs[j].DevId.Bus;
			HRConfigs[j].Res.Cls = gCacheLineSize;
		}
	}
}//InitCommonHRConfigs

VOID
InitHRDSPort_Disable(
    IN        UINT8 id,
    IN    OUT    BRDG_CONFIG* BrdgConf
)
{
    HRConfigs[id].Res = NOT_IN_USE_BRIDGE;
    HRConfigs[id].SBus = BrdgConf->SBus;
    HRConfigs[id].SubBus = BrdgConf->SBus;

    BrdgConf->SBus++;
}//InitHRDSPort_Disable

VOID
InitHRDSPort_1Port(
    IN  OUT BRDG_CONFIG* BrdgConf
)
{
    UINT16 MemBase  = BrdgConf->Res.MemBase & 0xFFF0;
    UINT64 PMemBase64 = BrdgConf->Res.PMemBase64 & ~0xFULL;
    UINT8  IOBase   = BrdgConf->Res.IOBase & 0xF0;
    UINT8  BusRange = BrdgConf->SubBus - BrdgConf->PBus - (MAX_CFG_PORTS - 2); // MAX_CFG_PORTS-1(US)-1(HIA) is num of bridges in HR, on each bridge bus# is incremented
    BusRange -= DOCK_BUSSES; // Bus range for Dock port

    if (gTbtIOresourceEnable == TRUE)
       HRConfigs[HR_DS_PORT3].Res.Cmd = CMD_BM_MEM_IO;
    else{
       HRConfigs[HR_DS_PORT3].Res = NOT_IN_USE_BRIDGE;
       HRConfigs[HR_DS_PORT3].Res.Cmd = CMD_BM_MEM;
    }
    HRConfigs[HR_DS_PORT3].Res.Cls = gCacheLineSize;
    HRConfigs[HR_DS_PORT3].Res.MemBase = MemBase;
    HRConfigs[HR_DS_PORT3].Res.MemLimit = MemBase + 0xE00 - 1;
    HRConfigs[HR_DS_PORT3].Res.PMemBase64 = PMemBase64;
    HRConfigs[HR_DS_PORT3].Res.PMemLimit64 = PMemBase64 + 0x1A00 - 1;

    if (gTbtIOresourceEnable == TRUE){
       HRConfigs[HR_DS_PORT3].Res.IOBase = IOBase;
       if ((BrdgConf->Res.IOLimit & 0xF0) < (IOBase + 0x50))
         HRConfigs[HR_DS_PORT3].Res.IOLimit = BrdgConf->Res.IOLimit & 0xF0;
       else
         HRConfigs[HR_DS_PORT3].Res.IOLimit = IOBase + 0x50;
    }

    HRConfigs[HR_DS_PORT3].SBus = BrdgConf->SBus;
    HRConfigs[HR_DS_PORT3].SubBus = BrdgConf->SBus + BusRange;

    BrdgConf->SBus = HRConfigs[HR_DS_PORT3].SubBus + 1;

    if (gTbtIOresourceEnable == TRUE)
       HRConfigs[HR_DS_PORT4].Res.Cmd = CMD_BM_MEM_IO;
    else{
       HRConfigs[HR_DS_PORT4].Res = NOT_IN_USE_BRIDGE;
       HRConfigs[HR_DS_PORT4].Res.Cmd = CMD_BM_MEM;
    }
    HRConfigs[HR_DS_PORT4].Res.Cls = gCacheLineSize;
    HRConfigs[HR_DS_PORT4].Res.MemBase = MemBase + 0xE00;
    HRConfigs[HR_DS_PORT4].Res.MemLimit = MemBase + 0x1600 - 1;
    HRConfigs[HR_DS_PORT4].Res.PMemBase64 = PMemBase64 + 0x1A00;
    HRConfigs[HR_DS_PORT4].Res.PMemLimit64 = PMemBase64 + 0x2200 - 1;

    if (gTbtIOresourceEnable == TRUE){
       if (HRConfigs[HR_DS_PORT3].Res.IOLimit == (BrdgConf->Res.IOLimit & 0xF0)){
          HRConfigs[HR_DS_PORT4].Res.IOBase = 0xF1;
          HRConfigs[HR_DS_PORT4].Res.IOLimit = 0x01;
       }
       else{
          HRConfigs[HR_DS_PORT4].Res.IOBase = IOBase + 0x60;
          HRConfigs[HR_DS_PORT4].Res.IOLimit = BrdgConf->Res.IOLimit & 0xF0;
       }
    }

    HRConfigs[HR_DS_PORT4].SBus = BrdgConf->SBus;
    HRConfigs[HR_DS_PORT4].SubBus = BrdgConf->SBus + DOCK_BUSSES;

    BrdgConf->SBus = HRConfigs[HR_DS_PORT4].SubBus + 1;
}//InitHRDSPort_1Port

VOID
InitHRDSPort_2Port(
    IN  OUT BRDG_CONFIG* BrdgConf
)
{
    UINT16 MemBase  = BrdgConf->Res.MemBase & 0xFFF0;
    UINT64 PMemBase64 = BrdgConf->Res.PMemBase64 & ~0xFULL;
    UINT8  IOBase   = BrdgConf->Res.IOBase & 0xF0;
    UINT8  BusRange = BrdgConf->SubBus - BrdgConf->PBus - (MAX_CFG_PORTS - 2); // MAX_CFG_PORTS-1(US)-1(HIA) is num of bridges in HR, on each bridge bus# is incremented

    BusRange -= 2 * DOCK_BUSSES; // Bus range for Dock ports
    // Rest of busses split between ports 3 and 5
    BusRange /= 2; // Bus range for port 3/5

    if (gTbtIOresourceEnable == TRUE)
       HRConfigs[HR_DS_PORT3].Res.Cmd = CMD_BM_MEM_IO;
    else{
       HRConfigs[HR_DS_PORT3].Res = NOT_IN_USE_BRIDGE;
       HRConfigs[HR_DS_PORT3].Res.Cmd = CMD_BM_MEM;
    }
    HRConfigs[HR_DS_PORT3].Res.Cls = gCacheLineSize;
    HRConfigs[HR_DS_PORT3].Res.MemBase = MemBase;
    HRConfigs[HR_DS_PORT3].Res.MemLimit = MemBase + 0x1000 - 1;
    HRConfigs[HR_DS_PORT3].Res.PMemBase64 = PMemBase64;
    HRConfigs[HR_DS_PORT3].Res.PMemLimit64 = PMemBase64 + 0x2000 - 1;

    if (gTbtIOresourceEnable == TRUE){
       HRConfigs[HR_DS_PORT3].Res.IOBase = IOBase;
       if ((BrdgConf->Res.IOLimit & 0xF0) < (IOBase + 0x50))
         HRConfigs[HR_DS_PORT3].Res.IOLimit = BrdgConf->Res.IOLimit & 0xF0;
       else
         HRConfigs[HR_DS_PORT3].Res.IOLimit = IOBase + 0x50;
    }

    HRConfigs[HR_DS_PORT3].SBus = BrdgConf->SBus;
    HRConfigs[HR_DS_PORT3].SubBus = BrdgConf->SBus + BusRange;

    BrdgConf->SBus = HRConfigs[HR_DS_PORT3].SubBus + 1;

    if (gTbtIOresourceEnable == TRUE)
       HRConfigs[HR_DS_PORT4].Res.Cmd = CMD_BM_MEM_IO;
    else{
       HRConfigs[HR_DS_PORT4].Res = NOT_IN_USE_BRIDGE;
       HRConfigs[HR_DS_PORT4].Res.Cmd = CMD_BM_MEM;
    }
    HRConfigs[HR_DS_PORT4].Res.Cls = gCacheLineSize;
    HRConfigs[HR_DS_PORT4].Res.MemBase = MemBase + 0x1000;
    HRConfigs[HR_DS_PORT4].Res.MemLimit = MemBase + 0x1800 - 1;
    HRConfigs[HR_DS_PORT4].Res.PMemBase64 = PMemBase64 + 0x2000;
    HRConfigs[HR_DS_PORT4].Res.PMemLimit64 = PMemBase64 + 0x2800 - 1;

    if (gTbtIOresourceEnable == TRUE){
        HRConfigs[HR_DS_PORT4].Res.Cmd     = CMD_BM_MEM;
        HRConfigs[HR_DS_PORT4].Res.IOBase  = 0xF1;
        HRConfigs[HR_DS_PORT4].Res.IOLimit = 0x01;
    }

    HRConfigs[HR_DS_PORT4].SBus = BrdgConf->SBus;
    HRConfigs[HR_DS_PORT4].SubBus = BrdgConf->SBus + DOCK_BUSSES;

    BrdgConf->SBus = HRConfigs[HR_DS_PORT4].SubBus + 1;

    if (gTbtIOresourceEnable == TRUE)
       HRConfigs[HR_DS_PORT5].Res.Cmd = CMD_BM_MEM_IO;
    else{
       HRConfigs[HR_DS_PORT5].Res = NOT_IN_USE_BRIDGE;
       HRConfigs[HR_DS_PORT5].Res.Cmd = CMD_BM_MEM;
    }
    HRConfigs[HR_DS_PORT5].Res.Cls = gCacheLineSize;
    HRConfigs[HR_DS_PORT5].Res.MemBase = MemBase + 0x1800;
    HRConfigs[HR_DS_PORT5].Res.MemLimit = MemBase + 0x2600 - 1;
    HRConfigs[HR_DS_PORT5].Res.PMemBase64 = PMemBase64 + 0x3000;
    HRConfigs[HR_DS_PORT5].Res.PMemLimit64 = PMemBase64 + 0x4A00 - 1;

    if (gTbtIOresourceEnable == TRUE){
        if (HRConfigs[HR_DS_PORT3].Res.IOLimit == (BrdgConf->Res.IOLimit & 0xF0)){
            HRConfigs[HR_DS_PORT5].Res.IOBase  = 0xF1;
            HRConfigs[HR_DS_PORT5].Res.IOLimit = 0x01;
        } else {
            HRConfigs[HR_DS_PORT5].Res.IOBase  = IOBase + 0x60;
            HRConfigs[HR_DS_PORT5].Res.IOLimit = BrdgConf->Res.IOLimit & 0xF0;
        }
    }
    HRConfigs[HR_DS_PORT5].SBus = BrdgConf->SBus;
    HRConfigs[HR_DS_PORT5].SubBus = BrdgConf->SBus + BusRange;

    BrdgConf->SBus = HRConfigs[HR_DS_PORT5].SubBus + 1;

    if (gTbtIOresourceEnable == TRUE)
       HRConfigs[HR_DS_PORT6].Res.Cmd = CMD_BM_MEM_IO;
    else{
       HRConfigs[HR_DS_PORT6].Res = NOT_IN_USE_BRIDGE;
       HRConfigs[HR_DS_PORT6].Res.Cmd = CMD_BM_MEM;
    }
    HRConfigs[HR_DS_PORT6].Res.Cls = gCacheLineSize;
    HRConfigs[HR_DS_PORT6].Res.MemBase = MemBase + 0x2600;
    HRConfigs[HR_DS_PORT6].Res.MemLimit = MemBase + 0x2E00 - 1;
    HRConfigs[HR_DS_PORT6].Res.PMemBase64 = PMemBase64 + 0x2800;
    HRConfigs[HR_DS_PORT6].Res.PMemLimit64 = PMemBase64 + 0x3000 - 1;
    if (gTbtIOresourceEnable == TRUE){
          HRConfigs[HR_DS_PORT6].Res.Cmd     = CMD_BM_MEM;
          HRConfigs[HR_DS_PORT6].Res.IOBase  = 0xF1;
          HRConfigs[HR_DS_PORT6].Res.IOLimit = 0x01;
    }
    HRConfigs[HR_DS_PORT6].SBus = BrdgConf->SBus;
    HRConfigs[HR_DS_PORT6].SubBus = BrdgConf->SBus + DOCK_BUSSES;

    BrdgConf->SBus = HRConfigs[HR_DS_PORT6].SubBus + 1;
}//InitHRDSPort_2Port

BOOLEAN
CheckLimits(
    IN      BOOLEAN         Is2PortDev,
    IN      BRDG_RES_CONFIG *HRResConf,
    IN      UINT8           BusRange
)
{
    UINT16 MemBase  = HRResConf->MemBase & 0xFFF0;
    UINT16 MemLimit = HRResConf->MemLimit & 0xFFF0;
    UINT64 PMemBase64  = HRResConf->PMemBase64 & 0xFFF0;
    UINT64 PMemLimit64 = HRResConf->PMemLimit64 & 0xFFF0;
    UINT8  IOBase   = HRResConf->IOBase & 0xF0;
    UINT8  IOLimit  = HRResConf->IOLimit & 0xF0;

    TRACE((-1, "TbtSmm.c: MemBase   = %x\n", MemBase));
    TRACE((-1, "TbtSmm.c: MemLimit  = %x\n", MemLimit));
    TRACE((-1, "TbtSmm.c: PMemBase  = %x\n", PMemBase64));
    TRACE((-1, "TbtSmm.c: PMemLimit = %x\n", PMemLimit64));

    // Check memory alignment
    if(MemBase & 0x3FF)
    {
        TRACE((-1, "TbtSmm.c: M alig is not 64 MB.\n"));
        return FALSE;
    }
    if(PMemBase64 & 0xFFF)
    {
        TRACE((-1, "TbtSmm.c: PM alig is not 256 MB.\n"));
        return FALSE;
    }

    // Check mem size
    
    if(Is2PortDev)
    {
        // Check mem size
        if(MemLimit + 0x10 - MemBase < 0x2E00)
        {
            TRACE((-1, "TbtSmm.c: M size is small than 737 MB.\n"));
            return FALSE;
        }
        // Check P-mem size
        if(PMemLimit64 + 0x10 - PMemBase64 < 0x4A00)
        {
            TRACE((-1, "TbtSmm.c: PM size is small than 1184 MB.\n"));
            return FALSE;
        }
        // Check bus range
        if(BusRange < 106)
        {
            TRACE((-1, "TbtSmm.c: Bus range is small than 106.\n"));
            return FALSE;
        }
    }
    else
    {
        if(MemLimit + 0x10 - MemBase < 0x1600) //Reserved mem min: 353MB
        {
            TRACE((-1, "TbtSmm.c: M size is small than 353 MB.\n"));
            return FALSE;
        }
        if(PMemLimit64 + 0x10 - PMemBase64 < 0x2200) //Prefetchable mem min: 544MB
        {
            TRACE((-1, "TbtSmm.c: PM size is small than 544 MB.\n"));
            return FALSE;
        }
        if(BusRange < 56) //Reserved bus min: 56
        {
            TRACE((-1, "TbtSmm.c: Bus range is small than 56\n"));
            return FALSE;
        }
    }

    return TRUE;
}

BOOLEAN
InitHRResConfigs(
    IN	  OUT    HR_CONFIG *HR_Config,
    IN           UINT8 BusNumLimit,
    IN    OUT    BRDG_RES_CONFIG* HRResConf
)
{
    BRDG_CONFIG BrdgConf = {0};
    InitCommonHRConfigs(HR_Config, BusNumLimit, HRResConf);
    BrdgConf.PBus = HR_Config->HRBus + 2;
    BrdgConf.SBus = HR_Config->HRBus + 3;
    BrdgConf.SubBus = BusNumLimit;
    BrdgConf.Res = *HRResConf;
    while(TRUE){
      switch(HR_Config->DeviceId)
      {
      case CR_HR_4C:
      case RR_HR_4C: 
      case FR_HR_4C: // 2 Port host
          if(CheckLimits(TRUE, HRResConf, BusNumLimit - HR_Config->HRBus))
          {
              InitHRDSPort_2Port(&BrdgConf);
              return TRUE;
          }
          else
          {
              HR_Config->DeviceId = 0; // Jump to default on next loop
              continue;
          }
      case CR_HR_2C:
      case RR_HR_2C:
      case FR_HR_2C: // 1 Port host
          if(CheckLimits(FALSE, HRResConf, BusNumLimit - HR_Config->HRBus))
          {	
              InitHRDSPort_1Port(&BrdgConf);
              InitHRDSPort_Disable(HR_DS_PORT5, &BrdgConf);
              InitHRDSPort_Disable(HR_DS_PORT6, &BrdgConf);
              return TRUE;
          }
      case BDW_TBT_LP_HR: // 1 Port host
          return TRUE;
      default:
              InitHRDSPort_Disable(HR_DS_PORT3, &BrdgConf);
              InitHRDSPort_Disable(HR_DS_PORT4, &BrdgConf);
              InitHRDSPort_Disable(HR_DS_PORT5, &BrdgConf);
              InitHRDSPort_Disable(HR_DS_PORT6, &BrdgConf);
              return FALSE;
      }//switch
    }//while
}//InitHRResConfigs

BOOLEAN
InitializeHostRouter(
        OUT  HR_CONFIG  *HR_Config
)
{
    UINT8             BusNumLimit;
    BRDG_RES_CONFIG   HRResConf = {0};
    UINT8             i;
	BOOLEAN           Ret = TRUE;

    for(i = 0; i < count(HR_Slots); ++i)
    {
        HR_Config->HRBus  = SmiPci8  (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_SBUS);
        HR_Config->DeviceId = SmiPci16 (0x00, HR_Config->HRBus, 0x00, 0x00, PCI_DID);
        if (IsTBTHostRouter(HR_Config->DeviceId))
            break;
    }

    if(i >= count(HR_Slots))
        return FALSE;

    if (gTbtIOresourceEnable == TRUE)
       HRResConf.Cmd         = CMD_BM_MEM_IO;
    else
       HRResConf.Cmd         = CMD_BM_MEM;
    HRResConf.Cls         = gCacheLineSize;
    HRResConf.IOBase      = SmiPci8  (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_IOBASE);
    HRResConf.IOLimit     = SmiPci8  (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_IOLIMIT);
    HRResConf.MemBase     = SmiPci16 (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_MEMBASE);
    HRResConf.MemLimit    = SmiPci16 (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_MEMLIMIT);
    HRResConf.PMemBase64  = SmiPci16 (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_PRE_MEMBASE);
    HRResConf.PMemLimit64 = SmiPci16 (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_PRE_MEMLIMIT);
    HRResConf.PMemBase64 |= SmiPci32 (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_PRE_MEMBASE_U) << 16;
    HRResConf.PMemLimit64|= SmiPci32 (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_PRE_MEMLIMIT_U) << 16;
    BusNumLimit           = SmiPci8  (0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_SUBUS);

    // BIOS support of Thunderbolt devices Specification Update
    // Revision 0.91
    // 8.1.2 VGA Enable should not be set
    // VGA Enable and VGA 16-bit decode registers of Bridge 
    // control register of Root port where Host router resides
    // should be cleaned(Both of them should set into 0).
    SmiPci8And(0x00, HR_Slots[i].Bus, HR_Slots[i].Dev, HR_Slots[i].Fun, PCI_BRIDGE_CNTL, 0xE7);

	Ret = InitHRResConfigs(HR_Config, BusNumLimit, &HRResConf);

    for(i = 0; i < HR_Config->BridgeLoops; ++i)
    {
        UINT8 Bus = HRConfigs[i].DevId.Bus;
        UINT8 Dev = HRConfigs[i].DevId.Dev;
        UINT8 Fun = HRConfigs[i].DevId.Fun;

        SmiPci8  (0x00, Bus, Dev, Fun, PCI_CLS) = HRConfigs[i].Res.Cls;
        SmiPci8  (0x00, Bus, Dev, Fun, PCI_PBUS) = HRConfigs[i].PBus;
        SmiPci8  (0x00, Bus, Dev, Fun, PCI_SBUS) = HRConfigs[i].SBus;
        SmiPci8  (0x00, Bus, Dev, Fun, PCI_SUBUS) = HRConfigs[i].SubBus;
        SmiPci16 (0x00, Bus, Dev, Fun, PCI_MEMBASE) = HRConfigs[i].Res.MemBase;
        SmiPci16 (0x00, Bus, Dev, Fun, PCI_MEMLIMIT) = HRConfigs[i].Res.MemLimit;
        SmiPci16 (0x00, Bus, Dev, Fun, PCI_PRE_MEMBASE) = (UINT16)(HRConfigs[i].Res.PMemBase64 & 0xFFFF);
        SmiPci16 (0x00, Bus, Dev, Fun, PCI_PRE_MEMLIMIT) = (UINT16)(HRConfigs[i].Res.PMemLimit64 & 0xFFFF);
        SmiPci32 (0x00, Bus, Dev, Fun, PCI_PRE_MEMBASE_U) = (UINT32)(HRConfigs[i].Res.PMemBase64 >> 16);
        SmiPci32 (0x00, Bus, Dev, Fun, PCI_PRE_MEMLIMIT_U) = (UINT32)(HRConfigs[i].Res.PMemLimit64 >> 16);
        SmiPci8  (0x00, Bus, Dev, Fun, PCI_IOBASE) = HRConfigs[i].Res.IOBase;
        SmiPci8  (0x00, Bus, Dev, Fun, PCI_IOLIMIT) = HRConfigs[i].Res.IOLimit;
        SmiPci32 (0x00, Bus, Dev, Fun, PCI_IOBASE_U) = 0x00000000;
        SmiPci8  (0x00, Bus, Dev, Fun, PCI_CMD) = HRConfigs[i].Res.Cmd;
    }

    SmiPci32 (0x00, (HR_Config->HRBus + 2), 0x00, 0x00, PCI_BAR0) = HRConfigs[HR_DS_PORT0].Res.MemLimit << 16;
    SmiPci32 (0x00, (HR_Config->HRBus + 2), 0x00, 0x00, PCI_BAR1) = (HRConfigs[HR_DS_PORT0].Res.MemLimit + 0x4) << 16;
    SmiPci8  (0x00, (HR_Config->HRBus + 2), 0x00, 0x00, PCI_CLS)  = gCacheLineSize;
    SmiPci8  (0x00, (HR_Config->HRBus + 2), 0x00, 0x00, PCI_CMD)  = CMD_BM_MEM;
    
    return Ret;
}//InitializeHostRouter

UINT8
ConfigureSlot(
    IN        UINT8     Bus,
    IN        UINT8     MAX_DEVICE,
    IN        INT8      Depth, 
    IN    OUT    PortInfo* pi
)
{
    UINT8    Device;
    UINT8    SBus;
    UINT8    UsedBusNumbers;
    UINT8    RetBusNum = 0;
    PortInfo CurrentSlot;

    for (Device = 0; Device < MAX_DEVICE; Device++)
    {
        // Continue if device is absent
        if (0xFFFF == SmiPci16 (0x00, Bus, Device, 0x00, PCI_DID))
            continue;

        if (P2P_BRIDGE != SmiPci16 (0x00, Bus, Device, 0x00, PCI_SCC))
        {
             SetDevResources(Bus, Device,
                PCI_MAX_FUNC, PCI_BAR5, pi);
            continue;
        }
        // Else Bridge

        CurrentSlot = *pi; // Save before update

        ++RetBusNum; // UP Bridge
        SBus = Bus + RetBusNum; // DS Bridge

        if (SBus + 1 >= pi->BusNumLimit)
            continue;

        SetDevResources(Bus, Device, 1, PCI_BAR1, pi);

        // Init UP Bridge to reach DS Bridge
        SmiPci8 (0x00, Bus, Device, 0x00, PCI_PBUS) = Bus;
        SmiPci8 (0x00, Bus, Device, 0x00, PCI_SBUS) = SBus;
        SmiPci8 (0x00, Bus, Device, 0x00, PCI_SUBUS) = pi->BusNumLimit;// Just in case
        if (gTbtIOresourceEnable == TRUE)
           SmiPci8 (0x00, Bus, Device, 0x00, PCI_CMD) = CMD_BM_MEM_IO;
        else
           SmiPci8 (0x00, Bus, Device, 0x00, PCI_CMD) = CMD_BM_MEM;

        UsedBusNumbers = ConfigureSlot(SBus, PCI_MAX_DEVICE + 1, -1, pi);

        RetBusNum += UsedBusNumbers;

        SetPHYPortResources(Bus, Device,
            SBus + UsedBusNumbers, Depth,
            &CurrentSlot, pi);
    }//for (Device = 0; Device <= PCI_MAX_DEVICE; Device++)
    return RetBusNum;
}// ConfigureSlot

VOID
SetCIOPortResources(
    IN        UINT8 Bus, 
    IN        UINT8 Dev,
    IN        UINT8 SBus,
    IN        UINT8 SubBus,
    IN      PortInfo* portInfoBeforeChange, 
    IN  OUT PortInfo* pi
)
{
    UINT8    Cmd = CMD_BUS_MASTER;

    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_PBUS) = Bus;
    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_SBUS) = SBus;
    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_SUBUS) = SubBus;
    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_CMD) = Cmd;

    if (pi->IOBase <= pi->IOLimit)
    {
        SmiPci8  (0x00, Bus, Dev, 0x00, PCI_IOBASE) = pi->IOBase;
        SmiPci8  (0x00, Bus, Dev, 0x00, PCI_IOLIMIT) = pi->IOLimit;
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_IOBASE_U) = 0x00000000;
        Cmd |= CMD_BM_IO;
    }
    else
    {
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_IOBASE) = DISBL_IO_REG1C;
    }

    if (pi->MemBase <= pi->MemLimit)
    {
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_MEMBASE) = pi->MemBase;
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_MEMLIMIT) = pi->MemLimit;
        Cmd |= CMD_BM_MEM;
    }
    else
    {
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_MEMBASE) = DISBL_MEM32_REG20;
    }

    if (pi->PMemBase64 <= pi->PMemLimit64)
    {
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE) = (UINT16)(pi->PMemBase64 & 0xFFFF);
        SmiPci16 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMLIMIT) = (UINT16)(pi->PMemLimit64 & 0xFFFF);
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE_U) = (UINT32)(pi->PMemBase64 >> 16);
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMLIMIT_U) = (UINT32)(pi->PMemLimit64 >> 16);
        Cmd |= CMD_BM_MEM;
    }
    else
    {
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE) = DISBL_PMEM_REG24;
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE_U) = 0;
        SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMLIMIT_U) = 0;
    }

    SmiPci8  (0x00, Bus, Dev, 0x00, PCI_CMD) = Cmd;
    SmiPci8 (0x00, Bus, Dev, 0x00, PCI_CLS) = gCacheLineSize;
}//SetCIOPortResources

VOID
SetSlotsAsUnused(
    IN        UINT8 Bus,
    IN        UINT8 MaxSlotNum,
    IN        UINT8 CIOSlot,
    IN    OUT PortInfo* pi
)
{
    UINT8 Slot;
    for (Slot = MaxSlotNum; Slot > CIOSlot; --Slot)
    {
        if (0xFFFF == SmiPci16 (0x00, Bus, Slot, 0x00, PCI_DID))
            continue;

        SmiPci8 (0x00, Bus, Slot, 0x00, PCI_CLS) = gCacheLineSize;
        SmiPci8  (0x00, Bus, Slot, 0x00, PCI_PBUS) = Bus;
        SmiPci8  (0x00, Bus, Slot, 0x00, PCI_SBUS) = pi->BusNumLimit;
        SmiPci8  (0x00, Bus, Slot, 0x00, PCI_SUBUS) = pi->BusNumLimit;
        SmiPci16 (0x00, Bus, Slot, 0x00, PCI_IOBASE) = DISBL_IO_REG1C;
        SmiPci32 (0x00, Bus, Slot, 0x00, PCI_MEMBASE) = DISBL_MEM32_REG20;
        SmiPci32 (0x00, Bus, Slot, 0x00, PCI_PRE_MEMBASE) = DISBL_PMEM_REG24;
        SmiPci8  (0x00, Bus, Slot, 0x00, PCI_CMD) = CMD_BUS_MASTER;

        pi->BusNumLimit--;
    }
}//SetSlotsAsUnused

#define PCIE_CAP_ID_VSEC   0x000B

UINT16
FindVendorSpecificHeader(
    IN        UINT8  Bus
)
{
    PCIE_EXT_CAP_HDR  ExtCap;
    UINT16 ExtendedRegister = 0x100;

    while (ExtendedRegister)
    {
        ExtCap.EXT_CAP_HDR = SmiPci32  (0x00, Bus, 0x00, 0x00, ExtendedRegister);
        if (ExtCap.ExtCapId == 0xFFFF)
            return 0x0000; // No Vendor-Specific Extended Capability header

        if (PCIE_CAP_ID_VSEC == ExtCap.ExtCapId)
            return ExtendedRegister;

        ExtendedRegister = (UINT16)ExtCap.NextItemPtr;
    }
    return 0x0000; // No Vendor-Specific Extended Capability header
}

#define PCIE_CAP_ID_SSID_SSVID   0x0D

UINT8
FindSSID_SSVIDHeader(
    IN        UINT8  Bus
)
{
    UINT8  CapHeaderId;
    UINT8  CapHeaderOffset = SmiPci8 (0x00, Bus, 0x00, 0x00, PCI_CAPP);

    while (CapHeaderOffset != 0)
    {
        CapHeaderId = SmiPci8 (0x00, Bus, 0x00, 0x00, CapHeaderOffset);

        if (CapHeaderId == PCIE_CAP_ID_SSID_SSVID)
            return CapHeaderOffset;

        CapHeaderOffset = SmiPci8 (0x00, Bus, 0x00, 0x00, CapHeaderOffset + 1);
    }
    TRACE((-1, "TbtSmm.c: Cannot find SSID Capability header...\n"));
    return 0;
}//FindSSID_SSVIDHeader

typedef union _BRDG_CIO_MAP_REG
{
    UINT32    AB_REG;
    struct
    {
        UINT32        NumOfDSPorts : 5;
        UINT32        CIOPortMap   : 27;
    };
}BRDG_CIO_MAP_REG;

BOOLEAN
GetCIOSlotByDevId(
    IN        UINT8  Bus,
        OUT    UINT8* CIOSlot,
        OUT    UINT8* MaxSlotNum
)
{
    UINT16            VSECRegister;
    BRDG_CIO_MAP_REG  BridgMap;
    UINT32            BitScanRes;
    UINT16            DevId = SmiPci16 (0x00, Bus, 0x00, 0x00, PCI_DID);

    // Init out params in case device is not recognised
    *CIOSlot = 4;
    *MaxSlotNum = 7;

    switch(DevId) // For known device IDs
    {
    case 0x1513:
    case 0x151A:
    case 0x151B:
    case 0x1547:
    case 0x1548:
        return TRUE; // Just return
    case 0x1549:
        return FALSE; // PR Device ID - have no CIO slots
    }

    VSECRegister = FindVendorSpecificHeader(Bus);
    if(!VSECRegister)
        return TRUE; // Just return

    // Go to Bridge/CIO map register
    VSECRegister += 0x18;

    BridgMap.AB_REG = SmiPci32  (0x00, Bus, 0x00, 0x00, VSECRegister);
    // Check for range
    if(BridgMap.NumOfDSPorts < 1 || BridgMap.NumOfDSPorts > 27)
        return TRUE;// Not a valid register

    // Set OUT params

    *MaxSlotNum = (UINT8)BridgMap.NumOfDSPorts;
    
    if(!_BitScanForward(&BitScanRes, BridgMap.CIOPortMap))// No DS bridge which is CIO port
        return FALSE;

    *CIOSlot = (UINT8)BitScanRes;
    return TRUE;
}//GetCIOSlotByDevId

#define TBT_LEGACY_SUB_SYS_ID 0x11112222

BOOLEAN
IsLegacyDevice(
    IN        UINT8  Bus
)
{
    UINT32 SID;
    UINT8  SIDRegister;
    UINT16 DevId = SmiPci16 (0x00, Bus, 0x00, 0x00, PCI_DID);
    switch(DevId) // For known device IDs
    {
    case 0x1513:
    case 0x151A:
    case 0x151B:
        TRACE((-1, "TbtSmm.c: Legacy device %x...\n", DevId));
        return TRUE; // Legacy device by Device Id
    }

    SIDRegister = FindSSID_SSVIDHeader(Bus);

    if(!SIDRegister)
        return TRUE; // May be absent for legacy devices

    // Go to register
    SIDRegister += 0x4;

    SID = SmiPci32  (0x00, Bus, 0x00, 0x00, SIDRegister);
    TRACE((-1, "TbtSmm.c: SSID of device is %x...\n", SID));

    return TBT_LEGACY_SUB_SYS_ID == SID || 0 == SID;
}//IsLegacyDevice

BOOLEAN
ConfigureEP(
    IN      INT8  Depth, 
    IN    OUT UINT8* Bus,
    IN    OUT PortInfo* pi
)
{
    UINT8     SBus;
    UINT8     CIOSlot = 4;
    UINT8     MaxSlotNum = 7;
    UINT8     MaxPHYSlots;
    UINT8     UsedBusNumbers;
    UINT8     cmd;
    BOOLEAN   CIOSlotPresent;
    BOOLEAN   Continue;
    PortInfo  portInfo = *pi;

	// Endpoint on CIO slot, but not a bridge device
	if (P2P_BRIDGE != SmiPci16 (0x00, *Bus, 0x00, 0x00, PCI_SCC))
	{
		// Check whether EP already configured by examining CMD register
		cmd = SmiPci8  (0x00, *Bus, 0x00, 0x00, PCI_CMD);
		if(cmd & CMD_BUS_MASTER) // Yes, no need to touch this EP
		{
			return FALSE;
		}
		// Configure it as regular PCIe device
		ConfigureSlot(*Bus, PCI_MAX_DEVICE + 1, -1, pi);

		return FALSE;
	}
    // Based on Device ID assign CIO slot and max number of PHY slots to scan
    CIOSlotPresent = GetCIOSlotByDevId(*Bus, &CIOSlot, &MaxSlotNum);
    MaxPHYSlots = MaxSlotNum;// Correct if CIO slot is absent
    // Check whether EP already configured by examining CMD register
    cmd = SmiPci8  (0x00, *Bus, 0x00, 0x00, PCI_CMD);
#if !defined TBT_PCIBUS_SKIP || TBT_PCIBUS_SKIP == 0
    if(IsFirstEnterFlag) cmd &= 0;  //AMI_OVERWRITE
#endif
    if(cmd & CMD_BUS_MASTER) // Yes no need to touch this EP, just move to next one in chain
    {
        UINT8  CIOBus = *Bus + 1;
        if(!CIOSlotPresent)// CIO slot is not present in EP, just return FALSE
        {
            //PrintCPStr("BMF");
            TRACE((-1, "TbtSmm.c: CIO slot is not present in EP, just return FALSE.\n"));
            return FALSE;
        }
        // Take all resources from CIO slot and return
        pi->BusNumLimit = SmiPci8  (0x00, CIOBus, CIOSlot, 0x00, PCI_SUBUS);
        pi->IOBase      = SmiPci8  (0x00, CIOBus, CIOSlot, 0x00, PCI_IOBASE);
        pi->IOLimit     = SmiPci8  (0x00, CIOBus, CIOSlot, 0x00, PCI_IOLIMIT);
        pi->MemBase     = SmiPci16 (0x00, CIOBus, CIOSlot, 0x00, PCI_MEMBASE);
        pi->MemLimit    = SmiPci16 (0x00, CIOBus, CIOSlot, 0x00, PCI_MEMLIMIT);
        pi->PMemBase64  = SmiPci16 (0x00, CIOBus, CIOSlot, 0x00, PCI_PRE_MEMBASE) & 0xFFF0;
        pi->PMemLimit64 = SmiPci16 (0x00, CIOBus, CIOSlot, 0x00, PCI_PRE_MEMLIMIT) & 0xFFF0;
        pi->PMemBase64 |= SmiPci32 (0x00, CIOBus, CIOSlot, 0x00, PCI_PRE_MEMBASE_U) << 16;
        pi->PMemLimit64|= SmiPci32 (0x00, CIOBus, CIOSlot, 0x00, PCI_PRE_MEMLIMIT_U) << 16;
        pi->PMemLimit64|= 0xF;
        // Jump to next EP
        *Bus = SmiPci8  (0x00, CIOBus, CIOSlot, 0x00, PCI_SBUS);
        // Should we continue?
        Continue = 0xFFFF != SmiPci16 (0x00, *Bus, 0x00, 0x00, PCI_DID);
        return Continue;
    }

    //Set is legacy dvice
    isLegacyDevice = IsLegacyDevice(*Bus);

    SetCIOPortResources(*Bus, 0, // Assign all available resources to US port of EP
        *Bus + 1, pi->BusNumLimit, 0, pi);

    SBus = *Bus + 1;// Jump to DS port 

    if(CIOSlotPresent)
        MaxPHYSlots = CIOSlot;

    UsedBusNumbers = ConfigureSlot(SBus, MaxPHYSlots, Depth, pi);

    if(!CIOSlotPresent)
        return FALSE; // Stop resource assignment on this chain

    // Set rest of slots us unused
    SetSlotsAsUnused(SBus, MaxSlotNum, CIOSlot, pi);

    SetCIOPortResources(SBus, CIOSlot,
        SBus + UsedBusNumbers + 1,
        pi->BusNumLimit, &portInfo, pi);

    *Bus = SBus + UsedBusNumbers + 1;// Go to next EP

    if (*Bus > pi->BusNumLimit - 2) // In case of bus numbers are exhausted stop enumeration
        return FALSE;

    // BIOS support of Thunderbolt devices Specification Update
    // Revision 0.94
    // This OPTIONAL workaround sholud be disable by default

    // BIOS support of Thunderbolt devices Specification Update
    // Revision 0.92
    // OPTIONAL workaround for devices that don't support surprise-removal
    // If SMI Handler cannot find any device behind a CIO port it means no more TBT devices 
    // attached to this PCIe sub-tree.  In this case BIOS should set MBASE = MLIMIT.
    // Check whether we should continue on this chain
    Continue = 0xFFFF != SmiPci16 (0x00, *Bus, 0x00, 0x00, PCI_DID);
    
/*  //Thunderbolt - BIOS additions - rev.1.8
    if (gTbtSurpriseRemove)
    {
       TRACE((-1, "TbtSmm.c: Enable Thunderbolt surprise-removal workaround.\n"));
       if(!Continue) //PCI_DID = 0xFFFF
       {
           // Workaround for LR devices
           // Move resource window to the end of memory range
           UINT8 cmd = SmiPci8  (0x00, SBus, CIOSlot, 0, PCI_CMD);
           SmiPci8  (0x00, SBus, CIOSlot, 0, PCI_CMD) = CMD_BUS_MASTER;

           if(DISBL_MEM32_REG20 != SmiPci32 (0x00, SBus, CIOSlot, 0x00, PCI_MEMBASE))
               SmiPci16 (0x00, SBus, CIOSlot, 0, PCI_MEMBASE) = SmiPci16 (0x00, SBus, CIOSlot, 0, PCI_MEMLIMIT);
           if(DISBL_PMEM_REG24 != SmiPci32 (0x00, SBus, CIOSlot, 0x00, PCI_PRE_MEMBASE))
               SmiPci16 (0x00, SBus, CIOSlot, 0, PCI_PRE_MEMBASE) = SmiPci16 (0x00, SBus, CIOSlot, 0, PCI_PRE_MEMLIMIT);

           SmiPci8  (0x00, SBus, CIOSlot, 0, PCI_CMD) = cmd;
       }
    }
*/    
    return Continue;
}//ConfigureEP

VOID
GetPortResources(
    IN        UINT8 Bus,
    IN        UINT8 Dev,
    IN    OUT PortInfo* pi
)
{
    pi->BusNumLimit = SmiPci8  (0x00, Bus, Dev, 0x00, PCI_SUBUS);
    pi->IOBase      = SmiPci8  (0x00, Bus, Dev, 0x00, PCI_IOBASE) & 0xF0;
    pi->IOLimit     = SmiPci8  (0x00, Bus, Dev, 0x00, PCI_IOLIMIT) & 0xF0;
    pi->MemBase     = SmiPci16 (0x00, Bus, Dev, 0x00, PCI_MEMBASE) & 0xFFF0;
    pi->MemLimit    = SmiPci16 (0x00, Bus, Dev, 0x00, PCI_MEMLIMIT) & 0xFFF0;
    pi->PMemBase64  = SmiPci16 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE) & 0xFFF0;
    pi->PMemLimit64 = SmiPci16 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMLIMIT) & 0xFFF0;
    pi->PMemBase64 |= SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMBASE_U) << 16;
    pi->PMemLimit64|= SmiPci32 (0x00, Bus, Dev, 0x00, PCI_PRE_MEMLIMIT_U) << 16;
    pi->IOLimit |= 0xF;
    pi->MemLimit |= 0xF;
    pi->PMemLimit64 |= 0xF;
}//GetPortResources

VOID
ConfigurePort(
    IN        UINT8 Bus,
    IN        UINT8 Dev,
    IN    OUT PortInfo* pi
)
{
    INT8      i;
    UINT8     USBusNum = SmiPci8  (0x00, Bus, Dev, 0x00, PCI_SBUS);

    if (0xFFFF == SmiPci16 (0x00, USBusNum, 0x00, 0x00, PCI_DID))// Nothing to do if TBT device is not connected
        return;
    
    GetPortResources(Bus, Dev, pi);// Take reserved resources from DS port

    // Assign resources to EPs
    for (i = 0; i < MAX_TBT_DEPTH; ++i)
    {
        pi->ConfedEP++;
        if(!ConfigureEP(i, &USBusNum, pi))
            return;
    }
}//ConfigurePort

/**
    This function will update Thunderbolt variable data to 
    Thunderbolt NVS area

    @param[in] HostSeries        Thunderbolt host chip series
    @param[in] HostActiveState   Recorded Thunderbolt host state

    @retval EFI_STATUS           The function completed successfully
**/
EFI_STATUS TbtUpdateNvsData (
    IN UINT8            HostSeries,
    IN UINT8            HostActiveState )
{
    AmiTbtNvs->TbtHRSeries = HostSeries;
    AmiTbtNvs->TbtHRStatus = HostActiveState;
    
    TRACE((-1, "TbtSmm.c: Update Thunderbolt host state to NVS date, series:%x | state:%x !!!\n", AmiTbtNvs->TbtHRSeries, AmiTbtNvs->TbtHRStatus));
    
    return SMM_CHILD_DISPATCH_SUCCESS;
}

/**
    This is a TBT software SMI Handler for Porting.

    @param[in] DispatchHandle       EFI Handle
    @param[in] DispatchContext      Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
    @param[out] CommBuffer     OPTIONAL
    @param[out] CommBufferSize OPTIONAL

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization
**/
EFI_STATUS TbtSwSmiCallback (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL )
{
    PortInfo                portInfo = {0};
    HR_CONFIG               HrConfig = {0};
    UINT8                   i;
    EFI_STATUS              Status;
    EFI_GUID                SetupGuid = SETUP_GUID;
    EFI_GUID                TbtHRStatusGuid = AMI_TBT_HR_STATUS_GUID;
    CHAR16                  TbtHRStatusVar[] = TBT_HR_STATUS_VARIABLE;
    UINTN                   SetupDataSize = sizeof(SETUP_DATA);
    SETUP_DATA              SetupData;
    AMI_TBT_HR_STATUS_DATA  TbtHRStatusData;
    
    TRACE((-1, "TbtSmm.c: Thunderbolt SWSMI Callback Function Entry !!!\n"));
    TRACE((-1, "TbtSmm.c: PCIE BASE ADDRESS:%x\n", PciExpressBaseAddress));
    Status = pRS->GetVariable(L"Setup", &SetupGuid, NULL, &SetupDataSize, &SetupData);
    if (!EFI_ERROR(Status)){
        SmiStall((UINTN)(SetupData.TbtSwSMIDelay * 1000));
    }
    
    // Workaround for synchronizing cache line size of Thunderbolt
    if (gCacheLineSize != SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, R_PCH_PCIE_CLS))
        SmiPci8AndThenOr( 0x00, gTbtBus, gTbtDev, gTbtFun, R_PCH_PCIE_CLS, 0x00, gCacheLineSize);
    
    SMI_PROGRESS_CODE (SMM_THUNDERBOLT_CALL);
    
    PortInfoInit(&portInfo);

    if (!InitializeHostRouter(&HrConfig)){
        SMI_PROGRESS_CODE (0xCB); //Cable is unplugged
        
        // BIOS support of Thunderbolt devices Specification Update
        // Revision 0.90
        // BIOS should remember whether HR is active(it is active 
        // when cable is connected)
        
        // HR status is setted inactive
        TbtHRStatusData.TbtHRStatus = 0;
        if ((HostDeviceId == 0x1547) || (HostDeviceId == 0x1548)) {
            TbtHRStatusData.TbtHRSeries = Cactus_Ridge;
        } else if ((HostDeviceId == 0x1567) || (HostDeviceId == 0x1569)) {
            TbtHRStatusData.TbtHRSeries = Redwood_Ridge;
        } else if ((HostDeviceId == 0x156B) || (HostDeviceId == 0x156D)){
            TbtHRStatusData.TbtHRSeries = Falcon_Ridge;
        } else {
            TbtHRStatusData.TbtHRSeries = BDW_TBT_LP;
        }
        
        Status = pRS->SetVariable( TbtHRStatusVar, \
                                   &gAmiTbtHrStatusGuid, \
                                   AmiTbtHrStatusAttribute, \
                                   sizeof(AMI_TBT_HR_STATUS_DATA), \
                                   &TbtHRStatusData );
        
#if !defined TBT_PCIBUS_SKIP || TBT_PCIBUS_SKIP == 0
        if(IsFirstEnterFlag) IsFirstEnterFlag = 0;
#endif
        TRACE((-1, "TbtSmm.c: Thunderbolt SWSMI Callback Function Exit !!!\n"));
        
        return SMM_CHILD_DISPATCH_SUCCESS;
    }
    
    // Configure DS ports
	for(i = HrConfig.MinDSNumber; i <= HrConfig.MaxDSNumber; ++i)
    {
		ConfigurePort(HrConfig.HRBus + 1, i, &portInfo);
    }
    SMI_PROGRESS_CODE (SMM_THUNDERBOLT_CALL + 2 + portInfo.ConfedEP); //PostCode = 0xAC + # of connected EP
    
    // BIOS support of Thunderbolt devices Specification Update
    // Revision 0.90
    // BIOS should remember whether HR is active(it is active 
    // when cable is connected)
    // HR status is setted active
    HostDeviceId  = SmiPci16 (0x00, HrConfig.HRBus, 0x00, 0x00, PCI_DID);
    TRACE((-1, "TbtSmm.c: Get Thunderbolt Host Device ID %x in SWSMI from Bus:%x \n", HostDeviceId, HrConfig.HRBus));
    if ((HostDeviceId == 0x1547) || (HostDeviceId == 0x1548))
        TbtHRStatusData.TbtHRSeries = Cactus_Ridge;
    if ((HostDeviceId == 0x1567) || (HostDeviceId == 0x1569))
        TbtHRStatusData.TbtHRSeries = Redwood_Ridge;
    if ((HostDeviceId == 0x156B) || (HostDeviceId == 0x156D))
        TbtHRStatusData.TbtHRSeries = Falcon_Ridge;
    if (HostDeviceId == 0x157E)
        TbtHRStatusData.TbtHRSeries = BDW_TBT_LP;
               
    TbtHRStatusData.TbtHRStatus = 1;
    Status = pRS->SetVariable( TbtHRStatusVar, \
                               &gAmiTbtHrStatusGuid, \
                               AmiTbtHrStatusAttribute, \
                               sizeof(AMI_TBT_HR_STATUS_DATA), \
                               &TbtHRStatusData );
    
#if !defined TBT_PCIBUS_SKIP || TBT_PCIBUS_SKIP == 0
    if(IsFirstEnterFlag) IsFirstEnterFlag = 0;
#endif
    TRACE((-1, "TbtSmm.c: Thunderbolt SWSMI Callback Function Exit !!!\n"));
    return SMM_CHILD_DISPATCH_SUCCESS;
}

/**
    The following flow should be performed as a last step before
    instructing the platform to enter Sx state:
    BIOS should assert GO2Sx pin
    That will trigger Host Router to prepare underlying devices
    BIOS should poll OK2GO2SX_N_OD pin
    Upon completion of all preparations, Host Router will assert
    this pin to indicate readiness for Sx entry
    At this stage BIOS should continue with legacy Sx entry steps

    @param[in] DispatchHandle       EFI Handle
    @param[in] DispatchContext      Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
    @param[out] CommBuffer     OPTIONAL
    @param[out] CommBufferSize OPTIONAL

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization

    @note  This function does not need to put the system to sleep.  This is
              handled by PutToSleep.
**/
EFI_STATUS TbtPowerButtonCallback (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL )
{
    EFI_STATUS     Status;
    UINT8          UpPortBus;
    UINT8          RegVal8;
    UINT16         PresenceFlag = 0;
    UINT8          SlotStatusCapOffset;
    UINT8          PowerManagerCapOffset;
    UINT32         Attributes;
    UINTN          TbtHRStatusDataSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    CHAR16         TbtHRStatusVar[]    = TBT_HR_STATUS_VARIABLE;
    AMI_TBT_HR_STATUS_DATA  TbtHRStatusData;
    
    Status = pRS->GetVariable( L"TbtHRStatusVar", \
                               &gAmiTbtHrStatusGuid, \
                               &Attributes, \
                               &TbtHRStatusDataSize, \
                               &TbtHRStatusData );
    if (!EFI_ERROR(Status)){
#if defined TBT_HR_SX_CHECK && TBT_HR_SX_CHECK == 1
        // Double check Thunderbolt host status
        SlotStatusCapOffset = PcieFindCapId(gTbtBus, gTbtDev, gTbtFun, PCI_CAP_ID_PCIEXP);
        PresenceFlag = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (SlotStatusCapOffset + 0x1A));
        
        TRACE((-1, "Thunderbolt Presence bit on PCIE root port%x :%x(Bit06)\n", gTbtFun, PresenceFlag));
        if (TbtHRStatusData.TbtHRStatus){
            if ((PresenceFlag & B_PCH_PCIE_SLSTS_PDS) == 0){
                // Host route status record is active but no device connect actually
                TbtHRStatusData.TbtHRStatus = 0;
                //TbtHRStatusData.TbtHRSeries = HostDeviceId;
                Status = pRS->SetVariable( TbtHRStatusVar, \
                                           &gAmiTbtHrStatusGuid, \
                                           Attributes, \
                                           sizeof(AMI_TBT_HR_STATUS_DATA), \
                                           &TbtHRStatusData );
                TRACE((-1, "Host route status record is active but no device connect actually !!!\nReset Thunderbolt Host state %r\n", Status));
            }
        } else {
            if ((PresenceFlag & B_PCH_PCIE_SLSTS_PDS) != 0){
                // Host route status record is inactive but device connect actually
                TbtHRStatusData.TbtHRStatus = 1;
                //TbtHRStatusData.TbtHRSeries = HostDeviceId;
                Status = pRS->SetVariable( TbtHRStatusVar, \
                                           &gAmiTbtHrStatusGuid, \
                                           Attributes, \
                                           sizeof(AMI_TBT_HR_STATUS_DATA), \
                                           &TbtHRStatusData );
                TRACE((-1, "Host route status record is inactive but device connect actually !!!\nReset Thunderbolt Host state %r\n", Status));
            }
        } //TbtHRStatus
#endif
        
        // Update Host route status to Thunderbolt NVS
        TbtUpdateNvsData(TbtHRStatusData.TbtHRSeries, TbtHRStatusData.TbtHRStatus);
    } // !EFI_ERROR(Status)

    if (!gTbtWakeupSupport){
        // System does not support wake from Thunderbolt device
        if ((HostDeviceId == 0x1547) || (HostDeviceId == 0x1548)){
            // Sleep entry flow for Cactus Ridge chip
#if defined TBT_HR_PWR && (TBT_HR_PWR != 0xFF)
            if (gTbtHandlePOC){
                Status = PowerOffPOC();
                TRACE((-1, "TbtSmm.c: Cut off Thunderbolt POC power %r !!!\n", Status));
                ASSERT_EFI_ERROR(Status);
            }
            else
#endif
                return SMM_CHILD_DISPATCH_UNSUPPORTED;
        } else {
            // Sleep entry flow for Redwood Ridge / Falcon Ridge / BDW-TBT-LP chip 
            // when system doesn't support thunderbolt wake function
            
            // put PCIE root port power state back to D0
            PowerManagerCapOffset = PcieFindCapId(gTbtBus, gTbtDev, gTbtFun, PCI_CAP_ID_PMI);
            RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
            RegVal8 &= ~B_PCH_PCIE_PMCS_PS;
            SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
            
            // BIOS support of Thunderbolt devices Specification Update Revision 1.4
            // 2.3.2.2 Sx Entry flow for RR Hosts without Thunderbolt wake support
            UpPortBus = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, PCI_SBUS);
            if (!TbtSetPCIe2TBTCommand(UpPortBus, 0, TBT_GO2SX_NO_WAKE, 0x8FFFF)){
                // restore PCIE root port power state back to D3
                RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
                RegVal8 |= B_PCH_PCIE_PMCS_PS;
                SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
                
                return SMM_CHILD_DISPATCH_NO_MEDIA;
            }
            
            // restore PCIE root port power state back to D3
            RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
            RegVal8 |= B_PCH_PCIE_PMCS_PS;
            SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
        }
    } else {
        // System support wake from Thunderbolt device
        if ((HostDeviceId == 0x1547) || (HostDeviceId == 0x1548)){
            // BIOS support of Thunderbolt devices Specification Update
            // Revision 0.85
            // 5. System power state (Sx) handing
            // For Cactus Ridge (CR) Host Router component, those GPIO's 
            // should be connected to the following pins:
            // 1. GPIO_2__GO2SX - active high
            // 2. GPIO_9__OK2GO2SX_N_OD - active low
            Status = ActiveTbtGpio2();
            ASSERT_EFI_ERROR(Status);
            
            Status = PollTbtGpio9();
            ASSERT_EFI_ERROR(Status);
        } else {
            // Sleep entry flow for Redwood Ridge / Falcon Ridge / BDW-TBT-LP chip 
            // when system support thunderbolt wake function
            //
            // Thunderbolt BIOS Implementation guide for Redwood Ridge/Falcon Ridge/BDW-TBT-LP based 
            // devices Specification Update Revision 1.0
            // 2.2.2.3 Sx Entry Flow for Host with Add-In Card support
            
#if !defined TBT_HR_SX_CHECK || TBT_HR_SX_CHECK == 0
            SlotStatusCapOffset = PcieFindCapId(gTbtBus, gTbtDev, gTbtFun, PCI_CAP_ID_PCIEXP);
            PresenceFlag = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (SlotStatusCapOffset + 0x1A));
#endif      
            if (gTbtAICSupport){
                if((PresenceFlag & B_PCH_PCIE_SLSTS_PDS) != 0){
                    // put PCIE root port power state back to D0
                    PowerManagerCapOffset = PcieFindCapId(gTbtBus, gTbtDev, gTbtFun, PCI_CAP_ID_PMI);
                    RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
                    RegVal8 &= ~B_PCH_PCIE_PMCS_PS;
                    SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
                    
                    // Get Thunderbolt host location
                    UpPortBus = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, PCI_SBUS);
                    if (!TbtSetPCIe2TBTCommand(UpPortBus, 0, TBT_GO2SX_WITH_WAKE, 0x8FFFF)){
                        // restore PCIE root port power state back to D3
                        RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
                        RegVal8 |= B_PCH_PCIE_PMCS_PS;
                        SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
                        
                        return SMM_CHILD_DISPATCH_TIMEOUT;
                    }
                    
                    // restore PCIE root port power state back to D3
                    RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
                    RegVal8 |= B_PCH_PCIE_PMCS_PS;
                    SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
                }
            }// end of AIC support
            
            //
            // BIOS support of Thunderbolt devices Specification Update Revision 1.4
            // 2.3.2.1 Sx Entry flow for RR/FR/WR Hosts with Thunderbolt wake support
            
            //UpPortBus = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, PCI_SBUS);
            //if (!TbtSetPCIe2TBTCommand(UpPortBus, 0, TBT_GO2SX_WITH_WAKE, 0x8FFFF))
            //   return SMM_CHILD_DISPATCH_NO_MEDIA;
        }
    }
    TRACE((-1, "TbtSmm: TbtPowerButtonCallback() !!!\n"));
    return SMM_CHILD_DISPATCH_SUCCESS;
}

/**
    The following flow should be performed as a last step before
    instructing the platform to enter Sx state:
    BIOS should assert GO2Sx pin
    That will trigger Host Router to prepare underlying devices
    BIOS should poll OK2GO2SX_N_OD pin
    Upon completion of all preparations, Host Router will assert
    this pin to indicate readiness for Sx entry
    At this stage BIOS should continue with legacy Sx entry steps

    @param[in] DispatchHandle       EFI Handle
    @param[in] DispatchContext      Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
    @param[out] CommBuffer     OPTIONAL
    @param[out] CommBufferSize OPTIONAL

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization

    @note  This function does not need to put the system to sleep.  This is
              handled by PutToSleep.
**/
EFI_STATUS TbtGo2SxCallback (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL )
{
    EFI_STATUS     Status;
    UINT8          UpPortBus;
    UINT8          RegVal8;
    UINT16         PresenceFlag = 0;
    UINT8          SlotStatusCapOffset;
    UINT8          PowerManagerCapOffset;
    UINT32         Attributes;
    UINTN          TbtHRStatusDataSize = sizeof(AMI_TBT_HR_STATUS_DATA);
    CHAR16         TbtHRStatusVar[]    = TBT_HR_STATUS_VARIABLE;
    AMI_TBT_HR_STATUS_DATA  TbtHRStatusData;
    
    Status = pRS->GetVariable( L"TbtHRStatusVar", \
                               &gAmiTbtHrStatusGuid, \
                               &Attributes, \
                               &TbtHRStatusDataSize, \
                               &TbtHRStatusData );
    if (!EFI_ERROR(Status)){
#if defined TBT_HR_SX_CHECK && TBT_HR_SX_CHECK == 1
        // Double check Thunderbolt host status
        SlotStatusCapOffset = PcieFindCapId(gTbtBus, gTbtDev, gTbtFun, PCI_CAP_ID_PCIEXP);
        PresenceFlag = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (SlotStatusCapOffset + 0x1A));
        
        TRACE((-1, "Thunderbolt Presence bit on PCIE root port%x :%x(Bit06)\n", gTbtFun, PresenceFlag));
        if (TbtHRStatusData.TbtHRStatus){
            if ((PresenceFlag & B_PCH_PCIE_SLSTS_PDS) == 0){
                // Host route status record is active but no device connect actually
                TbtHRStatusData.TbtHRStatus = 0;
                //TbtHRStatusData.TbtHRSeries = HostDeviceId;
                Status = pRS->SetVariable( TbtHRStatusVar, \
                                           &gAmiTbtHrStatusGuid, \
                                           Attributes, \
                                           sizeof(AMI_TBT_HR_STATUS_DATA), \
                                           &TbtHRStatusData );
                TRACE((-1, "Host route status record is active but no device connect actually !!!\nReset Thunderbolt Host state %r\n", Status));
            }
        } else {
            if ((PresenceFlag & B_PCH_PCIE_SLSTS_PDS) != 0){
                // Host route status record is inactive but device connect actually
                TbtHRStatusData.TbtHRStatus = 1;
                //TbtHRStatusData.TbtHRSeries = HostDeviceId;
                Status = pRS->SetVariable( TbtHRStatusVar, \
                                           &gAmiTbtHrStatusGuid, \
                                           Attributes, \
                                           sizeof(AMI_TBT_HR_STATUS_DATA), \
                                           &TbtHRStatusData );
                TRACE((-1, "Host route status record is inactive but device connect actually !!!\nReset Thunderbolt Host state %r\n", Status));
            }
        } //TbtHRStatus
#endif
        
        // Update Host route status to Thunderbolt NVS
        TbtUpdateNvsData(TbtHRStatusData.TbtHRSeries, TbtHRStatusData.TbtHRStatus);
    } // !EFI_ERROR(Status)

    if (!gTbtWakeupSupport){
        // System does not support wake from Thunderbolt device
        if ((HostDeviceId == 0x1547) || (HostDeviceId == 0x1548)){
            // Sleep entry flow for Cactus Ridge chip
#if defined TBT_HR_PWR && (TBT_HR_PWR != 0xFF)
            if (gTbtHandlePOC){
                Status = PowerOffPOC();
                TRACE((-1, "TbtSmm.c: Cut off Thunderbolt POC power %r !!!\n", Status));
                ASSERT_EFI_ERROR(Status);
            }
            else
#endif
                return SMM_CHILD_DISPATCH_UNSUPPORTED;
        } else {
            // Sleep entry flow for Redwood Ridge / Falcon Ridge / BDW-TBT-LP chip 
            // when system doesn't support thunderbolt wake function
            
            // put PCIE root port power state back to D0
            PowerManagerCapOffset = PcieFindCapId(gTbtBus, gTbtDev, gTbtFun, PCI_CAP_ID_PMI);
            RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
            RegVal8 &= ~B_PCH_PCIE_PMCS_PS;
            SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
            
            // BIOS support of Thunderbolt devices Specification Update Revision 1.4
            // 2.3.2.2 Sx Entry flow for RR Hosts without Thunderbolt wake support
            UpPortBus = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, PCI_SBUS);
            if (!TbtSetPCIe2TBTCommand(UpPortBus, 0, TBT_GO2SX_NO_WAKE, 0x8FFFF)){
                // restore PCIE root port power state back to D3
                RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
                RegVal8 |= B_PCH_PCIE_PMCS_PS;
                SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
                
                return SMM_CHILD_DISPATCH_NO_MEDIA;
            }
            
            // restore PCIE root port power state back to D3
            RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
            RegVal8 |= B_PCH_PCIE_PMCS_PS;
            SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
        }
    } else {
        // System support wake from Thunderbolt device
        if ((HostDeviceId == 0x1547) || (HostDeviceId == 0x1548)){
            // BIOS support of Thunderbolt devices Specification Update
            // Revision 0.85
            // 5. System power state (Sx) handing
            // For Cactus Ridge (CR) Host Router component, those GPIO's 
            // should be connected to the following pins:
            // 1. GPIO_2__GO2SX - active high
            // 2. GPIO_9__OK2GO2SX_N_OD - active low
            Status = ActiveTbtGpio2();
            ASSERT_EFI_ERROR(Status);
            
            Status = PollTbtGpio9();
            ASSERT_EFI_ERROR(Status);
        } else {
            // Sleep entry flow for Redwood Ridge / Falcon Ridge / BDW-TBT-LP chip 
            // when system support thunderbolt wake function
            //
            // Thunderbolt BIOS Implementation guide for Redwood Ridge/Falcon Ridge/BDW-TBT-LP based 
            // devices Specification Update Revision 1.0
            // 2.2.2.3 Sx Entry Flow for Host with Add-In Card support
            
#if !defined TBT_HR_SX_CHECK || TBT_HR_SX_CHECK == 0
            SlotStatusCapOffset = PcieFindCapId(gTbtBus, gTbtDev, gTbtFun, PCI_CAP_ID_PCIEXP);
            PresenceFlag = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (SlotStatusCapOffset + 0x1A));
#endif      
            if (gTbtAICSupport){
                if((PresenceFlag & B_PCH_PCIE_SLSTS_PDS) != 0){
                    // put PCIE root port power state back to D0
                    PowerManagerCapOffset = PcieFindCapId(gTbtBus, gTbtDev, gTbtFun, PCI_CAP_ID_PMI);
                    RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
                    RegVal8 &= ~B_PCH_PCIE_PMCS_PS;
                    SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
                    
                    // Get Thunderbolt host location
                    UpPortBus = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, PCI_SBUS);
                    if (!TbtSetPCIe2TBTCommand(UpPortBus, 0, TBT_GO2SX_WITH_WAKE, 0x8FFFF)){
                        // restore PCIE root port power state back to D3
                        RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
                        RegVal8 |= B_PCH_PCIE_PMCS_PS;
                        SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
                        
                        return SMM_CHILD_DISPATCH_TIMEOUT;
                    }
                    
                    // restore PCIE root port power state back to D3
                    RegVal8 = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04));
                    RegVal8 |= B_PCH_PCIE_PMCS_PS;
                    SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, (PowerManagerCapOffset + 0x04)) = RegVal8;
                }
            }// end of AIC support
            
            //
            // BIOS support of Thunderbolt devices Specification Update Revision 1.4
            // 2.3.2.1 Sx Entry flow for RR/FR/WR Hosts with Thunderbolt wake support
            
            //UpPortBus = SmiPci8(0x00, gTbtBus, gTbtDev, gTbtFun, PCI_SBUS);
            //if (!TbtSetPCIe2TBTCommand(UpPortBus, 0, TBT_GO2SX_WITH_WAKE, 0x8FFFF))
            //   return SMM_CHILD_DISPATCH_NO_MEDIA;
        }
    }
    
    return SMM_CHILD_DISPATCH_SUCCESS;
}

/**
    Installs TBT SMM Child Dispatcher Handler.

    @param[in] ImageHandle          Image handle
    @param[in] *SystemTable         Pointer to the system table

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization
**/

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS                             Status;
    EFI_HANDLE                             SwHandle = NULL;
    EFI_HANDLE                             hS3Smi   = NULL;
    EFI_HANDLE                             hS4Smi   = NULL;
    EFI_HANDLE                             hS5Smi   = NULL;
    EFI_HANDLE                             hPBSmi   = NULL;
    AMI_SMM_SW_DISPATCH_PROTOCOL           *SwDispatch;
    AMI_SMM_SX_DISPATCH_PROTOCOL           *SxDispatch;
    AMI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL *PowerButton;
    AMI_SMM_SW_DISPATCH_CONTEXT            SwContext;
    AMI_SMM_SX_DISPATCH_CONTEXT            S3DispatchContext  = {SxS3, SxEntry};
    AMI_SMM_SX_DISPATCH_CONTEXT            S4DispatchContext  = {SxS4, SxEntry};
    AMI_SMM_SX_DISPATCH_CONTEXT            S5DispatchContext  = {SxS5, SxEntry};
    AMI_SMM_POWER_BUTTON_DISPATCH_CONTEXT  PwrContext         = {EfiPowerButtonEntry};    

    TbtHotplugPinSciRouting();
    // Presence Detect Changed Enable
    //SmiPci8Or( 0x00, gTbtBus, gTbtDev, gTbtFun, R_PCH_PCIE_SLCTL, 0x08);
    
    Status = pSmst->SmmLocateProtocol( &gEfiSmmSwDispatch2ProtocolGuid, \
                                       NULL, \
                                       &SwDispatch );
    if (EFI_ERROR(Status)) return Status;

    Status = pSmst->SmmLocateProtocol( &gEfiSmmSxDispatch2ProtocolGuid , \
                                       NULL, \
                                       &SxDispatch );
    if (EFI_ERROR(Status)) return Status;

    Status = pSmst->SmmLocateProtocol( &gEfiSmmPowerButtonDispatch2ProtocolGuid, \
                                       NULL, \
                                       &PowerButton );
    if (EFI_ERROR(Status)) return Status;
    
    SwContext.SwSmiInputValue = TBT_SWSMI_VALUE;
    Status = SwDispatch->Register (
                              SwDispatch,
                              TbtSwSmiCallback,
                              &SwContext,
                              &SwHandle );
    if (EFI_ERROR(Status)) return Status;

    if (gTbtEnable == FALSE){
        TRACE((-1, "TbtSmm.c: Thunderbolt function is disable in Setup.\n"));
        TRACE((-1, "TbtSmm.c: Only register Tbt SwSMI for debug.\n"));
        return EFI_SUCCESS;
    }
    
    Status = SxDispatch->Register(
                              SxDispatch, \
                              TbtGo2SxCallback, \
                              &S3DispatchContext, \
                              &hS3Smi );
    if (EFI_ERROR(Status)) return Status;

    Status = SxDispatch->Register(
                              SxDispatch, \
                              TbtGo2SxCallback, \
                              &S4DispatchContext, \
                              &hS4Smi );
    if (EFI_ERROR(Status)) return Status;

    Status = SxDispatch->Register(
                              SxDispatch, \
                              TbtGo2SxCallback, \
                              &S5DispatchContext, \
                              &hS5Smi );
    if (EFI_ERROR(Status)) return Status;

    Status = PowerButton->Register( 
                               PowerButton,
                               TbtPowerButtonCallback,
                               &PwrContext,
                               &hPBSmi );
    if (EFI_ERROR(Status)) return Status;
    
    return EFI_SUCCESS;
}

/**
    Installs TBT SMM Child Dispatcher Handler.

    @param[in] ImageHandle          Image handle
    @param[in] *SystemTable         Pointer to the system table

    @retval EFI_SUCCESS             The function completed successfully
    @retval EFI_ERROR               Error occured on initialization
**/
EFI_STATUS TbtSmmInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    AMI_TBT_PLATFORM_POLICY_PROTOCOL   *AmiTbtPlatformPolicy = NULL;
    AMI_TBT_NVS_PROTOCOL               *AmiTbtNvsProtocol    = NULL;
    AMI_TBT_HR_STATUS_DATA             HRStatusData;
    UINTN                              HRStatusSize          = sizeof(AMI_TBT_HR_STATUS_DATA);
    CHAR16                             TbtHRStatusVar[]      = TBT_HR_STATUS_VARIABLE;
    EFI_STATUS                         Status                = EFI_SUCCESS;

	InitAmiLib(ImageHandle,SystemTable);
	TRACE((-1, "TbtSmm: TbtSmmInit() !!!\n"));
	
	//Update Pcie base address first
	PciExpressBaseAddress = PcdGet64 (PcdPciExpressBaseAddress);
	
	Status = pBS->LocateProtocol( &gAmiTbtPlatformPolicyProtocolGuid, \
	                              NULL, \
	                              &AmiTbtPlatformPolicy );
	if(!EFI_ERROR(Status)){
	    gCacheLineSize           = AmiTbtPlatformPolicy->CacheLineSize;
	    gTbtBus                  = AmiTbtPlatformPolicy->Bus;
	    gTbtDev                  = AmiTbtPlatformPolicy->Dev;
	    gTbtFun                  = AmiTbtPlatformPolicy->Fun;
	    gTbtHotPlugEvent         = AmiTbtPlatformPolicy->TbtHotPlugEvt;
	    gReserveMemoryPerSlot    = AmiTbtPlatformPolicy->ReserveMemoryPerSlot;
	    gReservePMemoryPerSlot   = AmiTbtPlatformPolicy->ReservePMemoryPerSlot;
	    gReserveIOPerSlot        = AmiTbtPlatformPolicy->ReserveIOPerSlot;
	    if (AmiTbtPlatformPolicy->TbtWakeupSupport)
	        gTbtWakeupSupport    = TRUE;
	    if (AmiTbtPlatformPolicy->TbtAICSupport)
	        gTbtAICSupport       = TRUE;
	    if (AmiTbtPlatformPolicy->TbtHandlePOC)
	        gTbtHandlePOC        = TRUE;
	    if (AmiTbtPlatformPolicy->TbtIOresourceEnable)
	        gTbtIOresourceEnable = TRUE;	    
	    if (AmiTbtPlatformPolicy->TbtEnable)
	        gTbtEnable           = TRUE;
	    TRACE((-1, "TbtSmm.c: Thunderbolt Host PCIE root port Location @B:%x|D:%x|F:%x from Thunderbolt policy\n", gTbtBus, gTbtDev, gTbtFun));
	    
	    // Convert slot resource to register format
	    gReserveMemoryPerSlot  <<= 4;
	    gReservePMemoryPerSlot <<= 4;
	    gReserveIOPerSlot      <<= 2;
	    TRACE((-1, "TbtSmm.c: gReserveMemoryPerSlot  = %x\n", gReserveMemoryPerSlot));
	    TRACE((-1, "TbtSmm.c: gReservePMemoryPerSlot = %x\n", gReservePMemoryPerSlot));
	    TRACE((-1, "TbtSmm.c: gReserveIOPerSlot      = %x\n", gReserveIOPerSlot));
	    
	    // Init Tbt Host Information in SMM RAM
	    Status = pRS->GetVariable( L"TbtHRStatusVar", \
	                               &gAmiTbtHrStatusGuid, \
	                               &AmiTbtHrStatusAttribute, \
	                               &HRStatusSize, \
	                               &HRStatusData );
	    if (!EFI_ERROR(Status)){
	        if (HRStatusData.TbtHRSeries == Cactus_Ridge) HostDeviceId = 0x1548;
	        else if (HRStatusData.TbtHRSeries == Redwood_Ridge) HostDeviceId = 0x1567;
	        else if (HRStatusData.TbtHRSeries == Falcon_Ridge) HostDeviceId = 0x156B;
	        else HostDeviceId = 0x157E;
	    } else {
	        AmiTbtHrStatusAttribute = (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS);
	        if (DEFAULT_TBT_CHIP == Cactus_Ridge) HostDeviceId = 0x1548;
	        else if (DEFAULT_TBT_CHIP == Redwood_Ridge) HostDeviceId = 0x1567;
	        else if (DEFAULT_TBT_CHIP == Falcon_Ridge) HostDeviceId = 0x156B;
	        else HostDeviceId = 0x157E;
	    }
	    
	    // Locate Thunderbolt NVS data
	    Status = pBS->LocateProtocol( &gAmiTbtNvsProtocolGuid, \
	                                  NULL, \
	                                  &AmiTbtNvsProtocol );
	    if(!EFI_ERROR(Status)){
	        AmiTbtNvs = AmiTbtNvsProtocol->TbtNvsArea;
	        TRACE((-1, "TbtSmm.c: AmiTbtNvs address = 0x%x\n", (UINT32)(UINTN)AmiTbtNvs));
	    }
	}
	      
	return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
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
