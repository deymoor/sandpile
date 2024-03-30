#pragma once
#include <cinttypes>

void ParseNumber(const char* str, uint64_t& number, uint8_t start);

void ThrowError(const char* error_message);

void PrintCommands();