#ifndef TOKENCOMPOSITE_H
#define TOKENCOMPOSITE_H
#include "baseshell.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <iostream>
#include "parser.h"
#include "token.h"

//Component class that has container of Token objects and will execute them
class TokenComposite : public BaseShell
{
public:
    TokenComposite();
        //container of BaseShell objects 
    std::vector<BaseShell*> commands;
        //loop that encapsualtes all the functions and will be used in main
    void shellLoop();
        //will iterate through commands vector and call execute on the leaf nodes
    void execute();
private:
        //user input
    std::string command;
    Parser parser;
        //user login
    struct passwd *login;
        //user hostname 
    char hostname[128];
        //vector will hold the connectors ; || &&
    std::vector<char> connectors;
        //static flag for exit command
    static int exitHit;

};

#endif // TOKENCOMPOSITE_H
