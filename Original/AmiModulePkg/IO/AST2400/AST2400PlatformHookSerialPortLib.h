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
// Name:  <AST2400PlatformHookSerialPortLib.h>
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "Token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA AST2400SerialPortDebugDecodeTable[]={
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    //Below decode is for DEBUG Mode
    {AST2400_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
    #ifdef EFI_DEBUG
    #if (AST2400_SERIAL_PORT1_PRESENT)
    {AST2400_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART}, // COMA decode
    #endif
    #endif
};

SIO_DEVICE_INIT_DATA AST2400SerialPortDebugInitTable[]={
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    {AST2400_CONFIG_INDEX, 0x00, AST2400_CONFIG_MODE_ENTER_VALUE},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_CONFIG_MODE_ENTER_VALUE},

    #if (AST2400_SERIAL_PORT1_PRESENT)

    #endif //#if (AST2400_SERIAL_PORT1_PRESENT)

    #ifdef EFI_DEBUG
    #if (AST2400_SERIAL_PORT1_PRESENT)
    // Select device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_UART1},
    // Program Base Addr
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE1_LO_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, (UINT8)(AST2400_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE1_HI_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, (UINT8)(AST2400_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_ACTIVATE_VALUE},
    #endif // #if (AST2400_SERIAL_PORT1_PRESENT)
    #endif // #ifdef EFI_DEBUG
    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    {AST2400_CONFIG_INDEX, 0x00, AST2400_CONFIG_MODE_EXIT_VALUE},
};

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
