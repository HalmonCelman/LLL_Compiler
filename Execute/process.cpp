#include "process.hpp"
#include "execute.hpp"


typedef enum{
    TOKEN,
    DELIMITER
} STATUS;

STATUS status=DELIMITER;
bool readyToExecute=false;
unsigned char error=0;

std::string tokens[3];
unsigned char actual_token = 0;
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

static void process(char actual_character, unsigned long long int line_number){
    switch(status){
        case TOKEN:
            if(isDelimiter(actual_character)){
                actual_token++;

                if(actual_token == 1){
                    actual_command = compareCommands(tokens[0],line_number);
                    actual_number_of_tokens = getNumberOfTokens(actual_command);
                }

                if(actual_token == actual_number_of_tokens){
                    readyToExecute=true;
                }
                status=DELIMITER;
            }else{
                tokens[actual_token].push_back(actual_character);
            }

        break;
        case DELIMITER:
            if(!isDelimiter(actual_character)){
                tokens[actual_token].push_back(actual_character);
                status = TOKEN;
            }
        break;
    }
}

static void processCommand(unsigned long long int line_number){
    if(readyToExecute){
        executeCommand(actual_command,tokens[0],tokens[1],tokens[2],line_number);
        tokens[0].clear();
        tokens[1].clear();
        tokens[2].clear();
        readyToExecute = false;
        actual_token = 0;
        actual_number_of_tokens = 1;
    }
}

void processTokensInLine(std::string line, unsigned long long int line_number){
    for(int i=0;line[i];i++){
        #if DEBUG_MODE
            std::cout<<"processing: '"<<line[i]<<"' \n";
        #endif
        process(line[i], line_number);
        
        processCommand(line_number);
    }
}

void endOfLine(unsigned long long int line_number){
    process(' ', line_number);
    processCommand(line_number);
}

void endOfProcessing(unsigned long long int line_number){
    process(' ', line_number);
    processCommand(line_number);
    if(actual_token || tokens[0].length()){
        std::cout<<"ERROR: Unexpected End Of File: "<<tokens[0]<<" "<<tokens[1]<<" "<<tokens[2]<<std::endl;
    }
}
