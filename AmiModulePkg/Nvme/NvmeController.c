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

/** @file NvmeController.c
    Provides Access to Nvme Controller

**/

//---------------------------------------------------------------------------

#include "NvmeIncludes.h"
#include "NvmeBus.h"

//---------------------------------------------------------------------------


/**
    Creates Submission and Completion Queue

        
    @param NVMeController 
    @param NvmeCmdWrapper 
    @param QueueNumber 
    @param QueueSize 

    @retval EFI_STATUS

    @note  Can be called recursively  

**/

EFI_STATUS
CreateAdditionalSubmissionCompletionQueue ( 
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
    IN  UINT16                          QueueNumber,
    IN  UINT32                          QueueSize
)
{
   
    EFI_STATUS              Status;
    COMPLETION_QUEUE_ENTRY  CompletionData;
    UINTN                   AllocatePageSize;
    UINT64                  QueueAddress = 0;
    
    
    // Clear memory
    SetMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0);
    
    // Allocate memory only if the pointer is NULL
    if (NvmeController->Queue1CompletionUnAligned == 0) {
        AllocatePageSize = NvmeController->MemoryPageSize + QueueSize * sizeof(COMPLETION_QUEUE_ENTRY);
    
        Status = NvmeController->PciIO->AllocateBuffer (NvmeController->PciIO,
                                                 AllocateAnyPages,
                                                 EfiRuntimeServicesData,
                                                 EFI_SIZE_TO_PAGES(AllocatePageSize),
                                                 (VOID **)&(QueueAddress),
                                                 EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                                 );
            
        if (EFI_ERROR(Status)) {
            return Status;
        }
    
        NvmeController->Queue1CompletionUnAligned = QueueAddress;
        NvmeController->Queue1CompletionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
        NvmeController->Queue1CompletionQueue = (QueueAddress & ~(NvmeController->MemoryPageSize - 1)) + 
                                                NvmeController->MemoryPageSize;
    
        NvmeController->Queue1CompletionQueueSize = QueueSize;
        
        SetMem((VOID *)NvmeController->Queue1CompletionQueue, \
                            NvmeController->Queue1CompletionQueueSize * sizeof (COMPLETION_QUEUE_ENTRY), 0);
        
        Status = NvmeController->PciIO->Map ( NvmeController->PciIO, 
                                      EfiPciIoOperationBusMasterCommonBuffer,
                                      (VOID *)NvmeController->Queue1CompletionQueue,
                                      &AllocatePageSize,
                                      &NvmeController->Queue1CompletionQueueMappedAddr,
                                      &NvmeController->Queue1CompletionQueueUnMap
                                      );
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    // Build NVME command
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = CREATE_IO_COMPLETION_QUEUE;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.NSID = 0;
            
    NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)NvmeController->Queue1CompletionQueueMappedAddr;
    NvmeCmdWrapper->NvmCmd.PRP2 = 0;
    NvmeCmdWrapper->NvmCmd.CDW10 = ((QueueSize - 1) << 16 )+ QueueNumber;
    NvmeCmdWrapper->NvmCmd.CDW11 = 1;           // Contiguous
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Cmd issued in Queue0
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    
    if (EFI_ERROR(Status)) {
        goto CreateAdditionalSubmissionCompletionQueue_Exit;
    }

    // Allocate memory only if the pointer is NULL
    if (NvmeController->Queue1SubmissionUnAligned == 0) { 
        
        AllocatePageSize = NvmeController->MemoryPageSize + 
                            QueueSize * sizeof(NVME_ADMIN_COMMAND);  
        
        Status = NvmeController->PciIO->AllocateBuffer (NvmeController->PciIO,
                                             AllocateAnyPages,
                                             EfiRuntimeServicesData,
                                             EFI_SIZE_TO_PAGES(AllocatePageSize),
                                             (VOID **)&(QueueAddress),
                                             EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                             );
                    
        if (EFI_ERROR(Status)) {
            return Status;
        }
    
        NvmeController->Queue1SubmissionUnAligned = QueueAddress;
        NvmeController->Queue1SubmissionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
        NvmeController->Queue1SubmissionQueue = (QueueAddress & ~(NvmeController->MemoryPageSize - 1)) + 
                                                NvmeController->MemoryPageSize;
    
        NvmeController->Queue1SubmissionQueueSize = QueueSize;
        SetMem((VOID *)NvmeController->Queue1SubmissionQueue, \
                                NvmeController->Queue1SubmissionQueueSize * sizeof(NVME_ADMIN_COMMAND), 0);
    
        Status = NvmeController->PciIO->Map ( NvmeController->PciIO, 
                                         EfiPciIoOperationBusMasterCommonBuffer,
                                         (VOID *)NvmeController->Queue1SubmissionQueue,
                                         &AllocatePageSize,
                                         &NvmeController->Queue1SubmissionQueueMappedAddr,
                                         &NvmeController->Queue1SubmissionQueueUnMap
                                         );
                
        if (EFI_ERROR(Status)) {
            return Status;
        }
                
    }
    
    // Build NVME command
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = CREATE_IO_SUBMISSION_QUEUE;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.NSID = 0;
            
    NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64)NvmeController->Queue1SubmissionQueueMappedAddr;
    NvmeCmdWrapper->NvmCmd.PRP2 = 0;
    NvmeCmdWrapper->NvmCmd.CDW10 = ((QueueSize - 1) << 16 )+ QueueNumber;
    NvmeCmdWrapper->NvmCmd.CDW11 = (QueueNumber << 16) + 1;           // Contiguous
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Cmd issued to admin queue
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    
    CreateAdditionalSubmissionCompletionQueue_Exit:

    NvmeController->Queue1PhaseTag = FALSE;
    
    NvmeController->Queue1SubmissionQueueTailPtr = 0;
    NvmeController->Queue1SubmissionQueueHeadPtr = 0;
    
    NvmeController->Queue1CompletionQueueTailPtr = 0;
    NvmeController->Queue1CompletionQueueHeadPtr = 0;
    
    return Status;
   
}

