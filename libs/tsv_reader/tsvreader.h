#pragma once
#include "../Classes/Field/Field.h"
#include "../utils/utils.h"
#include <fstream>
#include <iostream>

struct Offset {
    uint16_t x = 0;
    uint16_t y = 0;
};

void FindBorders(Field* field, std::ifstream& input, Offset& offset);

void FindOffsetOfCoordinate(std::ifstream& input, Offset& offset);

void InitSandPile(Field* field);

void ReadTsv(const char* filename, Field* field);