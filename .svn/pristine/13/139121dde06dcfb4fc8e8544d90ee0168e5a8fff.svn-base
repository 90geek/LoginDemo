/**
  This file contains an 'Intel Peripheral Driver' and is        
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
**/
/**

  Copyright (c) 2015 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.


    @file LtDxeLib.c

  This has platform-specific code for LT.  It contains hooks used by
  ServerCommon code that must be run during DXE for enabling/disabling/examining
  LT/TXT functions and status.

**/

#include <LtDxeLib.h>

EFI_HANDLE        mImageHandle;

//
// Helper PROCs for ServerCommonPkg/Universal/GetSec
//

/**

  Returns FLASH_REGION_SINIT_ACM_BASE to non-platform code

  @param  None

  @retval PCD for FLASH_REGION_SINIT_ACM_BASE

**/
UINTN
GetSinitAddress (
  VOID
  )
{
  return ((UINTN) FLASH_REGION_SINIT_ACM_BASE);
};

/**

  Returns Setup knob that says whether the system should
   be reset when ACM error occurs during LT lock

  @param  *BiosAcmErrorResetBit - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading Setup knob

**/
EFI_STATUS
GetBiosAcmErrorReset (
  UINT8 *BiosAcmErrorResetBit
  )
{
  EFI_STATUS              Status = EFI_UNSUPPORTED; 

  return Status;
}

/**

  Returns ACM type - see SYSTEM_CONFIGURATION for values

  @param  *AcmTypeValue - pointer back to value in ServerCommonPkg code

  @retval Status - Success/failure reading Setup knob

**/
EFI_STATUS
GetAcmType (
  UINT8 *AcmTypeValue
  )
{
  EFI_STATUS              Status = EFI_UNSUPPORTED; 

  return Status;
}

/**

  Writes ACM type - see SYSTEM_CONFIGURATION for values

  @param  *AcmTypeValue - pointer back to value in ServerCommonPkg code

  @retval Status - Success/failure reading/writing Setup knob

**/
EFI_STATUS
SetAcmType (
  IN UINT8 AcmTypeValue
  )
{
  EFI_STATUS              Status = EFI_UNSUPPORTED;
  return Status;
}

/**

  Returns Setup knob that says whether LT lock
   should be done 

  @param  *LockChipsetBit - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading Setup knob

**/
EFI_STATUS
GetLockChipset (
  UINT8 *LockChipsetBit
  )
{
  EFI_STATUS              Status; 
  UINTN                   VariableSize;
  SYSTEM_CONFIGURATION    SystemConfiguration;

  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);
  VariableSize = sizeof(SYSTEM_CONFIGURATION);

  Status = gRT->GetVariable (
		  L"IntelSetup",//AptioV Server Override
                  &gEfiSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SystemConfiguration
                  );  
  
  if (Status == EFI_SUCCESS) {
    *LockChipsetBit = SystemConfiguration.LockChipset;
  }

  return Status;
}

/**

  Returns Setup knob that says whether platform should be left unlocked
   i.e in Electrical Validation mode

  @param  *EVModeBit - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading Setup knob

**/
EFI_STATUS
GetEVMode (
  UINT8 *EVModeBit
  )
{
  EFI_STATUS              Status; 
  UINTN                   VariableSize;
  SYSTEM_CONFIGURATION    SystemConfiguration;

  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);
  VariableSize = sizeof(SYSTEM_CONFIGURATION);

  Status = gRT->GetVariable (
		  L"IntelSetup",//AptioV Server Override
                  &gEfiSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SystemConfiguration
                  );  
  
  if (Status == EFI_SUCCESS) {
    *EVModeBit = SystemConfiguration.EVMode;
  }

  return Status;
}

