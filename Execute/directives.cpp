#include "directives.hpp"

bool star=false;        // if star is present in comment, this boolean becomes 'true' - used in checking of end
bool exclamation=false; // if exclamation mark is present after beginning of comment exclamation boolean is set to 'true'
/*
is Directive?
checks if actual character have the prefix adequate for directives
*/
int isDirective(char actual_character){
    switch(actual_character){
        case '#': return 1;
        case '/': return 2;
        default: 
            return 0;
    }
}

/*
process Directive
get character and process into file or do nothing
if there is no ! after beginning of the comment nothing is done,
 when ! is present then comment are moved into the code memory (only for decompiler in fact)
*/
std::string processDirective(char actual_character, bool end_of_line, bool first_execution){
    std::string tmpString;
    if(!first_execution){
        if(exclamation){
            if(end_of_line) tmpString.push_back('\n');
            tmpString.push_back(actual_character);
        }
    }else{
        if('!' == actual_character){
            exclamation=true;
        }
    }
    return tmpString;
}

/*
end of directive - checks if actual character is ending actual directive

    when this is end it automaticcaly cleans exclamation boolean
    to end type 1 of directive( comment with # ) \n is needed
    to end type 2 (comment / ) * and / is needed 
*/
bool endOfDirective(int actual_directive,char actual_character,bool end_of_line){
    switch(actual_directive){
        case 1: 
            if(end_of_line){
                exclamation = false;
                return true;
            } else{
                return false;
            }
        case 2: 
            if('*' == actual_character){
                star = true;
                return false;
            }else{
                if('/' == actual_character){
                    if(star){
                        star = false;
                        exclamation = false;
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