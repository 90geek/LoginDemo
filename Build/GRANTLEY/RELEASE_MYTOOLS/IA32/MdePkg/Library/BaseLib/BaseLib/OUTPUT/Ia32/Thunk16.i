#line 1 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\Ia32\\Thunk16.asm"
#line 1 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\MdePkg\\Library\\BaseLib\\BaseLib\\DEBUG\\AutoGen.h"















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"



























#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"


























#pragma pack()
#line 29 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"


























#line 56 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"












#pragma warning ( disable : 4214 )




#pragma warning ( disable : 4100 )





#pragma warning ( disable : 4057 )




#pragma warning ( disable : 4127 )




#pragma warning ( disable : 4505 )




#pragma warning ( disable : 4206 )

#line 97 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"




  
  
  

  
  
  
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















































#line 199 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"





typedef UINT32  UINTN;




typedef INT32   INTN;








































  
  
  
  











#line 266 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"







#line 274 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"















#line 290 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"

#line 292 "c:\\1218_alibaba\\MdePkg\\Include\\Ia32\\ProcessorBind.h"

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


#line 17 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\MdePkg\\Library\\BaseLib\\BaseLib\\DEBUG\\AutoGen.h"
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

#line 18 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\MdePkg\\Library\\BaseLib\\BaseLib\\DEBUG\\AutoGen.h"

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;



extern GUID gEfiMdePkgTokenSpaceGuid;



extern const BOOLEAN _gPcd_FixedAtBuild_PcdVerifyNodeInList;



extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumLinkedListLength;





extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumAsciiStringLength;





extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumUnicodeStringLength;










#line 56 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\MdePkg\\Library\\BaseLib\\BaseLib\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\Ia32\\Thunk16.asm"

#line 1 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\BaseLibInternals.h"

















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"

































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































#line 19 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\BaseLibInternals.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"


























typedef struct {
  UINT32                            Ebx;
  UINT32                            Esi;
  UINT32                            Edi;
  UINT32                            Ebp;
  UINT32                            Esp;
  UINT32                            Eip;
} BASE_LIBRARY_JUMP_BUFFER;



#line 39 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"

















































#line 89 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"






















#line 112 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"















#line 128 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"



















#line 148 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"































#line 180 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"





























CHAR16 *
__cdecl
StrCpy (
       CHAR16                    *Destination,
        const CHAR16              *Source
  );
































CHAR16 *
__cdecl
StrnCpy (
       CHAR16                    *Destination,
        const CHAR16              *Source,
        UINTN                     Length
  );



















UINTN
__cdecl
StrLen (
        const CHAR16              *String
  );




















UINTN
__cdecl
StrSize (
        const CHAR16              *String
  );






























INTN
__cdecl
StrCmp (
        const CHAR16              *FirstString,
        const CHAR16              *SecondString
  );


































INTN
__cdecl
StrnCmp (
        const CHAR16              *FirstString,
        const CHAR16              *SecondString,
        UINTN                     Length
  );


































CHAR16 *
__cdecl
StrCat (
     CHAR16                    *Destination,
        const CHAR16              *Source
  );








































CHAR16 *
__cdecl
StrnCat (
     CHAR16                    *Destination,
        const CHAR16              *Source,
        UINTN                     Length
  );


























CHAR16 *
__cdecl
StrStr (
        const CHAR16              *String,
        const CHAR16              *SearchString
  );



































UINTN
__cdecl
StrDecimalToUintn (
        const CHAR16              *String
  );



































UINT64
__cdecl
StrDecimalToUint64 (
        const CHAR16              *String
  );
 




































UINTN
__cdecl
StrHexToUintn (
        const CHAR16              *String
  );





































UINT64
__cdecl
StrHexToUint64 (
        const CHAR16             *String
  );


































CHAR8 *
__cdecl
UnicodeStrToAsciiStr (
        const CHAR16              *Source,
       CHAR8                     *Destination
  );























CHAR8 *
__cdecl
AsciiStrCpy (
       CHAR8                     *Destination,
        const CHAR8               *Source
  );





























CHAR8 *
__cdecl
AsciiStrnCpy (
       CHAR8                     *Destination,
        const CHAR8               *Source,
        UINTN                     Length
  );



















UINTN
__cdecl
AsciiStrLen (
        const CHAR8               *String
  );



















UINTN
__cdecl
AsciiStrSize (
        const CHAR8               *String
  );




























INTN
__cdecl
AsciiStrCmp (
        const CHAR8               *FirstString,
        const CHAR8               *SecondString
  );































INTN
__cdecl
AsciiStriCmp (
        const CHAR8               *FirstString,
        const CHAR8               *SecondString
  );
































INTN
__cdecl
AsciiStrnCmp (
        const CHAR8               *FirstString,
        const CHAR8               *SecondString,
        UINTN                     Length
  );





























CHAR8 *
__cdecl
AsciiStrCat (
    CHAR8    *Destination,
   const CHAR8  *Source
  );






































CHAR8 *
__cdecl
AsciiStrnCat (
     CHAR8                     *Destination,
        const CHAR8               *Source,
        UINTN                     Length
  );


























CHAR8 *
__cdecl
AsciiStrStr (
        const CHAR8               *String,
        const CHAR8               *SearchString
  );
































UINTN
__cdecl
AsciiStrDecimalToUintn (
        const CHAR8               *String
  );
































UINT64
__cdecl
AsciiStrDecimalToUint64 (
        const CHAR8               *String
  );




































UINTN
__cdecl
AsciiStrHexToUintn (
        const CHAR8               *String
  );




































UINT64
__cdecl
AsciiStrHexToUint64 (
        const CHAR8                *String
  );





























CHAR16 *
__cdecl
AsciiStrToUnicodeStr (
        const CHAR8               *Source,
       CHAR16                    *Destination
  );















UINT8
__cdecl
DecimalToBcd8 (
        UINT8                     Value
  );
















UINT8
__cdecl
BcdToDecimal8 (
        UINT8                     Value
  );







































LIST_ENTRY *
__cdecl
InitializeListHead (
     LIST_ENTRY                *ListHead
  );
























