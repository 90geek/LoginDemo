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

/** @file BmcLanParam.c
    Reads the LAN parameters from BMC and updates in Setup
    and Verifies the Static BMC Network configuration with Setup Callback

**/

//----------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include "BmcLanConfig.h"
#include <ServerMgmtSetup.h>
#include <ServerMgmtSetupVariable.h>
#include <Protocol/AMIPostMgr.h>
#include <Protocol/HiiString.h>
#include <Protocol/HiiDatabase.h>
#include <Library/HiiLib.h>
#include <Include/IpmiNetFnTransportDefinitions.h>
#include <Protocol/IPMITransportProtocol.h>

//----------------------------------------------------------------------

#define STRING_BUFFER_LENGTH        4000

//
// Global Variables
//
EFI_IPMI_TRANSPORT  *gIpmiTransport;

//
// Function Prototype
//
VOID InitString(EFI_HII_HANDLE HiiHandle, STRING_REF StrRef, CHAR16 *sFormat, ...);

/**
    It will return the String length of the array.

    @param String It holds the base address of the array.

    @return UINTN Returns length of the char array.

    @note  Function variable description

            String - It holds the base address of the array.

            Length - Holds the String length.

**/

UINTN
EfiStrLen (
  IN CHAR16   *String )
{
    INTN Length = 0;

    while(*String++) Length++;

    return Length;
}

/**
    Validate the IP address, and also convert the string
    IP to decimal value.If the IP is invalid then 0 Ip
    is entered.

    The Source string is parsed from right to left with
    following rules
    1) no characters other than numeral and dot is allowed
    2) the first right most letter should not be a dot
    3) no consecutive dot allowed
    4) values greater than 255 not allowed
    5) not more than four parts allowed

    @param Destination - contains validated IP address in decimal
             system
    @param Source - string IP to be validated

    @retval EFI_STATUS

    @note  Function variable description

              Index           - Counter for for loop and store the length
                                of the source array initially.
              LookingIp       - IP address is taken into four parts, one
                                part by one will be extracted from the
                                string and saved to Destination variable.
                                LookingIp variable contains which IP part
                                currently we are extracting.
              SumIp           - Contains sum of the digit of an IP address
                                multiplied by its base power. SumIp=
                               (unit digit * 1) + (Tenth digit * 10) +
                               (hundredth digit * 100)
              IpDigit         - base power of the digit we are extracting
              DigitCount      - digit number - 1 we are extracting in a 
                                IP part
              IsIpValid       - flag to set if an invalid IP is entered
                                and break the loop.
              GotTheFirstDigit- flag is set when the first decimal value is
                                found in the string,So if a dot is 
                                encountered first, immediately the loop can
                                be terminated.
              TotalSumIp      - sum of all 4 SumIp part of an IP address.
                                this variable is used to avoid 
                                000.000.000.000 IP case in the
                                BmcLanConfiguration.intial value is set to
                                zero.if sum of all 4 SumIp part of an IP
                                address is zero then that is invalid
                                input.

**/

