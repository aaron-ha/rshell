#include <iostream>
#include "baseshell.h"
#include "token.h"
#include "tokencomposite.h"
#include "parser.h"

using namespace std;

int main() //call loop that will handle all the processes 
{
    TokenComposite token;
    token.shellLoop();
    return 0;
}
