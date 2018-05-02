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
// Name:  <SioPeiInit.c>
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AST2400PeiIoTable.h>

//-------------------------------------------------------------------------
// global funtion declare ; these funtions are used for other files.
//-------------------------------------------------------------------------
typedef struct _LPC_AHB_DATA{
    UINT8           Offset;
    UINT32           And;
    UINT32           Or;
} LPC_AHB_DATA;

//----------------------------------------------------------------------------
//  the table is used for LPC_AHB access function. OEM need to porting.
//----------------------------------------------------------------------------
LPC_AHB_DATA AST2400_SUC_access_Table[] = {
    //---------------------------------------------------------------------
    // program SCU Multi-Pin if needed.
    //---------------------------------------------------------------------
    {0x00, 0x00000000 , 0x1688A8A8},//Unlock SCU Registers
    #if (AST2400_SERIAL_PORT1_PRESENT)
    {0x84, 0xFF00FFFF , 0x00FF0000},//SCU84[23:16]="FFh" Enable UART1 or video VPB Multi-Function pins
    {0x90, 0xFFFFFFCF , 0x00000000},//SCU90[5:4]="00b" Disable digital video Multi-Function pins
    #endif //#if (AST2400_SERIAL_PORT1_PRESENT)
    #if (AST2400_SERIAL_PORT2_PRESENT)
//TH0108    {0x84, 0x00FFFFFF , 0xFF000000},//SCU84[31:24]="FFh" Enable UART2 or video VPB Multi-Function pins
    {0x84, 0x00FFFFFF , 0xC0000000},//SCU84[31:24]="FFh" Enable UART2 or video VPB Multi-Function pins //TH0108 
    {0x90, 0xFFFFFFCF , 0x00000000},//SCU90[5:4]="00b" Disable digital video Multi-Function pins
    #endif //#if (AST2400_SERIAL_PORT2_PRESENT)
    #if (AST2400_SERIAL_PORT3_PRESENT)
    {0x80, 0xFF00FFFF , 0x00FF0000},//SCU80[23:16]="FFh" Enable UART3 Multi-Function pins
    #endif //#if (AST2400_SERIAL_PORT3_PRESENT)
    #if (AST2400_SERIAL_PORT4_PRESENT)
    {0x80, 0x00FFFFFF , 0xFF000000},//SCU80[31:24]="FFh" Enable UART4 Multi-Function pins
    #endif //#if (AST2400_SERIAL_PORT4_PRESENT)
    //---------------------------------------------------------------------
    // >>Aspeed AP Workaround Start
    // EIP#175088: Implement AST2400/AST1400/AST1250 ap note #05
    //---------------------------------------------------------------------
    //Do not write a value other than 0x1688a8a8 to 0x1e6e2000
    //{0x00, 0x00000000 , 0x00000000},//Lock SCU Registers
    //---------------------------------------------------------------------
    // <<Aspeed AP Workaround end
    //---------------------------------------------------------------------
};

//*************************************************************************
// belows are functions defined
    VOID lpc_read(
        IN    UINT32        Address,
        OUT   UINT32         *Value
    );

    VOID lpc_write(
        IN    UINT32        Address,
        IN    UINT32         Vaule
    );

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: SioPeiInitEntryPoint
//
// Description:
//  This function provide PEI phase SIO initialization
//
// Input:
//  IN  EFI_FFS_FILE_HEADER    *FfsHeader - Logical Device's information
//  IN  EFI_PEI_SERVICES       **PeiServices  - Read/Write PCI config space
//
// Output:    None
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS AST2400PeiInitEntryPoint(
        IN       EFI_PEI_FILE_HANDLE  FileHandle,
        IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
        UINT8           index;
        UINTN           i;
        UINT32          address;
        UINT32          Value;

    for(index=0; index<sizeof(AST2400PeiDecodeTable)/sizeof(IO_DECODE_DATA); index++)
        AmiSioLibSetLpcDeviceDecoding(NULL, AST2400PeiDecodeTable[index].BaseAdd, AST2400PeiDecodeTable[index].UID, AST2400PeiDecodeTable[index].Type);

    ProgramRtRegisterTable(0, AST2400PeiInitTable, sizeof(AST2400PeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA));

    // initialize SUC part.
    for(i=0; i< ((sizeof(AST2400_SUC_access_Table))/(sizeof(LPC_AHB_DATA))); i++) {
        address = (UINT32)(AST2400_SUCBASE | (AST2400_SUC_access_Table[i].Offset));
        lpc_read(address , &Value);
        Value &= (AST2400_SUC_access_Table[i].And);
        Value |= (AST2400_SUC_access_Table[i].Or);
        lpc_write(address,Value);
    }

    return EFI_SUCCESS;
}


