#pragma once

#include <iostream>
#include <string>

#define DEBUG_MODE 0

void processTokensInLine(std::string line, unsigned long long int line_number);
void endOfProcessing(void);
void endOfLine(void);