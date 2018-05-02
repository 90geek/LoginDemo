//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file UsbHid.c
    USB HID class device driver

**/

#include "AmiDef.h"
#include "UsbDef.h"
#include "AmiUsb.h"
#include "UsbKbd.h"
extern USB_GLOBAL_DATA *gUsbData; 

UINT8	UsbControlTransfer(HC_STRUC*, DEV_INFO*, DEV_REQ, UINT16, VOID*);

VOID        USBHIDInitialize (VOID);
UINT8       USBHIDCheckForDevice (DEV_INFO*, UINT8, UINT8, UINT8);
DEV_INFO*   USBHIDConfigureDevice (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT16);
UINT8   	USBHIDProcessData ( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8       USBHIDDisconnectDevice (DEV_INFO*);

UINT8		HidGetReportDescriptor(HC_STRUC*, DEV_INFO*, HID_DESC*);  

VOID        USBMSInitialize (VOID);
DEV_INFO*   USBMSConfigureDevice (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT16); 
DEV_INFO*   USBKBDConfigureDevice (DEV_INFO*);  //(EIP84455)
DEV_INFO*   USBAbsConfigureDevice (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT16);  
VOID        CheckInputMode(DEV_INFO *DevInfo, HID_REPORT_FIELD * Field);    //(EIP101990)

VOID
USBHIDFillDriverEntries (DEV_DRIVER *fpDevDriver)
{
    fpDevDriver->bDevType               = BIOS_DEV_TYPE_HID;
    fpDevDriver->bBaseClass             = BASE_CLASS_HID;
    fpDevDriver->bSubClass              = 0;
    fpDevDriver->bProtocol              = 0;
    fpDevDriver->pfnDeviceInit          = USBHIDInitialize;
    fpDevDriver->pfnCheckDeviceType     = USBHIDCheckForDevice;
    fpDevDriver->pfnConfigureDevice     = USBHIDConfigureDevice;
    fpDevDriver->pfnDisconnectDevice    = USBHIDDisconnectDevice;
    return;
}

/**
    This function returns fills the host controller driver
    routine pointers in the structure provided

    @param VOID

    @retval VOID

**/

VOID
USBHIDInitialize (VOID)
{
	USBKBDInitialize();
	USBMSInitialize();

    return;
}

/**
    This routine checks for mouse type device from the
    interface data provided

    @param bBaseClass  USB base class code
        bSubClass   USB sub-class code
        bProtocol   USB protocol code

    @retval BIOS_DEV_TYPE_MOUSE type on success or 0FFH on error

**/

UINT8
USBHIDCheckForDevice (
    DEV_INFO* fpDevInfo,
    UINT8 bBaseClass,
    UINT8 bSubClass,
    UINT8 bProtocol
)
{
	//
	// Check the BaseClass, SubClass and Protocol for a HID/Boot/Mouse device.
	//
	if (bBaseClass != BASE_CLASS_HID) {
		return USB_ERROR;
	}

    if ((BOOT_PROTOCOL_SUPPORT != 0) || 
        (fpDevInfo->wIncompatFlags & USB_INCMPT_HID_BOOT_PROTOCOL_ONLY)) {
        if (bSubClass != SUB_CLASS_BOOT_DEVICE) {
            return USB_ERROR;
        }
    
        if (bProtocol != PROTOCOL_KEYBOARD &&
            bProtocol != PROTOCOL_MOUSE) {
            return USB_ERROR;
        }
    }

	return	BIOS_DEV_TYPE_HID;
}

/**
    This routine checks an interface descriptor of the USB device
    detected to see if it describes a HID/Boot/Keyboard device.
    If the device matches the above criteria, then the device is
    configured and initialized

    @param fpHCStruc   HCStruc pointer
        fpDevInfo   Device information structure pointer
        fpDesc      Pointer to the descriptor structure
        wStart      Offset within interface descriptor
        supported by the device
        wEnd        End offset of the device descriptor

    @retval FPDEV_INFO  New device info structure, 0 on error

**/
                                        //(EIP84455+)>
DEV_INFO*
USBHIDConfigureDevice (
    HC_STRUC*   fpHCStruc,
    DEV_INFO*   fpDevInfo,
    UINT8*      fpDesc,
    UINT16      wStart,
    UINT16      wEnd)
{
    ENDP_DESC       *fpEndpDesc;
    INTRF_DESC      *fpIntrfDesc;
	UINT8			*DescEnd;
	HID_DESC		*HidDesc = NULL;
	DEV_REQ			Request = {0};
    
	fpDevInfo->bDeviceType = (UINT8)BIOS_DEV_TYPE_HID;
	fpDevInfo->HidDevType = 0;

	MemSet(&fpDevInfo->HidReport, sizeof(fpDevInfo->HidReport), 0);

	USB_DEBUG(3, "USBHIDConfigureDevice...  \n");

    fpDevInfo->bCallBackIndex = USB_InstallCallBackFunction(USBHIDProcessData);

    fpIntrfDesc = (INTRF_DESC*)(fpDesc + wStart);
    DescEnd = fpDesc + ((CNFG_DESC*)fpDesc)->wTotalLength; // Calculate the end of descriptor block
    fpEndpDesc = (ENDP_DESC*)((char*)fpIntrfDesc + fpIntrfDesc->bDescLength);

    //Select correct endpoint
    for (;(fpEndpDesc->bDescType != DESC_TYPE_INTERFACE) && ((UINT8*)fpEndpDesc < DescEnd);
        fpEndpDesc = (ENDP_DESC*)((UINT8 *)fpEndpDesc + fpEndpDesc->bDescLength)){
        if(!(fpEndpDesc->bDescLength)) {
            break;  // Br if 0 length desc (should never happen, but...)
        }

		if (fpEndpDesc->bDescType == DESC_TYPE_HID ) {
			HidDesc = (HID_DESC*)fpEndpDesc;
			continue;
		}

        if (fpEndpDesc->bDescType != DESC_TYPE_ENDPOINT ) {
            continue;
        }

        //
        // Check for and configure Interrupt endpoint if present
        //
        if ((fpEndpDesc->bEndpointFlags & EP_DESC_FLAG_TYPE_BITS) !=
                EP_DESC_FLAG_TYPE_INT) {    // Bit 1-0: 10 = Endpoint does interrupt transfers
			continue;
        }

		if (fpEndpDesc->bEndpointAddr & EP_DESC_ADDR_DIR_BIT ) {
            fpDevInfo->bIntEndpoint = fpEndpDesc->bEndpointAddr;
            fpDevInfo->wIntMaxPkt = fpEndpDesc->wMaxPacketSize;
            fpDevInfo->bPollInterval = fpEndpDesc->bPollInterval;  
			break;
        }
    }

    if (fpDevInfo->bIntEndpoint == 0) {
        return 0;
    }

	//Set protocol (Option)
	if ((BOOT_PROTOCOL_SUPPORT != 0) &&
		!(fpDevInfo->wIncompatFlags & USB_INCMPT_SET_BOOT_PROTOCOL_NOT_SUPPORTED) ||
		(fpDevInfo->wIncompatFlags & USB_INCMPT_HID_BOOT_PROTOCOL_ONLY)) {
		//
		// Send the set protocol command, wValue = 0 (Boot protocol)
		//
		Request.wRequestType = HID_RQ_SET_PROTOCOL;
		Request.wValue = 0;		// 0: Boot Protocol
		Request.wIndex = fpDevInfo->bInterfaceNum;
		Request.wDataLength = 0;
		
		UsbControlTransfer(fpHCStruc, fpDevInfo, Request, 100, NULL);
	} 

	//Send Set_Idle command 
	Request.wRequestType = HID_RQ_SET_IDLE;
	Request.wValue = 0;
	Request.wIndex = fpDevInfo->bInterfaceNum;
	Request.wDataLength = 0;
	
	UsbControlTransfer(fpHCStruc, fpDevInfo, Request, 100, NULL);

	if ((BOOT_PROTOCOL_SUPPORT == 0) && 
        !(fpDevInfo->wIncompatFlags & USB_INCMPT_HID_BOOT_PROTOCOL_ONLY)) {
		HidGetReportDescriptor(fpHCStruc, fpDevInfo, HidDesc);
		fpDevInfo->HidReport.Flag |= HID_REPORT_FLAG_REPORT_PROTOCOL;
        if (fpDevInfo->PollingLength < fpDevInfo->wIntMaxPkt) {
            fpDevInfo->PollingLength = fpDevInfo->wIntMaxPkt;
        }
	} else {
		fpDevInfo->PollingLength = fpDevInfo->wIntMaxPkt;
		switch (fpDevInfo->bProtocol) {
			case PROTOCOL_KEYBOARD:
				fpDevInfo->HidDevType = HID_DEV_TYPE_KEYBOARD;
				break;

			case PROTOCOL_MOUSE:
				fpDevInfo->HidDevType = HID_DEV_TYPE_MOUSE;
				break;

			default:
				break;
		}
	}

    if (fpDevInfo->HidDevType & HID_DEV_TYPE_KEYBOARD) { 
        if (!(USBKBDConfigureDevice(fpDevInfo))) {
            return 0;
        }
    }

//Active polling
    if ((fpDevInfo->PollingLength != 0) && (fpDevInfo->bPollInterval != 0)) {
		if (!((fpDevInfo->HidDevType & HID_DEV_TYPE_MOUSE) && (gUsbData->dUSBStateFlag & USB_FLAG_EFIMS_DIRECT_ACCESS))) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDActivatePolling)(fpHCStruc,fpDevInfo);
        }
    }


    return fpDevInfo;
} 
                                        //<(EIP84455+)
