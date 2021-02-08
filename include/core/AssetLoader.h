/**
 * @file       AssetLoader.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-08
 * 
 * @brief    Header for asset loader
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include "interface/IRuntimeModule.h"
#include "Buffer.h"

#include <vector>
#include <string>

namespace Lumi {

class AssetLoader : implements IRuntimeModule {
public:
    /// File open mode
    enum AssetOpenMode {
        ASSET_OPEN_TEXT = 0,
        ASSET_OPEN_BINARY = 1,
    };
    /// File seek mode
    enum AssetSeekMode {
        ASSET_SEEK_SET = 0,
        ASSET_SEEK_CUR = 1,
        ASSET_SEEK_END = 2,
    };

private:
    /// Paths to search for the file
    std::vector<std::string> _searchPaths;

public:
    /// Constructors and destructors
    AssetLoader() = default;
    virtual ~AssetLoader() = default;
    /// Override functions
    virtual int Initialize() override { return 0; }
    virtual void Finalize() override {}
    virtual void Tick() override {}

    /**
     * @brief    Add a file searching path related to project root directory.
     *
     * @param    path        Path to search for the file
     *
     * @return   true        Succeed to add
     * @return   false       Fail to add
     */
    bool AddSearchPath(const char* path) {
        for (const auto &val : _searchPaths) {
            if (val == path) return true;
        }
        _searchPaths.emplace_back(path);
        return true;
    }

    /**
     * @brief    Remove a file searching path
     *
     * @param    path        Path to search for the file
     *
     * @return   true        Succeed to remove
     * @return   false       Succeed to remove
     */
    bool RemoveSearchPath(const char* path) {
        for (auto it = _searchPaths.begin(); it != _searchPaths.end(); ++it) {
            if(*it == path) {
                _searchPaths.erase(it);
                break;
            }
        }
        return true;
    }

    /**
     * @brief    Clear all file searching path
     *
     */
    void ClearSearchPath() { _searchPaths.clear(); }

    /**
     * @brief    Check whether the file exists.
     * 
     * @param    filename    Name of the file
     * 
     * @return   true        File exist
     * @return   false       File not exist
     */
    virtual bool Exists(const char* filename);

    /**
     * @brief    Open the file
     *
     * @param    filename    Name of the file
     * @param    mode        Enum of file open mode 
     *
     * @return   void*       Pointer to the file
     */
    virtual void* Open(const char* filename, AssetOpenMode mode);

    /**
     * @brief    Open the file and read the data
     *
     * @param    filename    Name of the file
     * @param    mode        Enum of file open mode
     *
     * @return   Buffer      Data buffer
     */
    virtual Buffer OpenAndRead(const char* filename, AssetOpenMode mode);

    /**
     * @brief    Read the file and store the data into buffer
     * 
     * @param    file        Pointer to file
     * @param    buffer      Reference of the buffer
     * 
     * @return   size_t      Size of the file
     */
    virtual size_t Read(void* file, Buffer &buffer) {
        if (!file) {
            fprintf(stderr, "Reading a null file pointer.\n");
            return 0;
        }
        return fread(buffer.data, buffer.size, 1, static_cast<FILE*>(file));
    }

    /**
     * @brief    Close the file
     * 
     * @param    file        Pointer to file
     * 
     */
    virtual void Close(void* file) { fclose(static_cast<FILE*>(file)); }

    /**
     * @brief    Get the size of the file
     *
     * @param    file        Pointer to file
     *
     * @return   size_t      Size of the file
     */
    virtual size_t SizeOf(void* file) {
        FILE *_file = static_cast<FILE*>(file);
        // Record original position
        long pos = ftell(_file);
        // Move the pointer to the end
        fseek(_file, 0, SEEK_END);
        size_t size = ftell(_file);
        // Restore the file pointer
        fseek(_file, pos, SEEK_SET);

        return size;
    }

    /**
     * @brief    Modify the I/O pointer in the file
     * 
     * @param    file        File pointer
     * @param    offset      Offset related to the seek mode
     * @param    mode        Enum of file seek mode
     * 
     * @return   int         Result code
     */
    virtual int Seek(void* file, long offset, AssetSeekMode mode) {
        return fseek(static_cast<FILE*>(file), offset, mode);
    }

    /**
     * @brief    Open the file and read the data into std::string
     *
     * @param    filename       Name of the file
     *
     * @return   std::string    String of file data
     */
    std::string OpenAndReadStr(const char* filename) {
        Buffer buffer = OpenAndRead(filename, ASSET_OPEN_TEXT);
        if (buffer.data && buffer.size > 0) {
            return reinterpret_cast<char*>(buffer.data); 
        } else {
            return "";
        }
    }

}; ///< class AssetLoader

extern AssetLoader* gAssetLoader;

}; ///< namespace Lumi