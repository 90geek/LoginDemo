#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmiSmmCorePlatformHookLib.mak
#
# Description: Generate SmmPlatformeLinks.h file
#
#<AMI_FHDR_END>
#**********************************************************************
Prepare : $(BUILD_DIR)/SmmPlatformeLinks.h

ifdef PLATFORMHOOK_BEFORE_SMMDISPATCH
$(error PLATFORMHOOK_BEFORE_SMMDISPATCH now Invalid. Use SDL E-link PLATFORMHOOK_BEFORE_AFTER_SMMDISPATCH.)
endif

ifdef PLATFORMHOOK_AFTER_SMMDISPATCH
$(error PLATFORMHOOK_AFTER_SMMDISPATCH now Invalid. Use SDL E-link PLATFORMHOOK_BEFORE_AFTER_SMMDISPATCH.)
endif

$(BUILD_DIR)/SmmPlatformeLinks.h : $(BUILD_DIR)/Token.h $(AmiSmmPlatFormHook_DIR)/AmiSmmCorePlatformHookLib.mak
	$(ECHO) \
"#define PLATFORMHOOK_BEFORE_AFTER_SMMDISPATCH $(PLATFORMHOOK_BEFORE_AFTER_SMMDISPATCH)$(EOL)"\
>$(BUILD_DIR)/SmmPlatformeLinks.h