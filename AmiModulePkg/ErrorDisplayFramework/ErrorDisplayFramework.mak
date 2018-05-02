Prepare : ErrorDisplayFiles

ErrorDisplayFiles : $(BUILD_DIR)/ErrorDisplayFramework.inf $(BUILD_DIR)/ErrorDisplayFrameworkPlugins.h 
#    $(ECHO) $(ERROR_LOOKUP_TABLE)


## Create ErrorDisplayPlugins.h here.  This will include the table of errors and 
## the elink function lists
$(BUILD_DIR)/ErrorDisplayFrameworkPlugins.h : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"#define ERROR_LOOKUP_TABLE_PLUGINS $(ERROR_LOOKUP_TABLE) $(EOL)\
$(EOL)\
#define OemPreDisplayFunction $(OemPreDisplayFunction)$(EOL)\
$(EOL)\
#define DisplayErrorFunction $(OemDisplayErrorFunction)$(EOL)\
$(EOL)\
#define OemPostDisplayFunction $(OemPostDisplayFunction)$(EOL)"\
> $(BUILD_DIR)/ErrorDisplayFrameworkPlugins.h
