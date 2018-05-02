/** @file FitHook.c
    SW SMI hook.

**/
//*************************************************************************

#include <AmiDxeLib.h>
#include <Protocol/SmiFlash.h>
#include "token.h"

#define FIT_TABLE_OFFSET_START          (FV_FIT_BASE - FLASH_BASE)
#define FIT_TABLE_OFFSET_END            (FIT_TABLE_OFFSET_START + FIT_TABLE_SIZE)

/**
    This function is SW SMI hook that sets Flash Block Description
    type for AMI AFU utility.

    @param 
        SwSmiNum    - SW SMI value number
        Buffer      - Flash descriptor address

    @retval VOID

**/

VOID AppendFvDataToAFU_UpdateBlockTypeId (
    IN UINT8  SwSmiNum,
    IN UINT64 Buffer )
{
    BLOCK_DESC *BlockDesc;
    UINTN  i;

    // return if SW SMI value is not "Get Flash Info"
    if (SwSmiNum != SMIFLASH_GET_FLASH_INFO)
        return;

    BlockDesc = (BLOCK_DESC*)&((INFO_BLOCK*)Buffer)->Blocks;

    for (i = 0; i < ((INFO_BLOCK*)Buffer)->TotalBlocks; i++) {

        TRACE((TRACE_ALWAYS,"AppendFvDataToAFU_UpdateBlockTypeId: %08X(%08X), Block %08X\n", FIT_TABLE_OFFSET_START, FIT_TABLE_OFFSET_END, BlockDesc[i].StartAddress));

        if (BlockDesc[i].StartAddress < FIT_TABLE_OFFSET_START)
            continue;

        if (BlockDesc[i].StartAddress >= FIT_TABLE_OFFSET_END)
            continue;

        TRACE((TRACE_ALWAYS,"AppendFvDataToAFU_UpdateBlockTypeId: Found Blocks %08X\n",BlockDesc[i].StartAddress));

        BlockDesc[i].Type = BOOT_BLOCK;
    }
}
