/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_80CF7257_87AB_47f9_A3FE_D50B76D89541
#define _AUTOGENH_80CF7257_87AB_47f9_A3FE_D50B76D89541

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x80CF7257, 0x87AB, 0x47f9, {0xA3, 0xFE, 0xD5, 0x0B, 0x76, 0xD8, 0x95, 0x41}}

// Guids
extern EFI_GUID gPcdDataBaseHobGuid;
extern EFI_GUID gPcdDataBaseSignatureGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiFileInfoGuid;

// Protocols
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gAmiDebugServiceProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gEfiGraphicsOutputProtocolGuid;
extern EFI_GUID gEfiHiiFontProtocolGuid;
extern EFI_GUID gEfiUgaDrawProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gEfiDriverConfigurationProtocolGuid;
extern EFI_GUID gEfiDriverConfiguration2ProtocolGuid;
extern EFI_GUID gEfiDriverDiagnosticsProtocolGuid;
extern EFI_GUID gEfiDriverDiagnostics2ProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gEfiLoadFileProtocolGuid;
extern EFI_GUID gEfiLoadFile2ProtocolGuid;
extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdVpdBaseAddress  130U
#define _PCD_SIZE_PcdVpdBaseAddress 4
#define _PCD_GET_MODE_SIZE_PcdVpdBaseAddress  _PCD_SIZE_PcdVpdBaseAddress 
#define _PCD_VALUE_PcdVpdBaseAddress  0x0U
extern const  UINT32  _gPcd_FixedAtBuild_PcdVpdBaseAddress;
#define _PCD_GET_MODE_32_PcdVpdBaseAddress  _gPcd_FixedAtBuild_PcdVpdBaseAddress
//#define _PCD_SET_MODE_32_PcdVpdBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c

#define PCD_PEI_SERVICE_DRIVER_VERSION         4

//
// External PCD database debug information
//
#if 0
#define PEI_GUID_TABLE_SIZE                1U
#define PEI_STRING_TABLE_SIZE              1U
#define PEI_SKUID_TABLE_SIZE               1U
#define PEI_LOCAL_TOKEN_NUMBER_TABLE_SIZE  5
#define PEI_LOCAL_TOKEN_NUMBER             5
#define PEI_EXMAPPING_TABLE_SIZE           1U
#define PEI_EX_TOKEN_NUMBER                0U
#define PEI_SIZE_TABLE_SIZE                2U
#define PEI_SKU_HEAD_SIZE                  1U
#define PEI_GUID_TABLE_EMPTY               TRUE
#define PEI_STRING_TABLE_EMPTY             TRUE
#define PEI_SKUID_TABLE_EMPTY              TRUE
#define PEI_DATABASE_EMPTY                 FALSE
#define PEI_EXMAP_TABLE_EMPTY              TRUE

typedef struct {
  UINT64             PcdUartDefaultBaudRate_914aebe7_4635_459b_aa1c_11e219b03a10[1];


  UINT32             PcdPchSataInitReg78Data_758e73aa_2587_4ef1_86a9_83a7fb872a52[1];
  UINT32             PcdPchSataInitReg88Data_758e73aa_2587_4ef1_86a9_83a7fb872a52[1];



  DYNAMICEX_MAPPING  ExMapTable[PEI_EXMAPPING_TABLE_SIZE];
  UINT32             LocalTokenNumberTable[PEI_LOCAL_TOKEN_NUMBER_TABLE_SIZE];
  GUID               GuidTable[PEI_GUID_TABLE_SIZE];


  SKU_HEAD           SkuHead[PEI_SKU_HEAD_SIZE];

  UINT8              StringTable[1]; /* _ */

  SIZE_INFO          SizeTable[PEI_SIZE_TABLE_SIZE];




  BOOLEAN            PcdBootState_d3705011_bc19_4af7_be16_f68030378c15[1];


  UINT8              SkuIdTable[PEI_SKUID_TABLE_SIZE];
  SKU_ID             SystemSkuId;
} PEI_PCD_DATABASE_INIT;

typedef struct {


  UINT32   PcdMePlatformWarmResetCounter_731d14ec_7f7c_4403_8c02_96ac8c335c2b[1];




} PEI_PCD_DATABASE_UNINIT;

typedef struct {
  //GUID                  Signature;  // PcdDataBaseGuid
  //UINT32                Length;
  //UINT32                UninitDataBaseSize;// Total size for PCD those default value with 0.
  //TABLE_OFFSET          LocalTokenNumberTableOffset;
  //TABLE_OFFSET          ExMapTableOffset;
  //TABLE_OFFSET          GuidTableOffset;     
  //TABLE_OFFSET          StringTableOffset;
  //TABLE_OFFSET          SizeTableOffset;
  //TABLE_OFFSET          SkuIdTableOffset; 
  //UINT16                LocalTokenCount;  // LOCAL_TOKEN_NUMBER for all
  //UINT16                ExTokenCount;     // EX_TOKEN_NUMBER for DynamicEx
  //UINT16                GuidTableCount;   // The Number of Guid in GuidTable
  //SKU_ID                SystemSkuId;      // Current SkuId value.
  //UINT8                 Pad;
  PEI_PCD_DATABASE_INIT    Init;
  PEI_PCD_DATABASE_UNINIT  Uninit;
} PEI_PCD_DATABASE;

