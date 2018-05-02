#line 1 "c:\\1218_alibaba\\GrantleySocketPkg\\Library\\ProcessorStartup\\Ia32\\ProcessorStartupUncore.asm"
#line 1 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\Build\\ProcessorStartup\\DEBUG\\AutoGen.h"















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


#line 17 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\Build\\ProcessorStartup\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\PiPei.h"






















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiBaseType.h"



















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Base.h"

































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































#line 21 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiBaseType.h"








typedef GUID                      EFI_GUID;



typedef RETURN_STATUS             EFI_STATUS;



typedef void                      *EFI_HANDLE;



typedef void                      *EFI_EVENT;



typedef UINTN                     EFI_TPL;



typedef UINT64                    EFI_LBA;




typedef UINT64                    EFI_PHYSICAL_ADDRESS;




typedef UINT64                    EFI_VIRTUAL_ADDRESS;












typedef struct {
  UINT16  Year;
  UINT8   Month;
  UINT8   Day;
  UINT8   Hour;
  UINT8   Minute;
  UINT8   Second;
  UINT8   Pad1;
  UINT32  Nanosecond;
  INT16   TimeZone;
  UINT8   Daylight;
  UINT8   Pad2;
} EFI_TIME;





typedef struct {
  UINT8 Addr[4];
} EFI_IPv4_ADDRESS;




typedef struct {
  UINT8 Addr[16];
} EFI_IPv6_ADDRESS;




typedef struct {
  UINT8 Addr[32];
} EFI_MAC_ADDRESS;





typedef union {
  UINT32            Addr[4];
  EFI_IPv4_ADDRESS  v4;
  EFI_IPv6_ADDRESS  v6;
} EFI_IP_ADDRESS;






















































































































































































#line 300 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiBaseType.h"

#line 302 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiBaseType.h"
#line 24 "c:\\1218_alibaba\\MdePkg\\Include\\PiPei.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiPeiCis.h"





















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiMultiPhase.h"

















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Guid/WinCertificate.h"





























typedef struct {
  
  
  
  
  UINT32  dwLength;
  
  
  
  
  UINT16  wRevision;
  
  
  
  
  
  UINT16  wCertificateType;
  
  
  
  
  
  
} WIN_CERTIFICATE;










typedef struct {
  EFI_GUID  HashType;
  UINT8     PublicKey[256];
  UINT8     Signature[256];
} EFI_CERT_BLOCK_RSA_2048_SHA256;





typedef struct {
  
  
  
  
  WIN_CERTIFICATE   Hdr;
  
  
  
  
  EFI_GUID          CertType;
  
  
  
  
  
  
  UINT8            CertData[1];
} WIN_CERTIFICATE_UEFI_GUID;










typedef struct {     
  
  
  
  
  WIN_CERTIFICATE Hdr;
  
  
  
  
  EFI_GUID        HashAlgorithm;
  
  
  
  
  
  
  
  
  
  
} WIN_CERTIFICATE_EFI_PKCS1_15;

extern EFI_GUID gEfiCertTypeRsa2048Sha256Guid;

#line 129 "c:\\1218_alibaba\\MdePkg\\Include\\Guid/WinCertificate.h"
#line 19 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiMultiPhase.h"



typedef enum {
  
  
  
  EfiReservedMemoryType,
  
  
  
  
  EfiLoaderCode,
  
  
  
  
  EfiLoaderData,
  
  
  
  EfiBootServicesCode,
  
  
  
  
  EfiBootServicesData,
  
  
  
  EfiRuntimeServicesCode,
  
  
  
  
  EfiRuntimeServicesData,
  
  
  
  EfiConventionalMemory,
  
  
  
  EfiUnusableMemory,
  
  
  
  EfiACPIReclaimMemory,
  
  
  
  EfiACPIMemoryNVS,
  
  
  
  
  EfiMemoryMappedIO,
  
  
  
  
  EfiMemoryMappedIOPortSpace,
  
  
  
  EfiPalCode,
  EfiMaxMemoryType
} EFI_MEMORY_TYPE;




typedef struct {
  
  
  
  
  
  UINT64  Signature;
  
  
  
  
  
  
  UINT32  Revision;
  
  
  
  UINT32  HeaderSize;
  
  
  
  
  UINT32  CRC32;
  
  
  
  UINT32  Reserved;
} EFI_TABLE_HEADER;



































typedef struct {
  
  
  
  
  
  
  UINT64                      MonotonicCount;
  
  
  
  
  
  
  
  
  WIN_CERTIFICATE_UEFI_GUID   AuthInfo;
} EFI_VARIABLE_AUTHENTICATION;









typedef struct {
  
  
  
  
  EFI_TIME                    TimeStamp;
  
  
  
  WIN_CERTIFICATE_UEFI_GUID   AuthInfo;
 } EFI_VARIABLE_AUTHENTICATION_2;

#line 194 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiMultiPhase.h"
#line 23 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiPeiCis.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"




















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiFirmwareVolume.h"























typedef UINT32  EFI_FV_FILE_ATTRIBUTES;











typedef UINT32  EFI_FVB_ATTRIBUTES_2;






















































typedef struct {
  
  
  
  UINT32 NumBlocks;
  
  
  
  UINT32 Length;
} EFI_FV_BLOCK_MAP_ENTRY;




typedef struct {
  
  
  
  
  UINT8                     ZeroVector[16];
  
  
  
  EFI_GUID                  FileSystemGuid;
  
  
  
  UINT64                    FvLength;
  
  
  
  UINT32                    Signature;
  
  
  
  EFI_FVB_ATTRIBUTES_2      Attributes;
  
  
  
  UINT16                    HeaderLength;
  
  
  
  UINT16                    Checksum;
  
  
  
  
  UINT16                    ExtHeaderOffset;
  
  
  
  UINT8                     Reserved[1];
  
  
  
  
  UINT8                     Revision;
  
  
  
  
  EFI_FV_BLOCK_MAP_ENTRY    BlockMap[1];
} EFI_FIRMWARE_VOLUME_HEADER;











typedef struct {
  
  
  
  EFI_GUID  FvName;
  
  
  
  UINT32    ExtHeaderSize;
} EFI_FIRMWARE_VOLUME_EXT_HEADER;




typedef struct {
  
  
  
  UINT16    ExtEntrySize;
  
  
  
  UINT16    ExtEntryType;
} EFI_FIRMWARE_VOLUME_EXT_ENTRY;





typedef struct {
  
  
  
  EFI_FIRMWARE_VOLUME_EXT_ENTRY Hdr;
  
  
  
  
  UINT32    TypeMask;
  
  
  
  
  
} EFI_FIRMWARE_VOLUME_EXT_ENTRY_OEM_TYPE;







typedef struct {
  
  
  
  EFI_FIRMWARE_VOLUME_EXT_ENTRY     Hdr;
  
  
  
  EFI_GUID                          FormatType;
  
  
  
  
  
} EFI_FIRMWARE_VOLUME_EXT_ENTRY_GUID_TYPE;

#line 235 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiFirmwareVolume.h"
#line 22 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiFirmwareFile.h"





















#pragma pack(1)



typedef union {
  struct {
    
    
    
    
    
    UINT8   Header;
    
    
    
    
    
    
    
    
    
    UINT8   File;
  } Checksum;
  
  
  
  UINT16    Checksum16;
} EFI_FFS_INTEGRITY_CHECK;







typedef UINT8 EFI_FV_FILETYPE;
typedef UINT8 EFI_FFS_FILE_ATTRIBUTES;
typedef UINT8 EFI_FFS_FILE_STATE;
















































typedef struct {
  
  
  
  EFI_GUID                Name;
  
  
  
  EFI_FFS_INTEGRITY_CHECK IntegrityCheck;
  
  
  
  EFI_FV_FILETYPE         Type;
  
  
  
  EFI_FFS_FILE_ATTRIBUTES Attributes;
  
  
  
  UINT8                   Size[3];
  
  
  
  EFI_FFS_FILE_STATE      State;
} EFI_FFS_FILE_HEADER;

typedef struct {
  
  
  
  
  
  EFI_GUID                  Name;
  
  
  
  
  EFI_FFS_INTEGRITY_CHECK   IntegrityCheck;
  
  
  
  
  EFI_FV_FILETYPE           Type;
  
  
  
  
  EFI_FFS_FILE_ATTRIBUTES   Attributes;
  
  
  
  
  
  
  
  
  UINT8                     Size[3];
  
  
  
  
  EFI_FFS_FILE_STATE        State;
  
  
  
  
  
  UINT32                    ExtendedSize;
} EFI_FFS_FILE_HEADER2;










typedef UINT8 EFI_SECTION_TYPE;



































typedef struct {
  
  
  
  
  UINT8             Size[3];
  EFI_SECTION_TYPE  Type;
  
  
  
} EFI_COMMON_SECTION_HEADER;

typedef struct {
  
  
  
  
  UINT8             Size[3];
  
  EFI_SECTION_TYPE  Type;
  
  
  
  
  
  UINT32            ExtendedSize;
} EFI_COMMON_SECTION_HEADER2;





typedef EFI_COMMON_SECTION_HEADER  EFI_COMPATIBILITY16_SECTION;
typedef EFI_COMMON_SECTION_HEADER2 EFI_COMPATIBILITY16_SECTION2;










typedef struct {
  
  
  
  EFI_COMMON_SECTION_HEADER   CommonHeader;
  
  
  
  UINT32                      UncompressedLength;
  
  
  
  UINT8                       CompressionType;
} EFI_COMPRESSION_SECTION;

typedef struct {
  
  
  
  EFI_COMMON_SECTION_HEADER2    CommonHeader;
  
  
  
  UINT32                        UncompressedLength;
  
  
  
  UINT8                         CompressionType;
} EFI_COMPRESSION_SECTION2;










typedef EFI_COMMON_SECTION_HEADER   EFI_DISPOSABLE_SECTION;
typedef EFI_COMMON_SECTION_HEADER2  EFI_DISPOSABLE_SECTION2;




typedef EFI_COMMON_SECTION_HEADER   EFI_DXE_DEPEX_SECTION;
typedef EFI_COMMON_SECTION_HEADER2  EFI_DXE_DEPEX_SECTION2;




typedef EFI_COMMON_SECTION_HEADER   EFI_FIRMWARE_VOLUME_IMAGE_SECTION;
typedef EFI_COMMON_SECTION_HEADER2  EFI_FIRMWARE_VOLUME_IMAGE_SECTION2;




typedef struct {
  
  
  
  EFI_COMMON_SECTION_HEADER   CommonHeader;
  
  
  
  EFI_GUID                    SubTypeGuid;
} EFI_FREEFORM_SUBTYPE_GUID_SECTION;

typedef struct {
  
  
  
  EFI_COMMON_SECTION_HEADER2    CommonHeader;
  
  
  
  EFI_GUID                      SubTypeGuid;
} EFI_FREEFORM_SUBTYPE_GUID_SECTION2;









typedef struct {
  
  
  
  EFI_COMMON_SECTION_HEADER   CommonHeader;
  
  
  
  EFI_GUID                    SectionDefinitionGuid;
  
  
  
  UINT16                      DataOffset;
  
  
  
  UINT16                      Attributes;
} EFI_GUID_DEFINED_SECTION;

typedef struct {
  
  
  
  EFI_COMMON_SECTION_HEADER2    CommonHeader;
  
  
  
  EFI_GUID                      SectionDefinitionGuid;
  
  
  
  UINT16                        DataOffset;
  
  
  
  UINT16                        Attributes;
} EFI_GUID_DEFINED_SECTION2;




typedef EFI_COMMON_SECTION_HEADER   EFI_PE32_SECTION;
typedef EFI_COMMON_SECTION_HEADER2  EFI_PE32_SECTION2;




typedef EFI_COMMON_SECTION_HEADER   EFI_PEI_DEPEX_SECTION;
typedef EFI_COMMON_SECTION_HEADER2  EFI_PEI_DEPEX_SECTION2;










typedef EFI_COMMON_SECTION_HEADER   EFI_PIC_SECTION;
typedef EFI_COMMON_SECTION_HEADER2  EFI_PIC_SECTION2;




typedef EFI_COMMON_SECTION_HEADER   EFI_TE_SECTION;
typedef EFI_COMMON_SECTION_HEADER2  EFI_TE_SECTION2;




typedef EFI_COMMON_SECTION_HEADER   EFI_RAW_SECTION;
typedef EFI_COMMON_SECTION_HEADER2  EFI_RAW_SECTION2;









typedef EFI_COMMON_SECTION_HEADER EFI_SMM_DEPEX_SECTION;
typedef EFI_COMMON_SECTION_HEADER2 EFI_SMM_DEPEX_SECTION2;





typedef struct {
  EFI_COMMON_SECTION_HEADER   CommonHeader;

  
  
  
  CHAR16                      FileNameString[1];
} EFI_USER_INTERFACE_SECTION;

typedef struct {
  EFI_COMMON_SECTION_HEADER2    CommonHeader;
  CHAR16                        FileNameString[1];
} EFI_USER_INTERFACE_SECTION2;





typedef struct {
  EFI_COMMON_SECTION_HEADER   CommonHeader;
  UINT16                      BuildNumber;

  
  
  
  CHAR16                      VersionString[1];
} EFI_VERSION_SECTION;

typedef struct {
  EFI_COMMON_SECTION_HEADER2    CommonHeader;
  
  
  
  
  UINT16                        BuildNumber;
  CHAR16                        VersionString[1];
} EFI_VERSION_SECTION2;










#pragma pack()

#line 494 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiFirmwareFile.h"

#line 23 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiBootMode.h"























typedef UINT32  EFI_BOOT_MODE;

















#line 43 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiBootMode.h"
#line 24 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiHob.h"








































typedef struct {
  
  
  
  UINT16    HobType;
  
  
  
  UINT16    HobLength;
  
  
  
  UINT32    Reserved;
} EFI_HOB_GENERIC_HEADER;











typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER  Header;
  
  
  
  
  
  UINT32                  Version;
  
  
  
  EFI_BOOT_MODE           BootMode;
  
  
  
  
  EFI_PHYSICAL_ADDRESS    EfiMemoryTop;
  
  
  
  EFI_PHYSICAL_ADDRESS    EfiMemoryBottom;
  
  
  
  
  EFI_PHYSICAL_ADDRESS    EfiFreeMemoryTop;
  
  
  
  EFI_PHYSICAL_ADDRESS    EfiFreeMemoryBottom;
  
  
  
  EFI_PHYSICAL_ADDRESS    EfiEndOfHobList;
} EFI_HOB_HANDOFF_INFO_TABLE;






typedef struct {
  
  
  
  
  
  
  
  EFI_GUID              Name;

  
  
  
  
  
  EFI_PHYSICAL_ADDRESS  MemoryBaseAddress;

  
  
  
  UINT64                MemoryLength;

  
  
  
  
  
  EFI_MEMORY_TYPE       MemoryType;

  
  
  
  UINT8                 Reserved[4];
} EFI_HOB_MEMORY_ALLOCATION_HEADER;






typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER            Header;
  
  
  
  
  EFI_HOB_MEMORY_ALLOCATION_HEADER  AllocDescriptor;
  
  
  
  
} EFI_HOB_MEMORY_ALLOCATION;







typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER            Header;
  
  
  
  
  EFI_HOB_MEMORY_ALLOCATION_HEADER  AllocDescriptor;
} EFI_HOB_MEMORY_ALLOCATION_STACK;







typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER            Header;
  
  
  
  
  EFI_HOB_MEMORY_ALLOCATION_HEADER  AllocDescriptor;
} EFI_HOB_MEMORY_ALLOCATION_BSP_STORE;




typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER            Header;
  
  
  
  
  EFI_HOB_MEMORY_ALLOCATION_HEADER  MemoryAllocationHeader;
  
  
  
  
  EFI_GUID                          ModuleName;
  
  
  
  
  EFI_PHYSICAL_ADDRESS              EntryPoint;
} EFI_HOB_MEMORY_ALLOCATION_MODULE;




typedef UINT32 EFI_RESOURCE_TYPE;

















#line 249 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiHob.h"




typedef UINT32 EFI_RESOURCE_ATTRIBUTE_TYPE;






































typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER      Header;
  
  
  
  
  EFI_GUID                    Owner;
  
  
  
  EFI_RESOURCE_TYPE           ResourceType;
  
  
  
  EFI_RESOURCE_ATTRIBUTE_TYPE ResourceAttribute;
  
  
  
  EFI_PHYSICAL_ADDRESS        PhysicalStart;
  
  
  
  UINT64                      ResourceLength;
} EFI_HOB_RESOURCE_DESCRIPTOR;





typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER      Header;
  
  
  
  EFI_GUID                    Name;
  
  
  
} EFI_HOB_GUID_TYPE;




typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER Header;
  
  
  
  EFI_PHYSICAL_ADDRESS   BaseAddress;
  
  
  
  UINT64                 Length;
} EFI_HOB_FIRMWARE_VOLUME;





typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER  Header;
  
  
  
  EFI_PHYSICAL_ADDRESS    BaseAddress;
  
  
  
  UINT64                  Length;
  
  
  
  EFI_GUID                FvName;
  
  
  
  EFI_GUID                FileName;
} EFI_HOB_FIRMWARE_VOLUME2;





typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER  Header;
  
  
  
  UINT8                   SizeOfMemorySpace;
  
  
  
  UINT8                   SizeOfIoSpace;
  
  
  
  UINT8                   Reserved[6];
} EFI_HOB_CPU;





typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER  Header;
} EFI_HOB_MEMORY_POOL;








typedef struct {
  
  
  
  EFI_HOB_GENERIC_HEADER Header;
  
  
  
  
  
  
  EFI_PHYSICAL_ADDRESS   BaseAddress;
  UINT64                 Length;
} EFI_HOB_UEFI_CAPSULE;




typedef union {
  EFI_HOB_GENERIC_HEADER              *Header;
  EFI_HOB_HANDOFF_INFO_TABLE          *HandoffInformationTable;
  EFI_HOB_MEMORY_ALLOCATION           *MemoryAllocation;
  EFI_HOB_MEMORY_ALLOCATION_BSP_STORE *MemoryAllocationBspStore;
  EFI_HOB_MEMORY_ALLOCATION_STACK     *MemoryAllocationStack;
  EFI_HOB_MEMORY_ALLOCATION_MODULE    *MemoryAllocationModule;
  EFI_HOB_RESOURCE_DESCRIPTOR         *ResourceDescriptor;
  EFI_HOB_GUID_TYPE                   *Guid;
  EFI_HOB_FIRMWARE_VOLUME             *FirmwareVolume;
  EFI_HOB_FIRMWARE_VOLUME2            *FirmwareVolume2;
  EFI_HOB_CPU                         *Cpu;
  EFI_HOB_MEMORY_POOL                 *Pool;
  EFI_HOB_UEFI_CAPSULE                *Capsule;
  UINT8                               *Raw;
} EFI_PEI_HOB_POINTERS;


#line 461 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiHob.h"
#line 25 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiDependency.h"














































#line 48 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiDependency.h"
#line 26 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiStatusCode.h"
























#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/DebugSupport.h"























#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\IndustryStandard/PeImage.h"























































typedef struct {
  UINT16  e_magic;    
  UINT16  e_cblp;     
  UINT16  e_cp;       
  UINT16  e_crlc;     
  UINT16  e_cparhdr;  
  UINT16  e_minalloc; 
  UINT16  e_maxalloc; 
  UINT16  e_ss;       
  UINT16  e_sp;       
  UINT16  e_csum;     
  UINT16  e_ip;       
  UINT16  e_cs;       
  UINT16  e_lfarlc;   
  UINT16  e_ovno;     
  UINT16  e_res[4];   
  UINT16  e_oemid;    
  UINT16  e_oeminfo;  
  UINT16  e_res2[10]; 
  UINT32  e_lfanew;   
} EFI_IMAGE_DOS_HEADER;




typedef struct {
  UINT16  Machine;
  UINT16  NumberOfSections;
  UINT32  TimeDateStamp;
  UINT32  PointerToSymbolTable;
  UINT32  NumberOfSymbols;
  UINT16  SizeOfOptionalHeader;
  UINT16  Characteristics;
} EFI_IMAGE_FILE_HEADER;























typedef struct {
  UINT32  VirtualAddress;
  UINT32  Size;
} EFI_IMAGE_DATA_DIRECTORY;

























          



typedef struct {
  
  
  
  UINT16                    Magic;
  UINT8                     MajorLinkerVersion;
  UINT8                     MinorLinkerVersion;
  UINT32                    SizeOfCode;
  UINT32                    SizeOfInitializedData;
  UINT32                    SizeOfUninitializedData;
  UINT32                    AddressOfEntryPoint;
  UINT32                    BaseOfCode;
  UINT32                    BaseOfData;  
  
  
  
  UINT32                    ImageBase;
  UINT32                    SectionAlignment;
  UINT32                    FileAlignment;
  UINT16                    MajorOperatingSystemVersion;
  UINT16                    MinorOperatingSystemVersion;
  UINT16                    MajorImageVersion;
  UINT16                    MinorImageVersion;
  UINT16                    MajorSubsystemVersion;
  UINT16                    MinorSubsystemVersion;
  UINT32                    Win32VersionValue;
  UINT32                    SizeOfImage;
  UINT32                    SizeOfHeaders;
  UINT32                    CheckSum;
  UINT16                    Subsystem;
  UINT16                    DllCharacteristics;
  UINT32                    SizeOfStackReserve;
  UINT32                    SizeOfStackCommit;
  UINT32                    SizeOfHeapReserve;
  UINT32                    SizeOfHeapCommit;
  UINT32                    LoaderFlags;
  UINT32                    NumberOfRvaAndSizes;
  EFI_IMAGE_DATA_DIRECTORY  DataDirectory[16];
} EFI_IMAGE_OPTIONAL_HEADER32;












typedef struct {
  
  
  
  UINT16                    Magic;
  UINT8                     MajorLinkerVersion;
  UINT8                     MinorLinkerVersion;
  UINT32                    SizeOfCode;
  UINT32                    SizeOfInitializedData;
  UINT32                    SizeOfUninitializedData;
  UINT32                    AddressOfEntryPoint;
  UINT32                    BaseOfCode;
  
  
  
  UINT64                    ImageBase;
  UINT32                    SectionAlignment;
  UINT32                    FileAlignment;
  UINT16                    MajorOperatingSystemVersion;
  UINT16                    MinorOperatingSystemVersion;
  UINT16                    MajorImageVersion;
  UINT16                    MinorImageVersion;
  UINT16                    MajorSubsystemVersion;
  UINT16                    MinorSubsystemVersion;
  UINT32                    Win32VersionValue;
  UINT32                    SizeOfImage;
  UINT32                    SizeOfHeaders;
  UINT32                    CheckSum;
  UINT16                    Subsystem;
  UINT16                    DllCharacteristics;
  UINT64                    SizeOfStackReserve;
  UINT64                    SizeOfStackCommit;
  UINT64                    SizeOfHeapReserve;
  UINT64                    SizeOfHeapCommit;
  UINT32                    LoaderFlags;
  UINT32                    NumberOfRvaAndSizes;
  EFI_IMAGE_DATA_DIRECTORY  DataDirectory[16];
} EFI_IMAGE_OPTIONAL_HEADER64;






typedef struct {
  UINT32                      Signature;
  EFI_IMAGE_FILE_HEADER       FileHeader;
  EFI_IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} EFI_IMAGE_NT_HEADERS32;







typedef struct {
  UINT32                      Signature;
  EFI_IMAGE_FILE_HEADER       FileHeader;
  EFI_IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} EFI_IMAGE_NT_HEADERS64;





















typedef struct {
  UINT8 Name[8];
  union {
    UINT32  PhysicalAddress;
    UINT32  VirtualSize;
  } Misc;
  UINT32  VirtualAddress;
  UINT32  SizeOfRawData;
  UINT32  PointerToRawData;
  UINT32  PointerToRelocations;
  UINT32  PointerToLinenumbers;
  UINT16  NumberOfRelocations;
  UINT16  NumberOfLinenumbers;
  UINT32  Characteristics;
} EFI_IMAGE_SECTION_HEADER;





         







                                                   




                                                   







                                              

































































































                                       










typedef struct {
  UINT32  VirtualAddress;
  UINT32  SymbolTableIndex;
  UINT16  Type;
} EFI_IMAGE_RELOCATION;











































typedef struct {
  UINT32  VirtualAddress;
  UINT32  SizeOfBlock;
} EFI_IMAGE_BASE_RELOCATION;
























typedef struct {
  union {
    UINT32  SymbolTableIndex; 
    UINT32  VirtualAddress;   
  } Type;
  UINT16  Linenumber;         
} EFI_IMAGE_LINENUMBER;



















typedef struct {
  UINT8 Name[16];     
  UINT8 Date[12];     
  UINT8 UserID[6];    
  UINT8 GroupID[6];   
  UINT8 Mode[8];      
  UINT8 Size[10];     
  UINT8 EndHeader[2]; 
} EFI_IMAGE_ARCHIVE_MEMBER_HEADER;














typedef struct {
  UINT32  Characteristics;
  UINT32  TimeDateStamp;
  UINT16  MajorVersion;
  UINT16  MinorVersion;
  UINT32  Name;
  UINT32  Base;
  UINT32  NumberOfFunctions;
  UINT32  NumberOfNames;
  UINT32  AddressOfFunctions;
  UINT32  AddressOfNames;
  UINT32  AddressOfNameOrdinals;
} EFI_IMAGE_EXPORT_DIRECTORY;




typedef struct {
  UINT16  Hint;
  UINT8   Name[1];
} EFI_IMAGE_IMPORT_BY_NAME;




typedef struct {
  union {
    UINT32                    Function;
    UINT32                    Ordinal;
    EFI_IMAGE_IMPORT_BY_NAME  *AddressOfData;
  } u1;
} EFI_IMAGE_THUNK_DATA;








typedef struct {
  UINT32                Characteristics;
  UINT32                TimeDateStamp;
  UINT32                ForwarderChain;
  UINT32                Name;
  EFI_IMAGE_THUNK_DATA  *FirstThunk;
} EFI_IMAGE_IMPORT_DESCRIPTOR;





typedef struct {
  UINT32  Characteristics;
  UINT32  TimeDateStamp;
  UINT16  MajorVersion;
  UINT16  MinorVersion;
  UINT32  Type;
  UINT32  SizeOfData;
  UINT32  RVA;           
  UINT32  FileOffset;    
} EFI_IMAGE_DEBUG_DIRECTORY_ENTRY;







typedef struct {
  UINT32  Signature;                        
  UINT32  Unknown;
  UINT32  Unknown2;
  UINT32  Unknown3;
  
  
  
} EFI_IMAGE_DEBUG_CODEVIEW_NB10_ENTRY;





typedef struct {
  UINT32  Signature;                        
  UINT32  Unknown;
  UINT32  Unknown2;
  UINT32  Unknown3;
  UINT32  Unknown4;
  UINT32  Unknown5;
  
  
  
} EFI_IMAGE_DEBUG_CODEVIEW_RSDS_ENTRY;






typedef struct {
  UINT32    Signature;                       
  GUID      MachOUuid;
  
  
  
} EFI_IMAGE_DEBUG_CODEVIEW_MTOC_ENTRY;




typedef struct {
  UINT32  Characteristics;
  UINT32  TimeDateStamp;
  UINT16  MajorVersion;
  UINT16  MinorVersion;
  UINT16  NumberOfNamedEntries;
  UINT16  NumberOfIdEntries;
  
  
  
} EFI_IMAGE_RESOURCE_DIRECTORY;




typedef struct {
  union {
    struct {
      UINT32  NameOffset:31;
      UINT32  NameIsString:1;
    } s;
    UINT32  Id;
  } u1;
  union {
    UINT32  OffsetToData;
    struct {
      UINT32  OffsetToDirectory:31;
      UINT32  DataIsDirectory:1;
    } s;
  } u2;
} EFI_IMAGE_RESOURCE_DIRECTORY_ENTRY;




typedef struct {
  UINT16  Length;
  CHAR16  String[1];
} EFI_IMAGE_RESOURCE_DIRECTORY_STRING;




typedef struct {
  UINT32  OffsetToData;
  UINT32  Size;
  UINT32  CodePage;
  UINT32  Reserved;
} EFI_IMAGE_RESOURCE_DATA_ENTRY;




typedef struct {
  UINT16                    Signature;            
  UINT16                    Machine;              
  UINT8                     NumberOfSections;     
  UINT8                     Subsystem;            
  UINT16                    StrippedSize;         
  UINT32                    AddressOfEntryPoint;  
  UINT32                    BaseOfCode;           
  UINT64                    ImageBase;            
  EFI_IMAGE_DATA_DIRECTORY  DataDirectory[2];     
} EFI_TE_IMAGE_HEADER;














typedef union {
  EFI_IMAGE_NT_HEADERS32   Pe32;
  EFI_IMAGE_NT_HEADERS64   Pe32Plus;
  EFI_TE_IMAGE_HEADER      Te;
} EFI_IMAGE_OPTIONAL_HEADER_UNION;

typedef union {
  EFI_IMAGE_NT_HEADERS32            *Pe32;
  EFI_IMAGE_NT_HEADERS64            *Pe32Plus;
  EFI_TE_IMAGE_HEADER               *Te;
  EFI_IMAGE_OPTIONAL_HEADER_UNION   *Union;
} EFI_IMAGE_OPTIONAL_HEADER_PTR_UNION;

#line 757 "c:\\1218_alibaba\\MdePkg\\Include\\IndustryStandard/PeImage.h"
#line 25 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/DebugSupport.h"

typedef struct _EFI_DEBUG_SUPPORT_PROTOCOL EFI_DEBUG_SUPPORT_PROTOCOL;













typedef INTN  EFI_EXCEPTION_TYPE;


























typedef struct {
  UINT16  Fcw;
  UINT16  Fsw;
  UINT16  Ftw;
  UINT16  Opcode;
  UINT32  Eip;
  UINT16  Cs;
  UINT16  Reserved1;
  UINT32  DataOffset;
  UINT16  Ds;
  UINT8   Reserved2[10];
  UINT8   St0Mm0[10], Reserved3[6];
  UINT8   St1Mm1[10], Reserved4[6];
  UINT8   St2Mm2[10], Reserved5[6];
  UINT8   St3Mm3[10], Reserved6[6];
  UINT8   St4Mm4[10], Reserved7[6];
  UINT8   St5Mm5[10], Reserved8[6];
  UINT8   St6Mm6[10], Reserved9[6];
  UINT8   St7Mm7[10], Reserved10[6];
  UINT8   Xmm0[16];
  UINT8   Xmm1[16];
  UINT8   Xmm2[16];
  UINT8   Xmm3[16];
  UINT8   Xmm4[16];
  UINT8   Xmm5[16];
  UINT8   Xmm6[16];
  UINT8   Xmm7[16];
  UINT8   Reserved11[14 * 16];
} EFI_FX_SAVE_STATE_IA32;




typedef struct {
  UINT32                 ExceptionData;
  EFI_FX_SAVE_STATE_IA32 FxSaveState;
  UINT32                 Dr0;
  UINT32                 Dr1;
  UINT32                 Dr2;
  UINT32                 Dr3;
  UINT32                 Dr6;
  UINT32                 Dr7;
  UINT32                 Cr0;
  UINT32                 Cr1;  
  UINT32                 Cr2;
  UINT32                 Cr3;
  UINT32                 Cr4;
  UINT32                 Eflags;
  UINT32                 Ldtr;
  UINT32                 Tr;
  UINT32                 Gdtr[2];
  UINT32                 Idtr[2];
  UINT32                 Eip;
  UINT32                 Gs;
  UINT32                 Fs;
  UINT32                 Es;
  UINT32                 Ds;
  UINT32                 Cs;
  UINT32                 Ss;
  UINT32                 Edi;
  UINT32                 Esi;
  UINT32                 Ebp;
  UINT32                 Esp;
  UINT32                 Ebx;
  UINT32                 Edx;
  UINT32                 Ecx;
  UINT32                 Eax;
} EFI_SYSTEM_CONTEXT_IA32;


























typedef struct {
  UINT16  Fcw;
  UINT16  Fsw;
  UINT16  Ftw;
  UINT16  Opcode;
  UINT64  Rip;
  UINT64  DataOffset;
  UINT8   Reserved1[8];
  UINT8   St0Mm0[10], Reserved2[6];
  UINT8   St1Mm1[10], Reserved3[6];
  UINT8   St2Mm2[10], Reserved4[6];
  UINT8   St3Mm3[10], Reserved5[6];
  UINT8   St4Mm4[10], Reserved6[6];
  UINT8   St5Mm5[10], Reserved7[6];
  UINT8   St6Mm6[10], Reserved8[6];
  UINT8   St7Mm7[10], Reserved9[6];
  UINT8   Xmm0[16];
  UINT8   Xmm1[16];
  UINT8   Xmm2[16];
  UINT8   Xmm3[16];
  UINT8   Xmm4[16];
  UINT8   Xmm5[16];
  UINT8   Xmm6[16];
  UINT8   Xmm7[16];
  
  
  
  UINT8   Reserved11[14 * 16];
} EFI_FX_SAVE_STATE_X64;




typedef struct {
  UINT64                ExceptionData;
  EFI_FX_SAVE_STATE_X64 FxSaveState;
  UINT64                Dr0;
  UINT64                Dr1;
  UINT64                Dr2;
  UINT64                Dr3;
  UINT64                Dr6;
  UINT64                Dr7;
  UINT64                Cr0;
  UINT64                Cr1;  
  UINT64                Cr2;
  UINT64                Cr3;
  UINT64                Cr4;
  UINT64                Cr8;
  UINT64                Rflags;
  UINT64                Ldtr;
  UINT64                Tr;
  UINT64                Gdtr[2];
  UINT64                Idtr[2];
  UINT64                Rip;
  UINT64                Gs;
  UINT64                Fs;
  UINT64                Es;
  UINT64                Ds;
  UINT64                Cs;
  UINT64                Ss;
  UINT64                Rdi;
  UINT64                Rsi;
  UINT64                Rbp;
  UINT64                Rsp;
  UINT64                Rbx;
  UINT64                Rdx;
  UINT64                Rcx;
  UINT64                Rax;
  UINT64                R8;
  UINT64                R9;
  UINT64                R10;
  UINT64                R11;
  UINT64                R12;
  UINT64                R13;
  UINT64                R14;
  UINT64                R15;
} EFI_SYSTEM_CONTEXT_X64;

















































