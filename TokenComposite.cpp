#include "BasehShell.h"
class TokenComposite : public BaseShell {
    
    //I'm hoping that the parser will be able to parse the String input into these token objects
    std::vector<Token*> commands; 
    
    //this will iterate through the container of token objects and call execute on them
    int execute(){};
    
}