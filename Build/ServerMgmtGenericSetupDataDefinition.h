#include<Token.h>
#pragma pack(1)
typedef struct{
  UINT8        BmcSupport;
#if BMC_INIT_DELAY
  UINT8        WaitForBmc;
#endif
#if BMC_TIMEZONE_SUPPORT
  CHAR16    TimeZone[6];
#endif
  #define SERVER_MGMT_CONFIGURATION_DATA_DEFINITION
  #include <ServerMgmtSetupDefinitions.h>
  #undef SERVER_MGMT_CONFIGURATION_DATA_DEFINITION
} SERVER_MGMT_CONFIGURATION_DATA;
#pragma pack()

