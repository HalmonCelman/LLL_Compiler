#include "convert.hpp"

#include <iostream>
#include <fstream>

static void joinString(char * where,char * what){
    while( *where++ = *what++);
    *where=0;
}


void convertFileToLowLetters(const char * out_file,const char * in_file){
    std::ofstream out;
    std::ifstream in;

    std::string line;

    out.open(out_file,std::ios::out | std::ios::trunc);
    if(!out.is_open()){
        std::cout<<"ERROR: Failed to create tmp output file: "<<out_file<<std::endl;
        exit(0);
    }

    in.open(in_file,std::ios::in);
    if(!in.is_open()){
        std::cout<<"ERROR: Failed to open input file: "<<in_file<<std::endl;
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

const char * makeTmpFilename(std::string dir,const char * file){
    dir.push_back('/');
    joinString(&dir[dir.length()],(char *)file);
    return dir.c_str();
}


