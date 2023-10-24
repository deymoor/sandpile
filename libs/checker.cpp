#include "utils.h"
#include <cstring>


void CheckNextArgument(int index, int argc) {
	if (index + 1 == argc) {
		ThrowError("You didn't write next argument!");
	}
}


void CheckHelpCommand(int argc, char* help) {
    if (argc == 2 && strcmp(help, "--help") == 0) {
        PrintCommands();
        std::exit(EXIT_SUCCESS);
    }
}


void CheckCountOfCommands(int argc){
    if (argc == 1) {
        ThrowError("Write any commands!\nPlease write --help to know all commands!");
    }
}


void CheckFile(const Arguments &arguments){
    if (!arguments.filename) {
        ThrowError("You didn't write the name of the file!");
    }
}