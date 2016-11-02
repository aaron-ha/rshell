#include "BaseShell.h"
//#include<unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "Parser.h"
#include "Token.h"
#include "TokenComposite.h"

    void TokenComposite::shelloop()
    {
        
        while(1){
            std::cout << "$ " << std::endl;
            
            //get user input
            getline(cin, argv); 
            
            //if the user in types in exit (we can change that if we want) exit the loop
            if(argv == "exit"){
               break; 
            }
            
            //pass argument into parser
            //parse(argv); 
            
            
            //commands = parse.cmdToVector(); 
            
            //will iterate through vector container calling execute on the children
            execute();
                
                
        }
    }
    //this will iterate through the container of token objects and call execute on them
    void TokenComposite::execute()
    {
        //connectors = parser.getChContainer(); 
        connectors.push_back('&'); 
        connectors.push_back(';'); 
        int counter = 0; //this is so that we will execute the first time regardless of the connector after it. 
        int connectorCounter = 0; 
        int previousSuccessFlag;  
        
        for(std::vector<BaseShell*>::iterator it = commands.begin() ; it != commands.end(); ++it)
        {
           if(counter == 0)
            {
                (*it)->execute();
                counter = 1; 
                previousSuccessFlag = (*it)->successFlag;
                
            }
            else if(connectors[connectorCounter] == ';')
            {
                (*it)->execute();
                previousSuccessFlag = (*it)->successFlag;
                connectorCounter++;
                
            }
            else if(connectors[connectorCounter] == '|')
            {
                if(previousSuccessFlag == 1)
                {
                    break; 
                }
                else
                {
                    (*it)->execute();
                    previousSuccessFlag = (*it)->successFlag;
                }
                connectorCounter++;
            }
            else
            {
                if(previousSuccessFlag == 1)
                {
                    (*it)->execute(); 
                    previousSuccessFlag = (*it)->successFlag;
                }
                connectorCounter++;
            }
            
        }
    }
    
