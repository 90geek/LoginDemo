#line 1 "c:\\1218_alibaba\\AmiCompatibilityPkg\\Library\\x64\\x64AsmLib\\ReadRtdsc.asm"
#line 1 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\AmiCompatibilityPkg\\Library\\AmiDxeLib\\DEBUG\\AutoGen.h"















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


#line 17 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\AmiCompatibilityPkg\\Library\\AmiDxeLib\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\PiDxe.h"


















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














































































































































#line 260 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiBaseType.h"






#line 267 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiBaseType.h"
































#line 300 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiBaseType.h"

#line 302 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiBaseType.h"
#line 20 "c:\\1218_alibaba\\MdePkg\\Include\\PiDxe.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"





















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
#line 23 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"

#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/DevicePath.h"





















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Guid/PcAnsi.h"












































  





extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;

#line 59 "c:\\1218_alibaba\\MdePkg\\Include\\Guid/PcAnsi.h"
#line 23 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/DevicePath.h"














#pragma pack(1)









typedef struct {
  UINT8 Type;       
                    
                    
                    
                    
                    
                    
  UINT8 SubType;    
                    
                    
                    
                    
  UINT8 Length[2];  
                    
                    
} EFI_DEVICE_PATH_PROTOCOL;




typedef EFI_DEVICE_PATH_PROTOCOL  EFI_DEVICE_PATH;














typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT8                           Function;
  
  
  
  UINT8                           Device;
} PCI_DEVICE_PATH;









typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT8                           FunctionNumber;
} PCCARD_DEVICE_PATH;









typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT32                          MemoryType;
  
  
  
  EFI_PHYSICAL_ADDRESS            StartingAddress;
  
  
  
  EFI_PHYSICAL_ADDRESS            EndingAddress;
} MEMMAP_DEVICE_PATH;











typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_GUID                        Guid;
  
  
  
} VENDOR_DEVICE_PATH;









typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT32                          ControllerNumber;
} CONTROLLER_DEVICE_PATH;










typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  
  
  UINT32                          HID;
  
  
  
  
  
  
  
  UINT32                          UID;
} ACPI_HID_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  
  
  UINT32                          HID;
  
  
  
  
  
  UINT32                          UID;
  
  
  
  
  
  
  UINT32                          CID;
  
  
  
  
  
} ACPI_EXTENDED_HID_DEVICE_PATH;


























typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  
  
  UINT32                          ADR;
  
  
  
} ACPI_ADR_DEVICE_PATH;





























typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT8                           PrimarySecondary;
  
  
  
  UINT8                           SlaveMaster;
  
  
  
  UINT16                          Lun;
} ATAPI_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT16                          Pun;
  
  
  
  UINT16                          Lun;
} SCSI_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT32                          Reserved;
  
  
  
  UINT64                          WWN;
  
  
  
  UINT64                          Lun;
} FIBRECHANNEL_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT32                          Reserved;
  
  
  
  UINT8                           WWN[8];
  
  
  
  UINT8                           Lun[8];
} FIBRECHANNELEX_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT32                          Reserved;
  
  
  
  UINT64                          Guid;
} F1394_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  
  
  
  UINT8                         ParentPortNumber;
  
  
  
  UINT8                         InterfaceNumber;
} USB_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  
  
  
  
  UINT16                        VendorId;
  
  
  
  
  UINT16                        ProductId;
  
  
  
  
  UINT8                         DeviceClass;
  
  
  
  
  UINT8                         DeviceSubClass;
  
  
  
  
  UINT8                         DeviceProtocol;
} USB_CLASS_DEVICE_PATH;









typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  
  
  
  UINT16                        InterfaceNumber;
  
  
  
  UINT16                        VendorId;
  
  
  
  UINT16                        ProductId;
  
  
  
  
  
  
  
} USB_WWID_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL      Header;
  
  
  
  UINT8                         Lun;
} DEVICE_LOGICAL_UNIT_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  
  UINT16                          HBAPortNumber;
  
  
  
  
  
  UINT16                          PortMultiplierPortNumber;
  
  
  
  UINT16                          Lun;
} SATA_DEVICE_PATH;










typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT32                          Tid;
} I2O_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_MAC_ADDRESS                 MacAddress;
  
  
  
  UINT8                           IfType;
} MAC_ADDR_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_IPv4_ADDRESS                LocalIpAddress;
  
  
  
  EFI_IPv4_ADDRESS                RemoteIpAddress;
  
  
  
  UINT16                          LocalPort;
  
  
  
  UINT16                          RemotePort;
  
  
  
  UINT16                          Protocol;
  
  
  
  
  BOOLEAN                         StaticIpAddress;
  
  
  
  EFI_IPv4_ADDRESS                GatewayIpAddress;
  
  
  
  EFI_IPv4_ADDRESS                SubnetMask;
} IPv4_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_IPv6_ADDRESS                LocalIpAddress;
  
  
  
  EFI_IPv6_ADDRESS                RemoteIpAddress;
  
  
  
  UINT16                          LocalPort;
  
  
  
  UINT16                          RemotePort;
  
  
  
  UINT16                          Protocol;
  
  
  
  
  
  
  
  UINT8                           IpAddressOrigin;
  
  
  
  UINT8                           PrefixLength;
  
  
  
  EFI_IPv6_ADDRESS                GatewayIpAddress;
} IPv6_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  
  
  
  
  
  
  UINT32                          ResourceFlags;
  
  
  
  UINT8                           PortGid[16];
  
  
  
  
  UINT64                          ServiceId;
  
  
  
  UINT64                          TargetPortId;
  
  
  
  UINT64                          DeviceId;
} INFINIBAND_DEVICE_PATH;











typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT32                          Reserved;
  
  
  
  
  UINT64                          BaudRate;
  
  
  
  
  UINT8                           DataBits;
  
  
  
  
  
  
  
  
  
  UINT8                           Parity;
  
  
  
  
  
  
  
  UINT8                           StopBits;
} UART_DEVICE_PATH;





typedef VENDOR_DEVICE_PATH        VENDOR_DEFINED_DEVICE_PATH;










typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_GUID                        Guid;
  
  
  
  
  
  
  UINT32                          FlowControlMap;
} UART_FLOW_CONTROL_DEVICE_PATH;








typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_GUID                        Guid;
  
  
  
  UINT32                          Reserved;
  
  
  
  UINT64                          SasAddress;
  
  
  
  UINT64                          Lun;
  
  
  
  UINT16                          DeviceTopology;
  
  
  
  UINT16                          RelativeTargetPort;
} SAS_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT8                           SasAddress[8];
  
  
  
  UINT8                           Lun[8];
  
  
  
  UINT16                          DeviceTopology;
  
  
  
  UINT16                          RelativeTargetPort;
} SASEX_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  UINT32                          NamespaceId;
  UINT64                          NamespaceUuid;
} NVME_NAMESPACE_DEVICE_PATH;





typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT16                          NetworkProtocol;
  
  
  
  UINT16                          LoginOption;
  
  
  
  UINT64                          Lun;
  
  
  
  
  UINT16                          TargetPortalGroupTag;
  
  
  
  
  
} ISCSI_DEVICE_PATH;














typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT16                          VlanId;
} VLAN_DEVICE_PATH;














typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  
  
  
  UINT32                          PartitionNumber;
  
  
  
  UINT64                          PartitionStart;
  
  
  
  UINT64                          PartitionSize;
  
  
  
  
  
  
  
  UINT8                           Signature[16];
  
  
  
  
  
  UINT8                           MBRType;
  
  
  
  
  
  
  UINT8                           SignatureType;
} HARDDRIVE_DEVICE_PATH;
















typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT32                          BootEntry;
  
  
  
  UINT64                          PartitionStart;
  
  
  
  UINT64                          PartitionSize;
} CDROM_DEVICE_PATH;










typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  CHAR16                          PathName[1];
} FILEPATH_DEVICE_PATH;













typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_GUID                        Protocol;
} MEDIA_PROTOCOL_DEVICE_PATH;









typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_GUID                        FvFileName;
} MEDIA_FW_VOL_FILEPATH_DEVICE_PATH;









typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  EFI_GUID                        FvName;
} MEDIA_FW_VOL_DEVICE_PATH;









typedef struct {
  EFI_DEVICE_PATH_PROTOCOL  Header;
  UINT32                    Reserved;
  UINT64                    StartingOffset;
  UINT64                    EndingOffset;
} MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH;














typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  
  
  
  UINT16                          DeviceType;
  
  
  
  UINT16                          StatusFlag;
  
  
  
  CHAR8                           String[1];
} BBS_BBS_DEVICE_PATH;

















typedef union {
  EFI_DEVICE_PATH_PROTOCOL                   DevPath;
  PCI_DEVICE_PATH                            Pci;
  PCCARD_DEVICE_PATH                         PcCard;
  MEMMAP_DEVICE_PATH                         MemMap;
  VENDOR_DEVICE_PATH                         Vendor;

  CONTROLLER_DEVICE_PATH                     Controller;
  ACPI_HID_DEVICE_PATH                       Acpi;
  ACPI_EXTENDED_HID_DEVICE_PATH              ExtendedAcpi;
  ACPI_ADR_DEVICE_PATH                       AcpiAdr;

  ATAPI_DEVICE_PATH                          Atapi;
  SCSI_DEVICE_PATH                           Scsi;
  ISCSI_DEVICE_PATH                          Iscsi;
  FIBRECHANNEL_DEVICE_PATH                   FibreChannel;
  FIBRECHANNELEX_DEVICE_PATH                 FibreChannelEx;

  F1394_DEVICE_PATH                          F1394;
  USB_DEVICE_PATH                            Usb;
  SATA_DEVICE_PATH                           Sata;
  USB_CLASS_DEVICE_PATH                      UsbClass;
  USB_WWID_DEVICE_PATH                       UsbWwid;
  DEVICE_LOGICAL_UNIT_DEVICE_PATH            LogicUnit;
  I2O_DEVICE_PATH                            I2O;
  MAC_ADDR_DEVICE_PATH                       MacAddr;
  IPv4_DEVICE_PATH                           Ipv4;
  IPv6_DEVICE_PATH                           Ipv6;
  VLAN_DEVICE_PATH                           Vlan;
  INFINIBAND_DEVICE_PATH                     InfiniBand;
  UART_DEVICE_PATH                           Uart;
  UART_FLOW_CONTROL_DEVICE_PATH              UartFlowControl;
  SAS_DEVICE_PATH                            Sas;
  SASEX_DEVICE_PATH                          SasEx;
  NVME_NAMESPACE_DEVICE_PATH                 NvmeNamespace;
  HARDDRIVE_DEVICE_PATH                      HardDrive;
  CDROM_DEVICE_PATH                          CD;

  FILEPATH_DEVICE_PATH                       FilePath;
  MEDIA_PROTOCOL_DEVICE_PATH                 MediaProtocol;

  MEDIA_FW_VOL_DEVICE_PATH                   FirmwareVolume;
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH          FirmwareFile;
  MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH    Offset;

  BBS_BBS_DEVICE_PATH                        Bbs;
} EFI_DEV_PATH;



typedef union {
  EFI_DEVICE_PATH_PROTOCOL                   *DevPath;
  PCI_DEVICE_PATH                            *Pci;
  PCCARD_DEVICE_PATH                         *PcCard;
  MEMMAP_DEVICE_PATH                         *MemMap;
  VENDOR_DEVICE_PATH                         *Vendor;

  CONTROLLER_DEVICE_PATH                     *Controller;
  ACPI_HID_DEVICE_PATH                       *Acpi;
  ACPI_EXTENDED_HID_DEVICE_PATH              *ExtendedAcpi;
  ACPI_ADR_DEVICE_PATH                       *AcpiAdr;

  ATAPI_DEVICE_PATH                          *Atapi;
  SCSI_DEVICE_PATH                           *Scsi;
  ISCSI_DEVICE_PATH                          *Iscsi;
  FIBRECHANNEL_DEVICE_PATH                   *FibreChannel;
  FIBRECHANNELEX_DEVICE_PATH                 *FibreChannelEx;

  F1394_DEVICE_PATH                          *F1394;
  USB_DEVICE_PATH                            *Usb;
  SATA_DEVICE_PATH                           *Sata;
  USB_CLASS_DEVICE_PATH                      *UsbClass;
  USB_WWID_DEVICE_PATH                       *UsbWwid;
  DEVICE_LOGICAL_UNIT_DEVICE_PATH            *LogicUnit;
  I2O_DEVICE_PATH                            *I2O;
  MAC_ADDR_DEVICE_PATH                       *MacAddr;
  IPv4_DEVICE_PATH                           *Ipv4;
  IPv6_DEVICE_PATH                           *Ipv6;
  VLAN_DEVICE_PATH                           *Vlan;
  INFINIBAND_DEVICE_PATH                     *InfiniBand;
  UART_DEVICE_PATH                           *Uart;
  UART_FLOW_CONTROL_DEVICE_PATH              *UartFlowControl;
  SAS_DEVICE_PATH                            *Sas;
  SASEX_DEVICE_PATH                          *SasEx;
  NVME_NAMESPACE_DEVICE_PATH                 *NvmeNamespace;
  HARDDRIVE_DEVICE_PATH                      *HardDrive;
  CDROM_DEVICE_PATH                          *CD;

  FILEPATH_DEVICE_PATH                       *FilePath;
  MEDIA_PROTOCOL_DEVICE_PATH                 *MediaProtocol;

  MEDIA_FW_VOL_DEVICE_PATH                   *FirmwareVolume;
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH          *FirmwareFile;
  MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH    *Offset;

  BBS_BBS_DEVICE_PATH                        *Bbs;
  UINT8                                      *Raw;
} EFI_DEV_PATH_PTR;