typedef struct {
  
  
  
  
  UINT64  Reserved;
  UINT64  R1;
  UINT64  R2;
  UINT64  R3;
  UINT64  R4;
  UINT64  R5;
  UINT64  R6;
  UINT64  R7;
  UINT64  R8;
  UINT64  R9;
  UINT64  R10;
  UINT64  R11;
  UINT64  R12;
  UINT64  R13;
  UINT64  R14;
  UINT64  R15;
  UINT64  R16;
  UINT64  R17;
  UINT64  R18;
  UINT64  R19;
  UINT64  R20;
  UINT64  R21;
  UINT64  R22;
  UINT64  R23;
  UINT64  R24;
  UINT64  R25;
  UINT64  R26;
  UINT64  R27;
  UINT64  R28;
  UINT64  R29;
  UINT64  R30;
  UINT64  R31;

  UINT64  F2[2];
  UINT64  F3[2];
  UINT64  F4[2];
  UINT64  F5[2];
  UINT64  F6[2];
  UINT64  F7[2];
  UINT64  F8[2];
  UINT64  F9[2];
  UINT64  F10[2];
  UINT64  F11[2];
  UINT64  F12[2];
  UINT64  F13[2];
  UINT64  F14[2];
  UINT64  F15[2];
  UINT64  F16[2];
  UINT64  F17[2];
  UINT64  F18[2];
  UINT64  F19[2];
  UINT64  F20[2];
  UINT64  F21[2];
  UINT64  F22[2];
  UINT64  F23[2];
  UINT64  F24[2];
  UINT64  F25[2];
  UINT64  F26[2];
  UINT64  F27[2];
  UINT64  F28[2];
  UINT64  F29[2];
  UINT64  F30[2];
  UINT64  F31[2];

  UINT64  Pr;

  UINT64  B0;
  UINT64  B1;
  UINT64  B2;
  UINT64  B3;
  UINT64  B4;
  UINT64  B5;
  UINT64  B6;
  UINT64  B7;

  
  
  
  UINT64  ArRsc;
  UINT64  ArBsp;
  UINT64  ArBspstore;
  UINT64  ArRnat;

  UINT64  ArFcr;

  UINT64  ArEflag;
  UINT64  ArCsd;
  UINT64  ArSsd;
  UINT64  ArCflg;
  UINT64  ArFsr;
  UINT64  ArFir;
  UINT64  ArFdr;

  UINT64  ArCcv;

  UINT64  ArUnat;

  UINT64  ArFpsr;

  UINT64  ArPfs;
  UINT64  ArLc;
  UINT64  ArEc;

  
  
  
  UINT64  CrDcr;
  UINT64  CrItm;
  UINT64  CrIva;
  UINT64  CrPta;
  UINT64  CrIpsr;
  UINT64  CrIsr;
  UINT64  CrIip;
  UINT64  CrIfa;
  UINT64  CrItir;
  UINT64  CrIipa;
  UINT64  CrIfs;
  UINT64  CrIim;
  UINT64  CrIha;

  
  
  
  UINT64  Dbr0;
  UINT64  Dbr1;
  UINT64  Dbr2;
  UINT64  Dbr3;
  UINT64  Dbr4;
  UINT64  Dbr5;
  UINT64  Dbr6;
  UINT64  Dbr7;

  UINT64  Ibr0;
  UINT64  Ibr1;
  UINT64  Ibr2;
  UINT64  Ibr3;
  UINT64  Ibr4;
  UINT64  Ibr5;
  UINT64  Ibr6;
  UINT64  Ibr7;

  
  
  
  UINT64  IntNat;

} EFI_SYSTEM_CONTEXT_IPF;























typedef struct {
  UINT64  R0;
  UINT64  R1;
  UINT64  R2;
  UINT64  R3;
  UINT64  R4;
  UINT64  R5;
  UINT64  R6;
  UINT64  R7;
  UINT64  Flags;
  UINT64  ControlFlags;
  UINT64  Ip;
} EFI_SYSTEM_CONTEXT_EBC;























typedef struct {
  UINT32  R0;
  UINT32  R1;
  UINT32  R2;
  UINT32  R3;
  UINT32  R4;
  UINT32  R5;
  UINT32  R6;
  UINT32  R7;
  UINT32  R8;
  UINT32  R9;
  UINT32  R10;
  UINT32  R11;
  UINT32  R12;
  UINT32  SP;
  UINT32  LR;
  UINT32  PC;
  UINT32  CPSR;
  UINT32  DFSR;
  UINT32  DFAR;
  UINT32  IFSR;
  UINT32  IFAR;
} EFI_SYSTEM_CONTEXT_ARM;















typedef struct {
  
  UINT64  X0;
  UINT64  X1;
  UINT64  X2;
  UINT64  X3;
  UINT64  X4;
  UINT64  X5;
  UINT64  X6;
  UINT64  X7;
  UINT64  X8;
  UINT64  X9;
  UINT64  X10;
  UINT64  X11;
  UINT64  X12;
  UINT64  X13;
  UINT64  X14;
  UINT64  X15;
  UINT64  X16;
  UINT64  X17;
  UINT64  X18;
  UINT64  X19;
  UINT64  X20;
  UINT64  X21;
  UINT64  X22;
  UINT64  X23;
  UINT64  X24;
  UINT64  X25;
  UINT64  X26;
  UINT64  X27;
  UINT64  X28;
  UINT64  FP;   
  UINT64  LR;   
  UINT64  SP;   

  
  UINT64  V0[2];
  UINT64  V1[2];
  UINT64  V2[2];
  UINT64  V3[2];
  UINT64  V4[2];
  UINT64  V5[2];
  UINT64  V6[2];
  UINT64  V7[2];
  UINT64  V8[2];
  UINT64  V9[2];
  UINT64  V10[2];
  UINT64  V11[2];
  UINT64  V12[2];
  UINT64  V13[2];
  UINT64  V14[2];
  UINT64  V15[2];
  UINT64  V16[2];
  UINT64  V17[2];
  UINT64  V18[2];
  UINT64  V19[2];
  UINT64  V20[2];
  UINT64  V21[2];
  UINT64  V22[2];
  UINT64  V23[2];
  UINT64  V24[2];
  UINT64  V25[2];
  UINT64  V26[2];
  UINT64  V27[2];
  UINT64  V28[2];
  UINT64  V29[2];
  UINT64  V30[2];
  UINT64  V31[2];

  UINT64  ELR;  
  UINT64  SPSR; 
  UINT64  FPSR; 
  UINT64  ESR;  
  UINT64  FAR;  
} EFI_SYSTEM_CONTEXT_AARCH64;





typedef union {
  EFI_SYSTEM_CONTEXT_EBC  *SystemContextEbc;
  EFI_SYSTEM_CONTEXT_IA32 *SystemContextIa32;
  EFI_SYSTEM_CONTEXT_X64  *SystemContextX64;
  EFI_SYSTEM_CONTEXT_IPF  *SystemContextIpf;
  EFI_SYSTEM_CONTEXT_ARM  *SystemContextArm;
  EFI_SYSTEM_CONTEXT_AARCH64  *SystemContextAArch64;
} EFI_SYSTEM_CONTEXT;












typedef
void
(__cdecl *EFI_EXCEPTION_CALLBACK)(
       EFI_EXCEPTION_TYPE               ExceptionType,
    EFI_SYSTEM_CONTEXT               SystemContext
  );







typedef
void
(__cdecl *EFI_PERIODIC_CALLBACK)(
    EFI_SYSTEM_CONTEXT               SystemContext
  );




typedef enum {
  IsaIa32 = 0x014c,           
  IsaX64  = 0x8664,            
  IsaIpf  = 0x0200,           
  IsaEbc  = 0x0EBC,            
  IsaArm  = 0x01c2, 
  IsaAArch64  = 0xAA64       
} EFI_INSTRUCTION_SET_ARCHITECTURE;

















typedef
EFI_STATUS
(__cdecl *EFI_GET_MAXIMUM_PROCESSOR_INDEX)(
   EFI_DEBUG_SUPPORT_PROTOCOL          *This,
   UINTN                              *MaxProcessorIndex
  );
















typedef
EFI_STATUS
(__cdecl *EFI_REGISTER_PERIODIC_CALLBACK)(
   EFI_DEBUG_SUPPORT_PROTOCOL          *This,
   UINTN                               ProcessorIndex,
   EFI_PERIODIC_CALLBACK               PeriodicCallback
  );

















typedef
EFI_STATUS
(__cdecl *EFI_REGISTER_EXCEPTION_CALLBACK)(
   EFI_DEBUG_SUPPORT_PROTOCOL          *This,
   UINTN                               ProcessorIndex,
   EFI_EXCEPTION_CALLBACK              ExceptionCallback,
   EFI_EXCEPTION_TYPE                  ExceptionType
  );














typedef
EFI_STATUS
(__cdecl *EFI_INVALIDATE_INSTRUCTION_CACHE)(
   EFI_DEBUG_SUPPORT_PROTOCOL          *This,
   UINTN                               ProcessorIndex,
   void                                *Start,
   UINT64                              Length
  );






struct _EFI_DEBUG_SUPPORT_PROTOCOL {
  
  
  
  EFI_INSTRUCTION_SET_ARCHITECTURE  Isa;
  EFI_GET_MAXIMUM_PROCESSOR_INDEX   GetMaximumProcessorIndex;
  EFI_REGISTER_PERIODIC_CALLBACK    RegisterPeriodicCallback;
  EFI_REGISTER_EXCEPTION_CALLBACK   RegisterExceptionCallback;
  EFI_INVALIDATE_INSTRUCTION_CACHE  InvalidateInstructionCache;
};

extern EFI_GUID gEfiDebugSupportProtocolGuid;

#line 779 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/DebugSupport.h"
#line 26 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiStatusCode.h"




typedef UINT32  EFI_STATUS_CODE_TYPE;










































typedef UINT32 EFI_STATUS_CODE_VALUE;
















typedef struct {
  
  
  
  UINT16    HeaderSize;
  
  
  
  UINT16    Size;
  
  
  
  EFI_GUID  Type;
} EFI_STATUS_CODE_DATA;







































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































#line 1200 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiStatusCode.h"

#line 27 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiS3BootScript.h"










































typedef enum {
  EfiBootScriptWidthUint8,
  EfiBootScriptWidthUint16,
  EfiBootScriptWidthUint32,
  EfiBootScriptWidthUint64,
  EfiBootScriptWidthFifoUint8,
  EfiBootScriptWidthFifoUint16,
  EfiBootScriptWidthFifoUint32,
  EfiBootScriptWidthFifoUint64,
  EfiBootScriptWidthFillUint8,
  EfiBootScriptWidthFillUint16,
  EfiBootScriptWidthFillUint32,
  EfiBootScriptWidthFillUint64,
  EfiBootScriptWidthMaximum
} EFI_BOOT_SCRIPT_WIDTH;

#line 60 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiS3BootScript.h"
#line 28 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"



















































































typedef struct {
  
  
  
  
  
  EFI_PHYSICAL_ADDRESS  PhysicalStart;
  
  
  
  
  EFI_PHYSICAL_ADDRESS  CpuStart;       
  
  
  
  UINT64                PhysicalSize;
  
  
  
  
  
  
  UINT64                RegionState;
} EFI_SMRAM_DESCRIPTOR;

typedef enum {
  EFI_PCD_TYPE_8,
  EFI_PCD_TYPE_16,
  EFI_PCD_TYPE_32,
  EFI_PCD_TYPE_64,
  EFI_PCD_TYPE_BOOL,
  EFI_PCD_TYPE_PTR
} EFI_PCD_TYPE;

typedef struct {
  
  
  
  
  EFI_PCD_TYPE      PcdType;
  
  
  
  
  UINTN             PcdSize;
  
  
  
  
  
  
  CHAR8             *PcdName;
} EFI_PCD_INFO;

#line 166 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiMultiPhase.h"
#line 24 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiPeiCis.h"




typedef void    *EFI_PEI_FV_HANDLE;




typedef void    *EFI_PEI_FILE_HANDLE;




typedef struct _EFI_PEI_SERVICES          EFI_PEI_SERVICES;




typedef struct _EFI_PEI_NOTIFY_DESCRIPTOR EFI_PEI_NOTIFY_DESCRIPTOR;


#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Ppi/CpuIo.h"
























typedef struct _EFI_PEI_CPU_IO_PPI  EFI_PEI_CPU_IO_PPI;




typedef enum {
  EfiPeiCpuIoWidthUint8,
  EfiPeiCpuIoWidthUint16,
  EfiPeiCpuIoWidthUint32,
  EfiPeiCpuIoWidthUint64,
  EfiPeiCpuIoWidthFifoUint8,
  EfiPeiCpuIoWidthFifoUint16,
  EfiPeiCpuIoWidthFifoUint32,
  EfiPeiCpuIoWidthFifoUint64,
  EfiPeiCpuIoWidthFillUint8,
  EfiPeiCpuIoWidthFillUint16,
  EfiPeiCpuIoWidthFillUint32,
  EfiPeiCpuIoWidthFillUint64,
  EfiPeiCpuIoWidthMaximum
} EFI_PEI_CPU_IO_PPI_WIDTH;
















typedef
EFI_STATUS
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_MEM)(
       const EFI_PEI_SERVICES    **PeiServices,
       const EFI_PEI_CPU_IO_PPI  *This,
       EFI_PEI_CPU_IO_PPI_WIDTH  Width,
       UINT64                    Address,
       UINTN                     Count,
    void                      *Buffer
  );




typedef struct {
  
  
  
  EFI_PEI_CPU_IO_PPI_IO_MEM  Read;
  
  
  
  EFI_PEI_CPU_IO_PPI_IO_MEM  Write;
} EFI_PEI_CPU_IO_PPI_ACCESS;












typedef
UINT8
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_READ8)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address
  );












typedef
UINT16
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_READ16)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address
  );












typedef
UINT32
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_READ32)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address
  );












typedef
UINT64
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_READ64)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address
  );











typedef
void
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_WRITE8)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address,
    UINT8                     Data
  );











typedef
void
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_WRITE16)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address,
    UINT16                    Data
  );











typedef
void
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_WRITE32)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address,
    UINT32                    Data
  );











typedef
void
(__cdecl *EFI_PEI_CPU_IO_PPI_IO_WRITE64)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address,
    UINT64                    Data
  );












typedef
UINT8
(__cdecl *EFI_PEI_CPU_IO_PPI_MEM_READ8)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address
  );












typedef
UINT16
(__cdecl *EFI_PEI_CPU_IO_PPI_MEM_READ16)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address
  );












typedef
UINT32
(__cdecl *EFI_PEI_CPU_IO_PPI_MEM_READ32)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address
  );












typedef
UINT64
(__cdecl *EFI_PEI_CPU_IO_PPI_MEM_READ64)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address
  );











typedef
void
(__cdecl *EFI_PEI_CPU_IO_PPI_MEM_WRITE8)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address,
    UINT8                     Data
  );











typedef
void
(__cdecl *EFI_PEI_CPU_IO_PPI_MEM_WRITE16)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address,
    UINT16                    Data
  );











typedef
void
(__cdecl *EFI_PEI_CPU_IO_PPI_MEM_WRITE32)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address,
    UINT32                    Data
  );











typedef
void
(__cdecl *EFI_PEI_CPU_IO_PPI_MEM_WRITE64)(
    const EFI_PEI_SERVICES    **PeiServices,
    const EFI_PEI_CPU_IO_PPI  *This,
    UINT64                    Address,
    UINT64                    Data
  );






struct _EFI_PEI_CPU_IO_PPI {
  
  
  
  EFI_PEI_CPU_IO_PPI_ACCESS       Mem;
  
  
  
  EFI_PEI_CPU_IO_PPI_ACCESS       Io;

  EFI_PEI_CPU_IO_PPI_IO_READ8     IoRead8;
  EFI_PEI_CPU_IO_PPI_IO_READ16    IoRead16;
  EFI_PEI_CPU_IO_PPI_IO_READ32    IoRead32;
  EFI_PEI_CPU_IO_PPI_IO_READ64    IoRead64;

  EFI_PEI_CPU_IO_PPI_IO_WRITE8    IoWrite8;
  EFI_PEI_CPU_IO_PPI_IO_WRITE16   IoWrite16;
  EFI_PEI_CPU_IO_PPI_IO_WRITE32   IoWrite32;
  EFI_PEI_CPU_IO_PPI_IO_WRITE64   IoWrite64;

  EFI_PEI_CPU_IO_PPI_MEM_READ8    MemRead8;
  EFI_PEI_CPU_IO_PPI_MEM_READ16   MemRead16;
  EFI_PEI_CPU_IO_PPI_MEM_READ32   MemRead32;
  EFI_PEI_CPU_IO_PPI_MEM_READ64   MemRead64;

  EFI_PEI_CPU_IO_PPI_MEM_WRITE8   MemWrite8;
  EFI_PEI_CPU_IO_PPI_MEM_WRITE16  MemWrite16;
  EFI_PEI_CPU_IO_PPI_MEM_WRITE32  MemWrite32;
  EFI_PEI_CPU_IO_PPI_MEM_WRITE64  MemWrite64;
};

extern EFI_GUID gEfiPeiCpuIoPpiInstalledGuid;

#line 429 "c:\\1218_alibaba\\MdePkg\\Include\\Ppi/CpuIo.h"
#line 47 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiPeiCis.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Ppi/PciCfg2.h"























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



#line 25 "c:\\1218_alibaba\\MdePkg\\Include\\Ppi/PciCfg2.h"




typedef struct _EFI_PEI_PCI_CFG2_PPI   EFI_PEI_PCI_CFG2_PPI;