/**
    This routine disconnects the keyboard by freeing
    the USB keyboard device table entry

    @param fpDevInfo   Pointer to DeviceInfo structure

    @retval USB_SUCCESS/USB_ERROR

**/

UINT8
USBHIDDisconnectDevice (
	DEV_INFO	*DevInfo
)
{
	HC_STRUC	*HcStruc = gUsbData->HcTable[DevInfo->bHCNumber - 1];
	UINT16		Index;

	// Stop polling the endpoint
	(*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDDeactivatePolling)(HcStruc, DevInfo);
	DevInfo->bIntEndpoint = 0;

    if (DevInfo->HidDevType & HID_DEV_TYPE_KEYBOARD) {
        USBKBDDisconnectDevice(DevInfo);
    }

    if (DevInfo->HidReport.Fields != NULL) {
		for (Index = 0; Index < DevInfo->HidReport.FieldCount; Index++) {
			if (DevInfo->HidReport.Fields[Index]->Usages != NULL) {
				USB_MemFree(DevInfo->HidReport.Fields[Index]->Usages, 
					GET_MEM_BLK_COUNT(DevInfo->HidReport.Fields[Index]->UsageCount * sizeof(UINT16)));
				DevInfo->HidReport.Fields[Index]->Usages = NULL;
			}
			USB_MemFree(DevInfo->HidReport.Fields[Index], GET_MEM_BLK_COUNT(sizeof(HID_REPORT_FIELD)));
			DevInfo->HidReport.Fields[Index] = NULL;
		}

		USB_MemFree(DevInfo->HidReport.Fields, GET_MEM_BLK_COUNT(DevInfo->HidReport.FieldCount * sizeof(HID_REPORT_FIELD*)));
        DevInfo->HidReport.Fields = NULL;
        DevInfo->HidReport.ReportDescLen = 0;
    }

	return USB_SUCCESS; 	
} 

