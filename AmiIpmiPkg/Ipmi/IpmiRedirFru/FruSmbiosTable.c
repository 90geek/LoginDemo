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

/** @file FruSmbiosTable.c
    Update SMBIOS type 1,2,3 structure

**/

//----------------------------------------------------------------------

#include "IpmiRedirFru.h"
#include <Protocol/Smbios.h>
#include <IndustryStandard/SmBios.h>
#include "Token.h"	//TH0107

//----------------------------------------------------------------------

//
// Macro definitions
//
#define MAX_SMBIOS_STRING_SIZE  0x40

//
// Macro represent size of SmBios structure end.
// Every SmBios type ends with 0x0000.
//
#define SIZE_OF_SMBIOS_STRUCTURE_END_MACRO sizeof(UINT16)

/**
    Convert the Unicode string into Ascii string.

    @param UnicodeStr Unicode string pointer.
    @param AsciiStr Ascii string pointer

    @retval CHAR8* Ascii string pointer.

**/

UINT8
Unicode2AsciiConversion (
  OUT CHAR8    *AsciiStr,
  IN  CHAR16   *UnicodeStr )
{
    UINT8   Length = 0;

    while (TRUE) {
        *AsciiStr = (CHAR8) *(UnicodeStr++);
        Length++;
        if (*(AsciiStr++) == '\0') {
            return Length;
        }
    }
}

/**
    Convert the Valid  Unicode string into Ascii string. If strinig is invalid
    truncate to maximum size and converted.

    @param AsciiStr Ascii string pointer
    @param UnicodeStr Unicode string pointer.

    @retval CHAR8* AsciiStr - Ascii string pointer.

**/

VOID
EFIAPI
GetValidSMBIOSString(
  OUT  CHAR8     *AsciiStr,
  IN   CHAR16    *UnicodeStr)
{
    CHAR16  TempUnicodeString[MAX_SMBIOS_STRING_SIZE];
    UINTN   Length;

    Length = StrSize (UnicodeStr);

    ZeroMem (&TempUnicodeString[0], Length);

    //
    // Validating string size
    //
    if ( Length >= MAX_SMBIOS_STRING_SIZE ) {

        //
        // Truncate size to maximum allowable
        //
        Length = MAX_SMBIOS_STRING_SIZE - 1;
    }
    StrnCpy (TempUnicodeString, UnicodeStr, Length);
    Unicode2AsciiConversion (AsciiStr, TempUnicodeString);
}

/**
    Notification function for SMBIOS protocol.
    Update SMBIOS type 1,2,3 structure.

    @param Event Event which caused this handler
    @param Context Context passed during Event Handler registration

    @retval VOID

**/

