/** @file
  x64 Virtual Memory Management Services in the form of an IA-32 driver.  
  Used to establish a 1:1 Virtual to Physical Mapping that is required to
  enter Long Mode (x64 64-bit mode).

  While we make a 1:1 mapping (identity mapping) for all physical pages 
  we still need to use the MTRR's to ensure that the cachability attributes
  for all memory regions is correct.

  The basic idea is to use 2MB page table entries where ever possible. If
  more granularity of cachability is required then 4K page tables are used.

  References:
    1) IA-32 Intel(R) Architecture Software Developer's Manual Volume 1:Basic Architecture, Intel
    2) IA-32 Intel(R) Architecture Software Developer's Manual Volume 2:Instruction Set Reference, Intel
    3) IA-32 Intel(R) Architecture Software Developer's Manual Volume 3:System Programmer's Guide, Intel

Copyright (c) 2006 - 2011, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/  

#include "DxeIpl.h"
#include "VirtualMemory.h"

//Aptio V Server Override Start: Use 2MB Page tables below 4GB

/**

    Gets the number of pages to allocate for paging.Unlimited if 1 GB page tables is supported.
    Otherwise, limit 512 MB address space.

    @param  NumberMemoryBits  Number of memory bits to map.
    @return Number of pages to requried for allocation

**/

UINT32 GetPgTblNumPages(
    IN UINT8 NumberMemoryBits
)
{
    BOOLEAN GigPageSupport = FALSE;
    UINT32  RegEdx;
    UINT32  NumPages;

    if (PcdGetBool(PcdUse1GPageTable)) {
        AsmCpuid(0x80000001, NULL, NULL, NULL, &RegEdx);
        GigPageSupport = !!(RegEdx & BIT26);
    }
    
    //Limit number of memory bits to 39 (512 GB) if no support for GB page-tables.
    if (!GigPageSupport && NumberMemoryBits > 39) NumberMemoryBits = 39;
    
    if (GigPageSupport) {
        //1 page for PML4E Table.
        //4 page for for Directory. First 4GB of 2MB pages.
        //1 Page for Page-Table Entries for 1st 2MB of 4k pages.        
        NumPages = 6;

        //Allocate pages for directory pointers.
        NumPages += 1 << (NumberMemoryBits > 39 ? NumberMemoryBits - 39 : 0);
   } else {
        //Allocate at least 7 pages to cover Identity Mapping for 32 bits.
        //1 page for PML4E Table
        //1 page for Page-Directory Pointer
        //Pages for Directory allocated later--one for each directory.
        //1 page for Page-Table Entries for 1st 2MB. This must be 4k blocks.
        NumPages = 3;
    
        //Allocate pages for page directories.
        NumPages += 1 << (NumberMemoryBits - 30);
    }
    return NumPages;
}

/**

    Fills a provided page table with an identity map.

    @param  NumberMemoryBits  Number of memory bits to map.
    @param  PageTable         Page table to fill

**/