LIST_ENTRY *
__cdecl
InsertHeadList (
     LIST_ENTRY                *ListHead,
     LIST_ENTRY                *Entry
  );
























LIST_ENTRY *
__cdecl
InsertTailList (
     LIST_ENTRY                *ListHead,
     LIST_ENTRY                *Entry
  );






















LIST_ENTRY *
__cdecl
GetFirstNode (
        const LIST_ENTRY          *List
  );























LIST_ENTRY *
__cdecl
GetNextNode (
        const LIST_ENTRY          *List,
        const LIST_ENTRY          *Node
  );

  





















LIST_ENTRY *
__cdecl
GetPreviousNode (
        const LIST_ENTRY          *List,
        const LIST_ENTRY          *Node
  );

  



















BOOLEAN
__cdecl
IsListEmpty (
        const LIST_ENTRY          *ListHead
  );




























BOOLEAN
__cdecl
IsNull (
        const LIST_ENTRY          *List,
        const LIST_ENTRY          *Node
  );

























BOOLEAN
__cdecl
IsNodeAtEnd (
        const LIST_ENTRY          *List,
        const LIST_ENTRY          *Node
  );




























LIST_ENTRY *
__cdecl
SwapListEntries (
     LIST_ENTRY                *FirstEntry,
     LIST_ENTRY                *SecondEntry
  );























LIST_ENTRY *
__cdecl
RemoveEntryList (
        const LIST_ENTRY          *Entry
  );




















UINT64
__cdecl
LShiftU64 (
        UINT64                    Operand,
        UINTN                     Count
  );

















UINT64
__cdecl
RShiftU64 (
        UINT64                    Operand,
        UINTN                     Count
  );

















UINT64
__cdecl
ARShiftU64 (
        UINT64                    Operand,
        UINTN                     Count
  );


















UINT32
__cdecl
LRotU32 (
        UINT32                    Operand,
        UINTN                     Count
  );


















UINT32
__cdecl
RRotU32 (
        UINT32                    Operand,
        UINTN                     Count
  );


















UINT64
__cdecl
LRotU64 (
        UINT64                    Operand,
        UINTN                     Count
  );


















UINT64
__cdecl
RRotU64 (
        UINT64                    Operand,
        UINTN                     Count
  );















INTN
__cdecl
LowBitSet32 (
        UINT32                    Operand
  );
















INTN
__cdecl
LowBitSet64 (
        UINT64                    Operand
  );
















INTN
__cdecl
HighBitSet32 (
        UINT32                    Operand
  );
















INTN
__cdecl
HighBitSet64 (
        UINT64                    Operand
  );















UINT32
__cdecl
GetPowerOfTwo32 (
        UINT32                    Operand
  );















UINT64
__cdecl
GetPowerOfTwo64 (
        UINT64                    Operand
  );














UINT16
__cdecl
SwapBytes16 (
        UINT16                    Value
  );














UINT32
__cdecl
SwapBytes32 (
        UINT32                    Value
  );














UINT64
__cdecl
SwapBytes64 (
        UINT64                    Value
  );
















UINT64
__cdecl
MultU64x32 (
        UINT64                    Multiplicand,
        UINT32                    Multiplier
  );
















UINT64
__cdecl
MultU64x64 (
        UINT64                    Multiplicand,
        UINT64                    Multiplier
  );
















INT64
__cdecl
MultS64x64 (
        INT64                     Multiplicand,
        INT64                     Multiplier
  );


















UINT64
__cdecl
DivU64x32 (
        UINT64                    Dividend,
        UINT32                    Divisor
  );


















UINT32
__cdecl
ModU64x32 (
        UINT64                    Dividend,
        UINT32                    Divisor
  );





















UINT64
__cdecl
DivU64x32Remainder (
        UINT64                    Dividend,
        UINT32                    Divisor,
       UINT32                    *Remainder  
  );





















UINT64
__cdecl
DivU64x64Remainder (
        UINT64                    Dividend,
        UINT64                    Divisor,
       UINT64                    *Remainder  
  );

























INT64
__cdecl
DivS64x64Remainder (
        INT64                     Dividend,
        INT64                     Divisor,
       INT64                     *Remainder  
  );















UINT16
__cdecl
ReadUnaligned16 (
   const UINT16              *Buffer
  );

















UINT16
__cdecl
WriteUnaligned16 (
   UINT16                    *Buffer,
    UINT16                    Value
  );















UINT32
__cdecl
ReadUnaligned24 (
   const UINT32              *Buffer
  );

















UINT32
__cdecl
WriteUnaligned24 (
   UINT32                    *Buffer,
    UINT32                    Value
  );















UINT32
__cdecl
ReadUnaligned32 (
   const UINT32              *Buffer
  );

















UINT32
__cdecl
WriteUnaligned32 (
   UINT32                    *Buffer,
    UINT32                    Value
  );















UINT64
__cdecl
ReadUnaligned64 (
   const UINT64              *Buffer
  );

















UINT64
__cdecl
WriteUnaligned64 (
   UINT64                    *Buffer,
    UINT64                    Value
  );

























UINT8
__cdecl
BitFieldRead8 (
        UINT8                     Operand,
        UINTN                     StartBit,
        UINTN                     EndBit
  );

























UINT8
__cdecl
BitFieldWrite8 (
        UINT8                     Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT8                     Value
  );


























UINT8
__cdecl
BitFieldOr8 (
        UINT8                     Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT8                     OrData
  );


























UINT8
__cdecl
BitFieldAnd8 (
        UINT8                     Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT8                     AndData
  );





























UINT8
__cdecl
BitFieldAndThenOr8 (
        UINT8                     Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT8                     AndData,
        UINT8                     OrData
  );





















UINT16
__cdecl
BitFieldRead16 (
        UINT16                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit
  );

























UINT16
__cdecl
BitFieldWrite16 (
        UINT16                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT16                    Value
  );


























UINT16
__cdecl
BitFieldOr16 (
        UINT16                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT16                    OrData
  );


























UINT16
__cdecl
BitFieldAnd16 (
        UINT16                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT16                    AndData
  );





























