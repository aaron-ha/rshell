#include <iostream>
#include "BaseShell.h"
#include "Token.cpp"
#include "TokenComposite.cpp"
#include "Parser.cpp"

using namespace std;

int main()
{
    TokenComposite token;
    token.shellLoop();
    return 0;
}