EFI_STATUS
ValidateIpAddress(
  OUT  UINT8      Destination[],
  IN  CHAR16      Source[] )
{
    INTN       Index;
    INT8       LookingIp;
    UINT8      SumIp;
    UINT8      IpDigit;
    UINT8      DigitCount;
    UINT8      IsIpValid;
    UINT8      GotTheFirstDigit;
    UINT16     TotalSumIp;

    LookingIp = 3;
    SumIp = 0;
    IpDigit = 1;
    DigitCount = 0;
    IsIpValid = 1;
    GotTheFirstDigit = 0;
    TotalSumIp = 0 ;

    Index = (INTN) EfiStrLen(Source);

    //
    //Assigning index = 15 because it is not returning 15 as strlen if ip is
    //like xxx.xxx.xxx.xxx this.
    //

    if ( Index > 15) {
        Index = 15;
    }

    for (Index = (Index - 1); Index >= 0; Index--) {

        if (Source[Index] <= 57 && Source[Index] >= 48) {

            GotTheFirstDigit = 1;

            if (DigitCount > 2) {

                IsIpValid = 0;
                break;
            }

            if (DigitCount == 2) {

                if (Source[Index] - 48 >2) {

                    IsIpValid = 0;
                    break;
                }
                if (Source[Index] - 48 == 2 && ((Source[Index + 1] - 48 > 5) ||
                (Source[Index + 1] - 48 == 5 && Source[Index + 2] - 48 > 5))) {
                        IsIpValid = 0;
                        break;
                    } 
                }

            SumIp = SumIp + ((UINT8)Source[Index] - 48) * IpDigit;
            IpDigit = IpDigit * 10;
            DigitCount = DigitCount + 1;
        } else if (Source[Index] == 46) {

                    if (GotTheFirstDigit == 0 || Source[Index + 1] == 46) {

                        IsIpValid = 0;
                        break;
                    }
                    Destination[LookingIp] = SumIp;
                    TotalSumIp = TotalSumIp + SumIp;

                    LookingIp--;

                    if(LookingIp < 0) {

                        IsIpValid = 0;
                        break;
                    }
                    SumIp = 0;
                    IpDigit = 1;
                    DigitCount = 0;
            } else if (Source[Index] != 0 ||
                        (Source[Index] == 0 && GotTheFirstDigit == 1)) {

                        IsIpValid = 0;
                        break;
                }
    }

    if (LookingIp == 0) {

        Destination[LookingIp] = SumIp;
        TotalSumIp = TotalSumIp + SumIp;

    } 

    if(LookingIp !=0 || IsIpValid == 0 || TotalSumIp == 0) {

        Destination[0] = 0;
        Destination[1] = 0;
        Destination[2] = 0;
        Destination[3] = 0;
        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}

/**
    Validate the MAC address, and also convert the string MAC to
    decimal value.If the MAC is invalid then 0 MAC is entered.

    The Source string is parsed from right to left with following
    rules

    1) no characters other than numeral, alphabets a-f, A-F and
    - is allowed
    2) the first right most letter should not be a -
    3) no consecutive - allowed
    4) not more than six parts allowed

    @param Destination - contains validated MAC address in decimal 
        system
    @param  Source      - string MAC to be validated

    @return EFI_STATUS

    @note  Function variable description
  
              Index        - counter for loop.
              LookingMac   - MAC address is taken into six parts, one part
                             by one will be extracted from the string and
                             saved to Destination variable.
                             LookingMac variable contains which MAC part
                             currently we are extracting.
              SumMac       - contains sum of the digit of an MAC address
                             multiplied by its base power. SumMac=
                             (unit digit * 1) + (Tenth digit * 16)
              MacDigit     - base power of the digit we are extracting
              DigitCount   - digit number - 1 we are extracting in a MAC
                             part         
              IsMacValid   - flag to set if an invalid MAC is entered and
                             break the loop.
              GotTheFirstDigit - flag is set when the first hex value is
                                 found in the string,So if a - is 
                                 encountered first,immediately the loop
                                 can be terminated. 
              TmpValue     - Used to convert all small letters to capital
                             letters
              TotalSumMac  - sum of all 6 SumMac part of an MAC address.
                             this variable is used to avoid 
                             00-00-00-00-00-00 MAC case in the
                             BmcLanConfiguration.intial value is set to 
                             zero.if sum of all 6 SumMac is zero then 
                             that is invalid MAC.

**/

EFI_STATUS
ValidateMacAddress(
  OUT UINT8       Destination[],
  IN  CHAR16      Source[] )
{
    INT8       Index;
    INT8       LookingMac;
    UINT8      SumMac;
    UINT8      MacDigit;
    UINT8      DigitCount;
    UINT8      IsMacValid;
    UINT8      GotTheFirstDigit;
    UINT8      TmpValue;
    UINT16     TotalSumMac; 

    LookingMac = 5;
    SumMac = 0;
    MacDigit = 1;
    DigitCount = 0;
    IsMacValid = 1;
    GotTheFirstDigit = 0;
    TotalSumMac = 0;

    for (Index = 16; Index >= 0; Index--) {
    
        if ( (Source[Index] <= 57 && Source[Index] >= 48) ||
             (Source[Index] >= 65 && Source[Index] <= 70) ||
             (Source[Index] >= 97 && Source[Index] <= 102) ) {

            GotTheFirstDigit = 1;

            if (DigitCount > 1) {
                IsMacValid = 0;
                break;
            }

            TmpValue = (UINT8)Source[Index];

            if (TmpValue >= 97 && TmpValue <= 102) {
                TmpValue = TmpValue - 32;
            }
            TmpValue = TmpValue - 48;

            if (TmpValue > 9) {
            TmpValue = TmpValue - 7;
            }

            SumMac = SumMac + (TmpValue * MacDigit);
            MacDigit = MacDigit * 16;
            DigitCount = DigitCount + 1;

        } else if (Source[Index] == 45) {

                if (GotTheFirstDigit == 0 || Source[Index + 1] == 45) {
                    IsMacValid = 0;
                    break;
                }

                Destination[LookingMac] = SumMac;
                TotalSumMac = TotalSumMac + SumMac;

                LookingMac--;

                if(LookingMac < 0) {
                    IsMacValid = 0;
                    break;
                }

                SumMac = 0;
                MacDigit = 1;
                DigitCount = 0;

            } else {
                    IsMacValid = 0;
                    break;
                }

    }

    if (LookingMac == 0) {
        Destination[LookingMac] = SumMac;
        TotalSumMac = TotalSumMac + SumMac;
    } 

    if (LookingMac !=0 || IsMacValid == 0 || TotalSumMac == 0) {
        Destination[0] = 0;
        Destination[1] = 0;
        Destination[2] = 0;
        Destination[3] = 0;
        Destination[4] = 0;
        Destination[5] = 0;
        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}

/**
    Set IP address to 0.0.0.0 to memory pointed by ZeroIp

    @param ZeroIp - Pointer to Ip address in BIOS setup variable

    @retval VOID

**/

VOID
SetZeroIp(
  OUT  CHAR16      ZeroIp[] )
{

    ZeroIp[0] = 48;
    ZeroIp[1] = 46;
    ZeroIp[2] = 48;
    ZeroIp[3] = 46;
    ZeroIp[4] = 48;
    ZeroIp[5] = 46;
    ZeroIp[6] = 48;
    ZeroIp[7] = 0;
    ZeroIp[8] = 0;
    ZeroIp[9] = 0;
    ZeroIp[10] = 0;
    ZeroIp[11] = 0;
    ZeroIp[12] = 0;
    ZeroIp[13] = 0;
    ZeroIp[14] = 0;

}

/**
    Set MAC address to 00-00-00-00-00-00 to memory pointed by
    ZeroMac

    @param ZeroMac - Pointer to MAC address in BIOS setup variable

    @retval VOID

**/

VOID
SetZeroMac(
  OUT  CHAR16      ZeroMac[] )
{

    ZeroMac[0] = 48;
    ZeroMac[1] = 48;
    ZeroMac[2] = 45;
    ZeroMac[3] = 48;
    ZeroMac[4] = 48;
    ZeroMac[5] = 45;
    ZeroMac[6] = 48;
    ZeroMac[7] = 48;
    ZeroMac[8] = 45;
    ZeroMac[9] = 48;
    ZeroMac[10] = 48;
    ZeroMac[11] = 45;
    ZeroMac[12] = 48;
    ZeroMac[13] = 48;
    ZeroMac[14] = 45;
    ZeroMac[15] = 48;
    ZeroMac[16] = 48;

}

/**
    This function validate the given ip and MAC addresses and
    display error messages if given input is invalid data

    @param HiiHandle A handle that was previously registered in the
                     HII Database.
    @param Class    Formset Class of the Form Callback Protocol passed in
    @param SubClass Formset sub Class of the Form Callback Protocol passed in
    @param Key Formset Key of the Form Callback Protocol passed in

    @return EFI_STATUS Return Status

**/
EFI_STATUS
BmcLanConfigCallbackFunction(
  IN  EFI_HII_HANDLE     HiiHandle,
  IN  UINT16             Class,
  IN  UINT16             SubClass,
  IN  UINT16             Key )
{
    SERVER_MGMT_CONFIGURATION_DATA     *ServerMgmtConfiguration = NULL;
    BMC_IP_BIOS_SETTINGS                BmcLanIp1SetupValues;
#if BMC_LAN_COUNT == 2
    BMC_IP_BIOS_SETTINGS                BmcLanIp2SetupValues;
#endif
    CHAR16                              OutputString[STRING_BUFFER_LENGTH];
    EFI_STATUS                          Status = EFI_SUCCESS;
    UINTN                               SelectionBufferSize;
    CHAR16                              CharPtr[STRING_BUFFER_LENGTH];
    EFI_STATUS                          OutputStrStatus = EFI_SUCCESS;
    UINTN                               BufferSize = STRING_BUFFER_LENGTH;

    SERVER_IPMI_TRACE ((-1, "\nEntered BmcLanConfigCallbackFunction with Key: %x \n", Key));

    //
    // Check for the key and Return if Key value does not match
    //
    if ( (Key != BMC_NETWORK_STATION_IP1_KEY) && \
         (Key != BMC_NETWORK_SUBNET1_KEY) && \
         (Key != BMC_NETWORK_ROUTER_IP1_KEY) && \
         (Key != BMC_NETWORK_ROUTER_MAC1_KEY) && \
         (Key != BMC_NETWORK_STATION_IP2_KEY) && \
         (Key != BMC_NETWORK_SUBNET2_KEY) && \
         (Key != BMC_NETWORK_ROUTER_IP2_KEY) && \
         (Key != BMC_NETWORK_ROUTER_MAC2_KEY) ) {
        SERVER_IPMI_TRACE ((-1,"\nCallback function is called with Wrong Key Value. \
                                              Returning EFI_UNSUPPORTED\n"));
        return EFI_UNSUPPORTED;
    }

    //
    // Allocate memory for SERVER_MGMT_CONFIGURATION_DATA
    //
    SelectionBufferSize = sizeof (SERVER_MGMT_CONFIGURATION_DATA);
    Status = pBS->AllocatePool (
                EfiBootServicesData,
                SelectionBufferSize,
                (VOID **)&ServerMgmtConfiguration );
    if (EFI_ERROR (Status)) {
        return Status;
    }
    //
    // Get Browser DATA
    //
    Status = HiiLibGetBrowserData (
                &SelectionBufferSize,
                ServerMgmtConfiguration,
                &gEfiServerMgmtSetupVariableGuid,
                L"ServerSetup" );
    SERVER_IPMI_TRACE ((-1,"\nStatus of HiiLibGetBrowserData() = %r\n",Status));
    ASSERT_EFI_ERROR (Status);
    #if ( TSE_BUILD > 0x1208 )
    {
        //
        // Get the call back parameters and verify the action
        //
        CALLBACK_PARAMETERS *CallbackParameters = GetCallbackParameters();
        if ( CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGED ) {
            pBS->FreePool(ServerMgmtConfiguration);
            SERVER_IPMI_TRACE ((-1,"\n CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGED... so return EFI_SUCCESS\n"));
            return  EFI_SUCCESS;
        }
    }
    #endif //#if (TSE_BUILD > 0x1208)
    //
    // Validate Ip/MAC, for error case, display error message
    //
    switch( Key )
    {
        case BMC_NETWORK_STATION_IP1_KEY :
            Status = ValidateIpAddress (
                        BmcLanIp1SetupValues.StationIp,
                        ServerMgmtConfiguration->StationIp1 );
            if ( EFI_ERROR (Status) ) {
                SetZeroIp (ServerMgmtConfiguration->StationIp1);
                OutputStrStatus = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_INVALID_STATION_IP), OutputString, &BufferSize, NULL);
            }
            break;

        case BMC_NETWORK_SUBNET1_KEY :
            Status = ValidateIpAddress (
                           BmcLanIp1SetupValues.Subnet,
                           ServerMgmtConfiguration->Subnet1 );
            if ( EFI_ERROR (Status) ) {
                SetZeroIp(ServerMgmtConfiguration->Subnet1);
                OutputStrStatus = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_INVALID_SUBNETMASK), OutputString, &BufferSize, NULL);
            }
            break;

        case BMC_NETWORK_ROUTER_IP1_KEY :
            Status = ValidateIpAddress (
                        BmcLanIp1SetupValues.RouterIp,
                        ServerMgmtConfiguration->RouterIp1 );
            if ( EFI_ERROR (Status) ) {
                SetZeroIp(ServerMgmtConfiguration->RouterIp1);
                OutputStrStatus = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_INVALID_ROUTER_IP), OutputString, &BufferSize, NULL);
            }
            break;

        case BMC_NETWORK_ROUTER_MAC1_KEY :
            Status = ValidateMacAddress (
                        BmcLanIp1SetupValues.RouterMac,
                        ServerMgmtConfiguration->RouterMac1 );
            if ( EFI_ERROR (Status) ) {
                SetZeroMac(ServerMgmtConfiguration->RouterMac1);
                OutputStrStatus = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_INVALID_ROUTER_MAC), OutputString, &BufferSize, NULL);
            }
            break;

