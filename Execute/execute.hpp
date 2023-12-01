#pragma once

#include "command_processing.hpp"

#include <iostream>
#include <string>

unsigned char getNumberOfTokens(lll_command command);
void executeCommand(lll_command command,std::string strcommand,std::string param1, std::string param2, unsigned long long int line_number);