/**
 * @file       MemoryManager.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-07
 *
 * @brief    Methods definitions for MemoryManager
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#include "core/MemoryManager.h"
#include <memory>

namespace Lumi {

static constexpr uint32_t BLOCKSIZES[] = {
    // 4-increments
    4,  8,  12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
    52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,
    // 32-increments
    128, 160, 192, 224, 256, 288, 320, 352, 384, 
    416, 448, 480, 512, 544, 576, 608, 640,
    // 64-increments
    704, 768, 832, 896, 960, 1024
};
// Number of block sizes
static constexpr uint32_t BLOCKSIZESNUM =
    sizeof(BLOCKSIZES) / sizeof(BLOCKSIZES[0]);
// Max block size
static constexpr uint32_t MAXBLOCKSIZE = BLOCKSIZES[BLOCKSIZESNUM - 1];

static constexpr uint32_t PAGESIZE = 8192;
static constexpr uint32_t ALIGN = 4;

// Definition of static variable in MemoryManager
size_t*     MemoryManager::_blockSizeLookup;
Allocator*  MemoryManager::_allocators;

}; ///< namespace Lumi

int Lumi::MemoryManager::Initialize() {
    // Initialize only once
    static bool hasInit = false;
    if (hasInit) return 0;

    // Block size lookup table
    _blockSizeLookup = new size_t[MAXBLOCKSIZE + 1];
    size_t index = 0;
    for (size_t i = 0; i <= MAXBLOCKSIZE; ++i) {
        if (i > BLOCKSIZES[index]) ++index;
        _blockSizeLookup[i] = index;
    }
    // Allocators
    _allocators = new Allocator[BLOCKSIZESNUM];
    for (size_t i = 0; i < BLOCKSIZESNUM; ++i) {
        _allocators[i].Reset(BLOCKSIZES[i], PAGESIZE, ALIGN);
    }

    hasInit = true;
    return 0;
}

void Lumi::MemoryManager::Finalize() {
    delete[] _blockSizeLookup;
    delete[] _allocators;
}

void Lumi::MemoryManager::Tick() {

}

Lumi::Allocator* Lumi::MemoryManager::LookupAllocator(size_t size) {
    if (size <= MAXBLOCKSIZE) {
        return &_allocators[_blockSizeLookup[size]];
    } else {
        return nullptr;
    }
}

void* Lumi::MemoryManager::Malloc(size_t size) {
    Allocator* allocator = LookupAllocator(size);
    if (allocator) {
        return allocator->Malloc();
    } else {
        return std::malloc(size);
    }
}

void Lumi::MemoryManager::Free(void* p, size_t size) {
    Allocator* allocator = LookupAllocator(size);
    if (allocator) {
        allocator->Free(p);
    } else {
        std::free(p);
    }
}

