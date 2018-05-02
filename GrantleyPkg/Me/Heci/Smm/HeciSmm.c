/*++
  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/*++

Copyright (c)  2008 - 2014 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  HeciSmm.c

Abstract:

  SMM HECI driver.
  This driver is reusing HECI-1 with DXE driver and later with OS driver.
  Thus it may not set SMI interrupt mode in HIDM and may do only simple
  request-response transactions, using unfragmented messages.

--*/

#include <Library/UefiLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
//AptioV Server Override Start : Adding Libraries
#include <Library\SmmServicesTableLib.h>	
#include <Library\UefiBootServicesTableLib.h>
//AptioV Server Override End : Adding Libraries

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/HeciCoreLib.h>

#include <Protocol/Smmbase.h>
#include <Protocol/SmmRtProtocol.h>
#include <Protocol/HeciSmm.h>
#include "Protocol/HeciProtocol.h"  // AptioV Server Override: EFI_SMM_HECI_PROTOCOL structure change conflict resolution

//AptioV server override start: dynamic MMCFG base change support.
#ifdef DYNAMIC_MMCFG_BASE_FLAG 
#include <PchSmmAccess.h> //AptioV server override: Support for Dynamic MMCFG. Do not USe PCIe PCD in SMM since PCD SMM is unavailable.
#else
#include <PchAccess.h>
#endif
//AptioV server override end: dynamic MMCFG base change support.
#include <HeciRegs.h>
#include <Platform.h>
#include <PchRegs/PchRegsRcrb.h>

BOOLEAN  gHeciSmmExecution; //AptioV Server override: Fix for tpl assert issue with AFUDOS ME update.

//AptioV Server override - Start: Clear Heci2 buffer before handoff to OS
#include "AcpiModeEnable.h"
#include "MeAccess.h"
#include <Library/TimerLib.h>
//AptioV Server override - End: Clear Heci2 buffer before handoff to OS

/*****************************************************************************
 * Local definitions.
 *****************************************************************************/


/*****************************************************************************
 * Local function prototypes.
 *****************************************************************************/
EFI_STATUS EFIAPI SmmHeciInit(IN OUT EFI_SMM_HECI_PROTOCOL *pThis,
                              IN OUT UINT32                *pTimeout);
EFI_STATUS EFIAPI SmmHeciQueReset(IN OUT EFI_SMM_HECI_PROTOCOL *pThis,
                                  IN OUT UINT32                *pTimeout);
EFI_STATUS EFIAPI SmmHeciQueState(IN OUT EFI_SMM_HECI_PROTOCOL *pThis,
                                     OUT BOOLEAN               *pIsReady,
                                     OUT UINT32                *pSendQue,
                                     OUT UINT32                *pRecvQue);
EFI_STATUS EFIAPI SmmHeciRequest(IN OUT EFI_SMM_HECI_PROTOCOL *pThis,
                                 IN OUT UINT32                *pTimeout,
                                 IN     HECI_MSG_HEADER       *pReqMsg,
                                    OUT HECI_MSG_HEADER       *pRspBuf,
                                 IN     UINT32                *pBufLen);


/*****************************************************************************
 * Variables.
 *****************************************************************************/
EFI_SMM_HECI_PROTOCOL     *pSmmHeci;  // AptioV Server Override: EFI_SMM_HECI_PROTOCOL structure change conflict resolution

/*****************************************************************************
 * Public functions.
 *****************************************************************************/
/**
 * SMM HECI driver entry point.
 *
 * param[in] ImageHandle    Handle of driver image
 * param[in] pSysTable      Pointer to the system table
 *
 * return EFI_STATUS is returned.
 */
