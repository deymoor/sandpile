#include "libs/Classes/Field/Field.h"
#include "libs/Classes/Arguments/Arguments.h"
#include "libs/parser/argparser.h"
#include "libs/tsv_reader/tsvreader.h"
#include "libs/iter_sand_pile/itersandpile.h"

int main(int argc, char* argv[]) {
	Arguments arguments;
    Field field;
    GetArguments(arguments, argc, argv);
    ReadTsv(arguments.filename, field);
    IterSandPile(field, arguments);
	return 0;
}