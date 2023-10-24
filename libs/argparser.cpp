#include "argparser.h"
#include "checker.h"
#include "utils.h"
#include <iostream>
#include <cstring>

// struct of comamnd line's arguments

// filename - name of the source file
// commands to filename: -i, --input

// dir (directory) - name of the directory, where bmp-images is saved
// commands to dir: -o, --output

// limit - limit of iterations
// commands to limit: -m, --max-iter

// freq (frequency) - frequency of bmp saving
// commands to freq: -f, --freq

void IdentifyArgument(Arguments &arguments, char* cmd, const int size){
    if ((strcmp(cmd, "-l") == 0) || (strncmp(cmd, "--lines=", 8) == 0)) {
        LengthCmd(arguments, cmd, size);
    } else if ((strcmp(cmd, "-t") == 0) || (strcmp(cmd, "--tail") == 0)) {
        TailCmd(arguments);
    } else if ((strcmp(cmd, "-r") == 0) || (strcmp(cmd, "--reverse") == 0)) {
        ReverseCmd(arguments);
    } else if ((strcmp(cmd, "-d") == 0) || (strncmp(cmd, "--delimiter=", 12) == 0)) {
        DelimiterCmd(arguments, cmd, size);
    } else if (strcmp(cmd, "--help") == 0) {
        ThrowError("Write --help without any defferent commands!");
    } else {
        ThrowError("Incorrect command or filename!\nPlease write --help to know all commands!");
    }
}

uint64_t ParseNumber(const char* str, uint64_t& number, uint8_t start) {
	char* end;
	uint64_t number = std::stoull(str + start, &end, 10);
	if (end != (str + std::strlen(str))) {
		ThrowError("You must to write integer numbers!");
	}
	return errno == ERANGE;
}

void LimitCmd(Arguments& arguments, int& index_cmd, int argc, char* argv[]) {
	char* cmd = argv[index_cmd];
	uint64_t number;
	if (strcmp(cmd, "-m") == 0) {
        CheckNextArgument(index_cmd, argc);
        char* str_number = argv[index_cmd + 1];
        ParseNumber(str_number, number, 0);
		index_cmd += 2;
	} else {
		ParseNumber(cmd, number, Arguments::size_of_limit_command);
		index_cmd++;
	}
	arguments.limit = number;
}

void IdentifyCommands(Arguments &arguments, int argc, char* argv[]){
	uint8_t index_cmd = 1;
	while (index_cmd < argc) {
		char* cmd = argv[index_cmd];
        if ((strcmp(cmd, "-i") == 0) || (strncmp(cmd, "--input=", Arguments::size_of_filename_command) == 0)) {
        	InputCmd(arguments, index_cmd, argv);
        } else if ((strcmp(cmd, "-o") == 0) || (strncmp(cmd, "--output=", Arguments::size_of_filename_command) == 0)) {

        } else if ((strcmp(cmd, "-m") == 0) || (strncmp(cmd, "--max_iter=", Arguments::size_of_filename_command) == 0)) {

        } else if ((strcmp(cmd, "-f") == 0) || (strncmp(cmd, "--freq=", Arguments::size_of_filename_command) == 0)) {

        } else {
        	ThrowError("Incorrect command or filename!\nPlease write --help to know all commands!");
        }
    }
}


void Parser(Arguments &arguments, int argc, char* argv[]) {
    CheckCountOfCommands(argc);
    CheckHelpCommand(argc, argv[1]);
    IdentifyCommands(arguments, argv[index_cmd]);
    CheckFile(arguments);
}