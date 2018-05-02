#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
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
# $Header:  $
#
# $Revision:  $
#
# $Date:  $
#**********************************************************************
# Revision History
# ----------------
# $Log:  $
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Grantley.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

#Do not change the order of Platform configurations.
ifeq ($(CRB_FLAG_ENABLE), 1)
EXTERNAL_CC_FLAGS +=  /D CRB_FLAG /D VFR_CRB_FLAG /D EXTERNAL_PACKAGE /D SSA_FLAG /D SSA_LOADER_FLAG
endif

ifeq ($(SDP_PLATFORM), 1)
EXTERNAL_CC_FLAGS += /D SDP_FLAG /D SV_OR_SDP_FLAG
endif
 
EXTERNAL_CC_FLAGS +=  /D HSX_HOST  /D BDX_HOST

ifeq ($(SV_BIOS_ENABLE), 1)
EXTERNAL_CC_FLAGS +=  /D SV_HOOKS /D SV_HOOKS_CPU /D SV_HOOKS_PCH /D QPI_SV_HOOKS /D SV_OR_SDP_FLAG /D MEM_SV_HOOKS
endif

ifeq ($(SOFTSDV_BIOS_ENABLE), 1)
EXTERNAL_CC_FLAGS +=  /D SOFTSDV /D SOFTSDV_FLAG
endif

ifeq ($(INTEL_TXT_SUPPORT), 1)
EXTERNAL_CC_FLAGS +=  /D LT_FLAG
endif

ifeq ($(SPLIT_RECOVERY_FV), 1)
EXTERNAL_CC_FLAGS +=  /D SPLIT_RECOVERY_FV
endif

ifeq ($(TRAD_BIOS_ENABLE), 1)
EXTERNAL_CC_FLAGS +=  /DTRAD_FLAG=1
endif

ifeq ($(ULT_BIOS_ENABLE), 1)
EXTERNAL_CC_FLAGS +=  /DULT_FLAG=1
endif

ifeq ($(SUS_WELL_RESTORE_ENABLE), 1)
EXTERNAL_CC_FLAGS +=  /DSUS_WELL_RESTORE=1
endif

ifeq ($(RSTE_TESTING), 1)
EXTERNAL_CC_FLAGS +=  /DRSTE_TEST=1
endif

ifeq ($(SERVER_BIOS_ENABLE), 1)
EXTERNAL_CC_FLAGS +=  /DPCH_SERVER_BIOS_FLAG=1
endif

ifeq ($(PCH_SERVER_BIOS_ENABLE), 1)
EXTERNAL_CC_FLAGS +=  /DPCH_SERVER_BIOS_FLAG=1
endif

