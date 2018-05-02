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


    @file LtDxeLib.h

  This has platform-specific code for LT.  It contains hooks used by
  ServerCommon code that must be run during DXE for enabling/disabling/examining
  LT/TXT functions and status.

**/

#ifndef _LT_DXE_LIB_H_
#define _LT_DXE_LIB_H_

#include <Uefi.h>

#include <PiDxe.h>
#include <Guid/PlatformTxt.h>
#include <Guid/PlatformInfo.h>
#include <Guid/SetupVariable.h>
#include <Include/IchRegs.h>
#include <Include/Platform.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/HobLib.h>
#include <Protocol/CpuIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/Spi.h>
#include <Protocol/MpService.h>
#include <Protocol/IioSystem.h>
#include <Uefi/UefiBaseType.h>
#include <FlashMap.h>
// Chispet register defines
//
#define SA_DPR_REG                          0x290
#define   SA_DPR_LOCK                       0x1
#define   SA_DPR_PRM                        0x4
    
// LT Configuration Space Register Definitions
//
#define LT_PUBLIC_SPACE_BASE_ADDRESS        0xFED30000
#define LT_DMA_PROTECTED_RANGE_REG_OFF      0x330

// Local macros
//
#define LT_SINIT_BASE_REG_OFF               0x270
#define LT_SINIT_SIZE_REG_OFF               0x278
#define LT_HEAP_BASE_REG_OFF                0x300
#define LT_HEAP_SIZE_REG_OFF                0x308

#ifndef SPI_OPCODE_READ_INDEX // AptioV Server Override Start
#define SPI_OPCODE_READ_INDEX               4
#endif //AptioV Server Override End

#define ACM_BASE_ADDRESS_MASK               0x00FFFFFF
#define ACM_TYPE_OFFSET                     0x0F
#define ACM_READ_SIZE                       0x10

#define TXT_PUBLIC_PRIVATE_BASE  0xFED20000   // TPM Decode and TXT Public/Private reg address
#define TXT_PUBLIC_PRIVATE_SIZE  0x25000      // TPM Decode and TXT Public/Private reg size

// Define PCI address macro for reg <= 0xFF
//
#define MmPciAddress(Bus, Device, Function, Register) \
      ( \
        (UINTN) (PcdGet64 (PcdPciExpressBaseAddress) + (UINTN) (Bus << 20) + (UINTN) (Device << 15) + (UINTN) \
          (Function << 12) + Register) \
      )

// Define PCI address macro for reg > 0xFF
//
#define EFI_PCI_ADDRESS_EXT(bus, dev, func, reg) \
    ((UINT64) ((((UINTN) reg) << 32) + (((UINTN) bus) << 24) + (((UINTN) dev) << 16) + (((UINTN) func) << 8)))

// External variables
//
extern EFI_RUNTIME_SERVICES        *gRT;
extern EFI_BOOT_SERVICES           *gBS;

// struct shared with ServerCommon TXT code
//  but need to define it here also because
//  can't unclude ServerCommon TXT include files
//  until after Brickland core-syncs to CP 3.1.2 or later
//
typedef struct _LT_DXE_LIB_CONTEXT_ {
  EFI_HANDLE                          ImageHandle;
  EFI_SYSTEM_TABLE                    *SystemTable;
  EFI_CPU_IO_PROTOCOL                 *CpuIo;
  EFI_MP_SERVICES_PROTOCOL            *MpService;
  EFI_PLATFORM_TXT_DEVICE_MEMORY      *PlatformTxtDeviceMemory;
  EFI_PLATFORM_TXT_POLICY_DATA        *PlatformTxtPolicyData;
  UINT8                               ApVector;
  UINT8                               ApCount;
  UINT32                              ApicId[512];
} LT_DXE_LIB_CONTEXT;

// External PROCs
//
UINT8
EFIAPI
IoRead8 (
  IN UINTN   Port
  );

UINT8
EFIAPI
IoWrite8 (
  IN UINTN   Port,
  IN UINT8   Value
  );

EFI_STATUS
FindAcmBinaryType (
  VOID
  );

#endif
