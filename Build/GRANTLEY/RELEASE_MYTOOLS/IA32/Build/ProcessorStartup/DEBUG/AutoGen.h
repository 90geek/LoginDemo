/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_0833A84D_8A39_431f_BD1C_30965AAE71DD
#define _AUTOGENH_0833A84D_8A39_431f_BD1C_30965AAE71DD

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <PiPei.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern EFI_GUID gCpuUncoreTokenSpaceGuid;

// PCD definitions
#define _PCD_TOKEN_PcdFlashSecCacheRegionBase  135U
extern const UINT32 _gPcd_FixedAtBuild_PcdFlashSecCacheRegionBase;
#define _PCD_GET_MODE_32_PcdFlashSecCacheRegionBase  _gPcd_FixedAtBuild_PcdFlashSecCacheRegionBase
//#define _PCD_SET_MODE_32_PcdFlashSecCacheRegionBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_PcdFlashSecCacheRegionBase 4
#define _PCD_GET_MODE_SIZE_PcdFlashSecCacheRegionBase _PCD_SIZE_PcdFlashSecCacheRegionBase
#define _PCD_TOKEN_PcdFlashSecCacheRegionSize  136U
extern const UINT32 _gPcd_FixedAtBuild_PcdFlashSecCacheRegionSize;
#define _PCD_GET_MODE_32_PcdFlashSecCacheRegionSize  _gPcd_FixedAtBuild_PcdFlashSecCacheRegionSize
//#define _PCD_SET_MODE_32_PcdFlashSecCacheRegionSize  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_SIZE_PcdFlashSecCacheRegionSize 4
#define _PCD_GET_MODE_SIZE_PcdFlashSecCacheRegionSize _PCD_SIZE_PcdFlashSecCacheRegionSize


#ifdef __cplusplus
}
#endif

#endif
