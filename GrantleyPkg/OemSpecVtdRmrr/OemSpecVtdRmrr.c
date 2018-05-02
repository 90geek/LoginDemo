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
// $Header:  $
//
// $Revision:  $
//
// $Date:  $
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  OemSpecVtdRmrr.c
//
// Description:
//  OemSpecVtdRmrr library implementation
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
#pragma optimize( "", off )

#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>

#include <Acpi/DMARemappingReportingTable.h>

#include <Protocol/DevicePath.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/DmaRemap.h>
#include <Protocol/OemVtdRmrrProtocol.h>
#include <Protocol/PciIo.h>
#include <Protocol/IioUds.h>

#include "HostMemoryReportProtocol.h"

#include "OemSpecVtdRmrr.h"

//----------------------------------------------------------------------

//
// Module global values
//
static EFI_GUID gEfiHostMemoryReportProtocolGuid = EFI_HOST_MEMORY_REPORT_PROTOCOL_GUID;

DMAR_RMRR           *gRmrr = NULL;
DEVICE_SCOPE        *gDevScope = NULL;
PCI_NODE            *gPciNode = NULL;

UINTN               gRmrrCount = 0;
UINTN               gDevScopeCount = 0;
UINTN               gPciNodeCount = 0;

//
// Function implementations
//
EFI_STATUS
OemSpecVtdRmrrInsertRmrr (
  IN  EFI_DMA_REMAP_PROTOCOL    *DmaRemap )
{
    EFI_STATUS          Status;
    UINTN               Index;

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "OemSpecVtdRmrrInsertRmrr entered  \n"));

    //
    // Insert RMRR table
    //
    for ( Index=0; Index < gRmrrCount; Index++ ) {
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "Insert RMRR table..\n"));
        Status = DmaRemap->InsertDmaRemap (DmaRemap, RmrrType, &gRmrr[Index]);
        DEBUG ((EFI_D_ERROR, "Index: %x  InsertDmaRemap Status: %r \n", Index, Status));
    }
    //
    // Free the memory
    //
    if ( gRmrr ) {
        gBS->FreePool (gRmrr);
    }
    if ( gDevScope ) {
        gBS->FreePool (gDevScope);
    }
    if ( gPciNode ) {
        gBS->FreePool(gPciNode);
    }

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "OemSpecVtdRmrrInsertRmrr exiting  \n"));

    return EFI_SUCCESS;
}

