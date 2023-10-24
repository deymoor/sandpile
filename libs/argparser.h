#pragma once
#include <iostream>

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
    char* filename = nullptr;
    char* dir = nullptr;
    uint64_t limit = 0;
    uint64_t freq = 0;
    void Destructor() {
        delete[] filename;
        delete[] dir;
    }
};

void ParseNumber(const char* str, uint64_t& number, uint8_t start);

void HandlerLimitCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]);

void HandlerFreqCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]);

void HandlerInputCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]);

void HandlerOutputCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]);

void IdentifyCommands(Arguments &arguments, int argc, char* argv[]);

void Parser(Arguments &arguments, int argc, char* argv[]);