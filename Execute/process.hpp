#pragma once

#include <iostream>
#include <string>

#define DEBUG_MODE 0

std::string processTokensInLine(std::string line, unsigned long long int line_number);
std::string endOfProcessing(unsigned long long int line_number);