EFI_STATUS
GetOemSpecDevicePath (
  IN  UINTN                     ControllerBusNumber,
  IN  UINTN                     ControllerDeviceNumber,
  IN  UINTN                     ControllerFunctionNumber,
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath )
{
    UINTN                       HandleCount;
    EFI_HANDLE                  *HandleBuffer;
    UINTN                       Index;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    UINTN                       SegmentNumber;
    UINTN                       BusNumber;
    UINTN                       DeviceNumber;
    UINTN                       FunctionNumber;
    EFI_STATUS                  Status;

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "FillPciPath entered  \n"));

    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "ControllerBusNumber: %x \n", ControllerBusNumber));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "ControllerDeviceNumber: %x \n", ControllerDeviceNumber));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "ControllerFunctionNumber: %x \n", ControllerFunctionNumber));

    //
    // Locate all PciIo handles
    //
    Status = gBS->LocateHandleBuffer (
                    ByProtocol,
                    &gEfiPciIoProtocolGuid,
                    NULL,
                    &HandleCount,
                    &HandleBuffer );
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "LocateHandleBuffer gEfiPciIoProtocolGuid. Status: %r \n", Status));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "HandleCount: %X \n", HandleCount));

    if ( EFI_ERROR(Status) ) {
        DEBUG((EFI_D_ERROR, "LocateHandleBuffer gEfiPciIoProtocolGuid. Status: %r \n", Status));
        return Status;
    }

    for (Index = 0; Index < HandleCount; Index ++) {
        //
        // Get the instance of Protocol
        //
        Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiPciIoProtocolGuid,
                    &PciIo );
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "HandleProtocol gEfiPciIoProtocolGuid. Status: %r \n", Status));
        if ( EFI_ERROR(Status) ) {
            DEBUG((EFI_D_ERROR, "HandleProtocol gEfiPciIoProtocolGuid. Status: %r \n", Status));
            break;
        }

        //
        // Get PCI Io Location
        //
        Status = PciIo->GetLocation ( 
                            PciIo,
                            &SegmentNumber,
                            &BusNumber,
                            &DeviceNumber,
                            &FunctionNumber );
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "PciIo->GetLocation GetLocation. Status: %r \n", Status));
        if ( EFI_ERROR(Status) ) {
            DEBUG((EFI_D_ERROR, "PciIo->GetLocation GetLocation. Status: %r \n", Status));
            break;
        }

        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "SegmentNumber: %x \n", SegmentNumber));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "BusNumber: %x \n", BusNumber));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "DeviceNumber: %x \n", DeviceNumber));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "FunctionNumber: %x \n", FunctionNumber));

        //
        // Get the PciIo handle by comparing Bus, Device and funtion numbers
        //
        if ( (BusNumber == ControllerBusNumber) && \
                (DeviceNumber == ControllerDeviceNumber) && \
                (FunctionNumber == ControllerFunctionNumber) ) {
            //
            // Get the device path
            //
            Status = gBS->HandleProtocol (
                            HandleBuffer[Index],
                            &gEfiDevicePathProtocolGuid,
                            DevicePath ); 
            OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "HandleProtocol gEfiDevicePathProtocolGuid. Status: %r \n", Status));
            if ( EFI_ERROR(Status) ) {
                DEBUG((EFI_D_ERROR, "HandleProtocol gEfiDevicePathProtocolGuid. Status: %r \n", Status));
            }
            break;
        }
    } // end of for loop

    //
    // Free the handle buffer
    //
    gBS->FreePool(HandleBuffer);

    if ( (Index == HandleCount) || EFI_ERROR(Status) ) {
        Status = EFI_NOT_FOUND;
        DEBUG((EFI_D_ERROR, "Error in getting the Device path. Status: %r \n", Status));
        return Status;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
GetBaseBusNumber (
  IN  UINTN    ControllerBusNumber,
  IN  UINT8    *BaseBusNumber )
{
    EFI_IIO_UDS_PROTOCOL    *IohUds;
    UINT8                   SocketNum;
    EFI_STATUS              Status;

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "GetBaseBusNumber entered  \n"));

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "ControllerBusNumber: %x  \n", ControllerBusNumber));

    //
    // Get the base bus number of the root bridge
    //
    Status = gBS->LocateProtocol(
                    &gEfiIioUdsProtocolGuid,
                    NULL,
                    &IohUds );
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "LocateProtocol gEfiIioUdsProtocolGuid. Status: %r \n", Status));
    if ( EFI_ERROR(Status) ) {
        DEBUG((EFI_D_ERROR, "gEfiIioUdsProtocolGuid. Status: %r \n", Status));
        return Status;
    }

    for ( SocketNum = 0; SocketNum < IohUds->IioUdsPtr->SystemStatus.numCpus; SocketNum++ ) {
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "IohUds->IioUdsPtr->PlatformData.IIO_resource[SocketNum].BusBase: %x \n", IohUds->IioUdsPtr->PlatformData.IIO_resource[SocketNum].BusBase));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "IohUds->IioUdsPtr->PlatformData.IIO_resource[SocketNum].BusLimit: %x \n", IohUds->IioUdsPtr->PlatformData.IIO_resource[SocketNum].BusLimit));
        if ( ControllerBusNumber >= IohUds->IioUdsPtr->PlatformData.IIO_resource[SocketNum].BusBase && \
                ControllerBusNumber <= IohUds->IioUdsPtr->PlatformData.IIO_resource[SocketNum].BusLimit ) {
            *BaseBusNumber = IohUds->IioUdsPtr->PlatformData.IIO_resource[SocketNum].BusBase;
            DEBUG ((EFI_D_ERROR, "BaseBusNumber: %x  \n", *BaseBusNumber));
            return EFI_SUCCESS;
        }
    }

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "GetBaseBusNumber exiting  \n"));

    return EFI_UNSUPPORTED;
}

