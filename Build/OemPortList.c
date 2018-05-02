#include <Pei.h>
typedef BOOLEAN (ONE_PARAM_FUNCTION)(
    IN EFI_PEI_SERVICES **PeiServices
);

extern ONE_PARAM_FUNCTION ForceRecovery, EndOfOneParamList;

ONE_PARAM_FUNCTION* IsRecoveryList[] = {ForceRecovery, NULL};

