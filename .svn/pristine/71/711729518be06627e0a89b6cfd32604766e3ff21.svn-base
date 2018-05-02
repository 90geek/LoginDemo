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

  Module Name:  CpuPpmLib.c

**/

#include "CpuPpmIncludes.h"

VOID
InitializeCpuPPMLib (
		EFI_CPU_PM_STRUCT   *ppm
		)
/*++

		Routine Description:

		Initializes the platform power management library. This must be called
		prior to any of the library functions being used.

		Arguments: None

		Returns: None

--*/
{
  UINT64    TempMsr;
  UINT64    PackagePowerSKUUnitMsr;
  UINT8     ProcessorPowerUnit = 0;
  UINT8     ProcessorTimeUnit = 0;
  UINT16    PackageTdp = 0;
  //EFI_STATUS    Status;

 
  ppm->Version.Major = (UINT8)PPM_MAJOR;
  ppm->Version.Minor = (UINT8)PPM_MINOR;
  ppm->Version.Rev   = (UINT8)PPM_REV;
  ppm->Version.Build = (UINT8)PPM_BUILD;

  DEBUG ( (EFI_D_INFO, " \n\n :: !!! PPM Revision: Major:%02XMinor:%02XRev:%02X%02X!!!. \n\n",
          ppm->Version.Major,ppm->Version.Minor,ppm->Version.Rev,ppm->Version.Build) );

  //
  // Get Processor TDP
  // Get Maximum Power from Turbo Power Limit MSR Bits[14:0]
  // and convert it to units specified by Package Power SKU
  // Unit MSR [3:0]
  //
  TempMsr                 = AsmReadMsr64 (MSR_TURBO_POWER_LIMIT);
  PackagePowerSKUUnitMsr  = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU_UNIT);

  ProcessorPowerUnit = (UINT8) (PackagePowerSKUUnitMsr & PACKAGE_POWER_UNIT_MASK);
  if( ProcessorPowerUnit == 0 ) {
    ProcessorPowerUnit = 1;
  } else {
    ProcessorPowerUnit = (UINT8) LShiftU64 (2, (ProcessorPowerUnit - 1));
  }

  PackageTdp = (UINT16) DivU64x32 ((TempMsr & POWER_LIMIT_MASK), ProcessorPowerUnit);

  ProcessorTimeUnit = (UINT8)((PackagePowerSKUUnitMsr & PACKAGE_TIME_UNIT_MASK) >> 16);
  if ( ProcessorTimeUnit == 0 ) {
    ProcessorTimeUnit = 1;
  } else {
    ProcessorTimeUnit = (UINT8) LShiftU64 (2, (ProcessorTimeUnit - 1));
  }

  ppm->Info->PackageTdp = PackageTdp;
  ppm->Info->ProcessorPowerUnit = ProcessorPowerUnit;
  ppm->Info->ProcessorTimeUnit  = ProcessorTimeUnit;

  return;
}

VOID
PStateTransition (
  EFI_CPU_PM_STRUCT   *ppm
  )
{

  MSR_REGISTER  PerformanceControl;
  MSR_REGISTER  PlatformInfo;
  UINT32        RegEcx;

  //HSX BIOS HSD - 4166511 BIOS does not test for GV3 support before attempting to write to IA32_PERF_CTRL
  AsmCpuid (EFI_CPUID_VERSION_INFO, NULL, NULL, &RegEcx, NULL);
  if (!(RegEcx & B_EFI_CPUID_VERSION_INFO_ECX_EIST))  return;

  PerformanceControl.Qword = AsmReadMsr64 (MSR_IA32_PERF_CTL);
  PlatformInfo.Qword =  AsmReadMsr64 (MSR_PLATFORM_INFO);

  PerformanceControl.Dwords.Low &= (UINT32)~(0x0000FF00);  //clear P target
  // set P-target to performance (max ratio) as default
  PerformanceControl.Dwords.Low |= (PlatformInfo.Dwords.Low & 0x0000FF00);

  if(ppm->Setup->AdvPwrMgtCtlFlags & PCU_CPU_EFFICIENT_BOOT) { //max efficent
    PerformanceControl.Dwords.Low &= (UINT32)~(0x0000FF00);  //clear P target
    // set P target to max efficient (min Ratio)
    PerformanceControl.Dwords.Low |= (PlatformInfo.Dwords.High & 0x0000FF00);
  }

  AsmWriteMsr64 (MSR_IA32_PERF_CTL, PerformanceControl.Qword);
  return;
}