/*
//AptioV Server override - Start: Clear Heci2 buffer before handoff to OS
static EFI_GUID gEfiAcpiEnDispatchProtocolGuid = EFI_ACPI_EN_DISPATCH_PROTOCOL_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   MEAcpiEnableLink
//
// Description: This routine will be called when ACPI mode is enabled.
//  Pending data in HECI2 buffer is cleared before handoff to the OS.
//
// Parameters:  DispatchHandle - SMM Dispatch Handle
//
// Returns:     None
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
MEAcpiEnableLink (
  IN EFI_HANDLE   DispatchHandle
)
{
    UINT64      Heci2Bar;
    UINT32      Data, Length; 
    volatile HECI_ME_CONTROL_REGISTER HeciRegMeCsrHa;

    //
    // Return if HECI2 device is disabled
    //
    if ( Heci2PciRead16(PCI_VENDOR_ID_OFFSET) != 0x8086 ) {
        return;
    }

    // Read MBAR
    Heci2Bar = ((Heci2PciRead32(R_HECIMBAR) & ~0xF) |\
                            (UINT64)Heci2PciRead32(R_HECIMBAR + 4) << 32);

    HeciRegMeCsrHa.ul = Mmio32(Heci2Bar, ME_CSR_HA);
    Length = HeciRegMeCsrHa.r.ME_CBWP_HRA - HeciRegMeCsrHa.r.ME_CBRP_HRA;
    while ( Length!=0 )
    {
        Data = Mmio32(Heci2Bar, ME_CB_RW);
        HeciRegMeCsrHa.ul = Mmio32(Heci2Bar, ME_CSR_HA);
        Length = HeciRegMeCsrHa.r.ME_CBWP_HRA - HeciRegMeCsrHa.r.ME_CBRP_HRA;
        MicroSecondDelay (0x500);
    }

}

EFI_STATUS
EFIAPI
CreateMEAcpiEnLink (
    IN CONST EFI_GUID  *Protocol,
    IN VOID            *Interface,
    IN EFI_HANDLE      Handle )
{
    EFI_STATUS                      Status;
    EFI_HANDLE                      RegisterHandle = NULL;
    EFI_ACPI_DISPATCH_PROTOCOL      *AcpiEnDispatch;

    Status = gSmst->SmmLocateProtocol (
                    &gEfiAcpiEnDispatchProtocolGuid,
                    NULL,
                    (VOID **)&AcpiEnDispatch );
    if ( EFI_ERROR (Status) ) {
        return Status;
    }

    Status = AcpiEnDispatch->Register(
                                AcpiEnDispatch,
                                MEAcpiEnableLink,
                                &RegisterHandle );

    return Status;
}
//AptioV Server override - End: Clear Heci2 buffer before handoff to OS
*///AptioV server Override todo

//
//Aptio V Server Override Start: EFI_SMM_HECI_PROTOCOL structure change conflict resolution
//

HECI_DEVICE   *mHeciDev;

static HECI_MSG_HEADER mHeciDxeMsgBuffer[HECI_MSG_MAXLEN / sizeof(HECI_MSG_HEADER)];

/**
 * Sends one message through the HECI and wait for the response message.
 *
 * This function sends one message to ME through HECI circular buffer and
 * waits for one message recived from ME. It does not guarantee that the
 * received message is response to the send message.
 * 
 * @param[in,out] Message     Pointer to the message buffer
 * @param[in]     SendLength  Length in bytes of the message to send
 * @param[in,out] RecvLength  Length of the buffer for received message
 * @param[in]     HostAddress Address of the sending entity
 * @param[in]     MeAddress   Address of the ME entity receiving the message
 *
 * @returns EFI_STATUS is returned.
 */
