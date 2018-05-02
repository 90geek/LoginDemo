#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#
# @file  Ipmi.mak
#
#   Make file for Ipmi Module
#


ifeq ($(OEM_SEL_SUPPORT), 1)

Prepare : $(BUILD_DIR)/OemStatusCodeTable.h

$(BUILD_DIR)/OemStatusCodeTable.h : $(BUILD_DIR)/Token.mak $(IPMI_DIR)/Ipmi.mak
	@$(ECHO) \
"#define END_OF_OEM_STATUS_CODE_LIST {0xFFFF, 0xFF, 0xFF, 0xFF, 0xFF}$(EOL)\
EFI_STATUS_CODE_TO_SEL_ENTRY OemStatusCodeToSelTable [] = {$(EOL)\
$(OEM_STATUS_CODE_LIST)$(EOL)\
END_OF_OEM_STATUS_CODE_LIST };$(EOL)" > $(BUILD_DIR)/OemStatusCodeTable.h

endif	#ifeq ($(OEM_SEL_SUPPORT), 1)

ifeq ($(PeiIpmiInitialize_SUPPORT), 1)

Prepare : $(BUILD_DIR)/InitLpcBmcHook.h

$(BUILD_DIR)/InitLpcBmcHook.h : $(BUILD_DIR)/Token.mak $(IPMI_DIR)/Ipmi.mak
	$(ECHO) \
"#define INIT_LPC_BMC_HOOK_LIST $(INIT_LPC_BMC_HOOK)$(EOL)"\
>$(BUILD_DIR)/InitLpcBmcHook.h

endif	#ifeq ($(PeiIpmiInitialize_SUPPORT), 1)

Prepare : $(BUILD_DIR)/SpmiAslScope.asl

$(BUILD_DIR)/SpmiAslScope.asl : $(BUILD_DIR)/Token.mak $(IPMI_DIR)/Ipmi.mak
	$(ECHO) \
"#define SPMI_SCOPE $(SPMI_SCOPE)$(EOL)"\
>$(BUILD_DIR)/SpmiAslScope.asl

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
