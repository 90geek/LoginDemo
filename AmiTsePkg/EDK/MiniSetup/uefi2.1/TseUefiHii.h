//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/TseUefiHii.h $
//
// $Author: Premkumara $
//
// $Revision: 27 $
//
// $Date: 2/02/12 3:05a $
//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:  			TseUefiHii.h
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
#ifndef _AMI_UEFI_HII_H_	// DO NOT CHANGE THIS TO _HII_H_ !!  That is used by the HII Protocol header
#define	_AMI_UEFI_HII_H_
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "minisetup.h"
#include "FormBrowser2.h"
#include EFI_PROTOCOL_DEFINITION(HiiDatabase)
#include EFI_PROTOCOL_DEFINITION(HiiFont)
#include EFI_PROTOCOL_DEFINITION(HiiString)
#include EFI_PROTOCOL_DEFINITION(HiiConfigRouting)
#include EFI_PROTOCOL_DEFINITION(HiiConfigAccess)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if TSE_USE_EDK_LIBRARY
#include "TianoHii.h"
#else
#include "UefiTianoHii.h"  // Internal file used then EDKsupport is OFF
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#define AMI_TIME_HOUR	1
#define AMI_TIME_MIN	2
#define AMI_TIME_SEC	3
#define AMI_DATE_YEAR	4
#define AMI_DATE_MONTH	5
#define AMI_DATE_DAY	6
//---------------------------------------------------------------------------
#define	TSE_REFRESH_GRANURALITY		5
//---------------------------------------------------------------------------
// Maximum supported page, variables, controls.
#define MAX_PAGE 246
#define MAX_CONTROLS 0xFFFE
#define MAX_VARIABLE 300

#ifndef _EFI_IFR_TYPE_BUFFER
#define EFI_IFR_TYPE_BUFFER            0x0B
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
extern EFI_HII_DATABASE_PROTOCOL *gHiiDatabase;
extern EFI_HII_FONT_PROTOCOL *gHiiFont;
extern EFI_HII_STRING_PROTOCOL *gHiiString;
extern EFI_HII_CONFIG_ROUTING_PROTOCOL *gHiiConfigRouting;

extern /*EFI_HII_HANDLE*/VOID* gHiiHandle;
extern UINTN	gTitle;
extern UINTN	gHelp;
extern UINTN	gSubTitle;
extern UINTN	gHelpTitle;
extern UINTN	gNavStrings;
extern BOOLEAN gIFRChangeNotify;
extern EFI_HII_HANDLE gRemovedHandle;
//---------------------------------------------------------------------------


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: EFI_HII_VALUE
//
// Description:
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Type					UINT8
// Value						EFI_IFR_TYPE_VALUE
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _EFI_HII_VALUE
{
  UINT8               Type;
  EFI_IFR_TYPE_VALUE  Value;
}EFI_HII_VALUE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: SETUP_LINK
//
// Description:
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// FormSet					UINT8*
// Handle					VOID*
// ClassID					UINT16
// FormSetLength			UINTN
// Added					UINT8
// SubClassID				UINT16
// ClassGuidCount			UINT16
// ClassGuid				EFI_GUID*
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct
{
  UINT8*		FormSet;
  VOID*			Handle;
  UINT16		ClassID;
  UINTN			FormSetLength;
  UINT8			Added;	//To know if this page was present in the tool data
  UINT16		SubClassID;
  UINT16    	ClassGuidCount;
  EFI_GUID*		ClassGuid;
}SETUP_LINK;

#define SLIDE_CHECKBOX_GUID { 0x7fde1bf0, 0xd936, 0x4e50, 0xae, 0xf6, 0x56, 0xa1, 0x6d, 0x46, 0x1c, 0xb6 }

//EIP111061
typedef struct AMI_EFI_IFR_VARSTORE_EFI {
  EFI_IFR_OP_HEADER        Header;
  EFI_VARSTORE_ID          VarStoreId;
  EFI_GUID                 Guid;
  UINT32                   Attributes;
  UINT16                   Size;
  UINT8                    Name[1];
} AMI_EFI_IFR_VARSTORE_EFI; //as per UEFI spec 2.3.1