EFI_STATUS EFIAPI
SmmHeciSendwACK(
  IN OUT  UINT32 *Message,
  IN      UINT32  SendLength,
  IN OUT  UINT32 *RecvLength,
  IN      UINT8   HostAddress,
  IN      UINT8   MeAddress)
{
  EFI_STATUS  Status;
  UINT32      i, Retry, Timeout, FrgLen;
  UINT8       *pMsg = (UINT8*)Message;
  
  if (Message == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  mHeciDxeMsgBuffer[0].DWord = 0;
  mHeciDxeMsgBuffer[0].Bits.MeAddress = MeAddress;
  mHeciDxeMsgBuffer[0].Bits.HostAddress = HostAddress;
  //
  // Fragment the message into queue-sized packets
  //
  ASSERT(mHeciDev->HMtu > 0); // make sure HECI is initialized when sending

    if (SendLength <= mHeciDev->HMtu)
    {
      mHeciDxeMsgBuffer[0].Bits.Length = SendLength;
      mHeciDxeMsgBuffer[0].Bits.MsgComplete = 1; // Set message complete in last fragment
    }
    else
    {
// The Message of lenght more than "mHeciDev->HMtu" is not supported in "HeciSendwACK".
      ASSERT(SendLength <= mHeciDev->HMtu);
      return EFI_INVALID_PARAMETER;
    }
    for (i = 0; i < mHeciDxeMsgBuffer[0].Bits.Length; i++)
    {
      ((UINT8*)&mHeciDxeMsgBuffer[1])[i] = pMsg[i];
    }
    Retry = HECI_MAX_RETRY;
    do
    {
      Timeout = HECI_SEND_TIMEOUT / HECI_TIMEOUT_UNIT;
      FrgLen = sizeof(mHeciDxeMsgBuffer);
      Status = pSmmHeci->HeciRequest(pSmmHeci, &Timeout, &mHeciDxeMsgBuffer[0], &mHeciDxeMsgBuffer[0], &FrgLen);
    }
    while (EFI_ERROR(Status) && Retry-- > 0);
    if (EFI_ERROR(Status))
    {
      goto GetOut;
    }
    else if (NULL != RecvLength)
    {
      FrgLen -= sizeof(HECI_MSG_HEADER);
      if (FrgLen > *RecvLength)
      {
        FrgLen = *RecvLength;
      }
      for (i = 0; i < FrgLen; i++)
      {
        ((UINT8*)Message)[i] = ((UINT8*)&mHeciDxeMsgBuffer[1])[i];
      }
      *RecvLength = FrgLen;
    }
  
GetOut:
  return Status;

} // SmmHeciSendwACK()

EFI_STATUS EFIAPI
SmmHeciReInitialize(VOID)
{
  UINT32 Timeout = HECI_INIT_TIMEOUT / HECI_TIMEOUT_UNIT;
  
  return pSmmHeci->HeciInit(pSmmHeci, &Timeout);
}

/**
 * Read one message from HECI, wait for it if needed.
 *
 * @param[in]     Blocking    Whether the function should wait for message
 * @param[out]    Message     Buffer for the received message
 * @param[in,out] Length      Length of the buffer/message
 *
 * @returns EFI_STATUS is returned.
 */
EFI_STATUS EFIAPI
HeciReceive (
  IN      UINT32  Blocking,
  IN OUT  UINT32 *MessageBody,
  IN OUT  UINT32 *Length)
{
  EFI_STATUS      Status;
  UINT32          i, Timeout, FrgLen, MsgLen;
  
  if (MessageBody == NULL || Length == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  Timeout = (Blocking) ? (HECI_READ_TIMEOUT / HECI_TIMEOUT_UNIT) : 0;
  MsgLen = 0;
  do
  {
    FrgLen = sizeof(mHeciDxeMsgBuffer);
    Status = HeciMsgRecv(mHeciDev, &Timeout,
                         &mHeciDxeMsgBuffer[0], &FrgLen);
    if (EFI_ERROR(Status))
    {
      break;
    }
    else
    {
      FrgLen -= sizeof(HECI_MSG_HEADER);
      if (MsgLen + FrgLen > *Length)
      {
        FrgLen = *Length - MsgLen;
      }
      for (i = 0; i < FrgLen; i++)
      {
        ((UINT8*)MessageBody)[MsgLen++] = ((UINT8*)&mHeciDxeMsgBuffer[1])[i];
      }
    }
  }
  while (!mHeciDxeMsgBuffer[0].Bits.MsgComplete);
  
  *Length = MsgLen;
  return Status;
} // HeciReceive()


/**
 * Function sends one message (of any length) through the HECI circular buffer.
 *
 * @param[in] Message              Pointer to the message data to be sent.
 * @param[in] Length               Length of the message in bytes.
 * @param[in] HostAddress          The address of the host processor.
 * @param[in] MeAddress            Address of the ME subsystem the message is being sent to.
 *
 * @return EFI_STATUS is returned.
 */
EFI_STATUS EFIAPI
HeciSend(
  IN     UINT32 *Message,
  IN     UINT32  Length,
  IN     UINT8   HostAddress,
  IN     UINT8   MeAddress)
{
  EFI_STATUS  Status;
  UINT32      i, Retry, Timeout;
  UINT8       *pMsg = (UINT8*)Message;
  
  if (Message == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  mHeciDxeMsgBuffer[0].DWord = 0;
  mHeciDxeMsgBuffer[0].Bits.MeAddress = MeAddress;
  mHeciDxeMsgBuffer[0].Bits.HostAddress = HostAddress;
  //
  // Fragment the message into queue-sized packets and loop until completely sent
  //
  ASSERT(mHeciDev->HMtu > 0); // make sure HECI is initialized when sending
  do
  {
    if (Length <= mHeciDev->HMtu)
    {
      mHeciDxeMsgBuffer[0].Bits.Length = Length;
      mHeciDxeMsgBuffer[0].Bits.MsgComplete = 1; // Set message complete in last fragment
    }
    else
    {
      mHeciDxeMsgBuffer[0].Bits.Length = mHeciDev->HMtu;
    }
    for (i = 0; i < mHeciDxeMsgBuffer[0].Bits.Length; i++)
    {
      ((UINT8*)&mHeciDxeMsgBuffer[1])[i] = pMsg[i];
    }
    pMsg += mHeciDxeMsgBuffer[0].Bits.Length;
    Length -= mHeciDxeMsgBuffer[0].Bits.Length;
    Retry = HECI_MAX_RETRY;
    do
    {
      Timeout = HECI_SEND_TIMEOUT / HECI_TIMEOUT_UNIT;
      Status = HeciMsgSend(mHeciDev, &Timeout, &mHeciDxeMsgBuffer[0]);
    }
    while (EFI_ERROR(Status) && Retry-- > 0);
    if (EFI_ERROR(Status))
    {
      goto GetOut;
    }
  }
  while (Length > 0);
  
GetOut:
  return Status;
} // HeciSendMsg()


//
//Aptio V Server Override End : EFI_SMM_HECI_PROTOCOL structure change conflict resolution
//
EFI_STATUS
SmmHeciEntryPoint(
  IN     EFI_HANDLE          ImageHandle,
  IN     EFI_SYSTEM_TABLE   *pSysTable)
{
#if 0
    return EFI_UNSUPPORTED;
#else
  EFI_STATUS                 Status;
  BOOLEAN                    InSmm;
  EFI_SMM_BASE2_PROTOCOL    *pSmmBase;
 // EFI_SMM_RUNTIME_PROTOCOL  *pSmmRt;//AptioV server override
  EFI_SMM_SYSTEM_TABLE2     *pSmst;
  EFI_HANDLE                 Handle;


  gHeciSmmExecution = TRUE; //AptioV Server override: Fix for tpl assert issue with AFUDOS ME update.

  Status = gBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &pSmmBase);
  if (EFI_ERROR(Status))
  {
    ASSERT(FALSE);
    return Status;
  }

  InSmm = FALSE;
  pSmmBase->InSmm(pSmmBase, &InSmm);
  if (!InSmm)
  {
    return EFI_UNSUPPORTED;
  }

//AptioV Server Override Start : AMI BIOS does not produce SmmRuntime protocol
/*
  Status = gBS->LocateProtocol(&gEfiSmmRuntimeProtocolGuid, NULL, &pSmmRt);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return Status;
    }
*/
//AptioV Server Override End : AMI BIOS does not produce SmmRuntime protocol
    //
    // Create database record and add to database
    //
  Status = pSmmBase->GetSmstLocation(pSmmBase, &pSmst);
  if (EFI_ERROR (Status))
  {
    ASSERT(FALSE);
    return Status;
  }
  Status = pSmst->SmmAllocatePool(EfiRuntimeServicesData, sizeof(*pSmmHeci), &(VOID*)pSmmHeci);
  if (EFI_ERROR(Status))
  {
    ASSERT(FALSE);
    return Status;
  }
  //
  // Initialize SMM HECI protocol data
  //
  pSmmHeci->HeciDev.Bus = HECI1_BUS;
  pSmmHeci->HeciDev.Dev = HECI1_DEV;
  pSmmHeci->HeciDev.Fun = HECI1_FUN;
  pSmmHeci->HeciDev.Hidm = HECI_HIDM_MSI;
  pSmmHeci->HeciDev.Mbar = HECI1_MBAR_DEFAULT;
  pSmmHeci->HeciInit = (SMM_HECI_INIT)SmmHeciInit;
  pSmmHeci->HeciQueReset = (SMM_HECI_QUE_RESET)SmmHeciQueReset;
  pSmmHeci->HeciQueState = (SMM_HECI_QUE_STATE)SmmHeciQueState;
  pSmmHeci->HeciRequest = (SMM_HECI_REQUEST)SmmHeciRequest;
  pSmmHeci->SendwACK = (EFI_HECI_SENDWACK)SmmHeciSendwACK; // AptioV Server Override: EFI_SMM_HECI_PROTOCOL structure change conflict resolution
  pSmmHeci->ReInitHeci = (EFI_HECI_REINIT)SmmHeciReInitialize; // AptioV Server Override: EFI_SMM_HECI_PROTOCOL structure change conflict resolution
  pSmmHeci->ReadMsg = (EFI_HECI_READ_MESSAGE)HeciReceive;  // AptioV Server Override: EFI_SMM_HECI_PROTOCOL structure change conflict resolution
  pSmmHeci->SendMsg = (EFI_HECI_SEND_MESSAGE)HeciSend; // AptioV Server Override: EFI_SMM_HECI_PROTOCOL structure change conflict resolution
  
  mHeciDev = &pSmmHeci->HeciDev; // AptioV Server Override: EFI_SMM_HECI_PROTOCOL structure change conflict resolution
  Handle = NULL;
  //
  // Install the SMM HECI API
  //
  Status = pSmst->SmmInstallProtocolInterface(&Handle, &gSmmHeciProtocolGuid,
                                              EFI_NATIVE_INTERFACE, pSmmHeci);
  DEBUG ((DEBUG_INFO, "Smm Heci Protocol install Status: %r\n", Status)); // AptioV Server Override: EFI_SMM_HECI_PROTOCOL structure change conflict resolution

  if (EFI_ERROR(Status))
  {
    ASSERT(FALSE);
    pSmst->SmmFreePool(pSmmHeci);
  }
  SmmHeciInit(pSmmHeci, NULL);
  DEBUG((EFI_D_ERROR, "[HECI]: SMM driver installed\n"));
  
  return Status;


/*
//AptioV Server override - Start: Clear Heci2 buffer before handoff to OS
  if ( !EFI_ERROR(Status) ) {
      VOID        *AcpiReg;
      EFI_STATUS    Status1;

      Status1 = gSmst->SmmRegisterProtocolNotify (
                      &gEfiAcpiEnDispatchProtocolGuid,
                      CreateMEAcpiEnLink,
                      &AcpiReg
                      );
  }
//AptioV Server override - End: Clear Heci2 buffer before handoff to OS
*/
  return Status;
  #endif
} // SmmHeciEntryPoint()


/**
 * Initialize HECI interface.
 *
 * This function initializes host side of HECI interface. If timeout is
 * greater than zero it also waits until ME is ready to receive messages.
 *
 * @param[in,out] pThis     Pointer to protocol structure
 * @param[in,out] pTimeout  On input timeout in ms, on exit time left
 */
EFI_STATUS EFIAPI SmmHeciInit(
  IN     EFI_SMM_HECI_PROTOCOL *pThis,
  IN OUT UINT32                *pTimeout)
{
  EFI_STATUS  Status;
  UINT32      Fd2;
  
  //
  // Make sure HECI-1 is visible on PCI. It may be hidden for basic ME firmware.
  //
  Fd2 = MmioRead32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2);
  MmioWrite32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2, Fd2 & ~B_PCH_RCRB_FD2_MEI1D);
  
  Status = HeciInit(&pThis->HeciDev, pTimeout);
  //
  // Restore HECI-1 hiding state
  //
  MmioWrite32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2, Fd2);
  
  return Status;
} // SmmHeciInit()


