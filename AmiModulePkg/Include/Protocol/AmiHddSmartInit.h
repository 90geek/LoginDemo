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
AMI defined Protocol header file for Hdd Smart Init Protocol
 **/

#ifndef _AMI_HDD_SMART_INIT_PROTOCOL_H
#define _AMI_HDD_SMART_INIT_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * HDD Smart Init Protocol Definition
*/

#define AMI_HDD_SMART_INIT_PROTOCOL_GUID \
        { 0x9401bd4f, 0x1a00, 0x4990, { 0xab, 0x56, 0xda, 0xf0, 0xe4, 0xe3, 0x48, 0xde } }

typedef struct _AMI_HDD_SMART_INIT_PROTOCOL AMI_HDD_SMART_INIT_PROTOCOL;


/**
     * HddSmart Init Protocol Definition 
*/

/**
    Installs Ami Smart Protocol interface on the controller
        
    @param BusInterface Ide or Ahci Bus Protocol Interface 
    @param ModeFlag     Ide or Ahci

    @retval 
        EFI_STATUS

    @note  
      Already Smart support capability has been established.

**/
typedef 
EFI_STATUS 
(EFIAPI *AMI_HDD_SMART_INSTALL) (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

/**
    Uninstall the Ami Smart Protocol interface 
       
    @param BusInterface Ide or Ahci Bus Protocol Interface 
    @param ModeFlag     Ide or Ahci

    @retval 
        EFI_STATUS

**/
typedef 
EFI_STATUS 
(EFIAPI *AMI_HDD_SMART_UNINSTALL) (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

/**
    Initialize Smart functionality
        
    @param BusInterface Ide or Ahci Bus Protocol Interface 
    @param ModeFlag     Ide or Ahci

    @retval 
        EFI_STATUS

**/
typedef 
EFI_STATUS 
(EFIAPI *AMI_HDD_SMART_INIT) (
    IN VOID     *BusInterface,
    IN BOOLEAN  ModeFlag
);

struct _AMI_HDD_SMART_INIT_PROTOCOL {
    AMI_HDD_SMART_INSTALL       InstallSmartInterface;
    AMI_HDD_SMART_UNINSTALL     UnInstallSmartInterface;
    AMI_HDD_SMART_INIT          InitSmartSupport;
    BOOLEAN                     SmartDiagonasticFlag;
};


extern EFI_GUID gAmiHddSmartInitProtocolGuid;

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
