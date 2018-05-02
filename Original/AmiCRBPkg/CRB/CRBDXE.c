//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
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
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        CRBDXE.c
//
// Description: This file contains code for Chipset Reference Board Template
//              initialization in the DXE stage
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Dxe.h>
#include <PCI.h>
#include <AmiHobs.h>
#include <AmiCspLib.h>
#if defined CIRA_SAMPLE_SUPPORT && CIRA_SAMPLE_SUPPORT == 1
#include <ME.h>
#include <AMT.h>
#endif
//AptioV
#include <CrbDxeInitElink.h>
// Produced Protocols

// Consumed Protocols
#include <Protocol\PciIO.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\BootScriptSave.h>

#if CMOS_MANAGER_SUPPORT
#include <Guid/SetupVariable.h>
#include <Include/CmosAccess.h>
#include <PchRegs/PchRegsSata.h>
#include <Library/UefiLib.h>
#endif

#if defined CRB_REPORT_TSEG_TO_E820_TABLE && CRB_REPORT_TSEG_TO_E820_TABLE == 1
#if defined CSM_SUPPORT && CSM_SUPPORT == 1
#include <Library/HobLib.h>
#include <Guid\SmramMemoryReserve.h>
#include "Platform.h"
#endif // CSM_SUPPORT
#endif
//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)


#if defined CRB_REPORT_TSEG_TO_E820_TABLE && CRB_REPORT_TSEG_TO_E820_TABLE == 1
#if defined CSM_SUPPORT && CSM_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CrbReportTsegToE820Table
//
// Description: Report TSEG to E820 table. Including SMRAM and IED memory.
//
// Input:       None
//
// Output:      EFI_SUCCESS - Report success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CrbReportTsegToE820Table ( VOID )
{
  EFI_STATUS                       Status;
  VOID                             *GuidHob;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK   *DescriptorBlock;
  EFI_PHYSICAL_ADDRESS             TsegSize;
  EFI_PHYSICAL_ADDRESS             TsegBase;
  EFI_PHYSICAL_ADDRESS             MemIedSize;
  DXE_SERVICES                     *DxeSvcTbl = NULL;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR  GcdMemorySpaceDescriptor;
  UINT64                           Attributes;
  UINTN                            TsegIndex;
  SYSTEM_CONFIGURATION             SystemConfiguration;
  UINTN                            VarSize;

  //
  // Get Hob list for SMRAM desc
  //
  GuidHob = GetFirstGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid);
  ASSERT (GuidHob);
  DescriptorBlock = GET_GUID_HOB_DATA (GuidHob);
  ASSERT (DescriptorBlock);
    
  //
  // Use the hob to get SMRAM capabilities
  //  
  TsegIndex = DescriptorBlock->NumberOfSmmReservedRegions - 1;
  ASSERT (TsegIndex <= (MAX_SMRAM_RANGES - 1));  
  TsegBase = (EFI_PHYSICAL_ADDRESS)(DescriptorBlock->Descriptor[TsegIndex].PhysicalStart);
  TsegSize = (EFI_PHYSICAL_ADDRESS)(DescriptorBlock->Descriptor[TsegIndex].PhysicalSize);

  VarSize = sizeof (SystemConfiguration);
  Status = pRS->GetVariable (
      L"IntelSetup",
      &gEfiSetupVariableGuid,
      NULL,
      &VarSize,
      &SystemConfiguration
      );
  ASSERT_EFI_ERROR(Status);
  	  
  switch (SystemConfiguration.IedSize) {
    case 1:
          MemIedSize = (4 * 1024 * 1024);
          break;
    case 0:
    default:
          MemIedSize = 0;
          break;
  }
  TsegSize += MemIedSize;
  
  Status = LibGetDxeSvcTbl(&DxeSvcTbl);
  ASSERT_EFI_ERROR (Status);  
  if (EFI_ERROR (Status)) return Status;

  Status = DxeSvcTbl->GetMemorySpaceDescriptor (TsegBase, &GcdMemorySpaceDescriptor);
  ASSERT_EFI_ERROR (Status);

  Attributes = GcdMemorySpaceDescriptor.Attributes | EFI_MEMORY_RUNTIME;

  Status = DxeSvcTbl->SetMemorySpaceAttributes(TsegBase, TsegSize, Attributes);
  ASSERT_EFI_ERROR(Status);
  
  return Status;
}
#endif // CSM_SUPPORT
#endif
  
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetRSTeBootInfo
//
// Description: Read the user settings for SCU and SATA OROM and update into the
//              CMOS token for use in the Get RSTe OROM Boot Info Int 15 handler.
//
// Input:       None
//
// Output:      None
//
// Return :     VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SetRSTeBootInfo (
  IN  EFI_EVENT Event,
  IN  VOID      *Context )
{
    EFI_STATUS					Status;
    EFI_CMOS_ACCESS_INTERFACE   *pCmosAccess;
    SYSTEM_CONFIGURATION        SystemConfiguration;
    EFI_GUID 					SetupGuid = SETUP_GUID;
    UINTN 						VariableSize = 0;
    UINT8 						RSTeBootInfo = 0; 
    UINT8						MaskValue = CMOSMGR_RSTE_BOOT_INFO_OFFSET_MASK;
    UINT8						BitPos = 0;

    Status = pBS->LocateProtocol( &gAmiCmosAccessDxeProtocolGuid, NULL, &pCmosAccess ); 
    if ( EFI_ERROR ( Status ) ){
      return;
    }

    VariableSize = sizeof( SYSTEM_CONFIGURATION );
    Status = pRS->GetVariable(
    		L"IntelSetup",
    		&gEfiSetupVariableGuid,
    		NULL,
    		&VariableSize,
    		&SystemConfiguration 
    		);
    if ( EFI_ERROR ( Status ) ) {
    	SystemConfiguration.SataLegacyBootContSel = 1; //default value
    	SystemConfiguration.sSataLegacyBootContSel = 1; //default value
    }

    pCmosAccess->Read( pCmosAccess, CMOSMGR_RSTE_BOOT_INFO_OFFSET, &RSTeBootInfo );
    RSTeBootInfo &= ~CMOSMGR_RSTE_BOOT_INFO_OFFSET_MASK; // Both SATA and sSATA controller is selected as boot controller.    
	
    if (( SystemConfiguration.sSataInterfaceMode == SATA_MODE_RAID && SystemConfiguration.sSataLegacyBootContSel ) &&
    ( SystemConfiguration.SataInterfaceMode == SATA_MODE_RAID && SystemConfiguration.SataLegacyBootContSel )){
    	goto RsteBootInfoExit; // Both SATA nor SCU controller is selected as boot controller.
    }
    
    if ( (!(SystemConfiguration.sSataLegacyBootContSel)) && (!(SystemConfiguration.SataLegacyBootContSel)) ) {
    	RSTeBootInfo |= CMOSMGR_RSTE_BOOT_INFO_OFFSET_MASK; // Neither SATA nor SCU controller is selected as boot controller.
    	goto RsteBootInfoExit;
    }

    // Get the Boot Info bits position from masked data. 
    while ( TRUE ) {
    	if ( MaskValue & BIT00 )
    		break;
    	BitPos++; 
    	MaskValue = MaskValue >> 1;       
    }          

    if ( SystemConfiguration.sSataInterfaceMode == SATA_MODE_RAID && SystemConfiguration.sSataLegacyBootContSel )
    	RSTeBootInfo |= ( BIT00 << BitPos );  // sSATA OROM is enabled.

    if ( SystemConfiguration.SataInterfaceMode == SATA_MODE_RAID && SystemConfiguration.SataLegacyBootContSel )
    	RSTeBootInfo |= ( BIT01 << BitPos ); // SATA OROM is enabled.

RsteBootInfoExit:
    Status = pCmosAccess->Write( pCmosAccess, CMOSMGR_RSTE_BOOT_INFO_OFFSET, RSTeBootInfo );
    if ( EFI_ERROR ( Status ) ){
        TRACE((-1," Get RSTe OROM Boot Info BIOS Services: Unable to write to CMOS variable holding RSTe Boot info. Status %r\n", Status ));
        return;
    }
	
    pBS->CloseEvent(Event);
}

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBDXE_Init
//
// Description: This function is the entry point for this DXE. This function
//              initializes the CRB
//
// Parameters:  ImageHandle Image handle
//              SystemTable Pointer to the system table
//
// Returns:     Return Status based on errors that occurred while waiting for
//              time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CRBDXE_Init (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status = EFI_SUCCESS;
#if CMOS_MANAGER_SUPPORT && CSM_SUPPORT
    SETUP_DATA          SetupData;
    EFI_GUID            SetupGuid = SETUP_GUID;
    UINTN               Size = sizeof(SETUP_DATA);
    VOID                *AmiCmosAccessProtocolRegistration;
