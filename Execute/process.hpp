#pragma once

#include <iostream>
#include <string>

#define DEBUG_MODE 0

const std::string& processTokensInLine(std::string line, unsigned long long int line_number);
const std::string& endOfProcessing(unsigned long long int line_number);