/**
    @param ExtractInputReportData


 intput:      

    @retval 

**/

UINT32
ExtractInputReportData (
	UINT8	*Report,
	UINT16	Offset,
	UINT16	Size
)
{
	UINT32	*Start;
	UINT8	BitOffset;
	UINT32	Data = 0;

	ASSERT(Data <= 32);
	Start = (UINT32*)((UINTN)Report + (Offset >> 3));
	BitOffset = Offset & 0x7;
	Data = (*Start >> BitOffset) & ((0x1 << Size) - 1);
	return Data;
}

/**
    @param GetItemData

    This funtion copy data of the item to buffer.

 intput:      

    @retval 

**/

VOID
GetItemData (
	HID_ITEM	*Item,
	VOID		*Buffer,
	UINT32		BufferSize
)
{
	UINT32	Size = Item->bSize > BufferSize ? BufferSize : Item->bSize;
	MemSet(Buffer, BufferSize, 0);
	MemCpy(Buffer, &Item->data, Size);
}

/**
    @param AddUsage

    This funtion adds usage into usage table.

 intput:      

    @retval 

**/

VOID
AddUsage (
	HID_REPORT_FIELD	*Field,
	UINT16				Usage
)
{
	if (Field->UsageCount >= Field->MaxUsages) {
		return;
	}

	Field->Usages[Field->UsageCount++] = Usage;
}

