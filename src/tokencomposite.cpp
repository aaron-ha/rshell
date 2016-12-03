#include "tokencomposite.h"

TokenComposite::TokenComposite(){}


void TokenComposite::shellLoop()
{
    //get user login info
    login = getpwuid(getuid());
    //get user hostname
    gethostname(hostname, sizeof hostname);
    char cwd[1024];
    setenv("OLDPWD", getenv("PWD"), 1);
    while(exitHit == 0){
        //output login and host name info
        std::cout << (login->pw_name);
        std::cout << "@";
        std::cout << hostname;
        std::cout << getcwd(cwd, sizeof(cwd));
        std::cout << " $";
        
        //get user input
        getline(cin, command);
        if(validateString(command)){
            //if the user in types in exit exit the loop
            if(command == "exit"){
                break;
            }
            //loop
            //we pass the user string ito the parser
            Parser parse;
            parse.parse(command); //we then populate the connectors vector
            TokenComposite* tkn = new TokenComposite();
            tkn->connectors = parse.getChContainer();
            vector<Token*> cmdList = parse.cmdsToVector(); //populate the vector of token objects
            for(unsigned int i = 0; i < cmdList.size(); i++){
                tkn->commands.push_back(cmdList.at(i));
            }
            //execute the programs
            tkn->execute();
        }
        else{
            std::cout << "Error: missing expected character" << std::endl; 
       }
    }
}
//this will iterate through the container of token objects and call execute on them
void TokenComposite::execute()
{
    int counter = 0; //this is so that we will execute the first time regardless of the connector after it.
    int connectorCounter = 0; //this will be used to iterate through the vector of connectors
    bool previousSuccessFlag; //this keep track whether the last command executed successfully 
    const char* ex  = "exit"; //exit command
    
    for(std::vector<Token*>::iterator it = commands.begin() ; it != commands.end(); ++it){
        //this will be the first command which always executes
        if(counter == 0){
            (*it)->execute();
            counter = 1;
            previousSuccessFlag = (*it)->successFlag;

        }
        
        //if ; execcute regardless of previous success flag
        else if(connectors[connectorCounter] == ';'){
            //if the user entered in the exit command set the flag to 1 so that it the program will end
            if((*it)->tokens.size() == 0){
                if(strcmp(ex, (*it)->command[0]) == 0){
                    exitHit = 1; 
                    break; 
                }
                else{
                        (*it)->execute();
                        previousSuccessFlag = (*it)->successFlag;
                        connectorCounter++;
                    }
            }
            else{
                (*it)->execute();
                previousSuccessFlag = (*it)->successFlag;
                connectorCounter++;
            }
     }
        //if || the only execute if the previous command was not successfull 
        else if(connectors[connectorCounter] == '|'){
            if(previousSuccessFlag == 1){
                previousSuccessFlag = 1; 
            }
            else{
                //if the user entered in the exit command set the flag to 1 so that it the program will end
                if((*it)->tokens.size() == 0){
                    if(strcmp(ex, (*it)->command[0]) == 0){
                        exitHit = 1; 
                        break; 
                    }
                    else {
                        (*it)->execute();
                        previousSuccessFlag = (*it)->successFlag;
                    }
                }
                else {
                    (*it)->execute();
                    previousSuccessFlag = (*it)->successFlag;
                }
            }
            connectorCounter++;
        }
        //&& will execute only if last command was successfull
        else{
            if(previousSuccessFlag == 1){
                //if the user entered in the exit command set the flag to 1 so that it the program will end
                if((*it)->tokens.size() == 0){
                    if(strcmp(ex, (*it)->command[0]) == 0){
                        exitHit = 1; 
                        break; 
                    }
                    else{
                        (*it)->execute();
                        previousSuccessFlag = (*it)->successFlag;
                    }
                }
                else
                {
                    (*it)->execute();
                    previousSuccessFlag = (*it)->successFlag;
                    connectorCounter++;
                }
                
            }
            connectorCounter++;
        }
        previousSuccessFlag = (*it)->successFlag && previousSuccessFlag; 
    }
}

bool TokenComposite::validateString(string str){
    string newStr = str;
    bool leftFlag = false;
    bool rightFlag = false; 
    int leftCount = 0; 
    int rightCount = 0; 
    size_t hash_found = str.find_first_of('#');             //truncates the string by shaving off the comments found after the pound symbol
    if(hash_found != string::npos){
        newStr = str.substr(0, hash_found);                 //creates a new string without the comments
    }  
    for(unsigned i = 0; i < newStr.length(); i++){
        int temp = i;
        if(newStr[i] == '('){
            temp++;
            while(newStr[temp] == ' ' || newStr[temp] == ')'){
                if(newStr[temp] == ')')
                    return false;
                temp++; 
            }
            leftFlag = true;
            leftCount++; 
        }
    }
    for(unsigned i = 0; i < newStr.length(); i++){
        int temp = i; 
        if(newStr[i] == ')'){
            temp++;
            while(newStr[temp] == ' ' || newStr[temp] == '('){
                if(newStr[temp] == '(')
                    return false;
                temp++;
            }
            rightFlag = true;
            rightCount++;
        }
    }
    if(((!leftFlag && !rightFlag) || (rightFlag && leftFlag)) && (rightCount == leftCount)){
        return true; 
    }
    return false; 
}