/**
    Programs PRP2 with the list of page address for data transfer

    @param This 

    @retval EFI_STATUS

**/

EFI_STATUS
ProgramPRP2List (
    IN  UINT64  *PRP2List, 
    IN  UINT32  PageSize, 
    IN  UINTN   BufferAddress,
    IN  UINTN   BufferSize,
    IN  UINTN   *PRP2TransferSize
)
{
    
    UINTN          TotalNumberOfEntries = PageSize / 8;        // Each entry 64 bytes long
            
    *PRP2TransferSize = 0;
    
    do {
        
        *PRP2List++ = BufferAddress;
        if (BufferSize >= PageSize) {
            *PRP2TransferSize += PageSize;
            BufferAddress += PageSize;
            BufferSize -= PageSize;
        } else {
              *PRP2TransferSize = *PRP2TransferSize + (UINT32)BufferSize;
              BufferAddress += BufferSize;
              BufferSize = 0;
        }
        
    } while (--TotalNumberOfEntries && (BufferSize > 0));
    
    return  EFI_SUCCESS;
    
}

/**
    Read/Write data from the given LBA address

        
    @param This 
    @param MediaId 
    @param LBA
    @param BufferSize 
    @param Buffer 
    @param ReadWriteOpCode 

    @retval EFI_STATUS

**/

