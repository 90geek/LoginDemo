/*++
  This file contains an 'Intel Peripheral Driver' and is        
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
--*/
/*++

Copyright (c)  1999 - 2015 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  VarstoreVariableInitDxe.c
  
Abstract:
  
  Do varstore specific Variable DXE initializations.

--*/

#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/VariableWrite.h>
#include <Guid/SetupVariable.h>


extern EFI_GUID gEfiMemoryConfigDataGuid;

#ifndef EFI_VARIABLE_RUNTIME_ALLOW_RECLAIM
#define EFI_VARIABLE_RUNTIME_ALLOW_RECLAIM 0x00001000
#endif


/*++

Routine Description:

  This function is called to change a variable's attribute. 

Arguments:

  Name        - Pointer to variable name.
  Guid        - Pointer to variable guid.
  Attribute   - Variable attribute to be set

Returns:

  None

--*/
EFI_STATUS
EFIAPI
ChangeVarAttribute (
  IN CHAR16          *Name,
  IN EFI_GUID        *Guid,
  IN UINT32          Attribute
  )
{
  EFI_STATUS  Status;
  UINTN       BufferSize = 0;
  VOID        *Buffer = NULL;
  UINT32      Attr;

  ASSERT (Name != NULL && Guid != NULL);
 
  Status = gRT->GetVariable (
        Name,
        Guid,
        &Attr,
        &BufferSize, 
        Buffer
        );

  if (Status == EFI_BUFFER_TOO_SMALL) {
     //
     // Allocate the buffer
     //
     Buffer = AllocatePool (BufferSize);
     ASSERT (Buffer != NULL);
     //
     // Read variable into the allocated buffer.
     //
    Status = gRT->GetVariable (
                  Name,
                  Guid,
                  &Attr,
                  &BufferSize, 
                  Buffer
                  );
    if (!EFI_ERROR (Status) && (Attr != Attribute)) {

      DEBUG(( EFI_D_ERROR, "Variable name: %s, guid: %g, change attribute from %x to %x\n",Name, Guid, Attr, Attribute));

      //
      // Erarse Variable
      //
      Status = gRT->SetVariable (
                    Name,
                    Guid,
                    Attr,
                    0, 
                    Buffer
                    );
      if (!EFI_ERROR (Status)) {
        //
        // Set Variable with new attribute
        //
        Status = gRT->SetVariable (
                      Name,
                      Guid,
                      Attribute,
                      BufferSize, 
                      Buffer
                      );
      }
    }else
    	{
    	  DEBUG(( EFI_D_ERROR, "Variable name: %s, guid: %g, no change in attribute %x to %x\n",Name, Guid, Attr, Attribute));
    	}

    FreePool (Buffer);
  }else
  	{
  	 DEBUG(( EFI_D_ERROR, "Unable to find variable name: %s, guid: %g, Status \n",Name, Guid,  Status));
  	}
  
  return Status;
}

/*++

Routine Description:

  This function is called when a VARIABLE WRITE ARCH protocol is installed. 

Arguments:

  Event       - The event that occurred.  Not used.
  Context     - The context of the event.  Not used.


Returns:

  None

--*/
VOID
EFIAPI
EventVariableWriteArchProtocolNotify (
  IN EFI_EVENT     Event,
  IN VOID          *Context
  )
{

  EFI_STATUS  Status;
  VOID        *VariableWriteArch;
  CHAR16 EfiMemoryConfigVariable[] = L"MemoryConfig0";

  Status = gBS->LocateProtocol (
                  &gEfiVariableWriteArchProtocolGuid,
                  NULL,
                  &VariableWriteArch
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  Status = ChangeVarAttribute (
              L"IntelSetup",// AptioV Server Override: Changed VariableName to L"IntelSetup"
              &gEfiSetupVariableGuid,
			  SETUP_VARIABLE_ATTRIBUTES
              );

  Status = ChangeVarAttribute (
			 L"SetupDefault",
			 &gEfiSetupVariableGuid,
			 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS
			 );

  Status = EFI_SUCCESS;
  while (!EFI_ERROR (Status)) {
    Status = ChangeVarAttribute (
  			 EfiMemoryConfigVariable,
  			 &gEfiMemoryConfigDataGuid,
			 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_RUNTIME_ALLOW_RECLAIM
  			 );
    EfiMemoryConfigVariable[12]++;
  }


  //	 
  //
  // Add all of the varstore variables whose attribute needs to be changed from default here
  //
}


/*++

Routine Description:

  Entry point of this driver.

Arguments:

  ImageHandle  -  Image handle of this driver.
  SystemTable  -  Pointer to standard EFI system table.
    
Returns:

  EFI_SUCCESS       -  Succeed.


--*/
/*++

--*/ 
EFI_STATUS
EFIAPI
VarstoreVariableInitDxeEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  VOID                  *Registration;

  EfiCreateProtocolNotifyEvent (
    &gEfiVariableWriteArchProtocolGuid,
    TPL_NOTIFY,
    EventVariableWriteArchProtocolNotify,
    NULL,
    &Registration
    );

  return EFI_SUCCESS;
}


