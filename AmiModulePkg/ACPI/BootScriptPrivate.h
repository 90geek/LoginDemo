//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


/** @file BootScriptPrivate.h
    Boot script auxiliary data structures definitions

**/

#ifndef __BOOT_SCRIPT_PRIVATE__H__
#define __BOOT_SCRIPT_PRIVATE__H__

#include <efi.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TABLE_TYPE1(OpCode)				(OpCode)
#define TABLE_TYPE2(OpCode, Width)		((OpCode) + ((Width) << 8))

#define TABLE_END_OP_CODE				0xff

/**
    Boot script Write IO Data
    This function adds an I/O write record into a specified boot script table. On script execution, this 
	operation writes the presaved value into the specified I/O ports.
 
**/

typedef struct {
	UINT16	Type;
	UINT16	Port;///< The base address of the I/O operations. 
	UINT64	Count;///< The number of I/O operations to perform.
	//UINT8	Buffer[];
} BOOT_SCRIPT_WRITE_IO;

/**
    Boot script Read-Write IO Data
 	 This function adds an I/O read and write record into the specified boot script table. When the script 
	is executed, the register at Address is read, AND-ed with DataMask, and OR-ed with Data, and 
	finally the result is written back. 
**/

typedef struct {
	UINT16	Type;
	UINT16	Port;///< The base address of the I/O operations. 
	UINT64	Value;///< Data to be OR-ed.
	UINT64	Mask;///< Data mask to be AND-ed with the data read from the register.
} BOOT_SCRIPT_READ_WRITE_IO;

/**
    Boot script Poll IO Data
    A record for I/O reads the I/O location and continues when the exit criteria is satisfied
**/

typedef struct {
    UINT16 Type;
    UINT16 Port;///< The base address of the I/O operations. 
    UINT64 Mask;///< Mask used for the polling criteria.
    UINT64 Result;///< The comparison value used for the polling exit criteria.
} BOOT_SCRIPT_POLL_IO;



/**
    Boot script Write memory Data
 	When the script is executed, this operation writes the presaved value into the specified memory location. 
 	
**/

typedef struct {
	UINT16	Type;
	UINT64	Address;///< The base address of the memory operations.
//	UINT8	Value;
	UINT64	Count;///< The number of memory operations to perform.
	//UINT8	Buffer[];
} BOOT_SCRIPT_WRITE_MEM;

/**
    Boot script Read-Write memory Data
 	When the script is executed, the memory at Addressis read, AND-ed with DataMask, and OR-ed with Value, and 
	finally the result is written back. 
**/

typedef struct {
	UINT16	Type;
	UINT64	Address;///< The base address of the memory operations. 
	UINT64	Value;///< Data to be OR-ed.
	UINT64	Mask;///< Data mask to be AND-ed with the data read from the register.
} BOOT_SCRIPT_READ_WRITE_MEM;

/**
    Boot script Poll memory Data
	The memory read operation is repeated until (Data & DataMask) is equal to Result.
	
**/

typedef struct {
    UINT16 Type;
    UINT64 Address;///< The base address of the memory operations.
    UINT64 Mask;///< Mask used for the polling criteria.
    UINT64 Result;///< The comparison value used for the polling exit criteria.
} BOOT_SCRIPT_POLL_MEM;


/**
    Boot script Write PCI Data
	When the script is executed, this operation writes the presaved value into the specified location in PCI 
	configuration space.
**/

typedef struct {
	UINT16	Type;
	UINT64	Address;///< The address within the PCI configuration space.
	UINT64	Count;///< The number of PCI operations to perform.
	//UINT8	Buffer[];
} BOOT_SCRIPT_WRITE_PCI;

/**
    Boot script Read-Write PCI Data
    When the script is executed, the PCI configuration space location at Address is read, AND-ed with 
	Mask, and OR-ed with Value, and finally the result is written back.
 
**/
typedef struct {
	UINT16	Type;
	UINT64	Address;///< The address within the PCI configuration space.
	UINT64	Value;///< Data to be OR-ed.
	UINT64	Mask;///< Data mask to be AND-ed. 
} BOOT_SCRIPT_READ_WRITE_PCI;

/**
    Boot script Poll PCI Data
    The PCI configuration read operation is repeated until (Data& DataMask) is equal to Result.
 
**/

typedef struct {
    UINT16 Type;
    UINT64 Address;///< The address within the PCI configuration space.
    UINT64 Mask;///< Mask used for the polling criteria.
    UINT64 Result;///< The comparison value used for the polling exit criteria.
} BOOT_SCRIPT_POLL_PCI;

