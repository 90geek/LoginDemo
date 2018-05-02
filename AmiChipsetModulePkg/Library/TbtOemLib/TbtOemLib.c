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
#include <AmiCspLib.h>
#include <Library/IoLib.h>
#include <Library/AmiChipsetIoLib.h>
#include <Library/TbtOemLib.h>
#include <Guid/AmiTbtHrStatus.h>
#include <Pci.h>

// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
VOID SetSioLdn( IN UINT8 Ldn)
{
  IoWrite8(0x2e, Ldn);
  IoWrite8(0x2f, Ldn);
}

UINT8 ReadSio( IN UINT8 Index )
{
  IoWrite8(0x2e, Index);
  return IoRead8(0x2f);
}

VOID WriteSio( IN UINT8 Index, IN UINT8 Value )
{
  IoWrite8(0x2e, Index);
  IoWrite8(0x2f, Value);
}

VOID SetSio( IN UINT8 Index, IN UINT8 Set )
{
  UINT8 Data8;

  IoWrite8(0x2e, Index);
  Data8 = IoRead8(0x2f);
  Data8 |= Set;
  IoWrite8(0x2f, Data8);
}

VOID ResetSio( IN UINT8 Index, IN UINT8 Rst )
{
  UINT8 Data8;

  IoWrite8(0x2e, Index);
  Data8 = IoRead8(0x2f);
  Data8 &= ~Rst;
  IoWrite8(0x2f, Data8);
}

VOID OpenSioConfig ( VOID ) 
{
  IoWrite8(0x2e, 0x87);
  IoWrite8(0x2e, 0x01);
  IoWrite8(0x2e, 0x55);
  IoWrite8(0x2e, 0x55);
}
#endif
//*/

/**
    This snipped code contains PCIE2TBT <-> TBT2PCIE handshake 
    procedure and all related methods called directly or underectly 
    by TbtSetPCIe2TBTCommand.
    This function is Intel Sample code(Rev. 1.5).

    @param[in] UpPortBus        Thunderbolt host upstream bridge bus number
    @param[in] Data             Thunderbolt FW setting data
    @param[in] Command          Thunderbolt FW setting command
    @param[in] Timeout          Timeout value

    @retval TRUE                Set Thunderbolt FW success
    @retval FALSE               Set Thunderbolt FW fail
**/
BOOLEAN TbtSetPCIe2TBTCommand(
  IN UINT8             UpPortBus,
  IN UINT8             Data,
  IN UINT8             Command,
  IN UINTN             Timeout
)
{
    UINT32 REG_VAL = 0;
    UINTN  Counter = Timeout;

    REG_VAL = (Data << 8) | (Command << 1) | PCIE2TBT_VLD_B;

    MMIO_WRITE32(TBT_CFG_ADDRESS(UpPortBus, 0, 0, RR_PCIE2TBT), REG_VAL);

    while(Counter-- > 0){
        // BIOS support of Thunderbolt devices Specification Update Revision 0.9
        REG_VAL = MMIO_READ32(TBT_CFG_ADDRESS(UpPortBus, 0, 0, RR_TBT2PCIE));
        if (0xFFFFFFFF == REG_VAL){
            // Device is not here return now
            return FALSE;
        }
        if (REG_VAL & TBT2PCIE_DON_R){
            // Check TBT2PCIE.Done
            break;
        }
    }
    MMIO_WRITE32(TBT_CFG_ADDRESS(UpPortBus, 0, 0, RR_PCIE2TBT), 0);

    return TRUE;
}

