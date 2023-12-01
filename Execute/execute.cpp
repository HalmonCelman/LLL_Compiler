#include "execute.hpp"

unsigned char getNumberOfTokens(lll_command command){
    if(command != LLL_EXIT){
        return number_of_tokens[command];
    }else{
        return 1;
    }
}