VOID
PpmInitPostPhase3(
    EFI_CPU_PM_STRUCT   *ppm,
    UINT8               Socket
)
{
  // 4988855: System loops in BIOS after cpu went into unbreakable shutdown
  //  [clone from b286903] -  the PCU MCA error source status has to be cleared
  //                          only after the RST_CPL3
  ppm->CpuCsrAccess->WriteCpuCsr(Socket, 0, MCA_ERR_SRC_LOG_PCU_FUN2_REG, 0);
}

VOID
PpmSetBiosInitDone (
    EFI_CPU_PM_STRUCT   *ppm
    )
/*++

    Routine Description:

    Executed by System BSP only.
    Common software programming steps needed before warm reset and CPU-only reset.


    Arguments:

    PPMPolicy Pointer to PPM Policy protocol instance

    Returns:

    EFI_SUCCESS

--*/
{

  UINT32    data = 0;
  
  //
  //4987134  start
  //
  
  UINTN    RegAddr = 0; 
  //
  //4987134 end
  //
  
  UINT8     Size = 4;  
  UINT8     SocketNumber;
  EFI_CPU_CSR_ACCESS_PROTOCOL *CpuCsrAccess;

  UINT32 PM_MBX_CMD = 0;
  UINT32 PM_MBX_DATA = 0;
  UINT32 Tempdata = 0;

  // 
  // HSD 4167067 - ESCALATE from hexaii_hsx_mock:PL2_SAFETY_NET not enabled by BIOS
  // set PCU_MISC_CONFIG PL2_SAFETY_NET_ENABLE to 1 before CPL3
  //

  SocketNumber = ppm->Info->SocketNumber;
  CpuCsrAccess = ppm->CpuCsrAccess;
  data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, BIOS_MAILBOX_DATA_PCU_FUN1_REG);

    PM_MBX_CMD = (UINT32) MAILBOX_BIOS_CMD_READ_PCU_MISC_CONFIG;
    Tempdata = ppm->CpuCsrAccess->Bios2PcodeMailBoxWrite(SocketNumber, PM_MBX_CMD, PM_MBX_DATA);
    if ((Tempdata & 0x000000ff) != PPM_MAILBOX_BIOS_ERROR_CODE_INVALID_COMMAND) {
      data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, BIOS_MAILBOX_DATA_PCU_FUN1_REG);
      data &= ~PL2_SAFETY_NET_ENABLE;

      if (ppm->Setup->Pl2SafetyNetEnable) {
         data |= PL2_SAFETY_NET_ENABLE;
      } 

      //HSD: 4986250: BIOS settings for CAP x/ PkgC  with MC PLL ON  (for PkgC3/C6)
     
      if(((ppm->Info->CpuType == CPU_HASWELLSERVER) && (ppm->Info->CpuStepping >= C0_REV_HSX))) {
         data |= PKGC_RCOMP_DISABLE;
      } 

      PM_MBX_CMD = (UINT32) MAILBOX_BIOS_CMD_WRITE_PCU_MISC_CONFIG;
      PM_MBX_DATA = (UINT32) data; 

      Tempdata = ppm->CpuCsrAccess->Bios2PcodeMailBoxWrite(SocketNumber, PM_MBX_CMD, PM_MBX_DATA);

      if ((Tempdata & 0x000000ff) != PPM_MAILBOX_BIOS_ERROR_CODE_INVALID_COMMAND) {
      DEBUG ( (EFI_D_INFO, "\nDone Write MAILBOX_BIOS_CMD_WRITE_PCU_MISC_CONFIG, data = %x, SETUP Pl2SafetyNetEnable = %x\n", data, ppm->Setup->Pl2SafetyNetEnable) );
}
    }

    PM_MBX_CMD = (UINT32) MAILBOX_BIOS_CMD_READ_PCU_MISC_CONFIG;
    PM_MBX_DATA = 0; 
    Tempdata = ppm->CpuCsrAccess->Bios2PcodeMailBoxWrite(SocketNumber, PM_MBX_CMD, PM_MBX_DATA);
    if ((Tempdata & 0x000000ff) != PPM_MAILBOX_BIOS_ERROR_CODE_INVALID_COMMAND) {
      data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, BIOS_MAILBOX_DATA_PCU_FUN1_REG);
      DEBUG ( (EFI_D_INFO, ":: Read BIOS_MAILBOX_DATA_PCU_FUN1_REG back, data = %x\n", data) );
    }

  SocketNumber = ppm->Info->SocketNumber;
  CpuCsrAccess = ppm->CpuCsrAccess;

  //
  // Read/Modify/Wrtie setting BIOS Init Done in BIOS_RESET_CPL
  //

  //BIOS_RESET_CPL_PCU_FUN1_REG
  data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, BIOS_RESET_CPL_PCU_FUN1_REG);
  DEBUG ( (EFI_D_INFO, ":: Debug PpmSetBiosInitDone Read Data: %08X\n\n", data) );

  //
  // Set BIOS Init Done in BIOS, in Reset_CPl (CSR), to commuicate to Pcode to start PM flows
  //
  data |= BIOS_RSTCOL3_PMCFGDONE; // PM Init Done
  CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, BIOS_RESET_CPL_PCU_FUN1_REG, data);
  RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, BIOS_RESET_CPL_PCU_FUN1_REG, &Size);
  S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &data );

  PpmInitPostPhase3(ppm, SocketNumber);

  if (/*PPMPolicy->HybridMode == PPM_DISABLE*/ 1) {
    // if DRAM RAPL Hybrid mode is disabled then lock Mailbox interface, else leave it clear to be be set later
    data |= BIOS_RSTCPL4_MEMCFGDONE;// MemCFG Done,
    //Note: This is for DRAM RAPL, may move tie this to a
    //setup option later which is why this is on a seperate line
  }

  CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, BIOS_RESET_CPL_PCU_FUN1_REG, data);
  RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, BIOS_RESET_CPL_PCU_FUN1_REG, &Size);
  S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &data );


   return;
}

