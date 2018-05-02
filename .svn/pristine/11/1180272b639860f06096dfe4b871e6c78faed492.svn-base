//**********************************************************************
//<OEM_FHDR_START>
//
// Name:    ModifyBiosConfigOverBmc.c
//
// Description:
//  Modify BIOS Configuration Over BMC
//
//<OEM_FHDR_END>
//**********************************************************************

#include "ModifyBiosConfigOverBMC.h"
#include <MdePkg\Include\Library\DebugLib.h>
#include <AmiCompatibilityPkg\Include\AmiDxeLib.h>
#include <GrantleyPkg\Include\Guid\SetupVariable.h>
#include <AmiCompatibilityPkg\Include\Setup.h>
#include <GrantleySocketPkg\Library\MemoryQpiInit\Platform\Include\MemDefaults.H>
#include <MdePkg\Include\Library\UefiLib.h>
#include <MdePkg\Include\Library\MemoryAllocationLib.h>
#include <AmiIpmiPkg\Include\Protocol\IPMITransportProtocol.h>
#include <MdePkg\Include\Library\IoLib.h>
#include <AmiCompatibilityPkg\Include\AmiLib.h>

extern	EFI_BOOT_SERVICES			*gBS;
extern	EFI_RUNTIME_SERVICES		*gRT;
extern  EFI_GUID                    gAmiTseEventBeforeBootGuid;
extern	EFI_GUID					gAmiTseNVRAMUpdateGuid;

//
//Define reset type
//
#define WITHOUT_POWER_CYCLE_RESET       BIT0
#define POWER_CYCLE_RESET               BIT1


