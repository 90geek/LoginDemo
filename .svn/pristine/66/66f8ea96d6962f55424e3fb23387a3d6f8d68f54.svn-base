//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file AmiNvmeController.h
    Protocol Header file for the Nvme Controller 

**/

#ifndef _NVME_CONTROLLER_PROTOCOL_H_
#define _NVME_CONTROLLER_PROTOCOL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define NVME_MANUFACTUREID_LENGTH   30

typedef struct {
    NVME_ADMIN_COMMAND          NvmCmd;
    BOOLEAN                     AdminOrNVMCmdSet;           // TRUE for Admin
    UINT16                      SQIdentifier;               // Queue 0 for Admin cmds and 1 for NVM cmds
    UINT32                      CmdTimeOut;                 // In msec.
    UINT8                       RetryCount;
} NVME_COMMAND_WRAPPER;

typedef struct {
    
    UINT64                      NvmeBarOffset;
    EFI_PCI_IO_PROTOCOL         *PciIO;
    EFI_HANDLE                  ControllerHandle;
    UINT16                      CommandIdentifierAdmin;
    UINT16                      CommandIdentifierQueue1;
    UINT64                      RawControllerCapabilities;      
    UINT32                      MaxQueueEntrySupported;
    BOOLEAN                     ContiguousQueueRequired;
    UINT8                       ArbitrationMechanismSupport;
    UINT8                       TimeOut;
    UINT8                       DoorBellStride;
    BOOLEAN                     NVMResetSupport;
    UINT8                       CmdSetsSupported;
    UINT32                      MemoryPageSizeMin;
    UINT32                      MemoryPageSizeMax;
    UINT32                      MemoryPageSize;                   // In Bytes
    NVME_COMMAND_WRAPPER        *NvmeCmdWrapper;                  // Will be used by internal routines
    
//----------------------------Admin Queue--------------------------------------------------------------
    UINT64                      AdminSubmissionUnAligned;         // Points to the start of the buffer
    UINT64                      AdminSubmissionQueue;             // Points to the start of the buffer Aligned
    UINT64                      AdminSubmissionQueueMappedAddr;   // Mapped address for the controller to use
    VOID                        *AdminSubmissionQueueUnMap;       // 
    UINTN                       AdminSubmissionUnAlignedSize;     // in Pages
    UINT64                      AdminCompletionUnAligned;
    UINT64                      AdminCompletionQueue;
    UINT64                      AdminCompletionQueueMappedAddr;
    VOID                        *AdminCompletionQueueUnMap;
    UINTN                       AdminCompletionUnAlignedSize;
    UINT16                      AdminSubmissionQueueSize;         // Max is 4KB
    UINT16                      AdminCompletionQueueSize;         // Max is 4KB
    UINT16                      AdminCompletionQueueHeadPtr;  
    UINT16                      AdminCompletionQueueTailPtr;  
    UINT16                      AdminSubmissionQueueHeadPtr;      // Updated from Completion queue entry
    UINT16                      AdminSubmissionQueueTailPtr;      // Updated when new cmds are issued
    UINT8                       AdminPhaseTag : 1;
    UINT8                       RESERVED : 7;

//----------------------------Queue1 for Nvme Cmds------------------------------------------------------
    UINT16                      NVMQueueNumber;
    UINT64                      Queue1SubmissionUnAligned;        // Points to the start of the buffer
    UINTN                       Queue1SubmissionUnAlignedSize;    // Original size
    UINT64                      Queue1SubmissionQueue;            // Aligned address
    UINT64                      Queue1SubmissionQueueMappedAddr;  // Address for controller to use
    VOID                        *Queue1SubmissionQueueUnMap;      
    UINT64                      Queue1CompletionUnAligned;
    UINTN                       Queue1CompletionUnAlignedSize;
    UINT64                      Queue1CompletionQueue;
    UINT64                      Queue1CompletionQueueMappedAddr;
    VOID                        *Queue1CompletionQueueUnMap;
    UINT32                      Queue1SubmissionQueueSize;
    UINT32                      Queue1CompletionQueueSize;
    UINT16                      Queue1CompletionQueueHeadPtr;  
    UINT16                      Queue1CompletionQueueTailPtr;  
    UINT16                      Queue1SubmissionQueueHeadPtr;      // Updated from Completion queue entry
    UINT16                      Queue1SubmissionQueueTailPtr;      // Updated when new cmds are issued
    UINT8                       Queue1PhaseTag : 1;
    UINT8                       RESERVED1 : 7;
    BOOLEAN                     ReInitializingQueue1;             // Flag used to prevent initializing Queue1 in an infinite loop
  
  //-----------------------------------------------------------------------------------------------------  
    VOID                        *LegacyNvmeBuffer;
    BOOLEAN                     NvmeInSmm;
    IDENTIFY_CONTROLLER_DATA    *IdentifyControllerData;  
    UINT32                      *ActiveNameSpaceIDs;  
    LIST_ENTRY                  ActiveNameSpaceList;              // Linked list of Active Name space found in this controller
} AMI_NVME_CONTROLLER_PROTOCOL;


extern EFI_GUID gAmiNvmeControllerProtocolGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
