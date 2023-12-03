#pragma once

#include <iostream>
#include <string>

int isDirective(char actual_character);
std::string processDirective(char actual_character, bool end_of_line);
bool endOfDirective(int actual_directive,char actual_character,bool end_of_line);