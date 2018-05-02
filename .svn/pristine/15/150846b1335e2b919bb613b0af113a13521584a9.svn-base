//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
//<AMI_FHDR_START>
//
// Name:  <AST2400DxeInit.c>
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiGenericSio.h>
#include "AST2400DxeIoTable.h"

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: AST2400_ClearDevResource
//
// Description:
//  This function will Clear SIO resource
//
// Input:
//  SIO_DEV2* dev
// Output: 
//  NONE
//
//------------------------------------------------------------------------- 
// <AMI_PHDR_END>
VOID AST2400_ClearDevResource(
    IN  SIO_DEV2    *dev
)
{
    IoWrite8(AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_ENTER_VALUE);

    IoWrite8(AST2400_CONFIG_INDEX, AST2400_LDN_SEL_REGISTER);
    IoWrite8(AST2400_CONFIG_DATA, dev->DeviceInfo->Ldn);

    IoWrite8(AST2400_CONFIG_INDEX, AST2400_BASE1_HI_REGISTER);
    IoWrite8(AST2400_CONFIG_DATA, 0);
    IoWrite8(AST2400_CONFIG_INDEX, AST2400_BASE1_LO_REGISTER);
    IoWrite8(AST2400_CONFIG_DATA, 0);
    IoWrite8(AST2400_CONFIG_INDEX, AST2400_IRQ1_REGISTER);
    IoWrite8(AST2400_CONFIG_DATA, 0);

    IoWrite8(AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_EXIT_VALUE);
    
    return;

}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: AST2400_COM_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output:
//            EFI_STATUS
//            EFI_SUCCESS - Initial step sucessfully
//            EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if AST2400_SERIAL_PORT1_PRESENT | AST2400_SERIAL_PORT2_PRESENT | AST2400_SERIAL_PORT3_PRESENT | AST2400_SERIAL_PORT4_PRESENT
EFI_STATUS AST2400_COM_Init(
//    IN    AMI_SIO_PROTOCOL        *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL     *PciIo,
//    IN    SIO_INIT_STEP           InitStep
        AMI_BOARD_INIT_PROTOCOL     *This,
        IN UINTN                    *Function,
        IN OUT VOID                 *ParameterBlock)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;
    UINT8                           rv=0; //ComMode Register

    switch (InitStep)
    {
        case isGetSetupData:
            // Disable IODecode?
            if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)){
                AST2400_ClearDevResource(dev);
            }
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
            //Only decode UART1/UART2. More others UART port is decode in PEI
            //Attention! Remove the more com ports to PEI decode.
            if(dev->DeviceInfo->Uid < 0x02){
                //Decode?
                if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable){
                    AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
                }else{
                    AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
                }
            }
            // Program COM Clock Source Registers.
            if(AST2400_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].AndData8 == 0xFF) {
                rv=AST2400_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].OrData8;
            } else {
                Status=AmiSio->Access(AmiSio, FALSE, FALSE, AST2400_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].Reg8,&rv);
                ASSERT_EFI_ERROR(Status);
                rv &= AST2400_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].AndData8;
                rv |= AST2400_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].OrData8;
            }
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,AST2400_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].Reg8,&rv);
        break;

        case isGetModeData:
        break;

        case isAfterActivate:
        break;

        case isAfterBootScript:
        break;

        default: Status=EFI_INVALID_PARAMETER;
    }//switch

    return Status;
}
#endif
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: AST2400_KBC_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output:
//            EFI_STATUS
//            EFI_SUCCESS - Initial step sucessfully
//            EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if AST2400_KEYBOARD_PRESENT
EFI_STATUS AST2400_KBC_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
        AMI_BOARD_INIT_PROTOCOL    *This,
        IN UINTN                    *Function,
        IN OUT VOID                    *ParameterBlock )
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK    *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                    InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                 *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL              *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS  Status=EFI_SUCCESS;
    SIO_DEV2    *dev=(SIO_DEV2*)AmiSio;

