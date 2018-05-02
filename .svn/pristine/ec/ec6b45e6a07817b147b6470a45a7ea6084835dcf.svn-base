#pragma warning(disable: 4001)
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

/** @file UsbPoint.c
    AMI USB Absolute Device support implementation

**/

#include "AmiDef.h"
#include "UsbDef.h"
#include "AmiUsb.h"
#include "UsbKbd.h"
#include <Protocol/AbsPointerProtocol.h>

extern  USB_GLOBAL_DATA     *gUsbData;

static BOOLEAN globalAbsolutePolling = TRUE;

UINT8       USBAbsProcessMouseData (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID		SetABSData (UINT8*,UINT16*,UINT8,UINT8,UINT16);			 
UINT16      PerviousXPosition = 0;
UINT16      PerviousYPosition = 0;

/**
    This routine checks an interface descriptor of the USB device
    detected to see if it describes a HID/Boot/Mouse device.
    If the device matches the above criteria, then the device is
    configured and initialized

    @param HcStruc   HCStruc pointer
        DevInfo   Device information structure pointer
        Desc      Pointer to the descriptor structure
        Start     Offset within interface descriptor
        supported by the device
        End       End offset of the device descriptor

    @retval FPDEV_INFO  New device info structure, 0 on error

**/

DEV_INFO*
USBAbsConfigureDevice (
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Desc,
    UINT16      Start,
    UINT16      End
)
{
    return NULL;
}

/**

    @param HcStruc   Pointer to HCStruc
        DevInfo   Pointer to device information structure
        Td        Pointer to the polling TD
        Buffer    Pointer to the data buffer

    @retval Nothing

**/

UINT8
USBAbsProcessMouseData (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Td,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
	USBABS_DATA	        AbsBuffer;
	HID_REPORT_FIELD	*Field = NULL;
	UINT8 	            OffsetTmp = 0;
    UINT8               XStart = 0;
    UINT8               XEnd;
    UINT8               YStart = 0;
    UINT8               YEnd;
    UINT8               ButtonStart = 0;
    UINT8               ButtonEnd = 0;
    UINT8               i;
    UINT16              j;
	UINT16 	            MaxX;
    UINT16              MaxY;
    BOOLEAN             SetButtonData = FALSE;
    BOOLEAN             SetXData = FALSE;
    BOOLEAN             SetYData = FALSE;

    AbsBuffer.X =0;
    AbsBuffer.Y =0;
    AbsBuffer.Button =0;
    
	for (i = 0; i < DevInfo->HidReport.FieldCount; i++) {
		Field = DevInfo->HidReport.Fields[i];

		//Check is input?
		if (!(Field->Flag & HID_REPORT_FIELD_FLAG_INPUT)) {
			continue;
		}

		// Check if report id is matched
		if (Field->ReportId != 0 && Field->ReportId != Buffer[0]) {
			continue;
		}

		if ((Field->UsagePage == 0xd) && (Field->UsageCount) != 0) {
			for (j = 0; j < Field->UsageCount; j++) {
				//Check Tip switch
				if (Field->Usages[j] == 0x42) {					//(EIP79323)
                    if (SetButtonData == TRUE) {
                        break;
                    }
					ButtonStart = OffsetTmp;
					if (Field->ReportId != 0) {
						ButtonStart += 8; 
					}
                    ButtonEnd = ButtonStart + (Field->ReportSize * Field->ReportCount);		//(EIP101990)
                    SetABSData(Buffer, (UINT16*)(&AbsBuffer.Button), ButtonStart, ButtonEnd, 0xffff);        				//(EIP101990) 
                    SetButtonData = TRUE;
				}
			}
		}

		//Check Button
		if ((Field->UsagePage == 9) && (Field->Usages[0] == 1)) {	//(EIP114280)
            if (SetButtonData == TRUE) {
                break;
            }
			ButtonStart = OffsetTmp;
			if (Field->ReportId != 0) {
				ButtonStart += 8;
			}
            ButtonEnd = ButtonStart + Field->ReportSize * Field->ReportCount;		//(EIP101018)
            SetABSData(Buffer, (UINT16*)(&AbsBuffer.Button), ButtonStart, ButtonEnd, 0xffff);        				//(EIP101018)
            SetButtonData = TRUE;
		}

		//Check X,Y
		if ((Field->UsagePage == 1) && (Field->UsageCount) != 0) {
			for (j = 0; j < Field->UsageCount; j++) {
				//find X
				if (Field->Usages[j] == 0x30) {
                    if (SetXData == TRUE) {
                        break;
                    }
					XStart = OffsetTmp + (j * Field->ReportSize);
					if (Field->ReportId != 0) {
						XStart += 8;
					}
					XEnd = XStart + Field->ReportSize;
					SetABSData(Buffer, &AbsBuffer.X, XStart, XEnd, Field->LogicalMax);        //(EIP81983)
                    SetXData = TRUE;
					MaxX = Field->LogicalMax;
				}

				//find Y
				if (Field->Usages[j] == 0x31) {
                    if (SetYData == TRUE) {
                        break;
                    }
					YStart = OffsetTmp + (j * Field->ReportSize);
					if (Field->ReportId != 0) {
						YStart += 8;
					}
					YEnd = YStart + Field->ReportSize;
					MaxY = Field->LogicalMax; 
					SetABSData(Buffer, &AbsBuffer.Y, YStart, YEnd, Field->LogicalMax);        //(EIP81983)
                    SetYData = TRUE;
				}
			}
		}
		OffsetTmp += Field->ReportCount * Field->ReportSize;
	}
	
    if (AbsBuffer.Button == 0 && AbsBuffer.X == 0 && AbsBuffer.Y == 0) {
        return USB_SUCCESS;
    }
    
    if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {
        gUsbData->AbsMouseData[0].ButtonStauts = AbsBuffer.Button;
        //In UEFI spec, the definitions of bits within ActiveButtons are EFI_ABSP_TouchActive
        // and EFI_ABS_AltActive, we don't support AltActive, clear the unnecessary bits.
        gUsbData->AbsMouseData[0].ButtonStauts &= EFI_ABSP_TouchActive;
        gUsbData->AbsMouseData[0].Xcoordinate = AbsBuffer.X;
        gUsbData->AbsMouseData[0].Ycoordinate = AbsBuffer.Y;
        gUsbData->AbsMouseData[0].Pressure = 0;
		gUsbData->AbsMouseData[0].Max_X = MaxX;
		gUsbData->AbsMouseData[0].Max_Y = MaxY;
    }
    return USB_SUCCESS;
}

/**

**/

VOID
SetABSData (
    UINT8       *Buffer,
    UINT16 		*ReportData,
    UINT8 		Start,
    UINT8 		End,
    UINT16 		Maxvalue
)
{
	UINT8 	ReportSize;
    UINT8   Size;
    UINT8   PreSkip;
    UINT8   PostSkip;
	UINT32  TempData = 0;
    
	ReportSize = End - Start;
	Size = ReportSize / 8;
    
	if ((ReportSize % 8) !=0) {
        Size++;
    }

	ASSERT(Size > 0 && Size <= sizeof(TempData));
    if ((Size == 0) || (Size > sizeof(TempData))) {
        return;
    }
    
	MemCpy(&TempData, Buffer + Start / 8, Size);
    
	PreSkip = Start % 8;
	PostSkip = End % 8;

	if (PreSkip != 0) {
		TempData = TempData >> PreSkip;
	}
    
	if (PostSkip != 0) {
		TempData = TempData << PostSkip;
		TempData = TempData >> PostSkip;
	}
    
	if (TempData > Maxvalue) {
		TempData &= Maxvalue;
	}
    
	*ReportData = (UINT16)TempData;
	USB_DEBUG (DEBUG_LEVEL_4, "out data %x\n",*ReportData);
    
	return;
}

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
