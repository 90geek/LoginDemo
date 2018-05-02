/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.c
  Abstract:       Auto-generated AutoGen.c for building module or library.
**/
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>

GLOBAL_REMOVE_IF_UNREFERENCED GUID gEfiCallerIdGuid = {0x80CF7257, 0x87AB, 0x47f9, {0xA3, 0xFE, 0xD5, 0x0B, 0x76, 0xD8, 0x95, 0x41}};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gEfiCallerBaseName = "PcdDxe";

// Guids
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gPcdDataBaseHobGuid = { 0xEA296D92, 0x0B69, 0x423C, { 0x8C, 0x28, 0x33, 0xB4, 0xE0, 0xA9, 0x12, 0x68 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gPcdDataBaseSignatureGuid = { 0x3c7d193c, 0x682c, 0x4c14, { 0xa6, 0x8f, 0x55, 0x2d, 0xea, 0x4f, 0x43, 0x7e }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiMdeModulePkgTokenSpaceGuid = { 0xA1AFF049, 0xFDEB, 0x442a, { 0xB3, 0x20, 0x13, 0xAB, 0x4C, 0xB7, 0x2B, 0xBC }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiMdePkgTokenSpaceGuid = { 0x914AEBE7, 0x4635, 0x459b, { 0xAA, 0x1C, 0x11, 0xE2, 0x19, 0xB0, 0x3A, 0x10 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiVTUTF8Guid = { 0xAD15A0D6, 0x8BEC, 0x4ACF, { 0xA0, 0x73, 0xD0, 0x1D, 0xE7, 0x7E, 0x2D, 0x88 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiVT100Guid = { 0xDFA66065, 0xB419, 0x11D3, { 0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiVT100PlusGuid = { 0x7BAEC70B, 0x57E0, 0x4C76, { 0x8E, 0x87, 0x2F, 0x9E, 0x28, 0x08, 0x83, 0x43 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPcAnsiGuid = { 0xE0C14753, 0xF9BE, 0x11D2, { 0x9A, 0x0C, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiUartDevicePathGuid = { 0x37499a9d, 0x542f, 0x4c89, { 0xa0, 0x26, 0x35, 0xda, 0x14, 0x20, 0x94, 0xe4 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiSasDevicePathGuid = { 0xd487ddb4, 0x008b, 0x11d9, { 0xaf, 0xdc, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiEventReadyToBootGuid = { 0x7CE88FB3, 0x4BD7, 0x4679, { 0x87, 0xA8, 0xA8, 0xD8, 0xDE, 0xE5, 0x0D, 0x2B }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiEventLegacyBootGuid = { 0x2A571201, 0x4966, 0x47F6, { 0x8B, 0x86, 0xF3, 0x1E, 0x41, 0xF3, 0x2F, 0x10 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiGlobalVariableGuid = { 0x8BE4DF61, 0x93CA, 0x11D2, { 0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHobListGuid = { 0x7739F24C, 0x93D7, 0x11D4, { 0x9A, 0x3A, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiFileInfoGuid = { 0x09576E92, 0x6D3F, 0x11D2, { 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B }};

// Protocols
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gPcdProtocolGuid = { 0x11B34006, 0xD85B, 0x4D0A, { 0xA2, 0x90, 0xD5, 0xA5, 0x71, 0x31, 0x0E, 0xF7 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPcdProtocolGuid = { 0x13a3f0f6, 0x264a, 0x3ef0, { 0xf2, 0xe0, 0xde, 0xc5, 0x12, 0x34, 0x2f, 0x34 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gGetPcdInfoProtocolGuid = { 0x5be40f57, 0xfa68, 0x4610, { 0xbb, 0xbf, 0xe9, 0xc5, 0xfc, 0xda, 0xd3, 0x65 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiGetPcdInfoProtocolGuid = { 0xfd0f4478,  0xefd, 0x461d, { 0xba, 0x2d, 0xe5, 0x8c, 0x45, 0xfd, 0x5f, 0x5e } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gAmiDebugServiceProtocolGuid = { 0x36232936, 0xe76, 0x31c8, { 0xa1, 0x3a, 0x3a, 0xf2, 0xfc, 0x1c, 0x39, 0x32 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDevicePathProtocolGuid = { 0x09576E91, 0x6D3F, 0x11D2, { 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDebugPortProtocolGuid = { 0xEBA4E8D2, 0x3858, 0x41EC, { 0xA2, 0x81, 0x26, 0x47, 0xBA, 0x96, 0x60, 0xD0 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDriverBindingProtocolGuid = { 0x18A031AB, 0xB443, 0x4D1A, { 0xA5, 0xC0, 0x0C, 0x09, 0x26, 0x1E, 0x9F, 0x71 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiSimpleTextOutProtocolGuid = { 0x387477C2, 0x69C7, 0x11D2, { 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiGraphicsOutputProtocolGuid = { 0x9042A9DE, 0x23DC, 0x4A38, { 0x96, 0xFB, 0x7A, 0xDE, 0xD0, 0x80, 0x51, 0x6A }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHiiFontProtocolGuid = {0xe9ca4775, 0x8657, 0x47fc, {0x97, 0xe7, 0x7e, 0xd6, 0x5a, 0x08, 0x43, 0x24}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiUgaDrawProtocolGuid = { 0x982C298B, 0xF4FA, 0x41CB, { 0xB8, 0x38, 0x77, 0xAA, 0x68, 0x8F, 0xB8, 0x39 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiComponentNameProtocolGuid = { 0x107A772C, 0xD5E1, 0x11D4, { 0x9A, 0x46, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiComponentName2ProtocolGuid = { 0x6A7A5CFF, 0xE8D9, 0x4F70, { 0xBA, 0xDA, 0x75, 0xAB, 0x30, 0x25, 0xCE, 0x14 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDriverConfigurationProtocolGuid = { 0x107A772B, 0xD5E1, 0x11D4, { 0x9A, 0x46, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDriverConfiguration2ProtocolGuid = { 0xBFD7DC1D, 0x24F1, 0x40D9, { 0x82, 0xE7, 0x2E, 0x09, 0xBB, 0x6B, 0x4E, 0xBE }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDriverDiagnosticsProtocolGuid = { 0x0784924F, 0xE296, 0x11D4, { 0x9A, 0x49, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDriverDiagnostics2ProtocolGuid = { 0x4D330321, 0x025F, 0x4AAC, { 0x90, 0xD8, 0x5E, 0xD9, 0x00, 0x17, 0x3B, 0x63 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiLoadedImageProtocolGuid = { 0x5B1B31A1, 0x9562, 0x11D2, { 0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiFirmwareVolume2ProtocolGuid = { 0x220e73b6, 0x6bdb, 0x4413, { 0x84, 0x5, 0xb9, 0x74, 0xb1, 0x8, 0x61, 0x9a } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiLoadFileProtocolGuid = { 0x56EC3091, 0x954C, 0x11D2, { 0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiLoadFile2ProtocolGuid = { 0x4006c0c1, 0xfcb3, 0x403e, {0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiSimpleFileSystemProtocolGuid = { 0x964E5B22, 0x6459, 0x11D2, { 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B }};

// Definition of PCDs used in this module
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 _gPcd_FixedAtBuild_PcdVpdBaseAddress = _PCD_VALUE_PcdVpdBaseAddress;

// Definition of PCDs used in libraries

#define _PCD_TOKEN_PcdVerifyNodeInList  86U
#define _PCD_SIZE_PcdVerifyNodeInList 1
#define _PCD_GET_MODE_SIZE_PcdVerifyNodeInList  _PCD_SIZE_PcdVerifyNodeInList 
#define _PCD_VALUE_PcdVerifyNodeInList  ((BOOLEAN)0U)
GLOBAL_REMOVE_IF_UNREFERENCED const BOOLEAN _gPcd_FixedAtBuild_PcdVerifyNodeInList = _PCD_VALUE_PcdVerifyNodeInList;
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdVerifyNodeInList;
#define _PCD_GET_MODE_BOOL_PcdVerifyNodeInList  _gPcd_FixedAtBuild_PcdVerifyNodeInList
//#define _PCD_SET_MODE_BOOL_PcdVerifyNodeInList  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdMaximumLinkedListLength  87U
#define _PCD_SIZE_PcdMaximumLinkedListLength 4
#define _PCD_GET_MODE_SIZE_PcdMaximumLinkedListLength  _PCD_SIZE_PcdMaximumLinkedListLength 
#define _PCD_VALUE_PcdMaximumLinkedListLength  1000000U
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 _gPcd_FixedAtBuild_PcdMaximumLinkedListLength = _PCD_VALUE_PcdMaximumLinkedListLength;
extern const  UINT32  _gPcd_FixedAtBuild_PcdMaximumLinkedListLength;
#define _PCD_GET_MODE_32_PcdMaximumLinkedListLength  _gPcd_FixedAtBuild_PcdMaximumLinkedListLength
//#define _PCD_SET_MODE_32_PcdMaximumLinkedListLength  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdMaximumAsciiStringLength  88U
#define _PCD_SIZE_PcdMaximumAsciiStringLength 4
#define _PCD_GET_MODE_SIZE_PcdMaximumAsciiStringLength  _PCD_SIZE_PcdMaximumAsciiStringLength 
#define _PCD_VALUE_PcdMaximumAsciiStringLength  1000000U
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 _gPcd_FixedAtBuild_PcdMaximumAsciiStringLength = _PCD_VALUE_PcdMaximumAsciiStringLength;
extern const  UINT32  _gPcd_FixedAtBuild_PcdMaximumAsciiStringLength;
#define _PCD_GET_MODE_32_PcdMaximumAsciiStringLength  _gPcd_FixedAtBuild_PcdMaximumAsciiStringLength
//#define _PCD_SET_MODE_32_PcdMaximumAsciiStringLength  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdMaximumUnicodeStringLength  89U
#define _PCD_SIZE_PcdMaximumUnicodeStringLength 4
#define _PCD_GET_MODE_SIZE_PcdMaximumUnicodeStringLength  _PCD_SIZE_PcdMaximumUnicodeStringLength 
#define _PCD_VALUE_PcdMaximumUnicodeStringLength  1000000U
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 _gPcd_FixedAtBuild_PcdMaximumUnicodeStringLength = _PCD_VALUE_PcdMaximumUnicodeStringLength;
extern const  UINT32  _gPcd_FixedAtBuild_PcdMaximumUnicodeStringLength;
#define _PCD_GET_MODE_32_PcdMaximumUnicodeStringLength  _gPcd_FixedAtBuild_PcdMaximumUnicodeStringLength
//#define _PCD_SET_MODE_32_PcdMaximumUnicodeStringLength  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdDebugClearMemoryValue  90U
#define _PCD_SIZE_PcdDebugClearMemoryValue 1
#define _PCD_GET_MODE_SIZE_PcdDebugClearMemoryValue  _PCD_SIZE_PcdDebugClearMemoryValue 
#define _PCD_VALUE_PcdDebugClearMemoryValue  0xAFU
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 _gPcd_FixedAtBuild_PcdDebugClearMemoryValue = _PCD_VALUE_PcdDebugClearMemoryValue;
extern const  UINT8  _gPcd_FixedAtBuild_PcdDebugClearMemoryValue;
#define _PCD_GET_MODE_8_PcdDebugClearMemoryValue  _gPcd_FixedAtBuild_PcdDebugClearMemoryValue
//#define _PCD_SET_MODE_8_PcdDebugClearMemoryValue  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdDebugPropertyMask  91U
#define _PCD_SIZE_PcdDebugPropertyMask 1
#define _PCD_GET_MODE_SIZE_PcdDebugPropertyMask  _PCD_SIZE_PcdDebugPropertyMask 
#define _PCD_VALUE_PcdDebugPropertyMask  0x2FU
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 _gPcd_FixedAtBuild_PcdDebugPropertyMask = _PCD_VALUE_PcdDebugPropertyMask;
extern const  UINT8  _gPcd_FixedAtBuild_PcdDebugPropertyMask;
#define _PCD_GET_MODE_8_PcdDebugPropertyMask  _gPcd_FixedAtBuild_PcdDebugPropertyMask
//#define _PCD_SET_MODE_8_PcdDebugPropertyMask  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdDebugPrintErrorLevel  92U
#define _PCD_PATCHABLE_VALUE_PcdDebugPrintErrorLevel  ((UINT32)0x80000046U)
volatile  UINT32 _gPcd_BinaryPatch_PcdDebugPrintErrorLevel = _PCD_PATCHABLE_VALUE_PcdDebugPrintErrorLevel;
extern volatile   UINT32  _gPcd_BinaryPatch_PcdDebugPrintErrorLevel;
#define _PCD_GET_MODE_32_PcdDebugPrintErrorLevel  _gPcd_BinaryPatch_PcdDebugPrintErrorLevel
#define _PCD_PATCHABLE_PcdDebugPrintErrorLevel_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdDebugPrintErrorLevel  _gPcd_BinaryPatch_Size_PcdDebugPrintErrorLevel 
extern UINTN _gPcd_BinaryPatch_Size_PcdDebugPrintErrorLevel; 
GLOBAL_REMOVE_IF_UNREFERENCED UINTN _gPcd_BinaryPatch_Size_PcdDebugPrintErrorLevel = 4;
#define _PCD_SET_MODE_32_PcdDebugPrintErrorLevel(Value)  (_gPcd_BinaryPatch_PcdDebugPrintErrorLevel = (Value))
#define _PCD_SET_MODE_32_S_PcdDebugPrintErrorLevel(Value)  ((_gPcd_BinaryPatch_PcdDebugPrintErrorLevel = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdMaximumDevicePathNodeCount  146U
#define _PCD_SIZE_PcdMaximumDevicePathNodeCount 4
#define _PCD_GET_MODE_SIZE_PcdMaximumDevicePathNodeCount  _PCD_SIZE_PcdMaximumDevicePathNodeCount 
#define _PCD_VALUE_PcdMaximumDevicePathNodeCount  0U
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 _gPcd_FixedAtBuild_PcdMaximumDevicePathNodeCount = _PCD_VALUE_PcdMaximumDevicePathNodeCount;
extern const  UINT32  _gPcd_FixedAtBuild_PcdMaximumDevicePathNodeCount;
#define _PCD_GET_MODE_32_PcdMaximumDevicePathNodeCount  _gPcd_FixedAtBuild_PcdMaximumDevicePathNodeCount
//#define _PCD_SET_MODE_32_PcdMaximumDevicePathNodeCount  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdDriverDiagnosticsDisable  147U
#define _PCD_SIZE_PcdDriverDiagnosticsDisable 1
#define _PCD_GET_MODE_SIZE_PcdDriverDiagnosticsDisable  _PCD_SIZE_PcdDriverDiagnosticsDisable 
#define _PCD_VALUE_PcdDriverDiagnosticsDisable  ((BOOLEAN)0U)
GLOBAL_REMOVE_IF_UNREFERENCED const BOOLEAN _gPcd_FixedAtBuild_PcdDriverDiagnosticsDisable = _PCD_VALUE_PcdDriverDiagnosticsDisable;
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdDriverDiagnosticsDisable;
#define _PCD_GET_MODE_BOOL_PcdDriverDiagnosticsDisable  _gPcd_FixedAtBuild_PcdDriverDiagnosticsDisable
//#define _PCD_SET_MODE_BOOL_PcdDriverDiagnosticsDisable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdComponentNameDisable  148U
#define _PCD_SIZE_PcdComponentNameDisable 1
#define _PCD_GET_MODE_SIZE_PcdComponentNameDisable  _PCD_SIZE_PcdComponentNameDisable 
#define _PCD_VALUE_PcdComponentNameDisable  ((BOOLEAN)0U)
GLOBAL_REMOVE_IF_UNREFERENCED const BOOLEAN _gPcd_FixedAtBuild_PcdComponentNameDisable = _PCD_VALUE_PcdComponentNameDisable;
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdComponentNameDisable;
#define _PCD_GET_MODE_BOOL_PcdComponentNameDisable  _gPcd_FixedAtBuild_PcdComponentNameDisable
//#define _PCD_SET_MODE_BOOL_PcdComponentNameDisable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdDriverDiagnostics2Disable  149U
#define _PCD_SIZE_PcdDriverDiagnostics2Disable 1
#define _PCD_GET_MODE_SIZE_PcdDriverDiagnostics2Disable  _PCD_SIZE_PcdDriverDiagnostics2Disable 
#define _PCD_VALUE_PcdDriverDiagnostics2Disable  ((BOOLEAN)0U)
GLOBAL_REMOVE_IF_UNREFERENCED const BOOLEAN _gPcd_FixedAtBuild_PcdDriverDiagnostics2Disable = _PCD_VALUE_PcdDriverDiagnostics2Disable;
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdDriverDiagnostics2Disable;
#define _PCD_GET_MODE_BOOL_PcdDriverDiagnostics2Disable  _gPcd_FixedAtBuild_PcdDriverDiagnostics2Disable
//#define _PCD_SET_MODE_BOOL_PcdDriverDiagnostics2Disable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdComponentName2Disable  150U
#define _PCD_SIZE_PcdComponentName2Disable 1
#define _PCD_GET_MODE_SIZE_PcdComponentName2Disable  _PCD_SIZE_PcdComponentName2Disable 
#define _PCD_VALUE_PcdComponentName2Disable  ((BOOLEAN)0U)
GLOBAL_REMOVE_IF_UNREFERENCED const BOOLEAN _gPcd_FixedAtBuild_PcdComponentName2Disable = _PCD_VALUE_PcdComponentName2Disable;
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdComponentName2Disable;
#define _PCD_GET_MODE_BOOL_PcdComponentName2Disable  _gPcd_FixedAtBuild_PcdComponentName2Disable
//#define _PCD_SET_MODE_BOOL_PcdComponentName2Disable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUgaConsumeSupport  151U
#define _PCD_SIZE_PcdUgaConsumeSupport 1
#define _PCD_GET_MODE_SIZE_PcdUgaConsumeSupport  _PCD_SIZE_PcdUgaConsumeSupport 
#define _PCD_VALUE_PcdUgaConsumeSupport  ((BOOLEAN)1U)
GLOBAL_REMOVE_IF_UNREFERENCED const BOOLEAN _gPcd_FixedAtBuild_PcdUgaConsumeSupport = _PCD_VALUE_PcdUgaConsumeSupport;
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdUgaConsumeSupport;
#define _PCD_GET_MODE_BOOL_PcdUgaConsumeSupport  _gPcd_FixedAtBuild_PcdUgaConsumeSupport
//#define _PCD_SET_MODE_BOOL_PcdUgaConsumeSupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUefiLibMaxPrintBufferSize  152U
#define _PCD_SIZE_PcdUefiLibMaxPrintBufferSize 4
#define _PCD_GET_MODE_SIZE_PcdUefiLibMaxPrintBufferSize  _PCD_SIZE_PcdUefiLibMaxPrintBufferSize 
#define _PCD_VALUE_PcdUefiLibMaxPrintBufferSize  320U
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 _gPcd_FixedAtBuild_PcdUefiLibMaxPrintBufferSize = _PCD_VALUE_PcdUefiLibMaxPrintBufferSize;
extern const  UINT32  _gPcd_FixedAtBuild_PcdUefiLibMaxPrintBufferSize;
#define _PCD_GET_MODE_32_PcdUefiLibMaxPrintBufferSize  _gPcd_FixedAtBuild_PcdUefiLibMaxPrintBufferSize
//#define _PCD_SET_MODE_32_PcdUefiLibMaxPrintBufferSize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

//
// External PCD database debug information
//
#if 0
DXE_PCD_DATABASE_INIT gDXEPcdDbInit = {


  { 0x002CF6CFU }, /*  PcdCpuProcessorFeatureUserConfiguration_2ada836d_0a3d_43d6_a25a_3845cad2d400[1] */


  /* VPD */

  /* ExMapTable */
  {
    { 0x60008007U, 85U, 2U },

  },
  /* LocalTokenNumberTable */
  {
    offsetof(DXE_PCD_DATABASE, Init.PcdSystemManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdSystemProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdSystemVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdSystemSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardChassisLocation_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardChassisLink_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardNumberLinks_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisElements_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdSdrVersionNo_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400_Variable_Header) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_HII,
    offsetof(DXE_PCD_DATABASE, Init.PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15_Variable_Header) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_HII,
    offsetof(DXE_PCD_DATABASE, Init.PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15_Variable_Header) | PCD_TYPE_HII | PCD_DATUM_TYPE_UINT16,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdIdentifyMappingPageTablePtr_a1aff049_fdeb_442a_b320_13ab4cb72bbc) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdPlatformCpuAssetTags_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdPlatformCpuSocketNames_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdPlatformCpuSocketCount_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdPlatformCpuFrequencyLists_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureSetting_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureCapability_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Init.PcdCpuProcessorFeatureUserConfiguration_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureSettingEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureCapabilityEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureUserConfigurationEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuConfigContextBuffer_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuCallbackSignal_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdIsPowerOnReset_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuPageTableAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuMtrrTableAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuS3DataAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.PcdCpuHwCoordination_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuEnergyPolicy_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuClockModulationDutyCycle_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuAcpiLvl2Addr_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT16,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuPackageCStateLimit_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuDcuMode_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuProcessorMsrLockCtrl_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuDebugInterface_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuTurboOverride_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuIioLlcWaysBitMask_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuQlruCfgBitMask_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.PcdSbspSelection_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuPmStructAddr_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdWakeOnRTCS5_758e73aa_2587_4ef1_86a9_83a7fb872a52) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdRtcWakeupTimeHour_758e73aa_2587_4ef1_86a9_83a7fb872a52) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdRtcWakeupTimeMinute_758e73aa_2587_4ef1_86a9_83a7fb872a52) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdRtcWakeupTimeSecond_758e73aa_2587_4ef1_86a9_83a7fb872a52) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.DiskController_d34d3234_38ba_428b_9acd_84e830a80785) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PchDiskError_d34d3234_38ba_428b_9acd_84e830a80785) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT16,
    offsetof(DXE_PCD_DATABASE, Init.PcdSystemUuid_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardFeatureFlag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.PcdBaseBoardType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdChassisType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisBootupState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisPowerSupplyState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisThermalState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisSecurityState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdChassisOemDefined_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Init.PcdChassisHeight_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdChassisElementRecordLength_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdChassisElementCount_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.BulkDataTransferInterfaceType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.BulkDataTransferTimeout_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT16,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuHotPlugDataAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuSmmSmrr2Base_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuSmmSmrr2Size_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32,
    offsetof(DXE_PCD_DATABASE, Init.PcdCpuSmmSmrr2CacheType_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuSmmUseDelayIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuSmmUseBlockIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Uninit.PcdCpuSmmUseSmmEnableIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA,
    offsetof(DXE_PCD_DATABASE, Init.PcdSocketBaseBusNumbers_356471b1_b483_42ae_b6e7_3b2ebab14e15) | PCD_TYPE_STRING,
    offsetof(DXE_PCD_DATABASE, Init.PcdCpuSocketId_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_STRING,

  },
  /* GuidTable */
  {
    { 0x356471b1, 0xb483, 0x42ae, { 0xb6, 0xe7, 0x3b, 0x2e, 0xba, 0xb1, 0x4e, 0x15 } },
    { 0x8BE4DF61, 0x93CA, 0x11D2, { 0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C }},
    { 0x2ADA836D, 0x0A3D, 0x43D6, { 0xA2, 0x5A, 0x38, 0x45, 0xCA, 0xD2, 0xD4, 0x00 }},

  },
  { 0U }, /* PcdSystemManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 134U }, /* PcdSystemProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 268U }, /* PcdSystemVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 402U }, /* PcdSystemSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 536U }, /* PcdBaseBoardManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 670U }, /* PcdBaseBoardProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 804U }, /* PcdBaseBoardVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 938U }, /* PcdBaseBoardSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 1072U }, /* PcdBaseBoardAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 1206U }, /* PcdBaseBoardChassisLocation_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 1340U }, /* PcdBaseBoardChassisLink_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 1474U }, /* PcdBaseBoardNumberLinks_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 1608U }, /* PcdChassisManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 1742U }, /* PcdChassisVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 1876U }, /* PcdChassisSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 2010U }, /* PcdChassisAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 2144U }, /* PcdChassisElements_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 2278U }, /* PcdSdrVersionNo_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 2396U }, /* PcdSystemUuid_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 2412U }, /* PcdSocketBaseBusNumbers_356471b1_b483_42ae_b6e7_3b2ebab14e15[1] */
  { 2414U }, /* PcdCpuSocketId_2ada836d_0a3d_43d6_a25a_3845cad2d400[1] */

  /* PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400_Variable_Header[1] */
  {
    { 2294U, offsetof(DXE_PCD_DATABASE, Init.PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400_VariableDefault_2), 0U, 0U },
    { 0U, 2294U, 0U, offsetof(DXE_PCD_DATABASE, Init.PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400_VariableDefault_2) }

  },
  /* PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15_Variable_Header[1] */
  {
    { 2344U, offsetof(DXE_PCD_DATABASE, Init.PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15_VariableDefault_2), 0U, 0U },
    { 0U, 2344U, 0U, offsetof(DXE_PCD_DATABASE, Init.PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15_VariableDefault_2) }

  },
  /* PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15_Variable_Header[1] */
  {
    { 2380U, offsetof(DXE_PCD_DATABASE, Init.PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15_VariableDefault_2), 1U, 0U },
    { 1U, 2380U, 0U, offsetof(DXE_PCD_DATABASE, Init.PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15_VariableDefault_2) }

  },

/* SkuHead */
  {
   offsetof (DXE_PCD_DATABASE, Init.PcdSystemManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdSystemProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdSystemVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdSystemSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardChassisLocation_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardChassisLink_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardNumberLinks_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisElements_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdSdrVersionNo_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400_Variable_Header) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_HII, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15_Variable_Header) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_HII, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15_Variable_Header) | PCD_TYPE_HII | PCD_DATUM_TYPE_UINT16, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdIdentifyMappingPageTablePtr_a1aff049_fdeb_442a_b320_13ab4cb72bbc) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdPlatformCpuAssetTags_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdPlatformCpuSocketNames_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdPlatformCpuSocketCount_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdPlatformCpuFrequencyLists_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureSetting_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureCapability_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdCpuProcessorFeatureUserConfiguration_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureSettingEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureCapabilityEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuProcessorFeatureUserConfigurationEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuConfigContextBuffer_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuCallbackSignal_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdIsPowerOnReset_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuPageTableAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuMtrrTableAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuS3DataAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdCpuHwCoordination_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuEnergyPolicy_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuClockModulationDutyCycle_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuAcpiLvl2Addr_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT16, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuPackageCStateLimit_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuDcuMode_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuProcessorMsrLockCtrl_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuDebugInterface_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuTurboOverride_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuIioLlcWaysBitMask_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuQlruCfgBitMask_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdSbspSelection_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuPmStructAddr_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdWakeOnRTCS5_758e73aa_2587_4ef1_86a9_83a7fb872a52) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdRtcWakeupTimeHour_758e73aa_2587_4ef1_86a9_83a7fb872a52) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdRtcWakeupTimeMinute_758e73aa_2587_4ef1_86a9_83a7fb872a52) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdRtcWakeupTimeSecond_758e73aa_2587_4ef1_86a9_83a7fb872a52) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.DiskController_d34d3234_38ba_428b_9acd_84e830a80785) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PchDiskError_d34d3234_38ba_428b_9acd_84e830a80785) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT16, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdSystemUuid_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardFeatureFlag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdBaseBoardType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdChassisType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisBootupState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisPowerSupplyState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisThermalState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisSecurityState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdChassisOemDefined_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdChassisHeight_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdChassisElementRecordLength_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdChassisElementCount_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.BulkDataTransferInterfaceType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.BulkDataTransferTimeout_1e21c326_0d40_40f2_9f02_3a9b7838aa6b) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT16, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuHotPlugDataAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT64 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuSmmSmrr2Base_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuSmmSmrr2Size_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_DATA | PCD_DATUM_TYPE_UINT32, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdCpuSmmSmrr2CacheType_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8 | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuSmmUseDelayIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuSmmUseBlockIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Uninit.PcdCpuSmmUseSmmEnableIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_DATUM_TYPE_UINT8_BOOLEAN | PCD_TYPE_DATA, /* */
           offsetof (DXE_PCD_DATABASE, Uninit.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdSocketBaseBusNumbers_356471b1_b483_42ae_b6e7_3b2ebab14e15) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
   offsetof (DXE_PCD_DATABASE, Init.PcdCpuSocketId_2ada836d_0a3d_43d6_a25a_3845cad2d400) | PCD_TYPE_STRING, /* */
           offsetof (DXE_PCD_DATABASE, Init.SkuHead)  /* */
  
  },
 /* StringTable */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdSystemManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdSystemProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdSystemVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdSystemSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdBaseBoardManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdBaseBoardProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdBaseBoardVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdBaseBoardSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdBaseBoardAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdBaseBoardChassisLocation_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdBaseBoardChassisLink_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdBaseBoardNumberLinks_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdChassisManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdChassisVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdChassisSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdChassisAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x62, 0x00, 0x65, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x62, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x2e, 0x00, 0x4d, 0x00, 0x2e, 0x00, 0x00, 0x00}, /* PcdChassisElements_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x55, 0x00, 0x6e, 0x00, 0x6b, 0x00, 0x6e, 0x00, 0x6f, 0x00, 0x77, 0x00, 0x6e, 0x00, 0x00, 0x00}, /* PcdSdrVersionNo_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x43, 0x00, 0x70, 0x00, 0x75, 0x00, 0x53, 0x00, 0x6d, 0x00, 0x6d, 0x00, 0x4d, 0x00, 0x73, 0x00, 0x72, 0x00, 0x53, 0x00, 0x61, 0x00, 0x76, 0x00, 0x65, 0x00, 0x53, 0x00, 0x74, 0x00, 0x61, 0x00, 0x74, 0x00, 0x65, 0x00, 0x45, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x62, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x00, 0x00}, /* PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400 */
  {0x55, 0x00, 0x65, 0x00, 0x66, 0x00, 0x69, 0x00, 0x4f, 0x00, 0x70, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6d, 0x00, 0x69, 0x00, 0x7a, 0x00, 0x65, 0x00, 0x64, 0x00, 0x42, 0x00, 0x6f, 0x00, 0x6f, 0x00, 0x74, 0x00, 0x00, 0x00}, /* PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15 */
  {0x54, 0x00, 0x69, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x6f, 0x00, 0x75, 0x00, 0x74, 0x00, 0x00, 0x00}, /* PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* PcdSystemUuid_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  {0x00, 0x00}, /* PcdSocketBaseBusNumbers_356471b1_b483_42ae_b6e7_3b2ebab14e15 */
  {0x0, 0x00}, /* PcdCpuSocketId_2ada836d_0a3d_43d6_a25a_3845cad2d400 */

  /* SizeTable */
  {
    134U, ['134U'], /* PcdSystemManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdSystemProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdSystemVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdSystemSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdBaseBoardManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdBaseBoardProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdBaseBoardVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdBaseBoardSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdBaseBoardAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdBaseBoardChassisLocation_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdBaseBoardChassisLink_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdBaseBoardNumberLinks_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdChassisManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdChassisVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdChassisSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdChassisAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    134U, ['134U'], /* PcdChassisElements_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    16U, ['16U'], /* PcdSdrVersionNo_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    16U, ['16U'], /* PcdSystemUuid_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
    1U, ['1U'], /* PcdSocketBaseBusNumbers_356471b1_b483_42ae_b6e7_3b2ebab14e15 */
    1U, ['1U'], /* PcdCpuSocketId_2ada836d_0a3d_43d6_a25a_3845cad2d400 */

  },
  { 65535U }, /*  BulkDataTransferTimeout_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */

  10U, /* PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15_VariableDefault_2 */

  { 0xFFU }, /*  PcdSbspSelection_2ada836d_0a3d_43d6_a25a_3845cad2d400[1] */
  { 0x09U }, /*  PcdBaseBoardFeatureFlag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 0x0AU }, /*  PcdBaseBoardType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 0x03U }, /*  PcdChassisBootupState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 0x03U }, /*  PcdChassisPowerSupplyState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 0x03U }, /*  PcdChassisThermalState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 0x02U }, /*  PcdChassisSecurityState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 0x02U }, /*  PcdChassisHeight_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 0x02U }, /*  BulkDataTransferInterfaceType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1] */
  { 5U }, /*  PcdCpuSmmSmrr2CacheType_2ada836d_0a3d_43d6_a25a_3845cad2d400[1] */


  { 1U }, /*  PcdCpuHwCoordination_2ada836d_0a3d_43d6_a25a_3845cad2d400[1] */

  0U, /* PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400_VariableDefault_2 */
  0U, /* PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15_VariableDefault_2 */

  /* SkuIdTable */
  { 1, 0U,  },
  0
};
#endif


EFI_STATUS
EFIAPI
UefiBootServicesTableLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
UefiRuntimeServicesTableLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
UefiLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
HobLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );


VOID
EFIAPI
ProcessLibraryConstructorList (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;

  Status = UefiBootServicesTableLibConstructor (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);

  Status = UefiRuntimeServicesTableLibConstructor (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);

  Status = UefiLibConstructor (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);

  Status = HobLibConstructor (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);

}



VOID
EFIAPI
ProcessLibraryDestructorList (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

}

const UINT32 _gUefiDriverRevision = 0x00000000U;
const UINT32 _gDxeRevision = 0x00000000U;


EFI_STATUS
EFIAPI
ProcessModuleEntryPointList (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )

{
  return PcdDxeInit (ImageHandle, SystemTable);
}

VOID
EFIAPI
ExitDriver (
  IN EFI_STATUS  Status
  )
{
  if (EFI_ERROR (Status)) {
    ProcessLibraryDestructorList (gImageHandle, gST);
  }
  gBS->Exit (gImageHandle, Status, 0, NULL);
}

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 _gDriverUnloadImageCount = 0U;

EFI_STATUS
EFIAPI
ProcessModuleUnloadList (
  IN EFI_HANDLE        ImageHandle
  )
{
  return EFI_SUCCESS;
}
