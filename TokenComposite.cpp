#include "BaseShell.h"
//#include<unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
//#include "Parser.cpp"
#include "Token.h"
#include "TokenComposite.h"

    void TokenComposite::shelloop()
    {
        
        while(1){
            std::cout << "$ " << std::endl;
            
            //get user input
            std::cin >> argv; 
            
            //if the user in types in exit (we can change that if we want) exit the loop
            if(argv == "exit"){
               break; 
            }
            
            //pass argument into parser
            //parser(argv); 
            
            
            // commands = parser.SomeFunctionThatReturnsVector
            
            //will iterate through vector container calling execute on the children
            execute();
                
                
        }
    }
    //this will iterate through the container of token objects and call execute on them
    void TokenComposite::execute()
    {
        for(std::vector<BaseShell*>::iterator it = commands.begin() ; it != commands.end(); ++it)
        {
            (*it)->execute();
        }
    }
    
