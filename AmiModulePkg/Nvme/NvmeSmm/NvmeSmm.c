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

/** @file NvmeSmm.c
    Nvme SMM driver to handle the Nvme device access

**/

//---------------------------------------------------------------------------

#include "NvmeSmm.h"
#include <Library/BaseMemoryLib.h>
#include <Guid/SmmVariableCommon.h>
#include <Library/AmiBufferValidationLib.h>

//---------------------------------------------------------------------------

EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_SYSTEM_TABLE2           *pSmst2;
NVME_GLOBAL_DATA                *gNvmeData;
AMI_NVME_CONTROLLER_PROTOCOL    *gNvmeController[NVMEDEVS_MAX_ENTRIES] = {0};
BOOLEAN                         gFirstAPICall = FALSE;

/**
     NvmeMassApiTable - NVMe API Function Dispatch Table
        
**/


API_FUNC NvmeMassApiTable[] = {
    NvmeMassAPIGetDeviceInformation,    // Nvme Mass API Sub-Func 00h
    NvmeMassAPIGetDeviceGeometry,       // Nvme Mass API Sub-Func 01h
    NvmeMassAPIResetDevice,             // Nvme Mass API Sub-Func 02h
    NvmeMassAPIReadDevice,              // Nvme Mass API Sub-Func 03h
    NvmeMassAPIWriteDevice,             // Nvme Mass API Sub-Func 04h
    NvmeMassAPIPass,                    // Nvme Mass API Sub-Func 05h VerifyDevice
    NvmeMassAPIPass,                    // Nvme Mass API Sub-Func 06h FormatDevice
    NvmeMassAPINotSupported,            // Nvme Mass API Sub-Func 07h CommandPassThru
    NvmeMassAPINotSupported,            // Nvme BIOS API function 08h AssignDriveNumber
    NvmeMassAPINotSupported,            // Nvme BIOS API function 09h CheckDevStatus
    NvmeMassAPINotSupported,            // Nvme BIOS API function 0Ah GetDevStatus
    NvmeMassAPINotSupported             // Nvme BIOS API function 0Bh GetDeviceParameters
};

/**
    Get the Index# for the DeviceAddress

    @param  DeviceAddress,
    @param  **ActiveNameSpace

    @retval None

**/

VOID
GetDevEntry (
    UINT8                   DeviceAddress,
    ACTIVE_NAMESPACE_DATA   **ActiveNameSpace
)
{

    UINT8                           Count;
    LIST_ENTRY                      *LinkData;
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController;
    
    // Locate a free slot to copy the pointer
     for (Count = 0; Count < NVMEDEVS_MAX_ENTRIES; Count++ ){
         if (gNvmeController[Count]) {
             NvmeController = gNvmeController[Count];
             
             if(IsListEmpty(&NvmeController->ActiveNameSpaceList)) {
                 continue;
             } 
             
             for (LinkData = NvmeController->ActiveNameSpaceList.ForwardLink; \
                     LinkData != &NvmeController->ActiveNameSpaceList; 
                     LinkData = LinkData->ForwardLink) {
                 
                 *ActiveNameSpace = BASE_CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);
                 if ((*ActiveNameSpace)->Int13DeviceAddress == DeviceAddress) {
                     return;
                 }
             }
         }
     }
    
    *ActiveNameSpace = NULL;
    return ;

}

/**
    Return Device information

    @param  *NvmeURP

    @retval None

**/

VOID
NvmeMassAPIGetDeviceInformation (
    NVME_STRUC  *NvmeURP
)
{

    NvmeURP->bRetValue = NVME_NOT_SUPPORTED;
    return;
    
}

/**
    Return Device Geometry

    @param *NvmeURP

    @retval None

**/

VOID
NvmeMassAPIGetDeviceGeometry (
    NVME_STRUC  *NvmeURP
)
{
    NvmeURP->bRetValue = NVME_NOT_SUPPORTED;
    return;
}

/**
    Reset device

    @param  *NvmeURP

    @retval None

**/

VOID
NvmeMassAPIResetDevice (
    NVME_STRUC  *NvmeURP
)
{
    NvmeURP->bRetValue = NVME_NOT_SUPPORTED;
    return;
}

/**
    Read data from the device

    @param *NvmeURP

    @retval None

**/