UINT16
__cdecl
BitFieldAndThenOr16 (
        UINT16                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT16                    AndData,
        UINT16                    OrData
  );





















UINT32
__cdecl
BitFieldRead32 (
        UINT32                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit
  );

























UINT32
__cdecl
BitFieldWrite32 (
        UINT32                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT32                    Value
  );


























UINT32
__cdecl
BitFieldOr32 (
        UINT32                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT32                    OrData
  );


























UINT32
__cdecl
BitFieldAnd32 (
        UINT32                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT32                    AndData
  );





























UINT32
__cdecl
BitFieldAndThenOr32 (
        UINT32                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT32                    AndData,
        UINT32                    OrData
  );





















UINT64
__cdecl
BitFieldRead64 (
        UINT64                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit
  );

























UINT64
__cdecl
BitFieldWrite64 (
        UINT64                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT64                    Value
  );


























UINT64
__cdecl
BitFieldOr64 (
        UINT64                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT64                    OrData
  );


























UINT64
__cdecl
BitFieldAnd64 (
        UINT64                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT64                    AndData
  );





























UINT64
__cdecl
BitFieldAndThenOr64 (
        UINT64                    Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT64                    AndData,
        UINT64                    OrData
  );























UINT8
__cdecl
CalculateSum8 (
        const UINT8              *Buffer,
        UINTN                     Length
  );




















UINT8
__cdecl
CalculateCheckSum8 (
        const UINT8              *Buffer,
        UINTN                     Length
  );





















UINT16
__cdecl
CalculateSum16 (
        const UINT16             *Buffer,
        UINTN                     Length
  );






















UINT16
__cdecl
CalculateCheckSum16 (
        const UINT16             *Buffer,
        UINTN                     Length
  );





















UINT32
__cdecl
CalculateSum32 (
        const UINT32             *Buffer,
        UINTN                     Length
  );






















UINT32
__cdecl
CalculateCheckSum32 (
        const UINT32             *Buffer,
        UINTN                     Length
  );





















UINT64
__cdecl
CalculateSum64 (
        const UINT64             *Buffer,
        UINTN                     Length
  );






















UINT64
__cdecl
CalculateCheckSum64 (
        const UINT64             *Buffer,
        UINTN                     Length
  );













typedef
void
(__cdecl *SWITCH_STACK_ENTRY_POINT)(
        void                      *Context1,  
        void                      *Context2   
  );









void
__cdecl
MemoryFence (
  void
  );























UINTN
__cdecl
SetJump (
       BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer
  );


















void
__cdecl
LongJump (
        BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer,
        UINTN                     Value
  );






void
__cdecl
EnableInterrupts (
  void
  );






void
__cdecl
DisableInterrupts (
  void
  );










BOOLEAN
__cdecl
SaveAndDisableInterrupts (
  void
  );







void
__cdecl
EnableDisableInterrupts (
  void
  );












BOOLEAN
__cdecl
GetInterruptState (
  void
  );
















BOOLEAN
__cdecl
SetInterruptState (
        BOOLEAN                   InterruptState
  );









void
__cdecl
CpuPause (
  void
  );































void
__cdecl
SwitchStack (
        SWITCH_STACK_ENTRY_POINT  EntryPoint,
        void                      *Context1,  
        void                      *Context2,  
        void                      *NewStack,
  ...
  );









void
__cdecl
CpuBreakpoint (
  void
  );











void
__cdecl
CpuDeadLoop (
  void
  );
 














































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































#line 4874 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"






typedef union {
  struct {
    UINT32  CF:1;           
    UINT32  Reserved_0:1;   
    UINT32  PF:1;           
    UINT32  Reserved_1:1;   
    UINT32  AF:1;           
    UINT32  Reserved_2:1;   
    UINT32  ZF:1;           
    UINT32  SF:1;           
    UINT32  TF:1;           
    UINT32  IF:1;           
    UINT32  DF:1;           
    UINT32  OF:1;           
    UINT32  IOPL:2;         
    UINT32  NT:1;           
    UINT32  Reserved_3:1;   
  } Bits;
  UINT16    Uint16;
} IA32_FLAGS16;






typedef union {
  struct {
    UINT32  CF:1;           
    UINT32  Reserved_0:1;   
    UINT32  PF:1;           
    UINT32  Reserved_1:1;   
    UINT32  AF:1;           
    UINT32  Reserved_2:1;   
    UINT32  ZF:1;           
    UINT32  SF:1;           
    UINT32  TF:1;           
    UINT32  IF:1;           
    UINT32  DF:1;           
    UINT32  OF:1;           
    UINT32  IOPL:2;         
    UINT32  NT:1;           
    UINT32  Reserved_3:1;   
    UINT32  RF:1;           
    UINT32  VM:1;           
    UINT32  AC:1;           
    UINT32  VIF:1;          
    UINT32  VIP:1;          
    UINT32  ID:1;           
    UINT32  Reserved_4:10;  
  } Bits;
  UINTN     UintN;
} IA32_EFLAGS32;






typedef union {
  struct {
    UINT32  PE:1;           
    UINT32  MP:1;           
    UINT32  EM:1;           
    UINT32  TS:1;           
    UINT32  ET:1;           
    UINT32  NE:1;           
    UINT32  Reserved_0:10;  
    UINT32  WP:1;           
    UINT32  Reserved_1:1;   
    UINT32  AM:1;           
    UINT32  Reserved_2:10;  
    UINT32  NW:1;           
    UINT32  CD:1;           
    UINT32  PG:1;           
  } Bits;
  UINTN     UintN;
} IA32_CR0;






typedef union {
  struct {
    UINT32  VME:1;          
    UINT32  PVI:1;          
    UINT32  TSD:1;          
    UINT32  DE:1;           
    UINT32  PSE:1;          
    UINT32  PAE:1;          
    UINT32  MCE:1;          
    UINT32  PGE:1;          
    UINT32  PCE:1;          
                            
    UINT32  OSFXSR:1;       
                            
    UINT32  OSXMMEXCPT:1;   
                            
                            
    UINT32  Reserved_0:2;   
    UINT32  VMXE:1;         
    UINT32  Reserved_1:18;  
  } Bits;
  UINTN     UintN;
} IA32_CR4;