//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetCurrentConfigFromBios
//
// Description: 
//
// Input:       *BiosConfigPart
//
// Output:      *BiosConfigPart
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
VOID
GetCurrentConfigFromBios( IN OUT BIOS_CONFIG_PART *BiosConfigPart )
{
	EFI_STATUS                      Status;
	EFI_GUID						gSetupGuid = SETUP_GUID;
	SYSTEM_CONFIGURATION            SystemConfiguration;
	SETUP_DATA                      SetupData;
	UINTN                           VarSize;
	
    VarSize = sizeof(SYSTEM_CONFIGURATION);
	Status = gRT->GetVariable (
					L"IntelSetup",
					&gEfiSetupVariableGuid,
					NULL,
					&VarSize,
					&SystemConfiguration
					);
                  
    if(Status == EFI_SUCCESS){
    
        VarSize = sizeof (SETUP_DATA);
        Status = gRT->GetVariable (
                        L"Setup",
                        &gSetupGuid,
                        NULL,
                        &VarSize,
                        &SetupData 
                        );
                        
        if(Status == EFI_SUCCESS){

            // Offset: 00h - 0fh
	        //CDL002029 ++ >> Fixed HT issue
	        #if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
              if (SystemConfiguration.ProcessorHyperThreadingDisable == 0){
                BiosConfigPart->ProcessorHyperThreadingDisable = 1;
  	          } else if (SystemConfiguration.ProcessorHyperThreadingDisable == 1){
                  BiosConfigPart->ProcessorHyperThreadingDisable = 0;
	          } 
            #else 
	          BiosConfigPart->ProcessorHyperThreadingDisable   = SystemConfiguration.ProcessorHyperThreadingDisable;
	        #endif
	        //CDL002029 ++ <<
			

            BiosConfigPart->ProcessorFlexibleRatio           = 0xff;		                                    	//Does not support 
            BiosConfigPart->ExecuteDisableBit                = SystemConfiguration.ExecuteDisableBit;
            BiosConfigPart->ProcessorVmxEnable               = SystemConfiguration.ProcessorVmxEnable;
            BiosConfigPart->ProcessorLtsxEnable              = SystemConfiguration.ProcessorLtsxEnable;
            BiosConfigPart->MlcStreamerPrefetcherEnable      = SystemConfiguration.MlcStreamerPrefetcherEnable;
            BiosConfigPart->MlcSpatialPrefetcherEnable       = SystemConfiguration.MlcSpatialPrefetcherEnable;
            BiosConfigPart->DCUStreamerPrefetcherEnable      = SystemConfiguration.DCUStreamerPrefetcherEnable;
            BiosConfigPart->DCUIPPrefetcherEnable            = SystemConfiguration.DCUIPPrefetcherEnable;
            BiosConfigPart->DCUModeSelection                 = SystemConfiguration.DCUModeSelection;
            BiosConfigPart->DcaEnable                        = SystemConfiguration.DcaEnable;
            BiosConfigPart->AesEnable                        = SystemConfiguration.AesEnable;                     
			
	        //CDL002029 ++ >> Fixed Core Number issue
			#if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
              BiosConfigPart->CoresToEnable[0]               = SystemConfiguration.CoresToEnable[0];  // Processor 0 Code Number           	                                
              BiosConfigPart->CoresToEnable[1]               = SystemConfiguration.CoresToEnable[1];  // Processor 1 Code Number           	  
            #else 
			  BiosConfigPart->CoresToEnable[0]               = 0xff;             	                    //Does not support 
              BiosConfigPart->CoresToEnable[1]               = 0xff;   
    	    #endif
			//CDL002029 ++ <<   
			
			BiosConfigPart->CoresToEnable[2]                 = 0xff;                                                	//Does not support 
			BiosConfigPart->CoresToEnable[3]                 = 0xff;                                                	//Does not support 

            // Offset: 10h - 1fh
            BiosConfigPart->QpiLinkSpeed                     = SystemConfiguration.QpiLinkSpeed;
//TH0190            BiosConfigPart->UncoreFrequencyScaling           = 0xff;                                                	//Does not support 
            BiosConfigPart->UncoreFrequencyScaling           = SystemConfiguration.UFSDisable; //TH0190
            
		    //CDL002029 ++ >> 	
			#if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
              if (SystemConfiguration.ProcessorEistEnable == 0) {
                BiosConfigPart->ProcessorEistEnable = 1;
	          } else if (SystemConfiguration.ProcessorEistEnable == 1){
                  BiosConfigPart->ProcessorEistEnable = 0;
	          } 
            #else 
			  BiosConfigPart->ProcessorEistEnable            = SystemConfiguration.ProcessorEistEnable;
            #endif
			//CDL002029 ++ << 
			
			//CDL002029 ++ >> 	
			#if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
              if (SystemConfiguration.TurboMode == 0) {
                BiosConfigPart->TurboMode = 1;
	          } else if (SystemConfiguration.TurboMode == 1){
                  BiosConfigPart->TurboMode = 0;
	          } 
            #else 
			  BiosConfigPart->TurboMode                      = SystemConfiguration.TurboMode;
            #endif
			//CDL002029 ++ << 
			            
            BiosConfigPart->BootPState                       = SystemConfiguration.BootPState;
            BiosConfigPart->ProcessorCcxEnable               = SystemConfiguration.ProcessorCcxEnable;
            BiosConfigPart->PackageCState                    = SystemConfiguration.PackageCState;
            BiosConfigPart->C3Enable                         = SystemConfiguration.C3Enable;
            BiosConfigPart->C6Enable                         = SystemConfiguration.C6Enable;
            BiosConfigPart->ProcessorC1eEnable               = SystemConfiguration.ProcessorC1eEnable;
            BiosConfigPart->TStateEnable                     = SystemConfiguration.TStateEnable;
            BiosConfigPart->AltEngPerfBIAS                   = SystemConfiguration.AltEngPerfBIAS; 
            BiosConfigPart->DdrFreqLimit                     = SystemConfiguration.DdrFreqLimit;
            BiosConfigPart->thermalthrottlingsupport         = SystemConfiguration.thermalthrottlingsupport;
            BiosConfigPart->EarlySnoopEn                     = SystemConfiguration.EarlySnoopEn;
            BiosConfigPart->ClusterOnDieEn                   = SystemConfiguration.ClusterOnDieEn;
           
            // Offset: 20h - 2fh
            BiosConfigPart->NumaEn		                     = SystemConfiguration.NumaEn;
            BiosConfigPart->SocketInterleaveBelow4GB         = SystemConfiguration.SocketInterleaveBelow4GB;
            BiosConfigPart->ChannelInterleaving              = SystemConfiguration.ChannelInterleaving;
            BiosConfigPart->RankInterleaving                 = SystemConfiguration.RankInterleaving;
            BiosConfigPart->RASMode                          = SystemConfiguration.RASMode;
            BiosConfigPart->enableSparing                    = SystemConfiguration.enableSparing;
            BiosConfigPart->PatrolScrub                      = SystemConfiguration.PatrolScrub;
            BiosConfigPart->PatrolScrubDuration              = SystemConfiguration.PatrolScrubDuration;
            BiosConfigPart->DemandScrubMode                  = SystemConfiguration.DemandScrubMode;
            BiosConfigPart->DeviceTaggingMode                = SystemConfiguration.DeviceTaggingMode;           
            BiosConfigPart->VTdSupport                       = SystemConfiguration.VTdSupport;     
            BiosConfigPart->PxeOpRom                         = SetupData.PxeOpRom;										//SETUP_DATA.PxeOpRom
            BiosConfigPart->SetFanProfile                    = 0xff;			                            //Does not support  
            
			//CDL002029 ++ >>
            #if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
	          BiosConfigPart->SOLConsoleredirection            = SetupData.ConsoleRedirectionEnable[1];	                  //SOL Enable/Disable		                                    	
              BiosConfigPart->BootMode                         = SystemConfiguration.NmPwrOptBoot;                        //NV Power Boot Mode
	        #else 
			  BiosConfigPart->SOLConsoleredirection            = 0xff;			                                    	//Does not support 
              BiosConfigPart->BootMode                         = 0xff;
            #endif
			//CDL002029 ++ <<

            BiosConfigPart->ProcessorEistPsdFunc             = SystemConfiguration.ProcessorEistPsdFunc;
           
            // Offset: 30h - 35h
            BiosConfigPart->UselessValue                     = 0xff;			                                    	//Does not support 
            BiosConfigPart->SriovSupport                     = SetupData.SriovSupport;                                  //SETUP_DATA.SriovSupport
            BiosConfigPart->EnergyPerformance	             = 0xffff;			                                    	//Does not support
            BiosConfigPart->spareErrTh						 = SystemConfiguration.spareErrTh;

        }
    }
}