/**
 * Reset HECI queue.
 *
 * This function resets HECI queue. If timeout is greater than zero it also
 * waits until ME is ready to receive messages.
 *
 * @param[in,out] pThis     Pointer to protocol data
 * @param[in,out] pTimeout  On input timeout in us, on exit time left
 */
EFI_STATUS EFIAPI SmmHeciQueReset(
  IN     EFI_SMM_HECI_PROTOCOL *pThis,
  IN OUT UINT32                *pTimeout)
{
  EFI_STATUS  Status;
  UINT32      Fd2;
  
  //
  // Make sure HECI-1 is visible on PCI. It may be hidden for basic ME firmware.
  //
  Fd2 = MmioRead32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2);
  MmioWrite32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2, Fd2 & ~B_PCH_RCRB_FD2_MEI1D);
  
  Status = HeciQueReset(&pThis->HeciDev, pTimeout);
  //
  // Restore HECI-1 hiding state
  //
  MmioWrite32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2, Fd2);
  
  return Status;
} // SmmHeciReset()


/**
 * Get HECI queue state.
 *
 * This function reads HECI queue state. It informs whether queue is ready for
 * communication, and whether there are some dwords in send or receive queue.
 * If SmmHeciRequest() is called and queue is not empty reset is done to clear
 * it. SmmHeciQueState() may be used to detect this situation and if possible
 * delay the SMM request, so that OS driver can finish its transaction.
 *
 * @param[in,out] pThis     Pointer to protocol data
 * @param[in,out] pTimeout  On input timeout in us, on exit time left
 */