typedef union {
  struct {
    UINT32  LimitLow:16;
    UINT32  BaseLow:16;
    UINT32  BaseMid:8;
    UINT32  Type:4;
    UINT32  S:1;
    UINT32  DPL:2;
    UINT32  P:1;
    UINT32  LimitHigh:4;
    UINT32  AVL:1;
    UINT32  L:1;
    UINT32  DB:1;
    UINT32  G:1;
    UINT32  BaseHigh:8;
  } Bits;
  UINT64  Uint64;
} IA32_SEGMENT_DESCRIPTOR;




#pragma pack (1)
typedef struct {
  UINT16  Limit;
  UINTN   Base;
} IA32_DESCRIPTOR;
#pragma pack ()












typedef union {
  struct {
    UINT32  OffsetLow:16;   
    UINT32  Selector:16;    
    UINT32  Reserved_0:8;   
    UINT32  GateType:8;     
    UINT32  OffsetHigh:16;  
  } Bits;
  UINT64  Uint64;
} IA32_IDT_GATE_DESCRIPTOR;

#line 5043 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"





















#line 5065 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"




typedef struct {
  UINT8  Buffer[512];
} IA32_FX_BUFFER;




typedef struct {
  UINT32                            Reserved1;
  UINT32                            Reserved2;
  UINT32                            Reserved3;
  UINT32                            Reserved4;
  UINT8                             BL;
  UINT8                             BH;
  UINT16                            Reserved5;
  UINT8                             DL;
  UINT8                             DH;
  UINT16                            Reserved6;
  UINT8                             CL;
  UINT8                             CH;
  UINT16                            Reserved7;
  UINT8                             AL;
  UINT8                             AH;
  UINT16                            Reserved8;
} IA32_BYTE_REGS;

typedef struct {
  UINT16                            DI;
  UINT16                            Reserved1;
  UINT16                            SI;
  UINT16                            Reserved2;
  UINT16                            BP;
  UINT16                            Reserved3;
  UINT16                            SP;
  UINT16                            Reserved4;
  UINT16                            BX;
  UINT16                            Reserved5;
  UINT16                            DX;
  UINT16                            Reserved6;
  UINT16                            CX;
  UINT16                            Reserved7;
  UINT16                            AX;
  UINT16                            Reserved8;
} IA32_WORD_REGS;

typedef struct {
  UINT32                            EDI;
  UINT32                            ESI;
  UINT32                            EBP;
  UINT32                            ESP;
  UINT32                            EBX;
  UINT32                            EDX;
  UINT32                            ECX;
  UINT32                            EAX;
  UINT16                            DS;
  UINT16                            ES;
  UINT16                            FS;
  UINT16                            GS;
  IA32_EFLAGS32                     EFLAGS;
  UINT32                            Eip;
  UINT16                            CS;
  UINT16                            SS;
} IA32_DWORD_REGS;

typedef union {
  IA32_DWORD_REGS                   E;
  IA32_WORD_REGS                    X;
  IA32_BYTE_REGS                    H;
} IA32_REGISTER_SET;




typedef struct {
  IA32_REGISTER_SET                 *RealModeState;
  void                              *RealModeBuffer;
  UINT32                            RealModeBufferSize;
  UINT32                            ThunkAttributes;
} THUNK_CONTEXT;






























UINT32
__cdecl
AsmCpuid (
        UINT32                    Index,
       UINT32                    *Eax,  
       UINT32                    *Ebx,  
       UINT32                    *Ecx,  
       UINT32                    *Edx   
  );


































UINT32
__cdecl
AsmCpuidEx (
        UINT32                    Index,
        UINT32                    SubIndex,
       UINT32                    *Eax,  
       UINT32                    *Ebx,  
       UINT32                    *Ecx,  
       UINT32                    *Edx   
  );









void
__cdecl
AsmDisableCache (
  void
  );









void
__cdecl
AsmEnableCache (
  void
  );
















UINT32
__cdecl
AsmReadMsr32 (
        UINT32                    Index
  );



















UINT32
__cdecl
AsmWriteMsr32 (
        UINT32                    Index,
        UINT32                    Value
  );





















UINT32
__cdecl
AsmMsrOr32 (
        UINT32                    Index,
        UINT32                    OrData
  );





















UINT32
__cdecl
AsmMsrAnd32 (
        UINT32                    Index,
        UINT32                    AndData
  );
























UINT32
__cdecl
AsmMsrAndThenOr32 (
        UINT32                    Index,
        UINT32                    AndData,
        UINT32                    OrData
  );
























UINT32
__cdecl
AsmMsrBitFieldRead32 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit
  );



























UINT32
__cdecl
AsmMsrBitFieldWrite32 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT32                    Value
  );





























UINT32
__cdecl
AsmMsrBitFieldOr32 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT32                    OrData
  );





























UINT32
__cdecl
AsmMsrBitFieldAnd32 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT32                    AndData
  );

































UINT32
__cdecl
AsmMsrBitFieldAndThenOr32 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT32                    AndData,
        UINT32                    OrData
  );
















UINT64
__cdecl
AsmReadMsr64 (
        UINT32                    Index
  );



















UINT64
__cdecl
AsmWriteMsr64 (
        UINT32                    Index,
        UINT64                    Value
  );




















UINT64
__cdecl
AsmMsrOr64 (
        UINT32                    Index,
        UINT64                    OrData
  );




















UINT64
__cdecl
AsmMsrAnd64 (
        UINT32                    Index,
        UINT64                    AndData
  );























UINT64
__cdecl
AsmMsrAndThenOr64 (
        UINT32                    Index,
        UINT64                    AndData,
        UINT64                    OrData
  );
























UINT64
__cdecl
AsmMsrBitFieldRead64 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit
  );


























UINT64
__cdecl
AsmMsrBitFieldWrite64 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT64                    Value
  );





























UINT64
__cdecl
AsmMsrBitFieldOr64 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT64                    OrData
  );





























UINT64
__cdecl
AsmMsrBitFieldAnd64 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT64                    AndData
  );
