EFI_STATUS
NvmeReadWriteBlocks (
    IN  ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
    IN  UINT32                  MediaId,
    IN  EFI_LBA                 LBA,
    IN  UINTN                   BufferSize,
    OUT VOID                    *Buffer,
    OUT COMPLETION_QUEUE_ENTRY  *NvmeCompletionData,
    IN  UINT8                   ReadWriteOpCode
)
{
    
    EFI_STATUS                    Status = EFI_SUCCESS;
    AMI_NVME_CONTROLLER_PROTOCOL  *NvmeController = ActiveNameSpace->NvmeController;
    EFI_BLOCK_IO_MEDIA            *BlkMedia = ActiveNameSpace->NvmeBlockIO.Media;
    NVME_COMMAND_WRAPPER          *NvmeCmdWrapper = NvmeController->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY        CompletionData;
    COMPLETION_QUEUE_ENTRY        *pCompletionData = &CompletionData;
    UINTN                         DataN;
    UINT32                        LBACountInOneTransfer;
    UINTN                         PRP1TransferSize;
    UINTN                         PRP2TransferSize;
    UINTN                         MappedBufferSize = BufferSize;
    EFI_PHYSICAL_ADDRESS          MappedBuffer;
    VOID                          *BufferUnMap;
    
    if (!NvmeController->NvmeInSmm) {
        DEBUG((EFI_D_VERBOSE,"LBA : %lx BufferSize : %lx Buffer : %lx Opcode : %x", LBA, BufferSize, Buffer, ReadWriteOpCode));
    }
    
    // Check if Media ID matches
    if (BlkMedia->MediaId != MediaId) {
        return EFI_MEDIA_CHANGED;
    }

    if (BufferSize == 0) {
        return EFI_SUCCESS;
    }
    
    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    if((BlkMedia->IoAlign > 1 ) && ((UINTN)Buffer % BlkMedia->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Check whether the block size is multiple of BlkMedia->BlockSize
    DataN = BufferSize % BlkMedia->BlockSize;
    if (DataN){
	    return EFI_BAD_BUFFER_SIZE;
    }

    // Check for Valid start LBA #
    if (LBA > BlkMedia->LastBlock) {
        return EFI_INVALID_PARAMETER;
    }

    // Check for Valid End LBA #
    DataN = BufferSize / BlkMedia->BlockSize;
    if (LBA + DataN > BlkMedia->LastBlock + 1) {
        return EFI_INVALID_PARAMETER;
    }

    do {
        // Limit the transfer size to MDTS value
        if (NvmeController->IdentifyControllerData->MDTS && (MappedBufferSize > ((UINTN)LShiftU64(1, NvmeController->IdentifyControllerData->MDTS) * NvmeController->MemoryPageSizeMin))){
            MappedBufferSize = (UINTN)LShiftU64(1, NvmeController->IdentifyControllerData->MDTS) * NvmeController->MemoryPageSizeMin;
        }
       
        // After MAP, Mapped BufferSize may not be same as input. 
        // So need to complete the transfer in multiple loops.
        // When the call originates from SMM, don't call Map function
        MappedBuffer = (EFI_PHYSICAL_ADDRESS) Buffer;
        if (!NvmeController->NvmeInSmm) {

            Status = NvmeController->PciIO->Map ( NvmeController->PciIO,
                                          ((ReadWriteOpCode == NVME_READ) || (ReadWriteOpCode == NVME_COMPARE)) ? EfiPciIoOperationBusMasterWrite : EfiPciIoOperationBusMasterRead,
                                          Buffer,
                                          &MappedBufferSize,
                                          &MappedBuffer,
                                          &BufferUnMap
                                          );
          
            if (EFI_ERROR(Status)) {
                return Status;
            }
        }
    
        SetMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0); 
        LBACountInOneTransfer = 0;

        PRP2TransferSize = 0;
       
        NvmeCmdWrapper->NvmCmd.PRP1 = (UINT64) MappedBuffer; 
        PRP1TransferSize = NvmeController->MemoryPageSize - 
                            (MappedBuffer & ((UINTN)(NvmeController->MemoryPageSize) - 1));
        
        // If all data can be transferred using only PRP1 then do that.
        if (PRP1TransferSize >= MappedBufferSize) {
            PRP1TransferSize = MappedBufferSize;
        }
        
        // Do we need PRP2
        if (MappedBufferSize - PRP1TransferSize) {
            
            // Do we need either a PRP2 pointer or a List
            if (MappedBufferSize - PRP1TransferSize <= NvmeController->MemoryPageSize) {
                NvmeCmdWrapper->NvmCmd.PRP2 = NvmeCmdWrapper->NvmCmd.PRP1 + PRP1TransferSize;
                PRP2TransferSize = MappedBufferSize - PRP1TransferSize;
            } else {
                  // We need PRP2 List
                  Status = ProgramPRP2List (ActiveNameSpace->PRP2List, NvmeController->MemoryPageSize, \
                                        (UINTN)MappedBuffer + PRP1TransferSize, \
                                        MappedBufferSize -  PRP1TransferSize, &PRP2TransferSize
                                        );
                
                  if (EFI_ERROR(Status)) {
                    break;
                }
                
                  NvmeCmdWrapper->NvmCmd.PRP2 = (UINT64) ActiveNameSpace->PRP2ListMappedAddr;
            }
        }
        
        LBACountInOneTransfer = (UINT32)((PRP1TransferSize + PRP2TransferSize) / BlkMedia->BlockSize);
        
        // Build NVME command
        NvmeCmdWrapper->NvmCmd.CMD0.Opcode = ReadWriteOpCode;
        NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
        NvmeCmdWrapper->NvmCmd.CMD0.PSDT = 0;
        NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierQueue1;
        NvmeCmdWrapper->NvmCmd.NSID = ActiveNameSpace->ActiveNameSpaceID;
        
        NvmeCmdWrapper->NvmCmd.MPTR = 0;
        NvmeCmdWrapper->NvmCmd.CDW10 = (UINT32)LBA;       
        NvmeCmdWrapper->NvmCmd.CDW11 = (UINT32) RShiftU64 (LBA, 32);           
        NvmeCmdWrapper->NvmCmd.CDW12 = 0x80000000 + (LBACountInOneTransfer - 1);           
        NvmeCmdWrapper->NvmCmd.CDW13 = 0;           
        NvmeCmdWrapper->NvmCmd.CDW14 = 0;           
            
        NvmeCmdWrapper->AdminOrNVMCmdSet = FALSE;
        NvmeCmdWrapper->SQIdentifier = NvmeController->NVMQueueNumber;
        NvmeCmdWrapper->CmdTimeOut = 1000;
        
        // If caller has passed buffer to return controller status, use it.
        if (NvmeCompletionData) {
            pCompletionData = NvmeCompletionData;
        }
        
        Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, pCompletionData);
        
        if (EFI_ERROR(Status)) {
            if (!NvmeController->NvmeInSmm) {
                NvmeController->PciIO->Unmap(NvmeController->PciIO, BufferUnMap);
            }
            break;
        }
        
        // Remaining Bytes to be transferred
        MappedBufferSize -= (LBACountInOneTransfer * BlkMedia->BlockSize);
        
        // Update LBA # for next transfer if needed        
        LBA += LBACountInOneTransfer;
        
       // Adjust the Buffer address
       Buffer =(VOID*) ((UINTN) Buffer + (LBACountInOneTransfer * BlkMedia->BlockSize));
       BufferSize -= (LBACountInOneTransfer * BlkMedia->BlockSize);

       // When PciIO->Map is called, it might not map the complete buffer.
       // After the complete MappedBufferSize is transferred, if there is a left over do that transfer also
       if (MappedBufferSize == 0) {
           MappedBufferSize = BufferSize;
       }
       
       if (!NvmeController->NvmeInSmm) {
           NvmeController->PciIO->Unmap(NvmeController->PciIO, BufferUnMap);
       }
       
    } while (MappedBufferSize);

    if (!NvmeController->NvmeInSmm) {
        DEBUG((EFI_D_VERBOSE,"%r \n", Status));
    }
    
    return Status;
    
}