//---------------------------------------------------------------------------
EFI_IFR_FORM_SET *HiiGetFormSetFromHandle( /*EFI_HII_HANDLE*/VOID* handle );
EFI_IFR_FORM_SET *HiiGetFormSet( UINTN index );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
extern VOID RTIfrProcessAddVarListAndPageIDListWrapper(VOID);
extern VOID RTIfrProcessExitWrapper(VOID);
extern VOID RTIfrProcessRunTimeFormsWrapper(EFI_IFR_REF **ref);
extern BOOLEAN RTIfrUpdateVariableInfoWrapper(UINT32 ControlVariable, EFI_HANDLE Handle);
extern BOOLEAN RTIfrProcessFormIfUpdatedWrapper(UINT16 link);
extern INTN EfiStrnCmp(IN CHAR16 *String, IN CHAR16 *String2, IN UINTN Length);
extern EFI_STATUS GetHexStringAsBuffer(UINT8 **Buffer, CHAR16 *HexStringBuffer);
extern EFI_STATUS BufferToHexString(IN OUT CHAR16 *Str, IN UINT8 *Buffer, IN UINTN BufferSize);
extern EFI_STATUS UnicodeToConfigString(IN OUT CHAR16 *ConfigString, IN OUT UINTN *StrBufferLen, IN CHAR16 *UnicodeString);
//---------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Hii.c
// ----------------------------------------------------------------------------
EFI_STATUS HiiExit(VOID);
EFI_STATUS HiiFixupData();
EFI_STATUS HiiLoadDefaults( VOID **varList, UINT32 Mask );
EFI_STATUS FixSetupData();
EFI_STATUS HandleNewIFRPack(EFI_HANDLE Handle, UINT8 *PackData); 	//EIP 75588
EFI_STATUS HandleRemoveIFRPack(EFI_HANDLE Handle);
EFI_STATUS HandleAddIFRPack(EFI_HANDLE Handle, UINT8 *PackData);
VOID* HiiFindHandle( EFI_GUID *guid, UINT16 *index );
UINT16 HiiChangeString(VOID* handle, UINT16 token, CHAR16 *string);

VOID *GetFormByFormID(EFI_HII_PACKAGE_HEADER *IFRData, UINT16 FormID, UINTN *Length);
VOID *HiiGetForm( EFI_HII_HANDLE Handle, UINT16 form, UINTN *Length );

PAGE_ID_INFO *GetPageIdInfoByIndex(PAGE_ID_INFO *PageIdInfo, UINT16 PgIndex);
//EIP:56413 Function to update the Resetbutton Defaults to the control
EFI_STATUS UefiupdateResetButtonDefault(CONTROL_INFO ControlData, UINT16 DefaultId);
 //EIP: 57402 Evaluating the Control Default
UINT16 EvaluateControlDefault(CONTROL_INFO *CtrlInfo, UINT64 *Defaults);

// ----------------------------------------------------------------------------
// Uefi21Wrapper.c
// ----------------------------------------------------------------------------
EFI_STATUS GetConfigHeader(VARIABLE_INFO *VariableInfo, EFI_STRING *Configuration, UINTN *Length);
EFI_STATUS ProcessActionQuestionConfiguration(CONTROL_INFO *control);
EFI_STATUS UefiGetOneOfOptions(CONTROL_INFO *CtrlInfo, VOID **Handle, UINT16 **OptionPtrTokens,
                               UINT64 **ValuePtrTokens, UINT16 *ItemCount,
                               UINT16 *Interactive, UINT16 *CallBackKey);
VOID UefiGetValidOptionType(CONTROL_INFO *CtrlInfo, UINTN *Type, UINT32 *SizeOfData);
EFI_STATUS UefiVarGetNvram(VARIABLE_INFO *VariableInfo, VOID **Buffer, UINTN Offset, UINTN Size);
EFI_STATUS UefiVarSetNvram(VARIABLE_INFO *VariableInfo, VOID *Buffer, UINTN Offset, UINTN Size);

BOOLEAN IsPasswordEncodeEnabled(CONTROL_INFO *PwDataPtr);
BOOLEAN UefiIsEfiVariable(UINT32 variable, VARIABLE_INFO *varInfo);
BOOLEAN UefiIsInteractive(CONTROL_INFO *ControlData);