/**
    @param Add_Hid_Field

    Add input or output item.

 intput:      

    @retval 

**/
                                        //(EIP84455+)>
VOID
AddField (
	HID_REPORT			*Report,
	HID_REPORT_FIELD	*Field
)
{
	HID_REPORT_FIELD	*NewField;
	HID_REPORT_FIELD	**Fields;
	UINT16				Index;

	NewField = USB_MemAlloc(GET_MEM_BLK_COUNT(sizeof(HID_REPORT_FIELD)));
	ASSERT(NewField != NULL);
	if (NewField == NULL) {
		return;
	}

	if (Field->ReportId != 0) {
		Report->Flag |= HID_REPORT_FLAG_REPORT_ID;
	}

	MemCpy(NewField, Field, sizeof(HID_REPORT_FIELD));
	NewField->Usages = NULL;

	USB_DEBUG(4, "============================================== \n");
	USB_DEBUG(4, "Field index = %02x, \t", Report->FieldCount);
	USB_DEBUG(4, "Flag = %02x\n", NewField->Flag);
	USB_DEBUG(4, "UsagePage = %4x, \t", NewField->UsagePage);
	USB_DEBUG(4, "ReportId = %02x\n", NewField->ReportId);
	USB_DEBUG(4, "ReportCount = %02x, \t", NewField->ReportCount);
	USB_DEBUG(4, "bReportSize = %02x\n", NewField->ReportSize);
	USB_DEBUG(4, "LogicalMin = %4x, \t", NewField->LogicalMin);
	USB_DEBUG(4, "LogicalMax = %4x\n", NewField->LogicalMax);
	USB_DEBUG(4, "PhysicalMax = %4x, \t", NewField->PhysicalMax);
	USB_DEBUG(4, "PhysicalMin = %4x\n", NewField->PhysicalMin);
	USB_DEBUG(4, "UnitExponent = %2x, \t", NewField->UnitExponent);
	USB_DEBUG(4, "UsageCount = %4x\n", NewField->UsageCount);

	if (NewField->UsageCount != 0) {
		NewField->Usages = USB_MemAlloc (GET_MEM_BLK_COUNT(NewField->UsageCount * sizeof(UINT16)));
		ASSERT(NewField->Usages != NULL);
		if (NewField->Usages == NULL) {
			return;
		}

		MemCpy(NewField->Usages, Field->Usages, NewField->UsageCount * sizeof(UINT16));

		USB_DEBUG(4, "Usages:\n");
		for (Index = 0; Index < NewField->UsageCount; Index++) {
			if ((NewField->UsagePage == 0x01) && (NewField->Usages[Index] == 0x30)) {
				if (NewField->Flag & HID_REPORT_FIELD_FLAG_RELATIVE) {
					Report->Flag |= HID_REPORT_FLAG_RELATIVE_DATA;
				} else {
					Report->Flag |= HID_REPORT_FLAG_ABSOLUTE_DATA;
				}
				Report->AbsMaxX = NewField->LogicalMax;
			}
			if (NewField->Usages[Index] == 0x31) {
				Report->AbsMaxY= NewField->LogicalMax;
			}
			USB_DEBUG(4, "%02X ", NewField->Usages[Index]); 	
			if ((Index & 0xF) == 0xF) {
				USB_DEBUG(4, "\n"); 
			}
		}
	}
	USB_DEBUG(4, "\n============================================== \n");

	Fields = USB_MemAlloc(GET_MEM_BLK_COUNT((Report->FieldCount + 1) * sizeof(HID_REPORT_FIELD*)));
	ASSERT(Fields != NULL);
	if (Fields == NULL) {
		return;
	}

	if (Report->Fields != NULL) {
		MemCpy(Fields, Report->Fields, Report->FieldCount * sizeof(HID_REPORT_FIELD*));
		USB_MemFree(Report->Fields, GET_MEM_BLK_COUNT(Report->FieldCount * sizeof(HID_REPORT_FIELD*)));
	}

	Report->Fields = Fields;
	Report->Fields[Report->FieldCount++] = NewField;

	return;
}
                                        //<(EIP84455+)

