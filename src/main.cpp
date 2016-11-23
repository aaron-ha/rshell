#include <iostream>
#include "baseshell.h"
#include "token.h"
#include "tokencomposite.h"
#include "parser.h"
#include <unistd.h>
using namespace std;

int main() //call loop that will handle all the processes 
{
    TokenComposite token;
    token.shellLoop();
    return 0;
    
//   const char* temp; 
//   setenv("OLDPWD", "/home/ubuntu", 1);
//     if(chdir(getenv("OLDPWD")) == -1){
//             perror("Error changing directores");
//         }
//         temp = getenv("PWD");
//         setenv("PWD", getenv("OLDPWD"), 1); 
//         setenv("OLDPWD", temp, 1); 
       
//     if(chdir(getenv("OLDPWD")) == -1){
//             perror("Error changing directores");
//         } 
    
   
//      cout << "After: " << endl;
//      execvp(argv[0], (char**)argv);
}