UINT8 UefiGetBaseValue(VOID *IfrPtr);
UINT8 UefiGetIfrLength(VOID *IfrPtr);
UINT8 UefiGetMaxEntries(VOID *IfrPtr);

UINT16 UefiGetControlKey(CONTROL_INFO *ControlData);
UINT16 UefiGetHelpField(VOID *IfrPtr);
UINT16 UefiGetPromptField(VOID *IfrPtr);
UINT16 UefiGetQuestionOffset(VOID *IfrPtr);
UINT16 UefiGetTextField(VOID *IfrPtr);
UINT16 UefiGetTextTwoField(VOID *IfrPtr);
UINT16 UefiGetTitleField(VOID *IfrPtr);
UINT16 UefiGetWidth(VOID *IfrPtr);
UINT8 UefiGetFlagsField(VOID *IfrPtr);

UINT16 UefiTseLiteGetAmiCallbackIndex(VOID * Ptr,VOID * CtrlPtr);
UINT16 UefiTseLiteGetBootOverRideIndex(VOID *IfrPtr);

UINTN HiiGetDefaultMask(VOID);
UINTN HiiGetManufactuingMask(VOID);
UINTN HiiMyGetMultiLineStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token );
UINTN HiiMyGetStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token );

UINT64 UefiGetMaxValue(VOID *IfrPtr);
UINT64 UefiGetMinValue(VOID *IfrPtr);
UINT64 UefiGetStepValue(VOID *IfrPtr);

VOID EfiLibSafeFreePool(IN VOID *Buffer);
VOID HiiRemoveString(EFI_HII_HANDLE Handle, UINT16 Token);
VOID UefiGetDateTimeDetails(VOID *IfrPtr,UINT8 Type,UINT16 * Help,UINT16 * Min,UINT16 * Max);
VOID UefiSetPromptField(VOID *IfrPtr,UINT16 Token);
VOID UefiSetHelpField(VOID *IfrPtr,UINT16 Token);
VOID UefiSetSubTitleField(VOID *IfrPtr,UINT16 Token);

VOID *UefiCreateSubTitleTemplate(UINT16 Token);
VOID *UefiCreateStringTemplate(UINT16 Token);
EFI_STATUS UefiRefershQuestionValueNvRAM(CONTROL_INFO *ControlData);
UINT16 UefiGetResetButtonDefaultid(VOID *IfrPtr);//EIP:56413 Function decleration to get the Default ID
BOOLEAN CheckTimeFlags(UINT8 Flags);
BOOLEAN CheckDateFlags(UINT8 Flags);

// ----------------------------------------------------------------------------
// TSE Advanced
// ----------------------------------------------------------------------------
VOID UefiAddEndOp(VOID *IfrPtr);
VOID BBSUpdateControlOffset(CONTROL_INFO *control);
VOID UefiCreateDynamicControlCondition(CONTROL_INFO *control,UINT16 VarId, UINT16 PrevControlQuestionID,UINT16 Value);
VOID UefiSetEqIDValue(VOID *IfrPtr, UINT16 Value);
VOID UefiSetEqIDQuestionID(VOID *IfrPtr, UINT16 Value);
VOID UefiSetOneOfOption(VOID *IfrPtr, UINT64 Value, UINT32 Size, UINT8 Flag, UINT16 Option);
VOID UefiSetWidth(VOID *IfrPtr,UINT8 Width);
VOID UefiSpecialGuidCallback(VOID * HiiHandle, UINT16 Key, EFI_GUID *pGUID);
VOID UefiUpdateControlVarOffset(VOID *IfrPtr, UINT16 Value);

VOID* UefiCreateOneOfWithOptionsTemplate(UINTN OptionCount, CONTROL_INFO *CtrlInfo);
VOID* UefiGetSpecialEqIDIfrPtr(CONTROL_INFO *ControlInfo, UINT32 * Variable, GUID_INFO **GuidInfo);

BOOLEAN UefiIsOneOfControl(VOID *IfrPtr);

