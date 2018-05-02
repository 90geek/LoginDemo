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
#include <Protocol/SmmAccess2.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>

EFI_SMRAM_DESCRIPTOR *SmmAmiBufferValidationLibSmramRanges = NULL;
UINTN SmmAmiBufferValidationLibNumberOfSmramRange = 0;

EFI_STATUS AmiValidateMemoryBuffer(VOID* Buffer, UINTN BufferSize){
	UINTN  i;
	UINTN BufferAddress;

	if (SmmAmiBufferValidationLibNumberOfSmramRange==0) return EFI_NOT_FOUND;

	BufferAddress = (UINTN)Buffer;
	if (BufferAddress + BufferSize < BufferAddress) return EFI_INVALID_PARAMETER; // overflow
	for (i = 0; i < SmmAmiBufferValidationLibNumberOfSmramRange; i ++) {
		if (    BufferAddress >= SmmAmiBufferValidationLibSmramRanges[i].CpuStart
    	     && BufferAddress < SmmAmiBufferValidationLibSmramRanges[i].CpuStart + SmmAmiBufferValidationLibSmramRanges[i].PhysicalSize
    	) return EFI_ACCESS_DENIED; // Buffer starts in SMRAM
        if (    BufferAddress < SmmAmiBufferValidationLibSmramRanges[i].CpuStart
    	     && BufferAddress+BufferSize > SmmAmiBufferValidationLibSmramRanges[i].CpuStart
        ) return EFI_ACCESS_DENIED; // Buffer overlaps with SMRAM
	}
	
	return EFI_SUCCESS;
}

EFI_STATUS AmiValidateMmioBuffer(VOID* Buffer, UINTN BufferSize){
	return AmiValidateMemoryBuffer(Buffer,BufferSize);
}

EFI_STATUS AmiValidateSmramBuffer(VOID* Buffer, UINTN BufferSize){
	UINTN  i;
	UINTN BufferAddress;

	if (SmmAmiBufferValidationLibNumberOfSmramRange==0) return EFI_NOT_FOUND;

	BufferAddress = (UINTN)Buffer;
	if (BufferAddress + BufferSize < BufferAddress) return EFI_INVALID_PARAMETER; // overflow
	for (i = 0; i < SmmAmiBufferValidationLibNumberOfSmramRange; i ++) {
		if (    BufferAddress >= SmmAmiBufferValidationLibSmramRanges[i].CpuStart
    	     && BufferAddress+BufferSize <= SmmAmiBufferValidationLibSmramRanges[i].CpuStart + SmmAmiBufferValidationLibSmramRanges[i].PhysicalSize
    	) return EFI_SUCCESS; // Entire Buffer is in SMRAM
	}
	
	return EFI_ACCESS_DENIED;
}

EFI_STATUS EFIAPI SmmAmiBufferValidationLibConstructor(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS Status;
    EFI_SMM_ACCESS2_PROTOCOL *SmmAccess;
    UINTN Size;
    
    // Get SMRAM information
    Status = gBS->LocateProtocol (&gEfiSmmAccess2ProtocolGuid, NULL, (VOID **)&SmmAccess);
    if (EFI_ERROR(Status)) return Status;
    
    Size = 0;
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, NULL);
    if (Status != EFI_BUFFER_TOO_SMALL) return Status;
    Status = gSmst->SmmAllocatePool (EfiRuntimeServicesData, Size, (VOID **)&SmmAmiBufferValidationLibSmramRanges);
    if (EFI_ERROR(Status)){
    	SmmAmiBufferValidationLibSmramRanges = NULL;
    	return Status;
    }
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, SmmAmiBufferValidationLibSmramRanges);
    if (EFI_ERROR(Status)){
    	gSmst->SmmFreePool (SmmAmiBufferValidationLibSmramRanges);
    	SmmAmiBufferValidationLibSmramRanges = NULL;
    	return Status;
    }
    SmmAmiBufferValidationLibNumberOfSmramRange = Size / sizeof (EFI_SMRAM_DESCRIPTOR);

    return EFI_SUCCESS;
}

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
