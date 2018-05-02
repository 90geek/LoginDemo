//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//*************************************************************************
// Revision History
// ----------------
// $Log: $
//
//*************************************************************************

/** @file AmiTbtPlatformPolicy.h
    AMI Thunderbolt Platform Policy Protocol header file, define
    all the Thunderbolt Platform Policy equates and structures in
    this file.

**/

#ifndef _AMI_TBT_PLATFORM_POLICY_
#define _AMI_TBT_PLATFORM_POLICY_

#define AMI_TBT_PLATFROM_POLICY_PROTOCOL_GUID { 0x380D7A5E, 0x1BCA, 0x11E1, 0xA1, 0x10, 0xE8, 0xEB, 0x47, 0x24, 0x01, 0x9B }

typedef struct _AMI_TBT_PLATFORM_POLICY_PROTOCOL {
  UINT8                    TbtEnable;               ///< Enable/Disable Thunderbolt feature
  UINT8                    TbtGO2SX;                ///< GPIO pin number for TbtGO2SX
  UINT8                    TbtForcePWR;             ///< GPIO pin number for ForcePWR pin
  UINT8                    TbtHotPlugEvt;           ///< GPIO pin number for Hotplug event
  UINT8                    TbtOK2GO2SX_N;           ///< GPIO pin number for TbtOK2GO2SX_N
  UINT8                    CacheLineSize;           ///< Cache Line Size for Thunderbolt
  UINT8                    TbtWakeupSupport;        ///< Enable/Disable support wake from thunderbolt device feature
  UINT8                    TbtAICSupport;           ///< Enable/Disable support Thunderbolt AIC
  UINT8                    TbtHandlePOC;            ///< Enable/Disable BIOS handle Thunderbolt POC power
  UINT8                    TbtSecurityLevel;        ///< Thunderbolt host security level
  UINT8                    Bus;                     ///< Thunderbolt host location bus number
  UINT8                    Dev;                     ///< Thunderbolt host location device number
  UINT8                    Fun;                     ///< Thunderbolt host location function number
  UINT16                   ReserveMemoryPerSlot;    ///< Reserved Memory size for each  slot
  UINT16                   ReservePMemoryPerSlot;   ///< Reserved Pre-fetechable Memory size for each  slot
  UINT8                    ReserveIOPerSlot;        ///< Reserved IO size for each  slot
  UINT8                    SmiNotifyEnabled;        ///< Enable/Disable Thunderbolt notify and SMI
  UINT8                    SwSmiEnabled;            ///< Enable/Disable Thunderbolt SMI
  UINT8                    NotifyEnabled;           ///< Enable/Disable Thunderbolt notify
  UINT8                    TbtRmvReturnValue;       ///< ASL _RMV return value
  UINT8                    TbtOptionRom;            ///< Enable/Disable Thunderbolt device option rom
  UINT8                    TbtIOresourceEnable;     ///< Enable/Disable assign IO resource 
} AMI_TBT_PLATFORM_POLICY_PROTOCOL;

extern EFI_GUID gAmiTbtPlatformPolicyProtocolGuid;

#endif // _AMI_TBT_PLATFORM_POLICY_
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
