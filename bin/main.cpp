#include <libs/argparser.h>
#include <libs/tsvreader.h>
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

int main(int argc, char* argv[]) {
	std::cout << "Hello from labwork3" << std::endl;
	Arguments arguments;
	Parser(arguments, argc, argv);
    DoesItWork(arguments);
    ReadTsv(arguments.filename);
	// readtsv(&struct)j
	// iterfunc -> savebmp
    //arguments.Destructor();
	return 0;
}