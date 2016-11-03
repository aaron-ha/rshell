#include "TokenComposite.h"

TokenComposite::~TokenComposite(){
    //delete tokens;
}

TokenComposite::TokenComposite(){}

int TokenComposite::exitHit = 0;

void TokenComposite::shellLoop()
{
    login = getpwuid(getuid());
    gethostname(hostname, sizeof hostname);
    while(exitHit == 0){
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
        delete tokens;

    }
}
//this will iterate through the container of token objects and call execute on them
void TokenComposite::execute()
{

    int counter = 0; //this is so that we will execute the first time regardless of the connector after it.
    int connectorCounter = 0;
    bool previousSuccessFlag;
    const char* ex  = "exit";  

    for(std::vector<BaseShell*>::iterator it = commands.begin() ; it != commands.end(); ++it){
        if(strcmp(ex, (*it)->command[0]) == 0){
            exitHit = 1; 
            break; 
        }
        else if(counter == 0){
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