//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ValidateAndSetBiosConfig
//
// Description: 
//
// Input:       BIOS_CONFIG_PART	*BiosConfigPart	- A pointer point to request data which get from BMC
//				UINT8				*ResetType - Indicate the reset type after set configuration to BIOS.
//
// Output:      NONE
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
VOID
ValidateAndSetBiosConfig( IN BIOS_CONFIG_PART *BiosConfigPart, IN UINT8 *ResetType)
{
	EFI_STATUS                      Status;
	EFI_GUID						gSetupGuid = SETUP_GUID;
	SYSTEM_CONFIGURATION            SystemConfiguration;
	SETUP_DATA                      SetupData;
	UINTN                           VarSize;
	UINT32                          VarAttribute1;
	UINT32                          VarAttribute2;

	//CLD002029 ++ >>
	#if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
	  UINT32                           Core_Number_Per_PKG;
	  UINT32                           RegEax = 0;
      AsmCpuidEx (0x04, 0, &RegEax, NULL, NULL, NULL);
      Core_Number_Per_PKG = (RegEax >> 26) + 1;
     #endif
     //CLD002029 ++ <<

    VarSize = sizeof(SYSTEM_CONFIGURATION);
	Status = gRT->GetVariable (
					L"IntelSetup",
					&gEfiSetupVariableGuid,
					&VarAttribute1,
					&VarSize,
					&SystemConfiguration
					);
                    
    if(Status == EFI_SUCCESS){
    
        VarSize = sizeof (SETUP_DATA);
        Status = gRT->GetVariable (
                        L"Setup",
                        &gSetupGuid,
                        &VarAttribute2,
                        &VarSize,
                        &SetupData 
                        );
                        
        if(Status == EFI_SUCCESS){
              //
              // Offset: 00h - 0fh
              //
		
		 //CDL002029 ++ >>	  
		 #if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
		  if(((SystemConfiguration.ProcessorHyperThreadingDisable + BiosConfigPart->ProcessorHyperThreadingDisable) != 1) &&  
        	 (BiosConfigPart->ProcessorHyperThreadingDisable == 0 || BiosConfigPart->ProcessorHyperThreadingDisable == 1)){
			 if(BiosConfigPart->ProcessorHyperThreadingDisable == 0){
               SystemConfiguration.ProcessorHyperThreadingDisable = 1;
		     } else if (BiosConfigPart->ProcessorHyperThreadingDisable == 1){
                 SystemConfiguration.ProcessorHyperThreadingDisable = 0;
	         }				      
        	 *ResetType |= POWER_CYCLE_RESET;
           }
         #else 
		   if((SystemConfiguration.ProcessorHyperThreadingDisable != BiosConfigPart->ProcessorHyperThreadingDisable) && 
             (BiosConfigPart->ProcessorHyperThreadingDisable == 0 || BiosConfigPart->ProcessorHyperThreadingDisable == 1)){
        	    SystemConfiguration.ProcessorHyperThreadingDisable = BiosConfigPart->ProcessorHyperThreadingDisable;
        		*ResetType |= POWER_CYCLE_RESET;
        	}
         #endif
		 //CDL002029 ++ <<
        	
          
        	if((SystemConfiguration.ExecuteDisableBit != BiosConfigPart->ExecuteDisableBit) && 
        			(BiosConfigPart->ExecuteDisableBit == 0 || BiosConfigPart->ExecuteDisableBit == 1)){
        		SystemConfiguration.ExecuteDisableBit = BiosConfigPart->ExecuteDisableBit;
        		*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if(SystemConfiguration.ProcessorVmxEnable != BiosConfigPart->ProcessorVmxEnable && 
        			(BiosConfigPart->ProcessorVmxEnable == 0 || BiosConfigPart->ProcessorVmxEnable == 1)){
				SystemConfiguration.ProcessorVmxEnable = BiosConfigPart->ProcessorVmxEnable;
				*ResetType |= POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.ProcessorLtsxEnable != BiosConfigPart->ProcessorLtsxEnable) && 
        			(BiosConfigPart->ProcessorLtsxEnable == 0 || BiosConfigPart->ProcessorLtsxEnable == 1)){
				SystemConfiguration.ProcessorLtsxEnable = BiosConfigPart->ProcessorLtsxEnable;
				*ResetType |= POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.MlcStreamerPrefetcherEnable != BiosConfigPart->MlcStreamerPrefetcherEnable) && 
        			(BiosConfigPart->MlcStreamerPrefetcherEnable == 0 || BiosConfigPart->MlcStreamerPrefetcherEnable == 1)){
				SystemConfiguration.MlcStreamerPrefetcherEnable = BiosConfigPart->MlcStreamerPrefetcherEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.MlcSpatialPrefetcherEnable != BiosConfigPart->MlcSpatialPrefetcherEnable) && 
        			(BiosConfigPart->MlcSpatialPrefetcherEnable == 0 || BiosConfigPart->MlcSpatialPrefetcherEnable == 1)){
				SystemConfiguration.MlcSpatialPrefetcherEnable = BiosConfigPart->MlcSpatialPrefetcherEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.DCUStreamerPrefetcherEnable != BiosConfigPart->DCUStreamerPrefetcherEnable) && 
        			(BiosConfigPart->DCUStreamerPrefetcherEnable == 0 || BiosConfigPart->DCUStreamerPrefetcherEnable == 1)){
				SystemConfiguration.DCUStreamerPrefetcherEnable = BiosConfigPart->DCUStreamerPrefetcherEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.DCUIPPrefetcherEnable != BiosConfigPart->DCUIPPrefetcherEnable) && 
        			(BiosConfigPart->DCUIPPrefetcherEnable == 0 || BiosConfigPart->DCUIPPrefetcherEnable == 1)){
				SystemConfiguration.DCUIPPrefetcherEnable = BiosConfigPart->DCUIPPrefetcherEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.DCUModeSelection != BiosConfigPart->DCUModeSelection) && 
        			(BiosConfigPart->DCUModeSelection == 0 || BiosConfigPart->DCUModeSelection == 1)){
				SystemConfiguration.DCUModeSelection = BiosConfigPart->DCUModeSelection;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.DcaEnable != BiosConfigPart->DcaEnable) && 
        			(BiosConfigPart->DcaEnable == 0 || BiosConfigPart->DcaEnable == 1 || BiosConfigPart->DcaEnable == 2)){
				SystemConfiguration.DcaEnable = BiosConfigPart->DcaEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.AesEnable != BiosConfigPart->AesEnable) && 
        			(BiosConfigPart->AesEnable == 0 || BiosConfigPart->AesEnable == 1)){
				SystemConfiguration.AesEnable = BiosConfigPart->AesEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}

			//CDL002029 ++ >>
			#if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
			  if((SystemConfiguration.CoresToEnable[0] != BiosConfigPart->CoresToEnable[0]) && 
                (BiosConfigPart->CoresToEnable[0] >= 0 && BiosConfigPart->CoresToEnable[0] <= Core_Number_Per_PKG)){
          	
				   SystemConfiguration.CoresToEnable[0] = BiosConfigPart->CoresToEnable[0];
				  *ResetType |= WITHOUT_POWER_CYCLE_RESET;
               }

			   if((SystemConfiguration.CoresToEnable[1] != BiosConfigPart->CoresToEnable[1]) && 
          	     (BiosConfigPart->CoresToEnable[1] >= 0 && BiosConfigPart->CoresToEnable[1] <= Core_Number_Per_PKG)){
        		
				    SystemConfiguration.CoresToEnable[1] = BiosConfigPart->CoresToEnable[1];
				    *ResetType |= WITHOUT_POWER_CYCLE_RESET;
               }
		    #endif
            //CDL002029 ++ <<
        	
        	//
            // Offset: 10h - 1fh
        	//
        	if((SystemConfiguration.QpiLinkSpeed != BiosConfigPart->QpiLinkSpeed) && 
        			(BiosConfigPart->QpiLinkSpeed == 1 || BiosConfigPart->QpiLinkSpeed == 3 || BiosConfigPart->QpiLinkSpeed == 5 || 
        			BiosConfigPart->QpiLinkSpeed == 6 || BiosConfigPart->QpiLinkSpeed == 7)){
				SystemConfiguration.QpiLinkSpeed = BiosConfigPart->QpiLinkSpeed;
				*ResetType |= POWER_CYCLE_RESET;
        	}
