#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "BaseShell.h"

using namespace std;

class Token : public BaseShell
{

private:
    //const char** command;
public:
    Token(const char** argv);
    void execute();
};

#endif // TOKEN_H
