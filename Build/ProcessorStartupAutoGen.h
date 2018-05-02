#include <PiPei.h>

 typedef void (BIST_LIST)(void *);
 extern BIST_LIST PS_GetBist, EndOfOneParamList;
 BIST_LIST* BistList[] = {PS_GetBist, NULL};

 typedef void (SEC_ELINK_LIST)();
 extern SEC_ELINK_LIST  EndOfNoParamList;
 SEC_ELINK_LIST* SecElinkList[] = { NULL};

 typedef EFI_PEI_PPI_DESCRIPTOR* (RET_PPI_DESC_FUNC)();
 extern RET_PPI_DESC_FUNC  EndOfAddPpiList;
 RET_PPI_DESC_FUNC *RetPpiList[] = { NULL}; 
