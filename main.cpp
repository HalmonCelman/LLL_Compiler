#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>

#include <convert.hpp>
#include <help.hpp>
#include <process.hpp>

int main(int args, char **argv){
    if(args>2){
        std::cout<<"Initializing..."<<std::endl;

        // creating temporary files
        std::string TMP_DIR="lllc_tmp";
        if(mkdir(TMP_DIR.c_str())){
            if(errno == EEXIST){
                std::cout<<"NOTE: temporary folder already exist - overwriting"<<std::endl;
            } else{
                std::cout<<"ERROR: cannot create temporary dir \n check permissions for lllc"<<std::endl;
                exit(0);
            }
        }

        std::ofstream out_file;
        std::ifstream in_file;
        std::string line;
        unsigned long long int line_number = 0;


        out_file.open(argv[1],std::ios::out | std::ios::trunc);
        if(!out_file.is_open()){
            std::cout<<"Failed to open output file: "<<argv[1]<<std::endl;
            exit(0);
        }

        // compile loop
        for(int i=2; i<args; i++){
            const char * compiled_file=makeTmpFilename(TMP_DIR,argv[i]);
            convertFileToLowLetters(compiled_file, argv[i]); // non sensitive 

            in_file.open(compiled_file, std::ios::in);
            if(!in_file.is_open()){
                std::cout<<"Failed to open tmp input file: "<<compiled_file<<std::endl;
                exit(0);
            } else{
                std::cout<<"Compiling "<<compiled_file<<std::endl;
            }

            while(std::getline(in_file,line)){
                processTokensInLine(line, line_number);
                endOfLine();
            }
            endOfProcessing();

            in_file.close();
        }

        out_file.close();
        // deleting temporary files
        //std::filesystem::remove_all(TMP_DIR.c_str());
    } else{
        if(!strcmp(argv[1],"--help")){
            help();
        }else{
            std::cout<<"ERROR: No input files detected! \n write lllc --help to get help"<<std::endl;
        }
    }


    
    return 0;
}