/**
    this function will be executed before Thunderbolt Sx exit flow
    OEM can put anything they want to do

    @param[in] *Services        PeiService table point
    @param[in] TbtHostSeries    Recorded Thunderbolt host chip series

    @retval VOID
**/
VOID TbtBeforeSxExitFlow(
    IN VOID              *Services,
    IN UINT8             TbtHostSeries )
{
// Sample code for CRB
/*
    EFI_PEI_SERVICES    **PeiServices;
    UINT16      GPIOInv;
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8       Data8;
#else
    //UINT32      Data32;
#endif

    PeiServices = (EFI_PEI_SERVICES **)Services;

    if (TbtHostSeries == Cactus_Ridge){
        // only for SharkBay CRB
        GPIOInv = (IoRead16(GPIO_BASE_ADDRESS + GP_IOREG_GPI_INV) & 0xF7FF);
        IoWrite16(GPIO_BASE_ADDRESS + GP_IOREG_GPI_INV, GPIOInv);
    }

#if !defined BWT1_BOARD || BWT1_BOARD != 2
    OpenSioConfig();
    SetSioLdn (0x07);
    
    //program Super IO Base Address
    WriteSio(0x62, (UINT8)(IT8728F_GPIO_BASE_ADDRESS >> 8));
    WriteSio(0x63, (UINT8)(IT8728F_GPIO_BASE_ADDRESS & 0xFF));
    
    //program GP20, GP21, GP22 as GPIO pin
    Data8 = ReadSio (0x26);
    Data8 |= 0x07;
    WriteSio (0x26, Data8);
    

    if (TbtHostSeries == Cactus_Ridge){
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
        //program GP40 as GPIO pin
        Data8 = ReadSio (0x28);
        Data8 |= 0x01;
        WriteSio (0x28, Data8);
#endif  
        
        //program GP66, GP67 as GPIO pin
        Data8 = ReadSio (0x29);
        Data8 |= BIT07;
        WriteSio (0x29, Data8);
    } // Cactus Ridge
    
    //program GP20, GP21, GP22 GPIO polarity
    Data8 = ReadSio (0xB1);
    Data8 &= 0xF8;
    WriteSio (0xB1, Data8);
    
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
    if (TbtHostSeries == Cactus_Ridge){
        //program GP40 GPIO polarity
        Data8 = ReadSio (0xB3);
        Data8 &= 0xFE;
        WriteSio (0xB3, Data8);
    }
#endif
    
    //GP20, GP21, GP22 internal pull-up enable
    Data8 = ReadSio (0xB9);
    Data8 |= 0x03;
    WriteSio (0xB9, Data8);
    

    if (TbtHostSeries == Cactus_Ridge){
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
        //GP40 internal internal pull-up enable
        Data8 = ReadSio (0xBB);
        Data8 |= 0x01;
        WriteSio (0xBB, Data8);
#endif
        
        //GP66, GP67 internal pull-up enable
        Data8 = ReadSio (0xBD);
        Data8 |= 0xC0;
        WriteSio (0xBD, Data8);
    }
    
    //GP20, GP21, GP22 Simple I/O enable
    Data8 = ReadSio (0xC1);
    Data8 |= 0x07;
    WriteSio (0xC1, Data8);
    
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
    if (TbtHostSeries == Cactus_Ridge){
        //GP40 Simple I/O enable
        Data8 = ReadSio (0xC3);
        Data8 |= 0x01;
        WriteSio (0xC3, Data8);
    }
#endif
    
    //GP20, GP21, GP22 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xC9);
    Data8 |= 0x03;
    WriteSio (0xC9, Data8);
    
    if (TbtHostSeries == Cactus_Ridge){
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
        //GP40 Input/Output Configure
        //1:Output Mode 0:Input Mode
        Data8 = ReadSio (0xCB);
        Data8 |= 0x01;
        WriteSio (0xCB, Data8);
#endif
        
        //GP66, GP67 Input/Output Configure
        //1:Output Mode 0:Input Mode
        Data8 = ReadSio (0xCD);
        Data8 |= 0xC0;
        WriteSio (0xCD, Data8);
    }
    
    if (TbtHostSeries != Cactus_Ridge){
        //Pull high GPIO_9
        IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, 0x04);
    } // RR, FR and WR
#else
    // program ownship
    //Data32 = IoRead32(GPIO_BASE_ADDRESS + (TBT_HotPlugEvt/32)*4);
    //Data32 |= (BIT00 << (TBT_ForcePWR%32));
    //IoWrite32((GPIO_BASE_ADDRESS + (TBT_HotPlugEvt/32)*4), Data32);
    
    //Data32 = IoRead32(GPIO_BASE_ADDRESS + (TBT_HotPlugEvt/32)*4);
    //Data32 &= ~(BIT00 << (TBT_HotPlugEvt%32));
    //IoWrite32((GPIO_BASE_ADDRESS + (TBT_HotPlugEvt/32)*4), Data32);
    
    // program GPIO pin setting
    // TBT_ForcePWR is GPIO, is Output, is Level mode
    //Data32 = (BIT00 | BIT04) & (~BIT02);
    //IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
    
    // TBT_HotPlugEvt is GPIO, is input, need invert, is Edge mode
    //Data32 = (BIT00 | BIT02 | BIT03) & (~BIT04);
    //IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_HotPlugEvt * 8)), Data32);
#endif
//*/
}

