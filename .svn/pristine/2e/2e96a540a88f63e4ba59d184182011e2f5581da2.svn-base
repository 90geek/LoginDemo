//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgDxe.c
//
// Description: 
//  Abstracted functions for Tcg protocol are defined here
//
//<AMI_FHDR_END>
//*************************************************************************
#include <AmiTcg\TcgCommon.h>
#include <AmiTcg\sha.h>
#include <AmiTcg\TcgMisc.h>
#include <AmiTcg\Tpm20.h>
#include <AmiTcg\TrEEProtocol.h>
#include <Token.h>
#include <protocol\TcgTcmService.h>
#include <protocol\TcgPlatformSetupPolicy.h>
#include <protocol\AcpiSupport.h>
#include "AmiTcg\TcgPc.h"
#include "protocol\TcgService.h"
#include "protocol\TpmDevice.h"
#include<Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#if defined (RomLayout_SUPPORT) && (RomLayout_SUPPORT!=0)
#include <Library/AmiRomLayoutLib.h>
#endif
#include <Library/TimerLib.h>
#include <Library/LocalApicLib.h>
#include <industrystandard/Acpi30.h>
#include <Protocol\Runtime.h>
#include <Library\UefiLib.h>
#include <Library\HobLib.h>
#include <Guid\MemoryOverwriteControl.h>
#include <Protocol\FirmwareVolumeBlock.h>

#include <AmiProtocol.h>

#if PI_SPECIFICATION_VERSION<0x00010000
#include <Protocol\FirmwareVolume.h>
#else
#include <Protocol\FirmwareVolume2.h>
#endif


EFI_GUID gEfiAmiHLXEGuid =  AMI_PROTOCOL_INTERNAL_HLXE_GUID;

#define SHA1_DIGEST_SIZE    20
#define SHA256_DIGEST_SIZE  32

EFI_EVENT                  Event;
static VOID                *reg;
EFI_EVENT                  Event2;
static VOID                *reg2;
UINT8                      DigestAlgo=0;
UINT8                      Sha1Digest[SHA1_DIGEST_SIZE];
UINT8                      Sha2Digest[SHA256_DIGEST_SIZE];

UINT8  GetHashPolicy();

#pragma pack (1)
typedef struct
{
    EFI_PHYSICAL_ADDRESS PostCodeAddress;
    #if x64_TCG
    UINT64               PostCodeLength;
    #else
    UINTN                PostCodeLength;
    #endif
} EFI_TCG_EV_POST_CODE;

EFI_TCG_EV_POST_CODE       PhysicalAddressBases;

typedef struct
{
    EFI_TCG_PCR_EVENT_HEADER Header;
    EFI_TCG_EV_POST_CODE     Event;
} PEI_EFI_POST_CODE;


typedef struct {
    BYTE  sha1[SHA1_DIGEST_SIZE];  
    BYTE  sha256[SHA256_DIGEST_SIZE];  
} TPM2_HALG;

typedef struct {
    UINT32     count;
    TPM2_HALG   digests;
} TPM2_DIGEST_VALUES;

typedef struct{
   TCG_PCRINDEX         PCRIndex;
   TCG_EVENTTYPE        EventType;
   TPM2_DIGEST_VALUES   Digests;
   UINT32               EventSize; // UINT32 aligned
} TCG_PCR_EVENT2_HDR; 

typedef struct{
   TCG_PCR_EVENT2_HDR   hdr;
   UINT8                Event[1];
} TCG_PCR_EVENT2; 


typedef struct _AMI_INTERNAL_HLXE_PROTOCOL  AMI_INTERNAL_HLXE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI * INTERNAL_HASH_LOG_EXTEND_EVENT) (
  IN  EFI_TREE_PROTOCOL        *This,
  IN  UINT8                    *DataToHash,
  IN  UINT64                   Flags,
  IN  UINTN                    DataSize,
  IN  OUT  TCG_PCR_EVENT2_HDR  *NewEventHdr,
  IN  UINT8                    *NewEventData
);

struct _AMI_INTERNAL_HLXE_PROTOCOL {
    INTERNAL_HASH_LOG_EXTEND_EVENT  AmiHashLogExtend2;
};

#pragma pack()

