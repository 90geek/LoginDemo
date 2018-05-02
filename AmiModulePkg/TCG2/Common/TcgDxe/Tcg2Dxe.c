/*++
   Module Name:

   TcgDxe.c

   Abstract:

   DXE Driver that provides TCG services

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TcgNext/Common/TcgDxe/TcgDxe20.c 2     10/09/13 6:30p Fredericko $
//
// $Revision: 2 $
//
// $Date: 10/09/13 6:30p $
//*************************************************************************
// Revision History
// ----------------
// $Log:
#include <Uefi.h>
#include "AmiTcg\TcgCommon.h"
#include <AmiTcg\TcgMisc.h>
#include <Token.h>
#include <AmiTcg\Tpm20.h>
#include <AmiTcg\TrEEProtocol.h>
#include "protocol\TpmDevice.h"
#include <Protocol\ComponentName.h>
#include <Protocol\ComponentName2.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\AcpiSupport.h>
#include "Protocol\TcgPlatformSetupPolicy.h"
#include <industrystandard\Acpi30.h>
#include <Acpi.h>
#include "../../CRB_Lib/Tpm20CRBLib.h"
#include<Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include<Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <ImageAuthentication.h>
#include <Protocol/AcpiSupport.h>
#include <Tcg2Dxe.h>
#include <Library/IoLib.h>
#include <ImageAuthentication.h>
#include <Protocol/FirmwareVolume2.h>
#include <Guid\MemoryOverwriteControl.h>
#include <Library/UefiLib.h>
#include <Protocol\Reset.h>

/*
  locates the TPM20 hob from Pei. If found we are processing TPM 20 devic
  need to install the TreeProtocol and do TPM20 binding measurements
*/
#define EFI_ACPI_TABLE_VERSION_X        (EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0 | EFI_ACPI_TABLE_VERSION_4_0)
#define EFI_ACPI_TABLE_VERSION_ALL      (EFI_ACPI_TABLE_VERSION_1_0B|EFI_ACPI_TABLE_VERSION_X)

extern EFI_GUID gInternalAcpiSupportGuid;

EFI_EVENT                   Event;
static VOID                 *reg;

#define     MAX_LOG_AREA_SIZE (32 * 1024) // 32KB

static EFI_PHYSICAL_ADDRESS TreeEventLogLocation;
static EFI_PHYSICAL_ADDRESS LastEntry = 0;
static EFI_PHYSICAL_ADDRESS LastEventPtr = 0;
static EFI_TPM_DEVICE_PROTOCOL *TpmDevice=NULL;
Tpm20DeviceHob  *TpmSupport = NULL;
static BOOLEAN  IEventLogTruncated = FALSE;
static BOOLEAN  ReadyToBootSignaled=FALSE;
static EFI_PHYSICAL_ADDRESS TreeExtraTCPASha1LogLoc;

BOOLEAN IsTpm20Device();
EFI_STATUS TcgLibGetDsdt(EFI_PHYSICAL_ADDRESS *DsdtAddr, EFI_ACPI_TABLE_VERSION Version);
EFI_STATUS TcgUpdateAslNameObject(ACPI_HDR *PDsdt, UINT8 *ObjName, UINT64 Value);
BOOLEAN IsPTP();

#define EFI_TCG_PLATFORM_PROTOCOL_GUID  \
  { 0x8c4c9a41, 0xbf56, 0x4627, 0x9e, 0xa, 0xc8, 0x38, 0x6d, 0x66, 0x11, 0x5c }

#define AMI_VALID_BOOT_IMAGE_CERT_TBL_GUID \
    { 0x6683D10C, 0xCF6E, 0x4914, 0xB5, 0xB4, 0xAB, 0x8E, 0xD7, 0x37, 0x0E, 0xD7 }

EFI_GUID gEfiImageSecurityDatabaseguid =  EFI_IMAGE_SECURITY_DATABASE_GUID;
EFI_HANDLE PlatformProtocolHandle;

UINT32                  ActiveBankBitMap=0;
UINT32                  TcgSupportedBankBitMap=0;

//
//
// Data Table definition
//
typedef struct _AMI_VALID_CERT_IN_SIG_DB {
  UINT32          SigOffset;
  UINT32          SigLength;
} AMI_VALID_CERT_IN_SIG_DB;

EFI_TREE_PROTOCOL                 *TrEEProtocolInstance = NULL;

typedef
EFI_STATUS
(EFIAPI *EFI_TCG_MEASURE_PE_IMAGE) (
  IN      BOOLEAN                   BootPolicy,
  IN      EFI_PHYSICAL_ADDRESS      ImageAddress,
  IN      UINTN                     ImageSize,
  IN      UINTN                     LinkTimeBase,
  IN      UINT16                    ImageType,
  IN      EFI_HANDLE                DeviceHandle,
  IN      EFI_DEVICE_PATH_PROTOCOL  *FilePath
  );

typedef
EFI_STATUS
(EFIAPI *EFI_TCG_MEASURE_ACTION) (
  IN      CHAR8                     *ActionString
  );

typedef
EFI_STATUS
(EFIAPI *EFI_TCG_MEASURE_GPT_TABLE) (
  IN      EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );

typedef struct _EFI_TCG_PLATFORM_PROTOCOL {
  EFI_TCG_MEASURE_PE_IMAGE          MeasurePeImage;
  EFI_TCG_MEASURE_ACTION            MeasureAction;
  EFI_TCG_MEASURE_GPT_TABLE         MeasureGptTable;
} EFI_TCG_PLATFORM_PROTOCOL;



EFI_STATUS
__stdcall
TpmLibPassThrough (
  IN      TPM_1_2_REGISTERS_PTR     TpmReg,
  IN      UINTN                     NoInputBuffers,
  IN      TPM_TRANSMIT_BUFFER       *InputBuffers,
  IN      UINTN                     NoOutputBuffers,
  IN OUT  TPM_TRANSMIT_BUFFER       *OutputBuffers
  );

EFI_STATUS
__stdcall
TisRequestLocality (
  IN      TPM_1_2_REGISTERS_PTR     TpmReg
  );

EFI_STATUS
__stdcall
TisReleaseLocality (
  IN      TPM_1_2_REGISTERS_PTR     TpmReg
  );


EFI_STATUS
TreeSubmitCommand (
IN  EFI_TREE_PROTOCOL   *This,
IN  UINT32              InputParameterBlockSize,
IN  UINT8               *InputParameterBlock,
IN  UINT32              OutputParameterBlockSize,
IN  UINT8               *OutputParameterBlock
  );

static UINT16   *gDriverName=L"TPM Driver";
static BOOLEAN   Tpm20FwDevice = FALSE;


void printbuffer(UINT8 *Buffer, UINTN BufferSize)
{
    UINTN i=0; UINTN j=0;
    
    DEBUG((-1,"\n**********PrintBuffer Entry********"));
    
    for(i=0; i<BufferSize; i++){
        
        if(i%16 == 0){
            DEBUG((-1,"\n"));
            DEBUG((-1,"%04x :", j));
            j+=1;
        }

        DEBUG((-1,"%02x ", Buffer[i]));
    }
    DEBUG((-1,"\n"));
}


UINT8  GetHashPolicy()
{
    TCG_PLATFORM_SETUP_PROTOCOL     *ProtocolInstance;
    EFI_STATUS                      Status;
    EFI_GUID                        Policyguid = TCG_PLATFORM_SETUP_POLICY_GUID;

   Status = gBS->LocateProtocol (&Policyguid,  NULL, &ProtocolInstance);
   if (EFI_ERROR (Status)) {
      return 0;
   }
   
   return(ProtocolInstance->ConfigFlags.HashPolicy);
}

BOOLEAN IsTpm20Device()
{
   EFI_GUID gTpm20Supporthobguid = TPM20_HOB_GUID;
   
   TpmSupport = LocateATcgHob( gST->NumberOfTableEntries,
                  gST->ConfigurationTable,
                  &gTpm20Supporthobguid);

   if(TpmSupport != NULL){
      if(TpmSupport->Tpm20DeviceState == 1){
           return TRUE;
      }
   }  
      
   return FALSE;
}


EFI_STATUS
__stdcall TcgCommonPassThrough(
    IN VOID                    *Context,
    IN UINT32                  NoInputBuffers,
    IN TPM_TRANSMIT_BUFFER     *InputBuffers,
    IN UINT32                  NoOutputBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutputBuffers )
{
    return EFI_UNSUPPORTED;

}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcmCommonPassThrough
//
// Description: Helper function for TCM transmit command
//
// Input:       VOID *Context
//              UINT32 NoInputBuffers
//              TPM_TRANSMIT_BUFFER InputBuffers
//              UINT32 NoOutputBuffers
//              TPM_TRANSMIT_BUFFER OutputBuffers
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:   
//
// Notes:       
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
__stdcall TcmCommonPassThrough(
    IN VOID                    *Context,
    IN UINT32                  NoInputBuffers,
    IN TPM_TRANSMIT_BUFFER     *InputBuffers,
    IN UINT32                  NoOutputBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutputBuffers )
{
    return EFI_UNSUPPORTED;
}



UINT8  GetInterfacePolicy()
{
    TCG_PLATFORM_SETUP_PROTOCOL     *ProtocolInstance;
    EFI_STATUS                      Status;
    EFI_GUID                        Policyguid = TCG_PLATFORM_SETUP_POLICY_GUID;

   Status = gBS->LocateProtocol (&Policyguid,  NULL, &ProtocolInstance);
   if (EFI_ERROR (Status)) {
      return 0;
   }

   return(ProtocolInstance->ConfigFlags.InterfaceSel);
}