/**
    When entering Setup page, double check Security Level setting  
    is same or not between Thunderbolt host Fw and BIOS.

    This function only work for Thunderbolt Redwood Ridge based 
    host chip

    @param[in] BiosSecurityLevel   BIOS thunderbolt security level setting
    @param[in] TbtHostLocation     thunderbolt host location

    @retval 0 Security Level synchnized without change
    @retval 1 Security Level synchnized with programming again
    @retval 2 Error
**/
UINT8 SynchSecurityLevel(
  IN UINT8             BiosSecurityLevel,
  IN UINT8             TbtHostLocation
)
{
    UINT8            SynchState = 0;
// Sample code for ITE8728F and WTM2
/*
    UINT8            TbtHRbus;
    UINT8            PWRFlag = 0;
    UINT8            TBus = TBT_UP_PORT_BUS;
    UINT8            TDev = TBT_UP_PORT_DEV;
    UINT8            TFun = TBT_UP_PORT_FUNC;
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8            Data8;
#else
    UINT32           Data32;
#endif
    UINT32           RegVal;
    BOOLEAN          CmdDone;

    if (TbtHostLocation < 0x20){
        if (TbtHostLocation < 0x08) TFun = TbtHostLocation;
    } else {
        TDev = (TbtHostLocation & 0x0F) / 4 + 1;
        TFun = (TbtHostLocation & 0x0F) % 4;
    }
    
    // Get Thunderbolt Host Router Location
    TbtHRbus = MMIO_READ8(TBT_CFG_ADDRESS(TBus, TDev, TFun, PCI_SBUS));

    // Check Thunderbolt Host state
    RegVal = MMIO_READ32(TBT_CFG_ADDRESS(TbtHRbus, 0, 0, PCI_RID));
    if (RegVal == 0xFFFFFFFF){
        // Pull high GPIO_3(__FORCE_PWR) pin
#if !defined BWT1_BOARD || BWT1_BOARD != 2
        Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
        Data8 |= 0x02;
        IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
#else
        Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
        Data32 |= BIT31;
        IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif
    
        // Delay 50ms
        CountTime(50000, PM_BASE_ADDRESS);
        PWRFlag = 1;
    }
    
    // Do PCIE2TBT handshake to get Thunderbolt FW security level 
    CmdDone = TbtSetPCIe2TBTCommand(TbtHRbus, 0, TBT_GET_SECURITY_LEVEL, 0x008FFFFF);
    
    if (CmdDone){
        RegVal = MMIO_READ32(TBT_CFG_ADDRESS(TbtHRbus, 0, 0, RR_TBT2PCIE));

        if ((RegVal & MASK_ERROR) == 0){
            RegVal = (RegVal & MASK_DATA) >> 8;
        }
        else SynchState = 2;
    } else SynchState = 2;
    // So far, RegVal variable might be:
    // 1: 0xFFFFFFFF
    // 2: Thunderbolt host Revision ID and Class Code
    // 3: Thunderbolt host Fw security level setting

    // check Security Level setting between Thunderbolt Fw and BIOS
    if ((UINT8)RegVal != (BiosSecurityLevel - 1)){ 
        if (PWRFlag == 0){
            // Pull high GPIO_3(__FORCE_PWR) pin
#if !defined BWT1_BOARD || BWT1_BOARD != 2
            Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
            Data8 |= 0x02;
            IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
#else
            Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
            Data32 |= BIT31;
            IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif

            PWRFlag = 1;
        }
        IoWrite8(0x80, (BiosSecurityLevel - 1 + 0xC0));
        // After testing, TBT Fw needs Delay 600ms
        CountTime(600000, PM_BASE_ADDRESS);
        
        // Re-config Security Level with BIOS setting
        CmdDone = TbtSetPCIe2TBTCommand(TbtHRbus, (BiosSecurityLevel - 1), TBT_SET_SECURITY_LEVEL, 0x008FFFFF);

        if (CmdDone)  SynchState = 1;
        else SynchState = 2;
    }
    
    if (PWRFlag == 1){
        // Pull low GPIO_3(__FORCE_PWR) pin
#if !defined BWT1_BOARD || BWT1_BOARD != 2
        Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
        Data8 &= 0xFD;
        IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
#else
        Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
        Data32 &= (~BIT31);
        IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif

        // Delay 100ms
        CountTime(100000, PM_BASE_ADDRESS);
    }
//*/
    return SynchState;
}

