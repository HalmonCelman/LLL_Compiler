#pragma once

#include <iostream>
#include <string>
#include <vector>

//labels
typedef struct{
    std::string name;
    unsigned long long int counter= 0;
    bool minus = true;
    bool fromDirective;
    bool active = true;
    unsigned long long int offset = 0;
} label_s;

extern std::vector <label_s> labels;

typedef enum{
    LLL_ADD = 0,
    LLL_AND,
    LLL_CMP,
    LLL_DEC,
    LLL_FRJMP,
    LLL_IN,
    LLL_INC,
    LLL_JMP,
    LLL_MOV,
    LLL_MUL,
    LLL_NOT,
    LLL_OR,
    LLL_OUT,
    LLL_POP,
    LLL_PUSH,
    LLL_RET,
    LLL_RJMP,
    LLL_SUB,
    LLL_EXIT=63,
    
// Directives
    LLLC_DEF,
    LLLC_LABEL
} lll_command;

const std::string& lllc_add   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_and   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_cmp   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_dec   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_frjmp (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_in    (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_inc   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_jmp   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_mov   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_mul   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_not   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_or    (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_out   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_pop   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_push  (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_ret   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_rjmp  (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_sub   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_exit  (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
// directives
const std::string& lllc_def   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
const std::string& lllc_label (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number);
void printLabelStatus(void);