#endif

#if defined CIRA_SAMPLE_SUPPORT && CIRA_SAMPLE_SUPPORT == 1
    AMI_AMT_PROTOCOL *mAmtProtocol;
    EFI_GUID mAmtProtocolGuid = AMI_AMT_PROTOCOL_GUID;
    EFI_GUID mSetupGuid = SETUP_GUID;
    UINTN mSetupDataSize = NULL;
    SETUP_DATA mSetupData;
#endif

    InitAmiLib(ImageHandle, SystemTable);

#if defined CIRA_SAMPLE_SUPPORT && CIRA_SAMPLE_SUPPORT == 1
    mSetupDataSize = sizeof(SETUP_DATA);
    Status = pRS->GetVariable (  
                                L"Setup",
                                &mSetupGuid,
                                NULL,
                                &mSetupDataSize,
                                &mSetupData 
                              );

    if (mSetupData.CIRATrigger == 1)
    {
        Status = pBS->LocateProtocol(&mAmtProtocolGuid, NULL, &mAmtProtocol);
        if (!EFI_ERROR(Status))
            mAmtProtocol->SetCIRA(mAmtProtocol, CIRA_ENABLE, CIRA_DEFFAULT_TIME);
    }
#endif

 //
 // RSTe Support Starts
 //
#if CMOS_MANAGER_SUPPORT && CSM_SUPPORT
    Status = pRS->GetVariable(L"Setup", &SetupGuid, NULL, &Size, &SetupData);
    if(EFI_ERROR(Status)) {
    	SetupData.MassStorageOpRom = DEFAULT_MASS_STORAGE_OPROM_POLICY;
    }
    
    if(SetupData.MassStorageOpRom == CSMSETUP_LEGACY_ONLY_OPROMS) {

    	EfiCreateProtocolNotifyEvent (
    			&gAmiCmosAccessDxeProtocolGuid,
    			TPL_CALLBACK,
    			SetRSTeBootInfo,
    			NULL,
    			&AmiCmosAccessProtocolRegistration );
    }
    
#endif

#if defined CRB_REPORT_TSEG_TO_E820_TABLE && CRB_REPORT_TSEG_TO_E820_TABLE == 1
#if defined CSM_SUPPORT && CSM_SUPPORT == 1
    CrbReportTsegToE820Table ();
#endif // CSM_SUPPORT
#endif
	        
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