EFI_STATUS
EFIAPI
Tpm2GetCapability (
  IN      TPM_CAP                   Capability,
  IN      UINT32                    Property,
  IN      UINT32                    PropertyCount,
  OUT     TPMI_YES_NO               *MoreData,
  OUT     TPMS_CAPABILITY_DATA      *CapabilityData
  )
{
  EFI_STATUS                        Status;
  TPM2_GET_CAPABILITY_COMMAND       SendBuffer;
  TPM2_GET_CAPABILITY_RESPONSE      RecvBuffer;
  UINT32                            SendBufferSize;
  UINT32                            RecvBufferSize;
  EFI_TREE_PROTOCOL                 *pTreeProtocol  =  NULL;
  EFI_GUID  gEfiTrEEProtocolGuid =  EFI_TREE_PROTOCOL_GUID;

  Status = gBS->LocateProtocol(
                  &gEfiTrEEProtocolGuid,
                  NULL,
                  &pTreeProtocol);

  if(EFI_ERROR(Status))return Status;

  //
  // Construct command
  //
  SendBuffer.Header.tag = SwapBytes16(TPM_ST_NO_SESSIONS);
  SendBuffer.Header.commandCode = SwapBytes32(TPM_CC_GetCapability);

  SendBuffer.Capability = SwapBytes32 (Capability);
  SendBuffer.Property = SwapBytes32 (Property);
  SendBuffer.PropertyCount = SwapBytes32 (PropertyCount);
 
  SendBufferSize = (UINT32) sizeof (SendBuffer);
  SendBuffer.Header.paramSize = SwapBytes32 (SendBufferSize);
    
  //
  // send Tpm command
  //
  RecvBufferSize = sizeof (RecvBuffer);
  Status = TreeSubmitCommand (pTreeProtocol, SendBufferSize, (UINT8 *)&SendBuffer, RecvBufferSize, (UINT8 *)&RecvBuffer );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (RecvBufferSize <= sizeof (TPM2_RESPONSE_HEADER) + sizeof (UINT8)) {
    return EFI_DEVICE_ERROR;
  }

  //
  if (SwapBytes32(RecvBuffer.Header.responseCode) != TPM_RC_SUCCESS) {
    DEBUG((-1, "Tpm2GetCapability: Response Code error! 0x%08x\r\n", SwapBytes32(RecvBuffer.Header.responseCode)));
    return EFI_DEVICE_ERROR;
  }
  // Return the response
  //
  *MoreData = RecvBuffer.MoreData;
  //
  // Does not unpack all possiable property here, the caller should unpack it and note the byte order.
  //
  gBS->CopyMem (CapabilityData, &RecvBuffer.CapabilityData, RecvBufferSize - sizeof (TPM2_RESPONSE_HEADER) - sizeof (UINT8));
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm2GetCapabilityManufactureID (
  OUT     UINT32                    *ManufactureId
  )
{
  TPMS_CAPABILITY_DATA    TpmCap;
  TPMI_YES_NO             MoreData;
  EFI_STATUS              Status; 

  Status = Tpm2GetCapability (
             TPM_CAP_TPM_PROPERTIES, 
             TPM_PT_MANUFACTURER, 
             1, 
             &MoreData, 
             &TpmCap
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  *ManufactureId = SwapBytes32 (TpmCap.data.tpmProperties.tpmProperty->value);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm2GetCapabilityMaxCommandResponseSize (
  OUT UINT32                    *MaxCommandSize,
  OUT UINT32                    *MaxResponseSize
  )
{
  TPMS_CAPABILITY_DATA    TpmCap;
  TPMI_YES_NO             MoreData;
  EFI_STATUS              Status;

  Status = Tpm2GetCapability (
             TPM_CAP_TPM_PROPERTIES, 
             TPM_PT_MAX_COMMAND_SIZE, 
             1, 
             &MoreData, 
             &TpmCap
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  *MaxCommandSize = SwapBytes32 (TpmCap.data.tpmProperties.tpmProperty->value);

  Status = Tpm2GetCapability (
             TPM_CAP_TPM_PROPERTIES, 
             TPM_PT_MAX_RESPONSE_SIZE, 
             1, 
             &MoreData, 
             &TpmCap
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  *MaxResponseSize = SwapBytes32(TpmCap.data.tpmProperties.tpmProperty->value);
  return EFI_SUCCESS; 
}


EFI_STATUS
EFIAPI
Tpm2GetCapabilitySupportedAlg (
  OUT TPML_ALG_PROPERTY      *AlgList
  )
{
  TPMS_CAPABILITY_DATA    TpmCap;
  TPMI_YES_NO             MoreData;
  UINTN                   Index;
  EFI_STATUS              Status;
 
  Status = Tpm2GetCapability (
             TPM_CAP_ALGS, 
             1, 
             MAX_CAP_ALGS, 
             &MoreData, 
             &TpmCap
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  gBS->CopyMem (AlgList, &TpmCap.data.algorithms, sizeof (TPML_ALG_PROPERTY));

  AlgList->count = SwapBytes32 (AlgList->count);
  for (Index = 0; Index < AlgList->count; Index++) {
    AlgList->algProperties[Index].alg = SwapBytes16 (AlgList->algProperties[Index].alg);
    *(UINT32 *)&AlgList->algProperties[Index].algProperties = SwapBytes32 (*(UINT32 *)&AlgList->algProperties[Index].algProperties);
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm20ComponentNameGetDriverName (
  IN  EFI_COMPONENT_NAME_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  )
{
    //Supports only English
	if(!Language || !DriverName) return EFI_INVALID_PARAMETER;

	if (AsciiStriCmp( Language, "en-US"))
	    return EFI_UNSUPPORTED;
	else 
            *DriverName=gDriverName;
	
	return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm20ComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
Tpm20ComponentNameGetDriverName2 (
  IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  )
{
    //Supports only English
	if(!Language || !DriverName) return EFI_INVALID_PARAMETER;
//LANGUAGE_CODE_ENGLISH
	if (AsciiStriCmp( Language, "en-US"))
	    return EFI_UNSUPPORTED;
	else 
	    *DriverName=gDriverName;
	
	return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm20ComponentNameGetControllerName2 (
  IN  EFI_COMPONENT_NAME2_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  )
{
  return EFI_UNSUPPORTED;
}


static EFI_COMPONENT_NAME_PROTOCOL gComponentName = {
  Tpm20ComponentNameGetDriverName,
  Tpm20ComponentNameGetControllerName,
  "en-US"
};


static EFI_COMPONENT_NAME2_PROTOCOL gComponentName2 = {
  Tpm20ComponentNameGetDriverName2,
  Tpm20ComponentNameGetControllerName2,
  "en-US"
};


EFI_STATUS
EFIAPI
Tpm20DriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath   OPTIONAL
  )
{
  EFI_STATUS          Status      =  EFI_SUCCESS;
  static BOOLEAN      Initialized = FALSE;

  if(Initialized == FALSE){
        Initialized = TRUE;
    if(IsTpm20Device()){
        return EFI_SUCCESS;
    }else if(Tpm20FwDevice)return EFI_SUCCESS;
  }
 
  return EFI_UNSUPPORTED;
}


EFI_STATUS
EFIAPI
Tpm20DriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath   OPTIONAL
  )
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm20DriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
  IN  EFI_HANDLE                      Controller,
  IN  UINTN                           NumberOfChildren,
  IN  EFI_HANDLE                      *ChildHandleBuffer   OPTIONAL
  )
{
	return EFI_UNSUPPORTED;
}

EFI_DRIVER_BINDING_PROTOCOL Tpm20DriverBinding = {
  Tpm20DriverBindingSupported,
  Tpm20DriverBindingStart,
  Tpm20DriverBindingStop,
  0xa,
  NULL,
  NULL
};


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   OverwriteSystemMemory
//
// Description: Overwrites system memory
//
// Input:      
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS OverwriteSystemMemory(
)
{

  EFI_STATUS                           Status;
  UINT8                                TmpMemoryMap[1];
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  UINTN                                MemoryMapSize;
  EFI_MEMORY_DESCRIPTOR                *MemoryMap;
  EFI_MEMORY_DESCRIPTOR                *MemoryMapPtr;
  UINTN                                Index;
  UINT64                                Size;

  //
  // Get System MemoryMapSize
  //
  MemoryMapSize = 1;
  Status = gBS->GetMemoryMap (
                  &MemoryMapSize,
                  (EFI_MEMORY_DESCRIPTOR *)TmpMemoryMap,
                  &MapKey,
                  &DescriptorSize,
                  &DescriptorVersion
                  );
  ASSERT (Status == EFI_BUFFER_TOO_SMALL);
  //
  // Enlarge space here, because we will allocate pool now.
  //
  MemoryMapSize += EFI_PAGE_SIZE;
  Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  MemoryMapSize,
                  (VOID**)&MemoryMap
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Get System MemoryMap
  //
  Status = gBS->GetMemoryMap (
                  &MemoryMapSize,
                  MemoryMap,
                  &MapKey,
                  &DescriptorSize,
                  &DescriptorVersion
                  );
  ASSERT_EFI_ERROR (Status);

  MemoryMapPtr = MemoryMap;
  //
  // Search the request Address
  //
  for (Index = 0; Index < (MemoryMapSize / DescriptorSize); Index++) {
      switch (MemoryMap->Type){
            case EfiMemoryMappedIO:
            case EfiReservedMemoryType:
            case EfiRuntimeServicesCode:
            case EfiRuntimeServicesData:
            case EfiUnusableMemory:
            case EfiMemoryMappedIOPortSpace:
            case EfiPalCode:
            case EfiACPIReclaimMemory:
            case EfiACPIMemoryNVS:
            case EfiBootServicesCode:
            case EfiBootServicesData:
            case EfiLoaderCode:
            case EfiLoaderData:
            case EfiMaxMemoryType:
              	Size = MemoryMap->NumberOfPages <<  EFI_PAGE_SHIFT; 
        	DEBUG((-1,"MOR: Start = %x Len = %x", MemoryMap->PhysicalStart, Size));
        	DEBUG((-1," Left Alone \n"));
                break;
            default: 
               	Size = MemoryMap->NumberOfPages <<  EFI_PAGE_SHIFT; 
            	DEBUG((-1,"MOR: Start = %x Len = %x", MemoryMap->PhysicalStart, Size));
       	        DEBUG((-1," Cleaned \n"));
               Size = MemoryMap->NumberOfPages <<  EFI_PAGE_SHIFT; 
               SetMem((VOID*)MemoryMap->PhysicalStart, (UINTN)Size, 0);
        }
    MemoryMap = (EFI_MEMORY_DESCRIPTOR *)((UINTN)MemoryMap + DescriptorSize);
  }

  //
  // Done
  //
  gBS->FreePool (MemoryMapPtr);

  return Status;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ReadMORValue
//
// Description: Reads TCG MOR variable
//
// Input:       IN  EFI_PEI_SERVICES  **PeiServices,
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID ReadMORValue( )
{
    CHAR16     UefiMor[]   = L"MemoryOverwriteRequestControl";
    EFI_GUID   MorUefiGuid = MEMORY_ONLY_RESET_CONTROL_GUID;
    UINT8      mor         = 0;
    UINTN      size        = sizeof(mor);
    EFI_STATUS Status;

   
    Status = gRT->GetVariable( UefiMor, &MorUefiGuid,
                               NULL, &size, &mor );

    if(EFI_ERROR(Status))return;

    if ( (mor & 1)!=0 )
    {

        //clear memory
        DEBUG((-1,"MOR: before Clear memory"));
        Status = OverwriteSystemMemory();
        DEBUG((-1,"MOR: After Clear memory"));
	}	
}


EFI_STATUS
EFIAPI
Tpm2GetCapabilityCapPCRS ()
{
  TPMS_CAPABILITY_DATA    TpmCap;
  TPMI_YES_NO             MoreData;
  EFI_STATUS              Status;
  TPMS_PCR_SELECTION      *PcrSelect;
  UINT8                   *Buffer;
  UINTN                   size = 0, i=0, j=0;
  UINT32                  SupportedBankBitMap=0;
  EFI_GUID                gTcgInternalflagGuid = TCG_INTERNAL_FLAGS_GUID;
  AMITCGSETUPINFOFLAGS    Info;
  UINT16                  hash;
  
  SupportedBankBitMap = 0;
    
  Status  = Tpm2GetCapability (
             TPM_CAP_PCRS, 
             0, 
             MAX_PCR_PROPERTIES, 
             &MoreData, 
             &TpmCap);

  if(EFI_ERROR(Status)){
      Info.SupportedPcrBitMap = 1;
      Info.ActivePcrBitMap  = 1;
      Info.Reserved = 0;
      
      DEBUG(( -1," SupportedPcrBitMap = %x \n", Info.SupportedPcrBitMap));
      DEBUG(( -1," ActivePcrBitMap = %x \n", Info.ActivePcrBitMap));
      
      Status = gRT->SetVariable( L"PCRBitmap", \
                        &gTcgInternalflagGuid, \
                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, \
                         sizeof(AMITCGSETUPINFOFLAGS), \
                         &Info); 
      return Status;
  }

  printbuffer((UINT8 *)&TpmCap, 0x30);
  
  Buffer = (UINT8 *)&TpmCap;
  PcrSelect = (TPMS_PCR_SELECTION *)(Buffer + (sizeof(UINT32)*2));
  size = SwapBytes32(*(UINT32 *)(Buffer + sizeof(UINT32)));
  
  DEBUG(( -1," size = %x \n", size));

  //ActiveBankBitMap
  for(i=0; i<size; i++,PcrSelect++){
      
      printbuffer((UINT8 *)PcrSelect, 0x30);
      DEBUG(( -1," PcrSelect->hash = %x \n", PcrSelect->hash));
      DEBUG(( -1," PcrSelect->sizeofSelect = %x \n", PcrSelect->sizeofSelect));
      hash = SwapBytes16(PcrSelect->hash);
      switch(hash){
          case 0x4:
              SupportedBankBitMap |= 1;
              for(j=0; j<PcrSelect->sizeofSelect; j++){
                  if(PcrSelect->pcrSelect[j] ==0)continue;
                  else{ActiveBankBitMap |= 1;break;}
              }
              break;
          case 0xB:
              SupportedBankBitMap |= 2;
              for(j=0; j<PcrSelect->sizeofSelect; j++){
                 if(PcrSelect->pcrSelect[j] ==0)continue;
                  else{ActiveBankBitMap |= 2;break;}
               }
              break;
          case 0xC:
              SupportedBankBitMap |= 4;
              for(j=0; j<PcrSelect->sizeofSelect; j++){
                  if(PcrSelect->pcrSelect[j] ==0)continue;
                  else{ActiveBankBitMap |= 4;break;}
              }              
              break;
          case 0xD:
              SupportedBankBitMap |= 8;
              for(j=0; j<PcrSelect->sizeofSelect; j++){
                 if(PcrSelect->pcrSelect[j] ==0)continue;
                 else{ ActiveBankBitMap |= 4;break; }
              }
              break;
          case 0x12:
              for(j=0; j<PcrSelect->sizeofSelect; j++){
                   if(PcrSelect->pcrSelect[j] ==0)continue;
                   else {ActiveBankBitMap |= 0x10;break;}
              }
              SupportedBankBitMap |= 0x10;
              break;
      }
  }
  
  TcgSupportedBankBitMap = SupportedBankBitMap;
  Info.SupportedPcrBitMap = SupportedBankBitMap;
  Info.ActivePcrBitMap  = ActiveBankBitMap;
  Info.Reserved = 0;
  
  DEBUG(( -1," SupportedPcrBitMap = %x \n", Info.SupportedPcrBitMap));
  DEBUG(( -1," ActivePcrBitMap = %x \n", Info.ActivePcrBitMap));
  
  Status = gRT->SetVariable( L"PCRBitmap", \
                   &gTcgInternalflagGuid, \
                   EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, \
                   sizeof(AMITCGSETUPINFOFLAGS), \
                   &Info); 
  
  return Status;
}


EFI_STATUS 
DoResetNow(
    IN EFI_EVENT ev,
    IN VOID      *ctx )
{    
    gRT->ResetSystem( EfiResetCold, 0, 0, NULL );
    DEBUG((-1, "\tError: Reset failed???\n"));
    return EFI_SUCCESS;
}


EFI_STATUS Tpm2AllocatePCR(UINT32 RequestedBank, UINT32 ActivePCRBanks, UINT32 Supported)
{
    EFI_STATUS                 Status;
    TPM2_ALLOCATE_PCR_COMMAND  Tpm2Alloccmd;
    TPM2_ALLOCATE_PCR_RESPONSE Tpm2AllocResponse;
    UINT8                      *Buffer;
    UINT32                     *AuthsizeOffset;
    TPML_PCR_SELECTION         pcrAllocation;
    UINT32                     CmdSize = 0;
    UINT32                     RecvBufferSize=0;
    EFI_TREE_PROTOCOL                 *pTreeProtocol  =  NULL;
    EFI_GUID  gEfiTrEEProtocolGuid =  EFI_TREE_PROTOCOL_GUID;
    TPMI_YES_NO                *AllocPass;
    UINT8                       i=0, Count=0;
    UINT32                      PcrBanks=0;
    

    Status = gBS->LocateProtocol(
                     &gEfiTrEEProtocolGuid,
                     NULL,
                     &pTreeProtocol);

    if(EFI_ERROR(Status))return Status;
    
    gBS->SetMem(&Tpm2Alloccmd, sizeof(TPM2_ALLOCATE_PCR_COMMAND), 0);
    gBS->SetMem(&Tpm2AllocResponse, sizeof(TPM2_ALLOCATE_PCR_RESPONSE), 0);
    
    
    Tpm2Alloccmd.Header.tag          = SwapBytes16(TPM_ST_SESSIONS);
    Tpm2Alloccmd.Header.paramSize    = SwapBytes32(sizeof(TPM2_ALLOCATE_PCR_COMMAND));
    Tpm2Alloccmd.Header.commandCode  = SwapBytes32(TPM_CC_PCR_Allocate);
    Tpm2Alloccmd.Authhandle          = SwapBytes32(TPM_RH_PLATFORM);
    
    Buffer = (UINT8 *)&Tpm2Alloccmd.AuthorizationSize;
    AuthsizeOffset = (UINT32 *)Buffer;
    
    //set AuthorizationSize to 0
    *(UINT32 *)Buffer = 0;
    Buffer += sizeof(UINT32);
    
    //init authSessionHandle
    *(UINT32 *)Buffer = SwapBytes32(TPM_RS_PW);
    Buffer += sizeof(UINT32);
    
    //use nullNonce
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    //sessionAttributes should be zero
    *(UINT8 *)Buffer = 0;
    Buffer += sizeof(UINT8);

    //use = nullAuth
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);
    
    PcrBanks = Supported & RequestedBank;
    while(PcrBanks > 0)
    {
        if(PcrBanks & 1)Count+=1;
        PcrBanks = PcrBanks>>1;
    }
    
    PcrBanks = ActivePCRBanks & ~RequestedBank;
    while(PcrBanks > 0)
    {
        if(PcrBanks & 1)Count+=1;
        PcrBanks = PcrBanks>>1;
    }
    
    DEBUG((-1," Tpm2AllocatePCR:: Count = %x \n", Count));
    
    if(Count > 3)Count=3;
    pcrAllocation.count = SwapBytes32(Count);
    
    *AuthsizeOffset = SwapBytes32((UINT32)(Buffer - (UINT8 *)AuthsizeOffset - sizeof(UINT32)));
    
    DEBUG((-1," Tpm2AllocatePCR::Supported = %x \n", Supported));
    DEBUG((-1," Tpm2AllocatePCR::RequestedBank = %x \n", RequestedBank));
    DEBUG((-1," Tpm2AllocatePCR::ActivePCRBanks = %x \n", ActivePCRBanks));

    if(((Supported & TREE_BOOT_HASH_ALG_SHA1)!=0) && \
            (RequestedBank & TREE_BOOT_HASH_ALG_SHA1) == TREE_BOOT_HASH_ALG_SHA1){
        
        DEBUG((-1," Tpm2AllocatePCR::Allocate Sha-1 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SHA1);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0xFF);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }
    
    if((Supported & TREE_BOOT_HASH_ALG_SHA256) && \
                   (RequestedBank & TREE_BOOT_HASH_ALG_SHA256) == TREE_BOOT_HASH_ALG_SHA256 && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::Allocate Sha-2 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SHA256);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0xFF);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }
    
    if(((Supported & TREE_BOOT_HASH_ALG_SHA384)!=0) && \
                   (RequestedBank & TREE_BOOT_HASH_ALG_SHA384) == TREE_BOOT_HASH_ALG_SHA384 && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::Allocate Sha-3 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SHA384);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0xFF);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;

    }
    
    if(((Supported & TREE_BOOT_HASH_ALG_SHA512)!=0) && \
                   (RequestedBank & TREE_BOOT_HASH_ALG_SHA512) == TREE_BOOT_HASH_ALG_SHA512 && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::Allocate Sha-512 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SHA512);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0xFF);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }
    
    
    if(((Supported & TREE_BOOT_HASH_ALG_SM3)!=0) && \
                   (RequestedBank & TREE_BOOT_HASH_ALG_SM3) == TREE_BOOT_HASH_ALG_SM3 && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::Allocate SM3 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SM3_256);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0xFF);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0xFF);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }
    
    
    if(((ActivePCRBanks & TREE_BOOT_HASH_ALG_SHA1)!=0) && \
                   ((RequestedBank & TREE_BOOT_HASH_ALG_SHA1) == 0) && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::deAllocate Sha-1 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SHA1);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0x0);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }
    
    if(((ActivePCRBanks & TREE_BOOT_HASH_ALG_SHA256)!=0) && \
                   ((RequestedBank & TREE_BOOT_HASH_ALG_SHA256) == 0) && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::deAllocate Sha-2 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SHA256);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0x0);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }
    
    
    if(((ActivePCRBanks & TREE_BOOT_HASH_ALG_SHA384)!=0) && \
                   ((RequestedBank & TREE_BOOT_HASH_ALG_SHA384) == 0) && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::deAllocate Sha-3 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SHA384);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0x0);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }
    
    
    if(((ActivePCRBanks & TREE_BOOT_HASH_ALG_SHA512)!=0) && \
                   ((RequestedBank & TREE_BOOT_HASH_ALG_SHA512) == 0) && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::deAllocate Sha-512 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SHA512);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0x0);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }
    
    if(((ActivePCRBanks & TREE_BOOT_HASH_ALG_SM3)!=0) && \
                   ((RequestedBank & TREE_BOOT_HASH_ALG_SM3) == 0) && i < 3){
        DEBUG((-1," Tpm2AllocatePCR::deAllocate SM3 \n", Count));
        pcrAllocation.pcrSelections[i].hash = SwapBytes16(TPM2_ALG_SM3_256);
        pcrAllocation.pcrSelections[i].pcrSelect[0] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[1] = (0x0);
        pcrAllocation.pcrSelections[i].pcrSelect[2] = (0x0);
        pcrAllocation.pcrSelections[i].sizeofSelect = 3;
        i+=1;
    }

    
    CopyMem(Buffer, &pcrAllocation.count, sizeof(UINT32));
    Buffer+= sizeof(UINT32);    
    CopyMem(Buffer, &pcrAllocation.pcrSelections[0].hash, sizeof(TPMS_PCR_SELECTION)*i);
    Buffer+=(sizeof(TPMS_PCR_SELECTION)*i);
    
    CmdSize = (UINT32)(Buffer - (UINT8 *)&Tpm2Alloccmd);
    Tpm2Alloccmd.Header.paramSize = SwapBytes32(CmdSize);
     
    printbuffer((UINT8 *)&Tpm2Alloccmd, CmdSize);
    
    
    //DEBUG((-1," Tpm2AllocatePCR:: Recv Size = %x \n", sizeof(TPM2_ALLOCATE_PCR_RESPONSE)));
    
    //send command
    Status = TreeSubmitCommand (pTreeProtocol, CmdSize, (UINT8 *)&Tpm2Alloccmd, sizeof(TPM2_ALLOCATE_PCR_RESPONSE), (UINT8 *)&Tpm2AllocResponse );
    if (EFI_ERROR (Status)) {
       DEBUG((-1," Tpm2AllocatePCR:: TreeSubmitCommand returned error \n"));
       return Status;
    }
    
    RecvBufferSize = SwapBytes32(Tpm2AllocResponse.Header.paramSize);

    //printbuffer((UINT8 *)&Tpm2AllocResponse, RecvBufferSize);
    
    DEBUG((-1," Tpm2AllocatePCR:: RecvBufferSize = %x \n", RecvBufferSize));
    
    if(SwapBytes32(Tpm2AllocResponse.Header.responseCode)){
        DEBUG((-1," Tpm2AllocResponse.Header.responseCode = %x \n", SwapBytes32(Tpm2AllocResponse.Header.responseCode)));
        return EFI_DEVICE_ERROR;
    }
    
    if (RecvBufferSize <= sizeof (TPM2_RESPONSE_HEADER) + sizeof (UINT8)) {
      DEBUG((-1," Tpm2AllocatePCR:: RecvBufferSize <= sizeof (TPM2_RESPONSE_HEADER) + sizeof (UINT8) \n"));
      return EFI_DEVICE_ERROR;
    }
    
    AllocPass = (TPMI_YES_NO *)&Tpm2AllocResponse;
    AllocPass += (sizeof(TPM2_COMMAND_HEADER) + sizeof(UINT32));
        
    if(*AllocPass != 1){
      DEBUG((-1," Tpm2AllocatePCR:: TPM Alloca failed \n"));
      return EFI_DEVICE_ERROR;
    }
       
    DEBUG((-1," Tpm2AllocatePCR:: Allocation success \n"));
    return EFI_SUCCESS;
}


