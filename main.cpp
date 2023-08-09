#include <iostream>
#include <fstream>

typedef enum{
    LLL_ADD = 0,
    LLL_ADDI,
    LLL_SUB,
    LLL_SUBI,
    LLL_MUL,
    LLL_MULI,
    LLL_DIV,
    LLL_DIVI,
    LLL_AND,
    LLL_ANDI,
    LLL_OR,
    LLL_ORI,
    LLL_NOT,
    LLL_INC,
    LLL_DEC,
    LLL_SER,
    LLL_SERI,
    LLL_LJMP,
    LLL_JMP,
    LLL_RET,
    LLL_CMP,
    LLL_CMPI,
    LLL_SEQ,
    LLL_DEQ,
    LLL_SLO,
    LLL_DLO,
    LLL_SGR,
    LLL_DGR,
    LLL_IN,
    LLL_OUT,
    LLL_EXIT=255
} lll_command_list;




std::ofstream out_file;
std::ifstream in_file;
std::string line;

bool status;

void findAllAndChange(void);
lll_command_list compareCommands(void);
std::string getStringFromString(std::string,unsigned int);

int main(int args, char **argv){
    if(args < 3){
        std::cout<<"enter files to compile"<<std::endl;
    }else{
        
        out_file.open(argv[1],std::ios::out | std::ios::trunc);

        std::cout<<"loading files..."<<std::endl;
        for(int i=2;i<args;i++){
            std::cout<<"Compiling file: "<<argv[i]<<std::endl;
            in_file.open(argv[i],std::ios::in);
            while(std::getline(in_file,line)){
                findAllAndChange();
            }
        }
    }
    return 0;
}


std::string getStringFromString(std::string str1,unsigned int whichOne){
    status=false;
    std::string str2;
    for(int i=0;i<str1.length();i++){
        switch(str1[i]){
            case 0:
            case '\t':
            case '\r':
            case '\n':
            case ' ':
            case ',':
            case ';':
                if(status){
                    if(!whichOne){
                        return str2;
                    }else{
                        whichOne--;
                    }
                    status=false;
                }
            break;
            default:
                status=true;
                if(!whichOne){
                    str2.push_back(str1[i]);
                }
        };
    }

    if(!whichOne){
        return (str2.length() ? str2 : " ");
    }

    return " ";
}


lll_command_list compareCommands(std::string strcommand){

    if("add" == strcommand){ return LLL_ADD; }
    if("addi" == strcommand){ return LLL_ADDI; }
    if("sub" == strcommand){ return LLL_SUB; }
    if("subi" == strcommand){ return LLL_SUBI; }
    if("mul" == strcommand){ return LLL_MUL; }
    if("muli" == strcommand){ return LLL_MULI; }
    if("div" == strcommand){ return LLL_DIV; }
    if("divi" == strcommand){ return LLL_DIVI; }
    if("and" == strcommand){ return LLL_AND; }
    if("andi" == strcommand){ return LLL_ANDI; }
    if("or" == strcommand){ return LLL_OR; }
    if("ori" == strcommand){ return LLL_ORI; }
    if("not" == strcommand){ return LLL_NOT; }
    if("inc" == strcommand){ return LLL_INC; }
    if("dec" == strcommand){ return LLL_DEC; }
    if("ser" == strcommand){ return LLL_SER; }
    if("seri" == strcommand){ return LLL_SERI; }
    if("ljmp" == strcommand){ return LLL_LJMP; }
    if("jmp" == strcommand){ return LLL_JMP; }
    if("ret" == strcommand){ return LLL_RET; }
    if("cmp" == strcommand){ return LLL_CMP; }
    if("cmpi" == strcommand){ return LLL_CMPI; }
    if("seq" == strcommand){ return LLL_SEQ; }
    if("deq" == strcommand){ return LLL_DEQ; }
    if("slo" == strcommand){ return LLL_SLO; }
    if("dlo" == strcommand){ return LLL_DLO; }
    if("sgr" == strcommand){ return LLL_SGR; }
    if("dgr" == strcommand){ return LLL_DGR; }
    if("in" == strcommand){ return LLL_IN; }
    if("out" == strcommand){ return LLL_OUT; }
    if("exit" == strcommand){ return LLL_EXIT; }

    std::cout<<"ERROR: wrong command: "<<strcommand<<std::endl;
    exit(0);
}

void findAllAndChange(void){
    bool is64b=false;
    bool is32b=false;
    int command=0;
    std::string str;
    unsigned int i=0;
    do{
        str=getStringFromString(line,i);
        if(str != " "){
        if(str[0] == '#'){ //comment
            return;
        }else if(is64b){
            unsigned long long int strVal=std::stoi(&str[0]);
            out_file<<(char)(strVal>>56);
            out_file<<(char)(strVal>>48);
            out_file<<(char)(strVal>>40);
            out_file<<(char)(strVal>>32);
            out_file<<(char)(strVal>>24);
            out_file<<(char)(strVal>>16);
            out_file<<(char)(strVal>>8);
            out_file<<(char)(strVal);
            is64b=false;
        }else if(str[0] == '&' || str[0] == '*' || str[0] == ':' || is32b){ //register or label
            if(!is32b){
            out_file<<(char)str[0];
            }
            unsigned int strVal=std::stoi(&str[is32b?0:1]);
            out_file<<(char)(strVal>>24);
            out_file<<(char)(strVal>>16);
            out_file<<(char)(strVal>>8);
            out_file<<(char)(strVal);
            is32b=false;
        }else if(str[0]=='%'){
            out_file<<(char)str[0];
            out_file<<(char)str[1];
        }else if((str[0] >= '0') && (str[0] <= '9')) {  //INT
            out_file<<(char)std::stoi(str);
        }else if(str.length()==1){                      // char
            out_file<<(char)str[0];
        }else{ //command
            command=compareCommands(str);
            if(command == LLL_JMP){
                is64b=true;
            }else if(command == LLL_LJMP){
                is32b=true;
            }
            out_file<<(char)command;
        }
        i++;
        }
    }while(str!=" ");
}