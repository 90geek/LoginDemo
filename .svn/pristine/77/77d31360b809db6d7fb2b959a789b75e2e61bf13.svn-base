//
// This file contains an 'Intel Peripheral Driver' and is      
// licensed for Intel CPUs and chipsets under the terms of your
// license agreement with Intel or your vendor.  This file may 
// be modified by the user, subject to additional terms of the 
// license agreement                                           
//
/** @file

  Code File for CPU Power Management

  Copyright (c) 2006 - 2016, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  Module Name:  PpmInitialize.c

**/

#include "PpmInitialize.h"
#include "CpuPpmIncludes.h"
#include <Library/OemCpuInit.h>

#define   B_LOCK_DESIRED_CORES_CSR  BIT31

extern EFI_GUID gCompletePowerManagementProtocolGuid;	//Aptio V Server Override



EFI_CPU_PM_STRUCT                 mPpmLib ={ 0, 0, 0, 0 };

VOID CpuPmProgramMsrs (
  EFI_CPU_PM_STRUCT *ppm
  );

VOID   CpuPmProgramCsrs (
  VOID
  );

EFI_STATUS
CpuPpmInitDone (
  VOID
  );

VOID
EFIAPI
PpmOnReadyToBoot (
  IN      EFI_EVENT                 Event,
  IN      VOID                      *Context
  );


//Aptio V Server Override - Start

VOID
PpmSetMsrLockBitWrapper (
    EFI_CPU_PM_STRUCT   *ppm
    )
{
    UINTN    ProcessorNumber = 0;

    //Get Logical Processor Number and fill ppm struct. This is for the library function PpmSetMsrLockBit to set lock bits in S3.
    
    mMpService->WhoAmI(mMpService, &ProcessorNumber);
    ppm->ProcessorNumber = ProcessorNumber;

    PpmSetMsrLockBit(ppm);
}
//Aptio V Server Override - End


EFI_STATUS
CpuPpmInitDone (
    VOID
    )
/*++

    Routine Description:

    Set BIOS init done to enable PPM features.

    Arguments:

    PPMPolicy Pointer to PPM Policy protocol instance

    Returns:

    EFI_SUCCESS
--*/
{
  UINT8 SocketNumber;
  UINT32  data;

  //set BIOS_PCU_SEMAPHORE if OC part is detected
  mMpService->StartupAllAPs(mMpService,
                            PpmSetTurboLimitPcuSemaphore,
                            TRUE,       
                            NULL,       
                            0,          
                            (VOID *)&mPpmLib,
                            NULL
                            );

  PpmSetTurboLimitPcuSemaphore((EFI_CPU_PM_STRUCT *)&mPpmLib);

/* //Fix HSD 4986378: PROMOTE from haswell_server: BIOS 18D15 fails to achieve package C6 under Red Hat
  if(mPpmInfo->CpuType == CPU_HASWELLSERVER) { 
  //Because IioInit driver may be after PPM driver
  //Set PCIE PkgCstEntryCriteria before hand off to OS
  for (SocketNumber = 0; SocketNumber < MAX_SOCKET; SocketNumber++) {
      if (mPpmInfo->SocketPresentBitMap & (1 << SocketNumber)){
        mPpmLib.Info->SocketNumber = SocketNumber;
        SetupPCIEPkgCstEntryCriteria((EFI_CPU_PM_STRUCT   *)&mPpmLib);
      }
    }
  }
*/
  mMpService->StartupAllAPs(mMpService,
                            PpmSetMsrLockBitWrapper,    //Aptio V Server Override
                            TRUE,       
                            NULL,       
                            0,          
                            (VOID *)&mPpmLib,
                            NULL
                            );

  //BSP do lock
  PpmSetMsrLockBitWrapper((EFI_CPU_PM_STRUCT *)&mPpmLib); //Aptio V Server Override

  //
  // Set CSR lock bits on all processors.
  //
  for (SocketNumber = 0; SocketNumber < MAX_SOCKET; SocketNumber++) {
    if (mPpmInfo->SocketPresentBitMap & (1 << SocketNumber)){
      mPpmLib.Info->SocketNumber = SocketNumber;
      PpmSetCsrLockBit((EFI_CPU_PM_STRUCT *)&mPpmLib);

    }
  }

  //
  // Set BIOS Init Done on all processors.
  //
  for (SocketNumber = 0; SocketNumber < MAX_SOCKET; SocketNumber++) {
    if (mPpmInfo->SocketPresentBitMap & (1 << SocketNumber)){
      mPpmLib.Info->SocketNumber = SocketNumber;
      PpmSetBiosInitDone((EFI_CPU_PM_STRUCT *)&mPpmLib);
      //Lock DESIRED_CORE here - TODO: may move to other driver later
      data = mPpmLib.CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, CSR_DESIRED_CORES_PCU_FUN1_REG);
      data |= B_LOCK_DESIRED_CORES_CSR;
      mPpmLib.CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, CSR_DESIRED_CORES_PCU_FUN1_REG, data);
  
    }
  }