EFI_STATUS 
   EfiTreeGetActivePcrs(
   EFI_TREE_PROTOCOL    *This,
   UINT32               *ActivatePcrBanks
)
{
    *ActivatePcrBanks = ActiveBankBitMap;
    return EFI_SUCCESS;
}

//TODO::TREE PROTOCOL Spec has to be updated
EFI_STATUS 
   EfiTreeSetActivePcrs(
    EFI_TREE_PROTOCOL    *This,
    UINT32               ActivatePcrBanks
)
{
    UINT8       HashAlg=GetHashPolicy();
    EFI_STATUS  Status = EFI_SUCCESS;
    TCG_PLATFORM_SETUP_PROTOCOL     *PolicyInstance;
    EFI_GUID            gPolicyguid = TCG_PLATFORM_SETUP_POLICY_GUID;
    TCG_CONFIGURATION   Config;

    DEBUG(( -1, "[%d]: Enter EFI_TREE_SET_ACTIVE_PCRS_BANKS(...)\n", __LINE__));
    DEBUG(( -1, "ActivatePcrBanks[%x]\n", ActivatePcrBanks));

    if(ActivatePcrBanks == ActiveBankBitMap){
        return Status;
    }
    else if(ActivatePcrBanks & TcgSupportedBankBitMap){
        if(((ActivatePcrBanks & 1) == 1) || ((ActivatePcrBanks & 2) == 2)) //SHA-1 & SHA256..Need to consider SM3 next
        {
            Status = gBS->LocateProtocol (&gPolicyguid,  NULL, &PolicyInstance);
            if (EFI_ERROR (Status)) {
                return Status;
            }

            gBS-> CopyMem(&Config, &PolicyInstance->ConfigFlags, sizeof(TCG_CONFIGURATION));
            Config.HashPolicy = ActivatePcrBanks;
            
            PolicyInstance->UpdateStatusFlags(&Config, FALSE);
            return Status;
        }
    }

	return EFI_INVALID_PARAMETER;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TreeGetCapability
//
// Description: Get Tree Capability
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
TreeGetCapability (
  IN EFI_TREE_PROTOCOL                *This,
  IN OUT TREE_BOOT_SERVICE_CAPABILITY *ProtocolCapability
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINT8       HashAlg = GetHashPolicy();
  static UINT32 ManufactureID = 0xFFFFFFFF;
  static UINT32 MaxResponseSize = 0xFFFFFFFF;
  static UINT32 MaxCommandSize  = 0xFFFFFFFF;
  TPML_ALG_PROPERTY  AlgList;
  	  	 UINTN  			i	=0;
  
  TPM_CRB_ACCESS_REG_PTR dCrbAccessRegPtr = (TPM_CRB_ACCESS_REG_PTR)(( UINTN ) (PORT_TPM_IOMEMBASE));
 
  if((ProtocolCapability == NULL) || (This == NULL)){
    Status = EFI_INVALID_PARAMETER;
  }
  else {

    if(ManufactureID == 0xFFFFFFFF && MaxResponseSize == 0xFFFFFFFF && MaxCommandSize ==0xFFFFFFFF)
    {
        Status = Tpm2GetCapabilityManufactureID (&ManufactureID);
        if(EFI_ERROR(Status)){
            ManufactureID=0x0;
            Status = EFI_SUCCESS;
        }

        Status = Tpm2GetCapabilityMaxCommandResponseSize (&MaxCommandSize, &MaxResponseSize);
        if(EFI_ERROR(Status) && !IsPTP()){
            MaxCommandSize = 0x800;
            MaxResponseSize = 0x800;
            Status = EFI_SUCCESS;
        }
        
        if(MaxCommandSize == 0 || MaxResponseSize == 0){
            if(IsPTP())
            {
                MaxCommandSize = dCrbAccessRegPtr->TpmCrbCtrlCmdSize;
                MaxResponseSize = dCrbAccessRegPtr->TpmCrbCtrlRespSize;
                ManufactureID = dCrbAccessRegPtr->TpmCrbIntfId[1];
            }
        }

    }

    if(ProtocolCapability->Size < (sizeof(UINT8) + sizeof(TREE_VERSION) + sizeof(TREE_VERSION))){
      ProtocolCapability->Size = sizeof(*ProtocolCapability);
      Status = EFI_BUFFER_TOO_SMALL;
    }    
    else {
      ProtocolCapability->StructureVersion.Major = TREE_STRUCTURE_VER_MAJOR;
      ProtocolCapability->StructureVersion.Minor = TREE_STRUCTURE_VER_MINOR;
      ProtocolCapability->ProtocolVersion.Major  = TREE_PROTOCOL_MAJOR;
      ProtocolCapability->ProtocolVersion.Minor  = TREE_PROTOCOL_MINOR;

      if (ProtocolCapability->Size < sizeof(TREE_BOOT_SERVICE_CAPABILITY)){
        ProtocolCapability->Size = sizeof(TREE_BOOT_SERVICE_CAPABILITY);
        Status = EFI_BUFFER_TOO_SMALL;
      }
      else {
    	Status = Tpm2GetCapabilitySupportedAlg(&AlgList);
    	ProtocolCapability->HashAlgorithmBitmap = TREE_BOOT_HASH_ALG_SHA1;
    	if(!EFI_ERROR(Status)){    	
	    for(; i<AlgList.count; i++)
	    {
		if(AlgList.algProperties[i].alg == TPM2_ALG_SHA1 ){
		   ProtocolCapability->HashAlgorithmBitmap |= TREE_BOOT_HASH_ALG_SHA1;    			
		}
		
		if(AlgList.algProperties[i].alg == TPM2_ALG_SHA256){
		   ProtocolCapability->HashAlgorithmBitmap |= TREE_BOOT_HASH_ALG_SHA256;
		}
		
		if(AlgList.algProperties[i].alg == TPM2_ALG_SHA384){
		   ProtocolCapability->HashAlgorithmBitmap |= TREE_BOOT_HASH_ALG_SHA384;
		}
		
		if(AlgList.algProperties[i].alg == TPM2_ALG_SHA512){
		   ProtocolCapability->HashAlgorithmBitmap |= TREE_BOOT_HASH_ALG_SHA512;
		}
	    }
    	}
    	else {
    		Status = EFI_SUCCESS;
    	}

    	if(HashAlg == 1 ){
            ProtocolCapability->SupportedEventLogs  = TREE_EVENT_LOG_FORMAT_TCG_1_2;
            ProtocolCapability->ProtocolVersion.Minor = 0;
            ProtocolCapability->ActivePcrBanks   = 1; // SHA1 Bank
            ProtocolCapability->NumberOfPcrBanks = 1;
    	}else if(HashAlg == 2){
            //ProtocolCapability->SupportedEventLogs  = TREE_EVENT_LOG_FORMAT_TCG_2;
            ProtocolCapability->SupportedEventLogs  = TREE_EVENT_LOG_FORMAT_TCG_1_2 | TREE_EVENT_LOG_FORMAT_TCG_2;
            ProtocolCapability->ProtocolVersion.Minor = 1;
            ProtocolCapability->ActivePcrBanks = 3; // SHA2 + SHA1 Bank
            ProtocolCapability->NumberOfPcrBanks = 2;
    	}
        ProtocolCapability->TrEEPresentFlag     = TRUE;
        ProtocolCapability->MaxCommandSize      = MaxCommandSize;   
        ProtocolCapability->MaxResponseSize     = MaxResponseSize;   
        ProtocolCapability->ManufacturerID      = ManufactureID;
        ProtocolCapability->Size                = sizeof(*ProtocolCapability);
      }
    }
  }

  return Status;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TreeGetEventLog
//
// Description: Get TPM 20 Event log
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
TreeGetEventLog (
  IN  EFI_TREE_PROTOCOL     *This,
  IN  TREE_EVENTLOGTYPE     EventLogFormat,
  OUT EFI_PHYSICAL_ADDRESS  *EventLogLocation,
  OUT EFI_PHYSICAL_ADDRESS  *EventLogLastEntry,
  OUT BOOLEAN               *EventLogTruncated
	)
{
   EFI_STATUS Status = EFI_SUCCESS;
   UINT8      HashAlg = GetHashPolicy();
  
   if(HashAlg != 1 && EventLogFormat == TREE_EVENT_LOG_FORMAT_TCG_1_2 ){
	    UINTN   _LastEvtPtr;
	    UINTN TransferTcgEvent2ToTcpaEvent( VOID );

	    _LastEvtPtr = TransferTcgEvent2ToTcpaEvent();
	    if( 0 == _LastEvtPtr )
	        _LastEvtPtr = TreeExtraTCPASha1LogLoc;

	    *EventLogLocation  = TreeExtraTCPASha1LogLoc;
	    *EventLogLastEntry = _LastEvtPtr;
	    *EventLogTruncated = IEventLogTruncated;

	    goto Done;
   }

   if(HashAlg != 2 && EventLogFormat == TREE_EVENT_LOG_FORMAT_TCG_2 ){
	    goto Done;

   }

   *EventLogLocation  = TreeEventLogLocation;
   *EventLogLastEntry = LastEventPtr;
   *EventLogTruncated = IEventLogTruncated;  
Done:
   return Status;
}

EFI_STATUS
InternalTcg20CommonExtend(
    IN  EFI_TREE_PROTOCOL  *TrEEProtocol,
    IN  TPM_PCRINDEX PcrIndex,
    IN  TPM2_DIGEST_VALUES  *Digest,
    OUT TPM2_DIGEST_VALUES  *NewPCRValue,
    IN  UINTN               HashAlgo)
{
    TPM2_PCRExtend_cmd_t  Cmd;
    TPM2_PCRExtend_res_t  Res;
    TPM2_PCRExtend_res_t  Tmpres;
    UINT32                CmdSize;
    UINT8                 *Buffer;
    UINT8                 *AuthSizeOffset;
    UINT8                 *ResultBuf = NULL;
    UINT32                ResultBufSize = 0;
    UINT32                DigestSize=0;
    EFI_STATUS            Status;
    UINTN                 i=0;

    Cmd.Tag          = (TPMI_ST_COMMAND_TAG)TPM_H2NS(TPM_ST_SESSIONS);
    Cmd.CommandSize  = TPM_H2NL(sizeof(Cmd));
    Cmd.CommandCode  = TPM_H2NL(TPM_CC_PCR_Extend);

    Buffer = (UINT8 *)&Cmd.inputParameters;
    *(UINT32 *)Buffer = TPM_H2NL(PcrIndex);
    Buffer += sizeof(UINT32);

    AuthSizeOffset = Buffer;
    *(UINT32 *)Buffer = 0;
    Buffer += sizeof(UINT32);

    //  pcr authHandle
    *(UINT32 *)Buffer = TPM_H2NL(TPM_RS_PW);
    Buffer += sizeof(UINT32);

    // nonce = nullNonce
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // sessionAttributes = 0
    *(UINT8 *)Buffer = 0;
    Buffer += sizeof(UINT8);

    // auth = nullAuth
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // authorizationSize
    *(UINT32 *)AuthSizeOffset = TPM_H2NL((UINT32)(Buffer - AuthSizeOffset - sizeof(UINT32)));

	//Digest count
	*(UINT32 *)Buffer = TPM_H2NL(1);
    Buffer += sizeof(UINT32);


	// Get the digest size based on Hash Alg
    if(HashAlgo==TREE_BOOT_HASH_ALG_SHA1){
        //Hash alg
	    *(UINT16 *)Buffer = TPM_H2NS(TPM2_ALG_SHA1);
        Buffer += sizeof(UINT16);
        DigestSize = SHA1_DIGEST_SIZE;
        TcgCommonCopyMem(NULL, Buffer, &Digest->digests.sha1, DigestSize);
    }
    
    if(HashAlgo==TREE_BOOT_HASH_ALG_SHA256){
	    //Hash alg
	    *(UINT16 *)Buffer = TPM_H2NS(TPM2_ALG_SHA256);
        Buffer += sizeof(UINT16);
        DigestSize = SHA256_DIGEST_SIZE;
        TcgCommonCopyMem(NULL, Buffer, &Digest->digests.sha256, DigestSize);
    }

    Buffer += DigestSize;

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.CommandSize = TPM_H2NL(CmdSize);

    ResultBuf     = (UINT8 *) &Tmpres;
    ResultBufSize = sizeof(Res);
    
    Status  = TrEEProtocol->SubmitCommand(TrEEProtocol,CmdSize, (UINT8 *)&Cmd, ResultBufSize, ResultBuf);
    
    return Status;
}


EFI_STATUS
TpmHashLogExtendEventI(
  IN  EFI_TREE_PROTOCOL         *This,
  IN  UINT8                     *DataToHash,
  IN  UINT64                    Flags,
  IN  UINTN                     DataSize,
  IN  OUT  TCG_PCR_EVENT2_HDR   *NewEventHdr,
  IN      UINT8                 *NewEventData
)
{
  EFI_STATUS                Status;
  TPM2_DIGEST_VALUES        Out_Digest;
  static UINT32             HashAlgo = 0xFFFFFFFF;
  UINT32                    TempSize=0;
  UINTN                     RequiredSpace=0;
  TCG_PLATFORM_SETUP_PROTOCOL     *PolicyInstance;
  EFI_GUID                        gPolicyguid = TCG_PLATFORM_SETUP_POLICY_GUID;
  TCG_PCClient_PCR_Event2_Hdr	EventData;

  DEBUG(( -1," TpmHashLogExtendEvent Entry \n"));
#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0 
  if(NewEventHdr->EventType == EV_EFI_ACTION)
    {
      return EFI_SUCCESS;
  }
#endif
  
   if(HashAlgo == 0xFFFFFFFF){       
      Status = gBS->LocateProtocol (&gPolicyguid,  NULL, &PolicyInstance);
      if (EFI_ERROR (Status)) {
          HashAlgo = TREE_BOOT_HASH_ALG_SHA1;
      }else{
          HashAlgo = PolicyInstance->ConfigFlags.HashPolicy;
      }
    }
   
    DEBUG(( -1," HashAlgo = %x \n", HashAlgo));

    if(HashAlgo == TREE_BOOT_HASH_ALG_SHA1){
          RequiredSpace = sizeof(TCG_PCR_EVENT2_HDR) - sizeof(NewEventHdr->Digests)\
                          + sizeof(NewEventHdr->Digests.digests.sha1) +
                          NewEventHdr->EventSize;
 
          if(DataToHash!=NULL)
          {
              Status = SHA1HashAll( NULL, DataToHash, DataSize, (UINT8 *)&NewEventHdr->Digests.digests.sha1 );        
              DEBUG(( -1," SHA1HashAll Status = %r \n", Status));
              if(EFI_ERROR(Status))return Status;        
          }
      }
     
     if(HashAlgo == TREE_BOOT_HASH_ALG_SHA256){
         
         RequiredSpace = sizeof(TCG_PCClient_PCR_Event2_Hdr) - sizeof(TPML_DIGEST_VALUES)\
                                   + sizeof(UINT32) + sizeof(UINT16)*2 + SHA1_DIGEST_SIZE
                                   + SHA256_DIGEST_SIZE + NewEventHdr->EventSize;
         
         if(DataToHash!=NULL)
         {
             Status = SHA2HashAll( NULL, DataToHash, DataSize, (UINT8 *)&EventData.digests.digests[1].digest.sha256);
               if(EFI_ERROR(Status))return Status;
             Status = SHA1HashAll( NULL, DataToHash, DataSize, (UINT8 *)&EventData.digests.digests[0].digest.sha1);
               if(EFI_ERROR(Status))return Status;
             gBS->CopyMem(
                     (VOID*)( &NewEventHdr->Digests.digests.sha256 ),
                     (VOID*)( &EventData.digests.digests[1].digest.sha256 ),
                     SHA256_DIGEST_SIZE);
             gBS->CopyMem(
                     (VOID*)( &NewEventHdr->Digests.digests.sha1 ),
                     (VOID*)( &EventData.digests.digests[0].digest.sha1 ),
                     SHA1_DIGEST_SIZE);
         }
         
         if(DataToHash == NULL){
             gBS->CopyMem((VOID*)(&EventData.digests.digests[1].digest.sha256),
                     &NewEventHdr->Digests.digests.sha256,
                     SHA256_DIGEST_SIZE);
             gBS->CopyMem((VOID*)(&EventData.digests.digests[0].digest.sha1),
                     &NewEventHdr->Digests.digests.sha1,
                     SHA1_DIGEST_SIZE);
         }
         
         EventData.pcrIndex = NewEventHdr->PCRIndex;
         EventData.eventType = NewEventHdr->EventType;
         EventData.digests.count = 2;
         EventData.digests.digests[1].hashAlg = TPM2_ALG_SHA256;
         EventData.digests.digests[0].hashAlg = TPM2_ALG_SHA1;
     }

     //printbuffer((UINT8 *)&EventData, sizeof(TCG_PCClient_PCR_Event2_Hdr));
     //printbuffer((UINT8 *)NewEventHdr, sizeof(TCG_PCR_EVENT2_HDR));

     if((RequiredSpace + LastEntry) > \
                    (TreeEventLogLocation  + MAX_LOG_AREA_SIZE)){
                     IEventLogTruncated = TRUE;
     }
     
     if( NewEventHdr->EventType != EV_NO_ACTION)
     {
         Status = InternalTcg20CommonExtend(This,
                     NewEventHdr->PCRIndex,
                     &NewEventHdr->Digests,
                     &Out_Digest,
                     HashAlgo);

         if( TREE_BOOT_HASH_ALG_SHA256 == HashAlgo )
         {
             Status = InternalTcg20CommonExtend(This,
                         NewEventHdr->PCRIndex,
                         &NewEventHdr->Digests,
                         &Out_Digest,
                         TREE_BOOT_HASH_ALG_SHA1);
         }
     }
     
     DEBUG(( -1," InternalTcg20CommonExtend Status = %r \n", Status));
     if(EFI_ERROR(Status))return Status;
   
     if(IEventLogTruncated)return EFI_SUCCESS;;

     DEBUG(( -1," LastEntry = %x \n", LastEntry));
     if(LastEntry == 0) return EFI_ABORTED;
    
     LastEventPtr = LastEntry;
   
     CopyMem((VOID*)(UINTN)LastEntry,NewEventHdr,sizeof(TCG_PCR_EVENT2_HDR) 
                                           -sizeof(NewEventHdr->Digests) - sizeof(UINT32));   

     TempSize =  sizeof(TCG_PCR_EVENT2_HDR) -sizeof(NewEventHdr->Digests) - sizeof(UINT32);
       

     if(HashAlgo == TREE_BOOT_HASH_ALG_SHA1){ //log event record
         gBS->CopyMem(
                 (VOID*)(UINTN)(LastEntry + TempSize) ,
                 (UINT8 *)&NewEventHdr->Digests.digests.sha1,
                 sizeof(NewEventHdr->Digests.digests.sha1));

         TempSize+=sizeof(NewEventHdr->Digests.digests.sha1);
       
     }
   
     if(HashAlgo == TREE_BOOT_HASH_ALG_SHA256){

         *(UINT32*)(LastEntry + TempSize) = EventData.digests.count;
         TempSize += sizeof(UINT32);

         gBS->CopyMem(
                 (VOID*)(UINTN)(LastEntry + TempSize) ,
                 (UINT8 *)&EventData.digests.digests[0],
                 sizeof(UINT16) + SHA1_DIGEST_SIZE
                 );
         TempSize += sizeof(UINT16) + SHA1_DIGEST_SIZE;

         gBS->CopyMem(
                 (VOID*)(UINTN)(LastEntry + TempSize) ,
                 (UINT8 *)&EventData.digests.digests[1],
                 sizeof(UINT16) + SHA256_DIGEST_SIZE
                 );
         TempSize += sizeof(UINT16) + SHA256_DIGEST_SIZE;

     }

     gBS->CopyMem(
             (VOID*)(UINTN)(LastEntry + TempSize),
             (UINT8 *)&NewEventHdr->EventSize,
             sizeof(UINT32));
    
     TempSize+=sizeof(UINT32);

     gBS->CopyMem(
             (VOID*)(UINTN)(LastEntry + TempSize),
             NewEventData,
             NewEventHdr->EventSize);
     
     //printbuffer(NewEventData, NewEventHdr->EventSize);
    
     LastEntry = LastEventPtr + ((EFI_PHYSICAL_ADDRESS)(UINTN)(NewEventHdr->EventSize \
                              + TempSize));
    
     return EFI_SUCCESS;   
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TreeHashLogExtentEvent
//
// Description: Hash, log and Extend a TPM 20 Event
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
#pragma optimize ("",off)
EFI_STATUS
TreeHashLogExtentEvent (
  IN  EFI_TREE_PROTOCOL     *This,
  IN  UINT64                Flags,
  IN  EFI_PHYSICAL_ADDRESS  DataToHash,
  IN  UINT64                DataToHashLen,
  IN  TrEE_EVENT            *TreeEvent
  )
{
  EFI_STATUS            Status     = EFI_SUCCESS;
  TCG_PCR_EVENT2_HDR     TcgEvent;
  
  if((This == NULL ) || (DataToHash == 0) || (TreeEvent == NULL)) {
    Status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  else if(TreeEvent->Size < (TreeEvent->Header.HeaderSize + sizeof(UINT32))\
                                 || (TreeEvent->Header.PCRIndex > 23)){
   Status = EFI_INVALID_PARAMETER;
   goto Exit;
  }

  TcgEvent.PCRIndex  = TreeEvent->Header.PCRIndex;
  TcgEvent.EventType = TreeEvent->Header.EventType;
  TcgEvent.EventSize = TreeEvent->Size - sizeof(TrEE_EVENT_HEADER) \
                        -sizeof(UINT32);
  
  Status = TpmHashLogExtendEventI(This,
             (UINT8 *)(UINTN)DataToHash,
                      Flags,
             (UINTN)  DataToHashLen,
                      &TcgEvent,
             (UINT8 *)&TreeEvent->Event
                      );

Exit:

	return Status;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TreeSubmitCommand
//
// Description: Submit TPM 20 Command
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
#pragma optimize("",off)
EFI_STATUS
TreeSubmitCommand (
IN  EFI_TREE_PROTOCOL   *This,
IN  UINT32              InputParameterBlockSize,
IN  UINT8               *InputParameterBlock,
IN  UINT32              OutputParameterBlockSize,
IN  UINT8               *OutputParameterBlock
  )
{
    EFI_STATUS            Status     = EFI_SUCCESS;
    UINT32                ReturnSize = 0;
    UINT32                Size = 0;
    TPM_TRANSMIT_BUFFER   InBuffer[1], OutBuffer[1];
    TPM_1_2_REGISTERS_PTR     TpmReg = (TPM_1_2_REGISTERS_PTR)(UINTN)PORT_TPM_IOMEMBASE;

    if (This == NULL || InputParameterBlock == NULL || OutputParameterBlock == NULL) {
        return EFI_INVALID_PARAMETER;
    }
        
    if(TpmSupport->InterfaceType == 1){
        
         ReturnSize = OutputParameterBlockSize;

         TisRequestLocality ( TpmReg );

         InBuffer[0].Buffer  = InputParameterBlock;
         InBuffer[0].Size    = InputParameterBlockSize;
         OutBuffer[0].Buffer = OutputParameterBlock;
         OutBuffer[0].Size   = OutputParameterBlockSize;

         TpmLibPassThrough(TpmReg,sizeof (InBuffer) / sizeof (*InBuffer),
                         InBuffer,sizeof (OutBuffer) / sizeof (*OutBuffer),
                         OutBuffer);

         TisReleaseLocality ( TpmReg );
         
    }else{

        Size = OutputParameterBlockSize;
        Status = CrbSubmitCmd(InputParameterBlock,
                       InputParameterBlockSize,
                       OutputParameterBlock,
                       &Size);
    }

    return Status;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CopyTcgLog
//
// Description: Copy the Tcg log from Pei Ho into Memory
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
static EFI_STATUS CopyTcgLog(
    void )
{
    TCG_LOG_HOB     *TcgLog = NULL;
    void**          DummyPtr;
    EFI_GUID        gEfiPeiLogHobGuid = EFI_TCG_TREE_LOG_HOB_GUID;
    
    DEBUG(( -1," CopyTcgLog Entry \n"));

    TcgLog = (TCG_LOG_HOB*)                   LocateATcgHob(
        gST->NumberOfTableEntries,
        gST->ConfigurationTable,
        &gEfiPeiLogHobGuid );

    DummyPtr = &TcgLog;

    if ( *DummyPtr == NULL )
    {
        DEBUG(( -1," gEfiPeiLogHobGuid Not found \n"));
        return EFI_NOT_FOUND;
    }
    
    TcgLog->TableMaxSize = MAX_LOG_AREA_SIZE;
    DEBUG(( -1," TcgLog->TableMaxSize \n", TcgLog->TableMaxSize));
    
    gBS->CopyMem(
            (UINT8 *)(UINTN)TreeEventLogLocation,
            ((UINT8 *)TcgLog),
            sizeof(TCG_LOG_HOB)
            );

    gBS->CopyMem(
        (UINT8 *)(UINTN)TreeEventLogLocation,
        (((UINT8 *)TcgLog) + sizeof(TCG_LOG_HOB)),
        TcgLog->TableSize
        );

    LastEntry = TreeEventLogLocation  +  TcgLog->TableSize;
    DEBUG(( -1," CopyTcgLog LastEntry = %x \n", LastEntry));

    return EFI_SUCCESS;
}


EFI_TREE_PROTOCOL mTreeProtocol = {
  TreeGetCapability,
  TreeGetEventLog,
  TreeHashLogExtentEvent,
  TreeSubmitCommand,
  EfiTreeGetActivePcrs,
  EfiTreeSetActivePcrs
};

AMI_INTERNAL_HLXE_PROTOCOL  InternalLogProtocol = {
  TpmHashLogExtendEventI
};



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InstallTrEEProtocol
//
// Description: Install Tree Protocol
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
InstallTrEEProtocol(
  IN EFI_HANDLE Handle
  )
{    
  EFI_STATUS Status;
  EFI_GUID  gEfiTrEEProtocolGuid =  EFI_TREE_PROTOCOL_GUID;
  EFI_GUID  gEfiAmiHLXEGuid =  AMI_PROTOCOL_INTERNAL_HLXE_GUID;

  DEBUG(( -1," InstallTrEEProtocol \n"));
  
  Status = gBS->AllocatePages(AllocateAnyPages,
                        EfiRuntimeServicesData,
                        EFI_SIZE_TO_PAGES(MAX_LOG_AREA_SIZE),
                        (UINT64*)(UINTN)&TreeEventLogLocation);

  if(EFI_ERROR(Status))return Status;

  // When SHA1 + SHA2 enable, we still need to provide the SHA1 format log.
  Status = gBS->AllocatePages(AllocateAnyPages,
                      EfiRuntimeServicesData,
                      EFI_SIZE_TO_PAGES(MAX_LOG_AREA_SIZE),
                      (UINT64*)(UINTN)&TreeExtraTCPASha1LogLoc);

  if(EFI_ERROR(Status))return Status;
     
   gBS->SetMem(
              (VOID*)((UINTN)TreeEventLogLocation),
              (UINTN)MAX_LOG_AREA_SIZE,
              0x00);  

   gBS->SetMem(
              (VOID*)((UINTN)TreeExtraTCPASha1LogLoc),
              (UINTN)MAX_LOG_AREA_SIZE,
              0x00);  

  //locate PEI hob and copy to the TreeLogArea
  Status = CopyTcgLog();
  
  //interface installation is 
  Status =  gBS->InstallProtocolInterface (
                      &Handle,
                      &gEfiTrEEProtocolGuid,
                      EFI_NATIVE_INTERFACE,
                      &mTreeProtocol);

  if(EFI_ERROR(Status))return Status;

  Status =  gBS->InstallProtocolInterface (
                &Handle,
                &gEfiAmiHLXEGuid,
                EFI_NATIVE_INTERFACE,
                &InternalLogProtocol
                );
  
  if(EFI_ERROR(Status))return Status;
    
  DEBUG(( -1," InstallTrEEProtocol Exit Status = %r \n", Status));
  return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TrEEUpdateTpmDeviceASL
//
// Description: Update TPM Asl tokens
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID TrEEUpdateTpmDeviceASL(    
    IN EFI_EVENT ev,
    IN VOID      *ctx)
{   
   ACPI_HDR                    *dsdt;
   EFI_PHYSICAL_ADDRESS        dsdtAddress=0;
   EFI_STATUS                  Status;
   UINT64                      Value;

   DEBUG(( -1, "TrEEUpdateTpmDeviceASL Entry \n"));
   
    //locate AcpiProtocol
    Status = TcgLibGetDsdt(&dsdtAddress, EFI_ACPI_TABLE_VERSION_ALL);
    if (EFI_ERROR(Status)){
        DEBUG((-1, "TrEEUpdateTpmDeviceASL::DSDT not found\n"));
        if(Status == EFI_NOT_AVAILABLE_YET){
            //set callback
            Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   EFI_TPL_CALLBACK, TrEEUpdateTpmDeviceASL, &reg, &Event );

            if(EFI_ERROR(Status)){
                DEBUG((-1, "Unable to create Event..Exit(1)\n"));
                return;
            }
            Status = gBS->RegisterProtocolNotify( &gInternalAcpiSupportGuid, Event, &reg );   
        }
        return;
    }

    DEBUG((-1, "TrEEUpdateTpmDeviceASL::dsdtAddress %x \n", dsdtAddress));
    dsdt = (ACPI_HDR*)dsdtAddress;

    DEBUG((-1, "dsdt->Signature =  %x \n", dsdt->Signature));
    
    // Update for TCM Device
    if( AutoSupportType() )
    {
       Value = 1;
       DEBUG(( -1, "TrEEUpdateTpmDeviceASL::Set TCMF Device ID \n"));
       Status=TcgUpdateAslNameObject(dsdt, "TCMF", (UINT64)Value);
       if (EFI_ERROR(Status)){
           DEBUG((-1, "TrEEUpdateTpmDeviceASL::Failed set TCMF Device ID  %r \n", Status));
           return;
       }  
    }
        
    if(!IsTpm20Device()){
        Value = 0;
    }else{
        Value = 1;
    }
       
    DEBUG((-1, "TrEEUpdateTpmDeviceASL::Setting  TTDP to %x \n", Value));
    Status=TcgUpdateAslNameObject(dsdt, "TTDP", (UINT64)Value);
    if (EFI_ERROR(Status)){
        DEBUG((-1, "TrEEUpdateTpmDeviceASL::Failure setting ASL TTDP %r \n", Status));
        return;
    }    

    if(isTpm20CrbPresent()){
        Value = 0;
    }else{
        Value = 1;
    }

    DEBUG((-1, "TrEEUpdateTpmDeviceASL::Setting  TTPF to %x \n", Value));
    
    Status=TcgUpdateAslNameObject(dsdt, "TTPF", (UINT64)Value);
    if (EFI_ERROR(Status)){
        DEBUG((-1, "TrEEUpdateTpmDeviceASL::Failure setting ASL value %r \n", Status));
    }
    gBS->CloseEvent(ev);
    return;
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   MeasureCertificate
//
// Description: Measure a Certs
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
MeasureCertificate(UINTN sizeOfCertificate, 
                   UINT8 *pterCertificate)
{
    EFI_STATUS                Status;
    TrEE_EVENT               *Tcg20Event;
    EFI_VARIABLE_DATA        *VarLog = NULL;
    BOOLEAN                   AlreadyMeasuredCert = FALSE;
    UINTN                     i=0;
    UINTN                     VarNameLength;
    static BOOLEAN            initialized = 0;
    static TPM_DIGEST         digestTrackingArray[5];
    static TPM_DIGEST         zeroDigest;
    UINT8                     *tempDigest = NULL;
    UINT64                    HashedDataLen = 20; 
    SHA1_CTX                  Sha1Ctx;
    TCG_DIGEST                Sha1Digest;
    UINT64                    Flags = 0;
    UINT32                    EventSize = 0;
    UINT8                     *EventDataPtr;

    if(TrEEProtocolInstance == NULL) return EFI_NOT_FOUND;

    VarNameLength = StrLen(L"db");

    EventSize = (UINT32)( sizeof (*VarLog) + VarNameLength 
                              * sizeof (CHAR16) + sizeOfCertificate) - 3;

    gBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                      sizeof(UINT32) + EventSize), &Tcg20Event);

    if(Tcg20Event==NULL) return EFI_OUT_OF_RESOURCES;

    if(!initialized)
    {
        for(i=0;i<5; i++)
        {
            gBS->SetMem(digestTrackingArray[i].digest,20, 0);
        }
        gBS->SetMem(zeroDigest.digest,20, 0);
        initialized = TRUE;
    }

    Tcg20Event->Size  = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + EventSize;
    Tcg20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tcg20Event->Header.HeaderVersion = 1;
    Tcg20Event->Header.PCRIndex    = 7;
    Tcg20Event->Header.EventType   = 0x800000E0;
       
    Status = gBS->AllocatePool(EfiBootServicesData, EventSize, &VarLog);

    if ( VarLog == NULL ){
        return EFI_OUT_OF_RESOURCES;
    }
        
    VarLog->VariableName       = gEfiImageSecurityDatabaseGuid;
    VarLog->UnicodeNameLength  = VarNameLength;
    VarLog->VariableDataLength = sizeOfCertificate;

    gBS->CopyMem((CHAR16*)(VarLog->UnicodeName),
                L"db",
                VarNameLength * sizeof (CHAR16));
   
    gBS->CopyMem((CHAR16*)(VarLog->UnicodeName) + VarNameLength,
                 pterCertificate,
                 sizeOfCertificate);

    //before extending verify if we have already measured it.
    SHA1Init(&Sha1Ctx);
    
    SHA1Update(&Sha1Ctx,
                VarLog,
           (u32)EventSize);

    SHA1Final((unsigned char *)&Sha1Digest.digest, &Sha1Ctx);

    for(i=0; i<5; i++)
    {
        //tempDigest
        if(!CompareMem(digestTrackingArray[i].digest, &Sha1Digest, 20))
        return EFI_SUCCESS; //already measured

        if(!CompareMem(digestTrackingArray[i].digest, zeroDigest.digest, 20))
        break; //we need to measure
    }

	if(i<5){
		gBS->CopyMem(digestTrackingArray[i].digest, &Sha1Digest, 20);
	}
    
    EventDataPtr = (UINT8 *)Tcg20Event;

    EventDataPtr += sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32);

    gBS->CopyMem(EventDataPtr, VarLog, EventSize);
    
    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
                                            Flags, (EFI_PHYSICAL_ADDRESS)(UINT8 *)(UINTN)VarLog, (UINT64)EventSize,
                                            Tcg20Event);
    return Status;
}





//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   FindandMeasureSecureBootCertificate
//
// Description: Measure Secureboot Certs
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS FindandMeasureSecureBootCertificate()
{
    EFI_STATUS      Status;
    UINTN           VarSize  = 0;
    UINTN           i=0;
    UINT8           *SecureDBBuffer = NULL;
    UINT8           *CertificateBuffer = NULL;
    UINTN           SizeofCerificate = 0;
    EFI_GUID        Certificateguid = AMI_VALID_BOOT_IMAGE_CERT_TBL_GUID;
    AMI_VALID_CERT_IN_SIG_DB    *CertInfo;
    UINT8           *CertOffsetPtr = NULL;
   
    VarSize = 0;

    Status   = gRT->GetVariable(L"db",
                    &gEfiImageSecurityDatabaseGuid,
                    NULL,
                    &VarSize,
                    NULL);

    if ( Status != EFI_BUFFER_TOO_SMALL )
    {
        return EFI_NOT_FOUND;
    }

    Status = gBS->AllocatePool(EfiBootServicesData, VarSize, &SecureDBBuffer);
    
    if ( SecureDBBuffer != NULL )
    {
        Status = gRT->GetVariable(L"db",
                        &gEfiImageSecurityDatabaseGuid,
                        NULL,
                        &VarSize,
                        SecureDBBuffer);

        if ( EFI_ERROR( Status ))
        {
            gBS->FreePool( SecureDBBuffer  );
            SecureDBBuffer = NULL;
            return EFI_NOT_FOUND;
        }
    }else{
        return EFI_OUT_OF_RESOURCES;
    }

    //we need to find the pointer in the EFI system table and work from 
    //there
    CertInfo = NULL;
    EfiGetSystemConfigurationTable(&Certificateguid, &CertInfo );
    if(CertInfo == NULL){
     return EFI_NOT_FOUND;
    }
    if(CertInfo->SigLength == 0){
     return EFI_NOT_READY;
    }

    CertOffsetPtr = NULL;
    CertOffsetPtr = (SecureDBBuffer + CertInfo->SigOffset);
    MeasureCertificate((UINTN)CertInfo->SigLength,CertOffsetPtr);
    
    if(SecureDBBuffer!=NULL){
        gBS->FreePool( SecureDBBuffer  );
    }
    
    return Status;
}

VOID
PeCoffLoaderAdjustOffsetForTeImage (
  EFI_IMAGE_SECTION_HEADER              *SectionHeader,
  UINT32                                TeStrippedOffset
  );


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   MeasureTeImage
//
// Description: Measure a TE Image
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
MeasureTeImage (
  IN  EFI_IMAGE_LOAD_EVENT     *ImageLoad,
  IN  UINTN                     HashAlgorithm,
  IN  UINT8                    *Digest1,
  IN  UINT8                    *Digest2)
{
    SHA1_CTX                          Sha1Ctx;
    EFI_TE_IMAGE_HEADER               *ptrToTEHdr;
    EFI_IMAGE_SECTION_HEADER          *Section;
    UINT8                             *HashBase;
    UINTN                             HashSize;
    UINTN                             SumOfBytesHashed;
    UINTN                             SectionHeaderOffset;
    UINTN                             numOfSectionHeaders;
    UINTN                             Index;
    SHA2_CTX                          Sha2Ctx;
    UINTN                             Size= 0;
        
    // 2. Initialize a SHA hash context.
    if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA1){ SHA1Init(&Sha1Ctx);}
    
    if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA256)
    {
        sha256_init( &Sha2Ctx );
        SHA1Init(&Sha1Ctx);
    }
    
    DEBUG ((-1, "Printing TE Image Buffer in Memory Image Location = %x, Image size = %x\n",
            (UINTN)ImageLoad->ImageLocationInMemory, ImageLoad->ImageLengthInMemory));
    
    //printbuffer((UINT8 *)(UINTN)ImageLoad->ImageLocationInMemory, 1024);
    
    ptrToTEHdr = (EFI_TE_IMAGE_HEADER *)((UINT8 *)(UINTN)ImageLoad->ImageLocationInMemory);
    
    //Hash TE Image header and section headers
    
    HashBase = (UINT8 *)(UINTN)ptrToTEHdr;
    HashSize = sizeof(EFI_TE_IMAGE_HEADER) + ( EFI_IMAGE_SIZEOF_SECTION_HEADER * ptrToTEHdr->NumberOfSections);
    
    DEBUG ((-1, "Printing Hashed TE Hdr and Section Header\n"));
    
    DEBUG ((-1, "Base = %x Len = %x \n", HashBase, HashSize));
    
    //printbuffer(HashBase, HashSize);
    
    if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA1){
        SHA1Update(&Sha1Ctx,
                    HashBase,
                    (u32)HashSize);
    }
        
    if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA256){
        sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
        SHA1Update(&Sha1Ctx,
                    HashBase,
                    (u32)HashSize);
    }
    
    
    SectionHeaderOffset = sizeof(EFI_TE_IMAGE_HEADER) + (UINTN)ptrToTEHdr;
    
    numOfSectionHeaders = ptrToTEHdr->NumberOfSections;
    
    SumOfBytesHashed = HashSize;
    
    //check for alignment
    //hash Alignment buffer
    HashSize = (((EFI_IMAGE_SECTION_HEADER *)((UINT8 *)SectionHeaderOffset))->PointerToRawData 
            - ptrToTEHdr->StrippedSize + sizeof(EFI_TE_IMAGE_HEADER)+ (UINTN)ImageLoad->ImageLocationInMemory - ((UINTN)ImageLoad->ImageLocationInMemory + HashSize));
    
    if(HashSize !=0){
        HashBase += sizeof(EFI_TE_IMAGE_HEADER) + ( EFI_IMAGE_SIZEOF_SECTION_HEADER * ptrToTEHdr->NumberOfSections);
        
        DEBUG ((-1, "Printing Hashed TE Alignment Buffer\n"));
        
        DEBUG ((-1, "Base = %x Len = %x \n", HashBase, HashSize));
        //printbuffer(HashBase, HashSize);
        
        if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA1){
            SHA1Update(&Sha1Ctx,
                       HashBase,
                       (u32)HashSize);
        }
                
        if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA256){
             sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
             SHA1Update(&Sha1Ctx,
                        HashBase,
                        (u32)HashSize);
        }
        
        SumOfBytesHashed+=HashSize;
    }

    //
    // TE Images do not have a CertDirector
    //
    
    //process hash section by section
    //hash in order sections. We do not sort TE sections
    for (Index = 0; Index < numOfSectionHeaders; Index++) {
        
        Section = (EFI_IMAGE_SECTION_HEADER *)((UINT8 *)SectionHeaderOffset);
        
        if (Section->SizeOfRawData == 0) {
             continue;
        }
        
        //Hash raw data
        
        HashBase = (UINT8 *)(((UINTN)ImageLoad->ImageLocationInMemory) 
                        + (UINTN)Section->PointerToRawData - ptrToTEHdr->StrippedSize + sizeof(EFI_TE_IMAGE_HEADER));
        HashSize = (UINTN) Section->SizeOfRawData;
        
        DEBUG ((-1, "Section Base = %x Section Len = %x \n", HashBase, HashSize));
        
//        printbuffer(HashBase, 1024);

        if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA1){
           SHA1Update(&Sha1Ctx,
                      HashBase,
                      (u32)HashSize);
        }
              
        if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA256){
           sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
           SHA1Update(&Sha1Ctx,
                      HashBase,
                      (u32)HashSize);
        }


        SumOfBytesHashed += HashSize;              
        SectionHeaderOffset += EFI_IMAGE_SIZEOF_SECTION_HEADER;
    }  
    
    DEBUG ((-1, "SumOfBytesHashed = %x \n", SumOfBytesHashed));
   
    //verify size
    if ( ImageLoad->ImageLengthInMemory > SumOfBytesHashed) {
        
      DEBUG ((-1, "Hash rest of Data if true \n"));
        
      HashBase = (UINT8 *)(UINTN)ImageLoad->ImageLocationInMemory + SumOfBytesHashed;
      HashSize = (UINTN)(ImageLoad->ImageLengthInMemory - SumOfBytesHashed);
      
      DEBUG ((-1, "Base = %x Len = %x \n", HashBase, HashSize));
//      printbuffer(HashBase, 106);

      
      if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA1){
       SHA1Update(&Sha1Ctx,
                  HashBase,
                  (u32)HashSize);
      }
      
      if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA256){
       sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
       SHA1Update(&Sha1Ctx,
                  HashBase,
                  (u32)HashSize);
      }
    }
    

    //
    // Finalize the SHA hash.
    //
    if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA1){
      SHA1Final(Digest1, &Sha1Ctx);
    }
    
    if(HashAlgorithm == TREE_BOOT_HASH_ALG_SHA256){
      sha256_done( &Sha2Ctx, Digest2 );
      SHA1Final(Digest1, &Sha1Ctx);
    }

    return EFI_SUCCESS;
}