//TH0190>>>
        	if((SystemConfiguration.UFSDisable != BiosConfigPart->UncoreFrequencyScaling) && 
        			(BiosConfigPart->UncoreFrequencyScaling == 0 || BiosConfigPart->UncoreFrequencyScaling == 1)){
				SystemConfiguration.UFSDisable = BiosConfigPart->UncoreFrequencyScaling;
				*ResetType |= POWER_CYCLE_RESET;
        	}
//TH0190<<<

        //CDL002029 ++ >>
        #if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
		  if(((SystemConfiguration.ProcessorEistEnable + BiosConfigPart->ProcessorEistEnable)!= 1) && 
            (BiosConfigPart->ProcessorEistEnable == 0 || BiosConfigPart->ProcessorEistEnable == 1)){
     				
			if(BiosConfigPart->ProcessorEistEnable == 0){
              SystemConfiguration.ProcessorEistEnable = 1;
			} else if (BiosConfigPart->ProcessorEistEnable == 1){
                SystemConfiguration.ProcessorEistEnable = 0;
			}
			
			*ResetType |= WITHOUT_POWER_CYCLE_RESET;
          }
        #else 
		  if((SystemConfiguration.ProcessorEistEnable != BiosConfigPart->ProcessorEistEnable) && 
            (BiosConfigPart->ProcessorEistEnable == 0 || BiosConfigPart->ProcessorEistEnable == 1)){
				SystemConfiguration.ProcessorEistEnable = BiosConfigPart->ProcessorEistEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
          }	  
        #endif
		//CDL002029 ++ <<
			
        //CDL002029 ++ >>
        #if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
		  if(((SystemConfiguration.TurboMode + BiosConfigPart->TurboMode)!=1) &&  
            (BiosConfigPart->TurboMode == 0 || BiosConfigPart->TurboMode == 1)){
            if(BiosConfigPart->TurboMode == 0){
              SystemConfiguration.TurboMode = 1;
			} else if (BiosConfigPart->TurboMode == 1){
                SystemConfiguration.TurboMode = 0;
			}
				
			*ResetType |= WITHOUT_POWER_CYCLE_RESET;
		  }
          #else
		  	if((SystemConfiguration.TurboMode != BiosConfigPart->TurboMode) && 
        			(BiosConfigPart->TurboMode == 0 || BiosConfigPart->TurboMode == 1)){
				SystemConfiguration.TurboMode = BiosConfigPart->TurboMode;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
		  #endif
		  //CDL002029 ++ <<
		  
        	if((SystemConfiguration.BootPState != BiosConfigPart->BootPState) && 
        			(BiosConfigPart->BootPState == 0 || BiosConfigPart->BootPState == 1)){
				SystemConfiguration.BootPState = BiosConfigPart->BootPState;
				*ResetType |= POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.ProcessorCcxEnable != BiosConfigPart->ProcessorCcxEnable) && 
        			(BiosConfigPart->ProcessorCcxEnable == 0 || BiosConfigPart->ProcessorCcxEnable == 1)){
				SystemConfiguration.ProcessorCcxEnable = BiosConfigPart->ProcessorCcxEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.PackageCState != BiosConfigPart->PackageCState) && 
        			(BiosConfigPart->PackageCState == 0 || BiosConfigPart->PackageCState == 1 || BiosConfigPart->PackageCState == 2 || 
        			BiosConfigPart->PackageCState == 3)){
				SystemConfiguration.PackageCState = BiosConfigPart->PackageCState;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.C3Enable != BiosConfigPart->C3Enable) && 
        			(BiosConfigPart->C3Enable == 0 || BiosConfigPart->C3Enable == 1)){
				SystemConfiguration.C3Enable = BiosConfigPart->C3Enable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.C6Enable != BiosConfigPart->C6Enable) && 
        			(BiosConfigPart->C6Enable == 0 || BiosConfigPart->C6Enable == 1)){
				SystemConfiguration.C6Enable = BiosConfigPart->C6Enable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.ProcessorC1eEnable != BiosConfigPart->ProcessorC1eEnable) && 
        			(BiosConfigPart->ProcessorC1eEnable == 0 || BiosConfigPart->ProcessorC1eEnable == 1)){
				SystemConfiguration.ProcessorC1eEnable = BiosConfigPart->ProcessorC1eEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.TStateEnable != BiosConfigPart->TStateEnable) && 
        			(BiosConfigPart->TStateEnable == 0 || BiosConfigPart->TStateEnable == 1)){
				SystemConfiguration.TStateEnable = BiosConfigPart->TStateEnable;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.AltEngPerfBIAS != BiosConfigPart->AltEngPerfBIAS) && 
        			(BiosConfigPart->AltEngPerfBIAS == 0 || BiosConfigPart->AltEngPerfBIAS == 0x7 || BiosConfigPart->AltEngPerfBIAS == 0x8 || 
        			BiosConfigPart->AltEngPerfBIAS == 0xf)){
				SystemConfiguration.AltEngPerfBIAS = BiosConfigPart->AltEngPerfBIAS; 
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.DdrFreqLimit != BiosConfigPart->DdrFreqLimit) && 
        			(BiosConfigPart->DdrFreqLimit == 0 || BiosConfigPart->DdrFreqLimit == 5 || BiosConfigPart->DdrFreqLimit == 7 || 
        			BiosConfigPart->DdrFreqLimit == 9 || BiosConfigPart->DdrFreqLimit == 11)){
				SystemConfiguration.DdrFreqLimit = BiosConfigPart->DdrFreqLimit;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.thermalthrottlingsupport != BiosConfigPart->thermalthrottlingsupport) && 
        			(BiosConfigPart->thermalthrottlingsupport == 0 || BiosConfigPart->thermalthrottlingsupport == 1 || BiosConfigPart->thermalthrottlingsupport == 2)){
				SystemConfiguration.thermalthrottlingsupport = BiosConfigPart->thermalthrottlingsupport;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.EarlySnoopEn != BiosConfigPart->EarlySnoopEn) && 
        			(BiosConfigPart->EarlySnoopEn == 0 || BiosConfigPart->EarlySnoopEn == 1 || BiosConfigPart->EarlySnoopEn == 2)){
				SystemConfiguration.EarlySnoopEn = BiosConfigPart->EarlySnoopEn;
				*ResetType |= POWER_CYCLE_RESET;
        	}
        	if((SystemConfiguration.ClusterOnDieEn != BiosConfigPart->ClusterOnDieEn) && 
        			(BiosConfigPart->ClusterOnDieEn == 0 || BiosConfigPart->ClusterOnDieEn == 1 || BiosConfigPart->ClusterOnDieEn == 2)){
				SystemConfiguration.ClusterOnDieEn = BiosConfigPart->ClusterOnDieEn;
				*ResetType |= POWER_CYCLE_RESET;
        	}
        	
        	//
          // Offset: 20h - 2fh
        	//
        	if((SystemConfiguration.NumaEn != BiosConfigPart->NumaEn) && 
        			(BiosConfigPart->NumaEn == 0 || BiosConfigPart->NumaEn == 1)){
				SystemConfiguration.NumaEn = BiosConfigPart->NumaEn;
				*ResetType |= POWER_CYCLE_RESET;
			}
        	if((SystemConfiguration.SocketInterleaveBelow4GB != BiosConfigPart->SocketInterleaveBelow4GB) && 
        			(BiosConfigPart->SocketInterleaveBelow4GB == 0 || BiosConfigPart->SocketInterleaveBelow4GB == 1)){
				SystemConfiguration.SocketInterleaveBelow4GB = BiosConfigPart->SocketInterleaveBelow4GB;
				*ResetType |= POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.ChannelInterleaving != BiosConfigPart->ChannelInterleaving) && 
					(BiosConfigPart->ChannelInterleaving == CH_INTER_AUTO || BiosConfigPart->ChannelInterleaving == CH_1WAY || BiosConfigPart->ChannelInterleaving == CH_2WAY || 
					BiosConfigPart->ChannelInterleaving == CH_3WAY || BiosConfigPart->ChannelInterleaving == CH_4WAY)){
				SystemConfiguration.ChannelInterleaving = BiosConfigPart->ChannelInterleaving;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.RankInterleaving != BiosConfigPart->RankInterleaving) && 
					(BiosConfigPart->RankInterleaving == RANK_INTER_AUTO || BiosConfigPart->RankInterleaving == RANK_1WAY || BiosConfigPart->RankInterleaving == RANK_2WAY || 
					BiosConfigPart->RankInterleaving == RANK_4WAY || BiosConfigPart->RankInterleaving == RANK_8WAY)){
				SystemConfiguration.RankInterleaving = BiosConfigPart->RankInterleaving;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.RASMode != BiosConfigPart->RASMode) && 
					(BiosConfigPart->RASMode == RAS_MODE_DISABLE || BiosConfigPart->RASMode == MIRROR_ENABLED || BiosConfigPart->RASMode == LOCKSTEP_ENABLED)){	
				SystemConfiguration.RASMode = BiosConfigPart->RASMode;
				*ResetType |= POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.enableSparing != BiosConfigPart->enableSparing) && 
					(BiosConfigPart->enableSparing == SPARING_DISABLED || BiosConfigPart->enableSparing == SPARING_ENABLED)){	
				SystemConfiguration.enableSparing = BiosConfigPart->enableSparing;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.PatrolScrub != BiosConfigPart->PatrolScrub) && 
					(BiosConfigPart->PatrolScrub == PATROL_SCRUB_DIS || BiosConfigPart->PatrolScrub == PATROL_SCRUB_EN)){	
				SystemConfiguration.PatrolScrub = BiosConfigPart->PatrolScrub;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.PatrolScrubDuration != BiosConfigPart->PatrolScrubDuration) && 
					(BiosConfigPart->PatrolScrubDuration >= 0) && (BiosConfigPart->PatrolScrubDuration <= 24)){
				SystemConfiguration.PatrolScrubDuration = BiosConfigPart->PatrolScrubDuration;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.DemandScrubMode != BiosConfigPart->DemandScrubMode) && 
					(BiosConfigPart->DemandScrubMode == 0 || BiosConfigPart->DemandScrubMode == 1)){	
				SystemConfiguration.DemandScrubMode = BiosConfigPart->DemandScrubMode;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.DeviceTaggingMode != BiosConfigPart->DeviceTaggingMode) &&
					(BiosConfigPart->DeviceTaggingMode == 0 || BiosConfigPart->DeviceTaggingMode == 1)){	
				SystemConfiguration.DeviceTaggingMode = BiosConfigPart->DeviceTaggingMode;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.VTdSupport != BiosConfigPart->VTdSupport) && 
					(BiosConfigPart->VTdSupport == 0 || BiosConfigPart->VTdSupport == 1)){
				SystemConfiguration.VTdSupport = BiosConfigPart->VTdSupport;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SetupData.PxeOpRom != BiosConfigPart->PxeOpRom) && 
					(BiosConfigPart->PxeOpRom == 0 || BiosConfigPart->PxeOpRom == 1 || BiosConfigPart->PxeOpRom == 2)){	
				SetupData.PxeOpRom = BiosConfigPart->PxeOpRom;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.ProcessorEistPsdFunc != BiosConfigPart->ProcessorEistPsdFunc) && 
					(BiosConfigPart->ProcessorEistPsdFunc == 0 || BiosConfigPart->ProcessorEistPsdFunc == 1 || BiosConfigPart->ProcessorEistPsdFunc == 2)){	
				SystemConfiguration.ProcessorEistPsdFunc = BiosConfigPart->ProcessorEistPsdFunc;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
            
			//CDL002029 ++ >>
			#if defined (Ali_1218_SUPPORT) && (Ali_1218_SUPPORT == 1) 
			  if((SetupData.ConsoleRedirectionEnable[1] != BiosConfigPart->SOLConsoleredirection) && 
				(BiosConfigPart->SOLConsoleredirection == 0 || BiosConfigPart->SOLConsoleredirection == 1)){	
				  SetupData.ConsoleRedirectionEnable[1] = BiosConfigPart->SOLConsoleredirection;
				  *ResetType |= WITHOUT_POWER_CYCLE_RESET;
			  }

			  // ME NM Boot Mode
			  if((SystemConfiguration.NmPwrOptBoot != BiosConfigPart->BootMode) && 
			    (BiosConfigPart->BootMode == 0 || BiosConfigPart->BootMode == 1)){	
				 SystemConfiguration.NmPwrOptBoot = BiosConfigPart->BootMode;
				 *ResetType |= WITHOUT_POWER_CYCLE_RESET;
			} 
			#endif
			//CDL002029 ++ <<


			//
            // Offset: 30h - 35h
			//
			if((SetupData.SriovSupport != BiosConfigPart->SriovSupport) && 
					(BiosConfigPart->SriovSupport == 0 || BiosConfigPart->SriovSupport == 1)){
				SetupData.SriovSupport = BiosConfigPart->SriovSupport;                          //SETUP_DATA.SriovSupport
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
			}
			if((SystemConfiguration.spareErrTh != BiosConfigPart->spareErrTh) && 
					(BiosConfigPart->spareErrTh >= 0) && (BiosConfigPart->spareErrTh <= 0x7FFF)){
				SystemConfiguration.spareErrTh = BiosConfigPart->spareErrTh;
				*ResetType |= WITHOUT_POWER_CYCLE_RESET;
            }
           
        }
    }


	VarSize = sizeof(SYSTEM_CONFIGURATION);
    Status = gRT->SetVariable (
                    L"IntelSetup",
                    &gEfiSetupVariableGuid,
                    VarAttribute1,
                    VarSize,
                    &SystemConfiguration );

    VarSize = sizeof (SETUP_DATA);
    Status = gRT->SetVariable (
                    L"Setup",
                    &gSetupGuid,
                    VarAttribute2,
                    VarSize,
                    &SetupData );
    
}


