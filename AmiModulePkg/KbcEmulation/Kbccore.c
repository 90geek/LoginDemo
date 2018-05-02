//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Kbccore.c 9     1/09/12 1:30a Rameshr $
//
// $Revision: 9 $
//
// $Date: 1/09/12 1:30a $
//
//****************************************************************************

//<AMI_FHDR_START>
//**********************************************************************
//
// Name:        Kbccore.c
//
// Description: It has function for port 60 read, 60 write, 64 read and 64 write
//
//**********************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "Kbc.h"
#if UHCI_EMUL_SUPPORT
#include "KbcUhci.h"
#endif
#if OHCI_EMUL_SUPPORT
#include "KbcOhci.h"
#endif
#if SB_EMUL_SUPPORT
#include "KbcSb.h"
#endif
#if IOTRAP_EMUL_SUPPORT
#include "KbcIoTrap.h"
#endif

#pragma optimize("",off)
BOOLEAN         AcpiEmulationDisable=FALSE;
extern KBC*     gVirtualKBC;


#define SYNC_SMI_BIT  (1 << 0)


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindSMICpu
//
// Description: In a Multiprocessor environment, any logical CPU can generate
//              the SMI. This function finds the CPU that generates SMI by accessing
//              IO 60/64 Ports
//
// Input:       None
//
// Output:      UINT8 CpuIndex
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 FindSMICpu ( ) {
    UINT8                   CpuIndex;
#if PI_SPECIFICATION_VERSION >= 0x0001000A
    EFI_SMM_SAVE_STATE_IO_INFO  IoInfo;
#else
    UINT32                  SmmIoMiscInfo;
    UINT16                  IOAddress;
    UINT32                  Smbase=0;
#endif

    for (CpuIndex = 0; CpuIndex < gSmst1->NumberOfCpus; CpuIndex++) {

#if PI_SPECIFICATION_VERSION >= 0x0001000A

        SmmCpuProtocol->ReadSaveState(
                            SmmCpuProtocol,
                            2,
                            EFI_SMM_SAVE_STATE_REGISTER_IO,
                            CpuIndex,
                            (VOID*)&IoInfo
                            );
    
        if ((IoInfo.IoPort == 0x60) || (IoInfo.IoPort == 0x64)) {
            return CpuIndex;
        }
#else

        //
        // Find which CPU caused the SMI
        //    
        Smbase = gSmst1->CpuSaveState[CpuIndex].Ia32SaveState.SMBASE;
        SmmIoMiscInfo = *(UINT32 *) (((UINT8 *) (UINTN) Smbase) + 0x8000 + 0x7FA4);
        IOAddress =     SmmIoMiscInfo >> 16;
        if (((IOAddress == 0x60) || (IOAddress == 0x64)) && (SmmIoMiscInfo & SYNC_SMI_BIT)) {
            return CpuIndex;
        }
#endif

    }

    return 0xFF;  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   getTrapAL
//
// Description: Get the port 60 or 64 input value from the CPU save reg
//
// Input:       None
//
// Output:      UINT8 Value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetTrapAL()
{

#if UHCI_EMUL_SUPPORT || SB_EMUL_SUPPORT ||	IOTRAP_EMUL_SUPPORT

	UINT8   CpuIndex;

	CpuIndex = FindSMICpu ();
	ASSERT (CpuIndex != 0xFF);

#if PI_SPECIFICATION_VERSION >= 0x0001000A
{
    UINT8       TrapAl=0xFF;

    SmmCpuProtocol->ReadSaveState(
                            SmmCpuProtocol,
                            1,
                            EFI_SMM_SAVE_STATE_REGISTER_RAX,
                            CpuIndex,
                            &TrapAl
                            );
    return TrapAl;
}
#else
	return (UINT8)GET_CPUSAVESTATE_REG(CpuIndex, EAX);
#endif

#else
	return GetHceInput();
#endif

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   setTrapAL
//
// Description: Set the port 60 or 64 output value to the CPU save reg
//
// Input:       UINT8 Data
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void SetTrapAL(UINT8 data)
{

#if UHCI_EMUL_SUPPORT || SB_EMUL_SUPPORT || IOTRAP_EMUL_SUPPORT
    UINT8   CpuIndex;

    CpuIndex = FindSMICpu();
    ASSERT (CpuIndex != 0xFF);

#if PI_SPECIFICATION_VERSION >= 0x0001000A

    SmmCpuProtocol->WriteSaveState(
                            SmmCpuProtocol,
                            1,
                            EFI_SMM_SAVE_STATE_REGISTER_RAX,
                            CpuIndex,
                            &data
                            );
#else
    *(UINT8*)&GET_CPUSAVESTATE_REG(CpuIndex, EAX) = data;
#endif
#endif

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   trap64w
//
// Description: This function handles the Port64 write command
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void trap64w()
{
    (*gVirtualKBC->kbc_write_command)( gVirtualKBC,GetTrapAL() );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   setTrapAL
//
// Description: This function handles the Port60 write command
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void trap60w()
{
    (*gVirtualKBC->kbc_write_data)( gVirtualKBC,GetTrapAL() );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   setTrapAL
//
// Description: This function handles the Port64 Read command
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void trap64r()
{
    SetTrapAL((*gVirtualKBC->kbc_read_status)(gVirtualKBC));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   setTrapAL
//
// Description: This function handles the Port60 Read command
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void trap60r()
{
    SetTrapAL((*gVirtualKBC->kbc_read_data)(gVirtualKBC));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   hasTrapStatus
//
// Description: return the port 6064 trap status
//
// Input:       None
//
// Output:      TRUE: Trab enabled for port 6064
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN hasTrapStatus()
{
    
#if UHCI_EMUL_SUPPORT
    return Uhci_HasTrapStatus();
#endif
#if OHCI_EMUL_SUPPORT
    return Ohci_HasTrapStatus();
#endif
#if SB_EMUL_SUPPORT
    return Sb_HasTrapStatus();
#endif
#if IOTRAP_EMUL_SUPPORT
    return IoTrap_HasTrapStatus();
#endif
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   TrapEnable
//
// Description: Enable/disable the port6064 trap
//
// Input:       TRUE : enable the trap.
//              FALSE: Disable the trap.
//
// Output:      TRUE : when suucessfully done else FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TrapEnable(BOOLEAN b)
{

    if(AcpiEmulationDisable) {
        return FALSE;
    }

#if UHCI_EMUL_SUPPORT
    return Uhci_TrapEnable(b);
#endif
#if OHCI_EMUL_SUPPORT
    return Ohci_TrapEnable(b);
#endif
#if SB_EMUL_SUPPORT
    return Sb_TrapEnable(b);
#endif    
#if IOTRAP_EMUL_SUPPORT
    return IoTrapEnable(b);
#endif
	return TRUE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