UINT64
__cdecl
AsmMsrBitFieldAndThenOr64 (
        UINT32                    Index,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINT64                    AndData,
        UINT64                    OrData
  );












UINTN
__cdecl
AsmReadEflags (
  void
  );












UINTN
__cdecl
AsmReadCr0 (
  void
  );












UINTN
__cdecl
AsmReadCr2 (
  void
  );












UINTN
__cdecl
AsmReadCr3 (
  void
  );












UINTN
__cdecl
AsmReadCr4 (
  void
  );













UINTN
__cdecl
AsmWriteCr0 (
  UINTN  Cr0
  );













UINTN
__cdecl
AsmWriteCr2 (
  UINTN  Cr2
  );













UINTN
__cdecl
AsmWriteCr3 (
  UINTN  Cr3
  );













UINTN
__cdecl
AsmWriteCr4 (
  UINTN  Cr4
  );












UINTN
__cdecl
AsmReadDr0 (
  void
  );












UINTN
__cdecl
AsmReadDr1 (
  void
  );












UINTN
__cdecl
AsmReadDr2 (
  void
  );












UINTN
__cdecl
AsmReadDr3 (
  void
  );












UINTN
__cdecl
AsmReadDr4 (
  void
  );












UINTN
__cdecl
AsmReadDr5 (
  void
  );












UINTN
__cdecl
AsmReadDr6 (
  void
  );












UINTN
__cdecl
AsmReadDr7 (
  void
  );













UINTN
__cdecl
AsmWriteDr0 (
  UINTN  Dr0
  );













UINTN
__cdecl
AsmWriteDr1 (
  UINTN  Dr1
  );













UINTN
__cdecl
AsmWriteDr2 (
  UINTN  Dr2
  );













UINTN
__cdecl
AsmWriteDr3 (
  UINTN  Dr3
  );













UINTN
__cdecl
AsmWriteDr4 (
  UINTN  Dr4
  );













UINTN
__cdecl
AsmWriteDr5 (
  UINTN  Dr5
  );













UINTN
__cdecl
AsmWriteDr6 (
  UINTN  Dr6
  );













UINTN
__cdecl
AsmWriteDr7 (
  UINTN  Dr7
  );











UINT16
__cdecl
AsmReadCs (
  void
  );











UINT16
__cdecl
AsmReadDs (
  void
  );











UINT16
__cdecl
AsmReadEs (
  void
  );











UINT16
__cdecl
AsmReadFs (
  void
  );











UINT16
__cdecl
AsmReadGs (
  void
  );











UINT16
__cdecl
AsmReadSs (
  void
  );











UINT16
__cdecl
AsmReadTr (
  void
  );













void
__cdecl
AsmReadGdtr (
       IA32_DESCRIPTOR           *Gdtr
  );













void
__cdecl
AsmWriteGdtr (
        const IA32_DESCRIPTOR     *Gdtr
  );













void
__cdecl
AsmReadIdtr (
       IA32_DESCRIPTOR           *Idtr
  );













void
__cdecl
AsmWriteIdtr (
        const IA32_DESCRIPTOR     *Idtr
  );











UINT16
__cdecl
AsmReadLdtr (
  void
  );











void
__cdecl
AsmWriteLdtr (
        UINT16                    Ldtr
  );















void
__cdecl
AsmFxSave (
       IA32_FX_BUFFER            *Buffer
  );
















void
__cdecl
AsmFxRestore (
        const IA32_FX_BUFFER      *Buffer
  );











UINT64
__cdecl
AsmReadMm0 (
  void
  );











UINT64
__cdecl
AsmReadMm1 (
  void
  );











UINT64
__cdecl
AsmReadMm2 (
  void
  );











UINT64
__cdecl
AsmReadMm3 (
  void
  );











UINT64
__cdecl
AsmReadMm4 (
  void
  );











UINT64
__cdecl
AsmReadMm5 (
  void
  );











UINT64
__cdecl
AsmReadMm6 (
  void
  );











UINT64
__cdecl
AsmReadMm7 (
  void
  );











void
__cdecl
AsmWriteMm0 (
        UINT64                    Value
  );











void
__cdecl
AsmWriteMm1 (
        UINT64                    Value
  );











void
__cdecl
AsmWriteMm2 (
        UINT64                    Value
  );











void
__cdecl
AsmWriteMm3 (
        UINT64                    Value
  );











void
__cdecl
AsmWriteMm4 (
        UINT64                    Value
  );











void
__cdecl
AsmWriteMm5 (
        UINT64                    Value
  );











void
__cdecl
AsmWriteMm6 (
        UINT64                    Value
  );











void
__cdecl
AsmWriteMm7 (
        UINT64                    Value
  );











UINT64
__cdecl
AsmReadTsc (
  void
  );













UINT64
__cdecl
AsmReadPmc (
        UINT32                    Index
  );


















UINTN
__cdecl
AsmMonitor (
        UINTN                     Eax,
        UINTN                     Ecx,
        UINTN                     Edx
  );
















UINTN
__cdecl
AsmMwait (
        UINTN                     Eax,
        UINTN                     Ecx
  );









void
__cdecl
AsmWbinvd (
  void
  );









void
__cdecl
AsmInvd (
  void
  );

















void *
__cdecl
AsmFlushCacheLine (
        void                      *LinearAddress
  );







































void
__cdecl
AsmEnablePaging32 (
        SWITCH_STACK_ENTRY_POINT  EntryPoint,
        void                      *Context1,  
        void                      *Context2,  
        void                      *NewStack
  );




































void
__cdecl
AsmDisablePaging32 (
        SWITCH_STACK_ENTRY_POINT  EntryPoint,
        void                      *Context1,  
        void                      *Context2,  
        void                      *NewStack
  );


































void
__cdecl
AsmEnablePaging64 (
        UINT16                    Cs,
        UINT64                    EntryPoint,
        UINT64                    Context1,  
        UINT64                    Context2,  
        UINT64                    NewStack
  );
































void
__cdecl
AsmDisablePaging64 (
        UINT16                    Cs,
        UINT32                    EntryPoint,
        UINT32                    Context1,  
        UINT32                    Context2,  
        UINT32                    NewStack
  );



























