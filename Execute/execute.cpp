#include "execute.hpp"
#include "flags.hpp"

/*
lllcSuffix

this function adds suffix to the input string
if s option is set -> 7th bit is set
if there is some condition -> 8th bit is set and function returns true
-> also condition flags are set in byte 2
*/
std::string lllcSuffix(std::string options, unsigned long long line_number){
    std::string tmpString;
    char tmpChar;
    unsigned char len = options.length()-1;
    if(options.length()){
        unsigned char i=0;

        if('s' == options[0]){
            tmpString.push_back((char)(1<<6));
            i++;
        }
        if(len >=1){
            if('s' == options[len]){
                tmpString.push_back((char)(1<<7));
                tmpString[0] |= (1<<7);
            }else if('c' == options[len]){
                tmpString.push_back((char)0);
                tmpString[0] |= (1<<7);
            }else{
                std::cout<<"ERROR: unrecognized option: "<<options[len]<<" in line: "<<line_number<<std::endl;
                exit(0);
            }
        }

        for(;i<len;i++){
            tmpString[1] |= (1<<checkFlag(options[i],line_number));
        }
    }else{
        tmpString.push_back(0);
    }
    return tmpString;
}

static std::string executeSubparameter(std::string parameter, unsigned long int type, unsigned long long int line_number){
    unsigned char len = parameter.length();
    unsigned char tmpOffset=0;
    unsigned char tmpType=0;
    bool isflag=false;
    unsigned long long maxValue=0;
    unsigned long long actualValue=0;
    std::string tmpString;

    if("sreg" == parameter){
        tmpString.push_back('$');
        return tmpString;
    }

    switch(parameter[0]){
        case ':':
            if(type & label){
                tmpString=parameter;
                tmpString.push_back(' ');
                return tmpString;
            }else{
                std::cout<<"ERROR: label not allowed in this parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
                exit(0);
            }
        case '%':
            if(type & flag){
                tmpString.push_back(parameter[0]);
                tmpType = 1;
                isflag=true;
                actualValue = checkFlag(parameter[1],line_number);
                break;
            }else{
                std::cout<<"ERROR: flag not allowed in this parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
                exit(0);
            }
        case '@':
            if(type & cst){    
                tmpString.push_back(parameter[0]);
                tmpType = 1;
                tmpOffset=1;
                maxValue=0xFF;
                break;
            }else{
                std::cout<<"ERROR: constant not allowed in this parameter: "<<parameter<<" in line: "<<line_number<<std::endl;    
                exit(0);
            }
        case '*':
            if(type & indir){
                tmpString.push_back(parameter[0]);
                tmpType=2;
                tmpOffset=1;
                maxValue=0xFFFFFFFF;
                break;
            }else{
                std::cout<<"ERROR: indirect memory address not allowed in this parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
                exit(0);
            }
        case '&':
            if(type & mem){
                tmpString.push_back(parameter[0]);
                tmpType=2;
                tmpOffset=1;
                maxValue=0xFFFFFFFF;
            }else{
                std::cout<<"ERROR: memory address not allowed in this parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
                exit(0);
            }
        case 'r':
            if(type & reg){
                tmpString.push_back(parameter[0]);
                tmpType=1;
                tmpOffset=1;
                maxValue=0xFF;
                break;
            }else{
                std::cout<<"ERROR: register not allowed in this parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
                exit(0);
            }
        case '^':
            if(type & range){
                tmpString.push_back(parameter[0]);
                return tmpString;
            }else{
                std::cout<<"ERROR: stack pointer(range) not allowed in this parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
                exit(0);
            }
        case '$':
            if(type & range){
                tmpString.push_back(parameter[0]);
                return tmpString;
            }else{
                std::cout<<"ERROR: status register not allowed in this parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
            }
        default:
            if(type & v64){
                maxValue = 0xFFFFFFFFFFFFFFFF;
                tmpType = 3;
            }
            else if(type & v32){
               maxValue=0xFFFFFFFF;
               tmpType = 2;  
            } 
            else if((type & v8) | (type & bv)){
                tmpType = 1;
                maxValue=0xFF;
            }else{
                std::cout<<"ERROR: Wrong parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
                exit(0);
            }
            break;
    }

    if(!isflag){
        try{
            actualValue = std::stoull(parameter.substr(tmpOffset));
        }catch(std::invalid_argument& e){
            std::cout<<"ERROR: wrong parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
            exit(0);
        }catch(std::out_of_range& e){
            std::cout<<"ERROR: too large number in parameter: "<<parameter<<" in line: "<<line_number<<" parameter must not exceed: "<<maxValue<<std::endl;
            exit(0);
        }
    }

    switch(tmpType){
        case 3:
            tmpString.push_back((actualValue>>56) & 0xFF);
            tmpString.push_back((actualValue>>48) & 0xFF);
            tmpString.push_back((actualValue>>40) & 0xFF);
            tmpString.push_back((actualValue>>32) & 0xFF);
        case 2:
            tmpString.push_back((actualValue>>24) & 0xFF);
            tmpString.push_back((actualValue>>16) & 0xFF);
            tmpString.push_back((actualValue>>8)  & 0xFF);
        case 1:
            tmpString.push_back(actualValue & 0xFF);
            break;
        default:
        std::cout<<"COMPILER ERROR: execute parameter should never enter this state - tmpType: "<<(int)tmpType<<std::endl;
        exit(0);
    }

    return tmpString;
}


std::string executeParameter(std::string parameter, unsigned long int type, unsigned long long int line_number){
    std::string tmpString;
    unsigned char minusp=0;
    for(int i=0;i<parameter.length();i++){
        if('-' == parameter[i]){
            minusp = i;
        }
    }
    if(minusp){
        if(type & range){
            tmpString = executeSubparameter(parameter.substr(0,minusp),type,line_number);
            tmpString += "-";
            tmpString += executeSubparameter(parameter.substr(minusp+1),type,line_number);
        }else{
            std::cout<<"ERROR: range not allowed in parameter: "<<parameter<<" in line: "<<line_number<<std::endl;
            exit(0);
        }
    }else{
        tmpString = executeSubparameter(parameter,type,line_number);
    }
    return tmpString;
}

