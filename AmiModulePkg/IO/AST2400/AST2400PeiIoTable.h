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
// Name:  <AST2400PeiIoTable.h>
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA AST2400PeiDecodeTable[]={
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {AST2400_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for recovery mode
    #if defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT)
    #if (AST2400_SERIAL_PORT1_PRESENT)
        {AST2400_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART}, // COMA decode
    #endif
    #if (AST2400_KEYBOARD_PRESENT)
        {0x60, 0, dsPS2K},                                  // KBC decode
    #endif
    #endif
    //Below decode is for SIO generic IO decode
    #if defined(AST2400_TOTAL_BASE_ADDRESS) && (AST2400_TOTAL_BASE_ADDRESS != 0)
        {AST2400_TOTAL_BASE_ADDRESS, AST2400_TOTAL_LENGTH, 0xFF}, // open a IODecode section for GPIO+PME+...
    #endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    // Add more OEM IO decode below.
        {0x3E0, 0x10, 0xFF}, // 0x3E0~0x3F0 , open a IODecode section for UART3 4 
        {0x2E0, 0x20, 0xFF}, // 0x2E0~0x2FF , open a IODecode section for UART5 6
};

SIO_DEVICE_INIT_DATA AST2400PeiInitTable[]={
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    {AST2400_CONFIG_INDEX, 0x00, AST2400_CONFIG_MODE_ENTER_VALUE},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_CONFIG_MODE_ENTER_VALUE},
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    //    {AST2400_CONFIG_INDEX, 0x00, 0x21}, //SIO to BMC scratch register 1
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x22}, //SIO to BMC scratch register 2
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x23}, //SIO to BMC scratch register 3
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x24}, //SIO to BMC scratch register 4
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x25}, //SIO to BMC scratch register 5
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x26}, //SIO to BMC scratch register 6
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x27}, //SIO to BMC scratch register 7
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x28}, //BMC to SIO scratch register 0
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x29}, //BMC to SIO scratch register 1
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x2A}, //BMC to SIO scratch register 2
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x2B}, //BMC to SIO scratch register 3
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x2C}, //BMC to SIO scratch register 4
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x2D}, //BMC to SIO scratch register 5
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x2E}, //BMC to SIO scratch register 6
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},
    //    {AST2400_CONFIG_INDEX, 0x00, 0x2F}, //BMC to SIO scratch register 7
    //    {AST2400_CONFIG_DATA,  0x00, 0x00},

    //---------------------------------------------------------------------
    // Initialize the Serial Port for Recovery. Default is COMA
    //---------------------------------------------------------------------
    #if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
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
    #endif // AST2400_SERIAL_PORT1_PRESENT
    #endif 

    //---------------------------------------------------------------------
    // Initialize the KeyBoard and floppy controller for Recovery
    //---------------------------------------------------------------------
    #if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
    #if (AST2400_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_PS2K},
    // Program Base Addr
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE1_HI_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE1_LO_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x60},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE2_HI_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE2_LO_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x64},
    // Program Interrupt
    {AST2400_CONFIG_INDEX, 0x00, AST2400_IRQ1_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x01},
    // Activate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_ACTIVATE_VALUE},
    #else
    // Deactivate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_PS2K},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_DEACTIVATE_VALUE},
    #endif //AST2400_KEYBOARD_PRESENT

    #endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT == 1)
    //---------------------------------------------------------------------
    // Disable Non-Used Device in Pei Phase,if its default value is actived.
    //---------------------------------------------------------------------
    // Select device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_UART3},
    // Program Base Addr 
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE1_LO_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE1_HI_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_DEACTIVATE_VALUE},
    
    // Select device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_UART4},
    // Program Base Addr 
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE1_LO_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_BASE1_HI_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_DEACTIVATE_VALUE},
    
    #if (AST2400_SWC_PRESENT)
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_SWC},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_IRQ1_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
//    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
//    {AST2400_CONFIG_DATA,  0x00, AST2400_ACTIVATE_VALUE},
    #else
    // Deactivate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_SWC},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_DEACTIVATE_VALUE},
    #endif //#if (AST2400_SWC_PRESENT)

    #if (AST2400_GPIO_PORT_PRESENT)
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_GPIO},
//    {AST2400_CONFIG_INDEX, 0x00, 0x38},//bit7:enable inverse polarity of port 80h GPIO, BIt[0-4]: IO band selection
//    {AST2400_CONFIG_DATA,  0x00, 0x00},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_IRQ1_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
//    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
//    {AST2400_CONFIG_DATA,  0x00, AST2400_ACTIVATE_VALUE},
    #else
    // Deactivate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_GPIO},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_DEACTIVATE_VALUE},
    #endif //#if (AST2400_GPIO_PORT_PRESENT)

    #if (AST2400_LPC2AHB_PRESENT)
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_LPC2AHB},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_IRQ1_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
//    {AST2400_CONFIG_INDEX, 0x00, 0xF0},
//    {AST2400_CONFIG_DATA,  0x00, },    //SIO iLPC2AHB address bit[31:24]
//    {AST2400_CONFIG_INDEX, 0x00, 0xF1},
//    {AST2400_CONFIG_DATA,  0x00, },    //SIO iLPC2AHB address bit[23:16]
//    {AST2400_CONFIG_INDEX, 0x00, 0xF2},
//    {AST2400_CONFIG_DATA,  0x00, },    //SIO iLPC2AHB address bit[15:8]
//    {AST2400_CONFIG_INDEX, 0x00, 0xF3},
//    {AST2400_CONFIG_DATA,  0x00, },    //SIO iLPC2AHB address bit[7:0]
//    {AST2400_CONFIG_INDEX, 0x00, 0xF4},
//    {AST2400_CONFIG_DATA,  0x00, },    //SIO iLPC2AHB data bit[31:24]
//    {AST2400_CONFIG_INDEX, 0x00, 0xF5},
//    {AST2400_CONFIG_DATA,  0x00, },    //SIO iLPC2AHB data bit[23:16]
//    {AST2400_CONFIG_INDEX, 0x00, 0xF6},
//    {AST2400_CONFIG_DATA,  0x00, },    //SIO iLPC2AHB data bit[15:8]
//    {AST2400_CONFIG_INDEX, 0x00, 0xF7},
//    {AST2400_CONFIG_DATA,  0x00, },    //SIO iLPC2AHB data bit[7:0]
//    {AST2400_CONFIG_INDEX, 0x00, 0xF8},
//    {AST2400_CONFIG_DATA,  0x00, 0x00},
//    {AST2400_CONFIG_INDEX, 0x00, 0xFE},
//    {AST2400_CONFIG_DATA,  0x00, 0x00},
//    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
//    {AST2400_CONFIG_DATA,  0x00, AST2400_ACTIVATE_VALUE},
    #else
    // Deactivate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_LPC2AHB},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_DEACTIVATE_VALUE},
    #endif //#if (AST2400_LPC2AHB_PRESENT)

    #if (AST2400_MAILBOX_PRESENT)
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_MAILBOX},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_IRQ1_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, 0x00},
//    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
//    {AST2400_CONFIG_DATA,  0x00, AST2400_ACTIVATE_VALUE},
    #else
    // Deactivate Device
    {AST2400_CONFIG_INDEX, 0x00, AST2400_LDN_SEL_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_LDN_MAILBOX},
    {AST2400_CONFIG_INDEX, 0x00, AST2400_ACTIVATE_REGISTER},
    {AST2400_CONFIG_DATA,  0x00, AST2400_DEACTIVATE_VALUE},
    #endif //#if (AST2400_MAILBOX_PRESENT)
    
    //---------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------

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