EFI_STATUS
FillRmrrStructure (
  IN  EFI_HOST_MEMORY_REPORT_INFO   HostMemoryInfo )
{
    EFI_STATUS                      Status;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath = NULL;
    EFI_DEVICE_PATH_PROTOCOL        *Node = NULL;
    UINT8                           StartBusNumber = 0;

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "FillRmrrStructure Entering  \n"));

    //
    // Get the Base bus number
    //
    Status = GetBaseBusNumber (HostMemoryInfo.Bus, &StartBusNumber);
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "GetBaseBusNumber. Status: %r \n", Status));
    if ( EFI_ERROR(Status) ) {
        DEBUG((EFI_D_ERROR, "GetBaseBusNumber. Status: %r \n", Status));
        return Status;
    }

    DEBUG((EFI_D_ERROR, "StartBusNumber: %X \n", StartBusNumber));

    //
    // Get Device path
    //
    Status = GetOemSpecDevicePath (
                HostMemoryInfo.Bus,
                HostMemoryInfo.Device,
                HostMemoryInfo.Func,
                &DevicePath );
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "GetOemSpecDevicePath. Status: %r DevicePath: %lx \n", Status, DevicePath));
    if ( EFI_ERROR(Status) ) {
        DEBUG((EFI_D_ERROR, "GetOemSpecDevicePath. Status: %r \n", Status));
        return Status;
    }

    //
    // Fill RMRR Structure
    //
    gRmrr[gRmrrCount].Signature         = RMRR_SIGNATURE;
    gRmrr[gRmrrCount].SegmentNumber     = SEGMENT0;
    gRmrr[gRmrrCount].DeviceScopeNumber = 00;
    gRmrr[gRmrrCount].RsvdMemBase       = HostMemoryInfo.HostMemoryAddress;
    gRmrr[gRmrrCount].RsvdMemLimit      = (HostMemoryInfo.HostMemoryAddress+HostMemoryInfo.Size-1);
    gRmrr[gRmrrCount].DeviceScope       = &gDevScope[gDevScopeCount];
    gRmrr[gRmrrCount].DeviceScopeNumber++;

    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gRmrr[%d].Signature: %lX \n", gRmrrCount, gRmrr[gRmrrCount].Signature));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gRmrr[%d].SegmentNumber: %lX \n", gRmrrCount, gRmrr[gRmrrCount].SegmentNumber));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gRmrr[%d].DeviceScopeNumber: %lX \n", gRmrrCount, gRmrr[gRmrrCount].DeviceScopeNumber));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gRmrr[%d].RsvdMemBase: %lX \n", gRmrrCount, gRmrr[gRmrrCount].RsvdMemBase));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gRmrr[%d].RsvdMemLimit: %lX \n", gRmrrCount, gRmrr[gRmrrCount].RsvdMemLimit));

    //
    // Increment RMRR count
    //
    gRmrrCount++;

    //
    // Fill Device scope Structure
    //
    gDevScope[gDevScopeCount].DeviceType       = EFI_ACPI_DEVICE_SCOPE_ENTRY_TYPE_ENDPOINT;
    gDevScope[gDevScopeCount].EnumerationID    = 00;
    gDevScope[gDevScopeCount].StartBusNumber    = StartBusNumber;
    gDevScope[gDevScopeCount].PciNode          = &gPciNode[gPciNodeCount];

    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gDevScope[%d].DeviceType: %X \n", gDevScopeCount, gDevScope[gDevScopeCount].DeviceType));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gDevScope[%d].EnumerationID: %X \n", gDevScopeCount, gDevScope[gDevScopeCount].EnumerationID));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gDevScope[%d].StartBusNumber: %X \n", gDevScopeCount, gDevScope[gDevScopeCount].StartBusNumber));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gDevScope[%d].PciNode: %X \n", gDevScopeCount, gDevScope[gDevScopeCount].PciNode));

    //
    // Increment Device Scope count
    //
    gDevScopeCount++;

    //
    // Parse device path and Fill Pci Nodes
    // First node contains ACPI device path. Skip the first node.
    //
    Node = NextDevicePathNode (DevicePath);

    while ( !IsDevicePathEnd (Node) ) {

        gPciNode[gPciNodeCount].Device          = ((PCI_DEVICE_PATH *)Node)->Device;
        gPciNode[gPciNodeCount].Function        = ((PCI_DEVICE_PATH *)Node)->Function;

        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gPciNode[%d].Device: %X \n", gPciNodeCount, gPciNode[gPciNodeCount].Device));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gPciNode[%d].Function: %X \n", gPciNodeCount, gPciNode[gPciNodeCount].Function));

        //
        // Increment Pci Node count
        //
        gPciNodeCount++;

        //
        // Next device path node
        //
        Node = NextDevicePathNode (Node);
    }

    //
    // Fill Pci End Node Structure
    //
    gPciNode[gPciNodeCount].Device    = (UINT8) -1;
    gPciNode[gPciNodeCount].Function  = (UINT8) -1;

    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gPciNode[%d].Device: %X \n", gPciNodeCount, gPciNode[gPciNodeCount].Device));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "gPciNode[%d].Function: %X \n", gPciNodeCount, gPciNode[gPciNodeCount].Function));

    //
    // Increment Pci Node count
    //
    gPciNodeCount++;

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "FillRmrrStructure exiting  \n"));

    return EFI_SUCCESS;
}

