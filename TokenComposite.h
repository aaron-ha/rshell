#ifndef TOKENCOMPOSITE_H
#define TOKENCOMPOSITE_H
#include "BaseShell.h"
//#include<unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
//#include "Parser.cpp"

class TokenComposite : public BaseShell 
{
    
    private: 
        std::string argv; 
        //Parser parser; 
        //std::vector<BaseShell*> commands; 
        char *buffer; 
    public: 
    std::vector<BaseShell*> commands;
    
    
    //TokenComposite();
    void shelloop();
    //this will iterate through the container of token objects and call execute on them
    void execute();
}; 
#endif