typedef enum {
  
  
  
  EfiPeiPciCfgWidthUint8  = 0,
  
  
  
  EfiPeiPciCfgWidthUint16 = 1,
  
  
  
  EfiPeiPciCfgWidthUint32 = 2,
  
  
  
  EfiPeiPciCfgWidthUint64 = 3,
  EfiPeiPciCfgWidthMaximum
} EFI_PEI_PCI_CFG_PPI_WIDTH;




typedef struct {
  
  
  
  
  UINT8   Register;
  
  
  
  
  UINT8   Function;
  
  
  
  UINT8   Device;
  
  
  
  UINT8   Bus;
  
  
  
  
  
  UINT32  ExtendedRegister;
} EFI_PEI_PCI_CFG_PPI_PCI_ADDRESS;

























typedef
EFI_STATUS
(__cdecl *EFI_PEI_PCI_CFG2_PPI_IO)(
   const  EFI_PEI_SERVICES          **PeiServices,
   const  EFI_PEI_PCI_CFG2_PPI      *This,
          EFI_PEI_PCI_CFG_PPI_WIDTH Width,
          UINT64                    Address,
       void                      *Buffer
);
































typedef
EFI_STATUS
(__cdecl *EFI_PEI_PCI_CFG2_PPI_RW)(
   const  EFI_PEI_SERVICES          **PeiServices,
   const  EFI_PEI_PCI_CFG2_PPI      *This,
          EFI_PEI_PCI_CFG_PPI_WIDTH Width,
          UINT64                    Address,
          void                      *SetBits,
          void                      *ClearBits
);





struct _EFI_PEI_PCI_CFG2_PPI {
  EFI_PEI_PCI_CFG2_PPI_IO  Read;
  EFI_PEI_PCI_CFG2_PPI_IO  Write;
  EFI_PEI_PCI_CFG2_PPI_RW  Modify;
  
  
  
  UINT16                  Segment;
};


extern EFI_GUID gEfiPciCfg2PpiGuid;

#line 185 "c:\\1218_alibaba\\MdePkg\\Include\\Ppi/PciCfg2.h"
#line 48 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiPeiCis.h"













typedef
EFI_STATUS
(__cdecl *EFI_PEIM_ENTRY_POINT2)(
   EFI_PEI_FILE_HANDLE             FileHandle,
   const EFI_PEI_SERVICES          **PeiServices
  );










typedef
EFI_STATUS
(__cdecl *EFI_PEIM_NOTIFY_ENTRY_POINT)(
   EFI_PEI_SERVICES           **PeiServices,
   EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
   void                       *Ppi
  );














typedef struct {
  
  
  
  
  UINTN     Flags;
  
  
  
  EFI_GUID  *Guid;
  
  
  
  void      *Ppi;
} EFI_PEI_PPI_DESCRIPTOR;





struct _EFI_PEI_NOTIFY_DESCRIPTOR {
  
  
  
  UINTN                       Flags;
  
  
  
  EFI_GUID                    *Guid;
  
  
  
  EFI_PEIM_NOTIFY_ENTRY_POINT Notify;
};





typedef union {
  
  
  
  EFI_PEI_NOTIFY_DESCRIPTOR   Notify;
  
  
  
  EFI_PEI_PPI_DESCRIPTOR      Ppi;
} EFI_PEI_DESCRIPTOR;


















typedef
EFI_STATUS
(__cdecl *EFI_PEI_INSTALL_PPI)(
   const EFI_PEI_SERVICES            **PeiServices,
   const EFI_PEI_PPI_DESCRIPTOR      *PpiList
  );



















typedef
EFI_STATUS
(__cdecl *EFI_PEI_REINSTALL_PPI)(
   const EFI_PEI_SERVICES                **PeiServices,
   const EFI_PEI_PPI_DESCRIPTOR          *OldPpi,
   const EFI_PEI_PPI_DESCRIPTOR          *NewPpi
  );














typedef
EFI_STATUS
(__cdecl *EFI_PEI_LOCATE_PPI)(
   const EFI_PEI_SERVICES            **PeiServices,
   const EFI_GUID                    *Guid,
   UINTN                             Instance,
      EFI_PEI_PPI_DESCRIPTOR      **PpiDescriptor ,
      void                        **Ppi
  );
















typedef
EFI_STATUS
(__cdecl *EFI_PEI_NOTIFY_PPI)(
   const EFI_PEI_SERVICES                **PeiServices,
   const EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyList
  );










typedef
EFI_STATUS
(__cdecl *EFI_PEI_GET_BOOT_MODE)(
   const EFI_PEI_SERVICES            **PeiServices,
   EFI_BOOT_MODE                    *BootMode
  );










typedef
EFI_STATUS
(__cdecl *EFI_PEI_SET_BOOT_MODE)(
   const EFI_PEI_SERVICES            **PeiServices,
   EFI_BOOT_MODE                     BootMode
  );











typedef
EFI_STATUS
(__cdecl *EFI_PEI_GET_HOB_LIST)(
   const EFI_PEI_SERVICES        **PeiServices,
   void                         **HobList
  );













typedef
EFI_STATUS
(__cdecl *EFI_PEI_CREATE_HOB)(
   const EFI_PEI_SERVICES            **PeiServices,
   UINT16                            Type,
   UINT16                            Length,
    void                          **Hob
  );




















typedef
EFI_STATUS
(__cdecl *EFI_PEI_FFS_FIND_NEXT_VOLUME2)(
   const EFI_PEI_SERVICES                **PeiServices,
   UINTN                                 Instance,
   EFI_PEI_FV_HANDLE                    *VolumeHandle
  );






















typedef
EFI_STATUS
(__cdecl *EFI_PEI_FFS_FIND_NEXT_FILE2)(
   const EFI_PEI_SERVICES                **PeiServices,
   EFI_FV_FILETYPE                       SearchType,
   const EFI_PEI_FV_HANDLE               FvHandle,
    EFI_PEI_FILE_HANDLE               *FileHandle
  );




















typedef
EFI_STATUS
(__cdecl *EFI_PEI_FFS_FIND_SECTION_DATA2)(
   const EFI_PEI_SERVICES            **PeiServices,
   EFI_SECTION_TYPE                  SectionType,
   EFI_PEI_FILE_HANDLE               FileHandle,
   void                             **SectionData
  );






















typedef
EFI_STATUS
(__cdecl *EFI_PEI_FFS_FIND_SECTION_DATA3)(
   const EFI_PEI_SERVICES            **PeiServices,
   EFI_SECTION_TYPE                  SectionType,
   UINTN                             SectionInstance,
   EFI_PEI_FILE_HANDLE               FileHandle,
   void                             **SectionData,
   UINT32                           *AuthenticationStatus
  );













typedef
EFI_STATUS
(__cdecl *EFI_PEI_INSTALL_PEI_MEMORY)(
   const EFI_PEI_SERVICES     **PeiServices,
   EFI_PHYSICAL_ADDRESS       MemoryBegin,
   UINT64                     MemoryLength
  );


















typedef
EFI_STATUS
(__cdecl *EFI_PEI_ALLOCATE_PAGES)(
   const EFI_PEI_SERVICES     **PeiServices,
   EFI_MEMORY_TYPE            MemoryType,
   UINTN                      Pages,
   EFI_PHYSICAL_ADDRESS      *Memory
  );













typedef
EFI_STATUS
(__cdecl *EFI_PEI_ALLOCATE_POOL)(
   const EFI_PEI_SERVICES     **PeiServices,
   UINTN                      Size,
   void                      **Buffer
  );









typedef
void
(__cdecl *EFI_PEI_COPY_MEM)(
   void                       *Destination,
   void                       *Source,
   UINTN                      Length
  );









typedef
void
(__cdecl *EFI_PEI_SET_MEM)(
   void                       *Buffer,
   UINTN                      Size,
   UINT8                      Value
  );






























typedef
EFI_STATUS
(__cdecl *EFI_PEI_REPORT_STATUS_CODE)(
   const EFI_PEI_SERVICES         **PeiServices,
   EFI_STATUS_CODE_TYPE           Type,
   EFI_STATUS_CODE_VALUE          Value,
   UINT32                         Instance,
   const EFI_GUID                 *CallerId ,
   const EFI_STATUS_CODE_DATA     *Data 
  );














typedef
EFI_STATUS
(__cdecl *EFI_PEI_RESET_SYSTEM)(
   const EFI_PEI_SERVICES   **PeiServices
  );





















typedef
EFI_STATUS
(__cdecl *EFI_PEI_FFS_FIND_BY_NAME)(
    const  EFI_GUID            *FileName,
    EFI_PEI_FV_HANDLE          VolumeHandle,
   EFI_PEI_FILE_HANDLE        *FileHandle
  );




typedef struct {
  
  
  
  EFI_GUID                FileName;
  
  
  
  EFI_FV_FILETYPE         FileType;
  
  
  
  EFI_FV_FILE_ATTRIBUTES  FileAttributes;
  
  
  
  
  
  void                    *Buffer;
  
  
  
  UINT32                  BufferSize;
} EFI_FV_FILE_INFO;




typedef struct {
  
  
  
  EFI_GUID                FileName;
  
  
  
  EFI_FV_FILETYPE         FileType;
  
  
  
  EFI_FV_FILE_ATTRIBUTES  FileAttributes;
  
  
  
  
  
  void                    *Buffer;
  
  
  
  UINT32                  BufferSize;
  
  
  
  UINT32                  AuthenticationStatus;
} EFI_FV_FILE_INFO2;



















typedef
EFI_STATUS
(__cdecl *EFI_PEI_FFS_GET_FILE_INFO)(
    EFI_PEI_FILE_HANDLE         FileHandle,
   EFI_FV_FILE_INFO            *FileInfo
  );


















typedef
EFI_STATUS
(__cdecl *EFI_PEI_FFS_GET_FILE_INFO2)(
    EFI_PEI_FILE_HANDLE         FileHandle,
   EFI_FV_FILE_INFO2           *FileInfo
  );




typedef struct {
  
  
  
  EFI_FVB_ATTRIBUTES_2  FvAttributes;
  
  
  
  EFI_GUID              FvFormat;
  
  
  
  EFI_GUID              FvName;
  
  
  
  
  
  void                  *FvStart;
  
  
  
  UINT64                FvSize;
} EFI_FV_INFO;


















typedef
EFI_STATUS
(__cdecl *EFI_PEI_FFS_GET_VOLUME_INFO)(
    EFI_PEI_FV_HANDLE       VolumeHandle,
   EFI_FV_INFO             *VolumeInfo
  );

























typedef
EFI_STATUS
(__cdecl *EFI_PEI_REGISTER_FOR_SHADOW)(
    EFI_PEI_FILE_HANDLE FileHandle
  );

































struct _EFI_PEI_SERVICES {
  
  
  
  EFI_TABLE_HEADER                Hdr;

  
  
  
  EFI_PEI_INSTALL_PPI             InstallPpi;
  EFI_PEI_REINSTALL_PPI           ReInstallPpi;
  EFI_PEI_LOCATE_PPI              LocatePpi;
  EFI_PEI_NOTIFY_PPI              NotifyPpi;

  
  
  
  EFI_PEI_GET_BOOT_MODE           GetBootMode;
  EFI_PEI_SET_BOOT_MODE           SetBootMode;

  
  
  
  EFI_PEI_GET_HOB_LIST            GetHobList;
  EFI_PEI_CREATE_HOB              CreateHob;

  
  
  
  EFI_PEI_FFS_FIND_NEXT_VOLUME2   FfsFindNextVolume;
  EFI_PEI_FFS_FIND_NEXT_FILE2     FfsFindNextFile;
  EFI_PEI_FFS_FIND_SECTION_DATA2  FfsFindSectionData;

  
  
  
  EFI_PEI_INSTALL_PEI_MEMORY      InstallPeiMemory;
  EFI_PEI_ALLOCATE_PAGES          AllocatePages;
  EFI_PEI_ALLOCATE_POOL           AllocatePool;
  EFI_PEI_COPY_MEM                CopyMem;
  EFI_PEI_SET_MEM                 SetMem;

  
  
  
  EFI_PEI_REPORT_STATUS_CODE      ReportStatusCode;

  
  
  
  EFI_PEI_RESET_SYSTEM            ResetSystem;

  
  
  
  
  EFI_PEI_CPU_IO_PPI              *CpuIo;
  EFI_PEI_PCI_CFG2_PPI            *PciCfg;

  
  
  
  EFI_PEI_FFS_FIND_BY_NAME        FfsFindFileByName;
  EFI_PEI_FFS_GET_FILE_INFO       FfsGetFileInfo;
  EFI_PEI_FFS_GET_VOLUME_INFO     FfsGetVolumeInfo;
  EFI_PEI_REGISTER_FOR_SHADOW     RegisterForShadow;
  EFI_PEI_FFS_FIND_SECTION_DATA3  FindSectionData3;
  EFI_PEI_FFS_GET_FILE_INFO2      FfsGetFileInfo2;
};







typedef struct _EFI_SEC_PEI_HAND_OFF {
  
  
  
  UINT16  DataSize;

  
  
  
  
  
  void    *BootFirmwareVolumeBase;

  
  
  
  UINTN   BootFirmwareVolumeSize;

  
  
  
  void    *TemporaryRamBase;

  
  
  
  UINTN   TemporaryRamSize;

  
  
  
  
  
  
  
  
  
  void    *PeiTemporaryRamBase;

  
  
  
  
  UINTN   PeiTemporaryRamSize;

  
  
  
  
  
  
  void    *StackBase;

  
  
  
  UINTN   StackSize;
} EFI_SEC_PEI_HAND_OFF;





































typedef
void
(__cdecl *EFI_PEI_CORE_ENTRY_POINT)(
   const  EFI_SEC_PEI_HAND_OFF    *SecCoreData,
   const  EFI_PEI_PPI_DESCRIPTOR  *PpiList
);

#line 1017 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiPeiCis.h"

#line 25 "c:\\1218_alibaba\\MdePkg\\Include\\PiPei.h"

#line 27 "c:\\1218_alibaba\\MdePkg\\Include\\PiPei.h"

#line 18 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\Build\\ProcessorStartup\\DEBUG\\AutoGen.h"
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

#line 19 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\Build\\ProcessorStartup\\DEBUG\\AutoGen.h"

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;



extern EFI_GUID gCpuUncoreTokenSpaceGuid;



extern const UINT32 _gPcd_FixedAtBuild_PcdFlashSecCacheRegionBase;





extern const UINT32 _gPcd_FixedAtBuild_PcdFlashSecCacheRegionSize;










#line 47 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\IA32\\Build\\ProcessorStartup\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\GrantleySocketPkg\\Library\\ProcessorStartup\\Ia32\\ProcessorStartupUncore.asm"
;
; This file contains an 'Intel Pre-EFI Module' and is licensed
; for Intel CPUs and Chipsets under the terms of your license 
; agreement with Intel or your vendor.  This file may be      
; modified by the user, subject to additional terms of the    
; license agreement                                           
;
;------------------------------------------------------------------------------
;
; Copyright (c) 1999 - 2015, Intel Corporation. All rights reserved.<BR>
; This software and associated documentation (if any) is furnished
; under a license and may only be used or copied in accordance
; with the terms of the license. Except as permitted by such
; license, no part of this software or documentation may be
; reproduced, stored in a retrieval system, or transmitted in any
; form or by any means without the express written consent of
; Intel Corporation.
;
; Module Name:
;
;  ProcessorStartupUncore.asm
;
; Abstract:
;
;
;------------------------------------------------------------------------------        
        .586P
        .XMM
        .MODEL  SMALL, c


        
        include ProcessorStartupPlatform.inc
        include ProcessorStartupChipset.inc
        include ProcessorStartupUncore.inc
        include ProcessorStartup.inc

        EXTERN  ReadPciLegacy:NEAR32
        EXTERN  WritePciLegacy:NEAR32
        EXTERN  _OEMCpuSecInit:NEAR32
        EXTERN  TearDownNEMandHalt:NEAR32

;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG SEGMENT PARA PUBLIC 'CODE' USE32

;----------------------------------------------------------------------------
; SetTargetList executes by all PBSPs. The purpose is to make sure that 
; default IO target will be match as legacy socket ID as at default before
; issue any IO transactions such as port 80. MMIO target also setup here 
;
;  Input:  All general puropse registers undefined
;          Stack may not be available
;          MMX3 = routine return address
;  Output: 
;          All general puropse registers undefined. MMCFG and CPUBUSNO related CSRs are initialized.
;          xmm1  [7:0]= legact socket id,  [27:8]= CPU Family/stepping info from cpuid instruction
;----------------------------------------------------------------------------
SetTargetList    PROC    NEAR    PUBLIC

      ;
      ; In CR4, set OSFXSR bit 9 and OSXMMEXCPT bit 10 to enable access to XMM registers used by this routine
      ;
      mov   eax, cr4
      or    eax, 1 SHL 9 + 1 SHL 10
      mov   cr4, eax

; BIOS HSD 3875167
; Disable LOCK lockcontrol.lockdisable (bus 1, device 0xb, function 0, offset 0x50, bit 0)
      mov   eax, CSR_LEGACY_LOCKCONTROL
      READ_PCI_DWORD_LEGACY               ; ebx = reg dword data
      or    ebx, 0x00000001                     ; set bit0
      WRITE_PCI_DWORD_LEGACY 

      ; make sure we program IOPORT_TARGET_LIST before can can do any io transaction
      ; 
      ; 1st get legacy socket ID and store in xmm1[7:0]
      mov   eax, CSR_LEGACY_SAD_TARGET_CBO    ; get legacy socket ID
      READ_PCI_DWORD_LEGACY
      and   ebx, 038h                         ; keep bit5:3
      shr   ebx, 3
      movd  xmm1, ebx                         ; save legacy node id in xmm1[7:0]
      ; 2nd program legacy socket ID to IOPORT_TARGET_LIST