void
__cdecl
AsmGetThunk16Properties (
       UINT32                    *RealModeBufferSize,
       UINT32                    *ExtraStackSize
  );
















void
__cdecl
AsmPrepareThunk16 (
     THUNK_CONTEXT             *ThunkContext
  );























































void
__cdecl
AsmThunk16 (
     THUNK_CONTEXT             *ThunkContext
  );






















void
__cdecl
AsmPrepareAndThunk16 (
     THUNK_CONTEXT             *ThunkContext
  );

#line 7279 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"
#line 7280 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseLib.h"



#line 20 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\BaseLibInternals.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseMemoryLib.h"






































void *
__cdecl
CopyMem (
   void       *DestinationBuffer,
   const void  *SourceBuffer,
   UINTN       Length
  );















void *
__cdecl
SetMem (
   void  *Buffer,
   UINTN  Length,
   UINT8  Value
  );




















void *
__cdecl
SetMem16 (
   void   *Buffer,
   UINTN   Length,
   UINT16  Value
  );




















void *
__cdecl
SetMem32 (
   void   *Buffer,
   UINTN   Length,
   UINT32  Value
  );




















void *
__cdecl
SetMem64 (
   void   *Buffer,
   UINTN   Length,
   UINT64  Value
  );




















void *
__cdecl
SetMemN (
   void  *Buffer,
   UINTN  Length,
   UINTN  Value
  );















void *
__cdecl
ZeroMem (
   void  *Buffer,
   UINTN  Length
  );























INTN
__cdecl
CompareMem (
   const void  *DestinationBuffer,
   const void  *SourceBuffer,
   UINTN       Length
  );




















void *
__cdecl
ScanMem8 (
   const void  *Buffer,
   UINTN       Length,
   UINT8       Value
  );






















void *
__cdecl
ScanMem16 (
   const void  *Buffer,
   UINTN       Length,
   UINT16      Value
  );






















void *
__cdecl
ScanMem32 (
   const void  *Buffer,
   UINTN       Length,
   UINT32      Value
  );






















void *
__cdecl
ScanMem64 (
   const void  *Buffer,
   UINTN       Length,
   UINT64      Value
  );






















void *
__cdecl
ScanMemN (
   const void  *Buffer,
   UINTN       Length,
   UINTN       Value
  );
  















GUID *
__cdecl
CopyGuid (
   GUID       *DestinationGuid,
   const GUID  *SourceGuid
  );

















BOOLEAN
__cdecl
CompareGuid (
   const GUID  *Guid1,
   const GUID  *Guid2
  );























void *
__cdecl
ScanGuid (
   const void  *Buffer,
   UINTN       Length,
   const GUID  *Guid
  );

#line 447 "c:\\1218_alibaba\\MdePkg\\Include\\Library/BaseMemoryLib.h"
#line 21 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\BaseLibInternals.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Library/DebugLib.h"





























































































void
__cdecl
DebugPrint (
    UINTN        ErrorLevel,
    const CHAR8  *Format,
  ...
  );























void
__cdecl
DebugAssert (
   const CHAR8  *FileName,
   UINTN        LineNumber,
   const CHAR8  *Description
  );

















void *
__cdecl
DebugClearMemory (
   void  *Buffer,
   UINTN  Length
  );












BOOLEAN
__cdecl
DebugAssertEnabled (
  void
  );












BOOLEAN
__cdecl
DebugPrintEnabled (
  void
  );












BOOLEAN
__cdecl
DebugCodeEnabled (
  void
  );












BOOLEAN
__cdecl
DebugClearMemoryEnabled (
  void
  );








































  









#line 273 "c:\\1218_alibaba\\MdePkg\\Include\\Library/DebugLib.h"














  







#line 296 "c:\\1218_alibaba\\MdePkg\\Include\\Library/DebugLib.h"














  










#line 322 "c:\\1218_alibaba\\MdePkg\\Include\\Library/DebugLib.h"
























  

















#line 365 "c:\\1218_alibaba\\MdePkg\\Include\\Library/DebugLib.h"




































































































  






#line 473 "c:\\1218_alibaba\\MdePkg\\Include\\Library/DebugLib.h"
    
#line 475 "c:\\1218_alibaba\\MdePkg\\Include\\Library/DebugLib.h"
#line 22 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\BaseLibInternals.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Library/PcdLib.h"



































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































#line 23 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\BaseLibInternals.h"


















UINT64
__cdecl
InternalMathLShiftU64 (
        UINT64                    Operand,
        UINTN                     Count
  );














UINT64
__cdecl
InternalMathRShiftU64 (
        UINT64                    Operand,
        UINTN                     Count
  );














UINT64
__cdecl
InternalMathARShiftU64 (
        UINT64                    Operand,
        UINTN                     Count
  );















UINT64
__cdecl
InternalMathLRotU64 (
        UINT64                    Operand,
        UINTN                     Count
  );















UINT64
__cdecl
InternalMathRRotU64 (
        UINT64                    Operand,
        UINTN                     Count
  );













UINT64
__cdecl
InternalMathSwapBytes64 (
        UINT64                    Operand
  );















UINT64
__cdecl
InternalMathMultU64x32 (
        UINT64                    Multiplicand,
        UINT32                    Multiplier
  );















UINT64
__cdecl
InternalMathMultU64x64 (
        UINT64                    Multiplicand,
        UINT64                    Multiplier
  );















UINT64
__cdecl
InternalMathDivU64x32 (
        UINT64                    Dividend,
        UINT32                    Divisor
  );















UINT32
__cdecl
InternalMathModU64x32 (
        UINT64                    Dividend,
        UINT32                    Divisor
  );


















UINT64
__cdecl
InternalMathDivRemU64x32 (
        UINT64                    Dividend,
        UINT32                    Divisor,
       UINT32                    *Remainder 
  );


















UINT64
__cdecl
InternalMathDivRemU64x64 (
        UINT64                    Dividend,
        UINT64                    Divisor,
       UINT64                    *Remainder 
  );


















INT64
__cdecl
InternalMathDivRemS64x64 (
        INT64                     Dividend,
        INT64                     Divisor,
       INT64                     *Remainder  
  );

