VOID
NvmeMassAPIReadDevice (
    NVME_STRUC  *NvmeURP
)
{
    
    ACTIVE_NAMESPACE_DATA               *ActiveNameSpace = NULL;
    EFI_STATUS                          Status;
    EFI_LBA                             Lba;
    UINT16                              NumBlks;
    UINT16                              BlksPerTransfer;
    VOID                                *Buffer = NULL;
    VOID                                *ReadBuffer;
    UINTN                               BufferSize;
    BOOLEAN                             UnalignedTransfer = FALSE;
    AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController;
    UINT32                              Offset;
    COMPLETION_QUEUE_ENTRY              *pCmdCompletionData;
    
    GetDevEntry(NvmeURP->ApiData.Read.DeviceAddress, &ActiveNameSpace);
    
    if(ActiveNameSpace == NULL) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return;
    }
    
    NvmeController = ActiveNameSpace->NvmeController;
    if (NvmeController->Queue1SubmissionQueueTailPtr == 0xFFFF) {
        Offset = QUEUE_DOORBELL_OFFSET( NvmeController->NVMQueueNumber, 1, NvmeController->DoorBellStride);
        NvmeController->Queue1CompletionQueueHeadPtr = CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset); 
        NvmeController->Queue1SubmissionQueueHeadPtr = NvmeController->Queue1CompletionQueueHeadPtr;
        NvmeController->Queue1SubmissionQueueTailPtr = NvmeController->Queue1CompletionQueueHeadPtr;
        // Check if there is a roller over
        if (NvmeController->Queue1SubmissionQueueTailPtr >= NvmeController->Queue1SubmissionQueueSize) {
            NvmeController->Queue1SubmissionQueueTailPtr = 0;
        }
        
        // Update the phase tag from the Completion queue
        pCmdCompletionData = (COMPLETION_QUEUE_ENTRY *)NvmeController->Queue1CompletionQueueMappedAddr;
        NvmeController->Queue1PhaseTag = (UINT8)pCmdCompletionData->PhaseTag;
        NvmeController->CommandIdentifierQueue1 = 0;
        NvmeController->CommandIdentifierAdmin = 0;
    }
    
        
    Lba=NvmeURP->ApiData.Read.LBA;
    NumBlks=NvmeURP->ApiData.Read.NumBlks;
   
    (UINT32)Buffer= NvmeURP->ApiData.Read.BufferAddress;

    BlksPerTransfer =  NumBlks;
    ReadBuffer = Buffer;
    
    //If Buffer isn't aligned use internal buffer
    if ((UINTN)NvmeURP->ApiData.Read.BufferAddress & ((1 << ActiveNameSpace->NvmeBlockIO.Media->IoAlign)-1)) {
        BlksPerTransfer = 1;
        ReadBuffer = NvmeController->LegacyNvmeBuffer;
        UnalignedTransfer = TRUE;
    }

    BufferSize = BlksPerTransfer * ActiveNameSpace->NvmeBlockIO.Media->BlockSize;
    
    for (  ;  NumBlks; NumBlks -= BlksPerTransfer){
        Status = NvmeReadWriteBlocks (ActiveNameSpace, ActiveNameSpace->NvmeBlockIO.Media->MediaId, Lba, BufferSize, ReadBuffer,NULL,NVME_READ);
        if (EFI_ERROR(Status)) {
            break;
        }
        if  (UnalignedTransfer) {
            CopyMem (Buffer, ReadBuffer, BufferSize); 
        }
        (UINTN)Buffer = (UINTN)Buffer + BufferSize;
        Lba += BlksPerTransfer;

    }
   
    if (EFI_ERROR(Status)) {
        NvmeURP->bRetValue = NVME_READ_ERR;
    } else {
        NvmeURP->bRetValue = NVME_SUCCESS;
    }
    
    return;
    
}

/**
    Write data to the device

    @param  *NvmeURP

    @retval None

**/

