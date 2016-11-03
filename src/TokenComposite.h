#ifndef TOKENCOMPOSITE_H
#define TOKENCOMPOSITE_H
#include "BaseShell.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <iostream>
#include "Parser.h"
#include "Token.h"

class TokenComposite : public BaseShell
{

    private:
        std::string command;
        Parser parser;
        struct passwd *login;
        char hostname[128];
        std::vector<char> connectors;
        static int exitHit; 

    public:
        std::vector<BaseShell*> commands;
        void shellLoop();
        void execute();

        ~TokenComposite();
        TokenComposite();
};

#endif // TOKENCOMPOSITE_H
