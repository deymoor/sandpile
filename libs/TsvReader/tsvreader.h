#pragma once
#include "../Classes/Field/Field.h"
#include "../Classes/Vector/Vector.h"
#include "../utils.h"
#include <fstream>
#include <iostream>

void ReadTsv(const char* filename, Field& field);