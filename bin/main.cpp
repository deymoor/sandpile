#include "libs/Classes/Field/Field.h"
#include "libs/Classes/Arguments/Arguments.h"
#include "libs/parser/argparser.h"
#include "libs/tsv_reader/tsvreader.h"
#include "libs/iter_sand_pile/itersandpile.h"
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

void PrintSandPile(Field* field) {
    for (int i = 0; i < field->border_y; ++i) {
        for (int j = 0; j < field->border_x; ++j) {
            std::cout << field->sand_pile[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

// обработка отрицательных чисел
int main(int argc, char* argv[]) {
	std::cout << "Hello from labwork3" << std::endl;
	Arguments arguments;
    auto field = new Field();
	Parser(arguments, argc, argv);
    DoesItWork(arguments);
    ReadTsv(arguments.filename, field);
    IterSandPile(field, arguments);
    delete field;
	return 0;
}