void printbuffer(UINT8 *Buffer, UINTN BufferSize)
{
    UINTN i=0; UINTN j=0;
    
    DEBUG ((-1, "Buffer  = %x  \n", Buffer));
    DEBUG ((-1, "BufferSize  = %x  \n", BufferSize));
                
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


EFI_STATUS
__stdcall Tpm12ProtocolExtend(
    EFI_TCG_PROTOCOL                  *TcgProtocol,
    TPM_PCRINDEX PCRIndex)
{
    EFI_STATUS          Status;
    UINT8               *commandbuff;
    UINT8               *buffer;
    UINT8               *returnbuff;
    UINT32               cmdLen=0, retLen=0;

    DEBUG((-1,"Tpm1_2 Extend\n"));
 
    cmdLen = sizeof(TPM_1_2_CMD_HEADER) + sizeof(UINT32) + SHA1_DIGEST_SIZE;
    
    Status = gBS->AllocatePool(EfiBootServicesData, cmdLen , &commandbuff );
    if(EFI_ERROR(Status))return Status;
    
    retLen = sizeof(TPM_1_2_RET_HEADER) + sizeof(UINT32) + SHA1_DIGEST_SIZE;
    
    Status = gBS->AllocatePool(EfiBootServicesData, retLen , &returnbuff );
    if(EFI_ERROR(Status))return Status;
    
    buffer = commandbuff;

    ((TPM_1_2_CMD_HEADER *)buffer)->Tag       = TPM_H2NS( TPM_TAG_RQU_COMMAND );
    ((TPM_1_2_CMD_HEADER *)buffer)->ParamSize = cmdLen;
    ((TPM_1_2_CMD_HEADER *)buffer)->Ordinal = TPM_H2NL( TPM_ORD_Extend );
    
    buffer+= sizeof (TPM_1_2_CMD_HEADER);
    
    (*(UINT32 *)buffer) = TcgCommonH2NL( PCRIndex );
    buffer+=sizeof(UINT32);
    
    gBS->CopyMem(buffer, Sha1Digest, SHA1_DIGEST_SIZE);
    
    Status = TcgProtocol->PassThroughToTpm(TcgProtocol,cmdLen,
                        commandbuff, retLen, returnbuff );
   
    DEBUG((-1,"Tpm1_2 PassThroughToTpm Status = %r  \n", Status));
    
    DEBUG((-1,"((TPM_1_2_RET_HEADER *)returnbuff)->RetCode = %x \n", 
                                            ((TPM_1_2_RET_HEADER *)returnbuff)->RetCode));
    
    if(((TPM_1_2_RET_HEADER *)returnbuff)->RetCode){
        return EFI_DEVICE_ERROR;
    }
    
    return Status;
}

VOID CallbackOnTcgprotocolInstall(IN EFI_EVENT event,
                           IN VOID      *ctx)
{
    EFI_STATUS                        Status;
    EFI_TCG_PROTOCOL                  *TcgProtocol;
    PEI_EFI_POST_CODE                 ev;
    UINTN                             i=0;
    UINT32                             EventNumber;


    DEBUG ((-1, "CallbackOnTcgprotocolInstall Entry\n"));
    
    Status = gBS->LocateProtocol(&gEfiTcgProtocolGuid,
                                 NULL,
                                 &TcgProtocol);
    
    if(EFI_ERROR(Status))return;
    
    ev.Header.PCRIndex      = PCRi_CRTM_AND_POST_BIOS;
    ev.Header.EventType     = EV_POST_CODE;
    ev.Header.EventDataSize = sizeof (EFI_TCG_EV_POST_CODE);
    ev.Event.PostCodeAddress = \
                       (EFI_PHYSICAL_ADDRESS)PhysicalAddressBases.PostCodeAddress;
                
    //Status = Tpm12ProtocolExtend(TcgProtocol, 0);
                
    //DEBUG ((-1, " Tpm12ProtocolExtend Status = %r \n", Status));
    //printbuffer((UINT8 *)&ev, sizeof(PEI_EFI_POST_CODE));
    gBS->CopyMem(&ev.Header.Digest, Sha1Digest, SHA1_DIGEST_SIZE);
    Status = TcgProtocol->LogEvent(TcgProtocol, (TCG_PCR_EVENT *)&ev, &EventNumber,0x00);
    if(EFI_ERROR(Status))return;

}




VOID CallbackOnTreeInstall(IN EFI_EVENT ev,
                           IN VOID      *ctx)
{
    EFI_STATUS                        Status;
    EFI_TREE_PROTOCOL                 *pTreeProtocol  =  NULL;
    EFI_GUID  gEfiTrEEProtocolGuid  = EFI_TREE_PROTOCOL_GUID;
    AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;
    TCG_PCR_EVENT2_HDR                Tcg20Event;
    EFI_TCG_EV_POST_CODE              EventData;
    UINTN                             i=0;


    DEBUG ((-1, "CallbackOnTreeInstall Entry\n"));
    
    Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid,
                                 NULL,
                                 &pTreeProtocol);
        
    Status = gBS->LocateProtocol(&gEfiAmiHLXEGuid, NULL, &InternalHLXE);
    if(EFI_ERROR(Status))return;
    
    EventData.PostCodeAddress = PhysicalAddressBases.PostCodeAddress;
    EventData.PostCodeLength  = PhysicalAddressBases.PostCodeLength;
            
    Tcg20Event.EventSize = sizeof(EventData);
    Tcg20Event.EventType = EV_POST_CODE;
    Tcg20Event.PCRIndex  = 0;

    
    if(DigestAlgo == TREE_BOOT_HASH_ALG_SHA1){
        gBS->CopyMem(Tcg20Event.Digests.digests.sha1, Sha1Digest, SHA1_DIGEST_SIZE);
        gBS->SetMem(Tcg20Event.Digests.digests.sha256, SHA256_DIGEST_SIZE, 0);
        //printbuffer(Sha1Digest,SHA1_DIGEST_SIZE );
    }else if(DigestAlgo == TREE_BOOT_HASH_ALG_SHA256){
    	gBS->CopyMem(Tcg20Event.Digests.digests.sha1, Sha1Digest, SHA1_DIGEST_SIZE);
        gBS->CopyMem(Tcg20Event.Digests.digests.sha256, Sha2Digest, SHA256_DIGEST_SIZE);
        //printbuffer(Sha2Digest,SHA256_DIGEST_SIZE );
    }
     
    DEBUG ((-1, "AmiHashLogExtend2 FwVol\n"));
    DEBUG ((-1, "sizeof(TCG_PCR_EVENT2_HDR) = %x\n", sizeof(TCG_PCR_EVENT2_HDR)));
    //printbuffer((UINT8 *)&Tcg20Event,sizeof(TCG_PCR_EVENT2_HDR));
    InternalHLXE->AmiHashLogExtend2(pTreeProtocol, NULL, 0,0, &Tcg20Event, (UINT8 *)&EventData); 
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

//#define TREE_BOOT_HASH_ALG_SHA1   0x00000001
//#define TREE_BOOT_HASH_ALG_SHA256 0x00000002
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgHookCoreinit
//
// Description: Hashes FVMain Volume
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
void TcgHookCoreinit(IN EFI_HANDLE        ImageHandle,
                     IN EFI_SYSTEM_TABLE  *SystemTable)
{   
    EFI_STATUS Status;
    SHA1_CTX     Sha1Ctx;
    SHA2_CTX       Sha2Ctx;
    UINT8        j=0,i=0;
    FwVolHob    *TpmFwVolHob;
    UINTN        FwVolHobCount;
    EFI_PEI_HOB_POINTERS          FvHob;
    UINTN        MeasuredCount=0;
    EFI_GUID     amiFVhoblistguid = AMI_FV_HOB_LIST_GUID;
    
    
    DEBUG ((-1, "TcgHookCoreinit Entry\n"));
        
    TpmFwVolHob = LocateATcgHob( gST->NumberOfTableEntries,
                               gST->ConfigurationTable,
                               &amiFVhoblistguid);
    
    if(TpmFwVolHob == NULL)return;
             
    DEBUG ((-1, "SHA1Init done\n"));
    FwVolHobCount = TpmFwVolHob->Count;
    
    
    if(FwVolHobCount == 0) return;
    
    DEBUG ((-1, "FwVolHobCount = %x \n", FwVolHobCount));
    
    DigestAlgo = TpmFwVolHob->Algorithm;
    if(TpmFwVolHob->Algorithm == TREE_BOOT_HASH_ALG_SHA1){
        SHA1Init( &Sha1Ctx );
    }else if(TpmFwVolHob->Algorithm == TREE_BOOT_HASH_ALG_SHA256){
        sha256_init(&Sha2Ctx);
        SHA1Init( &Sha1Ctx );
    }
    
    FvHob.Raw = GetHobList ();
    DEBUG ((-1, "TpmFwVolHob->Algorithm = %x \n", TpmFwVolHob->Algorithm));
    while ((FvHob.Raw = GetNextHob (EFI_HOB_TYPE_FV, FvHob.Raw)) != NULL) {
    
        for(i=0; i<FwVolHobCount; i++){
          if(TpmFwVolHob[i].baseAddress == FvHob.FirmwareVolume->BaseAddress || 
             TpmFwVolHob[i].Size == FvHob.FirmwareVolume->Length){
              if(TpmFwVolHob->Algorithm == TREE_BOOT_HASH_ALG_SHA1){
                  DEBUG ((-1, "SHA1Update FwVol hob \n"));
                  DEBUG ((-1, "(u32)FvHob.FirmwareVolume->Length  = %x  \n", (u32)FvHob.FirmwareVolume->Length ));
                  DEBUG ((-1, "(u32)FvHob.FirmwareVolume->BaseAddres  = %x  \n", (u32)FvHob.FirmwareVolume->BaseAddress));
                  //printbuffer((UINT8 *)FvHob.FirmwareVolume->BaseAddress,FvHob.FirmwareVolume->Length );
                  SHA1Update( &Sha1Ctx, (unsigned char *)FvHob.FirmwareVolume->BaseAddress, (u32)FvHob.FirmwareVolume->Length );
                  MeasuredCount+=1;
              }else if(TpmFwVolHob->Algorithm == TREE_BOOT_HASH_ALG_SHA256){
                  DEBUG ((-1, "sha256_process FwVol hob \n"));
                  DEBUG ((-1, "(u32)FvHob.FirmwareVolume->Length  = %x  \n", (u32)FvHob.FirmwareVolume->Length ));
                  DEBUG ((-1, "(u32)FvHob.FirmwareVolume->BaseAddres  = %x  \n", (u32)FvHob.FirmwareVolume->BaseAddress));
                  //printbuffer((UINT8 *)FvHob.FirmwareVolume->BaseAddress,FvHob.FirmwareVolume->Length );
                  sha256_process( &Sha2Ctx, (unsigned char *)FvHob.FirmwareVolume->BaseAddress, (u32)FvHob.FirmwareVolume->Length );
                  SHA1Update( &Sha1Ctx, (unsigned char *)FvHob.FirmwareVolume->BaseAddress, (u32)FvHob.FirmwareVolume->Length );
                  MeasuredCount+=1;
              }
          }
       }
       FvHob.Raw = GET_NEXT_HOB (FvHob);
    }
       
    DEBUG ((-1, "MeasuredCount = %x \n", MeasuredCount));
       
    if(MeasuredCount == FwVolHobCount){
        if(DigestAlgo == TREE_BOOT_HASH_ALG_SHA1){
            SHA1Final((unsigned char *)Sha1Digest, &Sha1Ctx);
            //printbuffer(Sha1Digest,SHA1_DIGEST_SIZE );
         }else if(DigestAlgo == TREE_BOOT_HASH_ALG_SHA256){
            sha256_done(&Sha2Ctx,(unsigned char *)Sha2Digest);
            SHA1Final((unsigned char *)Sha1Digest, &Sha1Ctx);
            //printbuffer(Sha2Digest,SHA256_DIGEST_SIZE );
         }
       
         //hashlogexend digest
         PhysicalAddressBases.PostCodeAddress = TpmFwVolHob[0].baseAddress;
         PhysicalAddressBases.PostCodeLength  = TpmFwVolHob[0].Size;
           
         Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                  EFI_TPL_CALLBACK, CallbackOnTreeInstall, &reg, &Event );

         if(EFI_ERROR(Status)){
              DEBUG((-1, "Unable to create Event..Exit(1)\n"));
               return;
         }
          
         Status = gBS->RegisterProtocolNotify( &gEfiAmiHLXEGuid, Event, &reg );  
         DEBUG ((-1, "TcgHookCoreinit::RegisterProtocolNotify Status = %r\n", Status));
         
         Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                           EFI_TPL_CALLBACK, CallbackOnTcgprotocolInstall, &reg2, &Event2);

         if(EFI_ERROR(Status)){
             DEBUG((-1, "Unable to create Event..Exit(1)\n"));
             return;
         }
                   
         Status = gBS->RegisterProtocolNotify( &gEfiTcgProtocolGuid, Event2, &reg2);  
         DEBUG ((-1, "TcgHookCoreinit::RegisterProtocolNotify Status = %r\n", Status));
    }
        
    return;
}
