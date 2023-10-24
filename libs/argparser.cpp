#include "argparser.h"
#include "checker.h"
#include "utils.h"
#include <iostream>
#include <cstring>


void HandlerLimitCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]) {
	char* cmd = argv[index_cmd];
	uint64_t number;
	if (strcmp(cmd, "-m") == 0) {
        CheckNextArgument(index_cmd, argc);
        char* str_number = argv[index_cmd + 1];
        if (str_number[0] == '-') {
            ThrowError("You must to write positive number!");
        }
        ParseNumber(str_number, number, 0);
		index_cmd += 2;
	} else {
        if (cmd[Arguments::size_of_limit_command] == '-') {
            ThrowError("You must to write positive number!");
        }
		ParseNumber(cmd, number, Arguments::size_of_limit_command);
		index_cmd++;
	}
	arguments.limit = number;
}

void HandlerFreqCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]) {
    char* cmd = argv[index_cmd];
    uint64_t number;
    if (strcmp(cmd, "-f") == 0) {
        CheckNextArgument(index_cmd, argc);
        char* str_number = argv[index_cmd + 1];
        if (str_number[0] == '-') {
            ThrowError("You must to write positive number!");
        }
        ParseNumber(str_number, number, 0);
        index_cmd += 2;
    } else {
        if (cmd[Arguments::size_of_freq_command] == '-') {
            ThrowError("You must to write positive number!");
        }
        ParseNumber(cmd, number, Arguments::size_of_freq_command);
        index_cmd++;
    }
    arguments.freq = number;
}

void HandlerInputCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]) {
    char* cmd = argv[index_cmd];
    const uint8_t null_terminated = 1;
    if (strcmp(cmd, "-i") == 0) {
        CheckNextArgument(index_cmd, argc);
        arguments.filename = new char[strlen(argv[index_cmd + 1]) + null_terminated];
        strcpy(arguments.filename, argv[index_cmd + 1]);
        index_cmd += 2;
    } else {
        arguments.filename = new char[strlen(cmd) - Arguments::size_of_filename_command + null_terminated];
        strcpy(arguments.filename, cmd + Arguments::size_of_filename_command);
        index_cmd++;
    }
}

void HandlerOutputCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]) {
    char* cmd = argv[index_cmd];
    const uint8_t null_terminated = 1;
    if (strcmp(cmd, "-o") == 0) {
        CheckNextArgument(index_cmd, argc);
        arguments.dir = new char[strlen(argv[index_cmd + 1]) + null_terminated];
        strcpy(arguments.dir, argv[index_cmd + 1]);
        index_cmd += 2;
    } else {
        arguments.dir = new char[strlen(cmd) - Arguments::size_of_dir_command + null_terminated];
        strcpy(arguments.dir, cmd + Arguments::size_of_dir_command);
        index_cmd++;
    }
}

void IdentifyCommands(Arguments &arguments, int argc, char* argv[]) {
	uint8_t index_cmd = 1;
	while (index_cmd < argc) {
		char* cmd = argv[index_cmd];
        if ((strcmp(cmd, "-i") == 0) || (strncmp(cmd, "--input=", Arguments::size_of_filename_command) == 0)) {
            HandlerInputCmd(arguments, index_cmd, argc, argv);
        } else if ((strcmp(cmd, "-o") == 0) || (strncmp(cmd, "--output=", Arguments::size_of_dir_command) == 0)) {
            HandlerOutputCmd(arguments, index_cmd, argc, argv);
        } else if ((strcmp(cmd, "-m") == 0) || (strncmp(cmd, "--max_iter=", Arguments::size_of_limit_command) == 0)) {
            HandlerLimitCmd(arguments, index_cmd, argc, argv);
        } else if ((strcmp(cmd, "-f") == 0) || (strncmp(cmd, "--freq=", Arguments::size_of_freq_command) == 0)) {
            HandlerFreqCmd(arguments, index_cmd, argc, argv);
        } else {
        	ThrowError("Incorrect command or filename!\nPlease write --help to know all commands!");
        }
    }
}


void Parser(Arguments &arguments, int argc, char* argv[]) {
    CheckCountOfCommands(argc);
    CheckHelpCommand(argc, argv[1]);
    IdentifyCommands(arguments, argc, argv);
    CheckFile(arguments.filename);
}