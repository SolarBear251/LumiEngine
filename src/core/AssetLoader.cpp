/**
 * @file       AssetLoader.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-08
 *
 * @brief    Methods definitions of AssetLoader
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#include <lumi/core/AssetLoader.h>

bool lumi::AssetLoader::Exists(const char* filename) {
    void* file = Open(filename, ASSET_OPEN_BINARY);
    if (file) {
        Close(file);
        return true;
    } else {
        return false;
    }
}

void* lumi::AssetLoader::Open(const char* filename, AssetOpenMode mode) {
    std::string upPath;     ///< Prefix
    std::string fullPath;

    // Loop for N times up the hierarchy
    // to find the file at each level
    constexpr int N = 10;
    for (int i = 0; i < N; ++i) {
        auto it = _searchPaths.begin();
        bool looping = true;
        while (looping) {
            fullPath = upPath;
            if (it != _searchPaths.end()) {
                fullPath += *it + "/asset/";
                ++it;
            } else {
                fullPath += "asset/";
                looping = false;
            }
            fullPath += filename;

            FILE* file = nullptr;
            errno_t res;
            if (mode == ASSET_OPEN_TEXT) {
                res = fopen_s(&file, fullPath.c_str(), "r");
            } else if (mode == ASSET_OPEN_BINARY) {
                res = fopen_s(&file, fullPath.c_str(), "rb");
            }
            if (res == 0) return file;
        }
        upPath += "../";
    }

    return nullptr;
}

lumi::Buffer lumi::AssetLoader::OpenAndRead(const char* filename,
                                            AssetOpenMode mode) {
    FILE* file = static_cast<FILE*>(Open(filename, mode));
    
    Buffer buffer;
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return buffer;
    }
    size_t len = SizeOf(file);
    uint8_t* data;
    
    if (mode == ASSET_OPEN_TEXT) {
        // Text
        data = new uint8_t[len + 1];
        fread(data, 1, len, file);
#ifdef _DEBUG
        fprintf(stderr, "Read %zu bytes in file: %s\n", len, filename);
#endif
        data[len] = '\0';
        buffer.Set(data, len + 1);
    } else if (mode == ASSET_OPEN_BINARY) {
        // Binary
        data = new uint8_t[len];
        fread(data, 1, len, file);
#ifdef _DEBUG
        fprintf(stderr, "Read %zu bytes in file: %s\n", len, filename);
#endif
        buffer.Set(data, len);
    } else {
        fprintf(stderr, "Unknown open mode \'%d\' when opening file: %s\n",
                mode, filename);
    }

    Close(file);
    return buffer;
}