EFI_STATUS
OemSpecVtdRmrrCollectLegacyInfo (
  VOID )
{
    EFI_STATUS                              Status;
    EFI_HOST_MEMORY_REPORT_INFO             HostMemoryInfo;
    UINT16                                  HandleCount;
    UINT16                                  Index;
    EFI_LEGACY_BIOS_PROTOCOL                *LegacyBios=NULL;
    BOOLEAN                                 ReturnSuccess;
    UINT8                                   BaseBusNumber=0;
    BOOLEAN                                 Int86Status;
    EFI_IA32_REGISTER_SET                   RegSet;
    UINTN                                   SizeinPages=0;

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "OemSpecVtdRmrrCollectLegacyInfo entered  \n"));

    //
    // Locate gEfiLegacyBiosProtocolGuid protocol
    //
    Status = gBS->LocateProtocol (
                &gEfiLegacyBiosProtocolGuid,
                NULL,
                &LegacyBios );
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "LocateProtocol gEfiLegacyBiosProtocolGuid. Status: %r \n", Status));
    if ( EFI_ERROR(Status) ) {
        DEBUG((EFI_D_ERROR, "gEfiLegacyBiosProtocolGuid. Status: %r \n", Status));
        return Status;
    }

    ZeroMem (&RegSet, sizeof (EFI_IA32_REGISTER_SET));

    //
    // Get controller count
    //
    RegSet.H.AH = OEM_SPEC_FUNCTION_CODE;
    RegSet.H.AL = OemSpecGetControllerCount;
    RegSet.E.EDX = OEM_SPEC_FUNCTION_SIGNATURE;

    Int86Status = LegacyBios->Int86 (
                    LegacyBios, 
                    OEM_SPEC_INT_15H, 
                    &RegSet );
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "LegacyBios->Int86. OemSpecGetControllerCount Int86Status: %X \n", Int86Status));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.X.Flags.CF: %X \n", RegSet.X.Flags.CF));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.H.AH: %X \n", RegSet.H.AH));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.X.CX: %X \n", RegSet.X.CX));

    if ( Int86Status || RegSet.X.Flags.CF ) {
        DEBUG((EFI_D_ERROR, "OEM SPEC Function OemSpecGetControllerCount Status: %r \n", EFI_UNSUPPORTED));
        return EFI_UNSUPPORTED;
    }

    //
    // Fill Handle Count
    //
    HandleCount = RegSet.X.CX;

    //
    // Allocate memory
    //
    gRmrr = AllocateZeroPool(HandleCount* sizeof (DMAR_RMRR));
    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "AllocateZeroPool  gRmrr: %lx \n", gRmrr));
    if (gRmrr == NULL) {
        DEBUG ((EFI_D_ERROR, "Failed to allocate memory for gRmrr! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    gDevScope = AllocateZeroPool(HandleCount*sizeof (DEVICE_SCOPE));
    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "AllocateZeroPool  gDevScope: %lx \n", gDevScope));
    if (gRmrr == NULL) {
        DEBUG ((EFI_D_ERROR, "Failed to allocate memory for gDevScope! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    gPciNode = AllocateZeroPool(HandleCount*21*sizeof (PCI_NODE));
    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "AllocateZeroPool  gPciNode: %lx \n", gPciNode));
    if (gRmrr == NULL) {
        DEBUG ((EFI_D_ERROR, "Failed to allocate memory for gPciNode! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    for (Index = 0; Index < HandleCount; Index ++) {

        ZeroMem (&RegSet, sizeof (EFI_IA32_REGISTER_SET));

        //
        // Get Memory Request Size and BDF information
        //
        RegSet.H.AH = OEM_SPEC_FUNCTION_CODE;
        RegSet.H.AL = OemSpecGetMemoryReqBDFInfo;
        RegSet.E.EDX = OEM_SPEC_FUNCTION_SIGNATURE;
        RegSet.X.CX = Index;

        Int86Status = LegacyBios->Int86 (
                        LegacyBios, 
                        OEM_SPEC_INT_15H, 
                        &RegSet );
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "LegacyBios->Int86. OemSpecGetMemoryReqBDFInfo Int86Status: %X \n", Int86Status));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.X.Flags.CF: %X \n", RegSet.X.Flags.CF));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.H.AH: %X \n", RegSet.H.AH));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.X.CX: %X \n", RegSet.X.CX));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.E.EBX: %X \n", RegSet.E.EBX));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.E.ESI: %X \n", RegSet.E.ESI));

        if ( Int86Status || RegSet.X.Flags.CF ) {
            DEBUG((EFI_D_ERROR, "OEM SPEC Function OemSpecGetMemoryReqBDFInfo Status: %r \n", EFI_DEVICE_ERROR));
            continue;
        }

        ZeroMem (&HostMemoryInfo, sizeof (HostMemoryInfo));

        HostMemoryInfo.Bus = (RegSet.X.CX >>8) & 0xFF;
        HostMemoryInfo.Device = (RegSet.X.CX >>3) & 0x1F;
        HostMemoryInfo.Func = RegSet.X.CX & 0x7;

        HostMemoryInfo.Size =  (RegSet.E.EBX << 4)+ RegSet.E.ESI;
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.Size: %lX \n", HostMemoryInfo.Size));

        //
        // Allocate 32 bit memory for HOST
        //
        SizeinPages = EFI_SIZE_TO_PAGES(HostMemoryInfo.Size);
        DEBUG((EFI_D_ERROR, "SizeinPages: %lX \n", SizeinPages));

        HostMemoryInfo.HostMemoryAddress = 0xFFFFFFFF;
        Status = gBS->AllocatePages (
                        AllocateMaxAddress,
                        EfiRuntimeServicesData,
                        SizeinPages, 
                        &HostMemoryInfo.HostMemoryAddress);
        OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "gBS->AllocatePages  Status: %r \n", Status));
        if ( EFI_ERROR(Status) ) {
            DEBUG ((EFI_D_ERROR, "Failed to allocate memory for Host! \n"));
            continue;
        }

        DEBUG((EFI_D_ERROR, "HostMemoryInfo.HostMemoryAddress: %lX \n", HostMemoryInfo.HostMemoryAddress));
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.Bus: %X \n", HostMemoryInfo.Bus));
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.Device: %X \n", HostMemoryInfo.Device));
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.Func: %X \n", HostMemoryInfo.Func));

        ZeroMem (&RegSet, sizeof (EFI_IA32_REGISTER_SET));

        //
        // Set Memory
        //
        RegSet.H.AH = OEM_SPEC_FUNCTION_CODE;
        RegSet.H.AL = OemSpecSetMemory;
        RegSet.E.EDX = OEM_SPEC_FUNCTION_SIGNATURE;
        RegSet.X.CX = Index;

        RegSet.E.ESI =  (UINT32)HostMemoryInfo.HostMemoryAddress;
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.E.ESI: %X \n", RegSet.E.ESI));

        Int86Status = LegacyBios->Int86 (
                        LegacyBios, 
                        OEM_SPEC_INT_15H, 
                        &RegSet );
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "LegacyBios->Int86. OemSpecSetMemory Int86Status: %X \n", Int86Status));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.X.Flags.CF: %X \n", RegSet.X.Flags.CF));
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "RegSet.H.AH: %X \n", RegSet.H.AH));

        if ( Int86Status || RegSet.X.Flags.CF ) {
            DEBUG((EFI_D_ERROR, "OEM SPEC Function OemSpecSetMemory Status: %r \n", EFI_DEVICE_ERROR));
            continue;
        }

        //
        // Fill the RMRR structure
        //
        Status = FillRmrrStructure ( HostMemoryInfo );
        OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "FillRmrrStructure  Status: %r \n", Status));
        if ( EFI_ERROR(Status) ) {
            DEBUG ((EFI_D_ERROR, "FillRmrrStructure  Status: %r \n", Status));
            continue;
        }

        //
        // If control comes here, return success
        //
        ReturnSuccess = TRUE;

    }

    DEBUG ((EFI_D_ERROR, "ReturnSuccess: %x \n", ReturnSuccess));

    if ( ReturnSuccess ) {
        Status = EFI_SUCCESS;
    } else {
        //
        // Free the memory
        //
        if ( gRmrr ) {
            gBS->FreePool (gRmrr);
        }
        if ( gDevScope ) {
            gBS->FreePool (gDevScope);
        }
        if ( gPciNode ) {
            gBS->FreePool(gPciNode);
        }
        Status = EFI_UNSUPPORTED;
    }

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "OemSpecVtdRmrrCollectLegacyInfo exiting  Status: %r \n", Status));

    return Status;
}