VOID
NvmeMassAPIWriteDevice (
    NVME_STRUC  *NvmeURP
)
{
    
    ACTIVE_NAMESPACE_DATA               *ActiveNameSpace = NULL;
    EFI_STATUS                          Status;
    EFI_LBA                             Lba;
    UINT16                              NumBlks;
    UINT16                              BlksPerTransfer;
    VOID                                *Buffer = NULL;
    VOID                                *ReadBuffer;
    UINTN                               BufferSize;
    BOOLEAN                             UnalignedTransfer = FALSE;
    AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController;
    UINT32                              Offset;
    COMPLETION_QUEUE_ENTRY              *pCmdCompletionData;
    
    GetDevEntry(NvmeURP->ApiData.Read.DeviceAddress, &ActiveNameSpace);
    
    if(ActiveNameSpace == NULL) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return;
    }
    
    NvmeController = ActiveNameSpace->NvmeController;
    if (NvmeController->Queue1SubmissionQueueTailPtr == 0xFFFF) {
        Offset = QUEUE_DOORBELL_OFFSET( NvmeController->NVMQueueNumber, 1, NvmeController->DoorBellStride);
        NvmeController->Queue1CompletionQueueHeadPtr = CONTROLLER_REG32(NvmeController->NvmeBarOffset, Offset); 
        NvmeController->Queue1SubmissionQueueHeadPtr = NvmeController->Queue1CompletionQueueHeadPtr;
        NvmeController->Queue1SubmissionQueueTailPtr = NvmeController->Queue1CompletionQueueHeadPtr;
        // Check if there is a roller over
        if (NvmeController->Queue1SubmissionQueueTailPtr >= NvmeController->Queue1SubmissionQueueSize) {
            NvmeController->Queue1SubmissionQueueTailPtr = 0;
        }
        
        // Update the phase tag from the Completion queue
        pCmdCompletionData = (COMPLETION_QUEUE_ENTRY *)NvmeController->Queue1CompletionQueueMappedAddr;
        NvmeController->Queue1PhaseTag = (UINT8)pCmdCompletionData->PhaseTag;
        NvmeController->CommandIdentifierQueue1 = 0;
        NvmeController->CommandIdentifierAdmin = 0;
        
    }
    
        
    Lba=NvmeURP->ApiData.Read.LBA;
    NumBlks=NvmeURP->ApiData.Read.NumBlks;
   
    (UINT32)Buffer= NvmeURP->ApiData.Read.BufferAddress;

    BlksPerTransfer =  NumBlks;
    ReadBuffer = Buffer;
    
    //If Buffer isn't aligned use internal buffer
    if ((UINTN)NvmeURP->ApiData.Read.BufferAddress & ((1 << ActiveNameSpace->NvmeBlockIO.Media->IoAlign)-1)) {
        BlksPerTransfer = 1;
        ReadBuffer = NvmeController->LegacyNvmeBuffer;
        UnalignedTransfer = TRUE;
    }

    BufferSize = BlksPerTransfer * ActiveNameSpace->NvmeBlockIO.Media->BlockSize;
    
    for (  ;  NumBlks; NumBlks -= BlksPerTransfer){
        
        if  (UnalignedTransfer) {
            CopyMem (ReadBuffer, Buffer, BufferSize); 
        }
        
        Status = NvmeReadWriteBlocks (ActiveNameSpace, ActiveNameSpace->NvmeBlockIO.Media->MediaId, Lba, BufferSize, ReadBuffer,NULL, NVME_WRITE);
        if (EFI_ERROR(Status)) {
            break;
        }

        (UINTN)Buffer = (UINTN)Buffer + BufferSize;
        Lba += BlksPerTransfer;

    }
   
    if (EFI_ERROR(Status)) {
        NvmeURP->bRetValue = NVME_WRITE_ERR;
    }
    else {
        NvmeURP->bRetValue = NVME_SUCCESS;
    }
    
    return;
    
}



/**
    Dummy handler to return NVME_SUCCESS

        
    @param *NvmeURP
    @retval None

**/

VOID
NvmeMassAPIPass(
    NVME_STRUC *NvmeURP
)
{

    NvmeURP->bRetValue = NVME_SUCCESS;
    return;

}


/**
    Dummy handler to return NVME_NOT_SUPPORTED

    @param *NvmeURP

    @retval None

**/

VOID
NvmeMassAPINotSupported (
    NVME_STRUC  *NvmeURP
)
{

    NvmeURP->bRetValue = NVME_NOT_SUPPORTED;
    return;

}

/**
    Initialize NVMe SMM data area

    @param   DispatchHandle,
    @param   *Context         OPTIONAL,
    @param   *CommBuffer      OPTIONAL,
    @param   *CommBufferSize  OPTIONAL

    @retval  EFI_STATUS

**/