/**
    @param HidParserMain


 intput:      

    @retval 

**/

UINT8
HidParserMain (
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field,
	HID_ITEM 			*Item
)
{
    UINT8	Data = 0;
                                        //(EIP71068)>
	switch (Item->bTag) {
		case HID_MAIN_ITEM_TAG_BEGIN_COLLECTION:
			GetItemData(Item, &Data, sizeof(Data));

			// Check if it is application collection
			if (Data == 0x01) {
				if (Field->UsagePage == 0x01) { 	// Generic Desktop
					switch (Field->Usages[Field->UsageCount - 1]) {
						case 0x01:		// Pointer
						case 0x02:		// Mouse
							DevInfo->HidDevType |= HID_DEV_TYPE_MOUSE;
							break;
						case 0x06:		// Keyboard
						case 0x07:		// KeyPad
							DevInfo->HidDevType |= HID_DEV_TYPE_KEYBOARD;
							break;
						default:
							break;
					}
				} else if (Field->UsagePage == 0x0D) {	// Digitizer
					if (Field->Usages[Field->UsageCount - 1] == 0x04) {
						DevInfo->HidDevType |= HID_DEV_TYPE_POINT;
					}
				}
			}
			break;

		case HID_MAIN_ITEM_TAG_END_COLLECTION:
			break;

		case HID_MAIN_ITEM_TAG_INPUT:
			GetItemData(Item, &Field->Flag, sizeof(Field->Flag));
			Field->Flag = (Field->Flag & 7) | HID_REPORT_FIELD_FLAG_INPUT;
            
            // Microstep USB Keyboard (Sonix Technology Co chip) workaround
            // The report descriptor has an error, Modifier keys is bitmap data, but 
            // it reports as array data. We force variable flag for Modifier keys input item.
            if ((DevInfo->wVendorId == 0x0C45) && 
                ((DevInfo->wDeviceId == 0x7603) || (DevInfo->wDeviceId == 0x7624))) {
                if ((Field->UsagePage == HID_UP_KEYBOARD) && 
                    (Field->UsageMin == HID_UP_KEYBOARD_LEFT_CTRL) &&
                    (Field->UsageMax == HID_UP_KEYBOARD_RIGHT_GUI)) {
                    Field->Flag |= HID_REPORT_FIELD_FLAG_VARIABLE;
                }
            }
            
    		AddField(&DevInfo->HidReport, Field);
			break;

		case HID_MAIN_ITEM_TAG_OUTPUT:
			GetItemData(Item, &Field->Flag, sizeof(Field->Flag));
			Field->Flag &= 7;
                                        //(EIP98251+)>
            if (Field->UsagePage == 0x8) {
				AddField(&DevInfo->HidReport, Field);
            }                                        //<(EIP98251+)
			break;

		case HID_MAIN_ITEM_TAG_FEATURE:
            CheckInputMode(DevInfo, Field);  //(EIP101990)
			break;

		default:
			break;
	}
                                        //<(EIP71068)
                                        //(EIP84455+)>
//Clear Local Item
	MemSet(Field->Usages, Field->UsageCount * sizeof(UINT16), 0);
	Field->UsageCount = 0;
	Field->UsageMin = 0;
	Field->UsageMax = 0;

                                        //<(EIP84455+)
	return 0;
}  