#pragma pack()
                                             




extern EFI_GUID gEfiDevicePathProtocolGuid;

#line 1170 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/DevicePath.h"

#line 25 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/SimpleTextIn.h"

























typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL  EFI_SIMPLE_TEXT_INPUT_PROTOCOL;









typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL  SIMPLE_INPUT_INTERFACE;




typedef struct {
  UINT16  ScanCode;
  CHAR16  UnicodeChar;
} EFI_INPUT_KEY;














































typedef
EFI_STATUS
(__cdecl *EFI_INPUT_RESET)(
   EFI_SIMPLE_TEXT_INPUT_PROTOCOL       *This,
   BOOLEAN                              ExtendedVerification
  );















typedef
EFI_STATUS
(__cdecl *EFI_INPUT_READ_KEY)(
   EFI_SIMPLE_TEXT_INPUT_PROTOCOL       *This,
   EFI_INPUT_KEY                       *Key
  );





struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
  EFI_INPUT_RESET     Reset;
  EFI_INPUT_READ_KEY  ReadKeyStroke;
  
  
  
  EFI_EVENT           WaitForKey;
};

extern EFI_GUID gEfiSimpleTextInProtocolGuid;

#line 135 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/SimpleTextIn.h"
#line 26 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/SimpleTextInEx.h"





















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/SimpleTextIn.h"






































































































































#line 23 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/SimpleTextInEx.h"





typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;


























typedef
EFI_STATUS
(__cdecl *EFI_INPUT_RESET_EX)(
   EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
   BOOLEAN                           ExtendedVerification
);







typedef UINT8 EFI_KEY_TOGGLE_STATE;

typedef struct _EFI_KEY_STATE {
  
  
  
  
  
  
  UINT32                KeyShiftState;
  
  
  
  
  
  
  EFI_KEY_TOGGLE_STATE  KeyToggleState;
} EFI_KEY_STATE;

typedef struct {
  
  
  
  EFI_INPUT_KEY   Key;
  
  
  
  EFI_KEY_STATE   KeyState;
} EFI_KEY_DATA;










































































































typedef
EFI_STATUS
(__cdecl *EFI_INPUT_READ_KEY_EX)(
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
   EFI_KEY_DATA                      *KeyData
);





















typedef
EFI_STATUS
(__cdecl *EFI_SET_STATE)(
   EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
   EFI_KEY_TOGGLE_STATE              *KeyToggleState
);




typedef
EFI_STATUS
(__cdecl *EFI_KEY_NOTIFY_FUNCTION)(
   EFI_KEY_DATA *KeyData
);


























typedef
EFI_STATUS
(__cdecl *EFI_REGISTER_KEYSTROKE_NOTIFY)(
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    EFI_KEY_DATA                      *KeyData,
    EFI_KEY_NOTIFY_FUNCTION           KeyNotificationFunction,
   void                              **NotifyHandle
);
















typedef
EFI_STATUS
(__cdecl *EFI_UNREGISTER_KEYSTROKE_NOTIFY)(
   EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
   void                               *NotificationHandle
);








struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL{
  EFI_INPUT_RESET_EX              Reset;
  EFI_INPUT_READ_KEY_EX           ReadKeyStrokeEx;
  
  
  
  EFI_EVENT                       WaitForKeyEx;
  EFI_SET_STATE                   SetState;
  EFI_REGISTER_KEYSTROKE_NOTIFY   RegisterKeyNotify;
  EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
};


extern EFI_GUID gEfiSimpleTextInputExProtocolGuid;

#line 325 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/SimpleTextInEx.h"

#line 27 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/SimpleTextOut.h"
































typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;




typedef EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   SIMPLE_TEXT_OUTPUT_INTERFACE;

























































































































typedef
EFI_STATUS
(__cdecl *EFI_TEXT_RESET)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
   BOOLEAN                                ExtendedVerification
  );



















typedef
EFI_STATUS
(__cdecl *EFI_TEXT_STRING)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
   CHAR16                                 *String
  );















typedef
EFI_STATUS
(__cdecl *EFI_TEXT_TEST_STRING)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
   CHAR16                                 *String
  );

















typedef
EFI_STATUS
(__cdecl *EFI_TEXT_QUERY_MODE)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
   UINTN                                  ModeNumber,
   UINTN                                 *Columns,
   UINTN                                 *Rows
  );












typedef
EFI_STATUS
(__cdecl *EFI_TEXT_SET_MODE)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
   UINTN                                  ModeNumber
  );















typedef
EFI_STATUS
(__cdecl *EFI_TEXT_SET_ATTRIBUTE)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
   UINTN                                  Attribute
  );












typedef
EFI_STATUS
(__cdecl *EFI_TEXT_CLEAR_SCREEN)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *This
  );


















typedef
EFI_STATUS
(__cdecl *EFI_TEXT_SET_CURSOR_POSITION)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
   UINTN                                  Column,
   UINTN                                  Row
  );















typedef
EFI_STATUS
(__cdecl *EFI_TEXT_ENABLE_CURSOR)(
   EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
   BOOLEAN                                Visible
  );





typedef struct {
  
  
  
  INT32   MaxMode;

  
  
  

  
  
  
  INT32   Mode;
  
  
  
  INT32   Attribute;
  
  
  
  INT32   CursorColumn;
  
  
  
  INT32   CursorRow;
  
  
  
  BOOLEAN CursorVisible;
} EFI_SIMPLE_TEXT_OUTPUT_MODE;







struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
  EFI_TEXT_RESET                Reset;

  EFI_TEXT_STRING               OutputString;
  EFI_TEXT_TEST_STRING          TestString;

  EFI_TEXT_QUERY_MODE           QueryMode;
  EFI_TEXT_SET_MODE             SetMode;
  EFI_TEXT_SET_ATTRIBUTE        SetAttribute;

  EFI_TEXT_CLEAR_SCREEN         ClearScreen;
  EFI_TEXT_SET_CURSOR_POSITION  SetCursorPosition;
  EFI_TEXT_ENABLE_CURSOR        EnableCursor;

  
  
  
  EFI_SIMPLE_TEXT_OUTPUT_MODE   *Mode;
};

extern EFI_GUID gEfiSimpleTextOutProtocolGuid;

#line 405 "c:\\1218_alibaba\\MdePkg\\Include\\Protocol/SimpleTextOut.h"
#line 28 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"




typedef enum {
  
  
  
  AllocateAnyPages,
  
  
  
  
  AllocateMaxAddress,
  
  
  
  AllocateAddress,
  
  
  
  MaxAllocateType
} EFI_ALLOCATE_TYPE;







































typedef struct {
  
  
  
  UINT32                Type;
  
  
  
  
  EFI_PHYSICAL_ADDRESS  PhysicalStart;
  
  
  
  
  EFI_VIRTUAL_ADDRESS   VirtualStart;
  
  
  
  UINT64                NumberOfPages;
  
  
  
  
  
  UINT64                Attribute;
} EFI_MEMORY_DESCRIPTOR;




















typedef
EFI_STATUS
(__cdecl *EFI_ALLOCATE_PAGES)(
       EFI_ALLOCATE_TYPE            Type,
       EFI_MEMORY_TYPE              MemoryType,
       UINTN                        Pages,
    EFI_PHYSICAL_ADDRESS         *Memory
  );













typedef
EFI_STATUS
(__cdecl *EFI_FREE_PAGES)(
    EFI_PHYSICAL_ADDRESS         Memory,
    UINTN                        Pages
  );


























typedef
EFI_STATUS
(__cdecl *EFI_GET_MEMORY_MAP)(
    UINTN                       *MemoryMapSize,
    EFI_MEMORY_DESCRIPTOR       *MemoryMap,
      UINTN                       *MapKey,
      UINTN                       *DescriptorSize,
      UINT32                      *DescriptorVersion
  );














typedef
EFI_STATUS
(__cdecl *EFI_ALLOCATE_POOL)(
    EFI_MEMORY_TYPE              PoolType,
    UINTN                        Size,
   void                         **Buffer
  );










typedef
EFI_STATUS
(__cdecl *EFI_FREE_POOL)(
    void                         *Buffer
  );




















typedef
EFI_STATUS
(__cdecl *EFI_SET_VIRTUAL_ADDRESS_MAP)(
    UINTN                        MemoryMapSize,
    UINTN                        DescriptorSize,
    UINT32                       DescriptorVersion,
    EFI_MEMORY_DESCRIPTOR        *VirtualMap
  );


























typedef
EFI_STATUS
(__cdecl *EFI_CONNECT_CONTROLLER)(
    EFI_HANDLE                    ControllerHandle,
    EFI_HANDLE                    *DriverImageHandle,   
    EFI_DEVICE_PATH_PROTOCOL      *RemainingDevicePath, 
    BOOLEAN                       Recursive
  );

























typedef
EFI_STATUS
(__cdecl *EFI_DISCONNECT_CONTROLLER)(
    EFI_HANDLE                     ControllerHandle,
    EFI_HANDLE                     DriverImageHandle, 
    EFI_HANDLE                     ChildHandle        
  );























typedef
EFI_STATUS
(__cdecl *EFI_CONVERT_POINTER)(
       UINTN                      DebugDisposition,
    void                       **Address
  );































typedef
void
(__cdecl *EFI_EVENT_NOTIFY)(
    EFI_EVENT                Event,
    void                     *Context
  );

















typedef
EFI_STATUS
(__cdecl *EFI_CREATE_EVENT)(
    UINT32                       Type,
    EFI_TPL                      NotifyTpl,
    EFI_EVENT_NOTIFY             NotifyFunction,
    void                         *NotifyContext,
   EFI_EVENT                    *Event
  );




















typedef
EFI_STATUS
(__cdecl *EFI_CREATE_EVENT_EX)(
         UINT32                 Type,
         EFI_TPL                NotifyTpl,
         EFI_EVENT_NOTIFY       NotifyFunction ,
   const void                   *NotifyContext ,
   const EFI_GUID               *EventGroup    ,
        EFI_EVENT              *Event
  );




typedef enum {
  
  
  
  TimerCancel,
  
  
  
  TimerPeriodic,
  
  
  
  TimerRelative
} EFI_TIMER_DELAY;

















typedef
EFI_STATUS
(__cdecl *EFI_SET_TIMER)(
    EFI_EVENT                Event,
    EFI_TIMER_DELAY          Type,
    UINT64                   TriggerTime
  );









typedef
EFI_STATUS
(__cdecl *EFI_SIGNAL_EVENT)(
    EFI_EVENT                Event
  );















typedef
EFI_STATUS
(__cdecl *EFI_WAIT_FOR_EVENT)(
    UINTN                    NumberOfEvents,
    EFI_EVENT                *Event,
   UINTN                    *Index
  );









typedef
EFI_STATUS
(__cdecl *EFI_CLOSE_EVENT)(
   EFI_EVENT                Event
  );











typedef
EFI_STATUS
(__cdecl *EFI_CHECK_EVENT)(
   EFI_EVENT                Event
  );



















typedef
EFI_TPL
(__cdecl *EFI_RAISE_TPL)(
   EFI_TPL      NewTpl
  );







typedef
void
(__cdecl *EFI_RESTORE_TPL)(
   EFI_TPL      OldTpl
  );
























typedef
EFI_STATUS
(__cdecl *EFI_GET_VARIABLE)(
       CHAR16                      *VariableName,
       EFI_GUID                    *VendorGuid,
      UINT32                      *Attributes,    
    UINTN                       *DataSize,
      void                        *Data
  );





















typedef
EFI_STATUS
(__cdecl *EFI_GET_NEXT_VARIABLE_NAME)(
    UINTN                    *VariableNameSize,
    CHAR16                   *VariableName,
    EFI_GUID                 *VendorGuid
  );





































typedef
EFI_STATUS
(__cdecl *EFI_SET_VARIABLE)(
    CHAR16                       *VariableName,
    EFI_GUID                     *VendorGuid,
    UINT32                       Attributes,
    UINTN                        DataSize,
    void                         *Data
  );






typedef struct {
  
  
  
  
  
  
  UINT32    Resolution;
  
  
  
  
  
  
  UINT32    Accuracy;
  
  
  
  
  
  
  
  BOOLEAN   SetsToZero;
} EFI_TIME_CAPABILITIES;














typedef
EFI_STATUS
(__cdecl *EFI_GET_TIME)(
    EFI_TIME                    *Time,
    EFI_TIME_CAPABILITIES       *Capabilities 
  );











typedef
EFI_STATUS
(__cdecl *EFI_SET_TIME)(
    EFI_TIME                     *Time
  );
















typedef
EFI_STATUS
(__cdecl *EFI_GET_WAKEUP_TIME)(
   BOOLEAN                     *Enabled,
   BOOLEAN                     *Pending,
   EFI_TIME                    *Time
  );















typedef
EFI_STATUS
(__cdecl *EFI_SET_WAKEUP_TIME)(
    BOOLEAN                      Enable,
    EFI_TIME                     *Time   
  );































typedef
EFI_STATUS
(__cdecl *EFI_IMAGE_LOAD)(
    BOOLEAN                      BootPolicy,
    EFI_HANDLE                   ParentImageHandle,
    EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
    void                         *SourceBuffer ,
    UINTN                        SourceSize,
   EFI_HANDLE                   *ImageHandle
  );