#if BMC_LAN_COUNT == 2

        case BMC_NETWORK_STATION_IP2_KEY :
            Status = ValidateIpAddress (
                        BmcLanIp2SetupValues.StationIp,
                        ServerMgmtConfiguration->StationIp2 );
            if ( EFI_ERROR (Status) ) {
                SetZeroIp(ServerMgmtConfiguration->StationIp2);
                OutputStrStatus = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_INVALID_STATION_IP), OutputString, &BufferSize, NULL);
            }
            break;

        case BMC_NETWORK_SUBNET2_KEY :
            Status = ValidateIpAddress (
                        BmcLanIp2SetupValues.Subnet,
                        ServerMgmtConfiguration->Subnet2 );
            if ( EFI_ERROR (Status) ) {
                SetZeroIp(ServerMgmtConfiguration->Subnet2);
                OutputStrStatus = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_INVALID_SUBNETMASK), OutputString, &BufferSize, NULL);
            }
            break;

        case BMC_NETWORK_ROUTER_IP2_KEY :
            Status = ValidateIpAddress (
                        BmcLanIp2SetupValues.RouterIp,
                        ServerMgmtConfiguration->RouterIp2 );
            if ( EFI_ERROR (Status) ) {
                SetZeroIp(ServerMgmtConfiguration->RouterIp2);
                OutputStrStatus = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_INVALID_ROUTER_IP), OutputString, &BufferSize, NULL);
            }
            break;

        case BMC_NETWORK_ROUTER_MAC2_KEY :
            Status = ValidateMacAddress (
                        BmcLanIp2SetupValues.RouterMac,
                        ServerMgmtConfiguration->RouterMac2 );
            if ( EFI_ERROR (Status) ) {
                SetZeroMac(ServerMgmtConfiguration->RouterMac2);
                OutputStrStatus = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_INVALID_ROUTER_MAC), OutputString, &BufferSize, NULL);
            }
            break;
