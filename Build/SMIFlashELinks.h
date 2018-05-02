#define SMIFLASH_IN_SMM_LIST 
#define SMIFLASH_NOT_IN_SMM_LIST 
#define SMIFLASH_END_UPDATE_LIST RestoreVariables, EnableUSBKBD,
#define SMIFLASH_PRE_UPDATE_LIST PreserveVariables, DisableUSBKBD,
#define SMIFLASH_PRE_HANDLER_LIST 
#define SMIFLASH_END_HANDLER_LIST OemActivationUpdateBlockTypeId, AppendFvDataToAFU_UpdateBlockTypeId, BiosLockEnableSmiFlashHook,
#define SMIFLASH_SAVE_VARS_LIST 
#define SMIFLASH_SAVE_GUIDS_LIST { 0x77FA9ABD, 0x0359, 0x4D32, 0xBD, 0x60, 0x28, 0xF4, 0xE7, 0x8F, 0x78, 0x4B },

