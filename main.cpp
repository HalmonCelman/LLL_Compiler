#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>

#include <convert.hpp>
#include <help.hpp>
#include <process.hpp>
#include <end.hpp>

#ifdef _WIN32
    int mkdir(const char * path,int options){
        return mkdir(path);
    }
#endif


int main(int args, char **argv){
    if(args>2){
        std::cout<<"Initializing..."<<std::endl;

        // creating temporary files
        std::string TMP_DIR="lllc_tmp";
        if(mkdir(TMP_DIR.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)){
            if(errno == EEXIST){
                std::cout<<"NOTE: temporary folder already exist - overwriting"<<std::endl;
            } else{
                std::cout<<"ERROR: cannot create temporary dir \n check permissions for lllc"<<std::endl;
                exit(0);
            }
        }

        std::ofstream out_file;
        std::fstream tmp_out_file;
        std::ifstream in_file;
        std::string line;
        unsigned long long int line_number;

        std::string without_jumps_file = TMP_DIR + "/" + (std::string)(argv[1]);

        tmp_out_file.open(without_jumps_file,std::ios::out | std::ios::trunc);

        if(!tmp_out_file.is_open()){
            std::cout<<"Failed to open temporary output file: "<<without_jumps_file<<std::endl;
            exit(0);
        }

        out_file.open(argv[1], std::ios::out | std::ios::in | std::ios::trunc);

        if(!out_file.is_open()){
            std::cout<<"Failed to open output file: "<<argv[1]<<std::endl;
            exit(0);
        }

        // compile loop
        for(int i=2; i<args; i++){

            line_number = 1;
            std::cout<<std::endl;

            std::string compiled_file = TMP_DIR + "/" + (std::string)(argv[i]);
            convertFileToLowLetters(compiled_file.c_str(), argv[i]); // non sensitive 

            in_file.open(compiled_file, std::ios::in);
            if(!in_file.is_open()){
                std::cout<<"Failed to open tmp input file: "<<compiled_file<<std::endl;
                exit(0);
            } else{
                std::cout<<"Compiling "<<compiled_file<<std::endl;
            }
            while(std::getline(in_file,line)){
                tmp_out_file << processTokensInLine(line, line_number);
                
                line_number++;
            }
            tmp_out_file << endOfProcessing(line_number);

            in_file.close();
        }
        tmp_out_file.close();

        out_file << endOfCompiling(without_jumps_file);
        out_file.close();
        // deleting temporary files
        std::filesystem::remove_all(TMP_DIR.c_str());
    } else{
        if(!strcmp(argv[1],"--help")){
            help();
        }else{
            std::cout<<"ERROR: No input files detected! \n write lllc --help to get help"<<std::endl;
        }
    }


    
    return 0;
}
