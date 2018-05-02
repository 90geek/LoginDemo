// The ASL file for _OSC Method Implementation
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//-----------------------------------------------------------------------

//;<AMI_PHDR_START>
//;------------------------------------------------------------------------
//;
//; Procedure:    _OSC
//; Description:  METHOD CALLED ON SYSTEM STARTUP TO NEGOTIATE OS/BIOS
//; SUPPORTED FEATURES
//; Input: 	Arg0 (Buffer): UUID
//;		Arg1 (Integer): Revision ID
//;		Arg2 (Integer): Count
//;		Arg3 (Buffer): Capabilities Buffer,
//;
//; Output: Returns modified Arg3.
//;
//;-------------------------------------------------------------------------
//;<AMI_PHDR_END>

  Method(_OSC,4,Serialized)
		{ 
    Name(SUPP,0) // PCI _OSC Support Field value
    Name(CTRL,0) // PCI _OSC Control Field value
    // Create DWord-adressable fields from the Capabilities Buffer
    CreateDWordField(Arg3,0,CDW1)
    CreateDWordField(Arg3,4,CDW2)
    If(LGreater(Arg2,2)) {         // Fill 3rd capability DWORD only if the count is greater than2.
        CreateDWordField(Arg3,8,CDW3)
    } 	
    //AptioV server override Start: GPE message generation should not apply to DMI port on Grantley Refresh
    //Execute the code only for IIO0
    Store(_BBN(),Local0)
    If( LEqual(Local0,0x0000) ) {					
        //
        // The Intel xHCI driver will call _OSC with this UUID
        // This is to enable xHCI controller on older OSs
        //
        If (LEqual (Arg0, ToUUID("7C9512A9-1705-4CB4-AF7D-506A2423AB71"))) {
        Return (\_SB.PCI0.XHCI.POSC(Arg1, Arg2, Arg3))
        }         
    }
    //AptioV server override end: GPE message generation should not apply to DMI port on Grantley Refresh
      
    // Check for proper UUID
    If(LEqual(Arg0,ToUUID("33DB4D5B-1FF7-401C-9657-7441C03DD766")))
    {
				// Save Capabilities DWord2 & 3
				Store(CDW2,SUPP)
				Store(CDW3,CTRL)
				//Support Bits: 
				//0 - extended pci config operation region
				//1 - ASPM supported
				//2 - Clock Power Management Capability supported
				//3 - Pci Segment Groups supported
				//4 - MSI supported
		
				//Control Bits: 
				//0 - Pci Express Native Hot Plug control
				//1 - SHPC Native Hot Plug control
				//2 - Pci Express Native Power Management Events control
				//3 - Pci Express Advanced Error Reporting control
				//4 - Pci Express Capability Structure control
		
				// Only allow native hot plug control if OS supports:
				// * ASPM
				// * Clock PM
				// * MSI/MSI-X
		
        If (LOr(AHPE, LNotEqual(And(SUPP, 0x16), 0x16))) { // Conditions not met?         
            And(CTRL,0x1E,CTRL) // Mask bit 0 to deny native PCIE HP.
            Sleep(1000)      // AptioV server override - GPE message generation should not apply to DMI port on Grantley Refresh
        }
    //
    // Never allow SHPC (no SHPC controller in system)
    //
    And(CTRL, 0x1D, CTRL)
    //AptioV server override end: Never allow SHPC				
    if (LNot(PEPM)) //BIOS Supports PCI Express ASPM?  
    {
        And(CTRL,0x1B,CTRL) //Have OS Control ASPM
        //Or(CTRL,0x04)     //Keep BIOS Settings.
    }
    if (LNot(PEER))	//BIOS Supports PCI Express Adv Error Reporting? 	 
    {
        And(CTRL,0x15,CTRL)
    }
    if (LNot(PECS)) //BIOS Provides PCI Express MCFG Table?  
    {
        And(CTRL,0xF,CTRL)
    }

    //AptioV server override start: Code moved from SysBus.asi to use only AMI _OSC method
    If (Not(And(CDW1,1))) { // Query Flag Clear?
    //
    // Disable GPEs for Features granted native control
    //
    If (And(CTRL, 0x01)) { // Native Hot plug control granted?
                    
        \_SB.PCI0.BR1A.OSHP ()
        \_SB.PCI0.BR1B.OSHP ()
        \_SB.PCI0.BR2A.OSHP ()
        \_SB.PCI0.BR2B.OSHP ()
        \_SB.PCI0.BR2C.OSHP ()
        \_SB.PCI0.BR2D.OSHP ()
        \_SB.PCI0.BR3A.OSHP ()
        \_SB.PCI0.BR3B.OSHP ()
        \_SB.PCI0.BR3C.OSHP ()
        \_SB.PCI0.BR3D.OSHP ()
// AptioV server override  - start
        ShiftRight(IIOH, 1, Local1)
        And(Local1, 0x1, Local1)
        if(LEqual(Local1, 1)) {
// AptioV server override - end
         	\_SB.PCI1.QRP0.OSHP ()
		\_SB.PCI1.QR1A.OSHP ()
		\_SB.PCI1.QR1B.OSHP ()
		\_SB.PCI1.QR2A.OSHP ()
		\_SB.PCI1.QR2B.OSHP ()
		\_SB.PCI1.QR2C.OSHP ()
		\_SB.PCI1.QR2D.OSHP ()
		\_SB.PCI1.QR3A.OSHP ()
		\_SB.PCI1.QR3B.OSHP ()
		\_SB.PCI1.QR3C.OSHP ()
		\_SB.PCI1.QR3D.OSHP ()        
        }  //AptioV server override
// AptioV server override start
        ShiftRight(IIOH, 2, Local1)
        And(Local1, 0x1, Local1)
        if(LEqual(Local1, 1)) {
// AptioV server override end
                \_SB.PCI2.RRP0.OSHP ()
                \_SB.PCI2.RR1A.OSHP ()
                \_SB.PCI2.RR1B.OSHP ()
                \_SB.PCI2.RR2A.OSHP ()
                \_SB.PCI2.RR2B.OSHP ()
                \_SB.PCI2.RR2C.OSHP ()
                \_SB.PCI2.RR2D.OSHP ()
                \_SB.PCI2.RR3A.OSHP ()
                \_SB.PCI2.RR3B.OSHP ()
                \_SB.PCI2.RR3C.OSHP ()
                \_SB.PCI2.RR3D.OSHP ()
        }  //AptioV server override
// AptioV server override start
        ShiftRight(IIOH, 3, Local1)
        And(Local1, 0x1, Local1)
        if(LEqual(Local1, 1)) {
// AptioV server override end
                \_SB.PCI3.SRP0.OSHP ()
                \_SB.PCI3.SR1A.OSHP ()
                \_SB.PCI3.SR1B.OSHP ()
                \_SB.PCI3.SR2A.OSHP ()
                \_SB.PCI3.SR2B.OSHP ()
                \_SB.PCI3.SR2C.OSHP ()
                \_SB.PCI3.SR2D.OSHP ()
                \_SB.PCI3.SR3A.OSHP ()
                \_SB.PCI3.SR3B.OSHP ()
                \_SB.PCI3.SR3C.OSHP ()
                \_SB.PCI3.SR3D.OSHP ()
        }
                        
        Store (0x01, GPSH)                // Clear Hotplug SCI Enable status in GPE0
        }
        //AptioV server override end: Code moved from SysBus.asi to use only AMI _OSC method
            
          If (LNotEqual(Arg1,one)) { // unknown revision
            Or(CDW1,0x08,CDW1)
          }

          If(LNotEqual(CDW3,CTRL)) { // capabilities bits were masked
            Or(CDW1,0x10,CDW1)
          }
          //
          // update DWORD3 in the buffer
          //
          Store(CTRL,CDW3)
          Return(Arg3)

      } Else {
        //
        // Just indicate unrecognized UUID
        // Leave it at that
        //
        Or (CDW1,4,CDW1)
        Store (0xEE, IO80)
        Return(Arg3)
      }
    }
  } // End _OSC

//-----------------------------------------------------------------------
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