typedef
EFI_STATUS
(__cdecl *EFI_IMAGE_START)(
    EFI_HANDLE                  ImageHandle,
   UINTN                       *ExitDataSize,
   CHAR16                      **ExitData    
  );





















typedef
EFI_STATUS
(__cdecl *EFI_EXIT)(
    EFI_HANDLE                   ImageHandle,
    EFI_STATUS                   ExitStatus,
    UINTN                        ExitDataSize,
    CHAR16                       *ExitData     
  );










typedef
EFI_STATUS
(__cdecl *EFI_IMAGE_UNLOAD)(
    EFI_HANDLE                   ImageHandle
  );











typedef
EFI_STATUS
(__cdecl *EFI_EXIT_BOOT_SERVICES)(
    EFI_HANDLE                   ImageHandle,
    UINTN                        MapKey
  );










typedef
EFI_STATUS
(__cdecl *EFI_STALL)(
    UINTN                    Microseconds
  );

















typedef
EFI_STATUS
(__cdecl *EFI_SET_WATCHDOG_TIMER)(
   UINTN                    Timeout,
   UINT64                   WatchdogCode,
   UINTN                    DataSize,
   CHAR16                   *WatchdogData 
  );




typedef enum {
  
  
  
  
  
  
  EfiResetCold,
  
  
  
  
  
  EfiResetWarm,
  
  
  
  
  
  EfiResetShutdown,
  
  
  
  
  
  
  
  EfiResetPlatformSpecific
} EFI_RESET_TYPE;












typedef
void
(__cdecl *EFI_RESET_SYSTEM)(
   EFI_RESET_TYPE           ResetType,
   EFI_STATUS               ResetStatus,
   UINTN                    DataSize,
   void                     *ResetData 
  );











typedef
EFI_STATUS
(__cdecl *EFI_GET_NEXT_MONOTONIC_COUNT)(
   UINT64                  *Count
  );











typedef
EFI_STATUS
(__cdecl *EFI_GET_NEXT_HIGH_MONO_COUNT)(
   UINT32                  *HighCount
  );
















typedef
EFI_STATUS
(__cdecl *EFI_CALCULATE_CRC32)(
    void                              *Data,
    UINTN                             DataSize,
   UINT32                            *Crc32
  );









typedef
void
(__cdecl *EFI_COPY_MEM)(
   void     *Destination,
   void     *Source,
   UINTN    Length
  );









typedef
void
(__cdecl *EFI_SET_MEM)(
   void     *Buffer,
   UINTN    Size,
   UINT8    Value
  );