/**
    Execute Admin and Nvme cmds

    @param NvmeController 
    @param NvmeCmdWrapper 
    @param CmdCompletionData 

    @retval EFI_STATUS

    @note  If the cmd needs to be retried due to a failure, caller can 
    initialize the RetryCount.Can be called recursively.


**/

EFI_STATUS
ExecuteNvmeCmd (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY          *CmdCompletionData
)

{
    EFI_STATUS      Status;
    
    if (!NvmeController->NvmeInSmm) {
        PrintNvmeCmdWrapper (NvmeCmdWrapper);
    }
    
    do {
        // Because of recursive nature and retry mechanism, cmd identifier needs to be updated just before giving the call.
        NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->CommandIdentifierAdmin : \
                                                         NvmeController->CommandIdentifierQueue1;
        
        NvmeCmdWrapper->AdminOrNVMCmdSet ? (Status = AddToAdminSubmissionQueue(NvmeController, NvmeCmdWrapper)) : \
                (Status = AddToQueue1SubmissionQueue(NvmeController, NvmeCmdWrapper));
    
        if (EFI_ERROR(Status)) {
            continue;
        }
    
        Status = UpdateDoorBellRegister(NvmeController, 
                                        NvmeCmdWrapper->SQIdentifier,
                                        NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->AdminSubmissionQueueTailPtr :
                                        NvmeController->Queue1SubmissionQueueTailPtr 
                                        );

        if (EFI_ERROR(Status)) {
            continue;
        }

        //Wait for cmd to complete
        if (NvmeCmdWrapper->NvmCmd.CMD0.Opcode != ASYNC_EVENT_REQUEST) {
            Status = WaitForCompletionQueueUpdate(NvmeController, NvmeCmdWrapper, CmdCompletionData);
        }
    
    } while (EFI_ERROR(Status) && NvmeCmdWrapper->RetryCount--);
    
    return  Status;
    
}

/**
    Submits the cmd to the Admin Submission queue


    @param NvmeController 
    @param NvmeCmdWrapper 

    @retval EFI_STATUS

**/

EFI_STATUS
AddToAdminSubmissionQueue (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper
)
{
    EFI_STATUS          Status;
    UINT64              DestinationAddress;
    
    // Is Admin Queue full?
    if (NvmeController->AdminSubmissionQueueHeadPtr) {  // Non-zero value
        if ((NvmeController->AdminSubmissionQueueTailPtr - 1) == NvmeController->AdminSubmissionQueueHeadPtr){
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
            
            Status = RecreateAllQueues (NvmeController);
            if (EFI_ERROR(Status)) {            
                return EFI_OUT_OF_RESOURCES;
            }
          
        }
    } else {
        // If Head is at the start and Tail is at the end, then queue is full
          if (NvmeController->AdminSubmissionQueueTailPtr == (NvmeController->AdminSubmissionQueueHeadPtr + 
                                                            NvmeController->AdminSubmissionQueueSize - 1)) {
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
              Status = RecreateAllQueues (NvmeController);
              if (EFI_ERROR(Status)) {            
                  return EFI_OUT_OF_RESOURCES;
              }
          }
    }
    
    // Copy cmd to Admin Queue
    DestinationAddress = NvmeController->AdminSubmissionQueue + (
                        NvmeController->AdminSubmissionQueueTailPtr * sizeof(NVME_ADMIN_COMMAND));
    
#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        DEBUG((EFI_D_VERBOSE, "Destination Address for Cmd               : %016lx\n", DestinationAddress));
    }
#endif
    
    CopyMem ((VOID *)DestinationAddress, &(NvmeCmdWrapper->NvmCmd), sizeof(NVME_ADMIN_COMMAND));
    
    NvmeController->AdminSubmissionQueueTailPtr++;
    
    // Check if there is a roller over
    if (NvmeController->AdminSubmissionQueueTailPtr >= (NvmeController->AdminSubmissionQueueSize)) {
        NvmeController->AdminSubmissionQueueTailPtr = 0;
    }
    
    return EFI_SUCCESS;
    
}

