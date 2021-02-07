/**
 * @file       MemoryManager.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-07
 * 
 * @brief    Header for memory manager. Not thread-safe right now.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include "Allocator.h"
#include "interface/IRuntimeModule.h"
#include <new>

namespace Lumi {

class MemoryManager : implements IRuntimeModule {
private:
    /// Lookup table for block size --> index of BLOCKSIZE array
    static size_t* _blockSizeLookup;
    /// Allocators of diffrent block size
    static Allocator* _allocators;

public:
    /// Constructors and Destructors
    MemoryManager() = default;
    virtual ~MemoryManager() {}

    /// Override functions
    virtual int Initialize() override;
    virtual void Finalize() override;
    virtual void Tick() override;

    /**
     * @brief    Allocate memory with certain size.
     * 
     * @param    size        Request size
     * 
     * @return   void*       Pointer to allocated memory
     */
    void* Malloc(size_t size);

    /**
     * @brief    Free allocated memory with certain size.
     *
     * @param    p           Pointer to allocated memory
     * @param    size        Size of the memory
     *
     */
    void Free(void* p, size_t size);

    /**
     * @brief    An implementation of operator new
     *
     * @tparam   T           Typename
     * @tparam   Arguments   Constructor parameters types
     *
     * @param    parameters  Constructor parameters
     *
     * @return   T*     Allocated new object
     */
    template <typename T, typename... Arguments>
    T* New(Arguments... parameters) {
        return new (Malloc(sizeof(T))) T(parameters...);
    }

    /**
     * @brief    An implementation of operator delete
     *
     * @tparam   T           Typename
     *
     * @param    p           Allocated object
     *
     */
    template <typename T>
    void Delete(T* p) {
        p->~T();
        Free(p, sizeof(T));
    }

private:
    /**
     * @brief    Find the allocator for request size.
     * 
     * @param    size        Request size
     * 
     * @return   Allocator*  Matched allocator
     */
    static Allocator* LookupAllocator(size_t size);


}; ///< class MemoryManager

}; ///< namespace Lumi