#include "utils.h"
#include <iostream>
#include <cstring>

void ParseNumber(const char* str, uint64_t& number, uint8_t start) {
    char* end;
    number = std::strtoull(str + start, &end, 10);
    if (end != (str + std::strlen(str))) {
        ThrowError("You must to write integer numbers!");
    }
    if (errno == ERANGE) {
        ThrowError("The number is greater than maximum of uint64_t");
    }
}

void ThrowError(const char* error_message){
    std::cerr << error_message << '\n';
    std::exit(EXIT_FAILURE);
}

void PrintCommands(){
    std::cout << "--------------------------------------\n";
    std::cout << "You can use this commands:\n";
    std::cout << "Use -m {number} or --max_iter={number} to set the maximum quantity of iterations\n";
    std::cout << "Use -i {filename} or --input={filename} to write name of the file\n";
    std::cout << "Use -o {directory} or --output={directory} to set directory, where your images will be saved\n";
    std::cout << "Use -f {number} or --freq={number} to set frequency of saving images\n";
    std::cout << "--------------------------------------\n";
}