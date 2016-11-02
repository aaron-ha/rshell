#include <iostream>
#include "BaseShell.h"
#include "TokenComposite.h"
#include "TokenComposite.cpp"
#include "Token.h"
#include "Token.cpp"

int main()
{
  TokenComposite* tokens = new TokenComposite(); 
  
  
  const char* cmd1[] = {"ls", "-a", NULL}; 
  const char* cmd2[] = {"mkdir", "test1", NULL}; 
  
  Token* tk1 = new Token(cmd1); 
  Token* tk2 = new Token(cmd2); 
  
  tokens->commands.push_back(tk1); 
  tokens->commands.push_back(tk2);
   
  tokens->execute(); 
  
    
}