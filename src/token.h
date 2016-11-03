#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
};

#endif // TOKEN_H