; Program the IO Target List; Legacy IIO is the target
      mov   eax, ebx                          
      mov   cl, 3                             ; number of node id bits
      mov   ch, 7     
set_io_target_legacy:
      shl   eax, cl
      or    ebx, eax
      dec   ch
      jnz   set_io_target_legacy
                               
      mov   eax, CSR_LEGACY_IO_TARGET_LIST_CBO
      WRITE_PCI_DWORD_LEGACY 

      mov   eax, CSR_LEGACY_MMIO_TARGET_LIST_CBO
      WRITE_PCI_DWORD_LEGACY 

;  Read CPU Family/stepping info and store in xmm1[27:8]
      mov  eax, 1
      cpuid
      and  eax, 0fffffh
      shl  eax, 8          ; shift to bit[27:8]
      movd ebx, xmm1
      or   ebx, eax
      movd xmm1, ebx

      RET_ESI_MMX3

SetTargetList    ENDP


EarlyUncoreInit  PROC    NEAR    PUBLIC

        ;
        ; In CR4, set OSFXSR bit 9 and OSXMMEXCPT bit 10
        ;
        mov   eax, cr4
        or    eax, 1 SHL 9 + 1 SHL 10
        mov   cr4, eax

        ;
        ; Enable the MMIO Rule3 to cover the 0xFC000000 to 0xFFFFFFFF so that the NEM DATA region can be mapped to it.
        ; The target is set to local IIO.
        ;

        ; Program the MMIO Rule3 Base/Limit
              mov   eax, (CSR_LEGACY_MMIO_RULE3_CBO + 4)
              mov   ebx, 0h                                                       ; Higher bits of the rule are all 0
              WRITE_PCI_DWORD_LEGACY 
              mov   eax, CSR_LEGACY_MMIO_RULE3_CBO
              mov   ebx, 0FF00007Fh                             ; Base = 0xFC000000; Limit = 0xFFFFFFFF; Set the enable bit                     ; Higer bits of the tule are all 0
              WRITE_PCI_DWORD_LEGACY 

        CALL_MMX4   EnableAccessCSR                      ; init MMCFG/CPUBUSNO cnofig scheme

        RET_ESI_MMX3
EarlyUncoreInit  ENDP


MidUncoreInit    PROC    NEAR    PUBLIC

        ;---If Limit CPU ID enabled because of soft reset, disable.
        mov     ecx, 01a0h
        rdmsr
        btr     eax, 22                                 ; Reset bit
        jnc     @f                                      ; If already reset, don't write to 1a0.

        wrmsr
@@:
        ;---Change APIC Address---
        mov   ecx, MSR_XAPIC_BASE                       ; Enable local APIC
        rdmsr
        and   edx, NOT 0fh                              ; Mask local APIC address
        and   eax, NOT 0fffff000h                       ; Mask local APIC address
        or    eax, LOCAL_APIC_BASE
        wrmsr

        RET_ESI_MMX3

MidUncoreInit    ENDP

PreNemUncoreInit    PROC    NEAR    PUBLIC

        ;
        ; Prior to NEM init, use VCU API to notify VCU of "BIOS is about to enable cache"
        ;
        mov  eax, 1
        cpuid
        and eax, 0fffffh
        shr eax, 4
        cmp eax, CPU_FAMILY_HSX                       ; HSX CPU?
        je  hsx_or_bdx_cpu                              ; Jump to hsx_or_bdx_cpu for HSX or BDX
        cmp eax, CPU_FAMILY_BDX_DE                       ; BDX CPU ?
        je  hsx_or_bdx_cpu
        cmp eax, CPU_FAMILY_BDX
        jne pnui_exit                                   ; No, skip   
       
hsx_or_bdx_cpu:
      ; A this point, EnableAccessCsr() has been executed and CPUBUSNO/MMCFG  have been set up already
      ; Information in the xmm registers can be reused here
      ;
      ; check if running on real hardware or simulation tool
      ;
      movd  ecx, xmm2                                ; xmm2[31:24] stores the socketID
      shr   ecx, 24t                                 ; CL = local socket ID
      mov   eax, CSR_EMULATION_FLAG_UBOX
      CALL_MMX6  GetCpuCsrAddrNoStack                 ;[edi] = MMCFG config address of the CSR
      mov   eax, dword ptr ds:[edi]                   ; read CSR
      or    al, al                                    ; read hardware?
      jnz   pnui_exit                                 ; no, skip
      and   edi, 0fff00000h                               ; edi = MMCFG_Base + uncore bus#
      mov   ecx, VCODE_API_DELAY_COUNT                    ; software timeout loop-count
      mov   ebx, CSR_VCU_MAILBOX_INTERFACE AND 000fffffh  ; ebx = Dev:Func:Offset of VCU_MAILBOX_INTERFACE CSR
      mov   edx, CSR_VCU_MAILBOX_DATA AND 000fffffh       ; edx = Dev:Func:Offset of VCU_MAILBOX_DATA CSR
poll_vcu_busy1:
        mov   eax, dword ptr ds:[edi][ebx]              ; read CSR VCU_MAILBOX_INTERFACE
        cmp   eax, 0ffffffffh                 
        je    pnui_vcu_failure                          ; debug: - skip if the CSR is not implemented 
        test  eax, 0x80000000
        loopnz poll_vcu_busy1
        or    ecx, ecx
        jz    pnui_vcu_failure
       
        ; 
        ;  Call VCU API Open Sequnece (IOT_LLC_SETUP)
        ;
        mov   eax, VCODE_API_SEQ_ID_IOT_LLC_SETUP
        mov   dword ptr ds:[edi][edx], eax              ; write CSR VCU_MAILBOX_DATA

        mov   eax, (0x80000000 OR VCODE_API_OPCODE_OPEN_SEQUENCE)
        mov   dword ptr ds:[edi][ebx], eax              ; write CSR VCU_MAILBOX_INTERFACE

        mov   ecx, VCODE_API_DELAY_COUNT                ; software timeout loop-count
poll_vcu_busy2:
        mov   eax, dword ptr ds:[edi][ebx]              ; read CSR VCU_MAILBOX_INTERFACE
        test  eax, 0x80000000
        loopnz poll_vcu_busy2
        or    ecx, ecx
        jz    pnui_vcu_failure

        ; 
        ;  Call VCU API SET_PARAMETER with Index = 0
        ;  This step is required although the parameters  is don't care 
        ;

        mov   eax, 0                                    ; set data = 0
        mov   dword ptr ds:[edi][edx], eax              ; write CSR VCU_MAILBOX_DATA
        mov   eax, (0x80000000 OR VCODE_API_OPCODE_SET_PARAMETER)
        mov   dword ptr ds:[edi][ebx], eax              ; write CSR VCU_MAILBOX_INTERFACE

        mov   ecx, VCODE_API_DELAY_COUNT                ; software timeout loop-count
poll_vcu_busy3:
        mov   eax, dword ptr ds:[edi][ebx]              ; read CSR VCU_MAILBOX_INTERFACE
        test  eax, 0x80000000
        loopnz poll_vcu_busy3
        or    ecx, ecx
        jz    pnui_vcu_failure

        ;
        ;  Call VCU API  IOT_LLC_SETUP with Index=1
        ;
        mov   eax, (0x80000000 OR VCODE_API_OPCODE_IOT_LLC_SETUP)
        or    eax, (1 SHL 16)                               ; bit[23:16] = Index = 1
        mov   dword ptr ds:[edi][ebx], eax                  ; write CSR VCU_MAILBOX_INTERFACE

        mov   ecx, VCODE_API_DELAY_COUNT                    ; software timeout loop-count
poll_vcu_busy4:
        mov   eax, dword ptr ds:[edi][ebx]                  ; read CSR VCU_MAILBOX_INTERFACE
        test  eax, 0x80000000
        loopnz poll_vcu_busy4
        or    ecx, ecx
        jz    pnui_vcu_failure

        ; 
        ; Call VCU API Close Sequnece (IOT_LLC_SETUP)
        ;
        mov   eax, VCODE_API_SEQ_ID_IOT_LLC_SETUP
        mov   dword ptr ds:[edi][edx], eax                  ; write CSR VCU_MAILBOX_DATA

        mov   eax, (0x80000000 OR VCODE_API_OPCODE_CLOSE_SEQUENCE)
        mov   dword ptr ds:[edi][ebx], eax                  ; write CSR VCU_MAILBOX_INTERFACE
        
        mov   ecx, VCODE_API_DELAY_COUNT                    ; software timeout loop-count
poll_vcu_busy5:
        mov   eax, dword ptr ds:[edi][ebx]                  ; read CSR VCU_MAILBOX_INTERFACE
        test  eax, 0x80000000
        loopnz poll_vcu_busy5
        or    ecx, ecx
        jz    pnui_vcu_failure

pnui_exit:
        RET_ESI_MMX3
        

pnui_vcu_failure:
        PORT80(0CBh)                                    ; error code to port 80h
        jmp  pnui_exit

PreNemUncoreInit    ENDP



PostNemUncoreInit    PROC    NEAR    PUBLIC

        call ProcessorWorkaround                ; Early CPU WAs
        call QpiProgramMsrForWorkaound          ; Early QPI WAs
        call QpiPassInPllRatio                  ; Pass in Over-Clocking PLL Ratio for QPIRC

        call SetupProcessorCheckinData
    
        ;
        ; Early SBSP Selection
        ;                           
        call GetLocalSktId                      ; CL = Current socketId
        call GetSbspSktId                       ; AL = SBSP socketId
        cmp  cl, al
        jz   ImSbsp

        call ParkNbsp                           ; PBSPs will nott return 

ImSbsp:        
       ;
       ; Only SBSP comes here to continue posting. Other PBSPs are held in a loop.
       ; 
       ret
PostNemUncoreInit    ENDP



;----------------------------------------------------------------------------
;  Initialize PROC MMCFG and CPUBUSNO related registers 
;  Executed by all BSPs present in the system early after reset
;  
;  Input:  All general puropse registers undefined
;          Stack may not be available
;          MMX4 = routine return address
;          xmm1  [7:0]= legact socket id,  [27:8]= CPU Family/stepping info from cpuid instruction
;  Output: All general puropse registers undefined. MMCFG and CPUBUSNO related CSRs are initialized.
;          Following xmm registers hold MMCFG and bus number config scheme info (later used by otehr routines in this file)
;          xmm1  [7:0]= legact socket id,  [27:8]= CPU Family/stepping info from cpuid instruction
;          xmm2 = [31:24] SocketID, [23:0] MMCFG_TARGET_LIST 
;          xmm3 = MMCFG_RULE
;          xmm4/5 = IIO/Uncore Bus # array for socket0:3 Id (a.k.a node ID). 
;              bit  [7:0] Bus# for nodeId 0
;              bit [15:8] Bus# for nodeId 1
;              bit[23:16] Bus# for nodeId 2
;              bit[31:24] Bus# for nodeId 3
;          xmm6/7 = IIO/Uncore Bus # array for socket4:7 Id (a.k.a node ID).
;              bit  [7:0] Bus# for nodeId 4
;              bit [15:8] Bus# for nodeId 5
;              bit[23:16] Bus# for nodeId 6
;              bit[31:24] Bus# for nodeId 7

;----------------------------------------------------------------------------

EnableAccessCSR    PROC    NEAR  PUBLIC

      ; Initialize MMCFG_Target_List and CPUBUSNO to be used for this boot:
      ;   Cold-boot: Use a pre-defined MMCFG_Target_rule and bus # assighment scheme:
      ;     for 4S:  MMCFG_Target_List = [3,3,2,2,1,1,0,0], bus#s of 00, 0x40, 0x80, 0xC0
      ;     for 8S:  MMCFG_Target_List = [7,6,5,4,3,2,1,0], bus#s of 00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0
      ;   Warm boot: Calculate mmcfg/busnumber info using data in the sticky scratch pad reg saved from last boot.

         comment ^ 
         Scratch Pad Register 2 Format
         [7:0]   - CPU present bitmap (QPIRC updates, in all sockets); this list reflects the CPUs after the topology is degraded, if needed
         [31:8]  - used by QPIRC
         Scratch Pad Register 3 Format
         [2:0]   - Total number of buses  assigned to CPU0 in 32 Bus granularity; 00 - 32 buses, 1 - 64 buses ... 7 - 256 buses
         [5:3]   - CPU1 bus range
         [8:6]   - CPU2 bus range
         [11:9]  - CPU3 bus range
         [14:12] - CPU4 bus range
         [17:15] - CPU5 bus range
         [20:18] - CPU6 bus range
         [23:21] - CPU7 bus range
         [29:24] - MMCFG Base, to store Address [31:26] of MMCFG BASE
         [31:30] - Reserved

         Scratch Pad Register 7 Format
         [0]     - ExtRTID Mode enabled or not 
         [4]     - Entered Cold Reset Flow (CPURC Updates as soon as possible, on all sockets)
         [5]     - Comlepted Cold Reset Flow (The code that issues warn reset requested by RC updates this, on all sockets)
         [10:8]  - Local socket id
         [19:16] - SBSP socket id
         [24]    - DCU_MODE select 0/1: 32KB 8-way no-ECC (hardware default) / 16KB 4-way with ECC  (CPU RC updates, in all sockets)
         [other bits] - Reserved

           CPU MMCFG_TARGET_LIST Register Format
               23:21                 11:9     8:6      5:3      2:0      bit
         --------------------------------------------------------------
             | NodeID |    ...    | NodeID | NodeID | NodeID | NodeID |
         --------------------------------------------------------------
               FF-E0                 7F-60   5F-40    3F-20     1F-00    bus-range
               note: legacy socket will always have lowest bus range start from bus0
         end comment ^
      
        ;
        ; In CR4, set OSFXSR bit 9 and OSXMMEXCPT bit 10 to enable access to XMM registers used by this routine
        ;
        mov   eax, cr4
        or    eax, 1 SHL 9 + 1 SHL 10
        mov   cr4, eax

      ; Read sticky scratch pad register for mmcfg/bus number config info 
      mov   eax, SSR_LEGACY_BOOT_CONFIG_INFO_CSR   
      READ_PCI_DWORD_LEGACY                    ; ebx = scratch pad reg dword data
      test  ebx, 0x00000020                          ; Cold Reset Flow Completed = 1?
      jz    short @f                           ; no
      
      test  ebx, 0x00000040                          ; hotplug Reset Flow Entered flag = 1?     
      jnz   use_default_cfg_scheme             ; Yes (use default cfg scheme) 
      
      and   bl, NOT (0x00000010)                     ; clear bit4 of scratch pad register
      WRITE_PCI_DWORD_LEGACY 
      jmp   calculate_cfg_scheme               ; take the warm boot path

@@:
      test  ebx, 0x00000010                          ; Cold Reset Flow Entered flag = 1?
      jz    use_default_cfg_scheme             ; No (normal cold boot path) 

      ; Warm reset occured before completion of MRC on the cold boot path.
      ; In this case SBSP triggers a power-good reset while other socket BSPs waits
      ; Note: legacy socket will always SBSP at SEC phase

      ; Read own socketId from CSR
      mov   eax, CSR_LEGACY_SAD_CONTROL_CBO
      READ_PCI_DWORD_LEGACY                    ; ebx = reg dword data
      mov   bh, bl                             ; nodeId 
      and   bl, 00011b
      and   bh, 01000b
      shr   bh, 1
      or    bl, bh                             ; bl = local socketId
      movd  eax,  xmm1                         ; al = legacy socket ID
      cmp   bl, al
      jne   short @f                           ; br if non-legacy socket

      ; Legacy BSP comes here - Triggers a power-good reset.
      mov   al, 0eh
      mov   dx, 0cf9h
      out   dx, al
@@:
      jmp   $                                  ; wait for reset to occur


use_default_cfg_scheme:

      ; set Cold Reset Flow Entered flag = 1 in scratch pad register
      or   ebx, 0x00000010
      WRITE_PCI_DWORD_LEGACY 

      ; Use pre-defined config scheme for cold boot path
      mov   eax, DEFAULT_COLDBOOT_MMCFG_TARGET_LIST
      movd  xmm2, eax
      mov   eax, DEFAULT_COLDBOOT_MMCFG_RULE
      movd  xmm3, eax
      mov   eax, DEFAULT_COLDBOOT_IIO_BUS_NUMS
      movd  xmm4, eax
      mov   eax, DEFAULT_COLDBOOT_UNCORE_BUS_NUMS
      movd  xmm5, eax

IF MAX_CPU_SOCKETS GT 4
      mov   eax, DEFAULT_COLDBOOT_IIO_BUS_NUMS_4_7_S
      movd  xmm6, eax
      mov   eax, DEFAULT_COLDBOOT_UNCORE_BUS_NUMS_4_7_S
      movd  xmm7, eax