typedef enum {
  
  
  
  EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;





















typedef
EFI_STATUS
(__cdecl *EFI_INSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE               *Handle,
       EFI_GUID                 *Protocol,
       EFI_INTERFACE_TYPE       InterfaceType,
       void                     *Interface
  );

















typedef
EFI_STATUS
(__cdecl *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    EFI_HANDLE           *Handle,
  ...
  );



















typedef
EFI_STATUS
(__cdecl *EFI_REINSTALL_PROTOCOL_INTERFACE)(
   EFI_HANDLE               Handle,
   EFI_GUID                 *Protocol,
   void                     *OldInterface,
   void                     *NewInterface
  );


















typedef
EFI_STATUS
(__cdecl *EFI_UNINSTALL_PROTOCOL_INTERFACE)(
   EFI_HANDLE               Handle,
   EFI_GUID                 *Protocol,
   void                     *Interface
  );












typedef
EFI_STATUS
(__cdecl *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
   EFI_HANDLE           Handle,
  ...
  );
















typedef
EFI_STATUS
(__cdecl *EFI_HANDLE_PROTOCOL)(
    EFI_HANDLE               Handle,
    EFI_GUID                 *Protocol,
   void                     **Interface
  );



































typedef
EFI_STATUS
(__cdecl *EFI_OPEN_PROTOCOL)(
    EFI_HANDLE                Handle,
    EFI_GUID                  *Protocol,
   void                      **Interface, 
    EFI_HANDLE                AgentHandle,
    EFI_HANDLE                ControllerHandle,
    UINT32                    Attributes
  );























typedef
EFI_STATUS
(__cdecl *EFI_CLOSE_PROTOCOL)(
   EFI_HANDLE               Handle,
   EFI_GUID                 *Protocol,
   EFI_HANDLE               AgentHandle,
   EFI_HANDLE               ControllerHandle
  );




typedef struct {
  EFI_HANDLE  AgentHandle;
  EFI_HANDLE  ControllerHandle;
  UINT32      Attributes;
  UINT32      OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;
















typedef
EFI_STATUS
(__cdecl *EFI_OPEN_PROTOCOL_INFORMATION)(
    EFI_HANDLE                          Handle,
    EFI_GUID                            *Protocol,
   EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
   UINTN                               *EntryCount
  );






















typedef
EFI_STATUS
(__cdecl *EFI_PROTOCOLS_PER_HANDLE)(
    EFI_HANDLE      Handle,
   EFI_GUID        ***ProtocolBuffer,
   UINTN           *ProtocolBufferCount
  );
















typedef
EFI_STATUS
(__cdecl *EFI_REGISTER_PROTOCOL_NOTIFY)(
    EFI_GUID                 *Protocol,
    EFI_EVENT                Event,
   void                     **Registration
  );




typedef enum {
  
  
  
  AllHandles,
  
  
  
  ByRegisterNotify,
  
  
  
  
  ByProtocol
} EFI_LOCATE_SEARCH_TYPE;























typedef
EFI_STATUS
(__cdecl *EFI_LOCATE_HANDLE)(
       EFI_LOCATE_SEARCH_TYPE   SearchType,
       EFI_GUID                 *Protocol,    
       void                     *SearchKey,   
    UINTN                    *BufferSize,
      EFI_HANDLE               *Buffer
  );

















typedef
EFI_STATUS
(__cdecl *EFI_LOCATE_DEVICE_PATH)(
       EFI_GUID                         *Protocol,
    EFI_DEVICE_PATH_PROTOCOL         **DevicePath,
      EFI_HANDLE                       *Device
  );














typedef
EFI_STATUS
(__cdecl *EFI_INSTALL_CONFIGURATION_TABLE)(
   EFI_GUID                 *Guid,
   void                     *Table
  );




















typedef
EFI_STATUS
(__cdecl *EFI_LOCATE_HANDLE_BUFFER)(
       EFI_LOCATE_SEARCH_TYPE       SearchType,
       EFI_GUID                     *Protocol,      
       void                         *SearchKey,     
    UINTN                        *NoHandles,
      EFI_HANDLE                   **Buffer
  );

















typedef
EFI_STATUS
(__cdecl *EFI_LOCATE_PROTOCOL)(
    EFI_GUID  *Protocol,
    void      *Registration, 
   void      **Interface
  );




typedef struct {
  
  
  
  UINT64                  Length;
  union {
    
    
    
    
    EFI_PHYSICAL_ADDRESS  DataBlock;
    
    
    
    
    
    
    EFI_PHYSICAL_ADDRESS  ContinuationPointer;
  } Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;




typedef struct {
  
  
  
  EFI_GUID          CapsuleGuid;
  
  
  
  
  
  UINT32            HeaderSize;
  
  
  
  
  
  UINT32            Flags;
  
  
  
  UINT32            CapsuleImageSize;
} EFI_CAPSULE_HEADER;






typedef struct {
  
  
  
  UINT32   CapsuleArrayNumber;
  
  
  
  void*    CapsulePtr[1];
} EFI_CAPSULE_TABLE;



































typedef
EFI_STATUS
(__cdecl *EFI_UPDATE_CAPSULE)(
   EFI_CAPSULE_HEADER     **CapsuleHeaderArray,
   UINTN                  CapsuleCount,
   EFI_PHYSICAL_ADDRESS   ScatterGatherList   
  );
























typedef
EFI_STATUS
(__cdecl *EFI_QUERY_CAPSULE_CAPABILITIES)(
    EFI_CAPSULE_HEADER     **CapsuleHeaderArray,
    UINTN                  CapsuleCount,
   UINT64                 *MaximumCapsuleSize,
   EFI_RESET_TYPE         *ResetType
  );























typedef
EFI_STATUS
(__cdecl *EFI_QUERY_VARIABLE_INFO)(
    UINT32            Attributes,
   UINT64            *MaximumVariableStorageSize,
   UINT64            *RemainingVariableStorageSize,
   UINT64            *MaximumVariableSize
  );





























#line 1781 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"








typedef struct {
  
  
  
  EFI_TABLE_HEADER                Hdr;

  
  
  
  EFI_GET_TIME                    GetTime;
  EFI_SET_TIME                    SetTime;
  EFI_GET_WAKEUP_TIME             GetWakeupTime;
  EFI_SET_WAKEUP_TIME             SetWakeupTime;

  
  
  
  EFI_SET_VIRTUAL_ADDRESS_MAP     SetVirtualAddressMap;
  EFI_CONVERT_POINTER             ConvertPointer;

  
  
  
  EFI_GET_VARIABLE                GetVariable;
  EFI_GET_NEXT_VARIABLE_NAME      GetNextVariableName;
  EFI_SET_VARIABLE                SetVariable;

  
  
  
  EFI_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
  EFI_RESET_SYSTEM                ResetSystem;

  
  
  
  EFI_UPDATE_CAPSULE              UpdateCapsule;
  EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;

  
  
  
  EFI_QUERY_VARIABLE_INFO         QueryVariableInfo;
} EFI_RUNTIME_SERVICES;








typedef struct {
  
  
  
  EFI_TABLE_HEADER                Hdr;

  
  
  
  EFI_RAISE_TPL                   RaiseTPL;
  EFI_RESTORE_TPL                 RestoreTPL;

  
  
  
  EFI_ALLOCATE_PAGES              AllocatePages;
  EFI_FREE_PAGES                  FreePages;
  EFI_GET_MEMORY_MAP              GetMemoryMap;
  EFI_ALLOCATE_POOL               AllocatePool;
  EFI_FREE_POOL                   FreePool;

  
  
  
  EFI_CREATE_EVENT                  CreateEvent;
  EFI_SET_TIMER                     SetTimer;
  EFI_WAIT_FOR_EVENT                WaitForEvent;
  EFI_SIGNAL_EVENT                  SignalEvent;
  EFI_CLOSE_EVENT                   CloseEvent;
  EFI_CHECK_EVENT                   CheckEvent;

  
  
  
  EFI_INSTALL_PROTOCOL_INTERFACE    InstallProtocolInterface;
  EFI_REINSTALL_PROTOCOL_INTERFACE  ReinstallProtocolInterface;
  EFI_UNINSTALL_PROTOCOL_INTERFACE  UninstallProtocolInterface;
  EFI_HANDLE_PROTOCOL               HandleProtocol;
  void                              *Reserved;
  EFI_REGISTER_PROTOCOL_NOTIFY      RegisterProtocolNotify;
  EFI_LOCATE_HANDLE                 LocateHandle;
  EFI_LOCATE_DEVICE_PATH            LocateDevicePath;
  EFI_INSTALL_CONFIGURATION_TABLE   InstallConfigurationTable;

  
  
  
  EFI_IMAGE_LOAD                    LoadImage;
  EFI_IMAGE_START                   StartImage;
  EFI_EXIT                          Exit;
  EFI_IMAGE_UNLOAD                  UnloadImage;
  EFI_EXIT_BOOT_SERVICES            ExitBootServices;

  
  
  
  EFI_GET_NEXT_MONOTONIC_COUNT      GetNextMonotonicCount;
  EFI_STALL                         Stall;
  EFI_SET_WATCHDOG_TIMER            SetWatchdogTimer;

  
  
  
  EFI_CONNECT_CONTROLLER            ConnectController;
  EFI_DISCONNECT_CONTROLLER         DisconnectController;

  
  
  
  EFI_OPEN_PROTOCOL                 OpenProtocol;
  EFI_CLOSE_PROTOCOL                CloseProtocol;
  EFI_OPEN_PROTOCOL_INFORMATION     OpenProtocolInformation;

  
  
  
  EFI_PROTOCOLS_PER_HANDLE          ProtocolsPerHandle;
  EFI_LOCATE_HANDLE_BUFFER          LocateHandleBuffer;
  EFI_LOCATE_PROTOCOL               LocateProtocol;
  EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES    InstallMultipleProtocolInterfaces;
  EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  UninstallMultipleProtocolInterfaces;

  
  
  
  EFI_CALCULATE_CRC32               CalculateCrc32;

  
  
  
  EFI_COPY_MEM                      CopyMem;
  EFI_SET_MEM                       SetMem;
  EFI_CREATE_EVENT_EX               CreateEventEx;
} EFI_BOOT_SERVICES;





typedef struct {
  
  
  
  EFI_GUID                          VendorGuid;
  
  
  
  void                              *VendorTable;
} EFI_CONFIGURATION_TABLE;




typedef struct {
  
  
  
  EFI_TABLE_HEADER                  Hdr;
  
  
  
  
  CHAR16                            *FirmwareVendor;
  
  
  
  
  UINT32                            FirmwareRevision;
  
  
  
  
  EFI_HANDLE                        ConsoleInHandle;
  
  
  
  
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL    *ConIn;
  
  
  
  EFI_HANDLE                        ConsoleOutHandle;
  
  
  
  
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *ConOut;
  
  
  
  
  EFI_HANDLE                        StandardErrorHandle;
  
  
  
  
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *StdErr;
  
  
  
  EFI_RUNTIME_SERVICES              *RuntimeServices;
  
  
  
  EFI_BOOT_SERVICES                 *BootServices;
  
  
  
  UINTN                             NumberOfTableEntries;
  
  
  
  
  EFI_CONFIGURATION_TABLE           *ConfigurationTable;
} EFI_SYSTEM_TABLE;












typedef
EFI_STATUS
(__cdecl *EFI_IMAGE_ENTRY_POINT)(
    EFI_HANDLE                   ImageHandle,
    EFI_SYSTEM_TABLE             *SystemTable
  );




















typedef union {
  struct {
    
    
    
    UINT32  Revision        : 8;
    
    
    
    UINT32  ShiftPressed    : 1;
    
    
    
    UINT32  ControlPressed  : 1;
    
    
    
    UINT32  AltPressed      : 1;
    
    
    
    UINT32  LogoPressed     : 1;
    
    
    
    UINT32  MenuPressed     : 1;
    
    
    
    UINT32  SysReqPressed    : 1;
    UINT32  Reserved        : 16;
    
    
    
    
    
    UINT32  InputKeyCount   : 2;
  } Options;
  UINT32  PackedValue;
} EFI_BOOT_KEY_DATA;




#pragma pack(1)
typedef struct {
  
  
  
  EFI_BOOT_KEY_DATA  KeyData;
  
  
  
  
  
  UINT32             BootOptionCrc;
  
  
  
  
  UINT16             BootOption;
  
  
  
  
  
  
} EFI_KEY_OPTION;
#pragma pack()












#line 2136 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"

#line 2138 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"
  







#line 2147 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"

#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiPxe.h"























#pragma pack(1)















































typedef void           PXE_VOID;
typedef UINT8          PXE_UINT8;
typedef UINT16         PXE_UINT16;
typedef UINT32         PXE_UINT32;
typedef UINTN          PXE_UINTN;




typedef UINT64      PXE_UINT64;

typedef PXE_UINT8 PXE_BOOL;



typedef PXE_UINT16      PXE_OPCODE;
































































































typedef PXE_UINT16  PXE_OPFLAGS;































































































































































































































typedef PXE_UINT16  PXE_STATFLAGS;
































































































































































































typedef PXE_UINT16  PXE_STATCODE;





























typedef PXE_UINT16  PXE_IFNUM;












typedef PXE_UINT16  PXE_CONTROL;




















typedef PXE_UINT8   PXE_FRAME_TYPE;










typedef PXE_UINT32  PXE_IPV4;

typedef PXE_UINT32  PXE_IPV6[4];


typedef PXE_UINT8   PXE_MAC_ADDR[32];

typedef PXE_UINT8   PXE_IFTYPE;
typedef UINT16      PXE_MEDIA_PROTOCOL;
































typedef struct s_pxe_hw_undi {
  PXE_UINT32  Signature;      
  PXE_UINT8   Len;            
  PXE_UINT8   Fudge;          
  PXE_UINT8   Rev;            
  PXE_UINT8   IFcnt;          
  PXE_UINT8   MajorVer;       
  PXE_UINT8   MinorVer;       
  PXE_UINT8   IFcntExt;       
  PXE_UINT8   reserved;       
  PXE_UINT32  Implementation; 
  
  
  
  
  
} PXE_HW_UNDI;
















































































typedef struct s_pxe_sw_undi {
  PXE_UINT32  Signature;      
  PXE_UINT8   Len;            
  PXE_UINT8   Fudge;          
  PXE_UINT8   Rev;            
  PXE_UINT8   IFcnt;          
  PXE_UINT8   MajorVer;       
  PXE_UINT8   MinorVer;       
  PXE_UINT8   IFcntExt;       
  PXE_UINT8   reserved1;      
  PXE_UINT32  Implementation; 
  PXE_UINT64  EntryPoint;     
  PXE_UINT8   reserved2[3];   
  PXE_UINT8   BusCnt;         
  PXE_UINT32  BusType[1];     
} PXE_SW_UNDI;

typedef union u_pxe_undi {
  PXE_HW_UNDI hw;
  PXE_SW_UNDI sw;
} PXE_UNDI;













































typedef struct s_pxe_cdb {
  PXE_OPCODE    OpCode;
  PXE_OPFLAGS   OpFlags;
  PXE_UINT16    CPBsize;
  PXE_UINT16    DBsize;
  PXE_UINT64    CPBaddr;
  PXE_UINT64    DBaddr;
  PXE_STATCODE  StatCode;
  PXE_STATFLAGS StatFlags;
  PXE_UINT16    IFnum;
  PXE_CONTROL   Control;
} PXE_CDB;

typedef union u_pxe_ip_addr {
  PXE_IPV6  IPv6;
  PXE_IPV4  IPv4;
} PXE_IP_ADDR;

typedef union pxe_device {
  
  
  
  
  
  
  struct {
    
    
    
    
    PXE_UINT32  BusType;

    
    
    
    PXE_UINT16  Bus;
    PXE_UINT8   Device;
    PXE_UINT8   Function;
  }
  PCI, PCC;

} PXE_DEVICE;









typedef struct s_pxe_cpb_start_30 {
  
  
  
  
  
  
  
  
  
  
  UINT64  Delay;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  UINT64  Block;

  
  
  
  
  
  
  
  
  
  
  
  
  UINT64  Virt2Phys;
  
  
  
  
  
  
  
  
  
  
  UINT64  Mem_IO;
} PXE_CPB_START_30;

typedef struct s_pxe_cpb_start_31 {
  
  
  
  
  
  
  
  
  
  
  UINT64  Delay;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  UINT64  Block;

  
  
  
  
  
  
  
  
  
  
  
  
  UINT64  Virt2Phys;
  
  
  
  
  
  
  
  
  
  
  UINT64  Mem_IO;
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  UINT64  Map_Mem;

  
  
  
  
  
  
  
  
  
  UINT64  UnMap_Mem;

  
  
  
  
  
  
  
  
  
  
  UINT64  Sync_Mem;

  
  
  
  
  
  
  UINT64  Unique_ID;
} PXE_CPB_START_31;












typedef struct s_pxe_db_get_init_info {
  
  
  
  
  
  
  
  
  PXE_UINT32  MemoryRequired;

  
  
  
  PXE_UINT32  FrameDataLen;

  
  
  
  
  
  PXE_UINT32  LinkSpeeds[4];

  
  
  
  PXE_UINT32  NvCount;

  
  
  
  PXE_UINT16  NvWidth;

  
  
  
  
  
  PXE_UINT16  MediaHeaderLen;

  
  
  
  PXE_UINT16  HWaddrLen;

  
  
  
  
  PXE_UINT16  MCastFilterCnt;

  
  
  
  
  
  
  
  PXE_UINT16  TxBufCnt;
  PXE_UINT16  TxBufSize;
  PXE_UINT16  RxBufCnt;
  PXE_UINT16  RxBufSize;

  
  
  
  
  
  PXE_UINT8   IFtype;

  
  
  
  PXE_UINT8   SupportedDuplexModes;

  
  
  
  PXE_UINT8   SupportedLoopBackModes;
} PXE_DB_GET_INIT_INFO;












typedef struct s_pxe_pci_config_info {
  
  
  
  
  UINT32  BusType;

  
  
  
  
  UINT16  Bus;
  UINT8   Device;
  UINT8   Function;

  
  
  
  
  union {
    UINT8   Byte[256];
    UINT16  Word[128];
    UINT32  Dword[64];
  } Config;
} PXE_PCI_CONFIG_INFO;

typedef struct s_pxe_pcc_config_info {
  
  
  
  
  PXE_UINT32  BusType;

  
  
  
  
  PXE_UINT16  Bus;
  PXE_UINT8   Device;
  PXE_UINT8   Function;

  
  
  
  
  union {
    PXE_UINT8   Byte[256];
    PXE_UINT16  Word[128];
    PXE_UINT32  Dword[64];
  } Config;
} PXE_PCC_CONFIG_INFO;

typedef union u_pxe_db_get_config_info {
  PXE_PCI_CONFIG_INFO   pci;
  PXE_PCC_CONFIG_INFO   pcc;
} PXE_DB_GET_CONFIG_INFO;

typedef struct s_pxe_cpb_initialize {
  
  
  
  
  
  PXE_UINT64  MemoryAddr;

  
  
  
  
  PXE_UINT32  MemoryLength;

  
  
  
  
  
  PXE_UINT32  LinkSpeed;

  
  
  
  
  
  
  
  
  
  
  PXE_UINT16  TxBufCnt;
  PXE_UINT16  TxBufSize;
  PXE_UINT16  RxBufCnt;
  PXE_UINT16  RxBufSize;

  
  
  
  
  PXE_UINT8   DuplexMode;

  PXE_UINT8   LoopBackMode;
} PXE_CPB_INITIALIZE;











typedef struct s_pxe_db_initialize {
  
  
  
  
  
  
  
  
  PXE_UINT32  MemoryUsed;

  
  
  
  
  PXE_UINT16  TxBufCnt;
  PXE_UINT16  TxBufSize;
  PXE_UINT16  RxBufCnt;
  PXE_UINT16  RxBufSize;
} PXE_DB_INITIALIZE;

typedef struct s_pxe_cpb_receive_filters {
  
  
  
  
  PXE_MAC_ADDR  MCastList[8];
} PXE_CPB_RECEIVE_FILTERS;

typedef struct s_pxe_db_receive_filters {
  
  
  
  PXE_MAC_ADDR  MCastList[8];
} PXE_DB_RECEIVE_FILTERS;

typedef struct s_pxe_cpb_station_address {
  
  
  
  
  PXE_MAC_ADDR  StationAddr;
} PXE_CPB_STATION_ADDRESS;

typedef struct s_pxe_dpb_station_address {
  
  
  
  PXE_MAC_ADDR  StationAddr;

  
  
  
  PXE_MAC_ADDR  BroadcastAddr;

  
  
  
  PXE_MAC_ADDR  PermanentAddr;
} PXE_DB_STATION_ADDRESS;

typedef struct s_pxe_db_statistics {
  
  
  
  
  
  
  
  
  
  PXE_UINT64  Supported;

  
  
  
  PXE_UINT64  Data[64];
} PXE_DB_STATISTICS;















































































typedef struct s_pxe_cpb_mcast_ip_to_mac {
  
  
  
  PXE_IP_ADDR IP;
} PXE_CPB_MCAST_IP_TO_MAC;

typedef struct s_pxe_db_mcast_ip_to_mac {
  
  
  
  PXE_MAC_ADDR  MAC;
} PXE_DB_MCAST_IP_TO_MAC;

typedef struct s_pxe_cpb_nvdata_sparse {
  
  
  
  struct {
    
    
    
    PXE_UINT32  Addr;

    
    
    
    union {
      PXE_UINT8   Byte;
      PXE_UINT16  Word;
      PXE_UINT32  Dword;
    } Data;
  } Item[128];
} PXE_CPB_NVDATA_SPARSE;





typedef union u_pxe_cpb_nvdata_bulk {
  
  
  
  PXE_UINT8   Byte[128 << 2];

  
  
  
  PXE_UINT16  Word[128 << 1];

  
  
  
  PXE_UINT32  Dword[128];
} PXE_CPB_NVDATA_BULK;

typedef struct s_pxe_db_nvdata {
  
  
  
  union {
    
    
    
    PXE_UINT8   Byte[128 << 2];

    
    
    
    PXE_UINT16  Word[128 << 1];

    
    
    
    PXE_UINT32  Dword[128];
  } Data;
} PXE_DB_NVDATA;

typedef struct s_pxe_db_get_status {
  
  
  
  
  PXE_UINT32  RxFrameLen;

  
  
  
  PXE_UINT32  reserved;

  
  
  
  PXE_UINT64  TxBuffer[32];
} PXE_DB_GET_STATUS;

typedef struct s_pxe_cpb_fill_header {
  
  
  
  
  PXE_MAC_ADDR  SrcAddr;
  PXE_MAC_ADDR  DestAddr;

  
  
  
  
  PXE_UINT64        MediaHeader;

  
  
  
  PXE_UINT32        PacketLen;

  
  
  
  
  
  PXE_UINT16        Protocol;

  
  
  
  PXE_UINT16        MediaHeaderLen;
} PXE_CPB_FILL_HEADER;





typedef struct s_pxe_cpb_fill_header_fragmented {
  
  
  
  
  PXE_MAC_ADDR        SrcAddr;
  PXE_MAC_ADDR        DestAddr;

  
  
  
  PXE_UINT32          PacketLen;

  
  
  
  
  
  PXE_MEDIA_PROTOCOL  Protocol;

  
  
  
  PXE_UINT16          MediaHeaderLen;

  
  
  
  PXE_UINT16          FragCnt;

  
  
  
  PXE_UINT16          reserved;

  
  
  
  
  struct {
    
    
    
    PXE_UINT64  FragAddr;

    
    
    
    PXE_UINT32  FragLen;

    
    
    
    PXE_UINT32  reserved;
  } FragDesc[16];
}
PXE_CPB_FILL_HEADER_FRAGMENTED;

typedef struct s_pxe_cpb_transmit {
  
  
  
  
  PXE_UINT64  FrameAddr;

  
  
  
  
  PXE_UINT32  DataLen;

  
  
  
  PXE_UINT16  MediaheaderLen;

  
  
  
  PXE_UINT16  reserved;
} PXE_CPB_TRANSMIT;

typedef struct s_pxe_cpb_transmit_fragments {
  
  
  
  PXE_UINT32  FrameLen;

  
  
  
  PXE_UINT16  MediaheaderLen;

  
  
  
  PXE_UINT16  FragCnt;

  
  
  
  
  struct {
    
    
    
    PXE_UINT64  FragAddr;

    
    
    
    PXE_UINT32  FragLen;

    
    
    
    PXE_UINT32  reserved;
  } FragDesc[16];
}
PXE_CPB_TRANSMIT_FRAGMENTS;

typedef struct s_pxe_cpb_receive {
  
  
  
  
  PXE_UINT64  BufferAddr;

  
  
  
  
  
  PXE_UINT32  BufferLen;

  
  
  
  PXE_UINT32  reserved;
} PXE_CPB_RECEIVE;

typedef struct s_pxe_db_receive {
  
  
  
  PXE_MAC_ADDR        SrcAddr;
  PXE_MAC_ADDR        DestAddr;

  
  
  
  
  
  PXE_UINT32          FrameLen;

  
  
  
  PXE_MEDIA_PROTOCOL  Protocol;

  
  
  
  PXE_UINT16          MediaHeaderLen;

  
  
  
  PXE_FRAME_TYPE      Type;

  
  
  
  PXE_UINT8           reserved[7];

} PXE_DB_RECEIVE;

#pragma pack()

#line 1773 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiPxe.h"

#line 2149 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiGpt.h"



























#pragma pack(1)




typedef struct {
  
  
  
  
  EFI_TABLE_HEADER  Header;
  
  
  
  EFI_LBA           MyLBA;
  
  
  
  EFI_LBA           AlternateLBA;
  
  
  
  
  EFI_LBA           FirstUsableLBA;
  
  
  
  
  EFI_LBA           LastUsableLBA;
  
  
  
  EFI_GUID          DiskGUID;
  
  
  
  EFI_LBA           PartitionEntryLBA;
  
  
  
  UINT32            NumberOfPartitionEntries;
  
  
  
  
  
  
  UINT32            SizeOfPartitionEntry;
  
  
  
  
  
  
  UINT32            PartitionEntryArrayCRC32;
} EFI_PARTITION_TABLE_HEADER;




typedef struct {
  
  
  
  
  EFI_GUID  PartitionTypeGUID;
  
  
  
  
  
  EFI_GUID  UniquePartitionGUID;
  
  
  
  EFI_LBA   StartingLBA;
  
  
  
  EFI_LBA   EndingLBA;
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  UINT64    Attributes;
  
  
  
  CHAR16    PartitionName[36];
} EFI_PARTITION_ENTRY;

#pragma pack()
#line 140 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiGpt.h"


#line 2150 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"
#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiInternalFormRepresentation.h"






















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Guid/HiiFormMapMethodGuid.h"






















extern EFI_GUID gEfiHiiStandardFormGuid;

#line 26 "c:\\1218_alibaba\\MdePkg\\Include\\Guid/HiiFormMapMethodGuid.h"
#line 24 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiInternalFormRepresentation.h"




typedef void*   EFI_HII_HANDLE;
typedef CHAR16* EFI_STRING;
typedef UINT16  EFI_IMAGE_ID;
typedef UINT16  EFI_QUESTION_ID;
typedef UINT16  EFI_STRING_ID;
typedef UINT16  EFI_FORM_ID;
typedef UINT16  EFI_VARSTORE_ID;
typedef UINT16  EFI_ANIMATION_ID;

typedef UINT16  EFI_DEFAULT_ID;

typedef UINT32  EFI_HII_FONT_STYLE;



#pragma pack(1)









typedef struct {
  EFI_GUID               PackageListGuid;
  UINT32                 PackageLength;
} EFI_HII_PACKAGE_LIST_HEADER;




typedef struct {
  UINT32  Length:24;
  UINT32  Type:8;
  
} EFI_HII_PACKAGE_HEADER;


































typedef struct {
  
  
  
  
  CHAR16                 UnicodeWeight;
  
  
  
  UINT8                  Attributes;
  
  
  
  
  
  UINT8                  GlyphCol1[19];
} EFI_NARROW_GLYPH;





typedef struct {
  
  
  
  
  CHAR16                 UnicodeWeight;
  
  
  
  UINT8                  Attributes;
  
  
  
  
  
  UINT8                  GlyphCol1[19];
  
  
  
  
  
  UINT8                  GlyphCol2[19];
  
  
  
  
  
  UINT8                  Pad[3];
} EFI_WIDE_GLYPH;





typedef struct _EFI_HII_SIMPLE_FONT_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER Header;
  UINT16                 NumberOfNarrowGlyphs;
  UINT16                 NumberOfWideGlyphs;
  
  
} EFI_HII_SIMPLE_FONT_PACKAGE_HDR;


















typedef struct _EFI_HII_GLYPH_INFO {
  UINT16                 Width;
  UINT16                 Height;
  INT16                  OffsetX;
  INT16                  OffsetY;
  INT16                  AdvanceX;
} EFI_HII_GLYPH_INFO;







typedef struct _EFI_HII_FONT_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER Header;
  UINT32                 HdrSize;
  UINT32                 GlyphBlockOffset;
  EFI_HII_GLYPH_INFO     Cell;
  EFI_HII_FONT_STYLE     FontStyle;
  CHAR16                 FontFamily[1];
} EFI_HII_FONT_PACKAGE_HDR;

















typedef struct _EFI_HII_GLYPH_BLOCK {
  UINT8                  BlockType;
} EFI_HII_GLYPH_BLOCK;





typedef struct _EFI_HII_GIBT_DEFAULTS_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  EFI_HII_GLYPH_INFO     Cell;
} EFI_HII_GIBT_DEFAULTS_BLOCK;

