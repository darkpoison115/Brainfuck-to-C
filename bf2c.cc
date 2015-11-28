#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

void fatalError();

std::string compile(std::string);

int main(int argc,char** argv){
    
    if(argc!=2){
        fatalError();
    } 
    else{
        std::string fileName = argv[1];
        std::ifstream bfFile;
        std::ofstream cFile;
        
        bfFile.open((fileName+".bf").c_str());
        
        if(bfFile.fail()){
            perror((fileName+".bf").c_str());
        }
        
        std::stringstream strStream;
        
        strStream << bfFile.rdbuf();
        
        std::string input = strStream.str();
        
        bfFile.close();
        
        cFile.open((fileName+".c").c_str());
        
        cFile << compile(input);
        
        cFile.close();
        
        std::cout<<"Done!"<<std::endl;
        
    }
    
    return 0;
}

void fatalError(){
    std::cerr<<"Fatal error!"<<std::endl;
    exit(1);
}

std::string compile(std::string in){
    
    //https://en.wikipedia.org/wiki/Brainfuck
    
    /******************************************************************
    *                     *   char array[infinitely large size] = {0};* <= of course this is not possible!
    *   (Program Start)   *                                           *
    *                     *   char *ptr=array;                        *
    *******************************************************************
    *          >          *   ++ptr;                                  *
    *******************************************************************
    *          <          *   --ptr;                                  *
    *******************************************************************
    *          +          *   ++*ptr;                                 *
    *******************************************************************
    *          -          *   --*ptr;                                 *
    *******************************************************************
    *          .          *   putchar(*ptr);                          *
    *******************************************************************
    *          ,          *   *ptr=getchar();                         *
    *******************************************************************
    *          [          *   while (*ptr) {                          *
    * *****************************************************************
    *          ]          *   }                                       *
    ******************************************************************/
    
    std::string out;
    
    out += "#include <stdio.h> \n\n";
    out += "int main(){\n";
    out += "char array[1024] = {0};\n"; //TODO: allow configure this.
    out += "char *ptr=array;\n";
    
    for ( std::string::iterator it=in.begin(); it!=in.end(); ++it){
        
        switch(*it){
            case '>':
                out += "++ptr;";
                break;
            case '<':
                out += "--ptr;";
                break;
            case '+':
                out += "++*ptr;";
                break;
            case '-':
                out += "--*ptr;";
                break;
            case '.':
                out += "putchar(*ptr);";
                break;
            case ',':
                out += "*ptr=getchar();";
                break;
            case '[':
                out += "while (*ptr) {";
                break;
            case ']':
                out += "}";
                break;
            default:
                //ignore
                break;
        }
        
    }
    
    out += "\n}";
    
    return out;
}