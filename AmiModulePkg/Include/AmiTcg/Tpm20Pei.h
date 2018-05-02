#ifndef TPM_2_0_PEI_H
#define TPM_2_0_PEI_H

#include <AmiTcg\Tpm20.h>
#include "PPI\AmiTreePpi.h"
#include <PiPei.h>

#pragma pack(push, 1)

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


typedef struct _TPM2_Startup{
    TPMI_ST_COMMAND_TAG tag;
    UINT32              CommandSize;
    TPM_CC              CommandCode;
    TPM_SU              StartupType;
}TPM2_Startup_Cmd;

typedef struct _TPM2_SelfTest{
    TPMI_ST_COMMAND_TAG tag;
    UINT32              CommandSize;
    TPM_CC              CommandCode;
    TPMI_YES_NO         SelfTestType;
}TPM2_SelfTest;

typedef struct _TPM2_Startup_Resp{
    TPM_ST              tag;
    UINT32              ResponsSize;
    TPM_RC              ResponseCode;
}TPM2_Common_RespHdr;

typedef struct tdTCG_PCClient_PCR_Event2_Hdr{
    UINT32              pcrIndex;
    UINT32              eventType;
    TPML_DIGEST_VALUES  digests;
    UINT32              eventSize;//UINT32 aligned
}TCG_PCClient_PCR_Event2_Hdr;

typedef struct tdTCG_PCClient_PCR_Event2{
    UINT32              pcrIndex;
    UINT32              eventType;
    TPML_DIGEST_VALUES  digests;
    UINT32              eventSize;//UINT32 aligned
    BYTE                event[1]; 
}TCG_PCClient_PCR_Event2;

#pragma pack(pop)


EFI_STATUS Tpm20PeiSendStartup(IN CONST EFI_PEI_SERVICES **PeiServices,
                               AMI_TREE_PPI *TrEEPeiPpi, EFI_BOOT_MODE BootMode);

typedef EFI_STATUS (TPM20_MEASURE_CRTM_VERSION_PEI_FUNC_PTR)(
    IN CONST EFI_PEI_SERVICES **PeiServices, 
    IN AMI_TREE_PPI *TrEEppi
);

extern TPM20_MEASURE_CRTM_VERSION_PEI_FUNC_PTR        *Tpm20MeasureCRTMVersionFuncPtr;
typedef struct _AMI_INTERNAL_HLXE_PPI  AMI_INTERNAL_HLXE_PPI;

typedef
EFI_STATUS
(EFIAPI * INTERNAL_HASH_LOG_EXTEND_EVENT) (
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  IN  AMI_TREE_PPI             *TrEEPpi,
  IN  UINT8                    *DataToHash,
  IN  UINT64                   Flags,
  IN  UINTN                    DataSize,
  IN  OUT  TCG_PCR_EVENT2_HDR  *NewEventHdr,
  IN  UINT8                    *NewEventData
);

struct _AMI_INTERNAL_HLXE_PPI {
    INTERNAL_HASH_LOG_EXTEND_EVENT  AmiHashLogExtendEx;
};

#endif