/**
    Submits the Nvme cmd to the Queue1 Submission queue

    @param  NvmeController 
    @param  NvmeCmdWrapper 

    @retval EFI_STATUS

**/

EFI_STATUS
AddToQueue1SubmissionQueue (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper
)
{
    EFI_STATUS          Status;
    UINT64              DestinationAddress;
    
    // Is Queue full? If Tail is one less than the Head queue is full.
    if (NvmeController->Queue1SubmissionQueueHeadPtr) {  // Non-zero value
        if ((NvmeController->Queue1SubmissionQueueTailPtr - 1) == NvmeController->Queue1SubmissionQueueHeadPtr){
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
            Status = RecreateQueue1 (NvmeController);
            if (EFI_ERROR(Status)) {    
                return EFI_OUT_OF_RESOURCES;
            }
            
        }
    } else { 
          // If Head is at the start and Tail is at the end, then queue is full
          if (NvmeController->Queue1SubmissionQueueTailPtr == (NvmeController->Queue1SubmissionQueueHeadPtr + 
                                                        NvmeController->Queue1SubmissionQueueSize - 1)) {
              
              // In this design, queue should never get filled up. 
              // If it does something is wrong. Delete and start all over again.
              
              Status = RecreateQueue1 (NvmeController);
              if (EFI_ERROR(Status)) {		    
                  return EFI_OUT_OF_RESOURCES;
              }
          }
    }
    
    // Copy cmd to Admin Queue
    DestinationAddress = NvmeController->Queue1SubmissionQueue + 
                        (NvmeController->Queue1SubmissionQueueTailPtr * sizeof(NVME_ADMIN_COMMAND));

#if NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        DEBUG((EFI_D_VERBOSE, "Destination Address for Cmd               : %016lx\n", DestinationAddress));
    }
#endif
    
    CopyMem ((VOID *)DestinationAddress, &(NvmeCmdWrapper->NvmCmd), sizeof(NVME_ADMIN_COMMAND));
    
    NvmeController->Queue1SubmissionQueueTailPtr++; 
    
    // Check if there is a roller over
    if (NvmeController->Queue1SubmissionQueueTailPtr >= NvmeController->Queue1SubmissionQueueSize) {
        NvmeController->Queue1SubmissionQueueTailPtr = 0;
    }
    
    return EFI_SUCCESS;
    
}

/**
    Update door bell register for the controller to start executing the cmd

    @param  NvmeController 
    @param  QueueNumber 
    @param  Value 

    @retval EFI_STATUS

**/

EFI_STATUS
UpdateDoorBellRegister (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  UINT16                          QueueNumber,
    IN  UINT32                          Value
)
{
    
    UINT32      Offset;
    
    // Update Door Bell Register
    Offset = QUEUE_DOORBELL_OFFSET(QueueNumber, 0, NvmeController->DoorBellStride);
    
#if  NVME_VERBOSE_PRINT  
    if (!NvmeController->NvmeInSmm) {
        DEBUG((EFI_D_VERBOSE, "\nDoorBell Offset %016lx Value %08X\n", NvmeController->NvmeBarOffset + Offset, Value));
    }
#endif
    
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset) = Value;
    return EFI_SUCCESS;
    
}

/**
    Checks for the completion queue for the correct PhaseTag, 
    Queue Identified and Cmd Identifier.

    @param  NvmeController 
    @param  NvmeCmdWrapper 
    @param  CmdCompletionData 

    @retval EFI_STATUS

**/

