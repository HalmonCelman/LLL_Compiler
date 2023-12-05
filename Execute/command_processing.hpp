#pragma once

#include <iostream>
#include <string>

unsigned int compareCommands(std::string strcommand,unsigned long long int line_number);
unsigned char getNumberOfTokens(unsigned int command);
std::string executeCommand(unsigned int command,std::string strcommand,std::string param1, std::string param2, std::string param3, unsigned long long int line_number);