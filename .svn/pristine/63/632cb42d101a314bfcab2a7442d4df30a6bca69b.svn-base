//
// This file contains an 'Intel Peripheral Driver' and is
// licensed for Intel CPUs and chipsets under the terms of your
// license agreement with Intel or your vendor.  This file may
// be modified by the user, subject to additional terms of the
// license agreement
//
#ifndef _DCMI_SMM_
#define _DCMI_SMM_
/* dirty stuff, pretty dirty and ugly */
//#include "token.h"
//#include  EFI_PROTOCOL_DEFINITION(SmmSwDispatch)
#include <Protocol/SmmSwDispatch2.h>
#include <Library/PciExpressLib.h> //AptioV server override: dynamic MMCFG base change support.

#define DCMI_ERROR_SHARE_PROTOCOL_GUID { 0xb30f315d, 0xcce3, 0x464e, 0x84, 0x2b, 0x8, 0x61, 0x3, 0x7, 0xb2, 0xb5 }

#define DCMI_ERROR_SHARE_RECORD_ID 0xEAEA

#define DCMI_ERROR_SHARE_RECORD_TYPE 0x02

#define DCMI_ERROR_SHARE_TIMESTAMP_TODO 0xFFFFFFFF

#define DCMI_ERROR_SHARE_GENERATOR_ID  0x01  /* System Software ID */

#define DCMI_ERROR_SHARE_EVM_REV 0x04



#ifndef IPMI_HDR_COMMAND_DEFINED
typedef struct{ 
	UINT8 b1;
} IPMI_HDR_COMMAND ;
#endif

/* Fixed commands to be send in SMM */

typedef struct {
	UINT8			ResponserSlave; 
	IPMI_HDR_COMMAND 	IpmiHeader;
} DCMI_HI_REQ_HEADER;

/* Bromolow TODO: Do we need to use permanent Memmory or so for "Dynamic  Mem allocation"? ?*/
/* just guessing */

typedef struct  {
	DCMI_HI_REQ_HEADER DcmiHeader;
	UINT8  SystemPowerState;
	UINT8  DevicePowerState;
	UINT8  CommitByte;
} SetACPIHeader ;

typedef struct {
	DCMI_HI_REQ_HEADER DcmiHeader;
		UINT8	 CommitByte;
} GetDeviceHeader;





typedef struct {
	UINT8			ResponserSlave; 
	IPMI_HDR_COMMAND 	IpmiHeader;
	UINT8			CompletionCode;
	UINT8			Data[256];		//Commit will be part of this 
} DCMI_HI_RESP;





typedef
VOID
(EFIAPI *DCMI_ADDSEL_ENTRY)  (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_SW_CONTEXT   *DispatchContext
  );

#pragma pack(1)
typedef struct {
	UINT16 	RecordID;
	UINT8	RecordType;
	UINT32	Timestamp;
	UINT16  GeneratorID;
	UINT8	EVMRev;
} SELRecordHeader;

typedef struct { 
	UINT8	SensorType;
	UINT8	SensorNumber;
	UINT8 	EventDirType;
	UINT8   EventData1;
	UINT8   EventData2;
	UINT8   EventData3;
}SELEventData;
 
typedef struct { 
	SELRecordHeader     SELHeader; 
	SELEventData        SELData;
} DCMI_ADD_SEL_ENTRY_DATA; 

typedef struct { 
	DCMI_HI_REQ_HEADER  DcmiHeader;
	SELRecordHeader     SELHeader; 
	SELEventData        SELData;
	UINT8		    Commit;
} AddSELEntryHeader; 

typedef struct { 
	SELRecordHeader     SELHeader; 
	SELEventData        SELData;
	DCMI_ADDSEL_ENTRY   sDcmiAddSelEntry; 
} DcmiShareProtocol; 


typedef struct { 
	UINT8 CompletionCode; 
	UINT16 RecordID;
} DcmiSELResponse ; 
#pragma pack()
//AptioV server override start: dynamic MMCFG base change support.
#ifndef DYNAMIC_MMCFG_BASE_FLAG 
#define PCIE_CFG_ADDR(bus,dev,func,reg) \
  ( (UINTN)(PcdGet64 (PcdPciExpressBaseAddress) + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg))
#else
#define PCIE_CFG_ADDR(bus,dev,func,reg) \
  ( (UINTN) GetPciExpressBaseAddress() + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg))//AptioV server overrride: Dynamic mmcfg base address change
#endif
//AptioV server override end: dynamic MMCFG base change support.
#define HECI1_BUS	0x00
#define HECI1_DEV	0x16
#define HECI1_FUN	0x00
#define HECI_INTR_OFF	0x3C

#define MmioRead16(Address, Value)     (Value = (*(volatile UINT16*)(UINTN)(Address)))
#define MmioWrite16(Address, Value)     ((*(volatile UINT16*)(UINTN)(Address)) = Value)

#endif
