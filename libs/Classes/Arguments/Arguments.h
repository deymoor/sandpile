#pragma once
#include <cstdint>

// struct of comamnd line's arguments

// filename - name of the source file
// commands to filename: -i, --input

// dir (directory) - name of the directory, where bmp-images is saved
// commands to dir: -o, --output

// limit - limit of iterations
// commands to limit: -m, --max-iter

// freq (frequency) - frequency of bmp saving
// commands to freq: -f, --freq


struct Arguments {
    static const uint8_t size_of_filename_command = 8;
    static const uint8_t size_of_dir_command = 9;
    static const uint8_t size_of_limit_command = 11;
    static const uint8_t size_of_freq_command = 7;
    char* filename;
    char* dir;
    uint64_t limit;
    uint64_t freq;

    Arguments() {
        filename = nullptr;
        dir = nullptr;
        limit = 0;
        freq = 0;
    }

    ~Arguments() {
        delete[] filename;
        delete[] dir;
    }
};