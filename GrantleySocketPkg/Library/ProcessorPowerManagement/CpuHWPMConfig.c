//
// This file contains an 'Intel Peripheral Driver' and is      
// licensed for Intel CPUs and chipsets under the terms of your
// license agreement with Intel or your vendor.  This file may 
// be modified by the user, subject to additional terms of the 
// license agreement                                           
//
/** @file

  Code File for CPU Power Management

  Copyright (c) 2006 - 2014, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  Module Name:  CpuHWPMConfig.c

**/

#include "CpuPpmIncludes.h"




/**
	   Enables HWPM Interface feature  for specified processor.
	
	  This function enables of HWPM Interface for specified processor.
	
	  @param  setup provided user options.
	 
	**/

VOID
HWPMInterfaceReg (
  EFI_CPU_PM_STRUCT   *ppm
		)
{
  
 MSR_REGISTER MsrValue;
 EFI_CPU_CSR_ACCESS_PROTOCOL *CpuCsrAccess;
 UINT32 CapId5 = 0;
  //
  // Read MSR_MISC_PWR_MGMT
  //
  MsrValue.Qword = AsmReadMsr64 (MSR_MISC_PWR_MGMT);
  
  

  //MsrValue.Dwords.Low |= ppm->Setup->Hwpm.HWPMNative; //get from setup
  CpuCsrAccess = ppm->CpuCsrAccess;
  CapId5 = CpuCsrAccess->ReadCpuCsr(0, 0, CAPID5_PCU_FUN3_REG);
  
  if (ppm->Setup->Hwpm.HWPMNative){ //make it true if setup has choosen NAtive mode
  	if(CapId5 & B_HWPM_ENABLE){
  	  MsrValue.Dwords.Low |= N_MSR_HWPM_NATIVE_INTERFACE_ENABLE;
	  //
	  //Clear OOB Native if Native mode is being configured.
	  //
	  MsrValue.Dwords.Low &= ~N_MSR_HWPM_OOB_INTERFACE_ENABLE;
	  
	  //
	  // HWPM Interface setup 
	  //

	  AsmWriteMsr64 (MSR_MISC_PWR_MGMT, MsrValue.Qword);
	  //save for S3
	  WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_MISC_PWR_MGMT, 0, 64, MsrValue.Qword);
	  
	 
    }//capid5
  }
}
/**
	   Enables HWPM-OOB feature  for specified processor.
	
	  This function enables of HWPM-OOB  feature  for specified processor.
	
	  @param  setup provided user options.
	 
	**/


VOID
HWPMOOBModeReg (
   EFI_CPU_PM_STRUCT   *ppm
		)
{
  MSR_REGISTER MsrValue;
  EFI_CPU_CSR_ACCESS_PROTOCOL *CpuCsrAccess;
  UINT32 CapId5 = 0;
  //
  // Read MSR_MISC_PWR_MGMT
  //
  MsrValue.Qword = AsmReadMsr64 (MSR_MISC_PWR_MGMT);
  
 //ppm->Setup->Hwpm.HWPMOOB; //get from setup
  CpuCsrAccess = ppm->CpuCsrAccess;
  CapId5 = CpuCsrAccess->ReadCpuCsr(0, 0, CAPID5_PCU_FUN3_REG);
  
 if (ppm->Setup->Hwpm.HWPMOOB){
 	if(CapId5 & B_HWPM_ENABLE){
  MsrValue.Dwords.Low |= N_MSR_HWPM_OOB_INTERFACE_ENABLE;
  //
  //Clear HWPM Native if OOB mode is being configured.
  //
   MsrValue.Dwords.Low &= ~N_MSR_HWPM_NATIVE_INTERFACE_ENABLE;
  //
  // HWPM Ineterface setup for Broadwell-DE processors.
  //

  AsmWriteMsr64 (MSR_MISC_PWR_MGMT, MsrValue.Qword);
  //save for S3
  WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_MISC_PWR_MGMT, 0, 64, MsrValue.Qword);

  
  //
  // HWPM Ineterface setup for Broadwell-DE processors.
  //
  }
 }
}
	/**
	   Enables Autonomous Cstate feature  for specified processor.
	
	  This function enables of Autonomous Cstate feature  for specified processor.
	
	  @param  setup provided user options.
	 
	**/
	
