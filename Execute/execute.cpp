#include "execute.hpp"
#include "commands.hpp"

typedef std::string (*lllc_exec)(std::string,std::string,std::string,unsigned long long int);

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
    lllc_exit
};


/*
gets number of tokens from the array number_of_tokens
only exception is when exit function is invoked
*/
unsigned char getNumberOfTokens(lll_command command){
    if(command != LLL_EXIT){
        return number_of_tokens[command];
    }else{
        return 1;
    }
}

/*
this function executes command matching to lllc_command_map
at this moment also shows all parameters of function
returns string to write to output file
*/
std::string executeCommand(lll_command command,std::string strcommand,std::string param1, std::string param2, std::string param3, unsigned long long int line_number){
    std::cout<<line_number<<": "<<strcommand<<":"<<param1<<":"<<param2<<":"<<param3<<std::endl;

    return lllc_command_map[command](param1,param2,param3,line_number);
}
