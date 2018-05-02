/** @file
Module Name:

  FxupdateSystemInfo.c

Abstract: Provide functions to update the BMC with system's processor and 
          PCIe information.

  Copyright 2011 - 2015, Foxconn Corporation.
  
  This software contains information confidential and proprietary to
  Foxconn Corporation. It shall not be reproduced in whole or in part,
  or transferred to other documents, or disclosed to third parties, or used
  for any purpose other than that for which it was obtained without the prior
  written consent of Foxconn Corporation.
  

**/

#include "FxSystemInfo.h"

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h> 
#include <Library/DebugLib.h>
#include <Library/PciLib.h>
#include <IndustryStandard/SmBios.h>

#include <Protocol/IPMITransportProtocol.h>
#include <Protocol/Smbios.h>
#include <Protocol/PciEnumerationComplete.h>

#include <Token.h> //ZCH001002+
#include <AmiLib.h> //ZCH001009+
#include <AmiDxeLib.h>//ZCH001009+

//JPG001006+START
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h> 
#include <Protocol/IPMITransportProtocol.h>
#include <Guid/MemoryMapData.h> 
#include <Library/HobLib.h>
#include <Library/HiiLib.h>
#include <Library/UefiLib.h>
//JPG001006+END
#include <Guid/SetupVariable.h>                  
#include <Include/IpmiNetFnChassisDefinitions.h> 
//JPG001004+START
#include <Library/NetLib.h>
#include <Protocol/SimpleNetwork.h>
#include <Library/BaseMemoryLib.h>
#include <uefi/UefiBaseType.h>
#include <Library/DevicePathLib.h>
#include <uefi/UefiSpec.h>
#include <Guid/NetworkStackSetup.h>

#include <Include/ServerMgmtSetupVariable.h> 

UINT8 FxCpuReadSpdByte(UINT8 DimmNumber, UINT8 Offset, UINT32 SmbCntlData);


EFI_RUNTIME_SERVICES *gRT;
//JPG001004+END

//
// Module Global variables
//
EFI_IPMI_TRANSPORT              *gIpmiTransport = NULL;

#define STR(a) CONVERT_TO_STRING(a) 


//JPG002005+START
static PLATFORM_PCIE_SLOT    mPcieSlotTable[] = { 
     //
     // Add Slot Info here.
     //
//JPG002005A-    {SAS_MEZZ, 0, 1, 0},
	{SAS_MEZZ, 0, 3, 0},  //JPG002005A+
 
    // End of table
    {0xFF, 0xFF, 0xFF, 0xFF}
  };
//JPG002005+END

