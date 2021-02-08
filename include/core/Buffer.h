/**
 * @file       Buffer.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-08
 * 
 * @brief    Data buffer
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <cstdint>

namespace Lumi {

class Buffer
{
public:
    uint8_t* data;      ///< Pointer to the buffer
    size_t size;        ///< Size of the buffer

    /// Constructors
    Buffer() = default;
    Buffer(size_t size) : data(new uint8_t[size]), size(size) {}
    /// Copy and destructor
    Buffer(const Buffer& rhs) = delete;
    Buffer(Buffer&& rhs) noexcept {
        data = rhs.data;
        size = rhs.size;
        rhs.data = nullptr;
        rhs.size = 0;
    }
    Buffer& operator=(const Buffer& rhs) = delete;
    Buffer& operator=(Buffer&& rhs) noexcept {
        if (data) delete[] data;
        data = rhs.data;
        size = rhs.size;
        rhs.data = nullptr;
        rhs.size = 0;
        return *this;
    }
    ~Buffer() {
        if (data) delete[] data;
    }

    /**
     * @brief    Move the data away from this buffer.
     * 
     * @return   uint8_t*   The data being moved
     */
    uint8_t* Move() {
        uint8_t* res = data;
        data = nullptr;
        size = 0;
        return res;
    }

    /**
     * @brief    Discard previous data and set new data
     * 
     * @param    data        New data
     * @param    size        Size of new data
     * 
     */
    void Set(uint8_t* data, size_t size) {
        if(this->data) delete[] this->data;
        this->data = data;
        this->size = size;
    }

}; ///< class Buffer


}; ///< namespace Lumi