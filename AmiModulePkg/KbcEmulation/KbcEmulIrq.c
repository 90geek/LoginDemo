//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        KbcEmulIrq.c
//
// Description: Handles the IRQ1 and IRQ12 generation
//
//****************************************************************************
//<AMI_FHDR_END>


#include "Token.h"

#include "KbcEmul.h"
#include "KbcEmulLib.h"
#include "KbcDevEmul.h"
#if OHCI_EMUL_SUPPORT
#include "KbcOhci.h"
#endif
#if SB_EMUL_SUPPORT
#include "KbcSb.h"
#endif

VOID GenerateIRQ12(VIRTKBC*);
VOID GenerateIRQ1(VIRTKBC*);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GenerateIRQ12
//
// Description: Generate IRQ1
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GenerateIRQ12(VIRTKBC* vkbc)
{

#if UHCI_EMUL_SUPPORT || IOTRAP_EMUL_SUPPORT
  

    ByteReadIO(SW_IRQ_GENERATION_REG);
    ByteWriteIO(SW_IRQ_GENERATION_REG, 0);
    ByteWriteIO(SW_IRQ_GENERATION_REG,  2);
    return;
#endif
    
#if OHCI_EMUL_SUPPORT
    if (GetHceStatus() & HCE_STS_OUTPUTFULL ){
        SetHceControl((GetHceControl() | HCE_CNTRL_IRQ_ENABLE));  
    } else {
        SetHceStatus((GetHceStatus() | HCE_STS_OUTPUTFULL | HCE_STS_AUXOUTPUTFULL));
        SetHceControl((GetHceControl() | HCE_CNTRL_IRQ_ENABLE));  
    }
    return;
#endif

#if SB_EMUL_SUPPORT
    GenerateSbIRQ12();
    return;
#endif
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GenerateIRQ1
//
// Description: Generate IRQ1
//
// Input:       None
//
// Output:      None    
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GenerateIRQ1(VIRTKBC* vkbc)
{

#if UHCI_EMUL_SUPPORT || IOTRAP_EMUL_SUPPORT
    UINT8       IrqMask;

    //
    //Enable IRQ1 before generating the IRQ1.
    //
    IrqMask = ByteReadIO(0x21);
    if (IrqMask & 0x02) {
      IrqMask &= 0xFD;
      ByteWriteIO (0x21, IrqMask);
    }

    ByteReadIO(SW_IRQ_GENERATION_REG);
    ByteWriteIO(SW_IRQ_GENERATION_REG, 0);
    ByteWriteIO(SW_IRQ_GENERATION_REG,  1);
    return;

#endif
#if OHCI_EMUL_SUPPORT    
    UINT8       IrqMask;
    //
    //Enable IRQ1 before generating the IRQ1.
    //
    IrqMask = ByteReadIO(0x21);
    if (IrqMask & 0x02) {
      IrqMask &= 0xFD;
      ByteWriteIO (0x21, IrqMask);
    }

    if (GetHceStatus() & HCE_STS_OUTPUTFULL ){
        SetHceControl((GetHceControl() | HCE_CNTRL_IRQ_ENABLE));  
    } else {
        vkbc->st_ |= KBC_STATUS_OBF;
        SetHceStatus((GetHceStatus() | KBC_STATUS_OBF));  
        SetHceControl((GetHceControl() | HCE_CNTRL_IRQ_ENABLE));  
    }
    return;
#endif

#if SB_EMUL_SUPPORT
    GenerateSbIRQ1();
    return;
#endif    
}

//****************************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