void
__cdecl
InternalSwitchStack (
        SWITCH_STACK_ENTRY_POINT  EntryPoint,
        void                      *Context1,   
        void                      *Context2,   
        void                      *NewStack,
        VA_LIST                   Marker
  );























BOOLEAN
__cdecl
IsNodeInList (
        const LIST_ENTRY      *List,
        const LIST_ENTRY      *Node
  );













UINTN
__cdecl
BitFieldReadUint (
        UINTN                     Operand,
        UINTN                     StartBit,
        UINTN                     EndBit
  );


















UINTN
__cdecl
BitFieldOrUint (
        UINTN                     Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINTN                     OrData
  );


















UINTN
__cdecl
BitFieldAndUint (
        UINTN                     Operand,
        UINTN                     StartBit,
        UINTN                     EndBit,
        UINTN                     AndData
  );













void
__cdecl
InternalAssertJumpBuffer (
        BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer
  );













void
__cdecl
InternalLongJump (
        BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer,
        UINTN                     Value
  );
















void
__cdecl
InternalX86ReadGdtr (
       IA32_DESCRIPTOR           *Gdtr
  );










void
__cdecl
InternalX86WriteGdtr (
        const IA32_DESCRIPTOR     *Gdtr
  );










void
__cdecl
InternalX86ReadIdtr (
       IA32_DESCRIPTOR           *Idtr
  );










void
__cdecl
InternalX86WriteIdtr (
        const IA32_DESCRIPTOR     *Idtr
  );











void
__cdecl
InternalX86FxSave (
       IA32_FX_BUFFER            *Buffer
  );











void
__cdecl
InternalX86FxRestore (
        const IA32_FX_BUFFER      *Buffer
  );


































void
__cdecl
InternalX86EnablePaging32 (
        SWITCH_STACK_ENTRY_POINT  EntryPoint,
        void                      *Context1,  
        void                      *Context2,  
        void                      *NewStack
  );































void
__cdecl
InternalX86DisablePaging32 (
        SWITCH_STACK_ENTRY_POINT  EntryPoint,
        void                      *Context1,  
        void                      *Context2,  
        void                      *NewStack
  );




























void
__cdecl
InternalX86EnablePaging64 (
        UINT16                    Cs,
        UINT64                    EntryPoint,
        UINT64                    Context1,  
        UINT64                    Context2,  
        UINT64                    NewStack
  );



























void
__cdecl
InternalX86DisablePaging64 (
        UINT16                    Cs,
        UINT32                    EntryPoint,
        UINT32                    Context1,  
        UINT32                    Context2,  
        UINT32                    NewStack
  );



























































































































































































































































































































































































































































































































































































































































































































































































































































































































































#line 1654 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\BaseLibInternals.h"

#line 1656 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\BaseLibInternals.h"

#line 3 "c:\\1218_alibaba\\MdePkg\\Library\\BaseLib\\Ia32\\Thunk16.asm"

;------------------------------------------------------------------------------
;
; Copyright (c) 2006 - 2013, Intel Corporation. All rights reserved.<BR>
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
;   Thunk.asm
;
; Abstract:
;
;   Real mode thunk
;
;------------------------------------------------------------------------------

    .686p
    .model  flat,C

EXTERNDEF   C   m16Start:BYTE
EXTERNDEF   C   m16Size:WORD
EXTERNDEF   C   mThunk16Attr:WORD
EXTERNDEF   C   m16Gdt:WORD
EXTERNDEF   C   m16GdtrBase:WORD
EXTERNDEF   C   mTransition:WORD

;
; Here is the layout of the real mode stack. _ToUserCode() is responsible for
; loading all these registers from real mode stack.
;
IA32_REGS   STRUC   4t
_EDI        DD      ?
_ESI        DD      ?
_EBP        DD      ?
_ESP        DD      ?
_EBX        DD      ?
_EDX        DD      ?
_ECX        DD      ?
_EAX        DD      ?
_DS         DW      ?
_ES         DW      ?
_FS         DW      ?
_GS         DW      ?
_EFLAGS     DD      ?
_EIP        DD      ?
_CS         DW      ?
_SS         DW      ?
IA32_REGS   ENDS

    .const

;
; These are global constant to convey information to C code.
;
m16Size         DW      InternalAsmThunk16 - m16Start
mThunk16Attr    DW      _ThunkAttr - m16Start
m16Gdt          DW      _NullSegDesc - m16Start
m16GdtrBase     DW      _16GdtrBase - m16Start
mTransition     DW      _EntryPoint - m16Start

    .code

m16Start    LABEL   BYTE

SavedGdt    LABEL   FWORD
            DW      ?
            DD      ?
;------------------------------------------------------------------------------
; _BackFromUserCode() takes control in real mode after 'retf' has been executed
; by user code. It will be shadowed to somewhere in memory below 1MB.
;------------------------------------------------------------------------------
_BackFromUserCode   PROC
    ;
    ; The order of saved registers on the stack matches the order they appears
    ; in IA32_REGS structure. This facilitates wrapper function to extract them
    ; into that structure.
    ;
    push    ss
    push    cs
    DB      66h
    call    @Base                       ; push eip
@Base:
    pushf                               ; pushfd actually
    cli                                 ; disable interrupts
    push    gs
    push    fs
    push    es
    push    ds
    pushaw                              ; pushad actually
    DB      66h, 0bah                   ; mov edx, imm32
_ThunkAttr  DD      ?
    test    dl, 0x00000002
    jz      @1
    mov     eax, 15cd2401h              ; mov ax, 2401h & int 15h
    cli                                 ; disable interrupts
    jnc     @2
@1:
    test    dl, 0x00000004
    jz      @2
    in      al, 92h
    or      al, 2
    out     92h, al                     ; deactivate A20M#
