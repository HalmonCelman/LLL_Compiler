#include "directives.hpp"

bool star=false;
bool endType3=false;

int isDirective(char actual_character){
    switch(actual_character){
        case '#': return 1;
        case '/': return 2;
        default: 
            return 0;
    }
}

std::string processDirective(char actual_character, bool end_of_line){
    std::string tmpString;
    if(end_of_line) tmpString.push_back('\n');
    tmpString.push_back(actual_character);
    return tmpString;
}

bool endOfDirective(int actual_directive,char actual_character,bool end_of_line){
    switch(actual_directive){
        case 1: return end_of_line;
        case 2: 
            if('*' == actual_character){
                star = true;
                return false;
            }else{
                if('/' == actual_character){
                    if(star){
                        star = false;
                        return true;
                    }
                    return false;
                }
                star = false;
                return false;
            }
        default: 
            std::cout<<"COMPILER ERROR: directives should never enter this state";
            exit(0);
    }
}