TCG_PLATFORM_SETUP_PROTOCOL       *AmiProtocolInstance;
AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TreeMeasurePeImage
//
// Description: Measure a PE Image
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI
TreeMeasurePeImage (
  IN      BOOLEAN                   BootPolicy,
  IN      EFI_PHYSICAL_ADDRESS      ImageAddress,
  IN      UINTN                     ImageSize,
  IN      UINTN                     LinkTimeBase,
  IN      UINT16                    ImageType,
  IN      EFI_HANDLE                DeviceHandle,
  IN      EFI_DEVICE_PATH_PROTOCOL  *FilePath
  )
{

  EFI_STATUS                        Status;
  TCG_PCR_EVENT2_HDR                TcgEvent;
  UINT8                             *EventData = NULL;
  EFI_IMAGE_LOAD_EVENT              *ImageLoad;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL          *FullPath;
  UINT32                            FullPathSize;
  SHA1_CTX                          Sha1Ctx;
  EFI_IMAGE_DOS_HEADER              *DosHdr;
  UINT32                            PeCoffHeaderOffset;
  EFI_IMAGE_NT_HEADERS64            *Hdr;
  EFI_IMAGE_SECTION_HEADER          *Section;
  UINT8                             *HashBase;
  UINTN                             HashSize;
  UINTN                             SumOfBytesHashed;
  EFI_IMAGE_SECTION_HEADER          *SectionHeader;
  UINTN                             Index, iPos;
  TCG_DIGEST                        Sha1Digest;
  EFI_GUID                          gEfiAmiHLXEGuid =  AMI_PROTOCOL_INTERNAL_HLXE_GUID;
  EFI_GUID                          Policyguid = TCG_PLATFORM_SETUP_POLICY_GUID;
  SHA2_CTX                          Sha2Ctx;
  unsigned char                     Sha2DigestArray[32];  
  UINT32                            HashPolicy;
  
  EFI_GUID  gEfiTrEEProtocolGuid =  EFI_TREE_PROTOCOL_GUID;
  
  DEBUG ((-1, "TreeMeasurePeImage Entry\n"));  
  
  if(AmiProtocolInstance==NULL){
      Status = gBS->LocateProtocol (&Policyguid,  NULL, &AmiProtocolInstance);
      if (EFI_ERROR (Status)) {
          return 0;
      }
  }

  HashPolicy = AmiProtocolInstance->ConfigFlags.HashPolicy;
    
      
  ImageLoad     = NULL;
  FullPath      = NULL;
  SectionHeader = NULL;
  FullPathSize  = 0;

  DEBUG ((-1, "TreeMeasurePeImage Entry\n"));

  if (DeviceHandle != NULL) {
    //
    // Skip images loaded from FVs
    //
    Status = gBS->OpenProtocol (
                    DeviceHandle,
                    &gEfiFirmwareVolume2ProtocolGuid,
                    NULL,
                    NULL,
                    NULL,
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                    );

    if (!EFI_ERROR (Status)) {
      goto Done;
    }
    ASSERT (Status == EFI_UNSUPPORTED);

    //
    // Get device path for the device handle
    //
    Status = gBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiDevicePathProtocolGuid,
                    &DevicePath
                    );
    if (EFI_ERROR (Status)) {
      FullPathSize = (UINT32)GetDevicePathSize (FullPath); 
    }else{                 
      FullPath     = AppendDevicePath (DevicePath, FilePath);
      FullPathSize = (UINT32)GetDevicePathSize (FullPath); 
    }
  }else if(FilePath!= NULL){
      FullPath     = FilePath;
      FullPathSize  = (UINT32) GetDevicePathSize (FilePath);
  }

    //Allocate Event log memory
  Status = gBS ->AllocatePool(EfiBootServicesData, ((sizeof (*ImageLoad)
                                - sizeof (ImageLoad->DevicePath)) + FullPathSize), &EventData);

  if(EFI_ERROR(Status))return Status;
  //
  // Determine destination PCR by BootPolicy
  //
  TcgEvent.EventSize  = sizeof (*ImageLoad) - sizeof (ImageLoad->DevicePath);
  TcgEvent.EventSize += FullPathSize;

  switch (ImageType) {
    case EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION:
      TcgEvent.PCRIndex   = 4;
      TcgEvent.EventType = EV_EFI_BOOT_SERVICES_APPLICATION;
      break;
    case EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
      TcgEvent.PCRIndex   = 2;
      TcgEvent.EventType = EV_EFI_BOOT_SERVICES_DRIVER;
#if defined(HashSmmDrivers) && (HashSmmDrivers == 0)
      if(ReadyToBootSignaled==FALSE){
          goto Done; 
      }
#endif
      break;
    case EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
      TcgEvent.PCRIndex   = 2;
      TcgEvent.EventType = EV_EFI_RUNTIME_SERVICES_DRIVER;
#if defined(HashSmmDrivers) && (HashSmmDrivers == 0)
      if(ReadyToBootSignaled==FALSE){
          goto Done; 
      }
#endif
      break;
    default:
      TcgEvent.EventType = ImageType;
      Status = EFI_UNSUPPORTED;
      goto Done;
  }

  Status = gBS ->AllocatePool(EfiBootServicesData,TcgEvent.EventSize, &ImageLoad);

  if (ImageLoad == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  ImageLoad->ImageLocationInMemory = ImageAddress;
  ImageLoad->ImageLengthInMemory   = ImageSize;
  ImageLoad->ImageLinkTimeAddress  = LinkTimeBase;
  ImageLoad->LengthOfDevicePath    = FullPathSize;
  gBS->CopyMem( ImageLoad->DevicePath, FullPath,  FullPathSize );

  //
  // Check PE/COFF image
  //
  DosHdr = (EFI_IMAGE_DOS_HEADER *)(UINTN)ImageAddress;
  PeCoffHeaderOffset = 0;
  if (DosHdr->e_magic == EFI_IMAGE_DOS_SIGNATURE) {
    PeCoffHeaderOffset = DosHdr->e_lfanew;
  }
  if (((EFI_TE_IMAGE_HEADER *)((UINT8 *)(UINTN)ImageAddress + PeCoffHeaderOffset))->Signature 
       == EFI_TE_IMAGE_HEADER_SIGNATURE) {
      
      //Measure TE Image
      if(HashPolicy == TREE_BOOT_HASH_ALG_SHA1){
          MeasureTeImage(ImageLoad, HashPolicy, Sha1Digest.digest, Sha2DigestArray);
          gBS->CopyMem(&TcgEvent.Digests.digests.sha1, Sha1Digest.digest, SHA1_DIGEST_SIZE);
       }
       
       if(HashPolicy == TREE_BOOT_HASH_ALG_SHA256){
         MeasureTeImage(ImageLoad, HashPolicy, Sha1Digest.digest, Sha2DigestArray);
         gBS->CopyMem(&TcgEvent.Digests.digests.sha256, Sha2DigestArray, SHA256_DIGEST_SIZE);
         gBS->CopyMem(&TcgEvent.Digests.digests.sha1, Sha1Digest.digest, SHA1_DIGEST_SIZE);
       }
       
    goto TEImageDone;
  }

  //
  // PE/COFF Image Measurement
  //
  //    NOTE: The following codes/steps are based upon the authenticode image hashing in 
  //      PE/COFF Specification 8.0 Appendix A.
  //      
  //

  // 1. Load the image header into memory.
  
  // 2. Initialize a SHA hash context.
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA1){ SHA1Init(&Sha1Ctx);}
  
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA256)
  {
    sha256_init( &Sha2Ctx );
    SHA1Init(&Sha1Ctx);
  }
  

  //
  // Measuring PE/COFF Image Header; 
  // But CheckSum field and SECURITY data directory (certificate) are excluded
  //
  Hdr   = (EFI_IMAGE_NT_HEADERS64 *)((UINT8 *)(UINTN)ImageAddress + PeCoffHeaderOffset);

  //
  // 3. Calculate the distance from the base of the image header to the image checksum address.
  // 4. Hash the image header from its base to beginning of the image checksum.
  //
  HashBase = (UINT8 *)(UINTN)ImageAddress;
  HashSize = (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.CheckSum) - HashBase);
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA1){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }
  
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA256){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }



  //
  // 5. Skip over the image checksum (it occupies a single ULONG).
  // 6. Get the address of the beginning of the Cert Directory.
  // 7. Hash everything from the end of the checksum to the start of the Cert Directory.
  //
  HashBase = (UINT8 *) &Hdr->OptionalHeader.CheckSum + sizeof (UINT32);
  HashSize = (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]) - HashBase);

  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA1){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }
  
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA256){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }

  //
  // 8. Skip over the Cert Directory. (It is sizeof(IMAGE_DATA_DIRECTORY) bytes.)
  // 9. Hash everything from the end of the Cert Directory to the end of image header.
  //
  HashBase = (UINT8 *) &Hdr->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1];
  HashSize = Hdr->OptionalHeader.SizeOfHeaders - 
             (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1]) - (UINT8 *)(UINTN)ImageAddress);
  
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA1){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }
  
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA256){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
  }


  //
  // 10. Set the SUM_OF_BYTES_HASHED to the size of the header 
  //
  SumOfBytesHashed = Hdr->OptionalHeader.SizeOfHeaders;

  //
  // 11. Build a temporary table of pointers to all the IMAGE_SECTION_HEADER 
  //     structures in the image. The 'NumberOfSections' field of the image 
  //     header indicates how big the table should be. Do not include any 
  //     IMAGE_SECTION_HEADERs in the table whose 'SizeOfRawData' field is zero.   
  //
  gBS ->AllocatePool(EfiBootServicesData,sizeof (EFI_IMAGE_SECTION_HEADER) * Hdr->FileHeader.NumberOfSections, &SectionHeader);

  if(SectionHeader==NULL)return EFI_OUT_OF_RESOURCES;
  gBS->SetMem(SectionHeader, (sizeof (EFI_IMAGE_SECTION_HEADER) * Hdr->FileHeader.NumberOfSections), 0);

  //
  // 12.    Using the 'PointerToRawData' in the referenced section headers as 
  //      a key, arrange the elements in the table in ascending order. In other 
  //      words, sort the section headers according to the disk-file offset of 
  //      the section.
  //
  Section = (EFI_IMAGE_SECTION_HEADER *) (
               (UINT8 *)(UINTN)ImageAddress +
               PeCoffHeaderOffset +
               sizeof(UINT32) + 
               sizeof(EFI_IMAGE_FILE_HEADER) + 
               Hdr->FileHeader.SizeOfOptionalHeader
               );  
  for (Index = 0; Index < Hdr->FileHeader.NumberOfSections; Index++) {
    iPos = Index;
    while ((iPos > 0) && (Section->PointerToRawData < SectionHeader[iPos - 1].PointerToRawData)) {
      gBS->CopyMem (&SectionHeader[iPos], &SectionHeader[iPos - 1], sizeof(EFI_IMAGE_SECTION_HEADER));
      iPos--;
    }
      gBS->CopyMem( &SectionHeader[iPos], Section,
                    sizeof(EFI_IMAGE_SECTION_HEADER));
    Section += 1;    
  }
  
  //
  // 13.    Walk through the sorted table, bring the corresponding section 
  //      into memory, and hash the entire section (using the 'SizeOfRawData' 
  //      field in the section header to determine the amount of data to hash).
  // 14.    Add the section's 'SizeOfRawData' to SUM_OF_BYTES_HASHED .
  // 15.    Repeat steps 13 and 14 for all the sections in the sorted table.
  //
  for (Index = 0; Index < Hdr->FileHeader.NumberOfSections; Index++) {
    Section  = (EFI_IMAGE_SECTION_HEADER *) &SectionHeader[Index];
    if (Section->SizeOfRawData == 0) {
      continue;
    }
    HashBase = (UINT8 *)(UINTN)ImageAddress + Section->PointerToRawData;
    HashSize = (UINTN) Section->SizeOfRawData;

    if(HashPolicy == TREE_BOOT_HASH_ALG_SHA1){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
    }
    
    if(HashPolicy == TREE_BOOT_HASH_ALG_SHA256){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
    }


    SumOfBytesHashed += HashSize;
  }    

  //
  // 16.    If the file size is greater than SUM_OF_BYTES_HASHED, there is extra
  //      data in the file that needs to be added to the hash. This data begins 
  //      at file offset SUM_OF_BYTES_HASHED and its length is:
  //             FileSize  -  (CertDirectory->Size)
  //
  if (ImageSize > SumOfBytesHashed) {
    HashBase = (UINT8 *)(UINTN)ImageAddress + SumOfBytesHashed;
    HashSize = (UINTN)(ImageSize -
               Hdr->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY].Size -
               SumOfBytesHashed);
    
    if(HashPolicy == TREE_BOOT_HASH_ALG_SHA1){
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
    }
    
    if(HashPolicy == TREE_BOOT_HASH_ALG_SHA256){
     sha256_process( &Sha2Ctx, HashBase, (u32)HashSize );
     SHA1Update(&Sha1Ctx,
                HashBase,
                (u32)HashSize);
    }
  }

  //
  // 17.    Finalize the SHA hash.
  //
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA1){
    SHA1Final(Sha1Digest.digest, &Sha1Ctx);
    gBS->CopyMem(&TcgEvent.Digests.digests.sha1, Sha1Digest.digest, SHA1_DIGEST_SIZE);
  }
  
  if(HashPolicy == TREE_BOOT_HASH_ALG_SHA256){
    sha256_done( &Sha2Ctx, Sha2DigestArray );
    gBS->CopyMem(&TcgEvent.Digests.digests.sha256, Sha2DigestArray, SHA256_DIGEST_SIZE);
    SHA1Final(Sha1Digest.digest, &Sha1Ctx);
    gBS->CopyMem(&TcgEvent.Digests.digests.sha1, Sha1Digest.digest, SHA1_DIGEST_SIZE);
  }
  
 TEImageDone:
    
  //
  // HashLogExtendEvent 
  //
  gBS->CopyMem(EventData, ImageLoad, TcgEvent.EventSize);

  Status = gBS->LocateProtocol(&gEfiAmiHLXEGuid, NULL, &InternalHLXE);
  if(EFI_ERROR(Status))return Status;
  
  if(TrEEProtocolInstance == NULL){
      Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, &TrEEProtocolInstance);
      if(EFI_ERROR(Status))return Status;
  }

  InternalHLXE->AmiHashLogExtend2(TrEEProtocolInstance, NULL, 0, 0, &TcgEvent, EventData);

  if(ImageType == EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION)
  {
     FindandMeasureSecureBootCertificate();
  }