@2:
    xor     ax, ax                      ; xor eax, eax
    mov     eax, ss                     ; mov ax, ss
    DB      67h
    lea     bp, [esp + sizeof (IA32_REGS)]
    ;
    ; esi's in the following 2 instructions are indeed bp in 16-bit code. Fact
    ; is "esi" in 32-bit addressing mode has the same encoding of "bp" in 16-
    ; bit addressing mode.
    ;
    mov     word ptr (IA32_REGS ptr [esi - sizeof (IA32_REGS)])._ESP, bp
    mov     ebx, (IA32_REGS ptr [esi - sizeof (IA32_REGS)])._EIP
    shl     ax, 4                       ; shl eax, 4
    add     bp, ax                      ; add ebp, eax
    DB      66h, 0b8h                   ; mov eax, imm32
SavedCr4    DD      ?
    mov     cr4, eax
    DB      66h
    lgdt    fword ptr cs:[edi + (SavedGdt - @Base)]
    DB      66h, 0b8h                   ; mov eax, imm32
SavedCr0    DD      ?
    mov     cr0, eax
    DB      0b8h                        ; mov ax, imm16
SavedSs     DW      ?
    mov     ss, eax
    DB      66h, 0bch                   ; mov esp, imm32
SavedEsp    DD      ?
    DB      66h
    retf                                ; return to protected mode
_BackFromUserCode   ENDP

_EntryPoint DD      _ToUserCode - m16Start
            DW      8h
_16Idtr     FWORD   (1 SHL 10) - 1
_16Gdtr     LABEL   FWORD
            DW      GdtEnd - _NullSegDesc - 1
_16GdtrBase DD      _NullSegDesc

;------------------------------------------------------------------------------
; _ToUserCode() takes control in real mode before passing control to user code.
; It will be shadowed to somewhere in memory below 1MB.
;------------------------------------------------------------------------------
_ToUserCode PROC
    mov     edx, ss
    mov     ss, ecx                     ; set new segment selectors
    mov     ds, ecx
    mov     es, ecx
    mov     fs, ecx
    mov     gs, ecx
    mov     cr0, eax                    ; real mode starts at next instruction
                                        ;  which (per SDM) *must* be a far JMP.
    DB      0eah
_RealAddr DW 0,0                       ; filled in by InternalAsmThunk16

    mov     cr4, ebp
    mov     ss, esi                     ; set up 16-bit stack segment
    xchg    sp, bx                      ; set up 16-bit stack pointer

;   mov     bp, [esp + sizeof(IA32_REGS)
    DB      67h
    mov     ebp, [esp + sizeof(IA32_REGS)] ; BackFromUserCode address from stack

;   mov     cs:[bp + (SavedSs - _BackFromUserCode)], dx
    mov     cs:[esi + (SavedSs - _BackFromUserCode)], edx

;   mov     cs:[bp + (SavedEsp - _BackFromUserCode)], ebx
    DB      2eh, 66h, 89h, 9eh
    DW      SavedEsp - _BackFromUserCode

;   lidt    cs:[bp + (_16Idtr - _BackFromUserCode)]
    DB      2eh, 66h, 0fh, 01h, 9eh
    DW      _16Idtr - _BackFromUserCode

    popaw                               ; popad actually
    pop     ds
    pop     es
    pop     fs
    pop     gs
    popf                                ; popfd
    DB      66h                         ; Use 32-bit addressing for "retf" below
    retf                                ; transfer control to user code
_ToUserCode ENDP

_NullSegDesc    DQ      0
_16CsDesc       LABEL   QWORD
                DW      -1
                DW      0
                DB      0
                DB      9bh
                DB      8fh             ; 16-bit segment, 4GB limit
                DB      0
_16DsDesc       LABEL   QWORD
                DW      -1
                DW      0
                DB      0
                DB      93h
                DB      8fh             ; 16-bit segment, 4GB limit
                DB      0
GdtEnd          LABEL   QWORD

;------------------------------------------------------------------------------
; IA32_REGISTER_SET *
; __cdecl
; InternalAsmThunk16 (
;         IA32_REGISTER_SET         *RegisterSet,
;      void                      *Transition
;   );
;------------------------------------------------------------------------------
InternalAsmThunk16  PROC    USES    ebp ebx esi edi ds  es  fs  gs
    mov     esi, [esp + 36]             ; esi <- RegSet, the 1st parameter
    movzx   edx, (IA32_REGS ptr [esi])._SS
    mov     edi, (IA32_REGS ptr [esi])._ESP
    add     edi, - (sizeof (IA32_REGS) + 4) ; reserve stack space
    mov     ebx, edi                    ; ebx <- stack offset
    imul    eax, edx, 16                ; eax <- edx * 16
    push    sizeof (IA32_REGS) / 4
    add     edi, eax                    ; edi <- linear address of 16-bit stack
    pop     ecx
    rep     movsd                       ; copy RegSet
    mov     eax, [esp + 40]             ; eax <- address of transition code
    mov     esi, edx                    ; esi <- 16-bit stack segment
    lea     edx, [eax + (SavedCr0 - m16Start)]
    mov     ecx, eax
    and     ecx, 0fh
    shl     eax, 12
    lea     ecx, [ecx + (_BackFromUserCode - m16Start)]
    mov     ax, cx
    stosd                               ; [edi] <- return address of user code
    add     eax, _RealAddr + 4 - _BackFromUserCode
    mov     dword ptr [edx + (_RealAddr - SavedCr0)], eax
    sgdt    fword ptr [edx + (SavedGdt - SavedCr0)]
    sidt    fword ptr [esp + 36]        ; save IDT stack in argument space
    mov     eax, cr0
    mov     [edx], eax                  ; save CR0 in SavedCr0
    and     eax, 7ffffffeh              ; clear PE, PG bits
    mov     ebp, cr4
    mov     [edx + (SavedCr4 - SavedCr0)], ebp
    and     ebp, NOT 30h                ; clear PAE, PSE bits
    push    10h
    pop     ecx                         ; ecx <- selector for data segments
    lgdt    fword ptr [edx + (_16Gdtr - SavedCr0)]
    pushfd                              ; Save df/if indeed
    call    fword ptr [edx + (_EntryPoint - SavedCr0)]
    popfd
    lidt    fword ptr [esp + 36]        ; restore protected mode IDTR
    lea     eax, [ebp - sizeof (IA32_REGS)] ; eax <- the address of IA32_REGS
    ret
InternalAsmThunk16  ENDP

    END
