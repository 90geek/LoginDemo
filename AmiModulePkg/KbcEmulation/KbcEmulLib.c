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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulLib.c 4     2/10/11 1:00a Rameshr $
//
// $Revision: 4 $
//
// $Date: 2/10/11 1:00a $
//
//****************************************************************************

//<AMI_FHDR_START>
//**********************************************************************
// Name:        KbcEmullib.c
//
// Description: KBC emulation lib file that used in other files
//
//**********************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "KbcEmulLib.h"

UINT16  WritePCIConfig(UINT16, UINT8);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteReadIO
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
ByteReadIO(UINT16 wIOAddr)
{
    UINT8 value;
    gSmst1->SmmIo.Io.Read(&gSmst1->SmmIo, SMM_IO_UINT8, (UINT64)wIOAddr, 1, &value);
    return value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteWriteIO
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
ByteWriteIO (UINT16 wIOAddr, UINT8 bValue)
{
	gSmst1->SmmIo.Io.Write(&gSmst1->SmmIo, SMM_IO_UINT8, (UINT64)wIOAddr, 1, &bValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordReadIO
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
WordReadIO(UINT16 wIOAddr)
{
    UINT16 value;
    gSmst1->SmmIo.Io.Read(&gSmst1->SmmIo, SMM_IO_UINT16, (UINT64)wIOAddr, 1, &value);
    return  value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordWriteIO
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
WordWriteIO (UINT16 wIOAddr, UINT16 wValue)
{
	gSmst1->SmmIo.Io.Write(&gSmst1->SmmIo, SMM_IO_UINT16, (UINT64)wIOAddr, 1, &wValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordReadIO
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
DwordReadIO(UINT16 wIOAddr)
{
    UINT32  value;
    gSmst1->SmmIo.Io.Read(&gSmst1->SmmIo, SMM_IO_UINT32, (UINT64)wIOAddr, 1, &value);
    return  value;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordWriteIO
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
DwordWriteIO(UINT16 wIOAddr, UINT32 dValue)
{
	gSmst1->SmmIo.Io.Write(&gSmst1->SmmIo, SMM_IO_UINT32, (UINT64)wIOAddr, 1, &dValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadPCIConfig
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
ReadPCIConfig(UINT16 BusDevFunc, UINT8 Register)
{
    UINT32 data;
    DwordWriteIO(0xCF8, (UINT32)(0x80000000 | (BusDevFunc<<8) | (Register & 0xFC)));
    data = DwordReadIO(0xCFC);
    return (data >> ((Register & 3) << 3)); // Adjust uneven register

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteWritePCIConfig
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
ByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    ByteWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordWritePCIConfig
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
WordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    WordWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordWritePCIConfig
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
DwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    DwordWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WritePCIConfig
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
WritePCIConfig(UINT16 wBDF, UINT8 bReg)
{
    DwordWriteIO(0xCF8, (UINT32)(0x80000000 | (wBDF<<8) | (bReg & 0xFC)));
    return (UINT16)(0xCFC+(bReg & 3));
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
