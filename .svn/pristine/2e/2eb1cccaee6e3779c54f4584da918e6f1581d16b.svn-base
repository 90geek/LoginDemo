//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: $
//
// $Revision: $
//
// $Date: $
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: KbcEmulDxeLib.c
//
// Description:	KBC emulation Lib header file used in other files
//
//<AMI_FHDR_END>
//**********************************************************************

#include "KbcEmulDxe.h"
#include "KbcEmulLib.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmByteReadIO
//
// Description: This routine reads a Byte from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
NonSmmByteReadIO(UINT16 wIOAddr)
{
    UINT8 value;
    CpuIo->Io.Read(CpuIo, SMM_IO_UINT8, wIOAddr, 1, &value);
    return value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmByteWriteIO
//
// Description: This routine writes a byte to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              bValue      Byte value to write
//
// Output:      None
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmByteWriteIO (UINT16 wIOAddr, UINT8 bValue)
{
    CpuIo->Io.Write(CpuIo, SMM_IO_UINT8, wIOAddr, 1, &bValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWordReadIO
//
// Description: This routine reads a Word from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
NonSmmWordReadIO(UINT16 wIOAddr)
{
    UINT16 value;
    CpuIo->Io.Read(CpuIo, SMM_IO_UINT16, wIOAddr, 1, &value);
    return  value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWordWriteIO
//
// Description: This routine writes a word to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              wValue      Word value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmWordWriteIO (UINT16 wIOAddr, UINT16 wValue)
{
    CpuIo->Io.Write(CpuIo, SMM_IO_UINT16, wIOAddr, 1, &wValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmDwordReadIO
//
// Description: This routine reads a dword from the specified IO address
//
// Input:       wIOAddr     I/O address to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
NonSmmDwordReadIO(UINT16 wIOAddr)
{
    UINT32  value;
    CpuIo->Io.Read(CpuIo, SMM_IO_UINT32, wIOAddr, 1, &value);
    return  value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmDwordWriteIO
//
// Description: This routine writes a double word to the specified IO address
//
// Input:       wIOAddr     I/O address to write
//              dValue      Double word value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmDwordWriteIO(UINT16 wIOAddr, UINT32 dValue)
{
    CpuIo->Io.Write(CpuIo, SMM_IO_UINT32, wIOAddr, 1, &dValue);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWritePCIConfig
//
// Description: This function opens PCI configuration for a given register
//
// Input:       wBDF  - Bus, device and function number
//              bReg  - Register number to read
//
// Output:      IO register to write the value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
NonSmmWritePCIConfig(UINT16 wBDF, UINT8 bReg)
{
    NonSmmDwordWriteIO(0xCF8, (UINT32)(0x80000000 | (wBDF<<8) | (bReg & 0xFC)));
    return (UINT16)(0xCFC+(bReg & 3));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmReadPCIConfig
//
// Description: This routine reads from the PCI configuration space register
//              the value can be typecasted to 8bits - 32bits
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//
// Output:      Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
NonSmmReadPCIConfig(UINT16 BusDevFunc, UINT8 Register)
{
    UINT32 data;
    NonSmmDwordWriteIO(0xCF8, (UINT32)(0x80000000 | (BusDevFunc<<8) | (Register & 0xFC)));
    data = NonSmmDwordReadIO(0xCFC);
    return (data >> ((Register & 3) << 3)); // Adjust uneven register

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmByteWritePCIConfig
//
// Description: This routine writes a byte value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//              Value      - Value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value)
{
    UINT16 wIOAddr;
    wIOAddr = NonSmmWritePCIConfig(BusDevFunc, Register);
    NonSmmByteWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWordWritePCIConfig
//
// Description: This routine writes a word value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to write
//              Value      - Value to write
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmWordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value)
{
    UINT16 wIOAddr;
    wIOAddr = NonSmmWritePCIConfig(BusDevFunc, Register);
    NonSmmWordWriteIO (wIOAddr, Value);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmDwordWritePCIConfig
//
// Description: This routine writes a Dword value to the PCI configuration
//              register space
//
// Input:       BusDevFunc - Bus, device & function number of the PCI device
//              Register   - Register offset to read
//              Value      - Value to write
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void
NonSmmDwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value)
{
    UINT16 wIOAddr;
    wIOAddr = NonSmmWritePCIConfig(BusDevFunc, Register);
    NonSmmDwordWriteIO (wIOAddr, Value);
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
