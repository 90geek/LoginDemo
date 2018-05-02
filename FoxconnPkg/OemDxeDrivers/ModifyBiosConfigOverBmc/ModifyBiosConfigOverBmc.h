//**********************************************************************
//<OEM_FHDR_START>
//
// Name : ModifyBiosConfigOverBmc.h  
//
// Description:
//  Modify BIOS Configuration Over BMC
//
//<OEM_FHDR_END>
//**********************************************************************

//TH0143B>>>
#define PREVIOUS_SETUP_BIOS_CONFIG_GUID \
{ 0x87d869c, 0xc2ba, 0x476b, { 0x8f, 0xa3, 0x2f, 0x89, 0xcd, 0xfc, 0x49, 0x70 } }
//TH0143B<<<

#pragma pack(1)

typedef struct {
	// Offset: 00h
    UINT8                   ProcessorHyperThreadingDisable;
	UINT8					ProcessorFlexibleRatio;			//Does not support
    UINT8                   ExecuteDisableBit;
    UINT8   				ProcessorVmxEnable;
    UINT8   				ProcessorLtsxEnable;
    UINT8                   MlcStreamerPrefetcherEnable;
	UINT8					MlcSpatialPrefetcherEnable;
    UINT8                   DCUStreamerPrefetcherEnable;
    UINT8   				DCUIPPrefetcherEnable;
    UINT8   				DCUModeSelection;
    UINT8                   DcaEnable;
	UINT8					AesEnable;
    UINT8                   CoresToEnable[4];
    
    // Offset: 10h
    UINT8   				QpiLinkSpeed;
    UINT8   				UncoreFrequencyScaling;
    UINT8                   ProcessorEistEnable;
	UINT8					TurboMode;
    UINT8                   BootPState;
    UINT8   				ProcessorCcxEnable;
    UINT8   				PackageCState;
    UINT8                   C3Enable;
	UINT8					C6Enable;
    UINT8                   ProcessorC1eEnable;
    UINT8   				TStateEnable;
    UINT8   				AltEngPerfBIAS;
    UINT8                   DdrFreqLimit;
	UINT8					thermalthrottlingsupport;
    UINT8                   EarlySnoopEn;
    UINT8   				ClusterOnDieEn;
        
    // Offset: 20h
    UINT8   				NumaEn;
    UINT8                   SocketInterleaveBelow4GB;
	UINT8					ChannelInterleaving;
    UINT8                   RankInterleaving;
    UINT8   				RASMode;
    UINT8   				enableSparing;
    UINT8                   PatrolScrub;
	UINT8					PatrolScrubDuration;
    UINT8                   DemandScrubMode;
    UINT8   				DeviceTaggingMode;
    UINT8                   VTdSupport;
	UINT8					PxeOpRom;						//SETUP_DATA.PxeOpRom
    UINT8                   SetFanProfile;					//Does not support
    UINT8   				SOLConsoleredirection;			//Does not support
    UINT8                   BootMode;						//Does not support
    UINT8                   ProcessorEistPsdFunc;
    
    // Offset: 30h                   
	UINT8                   UselessValue;           		//Does not support
	UINT8                   SriovSupport;           		//SETUP_DATA.SriovSupport
	UINT16                  EnergyPerformance;   			//Does not support
	UINT16                  spareErrTh;

} BIOS_CONFIG_PART;

typedef struct {
	UINT16					Offset;				//Offset to read
	BIOS_CONFIG_PART		BiosConfigPart;
}REPORT_BIOS_CONFIG;

typedef struct {
	UINT8					Count;				//Count returned ---count is ¡®1¡¯ based
	BIOS_CONFIG_PART		BiosConfigPart;
}GET_BIOS_CONFIG;

#pragma pack()
