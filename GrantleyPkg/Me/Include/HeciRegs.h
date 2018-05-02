/*++
  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/*++

Copyright (c) 2010-2014 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  HeciRegs.h

Abstract:

  Register definitions for HECI.

--*/
#ifndef _HECI_REGS_H
#define _HECI_REGS_H

/**
 * HECI functions location on PCI bus.
 */
#define HECI1_BUS   0
#define HECI1_DEV   22
#define HECI1_FUN   0

#define HECI2_BUS   0
#define HECI2_DEV   22
#define HECI2_FUN   1


/**
 * HECI PCI config space registers list.
 *
 * Note that HECI Device Id varies between chipset generations and also between
 * client and server chipset SKU.
 * Note that H_GSx registers are host status registers writable for host,
 * read only for ME, and HSF + GS_SHDWx registers are ME status writeable
 * for ME, read only for host side. HFS in HECI-1 is the well known ME Firmware
 * Status 1 register.
 * The definition of the status registers functionality depends on the type of
 * firmwere running in ME.
 */
#define HECI_R_VENDORID  0x00
#define HECI_R_DEVICEID  0x02
#define HECI_R_COMMAND   0x04
#define HECI_R_REVID     0x08
#define HECI_R_MBAR      0x10
#define HECI_R_IRQ       0x3C
#define HECI_R_HIDM      0xA0
#define HECI_R_HFS       0x40
#define HECI_R_MISC_SHDW 0x44
#define HECI_R_GS_SHDW   0x48
#define HECI_R_H_GS      0x4C
#define HECI_R_GS_SHDW2  0x60
#define HECI_R_GS_SHDW3  0x64
#define HECI_R_GS_SHDW4  0x68
#define HECI_R_GS_SHDW5  0x6C
#define HECI_R_H_GS2     0x70
#define HECI_R_H_GS3     0x74
#define HECI_R_MEFS1     HECI_R_HFS // HFS in HECI-1 is ME Firmware Status 1
#define HECI_R_MEFS2     HECI_R_GS_SHDW // GS_SHDW in HECI-1 is ME Firmware Status 2

#define HeciPciReadMefs1()                                                    \
        PciRead32(PCI_LIB_ADDRESS(HECI1_BUS, HECI1_DEV, HECI1_FUN, HECI_R_MEFS1))
#define HeciPciReadMefs2()                                                    \
        PciRead32(PCI_LIB_ADDRESS(HECI1_BUS, HECI1_DEV, HECI1_FUN, HECI_R_MEFS2))

/**
 * HECI command register bits.
 */
#define HECI_CMD_BME     0x04  // Bus Master Enable
#define HECI_CMD_MSE     0x02  // Memory Space Enable

/**
 * Default values to be used in HECI_R_MBAR before PCI enumeration.
 */
#define HECI1_MBAR_DEFAULT 0xFEDB0000
#define HECI2_MBAR_DEFAULT 0xFEDB0010


/**
 * HECI Interrupt Delivery Mode to be set in HECI_R_HIDM.
 */
#define HECI_HIDM_MSI 0
#define HECI_HIDM_SCI 1
#define HECI_HIDM_SMI 2
#define HECI_HIDM_LAST HECI_HIDM_SMI


/**
 * ME Firmware Status 1 register basics.
 *
 * ME Firmware Status 1 register is in HECI-1 configuration space at offset 40h.
 * Full definition of the register depends on type of the firmwere running in ME.
 * The structure HECI_MEFS1 defines only common, basic part.
 */
typedef union
{
  UINT32   DWord;
  struct
  {
    UINT32 CurrentState : 4,  //< 0:3   Current ME firmware state
           Reserved0    : 5,  //  4:8
           InitComplete : 1,  //< 9     ME firmware finished initialization
           Reserved1    : 2,  // 10:11
           ErrorCode    : 4,  //< 12:15 If set means fatal error
           OperatingMode: 4,  //< 16:19 Current ME operating mode
           Reserved2    : 5,  //< 20:24
           MsgAckData   : 3,  //< 25:27 MSG ACK Data specific for acknowledged BIOS message
           MsgAck       : 4;  //< 28:31 Acknowledge for register based BIOS message
  } Bits;
} HECI_MEFS1;