EFI_STATUS
EFIAPI
NvmeInitSmmData (
    IN  EFI_HANDLE  DispatchHandle,
    IN  CONST   VOID    *Context        OPTIONAL,
    IN  OUT     VOID    *CommBuffer     OPTIONAL,
    IN  OUT     UINTN   *CommBufferSize OPTIONAL
  )
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    ACTIVE_NAMESPACE_DATA         *OrgActiveNameSpace;
    ACTIVE_NAMESPACE_DATA         *ActiveNameSpace;
    AMI_NVME_CONTROLLER_PROTOCOL  *NvmeController;
    AMI_NVME_CONTROLLER_PROTOCOL  *OrgNvmeController;
    UINT8                         Count;
    LIST_ENTRY                    *LinkData;
    EFI_BLOCK_IO_MEDIA            *Media = NULL;
    
    // After the first API call is invoked, don't initialize SMM data area. This is an additional
    // Security check so that data won't get corrupted.
    if (gFirstAPICall) {
        return EFI_SUCCESS;
    }
    
    // If input is invalid, stop processing this SMI
    if (CommBuffer == NULL || CommBufferSize == NULL) {
        return EFI_SUCCESS;
    }

    (UINTN)OrgNvmeController = *(UINTN *)CommBuffer;
            
    // Locate a free slot to copy the pointer
     for (Count = 0; Count < NVMEDEVS_MAX_ENTRIES; Count++ ){
         if (!gNvmeController[Count]) {
             break;
         }
     }
     
     if (Count == NVMEDEVS_MAX_ENTRIES) {
         return EFI_OUT_OF_RESOURCES;
     }
     
    Status = pSmst2->SmmAllocatePool ( 
                                EfiRuntimeServicesData, 
                                sizeof (AMI_NVME_CONTROLLER_PROTOCOL),
                                (VOID**)&NvmeController);
    ASSERT_EFI_ERROR(Status);
    
    // Copy input NvmeController passed in OrgNvmeController into SMM
    CopyMem ((VOID *)NvmeController, OrgNvmeController, sizeof (AMI_NVME_CONTROLLER_PROTOCOL));
    
    
    // Copy IDENTIFY_CONTROLLER_DATA
    Status = pSmst2->SmmAllocatePool ( 
                                EfiRuntimeServicesData, 
                                sizeof (IDENTIFY_CONTROLLER_DATA),
                                (VOID**)&(NvmeController->IdentifyControllerData));
    ASSERT_EFI_ERROR(Status);
    
    CopyMem (NvmeController->IdentifyControllerData, OrgNvmeController->IdentifyControllerData, sizeof(IDENTIFY_CONTROLLER_DATA));
    
    gNvmeController[Count] = NvmeController;
 
    
    // Initialize some of the pointers to NULL which aren't applicable during runtime
    NvmeController->PciIO = NULL;
    NvmeController->NvmeInSmm = TRUE;
    NvmeController->Queue1SubmissionQueueTailPtr = 0xFFFF;
    
    InitializeListHead (&NvmeController->ActiveNameSpaceList);
    
    pSmst2->SmmAllocatePool ( EfiRuntimeServicesData, 
                              sizeof (NVME_COMMAND_WRAPPER),
                              (VOID**)&(NvmeController->NvmeCmdWrapper));
    
    ZeroMem (NvmeController->NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));
    
    // use original NVMe buffer for this as original address value is used.
    // Update the NvmeController pointer inside ActiveNameSpace
    for (LinkData = OrgNvmeController->ActiveNameSpaceList.ForwardLink; 
            LinkData != &OrgNvmeController->ActiveNameSpaceList; 
            LinkData = LinkData->ForwardLink) {
    
        OrgActiveNameSpace = BASE_CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);
        
        pSmst2->SmmAllocatePool ( EfiRuntimeServicesData, 
                                  sizeof (ACTIVE_NAMESPACE_DATA),
                                  (VOID**)&(ActiveNameSpace));
        
        
        CopyMem (ActiveNameSpace, OrgActiveNameSpace, sizeof(ACTIVE_NAMESPACE_DATA));
        
        ActiveNameSpace->NvmeController = NvmeController;
        ActiveNameSpace->EfiDevicePath = NULL;
        ActiveNameSpace->UDeviceName = NULL;

        pSmst2->SmmAllocatePool ( EfiRuntimeServicesData, 
                                  sizeof (EFI_BLOCK_IO_MEDIA),
                                  (VOID**)&(Media) );
        if( EFI_ERROR(Status) ) {
            ASSERT_EFI_ERROR(Status);
            return Status;
        }

        CopyMem ( Media, OrgActiveNameSpace->NvmeBlockIO.Media, sizeof(EFI_BLOCK_IO_MEDIA) );
        ActiveNameSpace->NvmeBlockIO.Media = Media;

        InsertTailList (&NvmeController->ActiveNameSpaceList, &ActiveNameSpace->Link);
        
    }

    return Status;
    
}

/**
    Handle SWSMI generated from NVMe CSM16 module 

    @param  DispatchHandle,
    @param  *DispatchContext OPTIONAL,
    @param  *CommBuffer OPTIONAL,
    @param  *CommBufferSize OPTIONAL
  
    @retval  EFI_STATUS

**/

