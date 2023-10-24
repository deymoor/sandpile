#include <libs/argparser.h>
#include <iostream>

// как будто песчинки хочется на связном списке написать

int main(int argc, char* argv[]) {
	std::cout << "Hello from labwork3" << std::endl;
	Arguments arguments;
	Parser(arguments, argc, argv);
	// argparser(&struct) - return filled in struct
	// tsv-format:	x	y	num
	// readtsv(&struct)
	// iterfunc -> savebmp
	return 0;
}