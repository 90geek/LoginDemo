#line 1 "c:\\1218_alibaba\\AmiCompatibilityPkg\\Smbios\\SmbiosBoard\\SmbiosStaticData\\SmbiosStaticData.asm16"
#line 1 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\AmiCompatibilityPkg\\Smbios\\SmbiosBoard\\SmbiosStaticData\\SmbiosStaticData\\DEBUG\\AutoGen.h"















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"



























#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"


























#pragma pack()
#line 29 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"



























#line 57 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"












#pragma warning ( disable : 4214 )




#pragma warning ( disable : 4100 )





#pragma warning ( disable : 4057 )




#pragma warning ( disable : 4127 )




#pragma warning ( disable : 4505 )




#pragma warning ( disable : 4206 )

#line 98 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"



  
  
  

  
  
  
  typedef unsigned __int64    UINT64;
  
  
  
  typedef __int64             INT64;
  
  
  
  typedef unsigned __int32    UINT32;
  
  
  
  typedef __int32             INT32;
  
  
  
  typedef unsigned short      UINT16;
  
  
  
  
  typedef unsigned short      CHAR16;
  
  
  
  typedef short               INT16;
  
  
  
  
  typedef unsigned char       BOOLEAN;
  
  
  
  typedef unsigned char       UINT8;
  
  
  
  typedef char                CHAR8;
  
  
  
  typedef signed char         INT8;















































#line 199 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"





typedef UINT64  UINTN;




typedef INT64   INTN;









































  
  
  
  
















#line 272 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"







#line 280 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"















#line 296 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"

#line 298 "c:\\1218_alibaba\\MdePkg\\Include\\X64\\ProcessorBind.h"

#line 29 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"























extern UINT8 _VerifySizeofBOOLEAN[(int)(sizeof(BOOLEAN) == (1)) /(int) (sizeof(BOOLEAN) == (1))];
extern UINT8 _VerifySizeofINT8[(int)(sizeof(INT8) == (1)) /(int) (sizeof(INT8) == (1))];
extern UINT8 _VerifySizeofUINT8[(int)(sizeof(UINT8) == (1)) /(int) (sizeof(UINT8) == (1))];
extern UINT8 _VerifySizeofINT16[(int)(sizeof(INT16) == (2)) /(int) (sizeof(INT16) == (2))];
extern UINT8 _VerifySizeofUINT16[(int)(sizeof(UINT16) == (2)) /(int) (sizeof(UINT16) == (2))];
extern UINT8 _VerifySizeofINT32[(int)(sizeof(INT32) == (4)) /(int) (sizeof(INT32) == (4))];
extern UINT8 _VerifySizeofUINT32[(int)(sizeof(UINT32) == (4)) /(int) (sizeof(UINT32) == (4))];
extern UINT8 _VerifySizeofINT64[(int)(sizeof(INT64) == (8)) /(int) (sizeof(INT64) == (8))];
extern UINT8 _VerifySizeofUINT64[(int)(sizeof(UINT64) == (8)) /(int) (sizeof(UINT64) == (8))];
extern UINT8 _VerifySizeofCHAR8[(int)(sizeof(CHAR8) == (1)) /(int) (sizeof(CHAR8) == (1))];
extern UINT8 _VerifySizeofCHAR16[(int)(sizeof(CHAR16) == (2)) /(int) (sizeof(CHAR16) == (2))];







  
  
  
  
  
  







#line 84 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"























#line 108 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"
  
#line 110 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"








  
#line 120 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"





typedef struct {
  UINT32  Data1;
  UINT16  Data2;
  UINT16  Data3;
  UINT8   Data4[8];
} GUID;




typedef UINT64 PHYSICAL_ADDRESS;




typedef struct _LIST_ENTRY LIST_ENTRY;




struct _LIST_ENTRY {
  LIST_ENTRY  *ForwardLink;
  LIST_ENTRY  *BackLink;
};










































































































































































































































































































































#line 480 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"


















#line 499 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"




typedef CHAR8 *VA_LIST;






























































#line 567 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"




typedef UINTN  *BASE_LIST;

















































#line 622 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"

















































































































typedef UINTN RETURN_STATUS;































































































































































































































































































#line 1024 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"


#line 17 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\AmiCompatibilityPkg\\Smbios\\SmbiosBoard\\SmbiosStaticData\\SmbiosStaticData\\DEBUG\\AutoGen.h"

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;









#line 30 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\AmiCompatibilityPkg\\Smbios\\SmbiosBoard\\SmbiosStaticData\\SmbiosStaticData\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\AmiCompatibilityPkg\\Smbios\\SmbiosBoard\\SmbiosStaticData\\SmbiosStaticData.asm16"
;****************************************************************************
;****************************************************************************
;**                                                                        **
;**           (C)Copyright 1985-2012, American Megatrends, Inc.            **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**            5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093           **
;**                                                                        **
;**                          Phone: (770)-246-8600                         **
;**                                                                        **
;****************************************************************************
;****************************************************************************

;****************************************************************************
; $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosStaticData/SmbiosStaticData.asm 10    3/26/12 12:02p Davidd $
;
; $Revision: 10 $
;
; $Date: 3/26/12 12:02p $
;****************************************************************************

;----------------------------------------------------------------------------

        INCLUDE token.equ
        INCLUDE smbhdr.equ
        INCLUDE smbmacro.aid
        INCLUDE smbstruc.def
        INCLUDE smb.equ
        INCLUDE smbdata.mac
;ZA0044>>>
IF MKF_Foxconn_SUPPORT
        INCLUDE FoxconnPkg\OemSmbdesc.def
