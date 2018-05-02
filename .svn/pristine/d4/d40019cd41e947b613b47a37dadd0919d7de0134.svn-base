//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file Elib.c
    AMI USB MEM/IO/PCI access routines

**/

#include "AmiDef.h"
#include "UsbDef.h"

extern  USB_GLOBAL_DATA         *gUsbData;
//extern  EFI_SMM_SYSTEM_TABLE    *gSmst;

UINT8   ByteReadIO(UINT16);
UINT16  WritePCIConfig(UINT16, UINT8);

/**
    This routine delays for specified number of micro seconds

    @param Usec      Amount of delay (count in 1 microsec)

    @retval VOID

**/

VOID 
FixedDelay(
    UINTN           Usec                           
 )
{
#if USB_RUNTIME_DRIVER_IN_SMM
    UINTN   Counter, i;
    UINT32  Data32, PrevData;

    Counter = Usec * 3;
    Counter += Usec / 2;
    Counter += (Usec * 2) / 25;

    //
    // Call WaitForTick for Counter + 1 ticks to try to guarantee Counter tick
    // periods, thus attempting to ensure Microseconds of stall time.
    //
    if (Counter != 0) {

        PrevData = IoRead32(PM_BASE_ADDRESS + 8);
        for (i=0; i < Counter; ) {
            Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
            if (Data32 < PrevData) {        // Reset if there is a overlap
                PrevData=Data32;
                continue;
            }
            i += (Data32 - PrevData);        
            PrevData = Data32;
        }
    }
#else
	pBS->Stall(Usec);
#endif
    return;
}

/**
    This routine reads a DWORD from the specified Memory Address

    @param 
        BaseAddr   - Memory address to read
        Offset     - Offset of BaseAddr

    @retval Value read

**/

UINT32
DwordReadMem(
    UINTN   BaseAddr, 
    UINT16  Offset
)
{
    return *(volatile UINT32*)(UINTN)(BaseAddr + Offset);
}


/**
    This routine writes a DWORD to a specified Memory Address

    @param 
        BaseAddr   - Memory address to write
        Offset     - Offset of BaseAddr
        Value      - Data to write

**/

VOID
DwordWriteMem(
    UINTN   BaseAddr, 
    UINT16  Offset, 
    UINT32  Value
)
{
    *(volatile UINT32*)(UINTN)(BaseAddr + Offset) = Value;
}


/**
    This routine resets the specified bits at specified memory address

    @param 
        BaseAddr   - Memory address to read
        Offset     - Offset of BaseAddr
        Value      - Data to reset

    @retval VOID

**/

VOID
DwordResetMem(
    UINTN   BaseAddr, 
    UINT16  Offset, 
    UINT32  Value
)
{
    UINT32 Data = DwordReadMem(BaseAddr, Offset);
    
    Data &= ~Value;
    DwordWriteMem(BaseAddr, Offset, Data);
}


/**
    This routine sets the specified bits at specified memory address

    @param 
        BaseAddr   - Memory address to read
        Offset     - Offset of BaseAddr
        Value      - Data to set

    @retval VOID

**/

VOID
DwordSetMem(
    UINTN   BaseAddr, 
    UINT16  Offset, 
    UINT32  Value
)
{
    UINT32 Data = DwordReadMem(BaseAddr, Offset);
    
    Data |= Value;
    DwordWriteMem(BaseAddr, Offset, Data);
}


/**
    This routine reads a Byte from the specified IO address

    @param wIOAddr     I/O address to read

    @retval Value read

**/

UINT8
ByteReadIO(UINT16 wIOAddr)
{
//    UINT8 value;
//    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT8, (UINT64)wIOAddr, 1, &value);
//    return value;
    return IoRead8(wIOAddr);
}


/**
    This routine writes a byte to the specified IO address

    @param wIOAddr     I/O address to write
        bValue      Byte value to write

    @retval VOID

**/

