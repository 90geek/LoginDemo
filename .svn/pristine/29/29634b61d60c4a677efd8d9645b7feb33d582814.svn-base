//**********************************************************************
//<OEM_FHDR_START>
//
// Name:    OemFunctions.c
//
// Description:
//  Execute OEM function in specific phase of POST.
//
//<OEM_FHDR_END>
//**********************************************************************

#include "OemFunctions.h"
#include <MdePkg\Include\Library\DebugLib.h>
#include <AmiCompatibilityPkg\Include\AmiDxeLib.h>
#include <GrantleyPkg\Include\Guid\SetupVariable.h>
#include <AmiCompatibilityPkg\Include\Setup.h>
#include <MdePkg\Include\Library\UefiLib.h>
#include <MdePkg\Include\Library\MemoryAllocationLib.h>
#include <MdePkg\Include\Library\IoLib.h>
#include <AmiCompatibilityPkg\Include\AmiLib.h>
#include <AmiIpmiPkg\Include\Protocol\IPMITransportProtocol.h>
#include <AmiIpmiPkg\Include\Include\IpmiNetFnStorageDefinitions.h>

extern	EFI_BOOT_SERVICES			*gBS;
extern	EFI_RUNTIME_SERVICES		*gRT;

extern	EFI_GUID					gAmiTseNVRAMUpdateGuid;

UINT8 ReadCmos( UINT8 Index );

VOID WriteCmos( UINT8 Index, UINT8 Data );

VOID
EnteringToSetup(
	IN EFI_EVENT        Event,
	IN VOID             *Context
);

//VOID
//SaveAndExitSetup(
//	IN EFI_EVENT        Event,
//	IN VOID             *Context
//);

VOID
ReadyToBoot(
	IN EFI_EVENT        Event,
	IN VOID             *Context 
);