ENDIF
     
      ; check to see if legacy socket id is 0 or not
      ; if not, we need to adjust target list and bus range for iio and uncore
      ; 1st adjust target list, 2nd iio bus and 3rd uncore bus
      ; the algorithm is swap nodeid, iio bus, uncore bus with node io 0
      ; note: default node id 0 always is 0
      movd  eax, xmm1         ; get legacy socekt id
      mov   cl, al            
      mov   ch, cl            ; save legacy socket id in ch
      cmp   cl, 0             ; legacy socket id 0?
      je    Write_cfg_scheme_to_CSRs    ; yes, no need to adjust
            
     ; xmm2 format: MMCFG_TARGET_LIST[23:0], local socket id [31:24]
      movd  eax, xmm2         ; get default target list
      and   eax, 000FFFFFFh   ; make sure [31:24] cleared
      mov   ebx, eax

      add   cl, ch             ; socketId * 3  = socketid+socketid+socketid;
      add   cl, ch
IF MAX_CPU_SOCKETS GT 4
      mov   edx, 0111b        ; node id field mask, >= 4s, 3 bit each, so no more add cl
ELSE
      add   cl, ch             ; 4S config, each node use 2 node fields, 2 * 3bit *socket#, add 3 more time
      add   cl, ch
      add   cl, ch
      mov   edx, 0111111b
ENDIF           
      shr   ebx, cl
      and   ebx, edx          ; only keep legacy node id field
      or    eax, ebx          ; now id 0 bit field repelace with legacy socket id
      shl   edx, cl
      not   edx
      and   eax, edx          ; repalce bit field with node id 0 
      movd  xmm2, eax         ; save updated target list back to xmm2

      ; now adjust iio bus
      mov   cl, ch            ; restore legacy node id to cl
      cmp   cl, 3
      jg    get_socket4_7_iiobus
      movd  eax, xmm4         ; is socket3:0, get iio bus range
      jmp   swap_iiobus
get_socket4_7_iiobus:
      movd  eax, xmm6         ; is socket7:4, get iio bus 
      sub   cl, 4             ; adjust for socket7:4 iio bus byte offset
swap_iiobus:
      mov   ebx, eax
      shl   cl, 3             ; socketId * 8 to get corresponding byte offset
      mov   edx, 0FFh         ; bus# bit mask
      shl   edx, cl
      not   edx
      and   eax, edx          ; node id 0 default iio bus always 0, now move to byte offset by leagcy socket id
      cmp   ch, 3
      jg    update_skt4_7_iiobus
 ;ppsong     movd  xmm4, eax
      jmp   update_offset0_iiobus
update_skt4_7_iiobus:
      movd  xmm6, eax
      movd  eax, xmm4
update_offset0_iiobus:        ; now need to update nodeid0 iio bus
      shr   ebx, cl
      and   ebx, 0FFh
      mov   al, bl            ; now we move legacy node id x default iio bus to node 0
      movd  xmm4, eax

      ; now adjust uncore bus
      mov   cl, ch            ; restore legacy node id to cl
      cmp   cl, 3
      jg    get_socket4_7_uncorebus
      movd  eax, xmm5         ; is socket3:0, get uncore bus 
      jmp   swap_uncorebus
get_socket4_7_uncorebus:
      movd  eax, xmm7         ; is socket7:4, get iio bus range
      sub   cl, 4             ; adjust for socket7:4 uncore bus byte offset
swap_uncorebus:
      mov   ebx, eax
      shl   cl, 3             ; socketId * 8 to get corresponding byte offset
      mov   edx, 0FFh         ; bus# bit mask
      shl   edx, cl
      not   edx
      and   eax, edx          ; node id 0 default uncore bus always 3fh for 4S 1Fh for 8S, now move to byte offset by leagcy socket id
IF MAX_CPU_SOCKETS GT 4
      mov   edx, 01Fh         ; > 4S config socket0 uncore bus 0x1F
ELSE
      mov   edx, 03Fh
ENDIF
      shl   edx, cl
      or    eax, edx          ; update legacy socekt uncore bus to default value
      cmp   ch, 3
      jg    update_skt4_7_uncorebus
      jmp   update_offset0_uncorebus
update_skt4_7_uncorebus:
      movd  xmm7, eax         ; save updated socket7:4 uncore bus back to xmm7
      movd  eax, xmm5
update_offset0_uncorebus:           ; now need to update nodeid0 iio bus
      shr   ebx, cl
      and   ebx, 0FFh
      mov   al, bl          ; now we move legacy node id x default iio bus to node 0
      movd  xmm5, eax
      jmp   Write_cfg_scheme_to_CSRs  ; done adjustment


calculate_cfg_scheme:
      mov   eax, LEGACY_BIOSSCRATCHPAD2
      READ_PCI_DWORD_LEGACY                    ; ebx = reg dword data
      and   ebx, 0FFh                          ; keep CPU present bitmap [7:0]
      movd  xmm3, ebx
      ; get bus range info from SSR03, and stored in xmm3 [31:8]
      mov   eax, SSR_LEGACY_BUS_CONFIG_INFO_CSR
      READ_PCI_DWORD_LEGACY                    ; ebx = reg dword data
      shl   ebx, 8h                            ; 
      movd  eax, xmm3
      or    eax, ebx
      movd  xmm3, eax      ; xmm3[31:8]=bus rang x for socket x (x=0..7), [7:0]=socket preset bimap

      xor   ebp, ebp       ; ebp = mmcfg_target_list data
      xor   esi, esi       ; esi = temperary IIO Bus # array [0..3, or 4..7], one byte for each node ID
      xor   edi, edi       ; edi = temperary Uncore Bus # array [0..3, or 4..7], one byte for each node ID
      xor   ecx, ecx       ; ecx[31:16] = total bus # range of all sockets
      xor   edx, edx       ; dx = nodeID, edx[31:16] = bit position of next NodeID field of MMCFG_TARGET_LIST

check_node_present:
      movd  eax, xmm3      ; restore Scratch Pad reg data into eax.
      mov   cx, dx         ; cx = node ID  (0..7)
      bt    ax, cx         ; CPU node present?
      jnc   next_node_id   ; no, skip

      ;build IIO bus# array in esi/xmm4(socket0:3), 6(socekt4:7)
      mov   ebx, ecx
      shr   ebx, 16t       ; bl = total bus # range accumulated so far for all sockets. Initial value = 0.
      or    esi, ebx       ; fill IIO bus# in esi

      ;calculate Target_List field for current NodeID
      shl   cx, 1          ; cx = NodeID * 2
      add   cx, dx         ; cx = NodeID * 3
      add   cx, 8          ; Bus Range info starts from bit8 of eax
      shr   eax, cl        ; eax [2:0] = Bus Range info for current node ID
      and   al, 0111b      ; al[2:0] = bus range size in 32-bus granulirity (0,1,2,3...7)
      inc   al             ; al[3:0] = bus range size in 32-bus granulirity (1,2,3...7,8)
      movzx ebx, dx        ; ebx[2:0] = current nodeID
      ror   edx, 16t       ; swap hi/low words in edx. DX now = bit position for next NodeID field in Target_List 
      mov   cx, dx
@@:
      shl   ebx, cl        ; shift nodeID in ebx to the right position
      or    ebp, ebx       ; fill in NodeID in Target_List for the current bus range pointed to by cl
      mov   cx, 3          ; get shift index in cl ready for the next 32-bus range
      add   dx, cx         ; update bit-pointer for next field in Target_List (3-bit for each NodeID field)

      ror   ecx, 16t       ; swap hi/low words in ecx. CX now = total bus# range of all sockets
      add   cx,  32t       ; keep count of total bus# range size of all sockets accumulated so far
      rol   ecx, 16t

      dec   al             ; done for this node ID?
      jnz   short @b       ; no, loop back
      rol   edx, 16t       ; swap hi/low words in edx. DX now = node ID

      ; build Uncore Bus# array in edi
      mov   ebx, ecx
      shr   ebx, 16t       ; bx = total bus # range accumulated so far for all sockets
      dec   ebx            ; bl = Uncore bus# for current nodeID (ex. 3Fh)
   
      ; following code is commented out to remove the option of uncore bus# = IIO bus# +1
      ;movd  eax, xmm4      ; get original SSR data
      ;;test  eax, 0x01000000    ; bit24 Uncore Bus Policy
      ;test  eax, 01000000h ; bit24 Uncore Bus Policy
      ;jnz   short @f      
      ;mov   ebx, esi       ; Uncore Bus# = IIO Bus# +1 
      ;and   bl, 0ffh
      ;inc   bl             ; bl = Uncore Bus# = IIO Bus# +1 (ex. 41h) 

      or    edi, ebx        ; fill uncore bus# in edi
    
next_node_id:
      ror   esi, 8         ; rotate esi for next node ID
      ror   edi, 8         ; rotate edi for next node ID
      cmp   dx, 3          ; check current node id
      jg    store_socket4_7_info
      movd  xmm4, esi      ; save iio bus info
      movd  xmm5, edi      ; save uncore bus info

      ;
      ; esi = temporary IIO Bus # array [0..3, or 4..7], one byte for each node ID    
      ; edi = temporary Uncore Bus # array [0..3, or 4..7], one byte for each node ID
      ;
      jb    data_saved     ; Scanning at Socket 3? 
      xor   esi, esi       ; Yes, clear esi edi before using esi edi again for Socket 4-7
      xor   edi, edi       
      jmp   data_saved

store_socket4_7_info:
      movd  xmm6, esi      ; save iio bus info
      movd  xmm7, edi      ; save uncore bus info
data_saved:
      inc   dx             ; inc Node ID in dx
      cmp   dx, MAX_CPU_SOCKETS          ; max 8 sockets/nodes
      jb    check_node_present

      movd  xmm2, ebp      ; save mmcfg target list

   ; xmm2 = calculated MMCFG_TARGET_LIST 
   ; xmm3 = mmcfg base [31:26]
   ; xmm4/6 = calculated IIO Bus # array for socket0:3/4:7
   ; xmm6/7 = calculated Uncore Bus # array for socket0:3/4:7
   ; ecx[31:16] = total bus range for all sockets (64,128,256); 

   ; calculate MMCFG_RULE using edi
      ; get MMCG Base from SSR03[29:24]
      mov   eax, SSR_LEGACY_BUS_CONFIG_INFO_CSR
      READ_PCI_DWORD_LEGACY
      shl   ebx, 2          ; make at 26:31
      mov   edi, ebx
      and   edi, 0fc000000h ; clear other bits
            
      mov   edx, ecx
      shr   edx, 16t       ; dx = total bus range for all sockets (64/128/192/256)
      cmp   dx, 128t
      jbe   @f
      mov   dx, 256t      ; if more than 128, such as 192 for 3S, round up to 256   
 @@:  shr   dx, 7          ; dx[1:0] = 10b/01b/00b 
      not   dl             ; 
      and   dl, 11b        ; dl[1:0] = 01b/10b/11b
      dec   dl             ; dl[1:0] = 00b/01b/10b 
      shl   dl, 1          ; dl[2:1] = 00b/01b/10b  for MMCFG_RULE[2:1]
      or    dl, 0x00000001       ; Enable = 1
      movzx edx, dl
      or    edi, edx       ; edi = final value for MMCFG_RULE

      movd  xmm3, edi      ; xmm3 <- MMCFG_RULE

Write_cfg_scheme_to_CSRs:
      ; xmm1  [7:0]= legact socket id,  [27:8]= CPU Family/stepping info from cpuid instruction
      ; xmm2 = MMCFG_TARGET_LIST[23:0], local socket id [31:24]
      ; xmm3 = MMCFG_RULE
      ; xmm4 = IIO Bus # array for socket0 - 3
      ; xmm5 = Uncore Bus # array for socket0 - 3
      ; xmm6 = IIO Bus # array for socket4 - 7
      ; xmm7 = Uncore Bus # array for socket4 - 7

      ; Read socketId from CSR
      mov   eax, CSR_LEGACY_SAD_CONTROL_CBO
      READ_PCI_DWORD_LEGACY                           ; ebx = reg dword data
      mov   bh, bl                                    ; nodeId encoding: SASS
      and   bl, 00011b
      and   bh, 01000b
      shr   bh, 1
      or    bl, bh                                    ; local socketId SSS in bl
      cmp   bl, 7                                     ; socket id must be 0..7
      jg    EnableAccessCsr_fatal_error               ; socket must be 0 - MAX_SOCKET_ID

      movzx edx, bl
      movd  eax, xmm2                                 ; save SocketID in xmm2[31:24]
      rol   eax, 8
      or    al, dl
      ror   eax, 8
      movd  xmm2, eax
      shl   edx, 16t                                  ; save SocketID in edx[23:16]
   
      ; Initialize  CPUBUSNO register in UBOX
      mov   cl,  bl                                   ; cl = socketId
      cmp   cl,  4                                    ; check is socket 4 - 7
      jge   is_socket4_7

      shl   cl,  3                                    ; cl = socketId * 8
      movd  ebx, xmm4                                 ; iioBusNum   
      shr   ebx, cl                                   ; ebx[7:0] = IIO Bus Number
      and   ebx, 000000ffh                            ; clear other bits
      movd  eax, xmm5                                 ; uncoreBusNum   
      jmp   set_bus_num

is_socket4_7:
      sub   cl,  4
      shl   cl,  3                                    ; cl = socketId * 8
      movd  ebx, xmm6                                 ; iioBusNum   
      shr   ebx, cl                                   ; ebx[7:0] = IIO Bus Number
      and   ebx, 000000ffh                            ; clear other bits
      movd  eax, xmm7                                 ; uncoreBusNum   

set_bus_num:
      shr   eax, cl                                   ; eax[7:0] = uncore bus #
      shl   eax, 8
      and   eax, 0000ff00h                            ; clear other bits
      or    ebx, eax                                  ; ebx [15:8] = uncore bus, [7:0] = IIO bus
      mov   ecx, ebx                                  ; save in ecx. ch = uncoreBus#, cl = iioBus#
      or    ebx, 0x80000000                                ; Valid = 1
      mov   eax, CSR_LEGACY_CPUBUSNO_UBOX             ; write CSR with dword in ebx
      WRITE_PCI_DWORD_LEGACY

;-------------------------------------------------------------------------------
; From this point on, valid matching bus# must be used to access all CSRs.
;-------------------------------------------------------------------------------
      ; edx [18:16] = socketID
      ; ecx [15:8] = uncore bus#, [7:0] = IIO bus#

      ; Initialize  MMCFG_Target_List register that matches the bus# assignment above
      mov   eax, CSR_LEGACY_MMCFG_TARGET_LIST_CBO
      and   eax, 0ff00ffffh                     ; clear bus# field [23:16]
      movzx ebx, ch                             ; ebx[7:0]   = uncore bus#
      shl   ebx, 16t                            ; ebx[23:16] = uncore bus#
      or    eax, ebx                            ; eax[23:16] = correct uncore bus#
      movd  ebx, xmm2                           ; ebx[23:0]  = mmcfg Target List
      and   ebx, 00ffffffh                      
      WRITE_PCI_DWORD_LEGACY

      ; Initialize and enable MMCFG_Rule register
      ; a. init Cbo MMCFG_RULE
      mov   ax, CSR_LEGACY_MMCFG_RULE_CBO AND 0000FFFFh  ; keep using the same bus# field in eax[23:16]
      movd  ebx, xmm3                           ; ebx = mmcfgRule
      or    ebx, 1                              ; set enable bit
      WRITE_PCI_DWORD_LEGACY
      and   ebx, (0x00000004+0x00000002+0x00000001)               ; keep mmcfgRule bus length and enable bits [2:0]
      mov   edi,  ebx                           ; save in edi
      ; b. init Ubox MMCFG_RULE
      mov   ax, CSR_LEGACY_MMCFG_RULE_UBOX AND 0000FFFFh
      READ_PCI_DWORD_LEGACY
      and   ebx, NOT (0x00000004+0x00000002+0x00000001)           ; clear bit2:0
      or    ebx, edi                              
      WRITE_PCI_DWORD_LEGACY                    

; ------------------------------------------------------------------
; When all BSPs are done with this step, remote CSR access among sockets is enabled. Valid bus number must be used to
; match the bus number of the target socket. Access to bus0  will be routed to Legacy Socket no matter which socket
; issues the access. 
; ------------------------------------------------------------------

      movd  edi, xmm3
      and   edi, 0fffffff0h                     ; edi = MMCFG_BASE_ADDR

      ; edi = MMCFG_BASE_ADDR
      ; edx [18:16] = socketID
      ; ecx [15:8] = uncore bus, [7:0] = IIO bus

      ; init CPUNODEID CSR
      mov   eax, CSR_CPUNODEID_UBOX
      and   eax, 000fffffh                      ; clear bus# field [27:20]
      movzx ebx, ch                             ; ebx[7:0]   = uncore bus#
      shl   ebx, 20t                            ; ebx[27:20] = uncore bus#
      or    ebx, eax                            ; [23:16] = correct bus#
      add   ebx, edi                            ; ebx = MMCFG_BASE + reg addr
      mov   eax, dword ptr ds:[ebx]             ; read CSR
      and   eax, NOT (07h)                      ; clear bit[2:0]
      ror   edx, 16t                            ; dl[2:0]= my socket ID
      or    al, dl                              ; al[2:0]= my socket ID
      rol   edx, 16t
      mov   dword ptr ds:[ebx], eax             ; write back CSR

      ; init CSR_GLOBAL_PKG_C_S_CONTROL_PCU CSR in PCU
      ;  Note: for a system without Node Controller, legacy socket is always treated as Master,
      ;        which matches the default value (0) of MASTER_NID field 
      movd  eax, xmm1                           ; get legacy node id
      mov   dh, al                              ; save it in dh
      mov   eax, CSR_GLOBAL_PKG_C_S_CONTROL_PCU AND 000fffffh  ; clear bus# field [27:20]
      and   ebx, 0fff00000h                     ; keep using the same uncore bus#
      or    ebx, eax                            ; ebx = MMCFG_BASE + reg addr
      mov   eax, dword ptr ds:[ebx]             ; read CSR into eax
      and   eax, NOT (0700h)                    ; clear MY_NID bit[10:8]
      ror   edx, 8t                             ; dx[10:8] = my socket ID
      or    ah, dh                              ; ax[10:8] = my socket ID
      rol   edx, 8t
      cmp   ah, dh                              ; my socket Id == legacy socket ID?
      jnz   short @f                            ; no, skip
      or    eax, 0x00000004                           ; set AM_I_MASTER=1 if legacy socket