#pragma pack(push,1)

/**
    Boot script SMBUS command Data
    When the script is executed, this operation executes a specified SMBus command.
 
**/

typedef struct {
	UINT16						Type;
	EFI_SMBUS_DEVICE_ADDRESS	SlaveAddress;///< The SMBus address for the slave device thatthe operation is targeting.
	EFI_SMBUS_DEVICE_COMMAND	Command;///< The command that is transmitted by the SMBus host controller to the SMBus slave device. 
	EFI_SMBUS_OPERATION			Operation;///< Indicates which particular SMBus protocol it will use to execute the SMBus transactions.
	BOOLEAN						PecCheck;///< Defines if Packet Error Code (PEC) checking is required for this operation.
	UINT64						Length;///< The number of bytes that this operation will do.
	//UINT8						Buffer[];
} BOOT_SCRIPT_SMBUS_EXECUTE;

/**
    Boot script SMBUS command Data (32 Bit)
 	 When the script is executed, this operation executes a specified SMBus command. 
**/

typedef struct {
	UINT16						Type;
	UINT32                      SlaveAddress;///< The SMBus address for the slave device thatthe operation is targeting.
	UINT32	                    Command;///< The command that is transmitted by the SMBus host controller to the SMBus slave device. 
	EFI_SMBUS_OPERATION			Operation;///< Indicates which particular SMBus protocol it will use to execute the SMBus transactions.
	BOOLEAN						PecCheck;///< Defines if Packet Error Code (PEC) checking is required for this operation.
	UINT64						Length;///< The number of bytes that this operation will do.
	//UINT8						Buffer[];
} BOOT_SCRIPT_SMBUS_EXECUTE_32;
#pragma pack(pop)

/**
    Boot script stall Data
    When the script is executed, this operation will stall the system for Duration number of microseconds.
 
**/

typedef struct {
	UINT16	Type;
	UINT64	Duration;///< Duration in microseconds of the stall.
} BOOT_SCRIPT_STALL;

/**
    Boot script dispatch Data
    This function adds a dispatch record into a specified boot script table, with which it can run the 
	arbitrary code that is specified.
 
**/

typedef struct {
	UINT16					Type;
	EFI_PHYSICAL_ADDRESS	EntryPoint;///< Entry point of the code to be dispatched.
} BOOT_SCRIPT_DISPATCH;

#if PI_SPECIFICATION_VERSION>=0x0001000A
/**
    Boot script information Data
    This function is used to store debug information in the S3 data stream. 

**/
typedef struct {
	UINT16	Type;
	UINT32	Size;///< Length of the data in bytes.
	EFI_PHYSICAL_ADDRESS	MessagePtr;///< Pointer to the information to belogged in the boot script.
} BOOT_SCRIPT_INFORMATION;

/**
    Boot script Dispatch2 Data
    This function adds a dispatch record into a specified boot script table, with which it can run the 
	arbitrary code that is specified.

**/
typedef struct {
	UINT16					Type;
	EFI_PHYSICAL_ADDRESS	EntryPoint;///< Entry point of the code to be dispatched.
    EFI_PHYSICAL_ADDRESS	Context;///< Argument to be passed into the EntryPointof the code to be dispatched.
} BOOT_SCRIPT_DISPATCH2;

 
/**
    Boot script Write PCI Data
    When the script is executed, this operation writes the presaved value into the specified location in PCI 
	configuration space.
 
**/

typedef struct {
	UINT16	Type;
	UINT64	Address;///< The address within the PCI configuration space.
	UINT64	Count;///< The number of PCI operations to perform. 
    UINT16  Segment;///< The PCI segment number for Address.
	//UINT8	Buffer[];
} BOOT_SCRIPT_PCI_CFG2_WRITE;

/**
    Boot script Read-Write PCI Data
    When the script is executed, the PCI configuration space location at Address is read, AND-ed with 
	Mask, and OR-ed with Value, and finally the result is written back.

 
**/
typedef struct {
	UINT16	Type;
	UINT64	Address;///< The address within the PCI configuration space. 
	UINT64	Value;///< Data to be OR-ed.
	UINT64	Mask;///< Data mask to be AND-ed. 
    UINT16  Segment;///< The PCI segment number for Address.
} BOOT_SCRIPT_PCI_CFG2_READ_WRITE;

/**
    Boot script Poll IO Data (PI 1.1)
    The I/O read operation is repeated until either a Delay of at least 100 ns units has expired, 
    or (Data & Mask) is equal to Result. At least one I/O access is always performed regardless of the value of Delay.
 
**/