/**
    This function is configure the Thunderbolt security level.
    OEM Porting required !!!

    @param[in] TbtSecurityLevel     BIOS Thunderbolt security level setting
    @param[in] TBTHostSeries        Thunderbolt host chip series
    @param[in] TbtHostLocation      Thunderbolt host location
    @param[in] IsPei                Flag to point out now is in PEI phase or not

    @retval VOID
**/
VOID ProgramTbtSecurityLevel(
  IN UINT8             *TbtSecurityLevel,
  IN UINT8             TBTHostSeries,
  IN UINT8             TbtHostLocation,
  IN BOOLEAN           IsPei
)
{
// Sample code for ITE8728F and WTM2
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8               Data8    = 0;
#else
    UINT32              Data32   = 0;
#endif
    UINT8               SecLevel = *TbtSecurityLevel;
    UINT8               TbtHRbus;
    BOOLEAN             TbtHostCmd = FALSE;
    UINT8               TBus = TBT_UP_PORT_BUS;
    UINT8               TDev = TBT_UP_PORT_DEV;
    UINT8               TFun = TBT_UP_PORT_FUNC;
    
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    switch(TBTHostSeries){
        case Cactus_Ridge:
            // For Cactus Ridge (CR) Host Router component, those GPIO's should be connected to the following pins:
            // * GPIO_3(__FORCE_PWR) - active high
            // * GPIO_6_OD__CIO_SDA_OD - active high
            // * GPIO_7_OD__CIO_SCL_OD - active high

            // 6.1 Security level menu requirements
            // 6.1.1 BIOS should supply security level menu with the following options
            // --------------------------------------------------------
            // | Security Level               | Gpio3 | Gpio7 | Gpio6 |
            // --------------------------------------------------------
            // |1. Normal mode with NHI       | Assert|   1   |   1   |
            // -------------------------------|       |----------------
            // |2. Normal mode without NHI    | For   |   0   |   0   |
            // -------------------------------|       |----------------
            // |3. Directly connected devices | 400ms |   0   |   1   |
            // |   without NHI                |       |       |       |
            // -------------------------------|       |----------------
            // |4. Redriver only              |       |   1   |   0   |
            // --------------------------------------------------------
            // |5. Off                        |       |       |       |
            // --------------------------------------------------------
            // |6. Thunderbolt debug          | Keep  |   1   |   1   |
            // --------------------------------------------------------
            if(IsPei){
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
                Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 3);
                if (SecLevel == TBT_OFF_MODE){
                    Data8 &= 0xFE;
                    IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 3, Data8);
                    return;
                }
                if (!(Data8 & BIT0)){
                    Data8 |= 0x01;
                    IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 3, Data8);
                }
