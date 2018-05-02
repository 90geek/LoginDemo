#include <Build\GRANTLEY\RELEASE_MYTOOLS\X64\Build\Setup\DEBUG\SetupStrDefs.h>

//--------------------------------------------------------------------------- 
// Constant and Variables declarations 
//--------------------------------------------------------------------------- 
typedef enum { 
//    BoTagLegacyXxx 
//    BoTagUefiXxx 
//    BoTagXxx 
//--standard device type don't modify--// 
    BoTagLegacyFloppy = 1,	//1 
    BoTagLegacyHardDisk,	//2 
    BoTagLegacyCdrom,		//3 
    BoTagLegacyPcmcia,		//4 
    BoTagLegacyUsb,		    //5 
    BoTagLegacyEmbedNetwork,	//6 
    BoTagLegacyBevDevice = 0x80,//7 
//--standard device type don't modify--// end 
    BoTagLegacyUSBFloppy = 8, 
    BoTagLegacyUSBHardDisk, 
    BoTagLegacyUSBCdrom, 
    BoTagLegacyUSBKey, 
    BoTagLegacyUSBLan, 
    BoTagLegacyHardDisk1, 
    BoTagLegacyHardDisk2, 
    BoTagLegacyHardDisk3, 
    BoTagLegacyHardDisk4, 
    BoTagLegacyHardDisk5, 
    BoTagUefiUsbFloppy,				//(EIP96232+) 
    BoTagUefiHardDisk, 
    BoTagUefiHardDisk1, 
    BoTagUefiHardDisk2, 
    BoTagUefiHardDisk3, 
    BoTagUefiHardDisk4, 
    BoTagUefiHardDisk5, 
    BoTagUefiCdrom, 
    BoTagUefiUsbHardDisk, 
    BoTagUefiUsbKey, 
    BoTagUefiUsbLan, 
    BoTagUefiUsb, 
#if SHELL_GROUP_SUPPORT 
    BoTagUefiApplication,			//(EIP115686+) 
#endif 
    BoTagUefiUsbCdrom, 
    BoTagUefiNetWork, 
    BoTagUefi, 
    BoTagEmbeddedShell 
} FIXED_BOOT_OPTION_TAG; 
#define FBO_CHANGE_DEVICE_NAME_FUNCS 
#define FBO_UEFI_DEVICE UEFI_HDD  UEFI_NETWORK  UEFI_USBODD  UEFI_USBHDD  UEFI_ODD  UEFI_APPLICATION 
#define FBO_LEGACY_DEVICE HDD  NETWORK  USBODD  USBHDD  ODD 
#define FBO_DUAL_DEVICE UEFI_HDD  UEFI_ODD  UEFI_USBODD  UEFI_USBHDD  UEFI_NETWORK  UEFI_APPLICATION  HDD  ODD  USBHDD  USBODD  NETWORK 