EFI_STATUS
WaitForCompletionQueueUpdate (
    IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController,
    IN  NVME_COMMAND_WRAPPER                *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY              *CmdCompletionData 
)
{
    
    EFI_STATUS              Status;
    UINT32                  TimeOut = NvmeCmdWrapper->CmdTimeOut;
    UINT32                  Offset;
    COMPLETION_QUEUE_ENTRY  *pCmdCompletionData;
    UINT16                  CommandIdentifier = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->CommandIdentifierAdmin : \
                                                        NvmeController->CommandIdentifierQueue1; 
    
    UINT64                  CompletionQueueStart = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->AdminCompletionQueue : \
                                                NvmeController->Queue1CompletionQueue; 
    
    UINT16                  CompletionQueueHeadPtr = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->AdminCompletionQueueHeadPtr :\
                                                NvmeController->Queue1CompletionQueueHeadPtr;
    
    // Toggle expected phase tag on every roll over
    if (CompletionQueueHeadPtr == 0) {
            NvmeCmdWrapper->AdminOrNVMCmdSet ? (NvmeController->AdminPhaseTag = ~NvmeController->AdminPhaseTag) : \
                        (NvmeController->Queue1PhaseTag = ~NvmeController->Queue1PhaseTag);
    }
    
    // Get the offset to the Command Completion Queue Head Pointer
    pCmdCompletionData = (COMPLETION_QUEUE_ENTRY *)(CompletionQueueStart + CompletionQueueHeadPtr * sizeof(COMPLETION_QUEUE_ENTRY));
    
    do {
        // Check whether Command Identifier, SQ ID matches and Phase Tag matches with the cmd issued.
        if ((pCmdCompletionData->CommandIdentifier == CommandIdentifier) && \
            (pCmdCompletionData->SQIdentifier == NvmeCmdWrapper->SQIdentifier) && \
            (pCmdCompletionData->PhaseTag == (NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->AdminPhaseTag : NvmeController->Queue1PhaseTag)))
        {
            break;
        }
        
        // check if there are any fatal errors
        if (CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & CSTS_CFS){
            
            if (!NvmeController->NvmeInSmm) {
                DEBUG((EFI_D_ERROR, "Nvme Fatal Error\n"));
            }
            return EFI_DEVICE_ERROR;            
            
        }
        
        MicroSecondDelay (1000);

    } while (--TimeOut);
    
    if (!NvmeController->NvmeInSmm) { 
        PrintCommandCompletionData (pCmdCompletionData);
    }
    
    
    if (!TimeOut) {
        
        // This is a fatal condition. We should expect some kind of response from the controller. 
        // If not we have to either wait for more time or delete and recreate the queue
        
        NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->CommandIdentifierAdmin++ : \
                                            NvmeController->CommandIdentifierQueue1++;
        
        if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
            Status = RecreateAllQueues(NvmeController);
        } else {
            Status = RecreateQueue1(NvmeController);
        }
        
        if (EFI_ERROR(Status)) {
            // If recreating the queue gets an error. nothing can be done.
            NvmeCmdWrapper->RetryCount = 0;
        } else {
            // Retry the cmd one more time
            NvmeCmdWrapper->RetryCount++;
        }
        
        return EFI_DEVICE_ERROR;
    }
    
    // Update HeadPtr from Completion Queue. 
    // Check what Queue was cmd posted to and then update the corresponding Head/Tail pointer
    if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
        NvmeController->AdminSubmissionQueueHeadPtr = pCmdCompletionData->SQHeadPointer;
        NvmeController->AdminCompletionQueueHeadPtr = NvmeController->AdminSubmissionQueueHeadPtr;
        Offset = QUEUE_DOORBELL_OFFSET(NvmeCmdWrapper->SQIdentifier, 1, NvmeController->DoorBellStride);
        CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset) = NvmeController->AdminCompletionQueueHeadPtr;
    } else { 
        NvmeController->Queue1SubmissionQueueHeadPtr = pCmdCompletionData->SQHeadPointer;
        NvmeController->Queue1CompletionQueueHeadPtr = NvmeController->Queue1SubmissionQueueHeadPtr;
        Offset = QUEUE_DOORBELL_OFFSET(NvmeCmdWrapper->SQIdentifier, 1, NvmeController->DoorBellStride);
        CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset) = NvmeController->Queue1CompletionQueueHeadPtr;   
    }
    
    // Check whether all cmds submitted has been completed. CompletionQueue Head pointer should give a clue on
    // how many cmds where executed.
    if (pCmdCompletionData->StatusCode || pCmdCompletionData->StatusCodeType) {
        Status = EFI_DEVICE_ERROR;
    } else {
        Status = EFI_SUCCESS;
    }

#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
            DEBUG((EFI_D_VERBOSE, "AdminSubmissionQueueHeadPtr %08X\n", NvmeController->AdminSubmissionQueueHeadPtr));
            DEBUG((EFI_D_VERBOSE, "AdminSubmissionQueueTailPtr %08X\n", NvmeController->AdminSubmissionQueueTailPtr));
            DEBUG((EFI_D_VERBOSE, "AdminCompletionQueueHeadPtr %08X\n", NvmeController->AdminCompletionQueueHeadPtr));
            DEBUG((EFI_D_VERBOSE, "AdminCompletionQueueTailPtr %08X\n", NvmeController->AdminCompletionQueueTailPtr));
        } else {
            DEBUG((EFI_D_VERBOSE, "Queue1SubmissionQueueHeadPtr %08X\n", NvmeController->Queue1SubmissionQueueHeadPtr));
            DEBUG((EFI_D_VERBOSE, "Queue1SubmissionQueueTailPtr %08X\n", NvmeController->Queue1SubmissionQueueTailPtr));
            DEBUG((EFI_D_VERBOSE, "Queue1CompletionQueueHeadPtr %08X\n", NvmeController->Queue1CompletionQueueHeadPtr));
            DEBUG((EFI_D_VERBOSE, "Queue1CompletionQueueTailPtr %08X\n", NvmeController->Queue1CompletionQueueTailPtr));
        }
    }
