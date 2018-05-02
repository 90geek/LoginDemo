//****************************************************************************
//****************************************************************************
//**                                                                        **
//**           (C)Copyright 1985-2015, American Megatrends, Inc.            **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                        **
//**                          Phone: (770)-246-8600                         **
//**                                                                        **
//****************************************************************************
//****************************************************************************

/** @file SmbiosBoard.c
    This file contains Smbios porting code for OEM

**/

//----------------------------------------------------------------------------
// Includes

#include <Token.h>
#include <Efi.h>
#include <AmiDxeLib.h>
#include <Protocol/AmiCpuInfo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/SmbiosDynamicData.h>
// Aptio V Server override start - Type9 porting
#if UPDATE_SLOT_TYPE9  
#include <Protocol\IioUds.h>
#include <Protocol\LegacyBiosExt.h>
#endif
// Aptio V Server override end - Type9 porting
#include <Protocol/SmBus.h>
#include <Protocol/AmiSmbios.h>
#include <SmbiosOemUpdateList.h>
#include <AmiVfr.h>//TH0088
//AptioV server override start: dynamic MMCFG base change support.
#ifdef DYNAMIC_MMCFG_BASE_FLAG 
#include <Library/PciExpressLib.h> //AptioV server override: dynamic MMCFG base change support.
#endif
//AptioV server override end: dynamic MMCFG base change support.
#define PCI_CFG_ADDRESS(bus,dev,func,reg) \
    ((UINT64)((((UINTN)bus) << 24) + (((UINTN)dev) << 16) + (((UINTN)func) << 8) + ((UINTN)reg)))& 0x00000000ffffffff

#if (SMBIOS_STATIC_DATA_SUPPORT == 0) && (SMBIOS_STATIC_DATA_DT_SUPPORT == 0)
#define BASE_BOARD_INFO 0
#define SYS_CHASSIS_INFO 0
#define OEM_STRING_INFO 0
#define SYSTEM_CONFIG_OPTION_INFO 0
#define MEMORY_ERROR_INFO 0
#define ONBOARD_DEVICE_INFO 0
#define PORTABLE_BATTERY_INFO 0
#define ADDITIONAL_INFO 0
#define ONBOARD_DEVICE_EXTENDED_INFO 0
#define SYSTEM_POWER_SUPPLY_INFO 0
#define NUMBER_OF_ONBOARD_DEVICES 0
#define NO_OF_PORTABLE_BATTERY 0
#define NUMBER_OF_ONBOARD_DEVICES 0
#define ONBOARD_DEVICE_EXT_COUNT 0
#endif

#ifndef PROCESSOR_DMIEDIT_SUPPORT
#define PROCESSOR_DMIEDIT_SUPPORT 0
#endif

extern  EFI_BOOT_SERVICES   *pBS;

#if AMI_SMBIOS_PROTOCOL_ENABLE
AMI_SMBIOS_PROTOCOL         *gAmiSmbiosProtocol;
#endif

UINT8                       SmbusCmdReg;
EFI_SMBUS_HC_PROTOCOL       *gSMBus = NULL;

EFI_STATUS CreateBaseBoardDataForSMBios();
EFI_STATUS CreateChassisDataForSMBios();
EFI_STATUS CreateCPUDataForSMBios();
EFI_STATUS CreateSlotDataForSMBios();
EFI_STATUS CreateOnBoardDevDataForSMBios();
EFI_STATUS CreateBatteryDataForSMBios();
EFI_STATUS CreateOnBoardDevExtInfoForSMBios();
EFI_STATUS EnableSmbusController();
EFI_STATUS RestoreSmbusController();
EFI_STATUS GetSpdByte(EFI_SMBUS_DEVICE_ADDRESS SpdAddr, UINTN Offset, UINT8 *Data);
VOID       OemUpdate();

EFI_SMBIOS_BOARD_PROTOCOL   SmbiosBoardProtocol = {BASE_BOARD_INFO,
                                                  SYS_CHASSIS_INFO,
                                                  PROCESSOR_DMIEDIT_SUPPORT,
                                                  OEM_STRING_INFO,
                                                  SYSTEM_CONFIG_OPTION_INFO,
                                                  MEMORY_ERROR_INFO,
                                                  ONBOARD_DEVICE_INFO,
                                                  PORTABLE_BATTERY_INFO,
                                                  ADDITIONAL_INFO,
                                                  ONBOARD_DEVICE_EXTENDED_INFO,
                                                  SYSTEM_POWER_SUPPLY_INFO,
                                                  NO_OF_PROCESSOR_SOCKETS,
                                                  NUMBER_OF_SYSTEM_SLOTS,
                                                  NUMBER_OF_ONBOARD_DEVICES,
                                                  NO_OF_PHYSICAL_MEMORY_ARRAY,
                                                  NO_OF_PORTABLE_BATTERY,
                                                  ONBOARD_DEVICE_EXT_COUNT,
                                                  CreateBaseBoardDataForSMBios,
                                                  CreateChassisDataForSMBios,
                                                  CreateCPUDataForSMBios,
                                                  CreateSlotDataForSMBios,
                                                  CreateOnBoardDevDataForSMBios,
                                                  CreateBatteryDataForSMBios,
                                                  CreateOnBoardDevExtInfoForSMBios,
                                                  EnableSmbusController,
                                                  RestoreSmbusController,
                                                  GetSpdByte,
                                                  OemUpdate,
                                                  A1_MEMORY_SOCKETS,
#if NO_OF_PHYSICAL_MEMORY_ARRAY >= 2
                                                  A2_MEMORY_SOCKETS,
#endif
#if NO_OF_PHYSICAL_MEMORY_ARRAY >= 3
                                                  A3_MEMORY_SOCKETS,
#endif
#if NO_OF_PHYSICAL_MEMORY_ARRAY == 4
                                                  A4_MEMORY_SOCKETS,
#endif
                                                  };

typedef VOID (SMBIOS_OEM_UPDATE) (VOID);
extern SMBIOS_OEM_UPDATE SMBIOS_OEM_UPDATE_LIST EndOfSmbiosOemUpdateList;
SMBIOS_OEM_UPDATE* SmbiosOemUpdate[] = {SMBIOS_OEM_UPDATE_LIST NULL};

