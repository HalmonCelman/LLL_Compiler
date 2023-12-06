#include "flags.hpp"

#include <iostream>

unsigned char checkFlag(char flag, unsigned long long line_number){
    switch(flag){
        case 'o': return 0;
        case 'a': return 1;
        case 'r': return 2;
        case 'z': return 3;
        default:
            std::cout<<"ERROR: unrecognized flag: "<<flag<<" in line: "<<line_number<<std::endl;
            exit(0);
    }
}