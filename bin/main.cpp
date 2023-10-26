#include "libs/Classes/Field/Field.h"
#include "libs/Classes/Arguments/Arguments.h"
#include "libs/Parser/argparser.h"
#include "libs/TsvReader/tsvreader.h"
#include "libs/SaveBmp/SaveBmp.h"
#include <iostream>


void DoesItWork(Arguments &arguments) {
    if (arguments.filename != nullptr) {
        std::cout << arguments.filename << '\n';
    } else {
        std::cout << "file name is empty\n";
    }
    if (arguments.dir != nullptr) {
        std::cout << arguments.dir << '\n';
    } else {
        std::cout << "dir is empty\n";
    }
    std::cout << arguments.limit << '\n';
    std::cout << arguments.freq << '\n';
}

void DoesReadWork(Field& field) {
    for (size_t i = 0; i < field.x_array.size(); ++i) {
        std::cout << field.x_array[i] << ' ';
    }
    std::cout << '\n';
    for (size_t i = 0; i < field.y_array.size(); ++i) {
        std::cout << field.y_array[i] << ' ';
    }
    std::cout << '\n';
    for (size_t i = 0; i < field.grain_array.size(); ++i) {
        std::cout << field.grain_array[i] << ' ';
    }
}

int main(int argc, char* argv[]) {
    //SaveBmp();
	std::cout << "Hello from labwork3" << std::endl;
	Arguments arguments;
    Field field;
	Parser(arguments, argc, argv);
    DoesItWork(arguments);
    ReadTsv(arguments.filename, field);
    DoesReadWork(field);
	// iterfunc -> savebmp
    //arguments.Destructor();
	return 0;
}