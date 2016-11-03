#include "tokencomposite.h"

TokenComposite::TokenComposite(){}

//static variable
int TokenComposite::exitHit = 0;

void TokenComposite::shellLoop()
{
    //get user login info
    login = getpwuid(getuid());
    //get user hostname
    gethostname(hostname, sizeof hostname);
    
    while(exitHit == 0){
        //output login and host name info
        std::cout << (login->pw_name);
        std::cout << "@";
        std::cout << hostname << "$";
        
        //get user input
        getline(cin, command);

        //if the user in types in exit exit the loop
        if(command == "exit"){
            break;
        }
        //we pass the user string ito the parser
        Parser parse;
        parse.parse(command); //we then populate the connectors vector
        TokenComposite* tokens = new TokenComposite();
        tokens->connectors = parse.getChContainer();
        vector<Token*> cmdList = parse.cmdsToVector(); //populate the vector of token objects
        for(unsigned int i = 0; i < cmdList.size(); i++){
            tokens->commands.push_back(cmdList.at(i));
        }
        //execute the programs
        tokens->execute();
    }
}
//this will iterate through the container of token objects and call execute on them
void TokenComposite::execute()
{

    int counter = 0; //this is so that we will execute the first time regardless of the connector after it.
    int connectorCounter = 0; //this will be used to iterate through the vector of connectors
    bool previousSuccessFlag; //this keep track whether the last command executed successfully 
    const char* ex  = "exit"; //exit command

    for(std::vector<BaseShell*>::iterator it = commands.begin() ; it != commands.end(); ++it){
        //if the user entered in the exit command set the flag to 1 so that it the program will end
        if(strcmp(ex, (*it)->command[0]) == 0){
            exitHit = 1; 
            break; 
        }
        //this will be the first command which always executes
        else if(counter == 0){
            (*it)->execute();
            counter = 1;
            previousSuccessFlag = (*it)->successFlag;

        }
        //if ; execcute regardless of previous success flag
        else if(connectors[connectorCounter] == ';'){
            (*it)->execute();
            previousSuccessFlag = (*it)->successFlag;
            connectorCounter++;

        }
        //if || the only execute if the previous command was not successfull 
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
        //&& will execute only if last command was successfull
        else{
            if(previousSuccessFlag == 1){
                (*it)->execute();
                previousSuccessFlag = (*it)->successFlag;
            }
            connectorCounter++;
        }

    }
}