VOID
ByteWriteIO (UINT16 wIOAddr, UINT8 bValue)
{
//    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT8, (UINT64)wIOAddr, 1, &bValue);
    IoWrite8(wIOAddr, bValue);
}


/**
    This routine reads a Word from the specified IO address

    @param wIOAddr     I/O address to read

    @retval Value read

**/

UINT16
WordReadIO(UINT16 wIOAddr)
{
//    UINT16 value;
//    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT16, (UINT64)wIOAddr, 1, &value);
//    return  value;
    return IoRead16(wIOAddr);
}


/**
    This routine writes a word to the specified IO address

    @param wIOAddr     I/O address to write
        wValue      Word value to write

    @retval VOID

**/

VOID
WordWriteIO (UINT16 wIOAddr, UINT16 wValue)
{
//    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT16, (UINT64)wIOAddr, 1, &wValue);
    IoWrite16(wIOAddr, wValue);
}


/**
    This routine reads a dword from the specified IO address

    @param wIOAddr     I/O address to read

    @retval Value read

**/

UINT32
DwordReadIO(UINT16 wIOAddr)
{
//    UINT32  value;
//    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT32, (UINT64)wIOAddr, 1, &value);
//    return  value;
    return IoRead32(wIOAddr);
}


/**
    This routine writes a double word to the specified IO address

    @param wIOAddr     I/O address to write
        dValue      Double word value to write

    @retval VOID

**/

VOID
DwordWriteIO(UINT16 wIOAddr, UINT32 dValue)
{
//    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT32, (UINT64)wIOAddr, 1, &dValue);
    IoWrite32(wIOAddr, dValue);
}


/**
    This routine reads from the PCI configuration space register
    the value can be typecasted to 8bits - 32bits

    @param BusDevFunc - Bus, device & function number of the PCI device
        Register   - Register offset to read

    @retval Value read

**/

UINT32
ReadPCIConfig(UINT16 BusDevFunc, UINT8 Register)
{
    UINT32  Data;
    UINTN   Address = (gUsbData->PciExpressBaseAddress + (UINTN)(BusDevFunc << 12 | Register));

    Data = *(volatile UINT32*)(Address);
   
    return Data;
}

/**
    This routine writes a byte value to the PCI configuration
    register space

    @param BusDevFunc - Bus, device & function number of the PCI device
        Register   - Register offset to read
        Value      - Value to write

**/

VOID
ByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value)
{
    UINTN   Address = (gUsbData->PciExpressBaseAddress + (UINTN)(BusDevFunc << 12 | Register));

    *(volatile UINT8*)(Address) = Value;
}

/**
    This routine writes a byte value to the PCI configuration
    register space

    @param BusDevFunc - Bus, device & function number of the PCI device
        Register   - Register offset to read
        Value      - Value to write

**/

VOID
WordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value)
{
    UINTN   Address = (gUsbData->PciExpressBaseAddress + (UINTN)(BusDevFunc << 12 | Register));

    *(volatile UINT16*)(Address) = Value;
}

/**
    This routine writes a Dword value to the PCI configuration
    register space

    @param BusDevFunc - Bus, device & function number of the PCI device
        Register   - Register offset to read
        Value      - Value to write

**/

VOID
DwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value)
{
    UINTN   Address = (gUsbData->PciExpressBaseAddress + (UINTN)(BusDevFunc << 12 | Register));

    *(volatile UINT32*)(Address) = Value;
}

/**
    This function opens PCI configuration for a given register

    @param wBDF  - Bus, device and function number
        bReg  - Register number to read

    @retval IO register to write the value

**/

UINT16
WritePCIConfig(UINT16 wBDF, UINT8 bReg)
{
    DwordWriteIO(0xCF8, (UINT32)(0x80000000 | (wBDF<<8) | (bReg & 0xFC)));
    return (UINT16)(0xCFC+(bReg & 3));
}