typedef struct {
    UINT16 Type;
    UINT16 Port;///< The base address of the I/O operations. 
    UINT64 Mask;///< Mask used for the polling criteria.
    UINT64 Result;///< The comparison value used for the polling exit criteria.
    UINT64 Delay;///< The number of 100ns units to poll. 
} BOOT_SCRIPT_IO_POLL;

/**
    Boot script Poll memory Data (PI 1.1)
    The memory read operation is repeated until either a timeout of Delay 100 ns units has expired, or 
    (Data & Mask) is equal to Result.
 
**/

typedef struct {
    UINT16 Type;
    UINT64 Address;///< The base address of the memory operations. 
    UINT64 Mask;///< Mask used for the polling criteria.
    UINT64 Result;///< The comparison value used for the polling exit criteria.
    UINT64 Delay;///< The number of 100ns units to poll. 
} BOOT_SCRIPT_MEM_POLL;

/**
    Boot script Poll PCI Data (PI 1.1)
    The PCI configuration read operation is repeated until either a timeout of Delay100 ns units has expired, 
    or (Data& Mask) is equal to Result.
    
 
**/

typedef struct {
    UINT16 Type;
    UINT64 Address;///< The address within the PCI configuration space.
    UINT64 Mask;///< Mask used for the polling criteria.
    UINT64 Result;///< The comparison value used for the polling exit criteria.
    UINT64 Delay;///< The number of 100ns units to poll. 
} BOOT_SCRIPT_PCI_CFG_POLL;

/**
    Boot script Poll PCI Data 2 (PI 1.1)
    The PCI configuration read operation is repeated until either a timeout of Delay100 ns units has expired, 
    or (Data& Mask) is equal to Result.
 
**/

typedef struct {
    UINT16 Type;
    UINT64 Address;///< The address within the PCI configuration space.
    UINT64 Mask;///< Mask used for the polling criteria.
    UINT64 Result;///< The comparison value used for the polling exit criteria.
    UINT64 Delay;///< The number of 100ns units to poll. 
    UINT16 Segment;///< The PCI segment number for Address.
} BOOT_SCRIPT_PCI_CFG2_POLL;

/**
    Boot script Label
 
**/
typedef struct {
	UINT16	Type;
	UINT32	Size;
	//UINT8	Buffer[];
} BOOT_SCRIPT_LABEL;

/**
    Internal Boot script info structure
 
**/

typedef struct {
    UINT32 UniqueIndex;
    UINT32 Length;
} BOOT_SCRIPT_INFO_STRUCTURE;
#endif

/**
    Boot script end table marker
 
**/

typedef struct {
	UINT16 Type;
} BOOT_SCRIPT_TABLE_END;

/**
    Boot script data union
 
**/

typedef union {
	BOOT_SCRIPT_WRITE_IO		WrIo;
	BOOT_SCRIPT_READ_WRITE_IO	RwIo;
    BOOT_SCRIPT_POLL_IO         PollIo;
	BOOT_SCRIPT_WRITE_MEM		WrMem;
	BOOT_SCRIPT_READ_WRITE_MEM	RwMem;
    BOOT_SCRIPT_POLL_MEM        PollMem;
	BOOT_SCRIPT_WRITE_PCI		WrPci;
	BOOT_SCRIPT_READ_WRITE_PCI	RwPci;
    BOOT_SCRIPT_POLL_PCI        PollPci;
	BOOT_SCRIPT_SMBUS_EXECUTE	ExecSmbus;
	BOOT_SCRIPT_STALL			Stall;
	BOOT_SCRIPT_DISPATCH		Dispatch;
#if PI_SPECIFICATION_VERSION>=0x0001000A
    BOOT_SCRIPT_INFORMATION         Info;
    BOOT_SCRIPT_DISPATCH2		    Dispatch2;
    BOOT_SCRIPT_PCI_CFG2_WRITE      WrPci2;
    BOOT_SCRIPT_PCI_CFG2_READ_WRITE RwPci2;
    BOOT_SCRIPT_IO_POLL             IoPoll;
    BOOT_SCRIPT_MEM_POLL            MemPoll;
    BOOT_SCRIPT_PCI_CFG_POLL        PciPoll;
    BOOT_SCRIPT_PCI_CFG2_POLL       PciPoll2;
#endif
	BOOT_SCRIPT_TABLE_END		End;	
} BOOT_SCRIPT_DATA;

VOID CallbackReadyToBoot(
	IN EFI_EVENT	Event,
	IN VOID			*Context
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
