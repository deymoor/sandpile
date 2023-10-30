#pragma once
#include <cstdint>


struct Arguments {
    static const uint8_t kFilenameArgLen = 8;
    static const uint8_t kDirArgLen = 9;
    static const uint8_t kLimitArgLen = 11;
    static const uint8_t kFreqArgLen = 7;
    char* filename;
    char* dir;
    uint64_t limit;
    uint64_t freq;

    Arguments() {
        filename = nullptr;
        dir = nullptr;
        limit = UINT64_MAX;
        freq = UINT64_MAX;
    }

    ~Arguments() {
        delete[] filename;
        delete[] dir;
    }
};