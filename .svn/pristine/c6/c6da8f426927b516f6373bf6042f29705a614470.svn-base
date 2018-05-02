//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file
AMI defined Protocol header file Opal Security Init Protocol
 **/

#ifndef _AMI_OPAL_SEC_INIT_PROTOCOL_H
#define _AMI_OPAL_SEC_INIT_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Opal Security Init Protocol Definition
 */

#define AMI_HDD_OPAL_SEC_INIT_PROTOCOL_GUID \
        { 0x59af16b0, 0x661d, 0x4865, { 0xa3, 0x81, 0x38, 0xde, 0x68, 0x38, 0x5d, 0x8d } }

typedef struct _AMI_HDD_OPAL_SEC_INIT_PROTOCOL AMI_HDD_OPAL_SEC_INIT_PROTOCOL;

/**
    Installs StorageSecurityProtocol if the drive supports 
    Trusted commands

    @param BusInterface Ide or Ahci Bus Protocol Interface 
    @param ModeFlag     Ide or Ahci

    @retval 
        EFI_SUCCESS    : StorageSecurity supported.
        Others         : Not supported.

**/
typedef 
EFI_STATUS 
(EFIAPI *AMI_HDD_OPAL_SEC_INIT_INSTALL) (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

/**
    Uninstalls the Storage Security Protocol if it's installed on the handle 

    @param BusInterface Ide or Ahci Bus Protocol Interface 
    @param ModeFlag     Ide or Ahci

    @retval 
        EFI_SUCCESS                      : Security Mode supported.
        EFI_DEVICE_ERROR/EFI_UNSUPPORTED : Not supported.

**/
typedef 
EFI_STATUS 
(EFIAPI *AMI_HDD_OPAL_SEC_INIT_UNINSTALL) (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

struct _AMI_HDD_OPAL_SEC_INIT_PROTOCOL {
    AMI_HDD_OPAL_SEC_INIT_INSTALL    InstallOpalSecurityInterface;
    AMI_HDD_OPAL_SEC_INIT_UNINSTALL  UnInstallOpalSecurityInterface;
};

extern EFI_GUID gAmiHddOpalSecInitProtocolGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