//DJH002026-- #if OEM_SEL_LOG_SUPPORT == 1
#if (OEM_SEL_LOG_SUPPORT == 1 || OEM_SENSOR_NUMBER_SUPPORT == 1 ) //DJH002026++
VOID AddPowerUpSEL ( IN EFI_IPMI_TRANSPORT* IpmiTransport );
#endif //OEM_SEL_LOG_SUPPORT

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EnteringToSetup
//
// Description: Execute Oem functions before entering to Setup.
//
// Input:       EFI_EVENT	Event
//				VOID		*Context
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
VOID
EnteringToSetup(
	IN EFI_EVENT        Event,
	IN VOID             *Context
)
{
	EFI_STATUS						Status;
	EFI_IPMI_TRANSPORT      	    *IpmiTransport = NULL;
	
    DEBUG ((DEBUG_INFO, "Execute Oem functions before entering to Setup.\n"));
    
    Status = gBS->LocateProtocol (
                &gEfiDxeIpmiTransportProtocolGuid,
                NULL,
                (VOID **)&IpmiTransport
                );
    
    if( !EFI_ERROR(Status) ) {
//DJH002026-- #if OEM_SEL_LOG_SUPPORT == 1
#if (OEM_SEL_LOG_SUPPORT == 1 || OEM_SENSOR_NUMBER_SUPPORT == 1 ) //DJH002026++
        AddPowerUpSEL( IpmiTransport );
#endif //OEM_SEL_LOG_SUPPORT
    }
}

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SaveAndExitSetup
//
// Description: Execute Oem functions after save and exit setup menu.
//
// Input:       EFI_EVENT	Event
//				VOID		*Context
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
//VOID
//SaveAndExitSetup(
//	IN EFI_EVENT        Event,
//	IN VOID             *Context
//)
//{
//    DEBUG ((DEBUG_INFO, "Execute Oem functions after save and exit setup menu.\n"));
//}

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadyToBoot
//
// Description: Execute Oem functions before boot.
//
// Input:       EFI_EVENT	Event
//				VOID		*Context
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
VOID
ReadyToBoot(
	IN EFI_EVENT        Event,
	IN VOID             *Context 
)
{
	EFI_STATUS						Status;
    EFI_IPMI_TRANSPORT      	    *IpmiTransport = NULL;
    
    DEBUG ((DEBUG_INFO, "Execute Oem functions before boot.\n"));
    
    Status = gBS->LocateProtocol (
                &gEfiDxeIpmiTransportProtocolGuid,
                NULL,
                (VOID **)&IpmiTransport
                );
    
    if( !EFI_ERROR(Status) ) {
//DJH002026-- #if OEM_SEL_LOG_SUPPORT == 1
#if (OEM_SEL_LOG_SUPPORT == 1 || OEM_SENSOR_NUMBER_SUPPORT == 1 ) //DJH002026++
        AddPowerUpSEL( IpmiTransport );
#endif //OEM_SEL_LOG_SUPPORT
    }
}

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RegisterOemFunctions
//
// Description: Register Event for guids to execute OEM function.
//
// Input:       EFI_HANDLE           ImageHandle,
//				EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
EFI_STATUS
EFIAPI
RegisterOemFunctions(
		  IN EFI_HANDLE           ImageHandle,
		  IN EFI_SYSTEM_TABLE     *SystemTable )
{
	EFI_STATUS						Status;
	EFI_EVENT						Event = NULL;
	EFI_GUID                        guidSetupEnter = AMITSE_SETUP_ENTER_GUID;
	
	// Register Event for Setup enter guid to execute Oem functions before entering to setup.
	EfiNamedEventListen (
		&guidSetupEnter,
		TPL_CALLBACK,
		EnteringToSetup,
		NULL,
		NULL);

	// Register Event for Nvram update guid to execute Oem functions after Save & Exit Setup menu.
//	EfiNamedEventListen (
//		&gAmiTseNVRAMUpdateGuid,
//		TPL_CALLBACK,
//		SaveAndExitSetup,
//		NULL,
//		NULL );

	// Register Event for ready to boot guid to execute Oem functions before boot.
    Status = SystemTable->BootServices->CreateEventEx (
                    EFI_EVENT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    ReadyToBoot,
                    NULL,
                    &gEfiEventReadyToBootGuid,
                    &Event
                    );
    ASSERT_EFI_ERROR (Status);

	return EFI_SUCCESS;
}

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadCmos
//
// Description: Read CMOS via IoRead8().
//
// Input:       UINT8	Index
//
// Output:      UINT8	Data
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
UINT8
ReadCmos(UINT8 Index)
{
	UINT8					NMI_EN;
	UINT8					CmosValue;
	
	NMI_EN = IoRead8(0x70) & 0x80;	//Bit 7 is the NMI bit -- it should be protected.
	IoWrite8(0x70, Index | NMI_EN);
	CmosValue = IoRead8(0x71);
	
	return CmosValue;
}

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteCmos
//
// Description: Write CMOS via IoWrite8().
//
// Input:       UINT8	Index,
//				UINT8	Data
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
VOID
WriteCmos(UINT8 Index, UINT8 Data)
{
	UINT8					NMI_EN;
	
	NMI_EN = IoRead8(0x70) & 0x80;  //Bit 7 is the NMI bit -- it should be protected.
	IoWrite8(0x70, Index | NMI_EN);
	IoWrite8(0x71, Data);
}

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AddPowerUpSEL
//
// Description: Add System Event Log of "PowerUp".
//
// Input:       EFI_IPMI_TRANSPORT*	IpmiTransport
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
//DJH002026-- #if OEM_SEL_LOG_SUPPORT == 1
#if (OEM_SEL_LOG_SUPPORT == 1 || OEM_SENSOR_NUMBER_SUPPORT == 1 ) //DJH002026++
VOID
AddPowerUpSEL( IN EFI_IPMI_TRANSPORT* IpmiTransport )
{
    EFI_STATUS					Status;
	UINT8	 					ResetCount;
    UINT16                      RecordId = 0;
	UINT8                       ResponseDataSize;
	
	EFI_SEL_RECORD_DATA SelRecordData = {
        0000,      // Record Id
        EFI_SEL_SYSTEM_RECORD,      // Record Type
        00000000,  // Time stamp
        (UINT16) EFI_GENERATOR_ID (BIOS_SOFTWARE_ID),    // GenID:BIOS
        EFI_EVM_REVISION,      // EFI_EVM_REVISION
        0x1D,      // Sensor Type
    //DJH002027++>>
	#if OEM_SENSOR_NUMBER_SUPPORT == 1
		0x9D,      // Sensor No
	#else
	//DJH002027++<<
        0xE0,      // Sensor No --DJH002027++
    #endif //DJH002027++
        EFI_SENSOR_TYPE_EVENT_CODE_DISCRETE,      // Event Dir
        00,        // Sensor specific Offset for Timestamp Clock Synch Event.
        00,        // ED2
        00         // ED3
	};
	
    ResetCount = ReadCmos(RESET_COUNTER_CMOS_INDEX);
      
    if ( ResetCount <= 1 ) {
    	DEBUG ((DEBUG_INFO, "Add power up SEL record.\n"));
    	
    	ResponseDataSize = sizeof (RecordId);
        Status = IpmiTransport->SendIpmiCommand (
                    IpmiTransport,
                    EFI_SM_NETFN_STORAGE,
                    BMC_LUN,
                    EFI_STORAGE_ADD_SEL_ENTRY,
                    (UINT8 *) &SelRecordData,
                    sizeof (EFI_SEL_RECORD_DATA),
                    (UINT8 *) &RecordId,
                    &ResponseDataSize );
        
        if(!EFI_ERROR(Status)) {
			ResetCount++;
			WriteCmos(RESET_COUNTER_CMOS_INDEX, ResetCount);
        }
    }
}
#endif //OEM_SEL_LOG_SUPPORT