#else
                if (SecLevel == TBT_CR_OFF_MODE) return;
#endif
                Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 5);
                Data8 &= ~(BIT6 | BIT7);
                 
                switch (SecLevel)
                {
                  case TBT_CR_DIRECT_CONNECTED_WO_NHI:
                      Data8 |= BIT6;
                      break;
                  case TBT_CR_REDRIVER_ONLY:
                      Data8 |= BIT7;
                      break;
                  case TBT_CR_NORMAL_MODE_WO_NHI:
                      break;
                      
                  case TBT_CR_NORMAL_MODE:
                  case TBT_CR_DEBUG_MODE:
                  default:
                      // Normal mode with NHI.
                      Data8 |= (BIT6 | BIT7);
                      break;
                }
                
                // Set GP66 and GP67
                IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 5, Data8);
                
                // Set GPIO6 and GPIO7 to the desired levels and
                // assert GPIO3 for at least 400ms period.
                // GP21 Pull high
                Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
                Data8 |= 0x02;
                IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
            } // In PEI phase
            break;
        case Redwood_Ridge:
        case Falcon_Ridge:
        case BDW_TBT_LP:
            if(!IsPei){
                // Get Thunderbolt Host Router Location
                if (TbtHostLocation < 0x20){
                    if (TbtHostLocation < 0x08) TFun = TbtHostLocation;
                } else {
                    TDev = (TbtHostLocation & 0x0F) / 4 + 1;
                    TFun = (TbtHostLocation & 0x0F) % 4;
                }
                TbtHRbus = MMIO_READ8(TBT_CFG_ADDRESS(TBus, TDev, TFun, PCI_SBUS));
                IoWrite8(0x80, (0xB0 | TbtHRbus));
                CountTime(50000, PM_BASE_ADDRESS);
                
                // First pull high GPIO_3(__FORCE_PWR) pin
                Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
                Data8 |= 0x02;
                IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
                
                IoWrite8(0x80, (0x80 | (SecLevel - 1)));
                CountTime(500000, PM_BASE_ADDRESS);
                
                // Do PCIE2TBT handshake
                TbtHostCmd = TbtSetPCIe2TBTCommand(TbtHRbus, (SecLevel - 1), TBT_SET_SECURITY_LEVEL, 0x008FFFFF);
                
                //for debug
                if(TbtHostCmd){
                    IoWrite8(0x80, 0x5D);
                    CountTime(100000, PM_BASE_ADDRESS);
                }
                
                // Finally pull low GPIO_3(__FORCE_PWR) pin
                Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
                Data8 &= 0xFD;
                IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
            } // In BDS phase
            break;
    } // end switch
#else
    if (IsPei != TRUE){
        //Get Thunderbolt Host Router Location
        if (TbtHostLocation < 0x20){
            if (TbtHostLocation < 0x08) TFun = TbtHostLocation;
        } else {
            TDev = (TbtHostLocation & 0x0F) / 4 + 1;
            TFun = (TbtHostLocation & 0x0F) % 4;
        }
        TbtHRbus = MMIO_READ8(TBT_CFG_ADDRESS(TBus, TDev, TFun, PCI_SBUS));
        IoWrite8(0x80, (0xB0 | TbtHRbus));
        CountTime(50000, PM_BASE_ADDRESS);
        
        // First pull high GPIO_3(__FORCE_PWR) pin
        Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
        Data32 |= BIT31;
        IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
       
        IoWrite8(0x80, (0x80 | (SecLevel - 1)));
        CountTime(500000, PM_BASE_ADDRESS);
          
        // Do PCIE2TBT handshake
        TbtHostCmd = TbtSetPCIe2TBTCommand(TbtHRbus, (SecLevel - 1), TBT_SET_SECURITY_LEVEL, 0x008FFFFF);
        
        //for debug
        if(TbtHostCmd){
            IoWrite8(0x80, 0x5D);
            CountTime(100000, PM_BASE_ADDRESS);
        }
        
        // Finally pull low GPIO_3(__FORCE_PWR) pin
        Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
        Data32 &= ~BIT31;
        IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
    } // Not at PEI phase
