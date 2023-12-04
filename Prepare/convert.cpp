#include "convert.hpp"

#include <iostream>
#include <fstream>

/*
converts 'HIGH' letters from input file: in_f
into 'low' letters:
A->a
B->b etc
and writes everything into output file: out_f
*/
void convertFileToLowLetters(const char * out_f,const char * in_f){
    std::ofstream out;
    std::ifstream in;

    std::string line;

    out.open(out_f,std::ios::out | std::ios::trunc);
    if(!out.is_open()){
        std::cout<<"ERROR: Failed to create tmp output file: "<<out_f<<std::endl;
        exit(0);
    }

    in.open(in_f,std::ios::in);
    if(!in.is_open()){
        std::cout<<"ERROR: Failed to open input file: "<<in_f<<std::endl;
        exit(0);
    }


    while(std::getline(in,line)){
        for(int i=0;i<line.length();i++){
            if(('A'<=line[i]) && (line[i]<='Z')){
                line[i]+=32;
            }
        }
        out<<line;
        out<<'\n';
    }

    in.close();
    out.close();

}

