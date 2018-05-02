/** @file
  This is the driver that implements the PCH S3 Support protocol

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement

**/

#include "PchS3Support.h"
#include "Token.h" //AptioV server override: S3 support on AztecCity

///
/// Global Variables
///
EFI_HANDLE                  mImageHandle;
EFI_PCH_S3_SUPPORT_PROTOCOL mPchS3SupportProtocol;
PCH_S3_PARAMETER_HEADER     *mS3Parameter;
UINT32                      mPchS3ImageEntryPoint;

//
// Functions
//

/**
  PCH S3 support driver entry point

  @param[in] ImageHandle          Handle for the image of this driver
  @param[in] SystemTable          Pointer to the EFI System Table

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
PchS3SupportEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "PchS3SupportEntryPoint() Start\n"));
  mImageHandle = ImageHandle;

  ///
  /// Load the PCH S3 image
  ///
  Status = LoadPchS3Image (&mPchS3ImageEntryPoint);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Set the PCH Init Variable
  /// Make sure NV Variable support is available before this driver
  /// is dispatched
  ///
  Status = SetPchInitVariable ();
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Install the PCH S3 Support protocol
  ///
  mPchS3SupportProtocol.SetDispatchItem = PchS3SetDispatchItem;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mImageHandle,
                  &gEfiPchS3SupportProtocolGuid,
                  &mPchS3SupportProtocol,
                  NULL
                  );

  DEBUG ((DEBUG_INFO, "PchS3SupportEntryPoint() End\n"));

  return Status;
}

/**
  Set the Pch Init Variable for consumption by PchInitS3 PEIM.
  bugbug: expect to extend the variable service to support <4G EfiReservedMemory
  variable storage, such that memory consumption is flexible and more economical.

  @param[in] VOID

  @retval None
**/
EFI_STATUS
SetPchInitVariable (
  VOID
  )
{
  EFI_STATUS            Status;
  EFI_PHYSICAL_ADDRESS  Address;
  UINT32                HeaderSize;

  ///
  /// Allcoate <4G EfiReservedMemory
  ///
  Address = 0xFFFFFFFF;
  Status  = (gBS->AllocatePages) (AllocateMaxAddress, EfiReservedMemoryType, 2, &Address); //AptioV server override: S3 support on AztecCity
  ASSERT_EFI_ERROR (Status);
  mS3Parameter  = (PCH_S3_PARAMETER_HEADER *) (UINTN) Address;

  HeaderSize    = sizeof (PCH_S3_PARAMETER_HEADER);
  HeaderSize    = (HeaderSize + 7) / 8 * 8;

  ///
  /// Initialize StorePosition and ExecutePosition
  ///
  mS3Parameter->StorePosition   = HeaderSize;
  mS3Parameter->ExecutePosition = HeaderSize;

  ///
  /// Set PCH_INIT_VARIABLE to point to the allocated buffer
  ///
  Status = gRT->SetVariable (
                  PCH_INIT_VARIABLE_NAME,
                  &gPchInitVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                  sizeof (UINT32),
                  &mS3Parameter
                  );

  return Status;
}

/**
  Set an item to be dispatched at S3 resume time. At the same time, the entry point
  of the PCH S3 support image is returned to be used in subsequent boot script save
  call

  @param[in] This                       Pointer to the protocol instance.
  @param[in] DispatchItem               The item to be dispatched.
  @param[out] S3DispatchEntryPoint      The entry point of the PCH S3 support image.

  @retval EFI_STATUS                    Successfully completed.
  @retval EFI_OUT_OF_RESOURCES          Out of resources.
**/
EFI_STATUS
EFIAPI
PchS3SetDispatchItem (
  IN     EFI_PCH_S3_SUPPORT_PROTOCOL   *This,
  IN     EFI_PCH_S3_DISPATCH_ITEM      *DispatchItem,
  OUT    EFI_PHYSICAL_ADDRESS          *S3DispatchEntryPoint
  )
{
  EFI_STATUS  Status;
  UINT32      TypeSize;
  UINT32      ParameterSize;
  UINT32      Size;
  UINT8       *CurrentPos;

  DEBUG ((DEBUG_INFO, "PchS3SetDispatchItem() Start\n"));

  Status = EFI_SUCCESS;
  ///
  /// Calculate the size required;
  /// ** Always round up to be 8 byte aligned
  ///
  switch (DispatchItem->Type) {
  case PchS3ItemTypeSendCodecCommand:
    ParameterSize = sizeof (EFI_PCH_S3_PARAMETER_SEND_CODEC_COMMAND);
    ParameterSize = (ParameterSize + 7) / 8 * 8;
    break;

  case PchS3ItemTypeInitPcieRootPortDownstream:
    ParameterSize = sizeof (EFI_PCH_S3_PARAMETER_INIT_PCIE_ROOT_PORT_DOWNSTREAM);
    ParameterSize = (ParameterSize + 7) / 8 * 8;
    break;

  case PchS3ItemTypePcieSetPm:
    ParameterSize = sizeof (EFI_PCH_S3_PARAMETER_PCIE_SET_PM);
    ParameterSize = (ParameterSize + 7) / 8 * 8;
    break;

  case PchS3ItemTypeProgramIobp:
    ParameterSize = sizeof (EFI_PCH_S3_PARAMETER_PROG_IOBP);
    ParameterSize = (ParameterSize + 7) / 8 * 8;
    break;

  default:
    return EFI_UNSUPPORTED; //EDKII implementarion
    break;
  }
  ///
  /// Round up TypeSize to be 8 byte aligned
  ///
  TypeSize  = sizeof (EFI_PCH_S3_DISPATCH_ITEM_TYPE);
  TypeSize  = (TypeSize + 7) / 8 * 8;

  ///
  /// Total size is TypeSize + ParameterSize
  ///
  Size = TypeSize + ParameterSize;

  if (mS3Parameter->StorePosition + Size > (2 * EFI_PAGE_SIZE)) { //AptioV server override: S3 support on AztecCity
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }
  ///
  /// Store the dispatch type and dispatch parameter
  ///
  CurrentPos  = (UINT8 *) mS3Parameter + mS3Parameter->StorePosition;
  *(EFI_PCH_S3_DISPATCH_ITEM_TYPE *) CurrentPos = DispatchItem->Type;
  CurrentPos += TypeSize;
  CopyMem (CurrentPos, DispatchItem->Parameter, ParameterSize);

  ///
  /// Move the store position ahead
  ///
  mS3Parameter->StorePosition += Size;

  ///
  /// Return the S3 Image's entry point
  ///
  *S3DispatchEntryPoint = mPchS3ImageEntryPoint;

  DEBUG ((DEBUG_INFO, "PchS3SetDispatchItem() End\n"));

  return Status;
}