/**
    @param HidParserGlobal

    Parsing Global item 

 intput:      

    @retval 

**/
UINT8
HidParserGlobal (
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field,
	HID_ITEM 			*Item
)
{
	switch (Item->bTag) {
		case HID_GLOBAL_ITEM_TAG_USAGE_PAGE:
			GetItemData(Item, &Field->UsagePage, sizeof(Field->UsagePage));
										//(EIP65344+)>
            //Get Led usage page
			if (Field->UsagePage == 0x8) {
                DevInfo->HidReport.Flag |= HID_REPORT_FLAG_LED_FLAG;
			}
										//<(EIP65344+) 
			break;

		case HID_GLOBAL_ITEM_TAG_LOGICAL_MINIMUM:
			GetItemData(Item, &Field->LogicalMin, sizeof(Field->LogicalMin));
			break;
		
		case HID_GLOBAL_ITEM_TAG_LOGICAL_MAXIMUM:
			GetItemData(Item, &Field->LogicalMax, sizeof(Field->LogicalMax));
			break;
                                        //(EIP127014+)>
		case HID_GLOBAL_ITEM_TAG_PHYSICAL_MINIMUM:
			GetItemData(Item, &Field->PhysicalMin, sizeof(Field->PhysicalMin));
			break;
		
		case HID_GLOBAL_ITEM_TAG_PHYSICAL_MAXIMUM:
			GetItemData(Item, &Field->PhysicalMax, sizeof(Field->PhysicalMax));
			break;

		case HID_GLOBAL_ITEM_TAG_UNIT_EXPONENT:
			GetItemData(Item, &Field->UnitExponent, sizeof(Field->UnitExponent));
			break;
                                        //<(EIP127014+)
		case HID_GLOBAL_ITEM_TAG_REPORT_SIZE:
			GetItemData(Item, &Field->ReportSize, sizeof(Field->ReportSize));
			break;
		
		case HID_GLOBAL_ITEM_TAG_REPORT_COUNT:
			GetItemData(Item, &Field->ReportCount, sizeof(Field->ReportCount));
			break;
		
		case HID_GLOBAL_ITEM_TAG_REPORT_ID:
			GetItemData(Item, &Field->ReportId, sizeof(Field->ReportId));
			break;
		
		default:
			break;
	} 

	return USB_SUCCESS;
}

/**
    @param HidParserLocal

    Parsing Local item

 intput:      

    @retval 

**/
UINT8
HidParserLocal (
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field,
	HID_ITEM			*Item
)
{
	UINT32	Data;

	GetItemData(Item, &Data, sizeof(Data));

	switch (Item->bTag) {
		case HID_LOCAL_ITEM_TAG_USAGE:
			AddUsage(Field, Data);
			break;
		
		case HID_LOCAL_ITEM_TAG_USAGE_MINIMUM:
			Field->UsageMin = Data;
			break;
		
		case HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM:
			Field->UsageMax = Data;
            
            // Medigenic-Esterline USB keboard (Advanced Input Devices chip) 
            // workaround. This device reports the wrong local minimum for 
            // keyboard data in its report descriptor, local minimum should be 0x00.
            
            if ((DevInfo->wVendorId == 0x059d) && (DevInfo->wDeviceId == 0x0708)) {
                if ((Field->UsageMin == 0x01) && (Field->UsageMax == 0x65)) {
                    Field->UsageMin = 0x00;
                }
            }

			for (Data = Field->UsageMin; Data <= Field->UsageMax; Data++) {
				AddUsage(Field, Data);
			}
			break;
		
		default:	
			break;
	}

	return USB_SUCCESS;
}