Done:
  if (ImageLoad != NULL) {
    gBS->FreePool (ImageLoad);
  }

  if (SectionHeader != NULL) {
    gBS->FreePool (SectionHeader);
  }
  return Status;
}

EFI_STATUS
InternalMeasureAction (
  IN      CHAR8                     *ActionString
  )
{
   return EFI_SUCCESS; //not supported
}

EFI_STATUS
InternalMeasureGpt (
  IN      EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{

    return EFI_SUCCESS; //not supported;
}


EFI_TCG_PLATFORM_PROTOCOL  mTcgPlatformProtocol = {
  TreeMeasurePeImage,
  InternalMeasureAction,
  InternalMeasureGpt
};


EFI_STATUS InstallTcgPlatformProtocol(
    VOID    
)
{

 EFI_GUID  gEfiTcgPrivateInterfaceGuid = EFI_TCG_PLATFORM_PROTOCOL_GUID;

 return gBS->InstallProtocolInterface (
                &PlatformProtocolHandle,
                &gEfiTcgPrivateInterfaceGuid,
                EFI_NATIVE_INTERFACE,
                &mTcgPlatformProtocol
                );

}


VOID
EFIAPI
TrEEOnReadyToBoot (
  IN      EFI_EVENT                 Event,
  IN      VOID                      *Context
  )
{
    ReadyToBootSignaled = TRUE;
}

VOID ReadMORValue( );


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TreeDxeEntry
//
// Description: TreeDxeEntry
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
EFIAPI TreeDxeEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS          Status;
    TCG_PLATFORM_SETUP_PROTOCOL     *PolicyInstance;
    EFI_GUID            gPolicyguid = TCG_PLATFORM_SETUP_POLICY_GUID;
    EFI_EVENT           ReadyToBootEvent;
    TCG_CONFIGURATION   Config;
    static              EFI_EVENT      Resetev;
    static      void    * Resetreg;
    static EFI_RESET_TYPE ptype;
    
    DEBUG(( -1," TreeDxeEntry \n"));
    Status = gBS->LocateProtocol (&gPolicyguid,  NULL, &PolicyInstance);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    
            
    gBS-> CopyMem(&Config, &PolicyInstance->ConfigFlags, sizeof(TCG_CONFIGURATION));
    
    if(Config.DeviceType == 0){
        Config.Tpm20Device = 0;   
        PolicyInstance->UpdateStatusFlags(&Config, FALSE);
        return EFI_SUCCESS;
    }
    
    if(!PolicyInstance->ConfigFlags.TpmSupport){
        return EFI_SUCCESS;
    }
          
    if(!IsTpm20Device()){
        Config.Tpm20Device = 0;  
        if(Config.DeviceType == 1){
        }
        PolicyInstance->UpdateStatusFlags(&Config, FALSE); 
        DEBUG(( -1," isTpm20CrbPresent returned false \n"));
        return EFI_UNSUPPORTED;
    }

    Config.Tpm20Device = 1;
    Config.InterfaceSel = TpmSupport->InterfaceType;

    ReadMORValue();
    
    Status = InstallTrEEProtocol(ImageHandle);
    if(EFI_ERROR(Status))return EFI_ABORTED;
    
    Tpm2GetCapabilityCapPCRS();
    
    DEBUG(( -1," ActiveBankBitMap = %x\n", ActiveBankBitMap));
    DEBUG(( -1," Config.PcrBanks = %x\n", Config.PcrBanks));
    
    if(((TcgSupportedBankBitMap & Config.PcrBanks)& ActiveBankBitMap) != (ActiveBankBitMap | (TcgSupportedBankBitMap & Config.PcrBanks))){
        Status = Tpm2AllocatePCR( Config.PcrBanks, ActiveBankBitMap, TcgSupportedBankBitMap);
        
        gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
        DEBUG((-1, "\tError: Reset failed???\n"));
        
        Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                     EFI_TPL_CALLBACK, DoResetNow, NULL, &Resetev);
    
        ASSERT( !EFI_ERROR( Status ));
        Status = gBS->RegisterProtocolNotify(&gEfiResetArchProtocolGuid, Resetev, &Resetreg);
        DEBUG((-1, "\tRegister DoResetNow after Reset Architecture driver\n"));
    }

     //install binding protocol TrEE binding protocol
    Tpm20DriverBinding.DriverBindingHandle = ImageHandle;
    Tpm20DriverBinding.ImageHandle = ImageHandle;

    Status = gBS->InstallMultipleProtocolInterfaces (
                               &Tpm20DriverBinding.DriverBindingHandle,
                               &gEfiDriverBindingProtocolGuid, &Tpm20DriverBinding,
                               &gEfiComponentNameProtocolGuid, &gComponentName,
                               &gEfiComponentName2ProtocolGuid, &gComponentName2,
                                NULL);
    
    InstallTcgPlatformProtocol();

    TrEEUpdateTpmDeviceASL(Event, reg);
    Config.TcgSupportEnabled = 1;
    Config.TcmSupportEnabled = 0;
    Config.TpmHardware = 0; // Hardware Present
    
    Status = EfiCreateEventReadyToBootEx(TPL_CALLBACK,
                                        TrEEOnReadyToBoot, 
                                        NULL, 
                                        &ReadyToBootEvent);
     
    if(EFI_ERROR(Status))return Status;
        
    
    Status = PolicyInstance->UpdateStatusFlags(&Config, FALSE); 
    return Status;
}

