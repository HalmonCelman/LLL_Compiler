#include "help.hpp"

#include <iostream>

void help(void){
    std::cout<<"write: \n lllc <output_file.l> <input_file1.lll> [<input_file2.lll> <input_file3.lll> ...]"<<std::endl;
    std::cout<<"\n You must provide at least name of output file and name of first input file \n"<<std::endl;
}