/**
    @param HidParserReserved

    Parsing Reserved item

 intput:      

    @retval 

**/

UINT8
HidParserReserved(
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field,
	HID_ITEM			*Item
)
{
	return USB_SUCCESS;
} 

/**
    @param HidParseReportDescriptor

              
 intput:      
              
    @retval 

**/

VOID
HidParseReportDescriptor (
    DEV_INFO	*DevInfo,
    UINT8		*ReportDesc
)
{
	HID_REPORT			*Report = &DevInfo->HidReport;
	UINT8				*Start = ReportDesc;
	UINT8				*End = Start + Report->ReportDescLen;
	UINT16				Usages[0x300] = {0};
	HID_REPORT_FIELD	Field = {0};
	HID_ITEM  			Item = {0};
	UINT8 				Data;
	UINT8				DataSize[] = {0, 1, 2, 4};

	static	UINT8 (*DispatchType[]) (DEV_INFO *DevInfo, 
					HID_REPORT_FIELD *Field, HID_ITEM *Item) = {
		HidParserMain,
		HidParserGlobal,
		HidParserLocal,
		HidParserReserved
	};

	Field.Usages = Usages;
	Field.MaxUsages = COUNTOF(Usages);
	
	while (Start < End) {
		Data = *Start++;

		Item.bType = (Data >> 2) & 0x3;
		Item.bTag  = (Data >> 4) & 0xF;
		Item.bSize = DataSize[Data & 0x3];

		if ((Start + Item.bSize) > End) {
			break;
		}
	
		MemCpy(&Item.data.u32, Start, Item.bSize);
		Start += Item.bSize;
		DispatchType[Item.bType](DevInfo, &Field, &Item);
	}

    return;
}

/**
    @param CalculateInputReportDataLength

    This function calculates max data length to be reported 
    in the HID device.

 intput:      
              
    @retval 

**/

UINT16
CalculateInputReportDataLength (
	DEV_INFO	*DevInfo
)
{
	UINT8				Index = 0;
	HID_REPORT_FIELD	*Field = NULL;
	UINT16				ReportLen[256] = {0};
	UINT16				Length = 0;
	UINT16				MaxLength = 0;
	UINT16				ReportId = 0;

	for (Index = 0; Index < DevInfo->HidReport.FieldCount; Index++) {
		Field = DevInfo->HidReport.Fields[Index];
		if (!(Field->Flag & HID_REPORT_FIELD_FLAG_INPUT)) {
			continue;
		}

		ReportId = Field->ReportId;
		ReportLen[ReportId] += Field->ReportCount * Field->ReportSize;
	}

	for (ReportId = 0; ReportId < COUNTOF(ReportLen); ReportId++) {
		if (ReportLen[ReportId] == 0) {
			continue;
		}

		Length = (ReportLen[ReportId] + 7) >> 3;
		if (ReportId != 0) {
			Length++;
		}

		MaxLength = MaxLength < Length ? Length : MaxLength;
	}

	return MaxLength;
}

/**
    @param HidGetReportDescriptor


 intput:      
              
    @retval 

**/

UINT8
HidGetReportDescriptor(
    HC_STRUC	*HcStruc,
    DEV_INFO	*DevInfo,
    HID_DESC	*HidDesc
)
{
	UINT8		*ReportDesc = NULL;
	UINT8		Index = 0;
	UINT8		Status = USB_ERROR;
	DEV_REQ		Request = {0};

	if (HidDesc == NULL) {
		return USB_ERROR;
	}

	if (HidDesc->bDescriptorLength == 0) {
		return USB_SUCCESS;
	}

    ReportDesc = USB_MemAlloc(GET_MEM_BLK_COUNT(HidDesc->bDescriptorLength));
	if (ReportDesc == NULL) {
		return USB_ERROR;
	}

	Request.wRequestType = HID_RQ_GET_DESCRIPTOR;
	Request.wValue = DESC_TYPE_REPORT << 8;
	Request.wIndex = DevInfo->bInterfaceNum;
	Request.wDataLength = HidDesc->bDescriptorLength;

	for (Index = 0; Index < 3; Index++) {
		Status = UsbControlTransfer(HcStruc, DevInfo, Request, USB_GET_REPORT_DESC_TIMEOUT_MS, ReportDesc);
		if (Status == USB_SUCCESS) {
			break;
		}
	}

    DevInfo->HidReport.ReportDescLen = HidDesc->bDescriptorLength ;		
	HidParseReportDescriptor(DevInfo, ReportDesc);
	DevInfo->PollingLength = CalculateInputReportDataLength(DevInfo);

    USB_MemFree(ReportDesc, GET_MEM_BLK_COUNT(HidDesc->bDescriptorLength));
	return USB_SUCCESS;
}
                                        //(EIP84455+)>