typedef struct _EFI_HII_GIBT_DUPLICATE_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  CHAR16                 CharValue;
} EFI_HII_GIBT_DUPLICATE_BLOCK;

typedef struct _EFI_GLYPH_GIBT_END_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
} EFI_GLYPH_GIBT_END_BLOCK;

typedef struct _EFI_HII_GIBT_EXT1_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  UINT8                  BlockType2;
  UINT8                  Length;
} EFI_HII_GIBT_EXT1_BLOCK;

typedef struct _EFI_HII_GIBT_EXT2_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  UINT8                  BlockType2;
  UINT16                 Length;
} EFI_HII_GIBT_EXT2_BLOCK;

typedef struct _EFI_HII_GIBT_EXT4_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  UINT8                  BlockType2;
  UINT32                 Length;
} EFI_HII_GIBT_EXT4_BLOCK;

typedef struct _EFI_HII_GIBT_GLYPH_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  EFI_HII_GLYPH_INFO     Cell;
  UINT8                  BitmapData[1];
} EFI_HII_GIBT_GLYPH_BLOCK;

typedef struct _EFI_HII_GIBT_GLYPHS_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  EFI_HII_GLYPH_INFO     Cell;
  UINT16                 Count;  
  UINT8                  BitmapData[1];
} EFI_HII_GIBT_GLYPHS_BLOCK;

typedef struct _EFI_HII_GIBT_GLYPH_DEFAULT_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  UINT8                  BitmapData[1];
} EFI_HII_GIBT_GLYPH_DEFAULT_BLOCK;

typedef struct _EFI_HII_GIBT_GLYPHS_DEFAULT_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  UINT16                 Count;
  UINT8                  BitmapData[1];
} EFI_HII_GIBT_GLYPHS_DEFAULT_BLOCK;

typedef struct _EFI_HII_GIBT_SKIP1_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  UINT8                  SkipCount;
} EFI_HII_GIBT_SKIP1_BLOCK;

typedef struct _EFI_HII_GIBT_SKIP2_BLOCK {
  EFI_HII_GLYPH_BLOCK    Header;
  UINT16                 SkipCount;
} EFI_HII_GIBT_SKIP2_BLOCK;










typedef struct _EFI_HII_DEVICE_PATH_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER   Header;
  
} EFI_HII_DEVICE_PATH_PACKAGE_HDR;









typedef struct _EFI_HII_GUID_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER  Header;
  EFI_GUID                Guid;
  
} EFI_HII_GUID_PACKAGE_HDR;













typedef struct _EFI_HII_STRING_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER  Header;
  UINT32                  HdrSize;
  UINT32                  StringInfoOffset;
  CHAR16                  LanguageWindow[16];
  EFI_STRING_ID           LanguageName;
  CHAR8                   Language[1];
} EFI_HII_STRING_PACKAGE_HDR;

typedef struct {
  UINT8                   BlockType;
} EFI_HII_STRING_BLOCK;

























typedef struct _EFI_HII_SIBT_DUPLICATE_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  EFI_STRING_ID           StringId;
} EFI_HII_SIBT_DUPLICATE_BLOCK;

typedef struct _EFI_HII_SIBT_END_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
} EFI_HII_SIBT_END_BLOCK;

typedef struct _EFI_HII_SIBT_EXT1_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   BlockType2;
  UINT8                   Length;
} EFI_HII_SIBT_EXT1_BLOCK;

typedef struct _EFI_HII_SIBT_EXT2_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   BlockType2;
  UINT16                  Length;
} EFI_HII_SIBT_EXT2_BLOCK;

typedef struct _EFI_HII_SIBT_EXT4_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   BlockType2;
  UINT32                  Length;
} EFI_HII_SIBT_EXT4_BLOCK;

typedef struct _EFI_HII_SIBT_FONT_BLOCK {
  EFI_HII_SIBT_EXT2_BLOCK Header;
  UINT8                   FontId;
  UINT16                  FontSize;
  EFI_HII_FONT_STYLE      FontStyle;
  CHAR16                  FontName[1];
} EFI_HII_SIBT_FONT_BLOCK;

typedef struct _EFI_HII_SIBT_SKIP1_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   SkipCount;
} EFI_HII_SIBT_SKIP1_BLOCK;

typedef struct _EFI_HII_SIBT_SKIP2_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT16                  SkipCount;
} EFI_HII_SIBT_SKIP2_BLOCK;

typedef struct _EFI_HII_SIBT_STRING_SCSU_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   StringText[1];
} EFI_HII_SIBT_STRING_SCSU_BLOCK;

typedef struct _EFI_HII_SIBT_STRING_SCSU_FONT_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   FontIdentifier;
  UINT8                   StringText[1];
} EFI_HII_SIBT_STRING_SCSU_FONT_BLOCK;

typedef struct _EFI_HII_SIBT_STRINGS_SCSU_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT16                  StringCount;
  UINT8                   StringText[1];
} EFI_HII_SIBT_STRINGS_SCSU_BLOCK;

typedef struct _EFI_HII_SIBT_STRINGS_SCSU_FONT_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   FontIdentifier;
  UINT16                  StringCount;
  UINT8                   StringText[1];
} EFI_HII_SIBT_STRINGS_SCSU_FONT_BLOCK;

typedef struct _EFI_HII_SIBT_STRING_UCS2_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  CHAR16                  StringText[1];
} EFI_HII_SIBT_STRING_UCS2_BLOCK;

typedef struct _EFI_HII_SIBT_STRING_UCS2_FONT_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   FontIdentifier;
  CHAR16                  StringText[1];
} EFI_HII_SIBT_STRING_UCS2_FONT_BLOCK;

typedef struct _EFI_HII_SIBT_STRINGS_UCS2_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT16                  StringCount;
  CHAR16                  StringText[1];
} EFI_HII_SIBT_STRINGS_UCS2_BLOCK;

typedef struct _EFI_HII_SIBT_STRINGS_UCS2_FONT_BLOCK {
  EFI_HII_STRING_BLOCK    Header;
  UINT8                   FontIdentifier;
  UINT16                  StringCount;
  CHAR16                  StringText[1];
} EFI_HII_SIBT_STRINGS_UCS2_FONT_BLOCK;






typedef struct _EFI_HII_IMAGE_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER  Header;
  UINT32                  ImageInfoOffset;
  UINT32                  PaletteInfoOffset;
} EFI_HII_IMAGE_PACKAGE_HDR;

typedef struct _EFI_HII_IMAGE_BLOCK {
  UINT8                   BlockType;
} EFI_HII_IMAGE_BLOCK;

























typedef struct _EFI_HII_IIBT_END_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
} EFI_HII_IIBT_END_BLOCK;

typedef struct _EFI_HII_IIBT_EXT1_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        BlockType2;
  UINT8                        Length;
} EFI_HII_IIBT_EXT1_BLOCK;

typedef struct _EFI_HII_IIBT_EXT2_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        BlockType2;
  UINT16                       Length;
} EFI_HII_IIBT_EXT2_BLOCK;

typedef struct _EFI_HII_IIBT_EXT4_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        BlockType2;
  UINT32                       Length;
} EFI_HII_IIBT_EXT4_BLOCK;

typedef struct _EFI_HII_IIBT_IMAGE_1BIT_BASE {
  UINT16                       Width;
  UINT16                       Height;
  UINT8                        Data[1];
} EFI_HII_IIBT_IMAGE_1BIT_BASE;

typedef struct _EFI_HII_IIBT_IMAGE_1BIT_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        PaletteIndex;
  EFI_HII_IIBT_IMAGE_1BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_1BIT_BLOCK;

typedef struct _EFI_HII_IIBT_IMAGE_1BIT_TRANS_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        PaletteIndex;
  EFI_HII_IIBT_IMAGE_1BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_1BIT_TRANS_BLOCK;