UINT32
HcReadPciReg(
    HC_STRUC	*HcStruc,
    UINT32		Offset
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    return ReadPCIConfig(HcStruc->wBusDevFuncNum, Offset);
#else
    EFI_STATUS	            Status;
	UINT32                  Data = 0;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return Data;
#endif
}

VOID
HcWritePciReg(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT32      Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    DwordWritePCIConfig(HcStruc->wBusDevFuncNum, Offset, Data);
    return;
#else
	EFI_STATUS              Status;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Pci.Write(PciIo, EfiPciIoWidthUint32, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return;
#endif
}

VOID
HcWordWritePciReg(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT16      Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    WordWritePCIConfig(HcStruc->wBusDevFuncNum, Offset, Data);
    return;
#else
    EFI_STATUS	            Status;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Pci.Write(PciIo, EfiPciIoWidthUint16, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return;
#endif
}

UINT32
HcReadHcMem(
    HC_STRUC    *HcStruc,
    UINT32      Offset
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    return DwordReadMem(HcStruc->BaseAddress, Offset);
#else
    EFI_STATUS              Status;
    UINT32                  Data = 0;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

	Status = PciIo->Mem.Read(PciIo, EfiPciIoWidthUint32, 0, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return Data;
#endif
}

VOID
HcWriteHcMem(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT32      Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    DwordWriteMem(HcStruc->BaseAddress, Offset, Data);
    return;
#else
    EFI_STATUS	            Status;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Mem.Write(PciIo, EfiPciIoWidthUint32, 0, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return;
#endif
}

VOID
HcSetHcMem(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT32      Bit
)
{
	UINT32  Data;

	Data = HcReadHcMem(HcStruc, Offset) | Bit;
	HcWriteHcMem(HcStruc, Offset, Data);
    return;
}

VOID
HcClearHcMem(
	HC_STRUC	*HcStruc,
	UINT32		Offset,
	UINT32		Bit
)
{
    UINT32  Data;

    Data = HcReadHcMem(HcStruc, Offset) & ~Bit;
    HcWriteHcMem(HcStruc, Offset, Data);
    return;
}

UINT32
HcReadOpReg(
    HC_STRUC    *HcStruc,
    UINT32      Offset
)
{
    return HcReadHcMem(HcStruc, HcStruc->bOpRegOffset + Offset);
}

VOID
HcWriteOpReg(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT32      Data
)
{
    HcWriteHcMem(HcStruc, HcStruc->bOpRegOffset + Offset, Data);
    return;
}

VOID
HcSetOpReg(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT32      Bit
)
{
    UINT32  Data;

    Data = HcReadOpReg(HcStruc, Offset) | Bit;
    HcWriteOpReg(HcStruc, Offset, Data);
    return;
}

VOID
HcClearOpReg(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT32      Bit
)
{
    UINT32  Data;

    Data = HcReadOpReg(HcStruc, Offset) & ~Bit;
    HcWriteOpReg(HcStruc, Offset, Data);
	return;
}

UINT8
HcByteReadHcIo(
    HC_STRUC    *HcStruc,
    UINT32      Offset
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    return ByteReadIO((UINT16)HcStruc->BaseAddress + Offset);
#else
    EFI_STATUS              Status;
    UINT8                   Data = 0;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Io.Read(PciIo, EfiPciIoWidthUint8, 4, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return Data;
#endif
}

VOID
HcByteWriteHcIo(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT8       Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    ByteWriteIO((UINT16)HcStruc->BaseAddress + Offset, Data);
    return;
#else
    EFI_STATUS	            Status;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Io.Write(PciIo, EfiPciIoWidthUint8, 4, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return;
#endif
}

UINT16
HcWordReadHcIo(
    HC_STRUC    *HcStruc,
    UINT32      Offset
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    return WordReadIO((UINT16)HcStruc->BaseAddress + Offset);
#else
    EFI_STATUS              Status;
    UINT16                  Data = 0;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Io.Read(PciIo, EfiPciIoWidthUint16, 4, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return Data;
#endif
}

VOID
HcWordWriteHcIo(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT16      Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    WordWriteIO((UINT16)HcStruc->BaseAddress + Offset, Data);
    return;
#else
    EFI_STATUS	            Status;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Io.Write(PciIo, EfiPciIoWidthUint16, 4, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return;
#endif
}

UINT32
HcDwordReadHcIo(
    HC_STRUC    *HcStruc,
    UINT32      Offset
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    return DwordReadIO((UINT16)HcStruc->BaseAddress + Offset);
#else
    EFI_STATUS              Status;
    UINT32                  Data = 0;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Io.Read(PciIo, EfiPciIoWidthUint32, 4, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return Data;
#endif
}

VOID
HcDwordWriteHcIo(
    HC_STRUC    *HcStruc,
    UINT32      Offset,
    UINT32      Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    DwordWriteIO((UINT16)HcStruc->BaseAddress + Offset, Data);
    return;
#else
    EFI_STATUS              Status;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Io.Write(PciIo, EfiPciIoWidthUint32, 4, Offset, 1, &Data);
    ASSERT_EFI_ERROR(Status);
    return;
#endif
}


UINT8
HcDmaMap(
    HC_STRUC    *HcStruc,
    UINT8       Direction,
    UINT8       *BufferAddr,
    UINT32      BufferSize,
    UINT8       **PhyAddr,
    VOID        **Mapping
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    *PhyAddr = BufferAddr;
#else
    EFI_PCI_IO_PROTOCOL_OPERATION       Operation;
    EFI_PHYSICAL_ADDRESS                Addr;
    EFI_STATUS                          Status;
    UINTN                               Bytes = BufferSize;
    EFI_PCI_IO_PROTOCOL	                *PciIo = HcStruc->PciIo;

    if (Direction & BIT7) {
        Operation = EfiPciIoOperationBusMasterWrite;
    } else {
        Operation = EfiPciIoOperationBusMasterRead;
    }

	Status = PciIo->Map(PciIo, Operation, BufferAddr, &Bytes, &Addr, Mapping);
    
	if (EFI_ERROR(Status) || Bytes != BufferSize) {
        *PhyAddr = BufferAddr;
		return USB_ERROR;
	}

	*PhyAddr = (UINT8*)Addr;
#endif
	return USB_SUCCESS;
}

UINT8
HcDmaUnmap(
	HC_STRUC	*HcStruc,
	VOID		*Mapping
)
{
#if !USB_RUNTIME_DRIVER_IN_SMM

    EFI_STATUS              Status;
    EFI_PCI_IO_PROTOCOL	    *PciIo = HcStruc->PciIo;

    Status = PciIo->Unmap(PciIo, Mapping);
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }
#endif
    return USB_SUCCESS;
}

/**
    This routine produces a sound on the internal PC speaker

    @param bFreq -     Sound frequency
        wDuration - Sound duration in 15 microsecond units
        fpHCStruc - Pointer to HCStruc

    @retval VOID

**/

VOID
SpeakerBeep (UINT8 bFreq, UINT16 wDuration, HC_STRUC*   fpHCStruc)
{
#if USB_BEEP_ENABLE
    UINT8   bValue;
    if(gUsbData->dUSBStateFlag & USB_FLAG_ENABLE_BEEP_MESSAGE) {
        ByteWriteIO((UINT8)0x43, (UINT8)0xB6);
        ByteWriteIO((UINT8)0x42, (UINT8)bFreq);
        ByteWriteIO((UINT8)0x42, (UINT8)bFreq);
        bValue = ByteReadIO((UINT8)0x61);
        ByteWriteIO((UINT8)0x61, (UINT8)(bValue | 03));
        FixedDelay((UINTN)wDuration * 15);
        ByteWriteIO((UINT8)0x61, (UINT8)(bValue));
    }
#endif
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
