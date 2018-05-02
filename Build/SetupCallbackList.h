
/// Structure used to define a callback entry
typedef struct _AMI_CALLBACK_LIST_ENTRY
{
    LIST_ENTRY Link;                        ///< Linked list entry
    EFI_QUESTION_ID QuestionId;             ///< Question ID associated with this callback
    AMI_SETUP_CALLBACK_FUNCTION Function;   ///< Callback function pointer
} AMI_CALLBACK_LIST_ENTRY;

/// Structure used to define a string initialization entry
typedef struct _AMI_STRING_INITIALIZATION_ENTRY
{
    LIST_ENTRY Link;                        ///< Linked list entry
    AMI_STRING_INIT_FUNCTION Function;      ///< String initialization function pointer
} AMI_STRING_INITIALIZATION_ENTRY;

/// Structure used to define a extract config handler
typedef struct _AMI_EXTRACT_CONFIG_ENTRY
{
    LIST_ENTRY Link;                        ///< Linked list entry
    EFI_HII_ACCESS_EXTRACT_CONFIG Function; ///< Hii Access extract config function
} AMI_EXTRACT_CONFIG_ENTRY;

/// Structure used to define a route config handler
typedef struct _AMI_ROUTE_CONFIG_ENTRY
{
    LIST_ENTRY Link;                        ///< Linked list entry
    EFI_HII_ACCESS_ROUTE_CONFIG Function;   ///< Hii Access route config fucntion
} AMI_ROUTE_CONFIG_ENTRY;

// Functions linked into the SetupInstallHiiPackagesHook eLink
VOID RegisterSetupItems(VOID);

#define SETUP_MODULE_POST_INSTALL_HII_PACKAGES_HOOK RegisterSetupItems,

// Compatability setup strings init functions
#define SETUP_STRING_INIT_LIST SetPsuPolicy,SavePsuState,OemInitAST2400SetupStrings,SioSetupStringsInit,InitPciBusStrings,InitTerminalStrings,InitCsmStrings,InitHddSecurityStrings,InitNvmeStrings,InitTcgStrings,InitUSBStrings,InitHomeWorkStrings,FixedBootOrderStringInit,InitNbStrings,

// Compatability callback functions list
#define SETUP_ITEM_CALLBACK_LIST ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,CSM_POLICY_LAUNCH_KEY,CsmPolicyLaunchCallback),ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS, 0, USB_DEVICES_ENABLED_REFRESH_KEY, UpdateUSBStrings),ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,ALI_CONFIG_KEY,AliConfig_CallBack),