#endif
//*/
}

/**
    If system does not support "Wake from Thunderbolt device"
    function, BIOS should depend on Security Level and BootMod to 
    pull low FORCE_PWR pin or not in PEI phase

    This function only work for Thunderbolt "Cactus Ridge" chip
    and "system doesn't support wake up from Thunderbolt Device"

    @param[in] TbtSecurityLevel     BIOS Thunderbolt security level setting

    @retval VOID
**/
VOID FinialProgramTbtSecurityLevel(
  IN UINT8             TbtSecurityLevel )
{
// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8 Data8;
    UINT8 SecLevel = TbtSecurityLevel;

    OpenSioConfig();
    SetSioLdn (0x07);
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728F_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728F_GPIO_BASE_ADDRESS & 0xFF));
    }

    if (SecLevel <= TBT_CR_REDRIVER_ONLY) {
        Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
        Data8 &= 0xFD;
        IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
    }
#endif
//*/
}

/**
    BIOS should assert GO2Sx pin
    That will trigger Host Router to prepare underlying devices
    For Thunderbolt host is Cactus Ridge chip

    This function only work for Thunderbolt "Cactus Ridge" chip 

    @param VOID

    @retval EFI_STATUS      The function completed successfully
**/
EFI_STATUS ActiveTbtGpio2 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8 Data8;
    
    OpenSioConfig();
    
    SetSioLdn(0x07);
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728F_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728F_GPIO_BASE_ADDRESS & 0xFF));
    }

    Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
    Data8 |= BIT0;
    IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
#endif
//*/
  return EFI_SUCCESS;
}

/**
    BIOS should deassert GO2Sx pin
    That will trigger Host Router to prepare underlying devices

    This function only work for Thunderbolt "Cactus Ridge" chip

    @param VOID

    @retval EFI_STATUS      The function completed successfully
**/
EFI_STATUS InactiveTbtGpio2 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8 Data8;
    
    OpenSioConfig();
    
    SetSioLdn(0x07);
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728F_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728F_GPIO_BASE_ADDRESS & 0xFF));
    }
  
    Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
    Data8 &= 0xFE;
    IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
#endif
//*/
  return EFI_SUCCESS;
}

/**
    BIOS should poll OK2GO2SX_N_OD pin
    Upon completion of all preparations, Host Router will assert
    this pin to indicate readiness for Sx entry.

    This function only work for Thunderbolt "Cactus Ridge" chip

    @param VOID

    @retval EFI_STATUS      The function completed successfully
**/
EFI_STATUS PollTbtGpio9 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT32 counter = 0;
    
    while(IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1) & BIT2){
        if (counter == 0x008FFFFF) break;
        counter++;
    }
#endif
//*/
    return EFI_SUCCESS;
};