VOID FillPgTbl(
    IN UINT8  NumberMemoryBits,
    IN VOID   *PageTable
)
{
    BOOLEAN GigPageSupport = FALSE;
    UINT32 RegEdx;
    UINT64 *Pml4eTable = (UINT64*)PageTable;
    UINT64 *PdpTable   = (UINT64*)((UINT8*)PageTable + 0x1000);
    UINT64 *PDir;
    UINT64 *PTableEntry;
    UINT32 NumPml4Entries;
    UINT32 NumPgDirPtrEntries;
    UINT32 NumPgDirEntries;
    UINT32 i;

    if (PcdGetBool(PcdUse1GPageTable)) {
        AsmCpuid(0x80000001, NULL, NULL, NULL, &RegEdx);
        GigPageSupport = !!(RegEdx & BIT26);
    }
    
    //Limit number of memory bits to 39 (512 GB) if no support for GB page-tables.
    if (!GigPageSupport && NumberMemoryBits > 39) NumberMemoryBits = 39;

    // Update Page-Map Level-4 tables.
    NumPml4Entries =  1 << (NumberMemoryBits > 39 ? NumberMemoryBits - 39 : 0);
    for (i = 0; i < NumPml4Entries; ++i) Pml4eTable[i] = BIT0 + BIT1 + (i << 12) + (UINT64)(UINTN)PdpTable;
    MemSet(Pml4eTable + i, 4096 - 8 * i, 0);    //Clear unused entries.

    //Update Page Pointer Directories.
    NumPgDirPtrEntries = 1 << (NumberMemoryBits - 30);
    PDir = PdpTable + (NumPgDirPtrEntries <= 512 ? 512 : NumPgDirPtrEntries);
    if (GigPageSupport) {
        //1st 4 pages must point to a Page directory
        PdpTable[0] = BIT0 + BIT1 + (0 << 12) + (UINT64)(UINTN)PDir;
        PdpTable[1] = BIT0 + BIT1 + (1 << 12) + (UINT64)(UINTN)PDir;
        PdpTable[2] = BIT0 + BIT1 + (2 << 12) + (UINT64)(UINTN)PDir;
        PdpTable[3] = BIT0 + BIT1 + (3 << 12) + (UINT64)(UINTN)PDir;
        for (i = 4; i <  NumPgDirPtrEntries; ++i)
            PdpTable[i] = BIT0 + BIT1 + BIT7 + Shl64(i, 30);
    } else {
        for (i = 0; i <  NumPgDirPtrEntries; ++i)
            PdpTable[i] = BIT0 + BIT1 + (i << 12) + (UINT64)(UINTN)PDir;
    }
    if (i < 512) MemSet(PdpTable + i, 4096 - 8 * i, 0); //Clear unused entries.

    //Initialize Page Directores.
    if (GigPageSupport) NumPgDirEntries = 2048;  //First 4 GB
    else NumPgDirEntries = 1 << (NumberMemoryBits - 21); //Number of 2MB pages.
    PTableEntry = PDir + NumPgDirEntries;
    PDir[0] = BIT0 + BIT1 + (UINT64)(UINTN)PTableEntry;  //4K Page Table for first 2MB.
    for(i = 1; i < NumPgDirEntries; ++i) PDir[i] = 0x83 + Shl64(i, 21); 

    //Initialize 4k page entries for first 2MB.
    for(i = 0; i < 512; ++i) PTableEntry[i] = BIT0 + BIT1 + (i << 12);
}


/**
  Allocates and fills in the Page Directory and Page Table Entries to
  establish a 1:1 Virtual to Physical mapping.

  @param  NumberOfProcessorPhysicalAddressBits  Number of processor address bits 
                                                to use. Limits the number of page 
                                                table entries  to the physical 
                                                address space. 

  @return The address of 4 level page map.

**/

UINTN
CreateIdentityMappingPageTables (
  VOID
  )
{  
  UINT32    RegEax;
  UINT8     PhysicalAddressBits;
  VOID      *PageMap;
  UINT32    TotalPagesNum;
  VOID      *Hob;

  //
  // Get physical address bits supported.
  //
  Hob = GetFirstHob (EFI_HOB_TYPE_CPU);
  if (Hob != NULL) {
    PhysicalAddressBits = ((EFI_HOB_CPU *) Hob)->SizeOfMemorySpace;
  } else {
    AsmCpuid (0x80000000, &RegEax, NULL, NULL, NULL);
    if (RegEax >= 0x80000008) {
      AsmCpuid (0x80000008, &RegEax, NULL, NULL, NULL);
      PhysicalAddressBits = (UINT8) RegEax;
    } else {
      PhysicalAddressBits = 36;
    }
  }

  //
  // IA-32e paging translates 48-bit linear addresses to 52-bit physical addresses.
  //
  ASSERT (PhysicalAddressBits <= 52);
  if (PhysicalAddressBits > 48) {
    PhysicalAddressBits = 48;
  }

  TotalPagesNum = GetPgTblNumPages(PhysicalAddressBits);
  PageMap = AllocateRuntimePages(TotalPagesNum); //AptioV server override: Taken from BP WW 47
  ASSERT (PageMap != 0);

  FillPgTbl(PhysicalAddressBits, PageMap);

  return (UINTN)PageMap;
}

//Aptio V Server Override End: Use 2MB Page tables below 4GB
