#include <iostream>


void ThrowError(const char* error_message){
    std::cerr << error_message << '\n';
    std::exit(EXIT_FAILURE);
}


void PrintCommands(){
    std::cout << "--------------------------------------\n";
    std::cout << "You can use this commands:\n";
    std::cout << "Use -l {number} or --lines={number} to set the count of the printed lines\n";
    std::cout << "Use -t or --tail to print lines from the end\n";
    std::cout << "Use -d {special character} or --delimiter={special_character} to set delimiter of lines\n";
    std::cout << "You can also write name of your file. But in the beginning of the name you can't use '-'\n";
    std::cout << "--------------------------------------\n";
}