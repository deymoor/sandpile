#pragma once
#include "../Classes/Arguments/Arguments.h"
#include "../utils/utils.h"
#include "checker.h"
#include <iostream>
#include <cstring>

void HandlerLimitCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]);

void HandlerFreqCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]);

void HandlerInputCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]);

void HandlerOutputCmd(Arguments& arguments, uint8_t& index_cmd, int argc, char* argv[]);

void IdentifyCommands(Arguments &arguments, int argc, char* argv[]);

void Parser(Arguments &arguments, int argc, char* argv[]);