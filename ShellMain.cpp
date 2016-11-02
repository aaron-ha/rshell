#include <iostream>
#include "BaseShell.h"
#include "TokenComposite.cpp"
#include "Token.cpp"
#include "Parser.cpp"

int main()
{
   TokenComposite* tokens = new TokenComposite(); 
  
  
   const char* cmd1[] = {"echo", "-apples", NULL}; 
   const char* cmd2[] = {"echo", "test2", NULL}; 
   const char* cmd3[] = {"echo", "test3", NULL}; 
  
   Token* tk1 = new Token(cmd1); 
   Token* tk2 = new Token(cmd2); 
   Token* tk3 = new Token(cmd3); 
  
   tokens->commands.push_back(tk1); 
   tokens->commands.push_back(tk2);
   tokens->commands.push_back(tk3);
   
   tokens->execute(); 
  
    /*string command;
    //Take in user input for RShell in the form of char*
    // ex: ls -a; echo meow
    cout << "Command: ";
    getline(cin, command);
    cout << command << endl;
    
    Parser* parse = new Parser(command);
    vector<string> myVector = parse->divideString(command);
    TokenComposite* tokens = new TokenComposite();
    vector<Token*> cmdList = parse->cmdsToVector();
    // const char** cmd1 = parse->makePtArr(myVector.at(0));
    
    for(int i = 0; i < cmdList.size(); i++){
        tokens->commands.push_back(cmdList.at(i));
    }
    
    // Token* tk1 = new Token(cmd1);

    // tokens->commands.push_back(tk1);

    tokens->execute();*/
}