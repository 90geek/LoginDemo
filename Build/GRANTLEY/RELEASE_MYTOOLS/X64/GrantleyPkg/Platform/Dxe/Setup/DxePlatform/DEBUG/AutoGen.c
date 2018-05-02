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

GLOBAL_REMOVE_IF_UNREFERENCED GUID gEfiCallerIdGuid = {0xABBCE13D, 0xE25A, 0x4d9f, {0xA1, 0xF9, 0x2F, 0x77, 0x10, 0x78, 0x68, 0x92}};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gEfiCallerBaseName = "Platform";

// Guids
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiSetupVariableGuid = {0xec87d643, 0xeba4, 0x4bb5, {0xa1, 0xe5, 0x3f, 0x3e, 0x36, 0xb2, 0xd, 0xa9 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiStatusCodeSpecificDataGuid = { 0x335984BD, 0xE805, 0x409A, { 0xB8, 0xF8, 0xD2, 0x7E, 0xCE, 0x5F, 0xF7, 0xA6 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gMainPkgListGuid = { 0x6205c3a4, 0x1149, 0x491a, { 0xa6, 0xd6, 0x1e, 0x72, 0x3b, 0x87, 0x83, 0xb1 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gAdvancedPkgListGuid = { 0xc09c81cb, 0x31e9, 0x4de6, { 0xa9, 0xf9, 0x17, 0xa1, 0x44, 0x35, 0x42, 0x45 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gTpmPkgListGuid = { 0x7da45aa9, 0x6dbf, 0x4f1b, { 0xa4, 0x3e, 0x32, 0x87, 0xcb, 0xe5, 0x13, 0x51 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiCpuHtCapableGuid = { 0x0d1b9c8e, 0xf77b, 0x4632, { 0x83, 0x43, 0x91, 0xf4, 0x3d, 0x9a, 0x85, 0x60 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiMemorySetupGuid = { 0x3eeff35f, 0x147c, 0x4cd1, { 0xa2, 0x34, 0x92, 0xa0, 0x69, 0x70, 0x0d, 0xb6 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiMemoryMapGuid = { 0xf8870015, 0x6994, 0x4b98, { 0x95, 0xa2, 0xbd, 0x56, 0xda, 0x91, 0xc0, 0x7f }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gBootOptionsPkgListGuid = { 0x62197ef0, 0x7b7e, 0x11e2, { 0xb9, 0x2a, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gMeSetupInfoGuid = { 0x78259433, 0x7B6D, 0x4DB3, { 0x9A, 0xE8, 0x36, 0xC4, 0xC2, 0xC3, 0xA1, 0x7D }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gSetupFwUpdChgGuid = { 0x37466687, 0x7ea9, 0x4f23, { 0x83, 0xa5, 0x3a, 0xd2, 0x10, 0xe7, 0xa6, 0x67 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gSetupMngChgGuid = { 0x35940cdb, 0x6e2e, 0x4078, { 0xae, 0xf3, 0xc0, 0x80, 0x15, 0x40, 0x81, 0xab }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gMeStateChgGuid = { 0xbc61783c, 0x10b9, 0x43a5, { 0xb7, 0x42, 0x71, 0x6d, 0xfa, 0xb2, 0xa2, 0xa7 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gMeSetupPolicyUpdate = { 0x5c4b7c33, 0xee9b, 0x4eda, { 0x80, 0x53, 0xc9, 0x58, 0x33, 0x12, 0xf7, 0x98 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gIccDataGuid = { 0x64192dca, 0xd034, 0x49d2, { 0xa6, 0xde, 0x65, 0xa8, 0x29, 0xeb, 0x4c, 0x74 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiSetupEnterGuid = { 0x71202EEE, 0x5F53, 0x40d9, { 0xAB, 0x3D, 0x9E, 0x0C, 0x26, 0xD9, 0x66, 0x57 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiAdminPasswordHobGuid = {0x4E173307, 0x92DB, 0x4a4f, {0x9A, 0x8E, 0x86, 0xA8, 0x56, 0x49, 0xB4, 0x05 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gServerCommonTokenSpaceGuid = { 0x356471b1, 0xb483, 0x42ae, { 0xb6, 0xe7, 0x3b, 0x2e, 0xba, 0xb1, 0x4e, 0x15 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPchTokenSpaceGuid = { 0x758e73aa, 0x2587, 0x4ef1, { 0x86, 0xa9, 0x83, 0xa7, 0xfb, 0x87, 0x2a, 0x52 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiMdePkgTokenSpaceGuid = { 0x914AEBE7, 0x4635, 0x459b, { 0xAA, 0x1C, 0x11, 0xE2, 0x19, 0xB0, 0x3A, 0x10 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiIntelFrameworkModulePkgTokenSpaceGuid = { 0xD3705011, 0xBC19, 0x4af7, { 0xBE, 0x16, 0xF6, 0x80, 0x30, 0x37, 0x8C, 0x15 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiMdeModulePkgTokenSpaceGuid = { 0xA1AFF049, 0xFDEB, 0x442a, { 0xB3, 0x20, 0x13, 0xAB, 0x4C, 0xB7, 0x2B, 0xBC }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiCpuTokenSpaceGuid = { 0x2ADA836D, 0x0A3D, 0x43D6, { 0xA2, 0x5A, 0x38, 0x45, 0xCA, 0xD2, 0xD4, 0x00 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiSerialPortTokenSpaceGuid = { 0xac274b5f, 0x4d79, 0x48d1, { 0x96, 0xdf, 0xfe, 0xe3, 0x54, 0xcf, 0x70, 0x83 }};
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
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gChipsetInitInfoHobGuid = { 0xc1392859, 0x1f65, 0x446e, {0xb3, 0xf5, 0x84, 0x35, 0xfc, 0xc7, 0xd1, 0xc4}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gPerformanceProtocolGuid = { 0x76B6BDFA, 0x2ACD, 0x4462, { 0x9E, 0x3F, 0xCB, 0x58, 0xC9, 0x69, 0xD9, 0x37 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gPerformanceExProtocolGuid = { 0x1ea81bec, 0xf01a, 0x4d98, { 0xa2, 0x1,  0x4a, 0x61, 0xce, 0x2f, 0xc0, 0x22 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPlatformInfoGuid = { 0x1e2acc41, 0xe26a, 0x483d, { 0xaf, 0xc7, 0xa0, 0x56, 0xc3, 0x4e, 0x08, 0x7b }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiMeBiosExtensionSetupGuid = { 0x1bad711c, 0xd451, 0x4241, { 0xb1, 0xf3, 0x85, 0x37, 0x81, 0x2e, 0x0c, 0x70 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gDxePlatformMePolicyGuid = { 0x69bf9e8a, 0x4ad6, 0x9a28, { 0x87, 0xf3, 0x09, 0xa0, 0x71, 0x29, 0x2a, 0x00 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiStatusCodeDataTypeStringGuid = { 0x92D11080, 0x496F, 0x4D95, { 0xBE, 0x7E, 0x03, 0x74, 0x88, 0x38, 0x2B, 0x0A }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gAmiGlobalVariableGuid = { 0x1368881, 0xc4ad, 0x4b1d, { 0xb6, 0x31, 0xd5, 0x7a, 0x8e, 0xc8, 0xdb, 0x6b } };

// Protocols
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDevicePathProtocolGuid = { 0x09576E91, 0x6D3F, 0x11D2, { 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHiiDatabaseProtocolGuid = {0xef9fc172, 0xa1b2, 0x4693, {0xb3, 0x27, 0x6d, 0x32, 0xfc, 0x41, 0x60, 0x42}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHiiConfigAccessProtocolGuid = {0x330d4706, 0xf2a0, 0x4e4f, {0xa3, 0x69, 0xb6, 0x6f, 0xa8, 0xd5, 0x43, 0x85}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHiiConfigRoutingProtocolGuid = {0x587e72d7, 0xcc50, 0x4f79, {0x82, 0x09, 0xca, 0x29, 0x1f, 0xc1, 0xa1, 0x0f}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiFormBrowser2ProtocolGuid = {0xb9d4c360, 0xbcfb, 0x4f9b, {0x92, 0x98, 0x53, 0xc1, 0x36, 0x98, 0x22, 0x58}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiTcgProtocolGuid = { 0xf541796d, 0xa62e, 0x4954, { 0xa7, 0x75, 0x95, 0x84, 0xf6, 0x1b, 0x9c, 0xdd }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPlatformPolicyProtocolGuid = {0x2977064f, 0xab96, 0x4fa9, { 0x85, 0x45, 0xf9, 0xc4, 0x02, 0x51, 0xe0, 0x7f}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPlatformTypeProtocolGuid = { 0x171e9398, 0x269c, 0x4081, { 0x90, 0x99, 0x38, 0x44, 0xe2, 0x60, 0x46, 0x6c }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPciRootBridgeIoProtocolGuid = { 0x2F707EBB, 0x4A1A, 0x11D4, { 0x9A, 0x38, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gDxePchPlatformPolicyProtocolGuid = { 0x4b0165a9, 0x61d6, 0x4e23, { 0xa0, 0xb5, 0x3e, 0xc7, 0x9c, 0x2e, 0x30, 0xd5 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPs2PolicyProtocolGuid = { 0x4DF19259, 0xDC71, 0x4D46, { 0xBE, 0xF1, 0x35, 0x7B, 0xB5, 0x78, 0xC4, 0x18 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiIsaIoProtocolGuid = { 0x7ee2bd44, 0x3da0, 0x11d4, { 0x9a, 0x38, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDiskInfoProtocolGuid = { 0xD432A67F, 0x14DC, 0x484B, { 0xB3, 0xBB, 0x3F, 0x02, 0x91, 0x84, 0x93, 0x27 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiDataHubProtocolGuid = { 0xae80d021, 0x618e, 0x11d4, { 0xbc, 0xd7, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiIioUdsProtocolGuid = { 0xa7ced760, 0xc71c, 0x4e1a, { 0xac, 0xb1, 0x89, 0x60, 0x4d, 0x52, 0x16, 0xcb }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiLegacyBootMarkerGuid = { 0x72e07da8, 0x63a9, 0x42d4, { 0x83, 0xd5, 0xb, 0xb5, 0x18, 0x38, 0x44, 0x75 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiWindowsInt10Workaround = { 0x387f555, 0x20a8, 0x4fc2,  { 0xbb, 0x94, 0xcd, 0x30, 0xda, 0x1b, 0x40, 0x8  }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiSmbiosProtocolGuid = {0x3583ff6, 0xcb36, 0x4940, { 0x94, 0x7e, 0xb9, 0xb3, 0x9f, 0x4a, 0xfa, 0xf7}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gDxePchPlatformResetPolicyProtocolGuid = {0x45ada968, 0xa8c5, 0x4f30, {0xac, 0xd4, 0xf5, 0x13, 0xbc, 0xe5, 0xb0, 0xb3}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiIioSystemProtocolGuid = { 0xddc3080a, 0x2740, 0x4ec2, {0x9a, 0xa5, 0xa0, 0xad, 0xef, 0xd6, 0xff, 0x9c }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiMpServiceProtocolGuid = { 0x3fdda605, 0xa76e, 0x4f46, { 0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gWdtProtocolGuid = { 0xB42B8D12, 0x2ACB, 0x499a, { 0xA9, 0x20, 0xDD, 0x5B, 0xE6, 0xCF, 0x09, 0xB1 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gPchResetProtocolGuid = { 0xdb63592c, 0xb8cc, 0x44c8, {0x91, 0x8c, 0x51, 0xf5, 0x34, 0x59, 0x8a, 0x5a }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gIccDataProtocolGuid = { 0x346b6db3, 0x39a3, 0x400e, { 0x81, 0xbd, 0x21, 0x6d, 0xb5, 0x79, 0x74, 0x46 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiCpuCsrAccessGuid = { 0x67835f, 0x9a50, 0x433a, {0x8c, 0xbb, 0x85, 0x20, 0x78, 0x19, 0x78, 0x14 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHiiPackageListProtocolGuid = { 0x6a1ee763, 0xd47a, 0x43b4, {0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gPcdProtocolGuid = { 0x11B34006, 0xD85B, 0x4D0A, { 0xA2, 0x90, 0xD5, 0xA5, 0x71, 0x31, 0x0E, 0xF7 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiPcdProtocolGuid = { 0x13a3f0f6, 0x264a, 0x3ef0, { 0xf2, 0xe0, 0xde, 0xc5, 0x12, 0x34, 0x2f, 0x34 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gGetPcdInfoProtocolGuid = { 0x5be40f57, 0xfa68, 0x4610, { 0xbb, 0xbf, 0xe9, 0xc5, 0xfc, 0xda, 0xd3, 0x65 } };
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiGetPcdInfoProtocolGuid = { 0xfd0f4478,  0xefd, 0x461d, { 0xba, 0x2d, 0xe5, 0x8c, 0x45, 0xfd, 0x5f, 0x5e } };
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
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiS3SaveStateProtocolGuid = {0xe857caf6, 0xc046, 0x45dc, { 0xbe, 0x3f, 0xee, 0x7, 0x65, 0xfb, 0xa8, 0x87}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHiiStringProtocolGuid = {0x0fd96974, 0x23aa, 0x4cdc, {0xb9, 0xcb, 0x98, 0xd1, 0x77, 0x50, 0x32, 0x2a}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHiiImageProtocolGuid = {0x31a6406a, 0x6bdf, 0x4e46, {0xb2, 0xa2, 0xeb, 0xaa, 0x89, 0xc4, 0x09, 0x20}};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiLoadedImageProtocolGuid = { 0x5B1B31A1, 0x9562, 0x11D2, { 0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiHeciProtocolGuid = { 0xCFB33810, 0x6E87, 0x4284, { 0xB2, 0x03, 0xA6, 0x6A, 0xBE, 0x07, 0xF6, 0xE8 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gPlatformMeHookProtocolGuid = { 0xbc52476e, 0xf67e, 0x4301, { 0xb2, 0x62, 0x36, 0x9c, 0x48, 0x78, 0xaa, 0xc2 }};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gMeBiosPayloadDataProtocolGuid = { 0x71a19494, 0x2ab6, 0x4e96, { 0x85, 0x81, 0xcf, 0x34, 0x25, 0x42, 0x73, 0xfe }};

// Definition of PCDs used in this module
GLOBAL_REMOVE_IF_UNREFERENCED const UINT64 _gPcd_FixedAtBuild_PcdPciExpressBaseAddress = _PCD_VALUE_PcdPciExpressBaseAddress;
GLOBAL_REMOVE_IF_UNREFERENCED const BOOLEAN _gPcd_FixedAtBuild_PcdUse1GPageTable = _PCD_VALUE_PcdUse1GPageTable;

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

#define _PCD_TOKEN_PcdSerialBoudRate  125U
#define _PCD_SIZE_PcdSerialBoudRate 4
#define _PCD_GET_MODE_SIZE_PcdSerialBoudRate  _PCD_SIZE_PcdSerialBoudRate 
#define _PCD_VALUE_PcdSerialBoudRate  115200U
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 _gPcd_FixedAtBuild_PcdSerialBoudRate = _PCD_VALUE_PcdSerialBoudRate;
extern const  UINT32  _gPcd_FixedAtBuild_PcdSerialBoudRate;
#define _PCD_GET_MODE_32_PcdSerialBoudRate  _gPcd_FixedAtBuild_PcdSerialBoudRate
//#define _PCD_SET_MODE_32_PcdSerialBoudRate  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdSerialRegisterBase  126U
#define _PCD_SIZE_PcdSerialRegisterBase 8
#define _PCD_GET_MODE_SIZE_PcdSerialRegisterBase  _PCD_SIZE_PcdSerialRegisterBase 
#define _PCD_VALUE_PcdSerialRegisterBase  0x3f8ULL
GLOBAL_REMOVE_IF_UNREFERENCED const UINT64 _gPcd_FixedAtBuild_PcdSerialRegisterBase = _PCD_VALUE_PcdSerialRegisterBase;
extern const  UINT64  _gPcd_FixedAtBuild_PcdSerialRegisterBase;
#define _PCD_GET_MODE_64_PcdSerialRegisterBase  _gPcd_FixedAtBuild_PcdSerialRegisterBase
//#define _PCD_SET_MODE_64_PcdSerialRegisterBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUartDefaultBaudRate  1U
#define _PCD_GET_MODE_64_PcdUartDefaultBaudRate  LibPcdGet64(_PCD_TOKEN_PcdUartDefaultBaudRate)
#define _PCD_GET_MODE_SIZE_PcdUartDefaultBaudRate  LibPcdGetSize(_PCD_TOKEN_PcdUartDefaultBaudRate)
#define _PCD_SET_MODE_64_PcdUartDefaultBaudRate(Value)  LibPcdSet64(_PCD_TOKEN_PcdUartDefaultBaudRate, (Value))
#define _PCD_SET_MODE_64_S_PcdUartDefaultBaudRate(Value)  LibPcdSet64S(_PCD_TOKEN_PcdUartDefaultBaudRate, (Value))

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

#define _PCD_TOKEN_PcdPerformanceLibraryPropertyMask  109U
#define _PCD_SIZE_PcdPerformanceLibraryPropertyMask 1
#define _PCD_GET_MODE_SIZE_PcdPerformanceLibraryPropertyMask  _PCD_SIZE_PcdPerformanceLibraryPropertyMask 
#define _PCD_VALUE_PcdPerformanceLibraryPropertyMask  0x0U
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 _gPcd_FixedAtBuild_PcdPerformanceLibraryPropertyMask = _PCD_VALUE_PcdPerformanceLibraryPropertyMask;
extern const  UINT8  _gPcd_FixedAtBuild_PcdPerformanceLibraryPropertyMask;
#define _PCD_GET_MODE_8_PcdPerformanceLibraryPropertyMask  _gPcd_FixedAtBuild_PcdPerformanceLibraryPropertyMask
//#define _PCD_SET_MODE_8_PcdPerformanceLibraryPropertyMask  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdPostCodePropertyMask  93U
#define _PCD_SIZE_PcdPostCodePropertyMask 1
#define _PCD_GET_MODE_SIZE_PcdPostCodePropertyMask  _PCD_SIZE_PcdPostCodePropertyMask 
#define _PCD_VALUE_PcdPostCodePropertyMask  0x08U
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 _gPcd_FixedAtBuild_PcdPostCodePropertyMask = _PCD_VALUE_PcdPostCodePropertyMask;
extern const  UINT8  _gPcd_FixedAtBuild_PcdPostCodePropertyMask;
#define _PCD_GET_MODE_8_PcdPostCodePropertyMask  _gPcd_FixedAtBuild_PcdPostCodePropertyMask
//#define _PCD_SET_MODE_8_PcdPostCodePropertyMask  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD


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

RETURN_STATUS
EFIAPI
BaseDebugLibSerialPortConstructor (
  VOID
  );

RETURN_STATUS
EFIAPI
BasePciExpressLibConstructor (
  VOID
  );

EFI_STATUS
EFIAPI
UefiLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
DxeS3BootScriptLibS3SaveStateProtocolConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
UefiHiiServicesLibConstructor (
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

  Status = BaseDebugLibSerialPortConstructor ();
  ASSERT_EFI_ERROR (Status);

  Status = BasePciExpressLibConstructor ();
  ASSERT_EFI_ERROR (Status);

  Status = UefiLibConstructor (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);

  Status = DxeS3BootScriptLibS3SaveStateProtocolConstructor (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);

  Status = UefiHiiServicesLibConstructor (ImageHandle, SystemTable);
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
  return SetupDriverEntry (ImageHandle, SystemTable);
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