ifeq ($(KAHUNA_PPO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D KAHUNA_PPO_FLAG
endif

ifeq ($(MAYAN_PPO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D MAYAN_PPO_FLAG
endif

ifeq ($(ARANDAS_PPO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D ARANDAS_PPO_FLAG
endif

ifeq ($(AZTEC_PPO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D AZTEC_PPO_FLAG
endif

ifeq ($(AZTECSTHI_PPO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D AZTECSTHI_PPO_FLAG
endif

ifeq ($(HEDT_PPO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D HEDT_PPO_FLAG
endif

ifeq ($(HEDTME_PPO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D HEDT_PPO_FLAG
endif

ifeq ($(INCA_PPO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D INCA_PPO_FLAG
endif

ifeq ($(ME_ENABLE), 1)
EXTERNAL_CC_FLAGS += /DME_SUPPORT_FLAG=1
	ifeq ($(SPS_ENABLE), 1)
  	EXTERNAL_CC_FLAGS += /DSPS_SUPPORT=1
   	endif
    ifeq ($(AMT_ENABLE), 1) 
    EXTERNAL_CC_FLAGS += /DAMT_SUPPORT=1
		ifeq ($(AT_ENABLE), 1)
         EXTERNAL_CC_FLAGS += /DAT_SUPPORT=1
   		endif
        ifeq ($(ICC_ENABLE), 1)
         EXTERNAL_CC_FLAGS += /DICC_SUPPORT=1
        endif
	endif #ifeq ($(AMT_ENABLE), 1)
endif #ifeq ($(ME_ENABLE), 1)

#Following are EDK build configurations.
#These are not required but defining then, to be in safer side.
ifeq ($(PFAT_EC_ENABLE), 1)
EXTERNAL_CC_FLAGS += /DPFAT_FLAG=1 /DPFAT_EC_FLAG=1
else
EXTERNAL_CC_FLAGS += /DPFAT_FLAG=1
endif

#MRC debug message support is provided as EXTERNAL flags based on DEBUG_CODE token.
ifeq ($(DEBUG_CODE), 1)
EXTERNAL_CC_FLAGS += /D SERIAL_DBG_MSG
endif

ifeq ($(BTG_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D BTG_FLAG
endif

#Dynamic mmcfg base address change support is provided as EXTERNAL flags based on DYNAMIC_MMCFG_BASE_SUPPORT token.
ifeq ($(DYNAMIC_MMCFG_BASE_SUPPORT), 1)
EXTERNAL_CC_FLAGS += /D DYNAMIC_MMCFG_BASE_FLAG
endif

# AptioV Server Override Start: Restore data during S3 Resume.

EXTERNAL_CC_FLAGS += /D AMI_PAM_SAVE_RESTORE_SWSMI_VALUE=$(AMI_PAM_SAVE_RESTORE_SWSMI)
EXTERNAL_CC_FLAGS += /D AMI_PAM_SAVE_CMD=$(AMI_PAM_SAVE)
EXTERNAL_CC_FLAGS += /D AMI_PAM_RESTORE_CMD=$(AMI_PAM_RESTORE)

# AptioV Server Override End: Restore data during S3 Resume.

ifeq ($(NVDIMM_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D MEM_NVDIMM_EN
endif

ifeq ($(NVMEM_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D NVMEM_FEATURE_EN
endif

ifeq ($(PPV_PLATFORM), 1)
EXTERNAL_CC_FLAGS += /D PPV_SETTINGS 
endif

ifeq ($(GRT_RF_PO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /D GRT_RF_PO_FLAG
endif

ifeq ($(ADSP_ENABLE), 1)
EXTERNAL_CC_FLAGS += /DADSP_FLAG=1
endif

ifeq ($(SERIAL_IO_ENABLE), 1)
EXTERNAL_CC_FLAGS += /DSERIAL_IO_FLAG=1
endif

ifeq ($(USB_PRECONDITION_ENABLE), 1)
EXTERNAL_CC_FLAGS += /DUSB_PRECONDITION_ENABLE_FLAG=1
endif

ifeq ($(WDT_SUPPORT_ENABLE), 1)
EXTERNAL_CC_FLAGS += /DWDT_SUPPORT_ENABLED=1
endif

ifeq ($(SECURE_BOOT_ENABLE), 1)
EXTERNAL_CC_FLAGS += /DSECURE_BOOT_FLAG
endif

ifeq ($(STORAGE_FEATURE_EN), 1)
EXTERNAL_CC_FLAGS += /D MEM_NVDIMM_EN /D NVMEM_FEATURE_EN
endif

Prepare: DeleteRomFile

DeleteRomFile: 
ifeq ($(SecureMod_SUPPORT),1)
	if exist $(FWCAPSULE_FILE_NAME) $(RM) $(FWCAPSULE_FILE_NAME)
endif	
	if exist $(PROJECT_TAG)*.CAP $(RM) $(PROJECT_TAG)*.CAP
	if exist $(PROJECT_TAG)*.ROM $(RM) $(PROJECT_TAG)*.ROM
	if exist OutImage*.bin $(RM) OutImage*.bin
	
End : CreateBinFile

OUTPUT_DIR = $(BUILD_DIR)\$(PLATFORM_NAME)\$(TARGET)_$(TOOL_CHAIN_TAG)
export OUTPUT_DIR

.PHONY : CreateBinFile
CreateBinFile:
ifeq ($(SecureMod_SUPPORT),1)
    ifeq ($(wildcard $(FWpriv)), $(FWpriv))
	@echo ----- Copy Signed BIOS Image file to AMIROM.fd for RomImage"
	@copy /Y $(FWCAPSULE_FILE_NAME) $(OUTPUT_DIR)\FV\AMIROM.fd
    else
	@echo ----- Copy Unsigned BIOS Image file from AMIROM.fd"
	@copy /Y $(OUTPUT_DIR)\FV\AMIROM.fd $(BIOS_TAG).ROM
    endif
else
	@copy /Y $(OUTPUT_DIR)\FV\AMIROM.fd $(BIOS_TAG).ROM
endif
	@$(ECHO) Generating OutImage.bin
	@call GrantleyPkg\BuildOutImage.bat $(FTOOL_DIR) $(FITC_XML_DIR) $(FITC_FILE_NAME) $(FITC_NM_FILE_NAME)
ifeq ("$(FITC_NM_FILE_NAME)", "")
	@copy $(OUTPUT_DIR)\ROM\OutImage.bin OutImage.bin	
else
	@copy $(OUTPUT_DIR)\ROM\OutImage.bin OutImage.bin
	@copy $(OUTPUT_DIR)\ROM\OutImage_NM.bin OutImage_NM.bin
endif	
ifeq ($(SecureMod_SUPPORT),1)
    ifeq ($(wildcard $(FWpriv)), $(FWpriv))
	@$(ECHO) OutImage.bin and $(FWCAPSULE_FILE_NAME) binaries created.
    else
	@$(ECHO) OutImage.bin and $(BIOS_TAG).ROM binaries created.
    endif
else
	@$(ECHO) OutImage.bin and $(BIOS_TAG).ROM binaries created.
endif

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************