#endif
    
    // Update o/p buffer
    CopyMem ((VOID *)CmdCompletionData, pCmdCompletionData, sizeof(COMPLETION_QUEUE_ENTRY));
    NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeController->CommandIdentifierAdmin++ : NvmeController->CommandIdentifierQueue1++;
    
    return Status;
    
}

/**
    Delete Admin and other Completion/Submission queue and 
    create it back again.

    @param  NvmeController 

    @retval EFI_STATUS

    @note  This procedure will be called if the queue gets filled up. 
    This situation shouldn't generally happen as each cmd is completed in 
    our case. So both Head and Tail should point to the same location 
    before and after cmd is executed.One possibility for calling this 
    routine will be when the cmd doesn't get completed and Completion 
    Queue doesn't get updated by the controller. Also any Set Feature 
    cmd that was issued during initialization should be re-issued here.

**/

EFI_STATUS
RecreateAllQueues (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController
)
{
    
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT32          ProgramCC = 0;
    UINT32          Delay;

    // In SMM, this function is not supported
    if (NvmeController->NvmeInSmm) {
        return EFI_DEVICE_ERROR;
    }
    
#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        DEBUG((EFI_D_ERROR, "Recreate Admin Queue : "));
    }
#endif
 
    ProgramCC = CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CC);
    
    // Check if the controller is already running. If yes stop it.
    Delay = NvmeController->TimeOut * 500;
    if (CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CC) & 0x1) {
        
        //  Clear Control register
        CONTROLLER_REG32 (NvmeController->NvmeBarOffset, Offset_CC) = 0;
        do {
            if (!(CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & 0x1)) {
                break;
            }
            MicroSecondDelay (1000);
        } while (--Delay);
        
    }
    
    if (!Delay) {
        goto  RecreateAllQueues_Error;  
    }
    
    // Program Admin Queue Size and Base Address
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Aqa) =  
             ((NvmeController->AdminCompletionQueueSize - 1) << 16) + (NvmeController->AdminSubmissionQueueSize - 1);
     
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Asq) = 
             (UINT32) NvmeController->AdminSubmissionQueue;
     
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Asq + 4) =  
             (UINT32) RShiftU64(NvmeController->AdminSubmissionQueue, 32);
     
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Acq) =  
             (UINT32)NvmeController->AdminCompletionQueue;
     
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_Acq + 4) =  
             (UINT32) RShiftU64(NvmeController->AdminCompletionQueue, 32);

    NvmeController->AdminPhaseTag = FALSE;

    // Enable Controller
    CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CC) = (ProgramCC | 1);
     
    // Wait for the controller to get ready
    // Check if the controller is already running. If yes stop it.
    Delay = NvmeController->TimeOut * 500;
    do {
        if ((CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset_CSTS) & 0x1)) {
            break;
        }
        
        MicroSecondDelay (1000);
    } while (--Delay);
         
RecreateAllQueues_Error:     
    if (!Delay) {
        Status = EFI_DEVICE_ERROR;
#if  NVME_VERBOSE_PRINT
        if (!NvmeController->NvmeInSmm) {
            DEBUG((EFI_D_ERROR, "Status  %r\n", Status));
        }
#endif
        return Status;
    }
    
    NvmeController->AdminSubmissionQueueHeadPtr = 0;
    NvmeController->AdminSubmissionQueueTailPtr = 0;
    NvmeController->AdminCompletionQueueHeadPtr = 0;
    NvmeController->AdminCompletionQueueTailPtr = 0;
    NvmeController->AdminPhaseTag = FALSE;
    
    if (!NvmeController->ReInitializingQueue1) {
        Status = RecreateQueue1 (NvmeController);
    }
    
    return Status;
}

/**
    Delete Completion and Submission queue and create it back again.

    @param  NvmeController 

    @retval EFI_STATUS

    @note  This procedure will be called if the queue gets filled up. 
    This situation shouldn't generally happen as each cmd is completed in 
    our case. So both Head and Tail should point to the same location 
    before and after cmd is executed. One possibility for calling this 
    routine will be when the cmd doesn't get completed and Completion 
    Queue doesn't get updated by the controller. Can be called recursively.

**/

EFI_STATUS
RecreateQueue1 (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController
)
{
    
    EFI_STATUS                      Status;
    NVME_COMMAND_WRAPPER            *NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY          CompletionData;

    // In SMM, this function not supported
    if (NvmeController->NvmeInSmm) {
        return EFI_DEVICE_ERROR;
    }
    
#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        DEBUG((EFI_D_ERROR, "Recreate Queue1 : "));
    }
