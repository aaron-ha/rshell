#ifndef TOKENCOMPOSITE_H
#define TOKENCOMPOSITE_H
#include "BaseShell.h"
//#include<unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "Parser.h"

class TokenComposite : public BaseShell 
{
    
    private: 
        std::string argv; 
        Parser parser; 
        char *buffer; 
        std::vector<char> connectors;
        
    public: 
        std::vector<BaseShell*> commands;
        TokenComposite(){};
        void shelloop();
        void execute();
        //this will iterate through the container of token objects and call execute on them
        
}; 
#endif