#endif

        default :
            pBS->FreePool(ServerMgmtConfiguration);
            SERVER_IPMI_TRACE ((-1,"\nCallback function is called with Wrong Key Value. \
                                              Returning EFI_UNSUPPORTED\n"));
            return EFI_UNSUPPORTED;
    }
    if ( EFI_ERROR (Status) ) {

        AMI_POST_MANAGER_PROTOCOL   *AmiPostMgr = NULL;
        UINT8                       MsgBoxSel;

        //
        // Locate AmiPostMgr protocol to print the Error message
        //
        if ( !EFI_ERROR(pBS->LocateProtocol
             (&gAmiPostManagerProtocolGuid, NULL, (VOID **)&AmiPostMgr)) ) {
            BufferSize = STRING_BUFFER_LENGTH;
            Status = IpmiHiiGetString (HiiHandle, STRING_TOKEN(STR_BMCLAN_ERROR_INFO), CharPtr, &BufferSize, NULL);
            if ( (!EFI_ERROR (OutputStrStatus)) && (!EFI_ERROR (Status))) {
                AmiPostMgr->DisplayMsgBox(
                    CharPtr,
                    OutputString,
                    MSGBOX_TYPE_OK,
                    &MsgBoxSel );
            }
        }
        //
        // Set Browser DATA
        //
        Status = HiiLibSetBrowserData (
                    SelectionBufferSize,
                    ServerMgmtConfiguration,
                    &gEfiServerMgmtSetupVariableGuid,
                    L"ServerSetup" );
        SERVER_IPMI_TRACE ((-1,"\nStatus of HiiLibSetBrowserData() = %r\n",Status));
    } // EFI_ERROR (Status)

    pBS->FreePool(ServerMgmtConfiguration);

    SERVER_IPMI_TRACE ((-1, "\nExiting...... BmcLanConfigCallbackFunction\n"));

    return EFI_SUCCESS;
}

