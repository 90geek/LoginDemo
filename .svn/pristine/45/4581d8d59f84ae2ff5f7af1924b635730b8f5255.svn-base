//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Tools/template.h 6     1/13/10 2:13p Felixp $
//
// $Revision: 6 $
//
// $Date: 1/13/10 2:13p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Tools/template.h $
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
/** @file TbtCommon.h
    this header file define all necessary definition for Thunderbolt 
    module on different platforms

**/
//**********************************************************************
#ifndef __TBT_COMMOM__H__
#define __TBT_COMMOM__H__
#ifdef __cplusplus
extern "C" {
#endif

//********************************************************
//          Chipset related GUID defintion
//********************************************************
#if defined TBT_HIGHLAND_PLATFORM_CONFIG && TBT_HIGHLAND_PLATFORM_CONFIG == 1
#ifndef gReadyForLockProtocolGuid
#define READY_FOR_LOCK_PROTOCOL_GUID { 0x8d6f1add, 0x45a5, 0x45a8, { 0x8b, 0xb8, 0x0c, 0x3a, 0x95, 0x31, 0x48, 0xfa }}
static  EFI_GUID gReadyForLockProtocolGuid = READY_FOR_LOCK_PROTOCOL_GUID;
#endif
#endif // TBT_HIGHLAND_PLATFORM_CONFIG

//********************************************************
//            Chipset related defintion
//********************************************************
#ifndef PCI_DEVICE_NUMBER_PCH_LPC
#define PCI_DEVICE_NUMBER_PCH_LPC    31
#endif

#ifndef PCI_FUNCTION_NUMBER_PCH_LPC
#define PCI_FUNCTION_NUMBER_PCH_LPC  0
#endif

#ifndef PMC_BASE_ADDRESS
#define PMC_BASE_ADDRESS             0
#endif

#ifndef R_PCH_PMC_PM_CFG
#define R_PCH_PMC_PM_CFG             0x08
#endif

#ifndef R_PCH_RCRB_PM_CFG
#define R_PCH_RCRB_PM_CFG            0x3318
#endif

#ifndef R_PCH_LPC_PMC_BASE
#define R_PCH_LPC_PMC_BASE           0x44
#endif

#ifndef R_PCH_LPC_GPI_ROUT
#define R_PCH_LPC_GPI_ROUT           0xB8
#endif

#ifndef R_PCH_PMC_GPI_ROUT
#define R_PCH_PMC_GPI_ROUT           0x58
#endif

//#ifndef PCIEX_BASE_ADDRESS
//#define PCIEX_BASE_ADDRESS           0xE0000000
//#endif

//#ifdef PCIEX_BASE_ADDRESS 
#ifdef NB_PCIE_CFG_ADDRESS
#define TBT_CFG_ADDRESS(bus, dev, func, reg) NB_PCIE_CFG_ADDRESS(bus, dev, func, reg)
#else
#define TBT_CFG_ADDRESS(bus, dev, func, reg) \
    ((VOID*) (UINTN)(PcdGet64 (PcdPciExpressBaseAddress) + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg))
#endif
//#endif

//********************************************************
//               PCIE related defintion
//********************************************************
#ifndef R_PCH_PCIE_CLS
#define R_PCH_PCIE_CLS               0x0C
#endif

#ifndef R_PCH_PCIE_SLSTS
#define R_PCH_PCIE_SLSTS             0x5A
#endif

#ifndef B_PCH_PCIE_SLSTS_PDS
#define B_PCH_PCIE_SLSTS_PDS         BIT06
#endif

#ifndef R_PCH_PCIE_PMCS
#define R_PCH_PCIE_PMCS              0xA4
#endif

#ifndef B_PCH_PCIE_PMCS_PS
#define B_PCH_PCIE_PMCS_PS           (BIT1 | BIT0)
#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
