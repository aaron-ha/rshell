#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "baseshell.h"

//Token Class that will encapsulate the individual commands 
class Token : public BaseShell
{
public:
    //constructor will take the character pointer array for us in execvp
    Token(const char** argv);
    
    //will execute the individual program
    void execute();
    //will test function
    void test(const char**);
    
    //use these two member variables the parser is in parenthesis
    vector<Token> tokens; 
    vector<char> connectors; 
    
};

#endif // TOKEN_H