typedef VOID (*tdTpmtHaProc)( UINT8* pTpmtHa, VOID* CallBackContext );

UINTN GetNextSMLEvent(MiscPCR_EVENT_HDR* pStart, MiscPCR_EVENT_HDR** pNext)
{
    UINT8*          _pStart = (UINT8*)pStart;
    UINTN           unIdx = 0;

    *pNext = (MiscPCR_EVENT_HDR*)(_pStart + sizeof( MiscPCR_EVENT_HDR ) + pStart->EventSize );

    if( !(*pNext)->EventType && !(*pNext)->EventSize )
        return -1;

    if( (UINTN)(*pNext) > LastEntry )
        return -1;

    return *pNext - pStart;
}

UINTN GetSize_TpmpHa( UINT8* pStart, UINT8** pNext, tdTpmtHaProc TpmtHaProc, VOID *CallBackContext )
{
    UINT8*      pBuf = pStart;
    UINTN       DigestSize;
    UINT16      AlgorithmId;

    AlgorithmId = *(UINT16*)pBuf;
//    AlgorithmId = TPM_H2NS( AlgorithmId );
    switch( AlgorithmId )
    {
        case TPM2_ALG_SHA1:
            DigestSize = SHA1_DIGEST_SIZE;
        break;
        case  TPM2_ALG_SHA256:
            DigestSize = SHA256_DIGEST_SIZE;
        break;
        case TPM2_ALG_SHA384:
            DigestSize = SHA384_DIGEST_SIZE;
        break;
        case TPM2_ALG_SHA512:
            DigestSize = SHA512_DIGEST_SIZE;
        break;
        default:
            DigestSize = -1;
            // The Digest AlgorithmId Err.
            return -1;
        break;
    }

    if( TpmtHaProc )
    {
        TpmtHaProc( pStart, CallBackContext );
    }

    pBuf += sizeof(UINT16);     // AlgorithmId
    pBuf += DigestSize;         // Digest

    *pNext = pBuf;

    return (UINTN)( pBuf - pStart );

}

