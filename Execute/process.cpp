#include "process.hpp"
#include "directives.hpp"
#include "command_processing.hpp"

// possible states of state machine in Process function
typedef enum{
    TOKEN,
    DELIMITER,
    DIRECTIVE
} STATUS;

STATUS status=DELIMITER;                                        // status of state machine in Process function

std::string tokens[4];                                          // list of tokens - command/directive and parameters
unsigned char actual_token = 0;                                 // actually managed token
int actual_directive = 0;                                       // actually detected directive
bool first_directive_execution = true;                          // only for exlamation mark in comments
unsigned char actual_number_of_tokens = 1;                      // number of tokens - always at least 1
unsigned int actual_command;                                     // it's actually detected and in future executed command

std::string delimiterList=" ,;";                                // list of possible delimiters ( without newline )
const unsigned char delimiterListLength=delimiterList.length(); // constant to don't check always length

/*
this function checks if actual character is delimiter
*/
static bool isDelimiter(char actual_character){
    for(int i=0;i<delimiterListLength;i++){
        if(actual_character == delimiterList[i])
            return true;
    }
    return false;
}

/*
this function execute command and do cleanup after succesfully finished execution
*/
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

/*
this function process one character at once, based on state machine architecture

- identify tokens/directives
- executes tokens/directives
*/
static std::string process(char actual_character, unsigned long long int line_number,bool end_of_line){
    
    std::string tmpString;
    
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
                first_directive_execution = true;
            }else{
                tmpString = processDirective(actual_character,end_of_line, first_directive_execution);
                first_directive_execution = false;
            }

            return tmpString;
        default: 
            std::cout<<"COMPILER ERROR: process should never enter this state";
            exit(0);
    }
}

/*
this function process all tokens at single line
*/
std::string processTokensInLine(std::string line, unsigned long long int line_number){
    std::string tmpString;
    for(int i=0;line[i];i++){
        #if DEBUG_MODE
            std::cout<<"processing: '"<<line[i]<<"' \n";
        #endif
        tmpString += process(line[i], line_number, false);
    }
    tmpString += process(' ', line_number, true);

    return tmpString;
}


/*
this function cleanup at the end - checks if any tokens left and process
*/
std::string endOfProcessing(unsigned long long int line_number){
    std::string tmpString = process(' ', line_number, true);
    if(actual_token || tokens[0].length()){
        std::cout<<"ERROR: Unexpected End Of File: "<<tokens[0]<<" "<<tokens[1]<<" "<<tokens[2]<<tokens[3]<<std::endl;
    }
    return tmpString;
}