//VOID lpc_read (ULONG ulAddress, BYTE jmode)
VOID lpc_read (
        IN      UINT32 ulAddress,
        OUT     UINT32  *Value)
{
//    ULONG    uldata = 0, ultemp = 0;
    UINT32     uldata = 0;
    UINT8     jtemp;

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_ENTER_VALUE);
    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_ENTER_VALUE);

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_LDN_SEL_REGISTER);
    IoWrite8 (AST2400_CONFIG_DATA, AST2400_LDN_LPC2AHB);

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_ACTIVATE_REGISTER);
    jtemp = IoRead8 (AST2400_CONFIG_DATA); //
    IoWrite8 (AST2400_CONFIG_DATA, (jtemp | 0x01));//Active
//Write Address
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF0);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0xFF000000) >> 24));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF1);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0x00FF0000) >> 16));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF2);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0x0000FF00) >> 8));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF3);
    IoWrite8 (AST2400_CONFIG_DATA, ulAddress & 0xFF);
//Write Mode
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF8);
    jtemp = IoRead8 (AST2400_CONFIG_DATA);
    IoWrite8 (AST2400_CONFIG_DATA, (jtemp & 0xFC) | 0x02);
//Fire
    IoWrite8 (AST2400_CONFIG_INDEX, 0xFE);
    jtemp = IoRead8 (AST2400_CONFIG_DATA);
//Get Data
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF4);
    uldata |= (IoRead8 (AST2400_CONFIG_DATA) << 24);
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF5);
    uldata |= (IoRead8 (AST2400_CONFIG_DATA) << 16);
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF6);
    uldata |= (IoRead8 (AST2400_CONFIG_DATA) << 8);
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF7);
    uldata |= (IoRead8 (AST2400_CONFIG_DATA));
    
    *Value = uldata;

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_EXIT_VALUE);
}

//VOID lpc_write (ULONG ulAddress, ULONG uldata, BYTE jmode)
VOID lpc_write (
        IN      UINT32  ulAddress,
        IN      UINT32   uldata)
{
    UINT8     jtemp;
    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_ENTER_VALUE);
    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_ENTER_VALUE);

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_LDN_SEL_REGISTER);
    IoWrite8 (AST2400_CONFIG_DATA, AST2400_LDN_LPC2AHB);

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_ACTIVATE_REGISTER);
    jtemp = IoRead8 (AST2400_CONFIG_DATA); //
    IoWrite8 (AST2400_CONFIG_DATA, (jtemp | 0x01));//Active
//Write Address
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF0);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0xff000000) >> 24));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF1);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0x00ff0000) >> 16));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF2);
    IoWrite8 (AST2400_CONFIG_DATA, ((ulAddress & 0x0000ff00) >> 8));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF3);
    IoWrite8 (AST2400_CONFIG_DATA, ulAddress & 0xFF);
//Write Data
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF4);
    IoWrite8 (AST2400_CONFIG_DATA, ((uldata & 0xff000000) >> 24));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF5);
    IoWrite8 (AST2400_CONFIG_DATA, ((uldata & 0x00ff0000) >> 16));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF6);
    IoWrite8 (AST2400_CONFIG_DATA, ((uldata & 0x0000ff00) >> 8));
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF7);
    IoWrite8 (AST2400_CONFIG_DATA, uldata);
//Write Mode
    IoWrite8 (AST2400_CONFIG_INDEX, 0xF8);
    jtemp = IoRead8 (AST2400_CONFIG_DATA);
    IoWrite8 (AST2400_CONFIG_DATA, (jtemp & 0xFC) | 0x02);
//Fire
    IoWrite8 (AST2400_CONFIG_INDEX, 0xFE);
    IoWrite8 (AST2400_CONFIG_DATA, 0xCF);

    IoWrite8 (AST2400_CONFIG_INDEX, AST2400_CONFIG_MODE_EXIT_VALUE);
}

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
