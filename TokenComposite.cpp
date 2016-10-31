#include "BasehShell.h"
class TokenComposite : public BaseShell 
{
    
    private: 
        string argv; 
        Parser parser; 
        std::vector<BaseShell*> commands; 
    public: 
    //I'm hoping that the parser will be able to parse the String input into these objects
    
    void shelloop()
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
            parser(argv); 
            
            //we need our vector container in THIS class (look at our private declarations up above)
            //to be assigned from the data in our parser class. I suggest we make our function in Parser.cpp have a function 
            //that returns a vector<BaseShell*> so we can simply assign it below. 
            
            // commands = parser.SomeFunctionThatReturnsVector
            
            //will iterate through vector container calling execute on the children
            execute();
                
                
        }
    }
    //this will iterate through the container of token objects and call execute on them
    void execute()
    {
        for(std::vector<BaseShell*>::iterator it = commands.begin() ; it != commands.end(); ++it)
        {
            *it->execute();
        }
    }
    
}