if(mPpmLib.Info->CpuType == CPU_BDX_DE_SERVER || mPpmLib.Info->CpuType== CPU_BDX_EP_SERVER) { 

 //
 //Enable ACC if CPU supports +setup option enabled
 //
 
 mMpService->StartupAllAPs(mMpService,
                            HWPMAutonomousCstateModeReg,
                            TRUE,       
                            NULL,       
                            0,          
                            (VOID *)&mPpmLib,
                            NULL
                            );

  //BSP to enable ACC
   HWPMAutonomousCstateModeReg(&mPpmLib);
   }//ACC end
  //
  //Si WA283389:Ucode incorrectly signals GP during WRMSR with lock bit set in MISC_PWR_MGM
  //With MISC_PWR_MGMT[HWPM_LOCK]=1,pcode signals GP if user tries to write the locked bits bit no 0,6,8,13 with the same values as present before the write. 
  //
if(((mPpmLib.Info->CpuType== CPU_BDX_EP_SERVER) && (mPpmLib.Info->CpuStepping >= A0_REV_BDX)) ||(( mPpmLib.Info->CpuType == CPU_BDX_DE_SERVER) && (mPpmLib.Info->CpuStepping >= C0_REV_BDX))){
//BSP first to set lock bit
  CpuPpmMISCPWRMGMTLock((EFI_CPU_PM_STRUCT *)&mPpmLib);

   mMpService->StartupAllAPs(mMpService,
							  CpuPpmMISCPWRMGMTLock,
							  TRUE, 	  
							  NULL, 	  
							  0,		  
							  (VOID *)&mPpmLib,
							  NULL
							  );
 }//hwpm lock end
 //
 //Si WA # 283389:Ucode incorrectly signals GP during WRMSR with lock bit set in MISC_PWR_MGM
 //
  return EFI_SUCCESS;

}
  
EFI_STATUS
EFIAPI
PpmInitializeEntry (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  )
/*++

    Routine Description:

    Call back routine used to do the Power Management related Register Programming

    Arguments:

    Event - PpmProcessorSupportProtocol Install

    Returns:

    Status
    EFI_SUCCESS
--*/

{
  EFI_STATUS                Status;
  EFI_EVENT                 Event;
  VOID                      *Registration;

  Status = EFI_SUCCESS;

  InitializeCpuInfoStruct();
  InitializeCpuPPMLib ((EFI_CPU_PM_STRUCT *)&mPpmLib);

  CpuPmProgramCsrs();

  mMpService->StartupAllAPs(mMpService,
                              CpuPmProgramMsrs,
                              TRUE,       
                              NULL,       
                              0,          
                              (VOID *)&mPpmLib,   
                              NULL
                              );
                              
  CpuPmProgramMsrs((EFI_CPU_PM_STRUCT *)&mPpmLib);

  OemCpuOtherChipThermalInit(&mPpmLib);
                             
  //allow APs switch to max non-turbo ratio if user choose 
  mMpService->StartupAllAPs(mMpService,
                              PStateTransition,
                              TRUE,       
                              NULL,       
                              0,          
                              (VOID *)&mPpmLib,   
                              NULL
                              );

  //allow SBSP switch to max non-turbo ratio if user choose 
  PStateTransition((EFI_CPU_PM_STRUCT *)&mPpmLib); 

  Event = EfiCreateProtocolNotifyEvent (
            //&gExitPmAuthProtocolGuid,	//Aptio V Sever Override
            &gCompletePowerManagementProtocolGuid,  //Aptio V Sever Override
            TPL_CALLBACK,
             PpmOnReadyToBoot,
             NULL,
            &Registration
             );
  ASSERT (Event);

  return Status;
}

VOID
EFIAPI
PpmOnReadyToBoot (
  IN      EFI_EVENT                 Event,
  IN      VOID                      *Context
  )
{
  EFI_STATUS Status;
  VOID       *ProtocolPointer;
 
 //Aptio V Sever Override
  Status = gBS->LocateProtocol (&gCompletePowerManagementProtocolGuid, NULL, &ProtocolPointer);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = CpuPpmInitDone();

  return;
}
//End of OnReadyToBoot


#ifdef DE_SKU
VOID
ProgramCsrPchThermControl (
		EFI_CPU_PM_STRUCT *ppm
		)
