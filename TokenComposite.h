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
        std::string command; 
        Parser parser; 
        struct passwd *login; 
        char hostname[128];  
        std::vector<char> connectors;
        
    public: 
        std::vector<BaseShell*> commands;
        TokenComposite(){};
        void shellLoop();
        void execute();
        //this will iterate through the container of token objects and call execute on them
        
}; 
#endif