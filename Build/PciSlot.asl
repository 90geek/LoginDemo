Scope( \_SB.PCI0.BR2A){
  Method ( _DSM, 4, NotSerialized, 0, UnknownObj, {BuffObj, IntObj, IntObj,PkgObj})
  {
        If (LEqual(Arg0, ToUUID ("E5C937D0-3553-4d7a-9117-EA4D19C3434D"))) {
          If (Land( Lequal(Arg1, 2 ), Lequal(Arg2,0 ))){
             return (Buffer() {0x80})
          }
          If (Land( Lequal(Arg1, 2), Lequal(Arg2,7 ))){
             Return ( Package(2 ){
                         0x1,
                         Unicode(" Slot1 x16")
                     }
                 )
          }
         }
             return(Buffer(){0})
  }
}
Scope( \_SB.PCI0.BR2C){
  Method ( _DSM, 4, NotSerialized, 0, UnknownObj, {BuffObj, IntObj, IntObj,PkgObj})
  {
        If (LEqual(Arg0, ToUUID ("E5C937D0-3553-4d7a-9117-EA4D19C3434D"))) {
          If (Land( Lequal(Arg1, 2 ), Lequal(Arg2,0 ))){
             return (Buffer() {0x80})
          }
          If (Land( Lequal(Arg1, 2), Lequal(Arg2,7 ))){
             Return ( Package(2 ){
                         0x3,
                         Unicode(" Slot3 x8")
                     }
                 )
          }
         }
             return(Buffer(){0})
  }
}
Scope( \_SB.PCI0.BR3D){
  Method ( _DSM, 4, NotSerialized, 0, UnknownObj, {BuffObj, IntObj, IntObj,PkgObj})
  {
        If (LEqual(Arg0, ToUUID ("E5C937D0-3553-4d7a-9117-EA4D19C3434D"))) {
          If (Land( Lequal(Arg1, 2 ), Lequal(Arg2,0 ))){
             return (Buffer() {0x80})
          }
          If (Land( Lequal(Arg1, 2), Lequal(Arg2,7 ))){
             Return ( Package(2 ){
                         0x3,
                         Unicode(" Slot3 x4")
                     }
                 )
          }
         }
             return(Buffer(){0})
  }
}
Scope( \_SB.PCI1.QR3A){
  Method ( _DSM, 4, NotSerialized, 0, UnknownObj, {BuffObj, IntObj, IntObj,PkgObj})
  {
        If (LEqual(Arg0, ToUUID ("E5C937D0-3553-4d7a-9117-EA4D19C3434D"))) {
          If (Land( Lequal(Arg1, 2 ), Lequal(Arg2,0 ))){
             return (Buffer() {0x80})
          }
          If (Land( Lequal(Arg1, 2), Lequal(Arg2,7 ))){
             Return ( Package(2 ){
                         0x2,
                         Unicode(" Slot2 x16")
                     }
                 )
          }
         }
             return(Buffer(){0})
  }
}
Scope( \_SB.PCI1.QR3C){
  Method ( _DSM, 4, NotSerialized, 0, UnknownObj, {BuffObj, IntObj, IntObj,PkgObj})
  {
        If (LEqual(Arg0, ToUUID ("E5C937D0-3553-4d7a-9117-EA4D19C3434D"))) {
          If (Land( Lequal(Arg1, 2 ), Lequal(Arg2,0 ))){
             return (Buffer() {0x80})
          }
          If (Land( Lequal(Arg1, 2), Lequal(Arg2,7 ))){
             Return ( Package(2 ){
                         0x4,
                         Unicode(" Slot4 x8")
                     }
                 )
          }
         }
             return(Buffer(){0})
  }
}
Scope( \_SB.PCI1.QR1A){
  Method ( _DSM, 4, NotSerialized, 0, UnknownObj, {BuffObj, IntObj, IntObj,PkgObj})
  {
        If (LEqual(Arg0, ToUUID ("E5C937D0-3553-4d7a-9117-EA4D19C3434D"))) {
          If (Land( Lequal(Arg1, 2 ), Lequal(Arg2,0 ))){
             return (Buffer() {0x80})
          }
          If (Land( Lequal(Arg1, 2), Lequal(Arg2,7 ))){
             Return ( Package(2 ){
                         0x4,
                         Unicode(" Slot4 x8")
                     }
                 )
          }
         }
             return(Buffer(){0})
  }
}