EFI_STATUS
NvmeSWSMIHandler (
    IN  EFI_HANDLE      DispatchHandle,
    IN  CONST   VOID    *DispatchContext OPTIONAL,
    IN  OUT     VOID    *CommBuffer OPTIONAL,
    IN  OUT     UINTN   *CommBufferSize OPTIONAL
)
{
    EFI_STATUS  Status =EFI_SUCCESS;
    NVME_STRUC  *NvmeURP=NULL;
    UINT8       bFuncIndex;
    UINT8       bNumberOfFunctions;
    UINT16      EbdaSeg;
    UINTN       *NvmeParameterBaseAddr = (UINTN*)CommBuffer;

    gFirstAPICall = TRUE;
    //
    // Checking whether the SMI is generated from EFI or Legacy.
    // If the SMI is generated from EFI, the NVME_STRUC address is taken \
    // from the CommBuffer. If the SMI is from Legacy, the NVME_STRUC \
    // address is taken from EBDA.
    //
    if(*NvmeParameterBaseAddr != 0) {
        //
        // Obtaining the NVME_STRUC Address
        //
        NvmeURP = (NVME_STRUC*)(*NvmeParameterBaseAddr);
        *NvmeParameterBaseAddr = 0;
    } else {
        //
        // Get the fpURP pointer from EBDA
        //
        EbdaSeg = *((UINT16*)0x40E);
        NvmeURP = *(NVME_STRUC**)(UINTN)(((UINT32)EbdaSeg << 4) + NVME_DATA_EBDA_OFFSET);
        NvmeURP = (NVME_STRUC*)((UINTN)NvmeURP & 0xFFFFFFFF);
    }

    // Validate if URP address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers
    Status = AmiValidateMemoryBuffer((VOID*)NvmeURP, sizeof(NVME_STRUC));
    if (EFI_ERROR(Status)) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return EFI_SUCCESS;
    }
    // Note: Buffer Address from URP is not validated with non SMRAM check
    // as DMA transfer isn’t supported inside SMM
    
    if  (NvmeURP->bFuncNumber != NVME_API_MASS_DEVICE_REQUEST) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return Status;    
    }
    
    bFuncIndex = NvmeURP->bSubFunc;
    bNumberOfFunctions = sizeof NvmeMassApiTable / sizeof (API_FUNC *);

    //
    // Make sure function number is valid; if function number is not zero
    // check for valid extended SDIO API function
    //
    if (bFuncIndex >= bNumberOfFunctions ) {
        NvmeURP->bRetValue = NVME_PARAMETER_FAILED;
        return Status;
    }

    //
    // Call the appropriate function
    //

    NvmeMassApiTable[bFuncIndex](NvmeURP);

    return Status;
}

/**
    Loads NVMe SMM module into SMM and registers SMI handler

    @param ImageHandle,
    @param *SystemTable

    @retval EFI_STATUS

**/

EFI_STATUS 
NvmeSmmDriverEntryPoint (
    IN  EFI_HANDLE       ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable
    )
{
    
    EFI_STATUS                      Status;
    EFI_HANDLE                      SwHandle = NULL;
    EFI_SMM_SW_DISPATCH2_PROTOCOL   *pSwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT     SwContext;
    EFI_HANDLE                      DispatchHandle;

    
    Status = gBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }

    Status = gSmmBase2->GetSmstLocation (gSmmBase2, &pSmst2);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }

    Status = pSmst2->SmmLocateProtocol(&gEfiSmmSwDispatch2ProtocolGuid,
                                       NULL,
                                       &pSwDispatch);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }

    SwContext.SwSmiInputValue = NVME_SWSMI;
    Status = pSwDispatch->Register (pSwDispatch,
                                    NvmeSWSMIHandler,
                                    &SwContext,
                                    &SwHandle);
    if (EFI_ERROR (Status)) {
        return Status;
    }
    
    //
    //Allocate Memory for NVMe global Data.
    //
    Status = pSmst2->SmmAllocatePool(EfiRuntimeServicesData,sizeof(NVME_GLOBAL_DATA), &gNvmeData);
    ASSERT_EFI_ERROR(Status);
    //
    //  Clear the Buffer
    //
    ZeroMem((VOID*)gNvmeData, sizeof(NVME_GLOBAL_DATA));
    
    
    //
    // Register Nvme handler to transfer data from DXE driver to SMM
    //
    Status = pSmst2->SmiHandlerRegister (
                      NvmeInitSmmData,
                      &gAmiSmmNvmeCommunicationGuid,
                      &DispatchHandle
                      );
    
    ASSERT_EFI_ERROR (Status);

    return EFI_SUCCESS;
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