UINT16 UefiGetEqIDQuestionID(VOID *IfrPtr);
UINT16 UefiGetQuestionID(CONTROL_INFO *Control);
UINT16 UefiGetSpecialEqIDValue(CONTROL_INFO *ControlInfo, GUID_INFO **GuidInfo);

UINT32 GetControlConditionVarId(CONTROL_INFO *controlInfo);
UINTN GetControlDataLength(CONTROL_INFO *controlInfo);

// ----------------------------------------------------------------------------
// Expression.c
// ----------------------------------------------------------------------------
EFI_STATUS EvaluateExpression(IN CONTROL_INFO *ControlInfo,
			      IN OUT EFI_HII_VALUE *ExpressionResult,
			      OUT UINTN *Offset);
VOID ResetScopeStack(VOID);
EFI_STATUS PushScope(IN UINT8 Operand);
EFI_STATUS PopScope(OUT UINT8 *Operand);
BOOLEAN IsScopeStackEmpty();
UINTN _SkipExpression(UINT8 *ControlCondPtr);
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Parse.c
// ----------------------------------------------------------------------------
EFI_STATUS AddPageIdToList(PAGE_ID_INFO *NewPageIdInfo);
EFI_STATUS AddPageToList(PAGE_INFO *NewPageInfo, UINT32 PageSize);
EFI_STATUS AddVariableToList(VARIABLE_INFO *NewVariableInfo);
EFI_STATUS CreatePage(PAGE_INFO **PageInfo, UINT32 *AllocatedSize, UINT32 *Offset, VOID *Buff, UINT32 BuffSize);
EFI_STATUS ParseForm(SETUP_LINK *Setup_Link);
UINT32 AddControlToList(CONTROL_INFO *ControlInfo, UINT32 ControlSize);
VOID GetDefaultValue(UINT8 Type, EFI_IFR_TYPE_VALUE *Value, UINT16 *Size, VOID *DefValue, UINT8 *TempData);
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// HiiCallBack.c
// ----------------------------------------------------------------------------
#if TSE_DEBUG_MESSAGES
#define SETUPDATAFILENAME 	L"SETUPDATA_0x%x_%03d.hpk" 
EFI_STATUS WritePackToFile(CHAR16 *filenameFormat, EFI_HANDLE Handle, UINT8 *PackData, UINTN length);
EFI_STATUS WriteDataToFile(CHAR16 *filename, VOID *Data, UINTN length, UINT32 index);
VOID *HiiGetPackList( EFI_HII_HANDLE Handle, UINT16 form, UINTN *Length );
VOID ProcessPackToFile(EFI_HII_DATABASE_NOTIFY_TYPE NotifyType, EFI_HANDLE Handle);
VOID DebugShowBufferContent(UINTN bufSize, VOID *buffer) ;
#endif //End of TSE_DEBUG_MESSAGES
EFI_STATUS FormCallBack(EFI_HII_HANDLE Handle, EFI_QUESTION_ID QuestionID, UINT8 Type, EFI_IFR_TYPE_VALUE *Value,EFI_BROWSER_ACTION action);
EFI_STATUS CallFormCallBack(CONTROL_INFO * ControlData, UINT16 Key ,UINT8 Flags,UINTN Action);//EIP-53480: Implementation of FormBrowser with actions support 
EFI_STATUS SpecialActionCallBack(CONTROL_INFO * ControlData, UINT16 Key);
EFI_STATUS CallTextCallBack(TEXT_DATA *text, ACTION_DATA *Data);
VOID UefiPreControlUpdate(CONTROL_INFO *ControlData);
EFI_STATUS UefiIsProceedWithPageChange(EFI_STATUS Status);
VOID UEFICallSetupFormCallBack(UINTN Action );//EIP-53480: Decleration of the Wrapper function which calls the CallFormCallBack()
EFI_BROWSER_ACTION UefiGetActionWapper(UINTN Action);//EIP-53480  The Wrapper function to get the actual action for the driver 
// ----------------------------------------------------------------------------

