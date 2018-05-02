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

/** @file BmcLanDefaults.c
    loads Optimized default values for BMC LAN configuration 
    parameters

**/


//----------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <ServerMgmtSetupVariable.h>
#include "setupdata.h"
#include <variable.h>

//----------------------------------------------------------------------

//
// Macro Definitions
//
#define STRUCT_OFFSET(type, field)  (UINTN)&(((type *)0)->field)

//
// Extern Variable
//
extern VARIABLE_LIST *gVariables;

//
// Functional Prototypes
//
BOOLEAN
EfiCompareGuid (
  IN EFI_GUID *Guid1,
  IN EFI_GUID *Guid2
  );

INTN
EfiStrCmp (
  IN CHAR16   *String,
  IN CHAR16   *String2
  );

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
    This function is a hook called after setup utility
    loaded configuration defaults based on user input. This
    function is available as ELINK. This function loads Optimized
    default values for BMC LAN configuration parameters.

    @param VOID

    @retval VOID

**/

VOID
LoadedBmcLanConfigDefaults ( 
  VOID )
{
    UINT32          VarId = 0;
    UINT16          VarName[] = L"ServerSetup";
    BOOLEAN         VarFound = FALSE;
    CHAR16          ZeroIp[15];
    CHAR16          ZeroMac[17];
    VARIABLE_INFO   *Variable = NULL;

    SERVER_IPMI_TRACE((-1,"LoadedBmcLanConfigDefaults function Entered.........\n"));

    //
    // Get the ServerMgmt Setup variable to set the default values
    // Get VariableList, compare GUID and String of ServerMgmt
    //
    for( VarId = 0; VarId < gVariables->VariableCount; VarId++ ) {
        Variable = (VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[VarId]);
        if( EfiCompareGuid (&gEfiServerMgmtSetupVariableGuid, &(Variable->VariableGuid)) ) {//Compare GUID
            if( EfiStrCmp (VarName, Variable->VariableName) == 0 ) {
                VarFound = TRUE;
                break;
            } // if (EfiStrCmp)
        } // if (EfiCompareGuid)
    } //for loop
    //
    // If the Variable is not found, Return.
    //
    if (VarFound == FALSE) {
        SERVER_IPMI_TRACE((-1,"ServerMgmt Variable is not found\n"));
        return;
    }
    //
    // Variable is found. Set the Zero IP and MAC to set Default values
    //
    SetZeroIp ( ZeroIp );
    SetZeroMac ( ZeroMac );
    //
    // Set default values for BMc LAN Parameters for Channel-1 when BMC_LAN_COUNT >= 1
    //
#if BMC_LAN_COUNT >= 1
    VarSetValue (VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,StationIp1), sizeof (ZeroIp), ZeroIp);
    VarSetValue (VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,Subnet1), sizeof (ZeroIp), ZeroIp);
    VarSetValue (VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,RouterIp1), sizeof (ZeroIp), ZeroIp);
    VarSetValue (VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,RouterMac1), sizeof (ZeroMac), ZeroMac);
#endif
    //
    // Set default values for BMC LAN Parameters for Channel-2 when BMC_LAN_COUNT == 2
    //
#if BMC_LAN_COUNT == 2
    VarSetValue (VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,StationIp2), sizeof (ZeroIp), ZeroIp);
    VarSetValue (VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,Subnet2), sizeof (ZeroIp), ZeroIp);
    VarSetValue (VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,RouterIp2), sizeof (ZeroIp), ZeroIp);
    VarSetValue (VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,RouterMac2), sizeof (ZeroMac), ZeroMac);
#endif

    SERVER_IPMI_TRACE((-1,"LoadedBmcLanConfigDefaults function Exiting.........\n"));

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
