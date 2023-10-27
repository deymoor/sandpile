#pragma once
#include "../Classes/Field/Field.h"
#include "../utils.h"
#include <fstream>
#include <iostream>

void FindBorders(Field* field, std::ifstream& input);

void InitSandPile(Field* field);

void ReadTsv(const char* filename, Field* field);