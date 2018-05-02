//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**       5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093       **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
//
// $Header: $
//
// $Revision: $
//
// $Date: $
//
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: $
// 
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		RtErrorLogBmc.c
//
// Description:	Runtime error log BMC library function definitions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "RtErrorLogBmc.h"
EFI_SEL_RECORD_DATA           mSelRecord;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UpdateGenericSelInfo
//
// Description: 
// This function will update generic IPMI info fields 
//
// Input:
//
//    SelRecord           - Pointer to SEL Record
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateGenericSelInfo (
  IN OUT  EFI_SEL_RECORD_DATA     *SelRecord
  )
{

  SelRecord->TimeStamp.Year = 0;
  SelRecord->RecordType = SEL_SYSTEM_RECORD;
  SelRecord->GeneratorId = (UINT16)EFI_GENERATOR_ID(SMI_HANDLER_SOFTWARE_ID);
  SelRecord->EvMRevision = EFI_EVM_REVISION;
  SelRecord->EventDirType = EFI_SENSOR_TYPE_EVENT_CODE_DISCRETE;
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UpdateSelInfoForMe
//
// Description: 
// Update the SEL Record information for Memory Errors
//
// Input:
//
//    MemorySensorOffset  - Memory offset to enum EFI_SEL_SENSOR_MEMORY_OFFSET
//    Channel          		- Channel, base 0
//    DimmNumber          - Dimm Number, base 0
//    SelRecord           - Pointer to SEL Record
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateSelInfoForMe (
  IN      EFI_SEL_SENSOR_MEMORY_OFFSET        MemorySensorOffset,
	IN      MEM_ERROR_LOCATION									*MemErrorLoc,
  IN OUT  EFI_SEL_RECORD_DATA                 *SelRecord
  )
{
  // Update Generic SEL related information

  UpdateGenericSelInfo (SelRecord);

  SelRecord->SensorType = EFI_MEMORY_SENSOR_TYPE;
  //DJH002019-- SelRecord->SensorNumber = (UINT8)0x8; // for UCE/CE

  if (MemorySensorOffset == EFI_MEMORY_SENSOR_OFFSET_ECC_UNCORRECTABLE) {
    // UCE error
    SelRecord->OEMEvData1 = 0xA0 | MEMORY_SENSOR_UCE_OFFSET; // Add error Id to identify the error
  } else if (MemorySensorOffset == EFI_MEMORY_SENSOR_OFFSET_ECC_CORRECTABLE){
    // Single bit error
    SelRecord->OEMEvData1 = 0xA0 | MEMORY_SENSOR_CE_OFFSET; // Add error Id to identify the error
  } else if (MemorySensorOffset == EFI_MEMORY_SENSOR_OFFSET_PARITY){
    // Parity error
    SelRecord->OEMEvData1 = 0xA0 | MEMORY_SENSOR_PARITY_ERROR_OFFSET; // Add error Id to identify the error
  } else if (MemorySensorOffset==EFI_MEMORY_SENSOR_OFFSET_ECC_CORRECTABLE_MAX){
	// Single bit error threshold reached
    SelRecord->OEMEvData1 = 0xA0 | MEMORY_SENSOR_CEMAX_OFFSET; // Add error Id to identify the error
  }

  SelRecord->OEMEvData2 = (MemErrorLoc->MemoryController << 1); 
  if (MemErrorLoc->Dimm == 0xff) {
      // No info about the error is available
      SelRecord->OEMEvData3 = (UINT8)((MemErrorLoc->Socket << OEMEvData3_SOCKET_NUM_BITS) |(MemErrorLoc->DdrChannel << OEMEvData3_CHANNEL_NUM_BITS) | DIMM_NUM_BITS);
  } else {
      SelRecord->OEMEvData3 = (UINT8)((MemErrorLoc->Socket << OEMEvData3_SOCKET_NUM_BITS) |(MemErrorLoc->DdrChannel << OEMEvData3_CHANNEL_NUM_BITS) | MemErrorLoc->Dimm);
  }

  //
  //Move OEMData2 Bit1 to OEMData3 Bit5
  //   
  SelRecord->OEMEvData3 |= ((SelRecord->OEMEvData2 & 0x02) << 4);//DJH002019A++
  
   #if OEM_SENSOR_NUMBER_SUPPORT == 1  //JPG002001+
  //DJH002019++>>  
  DEBUG((-1, "OEMEvData3:%0x\n", SelRecord->OEMEvData3));//DJH002019++
  switch (SelRecord->OEMEvData3){
  /*DJH002038++
  case 0x00:SelRecord->SensorNumber = (UINT8)0x50;break; // S0_C0_D0 for UCE/CE
  case 0x01:SelRecord->SensorNumber = (UINT8)0x51;break; // S0_C0_D1
  case 0x10:SelRecord->SensorNumber = (UINT8)0x52;break; // S0_C1_D0
  case 0x11:SelRecord->SensorNumber = (UINT8)0x53;break; // S0_C1_D1
  case 0x20:SelRecord->SensorNumber = (UINT8)0x54;break; // S0_C2_D0
  case 0x21:SelRecord->SensorNumber = (UINT8)0x55;break; // S0_C2_D1
  case 0x30:SelRecord->SensorNumber = (UINT8)0x56;break; // S0_C3_D0
  case 0x31:SelRecord->SensorNumber = (UINT8)0x57;break; // S0_C3_D1
  case 0x40:SelRecord->SensorNumber = (UINT8)0x58;break; // S1_C0_D0
  case 0x41:SelRecord->SensorNumber = (UINT8)0x59;break; // S1_C0_D1
  case 0x50:SelRecord->SensorNumber = (UINT8)0x5A;break; // S1_C1_D0
  case 0x51:SelRecord->SensorNumber = (UINT8)0x5B;break; // S1_C1_D1
  case 0x60:SelRecord->SensorNumber = (UINT8)0x5C;break; // S1_C2_D0
  case 0x61:SelRecord->SensorNumber = (UINT8)0x5D;break; // S1_C2_D1
  case 0x70:SelRecord->SensorNumber = (UINT8)0x5E;break; // S1_C3_D0
  case 0x71:SelRecord->SensorNumber = (UINT8)0x5F;break; // S1_C3_D1
  //DJH002038++>>
  */ 
  case 0x00:SelRecord->SensorNumber = (UINT8)0x50;break; // S0_C0_D0 for UCE/CE
  case 0x01:SelRecord->SensorNumber = (UINT8)0x51;break; // S0_C0_D1
  case 0x10:SelRecord->SensorNumber = (UINT8)0x53;break; // S0_C1_D0
  case 0x11:SelRecord->SensorNumber = (UINT8)0x54;break; // S0_C1_D1
  case 0x20:SelRecord->SensorNumber = (UINT8)0x56;break; // S0_C2_D0
  case 0x21:SelRecord->SensorNumber = (UINT8)0x57;break; // S0_C2_D1
  case 0x30:SelRecord->SensorNumber = (UINT8)0x59;break; // S0_C3_D0
  case 0x31:SelRecord->SensorNumber = (UINT8)0x5A;break; // S0_C3_D1
  case 0x40:SelRecord->SensorNumber = (UINT8)0x5C;break; // S1_C0_D0
  case 0x41:SelRecord->SensorNumber = (UINT8)0x5D;break; // S1_C0_D1
  case 0x50:SelRecord->SensorNumber = (UINT8)0x5F;break; // S1_C1_D0
  case 0x51:SelRecord->SensorNumber = (UINT8)0x60;break; // S1_C1_D1
  case 0x60:SelRecord->SensorNumber = (UINT8)0x62;break; // S1_C2_D0
  case 0x61:SelRecord->SensorNumber = (UINT8)0x63;break; // S1_C2_D1
  case 0x70:SelRecord->SensorNumber = (UINT8)0x65;break; // S1_C3_D0
  case 0x71:SelRecord->SensorNumber = (UINT8)0x66;break; // S1_C3_D1
  //DJH002038++<<
  }
  DEBUG((-1, "SelRecord->SensorNumber:%0x\n", SelRecord->SensorNumber));
  //DJH002019++<<
 //JPG002001+START
#else  
  //DJH002035-- SelRecord->SensorNumber = (UINT8)0x8; // for UCE/CE
  //DJH002035++>>
  switch (SelRecord->OEMEvData3){
  case 0x00:SelRecord->SensorNumber = (UINT8)0x60;break; // S0_C0_D0 for UCE/CE
  case 0x01:SelRecord->SensorNumber = (UINT8)0x61;break; // S0_C0_D1
  case 0x10:SelRecord->SensorNumber = (UINT8)0x62;break; // S0_C1_D0
  case 0x11:SelRecord->SensorNumber = (UINT8)0x63;break; // S0_C1_D1
  case 0x20:SelRecord->SensorNumber = (UINT8)0x64;break; // S0_C2_D0
  case 0x21:SelRecord->SensorNumber = (UINT8)0x65;break; // S0_C2_D1
  case 0x30:SelRecord->SensorNumber = (UINT8)0x66;break; // S0_C3_D0
  case 0x31:SelRecord->SensorNumber = (UINT8)0x67;break; // S0_C3_D1
  case 0x40:SelRecord->SensorNumber = (UINT8)0x68;break; // S1_C0_D0
  case 0x41:SelRecord->SensorNumber = (UINT8)0x69;break; // S1_C0_D1
  case 0x50:SelRecord->SensorNumber = (UINT8)0x6A;break; // S1_C1_D0
  case 0x51:SelRecord->SensorNumber = (UINT8)0x6B;break; // S1_C1_D1
  case 0x60:SelRecord->SensorNumber = (UINT8)0x6C;break; // S1_C2_D0
  case 0x61:SelRecord->SensorNumber = (UINT8)0x6D;break; // S1_C2_D1
  case 0x70:SelRecord->SensorNumber = (UINT8)0x6E;break; // S1_C3_D0
  case 0x71:SelRecord->SensorNumber = (UINT8)0x6F;break; // S1_C3_D1
  }
  //DJH002035++<<
#endif  //OEM_SENSOR_NUMBER_SUPPORT end
//JPG002001+END

  // Changes done for the LASTBOOT ERROR Support
  if (mLastbootMemErrFlag)
     SelRecord->OEMEvData2 |= BIT0; //ED2[0]: 0 - Current Boot. 1 - Last boot
  // Changes done for the LASTBOOT ERROR Support

  return EFI_SUCCESS;
}

//TH0159>>>
#if OEM_SEL_LOG_SUPPORT == 1

//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   OemUpdateSelInfoForMe
//
// Description: Update the SEL Record information for Memory Errors.
//
// Input:       MemorySensorOffset  - Memory offset to enum EFI_SEL_SENSOR_MEMORY_OFFSET
//				Channel				- Channel, base 0
//				DimmNumber          - Dimm Number, base 0
//				SelRecord           - Pointer to SEL Record
//
// Output:      NONE
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_START>
OemUpdateSelInfoForMe (
  IN      EFI_SEL_SENSOR_MEMORY_OFFSET        MemorySensorOffset,
  IN      MEM_ERROR_LOCATION                  *MemErrorLoc,
  IN OUT  EFI_SEL_RECORD_DATA                 *SelRecord
  )
{
  // Update Generic SEL related information
  UpdateGenericSelInfo (SelRecord);

  SelRecord->SensorType = EFI_MEMORY_SENSOR_TYPE;
  SelRecord->SensorNumber = (UINT8)0xE2;

  if (MemorySensorOffset == EFI_MEMORY_SENSOR_OFFSET_ECC_UNCORRECTABLE) {
    // UCE error
    SelRecord->OEMEvData1 = 0xA0 | MEMORY_SENSOR_UCE_OFFSET; // Add error Id to identify the error
    SelRecord->OEMEvData3 = (UINT8)(0x10 << 6);
  } else if (MemorySensorOffset == EFI_MEMORY_SENSOR_OFFSET_ECC_CORRECTABLE){
    // Single bit error
    SelRecord->OEMEvData1 = 0xA0 | MEMORY_SENSOR_CE_OFFSET; // Add error Id to identify the error
    SelRecord->OEMEvData3 = (UINT8)(0x01 << 6);
  } else if (MemorySensorOffset==EFI_MEMORY_SENSOR_OFFSET_ECC_CORRECTABLE_MAX){
	// Single bit error threshold reached
    SelRecord->OEMEvData1 = 0xA0 | MEMORY_SENSOR_CEMAX_OFFSET; // Add error Id to identify the error
    SelRecord->OEMEvData3 = (UINT8)(0x01 << 6);
  }

  if (MemErrorLoc->Dimm == 0xff) {
      // No info about the error is available
      SelRecord->OEMEvData2 = (UINT8)((MemErrorLoc->Socket << 6) |(MemErrorLoc->DdrChannel << 3) | DIMM_NUM_BITS);
  } else {
      SelRecord->OEMEvData2 = (UINT8)((MemErrorLoc->Socket << 6) |(MemErrorLoc->DdrChannel << 3) | MemErrorLoc->Dimm);
  }
  SelRecord->OEMEvData2 |= (UINT8)(MemErrorLoc->MemoryController << 4); //TH0159A

  // Changes done for the LASTBOOT ERROR Support
  if (mLastbootMemErrFlag)
//TH0159A     SelRecord->OEMEvData2 |= BIT0; //ED2[0]: 0 - Current Boot. 1 - Last boot
	  SelRecord->OEMEvData3 |= BIT0; //ED2[0]: 0 - Current Boot. 1 - Last boot	//TH0159A
  // Changes done for the LASTBOOT ERROR Support

  return EFI_SUCCESS;
}

#endif //OEM_SEL_LOG_SUPPORT
//TH0159<<<

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AllocSelRecord
//
// Description: 
//     Allocate memory for SelRecord
//
// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
AllocSelRecord(
  IN OUT EFI_SEL_RECORD_DATA **SelRecord
  )
{
  *SelRecord = &mSelRecord;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LogInfoToSel
//
// Description: 
//
//	This function will log the data into SEL using Generic Log API

// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogInfoToSel (
  IN  EFI_SEL_RECORD_DATA     *SelRecord
  )
{
  EFI_STATUS      				Status;
  EFI_IPMI_TRANSPORT			*IpmiTransport;
  UINT8      		  		    ResponseData[10];
  UINT8        	  				ResponseDataSize;
#if IPMI_COMPLETION_CODE_SUPPORT
  UINT8                         CompletionCode;
#endif
 ResponseDataSize = 10;

 Status = gSmst->SmmLocateProtocol (&gEfiSmmIpmiTransportProtocolGuid, NULL, &IpmiTransport);
  if (Status == EFI_SUCCESS) {
    Status = IpmiTransport-> SendIpmiCommand (IpmiTransport,
						EFI_SM_STORAGE,
						0,
						ADD_SEL_ENTRY,
						(UINT8 *) SelRecord,
						sizeof (EFI_SEL_RECORD_DATA),
						//TH0032 (UINT8 *) &ResponseData,
						(UINT8 *) ResponseData, //TH0032
#if IPMI_COMPLETION_CODE_SUPPORT
						(UINT8 *) &ResponseDataSize,
						(UINT8 *) &CompletionCode
#else
						(UINT8 *) &ResponseDataSize
#endif
						); 
  }

  Status = EFI_SUCCESS;
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LogMeToSel
//
// Description: 
//	Log the memory errors to BMC SEL
//
// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogMeToSel (
	MEMORY_DEV_INFO		*MemInfo
 )
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_SEL_RECORD_DATA             *SelRecord = NULL;
    EFI_SEL_SENSOR_MEMORY_OFFSET    MemorySensorOffset = EFI_MEMORY_SENSOR_OFFSET_ECC_CORRECTABLE_MAX;
    MEM_ERROR_LOCATION              MemErrorLoc;

    // Allocate memory for SelRecord
    AllocSelRecord( &SelRecord );

    // Set location
    MemErrorLoc.Socket = (UINT8)(NODE_TO_SKT(MemInfo->Node));
    MemErrorLoc.MemoryController = (UINT8)(NODE_TO_MC(MemInfo->Node));
    MemErrorLoc.DdrChannel = (UINT8)(MemInfo->Channel);
    MemErrorLoc.Dimm = (UINT8)(MemInfo->Dimm);

    // Set type
    if (MemInfo->Type == COR_ERROR_TYPE) {
        if (MemInfo->ErrorType == PLATFORM_MEM_ERROR_PARITY) {
            MemorySensorOffset = EFI_MEMORY_SENSOR_OFFSET_PARITY;
        }
        else {
            MemorySensorOffset = EFI_MEMORY_SENSOR_OFFSET_ECC_CORRECTABLE_MAX;
        }
    }
    else {
        MemorySensorOffset = EFI_MEMORY_SENSOR_OFFSET_ECC_UNCORRECTABLE;
    }

    // Log sel entry to report
//TH0159>>>
#if OEM_SEL_LOG_SUPPORT == 1
    Status = OemUpdateSelInfoForMe (MemorySensorOffset, &MemErrorLoc, SelRecord);
#else
//TH0159<<<
    Status = UpdateSelInfoForMe (MemorySensorOffset, &MemErrorLoc, SelRecord);
#endif	//TH0159
    Status = LogInfoToSel( SelRecord );
    return	Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LogCoreToSel
//
// Description: 
//	Log the Core errors to BMC SEL
//
// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogCoreToSel (
	CORE_ERROR_RECORD                  *CoreErrorData
 )
{
  EFI_STATUS                      Status = EFI_SUCCESS;
  EFI_SEL_RECORD_DATA             SelRecord;

     // Initialize generic parts of SEL record.
    Status = UpdateGenericSelInfo( &SelRecord );
    // Initialize specific parts of SEL record.
    SelRecord.SensorType = EFI_PROCESSOR_SENSOR_TYPE ; 
    //TH0171  SelRecord.SensorNumber = (UINT8)0x0; 
    //DJH002020-- SelRecord.SensorNumber = (UINT8)BIOS_CORE_VTD_SENSOR_NUM; //TH0171

    SelRecord.OEMEvData1 = 0xA0 | EFI_PROCESSOR_SENSOR_OFFSET_CONFIGURATION_ERROR; // Add error Id to identify the error
    SelRecord.OEMEvData2 = (CoreErrorData->ErrorType << 4) | (CoreErrorData->ErrorSeverity); 
    SelRecord.OEMEvData3 = (CoreErrorData->Socket << 4) | (CoreErrorData->CoreMcaBank); 

    #if OEM_SENSOR_NUMBER_SUPPORT == 1 //DJH002023++
    //DJH002020++>>
	DEBUG((-1, "SelRecord.OEMEvData3:%0x\n", SelRecord.OEMEvData2));
	DEBUG((-1, "CoreErrorData->Socket:%0x\n", CoreErrorData->Socket));
	switch (CoreErrorData->Socket) {
	  case 0x00:SelRecord.SensorNumber = (UINT8)0x47;break; // S0
	  case 0x01:SelRecord.SensorNumber = (UINT8)0x48;break; // S1
	  }
	DEBUG((-1, "SelRecord.SensorNumber:%0x\n", SelRecord.SensorNumber));
	//DJH002020++<<
	//DJH002023++>>
	#else
	SelRecord.SensorNumber = (UINT8)BIOS_CORE_VTD_SENSOR_NUM;
	#endif
	//DJH002023++<<
	

    // Report the error.
    Status = LogInfoToSel( &SelRecord ); 
    
    return	Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LogQpiToSel
//
// Description: 
//	Log the Qpi errors to BMC SEL
//
// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogQpiToSel (
	QPI_ERROR_RECORD                  *QpiErrorData
 )
{
  EFI_STATUS                      Status = EFI_SUCCESS;
  EFI_SEL_RECORD_DATA             SelRecord;

     // Initialize generic parts of SEL record.
    Status = UpdateGenericSelInfo( &SelRecord );
    // Initialize specific parts of SEL record.
    SelRecord.SensorType = EFI_PROCESSOR_SENSOR_TYPE ; 
//TH0171    SelRecord.SensorNumber = (UINT8)0x0; 

    //DJH002020-- SelRecord.SensorNumber = (UINT8)BIOS_QPI_SENSOR_NUM; //TH0171
    SelRecord.OEMEvData1 = 0xA0 | EFI_PROCESSOR_SENSOR_OFFSET_CONFIGURATION_ERROR; // Add error Id to identify the error
//TH0171    SelRecord.OEMEvData2 = (QpiErrorData->ErrorType << 4) | (QpiErrorData->ErrorSeverity); 
      SelRecord.OEMEvData2 = (QpiErrorData->Socket << 4) | (QpiErrorData->QpiPort); //TH0171
//TH0171    SelRecord.OEMEvData3 = (QpiErrorData->Socket << 4) | (QpiErrorData->QpiPort); 
      SelRecord.OEMEvData3 = (QpiErrorData->ErrorType << 4) | (QpiErrorData->ErrorSeverity); //TH0171
      
      #if OEM_SENSOR_NUMBER_SUPPORT == 1 //DJH002023++
      //DJH002020++>>
      DEBUG((-1, "SelRecord.OEMEvData2:%0x\n", SelRecord.OEMEvData2));
	  DEBUG((-1, "QpiErrorData->Socket:%0x\n", QpiErrorData->Socket));
      switch (QpiErrorData->Socket) {
	  	case 0x00:SelRecord.SensorNumber = (UINT8)0x47;break; // S0
	  	case 0x01:SelRecord.SensorNumber = (UINT8)0x48;break; // S1
	  	}
	  DEBUG((-1, "SelRecord.SensorNumber:%0x\n", SelRecord.SensorNumber));
      //DJH002020++<<
	  //DJH002023++>>
	  #else
	  SelRecord.SensorNumber = (UINT8)BIOS_QPI_SENSOR_NUM;
	  #endif
	  //DJH002023++<<

    // Report the error.
    Status = LogInfoToSel( &SelRecord ); 
    
    return	Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LogCboToSel
//
// Description: 
//	Log the Cbo errors to BMC SEL
//
// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogCboToSel (
	CBO_ERROR_RECORD                  *CboErrorData
 )
{
  EFI_STATUS                      Status = EFI_SUCCESS;
  EFI_SEL_RECORD_DATA             SelRecord;

     // Initialize generic parts of SEL record.
    Status = UpdateGenericSelInfo( &SelRecord );
    // Initialize specific parts of SEL record.
    SelRecord.SensorType = EFI_PROCESSOR_SENSOR_TYPE ; 
//TH0171    SelRecord.SensorNumber = (UINT8)0x0; 

    SelRecord.SensorNumber = (UINT8)BIOS_CBO_SENSOR_NUM; //TH0171
    SelRecord.OEMEvData1 = 0xA0 | EFI_PROCESSOR_SENSOR_OFFSET_CONFIGURATION_ERROR; // Add error Id to identify the error
    SelRecord.OEMEvData2 = (CboErrorData->ErrorType << 4) | (CboErrorData->ErrorSeverity); 
    SelRecord.OEMEvData3 = (CboErrorData->CoreId << 3) | (CboErrorData->ThreadId << 2) | (CboErrorData->CboMcaBank); 

    // Report the error.
    Status = LogInfoToSel( &SelRecord ); 
    
    return	Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   LogPciErrorToBmc
//
// Description:
//  Takes in an error type and the address of a PCI device. Correctly fills
//  in a SEL record and logs to the SEL.
//
// Input:
//  IN  UINT8     ErrorType - Type of PCI error (SERR, PERR, etc.)
//  IN  UINT8     Bus
//  IN  UINT8     Dev
//  IN  UINT8     Func
//
// Output: 
//  EFI_STATUS
//      EFI_SUCCESS - Error successfully logged.
//      Others - A problem occurred while trying to log error.
//
// Modified:
//  Nothing
//
// Referrals:
//  UpdateGenericSelInfo()
//  LogInfoToSel()
//
// Notes:
//  None
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogPciErrorToBmc (
    IN UINT8    ErrorSource,
    IN UINT8    ErrType,
    IN UINT8    Segment,
    IN UINT8    Bus,
    IN UINT8    Dev,
    IN UINT8    Func,
    IN BOOLEAN  IsBridge,
    IN UINT16   SecondaryStatus,
    IN UINT8    PcieCapOffset,
    IN UINT16   PcieDeviceStatus,
    IN UINT16   AerOffset,
    IN UINT32   UncorrErrStatus,
    IN UINT32   CorrErrStatus,
    IN UINT32   RootErrStatus
)
{
    EFI_SEL_RECORD_DATA SelRecord;
    EFI_STATUS          Status;

    // Initialize generic parts of SEL record.
    Status = UpdateGenericSelInfo( &SelRecord );

    // Initialize specific parts of SEL record.
    SelRecord.SensorType = SEL_SENS_TYPE_CRIT_ERR;
    //TH0171  SelRecord.SensorNumber = 0x00;
    SelRecord.SensorNumber = BIOS_PCI_SENSOR_NUM; //TH0171
    if (ErrType == PERROR_TYPE) {
        SelRecord.OEMEvData1 = 0xA0 | CRITICAL_INTERRUPT_PCI_PERR;    // OEM Data for byte 2, 3.
    }
    else if (ErrType == SERROR_TYPE) {
        SelRecord.OEMEvData1 = 0xA0 | CRITICAL_INTERRUPT_PCI_SERR;    // OEM Data for byte 2, 3.
    }
    else if (ErrType == COR_ERROR_TYPE) {
        SelRecord.OEMEvData1 = 0xA0 | CRITICAL_INTERRUPT_BUS_CORERR;    // OEM Data for byte 2, 3.
    }
    else if (ErrType == NONFATAL_ERROR_TYPE) {
        SelRecord.OEMEvData1 = 0xA0 | CRITICAL_INTERRUPT_BUS_UNCERR;    // OEM Data for byte 2, 3.
    }
    else if (ErrType == FATAL_ERROR_TYPE) {
        SelRecord.OEMEvData1 = 0xA0 | CRITICAL_INTERRUPT_BUS_FATERR;    // OEM Data for byte 2, 3.
    }
    else if (ErrType == LASTBOOT_PCIE_ERROR) {
        SelRecord.OEMEvData1 = 0xA0 | LASTBOOT_PCIE_ERROR;    // OEM Data for byte 2, 3.
    }
    SelRecord.OEMEvData2 = Bus;                 // Fill with Bus.
    SelRecord.OEMEvData3 = (Dev << 3) | Func;   // Fill with Dev and Func.

    // Report the error.
    Status = LogInfoToSel( &SelRecord ); 

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LogIohQpiToSel
//
// Description: 
//	Log the Ioh Qpi errors to BMC SEL
//
// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogIohQpiToSel (
    IN UINT8    Socket,
    IN UINT8    Port,
    IN UINT16   ErrorType,
    IN UINT8    ErrorSubType,
    IN ERROR_SEVERITY ErrorSeverity
 )
{
  EFI_STATUS                      Status = EFI_SUCCESS;
  EFI_SEL_RECORD_DATA             SelRecord;

     // Initialize generic parts of SEL record.
    Status = UpdateGenericSelInfo( &SelRecord );
    // Initialize specific parts of SEL record.
    SelRecord.SensorType = EFI_PROCESSOR_SENSOR_TYPE ; 
//TH0171    SelRecord.SensorNumber = (UINT8)0x0; 

    SelRecord.SensorNumber = (UINT8)BIOS_QPI_SENSOR_NUM; //TH0171
    SelRecord.OEMEvData1 = 0xA0 | EFI_PROCESSOR_SENSOR_OFFSET_CONFIGURATION_ERROR; // Add error Id to identify the error
    SelRecord.OEMEvData2 = (Socket << 4) | (Port); 
    SelRecord.OEMEvData3 = ErrorSubType ;

    // Report the error.
    Status = LogInfoToSel( &SelRecord ); 
    
    return	Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LogIohCoreToSel
//
// Description: 
//	Log the Ioh Core errors to BMC SEL
//
// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogIohCoreToSel (
    IN UINT8    Socket,
    IN UINT16   ErrorType,
    IN UINT8    ErrorSubType,
    IN ERROR_SEVERITY ErrorSeverity
 )
{
  EFI_STATUS                      Status = EFI_SUCCESS;
  EFI_SEL_RECORD_DATA             SelRecord;

     // Initialize generic parts of SEL record.
    Status = UpdateGenericSelInfo( &SelRecord );
    // Initialize specific parts of SEL record.
    SelRecord.SensorType = EFI_PROCESSOR_SENSOR_TYPE ; 
//TH0171    SelRecord.SensorNumber = (UINT8)0x0; 

    //DJH002020-- SelRecord.SensorNumber = (UINT8)BIOS_CORE_VTD_SENSOR_NUM; //TH0171
    SelRecord.OEMEvData1 = 0xA0 | EFI_PROCESSOR_SENSOR_OFFSET_CONFIGURATION_ERROR; // Add error Id to identify the error
    SelRecord.OEMEvData2 = Socket ; 
    SelRecord.OEMEvData3 = ErrorSubType ;
    
    #if OEM_SENSOR_NUMBER_SUPPORT == 1 //DJH002023++
    //DJH002020++>>
	DEBUG((-1, "SelRecord.OEMEvData2:%0x\n", SelRecord.OEMEvData2));
	switch (SelRecord.OEMEvData2) {
	  case 0x00:SelRecord.SensorNumber = (UINT8)0x47;break; // S0
	  case 0x01:SelRecord.SensorNumber = (UINT8)0x48;break; // S1
	  }
	DEBUG((-1, "SelRecord.SensorNumber:%0x\n", SelRecord.SensorNumber));
	//DJH002020++<<
	//DJH002023++>>
	#else
	SelRecord.SensorNumber = (UINT8)BIOS_CORE_VTD_SENSOR_NUM;
	#endif
	//DJH002023++<<

    // Report the error.
    Status = LogInfoToSel( &SelRecord ); 
    
    return	Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LogIohVtdToSel
//
// Description: 
//	Log the Ioh Vtd errors to BMC SEL
//
// Input:
//
// Output:
//
// Returns:     
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LogIohVtdToSel (
    IN UINT8    Socket,
    IN UINT16   ErrorType,
    IN UINT8    ErrorSubType,
    IN ERROR_SEVERITY ErrorSeverity
 )
{
  EFI_STATUS                      Status = EFI_SUCCESS;
  EFI_SEL_RECORD_DATA             SelRecord;

     // Initialize generic parts of SEL record.
    Status = UpdateGenericSelInfo( &SelRecord );
    // Initialize specific parts of SEL record.
    SelRecord.SensorType = EFI_PROCESSOR_SENSOR_TYPE ; 
//TH0171    SelRecord.SensorNumber = (UINT8)0x0; 

    //DJH002020-- SelRecord.SensorNumber = (UINT8)BIOS_CORE_VTD_SENSOR_NUM; //TH0171
    SelRecord.OEMEvData1 = 0xA0 | EFI_PROCESSOR_SENSOR_OFFSET_CONFIGURATION_ERROR; // Add error Id to identify the error
    SelRecord.OEMEvData2 = Socket; 
    SelRecord.OEMEvData3 = ErrorSubType ;
    
    #if OEM_SENSOR_NUMBER_SUPPORT == 1 //DJH002023++
    //DJH002020++>>
	DEBUG((-1, "SelRecord.OEMEvData2:%0x\n", SelRecord.OEMEvData2));
	switch (SelRecord.OEMEvData2) {
	  case 0x00:SelRecord.SensorNumber = (UINT8)0x47;break; // S0
	  case 0x01:SelRecord.SensorNumber = (UINT8)0x48;break; // S1
	  }
	DEBUG((-1, "SelRecord.SensorNumber:%0x\n", SelRecord.SensorNumber));
	//DJH002020++<<
	//DJH002023++>>
	#else
	SelRecord.SensorNumber = (UINT8)BIOS_CORE_VTD_SENSOR_NUM;
	#endif
	//DJH002023++<<

    // Report the error.
    Status = LogInfoToSel( &SelRecord ); 
    
    return	Status;
}

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**       5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093       **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
