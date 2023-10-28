#include "utils.h"
#include <iostream>
#include <cstring>

char* ConvertToBMPName(uint64_t num) {
    const uint8_t bmp_let = 5;
    uint64_t temp_num = num;
    uint32_t size = 0;
    while (temp_num || !size) {
        size++;
        temp_num /= 10;
    }
    char* name = new char[size + bmp_let];
    temp_num = num;
    uint32_t i = 0;
    while (temp_num || !i) {
        name[size - i - 1] = '0' + (temp_num % 10);
        temp_num /= 10;
        i++;
    }
    name[i] = '.';
    name[i + 1] = 'b';
    name[i + 2] = 'm';
    name[i + 3] = 'p';
    name[i + 4] = '\0';
    return name;
}

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