//HiiNotificationHandler.c
// ----------------------------------------------------------------------------
EFI_STATUS
IFRChangeNotifyFn (IN UINT8 PackageType, IN CONST EFI_GUID *PackageGuid,
  IN CONST EFI_HII_PACKAGE_HEADER *Package, IN EFI_HII_HANDLE Handle,
  IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType);
EFI_STATUS RegisterFormNotification(EFI_HII_DATABASE_NOTIFY PackageNotifyFn,
                                    EFI_HII_DATABASE_NOTIFY_TYPE NotifyType,
                                    EFI_HANDLE *NotifyHandle);
EFI_STATUS UnRegisterFormNotification(EFI_HANDLE NotifyHandle);
VOID VarUpdateFormSetVariable();
EFI_STATUS _DisplayErrorMessage(); // EIP : 52562 To display Error message when TSE limits exceeds
// ----------------------------------------------------------------------------

#define AMI_FLAG_MANUFACTURING	EFI_IFR_OPTION_DEFAULT_MFG
#define AMI_FLAG_DEFAULT	EFI_IFR_OPTION_DEFAULT
EFI_STATUS GetBlockName(EFI_STRING *Configuration, UINTN *Length, UINTN Offset, UINTN Size);

// ----------------------------------------------------------------------------
// To Be removed
#define EfiCopyMem(_Destination, _Source, _Length)  gBS->CopyMem ((_Destination), (_Source), (_Length))
#define EfiZeroMem(_Destination, _Length)  gBS->SetMem ((_Destination), (_Length), 0)

//EIP:56124 Defining the Default value linked list 
typedef struct _DEFAULT_VALUE
{
	UINT16 DefaultId;
	UINT64 Value;
	struct _DEFAULT_VALUE *Next;
}DEFAULT_VALUE;
//EIP:56124 END

//Added for UEFI spec. 2.3 compatibility- Start   
#ifndef EFI_BROWSER_ACTION_RETRIEVE
#define EFI_BROWSER_ACTION_RETRIEVE   2
#endif
#ifndef EFI_BROWSER_ACTION_FORM_OPEN
#define EFI_BROWSER_ACTION_FORM_OPEN  3
#endif
#ifndef EFI_BROWSER_ACTION_FORM_CLOSE
#define EFI_BROWSER_ACTION_FORM_CLOSE 4
#endif

#pragma pack (1)
typedef struct _AMI_EFI_IFR_REFRESH_ID {
  EFI_IFR_OP_HEADER Header;
  EFI_GUID          RefreshEventGroupId;
} AMI_EFI_IFR_REFRESH_ID;

#ifndef EFI_IFR_EQ_ID_LIST_OP
#define EFI_IFR_EQ_ID_LIST_OP      0x14
#endif 

#ifndef EFI_IFR_ANIMATION_OP
#define EFI_IFR_ANIMATION_OP           0x1F
#endif

#ifndef EFI_IFR_MAP_OP
#define EFI_IFR_MAP_OP                 0x22
#endif

#ifndef EFI_IFR_GET_OP
#define EFI_IFR_GET_OP                 0x2B
#endif

#ifndef EFI_IFR_SET_OP
#define EFI_IFR_SET_OP                 0x2C
#endif

#ifndef EFI_IFR_READ_OP
#define EFI_IFR_READ_OP                0x2D
#endif

#ifndef EFI_IFR_WRITE_OP
#define EFI_IFR_WRITE_OP               0x2E
#endif

#ifndef EFI_IFR_FORM_MAP_OP
#define EFI_IFR_FORM_MAP_OP            0x5D
#endif

#ifndef EFI_IFR_MODAL_TAG_OP
#define EFI_IFR_MODAL_TAG_OP           0x61
#endif

#ifndef EFI_IFR_REFRESH_ID_OP
#define EFI_IFR_REFRESH_ID_OP          0x62
#endif

#ifndef EFI_IFR_TYPE_UNDEFINED
#define EFI_IFR_TYPE_UNDEFINED         0x09
#endif

#ifndef EFI_IFR_TYPE_ACTION
#define EFI_IFR_TYPE_ACTION            0x0A
#endif

#ifndef EFI_IFR_TYPE_REF
#define EFI_IFR_TYPE_REF               0x0C
#endif

