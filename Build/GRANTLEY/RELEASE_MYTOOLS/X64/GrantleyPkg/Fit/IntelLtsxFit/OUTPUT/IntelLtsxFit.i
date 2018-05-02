#line 1 "c:\\1218_alibaba\\GrantleyPkg\\Fit\\IntelLtsxFit.asm16"
#line 1 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\GrantleyPkg\\Fit\\IntelLtsxFit\\DEBUG\\AutoGen.h"















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


#line 17 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\GrantleyPkg\\Fit\\IntelLtsxFit\\DEBUG\\AutoGen.h"

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;









#line 30 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\GrantleyPkg\\Fit\\IntelLtsxFit\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\GrantleyPkg\\Fit\\IntelLtsxFit.asm16"
;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************

;**********************************************************************
; $Header: /Alaska/SOURCE/Modules/Intel LT-SX/FIT/IntelLtsxFit.asm 4     
;
; $Revision: 4 $
;
; $Date: 8/02/11 3:56p $
;**********************************************************************
; Revision History
; ----------------
;
; 
;**********************************************************************
;<AMI_FHDR_START>
;
; Name: IntelLtsxFit.asm
;
; Description:	
;
;<AMI_FHDR_END>
;**********************************************************************
include Token.equ

;**********************************************************************
;* FIT Related Definitions
;**********************************************************************

FIT_BB_SIZE        EQU     (MKF_FV_BB_BLOCKS*MKF_FLASH_BLOCK_SIZE)/16
FIT_BB_SIZE_UPPER  EQU     (FIT_BB_SIZE AND 0FF0000h) SHR 16

FIT_SIGNATURE      EQU     02020205F5449465Fh
AMI_TYPE_7_SIG     EQU     0ABCDEFFEDCBA0123h
AMI_LAST_ENTRY_SIG EQU     0ABCDEF0123456789h

IO_TYPE_VERSION    EQU     0000h

STD_FIT_ENTRY   STRUCT
    ADDRESS     QWORD   0000000000000000h
    LOWER_SIZE  WORD    0000h
    UPPER_SIZE  BYTE    00h
    RESERVED    BYTE    00h
    VERSION     WORD    0000h
    CV_TYPE     BYTE    00h
    CHECKSUM    BYTE    00h
STD_FIT_ENTRY   ENDS

CMOS_FIT_ENTRY   STRUCT
    INDEX_ADDRESS  WORD    MKF_LTSX_CMOS_INDEX_REG_ADDRESS
    DATA_ADDRESS   WORD    MKF_LTSX_CMOS_DATA_REG_ADDRESS
    ACCESS_WIDTH   BYTE    MKF_LTSX_CMOS_ACCESS_WIDTH
    BIT_POSITION   BYTE    00h
    INDEX          WORD    0000h
    UPPER_SIZE     WORD    0000h
    LOWER_SIZE     BYTE    00h
    RESERVED       BYTE    00h
    VERSION        WORD    IO_TYPE_VERSION
    CV_TYPE        BYTE    00h
    CHECKSUM       BYTE    00h
CMOS_FIT_ENTRY   ENDS

;**********************************************************************
;* FIT Entries
;**********************************************************************
FIT_TABLE       SEGMENT
        ; Mandatory type 0 entry.  DO NOT CHANGE THIS.
        FitHeader       STD_FIT_ENTRY  <FIT_SIGNATURE, \
                                        0000h, \
                                        00h, \
                                        00h, \
                                        0100h, \
                                        00h, \
                                        00h>
        ; Microcode type 1 entries.  These are filled out by the FIT utility.
        ; DO NOT CHANGE THIS directly.  Please modify the appropriate
        ; SDL tokens instead.
        MicroCode       STD_FIT_ENTRY  MKF_FIT_NUM_MICROCODE_PATCHES DUP ( \
                                       <0FFFFFFFFFFFFFFFFh, \
                                        0FFFFh, \
                                        0FFh, \
                                        0FFh, \
                                        0FFFFh, \
                                        0FFh, \
                                        0FFh>)
        ; Mandatory type 2 entry.
        ; DO NOT CHANGE THIS.
        Type2           STD_FIT_ENTRY  <MKF_FV_ACM_BASE, \
                                        0000h, \
                                        00h, \
                                        00h, \
                                        0100h, \
                                        02h, \
                                        00h>
        ; Placeholder type 7 entry for FIT type 7 and 8 entries.  DO NOT
        ; CHANGE THIS.
        Type7_0         STD_FIT_ENTRY  <AMI_TYPE_7_SIG, \
                                        0000h, \
                                        00h, \
                                        00h, \
                                        0100h, \
                                        07h, \
                                        00h>
        ; Bootblock type 7 entry.  This can be modified according to policy
        ; and or OEM needs.  Additional entries can be inserted as desired.
        Type7_1         STD_FIT_ENTRY  <MKF_FV_BB_BASE, \
                                        FIT_BB_SIZE AND 0FFFFh, \
                                        FIT_BB_SIZE_UPPER, \
                                        00h, \
                                        0100h, \
                                        07h, \
                                        00h>
        ; TPM type 8 entry.  This should be modified through the appropriate
        ; SDL tokens, but can be removed if desired.
        Type8           CMOS_FIT_ENTRY < , , , \
                                         MKF_LTSX_TPM_CMOS_BIT_POSITION, \
                                         MKF_LTSX_TPM_CMOS_ADDRESS, \
                                         0000h, \
                                         00h, \
                                         00h, \
                                         , \
                                         08h, \
                                         00h>
IF MKF_FIT_SIGNED_POLICY_SUPPORT ne 0
        ; BIOS Policy Record (Type 9).
        Type9           STD_FIT_ENTRY <00h, \
                                       00h, \
                                       00h, \
                                       00h, \
                                       0100h, \
                                       09h, \
                                       00h>                                       
ENDIF
        ; TXT Support type 10 entry.
        Type10          CMOS_FIT_ENTRY < , , , \
                                         MKF_LTSX_TXT_CMOS_BIT_POSITION, \
                                         MKF_LTSX_TXT_CMOS_ADDRESS, \
                                         0000h, \
                                         00h, \
                                         00h, \
                                         , \
                                         0Ah, \
                                         00h>

        ; Special signature for telling FIT utility we have reached the last
        ; entry.  Do not place any FIT entries after this!
        LastEntry       DQ             AMI_LAST_ENTRY_SIG

        
FIT_TABLE       ENDS

END
;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