UINTN   GetSize_TpmlDigestValues( UINT8* pStart, UINT8** pNext, tdTpmtHaProc TpmtHaProc, VOID *CallBackContext )
{
    UINT8*      pBuf = pStart;
    UINTN       unIdx;
    UINTN       Count;

    Count = *(UINT32*)pBuf;
    pBuf += sizeof(UINT32);     // Count

    for( unIdx=0; unIdx<Count; ++unIdx)
    {
        if( -1 == GetSize_TpmpHa( pBuf, &pBuf, TpmtHaProc, CallBackContext ) )
        {
            // The Struct Parsing Err.
            return -1;
        }

    }

    *pNext = pBuf;

    return (UINTN)( pBuf - pStart );
}

VOID ExtraSha1FromTpmHa( UINT8* pTpmtHa, VOID* pCopyStartBuf )
{
    UINT8*      pBuf = pTpmtHa;
    UINT8*      pDigest = (UINT8*)pCopyStartBuf;
    UINTN       DigestSize;
    UINT16      AlgorithmId;

    AlgorithmId = *(UINT16*)pBuf;

//    AlgorithmId = TPM_H2NS( AlgorithmId );
    switch( AlgorithmId )
    {
        case TPM2_ALG_SHA1:
            DigestSize = SHA1_DIGEST_SIZE;
        break;
        case  TPM2_ALG_SHA256:
            DigestSize = SHA256_DIGEST_SIZE;
        break;
        case TPM2_ALG_SHA384:
            DigestSize = SHA384_DIGEST_SIZE;
        break;
        case TPM2_ALG_SHA512:
            DigestSize = SHA512_DIGEST_SIZE;
        break;
        default:
            DigestSize = -1;
            // The Digest AlgorithmId Err.
            return;
        break;
    }

    pBuf += sizeof(UINT16);

    if( SHA1_DIGEST_SIZE == DigestSize )
    {
        gBS->CopyMem( pCopyStartBuf, pBuf, SHA1_DIGEST_SIZE );
    }
}

