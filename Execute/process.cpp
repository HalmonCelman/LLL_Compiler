#include "process.hpp"
#include "execute.hpp"
#include "directives.hpp"

typedef enum{
    TOKEN,
    DELIMITER,
    DIRECTIVE
} STATUS;

STATUS status=DELIMITER;
unsigned char error=0;

std::string tokens[4];
unsigned char actual_token = 0;
int actual_directive = 0;
unsigned char actual_number_of_tokens = 1;
lll_command actual_command;

std::string delimiterList=" ,;";
const unsigned char delimiterListLength=delimiterList.length();

static bool isDelimiter(char actual_character){
    for(int i=0;i<delimiterListLength;i++){
        if(actual_character == delimiterList[i])
            return true;
    }
    return false;
}

static std::string processCommand(unsigned long long int line_number){
    std::string returnString = executeCommand(actual_command,tokens[0],tokens[1],tokens[2],tokens[3],line_number);
    //cleanup
    tokens[0].clear();
    tokens[1].clear();
    tokens[2].clear();
    tokens[3].clear();
    actual_token = 0;
    actual_number_of_tokens = 1;

    return returnString;
}

static std::string process(char actual_character, unsigned long long int line_number,bool end_of_line){
    switch(status){
        case TOKEN:
            if(isDelimiter(actual_character)){
                status=DELIMITER;
                actual_token++;

                if(actual_token == 1){
                    actual_command = compareCommands(tokens[0],line_number);
                    actual_number_of_tokens = getNumberOfTokens(actual_command);
                }

                if(actual_token == actual_number_of_tokens){
                    return processCommand(line_number);
                }
                
            }else{
                actual_directive=isDirective(actual_character);
                if(actual_directive){
                    process(' ',line_number, false);
                    status = DIRECTIVE;                    
                }else{
                    tokens[actual_token].push_back(actual_character);
                }
            }
            return "";

        case DELIMITER:
            if(!isDelimiter(actual_character)){
                actual_directive=isDirective(actual_character);
                if(actual_directive){
                    status = DIRECTIVE;
                }else{
                    tokens[actual_token].push_back(actual_character);
                    status = TOKEN;
                }
            }
            return "";

        case DIRECTIVE:

            if(endOfDirective(actual_directive,actual_character,end_of_line)){
                status=DELIMITER;
            }else{
                return processDirective(actual_character,end_of_line);
            }
            return "";
        default: 
            std::cout<<"COMPILER ERROR: process should never enter this state";
            exit(0);
    }
}

static std::string endOfLine(unsigned long long int line_number){
    return process(' ', line_number, true);
}

std::string processTokensInLine(std::string line, unsigned long long int line_number){
    std::string tmpString;
    for(int i=0;line[i];i++){
        #if DEBUG_MODE
            std::cout<<"processing: '"<<line[i]<<"' \n";
        #endif
        tmpString += process(line[i], line_number, false);
    }
    tmpString += endOfLine(line_number);

    return tmpString;
}



std::string endOfProcessing(unsigned long long int line_number){
    std::string tmpString = process(' ', line_number, true);
    if(actual_token || tokens[0].length()){
        std::cout<<"ERROR: Unexpected End Of File: "<<tokens[0]<<" "<<tokens[1]<<" "<<tokens[2]<<tokens[3]<<std::endl;
    }
    return tmpString;
}
