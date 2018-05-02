#pragma pack(1)
typedef struct{
  UINT8 Numlock;
  //ZA0035>>>
#if Foxconn_SUPPORT
  UINT8 AMISilentBoot;
#endif
//ZA0035<<<
  #define SETUP_DATA_DEFINITION
  #include <SetupDefinitions.h>
  #undef SETUP_DATA_DEFINITION
} SETUP_DATA;
#pragma pack()

