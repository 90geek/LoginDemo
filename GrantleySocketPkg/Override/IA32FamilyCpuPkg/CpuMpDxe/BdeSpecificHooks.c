#include "BdeSpecificHooks.h"
#include "MchkInit.h"
#include "Cpu\CpuRegs.h"
EFI_CPU_CSR_ACCESS_PROTOCOL         *mCpuCsrAccess;

extern MACHINE_CHECK_ATTRIBUTE MachineCheckAttribute[FixedPcdGet32(PcdCpuMaxLogicalProcessorNumber)];

VOID 
BdeHookInitialize()
{
  EFI_STATUS    Status;
  
  Status = gBS->LocateProtocol (&gEfiCpuCsrAccessGuid, NULL, &mCpuCsrAccess);
  ASSERT_EFI_ERROR (Status);
}

UINTN
GetNewSbspProcessNumber (
  UINT32 SocketNumber
  )
{
  UINTN       i;
  UINTN       ProcessorNumber = (UINTN)-1;
  UINT32      CoreNumber = (UINT32)-1;     
  UINT32      ThreadNumber = (UINT32)-1;  
   

  for (i = 0; i < mCpuConfigContextBuffer.NumberOfProcessors; i++) {

    if(mCpuConfigLibConfigContextBuffer->CollectedDataBuffer[i].ProcessorLocation.Package == SocketNumber) {
      if(mCpuConfigLibConfigContextBuffer->CollectedDataBuffer[i].ProcessorLocation.Core >= CoreNumber) {
        continue;
      } else {
        CoreNumber = mCpuConfigLibConfigContextBuffer->CollectedDataBuffer[i].ProcessorLocation.Core;
        if(mCpuConfigLibConfigContextBuffer->CollectedDataBuffer[i].ProcessorLocation.Thread > ThreadNumber) {
          continue;
        } else {
          ThreadNumber = mCpuConfigLibConfigContextBuffer->CollectedDataBuffer[i].ProcessorLocation.Thread;
          ProcessorNumber = i;
        }
      } //end of if CoreNumber
    } //end if SocketNumber
  }

  if(ProcessorNumber >= mCpuConfigContextBuffer.NumberOfProcessors) {  //don't find one
    ProcessorNumber = mCpuConfigLibConfigContextBuffer->BspNumber;     //deafult to current Sbsp
  }
  return ProcessorNumber;
}

//
// BIOS w/a for #3613974
// Please implement LLC init WA for all steppings != B0/B1
// C-step and higher will require BIOS workaround as it's removed from uCode again
//
// 
VOID WA_InitializeLLC(
  UINTN      ProcessorNumber
  )
{
  UINT32              FamilyId;
  UINT32              ModelId;
  UINT32              SteppingId;
  UINT32              CoreId;
  UINT32              ThreadId;
  UINT32              data32;
  UINT8               *StartAddr;                         // start from 256MB
  UINT32              Stride = 64;                        // 64-Byte stride
  UINT32              LoopCount = (24*1024*1024)/Stride;  // LoopCount = 24MB/Stride
  UINT32              i;

  GetProcessorVersionInfo (ProcessorNumber, &FamilyId, &ModelId, &SteppingId, NULL);
  if (!(FamilyId == NEHALEM_FAMILY_ID && ModelId== SANDYBRIDGE_SERVER_MODEL_ID)) {
    return;
  }
  if (SteppingId > 1 && SteppingId < 5) return; // 2 is B0, 3 is B1

  //
  //Execute this workaround only on Core0/Thread0 of a CPU package
  //
  GetProcessorLocation (ProcessorNumber, NULL, &CoreId, &ThreadId);
  if (!(CoreId ==0 && ThreadId == 0)) {
    return;
  }

  //
  //  Read memory cache-lines into LLC
  //
  StartAddr = (UINT8 *)((UINT64)0x020000000); 
  for (i=0; i<LoopCount; i++) {
    data32 =   *((volatile UINT32*) StartAddr);
    StartAddr += Stride;
  }
  //
  // Clear MCi_Status related to CBo LLC (MCA banks 12 thru 19) 
  //  
  if (FeaturePcdGet (PcdCpuMachineCheckFlag)) {
    for (i= 12; (i < 12 + 8) && (i < MachineCheckAttribute[ProcessorNumber].NumberOfErrorReportingBank); ++i) {
      WriteRegisterTable (ProcessorNumber, Msr, EFI_IA32_MC0_STATUS + 4 * i, 0, 64, 0);
    }
  }
}

//
//  BIOS w/a for 3875167, 3614340, 3612728 (SNB Server System Agent BSU).
//  Transactions Issued from Socket 1
//  Appear Locked Due to an INVD from Socket 0
//  Permanent workaround for B0 and later steppings
// 

