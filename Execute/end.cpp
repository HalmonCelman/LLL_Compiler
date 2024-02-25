#include "end.hpp"
#include "commands.hpp"

#include <fstream>
#include <algorithm>

int toSkip=0;
int bytesToWrite=0;
unsigned long long int increaseJumpLength;
unsigned long long int valueToWrite=0;
bool minus;

/*
constructor for sorting by offset
*/
struct by_offset
{
    inline bool operator() (const label_s& struct1, const label_s& struct2)
    {
        return (struct1.offset < struct2.offset);
    }
};

/*
    writes actual char into output file:
    - if label, writes its counter
    - if not, gives unchanged char
*/
static const std::string& oneChar(char actualChar, unsigned long long int offset){
    static unsigned char delay=0;
    static std::string tmpString;
    tmpString="";

    if(labels.size() && labels[0].offset == offset){
        std::cout<<"\n";
        if(actualChar & 0x80) delay=1;

        switch(actualChar & 0x3F){
            case LLL_FRJMP:
                toSkip=delay;
                bytesToWrite=1;
                valueToWrite=labels[0].counter;
                break;
            case LLL_RJMP:
                toSkip=3+delay;
                bytesToWrite=4;
                valueToWrite=labels[0].counter;
                break;
            case LLL_JMP:
                toSkip=7+delay;
                bytesToWrite=8;
                valueToWrite=(labels[0].minus ? offset - labels[0].counter: offset+labels[0].counter);
                break;
            default:
                std::cout<<"ERROR: wrong offset"<<std::endl;
                exit(0);
        }
        minus = labels[0].minus;
        tmpString.push_back(actualChar);
        
        labels.erase(labels.begin());
        
        return tmpString;
    }else{
        if(delay){
            delay=0;
            tmpString.push_back(actualChar);
        }if(bytesToWrite == 1){
            tmpString.push_back((char)(minus ? -valueToWrite:valueToWrite));
            bytesToWrite=0;
        }else if(bytesToWrite == 4){
            long int actValue = (minus ? -valueToWrite:valueToWrite);
            tmpString.push_back((actValue>>24) & 0xFF);
            tmpString.push_back((actValue>>16) & 0xFF);
            tmpString.push_back((actValue>>8) & 0xFF);
            tmpString.push_back((actValue) & 0xFF);
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

/*
1. Deletes all active labels, checks if some jumps are redundant
2. sorts labels
3. writes all labels with their counters, leaves everything unchanged
*/
const std::string& endOfCompiling(std::string path){ 
    static std::string resultString;
    int i=0;
    while(i<labels.size()){
        if(labels[i].active){
            if(labels[i].fromDirective){
                labels.erase(labels.begin()+i);
            }else{
                std::cout<<"ERROR: label "<<labels[i].name<<" not found"<<std::endl;
                exit(0);
            }
        }else{
            i++;
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
