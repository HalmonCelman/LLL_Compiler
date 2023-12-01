#include "command_processing.hpp" 

const unsigned char number_of_tokens[]={
    3,      // ADD
    3,      // AND
    3,      // CMP
    2,      // DEC
    3,      // DIV
    3,      // FRJMP
    3,      // IN
    2,      // INC
    3,      // JMP
    3,      // MOV
    3,      // MUL
    2,      // NOT
    3,      // OR
    3,      // OUT
    1,      // RET
    3,      // RJMP
    3      // SUB
};



lll_command compareCommands(std::string strcommand,unsigned long long int line_number){

    if("add" == strcommand){    return LLL_ADD;     }
    if("and" == strcommand){    return LLL_AND;     }
    if("cmp" == strcommand){    return LLL_CMP;     }
    if("dec" == strcommand){    return LLL_DEC;     }
    if("div" == strcommand){    return LLL_DIV;     }
    if("frjmp" == strcommand){  return LLL_FRJMP;   }
    if("in" == strcommand){     return LLL_IN;      }
    if("inc" == strcommand){    return LLL_INC;     }
    if("jmp" == strcommand){    return LLL_JMP;     }
    if("mov" == strcommand){    return LLL_MOV;     }
    if("mul" == strcommand){    return LLL_MUL;     }
    if("not" == strcommand){    return LLL_NOT;     }
    if("or" == strcommand){     return LLL_OR;      }
    if("out" == strcommand){    return LLL_OUT;     }
    if("ret" == strcommand){    return LLL_RET;     }
    if("rjmp" == strcommand){   return LLL_RJMP;    }
    if("sub" == strcommand){    return LLL_SUB;     }
    if("exit" == strcommand){   return LLL_EXIT;    }

    std::cout<<"ERROR: wrong command: "<<strcommand<<" in line:"<<line_number<<std::endl;
    exit(0);
}


