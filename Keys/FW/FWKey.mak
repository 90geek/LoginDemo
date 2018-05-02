#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
#<AMI_FHDR_START>
#
# Name: FWKey.mak
#
# Description: Include FWkey ffs with Root Platform key into the BIOS FV_BB
# 
#<AMI_FHDR_END>
#*************************************************************************
#-------------------------------------------------------------------------
#   Include Platform Firmware Root Key (FWKey) .FFS
#-------------------------------------------------------------------------
Prepare: $(BUILD_DIR)$(PATH_SLASH)FWKEY.BIN

ifneq ($(wildcard $(FWpub)), $(FWpub))
#-------------------------------------------------------------------------
#   FWpub key is not available at build
#   Create a dummy key placeholder file that will be updated with the 
#   real pub key at the time of signing the BIOS image
#-------------------------------------------------------------------------
ifeq ($(BUILD_OS), $(BUILD_OS_LINUX))
$(warning  *** )
$(warning  *** Missing RSA public key FWpub=$(FWpub) to verify Signed BIOS updates.)
$(warning  *** The Key is placed inside BIOS RTU (FV_BB) to verify signed BIOS updates.)
ifeq ($(FWCAPSULE_CERT_FORMAT),1)
$(error  *** Expected key file format: X.509 DER encoded Key Certificate(CER, PEM))
else
$(error  *** Expected key file format: Public portion of 2048bit RSA Key in PKCS#1v2.1 DER (PEM) format)
endif
endif
$(BUILD_DIR)$(PATH_SLASH)FWKEY.BIN: $(FWKey_DIR)$(PATH_SLASH)FWKey.mak
#Merge64 FwKey pad.
	$(ECHO)  \
"output$(EOL)\
    FWKEY_FILE($@)$(EOL)\
end$(EOL)\
group FWKEY_FILE$(EOL)\
    upper=0xffffffff$(EOL)\
components$(EOL)\
blank MICROCODE_PAD$(EOL)\
    size=$(FWKEY_FILE_SIZE)$(EOL)\
    pattern=(0xFF)$(EOL)\
end$(EOL)\
end end"\
>$(BUILD_DIR)$(PATH_SLASH)Fwkey.ini
	Merge64 /s $(BUILD_DIR)$(PATH_SLASH)Fwkey.ini
#-------------------------------------------------------------------------
else  
#-------------------------------------------------------------------------
#   FWpub key is present
#   Prepare Platform Firmware Root Key (FWKey) bin file
#-------------------------------------------------------------------------
$(BUILD_DIR)$(PATH_SLASH)FWKEY.BIN: $(FWpub)
ifeq ($(FWCAPSULE_CERT_FORMAT),1)
#x509 Cert Key
	$(CP) $< $@
ifeq ($(FWKEY_FILE_FORMAT),1)
#get SHA256 Hash of x509 Tbs cert section. Supported from Cryptocon.exe v4.7.31.2014
	$(CRYPTCON) -h2 -x $@ -o $@
endif	
ifeq ($(FWKEY_FILE_FORMAT),0)
$(error  *** Unsupported FWKEY_FILE_FORMAT(0). Please select between (1) SHA256 hash certificate or (2) X.509 DER encoded Key Certificate)
endif
else
#Extract 256byte n-modulus from x509 DER or PKCS#1v2 ASN.1 encoded RSA Key
# n-modulus can be extracted either from Public Key FWpub or full RSA Key FWpriv files
	$(CRYPTCON) -w -k $< -o $@
ifeq ($(FWKEY_FILE_FORMAT),1)
#get SHA256 Hash of n-modulus of RSA Key
	$(CRYPTCON) -h2 -f $@ -o $@
endif
endif

endif #ifneq ($(wildcard $(FWpub)), $(FWpub))
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