/**
    Checks for Set-In Progress Bit and Wait to get it Clear

    @param  LanChannelNumber - Channel Number of LAN

    @return EFI_STATUS
    @retval  EFI_SUCCESS - Set-In Progress Bit is Cleared
    @retval  EFI_TIMEOUT - Specified Time out over
    
**/

EFI_STATUS
IpmiWaitSetInProgressClear (
   UINT8 LanChannelNumber ) 
{
    EFI_STATUS                      Status;
    UINT8                           ResponseSize;
    UINT8                           Retries = 10;
    EFI_IPMI_GET_LAN_CONFIG_PRAM    GetLanParamCmd;
    EFI_GET_LAN_CONFIG_PARAM0          GetSetInProgResponse;

    GetLanParamCmd.LanChannel.ChannelNumber = LanChannelNumber;
    GetLanParamCmd.LanChannel.Reserved = 0;
    GetLanParamCmd.LanChannel.GetParam = 0; 
    GetLanParamCmd.ParameterSelector = 0;       
    GetLanParamCmd.SetSelector = 0;
    GetLanParamCmd.BlockSelector = 0;

    //
    // Wait for Set-In progress bit to clear
    //
    do {
        ResponseSize = sizeof (EFI_GET_LAN_CONFIG_PARAM0);
        Status = gIpmiTransport->SendIpmiCommand (
                     gIpmiTransport,
                     EFI_SM_NETFN_TRANSPORT,
                     BMC_LUN,
                     EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                     (UINT8*) &GetLanParamCmd,
                     sizeof (EFI_IPMI_GET_LAN_CONFIG_PRAM),
                     (UINT8*) &GetSetInProgResponse,
                     &ResponseSize );

        if ( EFI_ERROR (Status) ) {
            return Status;
        }

        if (GetSetInProgResponse.Param0.SetInProgress == 0) {
            break;
        }
        gBS->Stall (IPMI_STALL);
    } while (Retries-- > 0);

    if (Retries == 0) {
        return EFI_TIMEOUT;
    }
    return EFI_SUCCESS;
}