/**
    ***** PORTING REQUIRED *****
    (if SMBIOS module is part of the project)

    The purpose of this function is to allow OEM to update the
    SMBIOS table as needed. OEM can use the EFI_SMBIOS_PROTOCOL
    to read, add, delete, and write to the SMBIOS table.

    @param None

    @retval None

**/
VOID
OemUpdate (VOID)
{
//TH0088>>>>
    EFI_STATUS          Status = EFI_SUCCESS;
    UINT8               *Buffer = NULL;
    UINT16              BSize = 0;
    UINT16              Handle = 0;
    UINT64              PciAddress = 0;
    UINT8               SecBus = 0;
    UINT32              VID = 0;
    UINT8               SMS = 0;
    UINT8               PortCount = 0;
	UINT8               i;
    
    
    UINTN Size = sizeof(SETUP_HIDE_FEATURES);
    SETUP_HIDE_FEATURES SetupHideFeatures;
    EFI_GUID SetupHideGuid = SETUP_HIDE_GUID;

    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo = NULL;
    EFI_GUID gEfiPciRootBridgeIoProtocolGuid  = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;

    Status = pBS->LocateProtocol (
				&gAmiSmbiosProtocolGuid,
				NULL,
				&gAmiSmbiosProtocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->LocateProtocol (
                            &gEfiPciRootBridgeIoProtocolGuid,
                            NULL,
                            &gPciRootBridgeIo);
    ASSERT_EFI_ERROR(Status);

    Status = pRS->GetVariable (
                            L"SetupHideFeatures", \
                            &SetupHideGuid, \
                            NULL, \
                            &Size, \
                            &SetupHideFeatures );
    ASSERT_EFI_ERROR(Status);
    
    
    //
    //8. check SATA controller2.
    //
    Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(41, 8, &Buffer, &BSize);
    if (!EFI_ERROR(Status)) {
    	PciAddress = PCI_CFG_ADDRESS (0, 0x1F, 5, 0x00);
    	gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint32, PciAddress, 1, &VID);
    	if (VID != 0xFFFFFFFF) {
    		((SMBIOS_ONBOARD_DEV_EXT_INFO*)Buffer)->DeviceType |= 0x80;
        }
    	Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
    	gAmiSmbiosProtocol->SmbiosWriteStructure(Handle, Buffer, BSize);
    	pBS->FreePool(Buffer);
    }
    
    //
    //7. check SATA controller1.
    //
    Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(41, 7, &Buffer, &BSize);
    if (!EFI_ERROR(Status)) {
    	PciAddress = PCI_CFG_ADDRESS (0, 0x1F, 2, 0x00);
    	gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint32, PciAddress, 1, &VID);
    	
    	if (VID != 0xFFFFFFFF) {
    		((SMBIOS_ONBOARD_DEV_EXT_INFO*)Buffer)->DeviceType |= 0x80;
    		
    		PciAddress = PCI_CFG_ADDRESS (0, 0x1F, 2, 0x90);
    		gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint8, PciAddress, 1, &SMS);
    		
    		SMS = (SMS & (BIT06|BIT07)) >> 6; //bit7:6  SATA Mode Select
    		if (SMS == 0x01) {   //AHCI mode
    			*(UINT32*)(Buffer + 0x10) = 0x49434841;  //"AHCI"
    			} else if (SMS == 0x02) {    //RAID mode
    				*(UINT32*)(Buffer + 0x10) = 0x44494152;  //"RAID"
    				}
    	}
    	Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
    	gAmiSmbiosProtocol->SmbiosWriteStructure(Handle, Buffer, BSize);
    	pBS->FreePool(Buffer);
    }

    //
    //6. check SSATA controller.
    //
    Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(41, 6, &Buffer, &BSize);
    if (!EFI_ERROR(Status)) {
    	
    	PciAddress = PCI_CFG_ADDRESS (0, 0x11, 4, 0x00);
    	gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint32, PciAddress, 1, &VID);
    	if (VID != 0xFFFFFFFF) {
    		((SMBIOS_ONBOARD_DEV_EXT_INFO*)Buffer)->DeviceType |= 0x80;
    		
    		PciAddress = PCI_CFG_ADDRESS (0, 0x11, 4, 0x90);
    		gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint8, PciAddress, 1, &SMS);
    		
    		SMS = (SMS & (BIT06|BIT07)) >> 6; //bit7:6  SATA Mode Select
    		
    		if (SMS == 0x01) {   //AHCI mode
    			*(UINT32*)(Buffer + 0x10) = 0x49434841;  //"AHCI"
    			*(UINT32*)(Buffer + 0x14) = 0x6E6F4320;  //" Con"
    			*(UINT32*)(Buffer + 0x18) = 0x6C6F7274;  //"trol"
    			*(UINT32*)(Buffer + 0x1C) = 0x0072656C;  //"ler "
    			} else if (SMS == 0x02) {    //RAID mode
    				*(UINT32*)(Buffer + 0x10) = 0x44494152;  //"RAID"
    				*(UINT32*)(Buffer + 0x14) = 0x6E6F4320;  //" Con"
    				*(UINT32*)(Buffer + 0x18) = 0x6C6F7274;  //"trol"
    				*(UINT32*)(Buffer + 0x1C) = 0x0072656C;  //"ler "
    				}
    	}
    	Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
    	gAmiSmbiosProtocol->SmbiosWriteStructure(Handle, Buffer, BSize);
    	pBS->FreePool(Buffer);
    }

    //
    //5. check AST2400 VGA device.
    //
    Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(41, 5, &Buffer, &BSize);
    if (!EFI_ERROR(Status)) {
    	PciAddress = PCI_CFG_ADDRESS (0, 0x1C, 3, 0x00);
    	gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint32, PciAddress, 1, &VID);
    	if (VID != 0xFFFFFFFF) {
    		PciAddress = PCI_CFG_ADDRESS (0, 0x1C, 3, 0x19);
    		gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint8, PciAddress, 1, &SecBus);
    		PciAddress = PCI_CFG_ADDRESS (SecBus, 0, 0, 0x00);
    		gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint32, PciAddress, 1, &VID);
    		if (VID != 0xFFFFFFFF) {
    			PciAddress = PCI_CFG_ADDRESS (SecBus, 0, 0, 0x19);
    			gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint8, PciAddress, 1, &SecBus);
    			PciAddress = PCI_CFG_ADDRESS (SecBus, 0, 0, 0x00);
    			gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint32, PciAddress, 1, &VID);
    			if (VID == 0x20001A03) {
    				((SMBIOS_ONBOARD_DEV_EXT_INFO*)Buffer)->DeviceType |= 0x80;
    				((SMBIOS_ONBOARD_DEV_EXT_INFO*)Buffer)->BusNumber = SecBus;
    			}
    		}
    	} 
    	
    Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
    gAmiSmbiosProtocol->SmbiosWriteStructure(Handle, Buffer, BSize);
    pBS->FreePool(Buffer);
    }

	//
	//4. check LAN0-3 controller.
	//
	for(i = 0; i < 4; i++){
		Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(41, 4 -i, &Buffer, &BSize);
		Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
		if (!EFI_ERROR(Status)) {
			PciAddress = PCI_CFG_ADDRESS (0, 0x1C, 4 , 0x00);
			gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint32, PciAddress, 1, &VID);
			
			if (VID != 0xFFFFFFFF) {
				PciAddress = PCI_CFG_ADDRESS (0, 0x1C, 4, 0x19);
				gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint8, PciAddress, 1, &SecBus);
				PciAddress = PCI_CFG_ADDRESS (SecBus, 0, 3 - i, 0x00);
				gPciRootBridgeIo->Pci.Read (gPciRootBridgeIo, EfiPciWidthUint32, PciAddress, 1, &VID);
				
				if (VID == 0x15218086) {
					((SMBIOS_ONBOARD_DEV_EXT_INFO*)Buffer)->DeviceType |= 0x80;
					((SMBIOS_ONBOARD_DEV_EXT_INFO*)Buffer)->BusNumber = SecBus;
					((SMBIOS_ONBOARD_DEV_EXT_INFO*)Buffer)->DevFuncNumber = 0x03 - i;
					
					gAmiSmbiosProtocol->SmbiosWriteStructure(Handle, Buffer, BSize);
				}
			}
			pBS->FreePool(Buffer);
		}
	}
	
	//
    //Delete Type 8 structure by port count
	//
    PortCount = SetupHideFeatures.OnBoardI350PortCount;
    for(i = 0; i < 4-PortCount; i++){
		Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(8, 12-i, &Buffer, &BSize);
		Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
		gAmiSmbiosProtocol->SmbiosDeleteStructure(Handle);
		pBS->FreePool(Buffer);
    }
    //TH0088A>>>>
    //Delete Type 41 structure by port count 
    for(i = 0; i < 4-PortCount; i++){
		Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(41, 4-i, &Buffer, &BSize);
		Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
		gAmiSmbiosProtocol->SmbiosDeleteStructure(Handle);
		pBS->FreePool(Buffer);
    }
    //TH0088A<<<<
//TH0088<<<<
//----------------------------------------------------------------------------
/*
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   The following sample code DOES NOT serve any purposes.   ===
    // ===   It is included to illustrate the use of the SMBIOS       ===
    // ===   protocols only.                                          ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
{
    EFI_STATUS      Status;
    UINT8           *Buffer;
    UINT16          BSize;
    UINT16          Handle;

	Status = pBS->LocateProtocol(&gAmiSmbiosProtocolGuid, NULL, &gAmiSmbiosProtocol);
	ASSERT_EFI_ERROR(Status);

    // Read CPU structure
    Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(4, 1, &Buffer, &BSize);

    if (!EFI_ERROR(Status)) {
        // Update previously read CPU structure and write it back, overwriting old data
        Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
        ((SMBIOS_PROCESSOR_INFO*)Buffer)->MaxSpeed = 0x1234;
        gAmiSmbiosProtocol->SmbiosWriteStructure(Handle, Buffer, BSize);

        // Add structure with specific handle = 0x60
        Handle = 0x60;
        gAmiSmbiosProtocol->SmbiosAddStrucByHandle(Handle, Buffer, BSize);

        // Add structure with next available handle number
        gAmiSmbiosProtocol->SmbiosAddStructure(Buffer, BSize);

        // Delete structure with handle = 3
        gAmiSmbiosProtocol->SmbiosDeleteStructure(3);

        // Get available free handle, then add structure with that handle
        Handle = gAmiSmbiosProtocol->SmbiosGetFreeHandle();
        if (Handle != -1) {
            gAmiSmbiosProtocol->SmbiosAddStrucByHandle(Handle, Buffer, BSize);
        }

        // Free memory allocated by the earlier gAmiSmbiosProtocol->SmbiosReadStrucByType call
        pBS->FreePool(Buffer);
    }
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   End of sample code                                       ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
}
*/
//----------------------------------------------------------------------------

//===========================================================================
// 			 EC Version (Type 0 Offset 0x16-0x17) dynamic update
//
// This code requires EC major & minor versions to be available in
// ECRev1 & ECRev2 NVRAM variables respectively
//===========================================================================
#if (defined(DYNAMIC_UPDATE_TYPE0_EC_VERSION) && (DYNAMIC_UPDATE_TYPE0_EC_VERSION == 1))
/*
{
    EFI_STATUS  		Status;
	EFI_GUID    		gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
	UINT8				EcMajorVersion;
	UINT8				EcMinorVersion;
	UINTN				Size = sizeof(EcMajorVersion);
	UINT8				Type0Data[sizeof(SMBIOS_BIOS_INFO)];
	UINT16				Type0DataSize = sizeof(SMBIOS_BIOS_INFO);
	UINT8				*Type0DataPtr = &Type0Data[0];

	// Get EC version from ECRev1 & ECRev2 variables
    Status = pRS->GetVariable( L"ECRev1", \
                               &gEfiGlobalVariableGuid, \
                               NULL, \
                               &Size, \
                               &EcMajorVersion );
	if (EFI_ERROR(Status)) goto exitEcVersionUpdate;

    Status = pRS->GetVariable( L"ECRev2", \
                               &gEfiGlobalVariableGuid, \
                               NULL, \
                               &Size, \
                               &EcMinorVersion );
	if (EFI_ERROR(Status)) goto exitEcVersionUpdate;

    Status = pBS->LocateProtocol(
								&gAmiSmbiosProtocolGuid,
								NULL,
								&gAmiSmbiosProtocol);
    ASSERT_EFI_ERROR(Status);

    if (Status == EFI_SUCCESS) {
		// Read Smbios Type 0 structure, update EC version and write it back
		Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(
														0,
														1,
														&Type0DataPtr,
														&Type0DataSize);
	    ASSERT_EFI_ERROR(Status);

		((SMBIOS_BIOS_INFO*)Type0DataPtr)->ECFirmwareMajorRelease = EcMajorVersion;
		((SMBIOS_BIOS_INFO*)Type0DataPtr)->ECFirmwareMinorRelease = EcMinorVersion;

    	if (Status == EFI_SUCCESS) {
			Status = gAmiSmbiosProtocol->SmbiosWriteStructure(
						((SMBIOS_BIOS_INFO*)Type0DataPtr)->StructureType.Handle,
						Type0DataPtr,
						Type0DataSize);
		    ASSERT_EFI_ERROR(Status);
		}
	}

exitEcVersionUpdate:
	Status = EFI_SUCCESS;		// Dummy - To avoid build error in some cases
}
*/
#endif                                          // DYNAMIC_UPDATE_TYPE0_EC_VERSION
//===========================================================================
// 			 EC Version (Type 0 Offset 0x16-0x17) dynamic update End
//===========================================================================

