#define BUILD_TOOL_GENERATED_PROTOCOL_TABLE_VERSION 1

typedef struct{
    EFI_GUID Guid;
    CHAR8 *Name;
} BUILD_TOOL_GENERATED_PROTOCOL_TABLE;

static BUILD_TOOL_GENERATED_PROTOCOL_TABLE BuildToolGeneratedProtocolTable[] = {

};

static UINTN NumberofElementsInBuildToolGeneratedProtocolTable = sizeof(BuildToolGeneratedProtocolTable)/sizeof(BuildToolGeneratedProtocolTable[0]);

static INT32 BuildToolGeneratedCompareProtocolGuid(CONST EFI_GUID *Guid1, CONST EFI_GUID *Guid2){
	UINT8 i;

	if (Guid1->Data1 != Guid2->Data1) return (Guid1->Data1 < Guid2->Data1) ? -1 : 1;
	if (Guid1->Data2 != Guid2->Data2) return Guid1->Data2 - Guid2->Data2;
	if (Guid1->Data3 != Guid2->Data3) return Guid1->Data3 - Guid2->Data3;

	for (i = 0; i<8; i++) {
		if (Guid1->Data4[i] != Guid2->Data4[i]) return Guid1->Data4[i] - Guid2->Data4[i];
	}
	return 0;
}

CHAR8* GetProtocolNameFromBuildToolGeneratedTable(CONST EFI_GUID *Guid){
    INTN Low = 0;
    INTN High = (INTN)(NumberofElementsInBuildToolGeneratedProtocolTable-1);
    
    while(Low<=High){
        INTN i;
        INT32 CompareResult;
        
        i = (Low+High)/2;
        CompareResult = BuildToolGeneratedCompareProtocolGuid(&BuildToolGeneratedProtocolTable[i].Guid,Guid);
        if ( CompareResult < 0 ) Low = i+1;
        else if ( CompareResult > 0 ) High = i-1;
        else return BuildToolGeneratedProtocolTable[i].Name;
    }
    return NULL;
}
