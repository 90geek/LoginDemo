#define BUILD_TOOL_GENERATED_PPI_TABLE_VERSION 1

typedef struct{
    EFI_GUID Guid;
    CHAR8 *Name;
} BUILD_TOOL_GENERATED_PPI_TABLE;

static BUILD_TOOL_GENERATED_PPI_TABLE BuildToolGeneratedPpiTable[] = {
	{{ 0x3cd652b4, 0x6d33, 0x4dce, { 0x89, 0xdb, 0x83, 0xdf, 0x97, 0x66, 0xfc, 0xca }}, "EfiVectorHandoffInfo"},
	{{ 0xae933e1c, 0xcc47, 0x4e38, { 0x8f, 0x0e, 0xe2, 0xf6, 0x1d, 0x26, 0x05, 0xdf }}, "EfiPeiSmmCommunication"}
};

static UINTN NumberofElementsInBuildToolGeneratedPpiTable = sizeof(BuildToolGeneratedPpiTable)/sizeof(BuildToolGeneratedPpiTable[0]);

static INT32 BuildToolGeneratedComparePpiGuid(CONST EFI_GUID *Guid1, CONST EFI_GUID *Guid2){
	UINT8 i;

	if (Guid1->Data1 != Guid2->Data1) return (Guid1->Data1 < Guid2->Data1) ? -1 : 1;
	if (Guid1->Data2 != Guid2->Data2) return Guid1->Data2 - Guid2->Data2;
	if (Guid1->Data3 != Guid2->Data3) return Guid1->Data3 - Guid2->Data3;

	for (i = 0; i<8; i++) {
		if (Guid1->Data4[i] != Guid2->Data4[i]) return Guid1->Data4[i] - Guid2->Data4[i];
	}
	return 0;
}

CHAR8* GetPpiNameFromBuildToolGeneratedTable(CONST EFI_GUID *Guid){
    INTN Low = 0;
    INTN High = (INTN)(NumberofElementsInBuildToolGeneratedPpiTable-1);
    
    while(Low<=High){
        INTN i;
        INT32 CompareResult;
        
        i = (Low+High)/2;
        CompareResult = BuildToolGeneratedComparePpiGuid(&BuildToolGeneratedPpiTable[i].Guid,Guid);
        if ( CompareResult < 0 ) Low = i+1;
        else if ( CompareResult > 0 ) High = i-1;
        else return BuildToolGeneratedPpiTable[i].Name;
    }
    return NULL;
}
