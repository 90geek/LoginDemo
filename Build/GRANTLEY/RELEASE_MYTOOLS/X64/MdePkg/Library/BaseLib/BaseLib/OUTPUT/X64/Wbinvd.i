#line 1 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\X64\\Wbinvd.asm"
#line 1 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\MdePkg\\Library\\BaseLib\\BaseLib\\DEBUG\\AutoGen.h"















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


#line 17 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\MdePkg\\Library\\BaseLib\\BaseLib\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Library/PcdLib.h"












































































































































































































































































































































































































































































































































                                            


















































































































































































































































































                                         
















UINTN
__cdecl
LibPcdSetSku (
   UINTN   SkuId
  );












UINT8
__cdecl
LibPcdGet8 (
   UINTN             TokenNumber
  );












UINT16
__cdecl
LibPcdGet16 (
   UINTN             TokenNumber
  );












UINT32
__cdecl
LibPcdGet32 (
   UINTN             TokenNumber
  );












UINT64
__cdecl
LibPcdGet64 (
   UINTN             TokenNumber
  );












void *
__cdecl
LibPcdGetPtr (
   UINTN             TokenNumber
  );












BOOLEAN 
__cdecl
LibPcdGetBool (
   UINTN             TokenNumber
  );










UINTN
__cdecl
LibPcdGetSize (
   UINTN             TokenNumber
  );
















UINT8
__cdecl
LibPcdGetEx8 (
   const GUID        *Guid,
   UINTN             TokenNumber
  );
















UINT16
__cdecl
LibPcdGetEx16 (
   const GUID        *Guid,
   UINTN             TokenNumber
  );













UINT32
__cdecl
LibPcdGetEx32 (
   const GUID        *Guid,
   UINTN             TokenNumber
  );
















UINT64
__cdecl
LibPcdGetEx64 (
   const GUID        *Guid,
   UINTN             TokenNumber
  );
















void *
__cdecl
LibPcdGetExPtr (
   const GUID        *Guid,
   UINTN             TokenNumber
  );
















BOOLEAN
__cdecl
LibPcdGetExBool (
   const GUID        *Guid,
   UINTN             TokenNumber
  );
















UINTN
__cdecl
LibPcdGetExSize (
   const GUID        *Guid,
   UINTN             TokenNumber
  );
















UINT8
__cdecl
LibPcdSet8 (
   UINTN             TokenNumber,
   UINT8             Value
  );
















UINT16
__cdecl
LibPcdSet16 (
   UINTN             TokenNumber,
   UINT16            Value
  );
















UINT32
__cdecl
LibPcdSet32 (
   UINTN             TokenNumber,
   UINT32            Value
  );
















UINT64
__cdecl
LibPcdSet64 (
   UINTN             TokenNumber,
   UINT64            Value
  );

























void *
__cdecl
LibPcdSetPtr (
          UINTN             TokenNumber,
       UINTN             *SizeOfBuffer,
   const  void              *Buffer
  );
















BOOLEAN
__cdecl
LibPcdSetBool (
   UINTN             TokenNumber,
   BOOLEAN           Value
  );



















UINT8
__cdecl
LibPcdSetEx8 (
   const GUID        *Guid,
   UINTN             TokenNumber,
   UINT8             Value
  );



















UINT16
__cdecl
LibPcdSetEx16 (
   const GUID        *Guid,
   UINTN             TokenNumber,
   UINT16            Value
  );



















UINT32
__cdecl
LibPcdSetEx32 (
   const GUID        *Guid,
   UINTN             TokenNumber,
   UINT32            Value
  );



















UINT64
__cdecl
LibPcdSetEx64 (
   const GUID        *Guid,
   UINTN             TokenNumber,
   UINT64            Value
  );
























void *
__cdecl
LibPcdSetExPtr (
        const GUID        *Guid,
        UINTN             TokenNumber,
     UINTN             *SizeOfBuffer,
        void              *Buffer
  );



















BOOLEAN
__cdecl
LibPcdSetExBool (
   const GUID        *Guid,
   UINTN             TokenNumber,
   BOOLEAN           Value
  );


















typedef
void
(__cdecl *PCD_CALLBACK)(
          const GUID        *CallBackGuid, 
          UINTN             CallBackToken,
       void              *TokenData,
          UINTN             TokenDataSize
  );


















void
__cdecl
LibPcdCallbackOnSet (
   const GUID               *Guid,       
   UINTN                    TokenNumber,
   PCD_CALLBACK             NotificationFunction
  );















void
__cdecl
LibPcdCancelCallback (
   const GUID               *Guid,       
   UINTN                    TokenNumber,
   PCD_CALLBACK             NotificationFunction
  );





















UINTN           
__cdecl
LibPcdGetNextToken (
   const GUID               *Guid,       
   UINTN                    TokenNumber
  );
















GUID *
__cdecl
LibPcdGetNextTokenSpace (
   const GUID  *TokenSpaceGuid
  );

























void *
__cdecl
LibPatchPcdSetPtr (
          void        *PatchVariable,
          UINTN       MaximumDatumSize,
       UINTN       *SizeOfBuffer,
   const  void        *Buffer
  );

typedef enum {
  PCD_TYPE_8,
  PCD_TYPE_16,
  PCD_TYPE_32,
  PCD_TYPE_64,
  PCD_TYPE_BOOL,
  PCD_TYPE_PTR
} PCD_TYPE;

typedef struct {
  
  
  
  
  PCD_TYPE          PcdType;
  
  
  
  
  UINTN             PcdSize;
  
  
  
  
  
  
  CHAR8             *PcdName;
} PCD_INFO;














void
__cdecl
LibPcdGetInfo (
          UINTN           TokenNumber,
         PCD_INFO        *PcdInfo
  );














void
__cdecl
LibPcdGetInfoEx (
   const  GUID            *Guid,
          UINTN           TokenNumber,
         PCD_INFO        *PcdInfo
  );










UINTN
__cdecl
LibPcdGetSku (
  void
  );

#line 1635 "c:\\1218_alibaba\\MdePkg\\Include\\Library/PcdLib.h"

#line 18 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\MdePkg\\Library\\BaseLib\\BaseLib\\DEBUG\\AutoGen.h"

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;



extern GUID gEfiMdePkgTokenSpaceGuid;



extern const BOOLEAN _gPcd_FixedAtBuild_PcdVerifyNodeInList;



extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumLinkedListLength;





extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumAsciiStringLength;





extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumUnicodeStringLength;










#line 56 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\MdePkg\\Library\\BaseLib\\BaseLib\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\X64\\Wbinvd.asm"
;------------------------------------------------------------------------------
;
; Copyright (c) 2006, Intel Corporation. All rights reserved.<BR>
; This program and the accompanying materials
; are licensed and made available under the terms and conditions of the BSD License
; which accompanies this distribution.  The full text of the license may be found at
; http:
;
; THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
; WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
;
; Module Name:
;
;   Wbinvd.Asm
;
; Abstract:
;
;   AsmWbinvd function
;
; Notes:
;
;------------------------------------------------------------------------------

    .code

;------------------------------------------------------------------------------
; void
; __cdecl
; AsmWbinvd (
;   void
;   );
;------------------------------------------------------------------------------
AsmWbinvd   PROC
    wbinvd
    ret
AsmWbinvd   ENDP

    END
