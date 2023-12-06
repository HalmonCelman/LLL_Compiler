#include "command_processing.hpp" 
#include "commands.hpp"


typedef std::string (*lllc_exec)(std::string,std::string,std::string,std::string,unsigned long long int);


/// **************************** section of commands & directives ***********************************

/*
array with number of parameters( including command itself )
*/
const unsigned char number_of_tokens[]={
    4,      // ADD
    4,      // AND
    3,      // CMP
    2,      // DEC
    4,      // DIV
    3,      // FRJMP
    3,      // IN
    2,      // INC
    3,      // JMP
    3,      // MOV
    4,      // MUL
    3,      // NOT
    3,      // OR
    3,      // OUT
    1,      // RET
    3,      // RJMP
    4       // SUB
};

/*
it is map of functions to execute
it's just list of command functions
*/
const lllc_exec lllc_command_map[]={
    lllc_add,
    lllc_and,
    lllc_cmp,
    lllc_dec,
    lllc_div,
    lllc_frjmp,
    lllc_in,
    lllc_inc,
    lllc_jmp,
    lllc_mov,
    lllc_mul,
    lllc_not,
    lllc_or,
    lllc_out,
    lllc_ret,
    lllc_rjmp,
    lllc_sub,
    0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    lllc_exit,
    lllc_def,
    lllc_label
};


/*
compare commands
checks if token matches any command in string representation and converts it into ENUM representation
returns error if there is no such command
*/
unsigned int compareCommands(std::string strfullcommand,unsigned long long int line_number){
    std::string strcommand= strfullcommand.substr(0,3);

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
    if(".def" == strcommand){   return LLLC_DEF;    }
    if(':' == strcommand[0]){   return LLLC_LABEL;  }

    std::cout<<"ERROR: wrong command: "<<strcommand<<" in line:"<<line_number<<std::endl;
    exit(0);
}

/*
gets number of tokens from the array number_of_tokens
only exception is when exit or directive is invoked
*/
unsigned char getNumberOfTokens(unsigned int command){
    switch(command){
        //directives and exit
        case LLL_EXIT:
        case LLLC_LABEL:
            return 1;
        case LLLC_DEF:
            return 3;
        default:
            return number_of_tokens[command];
    }
}
/// ************************************** end of section **********************************************

/*
this function executes command matching to lllc_command_map
at this moment also shows all parameters of function
returns string to write to output file
*/
std::string executeCommand(unsigned int command,std::string strcommand,std::string param1, std::string param2, std::string param3, unsigned long long int line_number){
    std::cout<<line_number<<": "<<strcommand<<":"<<param1<<":"<<param2<<":"<<param3<<std::endl;

    return lllc_command_map[command](strcommand.substr(3),param1,param2,param3,line_number);
}
