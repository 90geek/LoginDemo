


#define PSTATE_SUPPORT 1
#define CSTATE_SUPPORT 1
#define TSTATE_SUPPORT 1    

#include <AcpiOemElinks.h>

DefinitionBlock (
    "AmiCpuPm.aml",
    "SSDT",
    2,
    ACPI_OEM_ID_MAK,
    "PmMgt",
    1)
{
Scope(\_SB) {
#include <TokenAsl.h>

External (\PETE, IntObj) 
External (PSEN, FieldUnitObj)
External (HWEN, FieldUnitObj) //HWPM
External (ACEN, FieldUnitObj) //HWPM
External (\HWPE, IntObj)

    Name(HWOB, 0) // OOB mode HWPM enabled flag

#define PER_THREAD_ACPI 0

    Name(TYPE, 0xFFFFFFFF)  

#if PSTATE_SUPPORT == 1
#include "AmiCpuPstates.asi"
#endif


#if CSTATE_SUPPORT == 1
#include "AmiCpuCstates.asi"
#endif

#if TSTATE_SUPPORT == 1
#include "AmiCpuTstates.asi"
#endif    
     
    //Global Methods
    
    Method(PDC,1) {
        //
        // Store result of PDC.
        //
        CreateDWordField(Arg0,8,CAPA)         // Point to 3rd DWORD.

        CreateDwordField (Arg0, 0, REVS)
        CreateDwordField (Arg0, 4, SIZE)

        //
        // Local0 = Number of bytes for Arg0
        //
        Store (SizeOf (Arg0), Local0)

        //
        // Local1 = Number of Capabilities bytes in Arg0 
        //
        Store (Subtract (Local0, 8), Local1)

        //
        // TEMP = Temporary field holding Capability DWORDs
        //
        CreateField (Arg0, 64, Multiply (Local1, 8), TEMP)

        //
        // Create the Status (STS0) buffer with the first DWORD = 0
        // This is required as per ACPI 3.0 Spec which says the
        // first DWORD is used to return errors defined by _OSC.
        //
        Name (STS0, Buffer () {0x00, 0x00, 0x00, 0x00})

        //
        // Concatenate the _PDC capabilities bytes to the STS0 Buffer
        // and store them in a local variable for calling OSC
        //
        Concatenate (STS0, TEMP, Local2)

        OSC (ToUUID("4077A616-290C-47BE-9EBD-D87058713953"), REVS, SIZE, Local2)

    }
    
    Method(OSC, 4)
    {
        //
        // Store result of PDC.
        //
        CreateDWordField(Arg3,4,CAPA)         // Point to 3rd DWORD.
        Store(CAPA, TYPE)                     // Store It in PDCx.

        // Point to Status DWORD in the Arg3 buffer (STATUS)
        CreateDWordField(Arg3, 0, STS0)

        // Point to Caps DWORDs of the Arg3 buffer (CAPABILITIES)
        CreateDwordField(Arg3, 4, CAP0)

        //
        // _OSC needs to validate the UUID and Revision.
        //
        // IF Unrecognized UUID
        //  Return Unrecognized UUID _OSC Failure
        // IF Unsupported Revision
        //  Return Unsupported Revision _OSC Failure
        //
        //    STS0[0] = Reserved
        //    STS0[1] = _OSC Failure
        //    STS0[2] = Unrecognized UUID
        //    STS0[3] = Unsupported Revision
        //    STS0[4] = Capabilities masked
        //
        // Note:  The comparison method used is necessary due to
        // limitations of certain OSes which cannot perform direct
        // buffer comparisons.
        //
        // Create a set of "Input" UUID fields.
        //
        CreateDwordField(Arg0, 0x0, IID0)
        CreateDwordField(Arg0, 0x4, IID1)
        CreateDwordField(Arg0, 0x8, IID2)
        CreateDwordField(Arg0, 0xC, IID3)
        //
        // Create a set of "Expected" UUID fields.
        //
        Name(UID0, ToUUID("4077A616-290C-47BE-9EBD-D87058713953"))
        CreateDwordField(UID0, 0x0, EID0)
        CreateDwordField(UID0, 0x4, EID1)
        CreateDwordField(UID0, 0x8, EID2)
        CreateDwordField(UID0, 0xC, EID3)
        //
        // Verify the input UUID matches the expected UUID.
        //
        If(LNot(LAnd(LAnd(LEqual(IID0, EID0),LEqual(IID1, EID1)),LAnd(LEqual(IID2, EID2),LEqual(IID3, EID3)))))
        {
            //
            // Return Unrecognized UUID _OSC Failure
            //
            Store (0x6, Index (STS0, 0))
            Return (Arg3)
        }

        If(LNot(LEqual(Arg1,1)))
        {
            //
            // Return Unsupported Revision _OSC Failure
            //
            Store (0xA, Index (STS0, 0))
            Return (Arg3)
        }

        //
        // Verify if OS is simply querying what functions are supported
        //
        // Bit 0 = Query Support Flag.
        //
        If(And(STS0,0x01))
        {
            //
            // Mask off the bits supported and return.
            //
            And(CAP0, 0xBFF, CAP0)
            Return (Arg3)
        }
        //	
        //HWPM changes-start
        //
        Store(0, HWOB)  //AptioV server override - As HWOB is defined in this file itself, \ should not be used.
        If(LEqual(HWEN,2))//check OOB mode in setup 
        {
            Store(1, HWOB)  //AptioV server override - As HWOB is defined in this file itself, \ should not be used.
        }
       
#if SPS_SUPPORT
        If(LOr(LEqual(HWEN,1), LEqual(HWEN,2)))//Native or OOB mode in setup
        {
            Store(1, \HWPE)
        }
#endif
        //HWPM changes-end
        And(CAP0, 0xBFF, CAP0)
        Store(CAP0, TYPE)               // Store It in PDCx.
        Return (Arg3)
    }

/////////////////////////////////////////////////////////////////////////////////////////


#undef PER_THREAD_ACPI
#define PER_THREAD_ACPI 1

#undef ToSocket
#define ToSocket(x) x##0

#undef SOCKET_NUM
#define SOCKET_NUM 0

#include "AmiCpuPmThreads.asi"

#undef ToSocket
#define ToSocket(x) x##1

#undef SOCKET_NUM
#define SOCKET_NUM 1

#include "AmiCpuPmThreads.asi"

#undef ToSocket
#define ToSocket(x) x##2

#undef SOCKET_NUM
#define SOCKET_NUM 2


#include "AmiCpuPmThreads.asi"

#undef ToSocket
#define ToSocket(x) x##3

#undef SOCKET_NUM
#define SOCKET_NUM 3

#include "AmiCpuPmThreads.asi"
}
}