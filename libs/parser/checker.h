#pragma once
#include "../utils/utils.h"
#include <cstring>
#include <iostream>


void CheckNextArgument(int index, int argc);

void CheckHelpCommand(int argc, char* help);

void CheckCountOfCommands(int argc);

void CheckFile(char const* filename);