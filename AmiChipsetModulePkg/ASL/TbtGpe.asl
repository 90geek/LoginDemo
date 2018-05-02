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
//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//*************************************************************************
// Revision History
// ----------------
// $Log: $
// 
//*************************************************************************
#include "tokenAsl.h"
#ifndef ASL_PCIEX_BASE_ADDRESS
#define ASL_PCIEX_BASE_ADDRESS  0x80000000  //AptioV server override
#endif

Scope(\)
{
    Mutex(OSUM, 0)  // OS Up mutex
    Event(WFEV)
//    Name(TBTE, 0) // Thunderbolt function enable
    Name(PEMA, ASL_PCIEX_BASE_ADDRESS) // PCIE base address
    Name(TBRP, ASL_DEFAULT_TBT_AIC_LOCATION) // PCIE root port location for Thunderbolt Host
    Name(TBUS, 0xFF) // Thunderbolt Host BUS number
    Name(TBHR, 0xFF) //1:Cactus Ridge 2:Redwood Ridge 3:Falcon Ridge 4:Win Ridge will be updated
    Name(TBMV, 0xFF) // _RMV return value for Thunderbolt
    Name(RPR6, 0)
    Name(RPR7, 0)
    Name(RPR8, 0)
    Name(RPR9, 0)
    Name(RPRA, 0)
    Name(RPRB, 0)
    
    OperationRegion(TBNV,SystemMemory,0xFFFF0000,0x7B7B)
    Field(TBNV,AnyAcc,Lock,Preserve)
    {
        TBHS, 8,    // Thunderbolt Host series
        THRS, 8,    // Thunderbolt Host Router State
        TBWS, 8,    // Wake from Thunderbolt
    }
    
#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
    //
    // Define SW SMI port as an ACPI Operating Region to use for generate SW SMI.
    //
    OperationRegion(SPRT,SystemIO, 0xB2,2)
    Field (SPRT, ByteAcc, Lock, Preserve) 
    {
        SSMP, 8
    }
#endif
    
    Method(TBWK, 1)
    {
        ASL_TBT_WAK
    }
    Method(TBPS, 1)
    {
        ASL_TBT_PTS
    }
}

Scope(\_SB)
{
    // Include OEM porting required ASL
    Include("AmiTbtOemPorting.asl")

	// WMI ACPI device to control TBT force power
    Device(WMTF)
    {
        // pnp0c14 is pnp id assigned to WMI mapper
        Name(_HID, "PNP0C14")
        Name(_UID, "TBFP")   
        
        Name(_WDG, Buffer() {
            // {86CCFD48-205E-4A77-9C48-2021CBEDE341}
            0x48, 0xFD, 0xCC, 0x86,
            0x5E, 0x20,
            0x77, 0x4A,
            0x9C, 0x48,
            0x20, 0x21, 0xCB, 0xED, 0xE3, 0x41,
            84, 70,    // Object Id (TF)
            1,         // Instance Count
            0x02       // Flags (WMIACPI_REGFLAG_METHOD)
        })
        
        // Set TBT force power
        // Arg2 is force power value
        Method(WMTF, 3)
        {
            CreateByteField(Arg2,0,FP)
            
            If(FP)
            {
                TBFP(1)
            }
            Else
            {
                TBFP(0)
            }						
        } // end WMTF method
    } // end WMTF device
} // end SB scope

