#pragma once
#include <cstdint>


struct Arguments {
    static const uint8_t size_of_filename_command = 8;
    static const uint8_t size_of_dir_command = 9;
    static const uint8_t size_of_limit_command = 11;
    static const uint8_t size_of_freq_command = 7;
    char* filename = nullptr;
    char* dir = nullptr;
    uint64_t limit = UINT64_MAX;
    uint64_t freq = UINT64_MAX;

    ~Arguments() {
        delete[] filename;
        delete[] dir;
    }
};