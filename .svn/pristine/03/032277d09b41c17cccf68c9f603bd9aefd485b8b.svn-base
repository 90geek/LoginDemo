#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
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
#---------------------------------------------------------------------------
# Name:     ProcessorStartup.mak
#
# Description:  
#   Make file for SEC.
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>

NumBistFunc := $(words $(GetBistFunc))

Prepare : DETECT_ERRORS 

DETECT_ERRORS:
ifneq ($(NumBistFunc), 1)
	$(error There should only be one BIST function. ELINK PS_GetBist is incorrect. See sample in ProcessorStartup.sdl.)
endif

