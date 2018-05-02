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
  Internal header file for the Flash Driver. Used by both the Dxe and Smm drivers.
**/

#ifndef __FLASH_COMMON__H__
#define __FLASH_COMMON__H__

#include <Protocol/AmiFlash.h>
#include <Library/AmiCriticalSectionLib.h>
#include <Library/AmiRomLayoutLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>

typedef struct
{
    UINT32 WriteEnableStatus;
    CRITICAL_SECTION Cs;
} FLASH_DRIVER_MAILBOX;

typedef struct
{
	AMI_FLASH_PROTOCOL Flash;
    FLASH_DRIVER_MAILBOX *MailBox;
} FLASH_PROTOCOL_PRIVATE;

extern FLASH_PROTOCOL_PRIVATE FlashData;

typedef struct
{
    AMI_ROM_AREA *RomArea;
    UINT32 AreaSize ;
} UPDATED_AREA_DESCRIPTOR;

extern UPDATED_AREA_DESCRIPTOR UpdatedArea[];
extern INT32 NumberOfUpdatedAreas;
extern CRITICAL_SECTION Cs;

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
