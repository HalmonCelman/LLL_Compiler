#pragma once

#include <iostream>
#include <string>
#include <map>

typedef enum{
    LLL_ADD = 0,
    LLL_AND,
    LLL_CMP,
    LLL_DEC,
    LLL_DIV,
    LLL_FRJMP,
    LLL_IN,
    LLL_INC,
    LLL_JMP,
    LLL_MOV,
    LLL_MUL,
    LLL_NOT,
    LLL_OR,
    LLL_OUT,
    LLL_RET,
    LLL_RJMP,
    LLL_SUB,
    LLL_EXIT=63
} lll_command;

extern const unsigned char number_of_tokens[];

lll_command compareCommands(std::string strcommand,unsigned long long int line_number);

