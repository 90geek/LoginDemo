/** @file

  Platform specific defnitions used by the FxUpdateSystemInfo driver 

  Copyright 2011 - 2015, Foxconn Corporation.
  
  This software contains information confidential and proprietary to
  Foxconn Corporation. It shall not be reproduced in whole or in part,
  or transferred to other documents, or disclosed to third parties, or used
  for any purpose other than that for which it was obtained without the prior
  written consent of Foxconn Corporation.
  

**/

#ifndef _FX_SYSTEM_INFO_H_
#define _FX_SYSTEM_INFO_H_

//
// Processor Info definition
//

//
// WCS Processor Types 
//
#define INTEL_CELERON       0x00
#define INTEL_PENTIUM_III   0x01
#define INTEL_PENTIUM_4     0x02
#define INTEL_XEON          0x03
#define INTEL_PRESTONIA     0x04
#define INTEL_NOCONA        0x05
#define AMD_OPTERON         0x06
#define INTEL_DEMPSEY       0x07
#define INTEL_CLOVERTOWN    0x08
#define INTEL_TIGERTON      0x09
#define INTEL_DUNNINGTON    0x0a
#define INTEL_HARPERTOWN    0x0b
#define INTEL_WOLFDALE_DP   0x0c
#define INTEL_NEHALEM_EP    0x0d
#define INTEL_LYNNFIELD     0x0e
#define AMD_LISBON          0x0f
#define AMD_PHENOM_II       0x10
#define AMD_ATHLON_II       0x11
#define AMD_OPERATON        0x12
#define AMD_SUZUKA          0x13
#define INTEL_CORE_I3       0x14
#define INTEL_SANDY_BRIDGE  0x15
#define INTEL_IVY_BRIDGE    0x16
#define INTEL_CENTERTON     0x17
#define INTEL_HASWELL       0x18
#define INTEL_BROADWELL     0x19
#define NO_CPU_PRESENT      0xff

//
//  Processor Status definition
//
#define PROCESSOR_PRESENT       0x01
#define PROCESSOR_NOT_PRESENT   0xFF

//
// Haswell CPUID signatures
//
#define CPUID_SIGNATURE_HASWELL_CLIENT          0x000306C0
#define CPUID_SIGNATURE_HASWELL_SERVER          0x000306F0

//
// Broadwell CPUID signatures
//
#define CPUID_SIGNATURE_BROADWELL_DE_SERVER       0x00050660
#define CPUID_SIGNATURE_BROADWELL_CLIENT          0x000406C0
#define CPUID_SIGNATURE_BROADWELL_SERVER          0x000406F0

//
// CPUID masks
//
#define CPUID_MASK_NO_STEPPING                  0x0FFF0FF0
#define CPUID_MASK_NO_STEPPING_MODEL            0x0FFF0F00

#pragma pack(1)

typedef struct {
  UINT8   SubCmd;   // 1h = Set Processor Info   //CZY001004+
  UINT8   Index;    // Processor index (0-based index)
  UINT8   Type;     // Processor type (WCS Processor Types)
  UINT16  Frequency;// Processor frequency (in MHz); LSB first
  UINT8   Status;   // Processor status: 01h is present FFh is not present
} FX_PROCESSOR_INFO;

#pragma pack()

//
//  PCIe Info deinitions
//

//
// WCS PCIe slot mapping
//
//JPG002005-START
/*#define LAN_MEZZ                      1
#define TRAY_BACKPLANE_PCIE_SLOT_A    2
#define TRAY_BACKPLANE_PCIE_SLOT_B    3
#define TRAY_BACKPLANE_PCIE_SLOT_C    4
#define TRAY_BACKPLANE_PCIE_SLOT_D    5
#define PCIE_SLOT_1_A                 6
#define PCIE_SLOT_1_B                 7
#define PCIE_SLOT_2_A                 8
#define PCIE_SLOT_2_B                 9
#define PCIE_SLOT_3_A                 10
#define PCIE_SLOT_3_B                 11
#define PCIE_SLOT_4_A                 12
#define PCIE_SLOT_4_B                 13
*/
//JPG002005-END
//JPG002005+START
#define SAS_MEZZ                     1 
#define LAN_MEZZ                     2
//JPG002005+END

typedef struct {
  UINT8  Index;
  UINT8  Bus;
  UINT8  Dev;
  UINT8  Func;
} PLATFORM_PCIE_SLOT;

typedef struct {
  UINT8   SubCmd; // 3h = Set PCIe Info  //CZY001004+
  UINT8   Presence;  // If PCIe Presence.
  UINT16  VID;    // Vendor ID; LSB
  UINT16  DID;    // Device ID; LSB
  UINT16  SVID;   // Subsystem Vendor ID; LSB
  UINT16  SID;    // Subsystem ID; LSB
} FX_PCIE_INFO;

typedef struct {
  UINT8   SubCmd; // 3h = Set PCIe Info
  UINT8   Index;  // 0: PCIe Slot location
  UINT8   Slot1_8;// PCIe Presence info in bit map for Slot 1 to Slot 8
  UINT8   Slot9_D;// [4:0] PCIe Presence info in bit map for Slot 9 to Slot 13 [7:5] Reserved - written as not present 0b.
} FX_PCIE_SLOT_MAPPING;

