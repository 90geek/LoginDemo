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
// $Header: /Alaska/SOURCE/Modules/VirtualSerialDevice/VirtualSerial.c 2     4/13/10 12:35a Rameshr $
//
// $Revision: 2 $
//
// $Date: 4/13/10 12:35a $
//**********************************************************************

//<AMI_FHDR_START>
//--------------------------------------------------------------------------
//
// Name: VirtualSerial.c
//
// Description: Create devicepath for the Virtual Serial Device. So that
//              SerialIO can consume this device and redirection can be done
//              via this Serial device.
//
//--------------------------------------------------------------------------
//<AMI_FHDR_END>


#include "VirtualSerial.h"
#include <Token.h> //TH0108

//TH0017 #define     MAXIMUM_NO_VIRTUAL_DEVICES 3
#define     MAXIMUM_NO_VIRTUAL_DEVICES 1 //TH0017

#ifndef _CR
#define _CR( Record, TYPE, Field ) \
    ( (TYPE *) ( (CHAR8 *) (Record) - (CHAR8 *) &( ( (TYPE *) 0 )->Field ) ) )
#endif

#define VIRTUAL_SERIAL_DATA_FROM_EFISIO(a) \
  _CR ( \
  (a), \
  VIRTUAL_DEV_DATA, \
  EfiSio \
)

EFI_GUID            gDxeSvcTblGuid = DXE_SERVICES_TABLE_GUID;
extern EFI_GUID     gEfiAmiSioProtocolGuid;
extern EFI_GUID     gEfiSioProtocolGuid;
static DXE_SERVICES        *gDxeSvcTbl=NULL;

//TH0108 VIRTUAL_SERIAL_DETAILS VirtualSerialDevices[MAXIMUM_NO_VIRTUAL_DEVICES]= {
VIRTUAL_SERIAL_DETAILS VirtualSerialDevices0[MAXIMUM_NO_VIRTUAL_DEVICES]= { //TH0108
    { 
        VIRTUAL_SERIAL_DEVICE1_BASE_ADDRESS,
        VIRTUAL_SERIAL_DEVICE1_IRQ,
        VIRTUAL_SERIAL_DEVICE1_UID
#if MAXIMUM_NO_VIRTUAL_DEVICES > 1 //TH0017
    },

    { 
        VIRTUAL_SERIAL_DEVICE2_BASE_ADDRESS,
        VIRTUAL_SERIAL_DEVICE2_IRQ,
        VIRTUAL_SERIAL_DEVICE2_UID
#if MAXIMUM_NO_VIRTUAL_DEVICES > 2 //TH0017
    },

    { 
        VIRTUAL_SERIAL_DEVICE3_BASE_ADDRESS,
        VIRTUAL_SERIAL_DEVICE3_IRQ,
        VIRTUAL_SERIAL_DEVICE3_UID
#endif //TH0017
#endif //TH0017
    }

};
//TH0108>>>
#if defined SIO_VIRTUAL_PORT_SUPPORT && SIO_VIRTUAL_PORT_SUPPORT == 1
VIRTUAL_SERIAL_DETAILS VirtualSerialDevices1[MAXIMUM_NO_VIRTUAL_DEVICES]= {
    { 
        VIRTUAL_SERIAL_DEVICE1_BASE_ADDRESS1,
        VIRTUAL_SERIAL_DEVICE1_IRQ1,
        VIRTUAL_SERIAL_DEVICE1_UID
#if MAXIMUM_NO_VIRTUAL_DEVICES > 1 
    },

    { 
        VIRTUAL_SERIAL_DEVICE2_BASE_ADDRESS,
        VIRTUAL_SERIAL_DEVICE2_IRQ,
        VIRTUAL_SERIAL_DEVICE2_UID
#if MAXIMUM_NO_VIRTUAL_DEVICES > 2 
    },

    { 
        VIRTUAL_SERIAL_DEVICE3_BASE_ADDRESS,
        VIRTUAL_SERIAL_DEVICE3_IRQ,
        VIRTUAL_SERIAL_DEVICE3_UID
#endif 
#endif 
    }

};
#endif
//TH0108<<<

