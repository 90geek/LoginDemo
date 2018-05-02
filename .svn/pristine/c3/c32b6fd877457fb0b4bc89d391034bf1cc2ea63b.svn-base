//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

#include <Token.h>
#include <Library/IoLib.h>
#include <Library/PchPlatformLib.h>

#define PCI_CONFIG_INDEX 0xcf8

static UINT32   gStoreCF8;
static UINT8    gStoreCMOS;
static UINT8    gStoreExtCMOS;

/**
  Performs platform specific tasks before invoking registered SMI handlers.
  
  This function performs platform specific tasks before invoking registered SMI handlers.
  
  @retval EFI_SUCCESS       The platform hook completes successfully.
  @retval Other values      The paltform hook cannot complete due to some error.

**/

EFI_STATUS EFIAPI ChipsetPlatformHookBeforeAfterSmmDispatch(BOOLEAN Save)
{
    UINT8           i;

    if (Save) {
      gStoreCF8 = IoRead32(PCI_CONFIG_INDEX);      // Store CF8 (PCI index)

      // Enable Alternate access mode, let port 70h can be readable.
      PchAlternateAccessMode (SB_RCBA, TRUE);

      // Read until value other than 0xFF returned or 100 reads performed
      for (i = 0; i < 100; i++) {
        gStoreCMOS = IoRead8(CMOS_ADDR_PORT);
        if (gStoreCMOS != 0xFF)
            break;
      }

      // Disable Alternate access mode.
      PchAlternateAccessMode (SB_RCBA, FALSE);

      gStoreCMOS &= 0x80;               // Combine CMOS index with NMI bit
      gStoreCMOS |= IoRead8(CMOS_IO_STD_INDEX);      // Store 0x74 standard CMOS index
      gStoreExtCMOS = IoRead8(CMOS_IO_EXT_INDEX);    // Store 0x72 extended CMOS index
    }
    else {
      IoWrite32(PCI_CONFIG_INDEX, gStoreCF8);      // Restore 0xCF8 (PCI index)
      IoWrite8(CMOS_ADDR_PORT, gStoreCMOS);       // Restore 0x70(CMOS index)
      IoWrite8(CMOS_IO_EXT_INDEX, gStoreExtCMOS); // Restore 0x72(EXT-CMOS index)
    }

    return EFI_SUCCESS;
}