/**

  Writes Setup knob that says whether LT lock
   should be done 

  @param  LockChipsetValue - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading/writing Setup knob

**/
EFI_STATUS
SetLockChipset (
  IN UINT8 LockChipsetValue
  )
{
  EFI_STATUS              Status; 
  UINTN                   VariableSize;
  SYSTEM_CONFIGURATION    SystemConfiguration;
  UINT32                  Attributes = 0;

  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);
  VariableSize = sizeof(SYSTEM_CONFIGURATION);

  Status = gRT->GetVariable (
		  L"IntelSetup",//AptioV Server Override
                  &gEfiSetupVariableGuid,
                  &Attributes,
                  &VariableSize,
                  &SystemConfiguration
                  );  
  
  if (Status == EFI_SUCCESS) {
    SystemConfiguration.LockChipset = LockChipsetValue;

    Status = gRT->SetVariable (
		    L"IntelSetup",//AptioV Server Override
                   &gEfiSetupVariableGuid,
                   Attributes,
                   VariableSize,
                   &SystemConfiguration 
                   );
  }

  return Status;
}

/**

  Writes Setup knob that says whether platform should be left unlocked
   i.e in Electrical Validation mode

  @param  EVModeValue - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading/writing Setup knob

**/
EFI_STATUS
SetEVMode (
  IN UINT8 EVModeValue
  )
{
  EFI_STATUS              Status; 
  UINTN                   VariableSize;
  SYSTEM_CONFIGURATION    SystemConfiguration;
  UINT32                  Attributes = 0;

  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);
  VariableSize = sizeof(SYSTEM_CONFIGURATION);

  Status = gRT->GetVariable (
		  L"IntelSetup",//AptioV Server Override
                  &gEfiSetupVariableGuid,
                  &Attributes,
                  &VariableSize,
                  &SystemConfiguration
                  );  
  
  if (Status == EFI_SUCCESS) {
    SystemConfiguration.EVMode = EVModeValue;

    Status = gRT->SetVariable (
		    L"IntelSetup",//AptioV Server Override
                   &gEfiSetupVariableGuid,
                   Attributes,
                   VariableSize,
                   &SystemConfiguration 
                   );
  }

  return Status;
}

/**

  Returns Setup knob that says whether LT lock
   is enabled in this processor 

  @param  *ProcessorLtsxEnableBit - pointer back to flag in ServerCommonPkg code

  @retval Status - Success/failure reading Setup knob

**/
EFI_STATUS
GetProcessorLtsxEnable (
  UINT8 *ProcessorLtsxEnableBit
  )
{
  EFI_STATUS              Status;
  UINTN                   VariableSize;
  SYSTEM_CONFIGURATION    SystemConfiguration;

  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);
  VariableSize = sizeof(SYSTEM_CONFIGURATION);

  Status = gRT->GetVariable (
		  L"IntelSetup",//AptioV Server Override
                  &gEfiSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SystemConfiguration
                  );

  if (Status == EFI_SUCCESS) {
    *ProcessorLtsxEnableBit = SystemConfiguration.ProcessorLtsxEnable;
  }

  return Status;
}

/**

  Disables Setup knob that says whether LT lock
   should be done 

  Also disables Safer Mode Extensions

  @param  None

  @retval Status - Success/failure reading/writing Setup knob

**/
EFI_STATUS
SetDisableLtsx (
  VOID
  )
{
  EFI_STATUS              Status; 
  UINTN                   VariableSize;
  SYSTEM_CONFIGURATION    SystemConfiguration;
  UINT32                  Attributes = 0;

  SetMem (&SystemConfiguration, sizeof(SYSTEM_CONFIGURATION), 0);
  VariableSize = sizeof(SYSTEM_CONFIGURATION);

  Status = gRT->GetVariable (
		  L"IntelSetup",//AptioV Server Override
                  &gEfiSetupVariableGuid,
                  &Attributes,
                  &VariableSize,
                  &SystemConfiguration
                  );  
  
  if (Status == EFI_SUCCESS) {
    SystemConfiguration.ProcessorLtsxEnable = 0;
    SystemConfiguration.ProcessorSmxEnable = 0;

    Status = gRT->SetVariable (
		    L"IntelSetup",//AptioV Server Override
                   &gEfiSetupVariableGuid,
                   Attributes,
                   VariableSize,
                   &SystemConfiguration 
                   );
  }

  return Status;
}