//===========================================================================
//                *****  DO NOT REMOVE THIS BLOCK  *****
//
// 			 Hardware Security (Type 24) dynamic update Start
//
// Update Type 24 Administrator and Power-on Password Status based on
// Setup settings
//===========================================================================
#if (defined(TSE_BUILD) && (HARDWARE_SECURITY_INFO == 1))	// Token indicating AMI TSE is used
/*
{
#include <Setup.h>

#define AMITSESETUP_GUID \
			{ 0xc811fa38, 0x42c8, 0x4579, 0xa9, 0xbb, 0x60, 0xe9, 0x4e, 0xdd, 0xfb, 0x34 }

    EFI_STATUS  Status;
	EFI_GUID 	AmiTseSetupGuid = AMITSESETUP_GUID;
	AMITSESETUP AmiTseData;
    UINTN       VariableSize = sizeof(AMITSESETUP);
	UINTN		TsePasswordLength = SETUP_PASSWORD_LENGTH * sizeof(CHAR16);
	CHAR16 		*TestPassWord;
	UINT8		HwdSecSettings = 0;
	UINT8		*Type24Data;
	UINT16		Type24Size;

    Status = pRS->GetVariable ( L"AMITSESetup", \
                                &AmiTseSetupGuid, \
                                NULL, \
                                &VariableSize, \
                                &AmiTseData );

    if (!EFI_ERROR(Status)) {
	    Status = pBS->AllocatePool(EfiRuntimeServicesData, TsePasswordLength, &TestPassWord);
		if (Status == EFI_SUCCESS) {
			MemSet(TestPassWord, TsePasswordLength, 0);

			if (MemCmp(AmiTseData.UserPassword, TestPassWord, TsePasswordLength) != 0) {
				HwdSecSettings |= BIT6;			// Power-on Password
			}
			if (MemCmp(AmiTseData.AdminPassword, TestPassWord, TsePasswordLength) != 0) {
				HwdSecSettings |= BIT2;			// Administrator Password
			}

		    Status = pBS->LocateProtocol(&gAmiSmbiosProtocolGuid,
										NULL,
										&gAmiSmbiosProtocol);
		    ASSERT_EFI_ERROR(Status);

		    if (Status == EFI_SUCCESS) {
				Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(
																24,
																1,
																&Type24Data,
																&Type24Size);

			    ASSERT_EFI_ERROR(Status);

		    	if (Status == EFI_SUCCESS) {
					((SMBIOS_HARDWARE_SECURITY_INFO*)Type24Data)->HardwareSecSettings &= 0x33;	// Clear Admin & Power-on pwd
					((SMBIOS_HARDWARE_SECURITY_INFO*)Type24Data)->HardwareSecSettings |= HwdSecSettings;
					Status = gAmiSmbiosProtocol->SmbiosWriteStructure(
								((SMBIOS_HARDWARE_SECURITY_INFO*)Type24Data)->StructureType.Handle,
								Type24Data,
								Type24Size);
				    ASSERT_EFI_ERROR(Status);

					pBS->FreePool(Type24Data);
				}
			}

			pBS->FreePool(TestPassWord);
		}
	}
}
*/
#endif                                          // HARDWARE_SECURITY_INFO
//===========================================================================
// 			 Hardware Security (Type 24) dynamic update End
//===========================================================================

//===========================================================================
//                *****  DO NOT REMOVE THIS BLOCK  *****
//                *****  Calling OEM Update eLinks *****
//
//                     OEM Update eLinks Block Start
//===========================================================================
    {
        UINT8   i;

        for (i = 0; SmbiosOemUpdate[i] != NULL; i++) {
            SmbiosOemUpdate[i]();
        }
    }
//===========================================================================
//                     OEM Update eLinks Block End
//===========================================================================
}

/**
                     ***** PORTING REQUIRED *****
               (if SMBIOS module is part of the project)

    This function saves the current setting of the Smbus
    Controller CMD register and then enables it so that SPD data
    can be accessed.

    @param None

    @return EFI_STATUS

**/
EFI_STATUS
EnableSmbusController (VOID)
{
    EFI_GUID        EfiSMBusProtocolGuid = EFI_SMBUS_HC_PROTOCOL_GUID;

    // Enables the SMBus controller command register if needed.

    return pBS->LocateProtocol( &EfiSMBusProtocolGuid, NULL, (void **)&gSMBus );
}

/**
                     ***** PORTING REQUIRED *****
               (if SMBIOS module is part of the project)

    This function restores the Smbus Controller CMD register
    to the previously saved setting.

    @param None

    @return EFI_STATUS

**/
EFI_STATUS
RestoreSmbusController (VOID)
{
    EFI_STATUS  Status = EFI_UNSUPPORTED;

    return Status;
}

/**
                     ***** PORTING REQUIRED *****
               (if SMBIOS module is part of the project)

    This function reads a byte from the system memory SPD

    @param SpdAddr
    @param Offset
    @param Data

    @return EFI_STATUS \n
            if success, *Data contains SPD data byte

**/
EFI_STATUS
GetSpdByte (
    IN      EFI_SMBUS_DEVICE_ADDRESS    SpdAddr,
    IN      UINTN                       Offset,
    IN OUT  UINT8                       *Data
)
{
    UINTN   Length = 1;

    if (gSMBus == NULL) return EFI_UNSUPPORTED;

    return gSMBus->Execute( gSMBus,
                            SpdAddr,
                            Offset,
                            EfiSmbusReadByte,
                            FALSE,
                            &Length,
                            Data );
}

