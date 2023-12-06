#include "commands.hpp"
#include "execute.hpp"

std::string lllc_add   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|cst|range, line_number);
    tmpString += executeParameter(param3, reg|mem|flag|indir|cst|range, line_number);

    return tmpString;
}

std::string lllc_and   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_AND;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|cst|range, line_number);
    tmpString += executeParameter(param3, reg|mem|flag|indir|cst|range, line_number);

    return tmpString;
}

std::string lllc_cmp   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
        std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|cst|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|cst|range, line_number);

    return tmpString;    
}

std::string lllc_dec   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);

    return tmpString;
}

std::string lllc_div   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|cst|range, line_number);
    tmpString += executeParameter(param3, reg|mem|flag|indir|cst|range, line_number);

    return tmpString;
}

std::string lllc_frjmp (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::cout<<"frjmp command"<<std::endl;
    return "";
}

std::string lllc_in    (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, v8 , line_number);

    return tmpString;
}

std::string lllc_inc   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);

    return tmpString;
}

std::string lllc_jmp   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::cout<<"jmp command"<<std::endl;
    return "";
}

std::string lllc_mov   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|cst|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|range, line_number);

    return tmpString;
}

std::string lllc_mul   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|cst|range, line_number);
    tmpString += executeParameter(param3, reg|mem|flag|indir|cst|range, line_number);

    return tmpString;
}

std::string lllc_not   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|cst|range, line_number);
    
    return tmpString;
}

std::string lllc_or    (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|cst|range, line_number);
    tmpString += executeParameter(param3, reg|mem|flag|indir|cst|range, line_number);

    return tmpString;
}

std::string lllc_out   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, v8 , line_number);

    return tmpString;
}

std::string lllc_ret   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    return tmpString;
}

std::string lllc_rjmp  (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::cout<<"rjmp command"<<std::endl;
    return "";
}

std::string lllc_sub   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    tmpString += executeParameter(param1, reg|mem|flag|indir|range, line_number);
    tmpString += executeParameter(param2, reg|mem|flag|indir|cst|range, line_number);
    tmpString += executeParameter(param3, reg|mem|flag|indir|cst|range, line_number);

    return tmpString;
}

std::string lllc_exit  (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::string tmpString;

    tmpString = lllcSuffix(options,line_number);
    tmpString[0] |= (char)LLL_ADD;
    
    return tmpString;
}

std::string lllc_def   (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::cout<<"def directive"<<std::endl;
    return "";
}

std::string lllc_label (std::string options, std::string param1,std::string param2,std::string param3,unsigned long long int line_number){
    std::cout<<"label directive"<<std::endl;
    return "";
}