//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReportBiosConfigToBmc
//
// Description: Report the requested BIOS config to BMC
//
// Input:       EFI_EVENT	Event
//				VOID		*Context
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
VOID
ReportBiosConfigToBmc(
	IN EFI_EVENT        Event,
	IN VOID             *Context 
)
{
    EFI_STATUS                      Status;
	EFI_IPMI_TRANSPORT      	    *IpmiTransport = NULL;
	UINT8 					        ResponseData;
	UINT8 					        ResponseDataSize = 1;
	REPORT_BIOS_CONFIG				*ReportBiosConfig = NULL;
	
    Status = gBS->LocateProtocol (
                &gEfiDxeIpmiTransportProtocolGuid,
                NULL,
                (VOID **)&IpmiTransport
             	);
    
    if(!EFI_ERROR(Status)) {
    
    	ReportBiosConfig = (REPORT_BIOS_CONFIG *)AllocateZeroPool (sizeof(REPORT_BIOS_CONFIG));
    	
    	ReportBiosConfig->Offset = 0;
    	GetCurrentConfigFromBios(&ReportBiosConfig->BiosConfigPart);

		Status = IpmiTransport->SendIpmiCommand (
						IpmiTransport,
						0x3E,
						BMC_LUN,
						0x20,
						(UINT8 *)ReportBiosConfig,
						sizeof(REPORT_BIOS_CONFIG),
						&ResponseData,
						&ResponseDataSize );
		gBS->FreePool(ReportBiosConfig);
		ReportBiosConfig = NULL;

    }

}