UINTN  ExtractSingleTcpaEventFromTcgEVENT2( UINT8* pStart, UINT8** pNext, UINT8 *pCopyStartBuf  )
{
    UINT8*          pBuf = pStart;
    UINTN           EventSize = 0;
    UINT8*          pCopyBuf = pCopyStartBuf;
    UINTN           unTmpOffset = 0;

    EFI_STATUS  Status;
    EFI_STATUS GetNextSMLEvent(MiscPCR_EVENT_HDR* pStart, MiscPCR_EVENT_HDR** pNext);

    if( ((MiscPCR_EVENT_HDR*)pStart)->EventType == 0x03 && pStart == (UINT8*)TreeEventLogLocation ) // EV_NO_ACTION
    {
//        bLogFirstActEvent = TRUE;
        Status = GetNextSMLEvent( (MiscPCR_EVENT_HDR*)pStart, (MiscPCR_EVENT_HDR**)pNext );
        if( EFI_ERROR(Status) )
        {
            DEBUG(( -1, "Error[%d]: \n", __LINE__ ));
            return -1;
        }

//        return (UINTN)( (*pNext) - pStart );
        return 0;
    }

    *(UINT32*)(pCopyStartBuf + unTmpOffset)  = *(UINT32*)(pStart + unTmpOffset);   // PCRIndex
    unTmpOffset += sizeof(UINT32);

    *(UINT32*)(pCopyStartBuf + unTmpOffset) = *(UINT32*)(pStart + unTmpOffset);   // EventType
    unTmpOffset += sizeof(UINT32);

    pBuf = pStart + unTmpOffset;
    pCopyBuf = pCopyStartBuf + unTmpOffset;
    if( -1 == GetSize_TpmlDigestValues( pBuf, &pBuf, ExtraSha1FromTpmHa, pCopyBuf ) )    // Digests
    {
        // The Struct Detect Err.
        return -1;
    }
    unTmpOffset += SHA1_DIGEST_SIZE;

    EventSize = *(UINT32*)(pBuf);
    *(UINT32*)(pCopyStartBuf + unTmpOffset) = (UINT32)EventSize;
    pBuf += sizeof(UINT32);
    unTmpOffset += sizeof(UINT32);     // EventSize

    gBS->CopyMem( pCopyStartBuf + unTmpOffset, pBuf, EventSize );
    unTmpOffset += EventSize;          // EventData
    pBuf += EventSize;

    *pNext = pBuf;

    return unTmpOffset;
}

UINTN TransferTcgEvent2ToTcpaEvent( VOID )
{
    EFI_STATUS                          Status = EFI_SUCCESS;
    UINT8*                              pNext = NULL;
    UINT8*                              pCopyBuf = (UINT8*)TreeExtraTCPASha1LogLoc;
    UINTN                               SingleEventSize = 0;

    pNext = (UINT8*)TreeEventLogLocation;
    for(SingleEventSize = 0; -1 != SingleEventSize; )
    {
        pCopyBuf += SingleEventSize;

        if( (UINTN)pNext >= (UINTN)LastEventPtr )
        {
            if(  (UINTN)pNext == (UINTN)LastEventPtr )
            {
                SingleEventSize = ExtractSingleTcpaEventFromTcgEVENT2( pNext, &pNext, pCopyBuf );
            }
            break;
        }

        SingleEventSize = ExtractSingleTcpaEventFromTcgEVENT2( pNext, &pNext, pCopyBuf );
    };

    return (UINTN)pCopyBuf;
}

//
// <+ End of Extract the TCPA Sha1 Log from Crypto Agile Log Event
//
