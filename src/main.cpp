#include <iostream>
#include "baseshell.h"
#include "token.h"
#include "tokencomposite.h"
#include "parser.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.cpp"
#include "tokencomposite.cpp"
#include "parser.cpp"

using namespace std;

int main() //call loop that will handle all the processes 
{
   TokenComposite token;
   token.shellLoop();
   return 0;
    /*struct stat sb; 
    const char* argv[] = {"test", "-e","/home/ubuntu/workspace/src"};  
    
     if (stat(argv[2], &sb) == -1) {
               perror("stat");
               exit(EXIT_FAILURE);
           }
    if(S_ISREG(sb.st_mode)){
        std::cout << "true" << std::endl; 
    }
    else if(S_ISDIR(sb.st_mode)){
        std::cout << "directory" << std::endl; 
    }*/
    
}

