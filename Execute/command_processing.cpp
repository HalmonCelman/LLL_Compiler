#include "command_processing.hpp" 
#include "commands.hpp"


typedef const std::string& (*lllc_exec)(std::string,std::string,std::string,std::string,unsigned long long int);


/// **************************** section of commands & directives ***********************************

/*
array with number of parameters( including command itself )
*/
const unsigned char number_of_tokens[]={
    4,      // ADD
    4,      // AND
    3,      // CMP
    2,      // DEC
    3,      // FRJMP
    3,      // IN
    2,      // INC
    3,      // JMP
    3,      // MOV
    4,      // MUL
    3,      // NOT
    4,      // OR
    3,      // OUT
    2,      // POP
    2,      // PUSH
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
    lllc_frjmp,
    lllc_in,
    lllc_inc,
    lllc_jmp,
    lllc_mov,
    lllc_mul,
    lllc_not,
    lllc_or,
    lllc_out,
    lllc_pop,
    lllc_push,
    lllc_ret,
    lllc_rjmp,
    lllc_sub,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,
    lllc_exit,
    lllc_def,
    lllc_label
};


/*
compare commands
checks if token matches any command in string representation and converts it into ENUM representation
returns error if there is no such command
*/
unsigned int compareCommands(std::string strcommand,unsigned long long int line_number){

    if("add"    == strcommand.substr(0,3)){     return LLL_ADD;     } else
    if("and"    == strcommand.substr(0,3)){     return LLL_AND;     } else
    if("cmp"    == strcommand.substr(0,3)){     return LLL_CMP;     } else
    if("dec"    == strcommand.substr(0,3)){     return LLL_DEC;     } else
    if("frjmp"  == strcommand.substr(0,5)){     return LLL_FRJMP;   } else
    if("inc"    == strcommand.substr(0,3)){     return LLL_INC;     } else
    if("in"     == strcommand.substr(0,2)){     return LLL_IN;      } else
    if("jmp"    == strcommand.substr(0,3)){     return LLL_JMP;     } else
    if("mov"    == strcommand.substr(0,3)){     return LLL_MOV;     } else
    if("mul"    == strcommand.substr(0,3)){     return LLL_MUL;     } else
    if("not"    == strcommand.substr(0,3)){     return LLL_NOT;     } else
    if("or"     == strcommand.substr(0,2)){     return LLL_OR;      } else
    if("out"    == strcommand.substr(0,3)){     return LLL_OUT;     } else
    if("pop"    == strcommand.substr(0,3)){     return LLL_POP;     } else
    if("push"   == strcommand.substr(0,4)){     return LLL_PUSH;    } else
    if("ret"    == strcommand.substr(0,3)){     return LLL_RET;     } else
    if("rjmp"   == strcommand.substr(0,4)){     return LLL_RJMP;    } else
    if("sub"    == strcommand.substr(0,3)){     return LLL_SUB;     } else
    if("exit"   == strcommand.substr(0,4)){     return LLL_EXIT;    } else
    if(".def"   == strcommand.substr(0,4)){     return LLLC_DEF;    } else
    if(':'      == strcommand[0])         {     return LLLC_LABEL;  }

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
const std::string& executeCommand(unsigned int command,std::string strcommand,std::string param1, std::string param2, std::string param3, unsigned long long int line_number){
    std::cout<<line_number<<": "<<strcommand<<":"<<param1<<":"<<param2<<":"<<param3<<std::endl;

    return lllc_command_map[command](strcommand,param1,param2,param3,line_number);
}