//AptioV server override start: All debug messages commented out to avoid assert seen when two processors are outputting debug messages and trying to raise TPL.
VOID
PpmSetCsrLockBit (
    EFI_CPU_PM_STRUCT   *ppm
    )
/*++

    Routine Description:

    Executed by System BSP only.
    Common software programming steps needed before warm reset and CPU-only reset.


    Arguments:

    PPMPolicy Pointer to PPM Policy protocol instance

    Returns:

    EFI_SUCCESS

--*/
{
  UINT32    data;
  UINTN     RegAddr = 0; 
  UINT8     Size = 4;  
  UINT8     SocketNumber;
  EFI_CPU_CSR_ACCESS_PROTOCOL *CpuCsrAccess; 

  SocketNumber = ppm->Info->SocketNumber;
  CpuCsrAccess = ppm->CpuCsrAccess;

  data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, PACKAGE_RAPL_LIMIT_N1_PCU_FUN0_REG);
  if (!(ppm->Info->CapId4 & B_OC_ENABLED)) {
   data |= POWER_LIMIT_LOCK;
  }
  CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, PACKAGE_RAPL_LIMIT_N1_PCU_FUN0_REG, data);
  RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, PACKAGE_RAPL_LIMIT_N1_PCU_FUN0_REG, &Size);
  S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &data );
  //DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in PACKAGE_RAPL_LIMIT with value = %x\n", data) );  // Comment all debug messages to prevent assert

  //
  // Read/Modify/Wrtie setting BIOS Init Done in BIOS_RESET_CPL
  //
  data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, SAPMCTL_PCU_FUN1_REG);
  data |= PPCCC_LOCK;
  CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, SAPMCTL_PCU_FUN1_REG, data);
  RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, SAPMCTL_PCU_FUN1_REG, &Size);
  S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &data );
  //DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in CSR_SAPMCTL with value = %x\n", data) );  // Comment all debug messages to prevent assert

  //DRAM_PLANE_POWER_LIMIT_N0_PCU_FUN2_REG
  data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, DRAM_PLANE_POWER_LIMIT_N0_PCU_FUN2_REG);
  data |= PPCCC_LOCK;
  CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, DRAM_PLANE_POWER_LIMIT_N0_PCU_FUN2_REG, data);
  RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, DRAM_PLANE_POWER_LIMIT_N0_PCU_FUN2_REG, &Size);
  S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &data );
  //DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in CSR_DRAM_PLANE_POWER_LIMIT with value = %x\n", data) );  // Comment all debug messages to prevent assert

  data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, P_STATE_LIMITS_PCU_FUN0_REG);
  data |= PPCCC_LOCK;
  CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, P_STATE_LIMITS_PCU_FUN0_REG, data);
  RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, P_STATE_LIMITS_PCU_FUN0_REG, &Size);
  S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &data );
  //DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in CSR_DRAM_PLANE_POWER_LIMIT with value = %x\n", data) );  // Comment all debug messages to prevent assert

  //CSR_DESIRED_CORES_PCU_FUN1_REG
  data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, CSR_DESIRED_CORES_PCU_FUN1_REG);
  data |= BIT31;
  CpuCsrAccess->WriteCpuCsr(SocketNumber, 0, CSR_DESIRED_CORES_PCU_FUN1_REG, data);
  RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, CSR_DESIRED_CORES_PCU_FUN1_REG, &Size);
  S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &data );
  //DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in CSR_DESIRED_CORES_PCU_FUN1_REG with value = %x\n", data) );  // Comment all debug messages to prevent assert

  // PACKAGE_RAPL_LIMIT_N1_PCU_FUN0_REG 
  data = CpuCsrAccess->ReadCpuCsr(SocketNumber, 0, PACKAGE_RAPL_LIMIT_N1_PCU_FUN0_REG);
  if (ppm->Setup->TurboPowerLimit.Dwords.High & POWER_LIMIT_LOCK) {
    data |= POWER_LIMIT_LOCK;
    RegAddr = CpuCsrAccess->GetCpuCsrAddress(SocketNumber, 0, PACKAGE_RAPL_LIMIT_N1_PCU_FUN0_REG, &Size);
    S3BootScriptSaveMemWrite (S3BootScriptWidthUint32, RegAddr, 1, &data );
    //DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in PACKAGE_RAPL_LIMIT_N1_PCU_FUN0_REG with value = %x\n", data) );  // Comment all debug messages to prevent assert
  }


  return;
}

