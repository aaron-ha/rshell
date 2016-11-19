#ifndef TOKENCOMPOSITE_H
#define TOKENCOMPOSITE_H
#include "baseshell.h"
#include "parser.h"
#include "token.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <iostream>

//Component class that has container of Token objects and will execute them
class TokenComposite : public BaseShell
{
public:
    TokenComposite();
        //container of BaseShell objects 
    std::vector<Token*> commands;
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
   
    static bool compositeSuccess; 
    bool validateString(std::string str); 
    

};

#endif // TOKENCOMPOSITE_H