EFI_STATUS
UpdatePcieInfo (
  VOID )
{
  EFI_STATUS     Status;
  FX_PCIE_INFO   PcieInfo;
  UINT8          PcieInfoSize = sizeof (PcieInfo);
  UINT8          DeviceBus;
  UINTN          Index = 0;
  UINT8          ResponseData;
  UINT8          ResponseDataSize;
  FX_PCIE_SLOT_MAPPING  SlotMapping = {FX_SET_PCIE_INFO, 0, 0, 0}; 

  while (mPcieSlotTable[Index].Index != 0xFF) {

//CZY001004+START
    //
    // if PCIe slot is supported
    //
    if (!(mPcieSlotTable[Index].Bus == 0xFF && mPcieSlotTable[Index].Dev == 0xFF && mPcieSlotTable[Index].Func == 0xFF) &&
        PciRead32(PCI_LIB_ADDRESS(mPcieSlotTable[Index].Bus, mPcieSlotTable[Index].Dev, mPcieSlotTable[Index].Func, 0)) != 0xffffffff){
        
      DeviceBus = PciRead8(PCI_LIB_ADDRESS (
                        (UINT8) mPcieSlotTable[Index].Bus,
                        (UINT8) mPcieSlotTable[Index].Dev,
                        (UINT8) (mPcieSlotTable[Index].Func),
                         0x19
                        )); 

      //
      // Read PCIe device Configure Info
      //
 //JPG002005B-     PcieInfo.Presence = 1;
      PcieInfo.VID   = PciRead16(PCI_LIB_ADDRESS (
                             (UINT8)DeviceBus,
                             (UINT8) 0,
                             (UINT8) 0,
                             0
                             ));
      PcieInfo.DID   = PciRead16(PCI_LIB_ADDRESS (
                             (UINT8)DeviceBus,
                             (UINT8) 0,
                             (UINT8) 0,
                             2
                             ));
      PcieInfo.SVID  = PciRead16(PCI_LIB_ADDRESS (
                             (UINT8)DeviceBus,
                             (UINT8) 0,
                             (UINT8) 0,
                             0x2c
                             ));
      PcieInfo.SID  = PciRead16(PCI_LIB_ADDRESS (
                             (UINT8)DeviceBus,
                             (UINT8) 0,
                             (UINT8) 0,
                             0x2e
                             ));

      DEBUG ((DEBUG_INFO, "%a: Bus=0x%02x, Device=0, Function=0\n",
               __FUNCTION__, DeviceBus));
      DEBUG ((DEBUG_INFO, "    VID=0x%04x, DID=0x%04x, SVID=0x%04x, SID=0x%04x\n",
                PcieInfo.VID, PcieInfo.DID, PcieInfo.SVID, PcieInfo.SID));
    }
    else {
 //JPG002005B-     PcieInfo.Presence = 0;
      PcieInfo.VID = 0xFFFF;
      PcieInfo.DID = 0xFFFF;
      PcieInfo.SVID = 0xFFFF;
      PcieInfo.SID = 0xFFFF;
      
      DEBUG ((DEBUG_INFO, "%a: HBA is not Presence \n",
               __FUNCTION__));      
    }
//JPG002005B+START
    if (PcieInfo.VID != 0xffff) {
    	PcieInfo.Presence = 1;
    } else {
    	PcieInfo.Presence = 0;
    }
 //JPG002005B+END
    PcieInfo.SubCmd = FX_SET_PCIE_INFO;
 	

    //
    // Send PCIe info to BMC
    //
    Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    FX_IPMI_OEM_COMMAND,   
                    BMC_LUN,
                    FX_BIOS_REPORT_TO_BMC, 
                    (UINT8 *) &PcieInfo,
                    PcieInfoSize,
                    (UINT8 *) &ResponseData,
                    (UINT8 *) &ResponseDataSize );

    DEBUG ((DEBUG_INFO, "UPDATE_PCIE_INFO Status: %r Response: %x\n", Status, ResponseData));  
  
    Index++;
  }
  return EFI_SUCCESS;
}

//DJH002022++>>
EFI_STATUS
UpdateDiskErrorInfo (
VIOD )
{
	UINT16         DiskError;
	EFI_STATUS	   Status;
	DISK_ERROR_INFO   DiskErrorInfo;
	UINT8		      DiskErrorInfoSize = sizeof (DiskErrorInfo);
	UINT8		      ResponseData;
	UINT8		      ResponseDataSize;
	
	UINT16         i;
	UINT16         j;
	UINT8          count = 0;
	

	DiskError = PcdGet16 (PchDiskError);
	DEBUG ((-1, "Set PchDiskError: %0x \n",DiskError));
	
	i = DiskError;
	for (;i != 0;i = i >> 1){
		j = i & 1;
		if(j == 1){
			count = count + 1;
		}
	}
	DiskErrorInfo.DiskIndex = count;
	DEBUG ((-1, " DiskErrorInfo.DiskIndex: %0d \n",DiskErrorInfo.DiskIndex));
	DiskErrorInfo.SubCmd = FX_SET_DISK_ERROR_INFO;
	DiskErrorInfo.DiskError = (UINT8)(DiskError >> 2);
	DEBUG ((-1, " DiskErrorInfo.DiskError: %0x \n",DiskErrorInfo.DiskError));

    //
    // Send Disk error info to BMC
    //
    Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    FX_IPMI_OEM_COMMAND,
                    BMC_LUN,
                    FX_BIOS_REPORT_TO_BMC,
                    (UINT8 *) &DiskErrorInfo,
                    DiskErrorInfoSize,
                    (UINT8 *) &ResponseData,
                    (UINT8 *) &ResponseDataSize );

    DEBUG ((DEBUG_INFO, "UPDATE_DISK_ERROR_INFO Status: %r Response: %x\n", Status, ResponseData));

		
	return EFI_SUCCESS;
}
//DJH002022++<<