@@:   mov   dword ptr ds:[ebx], eax             ; write back CSR

      ; init CPU_BUS_NUMBER CSR in PCU2
      mov   eax, CSR_CPU_BUS_NUMBER_PCU2 AND 000fffffh  ; clear bus# field [27:20]
      and   ebx, 0fff00000h                     ; keep using the same uncore bus#
      or    ebx, eax                            ; ebx = MMCFG_BASE + reg addr
      mov   eax, dword ptr ds:[ebx]             ; read CSR into eax
      mov   ax, cx                              ; eax = [15:8] = uncore bus, [7:0] = IIO bus
      mov   dword ptr ds:[ebx], eax             ; write back CSR

      ; save config address to esi for later use
      mov   esi, ebx                            ; esi = config address of CSR_CPU_BUS_NUMBER_PCU2 on uncore bus#

      ; init CPUBUSNO CSR in IIO
      mov   eax, CSR_CPUBUSNO_IIO AND 000fffffh  ; clear bus# field [27:20]
      movzx ebx, cl                             ; ebx[7:0]   = iio bus#
      shl   ebx, 20t                            ; ebx[27:20] = iio bus#
      or    ebx, eax                            ; [23:16] = correct bus#
      add   ebx, edi                            ; ebx = MMCFG_BASE + reg addr
      mov   eax, dword ptr ds:[ebx]             ; read CSR
      mov   ax, cx                              ; eax = [15:8] = uncore bus, [7:0] = IIO bus
      or    eax, 0x00010000                          ; set Valid = 1
      mov   dword ptr ds:[ebx], eax             ; write back CSR

      ; init MMCFG CSR in IIO

      movd  eax, xmm1                           ; xmm1[27:8] = cpu family/stepping info from cpuid instruction
      shr   eax, 8
      and   eax, 000fffffh                      ; eax[19:0] = cpu family/stepping info from cpuid instruction
      cmp   eax, (CPU_FAMILY_HSX SHL 4) OR A0_REV_HSX    ; HSX-A0 stepping?
      mov   eax, CSR_MMCFG_IIO_A0  AND 000fffffh  ; clear bus# field [27:20]
      mov   edx, CSR_MMCFG_IIO_BASE_LIMIT_GAP_A0  ; offset for CSR_MMCFG_IIO_limit
      jz    @f                                  ; Yes, HSX-A0,BDX
      mov   eax, CSR_MMCFG_IIO  AND 000fffffh   ; No. clear bus# field [27:20] (HSX-B0 Update: Change CSR_MMCFG_IIO_A0 to CSR_MMCFG_IIO)
      mov   edx, CSR_MMCFG_IIO_BASE_LIMIT_GAP   ; offset for CSR_MMCFG_IIO_limit
@@:
      and   ebx, 0fff00000h                     ; keep using the same IIO bus#  
      or    ebx, eax
      mov   dword ptr ds:[ebx], edi             ; write back CSR

      ; clear higher 32-bit of base address if HSX-B0 or later
      cmp   edx, CSR_MMCFG_IIO_BASE_LIMIT_GAP_A0 ; HSX-A0?
      je    @f                                   ; yes, skip
      mov   dword ptr ds:[ebx+4], 0              ; Clear higher 32-bit of mmcfg base address in IIO
@@:
      ; calculate mmcfg limit = mmcfg_base + Max_Bus * 1MB)
      movd  ecx, xmm3                           ; ecx = copy of MMCFG_RULE
      and   ecx, 0110b
      shr   cl, 1                               ; cl = max bus number encoding. 00: 256, 01: 128, 10: 64
      mov   eax, 0100h                          ; eax = 256 (buses)
      shr   eax, cl                             ; eax = 256 / 128 / 64 buses
      shl   eax, 20t                            ; eax = eax * 100000h (i.e.Max_Bus * 1MB) 
   
      add   eax, edi                            ; eax = MMCFG_BASE_ADDR + MMCFG_SIZE
      sub   eax, 1                              ; last decode byte is last byte in previous 64MB block
      and   eax, 0fc000000h                     ; 64MB block address of last block of MMCFG
      add   ebx, edx                            ; CSR_MMCFG_IIO + gap  (MMCFG.Limit) 
      mov   dword ptr ds:[ebx], eax             ; write back CSR

      ; save config address to edi for later use
      mov   edi, ebx                            

      ; esi = config address of CSR_CPU_BUS_NUMBER_PCU2 on uncore bus#
      ; edi = config address of CSR_MMCFG_IIO+4 on IIO bus# for HSX A0, CSR_MMCFG_IIO+8 for HSX B0 and Above
      ; esi[27:20] = uncore bus#
      ; edi[27:20] = IIO bus#

      ; Check CPU stepping and perform stepping-specific tasks

      ; Set the new "Valid" bit in CPU_BUS_NUMBER register of PCU
      ;mov   eax, CSR_CPU_BUS_NUMBER_PCU2 AND 000fffffh  ; clear bus# field [27:20]
      ;and   esi, 0fff00000h                     ; keep using the same uncore bus#
      ;or    esi, eax                            ; esi = register config addr
      mov    eax, dword ptr ds:[esi]             ; read the CSR
      or     eax, 0x80000000                          ; "Valid" bit = 1
      mov    dword ptr ds:[esi], eax             ; write the CSR

; CPL3 Change Start - Send SET_CORE_RING_RATIO (0xA4) B2P Command in cold boot path for C0 stepping onwards for HSX-EP and A1 stepping onwards for BDX-EP.
      mov   eax, 1
      cpuid
      and eax, 0fffffh
      cmp eax, (CPU_FAMILY_HSX shl 4)+ STEPPING_ID_C0  ; Check for HSX C0  (0x306F2)
      jb EndCpl3
      mov ebx, eax				    ; Preserve CPUID info in EBX, before losing stepping info from EAX
      shr eax, 4
      cmp eax, CPU_FAMILY_HSX                       ; HSX CPU?
      je  StartCpl3
      cmp eax, CPU_FAMILY_BDX_DE                    ; BDX-DE CPU? This feature is not supported on BDX-DE
      je  EndCpl3
      cmp eax, CPU_FAMILY_BDX                       ; BDX CPU?
      jne EndCpl3
      cmp ebx, (CPU_FAMILY_BDX shl 4)+ A0_REV_BDX   ; Check for BDX A0  (0x406F0)
      ja  StartCpl3
      mov eax, CSR_CAPID1_HSX_BDX            ; If not a BDX-EP B0 or above, check for A1 stepping (CAPID1_CSR[20]=1), as this B2P command is supported only from A1 stepping onwards.
      and eax, 0fffffh
      mov ebx, esi
      and ebx, 0fff00000h
      or  eax, ebx
      test  dword ptr ds:[eax], 0x00100000
      jz EndCpl3
 StartCpl3:
      ;check for warm reset
      mov eax, CSR_STICKYSCRATCHPAD07
      and eax, 0fffffh
      mov ebx, esi
      and ebx, 0fff00000h
      or  eax, ebx
      test  dword ptr ds:[eax], 0x00000020
      jz EndCpl3
      ;Construct SET_CORE_RING_RATIO command with actual P1 ratio and max uncore ratio
      mov ecx, 0ceh	   ; Read PLATFORM_INFO MSR (0xCE) that contains max non turbo ratio
      rdmsr
      mov ebx, eax
      and ebx, 0ff00h      ; PLATFORM_INFO[15:8] = Max Non Turbo Ratio
      mov ecx, 0620h       ; Read UNCORE_RATIO_LIMIT MSR (0x620) that contains max LLC/Ring Ratio
      rdmsr
      and eax, 0ffh        ; UNCORE_RATIO_LIMIT[7:0] = Max LLC/Ring Ratio
      shl eax, 16
      mov ecx, 0800000a4h  ; Store the Set Core Ring Ratio command data in ECX
      or  ecx, eax
      or  ecx, ebx
      mov eax, CSR_BIOS_MAILBOX_INTERFACE_PCU_FUN1_REG_HSX
      and eax, 0fffffh
      mov ebx, esi
      and ebx, 0fff00000h
      or  eax, ebx
Loop2:
     ; PCU Mailbox Interface
      test  dword ptr ds:[eax], 080000000h     ; Check for RUN_BUSY bit
      jnz   Loop2
      mov   dword ptr ds:[eax], ecx            ; Request for P1 speed
Loop1:
      test   dword ptr ds:[eax], 080000000h    ; Check for RUN_BUSY bit
      jnz   Loop1
EndCpl3:

; CPL3 Change End




eac_exit:
     RET_ESI_MMX4                              ; return


EnableAccessCsr_fatal_error:      ; fatal errors
      ;  debug - write an error code to PORT80()
      PORT80(0CCh)
      jmp  $                         ; dead loop

EnableAccessCSR    ENDP



;-------------------------------------------------------------------------
; CPU Early Workaround
;Executed by all package BSPs 
; Input: 
;    Stack available
; Output:
;    All general purpose registers destroyed
;-------------------------------------------------------------------------
ProcessorWorkaround PROC    NEAR    PUBLIC

  ; HSX 4165788 WA for PROCHOT - start
  pushad

  mov eax, 1
  cpuid
  cmp eax, (CPU_FAMILY_HSX SHL 4) OR A0_REV_HSX  
  jne done_hsx_wa           ; br if not HSX A0 or BDX DE,BDX EP grt than A0
  mov ecx, MSR_POWER_CTL
  rdmsr
  or  eax, 0x00000001 + 0x00200000
  wrmsr

done_hsx_wa: 
  popad

  ; HSX WA for PROCHOT - end

  call  _OEMCpuSecInit
  ret
ProcessorWorkaround  ENDP

;-------------------------------------------------------------------------
;
; Routine Description:
;
;    QPIEarly Workaround
;    Executed by all package BSPs, incl. SBSP. 
;    When contingency Silicon w/a are fixed by using MSR programming, it has to be done by each package BSP.
;    SBSP in QPI RC can access uncore CSR but not core MSR in remote packet BSP.
;    The current w/a is:
;         Program MSR as workarounds for Ax steppings.
;         SBSP writs the value into UBOX Sticky Scratch 07.
;         At subsequent warm resets, SBSP as well as all PBSPs will program MSRs as instructed.
;         Silicon fix will be added in B0 stepping and later.
;         See Brickland BIOS sighting 4029893 from Ivytown begeco 4539572 4539608
;        
;         Bit format for UBOX Sticky Scratch 07:
;        
;         [7]:       - 0 = to not program, 1 = to program MSR_AX_STEPPING_CBOBC
;         [9-8]:     - MSR_AX_STEPPING_CBOBC bit[1:0]
;         [10]:      - MSR_AX_STEPPING_CBOBC bit[3]
;         [11]:      - 0 = not program, 1 = program MSR_AX_STEPPING_R3QPI
;         [15-12]:   - MSR_AX_STEPPING_R3QPI bit[3:0]. If 2nd HA/MC fuse is set, bit[7:4] = bit[3:0]
;
;     Note: 
;         This code gets called at every reset, whether cold or warm reset. 
;         But for a sticky CSR, such as CSR_STICKYSCRATCHPAD07, the bits can only be seen as set at a subsequent warm reset following the original cold reset. 
;    
; Input: 
;
;    Stack available
;
; Output:
;
;    All general purpose registers destroyed
;
;-------------------------------------------------------------------------
QpiProgramMsrForWorkaound       PROC    NEAR    PUBLIC
        pushad

        call    GetLocalSktId                           ; CL = own local socket ID
        mov     eax, CSR_STICKYSCRATCHPAD07
        call    ReadCpuCsr                              ; EAX = current CSR data
        push    eax
        test    ax, 0x00000080
        jz      QpiNoLocHTCred

        mov     ebx, eax
        shr     eax, 8                                  ; bit[9:8] becomes bit[1:0]
        and     al, 03h                                
        shr     ebx, 7                                  ; bit[10] becomes bit[3]
        and     bl, 08h                                
        or      al, bl
        movzx   eax, al

        push    eax
        mov     ecx, MSR_A0_STEPPING_CBOBC
        ; rdmsr                                         ; Temporarily commmented out because the MSR is not yet available.
        pop     eax
        ; wrmsr                                         ; Temporarily commmented out because the MSR is not yet available.
        
QpiNoLocHTCred:
        pop     eax
        test    ax, 0x00000800
        jz      QpiNoCreditMerging

        shr     eax, 12                                  ; bit[15:12] becomes bit[3:0]
        and     al, 0Fh                                
        movzx   eax, al
        mov     ebx, eax
        shl     ebx, 4                                  ; bit[3:0] becomes bit[7:4]
        or      eax, ebx

        push    eax
        mov     ecx, MSR_A0_STEPPING_R3QPI
        ; rdmsr                                         ; Temporarily commmented out because the MSR is not yet available.
        pop     eax
        ; wrmsr                                         ; Temporarily commmented out because the MSR is not yet available.

QpiNoCreditMerging:

        popad
        ret
QpiProgramMsrForWorkaound  ENDP

;-------------------------------------------------------------------------
; Pass in the Over-Clocking PLL Ratio (MSR-61E Bits[3:2]) for 
; QPIRC via BIOS Non-Sticky Scratch Pad-2.
;
; Input:  None
;   
; Output: None
;
; Registers changed:
;   - CSR_BIOSSCRATCHPAD07 Bits[3:2]
;-------------------------------------------------------------------------
QpiPassInPllRatio PROC    NEAR
        pushad

        ; Assume Over-clocking feature is disabled
        mov     edx, 0                                  ; PLL Ratio (EDX) = 0

        ; Check actual status of Over-Clocking feature
        call    GetLocalSktId                           ; CL = own local socket ID
        mov     eax, CSR_CAPID4_HSX_BDX
        call    ReadCpuCsr
        test    eax, 0x10000000                              ; Over-clocking enabled?
        jz      QpiPassInPllRatio_StorePllRatio         ; If disabled, do not read PLL Ratio MSR - Just use default value

        ; Over-clocking enabled so get actual PLL Ratio (EDX)
        mov     ecx, MSR_OVER_CLOCK_PLL_RATIO           ; MSR only valid (readable) if Over-clocking is enabled
        rdmsr
        and     eax, (0x00000002+0x00000001)                        ; PLL Ratio in Bits[1:0]
        mov     edx, eax                                ; Save PLL Ratio for later use

QpiPassInPllRatio_StorePllRatio:
        ; Update scratch pad reg with PLL Ratio (EDX)
        mov     eax, CSR_BIOSNONSTICKYSCRATCHPAD2       ; CL already set to own local socket ID
        call    ReadCpuCsr
        mov     ebx, eax                                ; EBX = current Scratch Pad value

        and     ebx, NOT(0x00000008+0x00000004)                     ; Clear destination field within Scratch Pad (Bits[3:2])
        shl     edx, 2                                  ; Shift PLL Ratio into position
        or      ebx, edx                                ; Merge PLL Ratio into Scratch Pad
        mov     eax, CSR_BIOSNONSTICKYSCRATCHPAD2       ; CL already set to own local socket ID
        call    WriteCpuCsr                             ; EBX = current Scratch Pad and updated PLL Ratio

        popad
        ret
QpiPassInPllRatio ENDP                  


;-------------------------------------------------------------------------
; Read a Dword from PCI register 00h thru FFh using IO port CF8h/CFCh
; Input:
;   Stack is avaialble
;   
; Output: AL = SBSP Socket ID
; Registers changed: None except AL
;-------------------------------------------------------------------------
GetSbspSktId      PROC    NEAR
        movd eax, xmm1
        and  al, 7
        ret
GetSbspSktId      ENDP                  

;-------------------------------------------------------------------------
; Returns Socket/Packge ID of the current processor
; Input: 
;   Stack is avaialble
;   XMM registers initialized by EnableAccessCSR routine
;      XMM2[31:24] register contains local Socket ID
; Output: CL = Socket/Package ID of the current processor
; Registers changed: None except ecx
;-------------------------------------------------------------------------
GetLocalSktId      PROC    NEAR    PUBLIC

     movd  ecx, xmm2               ; xmm2[31:24] stores the socketID
     shr   ecx, 24t
     ret

GetLocalSktId      ENDP                  


;----------------------------------------------------------------------------
; SetupProcessorCheckinData
;  Executed by all socket BSPs.  Store data in its own local scratchpad register:
;       bit[0]        - check in flag
;       bit[23:8]   - ApicId  (only 16-bit is used)
;       bit[30:27] - stepping
;  Input:  Stack available
;          EnableAccessCSR has been called
;  Output: All general puropse registers preserved.
;----------------------------------------------------------------------------

