#include "tsvreader.h"

void ReadTsv(const char* filename, Field& field) {
    std::ifstream input(filename);
    if (!input) {
        ThrowError("Incorrect input file name!");
    }
    while (!input.eof()) {
        int16_t x;
        int16_t y;
        uint64_t grain;
        input >> x >> y >> grain;
        field.x_array.push_back(x);
        field.y_array.push_back(y);
        field.grain_array.push_back(grain);
    }
}