#include "end.hpp"
#include "commands.hpp"

#include <fstream>
#include <algorithm>

int toSkip=0;
int bytesToWrite=0;
unsigned long long int increaseJumpLength;
unsigned long long int valueToWrite=0;

struct by_offset
{
    inline bool operator() (const label_s& struct1, const label_s& struct2)
    {
        return (struct1.offset < struct2.offset);
    }
};

static std::string oneChar(char actualChar, unsigned long long int offset){
    std::string tmpString;
    
    if(!labels.size()){
        tmpString.push_back(actualChar);
        return tmpString;
    }

    if(labels[0].offset == offset){
        switch(actualChar){
            case LLL_FRJMP:
                toSkip=1;
                bytesToWrite=1;
                valueToWrite=(labels[0].minus ? -labels[0].counter:labels[0].counter);
                break;
            case LLL_RJMP:
                toSkip=4;
                bytesToWrite=4;
                valueToWrite=(labels[0].minus ? -labels[0].counter:labels[0].counter);
                break;
            case LLL_JMP:
                toSkip=8;
                bytesToWrite=8;
                valueToWrite=(labels[0].minus ? offset - labels[0].counter: offset+labels[0].counter);
                break;
            default:
                std::cout<<"ERROR: wrong offset"<<std::endl;
                exit(0);
        }
        tmpString.push_back(actualChar);
        
        labels.erase(labels.begin());
        
        return tmpString;
    }else{
        if(bytesToWrite == 1){
            tmpString.push_back(valueToWrite);
            bytesToWrite=0;
        }else if(bytesToWrite == 4){
            tmpString.push_back((valueToWrite>>24) & 0xFF);
            tmpString.push_back((valueToWrite>>16) & 0xFF);
            tmpString.push_back((valueToWrite>>8) & 0xFF);
            tmpString.push_back((valueToWrite) & 0xFF);
            bytesToWrite=0;
        }else if(bytesToWrite == 8){
            tmpString.push_back((valueToWrite>>56) & 0xFF);
            tmpString.push_back((valueToWrite>>48) & 0xFF);
            tmpString.push_back((valueToWrite>>40) & 0xFF);
            tmpString.push_back((valueToWrite>>32) & 0xFF);
            tmpString.push_back((valueToWrite>>24) & 0xFF);
            tmpString.push_back((valueToWrite>>16) & 0xFF);
            tmpString.push_back((valueToWrite>>8) & 0xFF);
            tmpString.push_back((valueToWrite) & 0xFF);
            bytesToWrite=0;
        }else{
            if(toSkip){
                toSkip--;
            }else{
                tmpString.push_back(actualChar);
            }
        }
        return tmpString;
    }
}


std::string endOfCompiling(std::string path){ 
    std::string resultString;

    for(int i=0;i<labels.size();i++){
        if(labels[i].active){
            if(labels[i].fromDirective){
                labels.erase(labels.begin()+i);
            }else{
                std::cout<<"ERROR: label "<<labels[i].name<<" not found"<<std::endl;
                exit(0);
            }
        }
    }

    std::sort(labels.begin(),labels.end(),by_offset());

    std::ifstream in;
    in.open(path,std::ios::in | std::ios::binary);
    if(!in.is_open()){
        std::cout<<"ERROR: cannot open temporary output file"<<std::endl;
        exit(0);
    }
    char actualChar;

    for(unsigned long long int i=0; in.get(actualChar); i++){
        resultString += oneChar(actualChar, i);
    }

    in.close();
    return resultString;
}
