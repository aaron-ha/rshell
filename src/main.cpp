#include <iostream>
#include "baseshell.h"
#include "token.h"
#include "tokencomposite.h"
#include "parser.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.cpp"
#include "tokencomposite.cpp"
#include "parser.cpp"

using namespace std;

int main() //call loop that will handle all the processes 
{
   TokenComposite token;
   token.shellLoop();
   return 0;
    
}