SetupProcessorCheckinData    PROC    NEAR    PUBLIC

        pushad

        mov    eax, 1
        cpuid                                               ; ebx[31:24] = initial APIC ID, eax[3:0] = stepping
        and    ebx, 0ff000000h
        shr    ebx, 16t                                     ; APIC ID in ebx[23:8]
        and    eax, 0fh
        shl    eax, 27t                                     ; eax[30:27] = stepping
        mov    esi, eax                                     ; esi [30:27] = setpping
        push   ebx                                          ; save ebx

        ; check to see if processor is x2Apic capable
        mov    eax, 0
        cpuid
        pop    ebx                                          ; restore ebx
        cmp    eax, 0bh                                     ; check to see if processor is x2Apic capable
        jb     SaveDataAndSetCheckIn                        ; processor is not x2APIC capable
      
        ; processor is x2Apic capable, get ApicId from cpuid leaf B
        mov    eax, 0bh
        xor    ecx, ecx
        cpuid  
        movzx  ebx, dx                                      ; though X2Apid is 32bit wide,                             
        shl    ebx, 8                                       ; HW support up to 12 bits (bit31:12=0)

SaveDataAndsetCheckIn:
        ; ebx [23:8] = Apic ID,  esi [30:27] = stepping
        call   GetLocalSktId                                 ; CL = own local socket ID
        mov    eax, SR_PBSP_CHECKIN_CSR
        call   ReadCpuCsr                                    ; EAX = current CSR data
        and    eax, 870000ffh                                ; clear bit[30:27], [23:8]
        or     ebx, eax                                      ;  ebx <- apci id
        or     ebx, esi                                      ;  ebx <- stepping
        or     ebx, 1                                        ; set check in bit
        mov    eax, SR_PBSP_CHECKIN_CSR
        call   WriteCpuCsr

        popad
        ret
  
SetupProcessorCheckinData       ENDP



;-------------------------------------------------------------------------
; Non-SBSPs execute this routine to clear BSP flag in MSR and
; loop on a local scratch pad register for command from SBSP
; Input: None
;   
; Output: None
;-------------------------------------------------------------------------

ParkNbsp      PROC    NEAR

     ; clear bit8 BSP flag in MSR
     mov     ecx, MSR_APIC_BASE
     rdmsr
     and     eax, NOT 0x00000100                                 ; clear bit8 BSP flag in MSR
     wrmsr

     ; clear the dispatch CSR        
     call  GetLocalSktId                                   ; CL = Local Socketr ID 
     mov   eax, SR_MEMORY_DATA_STORAGE_DISPATCH_PIPE_CSR   ; Pipe Dispatch register in local socket
     xor   ebx, ebx                                        ; Clear the dispactch CSR
     call  WriteCpuCsr 

   ; When SR_MEMORY_DATA_STORAGE_DISPATCH_PIPE_CSR becomes non-zero,
   ;       SR_MEMORY_DATA_STORAGE_DATA_PIPE_CSR will be the jmp location

SitAndSpin:
     mov   eax, SR_MEMORY_DATA_STORAGE_DISPATCH_PIPE_CSR   ; Pipe Dispatch register in local socket
     call  ReadCpuCsr

     cmp   eax, 0
     jz    SHORT SitAndSpin

     ; RAS requirements START
     cmp   eax, PIPE_DISPATCH_COMMAND_TEAR_NEM
     jne   @f
     call  TearDownNEMandHalt     ; will never return

@@:
     cmp   eax, PIPE_DISPATCH_COMMAND_PREPARE_RESET
     jne   @f
     call  PrepareForReset        ; will never return

@@:
     ; RAS requirements END

     mov   eax, SR_MEMORY_DATA_STORAGE_COMMAND_PIPE_CSR   ; Pipe Command register in local socket
     call  ReadCpuCsr
  
     cmp   eax, PIPE_DISPATCH_SYNCH_PSYSHOST
     jz    GoToAction

     ; clear out dispatch register because command is invalid
     mov   eax, SR_MEMORY_DATA_STORAGE_DISPATCH_PIPE_CSR   ; Pipe Dispatch register in local socket
     xor   ebx, ebx                                        ; Clear the dispactch CSR
     call  WriteCpuCsr 
     jmp   SitAndSpin
           
GoToAction:
   
     mov   eax, SR_MEMORY_DATA_STORAGE_DATA_PIPE_CSR       ; Pipe Data register in local socket
     call  ReadCpuCsr
     mov   esp, eax                                        ; sync up stack pointer with SBSP
  
     mov   eax, SR_MEMORY_DATA_STORAGE_DISPATCH_PIPE_CSR   ; Pipe Dispatch register in local socket
     xor   ebx, ebx                                        ; Clear the dispactch CSR
     call  WriteCpuCsr 

WaitForJmpPointer:
     mov   eax, SR_MEMORY_DATA_STORAGE_DISPATCH_PIPE_CSR   ; Pipe Dispatch register in local socket
     call  ReadCpuCsr

     cmp   eax, 0
     jz    SHORT WaitForJmpPointer

     mov  eax, SR_MEMORY_DATA_STORAGE_DISPATCH_PIPE_CSR
     call GetBusNum                                    ; update EAX[27:20] with the correct bus # 
     call GetMmcfgBase                                 ; esi = MMCFG Base address
     add  esi, eax                                     ; form cfg register address in esi
     and  esi, 0fffff000h                              ; keep only Bus:Dev:Func portion of it
  
     mov   eax, SR_MEMORY_DATA_STORAGE_DATA_PIPE_CSR   ; Pipe Data register in local socket
     call  ReadCpuCsr

   ; EAX = Function pointer to PipeSlaveInit( UINT32 NodeId, UINT32 CfgAddrBDF) 
   ; Emulate a C-style function call
     push   esi                                             ; push input arg (PCIE Config Address w/o register offset)
     push   ecx                                             ; push input arg (local socketId)
     call   eax                                             ; call PipeSlaveInit( UINT32 NodeId, UINT32 CfgAddrBDF) 
                                                            ; Note: Control will not return to here
ParkNbsp      ENDP                  

;-------------------------------------------------------------------------
; Hot Plug CPU execute this routine to go to halt state.  So that SBSP can
; issue reset on this socket.  Clear the Command Dispatch register before
; going to halt, so that SBSP knows that PBSP executed this routine
;
; Input: None
;   
; Output: None
;-------------------------------------------------------------------------

PrepareForReset    PROC    NEAR    PUBLIC

    ; clear out dispatch register to communicate SBSP
    mov   eax, SR_MEMORY_DATA_STORAGE_DISPATCH_PIPE_CSR   ; Pipe Dispatch register in local socket
    xor   ebx, ebx                                        ; Clear the dispactch CSR
    call  WriteCpuCsr 

loop1 :
    cli
    hlt
    jmp loop1     

PrepareForReset     ENDP


;-----------------------------------------------------------------------
; AcquireReleaseGlobalSemaphore
;-----------------------------------------------------------------------
;  Executed by a socket BSP to acquire ownership of the global semaphore
;  Input:  AL  1: Acquire    0: Release    
;          Stack available
;          EnableAccessCSR has been executed
;  Output: All general puropse registers preserved
;-----------------------------------------------------------------------

AcquireReleaseGlobalSemaphore    PROC    NEAR    PUBLIC

        pushad

        ; prepare data in ebx based on input CL, CH

        xor    ebx, ebx
        call   GetLocalSktId                                ; CL = local socket ID
        mov    bl, cl
        shl    ebx, 24t                                     ; ebx[26:24] = Requester NodeID
        or     al, al                                       ; Acquire or Release ?
        jz     short @f                                     ; Release Semaphore, keep bit1 = 0
        or     bl,  0x00000002                                    ; set bit1 (Acquire)
@@:
        ; calculate the address of the BSP check-in scratch register (on SBSP socket)
 
        push   ecx
        call   GetSbspSktId                                 ; al = SBSP socket ID
        mov    cl, al
        mov    eax, CSR_SYSTEMSEMAPHORE0
        call   GetBusNum                                    ; update EAX[27:20] with the correct bus# 
        call   GetMmcfgBase                                 ; esi = MMCFG Base Address
        add    esi, eax                                     ; form cfg register address in esi
        pop    ecx

        ; Read/modify/write Global Semaphore CSR
        mov    eax, dword ptr ds:[esi]                      ; read CSR into eax
        and    eax, 0F8FFFFFDh                              ; only modify bit[26:24] and bit[1]
        or     eax, ebx
        mov    dword ptr ds:[esi], eax                      ; write back CSR
        test   al, 0x00000002                                     ; Release?
        jz     args_exit                                    ; yes, done and exit

AcquireLoop:
        ;  CL = local socket ID
        ;  Read Global Semaphore until CurrentNode = local socket ID
        mov    eax, dword ptr ds:[esi]                      ; read CSR into eax
        shr    eax, 2                                       ; shift CurrentNode bit[4:2] to bit [2:0]
        and    al, 07h
        cmp    al, cl
        jne    short AcquireLoop

args_exit:
        popad
        ret
  
AcquireReleaseGlobalSemaphore     ENDP



;-------------------------------------------------------------------------
; Get MMCFG-based PCI Config Address of a CSR register
; Input: 
;   Stack is NOT available
;   MMX6 = return address via RET_ESI_MMX6 macro
;   XMM registers initialized by EnableAccessCSR routine
;      XMM2 register [31:24] contains local Socket ID
;      XMM3 register contains MMCFG_RULE
;   XMM4/XMM5 registers contain the IIO/Uncore bus number array for socket0:3 initialized by EnableAccessCSR routine
;   XMM6/XMM7 registers contain the IIO/Uncore bus number array for socket4:7 initialized by EnableAccessCSR routine
;   EAX = PCIe config address format with bus# field defined as follows
;     EAX[31:28] = 0h
;     EAX[27:20] = BusType #  ( 0: IIO device,  1: Uncore device)
;     EAX[19:15] = Dev #
;     EAX[14:12] = Func #
;     EAX[11:0]  = Reg offset (dword aligned)
;   CL  = socketId (0,1,2,3) of the target CPU socket
; Output: EDI = Config address of the CSR
;         The caller can then use mov eax, dword ptr [edi] to access the CSR data
; Registers changed: eax, ebx, edi, esi
;-------------------------------------------------------------------------

GetCpuCsrAddrNoStack    PROC  PUBLIC

      mov   ebx, 0ff00000h                            
      cmp   cl, 3                                        ; socket 0 - 3?
      jg    is_s4_7                                      ; no, br

      and   ebx, eax                                     ; ebx[27:20] = bus type (0: IIO bus, 1: Uncore Bus) 
      movd  ebx, xmm4                                    ; ebx = IIO Bus# array
      jz    short @f                                     ; zf set/clear by above "and"
      movd  ebx, xmm5                                    ; ebx = Uncore Bus# array   
      jmp   @f

is_s4_7:
      sub   cl,  4                                       
      and   ebx, eax                                     ; ebx[27:20] = bus type (0: IIO bus, 1: Uncore Bus) 
      movd  ebx, xmm6                                    ; ebx = IIO Bus# array
      jz    short @f
      movd  ebx, xmm7                                    ; ebx = Uncore Bus# array   

@@:
      shl   cl,  3                                       ; cl = socketId * 8
      shr   ebx, cl                                      ; ebx[7:0] = bus #
      shr   cl,  3                                       ; restore cl
      and   ebx, 000000ffh                               ; clear other bits
      shl   ebx, 20t                                     ; ebx[27:20] = bus #
      and   eax, 000fffffh                               ; mask off bus type field in eax
      or    ebx, eax                                     ; replace it with proper bus #
      movd  edi, xmm3                                    ; xmm3 stores MMCFG_RULE
      and   edi, 0fffffff0h                              ; make sure the lower 4 bits are 0s
      add   edi, ebx

      RET_ESI_MMX6

GetCpuCsrAddrNoStack    ENDP


;-------------------------------------------------------------------------
; Read a Dword from PCIe config register using mmcfg method
; Input: 
;   EAX = PCIe config address format with bus# field defined as follows
;     EAX[31:28] = 0h
;     EAX[27:20] = BusType #  ( 0: IIO device,  1: Uncore device)
;     EAX[19:15] = Dev #
;     EAX[14:12] = Func #
;     EAX[11:0]  = Reg offset (dword aligned)
;   CL  = socketId (0,1,2,3,4,5,6,7) of the target CPU
;   XMM registers initialized by EnableAccessCSR routine
;      XMM2 register [31:24] contains local Socket ID
;      XMM3 register contains MMCFG_RULE
;   XMM4/XMM5 registers contain the IIO/Uncore bus number array for socket0:3 initialized by EnableAccessCSR routine
;   XMM6/XMM7 registers contain the IIO/Uncore bus number array for socket4:7 initialized by EnableAccessCSR routine
;   Stack is available
; Output: EAX = regiser dword data
; Registers changed: None except EAX
;-------------------------------------------------------------------------

ReadCpuCsr      PROC    NEAR    PUBLIC

      push  esi
      call  GetBusNum                                    ; update EAX[27:20] with the correct bus# for the socket ID
      call  GetMmcfgBase                                 ; esi = MMCFG Base Address
      add   esi, eax                                     ; form cfg register full address in esi
      mov   eax, dword ptr ds:[esi]                      ; read dword
      pop   esi
      ret

ReadCpuCsr ENDP




;-------------------------------------------------------------------------
; Write a Dword from PCIe config register using mmcfg method
; Input: 
;   EAX = PCIe config address format with bus# field defined as follows
;     EAX[31:28] = 0h
;     EAX[27:20] = BusType #  ( 0: IIO device,  1: Uncore device)
;     EAX[19:15] = Dev #
;     EAX[14:12] = Func #
;     EAX[11:0]  = Reg offset (dword aligned)
;   CL  = socketId (0,1,2,3) of the target CPU
;   XMM registers initialized by EnableAccessCSR routine
;      XMM2 register [31:24] contains local Socket ID
;      XMM3 register contains MMCFG_RULE
;   XMM4/XMM5 registers contain the IIO/Uncore bus number array for socket0:3 initialized by EnableAccessCSR routine
;   XMM6/XMM7 registers contain the IIO/Uncore bus number array for socket4:7 initialized by EnableAccessCSR routine
;   Stack is available
; Output: None
; Registers changed: None
;-------------------------------------------------------------------------

WriteCpuCsr PROC

      push  eax
      push  esi
      call  GetBusNum                                    ; update EAX[27:20] with the correct bus# for the socket ID
      call  GetMmcfgBase                                 ; esi = MMCFG Base Address
      add   esi, eax                                     ; form cfg register full address in esi
      mov   dword ptr ds:[esi], ebx                      ; read dword
      pop   esi
      pop   eax
      ret

WriteCpuCsr ENDP




;-------------------------------------------------------------------------
;  Update EAX[27:20] with the target Bus number ( IIO bus or  Uncore bus)
; Input:
;   EAX = PCIe config address format with bus# field defined as follows
;     EAX[31:28] = 0h
;     EAX[27:20] = BusType #  ( 0: IIO device,  1: Uncore device)
;     EAX[19:15] = Dev #
;     EAX[14:12] = Func #
;     EAX[11:0]  = Reg offset (dword aligned)
;   CL  = socketId (0,1,2,3) of the target CPU
;   XMM4/XMM5 registers contain the IIO/Uncore bus number array for socket0:3 initialized by EnableAccessCSR routine
;   XMM6/XMM7 registers contain the IIO/Uncore bus number array for socket4:7 initialized by EnableAccessCSR routine
; Output: EAX[27:20] updated with the actual bus # intended
; Registers changed: None except EAX[27:20]
;-------------------------------------------------------------------------
GetBusNum      PROC

      push  ebx
      push  ecx
      push  edx

      mov   edx, 0ff00000h                            
      ; if its socket4 - 7  ; try xmm6/7
      cmp   cl, 3
      jg    is_socket4_7
      movd  ebx, xmm4                                    ; ebx = IIO Bus# array
      and   edx, eax                                     ; edx[27:20] = bus type (0: IIO bus, 1: Uncore Bus) 
      jz    short @f
      movd  ebx, xmm5                                    ; ebx = Uncore Bus# array   
      jmp   @f

is_socket4_7:
      sub   cl,  4                                       
      movd  ebx, xmm6                                    ; ebx = IIO Bus# array
      and   edx, eax                                     ; edx[27:20] = bus type (0: IIO bus, 1: Uncore Bus) 
      jz    short @f
      movd  ebx, xmm7                                    ; ebx = Uncore Bus# array   

@@:
      shl   cl,  3                                       ; cl = socketId * 8
      shr   ebx, cl                                      ; ebx[7:0] = bus #
      and   ebx, 000000ffh                               ; clear other bits
      shl   ebx, 20t                                     ; ebx[27:20] = bus #
      and   eax, 000fffffh                               ; mask off bus type field in eax
      or    eax, ebx                                     ; replace it with proper bus #

      pop   edx
      pop   ecx
      pop   ebx
      ret

GetBusNum      ENDP




;-------------------------------------------------------------------------
; Get MMCFG base address
;  Input: 
;   Stack avaialble. 
;   XMM3 register contains MMCFG_RULE
;  Output: ESI = 32-bit MMCFG base address
;  Registers changed: None except ESI
;-------------------------------------------------------------------------
GetMmcfgBase   PROC     NEAR    PUBLIC

      ; PCIe config base address actually written into the MMCFG_RULE CSR
      movd  esi, xmm3                                       ; xmm3 stores MMCFG_RULE
      and   esi, 0fffffff0h                                 ; make sure the lower bits are 0s
      ret

GetMmcfgBase   ENDP


STARTUP_SEG ENDS

END