EFI_STATUS EFIAPI SmmHeciQueState(
  IN OUT EFI_SMM_HECI_PROTOCOL *pThis,
     OUT BOOLEAN               *pIsReady,
     OUT UINT32                *pSendQue,
     OUT UINT32                *pRecvQue)
{
  EFI_STATUS  Status;
  UINT32      Fd2;
  
  //
  // Make sure HECI-1 is visible on PCI. It may be hidden for basic ME firmware.
  //
  Fd2 = MmioRead32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2);
  MmioWrite32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2, Fd2 & ~B_PCH_RCRB_FD2_MEI1D);
  
  Status = HeciQueState(&pThis->HeciDev, pIsReady, pSendQue, pRecvQue);
  //
  // Restore HECI-1 hiding state
  //
  MmioWrite32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2, Fd2);
  
  return Status;
} // SmmHeciQueState()


/**
 * Send request message to HECI queue, wait for response if needed.
 *
 * This function writes one message to HECI queue and - if receive buffer
 * was provided and timeout is greater than zero - waits for response message.
 * Fragmentation is not supported. Reqeust and response must be unfragmented.
 * Size of receive message buffer is given in bytes in (*pBufLen) on input.
 * On exit (*pBufLen) provides the number of bytes written to the message
 * buffer. If buffer is too short the message is truncated.
 *
 * @param[in]     pThis      Pointer to protocol data
 * @param[in,out] pTimeout   On input timeout in ms, on exit time left
 * @param[in]     pReqMsg    Request message
 * @param[out]    pMsgBuf    Buffer for the response message
 * @param[in,out] pBufLen    On input buffer size, on exit message, in bytes
 */
