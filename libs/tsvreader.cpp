#include "utils.h"
#include "tsvreader.h"
#include <fstream>

void ReadTsv(const char* filename) {
    std::ifstream input(filename);
    if (!input) {
        ThrowError("Incorrect input file name!");
    }
    while (input) {

    }
}