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

/** @file
  @brief Defines AmiBufferValidationLib library class.

  Buffer Validation Functions.
**/
#ifndef __AMI_BUFFER_VALIDATION_LIB__H__
#define __AMI_BUFFER_VALIDATION_LIB__H__

/**
    Validates memory buffer.
    
    The function verifies the buffer to make sure its address range is legal for a memory buffer.
    SMI handlers that receive buffer address and/or size from outside of SMM at runtime must validate
    the buffer using this function prior to using it or passing to other SMM interfaces.

    @param  Buffer Buffer address 
    @param  BufferSize Size of the Buffer
    
    @retval  EFI_SUCCESS - The buffer address range is valid and can be safely used.
    @retval  EFI_ACCESS_DENIED - The buffer can't be used because its address range overlaps with protected area such as SMRAM.
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
    @retval  EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified.
**/
EFI_STATUS AmiValidateMemoryBuffer(VOID* Buffer, UINTN BufferSize);

/**
    Validates MMIO buffer.
    
    The function verifies the buffer to make sure its address range is legal for a MMIO buffer.
    SMI handlers that receive buffer address and/or size from outside of SMM at runtime must validate
    the buffer using this function prior to using it or passing to other SMM interfaces.

    @param  Buffer Buffer address 
    @param  BufferSize Size of the Buffer
    
    @retval  EFI_SUCCESS - The buffer address range is valid and can be safely used.
    @retval  EFI_ACCESS_DENIED - The buffer can't be used because its address range overlaps with protected area such as SMRAM.
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
    @retval  EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified.
**/
EFI_STATUS AmiValidateMmioBuffer(VOID* Buffer, UINTN BufferSize);

/**
    Validates SMRAM buffer.
    
    The function verifies the buffer to make sure it resides in the SMRAM.
    
    @param  Buffer Buffer address 
    @param  BufferSize Size of the Buffer
    
    @retval  EFI_SUCCESS - The buffer resides in the SMRAM and can be safely used.
    @retval  EFI_ACCESS_DENIED - The buffer can't be used because at least one byte of the buffer is outside of SMRAM.
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
    @retval  EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified.
**/
EFI_STATUS AmiValidateSmramBuffer(VOID* Buffer, UINTN BufferSize);

#endif
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