VOID
PpmSetMsrLockBit (
    EFI_CPU_PM_STRUCT   *ppm
    )
/*++

    Routine Description:

    Set LOCK bit in MSR_PRIMARY_PLANE_CURRENT_CONFIG_CONTROL, MSR_DRAM_PLANE_POWER_LIMIT, and MSR_PRIMARY_PLANE_TURBO_POWER_LIMIT.

    NOTE: This routine should be specifically used to program MSR. There has been a separate routine created for programming CSR's.

    Arguments:

    PPMPolicy Pointer to PPM Policy protocol instance

    Returns:

    EFI_SUCCESS

--*/
{

  MSR_REGISTER TempMsr;

  // Program MSR_TURBO_POWER_LIMIT LOCK bit
  TempMsr.Qword = AsmReadMsr64 (MSR_TURBO_POWER_LIMIT);
  if (ppm->Setup->TurboPowerLimit.Dwords.High & POWER_LIMIT_LOCK) {
    TempMsr.Dwords.High |= POWER_LIMIT_LOCK;
    AsmWriteMsr64 (MSR_TURBO_POWER_LIMIT, TempMsr.Qword);
  }

  //Aptio V Server Override lock register.
  WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_TURBO_POWER_LIMIT, 0, 64, TempMsr.Qword);

  //
  // Multi-thread unsafe
  // DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in MSR 0x601, 0x618, 0x638....\n") );
  //
  // Program MSR_POWER_CTL LOCK bit
  TempMsr.Qword = AsmReadMsr64 (MSR_POWER_CTL);
  TempMsr.Dwords.Low |= PROCHOT_LOCK;
  AsmWriteMsr64 (MSR_POWER_CTL, TempMsr.Qword);

  //Aptio V Server Override lock register.
  WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_POWER_CTL, 0, 64, TempMsr.Qword);

  // Program MSR_PRIMARY_PLANE_CURRENT_CONFIG_CONTROL LOCK bit
  TempMsr.Qword = AsmReadMsr64 (MSR_PRIMARY_PLANE_CURRENT_CONFIG_CONTROL);
   if (!(ppm->Info->CapId4 & B_OC_ENABLED)) {
//AptioV server Override for XTU - START 
#if defined(PERF_TUNE_SUPPORT) && PERF_TUNE_SUPPORT == 1  
  // Unlock package current lock bit for XTU feature.
  TempMsr.Dwords.Low |= ppm->Setup->PP0CurrentCfg.Dwords.Low & PPCCC_LOCK;
#else
  TempMsr.Dwords.Low |= PPCCC_LOCK;
#endif
//AptioV server Override for XTU - EN
   }
  AsmWriteMsr64 (MSR_PRIMARY_PLANE_CURRENT_CONFIG_CONTROL, TempMsr.Qword);
  // Save Lock Bit for S3
  //Aptio V Server Override lock register.
  WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_PRIMARY_PLANE_CURRENT_CONFIG_CONTROL, 0, 64, TempMsr.Qword);

 // Program MSR_FLEX_RATIO LOCK bit (HSX, this bit is not defined until B0 stepping)
 // keeping this workaround for BDX also, please check if this need change.
 //

  if(((ppm->Info->CpuType == CPU_HASWELLSERVER) && (ppm->Info->CpuStepping >= B0_REV)&& (!ppm->Setup->OverclockingLock))||(((ppm->Info->CpuType == CPU_BDX_DE_SERVER) || (ppm->Info->CpuType == CPU_BDX_EP_SERVER)) && (!ppm->Setup->OverclockingLock))) {
    TempMsr.Qword = AsmReadMsr64 (MSR_FLEX_RATIO);
    if (TempMsr.Qword & OC_SUPPORTED) {              // if non-zero then the part support Overclocking
      //
      // Multi-thread unsafe
      // DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in MSR %x = %x.\n", MSR_FLEX_RATIO, AsmReadMsr64 (MSR_FLEX_RATIO)) );
      //
      TempMsr.Dwords.Low |= OC_LOCK;                 // cannot set the lock bit if OC is not supported (gp fault)
      AsmWriteMsr64 (MSR_FLEX_RATIO, TempMsr.Qword);

      //Aptio V Server Override lock register.
      WriteRegisterTable(ppm->ProcessorNumber, Msr, MSR_FLEX_RATIO, 0, 64, TempMsr.Qword);
    }
  }

  if(ppm->Setup->AdvPwrMgtCtlFlags & CPU_MSR_LOCK) {
    // Program MSR_PMG_CST_CONFIG_CONTROL LOCK bit
    TempMsr.Qword = AsmReadMsr64 (MSR_PMG_CST_CONFIG_CONTROL);
    TempMsr.Dwords.Low |= BIT15;
    AsmWriteMsr64 (MSR_PMG_CST_CONFIG_CONTROL, TempMsr.Qword);
    //
    // Multi-thread unsafe
    // DEBUG ( (EFI_D_ERROR, ":: Set LOCK bit in MSR %x = %x.\n", MSR_PMG_CST_CONFIG_CONTROL, AsmReadMsr64 (MSR_PMG_CST_CONFIG_CONTROL)) );
	//
  }

  return;
}
//AptioV server override end: All debug messages commented out to avoid assert seen when two processors are outputting debug messages and trying to raise TPL.