//DJH002030++>>
VOID
UpdateNvmeOrHDDInfo(
VOID)
{
	EFI_STATUS	Status;
	NVME_INFO       Nvme;
	UINT8		NvmeSize = sizeof (Nvme);
	UINT8		ResponseData;
	UINT8		ResponseDataSize;
	UINT8           NvmePresence = 0;
	UINT8	        BusNum;

	
	// For NVME 1
	if (0xFFFFFFFF != PciRead32(PCI_LIB_ADDRESS(0x80,2,0,0)) )
	{
		BusNum = PciRead8(PCI_LIB_ADDRESS(0x80,2,0,0x19));
		if(0xFFFFFFFF != PciRead32(PCI_LIB_ADDRESS(BusNum,0,0,0))) {
			DEBUG ( (-1, " NVME1_DID_VID: %0x \n",PciRead32(PCI_LIB_ADDRESS(BusNum,0,0,0))) );
			NvmePresence |=  1;
			//DEBUG ((-1, " NvmePresence: %0x \n",NvmePresence));
		}
	}
	
	// For NVME 2 
	if (0xFFFFFFFF != PciRead32(PCI_LIB_ADDRESS(0x80,2,1,0)) )
	{
		BusNum = PciRead8(PCI_LIB_ADDRESS(0x80,2,1,0x19));
		if(0xFFFFFFFF != PciRead32(PCI_LIB_ADDRESS(BusNum,0,0,0))){
			DEBUG( (-1, " NVME2_DID_VID: %0x \n",PciRead32(PCI_LIB_ADDRESS(BusNum,0,0,0))) );
			NvmePresence |= 0x02;
		}
	}	

	// For NVME 3
	if (0xFFFFFFFF != PciRead32(PCI_LIB_ADDRESS(0x80,2,2,0)) )
	{
		BusNum = PciRead8(PCI_LIB_ADDRESS(0x80,2,2,0x19));
		if(0xFFFFFFFF != PciRead32(PCI_LIB_ADDRESS(BusNum,0,0,0))) {
			DEBUG( (-1, " NVME3_DID_VID: %0x \n",PciRead32(PCI_LIB_ADDRESS(BusNum,0,0,0))) );
			NvmePresence |= 0x04;
		}
	}

	// For NVME 4
	if (0xFFFFFFFF != PciRead32(PCI_LIB_ADDRESS(0x80,2,3,0)) )
	{
		BusNum = PciRead8(PCI_LIB_ADDRESS(0x80,2,3,0x19));
		if(0xFFFFFFFF != PciRead32(PCI_LIB_ADDRESS(BusNum,0,0,0))){
			DEBUG( (-1, " NVME4_DID_VID: %0x \n",PciRead32(PCI_LIB_ADDRESS(BusNum,0,0,0))) );
			NvmePresence |= 0x08;
		}
	}	

	Nvme.SubCmd = FX_SET_NVME_INFO;
	Nvme.NvmeLocation = NvmePresence;
	DEBUG ((-1, " Nvme.NvmeLocation: %0x \n",Nvme.NvmeLocation));
	
    //
    // Send NVME info to BMC
    //
    Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    FX_IPMI_OEM_COMMAND,
                    BMC_LUN,
                    FX_BIOS_REPORT_TO_BMC,
                    (UINT8 *) &Nvme,
                    NvmeSize,
                    (UINT8 *) &ResponseData,
                    (UINT8 *) &ResponseDataSize );

    DEBUG ((DEBUG_INFO, "Send NVME info to BMC Status: %r \n", Status));
}
//DJH002030++<<


VOID
EFIAPI
UpdateSystemInfo (

  )
{
	
    DEBUG((DEBUG_INFO, "%a: Entering...\n", __FUNCTION__));
    //
    // Update the BMC with the new PCIe information.
    //
    UpdatePcieInfo ();
    UpdateDiskErrorInfo  (); //DJH002022++
    UpdateNvmeOrHDDInfo();   //DJH002030++
  

  DEBUG((DEBUG_INFO, "%a: Exiting...\n", __FUNCTION__));
  return;  
}

EFI_STATUS
FxUpdateSystemInfoDxeEntry (

  )
{
    EFI_STATUS      Status;

    
    DEBUG((DEBUG_INFO, "%a: Entering...\n", __FUNCTION__));
  
    Status = gBS->LocateProtocol (
                        &gEfiDxeIpmiTransportProtocolGuid,
                        NULL,
                        (VOID**)&gIpmiTransport );
  
    DEBUG ((DEBUG_INFO, "%a: Locate gEfiDxeIpmiTransportProtocolGuid Status: %r \n", __FUNCTION__, Status));
  
    if(EFI_ERROR (Status)) {
      return Status;
    }

    UpdateSystemInfo(); 
    
    return EFI_SUCCESS;              
}
