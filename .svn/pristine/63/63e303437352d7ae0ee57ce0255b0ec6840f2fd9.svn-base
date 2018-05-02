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
//*************************************************************************

/** @file AmiTbtHrStatus.h
    AMI Thunderbolt HR Status header file, define all the Thunderbolt 
    HR Status equates and structures in this file.

**/

#ifndef _AMI_TBT_HR_STATUS_H_
#define _AMI_TBT_HR_STATUS_H_

#define AMI_TBT_HR_STATUS_GUID { 0xba1d893b, 0x803e, 0x4b26, { 0xa3, 0xde, 0x58, 0x57, 0x3, 0xff, 0x7b, 0xd6 } }

#define TBT_HR_STATUS_VARIABLE L"TbtHRStatusVar"

#define RR_PCIE2TBT 0x54C   ///< Thunderbolt FW PCIE to TBT register

#define RR_TBT2PCIE 0x548   ///< Thunderbolt FW TBT to PCIE register

#define PCIE2TBT_VLD_B 1

#define TBT2PCIE_DON_R 1

#define MASK_DATA (BIT08 | BIT09 | BIT10 | BIT11)

#define MASK_ERROR (BIT12 | BIT13 | BIT14 | BIT15)

typedef enum {
    Cactus_Ridge = 1,
    Redwood_Ridge,
    Falcon_Ridge,
    BDW_TBT_LP
} TBT_HOST_SERIES;

typedef enum {
    TBT_CR_NORMAL_MODE = 1,
    TBT_CR_NORMAL_MODE_WO_NHI,
    TBT_CR_DIRECT_CONNECTED_WO_NHI,
    TBT_CR_REDRIVER_ONLY,
    TBT_CR_OFF_MODE,
    TBT_CR_DEBUG_MODE,
    TBT_LEGACY_CONNECTION = 0,
    TBT_UNIQUIE_ID,
    TBT_ONE_TIME_SAVED_KEY,
    TBT_DPPLUS
} TBT_SECURITY_TYPE;

typedef enum {
    TBT_GO2SX_WITH_WAKE = 2,
    TBT_GO2SX_NO_WAKE,
    TBT_SX_EXIT_TBT_CONNECTED,
    TBT_SX_EXIT_NO_TBT_CONNECTED,
    TBT_OS_UP,
    TBT_SET_SECURITY_LEVEL = 8,
    TBT_GET_SECURITY_LEVEL
} TBT_COMMOND;

typedef enum {
    TBT_SB_D28_F0 = 0,
    TBT_SB_D28_F1,
    TBT_SB_D28_F2,
    TBT_SB_D28_F3,
    TBT_SB_D28_F4,
    TBT_SB_D28_F5,
    TBT_SB_D28_F6,
    TBT_SB_D28_F7,
    
    TBT_SB_D29_F0 = 8,
    TBT_SB_D29_F1,
    TBT_SB_D29_F2,
    TBT_SB_D29_F3,
    TBT_SB_D29_F4,
    TBT_SB_D29_F5,
    TBT_SB_D29_F6,
    TBT_SB_D29_F7,
    
    TBT_SB_D27_F0 = 16,
    TBT_SB_D27_F1,
    TBT_SB_D27_F2,
    TBT_SB_D27_F3
} TBT_HOST_SB_PCIE_LOCATION;

typedef enum {
    TBT_CPU0_NB_D01_F0 = 0x20,
    TBT_CPU0_NB_D01_F1,
    TBT_CPU0_NB_D01_F2,
    TBT_CPU0_NB_D02_F0 = 0x24,
    TBT_CPU0_NB_D02_F1,
    TBT_CPU0_NB_D02_F2,
    TBT_CPU0_NB_D02_F3,
    TBT_CPU0_NB_D03_F0 = 0x28,
    TBT_CPU0_NB_D03_F1,
    TBT_CPU0_NB_D03_F2,
    TBT_CPU0_NB_D03_F3,
    
    TBT_CPU1_NB_D01_F0 = 0x30,
    TBT_CPU1_NB_D01_F1,
    TBT_CPU1_NB_D01_F2,
    TBT_CPU1_NB_D02_F0 = 0x34,
    TBT_CPU1_NB_D02_F1,
    TBT_CPU1_NB_D02_F2,
    TBT_CPU1_NB_D02_F3,
    TBT_CPU1_NB_D03_F0 = 0x38,
    TBT_CPU1_NB_D03_F1,
    TBT_CPU1_NB_D03_F2,
    TBT_CPU1_NB_D03_F3,
    
    TBT_CPU2_NB_D01_F0 = 0x40,
    TBT_CPU2_NB_D01_F1,
    TBT_CPU2_NB_D01_F2,
    TBT_CPU2_NB_D02_F0 = 0x44,
    TBT_CPU2_NB_D02_F1,
    TBT_CPU2_NB_D02_F2,
    TBT_CPU2_NB_D02_F3,
    TBT_CPU2_NB_D03_F0 = 0x48,
    TBT_CPU2_NB_D03_F1,
    TBT_CPU2_NB_D03_F2,
    TBT_CPU2_NB_D03_F3,
    
    TBT_CPU3_NB_D01_F0 = 0x50,
    TBT_CPU3_NB_D01_F1,
    TBT_CPU3_NB_D01_F2,
    TBT_CPU3_NB_D02_F0 = 0x54,
    TBT_CPU3_NB_D02_F1,
    TBT_CPU3_NB_D02_F2,
    TBT_CPU3_NB_D02_F3,
    TBT_CPU3_NB_D03_F0 = 0x58,
    TBT_CPU3_NB_D03_F1,
    TBT_CPU3_NB_D03_F2,
    TBT_CPU3_NB_D03_F3,
} TBT_HOST_NB_PCIE_LOCATION;

typedef struct _AMI_TBT_HR_STATUS_DATA {
    UINT8                   TbtHRSeries;    ///< Record Thunderbolt host chip series.
    UINT8                   TbtHRStatus;    ///< Record Thunderbolt host previous status.
} AMI_TBT_HR_STATUS_DATA;

extern EFI_GUID gAmiTbtHrStatusGuid;

#endif // _AMI_TBT_HR_STATUS_H_
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