/**
    Reads the LAN parameters from BMC and updates in Setup

    @param  HiiHandle - Handle to HII database
    @param  Class - Indicates the setup class

    @retval VOID

**/

VOID
BmcLanParamDisplayInSetup(
  IN EFI_HII_HANDLE HiiHandle,
  IN UINT16         Class )
{

    EFI_STATUS     Status;
    UINT8          CommandDataSize;
    EFI_IPMI_GET_LAN_CONFIG_PRAM  GetLanParamCmd;
    EFI_GET_LAN_IP_ADDRESS_SRC    LanAddressSource;
    EFI_GET_LAN_MAC_ADDRESS       LanMacAddress;
    EFI_GET_LAN_IP_ADDRESS        LanIPAddress;
    EFI_GET_LAN_SUBNET_MASK       LanSubnetMask;
    UINT8          ResponseDataSize;
    UINT16         IPSource[5] = { STRING_TOKEN(STR_UNSPECIFIED),
                                   STRING_TOKEN(STR_IPSOURCE_STATIC_ADDRESS),
                                   STRING_TOKEN(STR_IPSOURCE_DYNAMIC_ADDRESS_BMC_DHCP),
                                   STRING_TOKEN(STR_IPSOURCE_DYNAMIC_ADDRESS_BIOS_DHCP),
                                   STRING_TOKEN(STR_IPSOURCE_DYNAMIC_ADDRESS_BMC_NON_DHCP)
                                  };
    UINT8          IPSourceIndex;
    CHAR16         CharPtr[STRING_BUFFER_LENGTH];
    EFI_STATUS     CharPtrStatus = EFI_SUCCESS;
    UINTN          BufferLength = STRING_BUFFER_LENGTH;

    SERVER_IPMI_TRACE ((-1, "BmcLanParamDisplayInSetup: Class ID:  %x\n", Class));

    //
    // Continue only for Server Mgmt setup page
    //
    if ( Class!= SERVER_MGMT_CLASS_ID ) {
        return;
    }
    //
    // Locate the IPMI transport protocol
    //
    Status = pBS->LocateProtocol (
                &gEfiDxeIpmiTransportProtocolGuid,
                NULL,
                (VOID **)&gIpmiTransport );
    SERVER_IPMI_TRACE ((-1, " gEfiDxeIpmiTransportProtocolGuid Status: %r \n", Status));
    if ( EFI_ERROR (Status) ) {
        return ;
    }
    
    //
    // Common for all LAN 1 Channel
    //
    GetLanParamCmd.LanChannel.ChannelNumber = BMC_LAN1_CHANNEL_NUMBER;
    GetLanParamCmd.LanChannel.Reserved = 0;
    GetLanParamCmd.LanChannel.GetParam = 0; 
    GetLanParamCmd.SetSelector = 0;
    GetLanParamCmd.BlockSelector = 0;
    CommandDataSize = sizeof (EFI_IPMI_GET_LAN_CONFIG_PRAM);

    //
    //Get IP address Source for Channel-1
    //

    GetLanParamCmd.ParameterSelector = EfiIpmiLanIpAddressSource;
    ResponseDataSize = sizeof (EFI_GET_LAN_IP_ADDRESS_SRC);

    //
    // Wait until Set In Progress field is cleared          
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN1_CHANNEL_NUMBER);
    if (!EFI_ERROR (Status)) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanAddressSource,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            if( LanAddressSource.AddressSrc > 4) {
                IPSourceIndex = 0;
            } else {
                IPSourceIndex = LanAddressSource.AddressSrc ;
            }

            CharPtrStatus = IpmiHiiGetString (HiiHandle, IPSource[IPSourceIndex], CharPtr, &BufferLength, NULL);
            if (!EFI_ERROR(CharPtrStatus)) {
                InitString (
                    HiiHandle,
                    STRING_TOKEN(STR_CURR_LANCAS1_VAL),
                    CharPtr );
            }
        } 
    }
    if ( EFI_ERROR (Status)) {
        CharPtrStatus = IpmiHiiGetString (HiiHandle, IPSource[0], CharPtr, &BufferLength, NULL);
        if (!EFI_ERROR(CharPtrStatus)) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_CURR_LANCAS1_VAL),
                CharPtr);
        }
    }

    //
    //Get station IP address of Channel-1
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanIpAddress;
    ResponseDataSize = sizeof (EFI_GET_LAN_IP_ADDRESS);

    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN1_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status) ) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanIPAddress,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_STATION_IP1_VAL),
                L"%d.%d.%d.%d",
                LanIPAddress.IpAddress[0], LanIPAddress.IpAddress[1], LanIPAddress.IpAddress[2], LanIPAddress.IpAddress[3]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_STATION_IP1_VAL),
            L"%d.%d.%d.%d",
            0,0,0,0);
        }

    //
    //Get Subnet MASK of Channel-1
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanSubnetMask;
    ResponseDataSize = sizeof (EFI_GET_LAN_SUBNET_MASK);

    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN1_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status)) {
    
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanSubnetMask,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_SUBNET_MASK1_VAL),
                L"%d.%d.%d.%d",
                LanSubnetMask.IpAddress[0], LanSubnetMask.IpAddress[1], LanSubnetMask.IpAddress[2], LanSubnetMask.IpAddress[3]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_SUBNET_MASK1_VAL),
            L"%d.%d.%d.%d",
            0,0,0,0);
    }

    //
    //Get MAC address of Channel-1
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanMacAddress;
    ResponseDataSize = sizeof (EFI_GET_LAN_MAC_ADDRESS);

    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN1_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status)) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanMacAddress,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_STATION_MAC1_VAL),
                L"%02x-%02x-%02x-%02x-%02x-%02x",
                LanMacAddress.MacAddress[0], LanMacAddress.MacAddress[1], LanMacAddress.MacAddress[2], LanMacAddress.MacAddress[3], LanMacAddress.MacAddress[4], LanMacAddress.MacAddress[5]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_STATION_MAC1_VAL),
            L"%02x-%02x-%02x-%02x-%02x-%02x",
            0,0,0,0,0,0);
    }

    //
    //Get Router Gateway IP Address of Channel-1
    //

    GetLanParamCmd.ParameterSelector = EfiIpmiLanDefaultGateway;
    ResponseDataSize = sizeof (EFI_GET_LAN_IP_ADDRESS);

    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN1_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status) ) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanIPAddress,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_ROUTER_IP1_VAL),
                L"%d.%d.%d.%d",
                LanIPAddress.IpAddress[0], LanIPAddress.IpAddress[1], LanIPAddress.IpAddress[2], LanIPAddress.IpAddress[3]);
        }
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_ROUTER_IP1_VAL),
            L"%d.%d.%d.%d",
            0,0,0,0);
    }

    //
    //Get Router MAC address of Channel-1
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanDefaultGatewayMac;
    ResponseDataSize = sizeof (EFI_GET_LAN_MAC_ADDRESS);

    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN1_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status)) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanMacAddress,
                    &ResponseDataSize );
        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_ROUTER_MAC1_VAL),
                L"%02x-%02x-%02x-%02x-%02x-%02x",
                LanMacAddress.MacAddress[0], LanMacAddress.MacAddress[1], LanMacAddress.MacAddress[2], LanMacAddress.MacAddress[3], LanMacAddress.MacAddress[4], LanMacAddress.MacAddress[5]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_ROUTER_MAC1_VAL),
            L"%02x-%02x-%02x-%02x-%02x-%02x",
            0,0,0,0,0,0);
    }
