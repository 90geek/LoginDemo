#define PEI_GET_VAR_LIST 
#define PEI_GET_NEXT_VAR_NAME_LIST 
#define GET_VAR_LIST 
#define GET_NEXT_VAR_NAME_LIST 
#define SET_VAR_LIST 
#define IS_MFG_MODE_LIST 
#define IS_RESET_CONFIG_MODE_LIST IsIpmiCmosClear, IsPchRtcReset,
#define IS_DEFAULT_CONFIG_MODE_LIST IsPchRtcReset, IsIpmiCmosClear,
#define NVRAM_PRESERVE_VARIABLES_LIST  {L"Setup", { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }}, {L"AMITSESetup", { 0xc811fa38, 0x42c8, 0x4579, 0xa9, 0xbb, 0x60, 0xe9, 0x4e, 0xdd, 0xfb, 0x34 }},