/**
    BIOS should pull down OK2GO2SX_N_OD pin in Wake flow
    if remebered Host Router state was active.

    This function only work for Thunderbolt "Cactus Ridge" chip
    and "system doesn't support wake up from Thunderbolt Device"

    @param VOID

    @retval EFI_STATUS      The function completed successfully
**/
EFI_STATUS PullDownTbtGpio9 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8 Data8;
    
    OpenSioConfig();
    
    SetSioLdn(0x07);
    
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728F_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728F_GPIO_BASE_ADDRESS & 0xFF));
    }
    
    //program GP22 as GPIO pin
    Data8 = ReadSio (0x26);
    Data8 |= 0x04;
    WriteSio (0x26, Data8);
    
    //program GP22 GPIO polarity
    Data8 = ReadSio (0xB1);
    Data8 &= 0xF8;
    WriteSio (0xB1, Data8);
    
    //program GP22 internal pull-up enable
    Data8 = ReadSio (0xB9);
    Data8 |= 0x04;
    WriteSio (0xB9, Data8);
    
    //program GP22 Simple I/O enable
    Data8 = ReadSio (0xC1);
    Data8 |= 0x04;
    WriteSio (0xC1, Data8);
    
    //program GP22 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xC9);
    Data8 |= 0x04;
    WriteSio (0xC9, Data8);
    
    Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 1);
    Data8 &= 0xFB;
    IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 1, Data8);
#endif
//*/
    return EFI_SUCCESS;
}

/**
    BIOS should release pull down OK2GO2SX_N_OD pin in Wake flow
    if remebered Host Router state was active

    This function only work for Thunderbolt "Cactus Ridge" chip 
    and "system doesn't support wake up from Thunderbolt Device"

    @param VOID

    @retval EFI_STATUS      The function completed successfully
**/
EFI_STATUS ReleaseTbtGpio9 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8 Data8;
    
    OpenSioConfig();
    
    SetSioLdn(0x07);
    
    //program GP22 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xC9);
    Data8 &= 0xFB;
    WriteSio (0xC9, Data8);
#endif
//*/
    return EFI_SUCCESS;
}

/**
    Power on POC to wake up thunderbolt

    This function is optional and only work for Thunderbolt "Cactus 
    Ridge" chip and system doesn't support wake up from Thunderbolt 
    Device.

    @param VOID

    @retval EFI_STATUS      The function completed successfully
**/
EFI_STATUS PowerOnPOC ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8 Data8;
    
    OpenSioConfig();
    SetSioLdn(0x07);
    
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728F_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728F_GPIO_BASE_ADDRESS & 0xFF));
    }
    
    //program GP40 as GPIO pin
    Data8 = ReadSio (0x28);
    Data8 |= 0x01;
    WriteSio (0x28, Data8);
    
    //program GP40 GPIO polarity
    Data8 = ReadSio (0xB3);
    Data8 &= 0xFE;
    WriteSio (0xB3, Data8);
    
    //GP40 internal internal pull-up enable
    Data8 = ReadSio (0xBB);
    Data8 |= 0x01;
    WriteSio (0xBB, Data8);
    
    //GP40 Simple I/O enable
    Data8 = ReadSio (0xC3);
    Data8 |= 0x01;
    WriteSio (0xC3, Data8);
    
    //GP40 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xCB);
    Data8 |= 0x01;
    WriteSio (0xCB, Data8);
    
    Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 3);
    if (!(Data8 & BIT0)){
        Data8 |= 0x01;
        IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 3, Data8);
    }
#endif
//*/
    return EFI_SUCCESS;
}

/**
    Power off POC to cut off thunderbolt power 

    This function is optional and only work for Thunderbolt "Cactus 
    Ridge" chip and system doesn't support wake up from Thunderbolt 
    Device.

    @param VOID

    @retval EFI_STATUS      The function completed successfully
**/
EFI_STATUS PowerOffPOC ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT1_BOARD || BWT1_BOARD != 2
    UINT8 Data8;
    
    OpenSioConfig();
    SetSioLdn(0x07);
    
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728F_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728F_GPIO_BASE_ADDRESS & 0xFF));
    }
    
    Data8 = IoRead8(IT8728F_GPIO_BASE_ADDRESS + 3);
    Data8 &= 0xFE;
    IoWrite8(IT8728F_GPIO_BASE_ADDRESS + 3, Data8);
#endif
//*/
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