/**

  Disables software SMI before LT-SX initialization

  @param  None

  @retval None

**/
VOID
SetDisableSoftwareSmi (
  VOID
  )
{
  UINT8 Buffer8 = IoRead8 (PCH_ACPI_BASE_ADDRESS + R_ACPI_SMI_EN) & ~(B_SWSMI_TMR_EN);
  IoWrite8 (PCH_ACPI_BASE_ADDRESS + R_ACPI_SMI_EN, Buffer8);
}

/**

  Write SA_DPR_REG with value passed in

  @param  ValueToSet - Value to write

  @retval None

**/
VOID
SetDprs(UINT32 ValueToSet)
{
  EFI_STATUS                          Status;
  UINT32                              OldValue, NewValue;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridge;
  UINT64                              PciAddress;
  UINT8                               *BaseBusNumbers;
  UINTN                               BaseBusCount;
  UINT8                               SocketIdx;

  Status = gBS->LocateProtocol (
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  &PciRootBridge
                  );
  ASSERT_EFI_ERROR (Status);

  BaseBusNumbers = (UINT8 *) PcdGetPtr (PcdSocketBaseBusNumbers);
  ASSERT (BaseBusNumbers != NULL);
  BaseBusCount = LibPcdGetSize (PcdToken (PcdSocketBaseBusNumbers)) / sizeof (UINT8);

  for (SocketIdx = 0; SocketIdx < BaseBusCount; SocketIdx++) {

    //
    // BUGBUG: the PciAddress for DPR Register is changed from generation to gen, so need a PCD here.
    //
    PciAddress = EFI_PCI_ADDRESS_EXT (
                  BaseBusNumbers [SocketIdx],
                  5,
                  0,
                  SA_DPR_REG
                  );

    OldValue = 0;
    Status = PciRootBridge->Pci.Read (
                                  PciRootBridge,
                                  EfiPciWidthUint32,
                                  PciAddress,
                                  1,
                                  &OldValue
                                  );
    DEBUG ((EFI_D_INFO, "TXT-LIB SA_DPR_REG Register [%08lx] was %x, ", PciAddress, OldValue));
    
    Status = PciRootBridge->Pci.Write (
                                  PciRootBridge,
                                  EfiPciWidthUint32,
                                  PciAddress,
                                  1,
                                  &ValueToSet
                                  );
    ASSERT_EFI_ERROR (Status);
    DEBUG ((EFI_D_INFO, "wrote %x, ", ValueToSet));
    
    NewValue = 0;
    Status = PciRootBridge->Pci.Read (
                                  PciRootBridge,
                                  EfiPciWidthUint32,
                                  PciAddress,
                                  1,
                                  &NewValue
                                  );
    DEBUG ((EFI_D_INFO, "now %x\n", NewValue));

    //
    // Assert error if programmed value is different from requested. This
    // means error in requested size.
    //
    if ((NewValue & 0xFF0) == (ValueToSet & 0xFF0)){
      S3BootScriptSaveMemWrite (
        S3BootScriptWidthUint32,
        (UINTN) MmPciAddress (BaseBusNumbers [SocketIdx], 5, 0, SA_DPR_REG),
        1,
        &NewValue
        );
    } else {
      if (OldValue & SA_DPR_LOCK) {
        DEBUG ((EFI_D_INFO, "TXT-LIB SA_DPR_REG written while already locked\n"));
      } else {
        DEBUG ((EFI_D_ERROR, "TXT-LIB SA_DPR_REG did not set correctly!!!\n"));
      }
    }
  }
}

/**

  Write SA_DPR_REG with value that locks it

  @param  None

  @retval None

**/
VOID
LockDprs(VOID)
{
  SetDprs(SA_DPR_LOCK);
}