//<OEM_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ModifyBiosConfig
//
// Description: Modify BIOS config according to BMC requested.
//
// Input:       EFI_HANDLE           ImageHandle,
//				EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      None
//
// Notes:       OEM FUNCTION REQUIRED
//----------------------------------------------------------------------------
//<OEM_PHDR_END>
EFI_STATUS
EFIAPI
ModifyBiosConfig(
		  IN EFI_HANDLE           ImageHandle,
		  IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS                      Status;
	EFI_IPMI_TRANSPORT      	    *IpmiTransport=NULL;
	EFI_GUID                        guidSetupEnter = AMITSE_SETUP_ENTER_GUID;
//TH0143A	BIOS_CONFIG_PART				*EmptyConfig = NULL;
	UINT8 					        ResponseDataSize;
	UINT8							RequestData[3];
	GET_BIOS_CONFIG					*GetBiosConfig = NULL;
	UINT8                           ResetType = 0;
	EFI_EVENT                       ReportConfigEvent = NULL;
	UINT8							NMI_EN;	//TH0153
	
//TH0143B>>>	
	EFI_GUID						mPreviousSetupBiosConfgGuid = PREVIOUS_SETUP_BIOS_CONFIG_GUID;
	BIOS_CONFIG_PART	            CurrentBiosConfig;
	BIOS_CONFIG_PART	            PreviousBiosConfig;
	UINTN                           VarSize;
	
	//get current BIOS configuration
	GetCurrentConfigFromBios(&CurrentBiosConfig);
	
	//get previous BIOS configuration
    VarSize = sizeof(BIOS_CONFIG_PART);
	Status = gRT->GetVariable (
					L"PreviousSetupBiosConfg",
					&mPreviousSetupBiosConfgGuid,
					NULL,
					&VarSize,
					&PreviousBiosConfig
					);
	
	if( MemCmp(&PreviousBiosConfig, &CurrentBiosConfig, sizeof(BIOS_CONFIG_PART)) ){
		//Update 'PreviousBiosConfig' if current BIOS configuration differ from previous. 
		Status = gRT->SetVariable (
						L"PreviousSetupBiosConfg",
						&mPreviousSetupBiosConfgGuid,
						EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
						VarSize,
						&CurrentBiosConfig );

	}else{
//TH0143B<<<

		Status = gBS->LocateProtocol (
					&gEfiDxeIpmiTransportProtocolGuid,
					NULL,
					(VOID **)&IpmiTransport 
					);
		
		if(!EFI_ERROR(Status)) {
			//
			// Get config Value from BMC
			//
			RequestData[0] = 0x00;
			RequestData[1] = 0x00;
			RequestData[2] = sizeof(BIOS_CONFIG_PART);
			GetBiosConfig = (GET_BIOS_CONFIG *)AllocateZeroPool (sizeof(GET_BIOS_CONFIG));
			ResponseDataSize = sizeof(GET_BIOS_CONFIG);
			Status = IpmiTransport->SendIpmiCommand (
							IpmiTransport,
							0x3E,
							BMC_LUN,
							0x21,
							RequestData,
							sizeof(RequestData),
							(UINT8 *)GetBiosConfig,
							&ResponseDataSize );
	
			if(!EFI_ERROR(Status)){
/*TH0143A>>>
 *			1. The BIOS configuration is stored in a BMC system file which created by 'write BIOS configuration to BMC' cmd.
 *			2. The file will be deleted when refresh BMC FW or by 'Clear BIOS configuration in BMC' cmd.
 *			3. If the file does not exist, SendIpmiCommand() will return '0x07' when send 'Read BIOS configuration from BMC' cmd.
 *
TH0143A<<<*/
//TH0143A				EmptyConfig = (BIOS_CONFIG_PART *)AllocateZeroPool (sizeof(BIOS_CONFIG_PART));
//TH0143A				if( MemCmp(&GetBiosConfig->BiosConfigPart, EmptyConfig, sizeof(BIOS_CONFIG_PART)) ){

				if( MemCmp(&GetBiosConfig->BiosConfigPart, &CurrentBiosConfig, sizeof(BIOS_CONFIG_PART)) ){ //TH0143A
				
					ValidateAndSetBiosConfig(&GetBiosConfig->BiosConfigPart, &ResetType);
//TH0153>>>			
					NMI_EN = IoRead8(0x70) & 0x80;	//Bit 7 is the NMI bit -- it should be protected.
					IoWrite8(0x70, NUMA_CMOS_INDEX | NMI_EN);
					IoWrite8(0x71, GetBiosConfig->BiosConfigPart.NumaEn);
//TH0153<<<
					if(ResetType & POWER_CYCLE_RESET){
//TH0143A							gBS->Stall(100000);
						IoWrite8(0xCF9,0x0E);
					}
					if(ResetType & WITHOUT_POWER_CYCLE_RESET){
//TH0143A							gBS->Stall(100000);
						IoWrite8(0xCF9,0x06);
					}
					
				}
				
//TH0143A				FreePool(EmptyConfig);
			}
			FreePool(GetBiosConfig);
			GetBiosConfig = NULL;
		}

	}//TH0143B
    //************************************************************************************************
    //Register Event to report BIOS config to BMC before entering to setup or save&exit setup or boot.
    //************************************************************************************************
    
	//
	//1.Register Event for Setup enter guid to report BIOS config to BMC before entering to setup.
	//
	EfiNamedEventListen (
		&guidSetupEnter,
		TPL_CALLBACK,
		ReportBiosConfigToBmc,
		NULL,
		NULL);

	//
	//2.Register Event for Setup enter guid to report BIOS config to BMC after Save & Exit Setup menu.
	//
	EfiNamedEventListen (
		&gAmiTseNVRAMUpdateGuid,
		TPL_CALLBACK,
		ReportBiosConfigToBmc,
		NULL,
		NULL );

	//
	//3.Register Event for Setup enter guid to report BIOS config to BMC before boot.
	//    

	//
	// Register events to report BIOS config to BMC just before legacy Boot.
	//
	// In PiSmmIpl driver, there is a callback function registered for LegacybootEvent which denies access to all the
	// UEFI services in SMM after Legacy boot event is triggered. This callback function is getting control before our ReportBiosConfigToBmc().
	// Because of this Callback in PiSmmIpl driver, SmmCommunicate is not working after legacy boot event.
	// Changing the TPL_CALLBACK task priority level to TPL_NOTIFY to get the control before PismmIPl driver's callback gets control.
	EfiCreateEventLegacyBootEx (
		TPL_NOTIFY,
		//TPL_CALLBACK,
		ReportBiosConfigToBmc,
		NULL,
		&ReportConfigEvent );
	
	//
	// Register event for AMITSE_EVENT_BEFORE_BOOT_GUID to report BIOS config to BMC before Uefi boot.
	//
	EfiNamedEventListen (
		&gAmiTseEventBeforeBootGuid,
		TPL_CALLBACK,
		ReportBiosConfigToBmc,
		NULL,
		NULL );
            
    //************************************************************************************************
    //End of register Event.
    //************************************************************************************************
	
	return EFI_SUCCESS;
}