#if BMC_LAN_COUNT == 2
    //
    // Common for all LAN 2 Channel
    //
    GetLanParamCmd.LanChannel.ChannelNumber = BMC_LAN2_CHANNEL_NUMBER;
    GetLanParamCmd.LanChannel.Reserved = 0;
    GetLanParamCmd.LanChannel.GetParam = 0; 
    GetLanParamCmd.SetSelector = 0;
    GetLanParamCmd.BlockSelector = 0;
    CommandDataSize = sizeof (EFI_IPMI_GET_LAN_CONFIG_PRAM);

    //
    //Get IP address Source for Channel-2
    //

    GetLanParamCmd.ParameterSelector = EfiIpmiLanIpAddressSource;
    ResponseDataSize = sizeof (EFI_GET_LAN_IP_ADDRESS_SRC);
    
    //
    // Wait until Set In Progress field is cleared
    //
    BufferLength = STRING_BUFFER_LENGTH;
    Status = IpmiWaitSetInProgressClear (BMC_LAN2_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status) ) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanAddressSource,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {

            if( LanAddressSource.AddressSrc > 4) {
                IPSourceIndex = 0;
            } else {
                IPSourceIndex = LanAddressSource.AddressSrc;
            }
            CharPtrStatus = IpmiHiiGetString (HiiHandle, IPSource[IPSourceIndex], CharPtr, &BufferLength, NULL);
            if (!EFI_ERROR(CharPtrStatus)) {
                InitString (
                    HiiHandle,
                    STRING_TOKEN(STR_CURR_LANCAS2_VAL),
                    CharPtr);
            }
        } 
    }
    if ( EFI_ERROR (Status) ) {
        CharPtrStatus = IpmiHiiGetString (HiiHandle, IPSource[0], CharPtr, &BufferLength, NULL);
        if (!EFI_ERROR(CharPtrStatus)) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_CURR_LANCAS2_VAL),
                CharPtr);
        }
    }

    //
    //Get station IP address of Channel-2
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanIpAddress;
    ResponseDataSize = sizeof (EFI_GET_LAN_IP_ADDRESS);

    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN2_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status)) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanIPAddress,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_STATION_IP2_VAL),
                L"%d.%d.%d.%d",
                LanIPAddress.IpAddress[0], LanIPAddress.IpAddress[1], LanIPAddress.IpAddress[2], LanIPAddress.IpAddress[3]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_STATION_IP2_VAL),
            L"%d.%d.%d.%d",
            0,0,0,0);
    }

    //
    //Get Subnet MASK of Channel-2
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanSubnetMask;
    ResponseDataSize = sizeof (EFI_GET_LAN_SUBNET_MASK);

    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN2_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status) ) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanSubnetMask,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_SUBNET_MASK2_VAL),
                L"%d.%d.%d.%d",
                LanSubnetMask.IpAddress[0], LanSubnetMask.IpAddress[1], LanSubnetMask.IpAddress[2], LanSubnetMask.IpAddress[3]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_SUBNET_MASK2_VAL),
            L"%d.%d.%d.%d",
            0,0,0,0);
    }

    //
    //Get MAC address of Channel-2
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanMacAddress;
    ResponseDataSize = sizeof (EFI_GET_LAN_MAC_ADDRESS);
    
    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN2_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status) ) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanMacAddress,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_STATION_MAC2_VAL),
                L"%02x-%02x-%02x-%02x-%02x-%02x",
                LanMacAddress.MacAddress[0], LanMacAddress.MacAddress[1], LanMacAddress.MacAddress[2], LanMacAddress.MacAddress[3], LanMacAddress.MacAddress[4], LanMacAddress.MacAddress[5]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_STATION_MAC2_VAL),
            L"%02x-%02x-%02x-%02x-%02x-%02x",
            0,0,0,0,0,0);
    }

    //
    //Get Router Gateway IP Address of Channel-2
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanDefaultGateway;
    ResponseDataSize = sizeof (EFI_GET_LAN_IP_ADDRESS);
    
    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN2_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status) ) {
        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanIPAddress,
                    &ResponseDataSize );

        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_ROUTER_IP2_VAL),
                L"%d.%d.%d.%d",
                LanIPAddress.IpAddress[0], LanIPAddress.IpAddress[1], LanIPAddress.IpAddress[2], LanIPAddress.IpAddress[3]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_ROUTER_IP2_VAL),
            L"%d.%d.%d.%d",
            0,0,0,0);
    }

    //
    //Get Router MAC address of Channel-2
    //
    GetLanParamCmd.ParameterSelector = EfiIpmiLanDefaultGatewayMac;
    ResponseDataSize = sizeof (EFI_GET_LAN_MAC_ADDRESS);
    
    //
    // Wait until Set In Progress field is cleared
    //
    Status = IpmiWaitSetInProgressClear (BMC_LAN2_CHANNEL_NUMBER);
    if ( !EFI_ERROR (Status) ) {

        Status = gIpmiTransport->SendIpmiCommand (
                    gIpmiTransport,
                    EFI_SM_NETFN_TRANSPORT,
                    BMC_LUN,
                    EFI_TRANSPORT_GET_LAN_CONFIG_PARAMETERS,
                    (UINT8*)&GetLanParamCmd,
                    CommandDataSize,
                    (UINT8*)&LanMacAddress,
                    &ResponseDataSize );
        if ( !EFI_ERROR (Status) ) {
            InitString (
                HiiHandle,
                STRING_TOKEN(STR_ROUTER_MAC2_VAL),
                L"%02x-%02x-%02x-%02x-%02x-%02x",
                LanMacAddress.MacAddress[0], LanMacAddress.MacAddress[1], LanMacAddress.MacAddress[2], LanMacAddress.MacAddress[3], LanMacAddress.MacAddress[4], LanMacAddress.MacAddress[5]);
        } 
    }
    if ( EFI_ERROR (Status) ) {
        InitString (
            HiiHandle,
            STRING_TOKEN(STR_ROUTER_MAC2_VAL),
            L"%02x-%02x-%02x-%02x-%02x-%02x",
            0,0,0,0,0,0);
    }
#endif //#if BMC_LAN_COUNT == 2

    SERVER_IPMI_TRACE ((-1, "BmcLanParamDisplayInSetup: Returning..........\n"));
    return;
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
