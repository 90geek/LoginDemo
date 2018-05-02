//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2013, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           5555 Oakbrook Pkwy, Norcross, Georgia 30093       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
#ifndef __HOTKEY_BIN_H__
#define __HOTKEY_BIN_H__

#include "TseElinks.h" //GCH001002+
///EIP 115082 : Referance to Style module is removed. Managed from Style hooks
// Hotkey template moved to StyleHoook.h
extern VOID HandleEscKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID HandleHelpKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID HandlePrevValuesKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID HandleFailsafeKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID HandleOptimalKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID HandleSaveExitKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID HandlePrnScrnKey( VOID *app, VOID *hotkey, VOID *cookie );
extern VOID	PrntScrnKeyNotification(VOID *app, VOID *hotkey, VOID *cookie );

//GCH001001+START
VOID FxHandleSaveExitKey( VOID *app, VOID *hotkey, VOID *cookie )
{
	HandleSaveExitKey( app,hotkey,cookie );
	UpdateSystemInfoToBmc();
};
//GCH001002+END
#endif //__HOTKEY_BIN_H__
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2013, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           5555 Oakbrook Pkwy, Norcross, Georgia 30093       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