/**
    @param USBHIDProcessData


 intput:      
              
    @retval 

**/ 

UINT8
USBHIDProcessData(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Td,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UINT8               DataType = 0;
    UINT8               i;
    UINT16              j;
	HID_REPORT_FIELD 	*Field = NULL;

    DataType = DevInfo->bProtocol;

	if (DevInfo->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
		for (i = 0; i < DevInfo->HidReport.FieldCount; i++) {
			Field = DevInfo->HidReport.Fields[i];

			//Check is input?
			if (!(Field->Flag & HID_REPORT_FIELD_FLAG_INPUT)) {
				continue;
			}
			//if report id exist, check first byte
			if (Field->ReportId != 0 && Field->ReportId != Buffer[0]) {
				continue;
			}

            if (Field->UsagePage == 7) {
                DataType = HID_BTYPE_KEYBOARD;
            }
            //Check X,Y
            if ((Field->UsagePage == 1) && (Field->UsageCount)!= 0) {
                for (j = 0; j < Field->UsageCount; j++) {
                //find X
                    if (Field->Usages[j] == 0x30) {
                        if (Field->Flag & HID_REPORT_FIELD_FLAG_RELATIVE) {
                            DataType = HID_BTYPE_MOUSE;
                        } else {
                            DataType = HID_BTYPE_POINT;
                        }
                    }

				}    
            }
		}
	}

    switch(DataType) {
        case HID_BTYPE_KEYBOARD:
            USBKBDProcessKeyboardData(HcStruc, DevInfo, Td, Buffer, DataLength);
            break;
        case HID_BTYPE_MOUSE:
            USBMSProcessMouseData(HcStruc, DevInfo, Td, Buffer, DataLength);
            break;
        case HID_BTYPE_POINT:
            USBAbsProcessMouseData(HcStruc, DevInfo, Td, Buffer, DataLength);
            break;          
        default:
            break;
    }
    return USB_SUCCESS; 
}
                                        //<(EIP84455+)

                                        //(EIP101990+)>
/**
    @param CheckInputMode


 intput:      
              
    @retval 

**/ 
VOID
CheckInputMode(
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field
)
{
	HC_STRUC	*HcStruc = gUsbData->HcTable[DevInfo->bHCNumber - 1];
	DEV_REQ		Request = {0};
    UINT8		*Buffer;
	UINT16		Index;
    
    for (Index = 0; Index < Field->UsageCount; Index++) {
		if (Field->UsagePage == 0xd) {
        	if (Field->Usages[Index] == 0x52 && Field->Usages[Index + 1] == 0x53) {
				Request.wRequestType = HID_RQ_SET_REPORT;
				Request.wValue = (0x03 << 8) | Field->ReportId;
				Request.wIndex = DevInfo->bInterfaceNum;
				Request.wDataLength = 3;

				Buffer = USB_MemAlloc (1); 
				Buffer[0] = Field->ReportId;
				Buffer[1] = 2;
				Buffer[2] = 0;

				UsbControlTransfer(HcStruc, DevInfo, Request, 100, Buffer);

				USB_MemFree(Buffer, 1);
            	break;
        	}
        }
    }
}
                                        //<(EIP101990+)
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