VOID
HWPMAutonomousCstateModeReg (
	   EFI_CPU_PM_STRUCT   *ppm
		)
	{
	 MSR_REGISTER MsrValue;
	 EFI_CPU_CSR_ACCESS_PROTOCOL *CpuCsrAccess;
     UINT32 CapId5 = 0;
	  //
	  // Read MSR_MISC_PWR_MGMT
	  //
	  MsrValue.Qword = AsmReadMsr64 (MSR_PMG_CST_CONFIG_CONTROL);
	  //ppm->Setup->Hwpm.AutoCState; //get from setup
	 CpuCsrAccess = ppm->CpuCsrAccess;
     CapId5 = CpuCsrAccess->ReadCpuCsr(0, 0, CAPID5_PCU_FUN3_REG);
	 
	 if(CapId5 & B_ACC_ENABLE){
		if (ppm->Setup->Hwpm.AutoCState){
			MsrValue.Dwords.Low |=  N_MSR_AUTONOUMOUS_CSTATE_INTERFACE_ENABLE;
			//
			// HWPM Ineterface setup for Broadwell-DE processors.
			//

			AsmWriteMsr64 (MSR_PMG_CST_CONFIG_CONTROL, MsrValue.Qword);
			//save for S3
		//WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_PMG_CST_CONFIG_CONTROL, 0, 64, MsrValue.Qword);
		 }else{
			 MsrValue.Dwords.Low &=  ~N_MSR_AUTONOUMOUS_CSTATE_INTERFACE_ENABLE;
			 //
			 // HWPM Ineterface setup for Broadwell-DE processors.
			 //
			 AsmWriteMsr64 (MSR_PMG_CST_CONFIG_CONTROL, MsrValue.Qword);
			 //save for S3
			// WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_PMG_CST_CONFIG_CONTROL, 0, 64, MsrValue.Qword);
		 }//if
     }//capid check
}
//
//MSR_MISC_PWR_MGMT lock-start
//
VOID CpuPpmMISCPWRMGMTLock( EFI_CPU_PM_STRUCT   *ppm)
	/*++
	
			Routine Description:
	
			This routine is called to lock MSR_MISC_PWR_MGMT register
	
			Arguments:
	
			PPMPolicy Pointer to PPM Policy protocol instance
	
			Returns:
	
			VOID
	
	--*/
{

	  MSR_REGISTER MsrValue;
  	  EFI_CPU_CSR_ACCESS_PROTOCOL *CpuCsrAccess;
  	  UINT32 CapId5 = 0;
	  //
	  // Read MSR_MISC_PWR_MGMT
	  //
	  MsrValue.Qword = AsmReadMsr64 (MSR_MISC_PWR_MGMT);
	  
	  CpuCsrAccess = ppm->CpuCsrAccess;
	  CapId5 = CpuCsrAccess->ReadCpuCsr(0, 0, CAPID5_PCU_FUN3_REG);
	  
	   // HWPM lock bit is unset before setting bit,otherwise BIOS will see GP fault.
	  if(CapId5 & B_HWPM_ENABLE){
	   if( !(MsrValue.Dwords.Low & N_MSR_MISC_PWR_MGMT_LOCK)){
		  MsrValue.Dwords.Low |= N_MSR_MISC_PWR_MGMT_LOCK;
		  
		  //
		  //Program  LOCK BIT to lock MSR_MISC_PWR_MGMT register
		  //

		  AsmWriteMsr64 (MSR_MISC_PWR_MGMT, MsrValue.Qword);
		  //save for S3,causing S3 issue,WA for now
		 // WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_MISC_PWR_MGMT, 0, 64, MsrValue.Qword);
		   }
		  } 

	
}
//
//HWPM_END
//


