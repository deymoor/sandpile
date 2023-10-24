#include <libs/argparser.h>
#include <iostream>

// как будто песчинки хочется на связном списке написать

void DoesItWork(Arguments &arguments) {
    std::cout << arguments.filename << '\n';
    std::cout << arguments.dir << '\n';
    std::cout << arguments.limit << '\n';
    std::cout << arguments.freq << '\n';
}

int main(int argc, char* argv[]) {
	std::cout << "Hello from labwork3" << std::endl;
	Arguments arguments;
	Parser(arguments, argc, argv);
    DoesItWork(arguments);
	// tsv-format:	x	y	num
	// readtsv(&struct)
	// iterfunc -> savebmp
    arguments.Destructor();
	return 0;
}