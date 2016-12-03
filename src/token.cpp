#include "token.h"
#include <string>
Token::Token(){
    successFlag = true;
}

Token::Token(const char** argv) { //take in parsed argument 
    command = argv; 
    successFlag = true;
}


//this will execute the program using fork and execvp
void Token::execute(){
    pid_t pid;
    pid_t waitId;
    int status;
    if(this->tokens.size() != 0){
        executeTree(tokens); 
    }
    else if(strcmp(command[0], "test") == 0 || strcmp(command[0], "[") == 0){
        test(command); 
    }
    else if(strcmp(command[0], "cd") == 0){
        cd(command); 
    }
    else{
        //forks into two processes
        pid = fork();
        //There was an error during fork
        if (pid < 0){

            perror("There was an error");
        }
        else if (pid == 0){
            //must be cast because our function expects a char *const argv[]
            if (execvp(command[0], (char**)command)  < 0){
                //error at execvp
                perror("There was an error executing the process");
            }
            exit(EXIT_FAILURE);
        }
        //forking was sucessful, go to parent process and wait for child to complete.
        else{
            do{
                waitId = wait(&status);
                if(status != 0){ //if the status is not zero, then the user entered an invalid argument
                    successFlag = false;
                }
                if(waitId == -1){
                    perror("Error in parent process");
                    exit(EXIT_FAILURE);
                }
            }
            //when child exits or ternimated by signal call stop waiting
            while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
}

void Token::test(const char** command){
    struct stat sb; 
    
    int sizeOfCommand = 0;  
    for(int i = 0; command[i]!= NULL; i++){
        sizeOfCommand++; 
    }
    
    if(strcmp(command[0], "[") == 0 && strcmp(command[sizeOfCommand-1], "]") != 0){
        std::cout << "bash: [: missing ']" << std::endl;
    }
    else if(strcmp(command[1], "-e") == 0){
        if (stat(command[2], &sb) == -1) {
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            perror("File Status:");
        }
        else{
            std::cout << "(True)" << std::endl; 
        }
        
    }
    else if(strcmp(command[1], "-f" ) == 0){
        if (stat(command[2], &sb) == -1) {
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            perror("File Status:");
        }
        else if(S_ISREG(sb.st_mode)){
            std::cout << "(True)" << std::endl; 
        }
        else{
            std::cout << "(False)" << std::endl; 
        }

    }
    else if(strcmp(command[1], "-d" ) == 0){
        if (stat(command[2], &sb) == -1) {
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            perror("File Status:");
            
        }
        else if(S_ISDIR(sb.st_mode)){
            std::cout << "(True)" << std::endl; 
        }
        else{
            std::cout << "(False)" << std::endl; 
        }

    }
    else{
        if (stat(command[1], &sb) == -1) {
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            perror("File Status:");

        }
        else{
            std:: cout << "(True)" << std::endl; 
        }
    }
}

void Token::executeTree(std::vector<Token*> commands){

    int counter = 0; //this is so that we will execute the first time regardless of the connector after it.
    int connectorCounter = 0; //this will be used to iterate through the vector of connectors
    bool previousSuccessFlag; //this keep track whether the last command executed successfully 
    const char* ex  = "exit"; //exit command
    for(std::vector<Token*>::iterator it = commands.begin() ; it != commands.end(); ++it){

        //this will be the first command which always executes
        if(counter == 0){
            //if the user entered in the exit command set the flag to 1 so that it the program will end
            if(strcmp(ex, (*it)->command[0]) == 0){
                exit(EXIT_SUCCESS); 
            }
            else{
                (*it)->execute();
                counter = 1;
                previousSuccessFlag = (*it)->successFlag;
            }

        }
        //if ; execcute regardless of previous success flag
        else if(Tkconnectors[connectorCounter] == ';'){
            //if the user entered in the exit command set the flag to 1 so that it the program will end
            if(strcmp(ex, (*it)->command[0]) == 0){
                exit(EXIT_SUCCESS);
            }
            else{
                (*it)->execute();
                previousSuccessFlag = (*it)->successFlag;
                connectorCounter++;
           }

        }
        //if || the only execute if the previous command was not successfull 
        else if(Tkconnectors[connectorCounter] == '|'){
            if(previousSuccessFlag == 1){
                previousSuccessFlag = 1; 
            }
            else{
                //if the user entered in the exit command set the flag to 1 so that it the program will end
                if(strcmp(ex, (*it)->command[0]) == 0){
                    exit(EXIT_SUCCESS); 
                }
                else{
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
                if(strcmp(ex, (*it)->command[0]) == 0){
                    // tokenComposite.exitHit = 1; 
                    exitHit = 1;
                    break; 
                }
                else{
                    (*it)->execute();
                    previousSuccessFlag = (*it)->successFlag;
                }
            }
            connectorCounter++;
        }
        successFlag = (*it)->successFlag && successFlag; 
    }
}

void Token::cd(const char** command){
    
    //this is the buffer for getcwd
    char cwd[1024];
    std::string str = getcwd(cwd, sizeof(cwd));
    size_t pos = str.find_last_of("/\\");
    std::string newStr = str.substr(pos+1);
    //used for cd - swap
    const char* temp; 
    //if user enter in just cd
    if(!command[1]){
       
        if(chdir(getenv("HOME")) == -1 ){
            perror("Error changing directores"); 
            successFlag = false; 
        }
        else{
             setenv("OLDPWD", getenv("PWD"), 1); 
             setenv("PWD", getenv("HOME"), 1);
        }
    }
    //if user enters in cd -
    else if(strcmp(command[1] , "-") == 0){
        if(chdir(getenv("OLDPWD")) == -1){
            perror("Error changing directores");
            successFlag = false; 
        }
        else{
            temp = getenv("PWD");
            setenv("PWD", getenv("OLDPWD"), 1); 
            setenv("OLDPWD", temp, 1); 
        }
      
    }
    //if user enters in cd + path
    else{
        if(strcmp(newStr.c_str(), command[1]) != 0){
            
            if(chdir(command[1]) == -1 ){
                perror("Error changing directores"); 
                successFlag = false; 
            }
            else{
                setenv("OLDPWD", getenv("PWD"), 1); 
                setenv("PWD", getcwd(cwd, sizeof(cwd)), 1); 
            }
        }
    }
    
}