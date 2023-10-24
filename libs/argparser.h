#pragma once
#include <cstdint>

struct Arguments {
    char* filename = "";
    char* dir;
    uint64_t limit = 0;
    uint64_t freq = 0;
};

void Parser(Arguments &arguments, int argc, char* argv[]);