Scope(\_GPE)
{
    Method(OSUP, 1)
    {
        // OSUP method apply TB2P<->P2TB handshake procedure 
        // with Command = OS_Up
        // Arg0 - Memory mapped IO address of RR host router upstream port
        Add(Arg0, 0x548, Local0)
        OperationRegion(PXVD,SystemMemory,Local0,0x08)
        Field(PXVD,DWordAcc, NoLock, Preserve)
        {
            TB2P, 32, 
            P2TB, 32
        }    

        Store(100, Local1)
        Store(0x0D, P2TB) // Write (OS_Up << 1) | 1 to PCIe2TBT
        While(LGreater(Local1, 0))
        {
            Store(Subtract(Local1, 1), Local1)
            Store(TB2P, Local2)
            If(LEqual(Local2, 0xFFFFFFFF))// Device gone
            {
                Return(2)
            }
            If(And(Local2, 1)) // Done
            {
                break
            }
            Sleep(50)
        }
        Store(0x00, P2TB) // Write 0 to PCIe2TBT
        Return(1)
    } // end OSUP method

    Method(TSXE)
    {
        // Thunderbolt ACPI Sx_Exit flow
#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
        Store(0x14, DBG8)
#else
        P8XH(0, 0x14)     // for debug
#endif
        Store(MMTB(), Local0)
        OperationRegion(PXVD,SystemMemory,Local0,0x550)
        Field(PXVD,DWordAcc, NoLock, Preserve)
        {
            VIDI, 32,
            Offset(0x548),
            TB2P, 32, 
            P2TB, 32
        }
        
        Store(9, P2TB) // Store PCIE2TBT_SX_EXIT_TBT_CONNECTED + PCIE2TBT_VLD_B ((4 << 1) | 1) into PCIE2TBT
        Store(100, Local1)
        
        While(LGreater(Local1, 0))
        {
            Store(Subtract(Local1, 1), Local1)
            Store(TB2P, Local2)
            If(LEqual(Local2, 0xFFFFFFFF))// Device gone
            {
                Return()
            }
            If(And(Local2, 1)) // Done
            {
                break
            }
            Sleep(50)
        }
        Store(0x00, P2TB) // Write 0 to PCIe2TBT
        
        // Wait for DevId
        Store(500, Local1)
        While(LGreater(Local1, 0))
        {
            Store(Subtract(Local1, 1), Local1)
            Store(VIDI, Local2)
            If(LNotEqual(Local2, 0xFFFFFFFF))// Done
            {
                Return(0)
            }
            Sleep(50)
        }
        Return()
    } // end TSXE method

    Method(MMRP)
    {
        // Calculate Memory mapped IO address of RR host router PCIE root port
        // And put it into XXXXX
        
        Store(\PEMA, Local0)
        If(LLess(ToInteger(\TBRP), 0x08))     // SB PCIE root port
        {
            Add(Local0, 0xE0000, Local0) // RP01
            Store(ToInteger(\TBRP), Local1)
            Multiply(Local1, 0x1000, Local1)
            Add(Local0, Local1, Local0) //RP0x
        }
#if defined ASL_TBT_NB_PCIE_SLOT_SUPPORT && ASL_TBT_NB_PCIE_SLOT_SUPPORT == 1
        Else                          // NB PCIE root port
        {
            Add(Local0, 0x8000, Local0) // PEG0
            Subtract(ToInteger(\TBRP), 0x20, Local1)
            Divide(Local1, 0x04, Local5, Local4) // Local4 = Local1/4, Local5 = Local1%4
            Multiply(Local4, 0x8000, Local4) // Dev Num
            Add(Local0, Local4, Local0)
            Multiply(Local5, 0x1000, Local5) // Fun Num
            Add(Local0, Local5, Local0)
        }
#endif
        Return(Local0)
    } // end MMRP method

    Method(MMTB)
    {
        // Calculate Memory mapped IO address of RR host router upstream port
        // And put it into XXXXX
        
        Store(MMRP(), Local0)
        OperationRegion(MMMM, SystemMemory, Local0, 0x1A)
        Field(MMMM, AnyAcc, NoLock, Preserve)
        {
            Offset(0x19),
            SBUS, 8
        }
        
        Store(SBUS, Local2)
        Store(\PEMA, Local0)
        Multiply(Local2, 0x100000, Local2)
        Add(Local0, Local2, Local0)  //TBT HR US port MMIO address
        Return(Local0)
    } // end MMTB method

    Method(GDRP)
    {
        // Put TBT PCIE root port to D0 state
        
        Store(MMRP(), Local0)
        OperationRegion(RP_X, SystemMemory, Local0, 0x100)
        Field(RP_X, AnyAcc, NoLock, Preserve)
        {
            Offset(0x84),
            NBPS, 2,       // Power State of PEG slot
            Offset(0xA4),
            PSD3, 2,       // Power State of SB PCIE slot
            Offset(0xE4),
            HNPS, 2,       // Power State of NB PCIE slot of High land platform
        }
        
        If(LLess(ToInteger(\TBRP), 0x20))
        {
            Store(0, PSD3)
            Return (PSD3)
        }
        Else
        {
#if !defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG || ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 0
            Store(0, NBPS)
            Return (NBPS)
#else
            Store(0, HNPS)
            Return (HNPS)
#endif
        }
    } // end GDRP method

    Method(RPDX, 1)
    {
        // Change TBT PCIE root port Power state via Arg0
        // Arg0 - 0: D0 Status
        //        3: D3 Status
        
        Store(MMRP(), Local0)
        OperationRegion(RP_X, SystemMemory, Local0, 0x100)
        Field(RP_X, AnyAcc, NoLock, Preserve)
        {
            Offset(0x84),
            NBPS, 2,       // Power State of PEG slot
            Offset(0xA4),
            PSD3, 2,       // Power State of SB PCIE slot
            Offset(0xE4),
            HNPS, 2,       // Power State of NB PCIE slot of High land platform
        }

        If(LLess(ToInteger(\TBRP), 0x20))
        {
            Store(Arg0, PSD3)
        }
        Else
        {
#if !defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG || ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 0
            Store(Arg0, NBPS)
#else
            Store(Arg0, HNPS)
#endif
        }
        
        Sleep(100)
    } // end RPDX method

    Method(TBAC)
    {
        // Equal Intel BIOS method TSUB and WSUB
        
        Acquire(OSUM, 0xFFFF)
        Store(MMRP(), Local0)
        OperationRegion(RP_X, SystemMemory, Local0, 0x100)
        Field(RP_X, AnyAcc, NoLock, Preserve)
        {
            Offset(0x08),
            RDCC, 32,
            Offset(0x18),
            PBUS, 8,
            SBUS, 8,
            SUBS, 8,
            Offset(0x84),
            NBPS, 2,       // Power State of PEG slot
            Offset(0xA4),
            PSD3, 2,       // Power State of SB PCIE slot
            Offset(0xE4),
            HNPS, 2,       // Power State of NB PCIE slot of High land platform
        }
        Store(0, Local1)
        While(1)
        {
            If(LAnd(LNotEqual(RDCC, 0xFFFFFFFF), LNotEqual(SBUS, 0xFF)))
            {
                If(LAnd(LLess(ToInteger(\TBRP), 0x10), LEqual(PSD3, 0x0))){
                    Break
                }
#if !defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG || ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 0
                If(LAnd(LGreaterEqual(ToInteger(\TBRP), 0x10), LEqual(NBPS, 0x0))){
#else
                If(LAnd(LGreaterEqual(ToInteger(\TBRP), 0x10), LEqual(HNPS, 0x0))){
#endif
                    Break
                }
            }
            Else
            {
                Add(Local1, 0x01, Local1)
                If(LGreater(Local1, 0x03E8))
                {
#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
                    Store(0x7BAC, DBG9)
#else
                    P8XH(1,0x7B)
                    P8XH(0,0xAC)
#endif
                    Sleep(0x3E8)
                    Break
                }
                Else
                {
                    Sleep(0x10)
                }
            }
        } //  end while looop
        Release(OSUM)
    } // end TBAC method

    Method(NTFY)
    {
        // Intel Chipset Sample code Notify Method
        Sleep(100)
        Switch(ToInteger(\TBRP)) // TBT Selector
        {
#if defined ASL_SB_PCIE_ROOT_PORT_0 && ASL_SB_PCIE_ROOT_PORT_0 == 1
            Case (0)
            {
                Notify(\_SB.PCI0.RP01,0)
            }
#endif
#if defined ASL_SB_PCIE_ROOT_PORT_1 && ASL_SB_PCIE_ROOT_PORT_1 == 1
            Case (1)
            {
                Notify(\_SB.PCI0.RP02,0)
            }
#endif
#if defined ASL_SB_PCIE_ROOT_PORT_2 && ASL_SB_PCIE_ROOT_PORT_2 == 1
            Case (2)
            {
                Notify(\_SB.PCI0.RP03,0)
            }
#endif
#if defined ASL_SB_PCIE_ROOT_PORT_3 && ASL_SB_PCIE_ROOT_PORT_3 == 1
            Case (3)
            {
                Notify(\_SB.PCI0.RP04,0)
            }
#endif
#if defined ASL_SB_PCIE_ROOT_PORT_4 && ASL_SB_PCIE_ROOT_PORT_4 == 1
            Case (4)
            {
                Notify(\_SB.PCI0.RP05,0)
            }
#endif
#if defined ASL_SB_PCIE_ROOT_PORT_5 && ASL_SB_PCIE_ROOT_PORT_5 == 1
            Case (5)
            {
                Notify(\_SB.PCI0.RP06,0)
            }
#endif
#if defined ASL_SB_PCIE_ROOT_PORT_6 && ASL_SB_PCIE_ROOT_PORT_6 == 1
            Case (6)
            {
                Notify(\_SB.PCI0.RP07,0)
            }
#endif
#if defined ASL_SB_PCIE_ROOT_PORT_7 && ASL_SB_PCIE_ROOT_PORT_7 == 1
            Case (7)
            {
                Notify(\_SB.PCI0.RP08,0)
            }
#endif
#if defined ASL_NB_PCIE_ROOT_PORT_0 && ASL_NB_PCIE_ROOT_PORT_0 == 1
            Case (0x20)
            {
                Notify(\_SB.PCI0.PEG0,0)
            }
#endif
#if defined ASL_NB_PCIE_ROOT_PORT_1 && ASL_NB_PCIE_ROOT_PORT_1 == 1
            Case (0x21)
            {
                Notify(\_SB.PCI0.PEG1,0)
            }
#endif
#if defined ASL_NB_PCIE_ROOT_PORT_2 && ASL_NB_PCIE_ROOT_PORT_2 == 1
            Case (0x22)
            {
                Notify(\_SB.PCI0.PEG2,0)
            }
#endif
#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
            Case(0x20)
            {
                Notify(\_SB.PCI0.BR1A,0)
            }
            Case(0x21)
            {
                Notify(\_SB.PCI0.BR1B,0)
            }
            Case(0x24)
            {
                Notify(\_SB.PCI0.BR2A,0)
            }
            Case(0x25)
            {
                Notify(\_SB.PCI0.BR2B,0)
            }
            Case(0x26)
            {
                Notify(\_SB.PCI0.BR2C,0)
            }
            Case(0x27)
            {
                Notify(\_SB.PCI0.BR2D,0)
            }
            Case(0x28)
            {
                Notify(\_SB.PCI0.BR3A,0)
            }
            Case(0x29)
            {
                Notify(\_SB.PCI0.BR3B,0)
            }
            Case(0x2A)
            {
                Notify(\_SB.PCI0.BR3C,0)
            }
            Case(0x2B)
            {
                Notify(\_SB.PCI0.BR3D,0)
            }
#endif
        } // end switch
    } // end NTFY method

    Method(TBFF)
    {
        // Check for 0xFFFFFFFF in TBT Vendor/Device ID
        // And Call OSUP if true
        
        // Get mapped IO address of RR host router upstream port
        Store(MMTB(), Local0) 
        OperationRegion(PXVD,SystemMemory,Local0,0x4) 
        Field(PXVD,DWordAcc, NoLock, Preserve)
        {
            VEDI, 32 // Vendor/Device ID
        }    
      
        //Check Vendor/Device ID for 0xFFFFFFFF
        Store(VEDI, Local1)
        If(LEqual(Local1, 0xFFFFFFFF))
        {
            Return (OSUP(Local0))
        }
        Else
        {
            Return (0)
        }
    } // end TBFF method

    Method(OE1X)
    {
        Name(TSNE, 0xFF) //will be updated by setup menu

#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
        If(LLess(OSVR,14)) { Return() } // only support win7 or above OS
#else    
        If(LLess(OSYS,2009)) { Return() } // only support win7 or above OS
#endif

        Wait(WFEV, 0xFFFF)
        Signal(WFEV)
        TBAC()
        Acquire(OSUM, 0xFFFF)    
        If(LNotEqual(\TBHR, 0x01))// For Redwood Ridge/Falcon Ridge
        {
            Store(TBFF(), Local0)
            If(LEqual(Local0, 1))// Only HR
            {
                Sleep(16)
                Release(OSUM)
                Return ()
            }
            If(LEqual(Local0, 2)) // Disconnect
            {
                If(And(TSNE, 0x02)) // If notification is enabled call Notify
                {
                    Sleep(16)
                    NTFY()
                }
#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
                Store(0x7D, DBG8)
#else
                P8XH(0,0x7D)
#endif
                Release(OSUM)
                Return ()
            }
        }
        
        If(And(TSNE, 0x01))
        {
            Store(TBSW, SSMP)
        }
        If(And(TSNE, 0x02))
        {
            NTFY()
        }
        Sleep(16)
        Release(OSUM)
    } // end _Exx method
} // end GPE scope

#if defined (ASL_TBT_RMV_REPORT) && (ASL_TBT_RMV_REPORT == 1)
Scope (ASL_TBT_RP_NUM.PXSX)
{
    Method(_RMV)
    {
        Return(TBMV)
    } // end _RMV
}
#endif // TBT_RMV_REPORT

Scope (ASL_TBT_RP_NUM)
{
#if defined ASL_TBT_PCI0_INI_SUPPORT && ASL_TBT_PCI0_INI_SUPPORT == 1
    Method(TINI,0)
#else
    Method(_INI,0)
#endif
    {
#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
        If(LLess(OSVR,14)) { Return() } // only support win7 or above OS
#else 
        If(LLess(OSYS,2009)) { Return() } // only support win7 or above OS
#endif

        If(LAnd(LNotEqual(\TBHR, 0xFF), LNotEqual(\TBHR, 0x01)))// For Redwood Ridge/Falcon Ridge
        {
            Acquire(OSUM, 0xFFFF)
	  
#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
            Store(0x51, DBG8)
#else
            P8XH(0, 0x51)     // for debug
#endif

/*
            Store(MMRP(), Local1)
            OperationRegion(RP_X, SystemMemory, Local1, 0x20)
            Field(RP_X, DWordAcc, NoLock, Preserve)
            {
                REG0, 32,
                REG1, 32,
                REG2, 32,
                REG3, 32,
                REG4, 32,
                REG5, 32,
                REG6, 32,
                REG7, 32,
            }
            Store(REG6, Local2)
            Store(0x00F0F000, REG6)
*/
            \_GPE.TBAC()
            // Get memory mapped IO address of RR host router upstream port
            Store(\_GPE.MMTB(), Local3)
            // Call OSUP
            \_GPE.OSUP(Local3)
            Release(OSUM)
            Signal(WFEV)
        }
    } // end _INI/TINI method

#if defined(ASL_TBT_WAK_SUPPORT) && (ASL_TBT_WAK_SUPPORT==1)
    Method(TWAK, 1)
    {
        Name(RPL1, 0)
        Name(RPL6, 0)
        Name(RPL7, 0)
        Name(RPL8, 0)
        Name(RPL9, 0)
        Name(RPLA, 0)
        Name(RPLB, 0)

#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
        If(LLess(OSVR,14)) { Return() } // only support win7 or above OS
#else       
        If(LLess(OSYS,2009)) { Return() } // only support win7 or above OS
#endif

        If(LAnd(LNotEqual(\TBHR, 0xFF), LNotEqual(\TBHR, 0x01)))// Only for Redwood Ridge/Falcon Ridge
        {
            Acquire(OSUM, 0xFFFF)
            \_GPE.TBAC()
            //Sleep(50)  // fix hang up when S3 resuming
            
#if defined ASL_TBT_ASL_HANDLE_SX_EXIT && ASL_TBT_ASL_HANDLE_SX_EXIT == 1
            // Thunderbolt Intel Sample code rev 1.10
            // doing Sx_Exit flow in ACPI ASL code
            If(LEqual(ToInteger(\THRS), 1)){
                If(LEqual(ToInteger(\TBWS), 0)){
                    Sleep(500)
                }
                \_GPE.TSXE()
                
                If(LGreater(ToInteger(\TBRP), 0x0F))
                {
                    Sleep(600)
                }
            }
#endif
            
            // Get memory mapped IO address of RR host router upstream port
            Store(\_GPE.MMRP(), Local0)
            OperationRegion(RP_X, SystemMemory, Local0, 0x34)
            Field(RP_X, DWordAcc, NoLock, Preserve)
            {
                REG0, 32,
                REG1, 32,
                REG2, 32,
                REG3, 32,
                REG4, 32,
                REG5, 32,
                REG6, 32,
                REG7, 32,
                REG8, 32,
                REG9, 32,
                REGA, 32,
                REGB, 32,
                REGC, 32,
            }
            Store(REG1, RPL1)
            Store(REG6, RPL6)
            Store(REG7, RPL7)
            Store(REG8, RPL8)
            Store(REG9, RPL9)
            Store(REGA, RPLA)
            Store(REGB, RPLB)
            Store(RPR6, REG6)
            Store(RPR7, REG7)
            Store(RPR8, REG8)
            Store(RPR9, REG9)
            Store(RPRA, REGA)
            Store(RPRB, REGB)
            Store(0x00100007, REG1)
            Store(\_GPE.GDRP(), Local2)
            \_GPE.RPDX(Zero)
            Store(\_GPE.MMTB(), Local3)
            // Call OSUP
            \_GPE.OSUP(Local3)
            // Restore TBT root port resource/bus/cmd/D state registers as before Sx entry
            Store(TBSW, SSMP)
            // Restore original register values as before calling SMI
            Store(RPL1, REG1)
            Store(RPL6, REG6)
            Store(RPL7, REG7)
            Store(RPL8, REG8)
            Store(RPL9, REG9)
            Store(RPLA, REGA)
            Store(RPLB, REGB)
            \_GPE.RPDX(Local2)
            Release(OSUM)
            
            // For TBT host at NB PCIE slot
            If(LGreaterEqual(ToInteger(\TBRP), 0x20))
            {
                \_GPE.NTFY()
            } // end if 
        }

#if defined(ASL_TBT_S3_WAK_SMI) && (ASL_TBT_S3_WAK_SMI == 1) && (ASL_TBT_WAK_SUPPORT == 1)
        Store(Arg0,Local0)
        If(LAnd(LEqual(Local0, 0x03), LLess(ToInteger(\TBRP), 0x20))){
            If(ASL_TBT_RP_NUM.PDSX){
                Store(TBSW, SSMP)
                \_GPE.NTFY()
            }
        }
#endif
        Signal(WFEV)
    } // end TWAK method
#endif

#if defined(ASL_TBT_PTS_SUPPORT) && (ASL_TBT_PTS_SUPPORT==1)
    Method(TPTS, 1)
    {
#if defined ASL_TBT_HIGHLAND_PLATFORM_CONFIG && ASL_TBT_HIGHLAND_PLATFORM_CONFIG == 1
        If(LLess(OSVR,14)) { Return() } // only support win7 or above OS
#else 
        If(LLess(OSYS,2009)) { Return() } // only support win7 or above OS
#endif
        
        If(LAnd(LNotEqual(\TBHR, 0xFF), LNotEqual(\TBHR, 0x01)))// Only for Redwood Ridge/Falcon Ridge
        {
            Acquire(OSUM, 0xFFFF)
            Store(\_GPE.MMRP(), Local0)
            OperationRegion(RP_X, SystemMemory, Local0, 0x34)
            Field(RP_X, DWordAcc, NoLock, Preserve)
            {
                REG0, 32,
                REG1, 32,
                REG2, 32,
                REG3, 32,
                REG4, 32,
                REG5, 32,
                REG6, 32,
                REG7, 32,
                REG8, 32,
                REG9, 32,
                REGA, 32,
                REGB, 32,
                REGC, 32,
            }
            Store(REG6, RPR6)
            Store(REG7, RPR7)
            Store(REG8, RPR8)
            Store(REG9, RPR9)
            Store(REGA, RPRA)
            Store(REGB, RPRB)
            Release(OSUM)
        }
#if defined(ASL_TBT_CLEAR_PME_STATUS) && (ASL_TBT_CLEAR_PME_STATUS == 1)
        If(LLess(ToInteger(\TBRP), 0x20))
        {
            If(LOr(PSPX, PMEP))
            {
                Store(PMEX, Local1)
                Store(0, PMEX)
                Sleep(10)
                Store(1, PSPX)
                Sleep(10)
                If(PSPX)
                {
                    Store(1, PSPX)
                    Sleep(10)
                }
                Store(Local1, PMEX)
            }
        }
#endif
        Reset(WFEV)
    } // end TPTS method
#endif
} // end "ASL_TBT_RP_NUM" scope
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