/**

  Allocates 1 MB of 1MB-aligned memory for use as LT Device Memory.  Records
  the location of LT Device Memory in LT Chipset registers and then adds
  programming instructions for these registers into BootScript.

  @param   LtDxeCtx - A pointer to an initialized LT DXE Context data structure

  @retval  Status - EFI_SUCCESS always

**/
//AptioV Server override start: Commented as this is defined in TxtDxeLib.c
/*EFI_STATUS
SetupLtDeviceMemory (
  IN      LT_DXE_LIB_CONTEXT      *LtDxeCtx
  )
{
  EFI_STATUS                          Status;
  volatile UINT64                     *Ptr64;
  UINT64                              Value64;
  UINT32                              Value32;
  EFI_PHYSICAL_ADDRESS                Addr;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridge;
  UINT64                              PciAddress;
  EFI_IIO_SYSTEM_PROTOCOL             *IioSystemProtocol;
  IIO_GLOBALS                         *IioGlobalData;
  UINT8                               Iio;
  EFI_PLATFORM_INFO                   *PlatformInfo;
  EFI_HOB_GUID_TYPE                   *GuidHob;
  EFI_PHYSICAL_ADDRESS                TXTPublicBase  = TXT_PUBLIC_PRIVATE_BASE;
  
#if 1 //SINIT_IN_FLASH
  UINT8   * PtrSinitAddress;
  UINTN   SinitSize;
#endif
  //
  // Check whether we need to allocate memory
  //
  if ((LtDxeCtx->PlatformTxtDeviceMemory->SINITMemoryAddress == 0) ||
      (LtDxeCtx->PlatformTxtDeviceMemory->TXTHeapMemoryAddress == 0)) {
    //
    // We do not need support the case that SINIT/TXT heap unallocated, because they must be in DPR region.
    //
    return EFI_UNSUPPORTED;
  }
  
  Status = gBS->LocateProtocol (
                &gEfiPciRootBridgeIoProtocolGuid,
                NULL,
                &PciRootBridge
                );
  ASSERT_EFI_ERROR (Status);
  
  //
  // Find the PlatformInfo hob
  //
  GuidHob       = GetFirstGuidHob (&gEfiPlatformInfoGuid);
  PlatformInfo  = GET_GUID_HOB_DATA (GuidHob);
  ASSERT (PlatformInfo);

  //
  // Program LT Device Memory Chipset Registers and record them in
  // BootScript so they will be saved and restored on S3
  //

  //
  // NoDMA Registers
  // We do not need NoDMA support, which is deprecated by VTd
  //

  //
  // SINIT Registers
  //
  Ptr64       = (UINT64 *)(UINTN)(LT_PUBLIC_SPACE_BASE_ADDRESS + LT_SINIT_BASE_REG_OFF);
  Value64     = (UINT64)LtDxeCtx->PlatformTxtDeviceMemory->SINITMemoryAddress;
  *Ptr64      = Value64;
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32, 
    (UINT64)(UINTN)(Ptr64), 
    2, 
    &Value64
    );

  Ptr64       = (UINT64 *)(UINTN)(LT_PUBLIC_SPACE_BASE_ADDRESS + LT_SINIT_SIZE_REG_OFF);
  Value64     = (UINT64)LtDxeCtx->PlatformTxtDeviceMemory->SINITMemorySize;
  *Ptr64      = Value64;
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32, 
    (UINT64)(UINTN)(Ptr64), 
    2, 
    &Value64
    );

  ZeroMem (
    (VOID *)(UINTN)LtDxeCtx->PlatformTxtDeviceMemory->SINITMemoryAddress, 
    (UINTN)LtDxeCtx->PlatformTxtDeviceMemory->SINITMemorySize
    );

  //
  // TXTHEAP Registers
  //
  Ptr64       = (UINT64 *)(UINTN)(LT_PUBLIC_SPACE_BASE_ADDRESS + LT_HEAP_BASE_REG_OFF);
  Value64     = (UINT64)LtDxeCtx->PlatformTxtDeviceMemory->TXTHeapMemoryAddress;
  *Ptr64      = Value64;
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32, 
    (UINT64)(UINTN)(Ptr64), 
    2, 
    &Value64
    );

  Ptr64       = (UINT64 *)(UINTN)(LT_PUBLIC_SPACE_BASE_ADDRESS + LT_HEAP_SIZE_REG_OFF);
  Value64     = (UINT64)LtDxeCtx->PlatformTxtDeviceMemory->TXTHeapMemorySize;
  *Ptr64      = Value64;
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32, 
    (UINT64)(UINTN)(Ptr64), 
    2, 
    &Value64
    );

  ZeroMem (
    (VOID *)(UINTN)LtDxeCtx->PlatformTxtDeviceMemory->TXTHeapMemoryAddress, 
    (UINTN)LtDxeCtx->PlatformTxtDeviceMemory->TXTHeapMemorySize
    );   
    
  Status = PciRootBridge->Pci.Read (
                           PciRootBridge,
                           EfiPciWidthUint32,
                           EFI_PCI_ADDRESS_EXT (0, 5, 0, SA_DPR_REG),
                           1,
                           &Value32
                           );
  //
  // DPR Registers - skip if already programmed
  //  
  if (LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionAddress != 0 && ((Value32 & 0x0FFF) == 0)) {

    Status = gBS->LocateProtocol (
                    &gEfiIioSystemProtocolGuid,
                    NULL,
                    &IioSystemProtocol
                    );
    ASSERT_EFI_ERROR (Status);

    IioGlobalData = IioSystemProtocol->IioGlobalData;

    Value32 = ((UINT32)(LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionSize) >> 16) | SA_DPR_LOCK | SA_DPR_PRM;

    for (Iio = 0; Iio < MaxIIO; Iio++) {
      if (!IioGlobalData->IioVData.SocketPresent [Iio]) {
        continue;
      }
      
    //
	  // BUGBUG: the PciAddress for DPR Register is changed from generation to gen, so need a PCD here.
  	//
      PciAddress = EFI_PCI_ADDRESS_EXT (
                    IioGlobalData->IioVData.SocketBaseBusNumber [Iio],
                    5,
                    0,
                    SA_DPR_REG
                                      );

    Status = PciRootBridge->Pci.Write (
                                       PciRootBridge,
                                       EfiPciWidthUint32,
                                       PciAddress,
                                       1,
                                       &Value32
                                      );
      ASSERT_EFI_ERROR (Status);

    Value32 = 0;
    Status = PciRootBridge->Pci.Read (
                                       PciRootBridge,
                                       EfiPciWidthUint32,
                                       PciAddress,
                                       1,
                                       &Value32
                                       );
      DEBUG ((EFI_D_ERROR, "DPR Register [%08x] = %08x! on bus %x\n", PciAddress, Value32, IioGlobalData->IioVData.SocketBaseBusNumber [Iio]));

    //
    // Assert error if programmed value is different from requested. This
    // means error is requested size.
    //
    //BUGBUG: need to double check DPR REG//ASSERT (((Value32 & 0xFF0) << 16) == LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionSize);
    if (((Value32 & 0xFF0) << 16) == LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionSize){
      S3BootScriptSaveMemWrite (
        S3BootScriptWidthUint32,
          (UINTN)MmPciAddress (IioGlobalData->IioVData.SocketBaseBusNumber [Iio], 5, 0, SA_DPR_REG),
        1,
        &Value32
        );
    } else {
      DEBUG ((EFI_D_ERROR, "TXT-LIB SA_DPR_REG[0x%02x] = 0x%08x not set correctly!!! \n", SA_DPR_REG, Value32));
    }
    }

    //
    // DPR registers
    //
    Ptr64   = (UINT64 *) (UINTN) (LT_PUBLIC_SPACE_BASE_ADDRESS + LT_DMA_PROTECTED_RANGE_REG_OFF);
    Value64 = RShiftU64 (LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionSize, 16) | SA_DPR_LOCK ;
    //BUGBUG: we add top of the DPR, currently no one to set it?
    Value64 |= ((LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionAddress + LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionSize) & 0xFFF00000);

    *Ptr64 = Value64;
    //
    // Assert error if programmed value is different from requested. This
    // means error is requested size.
    //
    Value64 = *Ptr64;
    ASSERT ((LShiftU64 ((Value64 & 0xFFE), 16)) == LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionSize);

    S3BootScriptSaveMemWrite (
      S3BootScriptWidthUint32,
      (UINT64) (UINTN) (Ptr64),
      2,
      &Value64
      );

    //
    // Clear out the DMA protected memory area for use.
    //
    ZeroMem (
      (VOID *)(UINTN)LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionAddress, 
      (UINTN)LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionSize
      );
  }

  //
  // Fill BiosOsDataRegion
  //
  Ptr64 = (UINT64 *)(UINTN)(LtDxeCtx->PlatformTxtDeviceMemory->TXTHeapMemoryAddress + 8);
  
  if (LtDxeCtx->PlatformTxtPolicyData->BiosOsDataRegionRevision >= 2) {
    *(UINT64 *)(UINTN)LtDxeCtx->PlatformTxtDeviceMemory->TXTHeapMemoryAddress = sizeof(EFI_TXT_BIOS_OS_DATA_REGION_V3)+ 8 ;
    
    ((EFI_TXT_BIOS_OS_DATA_REGION_V3 *)Ptr64)->Revision = LtDxeCtx->PlatformTxtPolicyData->BiosOsDataRegionRevision;

    //
    // Allocate Physical Memory for LCP
    //
    ((EFI_TXT_BIOS_OS_DATA_REGION_V2 *)Ptr64)->LcpPolicyDataBase = 0;
    ((EFI_TXT_BIOS_OS_DATA_REGION_V2 *)Ptr64)->LcpPolicyDataSize = 0;

    if ((LtDxeCtx->PlatformTxtPolicyData->LcpPolicyDataBase != 0) &&
        (LtDxeCtx->PlatformTxtPolicyData->LcpPolicyDataSize != 0)) {

      //
      // LCP PD must be copied into a DMA protected region, here it will be copied to DPR region
      //
      Addr = LtDxeCtx->PlatformTxtDeviceMemory->DMAProtectionMemoryRegionAddress + (UINT32)LShiftU64 (PlatformInfo->PfatMemSize, 20);
      ZeroMem (
        (VOID *)(UINTN)Addr, 
        (UINTN)LtDxeCtx->PlatformTxtPolicyData->LcpPolicyDataSize
        );
      CopyMem (
        (VOID *)(UINTN)Addr,
        (VOID *)(UINTN)LtDxeCtx->PlatformTxtPolicyData->LcpPolicyDataBase,
        (UINTN)LtDxeCtx->PlatformTxtPolicyData->LcpPolicyDataSize
        );
      ((EFI_TXT_BIOS_OS_DATA_REGION_V3 *)Ptr64)->LcpPolicyDataBase = Addr;
      ((EFI_TXT_BIOS_OS_DATA_REGION_V3 *)Ptr64)->LcpPolicyDataSize = LtDxeCtx->PlatformTxtPolicyData->LcpPolicyDataSize;
    }
    
    ((EFI_TXT_BIOS_OS_DATA_REGION_V3 *)Ptr64)->NumberOfLogicalProcessors = (UINT32)LtDxeCtx->ApCount + 1;

    if (LtDxeCtx->PlatformTxtPolicyData->BiosOsDataRegionRevision == 3){
      ((EFI_TXT_BIOS_OS_DATA_REGION_V3 *)Ptr64)->FlagVariable = LtDxeCtx->PlatformTxtPolicyData->FlagVariable;
    }
  } 
  
  //
  // Set it to zero because SINIT_ACM is not loaded here.
  //
  ((EFI_TXT_BIOS_OS_DATA_REGION_V1 *)Ptr64)->BiosSinitSize = 0;

  //
  // Below debug should = 0x2c, when version = 3
  //
  DEBUG ((EFI_D_ERROR, "  Lt - BiosDataSize = 0x%08x\n", *(UINT64 *)(UINTN)LtDxeCtx->PlatformTxtDeviceMemory->TXTHeapMemoryAddress));

#if 1 //SINIT_IN_FLASH
    //
    // Copy SINIT-ACM to LT.SINIT.MEMORY.BASE(LT offset 0x270)
    //

#ifdef BTG_FLAG
    PtrSinitAddress = (UINT8 *)(UINTN)(LtDxeCtx->PlatformTxtPolicyData->StartupAcmAddress + 0x10000); // Get SINIT-ACM addresss 
#else
    PtrSinitAddress = (UINT8 *)(UINTN)(LtDxeCtx->PlatformTxtPolicyData->StartupAcmAddress + 0x20000); // Get SINIT-ACM addresss 
#endif

    SinitSize =  (UINTN) *(UINT32 *)(PtrSinitAddress+0x18);   // get SINIT-ACM size from ACM header
    SinitSize *= 4;                                 // Convert the size from 16 byte countes into byte countes
    DEBUG ((EFI_D_ERROR, " SINIT_IN_FLASH: copy from base:0x%08x, Size:0x%x\n", PtrSinitAddress,SinitSize));
      CopyMem (
        (VOID *)(UINTN)LtDxeCtx->PlatformTxtDeviceMemory->SINITMemoryAddress, 
        (VOID *)PtrSinitAddress,
        (UINTN)SinitSize
        );

    //
    // Update the SINIT size in BiosOsData region (in the TXT HEAP)
    //
    ((EFI_TXT_BIOS_OS_DATA_REGION_V3 *)Ptr64)->BiosSinitSize = (UINT32) SinitSize;
#endif
  
  //
  // Add TPM Decode and TXT Public and Private memory region as Runtime memory 
  // so that it can be reported in E820 table
  //
  Status = gDS->AddMemorySpace (
                  EfiGcdMemoryTypeMemoryMappedIo,
                  TXTPublicBase,
                  TXT_PUBLIC_PRIVATE_SIZE,
                  EFI_MEMORY_RUNTIME | EFI_MEMORY_UC
                  );
  ASSERT_EFI_ERROR(Status);

  Status = gDS->AllocateMemorySpace (
                  EfiGcdAllocateAddress,
                  EfiGcdMemoryTypeMemoryMappedIo,
                  0,
                  TXT_PUBLIC_PRIVATE_SIZE,
                  &TXTPublicBase,
                  mImageHandle,
                  NULL
                  );
  ASSERT_EFI_ERROR(Status);

  Status = gDS->SetMemorySpaceAttributes (
                  TXTPublicBase,
                  TXT_PUBLIC_PRIVATE_SIZE,
                  EFI_MEMORY_RUNTIME | EFI_MEMORY_UC
                  );
  ASSERT_EFI_ERROR (Status);
  

  return EFI_SUCCESS ;
}
*/
//AptioV Server override end: Commented as this is defined in TxtDxeLib.c
//
// The 8-bit data at offset 0xF in the ACM binary that gives ACM Type information. 
// It can be one of three values:
// 0x80 = debug signed ACM
// 0x40 = NPW production signed ACM
// 0x00 = PW production signed ACM
//
EFI_STATUS
FindAcmBinaryType()
{
  return EFI_SUCCESS;
}

/**
  Register the security handler to provide TPM measure boot service.

  @param  ImageHandle  ImageHandle of the loaded driver.
  @param  SystemTable  Pointer to the EFI System Table.

  @retval  EFI_SUCCESS            Register successfully.
  @retval  EFI_OUT_OF_RESOURCES   No enough memory to register this handler.
**/
EFI_STATUS
EFIAPI
LtDxeLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  mImageHandle = ImageHandle;
  return EFI_SUCCESS;
}
