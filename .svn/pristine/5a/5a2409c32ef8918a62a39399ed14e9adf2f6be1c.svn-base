//***************************************************************************
//***************************************************************************
//**                                                                       **
//**              (C)Copyright 1985-2006, American Megatrends, Inc.        **
//**                                                                       **
//**                          All Rights Reserved.                         **
//**                                                                       **
//**                  6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                       **
//**                        Phone (770)-246-8600                           **
//**                                                                       **
//***************************************************************************
//***************************************************************************
//***************************************************************************

//****************************************************************************
// $Header: N/A    7/09/14 9:52a SallyPeng $
//
// $Revision: 01 $
//
// $Date: 7/09/14 9:52a $
//
//****************************************************************************
//
//<OEM_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:   NMIButtonHandle.C
//
//  Description:    Oem NMI Function.
//
//-----------------------------------------------------------------------------
//<OEM_FHDR_END>

//****************************************************************************

#include <Protocol\SmmGpiDispatch2.h>
#include <Library/BaseLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <PchAccess.h>
#include <token.h>

static EFI_GUID gEfiSmmGpiDispatch2ProtocolGuid = EFI_SMM_GPI_DISPATCH2_PROTOCOL_GUID;

#define NMI_SC_PORT				0x61
#define NMI_EN_PORT				0x70
#define ALIASED_NMI_EN_PORT		0x74
#define ICH_IOREG_TCO1_STS		0x04
#define ICH_IOREG_TCO1_CNT		0x08

VOID GenerateNMINow ()  
{
    UINT8   Data8, Save_Nmi2Smi_En, Save_Port70;
    UINT32	mAcpiBaseAddr;
    UINT16	TCO_BASE_ADDRESS;

    DEBUG ((DEBUG_INFO, "GenerateNMINow start...\n"));
    mAcpiBaseAddr = (UINT32) (MmioRead16 (
                              MmPciAddress (0,
                              DEFAULT_PCI_BUS_NUMBER_PCH,
                              PCI_DEVICE_NUMBER_PCH_LPC,
                              PCI_FUNCTION_NUMBER_PCH_LPC,
                              R_PCH_LPC_ACPI_BASE)
                              ) & B_PCH_LPC_ACPI_BASE_BAR);

    TCO_BASE_ADDRESS = (UINT16) (mAcpiBaseAddr + 0x60);

    // Read the NMI2SMI_EN bit, save it for future restore
    Save_Nmi2Smi_En = IoRead8(TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT + 1);

    // Set the NMI2SMI_EN bit to 0
    Data8 = (UINT8)(Save_Nmi2Smi_En & 0xFD);
    IoWrite8(TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT + 1, Data8);

    // Enable NMI_EN
    Save_Port70 = IoRead8(ALIASED_NMI_EN_PORT);
    Data8 = (UINT8)(Save_Port70 & 0x7F);
    IoWrite8(NMI_EN_PORT, Data8);

    // Set NMI_NOW = 1
    Data8 = IoRead8(TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT + 1);
    Data8 = (UINT8) (Data8 | 0x01);
    IoWrite8(TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT + 1, Data8);

    // Clear NMI_NOW = 0 by writing 1 to NMI_NOW bit
    Data8 = IoRead8(TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT + 1);
    Data8 = (UINT8) (Data8 | 0x01);
    IoWrite8(TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT + 1, Data8);

    // Restore NMI2SMI_EN
    IoWrite8(TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT + 1, Save_Nmi2Smi_En);

    // Restore NMI_EN
    IoWrite8(NMI_EN_PORT, Save_Port70);
    DEBUG ((DEBUG_INFO, "GenerateNMINow end...\n"));
}

EFI_STATUS
SBGpi8SmiHandler (
    EFI_HANDLE	DispatchHandle, 
    CONST VOID	*Context,
    VOID		*CommBuffer,
    UINTN		*CommBufferSize )
{
    GenerateNMINow();
    return EFI_SUCCESS;
}

EFI_STATUS
InitializeGpi8Smi (
    IN EFI_HANDLE             ImageHandle,
    IN EFI_SYSTEM_TABLE       *SystemTable )
{
    EFI_SMM_GPI_REGISTER_CONTEXT      GpiContext;
    EFI_HANDLE                        GpiHandle;
    EFI_STATUS                        Status = EFI_SUCCESS;
    EFI_SMM_GPI_DISPATCH2_PROTOCOL    *GpiDispatch = NULL;
    UINT32                            Data32;

    //
    // Register our SMI handlers through a child protocol
    //
    Status = gSmst->SmmLocateProtocol (&gEfiSmmGpiDispatch2ProtocolGuid, NULL, &GpiDispatch);
    ASSERT_EFI_ERROR (Status);
    DEBUG ((DEBUG_INFO, "GpiSmmDispatch register start...\n"));
    
    //
    // Register the enable handler
    //
    GpiContext.GpiNum = NMI_Button_GPI_NUM;

    if (!EFI_ERROR(Status)) {
    	Status = GpiDispatch->Register (
		  	  	  	  	  	  GpiDispatch,
		  	  	  	  	  	  SBGpi8SmiHandler,
		  	  	  	  	  	  &GpiContext,
		  	  	  	  	  	  &GpiHandle
		  	  	  	  	  	  );
    	ASSERT_EFI_ERROR (Status);
    	DEBUG ((DEBUG_INFO, "GpiSmmDispatch registion Status = %r\n", Status));
    }
    DEBUG ((DEBUG_INFO, "GpiSmmDispatch register end...\n"));

    //Set GPI_ROUT so when GPI NMI_Button_GPI_NUM get low will generate SMI#
    Data32 = (UINT32) (MmioRead16 (
    			MmPciAddress (0,
    			DEFAULT_PCI_BUS_NUMBER_PCH,
    			PCI_DEVICE_NUMBER_PCH_LPC,
    			PCI_FUNCTION_NUMBER_PCH_LPC,
    			R_PCH_LPC_GPI_ROUT)
    			)); 
    Data32 |= (1 << (NMI_Button_GPI_NUM *2));	// GPI NMI_Button_GPI_NUM Route as #SMI

    MmioWrite32(
    			MmPciAddress (0,
    			DEFAULT_PCI_BUS_NUMBER_PCH,
    			PCI_DEVICE_NUMBER_PCH_LPC,
    			PCI_FUNCTION_NUMBER_PCH_LPC,
    			R_PCH_LPC_GPI_ROUT),Data32);

    return Status;
}
