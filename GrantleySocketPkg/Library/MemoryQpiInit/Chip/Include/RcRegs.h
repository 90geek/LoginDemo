//
// This file contains an 'Intel Pre-EFI Module' and is licensed
// for Intel CPUs and Chipsets under the terms of your license
// agreement with Intel or your vendor.  This file may be
// modified by the user, subject to additional terms of the
// license agreement
//
#ifndef _rcregs_h
#define _rcregs_h

#include "CBOBC_COH.h"
#include "CBOBC_IOSAD.h"
#include "CBOBC_MEMSAD.h"
#include "CBO_CFG.h"
#include "HA_CFG.h"
#include "HA_DFX.h"
#include "HA_GDXC.h"
#include "HA_PMON.h"
#include "IIOCB_FUNC0.h"
#include "IIOCB_FUNC1.h"
#include "IIOCB_FUNC2.h"
#include "IIOCB_FUNC3.h"
#include "IIOCB_FUNC4.h"
#include "IIOCB_FUNC5.h"
#include "IIOCB_FUNC6.h"
#include "IIOCB_FUNC7.h"
#include "IIO_DFX.h"
#include "IIO_DFX_GLOBAL.h"
#include "IIO_DFX_VTD.h"
#include "IIO_PCIEDMI.h"
#include "IIO_IOAPIC.h"
#include "IIO_PCIE.h"
#include "IIO_PCIENTB.h"
#include "IIO_PERFMON.h"
#include "IIO_RAS.h"
#include "IIO_VTD.h"
#include "IIO_MEMHP.h"
#include "MCDDC_CTL.h"
#include "MCDDC_DESC.h"
#include "MCDDC_DP.h"
#include "MCIO_DDRIO.h"
#include "MCIO_DDRIOEXT.h"
#include "MCIO_DDRIOEXTGBC.h"
#include "MCIO_DDRIOEXTMCC.h"
#include "MCIO_DDRIOGBC.h"
#include "MCIO_DDRIOMCC.h"
#include "MC_MAIN.h"
#include "MC_MAINEXT.h"
#include "PCU_FUN0.h"
#include "PCU_FUN1.h"
#include "PCU_FUN2.h"
#include "PCU_FUN3.h"
#include "PCU_FUN4.h"
#include "PCU_FUN5.h"
#include "PCU_FUN6.h"
#include "PCU_FUN7.h"
#include "QPIAGENT_DFX_CIO.h"
#include "QPIAGENT_DFX_COMMON.h"
#include "QPIAGENT_DFX_LINK.h"
#include "QPIAGENT_DFX_PHY.h"
#include "QPIAGENT_DFX_PHY_IOVB.h"
#include "QPIAGENT_DFX_PHY_IOVC.h"
#include "QPIAGENT_DFX_PHY_PQD.h"
#include "QPIAGENT_LL.h"
#include "QPIAGENT_PMON.h"
#include "QPIAGENT_REUT.h"
#include "R2PCIE_CFG.h"
#include "R2PCIE_PMON.h"
#include "R3QPI_CFG.h"
#include "R3QPI_LNK0PMON.h"
#include "R3QPI_LNK1PMON.h"
#include "UBOX_CFG.h"
#include "UBOX_DFX.h"
#include "UBOX_MISC.h"
#include "VCU_FUN_0.h"
#include "VCU_FUN_2.h"
#include "SBO_CFG.h"
#include "CB33_FUN_0.h"
#include "GbE_PF0.h"
#include "GbE_VF0.h"
#include "IIO_DFX_IOSF0.h"
#include "IIO_DFX_IOSF2.h"
#include "IIO_PCIEIOSF0.h"
#include "IIO_PCIEIOSF2.h"
#include "PCU_PMC.h"

// Registers not defined in ConfigDB -- START
// Scratch register usage
//

#ifndef ASM_INC
// register at B:D:F: 1:11:0, box:function 8:0 (UBOX_CFG) , offset 0xB0. with SoftSDV/VP flag
// Scratch register usage
//
#define CSR_EMULATION_FLAG_UBOX_CFG_REG 0x080040B0

//
// For BDX, this register changed to B:D:F 0:0:0, box:function 14:0, offset 0xFC.
//
#define CSR_BDX_EMULATION_FLAG_CFG_REG  0x0e0040FC 

//#define   EMULATION_INFO_UBOX_CFG_REG   0x401580B0
#define   EMULATION_INFO_UBOX_CFG_REG     0x080040B0

// Registers not defined in ConfigDB -- END


//
// ConfigDB has as SV ONLY, but shouldnt be -- START
//

#define   UNKNOWN1_0_6_7_CFG_REG   0x40037640
#endif // ASM_INC

#endif //_rcregs_h

