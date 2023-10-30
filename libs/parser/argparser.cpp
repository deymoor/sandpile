#include "argparser.h"


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
        if (cmd[Arguments::kLimitArgLen] == '-') {
            ThrowError("You must to write positive number!");
        }
		ParseNumber(cmd, number, Arguments::kLimitArgLen);
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
        if (cmd[Arguments::kFreqArgLen] == '-') {
            ThrowError("You must to write positive number!");
        }
        ParseNumber(cmd, number, Arguments::kFreqArgLen);
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
        arguments.filename = new char[strlen(cmd) - Arguments::kFilenameArgLen + null_terminated];
        strcpy(arguments.filename, cmd + Arguments::kFilenameArgLen);
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
        arguments.dir = new char[strlen(cmd) - Arguments::kDirArgLen + null_terminated];
        strcpy(arguments.dir, cmd + Arguments::kDirArgLen);
        index_cmd++;
    }
}

void IdentifyCommands(Arguments &arguments, int argc, char* argv[]) {
	uint8_t index_cmd = 1;
	while (index_cmd < argc) {
		char* cmd = argv[index_cmd];
        if ((strcmp(cmd, "-i") == 0) || (strncmp(cmd, "--input=", Arguments::kFilenameArgLen) == 0)) {
            HandlerInputCmd(arguments, index_cmd, argc, argv);
        } else if ((strcmp(cmd, "-o") == 0) || (strncmp(cmd, "--output=", Arguments::kDirArgLen) == 0)) {
            HandlerOutputCmd(arguments, index_cmd, argc, argv);
        } else if ((strcmp(cmd, "-m") == 0) || (strncmp(cmd, "--max_iter=", Arguments::kLimitArgLen) == 0)) {
            HandlerLimitCmd(arguments, index_cmd, argc, argv);
        } else if ((strcmp(cmd, "-f") == 0) || (strncmp(cmd, "--freq=", Arguments::kFreqArgLen) == 0)) {
            HandlerFreqCmd(arguments, index_cmd, argc, argv);
        } else {
        	ThrowError("Incorrect command or filename!\nPlease write --help to know all commands!");
        }
    }
}


void GetArguments(Arguments &arguments, int argc, char* argv[]) {
    CheckCountOfCommands(argc);
    CheckHelpCommand(argc, argv[1]);
    IdentifyCommands(arguments, argc, argv);
    CheckFile(arguments.filename);
}