struct {
    ACPI_HID_DEVICE_PATH      AcpiDevicePath;
    EFI_DEVICE_PATH_PROTOCOL  EndDevicePath;
} VirtualSerialDevicePath[MAXIMUM_NO_VIRTUAL_DEVICES] = {
    {
        {
            ACPI_DEVICE_PATH,
            ACPI_DP,
            (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
            (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8),
            EISA_PNP_ID (0x501), VIRTUAL_SERIAL_DEVICE1_UID
        },

        {
            END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
            sizeof(EFI_DEVICE_PATH_PROTOCOL)
        }
#if MAXIMUM_NO_VIRTUAL_DEVICES > 1 //TH0017
    },

    {
        {
            ACPI_DEVICE_PATH,
            ACPI_DP,
            (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
            (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8),
            EISA_PNP_ID (0x501), VIRTUAL_SERIAL_DEVICE2_UID
        },

        {
            END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
            sizeof(EFI_DEVICE_PATH_PROTOCOL)
        }
#if MAXIMUM_NO_VIRTUAL_DEVICES > 2 //TH0017
    },

    {
        {
            ACPI_DEVICE_PATH,
            ACPI_DP,
            (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
            (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8),
            EISA_PNP_ID (0x501), VIRTUAL_SERIAL_DEVICE3_UID
        },

        {
            END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
            sizeof(EFI_DEVICE_PATH_PROTOCOL)
        }
#endif //TH0017
#endif //TH0017
    }
};

VIRTUAL_DEV_DATA            VirtualDevice[MAXIMUM_NO_VIRTUAL_DEVICES];

T_ITEM_LIST     VirtualSerialResources;
ASLR_FixedIO    VirtualSerialBaseAddress;
ASLR_IRQNoFlags VirtualSerialIrq;
VOID            *ResourceList[2];

//
// AMI SIO protocol API definition
//

//TH0108>>>
UINT8 GetSioUartResourceSetup(
    IN UINT16 PnpId, 
    IN UINT8  Uid )
{
    CHAR16              s[40];
    EFI_STRING          vname = NULL;
    SIO_DEV_NV_DATA      NvData;
    EFI_GUID            ssg = SIO_VARSTORE_GUID;
    UINTN               vs;
    BOOLEAN             IsDefault = TRUE;
    EFI_STATUS          Status;
//------------------	
    NvData.DevPrsId = 0;
#if (SIO_SETUP_USE_APTIO_4_STYLE == 1)
    Swprintf(s, LD_NV_VAR_NAME_FORMAT, PnpId, Uid);	
    vname = MallocZ(Wcslen(s) * sizeof(CHAR16) + sizeof(CHAR16));
    Wcscpy(vname, s);
    vs = sizeof(SIO_DEV_NV_DATA);
    Status = pRS->GetVariable(vname, &ssg, NULL, &vs, &NvData);
    if(EFI_ERROR(Status)) {
        NvData.DevPrsId = 0;
    }
    if (vname != NULL) pBS->FreePool(vname);
#endif
    return NvData.DevPrsId;
}
//TH0108<<<

//<AMI_PHDR_START>
//============================================================================
// Procedure:   VirtualSerialRegister
//
// Description: Get the Virtual Serial Device Register details
//
// Input:   
//         
//          IN AMI_SIO_PROTOCOL *This,
//          IN BOOLEAN          Write,
//          IN BOOLEAN          ExitCfgMode,
//          IN UINT8            Register,
//          IN OUT UINT8        *Value 
//
// Output: 
//          This is not supported for virtual Serial device 
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
VirtualSerialRegister (
    IN AMI_SIO_PROTOCOL     *This,
    IN BOOLEAN              Write,
    IN BOOLEAN              ExitCfgMode,
    IN UINT8                Register,
    IN OUT UINT8            *Value
)
{

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   VirtualSerialCRS
//
// Description: Get the Virtual Serial Device current resource
//
// Input:   
//         
//          IN AMI_SIO_PROTOCOL *This,
//          IN BOOLEAN          Set,
//          IN OUT T_ITEM_LIST  **Resources
//
// Output: 
//          Return the virutal serial device current resource 
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END> 
EFI_STATUS 
EFIAPI
VirtualSerialCRS(
    IN AMI_SIO_PROTOCOL     *This,
    IN BOOLEAN              Set,
    IN OUT T_ITEM_LIST      **Resources
)
{

    VIRTUAL_DEV_DATA*    VirtualDevice=(VIRTUAL_DEV_DATA*)This;

    if (!VirtualDevice || !Resources) {
        return EFI_INVALID_PARAMETER;
    }

    if (Set) {
        return EFI_UNSUPPORTED;
    } else {

        // Virtual Serial Device Base address Resource
        VirtualSerialBaseAddress.Hdr.Name   = ASLV_RT_FixedIO;
        VirtualSerialBaseAddress._BAS       = VirtualDevice->DevBase;
        VirtualSerialBaseAddress._LEN       = 0x8;

        //Virtual Device IRQ details.
        VirtualSerialIrq.Hdr.Name           = ASLV_RT_IRQ;
        VirtualSerialIrq._INT               = VirtualDevice->DevIrq;

        ResourceList[0]                     =(VOID*)&VirtualSerialBaseAddress;
        ResourceList[1]                     =(VOID*)&VirtualSerialIrq;

        //Set the Resource details
        VirtualSerialResources.InitialCount = 2;
        VirtualSerialResources.ItemCount    = 2;
        VirtualSerialResources.Items        =(VOID*)&ResourceList[0];

        *Resources                          = &VirtualSerialResources;
    }

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//============================================================================
// Procedure:   VirtualSerialPRS
//
// Description: Provides combination of resources that can be used by the device
//
// Input:   
//         
//          IN AMI_SIO_PROTOCOL *This,
//          IN BOOLEAN          Set,
//          IN OUT T_ITEM_LIST  **Resources
//
// Output: 
//          Not Supported 
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END> 
EFI_STATUS 
EFIAPI
VirtualSerialPRS(
    IN AMI_SIO_PROTOCOL     *This,
    IN BOOLEAN              Set,
    IN OUT T_ITEM_LIST      **Resources
)
{
    return EFI_UNSUPPORTED;
}

//
// EFI SIO protocol API definition
//

//<AMI_PHDR_START>
//============================================================================
// Procedure:   VirtualEfiSioRegisterAccess
//
// Description: Get the Virtual Serial Device Register details
//
// Input:
//
//          IN EFI_SIO_PROTOCOL *This,
//          IN BOOLEAN          Write,
//          IN BOOLEAN          ExitCfgMode,
//          IN UINT8            Register,
//          IN OUT UINT8        *Value
//
// Output:
//          EFI_STATUS
//          This functionality is not supported for virtual Serial device
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
VirtualEfiSioRegisterAccess(
  IN   CONST  EFI_SIO_PROTOCOL  *This,
  IN          BOOLEAN           Write,
  IN          BOOLEAN           ExitCfgMode,
  IN          UINT8             Register,
  IN OUT      UINT8             *Value
)
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   VirtualEfiSioGetResources
//
// Description: Get the Virtual Serial Device current resource
//
// Input:
//
//          IN  CONST EFI_SIO_PROTOCOL            *This,
//          OUT       ACPI_RESOURCE_HEADER_PTR    *EfiResourceList
//
// Output:
//          EFI_STATUS
//          Returns the virtual serial device list of the current resources
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
VirtualEfiSioGetResources(
  IN  CONST EFI_SIO_PROTOCOL            *This,
  OUT       ACPI_RESOURCE_HEADER_PTR    *EfiResourceList
)

{
    VIRTUAL_DEV_DATA*    VirtualDevice;
    VOID                 *EfiSioRes = NULL;
    UINT8                *TempRes = NULL;
    UINT32               Size = 0;

    if (!This || !EfiResourceList)
        return EFI_INVALID_PARAMETER;

    VirtualDevice = VIRTUAL_SERIAL_DATA_FROM_EFISIO(This);

    // Virtual Serial Device Base address Resource
    VirtualSerialBaseAddress.Hdr.Length = sizeof(ASLR_FixedIO) - sizeof(ASLRF_S_HDR);
    VirtualSerialBaseAddress.Hdr.Name   = ASLV_RT_FixedIO;
    VirtualSerialBaseAddress.Hdr.Type   = ASLV_SMALL_RES;
    VirtualSerialBaseAddress._BAS       = VirtualDevice->DevBase;
    VirtualSerialBaseAddress._LEN       = 0x8;
    Size += sizeof(ASLR_FixedIO);

    // Virtual Device IRQ details
    VirtualSerialIrq.Hdr.Length = sizeof(ASLR_IRQNoFlags) - sizeof(ASLRF_S_HDR);
    VirtualSerialIrq.Hdr.Name   = ASLV_RT_IRQ;
    VirtualSerialIrq.Hdr.Type   = ASLV_SMALL_RES;
    VirtualSerialIrq._INT       = VirtualDevice->DevIrq;
    Size += sizeof(ASLR_IRQNoFlags);

    EfiSioRes =  TempRes = Malloc(Size + sizeof(ASLR_EndTag));

    if(!EfiSioRes)
        return EFI_OUT_OF_RESOURCES;

    MemCpy(TempRes, &VirtualSerialBaseAddress, sizeof(ASLR_FixedIO));
    TempRes += sizeof(ASLR_FixedIO);

    MemCpy(TempRes, &VirtualSerialIrq, sizeof(ASLR_IRQNoFlags));
    TempRes += sizeof(ASLR_IRQNoFlags);

    ((ASLR_EndTag*)TempRes)->Hdr.HDR = ASLV_END_TAG_HDR;
    ((ASLR_EndTag*)TempRes)->Chsum = 0;

    EfiResourceList->SmallHeader = EfiSioRes;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   VirtualEfiSioSetResources
//
// Description: Sets the Virtual Serial Device current resource
//
// Input:
//
//          IN CONST  EFI_SIO_PROTOCOL        *This,
//          IN        ACPI_RESOURCE_HEADER_PTR ResourceList
//
// Output:
//          EFI_STATUS
//          This functionality is not supported for virtual Serial device
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
VirtualEfiSioSetResources(
  IN CONST  EFI_SIO_PROTOCOL        *This,
  IN        ACPI_RESOURCE_HEADER_PTR ResourceList
)
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   VirtualEfiSioPossibleResources
//
// Description: Provides combination of resources that can be used by the device
//
// Input:
//
//          IN CONST  EFI_SIO_PROTOCOL        *This,
//          OUT       ACPI_RESOURCE_HEADER_PTR ResourceCollection
//
// Output:
//          EFI_STATUS
//          This functionality is not supported for virtual Serial device
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
VirtualEfiSioPossibleResources(
  IN  CONST EFI_SIO_PROTOCOL         *This,
  OUT       ACPI_RESOURCE_HEADER_PTR *ResourceCollection
)
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   VirtualEfiSioModify
//
// Description: Interface for multiple registers programming with single call
//
// Input:
//
//          IN CONST EFI_SIO_PROTOCOL         *This,
//          IN CONST EFI_SIO_REGISTER_MODIFY  *Command,
//          IN       UINTN                    NumberOfCommands
//
// Output:
//          EFI_STATUS
//          This functionality is not supported for virtual Serial device
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
VirtualEfiSioModify(
  IN CONST EFI_SIO_PROTOCOL         *This,
  IN CONST EFI_SIO_REGISTER_MODIFY  *Command,
  IN       UINTN                    NumberOfCommands
)
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure:   InitilizeVirtualSerialDevice
//
// Description: Initialize the Virtual Serial Device
//
// Input:   
//
// Output: 
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END> 
EFI_STATUS
InitilizeVirtualSerialDevice(
)
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//============================================================================
// Procedure: VirtualSerialEntryPoint
//
// Description:  Virtual Serial device Entry point. It creates the device path
//               for the Virtual Serial device
//
// Input:   ImageHandle         Image handle for this driver
//          SystemTable          Pointer to the EFI system table.
//
// Output: 
//          EFI_SUCCESS     The function completed successfully.
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END> 
EFI_STATUS
EFIAPI
VirtualSerialEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
    EFI_STATUS              Status;
    EFI_HANDLE              VirtualDeviceHandle=NULL;
    EFI_PHYSICAL_ADDRESS    addr=0;
    UINT16                  Len =8;
    UINT8                   Aln=0;
    UINT16                  IrqMask;
    UINT32                  Count=0;
//TH0108>>>
    VIRTUAL_SERIAL_DETAILS  VirtualSerialDevices[MAXIMUM_NO_VIRTUAL_DEVICES]; 
//TH0108<<<
    // Initialize the EFI driver library
    InitAmiLib(ImageHandle, SystemTable);

    gDxeSvcTbl=(DXE_SERVICES*)GetEfiConfigurationTable(SystemTable,
                                &gDxeSvcTblGuid);
    
    if(!gDxeSvcTbl) {
        return EFI_NOT_FOUND;
    }

    // Initialize the Virtual Serial Device
    InitilizeVirtualSerialDevice();

    for(Count=0;Count<MAXIMUM_NO_VIRTUAL_DEVICES;Count++) {
//TH0108>>>
        VirtualSerialDevices[Count] = VirtualSerialDevices0[Count];
#if defined SIO_VIRTUAL_PORT_SUPPORT && SIO_VIRTUAL_PORT_SUPPORT == 1
        /*Serial Port Setup Value Define:
                              0x0: Auto
                              0x1: IO3F8_IRQ4 (COMA)  IO2F8_IRQ3 (COMB)
                              0x2: IO3F8_IRQX (COMA)  IO3F8_IRQX (COMB)
                              0x3: IO2F8_IRQX (COMA)  IO2F8_IRQX (COMB)
                              0x4: IO3E8_IRQX (COMA)  IO3E8_IRQX (COMB)
                              0x5: IO2E8_IRQX (COMA)  IO2E8_IRQX (COMB)
        */
        if((Count == 0) && (GetSioUartResourceSetup(0x0501, 0) != 0x3)) {  //SIO COMA UID = 0,
//TH0176            IoWrite8(0x85, 0x66);
            VirtualSerialDevices[Count] = VirtualSerialDevices1[Count];
        }
#endif
//TH0108<<<
        if(VirtualSerialDevices[Count].BaseAddress == 0 ||
                VirtualSerialDevices[Count].Irq == 0) {

            // Device is not present. So continue for next device.
            continue;
        }

        addr=(EFI_PHYSICAL_ADDRESS)VirtualSerialDevices[Count].BaseAddress;
        Status=gDxeSvcTbl->AddIoSpace (
                            EfiGcdIoTypeIo,
                            addr,
                            Len
                            );

        if(EFI_ERROR(Status)) {
            continue;
        }

        // Inform the generic driver that Virtual Serial device base address
        //  is used. So that nobody else can use the resource
        Status=gDxeSvcTbl->AllocateIoSpace(EfiGcdAllocateAddress,
                                        EfiGcdIoTypeIo,
                                        Aln,
                                        Len, 
                                        &addr,
                                        ImageHandle,
                                        NULL
                                        );
        if(EFI_ERROR(Status)|| 
                ((UINT16)addr != VirtualSerialDevices[Count].BaseAddress)) {
            continue;
        }

        Status=AmiIsaIrqMask(&IrqMask, TRUE);

        if(Status==EFI_NOT_FOUND){
            IrqMask=ISA_IRQ_MASK;
            IrqMask |= (1<<VirtualSerialDevices[Count].Irq);
            Status = AmiIsaIrqMask(&IrqMask, FALSE);
        } else {
            IrqMask |= (1<<VirtualSerialDevices[Count].Irq);
            Status=AmiIsaIrqMask(&IrqMask, FALSE);
        }

        VirtualDevice[Count].AmiSio.Access          = VirtualSerialRegister;
        VirtualDevice[Count].AmiSio.CurrentRes      = VirtualSerialCRS;
        VirtualDevice[Count].AmiSio.PossibleRes     = VirtualSerialPRS;

        VirtualDevice[Count].EfiSio.RegisterAccess     = VirtualEfiSioRegisterAccess;
        VirtualDevice[Count].EfiSio.GetResources       = VirtualEfiSioGetResources;
        VirtualDevice[Count].EfiSio.SetResources       = VirtualEfiSioSetResources;
        VirtualDevice[Count].EfiSio.PossibleResources  = VirtualEfiSioPossibleResources;
        VirtualDevice[Count].EfiSio.Modify             = VirtualEfiSioModify;

        VirtualDevice[Count].DevBase        = VirtualSerialDevices[Count].BaseAddress;
        VirtualDevice[Count].DevIrq         = VirtualSerialDevices[Count].Irq;
        VirtualDevice[Count].DevDma         = 0;

        VirtualDeviceHandle=NULL;
        Status=pBS->InstallMultipleProtocolInterfaces( 
                                            &VirtualDeviceHandle, 
                                            &guidDevicePath, 
                                            &VirtualSerialDevicePath[Count], 
                                            &gEfiAmiSioProtocolGuid, 
                                            &VirtualDevice[Count].AmiSio, 
                                            &gEfiSioProtocolGuid,
                                            &VirtualDevice[Count].EfiSio,
                                            NULL 
                                            );
    }

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
