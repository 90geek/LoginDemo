/*++
  This file contains an 'Intel Pre-EFI Module' and is licensed  
  for Intel CPUs and Chipsets under the terms of your license   
  agreement with Intel or your vendor.  This file may be        
  modified by the user, subject to additional terms of the      
  license agreement                                             
--*/
/*++

Copyright (c) 2005-2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  UncoreInitPeim.c

--*/
#include "Uefi.h"
#include <Library/MemoryQpiInitLib.h>
#include <Library/OemMemoryQpiInit.h>

//TH0113>>>
#if INFORM_BMC_CATCH_QPI_MRC_DEBUG_MESSAGE //TH0113B
#include <Setup.h>
#include <Library/IoLib.h>
#include <Library/SerialPortLib/Ns16550.h>
#include <Ppi/IPMITransportPpi.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Guid/SetupVariable.h>
#endif //TH0113B
//TH0113<<<

EFI_STATUS
EFIAPI
PeimMemoryQpiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
/*++

Routine Description:

  Driver entry point                

Arguments:

  FfsHeader -  Not used.
  PeiServices - General purpose services available to every PEIM.

Returns:

  EFI_SUCCESS:  Memory initialization completed successfully.
  All other error conditions encountered result in an ASSERT.

--*/
{
  SYSHOST host;
  
  //TH0113>>>
#if INFORM_BMC_CATCH_QPI_MRC_DEBUG_MESSAGE //TH0113B
  //1.Prepare to print debug message. 
  
	EFI_STATUS              			Status;
	EFI_STATUS							BmcStatus = EFI_UNSUPPORTED;
	PEI_IPMI_TRANSPORT_PPI  			*IpmiTransportPpi = NULL;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*PeiVariable = NULL;
	SYSTEM_CONFIGURATION    			SystemConfiguration;
	UINTN								VariableSize = sizeof(SYSTEM_CONFIGURATION);
	SETUP_DATA 							SetupData;
	UINTN 								SetupDataVarSize = sizeof(SETUP_DATA);
	UINT8                   			RequestData[3] = {0};
	UINT8               				ResponseDataSize = 0;

	UINTN 								Divisor;
	UINT8 								OutputData;
	UINT8 								Data;
	UINT16 								mComBase 	= AST2400_SERIAL_PORT1_BASE_ADDRESS;
	UINTN  								mBps 		= UART_DEFAULT_BAUD_RATE;
	UINT8  								mData 		= 8;
	UINT8  								mStop 		= 1;
	UINT8  								mParity		= 0;
	UINT8	  							mBreakSet 	= 0;
	  
	Status = (*PeiServices)->LocatePpi( 
			(CONST EFI_PEI_SERVICES**)PeiServices,
			&gEfiPeiReadOnlyVariable2PpiGuid,
			0,
			NULL,
			&PeiVariable );
	
	if (!EFI_ERROR(Status)) {
		Status = PeiVariable->GetVariable(
					PeiVariable,
					L"IntelSetup",
					&gEfiSetupVariableGuid,
					NULL,
					&VariableSize,
					&SystemConfiguration
					);
		
		if ((!EFI_ERROR(Status)) && (SystemConfiguration.serialDebugMsgLvl != 0)){
			Status = PeiVariable->GetVariable(
						PeiVariable,
						L"Setup",
						&gEfiSetupVariableGuid,
						NULL,
						&SetupDataVarSize,
						&SetupData
						);
			
			if (!EFI_ERROR(Status)) {
			  //	  
			  //1).Send config to BMC and Inform BMC start to get message.
			  //	
				/*
				* OEM Command Data1----Enable/Disable function:	
				* 0x01		Began to output QPI debug info
				* 0x02		Stop to output QPI debug info
				* 
				* OEM Command Data2----Bit rate
				* 0x00		9600
				* 0x01		19200
				* 0x02		38400
				* 0x03		57600
				* 0x04		115200
				* 
				* OEM Command Data3----Data control
				* [7:6]	flow control
				* 00b		No flow control
				* 01b		RTS/CTS flow control
				* 10b		XON/XOF flow control
				* 
				* [5]	reserved
				* 
				* [4]	stop bits
				* 0b			1 stop bits
				* 1b			2 stop bits
				* 
				* [3]	character size
				* 0b			8 bits
				* 1			7 bits
				* 
				* [2:0]	parity
				* 000b		no parity
				* 001b		odd parity
				* 010b		even parity 
				*/
				
				//
				//OEM Command Data1
				//
				RequestData[0] = 0x01;	//Began to output QPI debug info
				
				//
				//OEM Command Data2
				//
				switch (SetupData.BaudRate[0]){
					case 3:	//Baud rate = 9600
						mBps = 9600;
						RequestData[1] = 0x00; 
						break;
					case 4:	//Baud rate = 19200
						mBps = 19200;
						RequestData[1] = 0x01;
						break;
					case 5:	//Baud rate = 38400
						mBps = 38400;
						RequestData[1] = 0x02;
						break;
					case 6:	//Baud rate = 57600
						mBps = 57600;
						RequestData[1] = 0x03;
						break;
					case 7:	//Baud rate = 115200
						mBps = 115200;
						RequestData[1] = 0x04;
						break;
					default:
						break;
				}
				
				//
				//OEM Command Data3
				//
				switch (SetupData.FlowControl[0]){
					case 0:	// No flow control
						break;
					case 1:	// RTS/CTS flow control	
						RequestData[2] |= BIT6;
						break;
					case 2:	// XON/XOF flow control
						RequestData[2] |= BIT7;
						break;
					default:
						break;
				}
				
				switch (SetupData.StopBits[0]){
					case 1:	// 1 stop bits
						mStop = 1;
						RequestData[2] &= ~BIT4;
						break;
					case 3:	// 2 stop bits
						mStop = 2;
						RequestData[2] |= BIT4;
						break;
					default:
						break;
				}
				
				switch (SetupData.DataBits[0]){
					case 7:	// 7 bits
						mData = 7;
						RequestData[2] |= BIT3;
						break;
					case 8:	// 8 bits
						mData = 8;
						RequestData[2] &= ~BIT3;
						break;
					default:
						break;
				}
				
				switch (SetupData.Parity[0]){
					case 1:	// no parity
						mParity = 0;
						break;
					case 2:	// even parity 
						mParity = 3;
						RequestData[2] |= BIT1;
						break;
					case 3:	// odd parity
						mParity = 1;
						RequestData[2] |= BIT0;
						break;
					default:
						break;		
				}
				
				//
				//Inform BMC begin to get message.
				//
				Status = (*PeiServices)->LocatePpi (
							(CONST EFI_PEI_SERVICES**)PeiServices,
							&gEfiPeiIpmiTransportPpiGuid,
							0,
							NULL,
							(VOID **)&IpmiTransportPpi );
					
				if ( !EFI_ERROR(Status) ) {		
					BmcStatus = IpmiTransportPpi->SendIpmiCommand (
								IpmiTransportPpi,
								0x30,
								0x00,
								0x70,
								RequestData,
								sizeof(RequestData),
								NULL,
								&ResponseDataSize );
				}
				
			  //	
			  //2).Initial Serial Port according to bios config.
			  //
				
				//
				// Some init is done by the platform status code initialization.
				//
				//
				// Map 5..8 to 0..3
				//
				Data = (UINT8) (mData - (UINT8) 5);
				
				//
				// Calculate divisor for baud generator
				//
				Divisor = 115200 / mBps;
				
				//
				// Set communications format
				//
				OutputData = (UINT8) ((DLAB << 7) | ((mBreakSet << 6) | ((mParity << 3) | ((mStop << 2) | Data))));
				IoWrite8 (mComBase + LCR_OFFSET, OutputData);
				
				//
				// Configure baud rate
				//
				IoWrite8 (mComBase + BAUD_HIGH_OFFSET, (UINT8) (Divisor >> 8));
				IoWrite8 (mComBase + BAUD_LOW_OFFSET, (UINT8) (Divisor & 0xff));
				
				//
				// Switch back to bank 0
				//
				OutputData = (UINT8) ((~DLAB << 7) | ((mBreakSet << 6) | ((mParity << 3) | ((mStop << 2) | Data))));
				IoWrite8 (mComBase + LCR_OFFSET, OutputData);
	
			}
		}
	}
#endif //TH0113B
  //TH0113<<<  

  //
  // Initialize data structures
  //
  MemSetLocal ((VOID *) &host, 0x00, sizeof (SYSHOST));

  host.var.common.oemVariable = (UINT32) PeiServices;

  ProcMemInit (&host);
  
  //TH0113>>>
#if INFORM_BMC_CATCH_QPI_MRC_DEBUG_MESSAGE //TH0113B
  //2.Inform BMC stop to get message.
  	if( !EFI_ERROR(BmcStatus) ) {
		RequestData[0] = 0x02;	//Stop to output QPI debug info
		RequestData[1] = 0x00;
		RequestData[2] = 0x00;
		Status = IpmiTransportPpi->SendIpmiCommand (
					  IpmiTransportPpi,
					  0x30,
					  0x00,
					  0x70,
					  RequestData,
					  sizeof(RequestData),
					  NULL,
					  &ResponseDataSize );
  	}
#endif //TH0113B
  //TH0113<<<
  
#ifdef SERIAL_DBG_MSG
  rcPrintf ((&host, " PeimMemoryQpiInit END \n"));
#endif
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UncoreInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
/*++

Routine Description:

  Driver entry point                

Arguments:

  FfsHeader -  Not used.
  PeiServices - General purpose services available to every PEIM.

Returns:

  EFI_SUCCESS:  Memory initialization completed successfully.
  All other error conditions encountered result in an ASSERT.

--*/
{
  return PeimMemoryQpiInit(FileHandle, PeiServices);
}
