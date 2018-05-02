#define PEI_INIT_LIST  SerialStatusInit,
#define DXE_INIT_LIST  SerialStatusInit, ConOutCpInit, DataHubInit,
#define PEI_STRING_LIST   SerialOutput,
#define DXE_STRING_LIST   SerialOutput,
#define RT_STRING_LIST   SerialOutput,
#define SMM_STRING_LIST   SerialOutput,
#define PEI_SIMPLE_LIST   CheckPointStatus, BeepStatus,
#define DXE_SIMPLE_LIST   CheckPointStatus, BeepStatus,
#define RT_SIMPLE_LIST   CheckPointStatus,
#define SMM_SIMPLE_LIST   CheckPointStatus,
#define PEI_MISC_LIST   BeepService,
#define DXE_MISC_LIST   BeepService, DataHubStatusCode,
#define RT_MISC_LIST   
#define SMM_MISC_LIST   
#define PEI_CHECKPOINT_LIST   Port80Checkpoint,
#define DXE_CHECKPOINT_LIST   Port80Checkpoint, ConOutCheckpoint,
#define RT_CHECKPOINT_LIST   Port80Checkpoint,
#define SMM_CHECKPOINT_LIST   Port80Checkpoint,
#define PEI_ERROR_CODE_ACTIONS   
#define RT_ERROR_CODE_ACTIONS   
#define SMM_ERROR_CODE_ACTIONS   
#define DXE_ERROR_CODE_ACTIONS   