#define PEI_NEX_TOKEN_NUMBER (PEI_LOCAL_TOKEN_NUMBER - PEI_EX_TOKEN_NUMBER)
#endif

#define PCD_DXE_SERVICE_DRIVER_VERSION         4

//
// External PCD database debug information
//
#if 0
#define DXE_GUID_TABLE_SIZE                3U
#define DXE_STRING_TABLE_SIZE              2416U
#define DXE_SKUID_TABLE_SIZE               1U
#define DXE_LOCAL_TOKEN_NUMBER_TABLE_SIZE  80
#define DXE_LOCAL_TOKEN_NUMBER             80
#define DXE_EXMAPPING_TABLE_SIZE           1U
#define DXE_EX_TOKEN_NUMBER                1U
#define DXE_SIZE_TABLE_SIZE                42U
#define DXE_SKU_HEAD_SIZE                  1U
#define DXE_GUID_TABLE_EMPTY               FALSE
#define DXE_STRING_TABLE_EMPTY             FALSE
#define DXE_SKUID_TABLE_EMPTY              TRUE
#define DXE_DATABASE_EMPTY                 FALSE
#define DXE_EXMAP_TABLE_EMPTY              FALSE

typedef struct {


  UINT32             PcdCpuProcessorFeatureUserConfiguration_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];



  DYNAMICEX_MAPPING  ExMapTable[DXE_EXMAPPING_TABLE_SIZE];
  UINT32             LocalTokenNumberTable[DXE_LOCAL_TOKEN_NUMBER_TABLE_SIZE];
  GUID               GuidTable[DXE_GUID_TABLE_SIZE];
  STRING_HEAD        PcdSystemManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdSystemProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdSystemVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdSystemSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdBaseBoardManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdBaseBoardProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdBaseBoardVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdBaseBoardSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdBaseBoardAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdBaseBoardChassisLocation_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdBaseBoardChassisLink_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdBaseBoardNumberLinks_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdChassisManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdChassisVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdChassisSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdChassisAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdChassisElements_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdSdrVersionNo_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdSystemUuid_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  STRING_HEAD        PcdSocketBaseBusNumbers_356471b1_b483_42ae_b6e7_3b2ebab14e15[1];
  STRING_HEAD        PcdCpuSocketId_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];

  VARIABLE_HEAD      PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400_Variable_Header[1];
  VARIABLE_HEAD      PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15_Variable_Header[1];
  VARIABLE_HEAD      PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15_Variable_Header[1];

  SKU_HEAD           SkuHead[DXE_SKU_HEAD_SIZE];

  UINT8              StringTable[134]; /* PcdSystemManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_1[134]; /* PcdSystemProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_2[134]; /* PcdSystemVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_3[134]; /* PcdSystemSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_4[134]; /* PcdBaseBoardManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_5[134]; /* PcdBaseBoardProductName_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_6[134]; /* PcdBaseBoardVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_7[134]; /* PcdBaseBoardSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_8[134]; /* PcdBaseBoardAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_9[134]; /* PcdBaseBoardChassisLocation_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_10[134]; /* PcdBaseBoardChassisLink_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_11[134]; /* PcdBaseBoardNumberLinks_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_12[134]; /* PcdChassisManufacturer_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_13[134]; /* PcdChassisVersion_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_14[134]; /* PcdChassisSerialNumber_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_15[134]; /* PcdChassisAssetTag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_16[134]; /* PcdChassisElements_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_17[16]; /* PcdSdrVersionNo_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_18[50]; /* PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400 */
  UINT8              StringTable_19[36]; /* PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15 */
  UINT8              StringTable_20[16]; /* PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15 */
  UINT8              StringTable_21[16]; /* PcdSystemUuid_1e21c326_0d40_40f2_9f02_3a9b7838aa6b */
  UINT8              StringTable_22[2]; /* PcdSocketBaseBusNumbers_356471b1_b483_42ae_b6e7_3b2ebab14e15 */
  UINT8              StringTable_23[2]; /* PcdCpuSocketId_2ada836d_0a3d_43d6_a25a_3845cad2d400 */

  SIZE_INFO          SizeTable[DXE_SIZE_TABLE_SIZE];
  UINT16             BulkDataTransferTimeout_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];

  UINT16             PcdPlatformBootTimeOut_d3705011_bc19_4af7_be16_f68030378c15_VariableDefault_2;

  UINT8              PcdSbspSelection_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT8              PcdBaseBoardFeatureFlag_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8              PcdBaseBoardType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8              PcdChassisBootupState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8              PcdChassisPowerSupplyState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8              PcdChassisThermalState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8              PcdChassisSecurityState_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8              PcdChassisHeight_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8              BulkDataTransferInterfaceType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8              PcdCpuSmmSmrr2CacheType_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];


  BOOLEAN            PcdCpuHwCoordination_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];

  BOOLEAN            PcdCpuSmmMsrSaveStateEnable_2ada836d_0a3d_43d6_a25a_3845cad2d400_VariableDefault_2;
  BOOLEAN            PcdUefiOptimizedBoot_356471b1_b483_42ae_b6e7_3b2ebab14e15_VariableDefault_2;

  UINT8              SkuIdTable[DXE_SKUID_TABLE_SIZE];
  SKU_ID             SystemSkuId;
} DXE_PCD_DATABASE_INIT;

