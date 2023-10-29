#include "tsvreader.h"


void FindBorders(Field* field, std::ifstream& input, Offset& offset) {
    while (!input.eof()) {
        int16_t x_real;
        int16_t y_real;
        uint64_t particle;
        input >> x_real >> y_real >> particle;
        uint16_t x = x_real + offset.x;
        uint16_t y = y_real + offset.y;
        field->border_x = std::max(field->border_x, x);
        field->border_y = std::max(field->border_y, y);
    }
    input.seekg(0, std::ios::beg);
}

void FindOffsetOfCoordinate(std::ifstream& input, Offset& offset) {
    while (!input.eof()) {
        int16_t x;
        int16_t y;
        uint64_t particle;
        input >> x >> y >> particle;
        if (x <= 0) {
            uint16_t offset_relative = abs(x) + 1;
            offset.x = std::max(offset_relative, offset.x);
        }
        if (y <= 0) {
            uint16_t offset_relative = abs(y) + 1;
            offset.y = std::max(offset_relative, offset.y);
        }
    }
    input.seekg(0, std::ios::beg);
}

void InitSandPile(Field* field) {
    field->sand_pile = new uint64_t*[field->border_y];
    for (size_t i = 0; i < field->border_y; ++i) {
        field->sand_pile[i] = new uint64_t[field->border_x] {0};
    }
}

void ReadTsv(const char* filename, Field* field) {
    std::ifstream input(filename);
    if (!input) {
        ThrowError("Incorrect input file name!");
    }
    Offset offset;
    FindOffsetOfCoordinate(input, offset);
    FindBorders(field, input, offset);
    InitSandPile(field);
    while (!input.eof()) {
        int16_t x_real;
        int16_t y_real;
        uint64_t particles;
        input >> x_real >> y_real >> particles;
        uint16_t x = x_real + offset.x - 1;
        uint16_t y = y_real + offset.y - 1;
        field->sand_pile[y][x] = particles;
    }
}