/**
 * HECI_MEFS::CurrentState values list.
 *
 * This field describes the current state of the firmware.
 */
#define MEFS1_CURSTATE_RESET        0  //< ME is in reset, will exit this state within 1 ms
#define MEFS1_CURSTATE_INIT         1  //< ME is initializing, will exit this state within 2 s
#define MEFS1_CURSTATE_RECOVERY     2  //< ME is in recovery mode
#define MEFS1_CURSTATE_DISABLED     4  //< ME functionality has been disabled
#define MEFS1_CURSTATE_NORMAL       5  //< ME is in normal operational state
#define MEFS1_CURSTATE_DISABLE_WAIT 6  //< Not used with SPS
#define MEFS1_CURSTATE_TRANSITION   7  //< ME is transitioning to a new operating State

/**
 * HECI_MEFS::ErrorCode values list.
 *
 * If HECI_MEFS::ErrorCode is set to non zero value the ME firmware has
 * encountered a fatal error and stopped normal operation.
 */
#define MEFS1_ERRCODE_NOERROR       0  //< ME firmware does not report errors
#define MEFS1_ERRCODE_UNKNOWN       1  //< Unkategorized error occured
#define MEFS1_ERRCODE_DISABLED      2  //< ME firmware disabled with for (debug)
#define MEFS1_ERRCODE_IMAGEFAIL     3  //< No valid firmware image in ME region

/**
 * HECI_MEFS1::OperatingMode values list.
 *
 * This field describes the current operating mode of ME.
 */
#define MEFS1_OPMODE_NORMAL         0  // Client firmware is running in ME
#define MEFS1_OPMODE_IGNITION       1  // Ignition firmware is running in ME
#define MEFS1_OPMODE_DEBUG          2  // 
#define MEFS1_OPMODE_TEMP_DISABLE   3  // 
#define MEFS1_OPMODE_SECOVR_JMPR    4  // Security Override activated with jumper
#define MEFS1_OPMODE_SECOVR_MSG     5  // Security Override activated with HMRFPO_ENABLE request
#define MEFS1_OPMODE_SPS           15  // SPS firmware is running in ME


/*
 * MISC_SHDW register in HECI-1 config space at offset 44h
 *
 * If MSVLD bit is not set the register is not implemented.
 * Only in HECI-1 this register is implemented.
 */
typedef union {
  UINT32   DWord;
  struct {
    UINT32 MUSZ     : 6,  // 0:5 - ME UMA Size
           Reserved0:10,  // 6:15 - Reserved
           MUSZV    : 1,  // 16:16 - ME UMA Size Valid
           Reserved1:14,  // 17:30 - Reserved
           MSVLD    : 1;  // 31:31 - Miscellaneous Shadow Valid
  } Bits;
} HECI_MISC_SHDW;

/**
 * HECI message header.
 *
 * HECI massage header is one double word long. It identifies communication
 * entities (subsystems) on ME and host side and provides the exact number
 * of bytes in the message body following this header.
 */
typedef union
{
  UINT32   DWord;
  struct
  {
    UINT32 MeAddress  : 8,  ///< Addressee on ME side
           HostAddress: 8,  ///< Addressee on host siede, zero for BIOS
           Length     : 9,  ///< Number of bytes following the header
           Reserved   : 6,
           MsgComplete: 1;  ///< Whether this is last fragment of a message
  } Bits;
} HECI_MSG_HEADER;

/**
 * Macro for building HECI message header dword using given ingredients.
 */
#define HeciMsgHeader(MeAdr, HstAdr, Len, Cpl) \
        (UINT32)(((MeAdr) & 0xFF) | ((HstAdr) & 0xFF) << 8 | ((Len) & 0x1FF) << 16 | ((Cpl) << 31))

/**
 * Maximum length of HECI message.
 *
 * Actually it is maximum length of HECI queue that can be configured by ME.
 * Single message must not exceed HECI queue size. Current HECI queue size is
 * configured by ME, so this macro does not define current maximum message
 * length. It defines maximum length in case ME configures maximum queue size.
 */
#define HECI_MSG_MAXLEN (0x80 * sizeof(UINT32))

#endif // HECI_REGS_H

