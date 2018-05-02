//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//****************************************************************************
// Revision History
// ----------------
// $Log: $
// 
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name: RuntimeMemoryHole.c
//
//  Description: This file provides primary functions of RuntimeMemoryHole module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <RuntimeMemoryHole.h>

EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_CPU_PROTOCOL            *gSmmCpu;

static EFI_PHYSICAL_ADDRESS		gpRuntimeMemoryHoleAddr = 0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   SwSmiHandler
//
//  Description:
//  This function will recognize the CPU which triggered SMI, and then fill
//	the value of reserved memory hole location into its dump area of EBX and
//	ECX.
//
//  Input:
//	IN EFI_HANDLE					DispatchHandle
//	IN EFI_SMM_SW_DISPATCH_CONTEXT	*DispatchContext
//
//  Output:
//	The CPU dump area of EBX and ECX will be filled with the value of the
//	location of reserved memory region.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
SwSmiHandler (
	EFI_HANDLE					DispatchHandle,
	CONST VOID					*Context,
	VOID						*CommBuffer,
	UINTN						*CommBufferSize
)
{
	UINT8		SwSmiNum;
	UINTN		CpuIndex = (INTN)-1;
	UINT32		AddressLow = *(UINT32 *)&gpRuntimeMemoryHoleAddr;
	UINT32		AddressHigh = ((UINT32 *)&gpRuntimeMemoryHoleAddr)[1];
	EFI_STATUS	Status = EFI_SUCCESS;

	EFI_SMM_CPU_SAVE_STATE	*pCpuSaveState = NULL;

	if (CommBuffer != NULL && CommBufferSize != NULL) {
		CpuIndex = ((EFI_SMM_SW_CONTEXT *)CommBuffer)->SwSmiCpuIndex;
		SwSmiNum = ((EFI_SMM_SW_CONTEXT *)CommBuffer)->CommandPort;
	}

	TRACE((TRACE_ALWAYS, "[RuntimeMemoryHole] AddressLow  : (%08X)\n", AddressLow));
	TRACE((TRACE_ALWAYS, "[RuntimeMemoryHole] AddressHigh : (%08X)\n", AddressHigh));

	if (CpuIndex != (INTN)-1) {
		switch (SwSmiNum) {
			case SW_SMI_GET_MEMORY_HOLE_LOCATION :
				Status = gSmmCpu->WriteSaveState(
									gSmmCpu,
									sizeof(UINT32),
									EFI_SMM_SAVE_STATE_REGISTER_RBX,
									CpuIndex,
									&AddressLow);
			    Status = gSmmCpu->WriteSaveState(
									gSmmCpu,
									sizeof(UINT32),
									EFI_SMM_SAVE_STATE_REGISTER_RCX,
									CpuIndex,
									&AddressHigh);
				break;

			default :
				break;
		}
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   InSmmFunction
//
//  Description:
//  This function will check Setup option. After ensuring user switched on
//	the Runtime Memory Hole, it will allocate a memory region and register the
//	SMI handler to SMM kernel.
//
//  Input:
//	IN EFI_HANDLE			ImageHandle
//	IN EFI_SYSTEM_TABLE		*SystemTable
//
//  Output:
//	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction (
	IN EFI_HANDLE			ImageHandle,
	IN EFI_SYSTEM_TABLE		*SystemTable
)
{
	EFI_HANDLE	SwSmiHandle;
	EFI_STATUS	Status;

	EFI_SMM_SW_DISPATCH2_PROTOCOL	*pSwDispatch = NULL;
	EFI_SMM_SW_REGISTER_CONTEXT		SwContext = { SW_SMI_GET_MEMORY_HOLE_LOCATION };

	InitAmiSmmLib(ImageHandle, SystemTable);

	Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
	if (EFI_ERROR(Status)) return Status;

	Status = pSmmBase->GetSmstLocation(gSmmBase2, &pSmst);
	if (EFI_ERROR(Status)) return Status;

	Status = pSmst->SmmLocateProtocol(&gEfiSmmSwDispatch2ProtocolGuid, NULL, &pSwDispatch);
	if (EFI_ERROR(Status)) return Status;

	Status = pSmst->SmmLocateProtocol(&gEfiSmmCpuProtocolGuid, NULL, &gSmmCpu);
	if (EFI_ERROR(Status)) return Status;

	Status = pBS->AllocatePages(
					AllocateAnyPages,
					EfiACPIMemoryNVS,
					RUNTIME_MEMORY_HOLE_SIZE / 0x1000,
					&gpRuntimeMemoryHoleAddr);
	if (EFI_ERROR(Status)) return Status;

	TRACE((TRACE_ALWAYS,
			"[RuntimeMemoryHole] Allocated Runtime Memory Hole at 0x%08X%08X\n",
			((UINT32 *)&gpRuntimeMemoryHoleAddr)[1],
			*(UINT32 *)&gpRuntimeMemoryHoleAddr));

	*(UINT32 *)gpRuntimeMemoryHoleAddr = 0xdeadbeef;	// Recognization pattern

	Status  = pSwDispatch->Register(pSwDispatch, SwSmiHandler, &SwContext, &SwSmiHandle);
	if (EFI_ERROR(Status)) return Status;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   RuntimeMemoryHoleEntryPoint
//
//  Description:
//  This is the entry point of Runtime Memory Hole module.
//
//  Input:
//	IN EFI_HANDLE			ImageHandle
//	IN EFI_SYSTEM_TABLE		*SystemTable
//
//  Output:
//	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RuntimeMemoryHoleEntryPoint (
	IN EFI_HANDLE			ImageHandle,
	IN EFI_SYSTEM_TABLE		*SystemTable
)
{
	// 1. Setup AMI library
	InitAmiLib(ImageHandle, SystemTable);

	// 2. Utilize EfiLib to init
	return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
