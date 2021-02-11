/**
 * @file       Allocator.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-07
 * 
 * @brief    Header for allocator. Not thread-safe right now.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <cstddef>
#include <cstdint>

/// Round up alignment
#define __ALIGN(x, a)  ( ((x) + ((a) - 1)) & ~((a) - 1) )

namespace Lumi {

/// Header of block
class BlockHeader {
public:
    BlockHeader* next;     ///< Next free block.
}; ///< class BlockHeader

/// Header of page
class PageHeader {
public:
    PageHeader* next;      ///< Next page.

    /**
     * @brief    Get pointer to the following blocks.
     * 
     * @return   BlockHeader* 
     */
    BlockHeader* Blocks() {
        return reinterpret_cast<BlockHeader*>(this + 1);
    }
}; ///< class PageHeader

class Allocator {
public:
    constexpr static uint8_t PATTERN_ALIGH = 0xFC;
    constexpr static uint8_t PATTERN_ALLOC = 0xFD;
    constexpr static uint8_t PATTERN_FREE  = 0xFE;

private:
    /// Page list
    PageHeader*   _pageList;
    /// Free block List
    BlockHeader*  _freeList;
    /// Size parameters
    size_t      _dataSize;
    size_t      _pageSize;
    size_t      _blockSize;
    size_t      _alignSize;
    size_t      _blocksPerPage;
    /// Statistics
    size_t      _pages;
    size_t      _blocks;
    size_t      _freeBlocks;

public:
    /// Constructors
    Allocator() = default;
    Allocator(size_t dataSize, size_t pageSize, size_t align)
        : _pageList(nullptr), _freeList(nullptr) {
        Reset(dataSize, pageSize, align);
    }
    /// Destructor
    virtual ~Allocator() { FreeAll(); }
    // Disable copy & assignment
    Allocator(const Allocator& rhs) = delete;
    Allocator& operator=(const Allocator& rhs) = delete;

    /**
     * @brief    Reset the config of current allocator.
     *
     * @param    dataSize    Byte size of single data
     * @param    pageSize    Byte size of page
     * @param    align       Byte alignment, must be 2^n
     *
     */
    void Reset(size_t dataSize, size_t pageSize, size_t align);

    /**
     * @brief    Allocate memory for a single block with current config.
     * 
     * @return   void*      Pointer to a free block.
     */
    void* Malloc();

    /**
     * @brief    Free the allocated memory given by input pointer.
     *
     * @param    p          Pointer to allocated memory.
     *
     */
    void Free(void* p);

    /**
     * @brief    Free all allocated memory.
     * 
     */
    void FreeAll();

private:
    /**
     * @brief    Get next block by address computation
     * 
     * @param    block          Current block
     * 
     * @return   BlockHeader*   Next block
     */
    BlockHeader* NextBlock(BlockHeader* block) {
        return reinterpret_cast<BlockHeader*>(
            reinterpret_cast<uint8_t*>(block) + _blockSize);
    }

#ifdef _DEBUG
    /**
     * @brief    Fill the page with debug pattern
     * 
     * @param    page        The page to be filled
     * @param    pattern     The pattern to fill
     * 
     */
    void FillPage(PageHeader* page, uint8_t pattern);

    /**
     * @brief    Fill the block with debug pattern
     *
     * @param    block       The block to be filled
     * @param    pattern     The pattern to fill
     *
     */
    void FillBlock(BlockHeader* block, uint8_t pattern);
#endif

}; ///< class Allocator

}; ///< namespace Lumi