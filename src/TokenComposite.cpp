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
#include "TokenComposite.h"

void TokenComposite::shellLoop()
{
    login = getpwuid(getuid());
    gethostname(hostname, sizeof hostname); 
    while(1){
        std::cout << (login->pw_name); 
        std::cout << "@"; 
        std::cout << hostname << "$"; 
        
            //get user input
        getline(cin, command); 
        
            //if the user in types in exit (we can change that if we want) exit the loop
        if(command == "exit"){
            break; 
        }
        Parser parse;
        parse.parse(command);
        TokenComposite* tokens = new TokenComposite();
        tokens->connectors = parse.getChContainer();

    
        vector<Token*> cmdList = parse.cmdsToVector();
    
        for(int i = 0; i < cmdList.size(); i++){
            tokens->commands.push_back(cmdList.at(i));
        }
    
        tokens->execute();
            
           
     }
}
    //this will iterate through the container of token objects and call execute on them
void TokenComposite::execute()
{
     
    int counter = 0; //this is so that we will execute the first time regardless of the connector after it. 
    int connectorCounter = 0; 
    bool previousSuccessFlag;  
        
    for(std::vector<BaseShell*>::iterator it = commands.begin() ; it != commands.end(); ++it){
         if(counter == 0){
            (*it)->execute();
            counter = 1; 
            previousSuccessFlag = (*it)->successFlag;
            
        }
        else if(connectors[connectorCounter] == ';'){
            (*it)->execute();
            previousSuccessFlag = (*it)->successFlag;
            connectorCounter++;
            
        }
        else if(connectors[connectorCounter] == '|'){
            if(previousSuccessFlag == 1){
                break; 
            }
            else{
                (*it)->execute();
                previousSuccessFlag = (*it)->successFlag;
            }
            connectorCounter++;
        }
        else{
            if(previousSuccessFlag == 1){
                (*it)->execute(); 
                previousSuccessFlag = (*it)->successFlag;
            }
            connectorCounter++;
        }
        
    }
}