typedef struct _EFI_HII_RGB_PIXEL {
  UINT8                        b;
  UINT8                        g;
  UINT8                        r;
} EFI_HII_RGB_PIXEL;

typedef struct _EFI_HII_IIBT_IMAGE_24BIT_BASE {
  UINT16                       Width;
  UINT16                       Height;
  EFI_HII_RGB_PIXEL            Bitmap[1];
} EFI_HII_IIBT_IMAGE_24BIT_BASE;

typedef struct _EFI_HII_IIBT_IMAGE_24BIT_BLOCK {
  EFI_HII_IMAGE_BLOCK           Header;
  EFI_HII_IIBT_IMAGE_24BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_24BIT_BLOCK;

typedef struct _EFI_HII_IIBT_IMAGE_24BIT_TRANS_BLOCK {
  EFI_HII_IMAGE_BLOCK           Header;
  EFI_HII_IIBT_IMAGE_24BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_24BIT_TRANS_BLOCK;

typedef struct _EFI_HII_IIBT_IMAGE_4BIT_BASE {
  UINT16                       Width;
  UINT16                       Height;
  UINT8                        Data[1];
} EFI_HII_IIBT_IMAGE_4BIT_BASE;

typedef struct _EFI_HII_IIBT_IMAGE_4BIT_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        PaletteIndex;
  EFI_HII_IIBT_IMAGE_4BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_4BIT_BLOCK;

typedef struct _EFI_HII_IIBT_IMAGE_4BIT_TRANS_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        PaletteIndex;
  EFI_HII_IIBT_IMAGE_4BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_4BIT_TRANS_BLOCK;

typedef struct _EFI_HII_IIBT_IMAGE_8BIT_BASE {
  UINT16                       Width;
  UINT16                       Height;
  UINT8                        Data[1];
} EFI_HII_IIBT_IMAGE_8BIT_BASE;

typedef struct _EFI_HII_IIBT_IMAGE_8BIT_PALETTE_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        PaletteIndex;
  EFI_HII_IIBT_IMAGE_8BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_8BIT_BLOCK;

typedef struct _EFI_HII_IIBT_IMAGE_8BIT_TRANS_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        PaletteIndex;
  EFI_HII_IIBT_IMAGE_8BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_8BIT_TRAN_BLOCK;

typedef struct _EFI_HII_IIBT_DUPLICATE_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  EFI_IMAGE_ID                 ImageId;
} EFI_HII_IIBT_DUPLICATE_BLOCK;

typedef struct _EFI_HII_IIBT_JPEG_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT32                       Size;
  UINT8                        Data[1];
} EFI_HII_IIBT_JPEG_BLOCK;

typedef struct _EFI_HII_IIBT_SKIP1_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT8                        SkipCount;
} EFI_HII_IIBT_SKIP1_BLOCK;

typedef struct _EFI_HII_IIBT_SKIP2_BLOCK {
  EFI_HII_IMAGE_BLOCK          Header;
  UINT16                       SkipCount;
} EFI_HII_IIBT_SKIP2_BLOCK;





typedef struct _EFI_HII_IMAGE_PALETTE_INFO_HEADER {
  UINT16                       PaletteCount;
} EFI_HII_IMAGE_PALETTE_INFO_HEADER;

typedef struct _EFI_HII_IMAGE_PALETTE_INFO {
  UINT16                       PaletteSize;
  EFI_HII_RGB_PIXEL            PaletteValue[1];
} EFI_HII_IMAGE_PALETTE_INFO;









typedef struct _EFI_HII_FORM_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER       Header;
  
  
} EFI_HII_FORM_PACKAGE_HDR;

typedef struct {
  UINT8 Hour;
  UINT8 Minute;
  UINT8 Second;
} EFI_HII_TIME;

typedef struct {
  UINT16 Year;
  UINT8  Month;
  UINT8  Day;
} EFI_HII_DATE;

typedef struct {
  EFI_QUESTION_ID QuestionId;
  EFI_FORM_ID     FormId;
  EFI_GUID        FormSetGuid;
  EFI_STRING_ID   DevicePath;
} EFI_HII_REF;

typedef union {
  UINT8           u8;
  UINT16          u16;
  UINT32          u32;
  UINT64          u64;
  BOOLEAN         b;
  EFI_HII_TIME    time;
  EFI_HII_DATE    date;
  EFI_STRING_ID   string; 
  EFI_HII_REF     ref;    
  
} EFI_IFR_TYPE_VALUE;













































































































typedef struct _EFI_IFR_OP_HEADER {
  UINT8                    OpCode;
  UINT8                    Length:7;
  UINT8                    Scope:1;
} EFI_IFR_OP_HEADER;

typedef struct _EFI_IFR_STATEMENT_HEADER {
  EFI_STRING_ID            Prompt;
  EFI_STRING_ID            Help;
} EFI_IFR_STATEMENT_HEADER;

typedef struct _EFI_IFR_QUESTION_HEADER {
  EFI_IFR_STATEMENT_HEADER Header;
  EFI_QUESTION_ID          QuestionId;
  EFI_VARSTORE_ID          VarStoreId;
  union {
    EFI_STRING_ID          VarName;
    UINT16                 VarOffset;
  }                        VarStoreInfo;
  UINT8                    Flags;
} EFI_IFR_QUESTION_HEADER;













typedef struct _EFI_IFR_DEFAULTSTORE {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            DefaultName;
  UINT16                   DefaultId;
} EFI_IFR_DEFAULTSTORE;














typedef struct _EFI_IFR_VARSTORE {
  EFI_IFR_OP_HEADER        Header;
  EFI_GUID                 Guid;
  EFI_VARSTORE_ID          VarStoreId;
  UINT16                   Size;
  UINT8                    Name[1];
} EFI_IFR_VARSTORE;

typedef struct _EFI_IFR_VARSTORE_EFI {
  EFI_IFR_OP_HEADER        Header;
  EFI_VARSTORE_ID          VarStoreId;
  EFI_GUID                 Guid;
  UINT32                   Attributes;
  UINT16                   Size;
  UINT8                    Name[1];
} EFI_IFR_VARSTORE_EFI;

typedef struct _EFI_IFR_VARSTORE_NAME_VALUE {
  EFI_IFR_OP_HEADER        Header;
  EFI_VARSTORE_ID          VarStoreId;
  EFI_GUID                 Guid;
} EFI_IFR_VARSTORE_NAME_VALUE;

typedef struct _EFI_IFR_FORM_SET {
  EFI_IFR_OP_HEADER        Header;
  EFI_GUID                 Guid;
  EFI_STRING_ID            FormSetTitle;
  EFI_STRING_ID            Help;
  UINT8                    Flags;
  
} EFI_IFR_FORM_SET;

