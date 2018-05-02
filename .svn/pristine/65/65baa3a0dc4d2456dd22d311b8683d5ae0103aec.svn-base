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
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <AST2400DxeIoTable.h>
//
// Description: 
//  SIO init table in DXE phase. Any customers have to review below tables 
//  for themselves platform and make sure each initialization is necessary.
//
// Notes:
//  In all tables, only fill with necessary setting. Don't fill with default
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _DXEIoTable_H
#define _DXEIoTable_H
#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Token.h>
#include <Library/AmiSioDxeLib.h>

//<AMI_THDR_START>
//-------------------------------------------------------------------------
//
// Name:        DXE_XXX_Init_Table
//
// Description: 
//  Table filled with SIO GPIO,PME,HWM, etc. logical devices' setting
//  For example:
//  1. GPIO will define the GPIO pin useage
//  2. PME will power management control
//  3. HWM will set temperature, fan, voltage and start control.
//
// Notes:
//
//-------------------------------------------------------------------------
//<AMI_THDR_END>

DXE_DEVICE_INIT_DATA   AST2400_DXE_COM_Mode_Init_Table[] = {
    // -----------------------------
    //| Reg8 | AndData8  | OrData8  |
    // -----------------------------
    // OEM_TODO: Base on OEM board.
    // Program COM Clock Source Registers.
    {0xF0, 0xFD, AST2400_SERIAL_PORT1_Clock_Value << 1},    //make no effect when com1 disabled
    {0xF0, 0xFD, AST2400_SERIAL_PORT2_Clock_Value << 1},    //make no effect when com2 disabled
    {0xF0, 0xFD, AST2400_SERIAL_PORT3_Clock_Value << 1},    //make no effect when com1 disabled
    {0xF0, 0xFD, AST2400_SERIAL_PORT4_Clock_Value << 1},    //make no effect when com2 disabled
};

//-------------------------------------------------------------------------
// SWC registers init table.
//-------------------------------------------------------------------------
#if AST2400_SWC_PRESENT
SIO_DEVICE_INIT_DATA   DXE_SWC_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  | 
    // -----------------------------
    // Program Global Configuration Registers.
//    {0x60,0x00, (UINT8)(IO1B >> 8)},    //SWC base address bit[15:8]
//    {0x61,0x00, (UINT8)(IO1B & 0xFF)},  //SWC base address bit[7:1]
//    {0x62,0x00, (UINT8)(IO2B >> 8)},    //PM1b_EVT base address bit[15:8]
//    {0x63,0x00, (UINT8)(IO2B & 0xFF)},  //PM1b_EVT base address bit[7:2]
    {0x64,0x00, (UINT8)(IO3B >> 8)},    //PM1b_CNT base address bit[15:8]
    {0x65,0x00, (UINT8)(IO3B & 0xFF)},  //PM1b_CNT base address bit[7:1]
    {0x66,0x00, (UINT8)(IO4B >> 8)},    //GPE1_BLK base address bit[15:8]
    {0x67,0x00, (UINT8)(IO4B & 0xFF)},  //GPE1_BLK base address bit[7:3]
}; //DXE_SWC_Init_Table_Before_Active
#endif //#if AST2400_SWC_PRESENT

//-------------------------------------------------------------------------
// GPIO registers init table.
//-------------------------------------------------------------------------
#if AST2400_GPIO_PORT_PRESENT
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  | 
    // -----------------------------
//OEM_TODO: Base on OEM board.
    {0x07,0x00, 0x07},
}; //DXE_GPIO_Init_Table_Before_Active
#endif //#if AST2400_GPIO_PORT_PRESENT

//-------------------------------------------------------------------------
// LPC2AHB registers init table.
//-------------------------------------------------------------------------
#if AST2400_LPC2AHB_PRESENT
SIO_DEVICE_INIT_DATA   DXE_LPC2AHB_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  | 
    // -----------------------------
    // Program Global Configuration Registers.
    {0x07, 0x00, 0x0E},  
}; //DXE_LPC2AHB_Init_Table_Before_Active
#endif //#if AST2400_LPC2AHB_PRESENT

//-------------------------------------------------------------------------
// MAILBOX registers init table.
//-------------------------------------------------------------------------
#if AST2400_MAILBOX_PRESENT
SIO_DEVICE_INIT_DATA   DXE_MAILBOX_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  | 
    // -----------------------------
    // Program Global Configuration Registers.
    {0x07, 0x00, 0x0E},  
}; //DXE_MAILBOX_Init_Table_Before_Active
#endif //#if AST2400_MAILBOX_PRESENT
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif //_DXEIoTable_H
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
