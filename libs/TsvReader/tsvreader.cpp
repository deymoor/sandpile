#include "tsvreader.h"


// without negative coordinate
void FindBorders(Field* field, std::ifstream& input) {
    while (!input.eof()) {
        int16_t x;
        int16_t y;
        uint64_t grain;
        input >> x >> y >> grain;
        field->border_x = std::max(field->border_x, x);
        field->border_y = std::max(field->border_y, y);
    }
    input.seekg(0, std::ios::beg);
}

void InitSandPile(Field* field) {
    field->sand_pile = new uint64_t*[field->border_y];
    for (size_t i = 0; i < field->border_y; ++i) {
        field->sand_pile[i] = new uint64_t[field->border_x];
    }
}

void ReadTsv(const char* filename, Field* field) {
    std::ifstream input(filename);
    if (!input) {
        ThrowError("Incorrect input file name!");
    }
    FindBorders(field, input);
    InitSandPile(field);
    while (!input.eof()) {
        int16_t x;
        int16_t y;
        uint64_t grain;
        input >> x >> y >> grain;
        x--;
        y--;
        field->sand_pile[y][x] = grain;
    }
}