/*++

		Routine Description:

		This routine is called to program CSR_PCH_TEMP Config. It will be called multiple times by passing any of the SocketNumber to be programmed.

		Arguments:

		PPMPolicy Pointer to PPM Policy protocol instance

		Returns:

		EFI_SUCCESS

--*/
{
  PCH_TEMP_PCU_FUN0_STRUCT pchTempPcuReg;
  UINTN RegAddr = 0; 
  UINT8  Size = 4;
  UINT8  SocketNumber;
  EFI_CPU_CSR_ACCESS_PROTOCOL *CpuCsrAccess;
  UINT64 MsrValue;

  SocketNumber = ppm->Info->SocketNumber;
  CpuCsrAccess = ppm->CpuCsrAccess;
  
  // Read (CSR)
  pchTempPcuReg.Data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, PCH_TEMP_PCU_FUN0_REG);

  //Program CSR, PCH_TEMP_PCU_FUN0_REG
  pchTempPcuReg.Bits.use_pch_hot = ppm->Setup->UsePchHot;
  pchTempPcuReg.Bits.use_pch_temp_from_me = ppm->Setup->UsePchTempFromME;
  pchTempPcuReg.Bits.allow_pch_throttle = ppm->Setup->CpuToPchThrottle;

  //PCH Tcontrol Offset is calculated by reading Temp Control Offset from MSR_TEMPERATURE_TARGET (0x1A2) and converting it to 9 bit value.
  MsrValue = AsmReadMsr64 (MSR_TEMPERATURE_TARGET);
  MsrValue &= 	B_MSR_TEMPERATURE_TARGET_FAN_TEMP_TARGET_OFFSET;
  MsrValue = (UINT8) RShiftU64 (MsrValue, N_MSR_TEMPERATURE_TARGET_FAN_TEMP_TARGET_OFFSET);
  pchTempPcuReg.Bits.t_control_offset = (UINT32)((MsrValue + 50) * 2);
  
  CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, PCH_TEMP_PCU_FUN0_REG, pchTempPcuReg.Data);
  RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, PCH_TEMP_PCU_FUN0_REG, &Size);
  S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &pchTempPcuReg.Data ); 

  return;
}
#endif  //#ifdef DE_SKU



VOID CpuPmProgramMsrs (
  EFI_CPU_PM_STRUCT *ppm
  )
{
  UINTN    ProcessorNumber = 0;

  mMpService->WhoAmI(mMpService, &ProcessorNumber);
  ppm->ProcessorNumber = ProcessorNumber;
  ProgramMsrPowerCtl (ppm);
  ProgMsrPriPlaneCurtCfgCtrL (ppm);
  ProgramMsrTurboPowerLimit (ppm);
  ProgramMsrTurboRatioLimit(ppm);
  ProgramEnergyPerfBiasConfigMsr(ppm);
   //
   //BIOS HSD 4988172:We don't need these knobs as these registers are Write only.
   //Recommendation: work arounds those knobs until bug Silicon HSD 281641 is fixed
   //

#ifdef DE_SKU
#endif    //#ifdef DE_SKU
   
  
//HWPM-start



if(mPpmLib.Info->CpuType == CPU_BDX_DE_SERVER || mPpmLib.Info->CpuType== CPU_BDX_EP_SERVER) { 
 //
 //Enable HWPM modes if CPU supports+setup option enabled
 //
 HWPMInterfaceReg(ppm);
 HWPMOOBModeReg(ppm);
 }
   
 
//HWPM-end
  if(mPpmLib.Info->CpuType == CPU_HASWELLSERVER || mPpmLib.Info->CpuType == CPU_BDX_DE_SERVER || mPpmLib.Info->CpuType== CPU_BDX_EP_SERVER ) { 
    ProgramMsrTemperatureTarget(ppm); 
    ProgramMsrMiscPwrMgmt(ppm); 

  }
  return;

}

VOID 
CpuPmProgramCsrs( VOID )
{

  UINT8  SocketNumber;

  for (SocketNumber = 0; SocketNumber < MAX_SOCKET; SocketNumber++) {
    if (mPpmInfo->SocketPresentBitMap & (1 << SocketNumber)){
      mPpmLib.Info->SocketNumber = SocketNumber;

      ProgramCSRTurboPowerLimit((EFI_CPU_PM_STRUCT *)&mPpmLib);
      ProgramCsrPkgCstEntryCriteriaMask((EFI_CPU_PM_STRUCT *)&mPpmLib);
      //ProgramCsrPcuBiosSpare2((EFI_CPU_PM_STRUCT *)&mPpmLib);  //take care in MPM (MemThrot.c)
      ProgramCsrPerfPlimitControl((EFI_CPU_PM_STRUCT *)&mPpmLib);
      ProgramCsrDynamicPerfPowerCtl((EFI_CPU_PM_STRUCT *)&mPpmLib);
      //ProgramCsrIoBandwidthPLimitControl((EFI_CPU_PM_STRUCT *)&mPpmLib);
      ProgramCsrSapmCtl((EFI_CPU_PM_STRUCT *)&mPpmLib);
      ProgramCsrSwLtrOvrd((EFI_CPU_PM_STRUCT *)&mPpmLib);

      if (mPpmLib.Info->CpuType == CPU_HASWELLSERVER || mPpmLib.Info->CpuType == CPU_BDX_DE_SERVER || mPpmLib.Info->CpuType == CPU_BDX_EP_SERVER) {   
        ProgramB2PFastRaplDutyCycle((EFI_CPU_PM_STRUCT *)&mPpmLib);
      }

#ifdef DE_SKU
      // Program PCH_TEMP_PCU_FUN0_REG if it is BDX-DE sku
      if(mPpmLib.Info->CpuType == CPU_BDX_DE_SERVER) {
        ProgramCsrPchThermControl((EFI_CPU_PM_STRUCT *)&mPpmLib);
      }
#endif  //#ifdef DE_SKU

      ProgramB2PPcuMiscConfig((EFI_CPU_PM_STRUCT *)&mPpmLib);


    }
  }
}


