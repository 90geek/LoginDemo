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

/** @file BmcTimeZoneDefaults.c
    1. Using setup callback function, validates Time Zone entered in Setup
    2. Using Hook function, loads optimal defaults when F3 is pressed

**/

//----------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <ServerMgmtSetupVariable.h>
#include "SetupData.h"
#include <Variable.h>

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
// Guid Definition
//

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
    Sets default Time Zone value to 0x7FFFF

    @param TimeZone[] - Pointer to TimeZone in BIOS setup variable

    @return VOID

**/

VOID
SetDefaultTimeZone (
  OUT  CHAR16  TimeZone[] )
{
    TimeZone[0] ='0';
    TimeZone[1] ='x';
    TimeZone[2] ='7';
    TimeZone[3] ='F';
    TimeZone[4] ='F';
    TimeZone[5] ='F';
}

/**
    This function is a hook called after setup utility loaded configuration defaults
    based on user input. This function is available as ELINK. This function loads
    Optimized default values for BMC LAN configuration parameters.

    @param VOID

    @return VOID

**/

VOID
LoadedBmcTimeZoneDefaults (
  VOID )
{
    UINT32          VarId = 0;
    UINT16          VarName[] = L"ServerSetup";
    BOOLEAN         VarFound = FALSE;
    CHAR16          TimeZone[6];
    VARIABLE_INFO   *Variable = NULL;

    SERVER_IPMI_TRACE((-1,"LoadedBmcTimeZoneDefaults function Entered.........\n"));

    //
    // Get the ServerMgmt Setup variable to set the default values
    // Get VariableList, compare GUID and String of ServerMgmt
    //
    for( VarId = 0; VarId < gVariables->VariableCount; VarId++ ) {
        Variable = (VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[VarId]);
        if( EfiCompareGuid(&gEfiServerMgmtSetupVariableGuid,&(Variable->VariableGuid)) ) {//Compare GUID
            if( EfiStrCmp(VarName,Variable->VariableName) == 0 ) {
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
    // Variable is found. Set the time zone to Default value
    //
    SetDefaultTimeZone ( TimeZone );
    VarSetValue(VarId, STRUCT_OFFSET(SERVER_MGMT_CONFIGURATION_DATA,TimeZone), sizeof (TimeZone), TimeZone);

    SERVER_IPMI_TRACE((-1,"LoadedBmcTimeZoneDefaults function Exiting.........\n"));
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
