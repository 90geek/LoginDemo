#ifndef _FXN_UPDATE_VARIABLE_DEFAULT__
#define _FXN_UPDATE_VARIABLE_DEFAULT__
#include <Token.h>
#include <Library\UefiBootServicesTableLib.h>
#include <Library\UefiRuntimeServicesTableLib.h>
#include <Library\BaseLib.h>
#include <Library\DebugLib.h>
#include <Library\MemoryAllocationLib.h>

//ZYY006022- #include <FxnFeatureSetup.h>
#include <Setup.h>
#include <Library/HiiLib.h>
#include <Guid/SetupVariable.h>
//#include <Include/ServerMgmtSetupVariable.h>
#include <Library/IoLib.h>
#include <AmiDxeLib.h>


#define DEFAULTS_GUID  \
  {0x4599d26f, 0x1a11, 0x49b8, 0xb9, 0x1f, 0x85, 0x87, 0x45, 0xcf, 0xf8, 0x24}
#define NVAR_SIGNATURE ('N'+('V'<<8)+(('A'+('R'<<8))<<16))
#pragma pack(push)
#pragma pack(1)
typedef struct{
  UINT32 signature;
  UINT16 size;
  UINT32 next:24;
  UINT32 flags:8;
  UINT8  GuidIndex;
  CHAR8  VariableName[1];
}NVAR;
#pragma pack(pop)

typedef
BOOLEAN
(EFIAPI *FXN_VARIABLE_PATCH_FUNCTION) (
  VOID   *Variable
  );


typedef struct _VARIABLE_PATCH_FUNCTION {
  EFI_GUID                    *VariableGuid;
  CHAR8                       VariableName [50];
  FXN_VARIABLE_PATCH_FUNCTION Function;   
} VARIABLE_PATCH_FUNCTION;

UINT8
CmosRead (
    IN UINT8    Offset
    );

BOOLEAN
PatchOemTSEVarConfig (
    VOID           *VariableBuffer
    );
BOOLEAN
PatchSocketPowerManagementConfig (
    VOID           *VariableBuffer
    );


BOOLEAN
PatchSetupVariableConfig (
    VOID           *VariableBuffer
    );
#endif