/**
                     ***** PORTING REQUIRED *****
               (if SMBIOS module is part of the project)

    This function gathers the System Slot status information and
    saves them in a variable named "SmbiosSlotsVar". This variable
    with the slot information is needed by the SMBIOS module to
    create the REQUIRED "Type 9" structure

    @param None

    @return EFI_STATUS \n
            Variable named "SmbiosSlotsVar" with system slot information

    @remark Refer to SYSTEM_SLOT_DYNAMIC_DATA in SmbiosDynamicData.h for\n
            structure information.

**/
EFI_STATUS
CreateSlotDataForSMBios (VOID)
{
    EFI_STATUS                      Status = EFI_SUCCESS;

#if UPDATE_SLOT_TYPE9
//    SmbiosSlotsVar = NULL;          // Remove this line when porting this function
/*
//----------------------------------------------------------------------------
//   PORTING REQUIRED   -   PORTING REQUIRED   -   PORTING REQUIRED
//----------------------------------------------------------------------------
//
// Create a SYSTEM_SLOT_DYNAMIC_DATA structure and fill it with system slots
// information - bus number for the slot and its current usage status.
// Return the slot structure information in a variable named "SmbiosSlotsVar"
//
*/
    // Aptio V Server override start: Type9 porting
    EFI_GUID                        EfiSmbiosDynamicDataGuid = EFI_SMBIOS_DYNAMIC_DATA_GUID;
    UINTN                           VarSize;
    UINT32                          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    SYSTEM_SLOT_DYNAMIC_DATA        SlotInfo;
    UINT8                           i;
    UINT8                           Value8;
    EFI_IIO_UDS_PROTOCOL  			*IIoUds;
    UINT8                       	IIOBus[NUMBER_CPU_SOCKETS] = {0xFF};
    UINTN							PcieBaseAddr; //AptioV server overrride start: Dynamic mmcfg base address change
    UINT32			Gp_Lvl2_Temp, Gp_Lvl3_Temp;//ZYY006001+
	Gp_Lvl2_Temp = IoRead32(GPIO_BASE_ADDRESS + 0x38);//ZYY006001+
	Gp_Lvl3_Temp = IoRead32(GPIO_BASE_ADDRESS + 0x48);//ZYY006001+
    Status = pBS->LocateProtocol(
     							&gEfiIioUdsProtocolGuid,
     							NULL,
     							&IIoUds);

    if (EFI_ERROR(Status))
        return Status;   
    
    TRACE((-1, "Updating SMBIOS type 9 slot data \n"));
    for (i = 0; i < NUMBER_CPU_SOCKETS; i++){
        if (!IIoUds->IioUdsPtr->PlatformData.IIO_resource[i].Valid){
     		   continue;
     	}
        IIOBus[i] = IIoUds->IioUdsPtr->PlatformData.IIO_resource[i].BusBase;
    }	
	

	//AptioV server overrride start: Dynamic mmcfg base address change
#ifdef DYNAMIC_MMCFG_BASE_FLAG 
    PcieBaseAddr = (UINTN) GetPciExpressBaseAddress ();
#else
    PcieBaseAddr = (UINTN) PcdGet64(PcdPciExpressBaseAddress);
#endif
    for (i = 0; i < NUMBER_OF_SYSTEM_SLOTS; i++) {	
       Value8 = 0xff;//TH0088	
            switch (i) {
//TH0088>>>>
#if Thor_SUPPORT == 1
/* TH0174
                case 0 :	SlotInfo.BusNumber[i] = IIOBus[IOH1_ID];	//TH0137
          	                Value8 = *(volatile UINT8*) (PcieBaseAddr + \
          	                		(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot1
                            break;
                case 1 :    if(IIOBus[IOH2_ID] != 0x80)
                				break;
                			SlotInfo.BusNumber[i] = IIOBus[IOH2_ID];	//TH0137
                  	  	    Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                  	  	    		(UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot2
                            break;
                case 2 :    if(IIOBus[IOH2_ID] != 0x80)
    							break;
                  	  	    Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                  	  	    		(UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot3
                            break;
                    case 3 :    
                  	  	    Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                  	  	    		(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (1 << 15) + (UINTN) (0 << 12) + 0x19 );	//SAS Mezzanine
                            break;
                    case 4 :    
                			Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                					(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (0 << 12) + 0x19 );	//10G Mezzanine              	
                            break;
TH0174 */
/*ZYY006001-START            
//TH0174>>>
            	case 0 :
            	case 1 :
            	case 2 :
            	case 3 :
						Value8 = *(volatile UINT8*) (PcieBaseAddr + \
							(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot1
						break;
						
            	case 4 :
            	case 5 :
            	case 6 :
						Value8 = *(volatile UINT8*) (PcieBaseAddr + \
							(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (2 << 12) + 0x19 );	//Slot3
						if(Value8 == 0xFF)
							Value8 = *(volatile UINT8*) (PcieBaseAddr + \
								(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (3 << 12) + 0x19 );	//Slot3
						break;
            		
            	case 7 :
            	case 8 :
            	case 9 :
            	case 10 :	
						if(IIOBus[IOH2_ID] != 0x80)
							break;
						Value8 = *(volatile UINT8*) (PcieBaseAddr + \
							(UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot2
						break;
            		
            	case 11 :
            	case 12 :
            	case 13 :
						if(IIOBus[IOH2_ID] != 0x80)
							break;
						Value8 = *(volatile UINT8*) (PcieBaseAddr + \
							(UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (2 << 12) + 0x19 );	//Slot4
						if(Value8 == 0xFF)
							Value8 = *(volatile UINT8*) (PcieBaseAddr + \
								(UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (1 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot4
						break;
//TH0174<<<
#else
//TH0088<<<<
                            
                case 0 :    
          	                Value8 = *(volatile UINT8*) (PcieBaseAddr + \
          	            		  (UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (0 << 12) + 0x19 );             
                            break;
                case 1 :    if(IIOBus[IOH2_ID] == 0xFF)
                				break;
                  	  	    Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                  	  			  (UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (1 << 15) + (UINTN) (0 << 12) + 0x19 );  
                            break;
                case 2 :    if(IIOBus[IOH2_ID] == 0xFF)
    							break;
                  	  	    Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                  	  			  (UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (0 << 12) + 0x19 );  
                            break;
                case 3 :    if(IIOBus[IOH2_ID] == 0xFF)
    							break;
                  	  	    Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                  	  			  (UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (2 << 12) + 0x19 );  
                            break;
                case 4 :    
                			Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                					(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (0 << 12) + 0x19 );              	
                            break;
                case 5 :    
                			Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                					(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (1 << 15) + (UINTN) (0 << 12) + 0x19 );              	
                            break;
                case 6 :    
                			Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                					(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (0x1C << 15) + (UINTN) (4 << 12) + 0x19 ); 
                			break;
                case 7:     if(IIOBus[IOH2_ID] == 0xFF)
    							break;  
                			Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                					(UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (0 << 12) + 0x19 ); 
#endif  //TH0088
                default :   break;
ZYY006001-END */
            
//ZYY006001+START            
                 case 0 :
                    		Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                    				(UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (0 << 12) + 0x19 );//Slot1 (x8x16)Riser x16
                    		break;
                 case 1 :
            				Value8 = *(volatile UINT8*) (PcieBaseAddr + \
            					    (UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (3 << 12) + 0x19 );//Slot2 (x8x16)Riser x4 	
            				break;
                 case 2 :
                 		    Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                				    (UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (0 << 12) + 0x19 );//Slot1 (x8x8)Riser x8	
                		    break;
                 case 3 :
            		        Value8 = *(volatile UINT8*) (PcieBaseAddr + \
            				        (UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (2 << 15) + (UINTN) (2 << 12) + 0x19 );//Slot2 (x8x8)Riser x8
            		        break;				    
            					
                 case 4 :
                            Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                                    (UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (1 << 15) + (UINTN) (0 << 12) + 0x19 );	//OCP Mezzanine
                            break;  
                 case 5 :
                            Value8 = *(volatile UINT8*) (PcieBaseAddr + \
                                    (UINTN) (IIOBus[IOH1_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (0 << 12) + 0x19 );	//SAS Mezzanine
                            break;  
                 case 6 :
            				if(IIOBus[IOH2_ID] != 0x80)
            					break;
            				Value8 = *(volatile UINT8*) (PcieBaseAddr + \
            					    (UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (1 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot2 (x8x16)Riser x8
            				break;
                 case 7 :
            			    if(IIOBus[IOH2_ID] != 0x80)
            				    break;
            			     Value8 = *(volatile UINT8*) (PcieBaseAddr + \
            				        (UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot1 (x8x16)Riser x16
            			     break;
                 case 8 :
            		         if(IIOBus[IOH2_ID] != 0x80)
            			         break;
            		         Value8 = *(volatile UINT8*) (PcieBaseAddr + \
            			            (UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (0 << 12) + 0x19 );	//Slot1 (x8x8)Riser x8
            		          break;	
                 case 9 :
            		         if(IIOBus[IOH2_ID] != 0x80)
            			         break;
            		         Value8 = *(volatile UINT8*) (PcieBaseAddr + \
            			            (UINTN) (IIOBus[IOH2_ID]  << 20) + (UINTN) (3 << 15) + (UINTN) (2 << 12) + 0x19 );	//Slot2 (x8x8)Riser x8
                    	     default :   break;
#endif //TH0088
//ZYY006001+END            
            }
  
   //AptioV server overrride end: Dynamic mmcfg base address change    
    if(Value8 == 0xFF){
        SlotInfo.CurrentUsage[i] = 0x02; //unknown
        SlotInfo.BusNumber[i] = 0xFF; //unknown
        
        //ZYY006006+START
        SlotInfo.SegGroupNumber[i] = 0xFFFF;
        SlotInfo.DevFuncNumber[i] = 0xFF;
        //ZYY006006+END
        
        continue;
    }

    // Fill slot bus number
//TH0137    SlotInfo.BusNumber[i] = Value8;
    SlotInfo.BusNumber[i] = Value8; //ZYY006001+
            
    // Check whether slot is available or in use
	//AptioV server overrride start: Dynamic mmcfg base address change   
	#ifdef DYNAMIC_MMCFG_BASE_FLAG 
    Value8 = *(volatile UINT8*) ((UINTN) GetPciExpressBaseAddress () + \
        (UINTN) (SlotInfo.BusNumber[i]  << 20) + (UINTN) (0 << 15) + (UINTN) (0 << 12) + 0 );  
	#endif		
	#ifndef DYNAMIC_MMCFG_BASE_FLAG 	 	
	Value8 = *(volatile UINT8*) ((UINTN) PcdGet64(PcdPciExpressBaseAddress) + \
        (UINTN) (SlotInfo.BusNumber[i]  << 20) + (UINTN) (0 << 15) + (UINTN) (0 << 12) + 0 );  
	#endif	
	 //AptioV server overrride end: Dynamic mmcfg base address change   
     	 	
    if (Value8 == 0xFF) {
        SlotInfo.CurrentUsage[i] = 0x03;
    }
    else {
        SlotInfo.CurrentUsage[i] = 0x04;
        }
    //ZYY006002+START
    if (Value8 != 0xFF) {
    	SlotInfo.SegGroupNumber[i] = 0x0; //ZYY006006+
        SlotInfo.DevFuncNumber[i] = 0x0;
    }
    //ZYY006002+END
    
    //ZYY006006+START
    else
    {
      SlotInfo.SegGroupNumber[i] = 0xFFFF;
      SlotInfo.BusNumber[i] = 0xFF;
      SlotInfo.DevFuncNumber[i] = 0xFF;
    }
    //ZYY006006+END
    
    } // for
    
    //ZY006001+START
        
    	/*
    	        CPU0:
    			2U2 Riser x8 + x8	GPIO 71 -> Low  
    								GPIO 34 -> High
    			2U2 Riser x8 + x16	GPIO 71 -> Low  
    								GPIO 34 -> Low
    			1U1 Riser x16		GPIO 71 -> High
    								GPIO 34 -> Low
    	*/

        
    	//Slot1 (PCIe_x20_CPU0) x20
        if (!(Gp_Lvl3_Temp & BIT7) && !(Gp_Lvl2_Temp & BIT2)) { // 2U2 Riser x8 + x16
        	SlotInfo.CurrentUsage[2] = 0x02; //Slot1 (x8x8)Riser x8
        	SlotInfo.CurrentUsage[3] = 0x02; //Slot2 (x8x8)Riser x8
        	//ZYY006006+START
        	if (SlotInfo.CurrentUsage[0] == 0x02){
        		SlotInfo.CurrentUsage[0] = 0x03;
        	}
        	if(SlotInfo.CurrentUsage[1] == 0x02){
        		SlotInfo.CurrentUsage[1] = 0x03;
        	}
        	//ZYY006006+END
        }else if (!(Gp_Lvl3_Temp & BIT7) && (Gp_Lvl2_Temp & BIT2)) {  // 2U2 Riser x8 + x8
        	SlotInfo.CurrentUsage[0] = 0x02; //Slot1 (x8x16)Riser x16
        	SlotInfo.CurrentUsage[1] = 0x02; //Slot2 (x8x16)Riser x4
        	//ZYY006006+START
        	if (SlotInfo.CurrentUsage[2] == 0x02){
        		SlotInfo.CurrentUsage[2] = 0x03;
        	}
        	if (SlotInfo.CurrentUsage[3] == 0x02){
        		SlotInfo.CurrentUsage[3] = 0x03;
        	}
        	//ZYY006006+END
    	}    
      	
        
    	/*
    	        CPU1:
    			2U2 Riser x8 + x8	GPIO 65 -> Low  
    								GPIO 66 -> High
    			2U2 Riser x8 + x16	GPIO 65 -> Low
    								GPIO 66 -> Low
    			1U1 Riser x16		GPIO 65 -> High
    								GPIO 66 -> Low
    	*/		
       	
    	//Slot1 (PCIe_x24_CPU0) x24
        if (!(Gp_Lvl3_Temp & BIT1) && !(Gp_Lvl3_Temp & BIT2)) { // 2U2 Riser x8 + x16
        	SlotInfo.CurrentUsage[8] = 0x02; //Slot1 (x8x8)Riser x8
        	SlotInfo.CurrentUsage[9] = 0x02; //Slot2 (x8x8)Riser x8
        	//ZYY006006+START
        	if (SlotInfo.CurrentUsage[6] == 0x02){
        		SlotInfo.CurrentUsage[6] = 0x03;
        	}
        	if (SlotInfo.CurrentUsage[7] == 0x02){
        		SlotInfo.CurrentUsage[7] = 0x03;
        	}
        	//ZYY006006+END
    	}else if (!(Gp_Lvl3_Temp & BIT1) && (Gp_Lvl3_Temp & BIT2)) { // 2U2 Riser x8 + x8
        	SlotInfo.CurrentUsage[6] = 0x02; //Slot2 (x8x16)Riser x8
        	SlotInfo.CurrentUsage[7] = 0x02; //Slot1 (x8x16)Riser x16
        	//ZYY006006+START
        	if (SlotInfo.CurrentUsage[8] == 0x02){
        		SlotInfo.CurrentUsage[8] = 0x03;
        	}
        	if (SlotInfo.CurrentUsage[9] == 0x02){
        		SlotInfo.CurrentUsage[9] = 0x03;
        	}
        	//ZYY006006+END

    	}	

    //ZYY006001+END 
    
    VarSize = sizeof(SYSTEM_SLOT_DYNAMIC_DATA);
    Status = pRS->SetVariable(SmbiosSlotsVar, &EfiSmbiosDynamicDataGuid,
                                    Attributes, VarSize, &SlotInfo);

	// Aptio V Server override end: Type9 porting
#endif                                          // UPDATE_SLOT_TYPE9

    return Status;
}

/**
    This function fills the input buffer with spaces. The number
    of spaces to be filled is specified in the input BufferSize

    @param BufferPtr
    @param BufferSize

    @return Buffer pointed by BufferPtr is filled with spaces

**/
VOID
FillStringBufferWithSpaces (
    IN UINT8    *BufferPtr,
    IN UINT8    BufferSize
)
{
    UINT8   i;

    for (i = 0; i < (BufferSize - 1); i++) {
        *BufferPtr = 0x20;
        BufferPtr++;
    }
    *BufferPtr = 0;
}

/**
        ***** PORTING REQUIRED *****
        (if SMBIOS module is part of the project)

    This function provides system chassis information. SMBIOS
    Core uses these information to dynamically update SMBIOS
    Chassis Type 2.

    @param None

    @return EFI_STATUS \n
            Creates variable named "SmbiosBaseBoardVar" with Chassis information

    @remark Refer to BASE_BOARD_DATA in SmbiosDynamicData.h for structure\n
            information.

**/
EFI_STATUS
CreateBaseBoardDataForSMBios (
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

#if UPDATE_BASEBOARD_TYPE2
    SmbiosBaseBoardVar = NULL;      // Remove this line when porting this function
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===               Start of SAMPLE TEMPLATE CODE                ===
    // ===                                                            ===
    // ===          Might need changes for specific platform          ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    BASE_BOARD_DATA     BaseBoardInfo;
    UINTN               VarSize;
    UINT32              Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;

    char* BoardID_Index[] = {
          "Board Name 1",       // 0x00
          "Board Name ",        // 0x01
          "Board Name ",        // 0x02
    };

    char* BoardManufacturerName = "XYZ Corporation";

    Status = pBS->LocateProtocol(
                        &gPlatformInfoProtocolGuid,
                        NULL,
                        &gPlatformInfoProtocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->AllocatePool(
                        EfiBootServicesData,
                        strlen(BoardManufacturerName),
                        &BaseBoardInfo.BoardManufacturer);

    strcpy(BaseBoardInfo.BoardManufacturer, BoardManufacturerName);

    Status = pBS->AllocatePool(
                        EfiBootServicesData,
                        strlen(BoardID_Index[gPlatformInfoProtocol->BoardId]),
                        &BaseBoardInfo.BoardName);

    strcpy(BaseBoardInfo.BoardName, BoardID_Index[gPlatformInfoProtocol->BoardId]);

    VarSize = sizeof(BASE_BOARD_DATA);

    Status = pRS->SetVariable(
                        SmbiosBaseBoardVar,
                        &gAmiSmbiosDynamicDataGuid,
                        Attributes,
                        VarSize,
                        &BaseBoardInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===                End of SAMPLE TEMPLATE CODE                 ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif                                          // UPDATE_BASEBOARD_TYPE2

    return Status;
}

/**
                     ***** PORTING REQUIRED *****
               (if SMBIOS module is part of the project)

    This function provides system chassis information. SMBIOS
    Core uses these information to dynamically update SMBIOS
    Chassis Type 3.

    @param None

    @return EFI_STATUS \n
            Creates variable named "SmbiosChassisVar" with Chassis information

    @remark Refer to CHASSIS_DATA in SmbiosDynamicData.h for structure\n
            information.

**/
EFI_STATUS
CreateChassisDataForSMBios (
)
{
    EFI_STATUS          Status = EFI_SUCCESS;

#if UPDATE_SYSTEM_CHASSIS_TYPE3
    SmbiosChassisVar = NULL;      // Remove this line when porting this function
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===               Start of SAMPLE TEMPLATE CODE                ===
    // ===                                                            ===
    // ===          Might need changes for specific platform          ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    CHASSIS_DATA        ChassisInfo;
    UINTN               VarSize;
    UINT32              Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;

    Status = pBS->LocateProtocol(
                        &gPlatformInfoProtocolGuid,
                        NULL,
                        &gPlatformInfoProtocol);
    ASSERT_EFI_ERROR(Status);

    switch (gPlatformInfoProtocol->PlatformFlavor) {
        case FlavorMobile:
            ChassisInfo.Type = 0x09; // EfiMiscChassisTypeLapTop
            break;
        case FlavorDesktop:
            ChassisInfo.Type = 0x03; // EfiMiscChassisTypeDeskTop
            break;
        case FlavorUpServer:
            ChassisInfo.Type = 0x11; // EfiMiscChassisTypeMainServerChassis
            break;
        default:
            ChassisInfo.Type = 0x02; // EfiMiscChassisTypeUnknown;
    }

    VarSize = sizeof(CHASSIS_DATA);
    Status = pRS->SetVariable(
                        SmbiosChassisVar,
                        &gAmiSmbiosDynamicDataGuid,
                        Attributes,
                        VarSize,
                        &ChassisInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===                End of SAMPLE TEMPLATE CODE                 ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif                                          // UPDATE_SYSTEM_CHASSIS_TYPE3

    return Status;
}

/**
                     ***** PORTING REQUIRED *****
               (if SMBIOS module is part of the project)

    This function gathers the System Processor information and
    saves them in a variable named "SmbiosCpuVar". This variable
    with the CPU information is needed by the SMBIOS module to
    create the "Type 4, 7" structure.

    @param None

    @return EFI_STATUS \n
            Variable named "SmbiosCpuVar" with System CPU information

    @remark Refer to CPU_DYNAMIC_DATA in SmbiosDynamicData.h for\n
            structure information.

          ******************** PORTING NOTE ********************\n
          By default, this function only returns EFI_SUCCESS and should\n
          only be ported if the CPU module does not install the\n
          SMBIOS_CPU_INFO_PROTOCOL.

**/
EFI_STATUS
CreateCPUDataForSMBios (VOID)
{
    EFI_STATUS                  Status = EFI_SUCCESS;

#if UPDATE_CPU_TYPE4
    SmbiosCpuVar = NULL;        // Remove this line when porting this function
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   Start of SAMPLE TEMPLATE CODE for Intel Weybridge CRB    ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    EFI_GUID                    gAmiCpuInfoProtocolGuid = AMI_CPU_INFO_PROTOCOL_GUID;
    UINTN                       NumCores = 1;
    UINTN                       NumHts = 1;
    UINTN                       i;
    UINTN                       j;
    UINT32                      Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT32                      L1Cache;
    UINT32                      L2Cache;
    UINT32                      L3Cache;
    AMI_CPU_INFO                *GetCpuInfo = NULL;
    AMI_CPU_INFO_PROTOCOL       *AmiCpuInfo;
    CPU_DYNAMIC_DATA            CpuInfo;
    CACHE_DESCRIPTOR_INFO       *CacheDescInfo;
    UINT8                       CacheTypeTable[] = {4, 3, 1, 5};
    UINT8                       AssociativityTable[] = {6, 1, 4, 1, 5, 1, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 8};

    Status = pBS->LocateProtocol (&gAmiCpuInfoProtocolGuid, NULL, &AmiCpuInfo);
    if (EFI_ERROR(Status)) return Status;

	CpuInfo.NumberCPU = NO_OF_PROCESSOR_SOCKETS;

    for(i = 0; i < NO_OF_PROCESSOR_SOCKETS; ++i) {
	    Status = AmiCpuInfo->GetCpuInfo(AmiCpuInfo, (UINTN)i*NumCores*NumHts, &GetCpuInfo);
	    if (Status) {
            // No data available from CPU module
            CpuInfo.CpuData[i].CpuData.Status = 0;
            CpuInfo.CpuData[i].CpuData.CurrentSpeed = 0;
            // Hardcode MaxSpeed to 4GHz (assumed system max speed)
            CpuInfo.CpuData[i].CpuData.MaxSpeed = 0x0FA0;
            CpuInfo.CpuData[i].CpuData.ExtClockFreq = CpuInfo.CpuData[0].CpuData.ExtClockFreq;
            CpuInfo.CpuData[i].CpuData.ProcessorID_1 = 0;
            CpuInfo.CpuData[i].CpuData.ProcessorID_2 = 0;
            CpuInfo.CpuData[i].CpuData.Voltage = BIT01;         // Assume 3.3V
            CpuInfo.CpuData[i].CpuData.Upgrade = CpuInfo.CpuData[0].CpuData.Upgrade;
            CpuInfo.CpuData[i].CpuData.Family = CpuInfo.CpuData[0].CpuData.Family;
            MemCpy(CpuInfo.CpuData[i].CpuData.Manufacturer, CpuInfo.CpuData[0].CpuData.Manufacturer, 18);
            MemCpy(CpuInfo.CpuData[i].CpuData.Version, CpuInfo.CpuData[0].CpuData.Version, 48);
            continue;
	    }

	    NumCores = GetCpuInfo->NumCores;
	    NumHts = GetCpuInfo->NumHts;
        CacheDescInfo = GetCpuInfo->CacheInfo;

        L1Cache = 0;
        L2Cache = 0;
        L3Cache = 0;
        CpuInfo.CpuData[i].L1Cache.SystemCacheType = 0xFF;
        CpuInfo.CpuData[i].L2Cache.SystemCacheType = 0xFF;
        CpuInfo.CpuData[i].L3Cache.SystemCacheType = 0xFF;
        for(j = 0; CacheDescInfo[j].Desc; ++j) {  // End of descriptors, Desc = 0.
            switch(GetCpuInfo->CacheInfo[j].Level) {
                case 1:
                        L1Cache = CacheDescInfo[j].Size;
                        if (CpuInfo.CpuData[i].L1Cache.SystemCacheType == 0xFF) {
           	                CpuInfo.CpuData[i].L1Cache.SystemCacheType = CacheTypeTable[CacheDescInfo[j].Type];
                        }
                        else {
			                CpuInfo.CpuData[i].L1Cache.SystemCacheType = 0x05;
                        }
                        CpuInfo.CpuData[i].L1Cache.Associativity = AssociativityTable[CacheDescInfo[j].Associativity];
                        break;
                case 2:
                        L2Cache = CacheDescInfo[j].Size;
                        if (CpuInfo.CpuData[i].L2Cache.SystemCacheType == 0xFF) {
                            CpuInfo.CpuData[i].L2Cache.SystemCacheType = CacheTypeTable[CacheDescInfo[j].Type];
                        }
                        else {
                            CpuInfo.CpuData[i].L2Cache.SystemCacheType = 0x05;
                        }
                        CpuInfo.CpuData[i].L2Cache.Associativity = AssociativityTable[CacheDescInfo[j].Associativity];
                        break;
                case 3:
                        L3Cache = CacheDescInfo[j].Size;
                        if (CpuInfo.CpuData[i].L3Cache.SystemCacheType == 0xFF) {
           	                CpuInfo.CpuData[i].L3Cache.SystemCacheType = CacheTypeTable[CacheDescInfo[j].Type];
                        }
                        else {
			                CpuInfo.CpuData[i].L3Cache.SystemCacheType = 0x05;
                        }
                        CpuInfo.CpuData[i].L3Cache.Associativity = AssociativityTable[CacheDescInfo[j].Associativity];
                        break;
            }
        }

        CpuInfo.CpuData[i].CpuData.CurrentSpeed = (UINT16)(GetCpuInfo->IntendedFreq);
        CpuInfo.CpuData[i].CpuData.MaxSpeed = 3800;     // Value from Intel Tiano BIOS
        CpuInfo.CpuData[i].CpuData.ExtClockFreq = (UINT16)(GetCpuInfo->FSBFreq);
        CpuInfo.CpuData[i].CpuData.ProcessorID_1 = (UINT32)(GetCpuInfo->Version);
        CpuInfo.CpuData[i].CpuData.ProcessorID_2 = (UINT32)(GetCpuInfo->Features);

        // From CPU module: GetCpuInfo->Voltage = Volt * 10000
        // From SMBIOS spec, this field should be set to CPU voltage * 10
        // Therefore this field should be set to GetCpuInfo->Voltage / 1000
        CpuInfo.CpuData[i].CpuData.Voltage = (UINT8)(GetCpuInfo->Voltage / 1000);
        CpuInfo.CpuData[i].CpuData.Status = 0x41;
        CpuInfo.CpuData[i].CpuData.Upgrade = 1;
        CpuInfo.CpuData[i].CpuData.Family = 0xBF;       // Intel(R) Core(TM) 2 Duo processor

        CpuInfo.CpuData[i].CpuData.CoreCount = GetCpuInfo->NumCores;
        CpuInfo.CpuData[i].CpuData.CoreEnabled = 1;
        CpuInfo.CpuData[i].CpuData.ThreadCount = GetCpuInfo->NumHts;
        CpuInfo.CpuData[i].CpuData.Family2 = 0xBF;

        if(i == 0) {
            FillStringBufferWithSpaces(CpuInfo.CpuData[i].CpuData.Version, sizeof(CpuInfo.CpuData[i].CpuData.Version));
            MemCpy(CpuInfo.CpuData[i].CpuData.Version, GetCpuInfo->BrandString, sizeof(CpuInfo.CpuData[i].CpuData.Version) - 1);
            FillStringBufferWithSpaces(CpuInfo.CpuData[i].CpuData.Manufacturer, sizeof(CpuInfo.CpuData[i].CpuData.Manufacturer));
            MemCpy(CpuInfo.CpuData[i].CpuData.Manufacturer, "Intel", 6);
        }
        else {
            MemCpy(CpuInfo.CpuData[i].CpuData.Manufacturer, CpuInfo.CpuData[0].CpuData.Manufacturer, sizeof(CpuInfo.CpuData[0].CpuData.Manufacturer));
            MemCpy(CpuInfo.CpuData[i].CpuData.Version, CpuInfo.CpuData[0].CpuData.Version, sizeof(CpuInfo.CpuData[0].CpuData.Version));
        }
        CpuInfo.CpuData[i].L1Cache.CacheConfig = 0x180;
        CpuInfo.CpuData[i].L1Cache.MaxCacheSize = L1Cache;  // CacheL1
        CpuInfo.CpuData[i].L1Cache.InstalledSize = L1Cache;
        CpuInfo.CpuData[i].L1Cache.SupportSRAM = 0x01;
        CpuInfo.CpuData[i].L1Cache.CurrentSRAM = 0x01;
        CpuInfo.CpuData[i].L1Cache.CacheSpeed = 0;
        CpuInfo.CpuData[i].L1Cache.ErrorCorrectionType = 0x03;

        CpuInfo.CpuData[i].L2Cache.CacheConfig = 0x281;
        CpuInfo.CpuData[i].L2Cache.MaxCacheSize = L2Cache;  // CacheL2
        CpuInfo.CpuData[i].L2Cache.InstalledSize = L2Cache;
        CpuInfo.CpuData[i].L2Cache.SupportSRAM = 0x01;
        CpuInfo.CpuData[i].L2Cache.CurrentSRAM = 0x01;
        CpuInfo.CpuData[i].L2Cache.CacheSpeed = 0;
        CpuInfo.CpuData[i].L2Cache.ErrorCorrectionType = 0x03;

        CpuInfo.CpuData[i].L3Cache.CacheConfig = 0x302;
        CpuInfo.CpuData[i].L3Cache.MaxCacheSize = L3Cache;  // CacheL3
        CpuInfo.CpuData[i].L3Cache.InstalledSize = L3Cache;
        CpuInfo.CpuData[i].L3Cache.SupportSRAM = 0x01;
        CpuInfo.CpuData[i].L3Cache.CurrentSRAM = 0x01;
        CpuInfo.CpuData[i].L3Cache.CacheSpeed = 0;
        CpuInfo.CpuData[i].L3Cache.ErrorCorrectionType = 0x03;
    }
    Status = pRS->SetVariable(
                            SmbiosCpuVar,
                            &gAmiSmbiosDynamicDataGuid,
                            Attributes,
                            sizeof(CPU_DYNAMIC_DATA),
                            &CpuInfo);
    ASSERT_EFI_ERROR(Status);
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   End of SAMPLE TEMPLATE CODE for Intel Weybridge CRB      ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/

/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===      Start of SAMPLE TEMPLATE CODE for AMD Warthog         ===
    // ===      platform. Uncomment this block to use.                ===
    // ===                                                            ===
    // ===      Might need changes for other platforms.               ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    EFI_GUID                gAmiCpuInfoProtocolGuid = AMI_CPU_INFO_PROTOCOL_GUID;
    UINT8                   AmiType, AmiAssoc, AmiCurLevel;
    UINT16                  AmiCurSize, L1CacheSize, L2CacheSize, L3CacheSize;
    UINT32                  Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINTN                   NumHts = 1, CurNode=0, CurCPU=0, NumCores = 1, CurCacheIndex;
    AMI_CPU_INFO            *AmiCpuInfo = NULL;
    AMI_CPU_INFO_PROTOCOL   *AmiCpuInfoProtocol;
    CPU_DYNAMIC_DATA        CpuInfo;
    CACHE_DESCRIPTOR_INFO   *AmiCacheDesc;
    CPU_DATA                *CurCpuData, *Cpu0Data;
    CACHE_DATA              *CurL1Cache, *CurL2Cache, *CurL3Cache;

    // ==================================================================
    // The mapping between AMI_CPU_INFO.CACHE_DESCRIPTOR_INFO.Type
    // and CPU_DYNAMIC_DATA.SINGLE_CPU_DATA.CACHE_DATA.SystemCacheType
    // should not require a translation table as the cache type is
    // encoded the same for both structures:
    //
    // CACHE_DESCRIPTOR_INFO.Type <-> CACHE_DATA.SystemCacheType
    //                (Other)   1 <-> 1
    //              (Unknown)   2 <-> 2
    //          (Instruction)   3 <-> 3
    //                 (Data)   4 <-> 4
    //              (Unified)   5 <-> 5
    //
    // ==================================================================
    // The mapping between AMI_CPU_INFO.CACHE_DESCRIPTOR_INFO.Associativity
    // and CPU_DYNAMIC_DATA.SINGLE_CPU_DATA.CACHE_DATA.Associativity
    // should not require a translation table as the cache associativity
    // is encoded the same for both structures:
    //
    // CACHE_DESCRIPTOR_INFO.Associativity <-> CACHE_DATA.Associativity
    //                         (Other)   1 <-> 1
    //                       (Unknown)   2 <-> 2
    //                        (Direct)   3 <-> 3
    //                     (2-way Set)   4 <-> 4
    //                     (4-way Set)   5 <-> 5
    //                         (Fully)   6 <-> 6
    //                     (8-way Set)   7 <-> 7
    //                    (16-way Set)   8 <-> 8
    //
    // ==================================================================
    // Fill Processor Information Table (Type 4) and associated Cache
    // Information structures.
    //
    // Notes:   A SINGLE_CPU_DATA structure is created for each
    //          slot/socket such that only one structure is created for
    //          a multi-core processor.  This implies the assumption
    //          that all cores on a processor have identical
    //          configuration.
    //
    // ==================================================================
    Status = pBS->LocateProtocol (
                &gAmiCpuInfoProtocolGuid,
                NULL,
                &AmiCpuInfoProtocol);
    if (EFI_ERROR(Status))
        return Status;

    Status = AmiCpuInfoProtocol->GetCpuInfo(
                AmiCpuInfoProtocol,
                0,
                &AmiCpuInfo);
    if (EFI_ERROR(Status))
        return Status;

    CpuInfo.NumberCPU = NO_OF_PROCESSOR_SOCKETS;
    Cpu0Data = &(CpuInfo.CpuData[0].CpuData);

    // For each Core0 on each slot/node, create a
    // CPU information table.
    for(CurNode=0, CurCPU=0;
        CurNode < NO_OF_PROCESSOR_SOCKETS;
        CurNode++, CurCPU = AmiCpuInfo->NumCores*CurNode )
    {
        Status = AmiCpuInfoProtocol->GetCpuInfo(
                        AmiCpuInfoProtocol,
                        CurCPU,
                        &AmiCpuInfo);

        // some pointers to make code easier to read/type
        CurCpuData = &(CpuInfo.CpuData[CurNode].CpuData);
        CurL1Cache = &(CpuInfo.CpuData[CurNode].L1Cache);
        CurL2Cache = &(CpuInfo.CpuData[CurNode].L2Cache);
        CurL3Cache = &(CpuInfo.CpuData[CurNode].L3Cache);

        // if an AMI_CPU_INFO structure does not exist for this Socket
        // then fill with default data and attempt to get next
        // socket information.
        if (Status) {
            CurCpuData->Status = 0;
            CurCpuData->CurrentSpeed = 0;
            CurCpuData->MaxSpeed = 0x0FA0;
            CurCpuData->ExtClockFreq = Cpu0Data->ExtClockFreq;
            CurCpuData->ProcessorID_1 = 0;
            CurCpuData->ProcessorID_2 = 0;
            CurCpuData->Status = 0;
            CurCpuData->Upgrade = Cpu0Data->Upgrade;
            CurCpuData->Family = Cpu0Data->Family;
            MemCpy(CurCpuData->Manufacturer, Cpu0Data->Manufacturer, 18);
            MemCpy(CurCpuData->Version, Cpu0Data->Version, 48);
            continue;
        }

        NumCores = AmiCpuInfo->NumCores;
        NumHts = AmiCpuInfo->NumHts;
        AmiCacheDesc = AmiCpuInfo->CacheInfo;
        L1CacheSize = 0;
        L2CacheSize = 0;
        L3CacheSize = 0;

        // if more than one L1, L2, or L3 cache exits,
        // its type will be unified by default.
        CurL1Cache->SystemCacheType = 0xFF;
        CurL2Cache->SystemCacheType = 0xFF;
        CurL3Cache->SystemCacheType = 0xFF;

        // ==========================================================
        // Fill Cache Information Table (Type 7) for this slot/node
        // ==========================================================
        for ( CurCacheIndex = 0;
              AmiCacheDesc[CurCacheIndex].Desc;   // Desc == 0 is last
              ++CurCacheIndex )
        {
            AmiType = AmiCacheDesc[CurCacheIndex].Type;
            AmiAssoc = AmiCacheDesc[CurCacheIndex].Associativity;
            AmiCurLevel = AmiCacheDesc[CurCacheIndex].Level;
            AmiCurSize = AmiCacheDesc[CurCacheIndex].Size;

            switch ( AmiCurLevel )
            {
                case EFI_CACHE_L1:
                    L1CacheSize = AmiCurSize;
                    if (CurL1Cache->SystemCacheType == 0xFF)
                        CurL1Cache->SystemCacheType = AmiType;
                    else
                        CurL1Cache->SystemCacheType = 0x05;
                    CurL1Cache->Associativity = AmiAssoc;
                    break;
                case EFI_CACHE_L2:
                    L2CacheSize = AmiCurSize;
                    if (CurL2Cache->SystemCacheType == 0xFF)
                        CurL2Cache->SystemCacheType = AmiType;
                    else
                        CurL2Cache->SystemCacheType = 0x05;
                    CurL2Cache->Associativity = AmiAssoc;
                    break;
                case EFI_CACHE_L3:
                    L3CacheSize = AmiCurSize;
                    if (CurL3Cache->SystemCacheType == 0xFF)
                        CurL3Cache->SystemCacheType = AmiType;
                    else
                        CurL3Cache->SystemCacheType = 0x05;
                    CurL3Cache->Associativity = AmiAssoc;
                    break;
            } // switch
        } // for

        CurCpuData->CurrentSpeed = (UINT16)(AmiCpuInfo->ActualFreq);
#if AMD_SYSTEM_BOARD == 1
        CurCpuData->MaxSpeed = (UINT16)(AmiCpuInfo->MaxFreq);
#endif
        CurCpuData->ExtClockFreq = (UINT16)(AmiCpuInfo->FSBFreq);
        CurCpuData->ProcessorID_1 = (UINT32)(AmiCpuInfo->Version);
        CurCpuData->ProcessorID_2 = (UINT32)(AmiCpuInfo->Features);
        CurCpuData->Status = 0x41;                  // Socket popuated
                                                    // and CPU enabled
        CurCpuData->Upgrade = SMBIOS_PROCESSOR_UPGRADE; // CPU.sdl tokens
        CurCpuData->Family = SMBIOS_PROCESSOR_FAMILY;
        if(CurNode == 0) {
            FillStringBufferWithSpaces(
                CurCpuData->Version,
                sizeof(CurCpuData->Version));
            MemCpy(
                CurCpuData->Version,
                AmiCpuInfo->BrandString,
                sizeof(CurCpuData->Version) - 1);
            FillStringBufferWithSpaces(
                CurCpuData->Manufacturer,
                sizeof(CurCpuData->Manufacturer));
            MemCpy(
                CurCpuData->Manufacturer,
                AmiCpuInfo->BrandString,
                5);
        }
        else {
            MemCpy(
                CurCpuData->Manufacturer,
                Cpu0Data->Manufacturer,
                sizeof(Cpu0Data->Manufacturer));
            MemCpy(
                CurCpuData->Version,
                Cpu0Data->Version,
                sizeof(Cpu0Data->Version));
        }
        CurL1Cache->CacheConfig = 0x180;
        CurL1Cache->MaxCacheSize = L1CacheSize;  // CacheL1
        CurL1Cache->InstalledSize = L1CacheSize;
        CurL1Cache->SupportSRAM = 0x01;
        CurL1Cache->CurrentSRAM = 0x01;
        CurL1Cache->CacheSpeed = 0;
        CurL1Cache->ErrorCorrectionType = 0x03;

        CurL2Cache->CacheConfig = 0x281;
        CurL2Cache->MaxCacheSize = L2CacheSize;  // CacheL2
        CurL2Cache->InstalledSize = L2CacheSize;
        CurL2Cache->SupportSRAM = 0x01;
        CurL2Cache->CurrentSRAM = 0x01;
        CurL2Cache->CacheSpeed = 0;
        CurL2Cache->ErrorCorrectionType = 0x03;

        CurL3Cache->CacheConfig = 0x302;
        CurL3Cache->MaxCacheSize = L3CacheSize;  // CacheL3
        CurL3Cache->InstalledSize = L3CacheSize;
        CurL3Cache->SupportSRAM = 0x01;
        CurL3Cache->CurrentSRAM = 0x01;
        CurL3Cache->CacheSpeed = 0;
        CurL3Cache->ErrorCorrectionType = 0x03;
    } // for

    Status = pRS->SetVariable(  SmbiosCpuVar,
                                &gAmiSmbiosDynamicDataGuid,
                                Attributes,
                                sizeof(CPU_DYNAMIC_DATA),
                                &CpuInfo );
    ASSERT_EFI_ERROR(Status);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===      End of SAMPLE TEMPLATE CODE for AMD Warthog           ===
    // ===      platform. Uncomment this block to use.                ===
    // ===                                                            ===
    // ===      Might need changes for other platforms.               ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif                                          // UPDATE_CPU_TYPE4

    return Status;
}

/**
                         ***** OPTIONAL *****
               (if SMBIOS module is part of the project)

    This function gathers the Onboard Device status information and
    saves them in a variable named "SmbiosOnBoardVar". This variable
    with the OnBoard Device information is needed by the SMBIOS
    module to create the "Type 10" structure.

    @param None

    @return EFI_STATUS \n
            Variable named "SmbiosOnBoardVar" with on-board device information

    @remark Refer to ONBOARD_DEV_DYNAMIC_DATA in SmbiosDynamicData.h for\n
            structure information.\n

            @li Set device status to 0 if disabled.
            @li Set device status to 0x80 if enabled.\n
            Ex: In sample code\n
                OnBoardDevInfo.OnBoardDev[0] = 0;           // Disabled\n
                OnBoardDevInfo.OnBoardDev[0] = 0x80;        // Enabled

**/
EFI_STATUS
CreateOnBoardDevDataForSMBios (VOID)
{
    EFI_STATUS                      Status = EFI_SUCCESS;

#if UPDATE_ONBOARD_DEV_TYPE10
    SmbiosOnBoardVar = NULL;        // Remove this line when porting this function
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   Start of SAMPLE TEMPLATE CODE for Intel Weybridge CRB    ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    UINTN                           VarSize;
    UINT32                          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    ONBOARD_DEV_DYNAMIC_DATA        OnBoardDevInfo;
    UINT64                          PciAddress;
    UINT8                           Value8;
    EFI_GUID gEfiPciRootBridgeIoProtocolGuid  = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

    Status = pBS->LocateProtocol(
                                &gEfiPciRootBridgeIoProtocolGuid,
                                NULL,
                                &gPciRootBridgeIo);
    ASSERT_EFI_ERROR(Status);

    // Onboard Video
    PciAddress = PCI_CFG_ADDRESS (0, 0, 0, MCH_REG_GGC);
    gPciRootBridgeIo->Pci.Read (
                                gPciRootBridgeIo,
                                EfiPciWidthUint8,
                                PciAddress,
                                1,
                                &Value8);
    if (Value8 & BIT01) {
        OnBoardDevInfo.OnBoardDev[0] = 0;           // Disabled
    }
    else {
        OnBoardDevInfo.OnBoardDev[0] = 0x80;        // Enabled
    }

    // Onboard LAN
    Value8 = *(UINT8*)(SB_RCBA + R_RCBA_BUC);
    if (Value8 & B_LAN_DISABLE) {
        OnBoardDevInfo.OnBoardDev[1] = 0;           // Disabled
    }
    else {
        OnBoardDevInfo.OnBoardDev[1] = 0x80;        // Enabled
    }

    // Onboard 1394 - Use GPIO49 0/1 = Enabled/Disabled
    Value8 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2 + 2);
    if (Value8 & BIT01) {
        OnBoardDevInfo.OnBoardDev[2] = 0;           // Disabled
    }
    else {
        OnBoardDevInfo.OnBoardDev[2] = 0x80;        // Enabled
    }

    VarSize = sizeof(ONBOARD_DEV_DYNAMIC_DATA);
    Status = pRS->SetVariable(SmbiosOnBoardVar, &gAmiSmbiosDynamicDataGuid,
                        Attributes, VarSize, &OnBoardDevInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   End of SAMPLE TEMPLATE CODE for Intel Weybridge CRB      ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif                                          // UPDATE_ONBOARD_DEV_TYPE10

    return Status;
}

/**
                         ***** OPTIONAL *****
               (if SMBIOS module is part of the project)

    This function gathers the Onboard Device status information
    and saves them in a variable named "SmbiosOnBoardExtVar".
    This variable with the OnBoard Device Extended information
    is needed by the SMBIOS module to create the "Type 41"
    structure.

    @param None

    @return EFI_STATUS \n
            Variable named "SmbiosOnBoardExtVar" with on-board device\n
            information.

    @remark Refer to ONBOARD_DEV_EXT_DYNAMIC_DATA in SmbiosDynamicData.h for\n
            structure information.\n

            @li Set device status to 0 if disabled.
            @li Set device status to 0x80 if enabled.\n
            Ex: In sample code\n
                OnBoardDevInfo.OnBoardDev[0] = 0;           // Disabled\n
                OnBoardDevInfo.OnBoardDev[0] = 0x80;        // Enabled

**/
EFI_STATUS
CreateOnBoardDevExtInfoForSMBios (VOID)
{
    EFI_STATUS                      Status = EFI_SUCCESS;

#if UPDATE_DEVICE_EXT_TYPE41
    SmbiosOnBoardExtVar = NULL;     // Remove this line when porting this function
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   Start of SAMPLE TEMPLATE CODE for Intel Weybridge CRB    ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    UINTN                           VarSize;
    UINT32                          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    ONBOARD_DEV_EXT_DYNAMIC_DATA    OnBoardDevExtInfo;
    UINT64                          PciAddress;
    UINT8                           Value8;
    EFI_GUID gEfiPciRootBridgeIoProtocolGuid  = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

    Status = pBS->LocateProtocol(
                                &gEfiPciRootBridgeIoProtocolGuid,
                                NULL,
                                &gPciRootBridgeIo);
    ASSERT_EFI_ERROR(Status);

    // Onboard Video
    PciAddress = PCI_CFG_ADDRESS (0, 0, 0, MCH_REG_GGC);
    gPciRootBridgeIo->Pci.Read (
                                gPciRootBridgeIo,
                                EfiPciWidthUint8,
                                PciAddress,
                                1,
                                &Value8);
    if (Value8 & BIT01) {
        OnBoardDevExtInfo.OnBoardDev[0] = 0;           // Disabled
    }
    else {
        OnBoardDevExtInfo.OnBoardDev[0] = 0x80;        // Enabled
    }

    OnBoardDevExtInfo.BusNumber[0] = 0;

    // Onboard LAN
    Value8 = *(UINT8*)(SB_RCBA + R_RCBA_BUC);
    if (Value8 & B_LAN_DISABLE) {
        OnBoardDevExtInfo.OnBoardDev[1] = 0;           // Disabled
    }
    else {
        OnBoardDevExtInfo.OnBoardDev[1] = 0x80;        // Enabled
    }

    OnBoardDevExtInfo.BusNumber[1] = 0;

    // Onboard 1394 - Use GPIO49 0/1 = Enabled/Disabled
    Value8 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2 + 2);
    if (Value8 & BIT01) {
        OnBoardDevExtInfo.OnBoardDev[2] = 0;           // Disabled
    }
    else {
        OnBoardDevExtInfo.OnBoardDev[2] = 0x80;        // Enabled
    }

    PciAddress = PCI_CFG_ADDRESS (0, 0x1C, 2, 0x19);
    gPciRootBridgeIo->Pci.Read (
                                gPciRootBridgeIo,
                                EfiPciWidthUint8,
                                PciAddress,
                                1,
                                &Value8);

    OnBoardDevExtInfo.BusNumber[2] = Value8;

    VarSize = sizeof(ONBOARD_DEV_EXT_DYNAMIC_DATA);
    Status = pRS->SetVariable(SmbiosOnBoardExtVar, &gAmiSmbiosDynamicDataGuid,
                        Attributes, VarSize, &OnBoardDevExtInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   End of SAMPLE TEMPLATE CODE for Intel Weybridge CRB      ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif                                          // UPDATE_DEVICE_EXT_TYPE41

    return Status;
}

/**
                     ***** PORTING REQUIRED *****
               (if SMBIOS module is part of the project)

    This function provides system battery information. SMBIOS
    Core uses these information to dynamically update SMBIOS
    Portable Battery Data structure Type 22.

    @param None

    @return EFI_STATUS \n
            Variable named "SmbiosBatteryVar" with Battery information

    @remark Refer to BATTERY_DYNAMIC_DATA in SmbiosDynamicData.h for\n
            structure information.

**/
EFI_STATUS
CreateBatteryDataForSMBios (VOID)
{
    EFI_STATUS              Status = EFI_SUCCESS;

#if UPDATE_BATTERY_TYPE22
    SmbiosBatteryVar = NULL;        // Remove this line when porting this function
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===                    Start of dummy code                     ===
    // ===                                                            ===
    // ===        PORTING IS NEEDED FOR INDIVIDUAL PLATFORM !!!       ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    BATTERY_DYNAMIC_DATA    BatteryInfo;
    UINTN                   VarSize;
    UINT32                  Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT8                   DeviceName1[] = "BATT 1";
    UINT8                   DeviceName2[] = "Another Battery Name";
    UINT8                   SbdsVersion1[] = "01.12.912";
    UINT8                   SbdsVersion2[] = "00.01";

    BatteryInfo.BatteryDynamicData[0].DesignCapacity = 1;
    BatteryInfo.BatteryDynamicData[0].DesignVoltage = 5000;
    BatteryInfo.BatteryDynamicData[0].SbdsSerialNumber = 0x1111;
    BatteryInfo.BatteryDynamicData[0].SbdsManufacturedDate = 0x2841;
    BatteryInfo.BatteryDynamicData[0].DesignCapacityMult = 1000;
    // When copying strings, MAKE SURE THE ZERO TERMINATOR
    // for the string is included
    MemCpy (BatteryInfo.BatteryDynamicData[0].DeviceName, DeviceName1, sizeof(DeviceName1));
    MemCpy (BatteryInfo.BatteryDynamicData[0].SbdsVersion, SbdsVersion1, sizeof(SbdsVersion1));
    BatteryInfo.BatteryDynamicData[0].Valid = TRUE;

    BatteryInfo.BatteryDynamicData[1].DesignCapacity = 1;
    BatteryInfo.BatteryDynamicData[1].DesignVoltage = 9000;
    BatteryInfo.BatteryDynamicData[1].SbdsSerialNumber = 0x4444;
    BatteryInfo.BatteryDynamicData[1].SbdsManufacturedDate = 0x1814;
    BatteryInfo.BatteryDynamicData[1].DesignCapacityMult = 500;
    // When copying strings, MAKE SURE THE ZERO TERMINATOR
    // for the string is included
    MemCpy (BatteryInfo.BatteryDynamicData[1].DeviceName, DeviceName2, sizeof(DeviceName2));
    MemCpy (BatteryInfo.BatteryDynamicData[1].SbdsVersion, SbdsVersion2, sizeof(SbdsVersion2));
    BatteryInfo.BatteryDynamicData[1].Valid = FALSE;

    BatteryInfo.BatteryDynamicData[2].DesignCapacity = 1;
    BatteryInfo.BatteryDynamicData[2].DesignVoltage = 3000;
    BatteryInfo.BatteryDynamicData[2].SbdsSerialNumber = 0x7777;
    BatteryInfo.BatteryDynamicData[2].SbdsManufacturedDate = 0x0814;
    BatteryInfo.BatteryDynamicData[2].DesignCapacityMult = 200;
    // When copying strings, MAKE SURE THE ZERO TERMINATOR
    // for the string is included
    MemCpy (BatteryInfo.BatteryDynamicData[2].DeviceName, DeviceName2, sizeof(DeviceName2));
    MemCpy (BatteryInfo.BatteryDynamicData[2].SbdsVersion, SbdsVersion2, sizeof(SbdsVersion2));
    BatteryInfo.BatteryDynamicData[2].Valid = FALSE;

    BatteryInfo.BatteryDynamicData[3].DesignCapacity = 1;
    BatteryInfo.BatteryDynamicData[3].DesignVoltage = 1000;
    BatteryInfo.BatteryDynamicData[3].SbdsSerialNumber = 0x9999;
    BatteryInfo.BatteryDynamicData[3].SbdsManufacturedDate = 0x5814;
    BatteryInfo.BatteryDynamicData[3].DesignCapacityMult = 700;
    // When copying strings, MAKE SURE THE ZERO TERMINATOR
    // for the string is included
    MemCpy (BatteryInfo.BatteryDynamicData[3].DeviceName, DeviceName2, sizeof(DeviceName2));
    MemCpy (BatteryInfo.BatteryDynamicData[3].SbdsVersion, SbdsVersion2, sizeof(SbdsVersion2));
    BatteryInfo.BatteryDynamicData[3].Valid = TRUE;

    VarSize = sizeof(BATTERY_DYNAMIC_DATA);
    Status = pRS->SetVariable(SmbiosBatteryVar,
                        &gAmiSmbiosDynamicDataGuid,
                        Attributes,
                        VarSize,
                        &BatteryInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===                     End of dummy code                      ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif                                          // UPDATE_BATTERY_TYPE22

    return Status;
}

/**
    SMBIOS Board driver entry point

    @param ImageHandle
    @param SystemTable

    @return EFI_STATUS

**/
EFI_STATUS
SMIBiosBoardDriverEntryPoint(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS              Status;

    InitAmiLib(ImageHandle, SystemTable);

    SmbiosMemVar = NULL;    // SmbiosMemVar is not used in this file
                            // Set to NULL to correct build error using GCC

    Status = pBS->InstallProtocolInterface(&ImageHandle,
                                          &gAmiSmbiosBoardProtocolGuid,
                                          EFI_NATIVE_INTERFACE,
                                          &SmbiosBoardProtocol);
    return Status;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**           (C)Copyright 1985-2015, American Megatrends, Inc.            **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                        **
//**                          Phone: (770)-246-8600                         **
//**                                                                        **
//****************************************************************************
//****************************************************************************