typedef struct _AMI_EFI_IFR_FORM_MAP_METHOD {
  ///
  /// The string identifier which provides the human-readable name of 
  /// the configuration method for this standards map form.
  ///
  EFI_STRING_ID            MethodTitle;
  ///
  /// Identifier which uniquely specifies the configuration methods 
  /// associated with this standards map form.
  ///
  EFI_GUID                 MethodIdentifier;
} AMI_EFI_IFR_FORM_MAP_METHOD;

typedef struct _AMI_EFI_IFR_FORM_MAP {
  ///
  /// The sequence that defines the type of opcode as well as the length 
  /// of the opcode being defined. Header.OpCode = EFI_IFR_FORM_MAP_OP. 
  ///
  EFI_IFR_OP_HEADER        Header;
  ///
  /// The unique identifier for this particular form.
  ///
  EFI_FORM_ID              FormId;
  ///
  /// One or more configuration method's name and unique identifier.
  ///
  // EFI_IFR_FORM_MAP_METHOD  Methods[];
} AMI_EFI_IFR_FORM_MAP;

typedef struct _AMI_EFI_IFR_SET {
  ///
  /// The sequence that defines the type of opcode as well as the length 
  /// of the opcode being defined. Header.OpCode = EFI_IFR_SET_OP. 
  ///
  EFI_IFR_OP_HEADER  Header;
  ///
  /// Specifies the identifier of a previously declared variable store to 
  /// use when storing the question's value. 
  ///
  EFI_VARSTORE_ID    VarStoreId;
  union {
    ///
    /// A 16-bit Buffer Storage offset.
    ///
    EFI_STRING_ID    VarName;
    ///
    /// A Name Value or EFI Variable name (VarName).
    ///
    UINT16           VarOffset;
  }                  VarStoreInfo;
  ///
  /// Specifies the type used for storage. 
  ///
  UINT8              VarStoreType;
} AMI_EFI_IFR_SET;

typedef struct _AMI_EFI_IFR_GET {
  ///
  /// The sequence that defines the type of opcode as well as the length 
  /// of the opcode being defined. Header.OpCode = EFI_IFR_GET_OP. 
  ///
  EFI_IFR_OP_HEADER  Header;
  ///
  /// Specifies the identifier of a previously declared variable store to 
  /// use when retrieving the value. 
  ///
  EFI_VARSTORE_ID    VarStoreId;
  union {
    ///
    /// A 16-bit Buffer Storage offset.
    ///
    EFI_STRING_ID    VarName;
    ///
    /// A Name Value or EFI Variable name (VarName).
    ///
    UINT16           VarOffset;
  }                  VarStoreInfo;
  ///
  /// Specifies the type used for storage. 
  ///
  UINT8              VarStoreType;
} AMI_EFI_IFR_GET;

//EIP109812, 107774
typedef struct _AMI_EFI_HII_REF {
    EFI_QUESTION_ID QuestionId;
    EFI_FORM_ID     FormId;
    EFI_GUID        FormSetGuid;
    EFI_STRING_ID   DevicePath;
} AMI_EFI_HII_REF;

typedef struct _AMI_EFI_IFR_REF5 {
	EFI_IFR_OP_HEADER 			Header;
	EFI_IFR_QUESTION_HEADER 	Question;
} AMI_EFI_IFR_REF5;

/////////////////////////////////////////////////////////////////////////////////
//
//Declaring the struct which are not present in core (UefiHii.h)
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _TSE_EFI_IFR_FORM_SET
#define _TSE_EFI_IFR_FORM_SET
typedef struct _TSE_EFI_IFR_FORM_SET {
  EFI_IFR_OP_HEADER        Header;
  EFI_GUID                 Guid;
  EFI_STRING_ID            FormSetTitle;
  EFI_STRING_ID            Help;
  UINT8                    Flags;
  EFI_GUID                 ClassGuid[1];
} TSE_EFI_IFR_FORM_SET;
#endif
#pragma pack ()

//End for UEFI spec. 2.3 compatibility

UINT16 GetCheckBoxStyle(CONTROL_INFO *controlInfo);

#endif /* _AMI_UEFI_HII_H_ */
// ----------------------------------------------------------------------------
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

