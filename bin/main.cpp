#include "libs/Classes/Field/Field.h"
#include "libs/Classes/Arguments/Arguments.h"
#include "libs/parser/argparser.h"
#include "libs/tsv_reader/tsvreader.h"
#include "libs/iter_sand_pile/itersandpile.h"
#include <iostream>

int main(int argc, char* argv[]) {
	Arguments arguments;
    auto field = new Field();
	Parser(arguments, argc, argv);
    ReadTsv(arguments.filename, field);
    IterSandPile(field, arguments);
    delete field;
	return 0;
}