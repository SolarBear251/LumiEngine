/**
 * @file       Allocator.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-07
 *
 * @brief    Methods definitions of Allocator
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#include <lumi/core/Allocator.h>

#include <cassert>
#include <cstring>

void lumi::Allocator::Reset(size_t dataSize, size_t pageSize, size_t align) {
    // Make sure the alignment is 2^n
    assert(align > 0 && ((align & (align - 1))) == 0);
    // Clear previous allocated memory
    FreeAll();
    // Compute size parameters
    _dataSize = dataSize;
    _pageSize = pageSize;
    size_t min_size =
        sizeof(BlockHeader) > _dataSize ? sizeof(BlockHeader) : _dataSize;
    _blockSize = __ALIGN(min_size, align);
    _alignSize = _blockSize - min_size;
    _blocksPerPage = (_pageSize - sizeof(PageHeader)) / _blockSize;
}

void* lumi::Allocator::Malloc() {
    // If no free blocks
    if (!_freeList) {
        // Allocate a new page
        PageHeader* newPage =
            reinterpret_cast<PageHeader*>(new uint8_t[_pageSize]);
        ++_pages;
        _blocks += _blocksPerPage;
        _freeBlocks += _blocksPerPage;

#ifdef _DEBUG
        // Fill the page with free pattern
        FillPage(newPage, PATTERN_FREE);
#endif
        // Insert the new page to front
        if (_pageList) {
            newPage->next = _pageList;
        }
        _pageList = newPage;
        // Insert the new blocks into free list
        BlockHeader* block = newPage->Blocks();
        _freeList = block;
        for(size_t i = 0; i < _blocksPerPage; ++i) {
            block->next = NextBlock(block);
            block = block->next;
        }
        block->next = nullptr;
    }
    // Get 1 free block
    BlockHeader* freeBlock = _freeList;
    _freeList = _freeList->next;
    --_freeBlocks;

#ifdef _DEBUG
    // Fill the block with allocated pattern
    FillBlock(freeBlock, PATTERN_ALLOC);
#endif

    return reinterpret_cast<void*>(freeBlock);
}

void lumi::Allocator::Free(void* p) {
    BlockHeader* block = reinterpret_cast<BlockHeader*>(p);

#ifdef _DEBUG
    // Fill the block with free pattern
    FillBlock(block, PATTERN_FREE);
#endif
    // Insert the block into the front of the free list
    block->next = _freeList;
    _freeList = block;
    ++_freeBlocks;
}

void lumi::Allocator::FreeAll() {
    PageHeader *page = _pageList;
    while (page) {
        PageHeader *cur = page;
        page = page->next;
        delete[] reinterpret_cast<uint8_t*>(cur);
    }

    _pageList   = nullptr;
    _freeList   = nullptr;
    _pages      = 0;
    _blocks     = 0;
    _freeBlocks = 0;
}

#ifdef _DEBUG
void lumi::Allocator::FillPage(PageHeader* page, uint8_t pattern) {
    page->next = nullptr;
    BlockHeader *block = page->Blocks();
    for (auto i = 0; i < _blocksPerPage; ++i) {
        FillBlock(block, pattern);
        block = NextBlock(block);
    }
}

void lumi::Allocator::FillBlock(BlockHeader* page, uint8_t pattern) {
    // Fill header and data
    size_t validSize = _blockSize - _alignSize;
    std::memset(page, pattern, validSize);
    // Fill alignment zone
    std::memset(reinterpret_cast<uint8_t*>(page) + validSize, 
                PATTERN_ALIGH, _alignSize);
}

#endif