ELSE
;ZA0044<<<
        INCLUDE smbdesc.def
ENDIF	;ZA0044

;----------------------------------------------------------------------------

SMBIOS_DSEG SEGMENT BYTE    PUBLIC  'DATA'
        ASSUME  cs: SMBIOS_DSEG
.586p

;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
        PUBLIC  _SMBDATA_STARTS
_smbdata_starts         LABEL   BYTE    ; Marks start of module
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
;   SMBIOS DATA STRUCTURES
;----------------------------------------------------------------------------

;SMBDataModuleHeaderSTRUC   {'_AMIDMI_',0203h,0101h,00h,offset smbios_structures_end,00h}

;----------------------------------------------------------------------------
        PUBLIC  smbios_structures_start
smbios_structures_start LABEL   BYTE

        handle = 0
IF MKF_TYPE0_STRUCTURE
        handle = CreateBiosInfo(handle)
ENDIF
IF MKF_TYPE1_STRUCTURE
        handle = CreateSysInfo(handle)
ENDIF
IF MKF_TYPE2_STRUCTURE
        handle = CreateBaseBoardInfo(handle)
ENDIF
IF MKF_TYPE3_STRUCTURE
        handle = CreateSysChassisInfo(handle)
ENDIF
IF MKF_TYPE4_STRUCTURE
        handle = CreateProcessorInfo(handle)
ENDIF
IF MKF_TYPE5_STRUCTURE
        handle = CreateMemCtrlInfo(handle, handle+1)
ENDIF
IF MKF_TYPE6_STRUCTURE
        handle = CreateMemModuleInfo(handle)
ENDIF
IF MKF_TYPE7_STRUCTURE
        handle = CreateExternalCacheInfo(handle)
ENDIF
IF MKF_TYPE8_STRUCTURE
        handle = CreatePortConnectorInfo(handle)
ENDIF
IF MKF_TYPE9_STRUCTURE
        handle = CreateSystemSlotInfo(handle)
ENDIF
IF MKF_TYPE10_STRUCTURE
        handle = CreateOnboardDeviceInfo(handle)
ENDIF
IF MKF_TYPE11_STRUCTURE
        handle = CreateOemStringInfo(handle)
ENDIF
IF MKF_TYPE12_STRUCTURE
        handle = CreateSystemConfigOptionInfo(handle)
ENDIF
IF MKF_TYPE15_STRUCTURE
        handle = CreateEventLogInfo(handle)
ENDIF
IF MKF_TYPE16_STRUCTURE
        handle = CreateMemoryInfo(handle)
ENDIF
IF MKF_FLASH_MEMORY_ARRAY_INFO
        handle = CreateFlashMemoryInfo(handle)
ENDIF
IF MKF_TYPE21_STRUCTURE
        handle = CreateBuiltinPointingDeviceInfo(handle)
ENDIF
IF MKF_TYPE22_STRUCTURE
        handle = CreatePortableBatteryInfo(handle)
ENDIF
IF MKF_TYPE23_STRUCTURE
        handle = CreateSystemResetInfo(handle)
ENDIF
IF MKF_TYPE24_STRUCTURE
        handle = CreateHardwareSecurityInfo(handle)
ENDIF
IF MKF_TYPE25_STRUCTURE
        handle = CreateSystemPowerControlsInfo(handle)
ENDIF
IF MKF_TYPE30_STRUCTURE
        handle = CreateOutofBandRemoteAccessInfo(handle)
ENDIF
IF MKF_TYPE31_STRUCTURE
        handle = CreateBootIntegrityServicesInfo(handle)
ENDIF
IF MKF_TYPE32_STRUCTURE
        handle = CreateSystemBootInfo(handle)
ENDIF
IF MKF_TYPE33_STRUCTURE
        handle = CreateSixtyFourBitMemoryErrorInfo(handle)
ENDIF
IF MKF_TYPE34_STRUCTURE
        handle = CreateManagementDeviceInfo(handle)
ENDIF
IF MKF_TYPE37_STRUCTURE
        handle = CreateMemoryChannelInfo(handle)
ENDIF
IF MKF_TYPE39_STRUCTURE
        handle = CreateSystemPowerSupplyInfo(handle)
ENDIF
IF MKF_TYPE40_STRUCTURE
        handle = CreateAdditionalInformation(handle)
ENDIF
IF MKF_TYPE41_STRUCTURE
        handle = CreateOnboardDevicesExtendedInfo(handle)
ENDIF
IF MKF_TYPE241_STRUCTURE
        handle = CreateOEMMemoryMappedGpnvInfo(handle)
ENDIF
IF MKF_TYPE240_STRUCTURE
        handle = CreateOEMIOMappedGpnvInfo(handle)
ENDIF
IF MKF_TYPE38_STRUCTURE
        handle = CreateIPMIDeviceInfo(handle)
ENDIF
IF MKF_TYPE129_STRUCTURE
        handle = CreateIntelASFTable(handle)
ENDIF
        handle = CreateEndOfTable(handle)

        db      MKF_EXTRA_RESERVED_BYTES dup (0FFh)          ; Extra Space

SMBIOS_DSEG    ENDS                 ; End of Segment
END                                 ; End of File

;----------------------------------------------------------------------------
;****************************************************************************
;****************************************************************************
;**                                                                        **
;**           (C)Copyright 1985-2012, American Megatrends, Inc.            **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**            5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093           **
;**                                                                        **
;**                          Phone: (770)-246-8600                         **
;**                                                                        **
;****************************************************************************
;****************************************************************************