/**
  Load the PCH S3 Image into Efi Reserved Memory below 4G.

  @param[out] ImageEntryPoint     The ImageEntryPoint after success loading

  @retval EFI_STATUS
**/
EFI_STATUS
LoadPchS3Image (
  OUT   UINT32          *ImageEntryPoint
  )
{
#ifdef EFI_S3_RESUME //AptioV server override: S3 support on AztecCity
  UINT8                                         *Buffer;
  UINTN                                         BufferSize;
  VOID                                          *FfsBuffer;
  PE_COFF_LOADER_IMAGE_CONTEXT                  ImageContext;
  EFI_STATUS              Status;
  PCH_S3_PEIM_VARIABLE    PchS3PeimData;        //AptioV server override :setVariable for Bootscripthide.

  *ImageEntryPoint = 0;

  Status = GetSectionFromAnyFv  (
             &gPchS3ImageGuid,
            EFI_SECTION_PE32,
             0,
             (VOID **) &Buffer,
             &BufferSize
            );
  if (Status == EFI_NOT_FOUND) {
    Status = GetSectionFromAnyFv  (
               &gPchS3ImageGuid,
               EFI_SECTION_TE,
               0,
               (VOID **) &Buffer,
               &BufferSize
               );
  }
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ImageContext.Handle = Buffer;
  ImageContext.ImageRead = PeCoffLoaderImageReadFromMemory;

  //
  // Get information about the image being loaded
  //
  Status = PeCoffLoaderGetImageInfo (&ImageContext);
  ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return Status;
    }

  Status = gBS->AllocatePool (
		EfiReservedMemoryType, //AptioV Server Override: S3 support on AztecCity
                BufferSize + ImageContext.SectionAlignment,
                &FfsBuffer
                        );
  ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
    return EFI_OUT_OF_RESOURCES;
      }

  ImageContext.ImageAddress = (PHYSICAL_ADDRESS)(UINTN)FfsBuffer;
  //
  // Align buffer on section boundry
  //
  if (ImageContext.SectionAlignment != 0) {
    ImageContext.ImageAddress += ImageContext.SectionAlignment - 1;
    ImageContext.ImageAddress &= ~(ImageContext.SectionAlignment - 1);
    }

  //
  // Load the image to our new buffer
  //
  Status = PeCoffLoaderLoadImage (&ImageContext);
  if (EFI_ERROR (Status)) {
    gBS->FreePool (FfsBuffer);
    return Status;
  }

  //
  // Relocate the image in our new buffer
  //
  Status = PeCoffLoaderRelocateImage (&ImageContext);
  if (EFI_ERROR (Status)) {
    PeCoffLoaderUnloadImage (&ImageContext);
    gBS->FreePool (FfsBuffer);
    return Status;
  }

  *ImageEntryPoint = (UINT32) ImageContext.EntryPoint;
  //AptioV server override start : setVariable for Bootscripthide support.
  PchS3PeimData.EntryPointAddress = ImageContext.EntryPoint;
  PchS3PeimData.PeimSize          = ImageContext.ImageSize;
  Status = gRT->SetVariable (
            PCH_S3_PEIM_VARIABLE_NAME,
            &gPchInitVariableGuid,
            EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
            sizeof (PCH_S3_PEIM_VARIABLE),
            &PchS3PeimData
            );
  ASSERT_EFI_ERROR (Status);
  //AptioV server override end :setVariable for Bootscripthide support.
  return Status;
#else //AptioV server override: S3 support on AztecCity
  return EFI_SUCCESS;
#endif  //AptioV server override: S3 support on AztecCity
}