//-----------------------------
    switch (InitStep) {
        case isGetSetupData:
        case isPrsSelect:
        case isAfterActivate:
        case isAfterBootScript:
        break;

        case isBeforeActivate:
            //Decode?
            if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable){
                AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
            }else{
                AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
            }
        break;

        case isGetModeData:
        break;

        default: Status=EFI_INVALID_PARAMETER;
    } //switch
//-----------------------------
    return Status;
}
#endif

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: AST2400_GPIO_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output:
//            EFI_STATUS
//            EFI_SUCCESS - Initial step sucessfully
//            EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if AST2400_GPIO_PORT_PRESENT
EFI_STATUS AST2400_GPIO_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
        AMI_BOARD_INIT_PROTOCOL    *This,
        IN UINTN                    *Function,
        IN OUT VOID                    *ParameterBlock )
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK    *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                    InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                 *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL              *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    EFI_STATUS    Status=EFI_SUCCESS;


    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
            ProgramIsaRegisterTable(AST2400_CONFIG_INDEX, AST2400_CONFIG_DATA,\
                    DXE_GPIO_Init_Table_Before_Active,sizeof(DXE_GPIO_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
        break;

        case isAfterActivate:
            // Initial GPIO register if you need.

        break;

        case isAfterBootScript:
        break;

        case isGetModeData:
        break;

        default: Status=EFI_INVALID_PARAMETER;
    } //switch
    return Status;
}
#endif

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: AST2400_SWC_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output:
//            EFI_STATUS
//            EFI_SUCCESS - Initial step sucessfully
//            EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if AST2400_SWC_PRESENT
EFI_STATUS AST2400_SWC_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
        AMI_BOARD_INIT_PROTOCOL    *This,
        IN UINTN                    *Function,
        IN OUT VOID                    *ParameterBlock )
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK    *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                    InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                 *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL              *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    EFI_STATUS    Status=EFI_SUCCESS;
    
    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
            ProgramIsaRegisterTable(AST2400_CONFIG_INDEX, AST2400_CONFIG_DATA,\
                    DXE_SWC_Init_Table_Before_Active,sizeof(DXE_SWC_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
        break;

        case isAfterActivate:

        break;

        case isAfterBootScript:
        break;

        case isGetModeData:
        break;

        default: Status=EFI_INVALID_PARAMETER;
    } //switch
    return Status;
}
#endif

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: AST2400_LPC2AHB_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output:
//            EFI_STATUS
//            EFI_SUCCESS - Initial step sucessfully
//            EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if AST2400_LPC2AHB_PRESENT
EFI_STATUS AST2400_LPC2AHB_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
        AMI_BOARD_INIT_PROTOCOL    *This,
        IN UINTN                    *Function,
        IN OUT VOID                    *ParameterBlock )
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK    *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                    InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                 *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL              *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    EFI_STATUS    Status=EFI_SUCCESS;
    
    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
            ProgramIsaRegisterTable(AST2400_CONFIG_INDEX, AST2400_CONFIG_DATA,\
                    DXE_LPC2AHB_Init_Table_Before_Active,sizeof(DXE_LPC2AHB_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
        break;

        case isAfterActivate:
        break;

        case isAfterBootScript:
        break;

        case isGetModeData:
        break;

        default: Status=EFI_INVALID_PARAMETER;
    } //switch
    return Status;
}
#endif

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: AST2400_MAILBOX_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output:
//            EFI_STATUS
//            EFI_SUCCESS - Initial step sucessfully
//            EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if AST2400_MAILBOX_PRESENT
EFI_STATUS AST2400_MAILBOX_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
        AMI_BOARD_INIT_PROTOCOL    *This,
        IN UINTN                    *Function,
        IN OUT VOID                    *ParameterBlock )
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK    *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                    InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                 *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL              *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    EFI_STATUS    Status=EFI_SUCCESS;
    
    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
            ProgramIsaRegisterTable(AST2400_CONFIG_INDEX, AST2400_CONFIG_DATA,\
                    DXE_MAILBOX_Init_Table_Before_Active,sizeof(DXE_MAILBOX_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
        break;

        case isAfterActivate:
        break;

        case isAfterBootScript:
        break;

        case isGetModeData:
        break;

        default: Status=EFI_INVALID_PARAMETER;
    } //switch
    return Status;
}
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
