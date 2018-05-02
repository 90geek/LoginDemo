//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Tools/template.h 6     1/13/10 2:13p Felixp $
//
// $Revision: 6 $
//
// $Date: 1/13/10 2:13p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Tools/template.h $
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
/** @file AmiTbtNvs.h
    AMI Thunderbolt GNVS header file, define all Thunderbolt GNVS variable
    and GNVS structure in this file
    
**/
#ifndef __AMI_TBT_NVS_H__
#define __AMI_TBT_NVS_H__
#ifdef __cplusplus
extern "C" {
#endif

#define AMI_TBT_NVS_PROTOCOL_GUID { 0xba1d893b, 0x803e, 0x4b26, { 0xa3, 0xde, 0x58, 0x57, 0x3, 0xff, 0x7b, 0x26 } }

#pragma pack (1)
typedef struct _AMI_TBT_NVS_DATA {
    UINT8                   TbtHRSeries;        ///< Record Thunderbolt host chip series
    UINT8                   TbtHRStatus;        ///< Record Thunderbolt host previous status
    UINT8                   TbtWakeupSupport;   ///< Support or not support wake from thunderbolt feature
} AMI_TBT_NVS_DATA;
#pragma pack ()

typedef struct _AMI_TBT_HR_STATUS_NVS_PROTOCOL {
    AMI_TBT_NVS_DATA        *TbtNvsArea;        ///< Thunderbolt GNVS area definition
} AMI_TBT_NVS_PROTOCOL;

extern EFI_GUID gAmiTbtNvsProtocolGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
