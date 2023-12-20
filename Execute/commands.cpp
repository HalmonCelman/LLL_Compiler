#include "commands.hpp"
#include "execute.hpp"

unsigned long long int actual_offset=0;

std::vector <label_s> labels;

static void increaseJumpLength(unsigned char byWhat){
    std::vector <label_s>::iterator it=labels.begin();

    while(it != labels.end()){
        if(it->active){
            it->counter+=byWhat;
        }
        it++;
    }
    actual_offset += byWhat;
}

static std::vector <int> Exist(std::string name){
    std::vector <int> ait;

    for(int i=0;i<labels.size();i++){
        if(name == labels[i].name){
            ait.push_back(i);
        }
    }
    return ait;
}

static void processLabel(std::string name, bool fromDirective, unsigned long long int line_number){
    std::vector <int> ait=Exist(name);
    bool onced=true;
    bool oncend=true;

    if(ait.size()){
    for(int i=0;i<ait.size();i++){
        if( labels[ait[i]].fromDirective == true){
            if(fromDirective){
                std::cout<<"ERROR: duplicate of label: "<<name<<" in line: "<<line_number<<std::endl;
                exit(0);
            } else{
                label_s tmpLabel={name,labels[ait[i]].counter,true,false,false,actual_offset};
                labels.push_back(tmpLabel);
            }
        }else{
            if(fromDirective){
                if(onced){
                label_s tmpLabel={name,0,true,true,true,0};
                labels.push_back(tmpLabel);
                
                onced=false;
                }
                labels[ait[i]].active=false;
            }else{
                if(oncend){
                    if(labels[ait[i]].active){
                        label_s tmpLabel={name,0,false,false,true,actual_offset};
                        labels.push_back(tmpLabel);
                        oncend=false;
                    }
                }
            }
        }
    }
    } else{
        label_s tmpLabel;
        if(fromDirective){
            tmpLabel={name,0,true,true,true,0};
        }else{
            tmpLabel={name,0,false,false,true,actual_offset};
        }
        labels.push_back(tmpLabel);
    }
}


static void printLabelStatus(void){
    std::vector <label_s>::iterator it=labels.begin();

    while(it != labels.end()){
        std::cout<<"Label "<<it->name<<" active: "<<it->active<<" counter: "<<it->counter<<" minus: "<<it->minus<<" dir: "<<it->fromDirective<<" offset: "<<it->offset<<std::endl;
        it++;
    }
    std::cout<<std::endl;
}


const std::string& lllc_add(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_ADD;


    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | cst | range, line_number);
    tmpString += executeParameter(param3, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_and(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_AND;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | cst | range, line_number);
    tmpString += executeParameter(param3, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_cmp(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_CMP;

    tmpString += executeParameter(param1, reg | mem | flag | indir | cst | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_dec(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_DEC;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_div(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_DIV;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | cst | range, line_number);
    tmpString += executeParameter(param3, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_frjmp(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(5), line_number);
    tmpString[0] |= (char)LLL_FRJMP;

    tmpString.push_back(0);
    tmpString += executeParameter(param2, bv, line_number);
    
    processLabel(param1,false,line_number);
    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_in(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(2), line_number);
    tmpString[0] |= (char)LLL_IN;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, v8, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_inc(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_INC;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_jmp(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_JMP;

    tmpString.push_back(0);
    tmpString.push_back(0);
    tmpString.push_back(0);
    tmpString.push_back(0);
    tmpString.push_back(0);
    tmpString.push_back(0);
    tmpString.push_back(0);
    tmpString.push_back(0);

    tmpString += executeParameter(param2, bv, line_number);

    processLabel(param1,false,line_number);
    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_mov(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_MOV;

    tmpString += executeParameter(param1, reg | mem | flag | indir | cst | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_mul(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_MUL;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | cst | range, line_number);
    tmpString += executeParameter(param3, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_not(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_NOT;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_or(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(2), line_number);
    tmpString[0] |= (char)LLL_OR;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | cst | range, line_number);
    tmpString += executeParameter(param3, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_out(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_OUT;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, v8, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_pop(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_POP;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_push(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(4), line_number);
    tmpString[0] |= (char)LLL_PUSH;

    tmpString += executeParameter(param1, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}


const std::string& lllc_ret(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_RET;

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_rjmp(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(4), line_number);
    tmpString[0] |= (char)LLL_RJMP;

    tmpString.push_back(0);
    tmpString.push_back(0);
    tmpString.push_back(0);
    tmpString.push_back(0);

    tmpString += executeParameter(param2, bv, line_number);

    processLabel(param1,false,line_number);
    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_sub(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(3), line_number);
    tmpString[0] |= (char)LLL_SUB;

    tmpString += executeParameter(param1, reg | mem | flag | indir | range, line_number);
    tmpString += executeParameter(param2, reg | mem | flag | indir | cst | range, line_number);
    tmpString += executeParameter(param3, reg | mem | flag | indir | cst | range, line_number);

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_exit(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    tmpString = lllcSuffix(strcommand.substr(4), line_number);
    tmpString[0] |= (char)LLL_EXIT;

    increaseJumpLength(tmpString.length());

    return tmpString;
}

const std::string& lllc_def(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    std::cout << "def directive" << std::endl;
    return tmpString;
}

const std::string& lllc_label(std::string strcommand, std::string param1, std::string param2, std::string param3, unsigned long long int line_number)
{
    static std::string tmpString;
    tmpString="";

    processLabel(strcommand,true,line_number);
    return tmpString;
}