typedef struct _EFI_IFR_END {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_END;

typedef struct _EFI_IFR_FORM {
  EFI_IFR_OP_HEADER        Header;
  UINT16                   FormId;
  EFI_STRING_ID            FormTitle;
} EFI_IFR_FORM;

typedef struct _EFI_IFR_IMAGE {
  EFI_IFR_OP_HEADER        Header;
  EFI_IMAGE_ID             Id;
} EFI_IFR_IMAGE;

typedef struct _EFI_IFR_MODAL_TAG {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_MODAL_TAG;

typedef struct _EFI_IFR_LOCKED {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_LOCKED;

typedef struct _EFI_IFR_RULE {
  EFI_IFR_OP_HEADER        Header;
  UINT8                    RuleId;
} EFI_IFR_RULE;

typedef struct _EFI_IFR_DEFAULT {
  EFI_IFR_OP_HEADER        Header;
  UINT16                   DefaultId;
  UINT8                    Type;
  EFI_IFR_TYPE_VALUE       Value;
} EFI_IFR_DEFAULT;

typedef struct _EFI_IFR_DEFAULT_2 {
  EFI_IFR_OP_HEADER        Header;
  UINT16                   DefaultId;
  UINT8                    Type;
} EFI_IFR_DEFAULT_2;

typedef struct _EFI_IFR_VALUE {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_VALUE;

typedef struct _EFI_IFR_SUBTITLE {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_STATEMENT_HEADER Statement;
  UINT8                    Flags;
} EFI_IFR_SUBTITLE;



typedef struct _EFI_IFR_CHECKBOX {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  UINT8                    Flags;
} EFI_IFR_CHECKBOX;




typedef struct _EFI_IFR_TEXT {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_STATEMENT_HEADER Statement;
  EFI_STRING_ID            TextTwo;
} EFI_IFR_TEXT;

typedef struct _EFI_IFR_REF {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  EFI_FORM_ID              FormId;
} EFI_IFR_REF;

typedef struct _EFI_IFR_REF2 {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  EFI_FORM_ID              FormId;
  EFI_QUESTION_ID          QuestionId;
} EFI_IFR_REF2;

typedef struct _EFI_IFR_REF3 {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  EFI_FORM_ID              FormId;
  EFI_QUESTION_ID          QuestionId;
  EFI_GUID                 FormSetId;
} EFI_IFR_REF3;

typedef struct _EFI_IFR_REF4 {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  EFI_FORM_ID              FormId;
  EFI_QUESTION_ID          QuestionId;
  EFI_GUID                 FormSetId;
  EFI_STRING_ID            DevicePath;
} EFI_IFR_REF4;

typedef struct _EFI_IFR_REF5 {
  EFI_IFR_OP_HEADER Header;
  EFI_IFR_QUESTION_HEADER Question;
} EFI_IFR_REF5;

typedef struct _EFI_IFR_RESET_BUTTON {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_STATEMENT_HEADER Statement;
  EFI_DEFAULT_ID           DefaultId;
} EFI_IFR_RESET_BUTTON;

typedef struct _EFI_IFR_ACTION {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  EFI_STRING_ID            QuestionConfig;
} EFI_IFR_ACTION;

typedef struct _EFI_IFR_ACTION_1 {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
} EFI_IFR_ACTION_1;

typedef struct _EFI_IFR_DATE {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  UINT8                    Flags;
} EFI_IFR_DATE;













typedef union {
  struct {
    UINT8 MinValue;
    UINT8 MaxValue;
    UINT8 Step;
  } u8;
  struct {
    UINT16 MinValue;
    UINT16 MaxValue;
    UINT16 Step;
  } u16;
  struct {
    UINT32 MinValue;
    UINT32 MaxValue;
    UINT32 Step;
  } u32;
  struct {
    UINT64 MinValue;
    UINT64 MaxValue;
    UINT64 Step;
  } u64;
} MINMAXSTEP_DATA;

typedef struct _EFI_IFR_NUMERIC {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  UINT8                    Flags;
  MINMAXSTEP_DATA          data;
} EFI_IFR_NUMERIC;















typedef struct _EFI_IFR_ONE_OF {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  UINT8                    Flags;
  MINMAXSTEP_DATA          data;
} EFI_IFR_ONE_OF;

typedef struct _EFI_IFR_STRING {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  UINT8                    MinSize;
  UINT8                    MaxSize;
  UINT8                    Flags;
} EFI_IFR_STRING;



typedef struct _EFI_IFR_PASSWORD {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  UINT16                   MinSize;
  UINT16                   MaxSize;
} EFI_IFR_PASSWORD;

typedef struct _EFI_IFR_ORDERED_LIST {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  UINT8                    MaxContainers;
  UINT8                    Flags;
} EFI_IFR_ORDERED_LIST;




typedef struct _EFI_IFR_TIME {
  EFI_IFR_OP_HEADER        Header;
  EFI_IFR_QUESTION_HEADER  Question;
  UINT8                    Flags;
} EFI_IFR_TIME;













typedef struct _EFI_IFR_DISABLE_IF {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_DISABLE_IF;

typedef struct _EFI_IFR_SUPPRESS_IF {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_SUPPRESS_IF;

typedef struct _EFI_IFR_GRAY_OUT_IF {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_GRAY_OUT_IF;

typedef struct _EFI_IFR_INCONSISTENT_IF {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            Error;
} EFI_IFR_INCONSISTENT_IF;

typedef struct _EFI_IFR_NO_SUBMIT_IF {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            Error;
} EFI_IFR_NO_SUBMIT_IF;

typedef struct _EFI_IFR_WARNING_IF {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            Warning;
  UINT8                    TimeOut;
} EFI_IFR_WARNING_IF;

typedef struct _EFI_IFR_REFRESH {
  EFI_IFR_OP_HEADER        Header;
  UINT8                    RefreshInterval;
} EFI_IFR_REFRESH;

typedef struct _EFI_IFR_VARSTORE_DEVICE {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            DevicePath;
} EFI_IFR_VARSTORE_DEVICE;

typedef struct _EFI_IFR_ONE_OF_OPTION {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            Option;
  UINT8                    Flags;
  UINT8                    Type;
  EFI_IFR_TYPE_VALUE       Value;
} EFI_IFR_ONE_OF_OPTION;





















typedef struct _EFI_IFR_GUID {
  EFI_IFR_OP_HEADER        Header;
  EFI_GUID                 Guid;
  
} EFI_IFR_GUID;

typedef struct _EFI_IFR_REFRESH_ID {
  EFI_IFR_OP_HEADER Header;
  EFI_GUID          RefreshEventGroupId;
} EFI_IFR_REFRESH_ID;

typedef struct _EFI_IFR_DUP {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_DUP;

typedef struct _EFI_IFR_EQ_ID_ID {
  EFI_IFR_OP_HEADER        Header;
  EFI_QUESTION_ID          QuestionId1;
  EFI_QUESTION_ID          QuestionId2;
} EFI_IFR_EQ_ID_ID;

typedef struct _EFI_IFR_EQ_ID_VAL {
  EFI_IFR_OP_HEADER        Header;
  EFI_QUESTION_ID          QuestionId;
  UINT16                   Value;
} EFI_IFR_EQ_ID_VAL;

typedef struct _EFI_IFR_EQ_ID_VAL_LIST {
  EFI_IFR_OP_HEADER        Header;
  EFI_QUESTION_ID          QuestionId;
  UINT16                   ListLength;
  UINT16                   ValueList[1];
} EFI_IFR_EQ_ID_VAL_LIST;

typedef struct _EFI_IFR_UINT8 {
  EFI_IFR_OP_HEADER        Header;
  UINT8 Value;
} EFI_IFR_UINT8;

typedef struct _EFI_IFR_UINT16 {
  EFI_IFR_OP_HEADER        Header;
  UINT16                   Value;
} EFI_IFR_UINT16;

typedef struct _EFI_IFR_UINT32 {
  EFI_IFR_OP_HEADER        Header;
  UINT32                   Value;
} EFI_IFR_UINT32;

typedef struct _EFI_IFR_UINT64 {
  EFI_IFR_OP_HEADER        Header;
  UINT64 Value;
} EFI_IFR_UINT64;

typedef struct _EFI_IFR_QUESTION_REF1 {
  EFI_IFR_OP_HEADER        Header;
  EFI_QUESTION_ID          QuestionId;
} EFI_IFR_QUESTION_REF1;

typedef struct _EFI_IFR_QUESTION_REF2 {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_QUESTION_REF2;

typedef struct _EFI_IFR_QUESTION_REF3 {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_QUESTION_REF3;

typedef struct _EFI_IFR_QUESTION_REF3_2 {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            DevicePath;
} EFI_IFR_QUESTION_REF3_2;

typedef struct _EFI_IFR_QUESTION_REF3_3 {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            DevicePath;
  EFI_GUID                 Guid;
} EFI_IFR_QUESTION_REF3_3;

typedef struct _EFI_IFR_RULE_REF {
  EFI_IFR_OP_HEADER        Header;
  UINT8                    RuleId;
} EFI_IFR_RULE_REF;

typedef struct _EFI_IFR_STRING_REF1 {
  EFI_IFR_OP_HEADER        Header;
  EFI_STRING_ID            StringId;
} EFI_IFR_STRING_REF1;

typedef struct _EFI_IFR_STRING_REF2 {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_STRING_REF2;

typedef struct _EFI_IFR_THIS {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_THIS;

typedef struct _EFI_IFR_TRUE {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_TRUE;

typedef struct _EFI_IFR_FALSE {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_FALSE;

typedef struct _EFI_IFR_ONE {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_ONE;

typedef struct _EFI_IFR_ONES {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_ONES;

typedef struct _EFI_IFR_ZERO {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_ZERO;

typedef struct _EFI_IFR_UNDEFINED {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_UNDEFINED;

typedef struct _EFI_IFR_VERSION {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_VERSION;

typedef struct _EFI_IFR_LENGTH {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_LENGTH;

typedef struct _EFI_IFR_NOT {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_NOT;

typedef struct _EFI_IFR_BITWISE_NOT {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_BITWISE_NOT;

typedef struct _EFI_IFR_TO_BOOLEAN {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_TO_BOOLEAN;
























typedef struct _EFI_IFR_TO_STRING {
  EFI_IFR_OP_HEADER        Header;
  UINT8                    Format;
} EFI_IFR_TO_STRING;

typedef struct _EFI_IFR_TO_UINT {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_TO_UINT;

typedef struct _EFI_IFR_TO_UPPER {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_TO_UPPER;

typedef struct _EFI_IFR_TO_LOWER {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_TO_LOWER;

typedef struct _EFI_IFR_ADD {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_ADD;

typedef struct _EFI_IFR_AND {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_AND;

typedef struct _EFI_IFR_BITWISE_AND {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_BITWISE_AND;

typedef struct _EFI_IFR_BITWISE_OR {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_BITWISE_OR;

typedef struct _EFI_IFR_CATENATE {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_CATENATE;

typedef struct _EFI_IFR_DIVIDE {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_DIVIDE;

typedef struct _EFI_IFR_EQUAL {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_EQUAL;

typedef struct _EFI_IFR_GREATER_EQUAL {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_GREATER_EQUAL;

typedef struct _EFI_IFR_GREATER_THAN {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_GREATER_THAN;

typedef struct _EFI_IFR_LESS_EQUAL {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_LESS_EQUAL;

typedef struct _EFI_IFR_LESS_THAN {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_LESS_THAN;

typedef struct _EFI_IFR_MATCH {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_MATCH;

typedef struct _EFI_IFR_MULTIPLY {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_MULTIPLY;

typedef struct _EFI_IFR_MODULO {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_MODULO;

typedef struct _EFI_IFR_NOT_EQUAL {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_NOT_EQUAL;

typedef struct _EFI_IFR_OR {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_OR;

typedef struct _EFI_IFR_SHIFT_LEFT {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_SHIFT_LEFT;

typedef struct _EFI_IFR_SHIFT_RIGHT {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_SHIFT_RIGHT;

typedef struct _EFI_IFR_SUBTRACT {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_SUBTRACT;

typedef struct _EFI_IFR_CONDITIONAL {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_CONDITIONAL;







typedef struct _EFI_IFR_FIND {
  EFI_IFR_OP_HEADER        Header;
  UINT8                    Format;
} EFI_IFR_FIND;

typedef struct _EFI_IFR_MID {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_MID;

typedef struct _EFI_IFR_TOKEN {
  EFI_IFR_OP_HEADER        Header;
} EFI_IFR_TOKEN;








typedef struct _EFI_IFR_SPAN {
  EFI_IFR_OP_HEADER        Header;
  UINT8                    Flags;
} EFI_IFR_SPAN;

typedef struct _EFI_IFR_SECURITY {
  
  
  
  EFI_IFR_OP_HEADER        Header;
  
  
  
  EFI_GUID                 Permissions;
} EFI_IFR_SECURITY;

typedef struct _EFI_IFR_FORM_MAP_METHOD {
  
  
  
  
  EFI_STRING_ID            MethodTitle;
  
  
  
  
  EFI_GUID                 MethodIdentifier;
} EFI_IFR_FORM_MAP_METHOD;

typedef struct _EFI_IFR_FORM_MAP {
  
  
  
  
  EFI_IFR_OP_HEADER        Header;
  
  
  
  EFI_FORM_ID              FormId;
  
  
  
  
} EFI_IFR_FORM_MAP;

typedef struct _EFI_IFR_SET {
  
  
  
  
  EFI_IFR_OP_HEADER  Header;
  
  
  
  
  EFI_VARSTORE_ID    VarStoreId;
  union {
    
    
    
    EFI_STRING_ID    VarName;
    
    
    
    UINT16           VarOffset;
  }                  VarStoreInfo;
  
  
  
  UINT8              VarStoreType;
} EFI_IFR_SET;

typedef struct _EFI_IFR_GET {
  
  
  
  
  EFI_IFR_OP_HEADER  Header;
  
  
  
  
  EFI_VARSTORE_ID    VarStoreId;
  union {
    
    
    
    EFI_STRING_ID    VarName;
    
    
    
    UINT16           VarOffset;
  }                  VarStoreInfo;
  
  
  
  UINT8              VarStoreType;
} EFI_IFR_GET;

typedef struct _EFI_IFR_READ {
  EFI_IFR_OP_HEADER       Header;
} EFI_IFR_READ;

typedef struct _EFI_IFR_WRITE {
  EFI_IFR_OP_HEADER      Header;
} EFI_IFR_WRITE;

typedef struct _EFI_IFR_MAP {
  EFI_IFR_OP_HEADER      Header;
} EFI_IFR_MAP;








typedef enum {    
  EfiKeyLCtrl,
  EfiKeyA0, 
  EfiKeyLAlt,
  EfiKeySpaceBar,
  EfiKeyA2,
  EfiKeyA3,
  EfiKeyA4,
  EfiKeyRCtrl,
  EfiKeyLeftArrow,
  EfiKeyDownArrow,
  EfiKeyRightArrow,
  EfiKeyZero,
  EfiKeyPeriod,
  EfiKeyEnter,
  EfiKeyLShift,
  EfiKeyB0,
  EfiKeyB1,
  EfiKeyB2,
  EfiKeyB3,
  EfiKeyB4,
  EfiKeyB5,
  EfiKeyB6,
  EfiKeyB7,
  EfiKeyB8,
  EfiKeyB9,
  EfiKeyB10,
  EfiKeyRShift,
  EfiKeyUpArrow,
  EfiKeyOne,
  EfiKeyTwo,
  EfiKeyThree,
  EfiKeyCapsLock,
  EfiKeyC1,
  EfiKeyC2,
  EfiKeyC3,
  EfiKeyC4,
  EfiKeyC5,
  EfiKeyC6,
  EfiKeyC7,
  EfiKeyC8,
  EfiKeyC9,
  EfiKeyC10,
  EfiKeyC11,
  EfiKeyC12,
  EfiKeyFour,
  EfiKeyFive,
  EfiKeySix,
  EfiKeyPlus,
  EfiKeyTab,
  EfiKeyD1,
  EfiKeyD2,
  EfiKeyD3,
  EfiKeyD4,
  EfiKeyD5,
  EfiKeyD6,
  EfiKeyD7,
  EfiKeyD8,
  EfiKeyD9,
  EfiKeyD10,
  EfiKeyD11,
  EfiKeyD12,
  EfiKeyD13,
  EfiKeyDel,
  EfiKeyEnd,
  EfiKeyPgDn,
  EfiKeySeven,
  EfiKeyEight,
  EfiKeyNine,
  EfiKeyE0,
  EfiKeyE1,
  EfiKeyE2,
  EfiKeyE3,
  EfiKeyE4,
  EfiKeyE5,
  EfiKeyE6,
  EfiKeyE7,
  EfiKeyE8,
  EfiKeyE9,
  EfiKeyE10,
  EfiKeyE11,
  EfiKeyE12,
  EfiKeyBackSpace,
  EfiKeyIns,
  EfiKeyHome,
  EfiKeyPgUp,
  EfiKeyNLck,
  EfiKeySlash,
  EfiKeyAsterisk,
  EfiKeyMinus,
  EfiKeyEsc,
  EfiKeyF1,
  EfiKeyF2,
  EfiKeyF3,
  EfiKeyF4,
  EfiKeyF5,
  EfiKeyF6,
  EfiKeyF7,
  EfiKeyF8,
  EfiKeyF9,
  EfiKeyF10,
  EfiKeyF11,
  EfiKeyF12,
  EfiKeyPrint,
  EfiKeySLck,
  EfiKeyPause
} EFI_KEY;

typedef struct {
  
  
  
  EFI_KEY                 Key;
  
  
  
  CHAR16                  Unicode;
  
  
  
  CHAR16                  ShiftedUnicode;
  
  
  
  CHAR16                  AltGrUnicode;
  
  
  
  CHAR16                  ShiftedAltGrUnicode;
  
  
  
  
  
  UINT16                  Modifier;
  UINT16                  AffectedAttribute;
} EFI_KEY_DESCRIPTOR;





















typedef struct {
  UINT16                  LayoutLength;
  EFI_GUID                Guid;
  UINT32                  LayoutDescriptorStringOffset;
  UINT8                   DescriptorCount;
  
} EFI_HII_KEYBOARD_LAYOUT;

typedef struct {
  EFI_HII_PACKAGE_HEADER  Header;
  UINT16                  LayoutCount;
  
} EFI_HII_KEYBOARD_PACKAGE_HDR;



























































typedef struct _EFI_IFR_ANIMATION {
  
  
  
  
  EFI_IFR_OP_HEADER        Header;
  
  
  
  EFI_ANIMATION_ID         Id;
} EFI_IFR_ANIMATION;




typedef struct _EFI_HII_ANIMATION_PACKAGE_HDR {
  
  
  
  EFI_HII_PACKAGE_HEADER  Header;
  
  
  
  
  UINT32                  AnimationInfoOffset;
} EFI_HII_ANIMATION_PACKAGE_HDR;





typedef struct _EFI_HII_ANIMATION_BLOCK {
  UINT8  BlockType;
  
} EFI_HII_ANIMATION_BLOCK;























typedef struct _EFI_HII_AIBT_EXT1_BLOCK  {
  
  
  
  EFI_HII_ANIMATION_BLOCK  Header;
  
  
  
  UINT8                    BlockType2;
  
  
  
  UINT8                    Length;
} EFI_HII_AIBT_EXT1_BLOCK;

typedef struct _EFI_HII_AIBT_EXT2_BLOCK {
  
  
  
  EFI_HII_ANIMATION_BLOCK  Header;
  
  
  
  UINT8                    BlockType2;
  
  
  
  UINT16                   Length;
} EFI_HII_AIBT_EXT2_BLOCK;

typedef struct _EFI_HII_AIBT_EXT4_BLOCK {
  
  
  
  EFI_HII_ANIMATION_BLOCK  Header;
  
  
  
  UINT8                    BlockType2;
  
  
  
  UINT32                   Length;
} EFI_HII_AIBT_EXT4_BLOCK;

typedef struct _EFI_HII_ANIMATION_CELL {
  
  
  
  
  UINT16                    OffsetX;
  
  
  
  
  UINT16                    OffsetY;
  
  
  
  
  EFI_IMAGE_ID              ImageId;
  
  
  
  
  
  UINT16                    Delay;
} EFI_HII_ANIMATION_CELL;





typedef struct _EFI_HII_AIBT_OVERLAY_IMAGES_BLOCK {
  
  
  
  
  
  
  
  
  EFI_IMAGE_ID            DftImageId;
  
  
  
  UINT16                  Width;
  
  
  
  UINT16                  Height;
  
  
  
  
  UINT16                  CellCount;
  
  
  
  EFI_HII_ANIMATION_CELL  AnimationCell[1];
} EFI_HII_AIBT_OVERLAY_IMAGES_BLOCK;






typedef struct _EFI_HII_AIBT_CLEAR_IMAGES_BLOCK {
  
  
  
  
  
  
  
  
  EFI_IMAGE_ID       DftImageId;
  
  
  
  UINT16             Width;
  
  
  
  UINT16             Height;
  
  
  
  
  UINT16             CellCount;
  
  
  
  
  EFI_HII_RGB_PIXEL  BackgndColor;
  
  
  
  EFI_HII_ANIMATION_CELL AnimationCell[1];
} EFI_HII_AIBT_CLEAR_IMAGES_BLOCK;






typedef struct _EFI_HII_AIBT_RESTORE_SCRN_BLOCK {
  
  
  
  
  
  
  
  
  EFI_IMAGE_ID            DftImageId;
  
  
  
  UINT16                  Width;
  
  
  
  UINT16                  Height;
  
  
  
  
  UINT16                  CellCount;
  
  
  
  EFI_HII_ANIMATION_CELL  AnimationCell[1];
} EFI_HII_AIBT_RESTORE_SCRN_BLOCK;





typedef EFI_HII_AIBT_OVERLAY_IMAGES_BLOCK  EFI_HII_AIBT_OVERLAY_IMAGES_LOOP_BLOCK;






typedef EFI_HII_AIBT_CLEAR_IMAGES_BLOCK    EFI_HII_AIBT_CLEAR_IMAGES_LOOP_BLOCK;






typedef EFI_HII_AIBT_RESTORE_SCRN_BLOCK    EFI_HII_AIBT_RESTORE_SCRN_LOOP_BLOCK;




typedef struct _EFI_HII_AIBT_DUPLICATE_BLOCK {
  
  
  
  
  EFI_ANIMATION_ID  AnimationId;
} EFI_HII_AIBT_DUPLICATE_BLOCK;




typedef struct _EFI_HII_AIBT_SKIP1_BLOCK {
  
  
  
  UINT8  SkipCount;
} EFI_HII_AIBT_SKIP1_BLOCK;




typedef struct _EFI_HII_AIBT_SKIP2_BLOCK {
  
  
  
  UINT16  SkipCount;
} EFI_HII_AIBT_SKIP2_BLOCK;

#pragma pack()













#line 2107 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiInternalFormRepresentation.h"

#line 2151 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"

#line 2153 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiSpec.h"

#line 21 "c:\\1218_alibaba\\MdePkg\\Include\\PiDxe.h"

#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiDxeCis.h"




















#line 1 "c:\\1218_alibaba\\MdePkg\\Include\\Uefi/UefiMultiPhase.h"

































































































































































































#line 22 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiDxeCis.h"
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
#line 23 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiDxeCis.h"




typedef enum {
  
  
  
  
  EfiGcdMemoryTypeNonExistent,
  
  
  
  
  
  EfiGcdMemoryTypeReserved,
  
  
  
  
  
  EfiGcdMemoryTypeSystemMemory,
  
  
  
  
  
  EfiGcdMemoryTypeMemoryMappedIo,
  EfiGcdMemoryTypeMaximum
} EFI_GCD_MEMORY_TYPE;




typedef enum {
  
  
  
  
  EfiGcdIoTypeNonExistent,
  
  
  
  
  EfiGcdIoTypeReserved,
  
  
  
  
  EfiGcdIoTypeIo,
  EfiGcdIoTypeMaximum
} EFI_GCD_IO_TYPE;




typedef enum {
  
  
  
  
  EfiGcdAllocateAnySearchBottomUp,
  
  
  
  
  EfiGcdAllocateMaxAddressSearchBottomUp,
  
  
  
  
  EfiGcdAllocateAddress,
  
  
  
  
  EfiGcdAllocateAnySearchTopDown,
  
  
  
  
  EfiGcdAllocateMaxAddressSearchTopDown,
  EfiGcdMaxAllocateType
} EFI_GCD_ALLOCATE_TYPE;




typedef struct {
  
  
  
  
  
  EFI_PHYSICAL_ADDRESS  BaseAddress;

  
  
  
  UINT64                Length;

  
  
  
  
  
  UINT64                Capabilities;
  
  
  
  
  UINT64                Attributes;
  
  
  
  
  EFI_GCD_MEMORY_TYPE   GcdMemoryType;

  
  
  
  
  
  
  EFI_HANDLE            ImageHandle;

  
  
  
  
  
  
  
  EFI_HANDLE            DeviceHandle;
} EFI_GCD_MEMORY_SPACE_DESCRIPTOR;




typedef struct {
  
  
  
  
  
  EFI_PHYSICAL_ADDRESS  BaseAddress;

  
  
  
  UINT64                Length;

  
  
  
  
  EFI_GCD_IO_TYPE       GcdIoType;

  
  
  
  
  
  
  EFI_HANDLE            ImageHandle;

  
  
  
  
  
  
  
  EFI_HANDLE            DeviceHandle;
} EFI_GCD_IO_SPACE_DESCRIPTOR;

































typedef
EFI_STATUS
(__cdecl *EFI_ADD_MEMORY_SPACE)(
   EFI_GCD_MEMORY_TYPE   GcdMemoryType,
   EFI_PHYSICAL_ADDRESS  BaseAddress,
   UINT64                Length,
   UINT64                Capabilities
  );































typedef
EFI_STATUS
(__cdecl *EFI_ALLOCATE_MEMORY_SPACE)(
       EFI_GCD_ALLOCATE_TYPE               GcdAllocateType,
       EFI_GCD_MEMORY_TYPE                 GcdMemoryType,
       UINTN                               Alignment,
       UINT64                              Length,
    EFI_PHYSICAL_ADDRESS                *BaseAddress,
       EFI_HANDLE                          ImageHandle,
       EFI_HANDLE                          DeviceHandle 
  );



















typedef
EFI_STATUS
(__cdecl *EFI_FREE_MEMORY_SPACE)(
   EFI_PHYSICAL_ADDRESS  BaseAddress,
   UINT64                Length
  );






















typedef
EFI_STATUS
(__cdecl *EFI_REMOVE_MEMORY_SPACE)(
   EFI_PHYSICAL_ADDRESS  BaseAddress,
   UINT64                Length
  );













typedef
EFI_STATUS
(__cdecl *EFI_GET_MEMORY_SPACE_DESCRIPTOR)(
    EFI_PHYSICAL_ADDRESS             BaseAddress,
   EFI_GCD_MEMORY_SPACE_DESCRIPTOR  *Descriptor
  );






















typedef
EFI_STATUS
(__cdecl *EFI_SET_MEMORY_SPACE_ATTRIBUTES)(
   EFI_PHYSICAL_ADDRESS         BaseAddress,
   UINT64                       Length,
   UINT64                       Attributes
  );
















typedef
EFI_STATUS
(__cdecl *EFI_GET_MEMORY_SPACE_MAP)(
   UINTN                            *NumberOfDescriptors,
   EFI_GCD_MEMORY_SPACE_DESCRIPTOR  **MemorySpaceMap
  );

























typedef
EFI_STATUS
(__cdecl *EFI_ADD_IO_SPACE)(
   EFI_GCD_IO_TYPE       GcdIoType,
   EFI_PHYSICAL_ADDRESS  BaseAddress,
   UINT64                Length
  );

























typedef
EFI_STATUS
(__cdecl *EFI_ALLOCATE_IO_SPACE)(
       EFI_GCD_ALLOCATE_TYPE               GcdAllocateType,
       EFI_GCD_IO_TYPE                     GcdIoType,
       UINTN                               Alignment,
       UINT64                              Length,
    EFI_PHYSICAL_ADDRESS                *BaseAddress,
       EFI_HANDLE                          ImageHandle,
       EFI_HANDLE                          DeviceHandle 
  );



















typedef
EFI_STATUS
(__cdecl *EFI_FREE_IO_SPACE)(
   EFI_PHYSICAL_ADDRESS  BaseAddress,
   UINT64                Length
  );
























typedef
EFI_STATUS
(__cdecl *EFI_REMOVE_IO_SPACE)(
   EFI_PHYSICAL_ADDRESS  BaseAddress,
   UINT64                Length
  );













typedef
EFI_STATUS
(__cdecl *EFI_GET_IO_SPACE_DESCRIPTOR)(
    EFI_PHYSICAL_ADDRESS         BaseAddress,
   EFI_GCD_IO_SPACE_DESCRIPTOR  *Descriptor
  );
















typedef
EFI_STATUS
(__cdecl *EFI_GET_IO_SPACE_MAP)(
   UINTN                        *NumberOfDescriptors,
   EFI_GCD_IO_SPACE_DESCRIPTOR  **IoSpaceMap
  );



















typedef
EFI_STATUS
(__cdecl *EFI_DISPATCH)(
  void
  );












typedef
EFI_STATUS
(__cdecl *EFI_SCHEDULE)(
   EFI_HANDLE  FirmwareVolumeHandle,
   const EFI_GUID    *FileName
  );












typedef
EFI_STATUS
(__cdecl *EFI_TRUST)(
   EFI_HANDLE  FirmwareVolumeHandle,
   const EFI_GUID    *FileName
  );



















typedef
EFI_STATUS
(__cdecl *EFI_PROCESS_FIRMWARE_VOLUME)(
   const void                       *FirmwareVolumeHeader,
   UINTN                            Size,
   EFI_HANDLE                      *FirmwareVolumeHandle
  );









typedef struct {
  
  
  
  
  EFI_TABLE_HEADER                Hdr;

  
  
  
  EFI_ADD_MEMORY_SPACE            AddMemorySpace;
  EFI_ALLOCATE_MEMORY_SPACE       AllocateMemorySpace;
  EFI_FREE_MEMORY_SPACE           FreeMemorySpace;
  EFI_REMOVE_MEMORY_SPACE         RemoveMemorySpace;
  EFI_GET_MEMORY_SPACE_DESCRIPTOR GetMemorySpaceDescriptor;
  EFI_SET_MEMORY_SPACE_ATTRIBUTES SetMemorySpaceAttributes;
  EFI_GET_MEMORY_SPACE_MAP        GetMemorySpaceMap;
  EFI_ADD_IO_SPACE                AddIoSpace;
  EFI_ALLOCATE_IO_SPACE           AllocateIoSpace;
  EFI_FREE_IO_SPACE               FreeIoSpace;
  EFI_REMOVE_IO_SPACE             RemoveIoSpace;
  EFI_GET_IO_SPACE_DESCRIPTOR     GetIoSpaceDescriptor;
  EFI_GET_IO_SPACE_MAP            GetIoSpaceMap;

  
  
  
  EFI_DISPATCH                    Dispatch;
  EFI_SCHEDULE                    Schedule;
  EFI_TRUST                       Trust;
  
  
  
  EFI_PROCESS_FIRMWARE_VOLUME     ProcessFirmwareVolume;
} DXE_SERVICES;

typedef DXE_SERVICES EFI_DXE_SERVICES;










typedef
void
(__cdecl *EFI_AP_PROCEDURE)(
    void  *Buffer
  );

#line 717 "c:\\1218_alibaba\\MdePkg\\Include\\Pi/PiDxeCis.h"

#line 23 "c:\\1218_alibaba\\MdePkg\\Include\\PiDxe.h"

#line 25 "c:\\1218_alibaba\\MdePkg\\Include\\PiDxe.h"

#line 18 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\AmiCompatibilityPkg\\Library\\AmiDxeLib\\DEBUG\\AutoGen.h"

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;



extern EFI_GUID gAmiGlobalVariableGuid;






#line 32 "c:\\1218_alibaba\\Build\\GRANTLEY\\RELEASE_MYTOOLS\\X64\\AmiCompatibilityPkg\\Library\\AmiDxeLib\\DEBUG\\AutoGen.h"
#line 1 "c:\\1218_alibaba\\AmiCompatibilityPkg\\Library\\x64\\x64AsmLib\\ReadRtdsc.asm"
;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************

;*************************************************************************
; $Header: /Alaska/SOURCE/Core/Modules/x64Core/x64AsmLib/ReadRtdsc.asm 1     10/01/10 5:08p Felixp $
;
; $Revision: 1 $
;
; $Date: 10/01/10 5:08p $
;*************************************************************************
;<AMI_FHDR_START>
;
; Name:
;
; Description:
;
;<AMI_FHDR_END>
;*************************************************************************
.code

;*************************************************************************
;<AMI_PHDR_START>
;
; Name: ReadRtdsc
;
; Description:
;  UINT64 ReadRtdsc() retrieves the time stamp counter.
;
; Input:
;  void.
;
; Output:
;  UINT64 value of the time stamp counter.
;
; Modified:
;
; Referrals:
;
; Notes:
;
;<AMI_PHDR_END>
;*************************************************************************
ReadRtdsc Proc
	rdtsc
	shl rdx,32
	or rax, rdx
	ret
ReadRtdsc endp

END
;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