#endif
    
    NvmeController->ReInitializingQueue1 = TRUE;
    
    Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof(NVME_COMMAND_WRAPPER),
                  (VOID**)&NvmeCmdWrapper
                  );
    
    if (EFI_ERROR(Status)) {
        NvmeController->ReInitializingQueue1 = FALSE;
        return Status;
    }
    
    // Clear memory
    SetMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER), 0);
    
    // Build NVME command to delete Submission queue
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = DELETE_IO_SUBMISSION_QUEUE;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.CDW10 = NvmeController->NVMQueueNumber;
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    if (EFI_ERROR(Status)) {
        goto RecreateQueue1_Error;
    }
    
    // Build NVME command to delete Completion queue
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = DELETE_IO_COMPLETION_QUEUE;
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = NvmeController->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.CDW10 = NvmeController->NVMQueueNumber;
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeController, NvmeCmdWrapper, &CompletionData);
    if (EFI_ERROR(Status)) {
        goto RecreateQueue1_Error;
    }
    
    // Create Submission and Completion Queue1
    Status  = CreateAdditionalSubmissionCompletionQueue(
                                NvmeController, 
                                NvmeCmdWrapper, 
                                NvmeController->NVMQueueNumber, 
                                NvmeController->Queue1SubmissionQueueSize
                                );
    
RecreateQueue1_Error:

    NvmeController->ReInitializingQueue1 = FALSE;
    
    gBS->FreePool (NvmeCmdWrapper);
    
#if  NVME_VERBOSE_PRINT
    if (!NvmeController->NvmeInSmm) {
        DEBUG((EFI_D_ERROR, "Status %r\n", Status));
    }
#endif
        
    return Status;
    
}

/**
    Prints the cmd completion status

    @param pCmdCompletionData 

    @retval VOID

    @note  The amount of data that will get printed can be controlled 
    using DEBUG_ERROR_LEVEL_MASK SDL token.
    Make sure PcdDebugPrintErrorLevel is properly cloned and set to 
    PcdsPatchableInModule in the project.

**/

VOID
PrintCommandCompletionData (
    IN  COMPLETION_QUEUE_ENTRY  *pCmdCompletionData
)
{
    
#if  NVME_VERBOSE_PRINT
    // Fig 25 NVM Express 1.1 spec
    // Print Completion Cmd Data
    DEBUG((EFI_D_VERBOSE, "Completion Queue DW2                      : %08X\n", *((UINT32 *)pCmdCompletionData + 2)));
    DEBUG((EFI_D_VERBOSE, "Completion Queue DW3                      : %08X\n", *((UINT32 *)pCmdCompletionData + 3)));
    DEBUG((EFI_D_VERBOSE, "Completion Queue DW0                      : %08X\n", pCmdCompletionData->DW0));
    DEBUG((EFI_D_VERBOSE, "Completion Queue Reserved                 : %08X\n", pCmdCompletionData->DW1));
#endif
    
}

/**
    Prints Nvme cmd parameters

    @param NvmeCmdWrapper 

    @retval VOID

    @note  The amount of data that will get printed can be controlled 
    using DEBUG_ERROR_LEVEL_MASK SDL token.
    Make sure PcdDebugPrintErrorLevel is properly cloned and set to 
    PcdsPatchableInModule in the project.

**/

VOID
PrintNvmeCmdWrapper (
    NVME_COMMAND_WRAPPER    *NvmeCmdWrapper
)
{
    
#if  NVME_VERBOSE_PRINT    
    DEBUG((EFI_D_VERBOSE,"\nCMD DW0                                  : %08X\n", *(UINT32 *)&(NvmeCmdWrapper->NvmCmd)));
    DEBUG((EFI_D_VERBOSE, "NSID                                      : %08X\n", NvmeCmdWrapper->NvmCmd.NSID));
    DEBUG((EFI_D_VERBOSE, "MPTR                                      : %016lX\n", NvmeCmdWrapper->NvmCmd.MPTR));
    DEBUG((EFI_D_VERBOSE, "PRP1                                      : %016lX\n", NvmeCmdWrapper->NvmCmd.PRP1));
    DEBUG((EFI_D_VERBOSE, "PRP2                                      : %016lX\n", NvmeCmdWrapper->NvmCmd.PRP2));
    DEBUG((EFI_D_VERBOSE, "CDW10                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW10));
    DEBUG((EFI_D_VERBOSE, "CDW11                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW11));
    DEBUG((EFI_D_VERBOSE, "CDW12                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW12));
    DEBUG((EFI_D_VERBOSE, "CDW13                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW13));
    DEBUG((EFI_D_VERBOSE, "CDW14                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW14));
    DEBUG((EFI_D_VERBOSE, "CDW15                                     : %08X\n",  NvmeCmdWrapper->NvmCmd.CDW15));
    DEBUG((EFI_D_VERBOSE, "Cmd sent to Queue                         : %08X\n",  NvmeCmdWrapper->SQIdentifier));
#endif   
    
}

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