EFI_STATUS EFIAPI SmmHeciRequest(
  IN     EFI_SMM_HECI_PROTOCOL *pThis,
  IN OUT UINT32                *pTimeout,
  IN     HECI_MSG_HEADER       *pReqMsg,
     OUT HECI_MSG_HEADER       *pRspBuf,
  IN     UINT32                *pBufLen)
{
  EFI_STATUS  Status;
  UINT32      Fd2;
  BOOLEAN     IntEnabled, IsReady;
  UINT32      SendQue, RecvQue;
  
  //
  // Make sure HECI-1 is visible on PCI. It may be hidden for basic ME firmware.
  //
  Fd2 = MmioRead32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2);
  MmioWrite32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2, Fd2 & ~B_PCH_RCRB_FD2_MEI1D);
  //
  // Save current interrupt enable state and disable interrupts
  //
  Status = HeciIntState(&pThis->HeciDev, &IntEnabled, NULL);
  if (EFI_ERROR(Status))
  {
    goto GetOut;
  }
  HeciIntEnable(&pThis->HeciDev, 0);
  //
  // If there is some date in the queue clear it by reseting the queue
  //
  HeciQueState(&pThis->HeciDev, &IsReady, &SendQue, &RecvQue);
  if (IsReady && (SendQue != 0 || RecvQue != 0))
  {
    Status = HeciQueReset(&pThis->HeciDev, pTimeout);
    if (EFI_ERROR(Status))
    {
      goto GetOut1;
    }
  }
  //
  // Send the request and wait for response if response expected
  //
  Status = HeciMsgSend(&pThis->HeciDev, pTimeout, pReqMsg);
  if (!EFI_ERROR(Status))
  {
    if (pRspBuf != NULL)
    {
      Status = HeciMsgRecv(&pThis->HeciDev, pTimeout, pRspBuf, pBufLen);
    }
  }
 GetOut1:
  //
  // Restore interrupt enable state
  //
  HeciIntEnable(&pThis->HeciDev, IntEnabled);
 GetOut:
  //
  // Restore HECI-1 hiding state
  //
  MmioWrite32(PCH_RCBA_ADDRESS + R_PCH_RCRB_FD2, Fd2);
  
  return Status;
} // SmmHeciRequest()