VOID WA_Lock()
{
  EFI_STATUS            Status;
  EFI_IIO_UDS_PROTOCOL  *IioUds;
  UINT32                data;
  UINT8                 i;
  UINT32                CpuSignature;

  if(FeaturePcdGet(PcdCpuBroadwellFamilyFlag) ||
     FeaturePcdGet(PcdCpuHaswellFamilyFlag))
    IntelSecurePhase();

  if (FeaturePcdGet (PcdCpuSandyBridgeFamilyFlag)) {
    AsmCpuid (EFI_CPUID_VERSION_INFO, &CpuSignature, NULL, NULL, NULL);
    if ((CpuSignature & 0x0fff0ff0) == 0x206d0) {
      //
      // Locate the IIO Protocol Interface
      //
      Status = gBS->LocateProtocol (&gEfiIioUdsProtocolGuid, NULL, &IioUds);
      ASSERT_EFI_ERROR (Status);

      //
      // After all APs has loaded microcode, clear LockControl.LockDisable on 
      // all sockets present in the system.
      //
      for (i = 0; i < MAX_SOCKET; i++) {
        if (IioUds->IioUdsPtr->PlatformData.CpuQpiInfo[i].Valid) {
          data = mCpuCsrAccess->ReadCpuCsr(i, 0, LOCKCONTROL_UBOX_CFG_REG);
          data &= ~BIT0;
          mCpuCsrAccess->WriteCpuCsr(i, 0, LOCKCONTROL_UBOX_CFG_REG , data);

          
        }
      }
    }
  }
}




/*
 *  Intel Secure Uncore - to protect Processor Uncore components from mis-configuration during runtime
 */
INTEL_SECURE_UNCORE                    mIntelSecure;

VOID
UncoreSmbClkCfgHide(
    IN UINTN  ProcessorNumber
)
{
  UINT64        BaseAddress=0;
  UINT64        Mask=0;

  //Check MSR_PLATFORM_INFO[61], if set then uCode supports SMBUS filtering
  if ((AsmReadMsr64(EFI_PLATFORM_INFORMATION) & BIT61) == 0) {
    return;
  }

  BaseAddress = mIntelSecure.PhyAddr & 0xFFFFFFFF;
  Mask        = mIntelSecure.Phymask & 0xFFFFFFFF;

  AsmWriteMsr64(MSR_SMBUS_MMIO_FILTER,
                (Mask << 32) +  //EDX contents
                BaseAddress);   //EAX contents
}

VOID
IntelSecurePhase()
{
  EFI_STATUS                      Status;
  EFI_IIO_UDS_PROTOCOL            *IioUds;
  UINT8                           UncoreBusNumber;
  UINTN                           PciExpressBase;
  UINT32                          CpuFamily;

  //
  // Locate the IIO Protocol Interface
  //
  Status = gBS->LocateProtocol (&gEfiIioUdsProtocolGuid, NULL, &IioUds);
  ASSERT_EFI_ERROR (Status);

  CpuFamily = IioUds->IioUdsPtr->SystemStatus.cpuFamily;
  if( CpuFamily == CPU_FAMILY_BDX_DE  ||
      CpuFamily == CPU_FAMILY_BDX     ||
      CpuFamily == CPU_FAMILY_HSX){

    //Set BaseAddress to MMCFG_BASE
    PciExpressBase = IioUds->IioUdsPtr->PlatformData.PciExpressBase;
    //Add BDF 1:18:0 reg 0 of socket 0
    UncoreBusNumber = IioUds->IioUdsPtr->PlatformData.IIO_resource[0].BusLimit;
    //This will set base address to point to first BDF that will be hidden.
    mIntelSecure.PhyAddr = PciExpressBase + PCI_PCIE_ADDR(/*Bus*/ UncoreBusNumber, /*Device*/ 18, /*Function*/ 0, /*Offset*/ 0);

    //The mask calculated here will inform uCode which bits from the BaseAddress above to ignore.
    //This effectively expands the BaseAddress from a single BDF to cover multiple Buses and Devices.
    mIntelSecure.Phymask = 0xFFFFF000; //Set mask initial value to BIT[31:12]=1 BIT[11:0]=0
    mIntelSecure.Phymask &= ~(BIT17 | BIT15); //Clear these bits to trap on device numbers 18,19,22,23
    mIntelSecure.Phymask &= ~(BIT27 | BIT26 | BIT25); //Also clear these bits to cover sockets 0-7

    DEBUG ((EFI_D_INFO, " - Uncore bus number skt 0 = 0x%x, MMCFG base = 0x%x\n", UncoreBusNumber, PciExpressBase));
    DEBUG ((EFI_D_INFO, " - Intel secure phyaddr = 0x%lx, phymask = 0x%lx\n", mIntelSecure.PhyAddr, mIntelSecure.Phymask));
    DEBUG ((EFI_D_INFO, " - final value = 0x%lx \n", (mIntelSecure.Phymask << 32) + mIntelSecure.PhyAddr));

    DispatchAPAndWait(
        TRUE,
        0,
        UncoreSmbClkCfgHide
    );

    UncoreSmbClkCfgHide(0);

  }
}
