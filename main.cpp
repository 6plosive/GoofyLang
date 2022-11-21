#include <iostream>
#include <fstream>
#include <stdio.h>
int decrypttable[10]{4, 3, 5, 0, 6, 2, 7, 1, 9, 8};
int decrypt(std::string& s){//(int)'0' = 48, (int)'9' = 57
    int result=0;
    for(int c:s){
        if(48<=c&&c<=57){//ignore characters, act as comment
            result=result*10+decrypttable[(c-48)];
        }
    }
    return result;
}
int main(int argc, const char * argv[]) {
    if(argc != 3 && argc != 4){
        std::cout<<"Usage: "<<argv[0]<<" inputfile.goofy outputfilename (optional)--keepcpp"<<std::endl;
        return 1;
    }
    std::string inputFilepath(argv[1]);
    std::string outputFilename(argv[2]);
    outputFilename+=".cpp";
    std::string arg3="";
    if(argc==4) arg3=argv[3];
    bool keepcpp=false;
    if(arg3=="--keepcpp") keepcpp=true;
    std::cout<<"[INFO] keepcpp = "<<std::boolalpha<<keepcpp<<std::endl;
    std::cout << "[INFO] Input Filename=\""<<inputFilepath<<"\"\n";
    if(keepcpp) std::cout << "[INFO] Output Filename=\""<<outputFilename<<"\"\n";
    std::cout<<"[INFO] Binary Filename=\""<<outputFilename.substr(0, outputFilename.length()-4)<<"\"\n";
    
    std::string line;
    std::string compileCommand="g++ "+outputFilename+" -o "+outputFilename.substr(0, outputFilename.length()-4);
    
    std::ifstream inputFile(inputFilepath.c_str());
    std::ofstream outputCode(outputFilename.c_str());
    if (inputFile.is_open() && outputCode.is_open()){
        while (inputFile>>line){
            char c=decrypt(line);
            if(c!=0) outputCode<<c;
        }
        inputFile.close();
        outputCode.close();
    }else{
        std::cout << "[ERROR] Unable to open file\n";
    }
    system(compileCommand.c_str());
    while(outputCode.is_open()){}
    if(!keepcpp) remove(outputFilename.c_str());
    outputFilename="./"+outputFilename;
    system(outputFilename.substr(0, outputFilename.length()-4).c_str());
    return 0;
}