EFI_STATUS
OemSpecVtdRmrrCollectUefiInfo (
  VOID )
{
    EFI_STATUS                              Status;
    EFI_HOST_MEMORY_REPORT_PROTOCOL         *HostMemoryReport = NULL;
    EFI_HOST_MEMORY_REPORT_INFO             HostMemoryInfo;
    UINTN                                   HandleCount;
    EFI_HANDLE                              *HandleBuffer;
    UINTN                                   Index;
    BOOLEAN                                 ReturnSuccess = FALSE;

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "OemSpecVtdRmrrCollectUefiInfo entered  \n"));

    //
    // Locate all instances of HostMemoryReport protocol
    //
    Status = gBS->LocateHandleBuffer (
                 ByProtocol,
                 &gEfiHostMemoryReportProtocolGuid,
                 NULL,
                 &HandleCount,
                 &HandleBuffer );
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "LocateHandleBuffer gEfiHostMemoryReportProtocolGuid. Status: %r \n", Status));
    OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "HandleCount: %X \n", HandleCount));

    if ( EFI_ERROR(Status) ) {
        DEBUG((EFI_D_ERROR, "LocateHandleBuffer gEfiHostMemoryReportProtocolGuid. Status: %r \n", Status));
        return Status;
    }

    //
    // Allocate memory
    //
    gRmrr = AllocateZeroPool(HandleCount* sizeof (DMAR_RMRR));
    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "AllocateZeroPool  gRmrr: %lx \n", gRmrr));
    if (gRmrr == NULL) {
        OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "Failed to allocate memory for gRmrr! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    gDevScope = AllocateZeroPool(HandleCount*sizeof (DEVICE_SCOPE));
    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "AllocateZeroPool  gDevScope: %lx \n", gDevScope));
    if (gRmrr == NULL) {
        OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "Failed to allocate memory for gDevScope! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    gPciNode = AllocateZeroPool(HandleCount*21*sizeof (PCI_NODE));
    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "AllocateZeroPool  gPciNode: %lx \n", gPciNode));
    if (gRmrr == NULL) {
        OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "Failed to allocate memory for gPciNode! \n"));
        return EFI_OUT_OF_RESOURCES;
    }

    for (Index = 0; Index < HandleCount; Index ++) {
        //
        // Get the instance of Protocol
        //
        Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiHostMemoryReportProtocolGuid,
                    &HostMemoryReport );
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "HandleProtocol gEfiHostMemoryReportProtocolGuid. Status: %r \n", Status));
        if ( EFI_ERROR(Status) ) {
            DEBUG((EFI_D_ERROR, "HandleProtocol gEfiHostMemoryReportProtocolGuid. Status: %r \n", Status));
            continue;
        }

        ZeroMem (&HostMemoryInfo, sizeof (HostMemoryInfo));

        //
        // Get Host Information
        //
        Status = HostMemoryReport->GetInfo (
                    HostMemoryReport,
                    &HostMemoryInfo );
        OEM_SPEC_RMMR_DEBUG((EFI_D_ERROR, "HostMemoryReport->GetInfo. Status: %r \n", Status));
        if ( EFI_ERROR(Status) ) {
            DEBUG((EFI_D_ERROR, "HostMemoryReport->GetInfo. Status: %r \n", Status));
            continue;
        }
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.HostMemoryAddress: %lX \n", HostMemoryInfo.HostMemoryAddress));
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.Size: %lX \n", HostMemoryInfo.Size));
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.Bus: %X \n", HostMemoryInfo.Bus));
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.Device: %X \n", HostMemoryInfo.Device));
        DEBUG((EFI_D_ERROR, "HostMemoryInfo.Func: %X \n", HostMemoryInfo.Func));

        //
        // Fill the RMRR structure
        //
        Status = FillRmrrStructure ( HostMemoryInfo );
        OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "FillRmrrStructure  Status: %r \n", Status));
        if ( EFI_ERROR(Status) ) {
            DEBUG ((EFI_D_ERROR, "FillRmrrStructure  Status: %r \n", Status));
            continue;
        }

        //
        // If control comes here, return success
        //
        ReturnSuccess = TRUE;

    }

    //
    // Free the handle buffer
    //
    gBS->FreePool(HandleBuffer);

    DEBUG ((EFI_D_ERROR, "ReturnSuccess: %x \n", ReturnSuccess));

    if ( ReturnSuccess ) {
        Status = EFI_SUCCESS;
    } else {
        //
        // Free the memory
        //
        if ( gRmrr ) {
            gBS->FreePool (gRmrr);
        }
        if ( gDevScope ) {
            gBS->FreePool (gDevScope);
        }
        if ( gPciNode ) {
            gBS->FreePool(gPciNode);
        }
        Status = EFI_UNSUPPORTED;
    }

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "OemSpecVtdRmrrCollectUefiInfo exiting  Status: %r \n", Status));

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name : OemSpecVtdRmrr
//
// Description:
//  OemSpecVtdRmrr Hook
//
// Input: 
//  IN OEM_VTD_RMRR_FUNC_NUMBER FuncNumber     - Function number
//  IN VOID *Ptr - NULL - OemVtdRmrrInsertRmrr function
//               - Pointer to DmaRemap protocol - OemVtdRmrrInsertRmrr function
//
// Output:
//   EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
OemSpecVtdRmrr (
  IN OEM_VTD_RMRR_FUNC_NUMBER FuncNumber,
  IN VOID                     *Ptr )
{
    EFI_STATUS      Status;

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "InitOemSpecVtdRmrr entered   FuncNumber: %x \n", FuncNumber));

    switch ( FuncNumber ) {
        case OemVtdRmrrCollectInfo:
            Status = OemSpecVtdRmrrCollectUefiInfo();
            if ( EFI_ERROR(Status) ) {
                Status = OemSpecVtdRmrrCollectLegacyInfo();
            }
            break;

        case OemVtdRmrrInsertRmrr:
            Status = OemSpecVtdRmrrInsertRmrr(Ptr);
            break;

        default:
            Status = EFI_UNSUPPORTED;
            break;
    } // switch case

    OEM_SPEC_RMMR_DEBUG ((EFI_D_ERROR, "InitOemSpecVtdRmrr exiting....... Status: %r \n", Status));

    return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