typedef struct {
  UINT8   SubCmd; // F0h = Enable BIOS report to BMC command
  UINT8   Data1;  // 0x55
  UINT8   Data2;  // 0xAA
} FX_ENABLE_BIOS_REPORT_DATA;

//
// IPMI OEM command definitions
//

#define FX_IPMI_OEM_COMMAND     0x3E  // NetFun: 30h = OEM Request
#define FX_BIOS_REPORT_TO_BMC   0x64  // Command: F0h = BIOS report to BMC command


//SubCmd
#define FX_SET_SETUP_INFO       0x00  // 0h = Set Setup Info
#define FX_SET_PROCESSOR_INFO   0x01  // 1h = Set Processor Info
#define FX_SET_MEMORY_INFO      0x02  // 2h = Set Memory Info
#define FX_SET_PCIE_INFO        0x05  // 3h = Set PCIe Info
#define FX_SET_NIC_INFO         0x04  // 4h = Set Nic Info

#define FX_SET_DISK_ERROR_INFO 0x06  // 6h = Set Disk error Info  //DJH002022++
#define FX_SET_NVME_INFO   0x07  // 7h = Set Nvme or HDD Info  //DJH002030++


#define FX_ENABLE_BIOS_REPORT_TO_BMC  0xF0  // F0h = Enable BIOS report to BMC command
#define FX_DISABLE_BIOS_REPORT_TO_BMC 0xF1  // F1h = Disable BIOS report to BMC command
//CZY001004+END

//JPG001006+START
//
//  Memory Status definition
//
#define MEMORY_RESERVED 0x00
#define MEMORY_UNKNOWN_TYPE 0x01
#define MEMORY_OK       0x02
#define MEMORY_NOT_PRESENT   0x03
#define MEMORY_SINGLE_BIT_ERROR 0x05
#define MEMORY_MULTI_BIT_ERROR 0x07

#define MEMORY_VOLTAGE  0x80
#define MEMORY_SPEED  0x40
#define MEMORY_TYPE  0x3F 

#define SOCKET 0x2  //JPG001010+
#define MAX_NODE SOCKET*MAX_HA  //JPG001010+
#define MAX_MEM_CH 0x4
#define MAX_MEM_DIMM 0x2

extern EFI_GUID gEfiHobListGuid;

#pragma pack(1)

typedef struct {
  UINT8   SubCmd; // 2h = Set Memory Info
  UINT8   Index;  // Memory index (1-based index)
  UINT8   Type;  // Memory type
  UINT16  Speed;  // Memory speed (in MHz); LSB first
  UINT16  Size;  // Memory size (in Megabytes); LSB first
  UINT8   Status;  // Memory status: 01h is present FFh is not present
} MEMORY_INFO;

typedef struct {
  UINT8   SubCmd; // 2h = Set Memory Info
  UINT8   DIMMIndex;  // 0: DIMM location
  UINT8   DIMMSlot;  //DIMM Slot number
  UINT8   Slot1_8;// DIMM Presence info in bit map for Slot 1 to Slot 8
  UINT8   Slot9_16;// DIMM Presence info in bit map for Slot 9 to Slot 16
} FX_DIMM_SLOT_MAPPING;

#pragma pack()
//JPG001006+END

//DJH002022++>>
#pragma pack(1)

typedef struct {
  UINT8   SubCmd;      // 6h = Set Disk error Info
  UINT8   DiskIndex;   //Error Disk number
  UINT8   DiskError; //BIT set to 1-disk error; bit0-sSata2; bit1-sSata3;bit2-Sata0;bit3-Sata1;bit4-Sata2;bit5-Sata3;bit6-Sata4;bit7-Sata4;
} DISK_ERROR_INFO;


#pragma pack()

//DJH002022++<<

//DJH002030++>>
#pragma pack(1)

typedef struct {
  UINT8   SubCmd;        // 7h = Set Nvme or HDD Info
  UINT8   NvmeLocation;  // 1:Nvme Presence
} NVME_INFO;


#pragma pack()

//DJH002030++<<


#pragma pack(1)  //WYB001015+

//JPG001004+START
typedef struct {
  UINT8   SubCmd; // 4h = Set NIC Info
  UINT8   Index;    // NIC index (1-based index)
  UINT8   Address[6];     // 6 - byte MAC address
} NIC_INFO;
//JPG001004+END

//WYB001015+START
typedef struct {
  UINT8   SubCmd; // 4h = Set NIC Info
  UINT8   NicIndex;  // 0: NIC location
  UINT8   Slot1_4;// [3:0] NIC Presence info in bit map for Slot 1 to Slot 4, [7:5] Reserved - written as not present 0b.
} FX_NIC_SLOT_MAPPING;

#pragma pack()
//WYB001015+END

//ZCH001002+START 
typedef struct {
  UINT8   SubCmd; // 6h = Report BiosVersion Info
  UINT8   String[24]; // 24 - byte BiosVersion
}BIOSVERSION_INFO;

//ZCH001002+END

//ZCH001002+START
UINT8 Strlen0(char *string) 
{
	UINT8 length=0;
	while(*string++) length++;
	return length;
}
//ZCH001002+END

//LLY001004+start
typedef struct {
  UINT8   SubCmd; // 7h = RandomPowerOnEnable
  UINT8   Value;  // 0:Disable  1:Enable 
} FX_RANDOM_POWER_ON;

//LLY001004+END
#endif