typedef struct {

  UINT64   PcdIdentifyMappingPageTablePtr_a1aff049_fdeb_442a_b320_13ab4cb72bbc[1];
  UINT64   PcdPlatformCpuAssetTags_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdPlatformCpuSocketNames_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdPlatformCpuFrequencyLists_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdCpuConfigContextBuffer_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdCpuPageTableAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdCpuMtrrTableAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdCpuS3DataAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdCpuIioLlcWaysBitMask_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdCpuQlruCfgBitMask_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdCpuPmStructAddr_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT64   PcdCpuHotPlugDataAddress_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];

  UINT32   PcdPlatformCpuSocketCount_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT32   PcdCpuProcessorFeatureSetting_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT32   PcdCpuProcessorFeatureCapability_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT32   PcdCpuProcessorFeatureSettingEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT32   PcdCpuProcessorFeatureCapabilityEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT32   PcdCpuProcessorFeatureUserConfigurationEx1_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT32   PcdCpuTurboOverride_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT32   PcdChassisOemDefined_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT32   PcdCpuSmmSmrr2Base_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT32   PcdCpuSmmSmrr2Size_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];

  UINT16   PcdCpuAcpiLvl2Addr_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT16   PchDiskError_d34d3234_38ba_428b_9acd_84e830a80785[1];

  UINT8    PcdCpuCallbackSignal_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT8    PcdCpuEnergyPolicy_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT8    PcdCpuClockModulationDutyCycle_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT8    PcdCpuPackageCStateLimit_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT8    PcdCpuDcuMode_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT8    PcdCpuProcessorMsrLockCtrl_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT8    PcdCpuDebugInterface_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  UINT8    PcdRtcWakeupTimeHour_758e73aa_2587_4ef1_86a9_83a7fb872a52[1];
  UINT8    PcdRtcWakeupTimeMinute_758e73aa_2587_4ef1_86a9_83a7fb872a52[1];
  UINT8    PcdRtcWakeupTimeSecond_758e73aa_2587_4ef1_86a9_83a7fb872a52[1];
  UINT8    DiskController_d34d3234_38ba_428b_9acd_84e830a80785[1];
  UINT8    PcdChassisType_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8    PcdChassisElementRecordLength_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];
  UINT8    PcdChassisElementCount_1e21c326_0d40_40f2_9f02_3a9b7838aa6b[1];

  BOOLEAN  PcdIsPowerOnReset_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  BOOLEAN  PcdWakeOnRTCS5_758e73aa_2587_4ef1_86a9_83a7fb872a52[1];
  BOOLEAN  PcdCpuSmmUseDelayIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  BOOLEAN  PcdCpuSmmUseBlockIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];
  BOOLEAN  PcdCpuSmmUseSmmEnableIndication_2ada836d_0a3d_43d6_a25a_3845cad2d400[1];

} DXE_PCD_DATABASE_UNINIT;

typedef struct {
  //GUID                  Signature;  // PcdDataBaseGuid
  //UINT32                Length;
  //UINT32                UninitDataBaseSize;// Total size for PCD those default value with 0.
  //TABLE_OFFSET          LocalTokenNumberTableOffset;
  //TABLE_OFFSET          ExMapTableOffset;
  //TABLE_OFFSET          GuidTableOffset;     
  //TABLE_OFFSET          StringTableOffset;
  //TABLE_OFFSET          SizeTableOffset;
  //TABLE_OFFSET          SkuIdTableOffset; 
  //UINT16                LocalTokenCount;  // LOCAL_TOKEN_NUMBER for all
  //UINT16                ExTokenCount;     // EX_TOKEN_NUMBER for DynamicEx
  //UINT16                GuidTableCount;   // The Number of Guid in GuidTable
  //SKU_ID                SystemSkuId;      // Current SkuId value.
  //UINT8                 Pad;
  DXE_PCD_DATABASE_INIT    Init;
  DXE_PCD_DATABASE_UNINIT  Uninit;
} DXE_PCD_DATABASE;

#define DXE_NEX_TOKEN_NUMBER (DXE_LOCAL_TOKEN_NUMBER - DXE_EX_TOKEN_NUMBER)
#endif


EFI_STATUS
EFIAPI
PcdDxeInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