VOID
EFIAPI
FruSmbiosTableUpdate (
  IN  EFI_EVENT                     Event,
  IN  VOID                          *Context )
{
    EFI_STATUS                      Status;
    EFI_STATUS                      StatusOfRequestedSmbiosType;
    EFI_SMBIOS_HANDLE               SmbiosHandle;
    EFI_SMBIOS_PROTOCOL             *SmbiosProtocol;
    EFI_SMBIOS_TYPE                 Type;
    EFI_SMBIOS_TABLE_HEADER         *Record;
    SMBIOS_TABLE_TYPE1              *Type1Structure;
    SMBIOS_TABLE_TYPE2              *Type2Structure;
    SMBIOS_TABLE_TYPE3              *Type3Structure;
    UINTN                           StringNumber;
    CHAR16                          *UnicodeString;
    //TH0107  CHAR8                           *SmBiosDefaultString = "To be filled by O.E.M.";
    CHAR8                           *SmBiosDefaultString="NULL";	//TH0107
    CHAR16                          *PcdDefaultString = L"To be filled by O.E.M.To be filled by O.E.M.To be filled by O.E.M.";
    CHAR8                           AsciiString[MAX_SMBIOS_STRING_SIZE];
    EFI_GUID                        *Uuid = NULL;
    EFI_GUID                        DefaultUuid = {0};

    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "In FruSmbiosTableUpdate function...\n"));
    Status = gBS->LocateProtocol (
                &gEfiSmbiosProtocolGuid,
                NULL,
                (VOID **) &SmbiosProtocol);
    DEBUG ((EFI_D_LOAD, "Locate SmbiosProtocol Status:%r \n", Status));
    if (EFI_ERROR (Status)) {
        return;
    }
    Status = gBS->CloseEvent (Event);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "CloseEvent Status:%r \n", Status));
  
    //
    // Smbios Type 1 structure process start
    //
    SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
    Type = 0x01;
    StatusOfRequestedSmbiosType = SmbiosProtocol->GetNext (
                                      SmbiosProtocol,
                                      &SmbiosHandle,
                                      &Type,
                                      &Record,
                                      NULL);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->GetNext Status:%r \n", StatusOfRequestedSmbiosType));
    if (EFI_ERROR(StatusOfRequestedSmbiosType)) {
        //
        // Type 1 structure is not available, needs to be created.
        //
        Type1Structure = AllocateZeroPool (sizeof (SMBIOS_TABLE_TYPE1) + SIZE_OF_SMBIOS_STRUCTURE_END_MACRO);
        if (Type1Structure == NULL) {
            return;
        }
        Type1Structure->Hdr.Type = EFI_SMBIOS_TYPE_SYSTEM_INFORMATION;
        Type1Structure->Hdr.Length = sizeof (SMBIOS_TABLE_TYPE1);
        Type1Structure->Hdr.Handle = 0xFFFF;//To be updated by SMBIOS driver.
    }else {
        Type1Structure = (SMBIOS_TABLE_TYPE1 *)Record;
    }
    Type1Structure->Manufacturer = 0x01;
    Type1Structure->ProductName = 0x02;
    Type1Structure->Version = 0x03;
    Type1Structure->SerialNumber = 0x04;

    //
    // Copy the Uuid
    //
#if UPDATE_UUID_FOLLOW_FRU	//TH0107
    Uuid = (EFI_GUID *)PcdGetPtr (PcdSystemUuid);
    if(AsciiStrCmp ((CONST CHAR8*)Uuid, (CONST CHAR8*)&DefaultUuid)!= 0x00) {
        CopyMem (&(Type1Structure->Uuid), Uuid, sizeof(EFI_GUID));
    }
#endif	//TH0107
    //
    // Creating the Smbios Type 1 Structure.
    //
    if (EFI_ERROR (StatusOfRequestedSmbiosType)) {
        SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
        Status = SmbiosProtocol->Add (
                     SmbiosProtocol,
                     NULL,
                     &SmbiosHandle,
                     (EFI_SMBIOS_TABLE_HEADER*) Type1Structure);
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->Add Status:%r \n", Status));
        if (EFI_ERROR (Status)) {
            return;
        }
    }
    //
    // Type 1 Manufacturer String
    //
    SmbiosHandle = Type1Structure->Hdr.Handle;
    StringNumber = 0x01;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdSystemManufacturer);
    //TH0107  if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        UnicodeString = (CHAR16 *) PcdGetPtr (PcdStrMfg);
    }
    GetValidSMBIOSString (AsciiString, UnicodeString);
    Status = SmbiosProtocol->UpdateString (
                 SmbiosProtocol,
                 &SmbiosHandle,
                 &StringNumber,
                 AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 1 Product Name String
    //
    SmbiosHandle = Type1Structure->Hdr.Handle;
    StringNumber = 0x02;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdSystemProductName);
    //TH0107  if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        UnicodeString = (CHAR16 *) PcdGetPtr (PcdStrProduct);
    }
    GetValidSMBIOSString (AsciiString, UnicodeString);
    Status = SmbiosProtocol->UpdateString (
                 SmbiosProtocol,
                 &SmbiosHandle,
                 &StringNumber,
                 AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 1 Version String
    //
    SmbiosHandle = Type1Structure->Hdr.Handle;
    StringNumber = 0x03;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdSystemVersion);
//TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                 SmbiosProtocol,
                 &SmbiosHandle,
                 &StringNumber,
                 AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 1 Serial Number String
    //
    SmbiosHandle = Type1Structure->Hdr.Handle;
    StringNumber = 0x04;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdSystemSerialNumber);
    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    if (EFI_ERROR (StatusOfRequestedSmbiosType)) {
        FreePool(Type1Structure);
    }
    //
    // Smbios Type 2 structure process start
    //
    SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
    Type = 0x02;
    StatusOfRequestedSmbiosType = SmbiosProtocol->GetNext (
                                    SmbiosProtocol,
                                    &SmbiosHandle,
                                    &Type,
                                    &Record,
                                    NULL);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->GetNext Status:%r \n", StatusOfRequestedSmbiosType));
    if (EFI_ERROR (StatusOfRequestedSmbiosType)) {
        //
        // Type 2 structure is not available, needs to be created.
        //
        Type2Structure = AllocateZeroPool (sizeof(SMBIOS_TABLE_TYPE2) + SIZE_OF_SMBIOS_STRUCTURE_END_MACRO);
        if (Type2Structure == NULL) {
            return;
        }
        Type2Structure->Hdr.Type = EFI_SMBIOS_TYPE_BASEBOARD_INFORMATION;
        Type2Structure->Hdr.Length = sizeof (SMBIOS_TABLE_TYPE2);
        Type2Structure->Hdr.Handle = 0xFFFF;//To be updated by SMBIOS driver.
    } else {
        Type2Structure = (SMBIOS_TABLE_TYPE2 *)Record;
    }
    Type2Structure->Manufacturer = 0x01;
    Type2Structure->ProductName = 0x02;
    Type2Structure->Version = 0x03;
    Type2Structure->SerialNumber = 0x04;
    Type2Structure->AssetTag = 0x05;
    //
    // Creating the Smbios Type 2 Structure.
    //
    if (EFI_ERROR (StatusOfRequestedSmbiosType)) {
        SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
        Status = SmbiosProtocol->Add (
                    SmbiosProtocol,
                    NULL,
                    &SmbiosHandle,
                    (EFI_SMBIOS_TABLE_HEADER*) Type2Structure);
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->Add Status:%r \n", Status));
        if (EFI_ERROR (Status)) {
            return;
        }
    }
    //
    // Type 2 Manufacturer String
    //
    SmbiosHandle = Type2Structure->Hdr.Handle;
    StringNumber = 0x01;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdBaseBoardManufacturer);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 2 Product Name String
    //
    SmbiosHandle = Type2Structure->Hdr.Handle;
    StringNumber = 0x02;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdBaseBoardProductName);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 2 Version String
    //
    SmbiosHandle = Type2Structure->Hdr.Handle;
    StringNumber = 0x03;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdBaseBoardVersion);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 2 Serial Number String
    //
    SmbiosHandle = Type2Structure->Hdr.Handle;
    StringNumber = 0x04;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdBaseBoardSerialNumber);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 2 AssetTag String
    //
    SmbiosHandle = Type2Structure->Hdr.Handle;
    StringNumber = 0x05;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdBaseBoardAssetTag);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    if (EFI_ERROR (StatusOfRequestedSmbiosType)) {
        FreePool (Type2Structure);
    }
    //
    // Smbios Type 3 structure process start
    //
    SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
    Type = 0x03;
    StatusOfRequestedSmbiosType = SmbiosProtocol->GetNext (
                                    SmbiosProtocol,
                                    &SmbiosHandle,
                                    &Type,
                                    &Record,
                                    NULL);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->GetNext Status:%r \n", Status));
    if (EFI_ERROR (StatusOfRequestedSmbiosType)) {
        //
        // Type 3 structure is not available, needs to be created.
        Type3Structure = AllocateZeroPool (sizeof (SMBIOS_TABLE_TYPE3) + SIZE_OF_SMBIOS_STRUCTURE_END_MACRO);
        if (Type3Structure == NULL) {
            return;
        }
        Type3Structure->Hdr.Type = EFI_SMBIOS_TYPE_SYSTEM_ENCLOSURE;
        Type3Structure->Hdr.Length = sizeof (SMBIOS_TABLE_TYPE3);
        Type3Structure->Hdr.Handle = 0xFFFF;//To be updated by SMBIOS driver.
    } else {
        Type3Structure = (SMBIOS_TABLE_TYPE3 *)Record;
    }
    Type3Structure->Manufacturer = 0x01;
    Type3Structure->Version = 0x02;
    Type3Structure->SerialNumber = 0x03;
    Type3Structure->AssetTag = 0x04;
    Type3Structure->Type = PcdGet8 (PcdChassisType);
    //
    // Creating the Smbios Type 3 Structure.
    //
    if (EFI_ERROR (StatusOfRequestedSmbiosType)) {
        SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
        Status = SmbiosProtocol->Add (
                    SmbiosProtocol,
                    NULL,
                    &SmbiosHandle,
                    (EFI_SMBIOS_TABLE_HEADER*) Type3Structure);
        SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->Add Status:%r \n", Status));
        if (EFI_ERROR (Status)) {
            return;
        }
    }
    //
    // Type 3 Manufacturer String
    //
    SmbiosHandle = Type3Structure->Hdr.Handle;
    StringNumber = 0x01;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdChassisManufacturer);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        UnicodeString = (CHAR16 *) PcdGetPtr (PcdStrMfg);
    }
    GetValidSMBIOSString (AsciiString, UnicodeString);
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 3 Version String
    //
    SmbiosHandle = Type3Structure->Hdr.Handle;
    StringNumber = 0x02;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdChassisVersion);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 3 SerialNumber String
    //
    SmbiosHandle = Type3Structure->Hdr.Handle;
    StringNumber = 0x03;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdChassisSerialNumber);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    //
    // Type 3 AssetTag String
    //
    SmbiosHandle = Type3Structure->Hdr.Handle;
    StringNumber = 0x04;
    UnicodeString = (CHAR16 *) PcdGetPtr (PcdChassisAssetTag);
    //TH0107    if ( StrCmp (UnicodeString, PcdDefaultString) == 0x00 ) {
    if ((StrCmp (UnicodeString, PcdDefaultString) == 0x00) || (StrLen (UnicodeString) == 0)) {	//TH0107
        AsciiStrCpy (AsciiString, SmBiosDefaultString);
    } else {
        GetValidSMBIOSString (AsciiString, UnicodeString);
    }
    Status = SmbiosProtocol->UpdateString (
                SmbiosProtocol,
                &SmbiosHandle,
                &StringNumber,
                AsciiString);
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "SmbiosProtocol->UpdateString Status:%r \n", Status));
    if (EFI_ERROR (StatusOfRequestedSmbiosType)) {
        FreePool (Type3Structure);
    }
    SERVER_IPMI_DEBUG ((EFI_D_LOAD, "Exiting from FruSmbiosTableUpdate function...\n"));
    return;
}

/**
    Register notification callback on SMBIOS protocol to update FRU Smbios
    structure.

    @param VOID

    @retval VOID

**/

EFI_STATUS
UpdateFruSmbiosTables (
  VOID )
{
    VOID    *SmbiosProtocolRegistration;

    //
    // Create Notification event for SmbiosProtocol GUID
    //
    EfiCreateProtocolNotifyEvent (
        &gEfiSmbiosProtocolGuid,
        TPL_CALLBACK,
        FruSmbiosTableUpdate,
        NULL,
        &SmbiosProtocolRegistration );

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
